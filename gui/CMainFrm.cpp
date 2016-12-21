/*
 * CMainFrm.cpp
 *
 *  Created on: 2016/12/12
 *      Author: kyon
 */

#include "CMainFrm.h"

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(CMainFrm, wxFrame)
	EVT_MENU(CMainFrm_Quit,  CMainFrm::OnQuit)
	EVT_MENU(CMainFrm_About, CMainFrm::OnAbout)
	EVT_MENU(CMainFrm_MemoryDump, CMainFrm::OnMemoryDump)
	EVT_MENU(CMainFrm_NesEditor, CMainFrm::OnNesEditor)
wxEND_EVENT_TABLE()


CMainFrm::~CMainFrm() {
	// TODO Auto-generated destructor stub
}


CMainFrm::CMainFrm(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150)) {

	// set the frame icon
	SetIcon(wxICON(sample));

	// create a menu bar
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(CMainFrm_Quit, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(CMainFrm_About, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	wxMenu *menuTool = new wxMenu;
	menuTool->Append(CMainFrm_MemoryDump, wxT("&MemoryDump\tCtrl-M"));
	menuTool->Append(CMainFrm_NesEditor, wxT("&NesEditor\tCtrl-E"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));
	menuBar->Append(menuTool, wxT("&Tool"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);


}


// event handlers

void CMainFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void CMainFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("The caret wxWidgets sample.\n(c) 1999 Vadim Zeitlin"),
				 wxT("About Caret"), wxOK | wxICON_INFORMATION, this);
}

void CMainFrm::OnMemoryDump(wxCommandEvent& WXUNUSED(event))
{
	// TODO memory leak ???
	CMemoryDumpFrm *frm = new CMemoryDumpFrm(this, wxT("Memory Dump"),
						wxPoint(50, 50), wxSize(450, 340));
	frm->Show(TRUE);
}

void CMainFrm::OnNesEditor(wxCommandEvent& WXUNUSED(event))
{
	// TODO memory leak ???
	CNesEditorFrm *frm = new CNesEditorFrm(this, wxT("Nes Editor"),
						wxPoint(50, 50), wxSize(650, 440));
	frm->Show(TRUE);

}
