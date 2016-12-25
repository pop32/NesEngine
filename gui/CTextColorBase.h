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
//	CTextColorBase& operator=(const wxString& str){
//		return NULL;
//	};
//	//CTextColorBase& operator=(wxString str);

	void Analyze(const wxString& str);

	std::vector<std::unique_ptr<CTextColorAnalyzedVal>>& GetAnalyzedVal()
	{
		return m_analysedVal;
	};

protected:
	std::vector<std::unique_ptr<CTextColorAnalyzedVal>> m_analysedVal;

	std::vector<std::unique_ptr<wxString>> m_separator;

	virtual void AnalyzeSub() = 0;

	void AddSpace(const wxString& str, wxString::const_iterator& ite);
	void AddSyntaxCommentToEol(const wxString& str, wxString::const_iterator& ite);
	void AddUndef(const wxString& str, wxString::const_iterator& ite);
};

} /* namespace NesEngine */

#endif /* GUI_CTEXTCOLORBASE_H_ */
