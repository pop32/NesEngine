/*
 * CChrEditorFrm.h
 *
 *  Created on: 2017/01/07
 *      Author: kyon
 */

#ifndef GUI_CCHREDITORFRM_H_
#define GUI_CCHREDITORFRM_H_

#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/custombgwin.h>
#include <wx/dcbuffer.h>
#include <wx/chartype.h>


namespace NesEngine {

class CChrEditorFrm : public wxFrame {

public:
	CChrEditorFrm(wxFrame *parent, const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CChrEditorFrm();

};

} /* namespace NesEngine */

#endif /* GUI_CCHREDITORFRM_H_ */
