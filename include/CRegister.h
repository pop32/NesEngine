/*
 * Register.h
 *
 *  Created on: 2016/11/21
 *      Author: kyon
 */

#ifndef CREGISTER_H_
#define CREGISTER_H_

#include "NesEngine.h"

namespace NesEngine {

	class CRegister {
	public:
		CRegister();
		virtual ~CRegister();

		uint8_t A;		// アキュームレータ
		uint8_t X;		// インデックスレジスタ
		uint8_t Y;		// インデックスレジスタ
		uint8_t S;		// スタックポインタ
		uint8_t P;		// ステータスレジスタ

		uint16_t OPERAND;


		void SetPC(uint16_t PC_) {
			PC = PC_;
		}

		void AddPC() {
			PC++;
		}

		void AddPC(uint16_t val) {
			PC += val;
		}

		int GetPC() {
			return PC;
		}

		uint8_t GetNegativeFlg() {
			return N;
		}

		bool IsCarryFlg() {
			return (C == TRUE);
		}

		bool IsZeroFlg() {
			return (Z == TRUE);
		}

		bool IsOverFlowFlg() {
			return (V == TRUE);
		}

		bool IsNegativeFlg() {
			return (N == TRUE);
		}

		uint8_t GetCarryFlg() {
			return C;
		}

		uint8_t GetNotCarryFlg() {
			return C^0x01;
		}

		uint8_t GetZeroFlg() {
			return Z;
		}

		void SetNZFlg(uint8_t val) {
			N = FALSE;
			if (val & 0x80) {
				N = TRUE;
			}
			Z = FALSE;
			if (val == 0) {
				Z = TRUE;
			}
		}

		void SetOverFlowFlg(int8_t prev, int8_t val, int8_t result) {
			V = FALSE;
			if (prev > 0 && val > 0 && result < 0) {
				V = TRUE;
			} else if (prev < 0 && val < 0 && result > 0) {
				V = TRUE;
			}
		}

		void SetCarryFlgAdd(uint8_t prev, uint8_t val, uint8_t result) {
			C = ( (((prev | val) & 0x80) == 0x80) &&  ((result & 0x80) == 0x00) )
						? TRUE : FALSE;
		}

		void SetCarryFlgSub(uint8_t prev, uint8_t result) {
			C = (result > prev) ? FALSE : TRUE;
		}

		void SetCarryFlg(bool bVal) {
			C = bVal ? TRUE : FALSE;
		}

		void SetCarryFlg() {
			C = TRUE;
		}

		void ClearCarryFlg() {
			C = FALSE;
		}

	private:
		uint16_t PC;		// プログラムカウンタ
		uint8_t N;			// ネガティブ
		uint8_t V;			// オーバーフロー
		uint8_t R;			// 予約済み
		uint8_t B;			// ブレークモード
		uint8_t D;			// デシマルモード
		uint8_t I;			// IRQ禁止
		uint8_t Z;			// ゼロ
		uint8_t C;			// キャリー

	};

}

#endif /* CREGISTER_H_ */
