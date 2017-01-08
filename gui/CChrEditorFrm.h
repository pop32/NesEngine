/*
 * CChrEditorFrm.h
 *
 *  Created on: 2017/01/07
 *      Author: kyon
 */

#ifndef GUI_CCHREDITORFRM_H_
#define GUI_CCHREDITORFRM_H_

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>
#include "CCommon.h"
#include "Resource.h"

using namespace std;

namespace NesEngine {

#define GUI_CCHREDITORFRM_H_BLOCK_NUM_COL 8
#define GUI_CCHREDITORFRM_H_BLOCK_NUM_ROW 8


///////////////////////////////////////////////////////////////////////////////
// グリッド
///////////////////////////////////////////////////////////////////////////////

class CNesEnineGridCell
{
public:
	CNesEnineGridCell(int nColNum, int nRowNum)
	{
		m_nColNum = nColNum;
		m_nRowNum = nRowNum;
	};

	virtual ~CNesEnineGridCell(){};

	void SetBackGroundColor(wxColor color);
	void SetValue(wxString val);

private:
	int m_nColNum;
	int m_nRowNum;
	wxColor m_bkColor;
	wxString m_val;
};


class CNesEngineGridBase : public wxScrolledWindow
{
public:
	CNesEngineGridBase(wxWindow *parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxPanelNameStr);

//	void AppendCols(int cols);			// 使っていない
//	void AppendRows(int rows);			// 使っていない
//	void SetCellWidth(int width);
//	void SetCellHeight(int height);

	void InitCells(int cols, int rows);
	void SetCellSize(wxSize size);
	void SetValue(int col, int row, wxString val);

protected:
	wxMemoryDC m_dc;
	void OnPaint( wxPaintEvent &event );

private:
	int nColNum;
	int nRowNum;

	vector<std::unique_ptr<CNesEnineGridCell>> m_cells;

//	void AddCells();

	void SetSurface();
	void DrawSurface();


};


///////////////////////////////////////////////////////////////////////////////
// 画像編集メイン
///////////////////////////////////////////////////////////////////////////////

class CChrEditorView : public CNesEngineGridBase
{

public:
	CChrEditorView(wxWindow *parent,
			wxWindowID winid = wxID_ANY,
			const wxPoint& pos = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = wxTAB_TRAVERSAL | wxNO_BORDER,
			const wxString& name = wxPanelNameStr);
	//virtual ~CChrEditorView();

private:

	int nBiritu;
	int nBlockSize;


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
