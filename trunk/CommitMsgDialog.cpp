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

#include "CommitMsgDialog.h"

//(*InternalHeaders(CommitMsgDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(CommitMsgDialog)
const long CommitMsgDialog::ID_SUMMARY1 = wxNewId();
const long CommitMsgDialog::ID_DETAILS = wxNewId();
const long CommitMsgDialog::ID_FILELIST = wxNewId();
//*)

BEGIN_EVENT_TABLE(CommitMsgDialog,wxScrollingDialog)
	//(*EventTable(CommitMsgDialog)
	//*)
END_EVENT_TABLE()

CommitMsgDialog::CommitMsgDialog(wxWindow* parent, wxString& msg, wxArrayString& CommitList) :
    m_msg(msg)
{
    const int id = wxID_ANY;    // I'm sick of fighting the resource editor

	//(*Initialize(CommitMsgDialog)
	wxStaticText* StaticText2;
	wxStaticText* StaticText1;
	wxStaticText* StaticText3;
	wxButton* Button2;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxSize(567,585));
	Move(wxDefaultPosition);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Summary of changes:"), wxPoint(16,8), wxDefaultSize, 0, _T("wxID_ANY"));
	m_Summary = new wxTextCtrl(this, ID_SUMMARY1, _("Brief summary of changes"), wxPoint(16,32), wxSize(536,27), 0, wxDefaultValidator, _T("ID_SUMMARY1"));
	m_Summary->SetMaxLength(50);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("Commit message:"), wxPoint(16,72), wxDefaultSize, 0, _T("wxID_ANY"));
	m_Details = new wxTextCtrl(this, ID_DETAILS, _("Enter your commit message here..."), wxPoint(16,96), wxSize(536,256), wxTE_NO_VSCROLL|wxTE_MULTILINE|wxTE_WORDWRAP|wxVSCROLL|wxFULL_REPAINT_ON_RESIZE, wxDefaultValidator, _T("ID_DETAILS"));
	m_OkButton = new wxButton(this, wxID_OK, wxEmptyString, wxPoint(464,544), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	m_OkButton->SetDefault();
	Button2 = new wxButton(this, wxID_CANCEL, wxEmptyString, wxPoint(368,544), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	m_FileList = new wxCheckListBox(this, ID_FILELIST, wxPoint(16,392), wxSize(536,136), 0, 0, 0, wxDefaultValidator, _T("ID_FILELIST"));
	StaticText3 = new wxStaticText(this, wxID_ANY, _("File list:"), wxPoint(16,368), wxDefaultSize, 0, _T("wxID_ANY"));

	Connect(ID_SUMMARY1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CommitMsgDialog::OnMessageChange);
	Connect(ID_DETAILS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CommitMsgDialog::OnMessageChange);
	Connect(ID_FILELIST,wxEVT_COMMAND_CHECKLISTBOX_TOGGLED,(wxObjectEventFunction)&CommitMsgDialog::OnMessageChange);
	//*)

    SetCommitList(CommitList);
}

void CommitMsgDialog::SetCommitList(wxArrayString& CommitList)
{
    m_FileList->Set(CommitList);

    for(unsigned int i=0; i<CommitList.size(); i++)
    {
        m_FileList->Check(i);
    }
}

CommitMsgDialog::~CommitMsgDialog()
{
	//(*Destroy(CommitMsgDialog)
	//*)
}

void CommitMsgDialog::EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        m_msg = _("\"")
            + m_Summary->GetValue()
            + _("\n\n")
            + m_Details->GetValue()
            + _("\"");
    }

    wxScrollingDialog::EndModal(retCode);
}

bool CommitMsgDialog::IsSelectionValid(void)
{
    unsigned int i;

    for(i=0; i<m_FileList->GetCount(); i++)
    {
        if(m_FileList->IsChecked(i))
        {
            return true;
        }
    }

    return false;
}

void CommitMsgDialog::OnMessageChange(wxCommandEvent& event)
{
    if((m_Summary->GetValue().size() + m_Details->GetValue().size()) != 0
       && IsSelectionValid())
    {
        m_OkButton->Enable();
    }
    else
    {
        m_OkButton->Disable();
    }
}
