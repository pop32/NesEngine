/*
 * CTextColorNesEngineAsm.h
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#ifndef GUI_CTEXTCOLORNESENGINEASM_H_
#define GUI_CTEXTCOLORNESENGINEASM_H_

#include <string>
#include <vector>
#include <memory>
#include <wx/string.h>
#include "CTextColorBase.h"

namespace NesEngine {

class CTextColorNesEngineAsm : public CTextColorBase {
public:
	CTextColorNesEngineAsm();
	virtual ~CTextColorNesEngineAsm();

//	CTextColorNesEngineAsm& operator=(const wxString& str)
//	{
//		return CTextColorBase::
//	};

protected:

	void AnalyzeSub(const wxString& str, wxString::const_iterator& ite);

};

} /* namespace NesEngine */

#endif /* GUI_CTEXTCOLORNESENGINEASM_H_ */
