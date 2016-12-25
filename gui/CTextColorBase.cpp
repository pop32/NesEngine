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
	for(ite = str.begin(); ite != str.end(); ite++) {
		bool bHit = false;
		for (const auto& sep : m_separator) {
			if (sep.get()->compare(*ite) == 0) {
				// 前回保存
				if (aVal->m_text.length() > 0) {
					m_analysedVal.push_back(std::unique_ptr<CTextColorAnalyzedVal>(aVal));
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
	}

	AnalyzeSub();

}


void CTextColorBase::AddSpace(const wxString& str, wxString::const_iterator& ite)
{

	std::unique_ptr<CTextColorAnalyzedVal> analyzed =
			std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
	CTextColorAnalyzedVal& aVal = *analyzed.get();
	aVal.m_syntax = CTextColorAnalyzedVal::SPACE;
	for(; ite != str.end(); ite++) {
		wchar_t uni_ch = *ite;
		switch (uni_ch) {
		case L' ':
		case L'\t':
			aVal.m_text += *ite;
			break;
		default:
			goto END_SPACE;
		}
	}
	END_SPACE:
	m_analysedVal.push_back(std::move(analyzed));

}

void CTextColorBase::AddSyntaxCommentToEol(const wxString& str, wxString::const_iterator& ite)
{
	std::unique_ptr<CTextColorAnalyzedVal> analyzed =
			std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
	CTextColorAnalyzedVal& aVal = *analyzed.get();
	aVal.m_syntax = CTextColorAnalyzedVal::COMMENT;
	for(; ite != str.end(); ite++) {
		aVal.m_text += *ite;
	}
	m_analysedVal.push_back(std::move(analyzed));
}

void CTextColorBase::AddUndef(const wxString& str, wxString::const_iterator& ite)
{
	std::unique_ptr<CTextColorAnalyzedVal> analyzed =
			std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
	CTextColorAnalyzedVal& aVal = *analyzed.get();
	aVal.m_syntax = CTextColorAnalyzedVal::UNDEF;
	for(; ite != str.end(); ite++) {
		wchar_t uni_ch = *ite;
		switch (uni_ch) {
		case L' ':
		case L'\t':
			goto END_ADD;

		default:
			aVal.m_text += *ite;
		}
	}
	END_ADD:
	m_analysedVal.push_back(std::move(analyzed));
}

} /* namespace NesEngine */
