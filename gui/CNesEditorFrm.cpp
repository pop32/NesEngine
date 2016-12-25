/*
 * CNesEditor.cpp
 *
 *  Created on: 2016/12/21
 *	  Author: kyon
 */

#include "CNesEditorFrm.h"


namespace NesEngine {

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


// ----------------------------------------------------------------------------
// テキストエディタ ベース処理
// ----------------------------------------------------------------------------


template <class T> NesEditorViewBase<T>::NesEditorViewBase(wxFrame *parent)
{
	m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_fontEditting = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);

	viewBkColor = *wxWHITE;

	wxBitmap bmp(50, 50);
	wxMemoryDC dc(bmp);
	dc.SetFont(m_font);
	m_heightChar = dc.GetCharHeight();
	m_widthChar = dc.GetCharWidth();

	m_xCharPos = 0;
	m_xCaret = m_yCaret = 0;
	m_xChars = m_yChars = 0;
	m_xMargin = m_yMargin = 3;

	m_ColorComment = wxColor(0, 128, 0);
	m_ColorReserved = wxColor(0xa7, 0x1d, 0x5d);

	wxCaret *caret = new wxCaret(this, m_widthChar, m_heightChar);
	caret->SetSize(m_widthChar, m_heightChar);
	this->SetCaret(caret);
	DoMoveCaret();
	caret->Show();

}

// ------------------------------
// イベントハンドラー
// ------------------------------

template <class T> WXLRESULT NesEditorViewBase<T>::MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
{
	WXLRESULT rc = 0;
	bool processed = false;
	switch (message) {

#ifdef __WINDOWS__

	// IME確定／編集中操作
	case WM_IME_COMPOSITION:
	{
		wchar_t szBuf[1024] = {'\0'};
		HIMC hImc = ImmGetContext(this->GetHWND());

		// TODO 複数単語変換処理

		// 確定
		if (lParam & GCS_RESULTSTR) {
			memset(szBuf, '\0', 1024);
			ImmGetCompositionStringW(hImc, GCS_RESULTSTR, szBuf, 1024);
		}

		// 編集中
		if (lParam & GCS_COMPSTR) {
			memset(szBuf, '\0', 1024);
			ImmGetCompositionStringW(hImc, GCS_COMPSTR, szBuf, 1024);
			wxString str = szBuf;
			PrintEdittingMultiByteStr(str);
		}
		ImmReleaseContext(this->GetHWND(), hImc);
		processed = true;
		break;
	}

	// IME関連の通知
	case WM_IME_NOTIFY:
	{
		switch (wParam) {
		// 候補文字列ウィンドウ
		case IMN_OPENCANDIDATE:
			HIMC hImc = ImmGetContext(this->GetHWND());
			CANDIDATEFORM cndFrm = {0};
			wxRect rect = this->GetClientRect();
			wxPoint point = GetCaretPixelPoint();
			cndFrm.ptCurrentPos.x = rect.GetLeft() + point.x;
			cndFrm.ptCurrentPos.y = rect.GetTop() + point.y;
			cndFrm.dwStyle = CFS_CANDIDATEPOS;  // 候補文字ウィンドウ位置指定
			ImmSetCandidateWindow(hImc, &cndFrm);
			ImmReleaseContext(this->GetHWND(), hImc);

		}
		processed = true;
		break;
	}
#endif

	}
	if (!processed) {
		rc = wxCustomBackgroundWindow<T>::MSWWindowProc(message, wParam, lParam);
	}
	return rc;

}

/**
 * 描画イベント
 */
template <class T> void NesEditorViewBase<T>::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	this->PrepareDC(dc);
	wxRegionIterator upd(this->GetUpdateRegion());

	while (upd) {
		wxRect rect(upd.GetRect());
		dc.Blit(rect.GetLeftTop(), rect.GetSize(), &m_dc, rect.GetLeftTop());
		upd++;
	}
}


/**
 * キーボード入力
 */
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
			// TODO 文字列操作
			DoKeyEnter();
			break;

		default:
			if ( !event.AltDown() && wxIsprint(event.GetKeyCode()) ) {
				wxChar ch = (wxChar)event.GetKeyCode();
				InsertStr(ch);
			} else {
				event.Skip();
			}

	}
	DoMoveCaret();
}

/**
 * キーボード押下
 * ※いまのところ使っていない
 */
template <class T> void NesEditorViewBase<T>::OnKeyDown( wxKeyEvent &event )
{
//	switch ( event.GetKeyCode() )
//	{
//	case WXK_LEFT:
//	default:
//		break;
//	}
	event.Skip();
}


// ------------------------------
// キーボード操作関連
// ------------------------------
template <class T> void NesEditorViewBase<T>::DoKeyEnter()
{
	AddNewLine();
	NextLine();

}


// ------------------------------
// キャレット操作関連
// ------------------------------

/**
 * キャレット描画
 */
template <class T> void NesEditorViewBase<T>::DoMoveCaret()
{
	this->GetCaret()->Move(m_xMargin + m_xCaret * m_widthChar,
					 m_yMargin + m_yCaret * m_heightChar);
	//this->GetCaret()->SetSize(m_widthChar, m_heightChar);

}

/**
 * キャレットを最初に移動
 */
template <class T> void NesEditorViewBase<T>::Home()
{
	m_xCharPos = 0;
	m_xCaret = 0;
}

/**
 * キャレットを最後に移動
 */
template <class T> void NesEditorViewBase<T>::End()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
	} else {
		m_xCharPos = m_text[m_yCaret]->length();
		CalcCaretXPosAndWidth();
	}
}

template <class T> void NesEditorViewBase<T>::FirstLine()
{

}

template <class T> void NesEditorViewBase<T>::LastLine()
{

}

/**
 * キャレットを一文字左へ
 */
template <class T> void NesEditorViewBase<T>::PrevChar()
{
	if (m_xCharPos == 0) {
		return;
	}
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
	} else {
		m_xCharPos--;
		CalcCaretXPosAndWidth();
	}
}

/**
 * キャレットを一文字右へ
 */
template <class T> void NesEditorViewBase<T>::NextChar()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
	} else {
		int tcnt = m_text[m_yCaret]->length();
		if (m_text[m_yCaret]->length() <= m_xCharPos) {
			m_xCharPos = tcnt;
		} else {
			m_xCharPos++;
		}
		CalcCaretXPosAndWidth();
	}
}

/**
 * キャレットを前の行へ
 */
template <class T> void NesEditorViewBase<T>::PrevLine()
{
	if (m_yCaret == 0) {
		return;
	}
	m_yCaret--;
	int tcnt = m_text[m_yCaret]->length();
	if (m_text[m_yCaret]->length() <= m_xCharPos) {
		m_xCharPos = tcnt;
	}
	CalcCaretXPosAndWidth();
}


/**
 * キャレットを次の行へ
 */
template <class T> void NesEditorViewBase<T>::NextLine()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
		m_yCaret = m_text.size();
	} else {
		m_yCaret++;
		if (IsLastLine()) {
			m_xCharPos = 0;
			m_xCaret = 0;
			m_yCaret = m_text.size();
			return;
		}
		int tcnt = m_text[m_yCaret]->length();
		if (m_text[m_yCaret]->length() <= m_xCharPos) {
			m_xCharPos = tcnt;
		}
		CalcCaretXPosAndWidth();
	}
}

template <class T> void NesEditorViewBase<T>::AddNewLine()
{
	if (IsLastLine()) {
		m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT(""))));
	} else {
		m_text.insert(m_text.begin() + m_yCaret+1,
				std::unique_ptr<wxString>(new wxString(wxT(""))));
	}
	DrawTextLine(m_yCaret);
}

/**
 * キャレットのX位置を更新
 * （２バイト文字考慮）
 */
template <class T> void NesEditorViewBase<T>::CalcCaretXPosAndWidth()
{
	m_xCaret = 0;
	if (IsLastLine()) {
		return;
	} else {
		wxString::const_iterator s;
		wxString &str = *m_text[m_yCaret];
		s = str.begin();
		for (size_t i=0; i < m_xCharPos; ++i, ++s) {
			wxUniChar uni_ch = *s;
			if (uni_ch.IsAscii()) {
				m_xCaret++;
			} else {
				m_xCaret+=2;
			}
		}
	}
}

/**
 * ウィンドウを基点とした、キャレットの物理位置を返す
 */
template <class T> wxPoint NesEditorViewBase<T>::GetCaretPixelPoint()
{
	wxPoint p;
	p.x = m_xMargin + (m_xCaret * m_widthChar);
	p.y = m_yMargin + (m_yCaret * m_heightChar);
	return p;
}

/**
 * キャレット位置が最終行か判断
 */
template <class T> bool NesEditorViewBase<T>::IsLastLine()
{
	return (m_text.size() < m_yCaret+1);
}


// ------------------------------
// 文字列操作関連
// ------------------------------

template <class T> void NesEditorViewBase<T>::InsertStr(wxChar ch)
{
	wxString str = ch;
	InsertStr(str);
}

/**
 * キャレット位置に文字列を挿入
 */
template <class T> void NesEditorViewBase<T>::InsertStr(wxString& str)
{
	if (IsLastLine()) {
		AddNewLine();
	}
	wxString &text = *m_text[m_yCaret];
	text.insert(m_xCharPos, str);
	m_xCharPos += str.length();
	CalcCaretXPosAndWidth();
	DrawText(text, 0, m_yCaret);

}

/**
 * 文字の横幅計算
 */
template <class T> size_t NesEditorViewBase<T>::GetStringPixelWidth(wxString& str)
{
	size_t ret = 0;
	wxString::const_iterator s;
	for (s = str.begin(); s != str.end(); s++) {
		wxUniChar uni_ch = *s;
		if (uni_ch.IsAscii()) {
			ret+=m_widthChar;
		} else {
			ret+=m_widthChar * 2;
		}
	}
	return ret;
}

/**
 * 文字長計算（バイト考慮）
 */
template <class T> size_t NesEditorViewBase<T>::GetStringBLen(wxString& str)
{
	size_t ret = 0;
	for (wxUniChar c : str) {
		if (c.IsAscii()) {
			ret++;
		} else {
			ret+=2;
		}
	}
	return ret;
}


// ------------------------------
// 描画関連
// ※clipse CDT は region使えない 2016/12/23
// ------------------------------

template <class T> void NesEditorViewBase<T>::PrintEdittingMultiByteStr(wxString &str)
{
	//DrawText(str, m_xCaret, m_yCaret, false);
}

template <class T> void NesEditorViewBase<T>::DrawTextLine(wxCoord startRow)
{
	int i = 0;
	for(auto ite = m_text.begin() + startRow; ite != m_text.end(); ite++) {
		wxString* str = (*ite).get();
		DrawText(*str, 0, startRow + i);
		i++;
	}
}

template <class T> void NesEditorViewBase<T>::DrawText(wxString& str, wxCoord col, wxCoord row)
{
	this->PrepareDC(m_dc);
	m_dc.SetPen(*wxWHITE);
	m_dc.SetBrush(*wxWHITE);
	wxSize s = this->GetSize();
	m_dc.DrawRectangle(0, m_yMargin + (row * m_heightChar)
			, s.GetWidth(), m_heightChar);

	m_dc.SetFont(m_font);
	m_dc.SetTextBackground(*wxWHITE);
	//m_dc.SetTextForeground(*wxGREEN);
	int x = col;
	wxColor colorFore;
	m_syntaxAnalyzer.get()->Analyze(str);
	std::vector<std::unique_ptr<CTextColorAnalyzedVal>>& lst = m_syntaxAnalyzer.get()->GetAnalyzedVal();
	for (const auto& v : lst) {
		switch (v.get()->m_syntax) {
		case CTextColorAnalyzedVal::COMMENT:
			colorFore = m_ColorComment;
			break;
		case CTextColorAnalyzedVal::RESERVED:
			colorFore = m_ColorReserved;
			break;

		case CTextColorAnalyzedVal::STRRING:
			colorFore = *wxYELLOW;
			break;

		case CTextColorAnalyzedVal::UNDEF:
		default:
			colorFore = *wxBLACK;
			break;
		}
		m_dc.SetTextForeground(colorFore);
		wxString& s = v.get()->m_text;
		m_dc.DrawText(s, m_xMargin + (x * m_widthChar), m_yMargin + (row * m_heightChar));
		x += GetStringBLen(s);
	}
	this->Refresh();
}

template <class T> void NesEditorViewBase<T>::DrawTextTest(wxString& str, wxCoord col, wxCoord row)
{
	this->PrepareDC(m_dc);
	m_dc.SetPen(*wxWHITE);
	m_dc.SetBrush(*wxWHITE);
	wxSize s = this->GetSize();
	m_dc.DrawRectangle(0, m_yMargin + (row * m_heightChar)
			, s.GetWidth(), m_heightChar);
	m_dc.SetFont(m_font);
	m_dc.SetTextBackground(*wxWHITE);
	m_dc.SetTextForeground(*wxBLACK);
	m_dc.DrawText(str, m_xMargin + (col * m_widthChar), m_yMargin + (row * m_heightChar));
	this->Refresh();
}

// ----------------------------------------------------------------------------
// テキストエディタ
// ----------------------------------------------------------------------------


wxBEGIN_EVENT_TABLE(NesEditorView, wxScrolledWindow)
	EVT_PAINT(NesEditorView::OnPaint)
	EVT_CHAR(NesEditorView::OnChar)
	EVT_KEY_DOWN(NesEditorView::OnKeyDown)
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

	wxBitmap bmp = wxBitmap(parent->GetSize());
	m_dc.SelectObject(bmp);
	PrepareDC(m_dc);
	m_dc.Clear();

	m_syntaxAnalyzer = std::unique_ptr<CTextColorBase>(new CTextColorNesEngineAsm());

	//TODO ↓↓TEST↓↓
//	CTextColorNesEngineAsm tasm;
//	wxString aaa = wxT("aaaa;bbbb");
//	//tasm.operator=(aaa);
//	tasm.Analyze(aaa);
//
//	std::vector<std::unique_ptr<CTextColorAnalyzedVal>>& abc = tasm.GetAnalyzedVal();
//	int a = abc.size();
//	for (const auto& v : abc) {
//		wxString &abc = v.get()->m_text;
//		wxString::const_iterator test = abc.begin();
//		for(; test != abc.end(); test++) {
//			wchar_t uni_ch = *test;
//			int a = 0;
//		}
//
//		DrawText(m_font, v.get()->m_text, 0, 0);
//	}

	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("abcde adc あいうえお ;aaaaaaa"))));
	DrawText(*m_text[0], 0, 0);


//		CTextColorNesEngineAsm testAnalyzer;
//		wxString testStr = wxT("aaa bbb  ccccc;ddddd");
//		testAnalyzer.Analyze(testStr);
//
//		std::vector<std::unique_ptr<CTextColorAnalyzedVal>>& analyzedVal =
//				testAnalyzer.GetAnalyzedVal();
//		int a = analyzedVal.size();
//		int x = 0;
//		for (const auto& v : analyzedVal) {
//			wxString &abc = v.get()->m_text;
//			wxString::const_iterator test = abc.begin();
//			for(; test != abc.end(); test++) {
//				wchar_t uni_ch = *test;
//				int a = 0;
//			}
//			DrawTextTest(v.get()->m_text, x, 0);
//			x += GetStringBLen(v.get()->m_text);
//		}

	//TODO ↑↑EST↑↑

}


} /* namespace NesEngine */
