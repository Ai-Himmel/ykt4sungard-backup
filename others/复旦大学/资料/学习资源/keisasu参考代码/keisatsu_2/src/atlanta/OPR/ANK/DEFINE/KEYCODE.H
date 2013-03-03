/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: KEYCODE.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キーコード定義
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef KEY_CODE_H
	#define KEY_CODE_H	1

/* POPLAR_Hと共通化するために、従来の定義文を下記ディレクトリに移動しました。
**     \src\atlanta\opr\ank\define\keycode.h"
** By O.Kimoto 1997/07/16*/

/* キーコード */
#define	NO_KEYCODE			0x00			/* 無効						*/  /* By S.Fuki Oct.1,1997 */
#define	AUTO_RX_KEY			0x01			/* 自動受信キー				*/
#define	HOOK_KEY			0x02			/* フック／会話予約キー		*/
#define	HOLD_KEY			0x03			/* 保留キー					*/
#define	MODE_KEY			0x04			/* 画質キー					*/
#define	CONTRAST_KEY		0x05			/* 濃度キー					*/
#define	FUNCTION_KEY		0x06			/* 機能／右矢印キー			*/
#define	CURSOR_LEFT_KEY		0x07			/* 左矢印キー				*/
#define	NEXT_DOC_KEY		CURSOR_LEFT_KEY	/* 次原稿キー				*/
#define	SET_KEY				0x08			/* セットキー				*/
#define	REVIEW_KEY			0x09			/* 通信中止／確認キー		*/
#define	CLEAR_KEY			0x0A			/* クリアキー				*/
#define	DIAL_MARK_KEY		0x0B			/* ダイヤル記号キー			*/
#define	SORT_KEY			DIAL_MARK_KEY	/* ソートキー				*/
#define	BROADCAST_KEY		0x0C			/* 同報キー					*/
#define	SPECIAL_KEY			0x0D			/* 応用通信キー				*/
#define	GROUP_KEY			0x0E			/* グループキー				*/
#define	SPEED_KEY			0x0F			/* 短縮／電話帳キー			*/
#define	MEMORY_TX_KEY		0x10			/* メモリ送信キー			*/
#define	STOP_KEY			0x11			/* ストップキー				*/
#define	START_KEY			0x12			/* スタートキー				*/
#define	COPY_KEY			0x13			/* コピーキー				*/
#define	REDIAL_KEY			0x14			/* リダイヤル／ポーズキー	*/
#define	PAPER_SELECT_KEY	REDIAL_KEY		/* 用紙選択キー				*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/07/21 */
#define	RESERVATION			0x15			/* 会話予約キー				*/
#else
#define	STAMP_KEY			0x15			/* 済みスタンプキー			*/
#endif		/* End of (defined (KEISATSU)) */
#define	REDUCTION_KEY		0x16			/* 縮小キー					*/
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
#define	MERCURY_KEY			REDUCTION_KEY	/* マーキュリーキー			*/
#endif
#if defined(DEU)
#define	GROUND_KEY			REDUCTION_KEY	/* グランドキー				*/
#endif
#define	FLASH_KEY			0x17			/* フラッシュキー			*/
#define	MAGNIFICATION_KEY	FLASH_KEY		/* 拡大キー					*/
#define	COPY_FAX_KEY		0x18			/* コピー／ファクスキー		*/
#define	BOOK_DOC_SIZE_KEY	0x19			/* ブック原稿サイズキー		*/
#define	COPY_RESET_KEY		0x1A			/* コピーリセットキー		*/
#define	TONE_KEY			0x1B			/* トーンキー				*/	/* 追加 97/11/04 T.Fukumoto */
#if defined(HINOKI3) || defined(KEISATSU)	/* by K.Watanabe 2004/10/26 */
#define	MERCURY_KEY			0x1C			/* プレフィックスキー（PRGではSTOCKHM2に合わせてマーキュリーキーのロジックを使用）	*/
#endif

#define	TEN_SHARP_KEY		0x23			/* テンキー＃キー			*/
#define	TEN_AST_KEY			0x2A			/* テンキー＊キー			*/
#define	TEN_0_KEY			0x30			/* テンキー０キー			*/
#define	TEN_1_KEY			0x31			/* テンキー１キー			*/
#define	TEN_2_KEY			0x32			/* テンキー２キー			*/
#define	TEN_3_KEY			0x33			/* テンキー３キー			*/
#define	TEN_4_KEY			0x34			/* テンキー４キー			*/
#define	TEN_5_KEY			0x35			/* テンキー５キー			*/
#define	TEN_6_KEY			0x36			/* テンキー６キー			*/
#define	TEN_7_KEY			0x37			/* テンキー７キー			*/
#define	TEN_8_KEY			0x38			/* テンキー８キー			*/
#define	TEN_9_KEY			0x39			/* テンキー９キー			*/

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
#define	ONETOUCH_01_KEY		0x41			/* ワンタッチ０１キー		*/
#define	ONETOUCH_02_KEY		0x42			/* ワンタッチ０２キー		*/
#define	ONETOUCH_03_KEY		0x43			/* ワンタッチ０３キー		*/
#define	ONETOUCH_04_KEY		0x44			/* ワンタッチ０４キー		*/
#define	ONETOUCH_05_KEY		0x45			/* ワンタッチ０５キー		*/
#define	ONETOUCH_06_KEY		0x46			/* ワンタッチ０６キー		*/
#define	ONETOUCH_07_KEY		0x47			/* ワンタッチ０７キー		*/
#define	ONETOUCH_08_KEY		0x48			/* ワンタッチ０８キー		*/
#define	ONETOUCH_09_KEY		0x49			/* ワンタッチ０９キー		*/
#define	ONETOUCH_10_KEY		0x4A			/* ワンタッチ１０キー		*/
#define	ONETOUCH_11_KEY		0x4B			/* ワンタッチ１１キー		*/
#define	ONETOUCH_12_KEY		0x4C			/* ワンタッチ１２キー		*/
#define	ONETOUCH_13_KEY		0x4D			/* ワンタッチ１３キー		*/
#define	ONETOUCH_14_KEY		0x4E			/* ワンタッチ１４キー		*/
#define	ONETOUCH_15_KEY		0x4F			/* ワンタッチ１５キー		*/
#define	ONETOUCH_16_KEY		0x50			/* ワンタッチ１６キー		*/
#define	ONETOUCH_17_KEY		0x51			/* ワンタッチ１７キー		*/
#define	ONETOUCH_18_KEY		0x52			/* ワンタッチ１８キー		*/
#define	ONETOUCH_19_KEY		0x53			/* ワンタッチ１９キー		*/
#define	ONETOUCH_20_KEY		0x54			/* ワンタッチ２０キー		*/
#define	ONETOUCH_21_KEY		0x55			/* ワンタッチ２１キー		*/
#define	ONETOUCH_22_KEY		0x56			/* ワンタッチ２２キー		*/
#define	ONETOUCH_23_KEY		0x57			/* ワンタッチ２３キー		*/
#define	ONETOUCH_24_KEY		0x58			/* ワンタッチ２４キー		*/
#define	ONETOUCH_25_KEY		0x59			/* ワンタッチ２５キー		*/
#define	ONETOUCH_26_KEY		0x5A			/* ワンタッチ２６キー		*/
#define	ONETOUCH_27_KEY		0x5B			/* ワンタッチ２７キー		*/
#define	ONETOUCH_28_KEY		0x5C			/* ワンタッチ２８キー		*/
#define	ONETOUCH_29_KEY		0x5D			/* ワンタッチ２９キー		*/
#define	ONETOUCH_30_KEY		0x5E			/* ワンタッチ３０キー		*/
#define	ONETOUCH_31_KEY		0x5F			/* ワンタッチ３１キー		*/
#define	ONETOUCH_32_KEY		0x60			/* ワンタッチ３２キー		*/
#define	ONETOUCH_33_KEY		0x61			/* ワンタッチ３３キー		*/
#define	ONETOUCH_34_KEY		0x62			/* ワンタッチ３４キー		*/
#define	ONETOUCH_35_KEY		0x63			/* ワンタッチ３５キー		*/
#define	ONETOUCH_36_KEY		0x64			/* ワンタッチ３６キー		*/
#define	ONETOUCH_37_KEY		0x65			/* ワンタッチ３７キー		*/
#define	ONETOUCH_38_KEY		0x66			/* ワンタッチ３８キー		*/
#define	ONETOUCH_39_KEY		0x67			/* ワンタッチ３９キー		*/
#define	ONETOUCH_40_KEY		0x68			/* ワンタッチ４０キー		*/
#define	ONETOUCH_41_KEY		0x69			/* ワンタッチ４１キー		*/
#define	ONETOUCH_42_KEY		0x6A			/* ワンタッチ４２キー		*/
#define	ONETOUCH_43_KEY		0x6B			/* ワンタッチ４３キー		*/
#define	ONETOUCH_44_KEY		0x6C			/* ワンタッチ４４キー		*/
#define	ONETOUCH_45_KEY		0x6D			/* ワンタッチ４５キー		*/
#define	ONETOUCH_46_KEY		0x6E			/* ワンタッチ４６キー		*/
#define	ONETOUCH_47_KEY		0x6F			/* ワンタッチ４７キー		*/
#define	ONETOUCH_48_KEY		0x70			/* ワンタッチ４８キー		*/
#define	ONETOUCH_49_KEY		0x71			/* ワンタッチ４９キー		*/
#define	ONETOUCH_50_KEY		0x72			/* ワンタッチ５０キー		*/
#define	ONETOUCH_51_KEY		0x73			/* ワンタッチ５１キー		*/
#define	ONETOUCH_52_KEY		0x74			/* ワンタッチ５２キー		*/
#define	ONETOUCH_53_KEY		0x75			/* ワンタッチ５３キー		*/
#define	ONETOUCH_54_KEY		0x76			/* ワンタッチ５４キー		*/
#define	ONETOUCH_55_KEY		0x77			/* ワンタッチ５５キー		*/
#define	ONETOUCH_56_KEY		0x78			/* ワンタッチ５６キー		*/
#define	ONETOUCH_57_KEY		0x79			/* ワンタッチ５７キー		*/
#define	ONETOUCH_58_KEY		0x7A			/* ワンタッチ５８キー		*/
#define	ONETOUCH_59_KEY		0x7B			/* ワンタッチ５９キー		*/
#define	ONETOUCH_60_KEY		0x7C			/* ワンタッチ６０キー		*/
#define	ONETOUCH_61_KEY		0x7D			/* ワンタッチ６１キー		*/
#define	ONETOUCH_62_KEY		0x7E			/* ワンタッチ６２キー		*/
#define	ONETOUCH_63_KEY		0x7F			/* ワンタッチ６３キー		*/
#define	ONETOUCH_64_KEY		0x80			/* ワンタッチ６４キー		*/
#define	ONETOUCH_65_KEY		0x81			/* ワンタッチ６５キー		*/
#define	ONETOUCH_66_KEY		0x82			/* ワンタッチ６６キー		*/
#define	ONETOUCH_67_KEY		0x83			/* ワンタッチ６７キー		*/
#define	ONETOUCH_68_KEY		0x84			/* ワンタッチ６８キー		*/
#define	ONETOUCH_69_KEY		0x85			/* ワンタッチ６９キー		*/
#define	ONETOUCH_70_KEY		0x86			/* ワンタッチ７０キー		*/
#define	ONETOUCH_71_KEY		0x87			/* ワンタッチ７１キー		*/
#define	ONETOUCH_72_KEY		0x88			/* ワンタッチ７２キー		*/
#define	ONETOUCH_73_KEY		0x89			/* ワンタッチ７３キー		*/
#define	ONETOUCH_74_KEY		0x8A			/* ワンタッチ７４キー		*/
#define	ONETOUCH_75_KEY		0x8B			/* ワンタッチ７５キー		*/
#define	ONETOUCH_76_KEY		0x8C			/* ワンタッチ７６キー		*/
#define	ONETOUCH_77_KEY		0x8D			/* ワンタッチ７７キー		*/
#define	ONETOUCH_78_KEY		0x8E			/* ワンタッチ７８キー		*/
#define	ONETOUCH_79_KEY		0x8F			/* ワンタッチ７９キー		*/
#define	ONETOUCH_80_KEY		0x90			/* ワンタッチ８０キー		*/
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if defined(ANZU_L) || defined(ANZU_V)
#define	ONETOUCH_A_KEY		0x41			/* ワンタッチＡキー			*/
#define	ONETOUCH_B_KEY		0x42			/* ワンタッチＢキー			*/
#define	ONETOUCH_C_KEY		0x43			/* ワンタッチＣキー			*/
#define	ONETOUCH_D_KEY		0x44			/* ワンタッチＤキー			*/
#define	ONETOUCH_E_KEY		0x45			/* ワンタッチＥキー			*/
#define	ONETOUCH_F_KEY		0x46			/* ワンタッチＦキー			*/
#define	ONETOUCH_G_KEY		0x47			/* ワンタッチＧキー			*/
#define	ONETOUCH_H_KEY		0x48			/* ワンタッチＨキー			*/
#define	ONETOUCH_I_KEY		0x49			/* ワンタッチＩキー			*/
#define	ONETOUCH_J_KEY		0x4A			/* ワンタッチＪキー			*/
#define	ONETOUCH_K_KEY		0x4B			/* ワンタッチＫキー			*/
#define	ONETOUCH_L_KEY		0x4C			/* ワンタッチＬキー			*/
#define	ONETOUCH_M_KEY		0x4D			/* ワンタッチＭキー			*/
#define	ONETOUCH_N_KEY		0x4E			/* ワンタッチＮキー			*/
#define	ONETOUCH_O_KEY		0x4F			/* ワンタッチＯキー			*/
#define	ONETOUCH_P_KEY		0x50			/* ワンタッチＰキー			*/
#define	ONETOUCH_Q_KEY		0x51			/* ワンタッチＱキー			*/
#define	ONETOUCH_R_KEY		0x52			/* ワンタッチＲキー			*/
#define	ONETOUCH_S_KEY		0x53			/* ワンタッチＳキー			*/
#define	ONETOUCH_T_KEY		0x54			/* ワンタッチＴキー			*/
#define	ONETOUCH_U_KEY		0x55			/* ワンタッチＵキー			*/
#define	ONETOUCH_V_KEY		0x56			/* ワンタッチＶキー			*/
#define	ONETOUCH_W_KEY		0x57			/* ワンタッチＷキー			*/
#define	ONETOUCH_X_KEY		0x58			/* ワンタッチＸキー			*/
#define	ONETOUCH_Y_KEY		0x59			/* ワンタッチＹキー			*/
#define	ONETOUCH_Z_KEY		0x5A			/* ワンタッチＺキー			*/

#define	ONETOUCH_a_KEY		0x61			/* ワンタッチａキー			*/
#define	ONETOUCH_b_KEY		0x62			/* ワンタッチｂキー			*/
#define	ONETOUCH_c_KEY		0x63			/* ワンタッチｃキー			*/
#define	ONETOUCH_d_KEY		0x64			/* ワンタッチｄキー			*/
#define	ONETOUCH_e_KEY		0x65			/* ワンタッチｅキー			*/
#define	ONETOUCH_f_KEY		0x66			/* ワンタッチｆキー			*/
#define	ONETOUCH_g_KEY		0x67			/* ワンタッチｇキー			*/
#define	ONETOUCH_h_KEY		0x68			/* ワンタッチｈキー			*/
#define	ONETOUCH_i_KEY		0x69			/* ワンタッチｉキー			*/
#define	ONETOUCH_j_KEY		0x6A			/* ワンタッチｊキー			*/
#define	ONETOUCH_k_KEY		0x6B			/* ワンタッチｋキー			*/
#define	ONETOUCH_l_KEY		0x6C			/* ワンタッチｌキー			*/
#define	ONETOUCH_m_KEY		0x6D			/* ワンタッチｍキー			*/
#define	ONETOUCH_n_KEY		0x6E			/* ワンタッチｎキー			*/
#define	ONETOUCH_o_KEY		0x6F			/* ワンタッチｏキー			*/
#define	ONETOUCH_p_KEY		0x70			/* ワンタッチｐキー			*/
#define	ONETOUCH_q_KEY		0x71			/* ワンタッチｑキー			*/
#define	ONETOUCH_r_KEY		0x72			/* ワンタッチｒキー			*/
#define	ONETOUCH_s_KEY		0x73			/* ワンタッチｓキー			*/
#define	ONETOUCH_t_KEY		0x74			/* ワンタッチｔキー			*/
#define	ONETOUCH_u_KEY		0x75			/* ワンタッチｕキー			*/
#define	ONETOUCH_v_KEY		0x76			/* ワンタッチｖキー			*/
#define	ONETOUCH_w_KEY		0x77			/* ワンタッチｗキー			*/
#define	ONETOUCH_x_KEY		0x78			/* ワンタッチｘキー			*/
#define	ONETOUCH_y_KEY		0x79			/* ワンタッチｙキー			*/
#define	ONETOUCH_z_KEY		0x7A			/* ワンタッチｚキー			*/

#define	ONETOUCH_U1_KEY		0x81			/* ワンタッチＵ１キー		*/
#define	ONETOUCH_U2_KEY		0x82			/* ワンタッチＵ２キー		*/
#define	ONETOUCH_U3_KEY		0x83			/* ワンタッチＵ３キー		*/
#define	ONETOUCH_U4_KEY		0x84			/* ワンタッチＵ４キー		*/
#define	ONETOUCH_U5_KEY		0x85			/* ワンタッチＵ５キー		*/
#define	ONETOUCH_U6_KEY		0x86			/* ワンタッチＵ６キー		*/
#define	ONETOUCH_U7_KEY		0x87			/* ワンタッチＵ７キー		*/
#define	ONETOUCH_U8_KEY		0x88			/* ワンタッチＵ８キー		*/

#define	PROGRAM_P01			0x91			/* プログラム１キー			*/
#define	PROGRAM_P02			0x92			/* プログラム２キー			*/
#define	PROGRAM_P03			0x93			/* プログラム３キー			*/
#define	PROGRAM_P04			0x94			/* プログラム４キー			*/
#define	PROGRAM_P05			0x95			/* プログラム５キー			*/
#define	PROGRAM_P06			0x96			/* プログラム６キー			*/
#define	PROGRAM_P07			0x97			/* プログラム７キー			*/
#define	PROGRAM_P08			0x98			/* プログラム８キー			*/
#define	PROGRAM_P09			0x99			/* プログラム９キー			*/
#define	PROGRAM_P10			0x9A			/* プログラム１０キー		*/
#define	PROGRAM_P11			0x9B			/* プログラム１１キー		*/
#define	PROGRAM_P12			0x9C			/* プログラム１２キー		*/
#endif	/* defined(ANZU_L) */

#if (PRO_KEYPANEL == PANEL_HINOKI)	/* Add By H.Fujimura 1998/12/28 */
#define	ONETOUCH_01_KEY		0x41			/* ワンタッチ０１キー		*/
#define	ONETOUCH_02_KEY		0x42			/* ワンタッチ０２キー		*/
#define	ONETOUCH_03_KEY		0x43			/* ワンタッチ０３キー		*/
#define	ONETOUCH_04_KEY		0x44			/* ワンタッチ０４キー		*/
#define	ONETOUCH_05_KEY		0x45			/* ワンタッチ０５キー		*/
#define	ONETOUCH_06_KEY		0x46			/* ワンタッチ０６キー		*/
#define	ONETOUCH_07_KEY		0x47			/* ワンタッチ０７キー		*/
#define	ONETOUCH_08_KEY		0x48			/* ワンタッチ０８キー		*/
#define	ONETOUCH_09_KEY		0x49			/* ワンタッチ０９キー		*/
#define	ONETOUCH_10_KEY		0x4A			/* ワンタッチ１０キー		*/
#define	ONETOUCH_11_KEY		0x4B			/* ワンタッチ１１キー		*/
#define	ONETOUCH_12_KEY		0x4C			/* ワンタッチ１２キー		*/
#define	ONETOUCH_13_KEY		0x4D			/* ワンタッチ１３キー		*/
#define	ONETOUCH_14_KEY		0x4E			/* ワンタッチ１４キー		*/
#define	ONETOUCH_15_KEY		0x4F			/* ワンタッチ１５キー		*/
#define	ONETOUCH_16_KEY		0x50			/* ワンタッチ１６キー		*/
#define	ONETOUCH_17_KEY		0x51			/* ワンタッチ１７キー		*/
#define	ONETOUCH_18_KEY		0x52			/* ワンタッチ１８キー		*/
#define	ONETOUCH_19_KEY		0x53			/* ワンタッチ１９キー		*/
#define	ONETOUCH_20_KEY		0x54			/* ワンタッチ２０キー		*/
#define	ONETOUCH_21_KEY		0x55			/* ワンタッチ２１キー		*/
#define	ONETOUCH_22_KEY		0x56			/* ワンタッチ２２キー		*/
#define	ONETOUCH_23_KEY		0x57			/* ワンタッチ２３キー		*/
#define	ONETOUCH_24_KEY		0x58			/* ワンタッチ２４キー		*/
#define	ONETOUCH_25_KEY		0x59			/* ワンタッチ２５キー		*/
#define	ONETOUCH_26_KEY		0x5A			/* ワンタッチ２６キー		*/
#define	ONETOUCH_27_KEY		0x5B			/* ワンタッチ２７キー		*/
#define	ONETOUCH_28_KEY		0x5C			/* ワンタッチ２８キー		*/
#define	ONETOUCH_29_KEY		0x5D			/* ワンタッチ２９キー		*/
#define	ONETOUCH_30_KEY		0x5E			/* ワンタッチ３０キー		*/
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
#define	ONETOUCH_01_KEY		0x41			/* ワンタッチ０１キー		*/
#define	ONETOUCH_02_KEY		0x42			/* ワンタッチ０２キー		*/
#define	ONETOUCH_03_KEY		0x43			/* ワンタッチ０３キー		*/
#define	ONETOUCH_04_KEY		0x44			/* ワンタッチ０４キー		*/
#define	ONETOUCH_05_KEY		0x45			/* ワンタッチ０５キー		*/
#define	ONETOUCH_06_KEY		0x46			/* ワンタッチ０６キー		*/
#define	ONETOUCH_07_KEY		0x47			/* ワンタッチ０７キー		*/
#define	ONETOUCH_08_KEY		0x48			/* ワンタッチ０８キー		*/
#define	ONETOUCH_09_KEY		0x49			/* ワンタッチ０９キー		*/
#define	ONETOUCH_10_KEY		0x4A			/* ワンタッチ１０キー		*/
#define	ONETOUCH_11_KEY		0x4B			/* ワンタッチ１１キー		*/
#define	ONETOUCH_12_KEY		0x4C			/* ワンタッチ１２キー		*/
#define	ONETOUCH_13_KEY		0x4D			/* ワンタッチ１３キー		*/
#define	ONETOUCH_14_KEY		0x4E			/* ワンタッチ１４キー		*/
#define	ONETOUCH_15_KEY		0x4F			/* ワンタッチ１５キー		*/
#define	ONETOUCH_16_KEY		0x50			/* ワンタッチ１６キー		*/
#define	ONETOUCH_17_KEY		0x51			/* ワンタッチ１７キー		*/
#define	ONETOUCH_18_KEY		0x52			/* ワンタッチ１８キー		*/
#define	ONETOUCH_19_KEY		0x53			/* ワンタッチ１９キー		*/
#define	ONETOUCH_20_KEY		0x54			/* ワンタッチ２０キー		*/
#define	COMM_REPORT_KEY		0x55			/* 通信証キー				*/ /* Added by SMuratec L.Z.W 2003/08/01 */
#define	CMD_LIST_KEY		0x56			/* Ｐ通信管理キー			*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	TCH_LIST_KEY		0x57			/* Ｐワンタッチリストキー	*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	SPD_LIST_KEY		0x58			/* Ｐ短縮リストキー			*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	VOLUME_KEY			0x59			/* 音量調整キー				*/ /* Added by Y.Kano 2003/08/27 */
#define	CHARACTER_KEY		0x5A			/* 文字キー					*/ /* Added by SMuratec L.Z.W 2003/10/10 */
#endif	

#define	OPR_GET_KEY_TIMEUP			0xB0	/* １分間キー入力なしタイムアップ			*/
#define	OPR_CHILD_TIMEUP			0xB1	/* チャイルド表示タイムアップ				*/
#define	OPR_PARAM_DISP_TIMEUP		0xB2	/* コピーパラメーター優先表示タイムアップ	*/
#define	OPR_TELBOOK_TEL				0xB3	/* 電話帳発呼 								*/
#define	OPR_SHEET_CHANGE			0xB4	/* ワンタッチシート切り替え 				*/
#define	OPR_TEL_OPERATION			0xB5	/* 電話状態変化								*/
#define	OPR_MEMORY_OVER_OPR			0xB6	/* メモリーオーバー処理						*/
#define	OPR_JAM_RECOVER_OPR			0xB7	/* ジャムリカバー処理						*/
#define	OPR_NEXT_DOC_STORED_OPR		0xB8	/* 次原稿蓄積確認処理						*/
#define	OPR_DIFFERENT_KEY_OPR		0xB9	/* 復号化時キー間違い処理					*/
#define	OPR_RX_ERASE_CIPHER_DOC_OPR	0xBA	/* 受信暗号化原稿消去確認処理				*/
#define	OPR_NO_KEY					0xFF	/* キーが押されていない 					*/


/*-----------------------*/
/* キータイプ 			 */
/*-----------------------*/
#define	NO_KEYTYPE			0				/* 無効						*/  /* By S.Fukui Oct.1,1997 */
#define	SINGLE				1				/* 単一オペレーションキー	*/
#define	HOOK				2				/* フックキー				*/
#define	HOLD				3				/* 保留キー					*/
#define	FUNCTION			4				/* 機能／右矢印キー			*/
#define	LEFT_ARROW			5				/* 左矢印キー				*/
#define	NEXT_DOC			LEFT_ARROW		/* 次原稿キー				*/
#define	ENTER				6				/* セットキー				*/
#define	REVIEW				7				/* 通信中止／確認キー		*/
#define	CLEAR				8				/* クリアキー				*/
#define	DIALMARK			9				/* ダイアル記号キー			*/
#define	SORT				DIALMARK		/* ソートキー				*/
#define	BROADCAST			10				/* 同報キー					*/
#define	SPECIAL				11				/* 応用通信キー				*/
#define	GROUP				12				/* グループキー				*/
#define	SPEED				13				/* 短縮／電話帳キー			*/
#define	STOP				14				/* ストップキー				*/
#define	START				15				/* スタートキー				*/
#define	COPY				16				/* コピーキー				*/
#define	REDIAL				17				/* リダイヤル／ポーズキー	*/
#define	PAPER_SELECT		REDIAL			/* 用紙選択キー				*/
#define	NUMBER				18				/* 数字キー（０～９）		*/
#define	AST					19				/* テンキー ＊				*/
#define	SHARP				20				/* テンキー ＃				*/
#define	REDUCTION			21				/* 縮小キー					*/
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
#define	MERCURY				REDUCTION		/* マーキュリーキー			*/
#endif
#if defined(DEU)
#define	GROUND				REDUCTION		/* グランドキー				*/
#endif
#define	FLASH				22				/* フラッシュキー			*/
#define	MAGNIFICATION		FLASH			/* 拡大キー					*/
#define	ONETOUCH			23				/* ワンタッチキー			*/
#define	PROGRAM				24				/* プログラムキー			*/
#define	COPY_FAX			25				/* コピー／ファクスキー		*/
#define	BOOK_DOC_SIZE		26				/* ブック原稿サイズキー		*/
#define	COPY_RESET			27				/* コピーリセットキー		*/
#define	TONE				28				/* トーンキー				*/	/* 追加 97/11/13 T.Fukumoto */
#define	KEY_TIME_UP			29				/* キー待ちタイムオーバー	*/
#define	NO_EFFECT			30				/* オペレーションにはあまり影響がないもの:チャイルド終了など */
#define	ERROR_OPERATION		31				/* 現在の状態では無効なキー	*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/08/01 */
#define	COMM_REPORT			32				/* 通信証キー				*/
#define	CMD_LIST			33				/* Ｐ通信管理キー			*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	TCH_LIST			34				/* Ｐワンタッチリストキー	*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	SPD_LIST			35				/* Ｐ短縮リストキー			*/ /* Added by SMuratec L.Z.W 2003/08/04 */
#define	VOLUME				36				/* 音量調整キー				*/ /* Added by Y.Kano 2003/08/27 */
#define	CHARACTER			37				/* 文字キー					*/ /* Added by SMuratec L.Z.W 2003/10/10 */
#elif defined(HINOKI3) || defined(KEISATSU)	/* by K.Watanabe 2004/10/12 */
#define	MERCURY				32				/* プレフィックスキー（PRGではSTOCKHM2に合わせてマーキュリーキーのロジックを使用）	*/
#endif
#endif
