#include "vcsprojecttracker.h"

vcsProjectTracker::vcsProjectTracker(IVersionControlSystem* vcs, const wxString& projectPath) :
    m_ProjectState(Item_Untracked),
    m_Vcs(*vcs)
{
}

vcsProjectTracker::~vcsProjectTracker()
{
    delete &m_Vcs;
}
