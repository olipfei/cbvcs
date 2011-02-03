#ifndef IVERSIONCONTROLSYSTEM_H
#define IVERSIONCONTROLSYSTEM_H

#include <globals.h>
#include <vector>
#include <map>

class wxString;
class ProjectFile;

#include "VcsFileOp.h"

class IVersionControlSystem
{
    public:
        IVersionControlSystem(const wxString& project,
                              const VcsFileOp& update,
                              const VcsFileOp& add,
                              const VcsFileOp& remove,
                              const VcsFileOp& commit,
                              const VcsFileOp& revert);
        virtual ~IVersionControlSystem();

        const VcsFileOp& UpdateOp;
        const VcsFileOp& AddOp;
        const VcsFileOp& RemoveOp;
        virtual bool move(std::vector<VcsTreeItem*>&) = 0;
        const VcsFileOp& CommitOp;
        const VcsFileOp& RevertOp;

    protected:
        const wxString& m_project;
    private:
};

#endif // IVERSIONCONTROLSYSTEM_H
