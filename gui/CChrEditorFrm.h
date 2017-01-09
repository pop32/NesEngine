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

		m_cellColor = *wxWHITE;
		m_leftLineColor = *wxBLACK;
		m_topLineColor = *wxBLACK;
		m_rightLineColor = *wxBLACK;
		m_bottomLineColor = *wxBLACK;

	};

	virtual ~CNesEnineGridCell(){};

	void SetCellColor(wxColor color)
	{
		m_cellColor = color;
	};
	void SetLeftLineColor(wxColor color)
	{
		m_leftLineColor = color;
	};
	void SetTopLineColor(wxColor color)
	{
		m_topLineColor = color;
	};
	void SetRightLineColor(wxColor color)
	{
		m_rightLineColor = color;
	};
	void SetBottomLineColor(wxColor color)
	{
		m_bottomLineColor = color;
	};
	void SetValue(wxString& val) {
		m_val = val;
	};

	wxColor GetCellColor()
	{
		return m_cellColor;
	};

	wxColor GetLeftLineColor()
	{
		return m_leftLineColor;
	};
	wxColor GetTopLineColor()
	{
		return m_topLineColor;
	};
	wxColor GetRightLineColor()
	{
		return m_rightLineColor;
	};
	wxColor GetBottomLineColor()
	{
		return m_bottomLineColor;
	};

private:
	int m_nColNum;
	int m_nRowNum;
	wxColor m_cellColor;
	wxColor m_leftLineColor;
	wxColor m_topLineColor;
	wxColor m_rightLineColor;
	wxColor m_bottomLineColor;
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
	void SetValue(int col, int row, wxString& val);

	void SetCellColor(int col, int row, wxColor color);
	void SetCellLineColor(int col, int row,
			wxColor reftColor,
			wxColor topColor,
			wxColor rightColor,
			wxColor bottomColor
			);

	CNesEnineGridCell* GetCell(int col, int row);

protected:
	wxMemoryDC m_dc;
	void OnPaint( wxPaintEvent &event );

	wxDC& GetSurfaceDC();

private:
	int nColNum;
	int nRowNum;

	vector<std::unique_ptr<CNesEnineGridCell>> m_cells;

	wxSize cellSize;

//	void AddCells();

	void SetSurface();
	void DrawSurface();
	void DrawCell(int col, int row);
	wxDECLARE_EVENT_TABLE();

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


	//wxDECLARE_EVENT_TABLE();

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
