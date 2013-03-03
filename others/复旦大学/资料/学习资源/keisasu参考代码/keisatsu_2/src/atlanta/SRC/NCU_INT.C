/********************************************
 * NCU_INT.C
 * ＣＩ割り込み処理
 * 1996/12/03 Eguchi
 *******************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\unisw_a.h"

#include	"\src\memsw\define\mems_pro.h"
#include	"\src\memsw\define\mem_sw_a.h"

#include	"\src\atlanta\ext_v\bkupram.h"

#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\define\sh_sys.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"

#if (PRO_CIPHER == ENABLE)	/* 98/06/16 By T.Fukumoto */
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\scd\ext_v\cph_data.h"
#include	"\src\atlanta\define\sys_stat.h"/*By Y.Suzuki 1998/08/12*/
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/11/28 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif

#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
#include	"\src\atlanta\define\mntsw_f.h"
#include	"\src\atlanta\define\sysdoc.h"
/*FOR TEST*/
#include	"\src\atlanta\define\sysmemrx.h"
#include	"\src\atlanta\define\syslocal.h"

#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/07/14 */
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_line.h"
#endif /* defined (KEISATSU) */


void	NCU_CI_Interrupt(void)
{

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	UBYTE available_ci_det;

 #if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
	if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
		SYB_DensitySw = SYS_LIGHT_DENSITY;
		DensityLedOn();
	}
 #endif
	
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
#if 0 /* 警察FAX DVT Added by SMuratec 李 2005/11/16 */
@@	if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
#else
	if (SYS_InternalLineNumber != SYS_EXT_LINE_COM) {
#endif
		CI_Counter_for_FCM++;	/* 発着衝突対策 By O.Kimoto 2002/07/08 */
	}
	
	if (CHK_UNI_Line0_TxRx() == EXCLUSIVE_TX) {	/* 送信専用の場合は着信させません */
		return;
	}
	available_ci_det = 1;
	if ( ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE)	/* 標準回線には受話中 */
#if 0 /* 警察FAX DVT Modified by SMuratec 李 2005/11/16 */
		|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) 	/* 標準回線には送話中 */
#else
		|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT) /* 標準回線には送話中 */
#endif
		/* 警察FAX DVT Added by SMuratec 李 2005/11/18 */
		|| (OhPortStatus & TEL1_OFF_HOOK)
		|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE) 	/* 標準回線には通信中 */
		|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_IN_USE) ) {	/* 標準回線には本体使用中 */
		available_ci_det = 0;
	}
	if (available_ci_det == 0) {
		return;
	}
#else /* !defined (KEISATSU) */
	CI_Counter_for_FCM++;	/* 発着衝突対策 By O.Kimoto 2002/07/08 */

	if (RingStatus & CI_EXT_LINE) {	/**	拡張ラインCI検出中のときは即割り込み終了	*/
#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
		if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
			/* 済スタンプ ON */
			SYB_LocalStatus[0] |= SYS_STAMP_ON;
			StampLedOn();
		}
#endif
		return;
	}
	if (CHK_UNI_Line0_TxRx() == EXCLUSIVE_TX) {	/* 1998/03/11 by T.Soneoka 送信専用の場合は着信させません */
		return;
	}
	available_ci_det = 1;
	if (!CHK_Phone2ExtLineOn()) {
		if (CHK_UNI_TEL2_TEL1Action()) {
			if ((OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK))
			||  (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK))) {
				available_ci_det = 0;
			}
		}
		else {
			if ((OhPortStatus & TEL1_OFF_HOOK)
			||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
				available_ci_det = 0;
			}
		}
		if (NCUStatus & HOOK_KEY_ON_STATE) {
			available_ci_det = 0;
		}
	}
	else {
		if ((OhPortStatus & TEL1_OFF_HOOK)
		||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
			available_ci_det = 0;
		}
		if (NCUStatus & HOOK_KEY_ON_STATE) {
			available_ci_det = 0;
		}
	}
	if (available_ci_det == 0) {
		return;
	}
#endif /* defined (KEISATSU) */
	if (!(Tel1OhCounter = (UWORD)CHK_OnhookOffhookTime() * 10)) {	/* (UWORD)キャスト追加 By M.Tachibana 1998/10/25 */
		Tel1OhCounter = 40;
	}
#else
	CI_Counter_for_FCM++;	/* 発着衝突対策 By O.Kimoto 2002/07/08 */
 #if !defined(FRA)/*By Y.Suzuki 1998/09/11*/
  /*
  ** ＨＩＮＯＫＩ ＴＷＮ ＪＰＮ共にこの処理を入れるため、ＮＣＵタイプできらずに機種名できります
  ** （ＨＩＮＯＫＩ ＴＷＮのＮＣＵタイプはANZU_GBR_TYPEのため） by H.Hirao 1999/03/23
  */
  #if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2) /* (PRO_NCU_TYPE == HINOKI_TYPE) */ /* HINOKI2 2001/11/13 T.Takagi */
		/* ＣＩの割り込み時にＯＨのステータスがたっている場合でも無視しない。 by H.Hirao 1999/03/15 */
  #else
	if (OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
   #if (0) /* (PRO_NCU_TYPE == HINOKI_TYPE) comment by H.Hirao 1999/03/15 */
  /* ＣＩを検出する回路の感度が悪い場合、ＣＩの入力と同時にＯＨがＯＦＦした場合、ＣＩの割り込みより先にOhPortStatusがOFF_HOOK状態になり
  ** 着信できない場合がある（特にＨＩＮＯＫＩの場合、ＧＩＮＴが約２ｍｓ遅れることがあり、発生しやすい）
  ** １０ｍｓ以上OhPortStatusがOFF_HOOK状態の場合にのみリターンする
  ** by H.Hirao 1999/03/13
  */
//		if ((OhPortStatus & TEL1_OFF_HOOK) && ((SYS_GeneralTimer - Tel1OhTimer) >= 2)) {	/* ＴＥＬ１が１０ｍｓ以上オフフック状態なら */
//   #if (PRO_NUMBER_DISPLAY == ENABLE)
//			if (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) {
//				FreqStatus = TimeStatus;
//				CI_Counter++;
//				RingStatus |= CI_ON;
//				idet_evt(EVT_CI_CHECK);
//			}
//   #endif
//			return;
//		}
//		else if ((OhPortStatus & TEL2_OFF_HOOK) && ((SYS_GeneralTimer - Tel2OhTimer) >= 2)) {	/* ＴＥＬ２が１０ｍｓ以上オフフック状態なら */
//   #if (PRO_NUMBER_DISPLAY == ENABLE)
//			if (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) {
//				FreqStatus = TimeStatus;
//				CI_Counter++;
//				RingStatus |= CI_ON;
//				idet_evt(EVT_CI_CHECK);
//			}
//   #endif
//			return;
//		}
//		else {
//			/* 以下の処理を続行する */
//		}
   #else
    #if (PRO_NUMBER_DISPLAY == ENABLE) /* モデムダィヤルインでは、オフフックでも CI 割り込みイベントが必要。 by H.Kubo 1998/10/29 */
		if (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) {
			FreqStatus = TimeStatus; /*周波数チェックのため。TimeStatus:周波数チェックタスクで監視 */
			CI_Counter++;
			RingStatus |= CI_ON;
#if defined(STOCKHM2) /* 本体鳴動のテスト :by SMuratec C.P 2004/09/24 */
 			SYS_IsCallingBuzzer = 1;
#endif
			idet_evt(EVT_CI_CHECK);
		}
    #endif
		return;
   #endif
	}
  #endif

	if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
		return;
	}

	if (!(Tel1OhCounter = (UWORD)CHK_OnhookOffhookTime() * 10)) {	/* (UWORD)キャスト追加 By M.Tachibana 1998/10/25 */
		Tel1OhCounter = 40;
	}
	Tel2OhCounter = Tel1OhCounter;
 #else/* FRA */
	/*５０Hzのリングトーン がきたときにＣＩ検出中にもかかわらず、ＯＨを検出し電話表示になる。
	その対策として、ＣＩ検出中ならＯＨ検出のカウンタをリセットします。By Y.Suzuki 1998/09/16 */
	if (CI_Counter > 1) {
		if (OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
			/*FRA By Y.Suzuki 1998/09/14*/
			if (!(Tel1OhCounter = (UWORD)CHK_OnhookOffhookTime() * 10)) {	/* (UWORD)キャスト追加 By M.Tachibana 1998/10/25 */
				Tel1OhCounter = 40;
			}
			Tel2OhCounter = Tel1OhCounter;
			/*ohのカウンタをリセットするだけではなく引き続きCIの検出を行う。*/
			/*return;By Y.Suzuki 98/09/16 */
		}
		if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
			return;
		}

		if (!(Tel1OhCounter = (UWORD)CHK_OnhookOffhookTime() * 10)) {	/* (UWORD)キャスト追加 By M.Tachibana 1998/10/25 */
			Tel1OhCounter = 40;
		}
		Tel2OhCounter = Tel1OhCounter;
	}
 #endif/* FRA */
#endif

/*	if ((S_RelaySetting())	By M.Tachibana 1997/10/16	下記１行に変更	@** CMLリレーＯＮならば */
	if ((CML_RelaySetting())				/** CMLリレーＯＮならば */
	||	(AfterCI_HL_RelayOn != 0)) {		/** Ｈ／Ｌリレーを動作させたあとあらば*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/06/19 */
#if (0) /* 仮着信中にCIが入ってきたとき、リレーを触らないようにします */
**		if (NCU_RxModeSwitch == SYS_DIAL_IN_READY) {		/* ダイアルイン待機 */
#else
		if ((NCU_RxModeSwitch == SYS_DIAL_IN_READY) 		/* ダイアルイン待機 */
		&& (!(NCUStatus & DIALIN_RECEIVE_STATE))) {
#endif
			NoRingRelayOn();
		}
#endif
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/13 */
#if 0 /* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
@@		if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
#else
		if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
#endif
			return;
		}
#else /* !defined (KEISATSU) */
		return;
#endif /* defined (KEISATSU) */
	}


 #if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
	if (RingStatus & CI_EXT_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
		if ((SYS_MemorySwitch[MEMORY_SW_A5] & NONE_CALL_CI_COOUNT) /* COOUNT->Defineのほが間違っとる！*/
		&&	(CI_Counter_2nd < 1)) {

			/*
			 * 無鳴動でリレーをひくリレーの回数が２回のとき
			 * 今検出したＣＩが１発目のやつの場合、それは完全に無視する
			 * 取り敢えず一回はベル鳴らすためかな?
			 */

			/* CI より先に入ってきた極反を CI と間違えることがあるので、
			** そういう回線では 2回目の CI がほんまもんだそうです。
			** by H.Kubo 1998/02/09
			*/

			CI_Counter_2nd++;
			return;
		}
	}
	else {	/*	CI検出状態が標準ラインの場合	*/
		if ((SYS_MemorySwitch[MEMORY_SW_A5] & NONE_CALL_CI_COOUNT) /* COOUNT->Defineのほが間違っとる！*/
		&&	(CI_Counter < 1)) {

			/*
			 * 無鳴動でリレーをひくリレーの回数が２回のとき
			 * 今検出したＣＩが１発目のやつの場合、それは完全に無視する
			 * 取り敢えず一回はベル鳴らすためかな?
			 */

			/* CI より先に入ってきた極反を CI と間違えることがあるので、
			** そういう回線では 2回目の CI がほんまもんだそうです。
			** by H.Kubo 1998/02/09
			*/

			CI_Counter++;
			return;
		}
	}
 #else /* !defined (KEISATSU) */
	if ((SYS_MemorySwitch[MEMORY_SW_A5] & NONE_CALL_CI_COOUNT) /* COOUNT->Defineのほが間違っとる！*/
	&&	(CI_Counter < 1)) {

		/*
		 * 無鳴動でリレーをひくリレーの回数が２回のとき
		 * 今検出したＣＩが１発目のやつの場合、それは完全に無視する
		 * 取り敢えず一回はベル鳴らすためかな?
		 */

		/* CI より先に入ってきた極反を CI と間違えることがあるので、
		** そういう回線では 2回目の CI がほんまもんだそうです。
		** by H.Kubo 1998/02/09
		*/

		CI_Counter++;
		return;
	}
 #endif /* defined (KEISATSU) */

#if (PRO_CIPHER == ENABLE)
	/* 受信優先設定がＯＮになっているとき、
	** スクランブル処理中ならスクランブルの中断処理を行います
	** 98/06/16 By T.Fukumoto
	*/
	if (CMN_CheckScrambleBusy()) {
		if ((!CHK_UNI_PriorityReceive()) && (!SYS_CipherInterruptionOn) && (!CipherStopOn)) {
			SYS_CipherInterruptionOn = SYS_CipherComExec;
			SYS_BackupCipherStatus = SYS_MachineStatus[SYS_CIPHER_STATUS];/*By Y.Suzuki 1998/08/12*/
			CipherStopOn = 1;
		}
	}
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/13 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
	if ((NCU_ND_Status & ND_WAIT_FOR_2ND_RING) && (SYS_LineNDStatus == ND_USED_IN_STD)) {
		NCU_ND_Status |= ND_DETECT_CI_AFTER_RX_RES;
	}
	if (SYS_LineNDStatus != ND_USED_IN_STD) {
		/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/25 */
		/* ナンバーディスプレイONの場合、CIを着たら、すぐ電話リレーを回線から分離し */
		if (CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (CR_Ringing == OFF)) { /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
			if (CHK_UNI_NoRingTel2Detachable()) {
				/* ２４Ｖオフ。Ｈ／Ｌオン */
				IO__PADRL &= ~IO_BIT_CONT24;
				RelayPortStatus &= ~IO_BIT_CONT24;
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			else {
				RI_On();
				/* ２４Ｖオン。Ｈ／Ｌオン */
				RelayPortStatus |= (UWORD)(IO_BIT_CONT24);
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
				if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
					HDST_Disable();	/* ハンドセットを使用禁止にします */
				}
			}
			else {
				H_RelayOn();
			}
		}
	}
	/* まずは、 CAR 無鳴動 */
	else if (NCU_IsCarWaitedFor() && (NCU_ND_Status & ND_WAIT_FOR_CAR)) { /* CAR も待っているか */
		if ((NCU_LineStatus & STD_HDST_OFFHOOK) || (SYS_LineTelStatus & STD_TEL2_OFFHOOK)) {
			NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
			return;
		}

		NCU_ND_Status |= ND_SUSPICIOUS_CI_DETECTED;					/* CAR の最初の疑いのある CI を見つけた状態になる */
		if (CR_Ringing == OFF) { /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
			if (CHK_UNI_NoRingTel2Detachable()) {
				/* ２４Ｖオフ。Ｈ／Ｌオン */
				IO__PADRL &= ~IO_BIT_CONT24;
				RelayPortStatus &= ~IO_BIT_CONT24;
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			else {
				RI_On();
				/* ２４Ｖオン。Ｈ／Ｌオン */
				RelayPortStatus |= (UWORD)(IO_BIT_CONT24);
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
				if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
					HDST_Disable();	/* ハンドセットを使用禁止にします */
				}
			}
			else {
				H_RelayOn();
			}
		}
		if (RingStatus & CI_STD_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
			if (CI_Counter > SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD]) {
				NCU_ND_Status |= ND_CI_SEQUENCE_DETECTED;
			}
		}
	}
#if 0 /* 警察FAX DVT_ID65 Deleted by SMuratec 李 2005/12/13 */
@@	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/25 */
@@	/* ナンバーディスプレイONの場合、CIを着たら、すぐ電話リレーを回線から分離し */
@@	else if (CHK_NumberDisplayON() && (SYS_RingCounter == 0)) {
@@		if (CHK_UNI_NoRingTel2Detachable()) {
@@			/* ２４Ｖオフ。Ｈ／Ｌオン */
@@			IO__PADRL &= ~IO_BIT_CONT24;
@@			RelayPortStatus &= ~IO_BIT_CONT24;
@@			OutputWORD(GA_PGADR, RelayPortStatus);
@@		}
@@		else {
@@			RI_On();
@@			/* ２４Ｖオン。Ｈ／Ｌオン */
@@			RelayPortStatus |= (UWORD)(IO_BIT_CONT24);
@@			OutputWORD(GA_PGADR, RelayPortStatus);
@@		}
@@		if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
@@			if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
@@				HDST_Disable();	/* ハンドセットを使用禁止にします */
@@			}
@@		}
@@		else {
@@			H_RelayOn();
@@		}
@@	}
#endif
	/* まずは、 CAR 無鳴動 */
	else if (CHK_NumberDisplayByExtPhoneON() && (NCU_ND_Status & ND_BEFORE_INFO_RECEIVED)) {
		/* 外付け ND 電話で ND 着信時は、無鳴動処理をしない 1998/10/23  */
	}
	else if ( (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) 
			&& !(NCU_ND_Status & ND_MODEM_DIALIN_DIAL)
			&& (NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY) && (!SYB_DialInNoNumberSignal)) {
		/* モデムダィヤルインで着番号が取れなかったときは TEL1, TEL2 を鳴らすので無鳴動処理をしない 1998/10/28  */
	}
	else if (CHK_NumberDisplayByExtPhoneON()
			&& (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)
			&& (NCU_ND_Status & (ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING))
			&& (SYS_RingCounter == 0)) {
		/* 外付け ND 電話で ND 着信時の最初は無鳴動処理をしない by H.Kubo 1998/10/23  */
	}
	else
 #else /* !defined (KEISATSU) */
	if (NCU_ND_Status & ND_WAIT_FOR_2ND_RING ) {
		NCU_ND_Status |= ND_DETECT_CI_AFTER_RX_RES;
	}
	/* まずは、 CAR 無鳴動 */
	if (NCU_IsCarWaitedFor() && (NCU_ND_Status & ND_WAIT_FOR_CAR)) { /* CAR も待っているか */

#if defined(HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2)	/* For Debug by O.Kimoto 2002/02/18 */
		if (OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
			NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
			return;
		}
#endif

		NCU_ND_Status |= ND_SUSPICIOUS_CI_DETECTED;					/* CAR の最初の疑いのある CI を見つけた状態になる */
		if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
			if (CR_Ringing == OFF) {
				NoRingRelayOnTel1();
			}
#else
			NoRingRelayOnTel1();
#endif
		}
		else {
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
			if (CR_Ringing == OFF) {
				NoRingRelayOn();
			}
#else
			NoRingRelayOn();
#endif
		}
 #if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
		if (RingStatus & CI_EXT_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
			if (CI_Counter_2nd > SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD]) {
				NCU_ND_Status |= ND_CI_SEQUENCE_DETECTED;
			}
		}
		else {	/*	CI検出状態が標準ラインの場合	*/
			if (CI_Counter > SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD]) {
				NCU_ND_Status |= ND_CI_SEQUENCE_DETECTED;
			}
		}
 #else /* !defined (KEISATSU) */
		if (CI_Counter > SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD]) {
			NCU_ND_Status |= ND_CI_SEQUENCE_DETECTED;
		}
 #endif /* defined (KEISATSU) */
	}
	else if (NCU_ND_Status &(ND_MODEM_DIALIN_TEL1_DIAL | ND_MODEM_DIALIN_TEL2_DIAL)) {
		/* モデムダイヤルインで TEL1, TEL2 鳴動中は切らない */
	}
	else if ((NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) && (NCU_ND_Status & ND_COUNTING_2ND_RING)) {
		/* モデムダイヤルインで FAX 番号に呼出があったが着信せずにいる間は切らない by H.Kubo 1999/02/26 */
	}
	else if (CHK_NumberDisplayByExtPhoneON() && (NCU_ND_Status & ND_BEFORE_INFO_RECEIVED)) {
		/* 外付け ND 電話で ND 着信時は、無鳴動処理をしない 1998/10/23  */
	}
	else if ( (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) 
			&& !(NCU_ND_Status & ND_MODEM_DIALIN_DIAL)
			&& (NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY) && (!SYB_DialInNoNumberSignal)) {
		/* モデムダィヤルインで着番号が取れなかったときは TEL1, TEL2 を鳴らすので無鳴動処理をしない 1998/10/28  */
	}
	else if (CHK_NumberDisplayByExtPhoneON()
			&& (SYB_ND_CarPattern[SYS_ND_NCU_CONTROL_MODE] & SYS_ND_SUPPLY_FIRST_IR)
			&& (NCU_ND_Status & (ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING))
			&& (SYS_RingCounter == 0)) {
		/* 外付け ND 電話で ND 着信時の最初は無鳴動処理をしない by H.Kubo 1998/10/23  */
	}
	else
 #endif /* defined (KEISATSU) */
#endif
	/* 無鳴動着信設定かどうか調べる */
/*	if ((SYB_SettingStatus[SETTING_STATUS_16] & STG_SILENT_OPERATION) By M.Tachibana 下記１行に変更 1997/10/16 @* サイレントモードＯＮ*/
	if (CHK_SilentOperation()						/* サイレントモードＯＮ */
    ||  CHK_UNI_SilentOperation()					/* サイレントモードＯＮ By M.Tachibana 1997/12/03 */
	||	(NCU_RxModeSwitch == SYS_DIAL_IN_READY)		/* ダイアルイン待機 */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/15 */
	|| ( NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY)
#endif
	||	(NCU_RxModeSwitch == SYS_FAX_TEL_READY)		/* ＦＡＸ／ＴＥＬ待機（電話／ＦＡＸのＦＡＸ優先 */
/*	||	(NCU_RxModeSwitch == SYS_FAX_TEL_READY)) [	 * ＦＡＸ／ＴＥＬ待機（電話／ＦＡＸのＦＡＸ優先 */
	|| ((NCU_RxModeSwitch == SYS_TEL_FAX_READY) && !CHK_RingCount())/* L400 着信ベル回数０回（無鳴動）あり By Y.Suzuki 1998/04/03 */
	|| ((NCU_RxModeSwitch == SYS_FAX_READY) && !CHK_RingCount())) {/* L400 着信ベル回数０回（無鳴動）あり By Y.Suzuki 1998/03/16 */

#if (0)	/* 下記関数に変更(cmn_io.c) By M.Tachibana 1997/10/17 */
//		/* リンガーをＯＦＦし、電話を回線から切り離す */
//#if defined(JPN)
//		/* RI ＯＮ */
//		RI_On();
//#endif
//		/* ２４Ｖオン。Ｈ／Ｌオン */
//		IO__PADRL |= (IO_BIT_CONT24 | IO_BIT_H | IO_BIT_L);
#endif
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
		if (CR_Ringing == OFF) {
			NoRingRelayOn();
		}
#else
		NoRingRelayOn();
#endif
	}

#if 0 /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
** #if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
**	if (RingStatus & CI_EXT_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
**		FreqStatus2nd = TimeStatus2nd; /*周波数チェックのため。TimeStatus:周波数チェックタスクで監視 */
**		CI_Counter_2nd++;
**	}
**	else {
**		FreqStatus = TimeStatus; /*周波数チェックのため。TimeStatus:周波数チェックタスクで監視 */
**		CI_Counter++;
**	}
** #else /* !defined (KEISATSU) */
**	FreqStatus = TimeStatus; /*周波数チェックのため。TimeStatus:周波数チェックタスクで監視 */
**	CI_Counter++;
**#endif /* defined (KEISATSU) */
#else
	FreqStatus = TimeStatus; /*周波数チェックのため。TimeStatus:周波数チェックタスクで監視 */
	CI_Counter++;
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
#if 0 /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
** #if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
**	if (RingStatus & CI_EXT_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
**		RingStatus2nd |= (CI_ON | CI_STD_LINE);
**	}
**	else {
**		RingStatus |= (CI_ON | CI_STD_LINE);
**	}
** #else /* !defined (KEISATSU) */
**	RingStatus |= (CI_ON | CI_STD_LINE);
** #endif /* defined (KEISATSU) */
#else
	RingStatus |= (CI_ON | CI_STD_LINE);
#endif
#else
	RingStatus |= CI_ON;
#endif
#if defined(STOCKHM2) /* 本体鳴動のテスト :by SMuratec C.P 2004/09/24 */
 	SYS_IsCallingBuzzer = 1;
#endif
#if 0 /* 2回線呼出監視仕様変更 Deleted by SMuratec 李 2005/10/19 */
**#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
**	if (!(RingStatus & CI_STD_LINE)) {	
**		idet_evt(EVT_2ND_CI_CHECK);
**	}
**	else {
**		idet_evt(EVT_CI_CHECK);
**	}
**#else /* !defined (KEISATSU) */
**	idet_evt(EVT_CI_CHECK);
**#endif /* defined (KEISATSU) */
#else
	idet_evt(EVT_CI_CHECK);
#endif
#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
	if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
		/* 高画質 ON */
		SYB_ModeSw = SYS_FINE;
		ModeLedOn();
	}
#endif

}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
/*************************************************************************
	module		:[CI2割り込み処理]
	function	:[
		1.CI1と排他処理をおこないます
	]
	return		:[]
	common		:[]
	condition	:[POPLAR_H 疑似２回線仕様]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1997/11/20]
	author		:[曽根岡拓]
*************************************************************************/
void	NCU_CI2_Interrupt(void)
{
	UBYTE available_ci_det;

# if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
	if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
		SYB_DensitySw = SYS_DARK_DENSITY;
		DensityLedOn();
	}
#endif

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
	if (CHK_UNI_Line_EXT_TxRx() == EXCLUSIVE_TX) {	/* 拡張回線が送信専用の場合は着信させません */
		return;
	}
	available_ci_det = 1;
	if ( ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)	/* 拡張回線には受話中 */
#if 0 /* 警察FAX DVT Modified by SMuratec 李 2005/11/16 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) 	/* 拡張回線には送話中 */
#else
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) 	/* 拡張回線には送話中 */
#endif
		/* 警察FAX DVT Added by SMuratec 李 2005/11/18 */
		|| (OhPortStatus & TEL2_OFF_HOOK)
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE) 	/* 拡張回線には通信中 */
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_IN_USE) ) {	/* 拡張回線には本体使用中 */		available_ci_det = 0;
		available_ci_det = 0;
	}
	if (available_ci_det == 0) {
		return;
	}
	if ((CML_RelaySetting())				/** CMLリレーＯＮならば */
	||	(AfterCI_HL_RelayOn != 0)) {		/** Ｈ／Ｌリレーを動作させたあとあらば*/
#if 0 /* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
@@		if (ModemRelaySetting()){ /* モデムを拡張回線に接続されている場合 */
#else
		if (SYS_InternalLineNumber == SYS_EXT_LINE_COM) {
#endif
			return;
		}
	}
	/* 警察FAX DVT Added by SMuratec 李 2005/11/18 */
	if (!(Tel2OhCounter = (UWORD)CHK_OnhookOffhookTime() * 10)) {	/* (UWORD)キャスト追加 By M.Tachibana 1998/10/25 */
		Tel2OhCounter = 40;
	}
#else /* !defined (KEISATSU) */
	if (RingStatus & CI_STD_LINE) {	/**	標準ラインCI検出中のときは即割り込み終了	*/
		return;
	}
	if (CHK_UNI_Line_EXT_TxRx() == EXCLUSIVE_TX) {	/* 1998/03/11 by T.Soneoka 拡張回線が送信専用の場合は着信させません */
		return;
	}
	available_ci_det = 1;
	if (!CHK_Phone2ExtLineOn()) {
		if (CHK_UNI_TEL2_TEL1Action()) {
			if ((OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK))
			||  (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK))) {
				available_ci_det = 0;
			}
		}
		else {
			if ((OhPortStatus & TEL1_OFF_HOOK)
			||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
				available_ci_det = 0;
			}
		}
		if (NCUStatus & HOOK_KEY_ON_STATE) {
			available_ci_det = 0;
		}
	}
	else {
		if ((OhPortStatus & TEL1_OFF_HOOK)
		||  (NCUStatus & TELEPHONE1_OFF_HOOK)) {
			available_ci_det = 0;
		}
		else if ((OhPortStatus & TEL2_OFF_HOOK)
		     ||  (NCUStatus & TELEPHONE2_OFF_HOOK)) {
			available_ci_det = 0;
		}
		if (NCUStatus & HOOK_KEY_ON_STATE) {
			available_ci_det = 0;
		}
	}
	if ((available_ci_det == 0)
	&&  (CHK_UNI_TelOpeDialTx())) {
		return;
	}
	if ((CML_RelaySetting())				/** CMLリレーＯＮならば */
	||	(AfterCI_HL_RelayOn != 0)) {		/** Ｈ／Ｌリレーを動作させたあとあらば*/
		return;
	}
#endif /* defined (KEISATSU) */

#if (PRO_CIPHER == ENABLE)
	/* 受信優先設定がＯＮになっているとき、
	** スクランブル処理中ならスクランブルの中断処理を行います
	** 98/06/16 By T.Fukumoto
	*/
	if (CMN_CheckScrambleBusy()) {
		if ((!CHK_UNI_PriorityReceive()) && (!SYS_CipherInterruptionOn) && (!CipherStopOn)) {
			SYS_BackupCipherStatus = SYS_MachineStatus[SYS_CIPHER_STATUS];/*By Y.Suzuki 1998/08/12*/
			SYS_CipherInterruptionOn = SYS_CipherComExec;
			CipherStopOn = 1;
		}
	}
#endif

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
	if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_EXT)) {
		if (NCU_ND_Status & ND_WAIT_FOR_2ND_RING) {
			NCU_ND_Status |= ND_DETECT_CI_AFTER_RX_RES;
		}
		/* まずは、 CAR 無鳴動 */
		if (NCU_IsCarWaitedFor() && (NCU_ND_Status & ND_WAIT_FOR_CAR)
			&& (SYS_LineNDStatus == ND_USED_IN_EXT)) { /* CAR も待っているか */
			if ((NCU_LineStatus & EXT_HDST_OFFHOOK) || (SYS_LineTelStatus & EXT_TEL2_OFFHOOK)) {
				NCU_ND_Status &= ~ND_SUSPICIOUS_CI_DETECTED;
				return;
			}

			NCU_ND_Status |= ND_SUSPICIOUS_CI_DETECTED;					/* CAR の最初の疑いのある CI を見つけた状態になる */
			if (CHK_UNI_NoRingTel2Detachable()) {
				/* ２４Ｖオフ。Ｈ／Ｌオン */
				IO__PADRL &= ~IO_BIT_CONT24;
				RelayPortStatus &= ~IO_BIT_CONT24;
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			else {
				RI_On();
				/* ２４Ｖオン。Ｈ／Ｌオン */
				RelayPortStatus |= (UWORD)(IO_BIT_CONT24);
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
				if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続 */
					HDST_Disable();	/* ハンドセットを使用禁止にします */
				}
 			}
			else {
				L_RelayOn();
			}
			if (RingStatus2nd & CI_EXT_LINE) {	/*	CI検出状態が拡張ラインの場合	*/
				if (CI_Counter_2nd > SYB_ND_CarPattern[SYS_ND_CI_COUNTER_THRESHOLD]) {
					NCU_ND_Status |= ND_CI_SEQUENCE_DETECTED;
				}
			}
		}
	}
#endif
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/29 */
#if 0 /* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
**	if (RingStatus & CI_STD_LINE) {	/**	CI検出状態が標準ラインの場合	*/
**		FreqStatus2nd = TimeStatus2nd;
**		CI_Counter_2nd++;
**		RingStatus2nd |= (CI_ON | CI_EXT_LINE);
**	}
**	else {
**		FreqStatus = TimeStatus;
**		CI_Counter++;
**		RingStatus |= (CI_ON | CI_EXT_LINE);
**	}
#else 
	FreqStatus2nd = TimeStatus2nd;
	CI_Counter_2nd++;
	
	RingStatus2nd |= (CI_ON | CI_EXT_LINE);
#endif
#else /* !defined (KEISATSU) */
	FreqStatus = TimeStatus;
	CI_Counter++;

	RingStatus |= (CI_ON | CI_EXT_LINE);
#endif /* defined (KEISATSU) */
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
#if 0 /* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
**	if (!(RingStatus & CI_EXT_LINE)) {	
**		idet_evt(EVT_2ND_CI_CHECK);
**	}
**	else {
**		idet_evt(EVT_CI_CHECK);
**	}
#else
	idet_evt(EVT_2ND_CI_CHECK);
#endif
#else /* !defined (KEISATSU) */
	idet_evt(EVT_CI_CHECK);
#endif /* defined (KEISATSU) */
#if defined(POPLAR_H) && defined(JP0)/* V851 By Y.Suzuki 2002/09/05*/
		/* 高画質 ON */
	if (SYB_MaintenanceSwitch[MNT_SW_F0] & 0x01) {
		SYB_ModeSw = SYS_FINE;
		ModeLedOn();
	}
#endif
}
#endif
