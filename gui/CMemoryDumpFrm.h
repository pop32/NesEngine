/*
 * CMemoryDumpFrm.h
 *
 *  Created on: 2016/12/12
 *      Author: kyon
 */

#ifndef GUI_CMEMORYDUMPFRM_H_
#define GUI_CMEMORYDUMPFRM_H_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>

template <class T = wxWindow>
class MemoryDumpViewBase : public wxCustomBackgroundWindow<T>
{
public:
	MemoryDumpViewBase(wxFrame *parent);

	void WriteByteHexTest(uint8_t b, int col, int row);


protected:
	wxBitmap surfaceBmp;
	wxFont font;
	wxColor fixBkColor;
	wxColor viewBkColor;

	int nFixedLeftMargin;
	int nFixedTopHeight;

	int nFixedTopMargin;
	int nFixedLeftWidth;

	int nViewLeftMargin;
	int nViewTopMargin;
	int nViewLeftStart;
	int nViewTopStart;

	int nHexViewWidth;
	int nHexViewHeight;
	int nDrawMarginX;
	int nDrawMarginY;
	int nBlockSizeX;
	int nBlockSizeY;

	int nViewWidth;
	int nViewHeight;

	void OnPaint( wxPaintEvent &event );
	//void OnEraseBackground( wxEraseEvent &event );

	void DoPaint(wxDC& dc);

	void WriteByteHex(wxDC& dc, uint8_t b, int col, int row);
	void WriteStr(wxDC& dc, wxString str, int col, int row);

	void WriteByteHexTopFixView(wxDC& dc, uint8_t b, int col);
	void WriteWordHexLeftFixView(wxDC& dc, uint16_t b, int row);

	void WriteStrTopFixView(wxDC& dc, wxString str, int col);
	void WriteStrLeftFixView(wxDC& dc, wxString str, int row);


};

class MemoryDumpViewHeader : public MemoryDumpViewBase<wxScrolledWindow>
{
public:
	MemoryDumpViewHeader(wxFrame *parent);

private:
	void DrawFixView(wxDC& dc);

	wxDECLARE_EVENT_TABLE();

};

class MemoryDumpView : public MemoryDumpViewBase<wxScrolledWindow>
{
public:
	MemoryDumpView(wxFrame *parent);

private:

	void DrawFixView(wxDC& dc);

	wxDECLARE_EVENT_TABLE();
};


class CMemoryDumpFrm : public wxFrame {
public:
	CMemoryDumpFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CMemoryDumpFrm();

	// event handlers (these functions should _not_ be virtual)
	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
//	void OnSetBlinkTime(wxCommandEvent& event);
//	void OnSetFontSize(wxCommandEvent& event);
//	void OnCaretMove(wxCommandEvent& event);

	void OnTimer(wxTimerEvent& event);

private:
	MemoryDumpView *m_MemoryDumpView;

	wxTimer m_timer;
	uint8_t testdata;

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
	CMemoryDumpFrm_TestTimer,
};


#endif /* GUI_CMEMORYDUMPFRM_H_ */
