/*	By Y.Suzuki 1996/10/12	*/
/*----------------------------------------------------------------------*/
/*プロジェクト : POPLAR/ANZU_L                                          */
/*ファイル名   : VECTOR.C                                               */
/*モジュ-ル名  :                                                        */
/*作成者名     : S.Kawasaki                                             */
/*日  付       : 95.11.1                                                */
/*概  要       : 例外処理ベクターテーブル                               */
/*ＣＰＵ       : ＳＨ７０３４／ＳＨ７０４Ｘ                             */
/*修正履歴     : 各モデル毎にテーブルを別にした T.Nose 1996/11/08       */
/*----------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\def_v\vector.c"
#else

#include "\src\atlanta\sh7043\define\def_mon.h"

/* 外部割込み */
extern void INI_Entry(void);			/* スタートエントリー */
extern void INT_IRQ0(void);				/* ＩＲＱ０エントリー */
extern void INT_IRQ1(void);				/* ＩＲＱ１エントリー */
extern void INT_IRQ2(void);				/* ＩＲＱ２エントリー */
extern void INT_IRQ3(void);				/* ＩＲＱ３エントリー */
extern void INT_IRQ4(void);				/* ＩＲＱ４エントリー */
extern void INT_IRQ5(void);				/* ＩＲＱ５エントリー */
extern void INT_IRQ6(void);				/* ＩＲＱ６エントリー */
extern void INT_IRQ7(void);				/* ＩＲＱ７エントリー */

/* 内蔵周辺割込み */
extern void INT_DMAC0_CH0(void);		/* 内蔵ＤＭＡＣチャネル０エントリー */
extern void INT_DMAC0_CH1(void);		/* 内蔵ＤＭＡＣチャネル１エントリー */
extern void INT_DMAC0_CH2(void);		/* 内蔵ＤＭＡＣチャネル２エントリー */
extern void INT_DMAC0_CH3(void);		/* 内蔵ＤＭＡＣチャネル３エントリー */
extern void INT_MTU0(void);				/* 内蔵タイマーチャネル０エントリー */
extern void INT_MTU1(void);				/* 内蔵タイマーチャネル１エントリー */
extern void INT_DTC(void);				/* 内蔵ＤＴＣエントリー             */

extern void INT_NMI(void);				/* ＮＭＩ割込                   */
extern void INT_UNKNOWN_BREAK(void);	/* 一般不当命令                 */
extern void INT_SLOT_BREAK(void);		/* スロット不当命令             */
extern void INT_CPU_ADR_BREAK(void);	/* ＣＰＵアドレスエラー         */
extern void INT_DMA_ADR_BREAK(void);	/* ＤＭＡ／ＤＴＣアドレスエラー */
extern void INT_UNDEFINE(void);			/* 未定義割込み */

/************************************************************************
 * ＰＯＰＬＡＲ／ＡＮＺＵ＿Ｌ共通ベクタテーブル							*
 * 各機種は共通でこのベクタテーブルと割込みエントリーを使用し、         *
 * エントリーから割り込み処理本体の呼び出しを外付けＲＯＭ上に           *
 * 機種別に持つ。                                                       *
 ************************************************************************/
const void(* const INT_VectorTable[])(void) = {
	INI_Entry,			/* 00	パワーオンリセット ＰＣ				*/
	0,					/* 01	パワーオンリセット ＳＰ				*/
	INI_Entry,			/* 02	マニュアルリセット ＰＣ 			*/
	0,					/* 03	マニュアルリセット ＳＰ				*/
	INT_UNKNOWN_BREAK,	/* 04	一般不当命令						*/
	0,					/* 05	（システム予約）					*/
	INT_SLOT_BREAK,		/* 06	スロット不当命令					*/
	0,					/* 07	ブレーク命令（システム予約）		*/
	0,					/* 08	ハードブレーク（システム予約）  	*/
	INT_CPU_ADR_BREAK,	/* 09	ＣＰＵアドレスエラー				*/
	INT_DMA_ADR_BREAK,	/* 10	ＤＭＡＣ／ＤＴＣアドレスエラー		*/
	INT_NMI,			/* 11	ＮＭＩ割込み    					*/
	INT_UNDEFINE,		/* 12	ユーザーブレーク割込み   			*/
	0,					/* 13	（システム予約）					*/
	0,					/* 14	（システム予約）					*/
	0,					/* 15	（システム予約）					*/
	0,					/* 16	（システム予約）    				*/
	0,					/* 17	（システム予約）					*/
	0,					/* 18	（システム予約）					*/
	0,					/* 19	（システム予約）					*/
	0,					/* 20	（システム予約）					*/
	0,					/* 21	（システム予約）					*/
	0,					/* 22	（システム予約）					*/
	0,					/* 23	（システム予約）					*/
	0,					/* 24   （システム予約）				  	*/
	0,					/* 25	（システム予約）					*/
	0,					/* 26	（システム予約）					*/
	0,					/* 27	（システム予約）					*/
 	0,					/* 28	（システム予約）					*/
	0,					/* 29	（システム予約）					*/
	0,					/* 30	（システム予約）					*/
	0,					/* 31	（システム予約）					*/
	INT_UNDEFINE,		/* 32	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 33	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 34	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 35	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 36	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 37	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 38	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 39	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 40   トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 41	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 42	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 43	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 44	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 45	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 46	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 47	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 48	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 49	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 50	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 51	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 52	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 53	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 54	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 55	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 56	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 57	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 58	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 59	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 60	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 61	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 62	トラップ命令（ユーザーベクター）	*/
	INT_UNDEFINE,		/* 63	トラップ命令（ユーザーベクター）	*/
	INT_IRQ0,			/* 64	割込み ＩＲＱ０						*/
	INT_IRQ1,			/* 65	割込み ＩＲＱ１						*/
	INT_IRQ2,			/* 66	割込み ＩＲＱ２						*/
	INT_IRQ3,			/* 67	割込み ＩＲＱ３						*/
	INT_IRQ4,			/* 68	割込み ＩＲＱ４						*/
	INT_IRQ5,			/* 69	割込み ＩＲＱ５						*/
	INT_IRQ6,			/* 70	割込み ＩＲＱ６						*/
	INT_IRQ7,			/* 71	割込み ＩＲＱ７						*/
	INT_DMAC0_CH0,		/* 72	内蔵周辺モジュール DMAC0:DEI0		*/
	INT_UNDEFINE,		/* 73	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 74	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 75	内蔵周辺モジュール					*/
	INT_DMAC0_CH1,		/* 76	内蔵周辺モジュール DMAC1:DEI1		*/
	INT_UNDEFINE,		/* 77	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 78	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 79	内蔵周辺モジュール					*/
	INT_DMAC0_CH2,  	/* 80	内蔵周辺モジュール DMAC2:DEI2		*/
	INT_UNDEFINE,		/* 81	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 82	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 83	内蔵周辺モジュール					*/
	INT_DMAC0_CH3,		/* 84	内蔵周辺モジュール DMAC3:DEI3		*/
	INT_UNDEFINE,		/* 85	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 86	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 87	内蔵周辺モジュール					*/
	INT_MTU0,			/* 88	内蔵周辺モジュール MTU0:TGI0A		*/
	INT_UNDEFINE,		/* 89	内蔵周辺モジュール MTU0:TGI0B		*/
	INT_UNDEFINE,		/* 90	内蔵周辺モジュール MTU0:TGI0C		*/
	INT_UNDEFINE,		/* 91	内蔵周辺モジュール MTU0:TGI0D		*/
	INT_UNDEFINE,		/* 92	内蔵周辺モジュール MTU0:TCI0V		*/
	INT_UNDEFINE,		/* 93	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 94	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 95	内蔵周辺モジュール					*/
	INT_MTU1,			/* 96	内蔵周辺モジュール MTU1:TGI1A		*/
	INT_UNDEFINE,		/* 97	内蔵周辺モジュール MTU1:TGI1B		*/
	INT_UNDEFINE,		/* 98	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 99	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 100	内蔵周辺モジュール MTU1:TCI1V		*/
	INT_UNDEFINE,		/* 101	内蔵周辺モジュール MTU1:TCI1U		*/
	INT_UNDEFINE,		/* 102	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 103	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 104	内蔵周辺モジュール MTU2:TGI2A		*/
	INT_UNDEFINE,		/* 105	内蔵周辺モジュール MTU2:TGI2B		*/
	INT_UNDEFINE,		/* 106	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 107	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 108	内蔵周辺モジュール MTU2:TCI2V		*/
	INT_UNDEFINE,		/* 109	内蔵周辺モジュール MTU2:TCI2U		*/
	INT_UNDEFINE,		/* 110	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 111	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 112	内蔵周辺モジュール MTU3:TGI3A		*/
	INT_UNDEFINE,		/* 113	内蔵周辺モジュール MTU3:TGI3B		*/
	INT_UNDEFINE,		/* 114	内蔵周辺モジュール MTU3:TGI3C		*/
	INT_UNDEFINE,		/* 115	内蔵周辺モジュール MTU3:TGI3D		*/
	INT_UNDEFINE,		/* 116	内蔵周辺モジュール MTU3:TCI3V		*/
	INT_UNDEFINE,		/* 117	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 118	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 119	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 120	内蔵周辺モジュール MTU4:TGI4A		*/
	INT_UNDEFINE,		/* 121	内蔵周辺モジュール MTU4:TGI4B		*/
	INT_UNDEFINE,		/* 122	内蔵周辺モジュール MTU4:TGI4C		*/
	INT_UNDEFINE,		/* 123	内蔵周辺モジュール MTU4:TGI4D		*/
	INT_UNDEFINE,		/* 124	内蔵周辺モジュール MTU4:TCI4V		*/
	INT_UNDEFINE,		/* 125	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 126	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 127	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 128	内蔵周辺モジュール SCI0:ERI0		*/
	INT_UNDEFINE,		/* 129	内蔵周辺モジュール SCI0:RXI0		*/
	INT_UNDEFINE,		/* 130	内蔵周辺モジュール SCI0:TXI0		*/
	INT_UNDEFINE,		/* 131	内蔵周辺モジュール SCI0:TEI0		*/
	INT_UNDEFINE,		/* 132	内蔵周辺モジュール SCI1:ERI1		*/
	INT_UNDEFINE,		/* 133	内蔵周辺モジュール SCI1:RXI1		*/
	INT_UNDEFINE,		/* 134	内蔵周辺モジュール SCI1:TXI1		*/
	INT_UNDEFINE,		/* 135	内蔵周辺モジュール SCI1:TEI1		*/
	INT_UNDEFINE,		/* 136	内蔵周辺モジュール A/D:ADI			*/
	INT_UNDEFINE,		/* 137	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 138	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 139	内蔵周辺モジュール					*/
	INT_DTC,			/* 140	内蔵周辺モジュール DTC:SWDTCE		*/
	INT_UNDEFINE,		/* 141	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 142	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 143	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 144	内蔵周辺モジュール CMT0:CMI0		*/
	INT_UNDEFINE,		/* 145	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 146	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 147	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 148	内蔵周辺モジュール CMT1:CMI1		*/
	INT_UNDEFINE,		/* 149	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 150	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 151	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 152	内蔵周辺モジュール WDT:ITI			*/
	INT_UNDEFINE,		/* 153	内蔵周辺モジュール BSC:CMI			*/
	INT_UNDEFINE,		/* 154	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 155	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 156	内蔵周辺モジュール I/O:OEI			*/
	INT_UNDEFINE,		/* 157	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 158	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 159	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 160	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 161	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 162	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 163	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 164	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 165	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 166	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 167	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 168	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 169	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 170	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 171	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 172	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 173	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 174	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 175	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 176	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 177	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 178	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 179	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 180	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 181	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 182	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 183	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 184	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 185	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 186	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 187	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 188	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 189	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 190	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 191	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 192	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 193	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 194	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 195	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 196	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 197	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 198	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 199	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 200	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 201	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 202	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 203	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 204	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 205	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 206	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 207	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 208	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 209	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 210	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 211	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 212	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 213	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 214	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 215	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 216	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 217	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 218	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 219	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 220	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 221	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 222	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 223	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 224	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 225	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 226	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 227	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 228	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 229	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 230	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 231	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 232	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 233	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 234	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 235	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 236	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 237	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 238	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 239	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 240	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 241	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 242	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 243	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 244	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 245	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 246	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 247	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 248	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 249	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 250	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 251	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 252	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 253	内蔵周辺モジュール					*/
	INT_UNDEFINE,		/* 254	内蔵周辺モジュール					*/
	INT_UNDEFINE		/* 255	内蔵周辺モジュール					*/
};

#endif
