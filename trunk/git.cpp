#include <logmanager.h>
#include <wx/string.h>
#include "git.h"
#include "CommitMsgDialog.h"
#include "VcsTreeItem.h"

git::git(const wxString& project) :
    m_GitUpdate(*this),
    m_GitAdd(*this),
    m_GitRemove(*this),
    m_GitCommit(*this),
    m_GitRevert(*this),
    IVersionControlSystem(project, m_GitUpdate, m_GitAdd, m_GitRemove, m_GitCommit, m_GitRevert)
{
    Manager::Get()->GetLogManager()->Log( _("git()") + project );
    //ctor
}

git::~git()
{
    //dtor
}

bool GitUpdateOp::IsOutsideRepo(const wxString& file) const
{
    return (file.compare(0, 2, _(".."))) == 0;
}

bool GitUpdateOp::SetStatusFromOutput(VcsTreeItem* Item, wxArrayString& Output) const
{
    for (size_t i = 0; i < Output.GetCount(); ++i)
    {
        wxString Status = Output[i].Mid(0, 2);
        wxString Name = Output[i].Mid(3);

        Manager::Get()->GetLogManager()->Log( _("  vcs:") + Name );
        if(Item->GetName() == Name)
        {
            if(Status == _(" M"))
            {
                Item->SetState(Item_Modified);
            }
            else if(Status == _("D "))
            {
                Item->SetState(Item_Removed);
            }
            else if(Status == _("A "))
            {
                Item->SetState(Item_Added);
            }
            else if(Status == _(" D"))
            {
                Item->SetState(Item_Missing);
            }
            else if(Status == _("??"))
            {
                Item->SetState(Item_Untracked);
            }
            else
            {
                Manager::Get()->GetLogManager()->Log( Name + _(" (unknown) status = ") + Status );
            }
            Output.RemoveAt(i);
            return true;
        }
        else if (Name.Right(1) == _("/") && Item->GetName().StartsWith(Name))
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

void GitUpdateOp::ApplyStatus(std::vector<VcsTreeItem*> proj_files, wxArrayString Output) const
{
    std::vector<VcsTreeItem*>::iterator fi;

    DumpOutput(Output);

    for(fi = proj_files.begin(); fi != proj_files.end(); fi++)
    {
        VcsTreeItem* pf = *fi;

        if(IsOutsideRepo(pf->GetName()))
        {
            continue;
        }

        Manager::Get()->GetLogManager()->Log( _("prj:") + pf->GetName() );

        if(!SetStatusFromOutput(pf, Output))
        {
            // File not found in output list. It could either be missing (untracked) or
            // up-to-date
            if(wxFileExists(pf->GetName()))
            {
                pf->SetState(Item_UpToDate);
                Manager::Get()->GetLogManager()->Log( _("    (Up-to-date)") );
            }
            else
            {
                pf->SetState(Item_UntrackedMissing);
                Manager::Get()->GetLogManager()->Log( _("    (untracked-missing)"));
            }
        }
        pf->VisualiseState();
    }
}

void GitUpdateOp::execute(std::vector<VcsTreeItem*> paths) const
{
    wxString cwd = wxGetCwd();
    wxArrayString Output;
    VcsExecute(_("git status --porcelain"), Output);
    ApplyStatus(paths, Output);
    wxSetWorkingDirectory(cwd);
}

void GitAddOp::execute(std::vector<VcsTreeItem*> paths) const
{
    wxString path_string;
    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        VcsTreeItem* f = *i;
        if(f->GetState() == Item_Untracked)
        {
            path_string += _(" ") + f->GetName();
        }
    }

    if(path_string.size() != 0)
    {
        wxString cwd = wxGetCwd();
        wxArrayString Output;
        VcsExecute(_("git add") + path_string, Output);
        wxSetWorkingDirectory(cwd);
    }
}

void GitRemoveOp::execute(std::vector<VcsTreeItem*> paths) const
{
    wxString UptodateFiles;
    wxString CachedFiles;

    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        VcsTreeItem* Item = *i;
        if(Item->GetState() == Item_UpToDate
           || Item->GetState() == Item_Missing)
        {
            UptodateFiles += _(" ") + Item->GetName();
        }
        else if(Item->GetState() == Item_Added
                || Item->GetState() == Item_Modified)
        {
            CachedFiles += _(" ") + Item->GetName();
        }
    }

    wxString cwd = wxGetCwd();
    wxArrayString Output;
    if(UptodateFiles.length())
    {
        VcsExecute(_("git rm") + UptodateFiles, Output);
    }

    if(CachedFiles.length())
    {
        VcsExecute(_("git rm --cached") + CachedFiles, Output);
    }

    wxSetWorkingDirectory(cwd);
}

void GitCommitOp::AddCommitItem(wxArrayString& ItemList,VcsTreeItem* FileItem) const
{
    Manager::Get()->GetLogManager()->Log( FileItem->GetName() );

    if(FileItem->GetState() == Item_Added
            || FileItem->GetState() == Item_Modified
            || FileItem->GetState() == Item_Removed)
    {
        Manager::Get()->GetLogManager()->Log( _T("... adding") );
        ItemList.Add(FileItem->GetName());
    }
}

wxString GitCommitOp::BuildCommitCmd(const wxString& CommitMsg, const wxArrayString& ItemList) const
{
    wxString Command = _("git commit -m " + CommitMsg);

    for(unsigned int i=0; i<ItemList.Count(); i++)
    {
        Command += _(" ") + ItemList[i];
    }

    return Command;
}

void GitCommitOp::execute(std::vector<VcsTreeItem*> paths) const
{
    wxString path_string;
    wxArrayString item_list;

Manager::Get()->GetLogManager()->Log( _T("GIT COMMIT") );

    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
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
        wxString cwd = wxGetCwd();
        wxArrayString Output;
        VcsExecute(BuildCommitCmd(msg, item_list), Output);
        wxSetWorkingDirectory(cwd);
    }
}

void GitRevertOp::execute(std::vector<VcsTreeItem*> paths) const
{
    wxString path_string;
    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        path_string += _(" ") + (*i)->GetName();
    }

    wxString cwd = wxGetCwd();
    wxArrayString Output;
    VcsExecute(_("git checkout HEAD -f") + path_string, Output);
    wxSetWorkingDirectory(cwd);
}

void git::LogOutput(const wxArrayString& OutStrings)
{
    unsigned int i;

    for(i=0; i<OutStrings.Count(); i++)
    {
        Manager::Get()->GetLogManager()->Log( OutStrings[i] );
    }
}

void git::ExecuteCommand(const wxString& Command, wxArrayString& Output )
{
    wxArrayString Errors;

    wxSetWorkingDirectory(wxPathOnly(m_project));
    const long pid = wxExecute(Command, Output, Errors, wxEXEC_SYNC);

    if (pid==-1)
    {
        wxString msg = _("Failed to execute" + Command);
        cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
        return;
    }

    LogOutput(Errors);
}

void GitOp::VcsExecute(const wxString& Command, wxArrayString& Output) const
{
    Manager::Get()->GetLogManager()->Log( Command );
    m_vcs.ExecuteCommand(Command, Output);
}

void GitOp::DumpOutput(const wxArrayString& Output) const
{
    unsigned int i;

    Manager::Get()->GetLogManager()->Log( _T("Output") );
    for(i=0; i<Output.Count(); i++)
    {
        Manager::Get()->GetLogManager()->Log( Output[i] );
    }
}
