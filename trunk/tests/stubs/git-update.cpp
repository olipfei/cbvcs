/***********************************************************************
 * AUTHOR: Dushara Jayasinghe <dushara>
 *   FILE: .//git-update.cpp
 *   DATE: Mon Feb 21 19:48:48 2011
 *  DESCR:
 ***********************************************************************/
#include "git-update.h"

/***********************************************************************
 *  Method: GitUpdateOp::GitUpdateOp
 *  Params: git &vcs, const ICommandExecuter &cmdExecutor
 * Effects:
 ***********************************************************************/
GitUpdateOp::GitUpdateOp(git& vcs,
                        const wxString& vcsRootDir,
                        ICommandExecuter& shellUtils) :
     GitOp(vcs, vcsRootDir, shellUtils)
{
}


/***********************************************************************
 *  Method: GitUpdateOp::execute
 *  Params: std::vector<VcsTreeItem *> &
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitUpdateOp::ExecuteImplementation(std::vector<VcsTreeItem *> &) const
{
}


/***********************************************************************
 *  Method: GitUpdateOp::SetStatusFromOutput
 *  Params: VcsTreeItem *Item, wxArrayString &Output
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
GitUpdateOp::SetStatusFromOutput(VcsTreeItem *Item, wxArrayString &Output) const
{
    bool dummy;

    return dummy;
}


/***********************************************************************
 *  Method: GitUpdateOp::ParseStatus
 *  Params: const wxString &statusLine, wxString &statusFlag, wxString &fileName
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitUpdateOp::ParseStatus(const wxString &statusLine, wxString &statusFlag, wxString &fileName) const
{
}


/***********************************************************************
 *  Method: GitUpdateOp::ApplyStatus
 *  Params: std::vector<VcsTreeItem *> &, wxArrayString &
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitUpdateOp::ApplyStatus(std::vector<VcsTreeItem *> &, wxArrayString &) const
{
}


