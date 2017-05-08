/*
 * CNesEditor.h
 *
 *  Created on: 2016/12/21
 *	  Author: kyon
 */

#ifndef GUI_CNESEDITORFRM_H_
#define GUI_CNESEDITORFRM_H_

#include <string>
#include <vector>
#include <memory>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>
#include <wx/caret.h>
#include "CTextColorBase.h"
#include "CTextColorNesEngineAsm.h"
#include "CCommon.h"
#include "Resource.h"

using namespace std;

namespace NesEngine {


///////////////////////////////////////////////////////////////////////////////
// 行番号表示用クラス
///////////////////////////////////////////////////////////////////////////////
class NesEditorLineNumberView : public wxCustomBackgroundWindow<wxWindow>
{
public:
//	NesEditorLineNumberView(wxFrame *parent);
	NesEditorLineNumberView(wxWindow *parent);

protected:
	wxMemoryDC m_dc;

};


///////////////////////////////////////////////////////////////////////////////
// エディタメイン処理ベース
///////////////////////////////////////////////////////////////////////////////
template <class T>
class NesEditorMainViewBase : public wxCustomBackgroundWindow<T>
{
public:
//	NesEditorMainViewBase(wxFrame *parent);
	NesEditorMainViewBase(wxWindow *parent);

protected:
	wxMemoryDC m_dc;
	//wxBitmap m_bitmap;

	wxFont m_font;
	wxFont m_fontEditting;						// 使っていない（余裕があれば）
	wxFont m_fontComment;						// 使っていない

	wxColor viewBkColor;

	size_t m_heightChar, m_widthChar;
	size_t m_xCharPos, m_yCharPos;				// 現在編集中の行
	size_t m_xCaret, m_yCaret;					// キャレット位置（画面上）
	size_t m_xMargin, m_yMargin;				// 使っていない（スクロールがバグるので）※sizerで何とかする予定
	size_t m_xScrollPos, m_yScrollPos;			// スクロール位置（ユニット単位）
	size_t m_xMaxScrollPos, m_yMaxScrollPos;	// 使っていない

	std::unique_ptr<CTextColorBase> m_syntaxAnalyzer;
	vector<std::unique_ptr<wxString>> m_text;
	wxColor m_ColorComment;
	wxColor m_ColorReserved;

	// event
	WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam);
	void OnPaint( wxPaintEvent &event );
	void OnChar(wxKeyEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	void OnScrollWin(wxScrollWinEvent& event);
	void OnScroll(wxScrollEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnKillFocus(wxFocusEvent& event);
	void OnSetFocus(wxFocusEvent& event);
	//void OnEraseBackground( wxEraseEvent &event );

	// キーボード操作
	void DoKeyEnter(wxKeyEvent &event);
	void DoKeyDelete(wxKeyEvent &event);
	void DoKeyBack(wxKeyEvent &event);
	void DoKeyLeft(wxKeyEvent &event);
	void DoKeyRight(wxKeyEvent &event);
	void DoKeyUp(wxKeyEvent &event);
	void DoKeyDown(wxKeyEvent &event);

	// キャレット操作
	void ShowCaret();
	void DestroyCaret();

	void DoMoveCaret();
	void Home();
	void End();
	void FirstLine();
	void LastLine();
	void PrevChar();
	void NextChar();
	void PrevLine();
	void NextLine();
	void AddNewLine(bool bRefresh = true);

	void CalcCaretXPosAndWidth();
	size_t GetStringPixelWidth(wxString& str);
	size_t GetStringBLen(wxString& str);
	wxPoint GetCaretPixelPoint();
	bool IsLastLine();

	void AdjustCaretPos();
	void AdjustScrollPos();
	int IsCaretExistsWindowArea();
	bool IsCaretWindowTop();
	bool IsCaretWindowBottom();
	void MoveScrollPos(int dx, int dy);

	// テキスト操作
	void InsertStr(wxChar ch);
	void InsertStr(wxString& str);

	void PrintEdittingMultiByteStr(wxString &str);
	void DrawTextAll(bool bRefresh = true);
	void DrawTextLine(wxCoord startRow, bool bRefresh = true);
	void DrawText(wxString& text, wxCoord col, wxCoord row, bool bRefresh = true);
	void DrawTextTest(wxString& text, wxCoord col, wxCoord row);
	void DrawKouhoText(wxString& text, wxCoord col, wxCoord row, bool bRefresh = true);

	void SetScroll(bool bRefresh = true);
	void SetSurface(bool bRefresh = true);
};


///////////////////////////////////////////////////////////////////////////////
// エディタメイン処理
///////////////////////////////////////////////////////////////////////////////
class NesEditorMainView : public NesEditorMainViewBase<wxScrolledWindow>
{
public:
//	NesEditorMainView(wxFrame *parent);
	NesEditorMainView(wxWindow *parent);

private:

	wxDECLARE_EVENT_TABLE();

};

///////////////////////////////////////////////////////////////////////////////
// エディタパネル ※フレームからはこちらを呼び出す
///////////////////////////////////////////////////////////////////////////////
class NesEditor : public wxWindow
{
public:
	NesEditor(wxWindow *parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxPanelNameStr);

};


class CNesEditorFrm : public wxFrame {
public:
	CNesEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CNesEditorFrm();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnToolLeftClick(wxCommandEvent& event);

private:

	wxDECLARE_EVENT_TABLE();

};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	CNesEditorFrm_Quit = 1,
	CNesEditorFrm_About,
	CNesEditorFrm_TestTimer,
};

} /* namespace NesEngine */

#endif /* GUI_CNESEDITORFRM_H_ */
