/*
 * CNesEditor.cpp
 *
 *  Created on: 2016/12/21
 *	  Author: kyon
 */

#include "CNesEditorFrm.h"



// ----------------------------------------------------------------------------
// メインフレーム
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(CNesEditorFrm, wxFrame)
	EVT_MENU(CNesEditorFrm_Quit,  CNesEditorFrm::OnQuit)
	EVT_MENU(CNesEditorFrm_About, CNesEditorFrm::OnAbout)
//	EVT_TIMER(CNesEditorFrm_TestTimer, CNesEditorFrm::OnTimer)
wxEND_EVENT_TABLE()


CNesEditorFrm::~CNesEditorFrm()
{
	//TODO memory leak?
}


// frame constructor
CNesEditorFrm::CNesEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
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

	menuFile->Append(CNesEditorFrm_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(CNesEditorFrm_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	wxBoxSizer *topBox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	vbox->Add(new NesEditorView(this), 0, wxEXPAND, 0);

	topBox->Add(vbox, 1, wxEXPAND, 0);
	SetSizer(topBox);
//
//
//	m_timer.Start(10);
//	testdata = 0;
}

// -----------------
// event handlers
// -----------------

void CNesEditorFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void CNesEditorFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("The caret NesEngine .\n(c) 2016 pop32")
			,wxT("About") , wxOK | wxICON_INFORMATION, this);
}

//void CNesEditorFrm::OnTimer(wxTimerEvent& event)
//{
//	testdata++;
//	m_MemoryDumpView->WriteByteHexTest(testdata, 0, 0);
//
//}

// ----------------------------------------------------------------------------
// テキストエディタ ベース処理
// ----------------------------------------------------------------------------

template <class T> NesEditorViewBase<T>::NesEditorViewBase(wxFrame *parent)
{
	m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	viewBkColor = *wxWHITE;

	wxBitmap bmp(50, 50);
	wxMemoryDC dc(bmp);
	dc.SetFont(m_font);
	m_heightChar = dc.GetCharHeight();
	m_widthChar = dc.GetCharWidth();

	m_CharPos = 0;
	m_xCaret = m_yCaret = 0;
	m_xChars = m_yChars = 0;
	m_xMargin = m_yMargin = 3;

	wxCaret *caret = new wxCaret(this, m_widthChar, m_heightChar);
	caret->SetSize(m_widthChar, m_heightChar);
	this->SetCaret(caret);
	DoMoveCaret();
	caret->Show();

}

template <class T> void NesEditorViewBase<T>::OnPaint( wxPaintEvent &WXUNUSED(event) )
{
	//wxAutoBufferedPaintDC dc(this);
	wxPaintDC dc(this);
	DoPaint(dc);
}

template <class T> void NesEditorViewBase<T>::OnChar( wxKeyEvent &event )
{

	switch ( event.GetKeyCode() )
	{
		case WXK_LEFT:
			PrevChar();
			break;

		case WXK_RIGHT:
			NextChar();
			break;

		case WXK_UP:
			PrevLine();
			break;

		case WXK_DOWN:
			NextLine();
			break;

		case WXK_HOME:
			Home();
			break;

		case WXK_END:
			End();
			break;

		case WXK_RETURN:
			Home();
			NextLine();
			break;

		default:
			event.Skip();
	}
	DoMoveCaret();
}

template <class T> void NesEditorViewBase<T>::DoPaint(wxDC& dc)
{
	this->PrepareDC(dc);
	dc.DrawBitmap(m_surfaceBmp,0, 0, true);
}

template <class T> void NesEditorViewBase<T>::DoMoveCaret()
{
	this->GetCaret()->Move(m_xMargin + m_xCaret * m_widthChar,
					 m_yMargin + m_yCaret * m_heightChar);
}

template <class T> void NesEditorViewBase<T>::Home()
{
	m_xCaret = 0;
}

template <class T> void NesEditorViewBase<T>::End()
{
	if (m_text.size() < m_yCaret) {
		m_xCaret = 0;
	} else {
		m_xCaret = 3;
	}
}

template <class T> void NesEditorViewBase<T>::FirstLine()
{

}

template <class T> void NesEditorViewBase<T>::LastLine()
{

}

template <class T> void NesEditorViewBase<T>::PrevChar()
{

}

template <class T> void NesEditorViewBase<T>::NextChar()
{

}

template <class T> void NesEditorViewBase<T>::PrevLine()
{

}

template <class T> void NesEditorViewBase<T>::NextLine()
{

}

template <class T> void NesEditorViewBase<T>::CalcCaretPos()
{

}


// ----------------------------------------------------------------------------
// テキストエディタ
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(NesEditorView, wxScrolledWindow)
	EVT_PAINT(NesEditorView::OnPaint)
	EVT_CHAR(NesEditorView::OnChar)
	//EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()

NesEditorView::NesEditorView(wxFrame *parent)
 : NesEditorViewBase(parent)
{
	Create(parent, wxID_ANY, wxDefaultPosition, parent->GetSize());
//	SetScrollbars( 0
//			, nBlockSizeY
//			, 40, 0x1000, 0, 0 );

	SetFocusIgnoringChildren();
	SetBackgroundColour(*wxCYAN);
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	m_surfaceBmp = wxBitmap(1024, 5000);
	wxMemoryDC dc(m_surfaceBmp);
	PrepareDC(dc);

	dc.Clear();

	m_text.push_back(new wxString(wxT("abcdeあいうえお")));

	dc.SetFont(m_font);
	dc.DrawText(*m_text[0], m_xMargin, m_yMargin);

	int a = m_text[0]->length();
	int b = m_text[0]->Length();
	int c = m_text[0]->Len();
	int d = 0;
	//m_text[0]->
}


