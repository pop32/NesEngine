/*
 * CChrEditorFrm.cpp
 *
 *  Created on: 2017/01/07
 *      Author: kyon
 */

#include "CChrEditorFrm.h"

namespace NesEngine {

///////////////////////////////////////////////////////////////////////////////
// メインフレーム
///////////////////////////////////////////////////////////////////////////////

wxBEGIN_EVENT_TABLE(CChrEditorFrm, wxFrame)
	EVT_MENU(CChrEditorFrm_Quit,  CChrEditorFrm::OnQuit)
	EVT_MENU(CChrEditorFrm_About, CChrEditorFrm::OnAbout)
	EVT_MENU(wxID_ANY, CChrEditorFrm::OnToolLeftClick)
wxEND_EVENT_TABLE()

CChrEditorFrm::CChrEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
{

	if ( !this->Create(parent, wxID_ANY,
						title,
						pos, size,
						(wxDEFAULT_FRAME_STYLE & ~( wxMAXIMIZE_BOX | wxRESIZE_BORDER )) | wxSYSTEM_MENU | wxCAPTION ) ) {
		return;
	}

	SetIcon(wxICON(sample));

	wxMenu *menuFile = new wxMenu;

	menuFile->Append(CChrEditorFrm_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(CChrEditorFrm_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
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

	toolBar->AddTool(wxID_OPEN, wxT("Open"),
					toolBarBitmaps[Tool_open], wxT("Open file"));

	toolBar->AddTool(wxID_SAVE, wxT("Save"),
					toolBarBitmaps[Tool_save], wxT("Save file"));

	toolBar->Realize();


	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	hBox->Add(new CChrEditorView(this, wxID_ANY,wxDefaultPosition, wxSize(500,500))
				, 0				// 横伸縮可
				, wxEXPAND
				, 0);

	SetSizer(hBox);
}
//
//CChrEditorFrm::~CChrEditorFrm() {
//	// TODO Auto-generated destructor stub
//}
//
//

// -----------------
// event handlers
// -----------------

void CChrEditorFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void CChrEditorFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("The caret NesEngine .\n(c) 2016 pop32")
			,wxT("About") , wxOK | wxICON_INFORMATION, this);
}

void CChrEditorFrm::OnToolLeftClick(wxCommandEvent& event)
{
	wxString str;
	str.Printf( wxT("Clicked on tool %d\n"), event.GetId());
}


///////////////////////////////////////////////////////////////////////////////
// グリッド
///////////////////////////////////////////////////////////////////////////////

wxBEGIN_EVENT_TABLE(CNesEngineGridBase, wxScrolledWindow)
	EVT_PAINT(CNesEngineGridBase::OnPaint)

wxEND_EVENT_TABLE()

CNesEngineGridBase::CNesEngineGridBase(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos,
		const wxSize& size,
		long style,
		const wxString& name)
{

	if ( !this->Create(parent, wxID_ANY,
						pos, size,
						style, name)) {
		return;
	}
	nColNum = 0;
	nRowNum = 0;

	SetSurface();
	DrawSurface();
}

void CNesEngineGridBase::InitCells(int cols, int rows)
{
	nColNum = cols;
	nRowNum = rows;
	if (nColNum == 0 || nRowNum == 0) {
		return;
	}
	m_cells.clear();

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			m_cells.push_back(std::unique_ptr<CNesEnineGridCell>(new CNesEnineGridCell(c, r)));
		}
	}

	DrawSurface();
}

void CNesEngineGridBase::SetCellSize(wxSize size)
{
	cellSize = size;
	DrawSurface();

}

void CNesEngineGridBase::SetValue(int col, int row, wxString& val)
{
	size_t cellIdx = col * row;
	if (m_cells.size() < cellIdx) {
		return;
	}

	CNesEnineGridCell& cell = *(m_cells[col * row].get());
	cell.SetValue(val);

	DrawSurface();
}


/**
 * 描画イベント
 */
void CNesEngineGridBase::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	this->PrepareDC(dc);
	dc.Blit(wxPoint(0,0), this->GetVirtualSize(), &m_dc, wxPoint(0,0));
}


void CNesEngineGridBase::SetSurface()
{

	wxBitmap bmp = wxBitmap(this->GetVirtualSize());
	m_dc.SelectObject(bmp);
	m_dc.Clear();

}

void CNesEngineGridBase::DrawSurface()
{

//	if (cellSize.GetWidth() == 0 || cellSize.GetHeight() == 0) {
//		return;
//	}

	wxDC& dc = m_dc;
	dc.Clear();

	if (nColNum == 0 || nRowNum == 0) {
		return;
	}

	wxPen pen(*wxBLUE, 1);
	dc.SetPen(pen);
	dc.SetBrush(*wxWHITE);

	for (int r = 0; r < nRowNum; r++) {
		for (int c = 0; c < nColNum; c++) {
			int x1 = c * (cellSize.GetWidth() - 1);
			int y1 = r * (cellSize.GetHeight() - 1);
			dc.DrawRectangle(wxPoint(x1 ,y1), cellSize);
		}
	}

	this->Refresh();

}


///////////////////////////////////////////////////////////////////////////////
// 画像編集メイン
///////////////////////////////////////////////////////////////////////////////


//wxBEGIN_EVENT_TABLE(CChrEditorView, wxScrolledWindow)
//	EVT_PAINT(CChrEditorView::OnPaint)
//
//wxEND_EVENT_TABLE()


CChrEditorView::CChrEditorView(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos,
		const wxSize& size,
		long style,
		const wxString& name)
 : CNesEngineGridBase(parent, winid, pos, size, style, name)
{

	nBiritu = 1;
	nBlockSize = 8 * nBiritu;

	InitCells(8, 8);
	SetCellSize(wxSize(10,10));


}


//CChrEditorView::~CChrEditorView() {
//	// TODO Auto-generated destructor stub
//}


} /* namespace NesEngine */
