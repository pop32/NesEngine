/*
 * CMemoryDumpFrm.cpp
 *
 *  Created on: 2016/12/04
 *	  Author: kyon
 */

#include "CMemoryDumpFrm.h"

// ----------------------------------------------------------------------------
// メインフレーム
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(CMemoryDumpFrm, wxFrame)
	EVT_MENU(CMemoryDumpFrm_Quit,  CMemoryDumpFrm::OnQuit)
	EVT_MENU(CMemoryDumpFrm_About, CMemoryDumpFrm::OnAbout)
wxEND_EVENT_TABLE()


CMemoryDumpFrm::~CMemoryDumpFrm()
{
	//TODO memory leak?
	delete m_MemoryDumpView;
}


// frame constructor
CMemoryDumpFrm::CMemoryDumpFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
//	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
	if ( !this->Create(parent, wxID_ANY,
						title,
						pos, size,
						wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) ) {
		return;
	}

	// set the frame icon
	SetIcon(wxICON(sample));

	// create a menu bar
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(CMemoryDumpFrm_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(CMemoryDumpFrm_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	m_MemoryDumpView = new MemoryDumpView( this );
}

// -----------------
// event handlers
// -----------------

void CMemoryDumpFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void CMemoryDumpFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("The caret wxWidgets sample.\n(c) 1999 Vadim Zeitlin"),
				 wxT("About Caret"), wxOK | wxICON_INFORMATION, this);
}


// ----------------------------------------------------------------------------
// メモリ表示部
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MemoryDumpView, wxScrolledWindow)
	EVT_PAINT(MemoryDumpView::OnPaint)
	//EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()


MemoryDumpView::MemoryDumpView(wxFrame *parent)
{
	Create(parent, wxID_ANY);
	SetScrollbars( 10, 10, 40, 100, 0, 0 );

	SetFocusIgnoringChildren();
	SetBackgroundColour(*wxCYAN);

	SetBackgroundStyle(wxBG_STYLE_PAINT);

	font = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

	surfaceBmp = wxBitmap(600, 2000);
	wxMemoryDC dc(surfaceBmp);
	PrepareDC(dc);

	dc.Clear();
	DrawTopLeft(dc);

}


// -----------------
// event handlers
// -----------------

void MemoryDumpView::DoPaint(wxDC& dc)
{
	PrepareDC(dc);
	dc.DrawBitmap(surfaceBmp,0, 0, true);

}

void MemoryDumpView::OnPaint( wxPaintEvent &WXUNUSED(event) )
{
	//wxAutoBufferedPaintDC dc(this);
	wxPaintDC dc(this);
	DoPaint(dc);
}

void MemoryDumpView::DrawTopLeft(wxDC& dc)
{

	PrepareDC(dc);
	dc.SetFont(font);
	dc.SetPen( wxPen( *wxBLACK, 1 ) );
	dc.SetTextForeground(*wxBLACK);

	// x, y
	dc.DrawLine(5, 5, 5, 100);

	wxString str;
	for (int i = 0; i < 0x10; i++) {
		str.Printf(wxT("%x"), i);
		dc.DrawText(str, 11 + (10 * i), 11);
	}

}
