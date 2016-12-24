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


void CTextColorNesEngineAsm::AnalyzeSub(const wxString& str, wxString::const_iterator& ite)
{

	wxString tmp;
	for(ite = str.begin(); ite != str.end();) {
		//wxUniChar uni_ch = *ite;
		wchar_t uni_ch = *ite;
		switch (uni_ch) {
		case L';':
			AddSyntaxCommentToEol(str, ite);
			//CTextColorBase::AddSyntaxCommentToEol(str, ite);
			break;
		default:
			ite++;
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
