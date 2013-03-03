/*	By Y.Suzuki 1996/10/24	*/
/*	Original File jun\usr2:\src\kobe\anzu\def_v\rom_tbl.c	*/
/* By S.K Spe.21,1995 */
/************************************************************************
 * 機種名ﾊﾞｰｼﾞｮﾝ名を定義 (16 Chars + NULL)								*
 * ROM_Revision[ROM_REVISION_MAX] = "0123456789ABCDEF";					*
 * 01234 : 機種名														*
 * 5	 : 空白															*
 * 678	 : 仕向国名(ISO参照)											*
 * 9	 : 空白															*
 * ABCDEF: バージョン名													*
 ************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

#if (PRO_EXT_ROM == ENABLE)
#include "\src\atlanta\define\rom_def.h"	/* by K.Watanabe 1998/02/27 */
#endif

#pragma section ROM_VER		/* セクション指定 */

/*------------------------------------------------------------------------
**	ポプラＢ
*/
#if defined(POPLAR_B)
 #if defined(JPN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B JPN 970227";	@* By Y.Suzuki 1996/10/24 第１回 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B JPN 971018";	@* By M.Tachibana フィールド評価用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B JPN 971118";	@* By T.Nose IWST/ADF変更 事前QAT ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 971218";	@* By M.Tachibana PPライン検査用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 971223";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 971229";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980106";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980118";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980123";	@* By M.Tachibana */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980124";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980128";	@* By M.Tachibana */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980130";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980209";	@* By M.Tachibana QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN A0A0A0";	@* 980209 量産用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980309";	@* AL100+DS100 QAT用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN B0A0A0";	@* AL100 + 不具合修正 1998/03/17 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980415";	@* DS100 + ﾜﾝﾀｯﾁ表示 QAT */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980417";	@* DS100 + ﾜﾝﾀｯﾁ表示 QAT */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980424";	@* DS100 + ﾜﾝﾀｯﾁ表示 QAT */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980429";	@* DS100 + ﾜﾝﾀｯﾁ表示 QAT */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN C0A0A0";	@* DS100 + ﾜﾝﾀｯﾁ表示 QAT */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980618";	@* DS100 + ﾍﾟｰｼﾞ分割変更 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN C1A0A0";	@* APS ｳｪｲﾄ数変更 1998/06/24 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980625";	@* DS100修正 1998/06/25 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980626";	@* DS100修正 1998/06/26 By T.Fukumoto */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980703";	@* CLASS1評価用 S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980706";	@* CLASS1評価用 M.Tachibana */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980707";	@* CLASS1評価用 S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN D0B0A0";	@* 拡張クラス１、リモートフラッシュ書換ＲＯＭ、富士製ドラム(Ｃ改）対応 S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 980805";	@* DS100 対応By Y.Suzuki 1998/07/31 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN E0A0A0";	@* DS100 対応量産用 By Y.Suzuki 1998/08/19 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN E5A0A0";	@* 量産用NG By M.Tachibana 1998/11/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN E6A0A0";	@* 量産用 By M.Tachibana 1998/12/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN E7A0A0";	@* 量産用 By Y.Suzuki 1999/01/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN F0A0A0";	@* 量産用 DRAMﾃｽﾄﾓｰﾄﾞ 寒冷地対策 By T.Nose 1999/01/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN F2A0A0";	@* 量産用 By M.Tachibana 1999/07/05 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 000124";	@* 通信管理ﾚﾎﾟｰﾄ出力選択 By M.Tachibana 2000/01/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN G0A0A0";	@* 通信管理ﾚﾎﾟｰﾄ出力選択 By M.Tachibana 2000/01/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN 000509";	@* 特ROM 100%コピーを101%で By M.Tachibana 2000/05/09 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V930  JPN H0A0A0";	/* 誤ダイヤル By M.Tachibana 2002/11/18 */
 #endif
 #if defined(DEU)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  DEU u971127";	@* By M.HARADA */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  DEU 980430";	@* By M.HARADA */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  DEU 980805";	@* By Y.Suzuki 1998/08/05 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU 980806";	@* By Y.Suzuki 1998/08/06 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU E1A0A0";	@* By Y.Suzuki 1998/10/01 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU E3A0A0";	@* 量産用位相ズレ対策By Y.Suzuki 1998/12/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU E3A1A0";	@* 英語の待機中表示日月にする By Y.Suzuki 1998/12/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU E3A2A0";	@* ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝ母国語対応 By Y.Suzuki 1999/01/07 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 DEU G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正By Y.Suzuki 2000/02/03 */
 #endif
 #if defined(FRA)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  FRA 980606";	@* By M.HARADA */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 FRA E0A0A0";	@* By By Y.Suzuki 1998/09/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 FRA E3A0A0";	@* By T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 FRA E3A1A0";	@* 英語の待機中表示日月にする By T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 FRA F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 FRA G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(USA)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 971111";	*//* アリロー無し By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 971117";	*//* アリロー有り/OPR,LST最適化 ON By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 971121";	*//* By M.Tachibana APTI出荷 アリロー有り/OPR,LST最適化 ON */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 971205";	*//* By M.Tachibana APTI出荷 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 971215";	*//* By S.Fukui MAI用 aliroo評価(CLASS1抜き) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980123";	*//* By S.Fukui 自動ｶｾｯﾄ選択/FBSInchｻｲｽﾞｺﾋﾟ-対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980202";	*//* By S.Fukui FBS CLASS1						*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980206";	*//* By S.Fukui ADF ﾚｼﾞｬｺﾋﾟｰ試験用	*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980220";	*//* By S.Fukui 回転受信LtrR -> Ltr印刷対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980225";	*//* By S.Fukui βテスト機用ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B USA 980302";	*//* By S.Fukui ＱＡＴ準備ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "41500 USA 980303";	*//* By S.Fukui ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980307";	*//* By S.Fukui ＱＡＴ用ＲＯＭ 41500 -> 1500 改称 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980318";	*//* By S.Fukui ＱＡＴ用ＲＯＭ 回転不具合対策/ｱﾘﾛｰ対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980319";	*//* By S.Fukui ＱＡＴ用ＲＯＭ 回転受信時マージン*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA A0A0A0";	*//* 量産用 980403 By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980416";	*//* DS100 ＱＡＴ用ＲＯＭ 980416 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980422";	*//* プログラムワンタッチ送信不具合対策 By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980423";	*//* DS100 QATrom bythonda 980423 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980518";	*//* DS100 QATrom bythonda 98/05/18 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980521";	*//* DS100 QATrom bythonda 98/05/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA C0A0A0";	*//* 量産用 980521 bythonda 98/05/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980623";	*//* 量産用 980623 bythonda 98/06/23 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA D0A0A0";	*//* 量産用 bythonda 98/06/30 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA D1A0A0";	*//* 量産用 bythonda 98/07/03 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA D1B0A0";	*//* 量産用 bythonda 98/07/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980805";	*//* 量産用 bythonda 98/08/05 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980818";	*//* 量産用 bythonda 98/08/18 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA 980825";	*//* bythonda980825 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA E0A0A0";	*//* bythonda980825 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 E0A0A0";	*//* S.Fukui ＰＢ仕様 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA E1A0A0";	*//* 逆順プリント不具合対策 By S.Fukui Aug.27, 1998 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 E1A0A0";	*//* S.Fukui ＰＢ仕様 逆順プリント不具合対策 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA E2A0A0";	*//* bythonda981005 富士ドラム対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 E2A0A0";	*//* bythonda981008 富士ドラム対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA E4A0A0";	*//* bythonda981027 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 E4A0A0";	*//* bythonda981027 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA F0A0A0";	*//* bythonda990126 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 F0A0A0";	*//* bythonda990126 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA F1A0A0";	*//* by K.Watanabe 1999/05/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  US1 F1A0A0";	*//* by K.Watanabe 1999/05/27 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1500  USA F1A1A0";	/* ソートコピー初期値ON UNISW J5:0 bythonda 1999/06/21 */
 #endif
 #if defined(GBR_OKI)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 GBR 981110";	@* 沖評価用By Y.Suzuki 1998/11/10 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 GBR E2A0A0";	@* 量産用By Y.Suzuki 1998/11/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 GBR E3A0A0";	@* 量産用 位相ズレ対策By Y.Suzuki 1998/12/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 GBR F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 GBR G0A0A0";	/* RTC誤検出対策 その他が共通不具合修正 By Y.Suzuki 2000/01/28 */
 #elif defined(GBR)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 971112";	*//* ＣＥ申請用 (Unique Sw[G]変更) By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 971117";	*//* アリロー有り/OPR,LST最適化 ON By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 971218";	*//* No Aliroo,部門時間管理有り,FBS local scan NG, 暫定電送	 By S.Fukui */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 980206";	*//* By S.Fukui ＤＶＴ用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 980217";	*//* By S.Fukui ＤＶＴ用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_B GBR 980310";	*//* By S.Fukui ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980319";	*//* By S.Fukui ＱＡＴ用ＲＯＭ 回転不具合対策/ｱﾘﾛｰ対応 D71_B -> D71B*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980331";	*//* By S.Fukui サンプル出荷用 (手差しサイズ変更） */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980406";	*//* By S.Fukui CLASS1/リモート診断 不具合対策 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR A0A0A0";	*//* 量産用 980407 By S.Fukui (パッチ対応）*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980416";	*//* DS100 ＱＡＴ用ＲＯＭ 980416 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980423";	*//* DS1000 ＱＡＴ用ＲＯＭ 980423 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980427";	*//* DS1000 ＱＡＴ用ＲＯＭ 980427 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980518";	*//* DS1000 ＱＡＴ用ＲＯＭ 98/05/18 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980521";	*//* DS100 QAT用ROM 98/05/21 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR C0A0A0";	*//* 量産用 980521 By T.Honda 98/05/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR C0A0A1";	*//* 量産用 980617 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR C1A0A0";	*//* 量産用 980617 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR D0B0A0";	*//* bythonda1998/07/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980810";	*//* 量産用 980810 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980818";	*//* 量産用 98/08/18 By T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 980825";	*//* bythonda980825 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR E0A0A0";	*//* bythonda980825 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR E2A0A0";	*//* bythonda981005 富士ドラム対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR E2B0A0";	*//* bythonda981209 不具合対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR F0A0A0";	*//* bythonda990205 DRAMbackupの不具合対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR F0B0A0";	*//* bythonda990331 SecurityRx設計変更 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 991117";	*//* 特ＲＯＭ ｼﾞｬｰﾅﾙ、TCRのYEAR対応 I7:1パッチ処理 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 000117";	*//* Version Up bythonda2000/01/17 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  GBR 000120";	/* Version Up bythonda2000/01/20 */
 #endif
 #if defined(AUS)
  #if defined(AUS_OKI)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 AUS F0A0A0";	@ Y.Suzuki 1999/02/18*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 AUS G0A0A0";	/* By Y.Suzuki 2000/01/31*/
  #else
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS ******";	*//* By M.HARADA */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS 980817";	*//* by T.Honda 98/08/17 from usa_980818 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS 980818";	*//* by T.Honda 98/08/18 from usa_980818 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS 980825";	*//* by T.Honda 980825 from usa_980818 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS E0A0A0";	*//* by T.Honda */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS E2A0A0";	*//* bythonda981007 富士ドラム対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS E3A0A0";	*//* bythonda981019 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS E3B0A0";	*//* bythonda981209 不具合対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS F0A0A0";	*//* bythonda990205 DRAMbackupの不具合対応 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  AUS 000121";	/* バージョンＵＰ bythonda2000/01/21 */
  #endif
 #endif
 #if defined(TWN)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  SEA ******";	/* By M.HARADA */
 #endif
 #if (0)	/* ヨーロッパ一般を国別に分けます by K.Watanabe 1998/10/22 */
// #if defined(EC1)
///*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  BEL 980416";	*//*  By M.HARADA */
//	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 BEL 980918";	/* by K.Watanabe 1998/09/18 */
// #endif
 #endif
 #if defined(BEL)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 BEL 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 BEL E3A0A0";	@* by T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 BEL F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 BEL G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(ESP)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ESP 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ESP E3A0A0";	@* by T.Nakajima 1998/12/16 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ESP G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(ITA)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ITA 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ITA E3A0A0";	@* by T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ITA F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 ITA G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(NLD)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NLD 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NLD E3A0A0";	@* by T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NLD F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NLD G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(NOR)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR E3A0A0";	@* by T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR E3A1A0";	@* by T.Nakajima 1998/12/17 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR E3A2A0";	@* 英語の待機中表示日月にする By Y.Suzuki 1998/12/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 NOR G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif
 #if defined(SWE)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE 981022";	@* by K.Watanabe 1998/10/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE E3A0A0";	@* by T.Nakajima 1998/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE E3A1A0";	@* by T.Nakajima 1998/12/17 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE E3A2A0";	@* 英語の待機中表示日月にする By Y.Suzuki 1998/12/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE F0A0A0";	@* DRAM、後回転、イマドコ By Y.Suzuki 99/1/28 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OO120 SWE G0A0A0";	/* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/01/28 */
 #endif

 #if defined(EU1)	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71B  EU1 991222";*/	/* 欧州仕様追加 by M.H 1999/12/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU1 000108";*/	/* 評価用 2000/01/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU1 000114";*/	/* 評価用 2000/01/14 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU1 000120";	/* 評価用 2000/01/20 */
 #endif
 #if defined(EU2)	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU2 990915";*/	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU2 000203";*/	/* 評価用 2000/02/03 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU2 G0A0A0";	/* 量産用 2000/02/22 */
 #endif
 #if defined(EU3)	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU3 990915";*/	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU3 000203";*/	/* 評価用 2000/02/03 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU3 G0A0A0";	/* 量産用 2000/02/22 */
 #endif
 #if defined(EU4)	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU4 990915";*/	/* 欧州仕様追加 by M.H 1999/09/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU4 000314";*/	/* 量産用 2000/03/10 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "4100  EU4 G0A0A0";	/* 量産用 2000/03/27 */
 #endif

#endif



/*------------------------------------------------------------------------
**	ポプラＢＮ Ｌ５００
*/
#if defined(POPLR_BN)
 #if defined(JPN)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L500  JPN 990513";
 #endif
#endif

/*------------------------------------------------------------------------
**	ポプラＬ
*/
#if defined(POPLAR_L)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_L  970827";	* By T.Yamaguchi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_L  970829";	* By T.Yamaguchi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971007";	* By Y.Suzuki 1997/10/07 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971015";	* By Y.Suzuki 1997/10/15 */
	/* 971020 CPUに対応するため */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971021";	* By Y.Suzuki 1997/10/21 */
	/* 971021 がプリント不良、蓄積不良だったため */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971022";	* By Y.Suzuki 1997/10/21 */
	/* 画質パラメータ、濃淡３段階 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971028";	* By Y.Suzuki 1997/10/28 */
	/* DVT開始する */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971106";	* By T.Yamaguchi 1997/11/05 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971117";	* By T.Yamaguchi 1997/11/17 */
	/* メモリ管理変更 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971121";	* By T.Yamaguchi 1997/11/21 */
	/* ＥＣＭバッファ２枚持ち */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971127";	* By T.Yamaguchi 1997/11/27 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971129";		* By T.Yamaguchi 1997/11/29 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971202";		* By T.Yamaguchi 1997/12/02 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971205";		* By T.Yamaguchi 1997/12/05 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971212";		* By T.Yamaguchi 1997/12/12 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D71_L JPN 971216";		* By T.Yamaguchi 1997/12/16 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 971219";		* By T.Yamaguchi 1997/12/19 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 971229";		* By T.Yamaguchi 1997/12/29 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980108";		* By Y.Suzuki 1998/01/08 */
	/* ＣＳ用のＲＯＭを作成 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980114";		* By 1998/01/13	 By T.Yamaguchi */
	/* マニュアル作成用 ROM */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980126";		* 1998/01/26  By T.Yamaguchi */
	/* 画質評価用 ROM */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980128";		* 1998/01/28  By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980212";		* 1998/02/12  By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980216";		* 1998/02/16  By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980217";		* QAT用	 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980227";		* QAT用 先端位置調整 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN A0A0A0";		* 量産用 1998/03/06	 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980518";		* flash書き換え By Y.Suzuki 1998/05/18 */
/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN B0A0A0";	* B4--A4 PRINT 修正 By Y.Suzuki 1998/05/18 */
/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN 980722";	* ﾐﾉﾙﾀ/FX(評価)用ﾊﾞｰｼﾞｮﾝｱｯﾌﾟBy Y.Suzuki 1998/07/22 */
/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN B0B0A0";	* ﾊﾞｰｼﾞｮﾝｱｯﾌﾟBy Y.Suzuki 1998/07/24*/
/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN D0A0A0";	* V730の富士電機製ドラム対応 By T.Nakajima 1998/10/19*/
/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "TC751 JPN 981028";	* FX出荷用 By T.Nakajima 1998/10/28*/
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN E0A0A0";	* ｽｷｬﾅ送信TTIｲﾝｻｲﾄﾞ CPU C0C0C0 対応修正 By Y.Suzuki 1998/10/31 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN F0A0A0";	* DRAM化け対応 1999/01/26  By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN F1A0A0";		@* ﾗﾝﾌﾟ確認ｴﾗｰ 800ms-->1s By Y.Suzuki 1999/03/01 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN F2A0A0";		@* ﾗﾝﾌﾟ確認ｴﾗｰ 800ms-->1s By Y.Suzuki 1999/03/01 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN G0A0A0";		@* RTC 誤検出対策 その他共通不具合修正 By Y.Suzuki 2000/02/03 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN G1A0A0";		@* ｺﾋﾟｰ画質変更処理の不具合を修正　By Y.Suzuki 2000/04/14 */
/*   CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN G2A0A0";	@* 英語ﾜｰﾃﾞｨﾝｸﾞずれ修正 ﾛｰｶﾙで対応する。次回OPR_WRD*差し替え要 By Y.Suzuki 2000/09/05 */
   CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  JPN G3A0A0";		/* G2A0A0に通信管理ﾃﾞｰﾀ消失不具合修正 By Y.Suzuki 2001/05/24 次回OPR_WRD*差し替え要 */
#endif

/*------------------------------------------------------------------------
**	ポプラＮ
*/
#if defined(POPLAR_N)
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V730  NTT 980117";		* 1998/01/17  By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  NTT 980315";		* By Y.Suzuki 1998/03/15*/
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN 980316";		* By 1998/03/16	 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN 980402";		* By 1998/04/02	 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN 980403";		* By 1998/04/03	 By T.Yamaguchi */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN 980514";		* By 1998/05/14	 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A0    ";		* By 1998/05/15	 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A1    ";		* By 1998/05/18 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A1    ";		* By 1998/05/21 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A2    ";		* メモリフル表示By 1998/06/08 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3    ";		* G3RXMR蓄積ON By 1998/06/19 By Y.Suzuki */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3.   ";		* 冨士電気ﾄﾞﾗﾑBy Y.Suzuki 1998/07/13 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3..  ";		* CPU Ver read By Y.Suzuki 1998/08/15 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3    ";		* 短縮ハンドシェーク受信修正 1998/10/20 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN 981125";		* いまどこFAX対策 特殊対応 1998/11/25 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3-   ";		* DRAM,後回転、99/01/28 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3+   ";		* ﾗﾝﾌﾟ確認ｴﾗｰ 800ms-->1s By Y.Suzuki 1999/03/01 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3 .  ";		* ﾊﾞｰｼﾞｮﾝ名変更のみ By Y.Suzuki 1999/03/05 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A3 .. ";	* PSSセンサ誤動作対策 By Y.Suzuki 1999/08/11 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A4    ";		@* RTCを必ず6個送出する By Y.Suzuki 1999/09/01 */
   CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400  JPN A4.   ";		/* 最終ﾊﾞｰｼﾞｮﾝｱｯﾌﾟ外部仕様に影響しないものを対応 By Y.Suzuki 2000/03/21 */
#endif

/*------------------------------------------------------------------------
**	ポプラＨ
*/
#if defined(POPLAR_H)
 #if defined(JP1)
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN A255A0";		@* 55転送 By O.Kimoto 2003/02/05 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN A355A0";		/* チェッカー擬似ベル鳴動 By Y.Suzuki 2003/04/30 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN B055A0";		@* 通信結果表示標準、通信予約表示変更など取説とセットで変更 By Y.Suzuki 2003/07/08 */
   CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN B255A0";		/* スキャナーモータ電流値制御、ダイヤルトーン検出ON By Y.Suzuki 2004/07/22 */
 #elif defined(JP0)/* V851 By Y.Suzuki 1902/06/06 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020725";		@* CHECKER 検査用 By Y.Suzuki 2002/07/25 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020726";		@* CHECKER 検査用 By Y.Suzuki 2002/07/26 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020812";		@* ｽﾋﾟｰｶ異音対策、回転受信分割時修正、ｽｷｬﾅ送信副走査ちぢみ対策By Y.Suzuki 2002/08/12 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020819";		@* DVT不具合修正 ﾁｪｯｶｰ最終品By Y.Suzuki 2002/08/19 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020821";		@* ﾁｪｯｶｰ最終品By Y.Suzuki 2002/08/19 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020823";		@* 保留、回転ﾒﾓﾘ残量、などy Y.Suzuki 2002/08/23 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020830";		@* QAT ROM 回転ﾀｽｸ、転写電圧測定ﾀｽｸ大ｽﾀｯｸ化 Y.Suzuki 2002/08/30 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020907";		@* QAT ROM 誤ﾀﾞｲﾔﾙ対策 Y.Suzuki 2002/08/30 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020912";		@* QAT ROM *,#対策 Y.Suzuki 2002/09/12 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020913";		@* QAT ROM 保留解除対策 省エネ FANﾁｮﾛまわり Y.Suzuki 2002/09/12 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020915";		@* QAT ROM CI TEST埋め込み Y.Suzuki 2002/09/15 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020920";		@* QAT ROM OPRｽﾀｯｸｵｰﾊﾞｰﾌﾛ対策 Y.Suzuki 2002/09/20 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020921";		@* QAT ROM ﾘﾓｰﾄ診断、AL100 TTI 修正 Y.Suzuki 2002/09/21 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020924";		@* QAT ROM 停電検出ﾘｽﾄSTOPｷｰを弾く  Y.Suzuki 2002/09/24 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 020926";		@* QAT ROM 機内FANﾛｯｸ 400ms Y.Suzuki 2002/09/26 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN 021001";		@* QAT ROM 原稿付きﾁｪｯｸﾒｯｾｰｼﾞゴミ対策 Y.Suzuki 2002/10/01 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN A0A0A0";		@* 量産ROM 原稿付きﾁｪｯｸﾒｯｾｰｼﾞゴミ対策 Y.Suzuki 2002/10/01 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN A1A0A0";		@* 量産ROM sakaki誤ﾀﾞｲﾔﾙ対策 Y.Suzuki 2002/10/03 */
/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN A2A0A0";		@* 量産ROM M.Maeda 2003/02/04 */
   CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V851  JPN B2A0A0";		/* スキャナーモータ電流値制御、ダイヤルトーン検出ON  By Y.Suzuki 2004/07/22 */
 #else
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980105"; */		 /*	 by H.Kubo 1997/12/25 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980109"; */		 /*	 by T.Soneoaka 1998/01/09 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980117"; */						 /*	 By O.Kimoto 1998/01/14 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980119"; */						 /*	 By O.Kimoto 1998/01/14 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980120"; */						 /*	 By T.Soneoka 1998/01/20 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "POPLAR_H  980121"; */						 /*	 By T.Soneoka 1998/01/21 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980122"; */						 /*	 By T.Soneoka 1998/01/22 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980127"; */						 /*	 By O.Kimoto 1998/01/26 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980128"; */						 /*	 By T.Soneoka 1998/01/28 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980129"; */						 /*	 By O.Kimoto 1998/01/29 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980130"; */						 /*	 By T.Soneoka 1998/01/30 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980203"; */						/*	By A.Hatanaka 1998/02/03 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980206"; */						/*	By A.Hatanaka 1998/02/06 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980210"; */						 /*	 By A.Hatanaka 1998/02/10 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980213"; */						/*	By H.Kubo 1998/02/13 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980215"; */						/*	By T.Soneoka 1998/02/15 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980216"; */						/*	By O.Kimoto 1998/02/16 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980218"; */						/*	By O.Kimoto 1998/02/16 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980219"; */						/* フィールド評価用 By O.Kimoto 1998/02/19 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980221"; */						/* フィールド評価用 By O.Kimoto 1998/02/19 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980302"; */						/* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/02 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980304"; */						/* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/02 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980314"; */						/* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/14 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980316"; */						/* 評価用ＲＯＭ by T.Soneoka 1998/03/19	 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980319"; */						/* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/16 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980326"; */						/* ＪＢＩＧ評価用 By T.Soneoka 1998/03/23 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980323"; */						/* ＪＢＩＧ評価用 ＥＤ／量産Ｒ．３．３調査用 By T.Soneoka 1998/03/23 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980327"; */							 /* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/27 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980331"; */							 /* インデックス化け修正ＲＯＭ By T.Soneoka 1998/03/31 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980401"; */							 /* 評価用ＲＯＭ By T.Soneoka 1998/04/01 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980402"; */							 /* 評価用ＲＯＭ By H.Kubo 1998/04/02 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980403"; */							 /* ＱＡＴ前ＲＯＭ中間ＶｅｒＵＰ By O.Kimoto 1998/03/27 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980406"; */							 /* ＱＡＴ用ＲＯＭ By O.Kimoto 1998/04/06 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980410"; */							 /* Ｖ８５０フルオプション対応 By O.Kimoto 1998/04/06 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980413"; */							 /* ＱＡＴ用 拡張受信できず対応版 By T.Soneoka 1998/04/13 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980415"; */							 /* ＱＡＴ用 拡張受信できず対応版 By T.Soneoka 1998/04/13 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980417"; */							  /* ２ｎｄＱＡＴ直前ＲＯＭ By O.Kimoto 1998/04/17 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980420"; */							 /* ３ｎｄＱＡＴ直前ＲＯＭ By T.Soneoka 1998/04/20 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980422"; */							  /* ＪＢＩＧフィールド評価用ＲＯＭ By T.Soneoka 1998/04/22 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980427"; */							 /* ４ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/04/27 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980428"; */							 /* ５ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/04/27 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980430"; */							/* ６ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/04/30 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980501"; */							 /* ６ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/01 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980506"; */							 /* ７ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/06 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980509"; */							 /* ７ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/07 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980513"; */							 /* ８ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/13 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980515"; */							 /* ９ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/13 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980519"; */							 /* ９ｔｈ ＱＡＴ ＲＯＭ By T.Soneoka 1998/05/19 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980521"; */							 /* QAT ROM By T.Soneoka 1998/05/21 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980522"; */							 /* QAT ROM By T.Soneoka 1998/05/22 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN D0A0A0"; */							 /* 量産ROM ROM By T.Soneoka 1998/06/03 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 98609";	*/							/* マルチＴＴＩ（特ＲＯＭ） By O.Kimoto 1998/06/09 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980617"; */						   /* スクランブル仕様変更対応 By O.Kimoto 1998/06/17 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980626"; */							 /* スクランブル仕様変更対応 1998/06/26 by T.Soneoka */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN D0B0A0"; */		/* ドラム（Ｃ改）対応ＲＯＭ By O.Kimoto 1998/07/09 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN D0B0A1"; */		/* 短縮ﾊﾝﾄﾞｼｪｰｸ修正 By O.Kimoto 1998/07/23 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980803"; */		/* マルチＴＴＩ（仮名ＩＤ対応）特ＲＯＭ By O.Kimoto 1998/08/03 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN D0B0B0"; */		/* ダイヤルイン番号登録時の不具合修正 By O.Kimoto 1998/08/06 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980812"; */		/* ＤＳ－１００ ＱＡＴ用ＲＯＭ By O.Kimoto 1998/08/10 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980824"; */		/* ﾌﾟﾛｸﾞﾗﾑﾜﾝﾀｯﾁ(一括送信)不具合修正、RTCﾃｽﾄ仕様変更 By H.Fujimura 1998/08/24 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980826"; */		/* ｽｸﾗﾝﾌﾞﾙ解除時にｷｰ間違いを検出しﾌﾟﾘﾝﾄをｷｬﾝｾﾙ時の不具合修正 By H.Fujimura 1998/08/26 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980904"; */		/* ＤＳ－１００ ＱＡＴ不具合修正 By H.Fujimura 1998/09/04 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980907"; */		/* ＤＳ－１００ ＱＡＴ不具合修正 By O.Kimoto 1998/09/07 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 980911"; */		/* ＤＳ－１００ ＱＡＴ不具合修正 By H.Fujimura 1998/09/11 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 981008"; */		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN E0A0A0"; */		/* 富士ドラム対応 By O.Kimoto 1998/10/05 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN E0A0B0";	*/	/* メモリ管理不具合（俗称：金太郎現象）修正 By O.Kimoto 1998/10/31 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN E0A0C0";	*/	/* E0A0A0時のINI_TBL.C差し替えミス不具合修正（富士ドラム対応初期値を反映する) 1998/11/02 by T.Soneoka */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 990130";	*/	/* 寒冷地対策・日立製ＤＲＡＭ対策用 by H.Kubo 1999/01/30 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 990201";	*/	/* 寒冷地対策第二版 by H.Kubo 1999/02/01 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN F0A0A0";	*/	/* 寒冷地対策・日立製ＤＲＡＭ対策など出荷ＲＯＭ by H.Kubo 1999/02/01 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN F0B0A0";	*/	/* ＳＲＡＭ化け時のループ対策出荷ＲＯＭ by H.Kubo 1999/02/27 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN G0A0A0";	*/	/* ＪＢＩＧ不具合／Ｔ．１．１対策導入量産ＲＯＭ by O.Kimoto 1999/04/23 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN H0A0A0";	*/	/* 通信管理記録仕様変更、その他 By O.Kimoto 1999/11/26 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN H1A0A0";	*/	/* 通信管理記録仕様変更、その他 By O.Kimoto 1999/11/26 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN 001013";	*/	/* ダム通知通報用特ＲＯＭ By O.Kimoto 2000/09/28 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN H2A0A0"; */	/* パルス発呼処理をタスク化 By O.Kimoto 2002/09/20 */
		/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN H3A0A0";	*/	/* ワンショットタイマー不正割り込み対策 By O.Kimoto 2002/10/04 */
		CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V850  JPN H4A0A0";		/* 英語ワーディングが出ない不具合対策 By H.Fujimura 2003/01/17 */
 #endif
#endif

/*------------------------------------------------------------------------
**	アンズＬ
*/
#if defined(ANZU_L)

 #if defined(USA)
  #if defined(USAOKI)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OF580RUSA A3A1A1"; */	/*980205 A3A1A0からUSAOKIのだけのためにワーディングを差し替えたもの(A4->LT)*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OF580RUSA A3A2A1"; */	/*980210 スキャナ送信時のスタック溢れスタティック化*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OF580RUSA C1A0A0"; */	/*980601 ﾌﾗｼｭﾘﾓｰﾄ書き換え*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OF580RUSA C2A0A0"; */	/*980605 LCD,LED I/Oｳｴｲﾄ*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "OF580RUSA E0A0A0";	/*000222 全メイク最終ロム*/
  #elif defined(USAMLT)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980514"; */	/* 1998/05/14 ﾐﾉﾙﾀ8ppmﾃｽﾄ用 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980518"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980522"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980528"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980601"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980609"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980806"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980807"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980811"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980815"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980817"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980818"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980827"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980831"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 980930"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 981001"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 981005"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 981118"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 981201"; */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R8PPM 981203";

  #else
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971001"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971002"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971003"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971009"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971014"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971016"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971018"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971019"; */	/*ここからRev.B*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971020"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971022"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971027"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971031"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971108"; */	/*DRAM wait up*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971117"; */	/*300*400対応テスト*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971119"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971122"; */	/*DVT2用*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971125"; */	/*ECMバッファ拡張*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971128"; */	/* MAI */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971208"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971213"; */	/*ここからRev.C*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971214"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971216"; */	/*最終メモリ管理*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971217"; */	/*Pre QAT Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971222"; */	/*QAT Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971226"; */	/*QAT2 Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 971227"; */	/*F100&F101用入札サンプル Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 980114"; */	/*F100 DVT Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A0A0A0"; */	/*980119 F100 QAT & F120量産第1号Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA 980123"; */	/*ソフトコーデック評価用 Y.SUZUKI */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A1A0A0"; */	/*980127 F100量産第1号 & F120量産第2号Rom*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A2A0A0"; */	/*980127 F100量産第1号 & F120量産第2号Rom(10mSタイマ処理をマルチタイマーへ移動)*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A3A0A0"; */	/*980129 F100量産第1号 & F120量産第2号Rom(プリントごみ処理)*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A3A1A0"; */	/*980202 F100量産第1号 ファインノーマル変換初期値変更*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A3A1A1"; */	/*980205 A3A1A0からUSAOKIのだけのためにワーディングを差し替えたもの(A4->LT)*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA A3A2A1"; */	/*980210 スキャナ送信時のスタック溢れスタティック化*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA B0A0A0"; */	/*980317 アラムコ用作成のため、USAをバージョンアップ*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA B0A0A1"; */	/*980416 B0A0A0のCL1にバグがあったため修正*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA B0A0A2"; */	/*980519 B0A0A1のCL1の停止処理をはじいてないため修正*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA C1A0A0"; */	/*980601 ﾌﾗｯｼｭﾘﾓｰﾄ書き換え*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA C1A0A1"; */	/*980603 ｱﾗﾑｺ仕様 A4対応*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA C2A0A0"; */	/*980605 LCD,LED I/Oｳｴｲﾄ C1A0A0ﾍﾞｰｽ*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA C2A0B0"; */	/*980608 LCD,LEDのI/Oｳｴｲﾄ & ｱﾗﾑｺ仕様A4対応 C1A0A1ﾍﾞｰｽ*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA C3A0A0"; */	/*980615 受信原稿に受信時刻を載せる対応(CIL) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA D0A0A0"; */	/*980714 Salutation機能追加 by Y.Tanimoto */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA E0A0A0"; */	/*000222 全メイク最終ロム*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA E1A0A0";	/*000925 増設メモリ実装次時の機器設定リストメモリ量表記不具合修正 */
  #endif
 #endif
 #if defined(GBR)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980116"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980119"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980220"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980223"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980224"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR 980225"; */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  GBR E0A0A0";	/*000222 全メイク最終ロム*/
 #endif
 #if defined(TWN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980116"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980119"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980119"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980202"; */	/*申請用ロム*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980209"; */	/*申請用ロム*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980214"; */	/*申請用ロム*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980218"; */	/*SGP,MYS申請用ロム*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980219"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980220"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA 980223"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA C0A0A0"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA C0A0A1"; */	/* 1998/05/19 CL1の停止処理をはじいてなかったﾊﾞｸﾞの修正 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA C0A0B0"; */	/* 1998/05/19 CL1の停止処理をはじいてなかったﾊﾞｸﾞの修正 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  SEA E0A0A0";	/*000222 全メイク最終ロム*/
 #endif
 #if defined(AUS)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS 980116"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS 980119"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS 980121"; */	/*申請用ロム*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS 980219"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS 980223"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS B1A0A0"; */	/* 量産No.1 1998/04/06 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS B1A0A1"; */	/*980416 B1A0A0のCL1にバグがあったため修正*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS B1A0A2"; */	/*980508 B1A0A1のPINにバグがあったため修正*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS C1A0A0"; */	/*980601 ﾌﾗｯｼｭﾘﾓｰﾄ書き換え*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS C2A0A0"; */	/*980608 LCD,LEDのI/Oｳｴｲﾄ*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D65R  AUS E0A0A0";	/*000222 全メイク最終ロム*/
 #endif

#endif	/* End of ANZU_L */

/*------------------------------------------------------------------------
**	サカキ
*/
#if defined(SAKAKI)
 #if defined(JP0)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN 021115"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN 021205"; */	/* QATROM(1) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN 021216"; */	/* QATROM(2) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A0A0A0"; */	/* 2002/12/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN 030116"; */	/* ＲＡＭチェック確認用 By M.Maeda 2003/01/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A1A0A0"; */	/* カバーオープン時に24VOFF 2003/01/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A2A0A0"; */	/* 1300Hz着信不良 2003/01/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A3A0A0"; */	/* リモートダイヤル転送対応 2003/01/29 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A4A0A0"; */	/* FM336PLUS対応 2003/06/03 H.Yoshikawa */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A5A0A0"; */	/* NG:OCA対応 2003/09/20 H.Yoshikawa */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A6A0A0"; */	/* OCA対応 2003/10/27 H.Yoshikawa */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A7A0A0"; */	/* OCA対応 2003/11/9 H.Yoshikawa */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN A8A0A0"; */	/* OCA対応 2003/11/28 H.Yoshikawa */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN B0A0A0"; */	/* DT音対応/DS1 2004/07/20 H.Yoshikawa */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F551  JPN B1A0A0";	/* DS1 2004/07/21 H.Yoshikawa */
 #else
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "XXXX  JPN YYMMDD"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981012"; */	/* CS用New Monitor(981010以降) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981021"; */	/* QAT用New Monitor(981021以降）*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981026"; */ /* QAT出荷ROM(1) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981031"; */ /* QAT出荷ROM(2) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981114"; */ /* QAT 前基本動作確認 ROM ICE一号機のLocalでROM化する */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981116"; */ /* QAT出荷ROM(3) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981117"; */	/* QAT出荷ROM(4) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981118"; */	/* QAT出荷ROM(4) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981119"; */	/* QAT出荷ROM(5) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981120"; */	/* QAT出荷ROM(6) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981122"; */	/* QAT出荷ROM(7) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981125"; */	/* QAT出荷ROM(8) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981126"; */	/* QAT出荷ROM(9) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN A0A0A0"; */	/* 量産出荷ROM(1) 1998/11/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN A1A0A0"; */	/* 量産出荷ROM(2) 1998/11/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN A2A0A0"; */	/* 量産出荷ROM(3) 1998/11/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981204"; */	/* ND テスト用 1998/11/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981205"; */	/* ﾄｯﾌﾟｶﾊﾞｰ開閉ﾃｽﾄ用 1998/12/5 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN A3A0A0"; */	/* 量産出荷ROM(4) 1998/12/05 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 981221"; */	/* 絵付き不達通知追加 1998/12/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990114"; */	/* リモートフラッシュ書き換えデバッグ用 1999/01/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990120"; */	/* リモートフラッシュ書き換えデバッグ用 1999/01/20 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990121"; */	/* リモートフラッシュ書き換えデバッグ用 1999/01/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990126"; */	/* 日立製ＤＲＡＭの立ち上げ時不具合対策検査用 1999/01/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990128"; */	/* 日立製ＤＲＡＭの立ち上げ時不具合対策検査用 1999/01/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN B0A0A0"; */	/* 量産出荷ROM(4) 1999/02/02 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN B1A0A0"; */	/* 量産出荷ROM(5) 1999/02/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN B2A0A0"; */	/* 量産出荷ROM(6) 1999/02/23 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 990401"; */	/* OCA QAT出荷前検査ROM 1999/04/01 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C0A0A0"; */	/* OCA量産出荷ROM(1) 1999/04/06 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C1A0A0"; */	/* 量産出荷ROM(7),OCA量産出荷ROM(2) 1999/4/23 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C2A0A0"; */	/* 量産出荷ROM(8) 1999/8/5 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C3A0A0"; */	/* 量産出荷ROM(9) 1999/08/30 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 991026"; */	/* 1999/10/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C4A0A0"; */	/* 量産出荷ROM(10) 2000/02/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C5A0A0"; */	/* 量産出荷ROM(10) 誤ダイヤル対策 2000/10/18 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN 010221"; */	/* 誤ダイヤル対策[2] ダイヤルパルス縮退対応 2001/02/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C6A0A0"; */ /* 量産出荷ROM(11) 誤ダイヤル対策[2] 2001/02/23 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C7A0A0"; */	/* 量産出荷ROM(12) 最低送信速度設定 2001/04/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN C90A0A0" */	/* 量産出荷ROM(13) F網・電源立ち上がらず パッチ修正 2002/02/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550A JPN D0A0A0"; */	/* 量産出荷ROM(14) アイフル仕様（任意短縮他）2002/02/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN D1A0A0"; */	/* 量産出荷ROM(15) 発着衝突&Head制御 2002/12/05 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F550  JPN D2A0A0";	/* 量産出荷ROM(16) OKI仕様　送信証フォーマット修正 2003/03/10 */
 #endif
	/* アイフル仕様のVersion名は		       = "F550A JPN D0A0A0";とします。2002/02/13 H.Yoshikawa */
#endif

/*------------------------------------------------------------------------
**	アンズＶ
*/
#if defined(ANZU_V)
	/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "ANZU_V    961024";	@* By Y.Suzuki 1996/10/24 */
	/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R USA IFAX  ";	@*1998/05/22 Eguchi*/
	/*CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R US9 980704";	@*1998/07/04 Eguchi*/
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F120R US9 980818";	/*1998/08/18 Eguchi*/
#endif

/*------------------------------------------------------------------------
**	ＨＩＮＯＫＩ
*/
#if defined(HINOKI)
 #if defined(JPN)
	/* HINOKI By O.Kimoto 1998/09/04 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    ******"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981013"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981029"; */	/* ＲＴＣテスト用ＲＯＭ By H.Fujimura 1998/10/29 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981031";	*/	/* 回線テスト用ＲＯＭ By H.Fujimura 1998/10/31 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981110"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "HINOKI    981113"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981118"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981125"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981126"; */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981201";	*/	/* 画質調整用 並河氏からの依頼分 1998/12/1 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981202";	*/	/* Fine 400 1-2相 画質調整用 並河氏からの依頼分 1998/12/2 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981203";	*/	/* プリント調査用 印可パルス／ＲＸモータ SP_INT 同期 1998/12/3 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981205";	*/	/* スキャナ画質調査用 Fine 400 1-2相 1998/12/3 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981208";	*/	/* スキャナ画質調査用 Fine 400 1-2相 1998/12/8 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981209";	*/	/* スキャナ画質調査用 Fine 400 1-2相 1998/12/8 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981211";	*/	/* 機械評価用 1998/12/11 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981212";	*/	/* 機械評価用 1998/12/11 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F-350 JPN 981218";	*/	/* ソフト評価用 1998/12/18 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 981225";	*/	/* ソフト評価用 1998/12/18 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990108";	*/	/* ソフトＤＶＴ用 by O.Kimoto 1999/01/07 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990109"; */	/* ソフトＤＶＴ用 by H.Hirao 1999/01/09 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990114";	*//* ソフトＤＶＴ用 By O.Kimoto 1999/01/15 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990118";	*//* ソフトＤＶＴ用 1999/01/18 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990119";	*//* ソフトＤＶＴ用 小タスクスタック４１６ｂｙｔｅに変更 1999/01/19 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990120";	*//* ＣＳ組み立て用＆ソフトＤＶＴ用 1999/01/20 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990127";	*//* ソフトＤＶＴ用 1999/01/27 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990128";	*//* プレＱＡＴ用 1999/01/28 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990209";	*//* プレＱＡＴ用 By O.Kimoto 1999/02/09 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990212";	*//* プレＱＡＴ不具合修正ＲＯＭ By O.Kimoto 1999/02/12 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990222";	*//* デュアル組み合わせ変更、プレＱＡＴ不具合修正ＲＯＭ By O.Kimoto 1999/02/22 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990223";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/02/23 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990224";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/02/24 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990226";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/02/26 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990301";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/01 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990303";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/03 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990304"; */	  /* ＱＡＴ不具合修正ＲＯＭ	 1999/03/04 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990305"; */	  /* ＱＡＴ不具合修正ＲＯＭ	 1999/03/05 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990309";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/09 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990310";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/10 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990315";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/15 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990316";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/16 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990318";	*/	/* ＱＡＴ不具合修正ＲＯＭ  1999/03/18 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990319"; */	  /* ＱＡＴ不具合修正ＲＯＭ	 1999/03/19 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN A0A0A0"; */	  /* ＱＡＴ合格 量産ＲＯＭ	1999/03/19 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN A1A0A0";	*/	/* ＰＳ２ Ａ／Ｄ変換対応他 By O.Kimoto 1999/03/29 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN A2A0A0";	*/	/* by H.Hirao 1999/03/30 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN C0A0A0";	*/	/* 1999/04/22 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990517";	*/	/* ＪＰＮ クラス１ 1999/05/15 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 990611";	*/	/* プリンタ受信仕様 1999/06/11 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D0A0A0";	*/	/* 量産ＲＯＭ 1999/06/11 by H.Hirao */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D1A0A0";	*/	/* 量産ＲＯＭ RDC-D86-001画質調整対応 1999/07/08 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D2A0A0";*/	  /* 量産ＲＯＭ RDC199900144 B4耳おれ対策 1999/11/24 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 991210"; */	  /* 医師会特ＲＯＭ（余白付き） By O.Kimoto 1999/12/10 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D3A0A1";	*/	/* 三洋ＯＥＭ用（ＳＦＸ７７Ｍ） By O.Kimoto 2000/03/01 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D4A0A0"; */	/* 量産ＲＯＭ 繰り込み不良時、励磁しっぱなし不具合修正  2000/04/12 by T.Soneoka */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D5A0A0"; */	/* 量産ＲＯＭ 原稿つき送信証対応  2000/08/01 by O.Kimoto */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 000904"; */	/* 疑似ベル鳴動中のBT検出特ROM By O.Kimoto 2000/09/04 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 001124";	*/	/* 誤ダイヤル対策 By O.Kimoto 2000/11/24 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 001206";	*/	/* 郵政向け特ＲＯＭ by H.Hirao 2000/12/06 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 010131";	*/	/* ジャーナル３０件 中国郵政局特ROM By O.Kimoto 2001/01/24 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 010302";	*/	/* 折り返し、花キューピット対応特ＲＯＭ by H.Hirao 2001/3/2 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D6A0A0";	*/	/* プリント中ループ対策 By O.Kimoto 1902/04/22 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D7A0A0";	*/	/* 原稿付きチェックメッセージプリント止まらず by O.Kimoto 2002/04/30 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN 020626"; */	/* 毎日Fコードポーリング（特ROM) By O.Kimoto 2002/06/26 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN D8A0A0";	*/	/* 発着衝突不具合対応 By T.Takagi 2002/07/08 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN E0A0A0";	*/	/* 誤ダイヤル他 By O.Kimoto 2002/11/14 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F350  JPN F0A0A0";		/* Version UP By O.Kimoto 2004/06/15 */
	
 #endif
 #if defined(TWN)
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN 990204";	@* 申請用 by H.Hirao 1999/02/04 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN 990311";	@* ＤＶＴ用 by H.Hirao 1999/03/11 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN 990313";	@* by H.Hirao 1999/03/13 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN 990323";	@* ＱＡＴ用 by H.Hirao 1999/03/23 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN 990402";	@* ＱＡＴ用 by H.Hirao 1999/04/02 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN A3A0A0";	@* 量産用 by H.Hirao 1999/04/12 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN C0A0A0";	@* 量産用バージョンアップ by H.Hirao 1999/05/06 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN C0A0B0";	@* ANS/FAX待機 CNG検出対応 by H.Hirao 1999/05/25 */
	/* CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN D0A0A0";	@* 量産ＲＯＭ RDC199900161 Ｂ４耳おれ対策 by H.Hirao 1999/12/11 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86   TWN D4A0A0";	/* 量産ＲＯＭ 繰り込み不良時、励磁しっぱなし不具合修正	2000/04/12 by T.Soneoka */
	

 #endif
#endif

/*------------------------------------------------------------------------
**	Ｌ４００後継
*/
#if defined(POPLAR_F)
 #if defined(JP1)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1234567890ABCDEF"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000109"; */	/* フィールド評価ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000124"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000129"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000130"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000131"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000212"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000301"; */	/* ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000309"; */	/* ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000322"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN 000324"; */	/* ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN A1A0A0"; */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V740  JPN A2A0A0";
 #elif defined(JPN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "1234567890ABCDEF"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991109"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN991109A"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991111"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991112"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991115"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991117"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991125"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991201"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991202"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991204"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991207"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991213"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L4xx  JPN 991214"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400J JPN 991217"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400J JPN 991228"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000106"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000109"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000111"; */	/* NTTファネット評価ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000115"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000120"; */	/* ＱＡＴ用ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000128"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000130"; */	/* ＱＡＴ用ＲＯＭ ２発目 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000131"; */	/* ＱＡＴ用ＲＯＭ ３発目 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000204"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000205"; */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000207"; */	/* ＱＡＴ用ＲＯＭ ４発目 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN 000212"; */	/* ＱＡＴ用ＲＯＭ ５発目 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN B0    "; */	/* 量産ROM 0002012よりﾊﾞｰｼﾞｮﾝのみ量産ﾊﾞｰｼﾞｮﾝへ変更 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN B1    "; */	/* リワーク 量産ROM	 2000/03/01 Y.Murata */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN B1   ."; */	/* ﾄﾞﾗﾑ無、ﾄﾅｰｶｯﾄﾘｯｼﾞ無表示順位変更 2000/03/09 Y.Murata */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN B1  .."; */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "L400A JPN B1.   ";
 #endif
#endif

/*------------------------------------------------------------------------
**	ＨＩＮＯＫＩ２
*/
 /* HINOKI2 2001/11/13 T.Takagi */
#if defined(HINOKI2) && !defined(HINOKI3)
/* NTT、５５転送と条件コンパイルが増えてきました。見間違い防止の為、不要と思われるコメント行を削除します。
** 参照したい場合、C2A0A0以前のバックアップCDROM内のrom_tbl.cを参照してください。2003/02/17 T.Takagi */
 #if defined(JPNNTT)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A0    ";*/	/* 量産用にバージョン名変更 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN T21204";*/	/* トーナルテストリセット対策 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A1    ";*/	/* 省エネ制御 24V ON/OFFによる電源リレー寿命の問題 */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A2    ";*/	/* 「紙なしでかつメモリフル時に"ﾂｳｼﾝ ﾃﾞｷﾏｽ"表示にする」処理を止める */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A3    ";	/* ループ対策（暫定） By O.Kimoto 2002/12/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A3.   ";*/	/* SG3送信で1m原稿長エラー時ループ対策 By O.Kimoto 2003/01/30 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 031201";*/	/* 音声応答中のBusyTone検出スイッチ対応 By O.Kimoto 2003/12/01 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 031208";*/	/* LC821033対応ROM by Y.Kano 2003/12/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 031210";*/	/* LC821033対応ROMでLC82103がハングアップする対策 by Y.Kano 2003/12/10 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 031211";*/	/* scn_tblのSPの値を変更 by Y.Kano 2003/12/11 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040114";*/	/* センサー自動調整対応ROM by Y.Kano 2004/01/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040116";*/	/* */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040120";*/	/* */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040127";*/	/* 黒シェーディングデータの平均値設定処理対応ROM by Y.Kano 2004/01/27 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040129";*/	/* 強調フィルタ設定処理変更ROM by Y.Kano 2004/01/29 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040206";*/	/* プレヒート印加パルス幅モニター処理追加ROM by Y.Kano 2004/02/06 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040209";*/	/* 二値ガンマテーブル変更ROM by Y.Kano 2004/02/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 040316";*/	/* ヒートパルス設定変更ROM by Y.Kano 2004/03/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 041220";	/* ＰＳ２センサ不具合対応用ROM by Y.Kano 2004/12/17 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 050214";*/	/* QATROM T.Nose 2005/02/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 050309";*/	/* 旧ﾀｲﾌﾟでのﾌｯｸLED問題対策ROM by Y.Kano 2005/03/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN 050318";*/	/* リアルタイムコピー実行キー入力音変更ROM by Y.Kano 2005/03/18 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340  JPN A7    ";	/* 量産用 T.Nose 2005/03/30 */
 #elif defined(JP1)	/* リモートダイヤル転送(55転送) */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN D055A0"; */	/* リモートダイヤル転送 2003/02/17 T.Takagi */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN PO5501"; */	/* 郵政用リモートダイヤル転送ROM 2004/02/12 T.Takagi */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040322"; */	/* 画処理パラメータ変更ROM 2004/03/22 by Y.Kano */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040330"; */	/* 画処理テスト用ROM 2004/03/30 by Y.Kano */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040401"; */	/* 中間調ガンマ補正テーブル変更ROM 2004/04/01 by Y.Kano */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040402"; */	/* 二値ガンマ補正テーブル変更ROM 2004/04/02 by Y.Kano */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN OO0427"; */
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 041220"; 	/* ＰＳ２センサ不具合対応用ROM by Y.Kano 2004/12/20 */
 #elif defined(JPN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN A0A0A0"; */	/* HINOKI2 量産ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN A1A0A0"; */	/* 朱色読み取り対応、プリント中ループ対策 by O.Kimoto 2002/04/18 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN A2A0A0"; */	/* 原稿付きチェックメッセージプリント止まらず */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 020527"; */	/* 郵政特ROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN A3A0A0"; */	/* 発着衝突不具合対応 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 020805"; */	/* 医師会特ＲＯＭ */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN A4A0A0"; */	/* F351 VerUp & SANYO OEM (SFX-78M) */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN B0A0A0"; */	/* 省エネ制御修正、他 2002/12/03 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN C0A0A0"; */ /* プリント中ループ、送受信不可対策ROM 2002/12/16 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 021217"; */	/* 郵政用 プリント中ループ、送受信不可対策ROM 2002/12/16 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN C1A0A0"; */	/* SFX78M 日付初期値を2003年に変更 2003/01/14 T.Takagi */
/*  CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN C2A0A0"; */	/* 長尺原稿スキャナ送信でループする対策 2003/01/30 T.Takagi */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 030131"; */	/* 長尺原稿スキャナ送信でループする対策郵政特ROM 2003/01/31 T.Takagi */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 030203"; */	/* スギ薬局特ROM */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 030331"; */	/* */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040114"; */	/* センサー自動調整対応ROM by Y.Kano 2004/01/14 */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040115"; */	/* */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040120"; */	/* */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040121"; */	/* センサー自動調整機能変更ROM by Y.Kano 2004/01/21 */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040204"; */	/* PS1センサーをRXﾓｰﾀ駆動中のみ監視する by Y.Kano 2004/02/04 */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 040302"; */	/* センサー自動調整機能変更ROM by Y.Kano 2004/03/02 */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 041221"; */	/* ＰＳ２センサ不具合対応用ROM by Y.Kano 2004/12/18 */
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F351  JPN 050224"; 	/* カッターテストROM O.Oshima  */
 #endif
 #if defined(TWN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN A0A0A0"; */	/* F76 量産ROM */
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN B0A0A0"; */	/* 省エネ制御修正、他 2002/12/04 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN C0A0A0"; */	/* プリント中ループ、送受信不可対策ROM 2002/12/16 T.Takagi */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN D2A0A0"; */	/* F76 ANS待機必ず着信対策 O.Oshima 2004/05/31 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN D3A0A0";	/* 上記二次不具合修正 O.Oshima 2004/07/12 */
 #endif
#endif
/*------------------------------------------------------------------------
**	ＳＡＴＳＵＫＩ２
*/
#if defined(SATSUKI2)
 #if defined(JPN)
 
/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 03112A"; CI割込み救済テストROM */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 031126";*/ /* QAT 3rd O.Oshima 2003/11/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN A0A0A0";*/ /* 量産ROM Y.Kano 2003/11/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 031212";*/ /* PS1,PB4センサーテスト用ROM Y.Kano 2003/12/12 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN A1A0A0";*/ /* 量産ROM O.Oshima 2003/12/15 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 031218";*/ /* PS1,PB4センサーチェック追加用ROM Y.Kano 2003/12/18 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 031227";*/ /* PS1,PB4センサー閾値設定ソフト追加用ROM Y.Kano 2003/12/27 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 040107";*/ /* PS1,PB4機器パラの初期化テーブル変更用ROM Y.Kano 2004/01/07 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 040109";*/ /* 先端読取り位置微調整を有効にする様に変更したROM Y.Kano 2004/01/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN 050222";*/ /* 防災FAX対応ROM Y.Kano 2005/02/22 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F250  JPN A6A0A0"; /* 防災FAX対応出荷用ROM Y.Kano 2005/03/07 */
 #endif
#endif

/*------------------------------------------------------------------------
** ＬＶＮＤＲ２
*/
#if defined(STOCKHM2)
 #if defined(JPN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040610";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040702";*/ /* テスト用ROM by Y.kano 2004/07/02 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040712";*/ /* ﾗﾍﾞﾝﾀﾞｰの印字ﾃｰﾌﾞﾙ参照機能追加ROM by Y.kano 2004/07/12 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040722";*/ /* ﾒﾓﾘｺﾋﾟｰの不具合対策ROM by Y.kano 2004/07/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040812";*/ /* ﾜｰﾃﾞｨﾝｸﾞ変更 and 黒ｼｪｰﾃﾞｨﾝｸﾞ固定変更ROM by Y.kano 2004/08/12 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040817";*/ /* 白ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀ上下反転ﾃｽﾄ用ROM by Y.kano 2004/08/17 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040820";*/ /* MON_ERR->MON_ERR2用ROM by Y.kano 2004/08/20 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040824";*/ /* 上海ソフトマージ用ROM by Y.kano 2004/08/24 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040826";*/ /* 中村氏変更依頼用ROM by Y.kano 2004/08/26 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040830";*/ /* 上海ソフトマージ用ROM by Y.kano 2004/08/30 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040903";*/ /* 中村氏よりｶﾞﾝﾏ補正ﾃｰﾌﾞﾙ（中間調、濃い）ﾃﾞｰﾀ変更、通信結果確認変更用ROM by Y.kano 2004/09/03 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040906";*/ /* 中村氏よりｶﾞﾝﾏ補正ﾃｰﾌﾞﾙ（中間調、濃い）ﾃﾞｰﾀ変更用ROM by Y.kano 2004/09/06 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040908";*/ /* 中村氏よりｶﾞﾝﾏ補正ﾃｰﾌﾞﾙ（中間調、普通）ﾃﾞｰﾀ変更用ROM by Y.kano 2004/09/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040910";*/ /* 上海ソフトマージ用ROM by Y.kano 2004/09/10 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040914";*/ /* 通信結果表示ﾌｫｰﾏｯﾄ変更用ROM by Y.kano 2004/09/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040916";*/ /* ﾘｽﾄ関連処理変更用ROM by Y.kano 2004/09/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040921";*/ /* ｼﾞｬｰﾅﾙ結果修正＆治具ｴﾗｰ対応用ROM by Y.kano 2004/09/21 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040929";*/ /* 呼出ベル対応テスト対応用ROM by Y.kano 2004/09/29 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 040930";*/ /* 上海ｿﾌﾄﾏｰｼﾞ（呼出ベル対応）用ROM by Y.kano 2004/09/30 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 041012";*/ /* 上海ｿﾌﾄﾏｰｼﾞ用ROM by Y.kano 2004/10/12 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 041013";*/ /* 中間調ガンマ補正テーブル変更用ROM by Y.kano 2004/10/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 041014";*/ /* ｽｷｬﾅｺﾋﾟｰ・写真ﾓｰﾄﾞでの印字問題対策用ROM by Y.kano 2004/10/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 041016";*/ /* 上海テストｽｷｬﾅｺﾋﾟｰ・写真ﾓｰﾄﾞでの印字問題対策用ROM by Y.kano 2004/10/16 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 041018";*/ /* 上海マージ用ROM by Y.kano 2004/10/18 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "V195  JPN 050303"; /*  インクリボン無しエラー対策ROM Y.Kano 2005/03/03 */
 #endif
#endif

/*------------------------------------------------------------------------
**	ＨＩＮＯＫＩ３
*/
 /* HINOKI2 2004/11/25 Y.Tanaka */
#if defined(HINOKI3)
 #if defined(JPNNTT)
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "T340A JPN 050113";
 #elif defined(JP1)	/* リモートダイヤル転送(55転送) */
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JP1 041021";
 #elif defined(JP2)
 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JP2 041118";
 #elif defined(KEISATSU) /* 警察FAX */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 050425";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 050926";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051017";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051020";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051026";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051027";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051028";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051104";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051107";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051110";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051114";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051115";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051116";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051117";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051118";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051121";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051122";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051125";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051201";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051207";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051212";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051214";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051217";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN 051222";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A0A0A0";*/	/* 量産ROM 05/12/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A1A0A0";*/	/* 不具合修正 06/01/10 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A2A0A0";*/	/* 不具合修正 06/01/10 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A3A0A0";*/	/* 不具合修正 06/01/13 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A4A0A0";*/	/* 不具合修正 06/01/13 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355P JPN A5A0A0";	/* 仕様追加 06/03/23 */

 #elif defined(JPN)
/* 	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041021";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041125";*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041201";*//*DVT ROM*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041209";*//*DVT ROM*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041214";*//*DVT ROM*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041216";*//*DVT ROM*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041217";*//*DVT ROM*/
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041222";*//* 自動チェッカー処理追加対応ROM by Y.Kano 2004/12/22 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041224";*//* 一時的に画処理の読み取り位置を変更 Y.Tanaka 2004/12/24 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041225";*//* 紙センサＰＳ１、ＰＢ４をポート読みに変更 Y.Kano 2004/12/25 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041227";*//* パネルチェッカー追加ROM Y.Kano 2004/12/27 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 041228";*//* CS用ROM Y.Kano 2004/12/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050107";*//* ペーパーセンサ不具合対策用ROM Y.Kano 2005/01/07 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050111";*//* 車検証モード機能追加用ROM Y.Kano 2005/01/11 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050111";*//* ＱＡＴ用ＲＯＭ T.Nose 2005/01/14 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050124";*//* 朱色シェーディングデータ取込み処理修正用ＲＯＭ Y.Kano 2005/01/24 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050128";*//* ＱＡＴ用ＲＯＭ Y.Kano 2005/01/28 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050204";*//* ＱＡＴ用ＲＯＭ T.Nose 2005/02/04 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050208";*//* 中間調ガンマテーブル変更ＲＯＭ Y.Kano 2005/02/08 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN A0A0A0";*//* 量産用 T.Nose 2005/02/09 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN 050217";*//* チェックサム表示機能追加用ROM Y.Kano 2005/02/17 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F355  JPN A1A0A0";/* 量産用ROM T.Nose 2005/04/01 */
 #endif
 #if defined(TWN)
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN D3A0A0";*/	/* 上記二次不具合修正 O.Oshima 2004/07/12 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "D86-2 TWN 050207";	/*  Y.Kano 2005/02/07 */
/*	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F86   TWN 050210";*/	/*  T.Nose 2005/02/10 */
	CONST UBYTE ROM_Revision[ROM_REVISION_MAX] = "F86   TWN 050331";	/*  Y.Kano 2005/03/31 */
 #endif
#endif


#pragma section

#if (PRO_EXT_ROM == ENABLE)
/* 拡張ＲＯＭリビジョン定義 by K.Watanabe 1998/02/27 */
#pragma section EXT_ROM		/* セクション指定 */
/* 拡張ＲＯＭの内容をビットアサインで確認するために追加 By Y.Suzuki 1998/03/02 */
CONST UWORD ExtRomType = MOD_SCRAMBLE;

/*CONST UBYTE EXT_ROM_Revision[ROM_REVISION_MAX] = "ALIROO    971209";	@* By Y.Suzuki 1997/12/09 */
/*CONST UBYTE EXT_ROM_Revision[ROM_REVISION_MAX] = "DS-100    980225";	@* By Y.Suzuki 1998/02/25 */

/***************** 拡張ＲＯＭのバージョン名について ******** S.Fukui  **********/
/***** DS100 A0A2A0以降 Version(XXYYZZ)の付け方を統一します。				****/
/*****	  前２つ XX	 : スクランブルのバージョン示す(２文字）				****/
/*****	  中２つ YY	 : CLASS1のバージョン前２つを示す						****/
/*****	  後２つ ZZ	 : 予約													****/
/***** (例）DS100  A1B3A0 : ｽｸﾗﾝﾌﾞﾙﾊﾞｰｼﾞｮﾝ A1xxxx, CLASS1ﾊﾞｰｼﾞｮﾝ B3A0A0		****/
/*[注意]DS100のバージョンは本来スクランブル自体のバージョンを指していましたが、*/
/*		今後、スクランブルと同梱されたソフトのバージョンを合わせた内容を意味   */
/*		することとします。													   */
/*******************************************************************************/
CONST UBYTE EXT_ROM_Revision[SYS_EXT_ROM_MAX][ROM_REVISION_MAX] = {
/*	"DS-100    980225",		 * スクランブル用ＲＯＭ	*/
/*	"DS-100    980305",		* スクランブル用ＲＯＭデモ版	*/
/*	"DS-100    980312",		* VER980311	*/
/*	"DS-100    980413",		* QAT用 */
/*	"DS-100    A0A0A0",		* 量産用 By Y.Suzuki 1998/08/18 */
	"DS-100    A0A2A0",		/* CLASS1 A2A0A0対応 By S.Fukui Oct.13,1998 */
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
/*	"CLASS1    980619",		*//* 評価用		*/
/*	"CLASS1    980703",		*//* 評価用		*/
/*	"CLASS1    980707",		*//* ＱＡＴ用	*/
/*	"CLASS1    A0A0A0",		*//* 量産用		*/
/*	"CLASS1    A1A0A0",		*//*  RS232C基盤 Rev.B からRev.Cの変更(TXD,RXD,RTS等の信号線のコンデンサ削除)に
							   ** よりPC側のケーブル抜け時にFAX着信があるとCTSの割込みが頻発し、ループする対策
							   ** Aug.18,1998 S.Fukui	*/
	"CLASS1    A2A0A0",		/*	TA経由時のリモート同報送信不具合対策 By S.Fukui Oct.13,1998 */
#else
	"                ",		/* 予約１				*/
#endif
	"                ",		/* 予約２				*/
	"                ",		/* 予約３				*/
	"                "		/* 予約４				*/
};
/*この後に拡張ROMモジュール参照用テーブルをロケートするので上記の配列のサイズは、変更時連絡ください。*/
#pragma section
#endif
