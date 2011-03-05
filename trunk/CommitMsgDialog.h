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
#ifndef COMMITMSGDIALOG_H
#define COMMITMSGDIALOG_H

//(*Headers(CommitMsgDialog)
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/button.h>
#include "scrollingdialog.h"
//*)

class CommitMsgDialog: public wxScrollingDialog
{
	public:

		CommitMsgDialog(wxWindow* parent, wxString& msg, wxArrayString& CommitList);
		virtual ~CommitMsgDialog();

		//(*Declarations(CommitMsgDialog)
		wxButton* m_OkButton;
		wxTextCtrl* m_Details;
		wxTextCtrl* m_Summary;
		wxCheckListBox* m_FileList;
		//*)

		virtual void EndModal( int retCode );

	protected:

		//(*Identifiers(CommitMsgDialog)
		static const long ID_SUMMARY1;
		static const long ID_DETAILS;
		static const long ID_FILELIST;
		//*)

	private:
        wxString& m_msg;

        bool IsSelectionValid(void);
        void SetCommitList(wxArrayString& CommitList);

		//(*Handlers(CommitMsgDialog)
		void OnMessageChange(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
