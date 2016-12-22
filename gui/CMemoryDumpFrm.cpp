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
	EVT_TIMER(CMemoryDumpFrm_TestTimer, CMemoryDumpFrm::OnTimer)
wxEND_EVENT_TABLE()


CMemoryDumpFrm::~CMemoryDumpFrm()
{
	//TODO memory leak?
}


// frame constructor
CMemoryDumpFrm::CMemoryDumpFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
//	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
: m_timer(this, CMemoryDumpFrm_TestTimer)
{
	if ( !this->Create(parent, wxID_ANY,
						title,
						pos, size,
						(wxDEFAULT_FRAME_STYLE & ~( wxMAXIMIZE_BOX | wxRESIZE_BORDER )) | wxSYSTEM_MENU | wxCAPTION ) ) {
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

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(new MemoryDumpViewHeader(this), 0, wxEXPAND, 0);

	m_MemoryDumpView = new MemoryDumpView(this);
	vbox->Add(m_MemoryDumpView, 1, wxEXPAND, 0);

	SetSizer(vbox);


	m_timer.Start(10);
	testdata = 0;
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
	wxMessageBox(wxT("The caret NesEngine .\n(c) 2016 pop32")
				,wxT("About") , wxOK | wxICON_INFORMATION, this);
}

void CMemoryDumpFrm::OnTimer(wxTimerEvent& event)
{
	testdata++;
	m_MemoryDumpView->WriteByteHexTest(testdata, 0, 0);

}

// ----------------------------------------------------------------------------
// メモリ表示部 ベース処理
// ----------------------------------------------------------------------------

template <class T> MemoryDumpViewBase<T>::MemoryDumpViewBase(wxFrame *parent)
{
	nDrawMarginX = 0;
	nDrawMarginY = 0;
	nBlockSizeX = 24;
	nBlockSizeY = 16;
	nFixedLeftMargin = 10;
	nFixedTopMargin = 3;
	nFixedLeftWidth = (nBlockSizeX * 2);
	nFixedTopHeight = nBlockSizeY + 3;

	nViewLeftMargin = 3;
	nViewTopMargin = 3;
	nViewLeftStart = nFixedLeftWidth + nViewLeftMargin;
	//nViewTopStart = nFixedTopHeight + nViewTopMargin;
	nViewTopStart = nViewTopMargin;

	nHexViewWidth = nViewLeftMargin + (nBlockSizeX * 0x10);
	nHexViewHeight = nBlockSizeY * 0x1000;

	nViewWidth = nFixedLeftWidth + nHexViewWidth;
	//nViewHeight = nFixedTopHeight + nHexViewHeight;
	nViewHeight = nHexViewHeight;

	//m_font = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_fixBkColor = wxColor(220, 230, 241);
	m_viewBkColor = *wxWHITE;
}

template <class T> void MemoryDumpViewBase<T>::WriteByteHexTest(uint8_t b, int col, int row)
{
	wxString str;
	str.Printf(wxT("%02x"), b);

	wxMemoryDC dc(m_surfaceBmp);
	this->PrepareDC(dc);
	WriteStr(dc, str, col, row);
	this->Refresh();
}


template <class T> void MemoryDumpViewBase<T>::DoPaint(wxDC& dc)
{
	this->PrepareDC(dc);
	dc.DrawBitmap(m_surfaceBmp,0, 0, true);
}

template <class T> void MemoryDumpViewBase<T>::OnPaint( wxPaintEvent &WXUNUSED(event) )
{
	//wxAutoBufferedPaintDC dc(this);
	wxPaintDC dc(this);
	DoPaint(dc);
}

template <class T> void MemoryDumpViewBase<T>::WriteByteHex(wxDC& dc, uint8_t b, int col, int row)
{
	wxString str;
	str.Printf(wxT("%02x"), b);
	WriteStr(dc, str, col, row);
}

template <class T> void MemoryDumpViewBase<T>::WriteStr(wxDC& dc, wxString& str, int col, int row)
{
	int x = nViewLeftStart + (nBlockSizeX * col);
	int y = nViewTopStart + (nBlockSizeY * row);

	dc.SetFont(m_font);
	dc.SetPen(*wxWHITE);
	dc.SetBrush(m_viewBkColor);
	dc.DrawRectangle(x, y, nBlockSizeX, nBlockSizeY);

	dc.DrawText(str, x, y);
}

template <class T> void MemoryDumpViewBase<T>::WriteByteHexTopFixView(wxDC& dc, uint8_t b, int col)
{
	wxString str;
	str.Printf(wxT("%02x"), b);
	WriteStrTopFixView(dc, str, col);
}

template <class T> void MemoryDumpViewBase<T>::WriteWordHexLeftFixView(wxDC& dc, uint16_t w, int row)
{
	wxString str;
	str.Printf(wxT("%04x"), w);
	WriteStrLeftFixView(dc, str, row);
}

template <class T> void MemoryDumpViewBase<T>::WriteStrTopFixView(wxDC& dc, wxString& str, int col)
{
	int x = nViewLeftStart + (nBlockSizeX * col);
	int y = nFixedTopMargin + (nBlockSizeY * 0);
	dc.DrawText(str, x, y);
}

template <class T> void MemoryDumpViewBase<T>::WriteStrLeftFixView(wxDC& dc, wxString& str, int row)
{
	int x = nFixedLeftMargin;
	int y = nViewTopStart + (nBlockSizeY * row);
	dc.DrawText(str, x, y);
}

// ----------------------------------------------------------------------------
// メモリ表示 ヘッダ部
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MemoryDumpViewHeader, wxWindow)
	EVT_PAINT(MemoryDumpViewHeader::OnPaint)
	//EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()

MemoryDumpViewHeader::MemoryDumpViewHeader(wxFrame *parent)
: MemoryDumpViewBase(parent)
{
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(nViewWidth, nFixedTopHeight));
	m_surfaceBmp = wxBitmap(nViewWidth - 8, nFixedTopHeight);
	wxMemoryDC dc(m_surfaceBmp);

	dc.Clear();
	DrawFixView(dc);

	//SetSize(nViewWidth, nFixedTopHeight);
}

void MemoryDumpViewHeader::DrawFixView(wxDC& dc)
{
	dc.SetFont(m_font);
	dc.SetPen( wxPen( *wxBLACK, 1 ) );
	dc.SetTextForeground(*wxBLACK);

	dc.SetBrush(m_fixBkColor);
	dc.DrawRectangle(0, 0, nViewWidth - 8, nFixedTopHeight);

	for (int i=0; i < 0x10; i++) {
		WriteByteHexTopFixView(dc, i, i);
	}

}

// ----------------------------------------------------------------------------
// メモリ表示 データ部
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MemoryDumpView, wxScrolledWindow)
	EVT_PAINT(MemoryDumpView::OnPaint)
	//EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()

MemoryDumpView::MemoryDumpView(wxFrame *parent)
 : MemoryDumpViewBase(parent)
{
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(nViewWidth, nViewHeight + 50));
	SetScrollbars( 0
			, nBlockSizeY
			, 40, 0x1000, 0, 0 );

	SetFocusIgnoringChildren();
	SetBackgroundColour(*wxCYAN);
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_surfaceBmp = wxBitmap(nViewWidth + 100, nViewHeight + 50);
	wxMemoryDC dc(m_surfaceBmp);
	PrepareDC(dc);

	dc.Clear();
	DrawFixView(dc);

}

void MemoryDumpView::DrawFixView(wxDC& dc)
{
	this->PrepareDC(dc);
	dc.SetFont(m_font);
	dc.SetPen( wxPen( *wxBLACK, 1 ) );
	dc.SetTextForeground(*wxBLACK);

	dc.SetBrush(m_fixBkColor);
	dc.DrawRectangle(0, 0, nFixedLeftWidth, nViewHeight + 100);

	for (int i=0; i < 0x1000; i++) {
		WriteWordHexLeftFixView(dc, i * 0x10, i);
	}

	for (int j=0; j < 10; j++) {
		for (int i=0; i < 0x10; i++) {
			WriteByteHex(dc, i, i, j);
		}
	}
}


