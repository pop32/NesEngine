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

using namespace std;

namespace NesEngine {

template <class T>
class NesEditorViewBase : public wxCustomBackgroundWindow<T>
{
public:
	NesEditorViewBase(wxFrame *parent);

protected:
	wxMemoryDC m_dc;
	wxFont m_font;
	wxFont m_fontEditting;
	wxFont m_fontComment;

	wxColor viewBkColor;

	int m_heightChar, m_widthChar;
	size_t m_xCharPos;
	size_t m_xCaret, m_yCaret;
	size_t m_xChars, m_yChars;
	int m_xMargin, m_yMargin;
	std::unique_ptr<CTextColorBase> m_syntaxAnalyzer;
	vector<std::unique_ptr<wxString>> m_text;
	wxColor m_ColorComment;
	wxColor m_ColorReserved;

	// event
	WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam);
	void OnPaint( wxPaintEvent &event );
	void OnChar(wxKeyEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	//void OnEraseBackground( wxEraseEvent &event );

	// キーボード操作
	void DoKeyEnter();

	// キャレット操作
	void DoMoveCaret();
	void Home();
	void End();
	void FirstLine();
	void LastLine();
	void PrevChar();
	void NextChar();
	void PrevLine();
	void NextLine();
	void AddNewLine();

	void CalcCaretXPosAndWidth();
	size_t GetStringPixelWidth(wxString& str);
	size_t GetStringBLen(wxString& str);
	wxPoint GetCaretPixelPoint();
	bool IsLastLine();


	// テキスト操作
	void InsertStr(wxChar ch);
	void InsertStr(wxString& str);

	void PrintEdittingMultiByteStr(wxString &str);
	void DrawTextLine(wxCoord startRow);
	void DrawText(wxString& text, wxCoord col, wxCoord row);
	void DrawTextTest(wxString& text, wxCoord col, wxCoord row);

};


class NesEditorView : public NesEditorViewBase<wxScrolledWindow>
{
public:
	NesEditorView(wxFrame *parent);

private:

	wxDECLARE_EVENT_TABLE();

};


class CNesEditorFrm : public wxFrame {
public:
	CNesEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CNesEditorFrm();

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

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
