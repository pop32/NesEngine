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
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>

class MemoryDumpView : public wxCustomBackgroundWindow<wxScrolledWindow>
{
public:
	MemoryDumpView(wxFrame *parent);


private:

	wxBitmap surfaceBmp;
	wxFont font;

	void OnPaint( wxPaintEvent &event );
	void OnEraseBackground( wxEraseEvent &event );

	void DoPaint(wxDC& dc);

	void DrawTopLeft(wxDC& dc);

	wxDECLARE_EVENT_TABLE();
};


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
	MemoryDumpView *m_MemoryDumpView;

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
