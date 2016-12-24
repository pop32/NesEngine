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


void CTextColorBase::AddSpace(wxString& str, wxString::const_iterator& ite)
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
