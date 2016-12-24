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
	wxString::const_iterator ite = str.begin();
	AnalyzeSub(str, ite);

}

//CTextColorBase& CTextColorBase::operator=(const wxString& str)
//{
//	m_analysedVal.clear();
//	//this->Analyze(str);
//	return *this;
//}


void CTextColorBase::SkipSpace(wxString& str, wxString::const_iterator& ite)
{

	for(ite = str.begin(); ite != str.end(); ite++) {
		wchar_t uni_ch = *ite;
		switch (uni_ch) {
		case L' ':
		case L'\t':
			int a = 0;
			break;
		}
	}

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

} /* namespace NesEngine */
