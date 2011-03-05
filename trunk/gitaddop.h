#ifndef GITADDOP_H_INCLUDED
#define GITADDOP_H_INCLUDED

#include "gitop.h"
#include "VcsTreeItem.h"

class GitAddOp : public GitOp
{
    public:
        GitAddOp(git& vcs,
                 const wxString& vcsRootDir,
                 ICommandExecuter& shellUtils) : GitOp(vcs, vcsRootDir, shellUtils) {}

    private:
        virtual void ExecuteImplementation(std::vector<VcsTreeItem*>&) const;
};


#endif // GITADDOP_H_INCLUDED
