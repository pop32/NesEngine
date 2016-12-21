/*
 * CNesEditor.h
 *
 *  Created on: 2016/12/21
 *      Author: kyon
 */

#ifndef GUI_CNESEDITORFRM_H_
#define GUI_CNESEDITORFRM_H_

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
	wxBitmap m_surfaceBmp;
	wxFont m_font;
	wxColor viewBkColor;

	int m_heightChar;
	int m_widthChar;

	void OnPaint( wxPaintEvent &event );
	//void OnEraseBackground( wxEraseEvent &event );

	void DoPaint(wxDC& dc);


	std::vector<wxString*> m_text;

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
