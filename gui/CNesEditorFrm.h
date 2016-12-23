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
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>
#include <wx/caret.h>

template <class T>
class NesEditorViewBase : public wxCustomBackgroundWindow<T>
{
public:
	NesEditorViewBase(wxFrame *parent);

protected:
	wxMemoryDC m_dc;
	wxFont m_font;
	wxFont m_fontEditting;
	wxColor viewBkColor;

	int m_heightChar, m_widthChar;
	uint32_t m_xCharPos;
	uint32_t m_xCaret, m_yCaret;
	uint32_t m_xChars, m_yChars;
	int m_xMargin, m_yMargin;
	std::vector<wxString*> m_text;

	// event
	WXLRESULT MSWWindowProc(WXUINT message, WXWPARAM wParam, WXLPARAM lParam);
	void OnPaint( wxPaintEvent &event );
	void OnChar(wxKeyEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	//void OnEraseBackground( wxEraseEvent &event );

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
	uint32_t GetStringPixelWidth(wxString& str);
	wxPoint GetCaretPixelPoint();
	bool IsLastLine();

	void PrintEdittingMultiByteStr(wxString &str);
	void DrawText(wxString& text, wxCoord col, wxCoord row);
	void DrawText(wxFont& font, wxString& text, wxCoord col, wxCoord row);
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


#endif /* GUI_CNESEDITORFRM_H_ */
