/*
 * Register.cpp
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#include "CRegister.h"

namespace NesEngine {


CRegister::CRegister()
{
	A = 0;			// アキュームレータ
	X = 0;			// インデックスレジスタ
	Y = 0;			// インデックスレジスタ
	S = 0;			// スタックポインタ
	P = 0;			// ステータスレジスタ

	PC = 0;
	N = 0;			// ネガティブ
	V = 0;			// オーバーフロー
	R = 0;			// 予約済み
	B = 0;			// ブレークモード
	D = 0;			// デシマルモード
	I = 0;			// IRQ禁止
	Z = 0;			// ゼロ
	C = 0;			// キャリー

	OPERAND = 0;
}

CRegister::~CRegister()
{

}


} /* namespace NesEngine */
