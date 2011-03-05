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
#include "gitcommitop.h"
#include "CommitMsgDialog.h"
#include <manager.h>

/***********************************************************************
 *  Method: GitCommitOp::execute
 *  Params: std::vector<VcsTreeItem *> &
 * Returns: void
 * Effects:
 ***********************************************************************/
void GitCommitOp::ExecuteImplementation(std::vector<VcsTreeItem*>& pathList) const
{
    wxString path_string;
    wxArrayString item_list;

    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=pathList.begin(); i!= pathList.end(); i++)
    {
        AddCommitItem(item_list, *i);
    }

    if(item_list.size() == 0)
    {
        return;
    }

    wxString msg;
    CommitMsgDialog dlg(Manager::Get()->GetAppWindow(), msg, item_list);

    DumpOutput(item_list);

    if(dlg.ShowModal() == wxID_OK)
    {
        wxArrayString outCapture, errCapture;
        m_ShellUtils.execute(BuildCommitCmd(msg, item_list), outCapture, errCapture);
    }
}


/***********************************************************************
 *  Method: GitCommitOp::BuildCommitCmd
 *  Params: const wxString &CommitMsg, const wxArrayString &ItemList
 * Returns: wxString
 * Effects:
 ***********************************************************************/
wxString GitCommitOp::BuildCommitCmd(const wxString &CommitMsg, const wxArrayString &ItemList) const
{
    wxString Command = _("git commit -m " + CommitMsg);

    for(unsigned int i=0; i<ItemList.Count(); i++)
    {
        Command += _(" ") + ItemList[i];
    }

    return Command;
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
    wxString relativeFilename = FileItem->GetRelativeName(m_VcsRootDir);

    if(relativeFilename.length() == 0)
    {
        return;
    }

    if(FileItem->GetState() == Item_Added
            || FileItem->GetState() == Item_Modified
            || FileItem->GetState() == Item_Removed)
    {
        ItemList.Add(relativeFilename);
    }
}


