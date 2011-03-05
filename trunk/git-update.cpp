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

#include "git-update.h"
#include "VcsTreeItem.h"
#include "icommandexecuter.h"
#include "git.h"

GitUpdateOp::GitUpdateOp(git& vcs,
                        const wxString& vcsRootDir,
                        ICommandExecuter& shellUtils) :
                        GitOp(vcs, vcsRootDir, shellUtils)
{
    m_StatusXlat[_("R ")] = Item_Added;
    m_StatusXlat[_(" M")] = Item_Modified;
    m_StatusXlat[_("D ")] = Item_Removed;
    m_StatusXlat[_("A ")] = Item_Added;
    m_StatusXlat[_(" D")] = Item_Missing;
    m_StatusXlat[_("??")] = Item_Untracked;
}

void GitUpdateOp::ParseStatus(const wxString& statusLine,
                              wxString& statusFlag,
                              wxString& fileName) const
{
    statusFlag = statusLine.Mid(0, 2);
    if(statusFlag == _("R "))
    {
        fileName = statusLine.AfterLast('>');
        fileName = fileName.Trim(false);
    }
    else
    {
        fileName = statusLine.Mid(3);
    }
}


bool GitUpdateOp::SetStatusFromOutput(VcsTreeItem* Item, wxArrayString& Output) const
{
    for (size_t i = 0; i < Output.GetCount(); ++i)
    {
        wxString relativeFilename = Item->GetRelativeName(m_VcsRootDir);
        if(relativeFilename.length() == 0)
        {
            continue;
        }

        wxString Status;
        wxString Name;

        ParseStatus(Output[i], Status, Name);

        if(relativeFilename == Name)
        {
            std::map<wxString, ItemState>::const_iterator it;
            it = m_StatusXlat.find(Status);
            if(it != m_StatusXlat.end())
            {
                Item->SetState(it->second);
            }
            Output.RemoveAt(i);
            return true;
        }
        else if (Name.Right(1) == _("/") && relativeFilename.StartsWith(Name))
        {
            if(Status == _("??"))
            {
                Item->SetState(Item_Untracked);
                Output.RemoveAt(i);
                return true;
            }
        }
    }

    return false;
}

void GitUpdateOp::ApplyStatus(std::vector<VcsTreeItem*>& proj_files, wxArrayString& Output) const
{
    std::vector<VcsTreeItem*>::iterator fi;

    DumpOutput(Output);

    for(fi = proj_files.begin(); fi != proj_files.end(); fi++)
    {
        VcsTreeItem* pf = *fi;

        wxString relativeFilename;

        relativeFilename = pf->GetRelativeName(m_VcsRootDir);

        if(relativeFilename.length() == 0)
        {
            continue;
        }

        if(!SetStatusFromOutput(pf, Output))
        {
            // File not found in output list. It could either be missing (untracked) or
            // up-to-date
            if(m_ShellUtils.FileExists(relativeFilename))
            {
                pf->SetState(Item_UpToDate);
            }
            else
            {
                pf->SetState(Item_UntrackedMissing);
            }
        }
        pf->VisualiseState();
    }
}

void GitUpdateOp::ExecuteImplementation(std::vector<VcsTreeItem*>& itemList) const
{
    wxArrayString outCapture, errCapture;
    m_ShellUtils.execute(_("git status --porcelain"), outCapture, errCapture);
    ApplyStatus(itemList, outCapture);
}
