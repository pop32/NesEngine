/*
 * CTextColorNesEngineAsm.h
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#ifndef GUI_CTEXTCOLORNESENGINEASM_H_
#define GUI_CTEXTCOLORNESENGINEASM_H_

#include <wx/string.h>

namespace NesEngine {

class CTextColorNesEngineAsm {
public:
	CTextColorNesEngineAsm();
	virtual ~CTextColorNesEngineAsm();

	CTextColorNesEngineAsm& operator=(wxString& str);
private:
	wxString m_text;

};

} /* namespace NesEngine */

#endif /* GUI_CTEXTCOLORNESENGINEASM_H_ */
