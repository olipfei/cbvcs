/***********************************************************************
 * AUTHOR: Dushara Jayasinghe <dushara>
 *   FILE: .//gitcommitop.cpp
 *   DATE: Sun Feb 20 20:44:12 2011
 *  DESCR:
 ***********************************************************************/
#include "gitcommitop.h"

/***********************************************************************
 *  Method: GitCommitOp::execute
 *  Params: std::vector<VcsTreeItem *> &
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitCommitOp::ExecuteImplementation(std::vector<VcsTreeItem*>&) const
{
}


/***********************************************************************
 *  Method: GitCommitOp::BuildCommitCmd
 *  Params: const wxString &CommitMsg, const wxArrayString &ItemList
 * Returns: wxString
 * Effects:
 ***********************************************************************/
wxString
GitCommitOp::BuildCommitCmd(const wxString &CommitMsg, const wxArrayString &ItemList) const
{
    wxString dummy;

    return dummy;
}


/***********************************************************************
 *  Method: GitCommitOp::AddCommitItem
 *  Params: wxArrayString &ItemList, VcsTreeItem *FileItem
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitCommitOp::AddCommitItem(wxArrayString &ItemList, VcsTreeItem *FileItem) const
{
}


