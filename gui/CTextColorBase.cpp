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
//	wxString::const_iterator ite = str.begin();
//	wxString tmp;
//	for(ite = str.begin(); ite != str.end();) {
//		wchar_t uni_ch = *ite;
//		switch (uni_ch) {
//		case L' ':
//		case L'\t':
//			AddSpace(str, ite);
//			break;
//
////		case L';':
////			AddSyntaxCommentToEol(str, ite);
////			break;
//
//		default:
//			AddUndef(str, ite);
//		}
//	}

	std::unique_ptr<CTextColorAnalyzedVal> analyzed =
			std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
	CTextColorAnalyzedVal& aVal = *analyzed.get();
	aVal.m_syntax = CTextColorAnalyzedVal::UNDEF;

	wxString::const_iterator ite = str.begin();
	wxString prevSeparator = wxT("");
	for(ite = str.begin(); ite != str.end(); ite++) {
		for (const auto& v : m_separator) {
			if (v.get()->compare(*ite)
					&& ! v.get()->compare(prevSeparator)) {
				prevSeparator = *v.get();
				m_analysedVal.push_back(std::move(analyzed));
				analyzed =
						std::unique_ptr<CTextColorAnalyzedVal>(new CTextColorAnalyzedVal());
				aVal = *analyzed.get();
				aVal.m_syntax = CTextColorAnalyzedVal::UNDEF;
			}
			aVal.m_text += *ite;
		}
	}
	m_analysedVal.push_back(std::move(analyzed));

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
