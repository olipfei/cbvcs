/*  cbvcs Code::Blocks version control system plugin

    Copyright (C) 2011 Dushara Jayasinghe.

    cbvcs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cbvcs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cbvcs.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "vcstrackermap.h"
#include "vcsfactory.h"
#include "icommandexecuter.h"

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

bool VcsTrackerMap::CreateTracker(const wxString& prjFilename,
                                  ICommandExecuter& shellUtils)
{
    if(Find(prjFilename))
    {
        return true;
    }

    IVersionControlSystem* vcs = VcsFactory::GetVcs(prjFilename, shellUtils);

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
