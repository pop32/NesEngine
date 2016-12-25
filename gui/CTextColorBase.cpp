/*
 * CTextColorBase.cpp
 *
 *  Created on: 2016/12/24
 *      Author: kyon
 */

#include "CTextColorBase.h"

namespace NesEngine {

CTextColorBase::CTextColorBase() {
	// TODO 自動生成されたコンストラクター・スタブ

}

CTextColorBase::~CTextColorBase() {
	// TODO Auto-generated destructor stub
}

void CTextColorBase::Analyze(const wxString& str)
{
	m_analysedVal.clear();
	if (str.length() == 0) {
		return;
	}

	CTextColorAnalyzedVal* aVal = new CTextColorAnalyzedVal();
	aVal->m_syntax = CTextColorAnalyzedVal::UNDEF;
	wxString::const_iterator ite = str.begin();
	for(; ite != str.end(); ite++) {
		bool bHit = false;
		for (const auto& sep : m_separator) {
			if (sep.get()->compare(*ite) == 0) {

				// 前回保存
				if (aVal->m_text.length() > 0) {
					m_analysedVal.push_back(std::unique_ptr<CTextColorAnalyzedVal>(aVal));
				} else {
					// TODO ここの実装なんとかならないか
					delete aVal;
				}

				// セパレータ保存
				aVal = new CTextColorAnalyzedVal();
				aVal->m_syntax = CTextColorAnalyzedVal::UNDEF;
				aVal->m_text += *ite;
				m_analysedVal.push_back(std::unique_ptr<CTextColorAnalyzedVal>(aVal));

				// 次の単語
				aVal = new CTextColorAnalyzedVal();
				aVal->m_syntax = CTextColorAnalyzedVal::UNDEF;
				bHit = true;
			}
		}
		if (!bHit) {
			aVal->m_text += *ite;
		}
	}

	if (aVal->m_text.length() > 0) {
		m_analysedVal.push_back(std::unique_ptr<CTextColorAnalyzedVal>(aVal));
	} else {
		delete aVal;
	}

	AnalyzeSub();

}


void CTextColorBase::SearchSpace()
{
	for (const auto& v : m_analysedVal) {

		if (v.get()->m_text.compare(L' ') == 0
				|| v.get()->m_text.compare(L' ') == 0) {
			v.get()->m_syntax = CTextColorAnalyzedVal::SPACE;
		}

	}
}


} /* namespace NesEngine */
