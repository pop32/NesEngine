/*
 * CMemoryDumpFrm.cpp
 *
 *  Created on: 2016/12/04
 *	  Author: kyon
 */

#include "CMemoryDumpFrm.h"

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(CMemoryDumpFrm, wxFrame)
	EVT_MENU(CMemoryDumpFrm_Quit,  CMemoryDumpFrm::OnQuit)
	EVT_MENU(CMemoryDumpFrm_About, CMemoryDumpFrm::OnAbout)
wxEND_EVENT_TABLE()


CMemoryDumpFrm::~CMemoryDumpFrm()
{
	//TODO memory leak?
}


// frame constructor
CMemoryDumpFrm::CMemoryDumpFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
//	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
	if ( !this->Create(parent, wxID_ANY,
						title,
						pos, size,
						wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE) ) {
		return;
	}

	// set the frame icon
	SetIcon(wxICON(sample));

	// create a menu bar
	wxMenu *menuFile = new wxMenu;

	menuFile->Append(CMemoryDumpFrm_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
	menuFile->AppendSeparator();
	menuFile->Append(CMemoryDumpFrm_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));

	// now append the freshly created menu to the menu bar...
	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, wxT("&File"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);
}


// event handlers

void CMemoryDumpFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void CMemoryDumpFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxT("The caret wxWidgets sample.\n(c) 1999 Vadim Zeitlin"),
				 wxT("About Caret"), wxOK | wxICON_INFORMATION, this);
}


//// frame constructor
//CMemoryDumpFrm::CMemoryDumpFrm(const wxString& title, const wxPoint& pos, const wxSize& size)
//	: wxFrame((wxFrame *)NULL, wxID_ANY, title, pos, size)
//{
//	// set the frame icon
//	SetIcon(wxICON(sample));
//
//	// create a menu bar
//	wxMenu *menuFile = new wxMenu;
//
//	menuFile->Append(Caret_SetBlinkTime, wxT("&Blink time...\tCtrl-B"));
//	menuFile->Append(Caret_SetFontSize, wxT("&Font size...\tCtrl-S"));
//	menuFile->Append(Caret_Move, wxT("&Move caret\tCtrl-C"));
//	menuFile->AppendSeparator();
//	menuFile->Append(Caret_About, wxT("&About\tCtrl-A"), wxT("Show about dialog"));
//	menuFile->AppendSeparator();
//	menuFile->Append(Caret_Quit, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
//
//	// now append the freshly created menu to the menu bar...
//	wxMenuBar *menuBar = new wxMenuBar;
//	menuBar->Append(menuFile, wxT("&File"));
//
//	// ... and attach this menu bar to the frame
//	SetMenuBar(menuBar);
//
//
//}
//
//
//// event handlers
//
//void CMemoryDumpFrm::OnQuit(wxCommandEvent& WXUNUSED(event))
//{
//	// true is to force the frame to close
//	Close(true);
//}
//
//void CMemoryDumpFrm::OnAbout(wxCommandEvent& WXUNUSED(event))
//{
//	wxMessageBox(wxT("The caret wxWidgets sample.\n(c) 1999 Vadim Zeitlin"),
//				 wxT("About Caret"), wxOK | wxICON_INFORMATION, this);
//}


