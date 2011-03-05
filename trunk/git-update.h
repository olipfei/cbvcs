#ifndef GIT_UPDATE_H
#define GIT_UPDATE_H

#include "gitop.h"
#include "VcsTreeItem.h"

class ICommandExecuter;
enum ItemState;

class GitUpdateOp : public GitOp
{
    public:
        GitUpdateOp(git& vcs,
                    const wxString& vcsRootDir,
                    ICommandExecuter& shellUtils);

    private:
        std::map<wxString, ItemState> m_StatusXlat;

        virtual void ExecuteImplementation(std::vector<VcsTreeItem*>&) const;
        bool SetStatusFromOutput(VcsTreeItem* Item, wxArrayString& Output) const;
        void ParseStatus(const wxString& statusLine, wxString& statusFlag, wxString& fileName) const;
        void ApplyStatus(std::vector<VcsTreeItem*>&, wxArrayString&) const;
};

#endif
