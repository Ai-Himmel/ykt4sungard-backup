#ifndef mdm_conf_h
	#define mdm_conf_h
/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                   */
/*  ファイル名   : mdm_conf.h                                                 */
/*  作成者       :                                                            */
/*  日  付       : 1999/10/06                                                 */
/*  概  要       : Ｒｏｃｋｗｅｌｌ Ｒ２８８Ｆモデム CONF 設定値              */
/*  修正履歴     :                                                            */
/*	keyword			:[MDM]                                                    */
/*	machine			:[SH7043]                                                 */
/*	language		:[MS-C(Ver.6.0)]                                          */
/*----------------------------------------------------------------------------*/

/************************************************************************
*  PLACE TO CHANGE when mdm_conf.h was introduced.
* 
* Global value to specify transmission rate and mode no longer hold  
* a CONF value of R288F modem chip. Translation between them occurs
* in the functions listed below:
*
* 	void					MDM_SetIO(unsigned char ,unsigned char );
*	unsigned char			MDM_GetIO(unsigned char );
*	void					MDM_SetModulationModeV34FDX(unsigned char );
*	void					MDM_SetModulationModeV34HDX(unsigned char );
*	void					MDM_SetModulationModeV32BIS(unsigned char );
*	void					MDM_SetModulationModeV22BIS(unsigned char );
*	void					MDM_SetModulationModeV17(unsigned char );
*	void					MDM_SetModulationModeV29(unsigned char );
*	void					MDM_SetModulationModeV27(unsigned char );
*	void					MDM_SetModulationModeV26TER(unsigned char );
*	void					MDM_SetModulationModeV26BIS(unsigned char );
*	void					MDM_SetModulationModeV23FDX(unsigned char );
*	void					MDM_SetModulationModeV23HDX(unsigned char );
*	void					MDM_SetModulationModeV21(unsigned char );
*	void					MDM_SetModulationModeVFC(unsigned char );
*
*************************************************************************/


/***********************************************************************
*          BY:   久保博
*        DATE:   Wed 18 Jun. 1997
* VAR TO HOLD:   
* DESCRIPTION:   Rockwell R288F のインターフェイスメモリビットに設定する通信ボーレートの値。
*				R288F Fax Modem Designer's guide 表 3.1 CONF (12:0-7) に設定する値。
*				表 7.3 の変調モードの設定値としても使用。
*				mdm_io.c, mdm_dsp.c 参照。
************************************************************************/
/** V.8 **/
#define		MDM_R288F_CONF_V8				0xAA
#define		MDM_R288F_CONF_V8_CLEARDOWN		0xAF
/** V.34 **/
#define		MDM_R288F_CONF_BPS33600_V34		0xCE
#define		MDM_R288F_CONF_BPS31200_V34		0xCD
#define		MDM_R288F_CONF_BPS28800_V34		0xCC
#define		MDM_R288F_CONF_BPS26400_V34		0xCB
#define		MDM_R288F_CONF_BPS24000_V34		0xCA
#define		MDM_R288F_CONF_BPS21600_V34		0xC9
#define		MDM_R288F_CONF_BPS19200_V34		0xC8
#define		MDM_R288F_CONF_BPS16800_V34		0xC7
#define		MDM_R288F_CONF_BPS14400_V34		0xC6
#define		MDM_R288F_CONF_BPS12000_V34		0xC5
#define		MDM_R288F_CONF_BPS9600_V34		0xC4
#define		MDM_R288F_CONF_BPS7200_V34		0xC3
#define		MDM_R288F_CONF_BPS4800_V34		0xC2
#define		MDM_R288F_CONF_BPS2400_V34		0xC1
#define		MDM_R288F_CONF_CLEARDOWN_V34	0xC0
/** V.33 **/
#define		MDM_R288F_CONF_BPS14400_V33		0x31
#define		MDM_R288F_CONF_BPS12000_V33		0x32
#define		MDM_R288F_CONF_BPS9600_V33		0x34
#define		MDM_R288F_CONF_BPS7200_V33		0x38
/** V.17 **/
#define		MDM_R288F_CONF_BPS14400_V17		0xB1
#define		MDM_R288F_CONF_BPS12000_V17		0xB2
#define		MDM_R288F_CONF_BPS9600_V17		0xB4
#define		MDM_R288F_CONF_BPS7200_V17		0xB8
/** V.29 **/
#define		MDM_R288F_CONF_BPS9600_V29		0x14
#define		MDM_R288F_CONF_BPS7200_V29		0x12
#define		MDM_R288F_CONF_BPS4800_V29		0x11
/** V.27 ter **/
#define		MDM_R288F_CONF_BPS4800_V27		0x02
#define		MDM_R288F_CONF_BPS2400_V27		0x01
/** V.21 **/
#define		MDM_R288F_CONF_BPS0_300_V21		0xA0
#define		MDM_R288F_CONF_BPS300_V21		0xA8	/** Channel 2 **/
/** Etc. **/
#define		MDM_R288F_CONF_TX_SINGLE_TONE	0x80
#define		MDM_R288F_CONF_TX_DUAL_TONE		0x83
#define		MDM_R288F_CONF_DIALING			0x81
#define		MDM_R288F_CONF_DTMF_RECEIVER	0x86

/* Caller ID By O.Kimoto 1997/06/10 */
/** V.23 **/
#define		MDM_R288F_CONF_TX1200_V23		0xA4	/* Tx:1200 Rx:75   */
#define		MDM_R288F_CONF_RX1200_V23		0xA1	/* Tx:75   Rx:1200 */


#endif /* ! mdm_conf_h */
