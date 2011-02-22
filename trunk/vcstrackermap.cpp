#include "vcstrackermap.h"
#include "vcsfactory.h"

VcsTrackerMap::~VcsTrackerMap()
{
    std::map<const wxString, vcsProjectTracker*>::iterator i;

    for(i=m_Map.begin(); i != m_Map.end(); i++)
    {
        Remove(i);
    }
}

vcsProjectTracker* VcsTrackerMap::Find(const wxString& prjFilename) const
{
    std::map<const wxString, vcsProjectTracker*>::const_iterator i;

    i = m_Map.find(prjFilename);
    if(i == m_Map.end())
    {
        return 0;
    }

    return i->second;
}

bool VcsTrackerMap::CreateTracker(const wxString& prjFilename)
{
    if(Find(prjFilename))
    {
        return true;
    }

    IVersionControlSystem* vcs = VcsFactory::GetVcs(prjFilename);

    if(!vcs)
    {
        // Project not controlled
        return false;
    }

    vcsProjectTracker* prjTracker = new vcsProjectTracker(vcs, prjFilename);
    m_Map[prjFilename] = prjTracker;

    return true;
}

void VcsTrackerMap::Remove(std::map<const wxString, vcsProjectTracker*>::iterator i)
{
    vcsProjectTracker* tracker = i->second;
    delete tracker;
    m_Map.erase(i);
}

bool VcsTrackerMap::RemoveTracker(const wxString& prjFilename)
{
    std::map<const wxString, vcsProjectTracker*>::iterator i;

    i = m_Map.find(prjFilename);
    if(i == m_Map.end())
    {
        return false;
    }

    Remove(i);
    return true;
}

vcsProjectTracker* VcsTrackerMap::GetTracker(const wxString& prjFilename)
{
    return Find(prjFilename);
}
