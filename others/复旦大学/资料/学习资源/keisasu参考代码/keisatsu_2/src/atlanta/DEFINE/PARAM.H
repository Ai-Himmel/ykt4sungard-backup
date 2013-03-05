/* by NOBUKO  Sep.22,95 */
#ifndef param_h
    #define param_h

/************************************************************************
 * unsigned char SYB_MachineParameter[0]								*
 * 国別コード 															*
 * 0～7までのスカラー値													*
 * 1994/02/05															*
 * 吉川弘康																*
 ************************************************************************/
/* Ａ 0 */
#define COUNTRY_CODE			0	/* SYB_MachineParameter[COUNTRY_CODE] */

#define COUNTRY_CODE_JPN		0x00	/* ＵＳＡ追加 by T.Soneoka 1997/03/26 */
#define COUNTRY_CODE_USA		0x01	/* ＵＳＡ追加 by T.Soneoka 1997/03/26 */
#define COUNTRY_CODE_FIN		0x06	/* フィンランド by K.Watanabe 1998/10/22 */
#define COUNTRY_CODE_DNK		0x07	/* デンマーク by K.Watanabe 1998/10/22 */

/************************************************************************
 * unsigned char SYB_MachineParameter[1]								*
 * 送出レベル画データ(減衰器設定値)										*
 * 1-0    1.0dB															*
 * 1-1    2.0dB															*
 * 1-2    4.0dB															*
 * 1-3    8.0dB															*
 * 受信側無装荷ケーブル補正												*
 *       0dB 4dB 8dB 12dB												*
 * 1-4    0   1   0    1												*
 * 1-5    0   0   1    1												*
 * 送信側無装荷ケーブル補正												*
 *       0dB 4dB 8dB 12dB												*
 * 1-6    0   1   0    1												*
 * 1-7    0   0   1    1												*
 * 1994/02/05															*
 * 吉川弘康																*
 ************************************************************************/
/* Ａ 1 */
#define MACHINE_PARA_1			1	/* SYB_MachineParameter[MACHINE_PARA_1] */

#define ATTENATION_MACHINE_PARA	0x0F

#define TONE_ATTENATION_1		0x01
#define TONE_ATTENATION_2		0x02
#define TONE_ATTENATION_3		0x04
#define TONE_ATTENATION_4		0x08
#define RX_CABLE_EQUALIZER_1	0x10
#define RX_CABLE_EQUALIZER_2	0x20
#define TX_CABLE_EQUALIZER_1	0x40
#define TX_CABLE_EQUALIZER_2	0x80

/************************************************************************
 * unsigned char SYS_MachineParamter[2]									*
 * 送出レベル画データ(減衰器設定値)										*
 * 2:送出レベルDTMF(減衰器設定値)										*
 * 2-0    1.0dB															*
 * 2-1    2.0dB															*
 * 2-2    4.0dB															*
 * 2-3    8.0dB															*
 * 保留メロディレベル(減衰器設定値)										*
 * 2-4    1.0dB															*
 * 2-5    2.0dB															*
 * 2-6    4.0dB															*
 * 2-7    8.0dB															*
 * 1994/02/05															*
 * 吉川弘康																*
 ************************************************************************/
/* Ａ 2 */
#define MACHINE_PARA_2			2	/* SYB_MachineParameter[MACHINE_PARA_2] */

#define DTMF_ATTENATION_1		0x01
#define DTMF_ATTENATION_2		0x02
#define DTMF_ATTENATION_3		0x04
#define DTMF_ATTENATION_4		0x08
#define MELODY_ATTENATION_1		0x10
#define MELODY_ATTENATION_2		0x20
#define MELODY_ATTENATION_4		0x40
#define MELODY_ATTENATION_8		0x80

/************************************************************************
 * unsigned char SYS_MachineParamter[3]									*
 * 待機位置から読みとり位置までのステップ値(FINE)						*
 * 1994/02/05															*
 * 吉川弘康																*
 *----------------------------------------------------------------------*
 * 川崎　真史 Jun.29,1994                                               *
 * 桐ＤＳ２　ＯＮから読み取り位置までのステップ数                       *
 * 設定値×１０が実際のステップ数として設定される。                     *
 * １ステップ＝０．０６３５ｍｍ                                         *
 * 設定値１～２５５で０．６３５ｍｍから１６１．９２５ｍｍまで可変       *
 ************************************************************************/
/* Ａ 3 */
#define MACHINE_PARA_3			3	/* SYB_MachineParameter[MACHINE_PARA_3] */
#define READY_TO_SCAN_STEP	/* SYB_MachineParameter[MACHINE_PARA_3] */

/************************************************************************
 * unsigned char SYS_MachineParamter[4]									*
 * DS2 OFFから読みとり位置までのステップ値(NORMAL)						*
 * 1994/02/05															*
 * 吉川弘康																*
 *----------------------------------------------------------------------*
 * 川崎　真史 Jun.29,1994                                               *
 * 桐ＤＳ２　ＯＦＦから読み取り位置までのステップ数                     *
 * 設定値×１０が実際のステップ数として設定される。                     *
 * １ステップ＝０．０６３５ｍｍ                                         *
 * 設定値１～２５５で０．６３５ｍｍから１６１．９２５ｍｍまで可変       *
 ************************************************************************/
/* Ａ 4 */
#define MACHINE_PARA_4			4	/* SYB_MachineParameter[MACHINE_PARA_4] */
#define DS2_TO_SCAN_STEP	/* SYB_MachineParameter[DS2_TO_SCAN_STEP] */

/* Ａ 5 */
#define MACHINE_PARA_5			5	/* Black Level of CCD */

/* Ａ 6 */
#define MACHINE_PARA_6			6

/* Ａ 7 */
#define MACHINE_PARA_7			7	/* DRAMサイズ */
/* 1bit == 1M <- 512K By M.Tachibana 1997/06/05 */

/* Ａ 8 */
#define MACHINE_PARA_8			8	/* DRAMサイズ */
/* 1bit == 1M <- 512K By M.Tachibana 1997/06/05 */

/* Ａ 9 */
#define MACHINE_PARA_9			9	/* 蓄積符号 */
#endif
