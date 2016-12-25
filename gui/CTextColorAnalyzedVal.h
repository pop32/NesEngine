/*
 * CTextColorAnalyzedVal.h
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#ifndef GUI_CTEXTCOLORANALYZEDVAL_H_
#define GUI_CTEXTCOLORANALYZEDVAL_H_

#include <wx/string.h>

namespace NesEngine {

class CTextColorAnalyzedVal {
public:
	CTextColorAnalyzedVal();
	virtual ~CTextColorAnalyzedVal();

	enum SyntaxType {
		VALUE = 1,
		COMMENT,
		STRRING,
		RESERVED,
		SPACE,
		UNDEF,
	};

	wxString m_text;
	SyntaxType m_syntax;
};

} /* namespace NesEngine */

#endif /* GUI_CTEXTCOLORANALYZEDVAL_H_ */
