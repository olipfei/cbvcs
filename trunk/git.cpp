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
    m_GitRoot(wxPathOnly(project)),
    IVersionControlSystem(project, m_GitUpdate, m_GitAdd, m_GitRemove, m_GitCommit, m_GitRevert)
{
    Manager::Get()->GetLogManager()->Log( _("git()") + project );
    //ctor
}

git::~git()
{
    //dtor
}

/*static*/ bool git::IsGitRepo(const wxString& project)
{
    wxString cwd = wxGetCwd();
    wxString Command = _("git rev-parse --show-toplevel");
    wxArrayString Output, Errors;

    wxSetWorkingDirectory(wxPathOnly(project));
    const long pid = wxExecute(Command, Output, Errors, wxEXEC_SYNC);

    if (pid==-1)
    {
        wxString msg = _("Failed to execute" + Command);
        cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK, Manager::Get()->GetAppWindow());
        return false;
    }

    wxSetWorkingDirectory(cwd);

    return Output.Count() != 0;
}

bool GitUpdateOp::SetStatusFromOutput(VcsTreeItem* Item, wxArrayString& Output) const
{
    for (size_t i = 0; i < Output.GetCount(); ++i)
    {
        wxString Status = Output[i].Mid(0, 2);
        wxString Name = Output[i].Mid(3);

        Manager::Get()->GetLogManager()->Log( _("  vcs:") + Name );

        wxString relativeFilename = Item->GetRelativeName(GitRoot());
        if(relativeFilename.length() == 0)
        {
            continue;
        }

        if(relativeFilename == Name)
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

        relativeFilename = pf->GetRelativeName(GitRoot());
        if(relativeFilename.length() == 0)
        {
            Manager::Get()->GetLogManager()->Log( _("reject:") + relativeFilename );
            continue;
        }

        Manager::Get()->GetLogManager()->Log( _("prj:") + relativeFilename );

        if(!SetStatusFromOutput(pf, Output))
        {
            // File not found in output list. It could either be missing (untracked) or
            // up-to-date
            if(wxFileExists(relativeFilename))
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
    Manager::Get()->GetLogManager()->Log( _("Apply Complete") );
}

void GitUpdateOp::execute(std::vector<VcsTreeItem*>& paths) const
{
    wxString cwd = wxGetCwd();
    wxArrayString Output;
    VcsExecute(_("git status --porcelain"), Output);
    ApplyStatus(paths, Output);
    wxSetWorkingDirectory(cwd);
}

void GitAddOp::execute(std::vector<VcsTreeItem*>& paths) const
{
    wxString path_string;
    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        VcsTreeItem* f = *i;

        wxString relativeFilename = f->GetRelativeName(GitRoot());
        if(relativeFilename.length() == 0)
        {
            continue;
        }

        if(f->GetState() == Item_Untracked)
        {
            path_string += _(" ") + relativeFilename;
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

void GitRemoveOp::execute(std::vector<VcsTreeItem*>& paths) const
{
    wxString UptodateFiles;
    wxString CachedFiles;

    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        VcsTreeItem* Item = *i;

        wxString relativeFilename = Item->GetRelativeName(GitRoot());
        if(relativeFilename.length() == 0)
        {
            continue;
        }

        if(Item->GetState() == Item_UpToDate
           || Item->GetState() == Item_Missing)
        {
            UptodateFiles += _(" ") + relativeFilename;
        }
        else if(Item->GetState() == Item_Added
                || Item->GetState() == Item_Modified)
        {
            CachedFiles += _(" ") + relativeFilename;
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
    wxString relativeFilename = FileItem->GetRelativeName(GitRoot());

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

wxString GitCommitOp::BuildCommitCmd(const wxString& CommitMsg, const wxArrayString& ItemList) const
{
    wxString Command = _("git commit -m " + CommitMsg);

    for(unsigned int i=0; i<ItemList.Count(); i++)
    {
        Command += _(" ") + ItemList[i];
    }

    return Command;
}

void GitCommitOp::execute(std::vector<VcsTreeItem*>& paths) const
{
    wxString path_string;
    wxArrayString item_list;

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

void GitRevertOp::execute(std::vector<VcsTreeItem*>& paths) const
{
    wxString path_string;
    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=paths.begin(); i!= paths.end(); i++)
    {
        wxString relativeFilename = (*i)->GetRelativeName(GitRoot());
        if(relativeFilename.length() == 0)
        {
            continue;
        }
        path_string += _(" ") + relativeFilename;
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

    wxSetWorkingDirectory(m_GitRoot);
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

    return;
    Manager::Get()->GetLogManager()->Log( _T("Output") );
    for(i=0; i<Output.Count(); i++)
    {
        Manager::Get()->GetLogManager()->Log( Output[i] );
    }
}

const wxString& GitOp::GitRoot(void) const
{
    return m_vcs.m_GitRoot;
}
