/*
 * CTextColorNesEngineAsm.cpp
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#include "CTextColorNesEngineAsm.h"

namespace NesEngine {

CTextColorNesEngineAsm::CTextColorNesEngineAsm() {
	// TODO 自動生成されたコンストラクター・スタブ
}

CTextColorNesEngineAsm::~CTextColorNesEngineAsm() {
	// TODO Auto-generated destructor stub
}


void CTextColorNesEngineAsm::Analyze(wxString& str)
{
	if (str.length() == 0) {
		return;
	}

	wxString::iterator ite = str.begin();
	wxString tmp;
	std::unique_ptr<CTextColorAnalyzedVal> analyzed = std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
	for(size_t i=0; i < str.length(); i++) {
		//wxUniChar uni_ch = *ite;
		wchar_t uni_ch = *ite;
		switch (uni_ch) {
		case ';':

			break;
		}

//		// コメント行
//		if (uni_ch. == ';')) {
//			analyzed.get()->m_text = str.substr(i);
//			analyzed.get()->m_syntax = CTextColorAnalyzedVal::COMMENT;
//			m_analysedVal.push_back(std::move(analyzed));
//		} else if (str.substr(i,1).compare(wxT(' '))
//				 || str.substr(i,1).compare(wxT('\t')) ) {
//			tmp += str.substr(i,1);
//		}

	}

}


} /* namespace NesEngine */
