#include "IVersionControlSystem.h"

IVersionControlSystem::IVersionControlSystem(const wxString& project,
                                             const VcsFileOp& update,
                                             const VcsFileOp& add,
                                             const VcsFileOp& remove,
                                             const VcsFileOp& commit,
                                             const VcsFileOp& revert) :
    UpdateOp(update),
    AddOp(add),
    RemoveOp(remove),
    CommitOp(commit),
    RevertOp(revert),
    m_project(project)
{
    //ctor
}

IVersionControlSystem::~IVersionControlSystem()
{
    //dtor
}
