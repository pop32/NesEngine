/*
 * CMainFrm.h
 *
 *  Created on: 2016/12/12
 *      Author: kyon
 */

#ifndef GUI_CMAINFRM_H_
#define GUI_CMAINFRM_H_

#include <wx/wxprec.h>
#include <wx/wx.h>

#include "CMemoryDumpFrm.h"
#include "CNesEditorFrm.h"

class CMainFrm : public wxFrame {
public:
	CMainFrm(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CMainFrm();

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnMemoryDump(wxCommandEvent& event);
	void OnNesEditor(wxCommandEvent& event);

private:

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();

};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	CMainFrm_Quit = 1,
	CMainFrm_About,
	CMainFrm_MemoryDump,
	CMainFrm_NesEditor,
};


#endif /* GUI_CMAINFRM_H_ */
