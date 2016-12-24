/*
 * CTextColorBase.h
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#ifndef GUI_CTEXTCOLORBASE_H_
#define GUI_CTEXTCOLORBASE_H_

#include <string>
#include <vector>
#include <memory>
#include <wx/string.h>
#include "CTextColorAnalyzedVal.h"

namespace NesEngine {

class CTextColorBase {
public:
	CTextColorBase();
	virtual ~CTextColorBase();
	CTextColorBase& operator=(wxString& str);

protected:
	std::vector<std::unique_ptr<CTextColorAnalyzedVal>> m_analysedVal;
	virtual void Analyze(wxString& str) = 0;

	wxString SkipSpace(wxString& str);
};

} /* namespace NesEngine */

#endif /* GUI_CTEXTCOLORBASE_H_ */
