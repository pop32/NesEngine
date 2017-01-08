/*
 * CChrEditorFrm.cpp
 *
 *  Created on: 2017/01/07
 *      Author: kyon
 */

#include "CChrEditorFrm.h"

namespace NesEngine {

CChrEditorFrm::CChrEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size)
{

	if ( !this->Create(parent, wxID_ANY,
						title,
						pos, size,
						(wxDEFAULT_FRAME_STYLE & ~( wxMAXIMIZE_BOX | wxRESIZE_BORDER )) | wxSYSTEM_MENU | wxCAPTION ) ) {
		return;
	}


}

CChrEditorFrm::~CChrEditorFrm() {
	// TODO Auto-generated destructor stub
}

} /* namespace NesEngine */
