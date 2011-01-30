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
