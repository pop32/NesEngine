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


CTextColorBase& CTextColorBase::operator=(wxString& str)
{
	m_analysedVal.clear();
	this->Analyze(str);
	return *this;
}


wxString CTextColorBase::SkipSpace(wxString& str)
{

}

} /* namespace NesEngine */
