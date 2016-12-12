/*
 * CMemoryDumpFrm.h
 *
 *  Created on: 2016/12/12
 *      Author: z1j7663
 */

#ifndef GUI_CMEMORYDUMPFRM_H_
#define GUI_CMEMORYDUMPFRM_H_

#include <wx/wxprec.h>
#include <wx/wx.h>

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

class CMemoryDumpFrm : public wxFrame {
public:
	CMemoryDumpFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CMemoryDumpFrm();

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSetBlinkTime(wxCommandEvent& event);
	void OnSetFontSize(wxCommandEvent& event);
	void OnCaretMove(wxCommandEvent& event);

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
    CMemoryDumpFrm_Quit = 1,
	CMemoryDumpFrm_About,
};


#endif /* GUI_CMEMORYDUMPFRM_H_ */
