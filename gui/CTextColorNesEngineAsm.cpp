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

	// ↓もう少しましな書き方ないだろうか

	m_separator.push_back(std::unique_ptr<wxString>(new wxString(wxT(" "))));
	m_separator.push_back(std::unique_ptr<wxString>(new wxString(wxT("\t"))));
	m_separator.push_back(std::unique_ptr<wxString>(new wxString(wxT(";"))));

	// コピー命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("lda"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("ldx"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("ldy"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sta"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("stx"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sty"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("tax"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("tay"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("tsx"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("txa"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("txs"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("tya"))));

	// 演算命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("adc"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("and"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("asl"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bit"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("cmp"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("cpx"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("cpy"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("dec"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("dex"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("dey"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("eor"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("inc"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("inx"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("iny"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("lsr"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("ora"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("ror"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sbc"))));

	// スタック命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("pha"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("php"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("pla"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("plp"))));

	// ジャンプ命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("jmp"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("jsr"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("rts"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("rti"))));

	// ブランチ命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bcc"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bcs"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("beq"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bmi"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bne"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bpl"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bvc"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("bvs"))));

	// フラグ変更命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("clc"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("cld"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("cli"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("clv"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sec"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sed"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("sei"))));

	// その他の命令
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("brk"))));
	m_reserve.push_back(std::unique_ptr<wxString>(new wxString(wxT("nop"))));

	size_t end = m_reserve.size();
	for (size_t i = 0; i < end; i++) {
		m_reserve.push_back(std::unique_ptr<wxString>(new wxString(m_reserve[i].get()->Upper())));
	}

}

CTextColorNesEngineAsm::~CTextColorNesEngineAsm() {
	// TODO Auto-generated destructor stub
}


void CTextColorNesEngineAsm::AnalyzeSub()
{
	SearchSpace();
	SearchComment();
	SearchReserved();
}

void CTextColorNesEngineAsm::SearchComment()
{
	bool bCommentStart = false;
	for (const auto& v : m_analysedVal) {
		if (!bCommentStart) {
			for (wchar_t ch : v.get()->m_text) {
				if (ch == L';') {
					bCommentStart = true;
					v.get()->m_syntax = CTextColorAnalyzedVal::COMMENT;
				}
			}
		} else {
			v.get()->m_syntax = CTextColorAnalyzedVal::COMMENT;
		}
	}
}


void CTextColorNesEngineAsm::SearchReserved()
{
	for (const auto& v : m_analysedVal) {
		if (v.get()->m_syntax != CTextColorAnalyzedVal::UNDEF) {
			continue;
		}
		for (const auto& re : m_reserve) {
			if (re.get()->compare(v.get()->m_text) == 0) {
				v.get()->m_syntax = CTextColorAnalyzedVal::RESERVED;
			}
		}
	}

}


//void CTextColorNesEngineAsm::SearchAddReserved(const wxString& str, wxString::const_iterator& ite)
//{
//	//wxString::const_iterator tmp = *ite;
//	//ite.
//	size_t idx = std::distance(str.begin(), ite);
//	for (const auto& v : m_reserve) {
//		bool bMatch = false;
//		wxString& r =*v.get();
//		if (str.substr(idx, r.length()).compare(r)) {
//
//			bMatch = true;
//		}
//	}
//	//if (str.substr(idx).compare() )
//}

} /* namespace NesEngine */
