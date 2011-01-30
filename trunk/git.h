#ifndef GIT_H
#define GIT_H

#include "IVersionControlSystem.h"

class wxArrayString;
class git;

class GitOp : public VcsFileOp
{
    public:
        GitOp(git& vcs) : m_vcs(vcs) {}

    protected:
        void VcsExecute(const wxString&, wxArrayString& ) const;
        void DumpOutput(const wxArrayString& ) const;

        git& m_vcs;

    private:
        wxString cwd;
};

class GitUpdateOp : public GitOp
{
    public:
        GitUpdateOp(git& vcs) : GitOp(vcs) {}
        virtual void execute(std::vector<VcsTreeItem*>) const;

    private:
        bool IsOutsideRepo(const wxString& file) const;
        bool SetStatusFromOutput(VcsTreeItem* Item, wxArrayString& Output) const;
        void ApplyStatus(std::vector<VcsTreeItem*>, wxArrayString) const;
};

class GitAddOp : public GitOp
{
    public:
        GitAddOp(git& vcs) : GitOp(vcs) {}
        virtual void execute(std::vector<VcsTreeItem*>) const;
};

class GitRemoveOp : public GitOp
{
    public:
        GitRemoveOp(git& vcs) : GitOp(vcs) {}
        virtual void execute(std::vector<VcsTreeItem*>) const;
};

class GitCommitOp : public GitOp
{
    public:
        GitCommitOp(git& vcs) : GitOp(vcs) {}
        virtual void execute(std::vector<VcsTreeItem*>) const;
    private:
        wxString BuildCommitCmd(const wxString& CommitMsg, const wxArrayString& ItemList) const;
        void AddCommitItem(wxArrayString& ItemList, VcsTreeItem* FileItem) const;
};

class GitRevertOp : public GitOp
{
    public:
        GitRevertOp(git& vcs) : GitOp(vcs) {}
        virtual void execute(std::vector<VcsTreeItem*>) const;
};

class git : public IVersionControlSystem
{
    public:
        git(const wxString& project);
        virtual ~git();

        virtual bool move(std::vector<VcsTreeItem*>) {}

    protected:
        friend class GitOp;
        void ExecuteCommand(const wxString&, wxArrayString& );

    private:
        GitUpdateOp m_GitUpdate;
        GitAddOp m_GitAdd;
        GitRemoveOp m_GitRemove;
        GitCommitOp m_GitCommit;
        GitRevertOp m_GitRevert;

        void LogOutput(const wxArrayString& OutStrings);
};

#endif // GIT_H
