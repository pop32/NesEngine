/*
 * CNesEditor.cpp
 *
 *  Created on: 2016/12/21
 *	  Author: kyon
 *
 *  Bug
 *   ・TODO 20170102_2 うまくいかないので、スクロールがきたらとりあえず全描画。
 *   ・TODO 小 キャレット一番下でスクロールできないときは、キャレット隠す
 *
 *  TODO一覧
 *   ・TODO 20170103_03 画面クリックでキャレット位置更新
 *   ・TODO 20170103_04 画面の文字列選択とコピー
 *   ・TODO 20170103_05 エンターなど押下時、文字列のライン移動など
 *   ・TODO 20170103_01 複数単語変換処理
 *   ・TODO 20170103_02 候補文字列の編集処理・描画処理
 *   ・TODO メモリリークしていない？
 *
 */


#include "CNesEditorFrm.h"


namespace NesEngine {

// ----------------------------------------------------------------------------
// メインフレーム
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(CNesEditorFrm, wxFrame)
	EVT_MENU(CNesEditorFrm_Quit,  CNesEditorFrm::OnQuit)
	EVT_MENU(CNesEditorFrm_About, CNesEditorFrm::OnAbout)
	EVT_MENU(wxID_ANY, CNesEditorFrm::OnToolLeftClick)

//	EVT_SIZE(CNesEditorFrm::OnSize)
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
						pos, size
						//,(wxDEFAULT_FRAME_STYLE & ~( wxMAXIMIZE_BOX | wxRESIZE_BORDER )) | wxSYSTEM_MENU | wxCAPTION ) )
						,(wxDEFAULT_FRAME_STYLE & ~( wxMAXIMIZE_BOX )) | wxSYSTEM_MENU | wxCAPTION ) )
	{
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


	// ツールバー設定
	wxToolBarBase *toolBar = GetToolBar();
	delete toolBar;
	SetToolBar(NULL);
	long style = wxTB_FLAT | wxTB_DOCKABLE ;
	toolBar = CreateToolBar(style, 9998);

	enum
	{
		Tool_new,
		Tool_open,
		Tool_save,
		Tool_Max
	};

	wxBitmap toolBarBitmaps[Tool_Max];

	INIT_TOOL_BMP(new);
	INIT_TOOL_BMP(open);
	INIT_TOOL_BMP(save);

	int w = toolBarBitmaps[Tool_new].GetScaledWidth(),
			h = toolBarBitmaps[Tool_new].GetScaledHeight();

	toolBar->SetToolBitmapSize(wxSize(w, h));

	toolBar->AddTool(wxID_NEW, wxT("New"),
					toolBarBitmaps[Tool_new], wxT("New file"));

	//	wxMenu* menu = new wxMenu;
	//	menu->Append(wxID_ANY, wxT("&First dummy item"));
	//	menu->Append(wxID_ANY, wxT("&Second dummy item"));
	//	menu->AppendSeparator();
	//	menu->Append(wxID_EXIT, wxT("Exit"));
	//	toolBar->SetDropdownMenu(wxID_NEW, menu);

	toolBar->AddTool(wxID_OPEN, wxT("Open"),
					toolBarBitmaps[Tool_open], wxT("Open file"));

	toolBar->AddTool(wxID_SAVE, wxT("Save"),
					toolBarBitmaps[Tool_save], wxT("Save file"));

	toolBar->Realize();

//	new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxEXPAND);

	// ※ wxEXPANDを指定しないと、なぜかクローズイベントが走る
	new NesEditor(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxEXPAND);

//	wxBoxSizer *topBox = new wxBoxSizer(wxVERTICAL);
//	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//
//	vbox->Add(new NesEditorPanel(this)
//				, 1				// 縦伸縮可
//				, wxEXPAND
//				, 0);
//
//	topBox->Add(vbox
//				, 1				// 横伸縮可
//				, wxEXPAND
//				, 0);
//
//	SetSizer(topBox);

//	wxPanel* p = new wxPanel(this, wxID_ANY);
//
//	topBox->Add(new wxButton(p, wxID_EXIT, wxT("Quit1"))
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);
//
//	topBox->Add(new wxButton(p, wxID_EXIT, wxT("Quit2"))
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);

//	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
//	wxPanel* p = new wxPanel(this, wxID_ANY);
//	hBox->Add(new wxButton(p, wxID_EXIT, wxT("Quit1"))
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);
//	hBox->Add(new wxButton(p, wxID_EXIT, wxT("Quit2"))
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);

//	wxScrolledWindow *wtest = new wxScrolledWindow(p,wxID_ANY, wxDefaultPosition,wxDefaultSize);
//	wxScrolledWindow *wtest = new wxScrolledWindow(p,wxID_ANY, wxDefaultPosition,wxSize(100,100));
//	wtest->SetScrollbars(0
//			, 10
//			, 1, 1000, 0, 0);
//
//	hBox->Add(wtest
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);
//
//	p->SetSizer(hBox);


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

void CNesEditorFrm::OnToolLeftClick(wxCommandEvent& event)
{
	wxString str;
	str.Printf( wxT("Clicked on tool %d\n"), event.GetId());
	int a = 0;
}


///////////////////////////////////////////////////////////////////////////////
// 行番号表示用クラス
///////////////////////////////////////////////////////////////////////////////

//NesEditorLineNumberView::NesEditorLineNumberView(wxFrame *parent)
//{
//
//}

NesEditorLineNumberView::NesEditorLineNumberView(wxWindow *parent)
{
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(50,-1));

}


///////////////////////////////////////////////////////////////////////////////
// エディタメイン処理ベース
///////////////////////////////////////////////////////////////////////////////

//template <class T>
//NesEditorMainViewBase<T>::NesEditorMainViewBase(wxFrame *parent)

template <class T>
NesEditorMainViewBase<T>::NesEditorMainViewBase(wxWindow *parent)
{
	m_font = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	m_fontEditting = wxFont(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, true);

	viewBkColor = *wxWHITE;

	// TODO メモリリークしていない？
	wxBitmap bmp(50, 50);
	wxMemoryDC dc(bmp);
	dc.SetFont(m_font);
	m_heightChar = dc.GetCharHeight();
	m_widthChar = dc.GetCharWidth();

	m_xCharPos = m_yCharPos = 0;
	m_xCaret = m_yCaret = 0;
	m_xMargin = m_yMargin = 0;
	m_xScrollPos = m_yScrollPos = 0;
	m_xMaxScrollPos =  m_yMaxScrollPos = 0;

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

template <class T>
WXLRESULT NesEditorMainViewBase<T>::MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam)
{
	WXLRESULT rc = 0;
	bool processed = false;
	switch (message) {

#ifdef __WINDOWS__

	// TODO 20170103_01 複数単語変換処理
	// TODO 20170103_02 候補文字列の編集処理・描画処理
	// IME確定／編集中操作
	case WM_IME_COMPOSITION:
	{
		wchar_t szBuf[1024] = {'\0'};
		HIMC hImc = ImmGetContext(this->GetHWND());


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
template <class T>
void NesEditorMainViewBase<T>::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	this->PrepareDC(dc);

	// スクロールイベントでキャレット位置を補正するとずれるので、ここで補正
	AdjustCaretPos();

//	wxPoint p = dc.GetDeviceOrigin();
////	m_dc.SetDeviceOrigin(p.x, p.y);
//	//m_dc.SetLogicalOrigin(0, 0);
//
//	//this->PrepareDC(m_dc);
//	wxRegionIterator upd(this->GetUpdateRegion());
//	while (upd) {
//		wxRect rect(upd.GetRect());
//		wxPoint lefttop = rect.GetLeftTop();
//		//wxSize updSize = wxSize()
//		rect.height += rect.y;
//		dc.Blit(rect.GetLeftTop(), rect.GetSize(), &m_dc, rect.GetLeftTop());
//		upd++;
//	}

	// スクロールするとき、↑アップデート領域がおかしい。
	// TODO 20170102_2 うまくいかないので、スクロールがきたらとりあえず全描画。
//	dc.Blit(wxPoint(0,0), this->GetVirtualSize(), &m_dc, wxPoint(0,0));

//	// m_yScrollPosの値がちゃんと取れるようになったので、ちょっと節約
//       → バグっている
	size_t y = m_yScrollPos * m_heightChar;
	dc.Blit(wxPoint(0,y), this->GetSize(), &m_dc, wxPoint(0,y));

//	dc.DrawBitmap(m_bitmap, wxPoint(0,0));

}

/**
 * キーボード入力
 */
template <class T>
void NesEditorMainViewBase<T>::OnChar( wxKeyEvent &event )
{

	switch ( event.GetKeyCode() )
	{
		case WXK_LEFT:
			DoKeyLeft(event);
			break;

		case WXK_RIGHT:
			DoKeyRight(event);
			break;

		case WXK_UP:
			DoKeyUp(event);
			break;

		case WXK_DOWN:
			DoKeyDown(event);
			break;

		case WXK_HOME:
			Home();
			break;

		case WXK_END:
			End();
			break;

		case WXK_RETURN:
			DoKeyEnter(event);
			break;

		case WXK_DELETE:
			DoKeyDelete(event);
			break;

		case WXK_BACK:
			DoKeyBack(event);
			break;

		default:
			if ( !event.AltDown() && wxIsprint(event.GetKeyCode()) ) {

				wxChar ch = (wxChar)event.GetKeyCode();
				wxUniChar uch = ch;
				if (uch.IsAscii()) {
					InsertStr(ch);
				}

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
template <class T>
void NesEditorMainViewBase<T>::OnKeyDown( wxKeyEvent &event )
{
//	switch ( event.GetKeyCode() )
//	{
//	case WXK_LEFT:
//	default:
//		break;
//	}
	event.Skip();
}


template <class T>
void NesEditorMainViewBase<T>::OnSize(wxSizeEvent& event)
{
//	this->SetSize(event.GetSize());
	// スクロールの領域を再設定
	SetScroll(false);

	// 背景DC再設定
	SetSurface(false);

	//AdjustScrollPos();
	//AdjustCaretPos();


	//this->Refresh();
	event.Skip(false);
}

template <class T>
void NesEditorMainViewBase<T>::OnScrollWin(wxScrollWinEvent& event)
{
	if (event.GetOrientation() == wxVERTICAL) {
		// ※TOPまたはBOTTOMに到達しても、LINEUP,LINEDOWNイベントが発生するので補正追加
//		wxEventType scrollType(event.GetEventType());
		int diff = this->CalcScrollInc(event);
		if (diff != 0) {
			m_yScrollPos += diff;
			this->Refresh();

			// BUG スクロールしきる前にキャレットが描画されるので、ずれる！！！
			// wxwidgets側でスクロール処理が実施されている？
			// その後のイベントがほしいがない、OnPaintでキャレット位置補正で逃げれそう。
			// AdjustCaretPos();
		}
	}

}

template <class T>
void NesEditorMainViewBase<T>::OnScroll(wxScrollEvent& event)
{
	event.Skip();
}

template <class T>
void NesEditorMainViewBase<T>::OnKillFocus(wxFocusEvent& event)
{
	// wxwidgets側でkillcaretされている。
}


template <class T>
void NesEditorMainViewBase<T>::OnSetFocus(wxFocusEvent& event)
{
	// wxwidgets側でcaret表示制御されているけれど、
	// キャレットがウィンドウ枠外に居るときも、表示されてしまうので補正
	AdjustCaretPos();
}

// ------------------------------
// キーボード操作関連
// ------------------------------
template <class T>
void NesEditorMainViewBase<T>::DoKeyEnter(wxKeyEvent &event)
{
	AddNewLine(false);
	NextLine();
	this->Refresh();
}

template <class T>
void NesEditorMainViewBase<T>::DoKeyDelete(wxKeyEvent &event)
{
	if (IsLastLine()) {
		return;
	}
	wxString& str = *(m_text[m_yCharPos].get());
	if (str.length() < m_xCharPos) {
		return;
	}
	str.Remove(m_xCharPos, 1);
	DrawText(str, 0, m_yCharPos);
}

template <class T>
void NesEditorMainViewBase<T>::DoKeyBack(wxKeyEvent &event)
{
	if (m_xCharPos == 0) {
		return;
	}
	wxString& str = *(m_text[m_yCharPos].get());
	if (str.length() < m_xCharPos) {
		return;
	}
	wxString::const_iterator ite = str.begin() + (m_xCharPos - 1);
	wxUniChar c = *ite;
	m_xCharPos--;
	if (c.IsAscii()) {
		m_xCaret--;
	}else {
		m_xCaret-=2;
	}
	str.Remove(m_xCharPos, 1);
	DrawText(str, 0, m_yCharPos);

}

template <class T>
void NesEditorMainViewBase<T>::DoKeyLeft(wxKeyEvent &event)
{
	PrevChar();
}

template <class T>
void NesEditorMainViewBase<T>::DoKeyRight(wxKeyEvent &event)
{
	NextChar();
}

template <class T>
void NesEditorMainViewBase<T>::DoKeyUp(wxKeyEvent &event)
{
	PrevLine();
}

template <class T>
void NesEditorMainViewBase<T>::DoKeyDown(wxKeyEvent &event)
{
	NextLine();
}


// ------------------------------
// キャレット操作関連
// ------------------------------

/**
 * キャレット描画
 */
template <class T>
void NesEditorMainViewBase<T>::DoMoveCaret()
{
	this->GetCaret()->Move(m_xMargin + m_xCaret * m_widthChar,
					 m_yMargin + m_yCaret * m_heightChar);
//	this->GetCaret()->Move(m_xMargin + m_xCaret * m_widthChar,
//					 m_yMargin + m_yCharPos * m_heightChar);
	//this->GetCaret()->SetSize(m_widthChar, m_heightChar);

}

/**
 * キャレットを最初に移動
 */
template<class T>
void NesEditorMainViewBase<T>::Home()
{
	m_xCharPos = 0;
	m_xCaret = 0;
}

/**
 * キャレットを最後に移動
 */
template <class T>
void NesEditorMainViewBase<T>::End()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
	} else {
		m_xCharPos = m_text[m_yCharPos]->length();
		CalcCaretXPosAndWidth();
	}
}

template <class T>
void NesEditorMainViewBase<T>::FirstLine()
{

}

template <class T> void NesEditorMainViewBase<T>::LastLine()
{

}

/**
 * キャレットを一文字左へ
 */
template <class T>
void NesEditorMainViewBase<T>::PrevChar()
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
template <class T>
void NesEditorMainViewBase<T>::NextChar()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
	} else {
		int tcnt = m_text[m_yCharPos]->length();
		if (m_text[m_yCharPos]->length() <= m_xCharPos) {
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
template <class T>
void NesEditorMainViewBase<T>::PrevLine()
{
	if (m_yCharPos == 0) {
		return;
	}
	// キャレット補正前に一旦現在のスクロール位置補正
	AdjustScrollPos();

	m_yCharPos--;

	int tcnt = m_text[m_yCharPos]->length();
	if (m_text[m_yCharPos]->length() <= m_xCharPos) {
		m_xCharPos = tcnt;
	}

	if (IsCaretWindowTop()) {
		// PGからスクロールさせると、スクロールイベントが発生しないので呼び出し ※内部変数更新用
		MoveScrollPos(0, -1);
	} else {
		m_yCaret--;
	}

	// TODO これ、キャレット補正関数にまとめたい
	CalcCaretXPosAndWidth();
}


/**
 * キャレットを次の行へ
 */
template <class T>
void NesEditorMainViewBase<T>::NextLine()
{
	if (IsLastLine()) {
		m_xCharPos = 0;
		m_xCaret = 0;
		m_yCharPos = m_text.size();
	} else {

		m_yCharPos++;
		if (IsLastLine()) {
			m_xCharPos = 0;
			m_xCaret = 0;
			m_yCharPos = m_text.size();

			// キャレットが画面上一番下なら、キャレットは動かさない
			if (IsCaretWindowBottom()) {
				// PGからスクロールさせると、スクロールイベントが発生しないので呼び出し ※内部変数更新用
				// たぶんほとんど下通る。
				MoveScrollPos(0, 1);
			} else {
				AdjustCaretPos();
			}

		} else {
			int tcnt = m_text[m_yCharPos]->length();
			if (m_text[m_yCharPos]->length() <= m_xCharPos) {
				m_xCharPos = tcnt;
			}

			// TODO これ、キャレット補正関数にまとめたい
			CalcCaretXPosAndWidth();

			// キャレット補正前に一旦現在のスクロール位置補正
			AdjustScrollPos();

			// キャレットが画面上一番下なら、キャレットは動かさない
			if (IsCaretWindowBottom()) {
				// PGからスクロールさせると、スクロールイベントが発生しないので呼び出し ※内部変数更新用
				MoveScrollPos(0, 1);
			} else {
				m_yCaret++;
			}
		}
		// スクロール位置を補正
		// AdjustScrollPos();
	}
}

template <class T>
void NesEditorMainViewBase<T>::AddNewLine(bool bRefresh)
{
	if (IsLastLine()) {
		m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT(""))));
	} else {
		m_text.insert(m_text.begin() + m_yCharPos+1,
				std::unique_ptr<wxString>(new wxString(wxT(""))));
	}

	SetScroll(false);
	SetSurface(false);
	DrawTextLine(m_yCharPos, false);
	if (bRefresh) {
		this->Refresh();
	}
}

/**
 * キャレットのX位置を更新
 * （２バイト文字考慮）
 */
template <class T>
void NesEditorMainViewBase<T>::CalcCaretXPosAndWidth()
{
	m_xCaret = 0;
	if (IsLastLine()) {
		return;
	} else {
		wxString::const_iterator s;
		wxString &str = *m_text[m_yCharPos];
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
template <class T>
wxPoint NesEditorMainViewBase<T>::GetCaretPixelPoint()
{
	wxPoint p;
	p.x = m_xMargin + (m_xCaret * m_widthChar);
	p.y = m_yMargin + (m_yCaret * m_heightChar);
	return p;
}

/**
 * キャレット位置が最終行か判断
 */
template <class T>
bool NesEditorMainViewBase<T>::IsLastLine()
{
	return (m_text.size() < m_yCharPos+1);
}


template <class T>
void NesEditorMainViewBase<T>::AdjustCaretPos()
{
	// キャレットがウィンドウ内にある
	if (IsCaretExistsWindowArea() == 0) {
		m_yCaret = (m_yCharPos) - m_yScrollPos;

		if (!this->GetCaret()->IsVisible()) {
			this->GetCaret()->Show();
		}

		DoMoveCaret();
	} else {
		if (this->GetCaret()->IsVisible()) {
			this->GetCaret()->Hide();
		}
	}

}


template <class T>
void NesEditorMainViewBase<T>::AdjustScrollPos()
{
	int caretArea = IsCaretExistsWindowArea();

	// 上にフレームアウト
	if (caretArea < 0) {
		m_yScrollPos = m_yCharPos;		// スクロール位置を現在編集中の行にする
		m_yCaret = 0;					// キャレット位置補正
		this->Scroll(0, m_yScrollPos);

		// 下にフレームアウト
	} else if (caretArea > 0) {
		wxSize s = this->GetSize();
		int bottom = (int)(s.GetHeight() / m_heightChar);
		m_yScrollPos = m_yCharPos - bottom;		// 現在編集中の行から↑にウィンドウサイズ分移動
		//m_yCharPos = m_yScrollPos;
		this->Scroll(0, m_yScrollPos);

	}

}

/**
 * -1:上にフレームアウト
 *  1:下にフレームアウト
 *  0:フレーム内
 */
template <class T>
int NesEditorMainViewBase<T>::IsCaretExistsWindowArea()
{
	wxSize winSize = this->GetSize();
//	wxPoint cp = this->GetCaret()->GetPosition();
	size_t caretPos = m_yCharPos * m_heightChar;	//キャレット(物理位置）
	size_t winY1 = m_yScrollPos * m_heightChar;		// スクロール位置からy1座標計算(物理位置）
	size_t winY2 = winY1 + winSize.GetHeight();		// スクロール位置＋画面の高さ(物理位置）
	if (caretPos < winY1) {
		return -1;
	}
	if (caretPos > winY2) {
		return 1;
	}

	return 0;
}

template <class T>
bool NesEditorMainViewBase<T>::IsCaretWindowTop()
{
	return (m_yCaret == 0);
}

template <class T>
bool NesEditorMainViewBase<T>::IsCaretWindowBottom()
{
	wxSize s = this->GetSize();
	size_t winH = s.GetHeight();
	size_t caretY = (m_yCaret + 2) * m_heightChar;
	bool bRet = false;
	if ( winH <= caretY ) {
		bRet = true;
	}
	return bRet;
}

template <class T>
void NesEditorMainViewBase<T>::MoveScrollPos(int dx, int dy)
{
	m_yScrollPos += dy;
	this->Scroll(0, m_yScrollPos);
	//this->ScrollPages(1);
	//this->ScrollLines((i++));
}

// ------------------------------
// 文字列操作関連
// ------------------------------

template <class T>
void NesEditorMainViewBase<T>::InsertStr(wxChar ch)
{
	wxString str = ch;
	InsertStr(str);
}

/**
 * キャレット位置に文字列を挿入
 */
template <class T>
void NesEditorMainViewBase<T>::InsertStr(wxString& str)
{
	if (IsLastLine()) {
		AddNewLine(false);
	}
	wxString &text = *m_text[m_yCharPos];
	text.insert(m_xCharPos, str);
	m_xCharPos += str.length();
	CalcCaretXPosAndWidth();
	DrawText(text, 0, m_yCharPos, false);
	this->Refresh();
}

/**
 * 文字の横幅計算
 */
template <class T>
size_t NesEditorMainViewBase<T>::GetStringPixelWidth(wxString& str)
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
template <class T>
size_t NesEditorMainViewBase<T>::GetStringBLen(wxString& str)
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

template <class T>
void NesEditorMainViewBase<T>::PrintEdittingMultiByteStr(wxString &str)
{
	// TODO 20170103_01 複数単語変換処理
	//DrawText(str, m_xCaret, m_yCaret, false);

	wxString &text = *m_text[m_yCharPos];
	DrawText(text, 0, m_yCharPos, false);
	// 候補を描画
	DrawKouhoText(str, m_xCaret, m_yCharPos, false);
	this->Refresh();
}

template <class T>
void NesEditorMainViewBase<T>::DrawTextAll(bool bRefresh)
{
	DrawTextLine(0, bRefresh);
}

template <class T>
void NesEditorMainViewBase<T>::DrawTextLine(wxCoord startRow, bool bRefresh)
{
	int i = 0;
	for(auto ite = m_text.begin() + startRow; ite != m_text.end(); ite++) {
		wxString* str = (*ite).get();
		DrawText(*str, 0, startRow + i, false);
		i++;
	}
	if (bRefresh) {
		this->Refresh();
	}

}

template <class T>
void NesEditorMainViewBase<T>::DrawText(wxString& str, wxCoord col, wxCoord row, bool bRefresh)
{
	//this->PrepareDC(m_dc); ←スクロールするとずれるので呼ばない

//	wxMemoryDC dc(m_bitmap);
	wxMemoryDC& dc = m_dc;

	dc.SetPen(*wxWHITE);
	dc.SetBrush(*wxWHITE);
	wxSize s = this->GetSize();
	dc.DrawRectangle(0, m_yMargin + (row * m_heightChar)
			, s.GetWidth(), m_heightChar);
	dc.SetFont(m_font);
	dc.SetTextBackground(*wxWHITE);

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
			colorFore = *wxBLACK;
			break;

		case CTextColorAnalyzedVal::UNDEF:
		default:
			colorFore = *wxBLACK;
			break;
		}

		dc.SetTextForeground(colorFore);
		wxString& s = v.get()->m_text;
		dc.DrawText(s, m_xMargin + (x * m_widthChar), m_yMargin + (row * m_heightChar));
		x += GetStringBLen(s);
	}
	dc.SetTextForeground(*wxBLUE);
	dc.DrawText(wxT('↵'), m_xMargin + (x * m_widthChar), m_yMargin + (row * m_heightChar));

	if (bRefresh) {
		this->Refresh();
	}

}

template <class T>
void NesEditorMainViewBase<T>::DrawTextTest(wxString& str, wxCoord col, wxCoord row)
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

template <class T>
void NesEditorMainViewBase<T>::DrawKouhoText(wxString& str, wxCoord col, wxCoord row, bool bRefresh)
{
	wxMemoryDC& dc = m_dc;

	dc.SetPen(*wxWHITE);
	dc.SetBrush(*wxWHITE);
	size_t slen = GetStringBLen(str);
	dc.DrawRectangle(0, m_yMargin + (row * m_heightChar)
			, m_xMargin + (slen * m_widthChar), m_heightChar);

	dc.SetFont(m_font);
	dc.SetTextForeground(*wxBLACK);
	int x = col;
	dc.DrawText(str, m_xMargin + (x * m_widthChar), m_yMargin + (row * m_heightChar));

	if (bRefresh) {
		this->Refresh();
	}

}


/**
 * スクロール幅設定
 */
template <class T>
void NesEditorMainViewBase<T>::SetScroll(bool bRefresh)
{
	//TODO 横スクロールの設定
	size_t line = m_text.size();
	wxRect winRect = this->GetClientRect();
	int winH = m_heightChar * (line + 1);
	if (winRect.height <= winH) {
		size_t gamenLine = ((int)(winRect.height) / m_heightChar);
		size_t unoY =gamenLine 										// 画面に収まる行数
				+ ((int)(winH - winRect.height) / m_heightChar);	// はみ出た行数

		// 画面サイズ変更時、画面を大きくすると一番上の現在画面位置までスクロールできなくなるので補正
		if (unoY < m_yScrollPos + gamenLine) {
			unoY += (m_yScrollPos + gamenLine) - unoY;
		}
//		this->SetScrollbars( 0
//				, m_heightChar
//				, 1, unoY, 0, 0 );
//		m_yMaxScrollPos = unoY;
//		this->Scroll(0, m_yScrollPos);

		// スクロール位置をスクロールバー設定時に指定するよう修正
		// 一度０に戻してからスクロールするとちらつく
		this->SetScrollbars( 0
				, m_heightChar
				, 1, unoY + 5, 0, m_yScrollPos );

	} else {
		// スクロールなし
		this->SetScrollbars(1, 1, 0, FALSE);
		m_yScrollPos = 0;
		//m_yMaxScrollPos = 0;
	}

	if (bRefresh) {
		this->Refresh();
	}

}

/**
 * 背景描画面設定
 */
template <class T>
void NesEditorMainViewBase<T>::SetSurface(bool bRefresh)
{
	// ※スクロール設定側で文字幅考慮したウィンドウサイズ設定しているので
	//   VirtualSizeでとってきている

	wxSize surfaceSize = m_dc.GetSize();
	wxSize winSize = this->GetVirtualSize();
	size_t surfaceHeight = surfaceSize.GetHeight();
	size_t surfaceWidth = surfaceSize.GetWidth();

	size_t winHeight = winSize.GetHeight();
	size_t addHeight = (m_heightChar * 100);
	size_t chkHeight = (m_heightChar * 10);

	size_t winWidth = winSize.GetWidth();
	size_t addWidth = (m_widthChar * 100);
	size_t chkWidth = (m_widthChar * 10);

	//size_t newHeight = winHeight + (m_heightChar * 100);

	// 縦チェック
	if (winHeight > surfaceHeight + chkHeight) {
		size_t h = (((int)(winHeight / m_heightChar)) * m_heightChar) + addHeight;
		size_t w = (((int)(winWidth / m_widthChar)) * m_widthChar) + addWidth;
		wxSize bmpSize(w, h);
		// TODO メモリリークしていない？
		// TODO メモリリークの検知手法
		wxBitmap bmp = wxBitmap(bmpSize);
//		m_bitmap = wxBitmap(bmpSize);

		m_dc.SelectObject(bmp);
//		m_dc.SelectObject(m_bitmap);
//		m_dc.SetDeviceOrigin(0, 0);
//		m_dc.SetLogicalOrigin(0, 0);
		//this->PrepareDC(m_dc);
		m_dc.Clear();
		DrawTextAll(bRefresh);
		return;
	}

	// 横チェック
	if (winWidth > surfaceWidth + chkWidth) {
		size_t h = (((int)(winHeight / m_heightChar)) * m_heightChar) + addHeight;
		size_t w = (((int)(winWidth / m_widthChar)) * m_widthChar) + addWidth;
		wxSize bmpSize(w, h);
		wxBitmap bmp = wxBitmap(bmpSize);
//		m_bitmap = wxBitmap(bmpSize);
		m_dc.SelectObject(bmp);
//		m_dc.SelectObject(m_bitmap);
//		m_dc.SetDeviceOrigin(0, 0);
//		m_dc.SetLogicalOrigin(0, 0);
		//this->PrepareDC(m_dc);
		m_dc.Clear();
		DrawTextAll(bRefresh);
		return;
	}

	// TODO 画面が小さくなったときは、背景のDCを小さくする。

}

///////////////////////////////////////////////////////////////////////////////
// エディタメイン処理
///////////////////////////////////////////////////////////////////////////////


wxBEGIN_EVENT_TABLE(NesEditorMainView, wxScrolledWindow)
	EVT_PAINT(NesEditorMainView::OnPaint)
	EVT_CHAR(NesEditorMainView::OnChar)
	EVT_KEY_DOWN(NesEditorMainView::OnKeyDown)
	EVT_SCROLLWIN(NesEditorMainView::OnScrollWin)
	EVT_SIZE(NesEditorMainView::OnSize)
	EVT_SET_FOCUS(NesEditorMainView::OnSetFocus)
	EVT_KILL_FOCUS(NesEditorMainView::OnKillFocus)
//	EVT_SCROLL(NesEditorMainView::OnScroll)
	//EVT_ERASE_BACKGROUND(MyCanvas::OnEraseBackground)
wxEND_EVENT_TABLE()


//NesEditorMainView::NesEditorMainView(wxFrame *parent)
// : NesEditorMainViewBase(parent)
//{
//	this->NesEditorMainView((wxWindow)parent);
//}

NesEditorMainView::NesEditorMainView(wxWindow *parent)
 : NesEditorMainViewBase(parent)
{
	Create(parent, wxID_ANY, wxDefaultPosition, parent->GetSize());
	DisableKeyboardScrolling();

	SetFocusIgnoringChildren();
	SetBackgroundColour(*wxCYAN);
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	SetSurface();

	m_syntaxAnalyzer = std::unique_ptr<CTextColorBase>(new CTextColorNesEngineAsm());

	//TODO ↓↓TEST↓↓
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("1abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("2abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("3abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("4abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("5abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("6abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("7abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("8abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("9abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("10abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("11abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("12abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("13abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("14abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("15abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("16abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("17abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("18abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("19abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("20abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("21abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("22abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("23abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("24abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("25abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("26abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("27abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("28abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("29abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("30abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("31abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("32abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("33abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("34abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("35abcde adc あいうえお ;aaaaaaa"))));
	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("36abcde adc あいうえお ;aaaaaaa"))));
	SetScroll();
	DrawTextAll(true);

//	this->SetScrollbars( 0
//			, m_heightChar
//			, 1, unoY, 0, m_yScrollPos );
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

//	m_text.push_back(std::unique_ptr<wxString>(new wxString(wxT("abcde adc あいうえお ;aaaaaaa"))));
//	DrawText(*m_text[0], 0, 0);


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


	//TODO ↑↑TEST↑↑


}


///////////////////////////////////////////////////////////////////////////////
// エディタパネル ※フレームからはこちらを呼び出す
///////////////////////////////////////////////////////////////////////////////

NesEditor::NesEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos,
		const wxSize& size,
		long style,
		const wxString& name)
 : wxWindow(parent, winid, pos, size, style, name)
{

	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);

//	hBox->Add(new wxButton(this, wxID_EXIT, wxT("Quit1"))
//				, 0				// 横伸縮可
//				, wxEXPAND
//				, 0);

	hBox->Add(new NesEditorLineNumberView(this)
				, 0				// 横伸縮可
				, wxEXPAND
				, 0);

	hBox->Add(new NesEditorMainView(this)
				, 1				// 横伸縮可
				, wxEXPAND
				, 0);


	SetSizer(hBox);

}




} /* namespace NesEngine */
