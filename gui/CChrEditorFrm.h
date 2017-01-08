/*
 * CChrEditorFrm.h
 *
 *  Created on: 2017/01/07
 *      Author: kyon
 */

#ifndef GUI_CCHREDITORFRM_H_
#define GUI_CCHREDITORFRM_H_

#include <stdio.h>
#include <memory.h>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>
#include "CCommon.h"
#include "Resource.h"

namespace NesEngine {

#define GUI_CCHREDITORFRM_H_BLOCK_NUM_COL 8
#define GUI_CCHREDITORFRM_H_BLOCK_NUM_ROW 8

class CChrData
{
public:
	CChrData() {
		memset(data, 0, sizeof(data));
	};
	virtual ~CChrData(){};

	int data[GUI_CCHREDITORFRM_H_BLOCK_NUM_COL][GUI_CCHREDITORFRM_H_BLOCK_NUM_ROW];

};

///////////////////////////////////////////////////////////////////////////////
// 画像編集メイン
///////////////////////////////////////////////////////////////////////////////

class CChrEditorView : public wxScrolledWindow
{

public:
	CChrEditorView(wxWindow *parent,
			const CChrData& chrData,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxPanelNameStr);
	//virtual ~CChrEditorView();

private:
	static const int BLOCK_SIZE = 4;
	static const int LINE_SIZE = 1;

	int nBiritu;
	int nBlockSize;

	wxMemoryDC m_dc;

	const CChrData& m_chrData;

	void OnPaint( wxPaintEvent &event );

	void SetSurface();
	void DrawSurface();

	wxDECLARE_EVENT_TABLE();

};


///////////////////////////////////////////////////////////////////////////////
// メインフレーム
///////////////////////////////////////////////////////////////////////////////

class CChrEditorFrm : public wxFrame {

public:
	CChrEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
//	virtual ~CChrEditorFrm();

private:
	CChrData m_chrData;

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnToolLeftClick(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	CChrEditorFrm_Quit = 1,
	CChrEditorFrm_About,
};


} /* namespace NesEngine */

#endif /* GUI_CCHREDITORFRM_H_ */
