#ifndef GITCOMMITOP_H_INCLUDED
#define GITCOMMITOP_H_INCLUDED

#include "gitop.h"
#include "VcsTreeItem.h"

class GitCommitOp : public GitOp
{
    public:
        GitCommitOp(git& vcs,
                    const wxString& vcsRootDir,
                    ICommandExecuter& shellUtils) : GitOp(vcs, vcsRootDir, shellUtils) {}

    private:
        virtual void ExecuteImplementation(std::vector<VcsTreeItem*>&) const;
        wxString BuildCommitCmd(const wxString& CommitMsg, const wxArrayString& ItemList) const;
        void AddCommitItem(wxArrayString& ItemList, VcsTreeItem* FileItem) const;
};

#endif // GITCOMMITOP_H_INCLUDED
