/*---------------------------------------------------------------------------*/
/*	�v���W�F�N�g : ATLANTA		ANZU���ڐA									 */
/*	�t�@�C����	 : FCMFIF2.C												 */
/*	���W���[��	 :															 */
/*				 : SetUpMemoryRx()											 */
/*				 : SetDocumentMemorySizeFrame()								 */
/*				 : CheckPollingTxType()										 */
/*				 : SetUpRxDocumentPollingTx()								 */
/*				 : SetRestMemoryFrame()										 */
/*				 : SetUpSecureMailRx()										 */
/*				 : SetUpSecureMailTx()										 */
/*				 : SetUpBufferingRx()										 */
/*				 : GetGroupNoFromStdID()									 */
/*				 : CountRelayedTxCommand()									 */
/*				 : SetUpRelayBroadCastRx()									 */
/*				 : GetDatabasePollingFileNumber()							 */
/*				 : SetUpRemoteFaxRx()										 */
/*				 : SetPasscodeFrame()										 */
/*				 : SetSecureMailFieldFrame()								 */
/*				 : SetDatabasePollingDataFrame()							 */
/*				 : SetRelayedBroadcastGroupFrame()							 */
/*	�쐬��		 : �R��														 */
/*	��	�t		 :1996/11/19												 */
/*	�T	�v		 :															 */
/*				 :															 */
/*	�C������	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSMAILB.H"
#include "\src\atlanta\define\SYSDIAL.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\STNG_PRO.H"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\CMN_PRO.H"
#include "\src\atlanta\define\UNI_PRO.H"

#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\OPR_PRO.H"
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\OPR_PRO.H"
#endif
#include "\src\atlanta\define\status.H"		/* 1998/01/21  By T.Yamaguchi */

/* MDM */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

/*--------------------------------------------------*/
/*	  TSI�ɂ�钆�X�p�w�� 14.Feb'95 Y.Suzuki		*/
/*--------------------------------------------------*/
#if(PRO_TSI_RELAY_COM == ENABLE)
 #include "\src\atlanta\ext_v\ROM_TBL.h"
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* ���[�v�@�\ By H.Hirao 1998/08/31 */
 #include "\src\atlanta\define\syswarp.h"
 #include "\src\atlanta\define\sysnd.h"
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/10/19 By M.Kuwahara */
 #include "\src\atlanta\define\cmn_nd.h"
#endif

/*************************************************************************
	module		:[��������M����]
	function	:[
		1.��������M
	]
	return		:[��������:YES �m�f:NO]
	common		:[]
	condition	:[]
	comment		:[�C������
				1.94/9/8 ��s�o�b�t�@�X�e�[�^�X�̕ύX�́A���C���^�X�N�ɂčs���B
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/05/06]
	author		:[��؈��]
*************************************************************************/
UBYTE SetUpMemoryRx(void)
{
	/*struct SYS_MemoryRxPrintData_t far *MemoryRxPrintPoint;* 29.Apr'94 */
	/*UBYTE j;*/

	if (CMN_CheckMemoryReceiveEnable() == TRUE) {
		/**	��s��M�o�b�t�@�A�������ɋ󂫂�����΁A��������M	*/
		SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;/*	�ʏ�̃�������M	*/
		SYS_RxMemoryFileNo = SYB_MemoryRxPrintWritePoint;
		SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;

	/* man_main.c MSG_RX_PRINT_PAGE ��M��ɃZ�b�g���Ă���̂ł����ł͂��Ȃ��B8.Sep'94
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
		MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
	*/
		return(YES);
	}
	else {/**	�󂫂��Ȃ���΁A�G���[����	*/
		SYS_RxMemoryFileItem = NULL;/* �ʐM�Ŏg�p���ɂ����v�����^���J�����邽�� */
		return(NO);
	}
	return(NO);
}


/*************************************************************************
	module		:[�m�r�r�t���[���Ɍ��e�������e�ʃZ�b�g]
	function	:[
		���e�������g�p�e�ʂ��m�r�r�t���[���ɃZ�b�g����
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[���f���o�b�t�@]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/5/2]
	author		:[��� ���]
*************************************************************************/
WORD SetDocumentMemorySizeFrame(WORD pos)					/*	���f���o�b�t�@�̃|�C���^	*/
{
	UWORD page;
	long block;
	UWORD no;

	page = 0;
	block = 0;
	no = 0;

	/* DB�|�[�����O,�o�b�`���M�̏ꍇ */
	if((SYS_DocBlock.Index.Item == SYS_MEM_DB_POLLING_FILE) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE1) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE2) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE3) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE4) ||
		(SYS_DocBlock.Index.Item == SYS_MEM_BATCH_TX_FILE5)) {
		for(no = TxMemoryFileCurrentExecutingNo;TxMemoryFileNo[no] != 0xFFFF; no++) {
			block += MEM_CountTotalBlock(SYS_DocBlock.Index.Item,TxMemoryFileNo[no], MEM_IGNORE_BOX_NUMBER);
			page += MEM_CountTotalPage(SYS_DocBlock.Index.Item,TxMemoryFileNo[no], MEM_IGNORE_BOX_NUMBER);
		}
	}
	/* �e�R�[�h�̏��������鎖1997/03/12  By T.Yamaguchi */
	else if((SYS_DocBlock.Index.Item == SYS_MEM_SUB_SECURE_FILE)
		 || (SYS_DocBlock.Index.Item == SYS_MEM_SUB_BULLETIN_FILE)) {
		for(no = TxMemoryFileCurrentExecutingNo;TxMemoryFileNo[no] != 0xFFFF; no++) {
			block += MEM_CountTotalBlock(SYS_DocBlock.Index.Item,TxMemoryFileNo[no],SYS_DocBlock.Index.BoxNumber );
			page += MEM_CountTotalPage(SYS_DocBlock.Index.Item,TxMemoryFileNo[no],SYS_DocBlock.Index.BoxNumber );
		}
	}
	/* DB�|�[�����O�ȊO�Ȃ�A*/
	else {
		block = MEM_CountTotalBlock(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, MEM_IGNORE_BOX_NUMBER);
		page = MEM_CountTotalPage(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, MEM_IGNORE_BOX_NUMBER);
	}
	/**	�g�p�y�[�W���Z�b�g	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)page;
	pos++;
	/*�P�u���b�N1024�o�C�g�Ɋ��Z*/
	block *= MEM_BLOCK_SIZE;/* �o�C�g�T�C�Y */
	block /= 1024;
	/**	�g�p�u���b�N���Z�b�g	*/
	/*	����	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)(0x000000FF & block);/*	���ʂ̂P�o�C�g�ɂ�����������邩�v�m�F	*/
	pos++;
	/*	���	*/
	MDM_ModemBuffer[InNS][pos] = (UBYTE)((0x0000FF00 & block) >> 8);/*	���ʂ̂P�o�C�g�ɂ�����������邩�v�m�F	*/

	/**	���^�[�����f���o�b�t�@�̃|�C���^	*/
	return(pos);
}



/*************************************************************************
	module		:[��M���e�|�[�����O���M��ʊm��]
	function	:[
		1.4�̃������X�C�b�`�����āA��ʂ��m�肷��
		�D�揇��	��s��M�@���@�e�W��M�@���@�e�h�o��M�@���@���M�\�񌴍e�i�Ƃ肠�����j
	]
	return		:[
					RX_DOC_POLLING_TX			:��s��M���e�|�[�����O���M
					SECURE_DOC_POLLING_TX		:�e�W��M���e�|�[�����O���M
					FIP_DOC_POLLING_TX			:�e�h�o��M���e�|�[�����O���M
					TX_DOC_POLLING_TX			:���M�\�񌴍e�|�[�����O���M
					NO							:��M���e�|�[�����O���M�Ȃ�
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/03/25]
	author		:[��؈��]
*************************************************************************/
UBYTE CheckPollingTxType(void)
{
	if(CHK_UNI_RxDocToPollingDoc()) {
		return(RX_DOC_POLLING_TX);
	}
	else if(CHK_UNI_SecureDocToPollingDoc()) {
		return(SECURE_DOC_POLLING_TX);
	}
#if(PRO_FIP == ENABLE)
	else if(CHK_UNI_FIP_DocToPollingDoc()) {
		return(FIP_DOC_POLLING_TX);
	}
#endif
	else if(CHK_UNI_TxDocToPollingDoc()) {
		return(TX_DOC_POLLING_TX);
	}
#if (PRO_CIPHER == ENABLE)/*By Y.Suzuki 1998/10/07*/
	else if(CHK_UNI_ScrambleDocToPollingDoc()) {
		return(SCRAMBLE_DOC_POLLING_TX);
	}
#endif
	return(0);
}

/*************************************************************************
	module		:[��M���e�|�[�����O���M����]
	function	:[
		1.�������X�C�b�`�m�F�@�ǂꂩ�A�P�̃������X�C�b�`�ɂ̂ݑΉ�
		2.�e�W���e�̏ꍇ�^�e�h�o��M���e�̏ꍇ
		  ���M���e�̗L���`�F�b�N
		  ����M�t�@�C���A�C�e��,�i���o�[��y�[�W�Z�b�g
		  ����݂���A�t�@�C���i���o�[�̏��������ɃZ�b�g����
		3.��s��M���e�̏ꍇ
		  ���M���e�̗L���`�F�b�N
		  ����M�t�@�C���A�C�e��,�i���o�[��y�[�W�Z�b�g
		  ���M�������ԂɃZ�b�g����
		4.���M�������t�@�C���̎��̃o�b�t�@��0xFFFF������
	]
	return		:[�Z�b�g�A�b�v����:YES	�m�f:NO]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/03/25]
	author		:[��؈��]
*************************************************************************/
UBYTE SetUpRxDocumentPollingTx(void)
{
	UWORD  page;
	UBYTE a;
	UBYTE b;
	UBYTE end_point;
	UBYTE ok_flag;
	UBYTE abort_flag;

	a = 0;
	b = 0;
	abort_flag = 0;
	ok_flag = NO;
	page = 0;
	if(RxDocumentPollingTxFlag == RX_DOC_POLLING_TX) {/* ��s��M���e�̏ꍇ	*/
		/*b = (UBYTE)(SYB_MemoryRxPrintWritePoint);By Y.Suzuki 1998/09/25 */
		if ((SYB_MemoryRxPrintWritePoint < 0) || (SYS_MEMORY_RX_MAX <= SYB_MemoryRxPrintWritePoint)) {
			/* ��s��M�t���A�������[�c�ʂȂ����́A0xff�ƂȂ��Ă���BBy Y.Suzuki 1998/09/25 */
			b = 0;
		}
		else {
			b = (UBYTE)(SYB_MemoryRxPrintWritePoint);
		}
		if (b == 0) {
			end_point = (UBYTE)(SYS_MEMORY_RX_MAX - 1);
		}
		else {
			end_point = (UBYTE)(b - 1);
		}
	}
	/*for (a = 0; a < (SYS_TX_MEMORY_FILE_NO_MAX); b++) [@** ���o����t�@�C��NO�̐� By Y.Suzuki 1998/09/16 */
	for (a = 0; a < (SYS_MEMORY_RX_MAX); b++) {/** ���o����t�@�C��NO�̐� */
		switch(RxDocumentPollingTxFlag) {
		case SECURE_DOC_POLLING_TX:
			/**	�e�W��M���e�|�[�����O���M�X�C�b�`�n�m	*/
			if(b < SYS_MAILBOX_MAX) {/**	���C���{�b�N�X�O�|�|�X�̎�M���e�̗L�����`�F�b�N����	*/
				if(SYB_MailBox[b].Status == SYS_MAILBOX_RECEIVE) {
					page = MEM_CountFinalPage(SYS_MEM_SECURE_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
					if(page != MEM_NO_INDEX) {/** ��M���e����	*/
						ok_flag = YES;
						TxMemoryFileNo[a] = b;/**	���M�t�@�C���m�n,�y�[�W�Z�b�g	*/
						PollingTxFilePage[a] = page;
						a++;
					}
				}
			}
			else {/**	�`�F�b�N�I��	*/
				if(ok_flag) {/**	���M�t�@�C���A�C�e���Z�b�g	*/
					TxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_SECURE_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
 #if(PRO_FIP == ENABLE)
		case FIP_DOC_POLLING_TX:
			/**	�e�h�o��M���e�|�[�����O���M�X�C�b�`�n�m	*/
			page = MEM_CountTotalPage(SYS_MEM_FIP_FILE, 0, MEM_IGNORE_BOX_NUMBER);
			if(page != MEM_NO_INDEX) {/** ��M���e����	*/
				ok_flag = YES;
				TxMemoryFileItem = SYS_MEM_FIP_FILE;/**	���M�t�@�C���A�C�e���Z�b�g	*/
				TxMemoryFileNo[a] = 0;/**	���M�t�@�C���m�n,�y�[�W�Z�b�g	*/
				PollingTxFilePage[a] = page;
				a++;
				abort_flag = 1;
				TxMemoryFilePage = SYS_TxTotalPage + 1;
			}
			break;
#endif
		case RX_DOC_POLLING_TX:
			/**	��s��M���e�|�[�����O���M�X�C�b�`�n�m	*/
			if (b > (SYS_MEMORY_RX_MAX - 1)) b = 0;/* ��s��M�o�b�t�@[0--9] */
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
			if(SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_PRINT) {
#else
			if ((SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_PRINT)
			 || (SYB_MemoryRxPrint[b].Status == SYS_MEMORY_RX_FAST_PRINT)) {
#endif
				page = MEM_CountFinalPage(SYS_MEM_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
				if(page != MEM_NO_INDEX) {/** ��M���e����	*/
					ok_flag = YES;
					TxMemoryFileNo[a] = b;/**	���M�t�@�C���m�n,�y�[�W�Z�b�g	*/
					PollingTxFilePage[a] = page;
					a++;
				}
			}
			if(b == end_point) {	/* �C�� 1997/04/01  By T.Yamaguchi */
				if(ok_flag) {/**	���M�t�@�C���A�C�e���Z�b�g	*/
					TxMemoryFileItem = SYS_MEM_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
		case TX_DOC_POLLING_TX:
			/**	���M�\�񌴍e�|�[�����O���M�X�C�b�`�n�m�@�����́A��s�Ɠ����������Ƃ肠��������Ă���	*/
			abort_flag = 1;/* �ǉ� 14.Mar'95 Y.Suzuki */
			ok_flag = NO;
			TxMemoryFilePage = SYS_TxTotalPage + 1;
			break;
#if (PRO_CIPHER ==ENABLE)/*By Y.Suzuki 1998/10/07*/
		case SCRAMBLE_DOC_POLLING_TX:
			/**	�X�N�����u����M���e�|�[�����O���M�X�C�b�`�n�m	*/
			if(b < SYS_CIPHERBOX_MAX) {/**	���C���{�b�N�X�O�|�|�X�̎�M���e�̗L�����`�F�b�N����	*/
				if(SYB_CipherBox[b].Status == SYS_CIPHERBOX_RECEIVE) {
					page = MEM_CountFinalPage(SYS_MEM_CIPHER_RX_FILE, b, MEM_IGNORE_BOX_NUMBER);
					if(page != MEM_NO_INDEX) {/** ��M���e����	*/
						ok_flag = YES;
						TxMemoryFileNo[a] = b;/**	���M�t�@�C���m�n,�y�[�W�Z�b�g	*/
						PollingTxFilePage[a] = page;
						a++;
					}
				}
			}
			else {/**	�`�F�b�N�I��	*/
				if(ok_flag) {/**	���M�t�@�C���A�C�e���Z�b�g	*/
					TxMemoryFileItem = SYS_MEM_CIPHER_RX_FILE;
					TxMemoryFilePage = MEM_CountTopPage(SYS_MEM_CIPHER_RX_FILE, TxMemoryFileNo[0], MEM_IGNORE_BOX_NUMBER);
				}
				abort_flag = 1;
			}
			break;
#endif
		}
		if(abort_flag == 1) {
			break;
		}
	}
	if (ok_flag == NO) {	/**	�w�肳�ꂽ�t�@�C���̃y�[�W�����S�ĂO�ȉ�	*/
		return(NO);/**	���^�[���O	*/
	}
	/**	���M�������t�@�C���̎��̃o�b�t�@��0xFFFF������	*/
	TxMemoryFileNo[a] = 0xFFFF;
	PollingTxFilePage[a] = 0xFFFF;
	/**	���^�[��1 ���M�t�@�C���y�[�W�Z�b�g	*/

	/* ��s��M���e���������v�����g������i���e�������ꂽ��j�ɁA�v�����^���~�܂����ꍇ
	**	��s��M���e���|�[�����O���M�ł��Ȃ��i�P�y�[�W�ڂ̌��e�������Ă��邩��j�œr���̌��e����ł��|�[�����O���M�ł���
	**	�悤��TxMemoryFilePage�Ɉ�ԏ�����page���Z�b�g����l�ɕύX	 1997/02/08	 By T.Yamaguchi
	TxMemoryFilePage = SYS_TxTotalPage + 1;
	*/

#if (0) /* ��M���e�|�[�����O���o���C���� �eRxDocumentPollingTxFlag���ƂɃZ�b�g����悤�ɕύX���܂� by T.Soneoka 1997/02/21 */
//	TxMemoryFilePage = MEM_CheckMostSmallPage(TxMemoryFileItem,TxMemoryFileNo[0]);
//	PollingTxFilePage[0] = (PollingTxFilePage[0] + TxMemoryFilePage - 1);
#endif
	return (YES);
}


/*************************************************************************
	module		:[�������c�ʃ`�F�b�N]
	function	:[
		NSF�NSC �̃������e�ʃt�B�[���h���Z�b�g����
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[���f���o�b�t�@]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[��� ���]
*************************************************************************/
WORD SetRestMemoryFrame(
				UBYTE FrameName,	/*	NSC,NSS,NSF	*/
				WORD pos)					/*	���f���o�b�t�@�̃|�C���^	*/
{
 #if 0 /* (PRO_PRINT_TYPE != LASER) 1997/03/22  By T.Yamaguchi */
//	UWORD page;
//	DWORD block;
//
//	page = 0;
//	block = 0;
//
//	page = MEM_CountTotalEmptyPage();
//	block = MEM_CountTotalEmptyBlock();
//	block *= MEM_BLOCK_SIZE;/* �o�C�g�T�C�Y */
//	block /= 1024;
//
//	/**	�󂫕Ő��Z�b�g	*/
//	if(page > 0x00FF) {/* �g�t */
//		MDM_ModemBuffer[InNS][pos] = 0xFF;
//	}
//	else {
//		MDM_ModemBuffer[InNS][pos] = (UBYTE)page;/* �����A���x���_�[�́AMAX 42�106(�C���f�b�N�X) */
//	}
//	pos++;
//	/**	�󂫃u���b�N���Z�b�g	*/
//	/*	���	*/
//	MDM_ModemBuffer[InNS][pos] = (UBYTE)(block & 0x000000FF);
//	pos++;
//	block &= 0x0000FF00;
//	block >>= 8;
//	/*	����	*/
//	MDM_ModemBuffer[InNS][pos] = (UBYTE)block;
//#else
#endif
	switch (FrameName) {		/**	�t���[����	*/
		case NSF_F:	/**	NSF	*/
		case NSC_F:	/**	NSC	*/
			/**	FF���R�o�C�g�Z�b�g	*/
			MDM_ModemBuffer[InNS][pos] = 0xFF;
			MDM_ModemBuffer[InNS][++pos] = 0xFF;
			MDM_ModemBuffer[InNS][++pos] = 0xFF;
			break;
		case NSS_F:	/**	NSS	*/
			/**	00���R�o�C�g�Z�b�g	*/
			MDM_ModemBuffer[InNS][pos] = 0x00;
			MDM_ModemBuffer[InNS][++pos] = 0x00;
			MDM_ModemBuffer[InNS][++pos] = 0x00;
			break;
	}
/*  #endif */
	/**	���^�[�����f���o�b�t�@�̃|�C���^	*/
	return(pos);
}


/*************************************************************************
	module		:[�Ǝ��t���[���Ɏ��Ѓ��[�h���Z�b�g����]
	function	:[
		1.�~�����̏ꍇ�́A�e�w�R�[�h���Z�b�g����B
	]
	return		:[]
	common		:[
					MDM_ModemBuffer
					InNS
					MAKERCODE_POS
					OwnMakerCode
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/01/28]
	author		:[��؈��]
*************************************************************************/
void SetMakerCodeFrame(void)
{
	MDM_ModemBuffer[InNS][MAKERCODE_POS] = OwnMakerCode;
	return;
}


/* ������艺�l�l�k��p */
#if(PRO_MAKER == MML)
/*************************************************************************
	module		:[�e�W��M����]
	function	:[
		1.�e�W��M�\�Ȃ��M�t�@�C���̃Z�b�g�A�b�v���s��
		2.NSS�ɂ��w�肳�ꂽ���C���{�b�N�XNO.�̎��o��
		3.���@�Ɏw�肳�ꂽ���C���{�b�N�X�����݂���
		4.���C���{�b�N�X�̎�M���
		5.���C���{�b�N�X�������h�c�o�^�i�������C���{�b�N�X�ɈقȂ�h�c��
		. �e�`�w�����M����ƍŌ�Ɏ�M�����h�c�̂ݗL���j
	]
	return		:[�n�j--YES�^�m�f--NO]
	common		:[
				NonStdFrm
				RxMemoryFileItem
				RxMemoryFileNo
				Mailbox.:Status
				FipSecureStartPage
				SYB_TTI_ID_Buffer
				OwnMakerCode
				Mailbox.:RemoteName
				SYS_TTI_buffer
	]
	condition	:[]
	comment		:[�������c�ʃ`�F�b�N���Ă��Ȃ� �������Ȃ��@�͐e�W��M�Ȃ�
				  �e�W��M���߰��No�̾�ĂŽð����RECEIVE�ł��P������M��
				  �Ă��Ȃ���������̂ł��̃p�X��ǉ�		1994/11/29 Y.M
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[��� ���]
*************************************************************************/
UBYTE SetUpSecureMailRx(WORD pos)	/*	���f���o�b�t�@�̃|�C���^�[	*/
{
	UWORD mailbox_no;
	UBYTE temp;
	UBYTE i;

	mailbox_no = 0;
	temp = 0;
	i = 0;

	switch (MDM_ModemBuffer[NonStdFrmPos][pos]) {		/**	�Ǝ��t���[���̃��C���{�b�N�XNO.�`�F�b�N	*/
		/**	���C���{�b�N�XNO.�����[�J���ϐ��ɃZ�b�g	*/
		/*	�w�肳��郁�C���{�b�N�X�́A�P��	*/
		/*	�Q�o�C�g�ɕʂ�Ă���	*/
		case 0x00:
			break;
		case 0x01:	/*	���C���{�b�N�XNO.0	*/
			mailbox_no = 0;
			break;
		case 0x02:	/*	���C���{�b�N�XNO.1	*/
			mailbox_no = 1;
			break;
		case 0x04:	/*	���C���{�b�N�XNO.2	*/
			mailbox_no = 2;
			break;
		case 0x08:	/*	���C���{�b�N�XNO.3	*/
			mailbox_no = 3;
			break;
		case 0x10:	/*	���C���{�b�N�XNO.4	*/
			mailbox_no = 4;
			break;
		case 0x20:	/*	���C���{�b�N�XNO.5	*/
			mailbox_no = 5;
			break;
		case 0x40:	/*	���C���{�b�N�XNO.6	*/
			mailbox_no = 6;
			break;
		case 0x80:	/*	���C���{�b�N�XNO.7	*/
			mailbox_no = 7;
			break;
		default:	/*	�Y�����Ȃ�NO.�̏ꍇ	*/
			/*	�e�W��M�s��	*/
			return (NO);
	}
	switch(MDM_ModemBuffer[NonStdFrmPos][pos+1]) {
		case 0x00:	/*	���C���{�b�N�XNO.	*/
			break;
		case 0x01:	/*	���C���{�b�N�XNO.8	*/
			mailbox_no = 8;
			break;
		case 0x02:	/*	���C���{�b�N�XNO.9	*/
			mailbox_no = 9;
			break;
		case 0x04:	/*	���C���{�b�N�XNO.	*/
		case 0x08:	/*	���C���{�b�N�XNO.	*/
		case 0x10:	/*	���C���{�b�N�XNO.	*/
		case 0x20:	/*	���C���{�b�N�XNO.	*/
		case 0x40:	/*	���C���{�b�N�XNO.	*/
		case 0x80:	/*	���C���{�b�N�XNO.	*/
		default:	/*	�e�W��M�s��	*/
			return (NO);
	}
	if (mailbox_no >= SYS_MAILBOX_MAX) {
		return (NO);
	}

	CMN_DisableInterrupt();		/** ���荞�݋֎~ *//*SYS_MAILBOX_RCV_TO_RECEVING*/

	/**	��������M�p�A�C�e���Z�b�g�i�e�W��M���e�j	*/
	SYS_RxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;

	/**	�w�胁�C���{�b�N�X�̏�Ԃ̃`�F�b�N	*/
	switch (SYB_MailBox[mailbox_no].Status) {		/**	���C���{�b�N�X�̃X�e�[�^�X	*/
		case SYS_MAILBOX_NO_SET:	/**	���o�^	*/
			/**	�e�W��M���Ȃ�	*/
			CMN_EnableInterrupt();		/** ���荞�݋��� */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
			break;
		case SYS_MAILBOX_RECEIVE:			/**	���C���{�b�N�X��M�ς�	*/
			/**	���C���{�b�N�X��M��	*/
			/* SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RECEIVING;/@ �o�b�N�A�b�v�̂��ߒǉ� 17.Aug'94 Y.Suzuki */
			SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RCV_TO_RECEVING;/* �o�b�N�b�v�̂��ߒǉ� 1997/10/18  By T.Yamaguchi */
			CMN_EnableInterrupt();		/** ���荞�݋��� */	/* 1998/01/22  By T.Yamaguchi */
			/* ��M���̐e�W���e�̏�����h�~���邽�� �� */
			/**	��������M�p�y�[�W�J�E���^�ɐe�W��M�ς݃y�[�W���Z�b�g	*/
			/*	SYS_RxMemoryFilePage = (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE, mailbox_no, MEM_IGNORE_BOX_NUMBER) + 1);	*/
			SYS_RxMemoryFilePage = MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE, mailbox_no, MEM_IGNORE_BOX_NUMBER);
			if (SYS_RxMemoryFilePage == MEM_NO_INDEX) {	/* �ð����SYS_MAILBOX_RECEIVE�ł���M�������O�̎������� */
				SYS_RxMemoryFilePage = 1;		/* 1994/11/29 Y.Murata */
			}
			else {	/* ���y�[�W���Z�b�g 1997/08/28  By T.Yamaguchi */
				SYS_RxMemoryFilePage++;
			}

 #if(PRO_FIP == ENABLE)
			/**	FIP�e�W��M�J�n�y�[�W�Ƀy�[�W�J�E���^���Z�b�g	*/
			SYS_FIP_SecureStartPage = SYS_RxMemoryFilePage;
 #endif
			break;
		case SYS_MAILBOX_SET:	/**	���C���{�b�N�X�o�^�ς�	*/
			/**	���C���{�b�N�X��M��	*/
			SYB_MailBox[mailbox_no].Status = SYS_MAILBOX_RECEIVING;/* �o�b�N�A�b�v�̂��ߒǉ� 17.Aug'94 Y.Suzuki */
			CMN_EnableInterrupt();		/** ���荞�݋��� */	/* 1998/01/22  By T.Yamaguchi */
			/* ��M���̐e�W���e�̏�����h�~���邽�� �� */
			/**	��������M�p�y�[�W�J�E���^�Ɂi��M�y�[�W���{�P�j���Z�b�g	*/
			SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
 #if(PRO_FIP == ENABLE)
			/**	FIP�e�W��M�J�n�y�[�W�Ƀy�[�W�J�E���^���Z�b�g	*/
			SYS_FIP_SecureStartPage = SYS_RxMemoryFilePage;
 #endif
			break;
		case SYS_MAILBOX_RECEIVING:
		case SYS_MAILBOX_RCV_TO_RECEVING:	/**	���C���{�b�N�X��M��	*/
			FaxCompatibleErrorCode = SECURE_INDEX_CONFLICT_ERROR;
			CMN_EnableInterrupt();		/** ���荞�݋��� */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
			break;
		default:/**	�X�e�[�^�X�G���[	*/
			/**	�e�W��M���Ȃ�	*/
			CMN_EnableInterrupt();		/** ���荞�݋��� */	/* 1998/01/22  By T.Yamaguchi */
			return(NO);
	}
	/**	��������M�t�@�C��NO.�Ƀ��C���{�b�N�XNO.	*/
	SYS_RxMemoryFileNo = (UWORD)mailbox_no;			/* SYS_MAILBOX_RCV_TO_RECEVING */
	CMN_EnableInterrupt();		/** ���荞�݋��� */

	/**	�e�W��M���C���{�b�N�X�Ǘ��f�[�^���̑����h�c�̃f�[�^�̓o�^������	*/
	if ((NonStandardID[0] != NULL) && (OwnMakerCode == MURATA_CODE)) {		/**	�Ǝ��i�J�i�j�h�c����A���l�l�k�@	*/
		/**	�J�i�h�c�o�^	*/
		for (i = 0; i < 16; i++) {
			SYB_MailBox[mailbox_no].RemoteName[i] = NonStandardID[i];
		}
		SYB_MailBox[mailbox_no].RemoteName[i] = NULL;
	}
	else if (StandardID[0] != NULL) {	/**	�W���h�c����	*/
		/**	�W���h�c�o�^	*/
		for (i = 0; i < 20; i++) {
			SYB_MailBox[mailbox_no].RemoteName[i] = StandardID[i];
		}
		SYB_MailBox[mailbox_no].RemoteName[i] = NULL;
	}
	else {
		/**	�o�^���Ȃ�	*/
		SYB_MailBox[mailbox_no].RemoteName[0] = NULL;
	}
	/**	���^�[��YES	*/
	return(YES);
}


/*************************************************************************
	module		:[�e�W���M����]
	function	:[
		1.�e�W���M�ɍۂ��đ��M���Ŏw���������C���{�b�N�X����M���ɃZ�b�g����Ă��邩�`�F�b�N����
	]
	return		:[�n�j--YES�^�m�f--NO]
	common		:[
					CommandP->Option.OptionNumber.:SecuteNumber
					MDM_ModemBuffer
					NonStdFrmPos
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[��� ���]
*************************************************************************/
UBYTE SetUpSecureMailTx(WORD pos)	/*	���f���o�b�t�@�̃|�C���^�[	*/
{
	UWORD compare_boxno;
	UWORD partner_boxno;
	UBYTE secure_no;	/* �e�W�ԍ� */

	compare_boxno = 0x01;
	partner_boxno = 0;
	secure_no = 0;

	secure_no = (UBYTE)(CommandP -> Option.OptionNumber.SecureNumber);

	compare_boxno = (UWORD)(compare_boxno << secure_no);

#if 0	/* ���ɕύX 1996/12/02	By T.Yamaguchi */
	switch (CommandP -> Option.OptionNumber.SecureNumber) {
		case 0:
			compare_boxno = 0x0001;
			break;
		case 1:
			compare_boxno = 0x0002;
			break;
		case 2:
			compare_boxno = 0x0004;
			break;
		case 3:
			compare_boxno = 0x0008;
			break;
		case 4:
			compare_boxno = 0x0010;
			break;
		case 5:
			compare_boxno = 0x0020;
			break;
		case 6:
			compare_boxno = 0x0040;
			break;
		case 7:
			compare_boxno = 0x0080;
			break;
		case 8:
			compare_boxno = 0x0100;
			break;
		case 9:
			compare_boxno = 0x0200;
			break;
		case 10:
			compare_boxno = 0x0400;
			break;
	}
#endif
	partner_boxno = MDM_ModemBuffer[NonStdFrmPos][pos+1];
	partner_boxno = partner_boxno << 8;
	partner_boxno |= MDM_ModemBuffer[NonStdFrmPos][pos];
	if (compare_boxno != (partner_boxno & compare_boxno)) {		/**	���M���Ŏw���������C���{�b�N�XNO�ɊY������Ǝ��t���[���̃r�b�g��ON���Ă���	*/
		/**	�e�W���M���Ȃ�	*/
		return(NO);
	}
	/**	�e�W���M��������	*/
	return(YES);
}

#if(PRO_TSI_RELAY_COM == ENABLE)
/*************************************************************************
	module		:[�s�r�h�ɂ�钆�X�p�w����M]
	function	:[
		TSI_Relay == 1�̂Ƃ��AStandardID[]�� �ɃX�y�[�X�������Ă���B
		�O���[�vNO�̋�؂�Ƃ��邽�߁B
		1.���X�p�R�}���h 000-
		2.1���̃O���[�v�m�n�́A�P���Ŏw������B
		3.�O���[�v�m�n�Ԃ́A'-'�B
		4.���p�w���z�M�̈���p��ٰ��NO.�̎��́A'--'�B(�ő�10����)
		5.'--'�̌�ɑ�����ٰ��NO.�́A���@�ɒ��p�w�������ٰ��NO.�B
		6.000-�̒����'--'��������G���[�B
		7.'--'�̒����NULL��������װ�B
		8.TSI���ɂQ��'--'����������װ�B
		9.�Ō�́ANULL�B
	]
	return		:[�������O���[�v�m�n���Z�b�g�����Ƃ�:�P�[�e�e�e�e�e�e�e�e
				  �O���[�v�m�n���Z�b�g�ł��Ȃ������Ƃ��F�O
	]
	common		:[]
	condition	:[]
	comment		:[
		1.���p�w���z�M�̈���̂��߂̸�ٰ��NO.�̎�荞�ǉ��B950929 Y.Suzuki
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/02/14]
	author		:[��؈��]
*************************************************************************/
UDWORD GetGroupNoFromStdID(UBYTE pos)
{
	/* pos �́AStandardID[]���߼޼�� */
	/* UBYTE pos,h,k; 950929 */
	UBYTE h,k;
	UDWORD g,gtmp;
	UBYTE reserve_address;/* ���p�w���z�M�̈��Đ�w�� '--' ���o�p 950929 */

	/*--------------------------------------------------------------------------------*/
	/* PC �� FAX BORD ���璆�X�p�w������� TSI StandardID[] ����O���[�vNO�����o���B*/
	/*--------------------------------------------------------------------------------*/
	h = 0;
	g = 0;
	gtmp = 0;
	k = 0;
	reserve_address = 0;
	if(pos == 0){
		pos = 4;
	}
	while(pos) {
		gtmp = 1;
		h = StandardID[pos++];
		if(((h < '0') || (h > '9')) && !reserve_address) {/* 000-,-,--�̎��������ȊO */
			return(0);/* �װ */
		}
		else {
			if((reserve_address == 1) && (h == ' ')) {/* TSI ����'--'���o */
				if(g && !TSI_Ptr) {/* '--'���o�܂łɸ�ٰ��NO.�̌��o���� == ���p�w���z�M���Đ� */
					TSI_Ptr = pos;
					return(g);
				}
				else{/* 000�̒����'--'�A�Q�x�ڂ�'--'�����o */
					return(0);
				}
			}
			k = StandardID[pos++];
			switch(k) {
			case NULL:
			case ' ':
				/* 1���w�� */
				if(h == '0') {/* �S�O���[�v�m�n�w�� */
					g = 0xFFFFFFFF;
					pos = 0;
				}
				else {
					h &= 0xCF;
					while(h) {
						h--;
						if(h > 0) {
							gtmp <<= 1;
						}
					}
					g |= gtmp;
				}
				if(k == NULL) {/* �O���[�vNO�����I�� */
					pos = 0;
				}
				else {
					reserve_address = 1;/* '--'���o�p */
				}
				break;
			default:/* 2���ŕ\�킳���O���[�vNO */
				if(((k < '0') || (k > '9')) || ((StandardID[pos] != ' ') && (StandardID[pos] != NULL))) {
					/* 2���ڂ������łȂ��܂��́A�R���ڂ����� */
					return(0);
				}
				if(StandardID[pos] == NULL) {/* �Ō�̃O���[�vNO */
					pos = 0;
				}
				else {/* ' ' ���X�L�b�v */
					reserve_address = 1;/* '--'���o�p */
					pos++;
				}
				h &= 0xCF;
				k &= 0xCF;
				h = (UBYTE)((10 * h) + k);
				if( h <= 32) {/* 33 �Ԉȏ�̃O���[�vNO�́A���肦�Ȃ��B*/
					while(h) {
						h--;
						if(h > 0) {
							gtmp <<= 1;
						}
					}
					g |= gtmp;
				}
				else {
					return(0);
				}
			}
		}
	}
	return(g);
}
#endif


#if (PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
/*************************************************************************
	module		:[���p�z�M�R�}���h�`�F�b�N(��)]
	function	:[
		�s�B�ʒm�ݒ�ON�̏ꍇ�A���p�z�M�R�}���h�́A�ő�X�܂łƂ���B
		1.�R�}���h�t�@�C���̋󂫏�Ԃ𒲂ׂ�B
		2.�R�}���h�t�@�C�����t���Ȃ�A�e�R�}���h�t�@�C���̃A�C�e���𒲂ׂ�B
		3.���p�z�M�ȊO�̃R�}���h���P�ł������OK
	]
	return		:[
			�R�}���h�t�@�C���󂫂���:YES �^ ���ׂẴR�}���h�����p�z�M�ł���:NO
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/02/09]
	author		:[��؈��]
*************************************************************************/
UBYTE CountRelayedTxCommand(void)
{
	UBYTE i;
	UBYTE empty_count;

	i = 0;
	empty_count = 0;
	/**	�󂫃R�}���h�t�@�C��������΃R�}���h�t�@�C���֓W�J����	*/
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if (SYB_CommandFile[i].Status == SYS_CMD_EMPTY) {
			empty_count++;
		}
	}
	if(empty_count >= 2) {	/**	�R�}���h�o�^�W�ȉ�	*/
		return(YES);
	}
	empty_count = 0;
	/** �R�}���h�t�@�C���t�� */
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if((SYB_CommandFile[i].Option.Item) != SYS_RELAYED_TX) {/** ���p�z�M�R�}���h�X�ȉ� */
			empty_count++;
		}
	}
	if(empty_count >= 2) {	/**	���p�z�M�R�}���h�W�ȉ�	*/
		return(YES);
	}
	/** ���p�z�M�R�}���h�P�O�� */
	return(NO);
}
#endif


/*************************************************************************
	module		:[���p�z�M��M����]
	function	:[
		1.���p�z�M�w����M�\�Ȃ��M�t�@�C���̃Z�b�g�A�b�v�܂ōs��
		2.�w�����ꂽ�O���[�vNO���S�ēo�^����Ă��Ȃ��ꍇ�͕��ʂ̎�M
		3.�w�����ꂽ�O���[�vNO�̓��ЂƂł��o�^����Ă�����OK
		4.�R�}���h�t�@�C�����t���̏ꍇ�@��M���Ȃ�
		5.��������M�t�@�C���̎w��
		6.���@�R�}���h�t�@�C���ւ̓W�J
	]
	return		:[�n�j--RELAY_RX�^��M�̂ݍs��--YES�^�m�f--NO]
	common		:[
					MDM_ModemBuffer
					NonStdFrmPos
					SYB_OnetouchDial.Setting.DialNumber.:Group
					SpeedMaxNumberRomDip
					SYB_SpeedDial.:Group
					SYB_CommandFile.:Status
					RelayedTxDocumentStatus
					RelayedCommandNo
					SYB_CommandFile.DialNumber.:Item
					SYB_CommandFile.DialNumber.FaxNumber.:Group
					SYB_CommandFile.Option.Item
					SYB_CommandFile.Option.OptionNumber.:RelaySourceID
					SYB_TTI_Buffer
					SYB_CommandFile.Option.:ConfirmationReport
					SYB_CommandFile.:DepartmentCode
					SYB_CommandFile.:TitleMessage
					RxMemoryFileItem
					RxMemoryFileNO
					SYS_RxMemoryFilePage
					SYS_RxTotalPage
					SYS_RxPrintFileItem
					SYS_RxPrintFileNo
					SYS_RxPrintFilePage
					SYS_RxTotalPage
					SYB_MemoryRxPrint.JournalPoint->:Number
					SYB_MemoryRxPrint.JournalPoint->:RemoteID_TTI
					SYB_MemoryRxPrint.JournalPoint->:Mode
					SYB_MemoryRxPrint.JournalPoint->:StartTime
					SYB_MemoryRxPrint.JournalPoint->:TotalTime
					SYB_MemoryRxPrint.JournalPoint->:DepartmentCode
					SYB_MemoryRxPrint.JournalPoint->:Type
					SYB_MemoryRxPrint.JournalPoint->:Result
					SYB_MemoryRxPrint.JournalPoint->:Kind
					SYB_MemoryRxPrint.JournalPoint->:Option
	]
	condition	:[]
	comment		:[�C������
					1.94/9/9 ��s�o�b�t�@�̃X�e�[�^�X�̃Z�b�g����߂�
					2.94/9/16 ��L�ύX�ɂ��o������ Warning �����̂���
					3.94/11/11 ���X�p�̏����ǉ�
					4.94/12/26 ���p�w����M���A�Z�k�E�����^�b�`�̓o�^��Ԃ��m�F
					5.95/2/1 TSI���g�p�������X�p�w���ɑΉ��i���j
					6.95/9/29 TSI���g�p�������X�p�w���ɑΉ� �d�l�ǉ��i���j
					  ���p�w���z�M������ٰ��NO.�Ŏw�肷��B
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[��� ���]
*************************************************************************/
UBYTE SetUpRelayBroadCastRx(WORD pos)/*	���f���o�b�t�@�̃|�W�V����	*/
{
	struct	SYS_CommandData_t	 *comp;/* 11.Jun'94 */
	/*struct SYS_MemoryRxPrintData far *MemoryRxPrintPoint;* 11.Jun'94 */
	UDWORD g;
	UDWORD gtmp;
	BYTE i;					/* char !! */
	UBYTE j;
	UBYTE ok_flag;
 #if(PRO_RELAYED_REPORT == ENABLE)
	UBYTE relayed_report;	/* ���p�z�M�s�B�ʒm�ݒ�p 9.Feb'95 Y.Suzuki */
	relayed_report = 0;
 #endif

	g = 0;
	gtmp = 0;
	i = 0;
	j = 0;
	ok_flag = NO;

 #if(PRO_RELAYED_REPORT == ENABLE)
	if(CHK_RelayedTxReport() && pos != 0) {/* TSI �ɂ�钆�X�p�w���ł͕s�B�ʒm�𑗂�Ȃ��B���p�z�M�s�B�ʒm�ݒ�Z�b�g 9.Feb'95 Y.Suzuki */
		relayed_report = YES;
	}
 #endif
	/**	���p�w�����ꂽ�O���[�vNO�̊l�� �O���[�v�m�n.�R�Q�|���U�S�Ή��̏ꍇ�ύX�v	*/
#if(PRO_TSI_RELAY_COM == ENABLE)
	/*--------------------------------------------------*/
	/*	  TSI�ɂ�钆�X�p�w�� 14.Feb'95 Y.Suzuki		*/
	/*--------------------------------------------------*/
	if((pos == 0) && (TSI_Relay == 1)) {
		/** ���p�w���z�M�̈��� �l�� */
		g = GetGroupNoFromStdID(0);/* �����ǉ� 950929 Y.S */
		if(g == 0) {/** TSI ����O���[�v�m�n���o���Ȃ����� */
			return(TSI_NG);
		}
	}
	else {
#endif
	for (i = 3; i >= 0; i--) {
		g = g | (UDWORD)MDM_ModemBuffer[NonStdFrmPos][pos + i];
		if (i != 0) {
			g = g << 8;
		}
	}
#if(PRO_TSI_RELAY_COM == ENABLE)
	}
#endif
	/*	���p�w�����ꂽ�O���[�vNO�������^�b�`�ɓo�^����Ă��邩�@��Q�����^�b�`�A�Z�k�̑Ή� �K�v �����A���x���_�[	*/
	for (j = 0; j < SYS_ONETOUCH_MAX; j++) {/**	�W�������^�b�`�_�C����	*/
		if((SYB_OnetouchDial[j].Dial[0] & 0xF0) != 0xF0) {		/* '96.02.22 BY T.Y */
			if (g & (SYB_OnetouchDial[j].Group)) {
				ok_flag = YES;/**	�O���[�v�o�^����Ă���	*/
				break;
			}
		}
	}
	if (ok_flag != YES) {		/**	���p�w�����ꂽ�O���[�vNO�������^�b�`�ɓo�^����Ă��Ȃ�	*/
		for (j = 0; j < SYS_SPEED_DIAL_MAX; j++) {/**	�W���Z�k�_�C����	*/
			if((SYB_SpeedDial[j].Dial[0] & 0xF0) != 0xF0) {/* 26.Dec'94 */
				if (g & (SYB_SpeedDial[j].Group)) {
					ok_flag = YES;/**	�O���[�v�o�^����Ă���	*/
					break;
				}
			}
		}
	}
	if (ok_flag == NO) {	/**	���p�w�����ꂽ�O���[�vNO���Z�k������^�b�`�ɓo�^����Ă��Ȃ�	*/
 #if(PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
								   /*----------------------------------*/
		if(relayed_report == YES) {/** ���p�z�M�s�B�ʒm��ON �Ȃ�G���[ */
								   /*----------------------------------*/
			return(NO);
		}
 #endif
		/**	���^�[��YES	*//*	��������M�̂ݍs��	*/
		return(YES);
	}
	/**	�󂫃R�}���h�t�@�C��������΃R�}���h�t�@�C���֓W�J����	*/
	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
		if (SYB_CommandFile[i].Status == SYS_CMD_EMPTY) {		/**	�󂫃R�}���h�t�@�C������	*/
#if(0) /* RelayedTxDocumentStatus[i] ���g�p 21.Feb'95 Y.Suzuki */
//			if (RelayedTxDocumentStatus[i] == NO_RELAYED_DOC) {/**	�z�M���e�Ȃ�	*/
//				SYB_CommandFile[i].Status = SYS_CMD_SETTING;
//				RelayedCommandNo = i;
//				comp = &SYB_CommandFile[RelayedCommandNo];
//				break;
//			}
#endif
			SYB_CommandFile[i].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[i] = SYS_CMD_SETTING;
#endif
			RelayedCommandNo = i;
			comp = &SYB_CommandFile[RelayedCommandNo];
			break;
		}
	}
	if (RelayedCommandNo == 0xFF) {	/*	������̧�قȂ� ������װ�ŉ���f	*/
		return (NO);
	}
	/**	�v�����g�p�o�b�t�@�Z�b�g	*/
	if (CMN_CheckMemoryReceiveEnable() == TRUE) {
		/**	�󂫂�����΁A��������M	*/
		SYS_RxPrintFileItem = SYS_MEM_RX_FILE;/*	�ʏ�̃�������M	*/
		SYS_RxPrintFileNo = SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage =  SYS_RxTotalPage + 1;
		/*--------- �����ł́A�Z�b�g���Ȃ��BMAN_MAIN.C �ɂăZ�b�g����B
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
		MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
		-------------------------------------------------------------*/
	}
	else {/**	�󂫂��Ȃ���΁A��M���Ȃ�	*/
		return(NO);
	}
 #if(PRO_RELAYED_REPORT == ENABLE)/* 9.Feb'95 Y.Suzuki */
	if(relayed_report == YES) {/** ���p�z�M�s�B�ʒm	 */
		if(CountRelayedTxCommand() == NO) {/** ���p�z�M�R�}���h�́A�X�܂� */
			return(NO);
		}
		/*------------------------------------------------------*/
		/**	�R�}���h�t�@�C���̒��p��ID�o�b�t�@�ɕW��ID���Z�b�g	*/
		/*------------------------------------------------------*/
		if(SetTransmitStationID() == NO) {/** TSI �s�ǃG���[ */
			return(TSI_NG);
		}
	}
 #endif
#if 0	/* POPLAR�ύX */
//	for (i = 0; i < SYS_COM_DIAL_MAX; i++) {/* Item Clear 95/03/28 Y.Suzuki	*/
//		comp->DialNumber[i].Item = SYS_EMPTY_DIAL;
//	}
#endif
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/* 1997/02/12  By T.Yamaguchi */
#if 0 /* POPLAR */
//	if (g == 0xFFFFFFFF) {		/**	�S�O���[�vNO���w�����ꂽ�i�O���[�v�O�w��j	*/
//		/**	�R�}���h�t�@�C���̃_�C�����A�C�e���ɃO���[�v���Z�b�g	*/
//		comp->DialNumber[0].Item = SYS_GROUP_DIAL;
//		/**	�R�}���h�t�@�C���̃_�C�����O���[�vNO�ɂO���Z�b�g	*/
//		comp->DialNumber[0].FaxNumber.Group = 0;
//	}
//	else {
//		j = 1;			/* j == GroupNo */
//		gtmp = 0x00000001;
//		for (i = 0; i < SYS_COM_DIAL_MAX; i++) {/* �P�ʐM������ő�P�O���Đ�	*/
//			ok_flag = NO;
//			/*comp->DialNumber[i].Item = SYS_EMPTY_DIAL; By H.Y 1994/11/30 */
//			while ((j <= 32) && (ok_flag == NO)){
//				if (g & gtmp) {
//					/**	�R�}���h�t�@�C���̃_�C�����A�C�e���ɃO���[�v���Z�b�g	*/
//					comp->DialNumber[i].Item = SYS_GROUP_DIAL;
//					/**	�R�}���h�t�@�C���̃_�C�����O���[�vNO�Ɏw�����ꂽ�O���[�v�S�ăZ�b�g	*/
//					comp->DialNumber[i].FaxNumber.Group = j;
//					ok_flag = YES;
//				}
//				gtmp = gtmp << 1;
//				j++;
//			}
//		}
//	}
#endif /* POPLAR */
	comp->DialNumber.Group = g;

#if(PRO_TSI_RELAY_COM == ENABLE)/*			950929 Y.Suzuki		*/
	/* ���p�w���z�M�����ٰ��NO.�ƒ��p�z�M��ٰ��NO.���قȂ�ꍇ */
	/* MML�̒��X�p�ł́A�Q�̸�ٰ��NO.�́A���ʂ������B			*/
	/* ���p�z�M��ٰ��NO.���l��									*/
	if(TSI_Ptr) {
		/* TSI ����'--'�ȍ~�̸�ٰ��NO.�̊l�� */
		g = GetGroupNoFromStdID(TSI_Ptr);
		if(g == 0) {/** TSI ����O���[�v�m�n���o���Ȃ����� */
			return(TSI_NG);
		}
	}
	/**	�R�}���h�t�@�C���A�C�e���ɒ��p���M���Z�b�g	*/
	/* �����p����̏ꍇ Item:SYS_MEMORY_RELAY_BROADCAST	  OptionNumber.RelayGroupNumber ��Group NO. ��� */
	if(CHK_RelayedRelayTxON() || ((TSI_Relay == 1) && (pos == 0))) {
		/* TSI �ɂ�钆�X�p�w���́A��ɒ��X�p�w����M����B14.Feb'95 Y.Suzuki */
		comp->Option.Item = SYS_MEMORY_RELAY_BROADCAST;
		comp->Option.OptionNumber.RelayGroupNumber = g;
	}
#else
	if(CHK_RelayedRelayTxON()) {
		comp->Option.Item = SYS_MEMORY_RELAY_BROADCAST;
		comp->Option.OptionNumber.RelayGroupNumber = g;
	}
#endif
	else {
		comp->Option.Item = SYS_RELAYED_TX;
	}
	/**	�R�}���h�t�@�C���̎�̏؃X�e�[�^�X�A����Ǘ��R�[�h�A�^�C�g�����b�Z�[�W���N���A	*/
	comp->Option.ConfirmationReport = NO;
  #if (PRO_DEPARTMENT == ENABLE)
	comp->DepartmentCode = 0xFFFF;	/* 96/08/14 By T.Yamaguchi */
/*	comp->DepartmentCode = NO;	*/
  #endif
	comp->TitleMessage = 0xFF;/* FF Clear !! 21.Oct'94 */

	comp->Ability = NO;		/* Clear 1996/09/12 T.Yamaguchi ANZU�ł͖��g�p�����N���A���Ă��� */

#if (PRO_PIN_ACCESS == ENABLE)
	/*
	** �o�h�m�̃��[�h���P�̎��A�����^�b�`�^�Z�k�ɓo�^����Ă���ԍ��𑗏o�\�ł����A
	** �o�h�m�̃��[�h���Q�̎��́A���Ă���PIN�ԍ����s��̂��߂n�e�e���� 1998/01/21  By T.Yamaguchi
	*/
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp->PIN_AccessMode = PIN_ACCESS_MODE1;
	}
	else {
		comp->PIN_AccessMode = 0;
	}
#endif

	/**	��������M�t�@�C���̎w��	*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;				  /* Item�� MEMORY_TX_DOC�Ƃ��� */
	SYS_RxMemoryFileNo = (UWORD)RelayedCommandNo;/* No�ͺ����No�ɑΉ� */
	SYS_RxMemoryFilePage = (UWORD)SYS_RxTotalPage + 1;
	/**	���^�[��RELAY_RX	*//*	���p�w������	*/
#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif
	return (SYS_RELAY_RX);
}


/*************************************************************************
	module		:[�����|�[�����O���M���������t�@�C���l��]
	function	:[
		1.�c�s�b��茟���|�[�����O�t�@�C��NO���o��
		2.�t�@�C���̃y�[�W���ƃt�@�C��NO�𑗐M�������t�@�C���ɃZ�b�g����
	]
	return		:[
				�t�@�C���l��--�Ǝ��t���[���i�c�s�b�j�̌����|�[�����O
				.			  �t�@�C���w��̍Ō�̃|�W�V����
				�t�@�C���Ȃ�--�O
	]
	common		:[
				MDM_ModemBuffer
				NonStdFrmPos
				TxMemoryFileNo
				PollingTxFilePage
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/28]
	author		:[��� ���]
*************************************************************************/
WORD GetDatabasePollingFileNumber(WORD pos)/*	���f���o�b�t�@�̃|�C���^	*/
{
	UWORD  page;
	UBYTE i;
	UBYTE mdm_data;
	UBYTE first_flag;
	UBYTE ok_flag;

	i = 0;
	mdm_data = 0;
	first_flag = NO;
	ok_flag = NO;
/*	for (i = 0; i < (SYS_TX_MEMORY_FILE_NO_MAX - 1); pos+=2) {/@@ ���o����t�@�C��NO�̐��A�ő�P�O�� */
	for (i = 0; i < (SYS_DATA_BASE_MAX - 1); pos+=2) {/** ���o����t�@�C��NO�̐��A�ő�P�O�� */
		/**	�����|�[�����O�t�@�C��NO���o��	*/
		mdm_data = MDM_ModemBuffer[NonStdFrmPos][pos];
		if ((i == 0) && (first_flag == NO)) {
			page = MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, (UWORD)mdm_data, MEM_IGNORE_BOX_NUMBER);
			first_flag = YES;
			if (page != MEM_NO_INDEX) {
				ok_flag = YES;
				/**	���M�������t�@�C��NO�Ɍ����|�[�����O�t�@�C��NO�Z�b�g	*/
				TxMemoryFileNo[i] = mdm_data;
				/**	���M�������t�@�C���y�[�W�Ƀy�[�W���Z�b�g	*/
				PollingTxFilePage[i] = page;
				i++;
			}
		}
		else {
			if (MDM_ModemBuffer[NonStdFrmPos][pos - 1] & BitNo8) {	/**	�p���r�b�g�n�m	*/
				/**	���̌����|�[�����O�t�@�C��NO���o��	*/
				page = MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, (UWORD)mdm_data, MEM_IGNORE_BOX_NUMBER);
				if (page != MEM_NO_INDEX) {
					ok_flag = YES;
					/**	���M�������t�@�C��NO�Ɍ����|�[�����O�t�@�C��NO�Z�b�g	*/
					TxMemoryFileNo[i] = mdm_data;
					/**	���M�������t�@�C���y�[�W�Ƀy�[�W���Z�b�g	*/
					PollingTxFilePage[i] = page;
					i++;
				}
			}
			else {
				break;
			}
		}
	}
	/**	���M�������t�@�C���̎��̃o�b�t�@��0xFFFF������	*/
	TxMemoryFileNo[i] = 0xFFFF;
	PollingTxFilePage[i] = 0xFFFF;

	if (ok_flag == NO) {	/**	�w�肳�ꂽ�t�@�C���̃y�[�W�����S�ĂO�ȉ�	*/
		pos = 1;/**	���^�[���O	*/
	}
	/**	���^�[�����f���o�b�t�@�̃|�W�V����	*/
	return (pos - 1);
}


/*************************************************************************
	module		:[�����[�g�e�`�w���o���p��M����]
	function	:[
		1.�����[�g���o���p�t�@�C���Z�b�g�A�b�v
		2.�����v�����g����̏ꍇ�A�v�����g�p�o�b�t�@�Z�b�g�A�b�v
	]
	return		:[
				YES--��������
				NO---�����v�����g����̏ꍇ�Ńv�����g�p�o�b�t�@
				.	 (��s��M�p)���t��
				]
	common		:[
				SYS_RxMemoryFileItem
				SYS_RxMemoryFileNo
				SYB_MemoryRxPrint.:Status
				SYS_RxPrintFileItem
				SYS_RxPrintFileNo
				SYS_RxPrintFilePage
				SYS_RxTotalPage
	]
	condition	:[]
	comment		:[�C������
					1.94/9/9 ��s�o�b�t�@�̃X�e�[�^�X�̃Z�b�g����߂�
					2.94/9/16 ��L�ύX�ɂ��o������ Warning �����̂���
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1994/02/17]
	author		:[��؈��]
*************************************************************************/
UBYTE SetUpRemoteFaxRx(void)
{
	/* struct SYS_MemoryRxPrintData far *MemoryRxPrintPoint;* 29.Apr'94 */
	/**	�e�W��M�̏ꍇ�́A�����[�g��M���Ȃ� 14.Apr'94	*/
	if (SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE) {
		return(YES);
	}
	/**	�����[�g���o���p�t�@�C���Z�b�g�A�b�v	*/
	SYS_RxMemoryFileItem = SYS_MEM_REMOTE_TX_FILE;
	/* SYS_RxMemoryFilePage = (MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) + 1);	*/
	SYS_RxMemoryFilePage = MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
	SYS_RxMemoryFileNo = 0;/* 0 �Œ� */
	if(SYS_RxMemoryFilePage != MEM_NO_INDEX) {/* �Y���C���f�b�N�X�Ȃ� MEM_CountTotalPage 0xFFFF */
		SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
	}
	if (RemoteFaxPRN_Flag == YES) {		/**	�����v�����g����	*/
		/**	�v�����g�p�o�b�t�@�Z�b�g	*/
		if (CMN_CheckMemoryReceiveEnable() == TRUE) {
			/**	�󂫂�����΁A��������M	*/
			SYS_RxPrintFileItem = SYS_MEM_RX_FILE;/*	�ʏ�̃�������M	*/
			SYS_RxPrintFileNo = SYB_MemoryRxPrintWritePoint;
			SYS_RxPrintFilePage =  SYS_RxTotalPage + 1;
			/*--------- �����ł́A�Z�b�g���Ȃ��BMAN_MAIN.C �ɂăZ�b�g����B
			MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
			-------------------------------------------------------------*/
	}
		else {
			SYS_RxMemoryFileItem = NULL;
			return(NO);
		}
	}
	return(YES);
}


/*************************************************************************
	module		:[�p�X�R�[�h�Z�b�g]
	function	:[
		���f���o�b�t�@�Ƀp�X�R�[�h���Z�b�g����
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[
			FrameName
			MDM_ModemBuffer
			SYB_PasscodeNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[��� ���]
*************************************************************************/
WORD SetPasscodeFrame(UBYTE FrameName,/*	NSC or NSS	*/WORD pos)
{
	UBYTE j;
	j = 0;
	/*	�T���t�����[�T�[�N���p �|�[�����O�p�X�R�[�h	*/
	if ((FrameName == NSC_F) && (CHK_UNI_SpecialPollingPasscode())) {		/**	�m�r�b�t���[���ł��\�t�g�X�C�b�`����|�[�����O�r�b�gON	*/
		/**	�p�X�R�[�h�{ 0x11 �����f���o�b�t�@�ɃZ�b�g	*/
		for(j = 0; j < 4; j++) {
			MDM_ModemBuffer[InNS][pos] = (UBYTE)(SYB_PasscodeNumber[j] + 0x11);
			pos++;
		}
	}
	else {
		/**	�p�X�R�[�h�����f���o�b�t�@�ɃZ�b�g	*/
		for(j = 0; j < 4; j++) {
			MDM_ModemBuffer[InNS][pos] = SYB_PasscodeNumber[j];
			pos++;
		}
	}
	return(pos - 1);
}


/*************************************************************************
	module		:[�e�W�t�B�[���h�f�[�^�Z�b�g]
	function	:[
		NSF �̏ꍇ:10�̃��C���{�b�N�X���P�O�r�b�g�ł���킷 �o�^�ς݂̃{�b�N�X�̓r�b�gON����
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[
					MDM_ModemBuffer
					SYB_MailBox.:Status
					SYS_CommandP->Option.OptionNumber.:SecureNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[��� ���]
*************************************************************************/
WORD SetSecureMailFieldFrame(UBYTE FrameName,/*	NSF,NSS	*/WORD pos)
{
	UBYTE j;
	UBYTE i;
	j = 0;

	MDM_ModemBuffer[InNS][pos] = BIT_CLEAR;
	MDM_ModemBuffer[InNS][pos + 1] = BIT_CLEAR;

	switch (FrameName) {		/**	�t���[����	*/
		case NSF_F:	/**	NSF	*/
			/**	���C���{�b�N�X���o�^����Ă���΁A�Ή�����r�b�g��ON����	*/
			i = 0;
			for (j = 0x01; i < 8; i++, j *= 2) {
				if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET) ||
					/* �����[�h�ύX�����Ǝ��̃y�[�W�ŃR���p�`�G���[�ƂȂ� �e�W̨���ނȂ��ɂȂ� 96/1/11 �ǉ� Y.S */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) ||
					(SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING) ||	/* add 1997/10/18  By T.Yamaguchi */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)) {
					MDM_ModemBuffer[InNS][pos] |= j;
				}
			}
			for (j = 0x01; i < SYS_MAILBOX_MAX; i++, j *= 2) {
				if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET) ||
					/* �����[�h�ύX�����Ǝ��̃y�[�W�ŃR���p�`�G���[�ƂȂ� �e�W̨���ނȂ��ɂȂ� 96/1/11 �ǉ� Y.S */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) ||
					(SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING) ||	/* add 1997/10/18  By T.Yamaguchi */
					(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)) {
					MDM_ModemBuffer[InNS][pos + 1] |= j;
				}
			}
			break;
		case NSS_F:	/**	NSS	*/
			/**	�R�}���h�ɃZ�b�g����Ă���e�WNO�ɑΉ�����r�b�g��ON����	*/
			switch (CommandP -> Option.OptionNumber.SecureNumber) {
				case 0:
					MDM_ModemBuffer[InNS][pos] |= 0x01;
					break;
				case 1:
					MDM_ModemBuffer[InNS][pos] |= 0x02;
					break;
				case 2:
					MDM_ModemBuffer[InNS][pos] |= 0x04;
					break;
				case 3:
					MDM_ModemBuffer[InNS][pos] |= 0x08;
					break;
				case 4:
					MDM_ModemBuffer[InNS][pos] |= 0x10;
					break;
				case 5:
					MDM_ModemBuffer[InNS][pos] |= 0x20;
					break;
				case 6:
					MDM_ModemBuffer[InNS][pos] |= 0x40;
					break;
				case 7:
					MDM_ModemBuffer[InNS][pos] |= 0x80;
					break;
				case 8:
					MDM_ModemBuffer[InNS][pos + 1] |= 0x01;
					break;
				case 9:
					MDM_ModemBuffer[InNS][pos + 1] |= 0x02;
					break;
				}
				break;
		case NSC_F:	/**	NSC	*/
		default:
			break;
	}
	/**	���^�[�����f���o�b�t�@�̃|�C���^	*/
	return (pos + 1);
}

/*************************************************************************
	module		:[�����|�[�����O�t�B�[���h�Z�b�g]
	function	:[
		NSC�̌����|�[�����O�t�B�[���h(�t�@�C��NO.�O�|�|�V�e�e�e(32767))��
		.���f���o�b�t�@�ɃZ�b�g���� ���̃t�B�[���h�́A�ʏ� �g���r�b�g
		.(1�r�b�g)�{�t�@�C��NO(7�r�b�g)�̂P�o�C�g�ł���킳��� �g���r�b�g
		.���P�Ȃ玟�̃o�C�g�������|�[�����O�t�B�[���h�ƂȂ�
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[
					MDM_ModemBuffer
					CommandP->Option.OptionNumber.:DatabaseNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[��� ���]
*************************************************************************/
WORD SetDatabasePollingDataFrame(WORD pos)/*	���f���o�b�t�@�̃|�C���^	*/
{
	UWORD n;	/* WORD -> UWORD�ɕύX 0xFFFF�Ɣ�r���鎞�ɁA0xFFFFFFFF�Ɣ�r���Ă��邽�߂��������Ȃ� 1997/09/16  By T.Yamaguchi */
	UBYTE nh;
	UBYTE nl;
	UBYTE i;

	n = 0;
	nh = 0;
	nl = 0;
	i = 0;

	for (i = 0; i < SYS_DATA_BASE_MAX; i++) {	/*	0 <= �t�@�C���� < 11	*/
		n = (CommandP -> Option.OptionNumber.DatabaseNumber[i]);
		if (n != 0xFFFF) {		/**	�R�}���h�t�@�C���ɃZ�b�g���ꂽ�t�@�C��NO�� FFFF �ł͂Ȃ�	*/
			/**	���f���o�b�t�@�ɃZ�b�g	*/
			nl = (UBYTE)(n & 0x00FF);
			nh = (UBYTE)((n & 0xEF00) >> 8);
			MDM_ModemBuffer[InNS][pos] = nl;
			pos++;
			MDM_ModemBuffer[InNS][pos] = nh;
			/**	�g���r�b�g��ON����	*/
			MDM_ModemBuffer[InNS][pos] |= BitNo8;
			pos++;
		}
		else {
			/**	ON�����g���r�b�g��OFF����	*/
			pos--;
			MDM_ModemBuffer[InNS][pos] &= ~BitNo8;
			break;
		}
	}
	/**	���^�[�����f���o�b�t�@�̃|�C���^	*/
	return (pos);
}


/*************************************************************************
	module		:[���p����̃O���[�v�Z�b�g]
	function	:[
		NSS�̒��p����t�B�[���h�ɃO���[�vNO���Z�b�g����
	]
	return		:[���f���o�b�t�@�̃|�C���^]
	common		:[
					MDM_ModemBuffer
					CommandP->Option.OptionNumber.:RelayGroupNumber
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(�����}�C�R��)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[��� ���]
*************************************************************************/
WORD SetRelayedBroadcastGroupFrame(WORD pos)/*	���f���o�b�t�@�̃|�C���^	*/
{
	UBYTE i;
	UBYTE j;
	UBYTE k;
	UBYTE n;
	UBYTE dummy_group;
	UDWORD g;
	UDWORD group;

	i = 0;
	j = 0;
	k = 0x01;
	n = 0;
	dummy_group = 0;
	g = 0x0001;
	group = 0;

	/**	���f���o�b�t�@�̃N���A	*/
	for(i = 0; i < 4; i++) {
		MDM_ModemBuffer[InNS][pos + i] = BIT_CLEAR;
	}

	group = CommandP->Option.OptionNumber.RelayGroupNumber;
	for(j = 0, i = 0; i < 4; i++) {	/*	�S�񃋁[�v	�R�Q�o�C�g�`�F�b�N	*/
		k = 0x01;
		dummy_group = 0;
		for(n = 0; n < 8; j++,n++) {/*	�W�񃋁[�v	�P�o�C�g�`�F�b�N	*/
			/**	�O���[�vNO�̃r�b�g�`�F�b�N	*/
			if (group & ((UDWORD)(g << j))) {
				dummy_group |= (UBYTE)(k << n);
			}
		}
		/**	�P�o�C�g���̃O���[�vNO�Z�b�g	*/
		MDM_ModemBuffer[InNS][pos + i] = dummy_group;
	}
	/**	���^�[�����f���o�b�t�@�̃|�C���^	*/
	return(pos + 3);
}


/*************************************************************************
	module		:[�Í�����M����]
	function	:[
		1.�Í�����M�\�Ȃ��M�t�@�C���̃Z�b�g�A�b�v���s��
		2.��Í�����M�a�n�w������
		3.���@�Ɏw�肳�ꂽ���C���{�b�N�X�����݂���
		4.���C���{�b�N�X�̎�M���
		5.
	]
	return		:[�n�j--YES�^�m�f--NO]
	common		:[
	]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/06/18]
	author		:[�R�� �N��]
*************************************************************************/
UBYTE SetUpCipherRx(void)
{
#if (PRO_CIPHER == ENABLE)
	UBYTE i;

	/* ��A�Í�����M�ԍ��̊l�� */
	CMN_DisableInterrupt();
	for (i = 0; i < SYS_CIPHERBOX_MAX; i++) {
		if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_NO) {
			break;
		}
	}
	if (i == SYS_CIPHERBOX_MAX) {	/* �S�Ă�BOX���g�p���A��M�ł��Ȃ� */
		FaxCompatibleErrorCode = NO_EMPTY_CIPHERBOX_ERROR;/* �Í�����MBOX�t���G���[	*/;
		CMN_EnableInterrupt();
		return(NO);
	}

	/* �o�b�N�A�b�v�̂��� */
	SYB_CipherBox[i].Status = SYS_CIPHERBOX_RECEIVING;
	CMN_EnableInterrupt();

	/**	��������M�p�A�C�e���Z�b�g�i�Í�����M���e�j	*/
	SYS_RxMemoryFileItem = SYS_MEM_CIPHER_RX_FILE;
	/**	��������M�t�@�C��NO.�Ɏ�MNO.	*/
	SYS_RxMemoryFileNo = (UWORD)i;
	SYS_RxMemoryFilePage = 1;
	SYS_RxMemoryFileBoxNumber = MEM_IGNORE_BOX_NUMBER;

	return(YES);
#else
	return(NO);
#endif
}

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* ���[�v�@�\ By H.Hirao 1998/08/31 */
/*************************************************************************
	module		:[���[�v��M����]
	function	:[1.���[�v�@�\�����ԓ����ǂ����̃`�F�b�N �S�Ď��ԊO�̏ꍇ���������Ƀ��^�[��
				  2.�R�}���h�t�@�C���̋󂫂����� �󂫂������ꍇ���������Ƀ��^�[��
				  3.���[�v�]�������M���e�����[�J���̃v�����^�Ńv�����g���邩�ǂ����̃`�F�b�N
				  4.�R�}���h�t�@�C���̃����o�o�^�i�����^�b�`�_�C�����A�Z�k�_�C�����A�O���[�v���o�^�j
				  5.��������M�t�@�C���A�C�e������M�t�@�C�����瑗�M�t�@�C���ɕύX
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[�L���ȃ��[�v�@�\�̐ݒ�̒��̓����v�����g�n�m���D�悳���
				  RxOriginalModeCheck()����R�[�������
	]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1998/08/31]
	author		:[���� �p�T]
*************************************************************************/
UBYTE SetUpWarpRx(void)
{
	struct	SYS_CommandData_t	 *comp;
	struct SYS_NumberDisplayTable *table;
	BYTE	is_warp_enable[SYS_WARP_MAX],
/*			is_nd_warp_enable[SYS_ND_MAX],*/	/* 1998/10/16 By M.Kuwahara */
			is_nd_warp_enable,
			warp_no,
/*			nd_warp_no,*/	/* 1998/10/16 By M.Kuwahara */
			command_no,
			exec_no,		/* added by H.Hirao 1999/01/12 */
			i,				/* added by H.Hirao 1999/01/12 */
			is_print;

	is_print	= 0;	/* 1998/10/07 By M.Kuwahara */
	exec_no		= 0;	/* added by H.Hirao 1999/01/12 */
	/*--------------------------------------------------*/
	/* ���[�v�@�\���L�������e���󎚂��邩�ۂ��̃`�F�b�N */
	/*--------------------------------------------------*/
	CMN_DisableInterrupt();	/* ���荞�݋֎~ */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
		if (!CHK_WarpFunctionON()) {
			is_warp_enable[warp_no] = FALSE;
			continue;
		}
#endif
		is_warp_enable[warp_no] = CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_WarpFile[warp_no], FaxComStartTime);
		if (is_warp_enable[warp_no]) {
			is_print |= CMN_CheckWarpPrint(SYB_WarpFile[warp_no].Option);
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	is_nd_warp_enable = FALSE;
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL && CHK_ND_WarpON()) {	/* ���ް�ި���ڲ���M�̎� */
 #else
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL) {	/* ���ް�ި���ڲ���M�̎� */
 #endif
		/** �i���o�[�f�B�X�v���C���M�ԍ����A�o�^����Ă��邩�̃`�F�b�N 	1998/10/16 By M.Kuwahara */
		/** ���������ԍ����o�^����Ă��Ă��A��Ԏn�߂Ɍ��o���ꂽ���̂������Z�b�g���� */
		table = CMN_ND_FindNdTableByPhoneNumber( SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial,
												 (UBYTE)CMN_StringLength(SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial));
		if (table != NULL) {
			/** �����ŁA���ݎ�M���̃i���o�[�f�B�X�v���C�Ɠo�^����Ă���i���o�[�f�B�X�v���C�̔�r������ */
			is_nd_warp_enable = 
						CMN_CheckWarpRange(&table->WarpData, FaxComStartTime);
			if (is_nd_warp_enable) {
				is_print |= CMN_CheckWarpPrint(table->WarpData.Option);
			}
		}
	}
 #if (0)	/* 1998/10/16 By M.Kuwahara */
//		for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//			/** �����ŁA���ݎ�M���̃i���o�[�f�B�X�v���C�Ɠo�^����Ă���i���o�[�f�B�X�v���C�̔�r������ */
//			is_nd_warp_enable[nd_warp_no] = 
//						CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_NumberDisplay[nd_warp_no].WarpData, FaxComStartTime);
//			if (is_nd_warp_enable[nd_warp_no]) {
//				is_print |= CMN_CheckWarpPrint(SYB_NumberDisplay[nd_warp_no].WarpData.Option);
//			}
//		}
//	}
 #endif
#endif
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
			break;
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
 #if (0)	/* 1998/10/16 By M.Kuwahara */
//	for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//		if (is_nd_warp_enable[nd_warp_no]) {
//			break;
//		}
//	}
//	if (warp_no == SYS_WARP_MAX && nd_warp_no == SYS_ND_MAX) {	/** ���[�v�@�\�����ׂĎ��ԊO */
 #endif
	if (warp_no == SYS_WARP_MAX && is_nd_warp_enable == FALSE) {	/** ���[�v�@�\�����ׂĎ��ԊO */
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		return (0);
	}
#else
	if (warp_no == SYS_WARP_MAX) {	/** ���[�v�@�\�����ׂĎ��ԊO */
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		return (0);
	}
#endif
	/*------------------------------*/
	/* �R�}���h�t�@�C���̋󂫂����� */
	/*------------------------------*/
	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
#endif
			RelayedCommandNo = command_no;
			comp = &SYB_CommandFile[RelayedCommandNo];
			break;
		}
	}
	if (RelayedCommandNo == 0xFF) {	/** �󂫃R�}���h���� */
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		return (0);
	}
	/*--------------------------*/
	/* ���e���v�����g���邩�ۂ� */
	/*--------------------------*/
	if (is_print) {
		SYS_RxPrintFileItem		= SYS_MEM_RX_FILE;
		SYS_RxPrintFileNo		= SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage		= SYS_RxTotalPage + 1;
/*		SYB_CommandFile[RelayedCommandNo].Ability &= ~SYS_WARP_PRINT; ���Ɉړ� 1998/10/21 H.Yoshikawa */	/* 1998/10/09 By M.Kuwahara */
	}
	else {	/* ��M���e�����p�@�Ƀv�����g����Ȃ��� 1998/09/30 By M.Kuwahara */
/*		SYB_CommandFile[RelayedCommandNo].Ability |= SYS_WARP_PRINT;	���Ɉړ� 1998/10/21 H.Yoshikawa */
	}
	/*------------------------------*/
	/* �R�}���h�t�@�C���̃����o�o�^ */
	/*------------------------------*/
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** �_�C�����f�[�^������ */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
#if (0)	/* 1998/10/06 By M.Kuwahara */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_WarpFile[warp_no].Onetouch[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Speed[0],
//							(UDWORD)SYB_WarpFile[warp_no].Group);
#else
 #if (0) /* comment by H.Hirao 1999/01/12 */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_WarpFile[warp_no].Direct[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Onetouch[0],
//							(UBYTE *)&SYB_WarpFile[warp_no].Speed[0],
//							(UDWORD)SYB_WarpFile[warp_no].Group);
 #else
			/* 
			** CMN_SetDialData()�́A�R�[�����閈�ɏ㏑������Ă��܂��܂��̂ŁA���ǍŌ�̈ꌏ�����]���ł��܂���
			** by H.Hirao 1999/01/12
			*/
			for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
				comp->DialNumber.Direct[exec_no][i] = SYB_WarpFile[warp_no].Direct[i];
			}
			for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Onetouch[i] |= SYB_WarpFile[warp_no].Onetouch[i];
			}
			for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Speed[i] |= SYB_WarpFile[warp_no].Speed[i];
			}
			comp->DialNumber.Group |= SYB_WarpFile[warp_no].Group;
			if (++exec_no >= SYS_COM_DIRECT_DIAL_MAX) {
				break;
				/* SaveReturnAddressAndJumpBegin(); */
			}
 #endif
#endif
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
 #if (0)
//	for (nd_warp_no = 0; nd_warp_no < SYS_ND_MAX; nd_warp_no++) {
//		if (is_nd_warp_enable[nd_warp_no]) {
// #if (0)	/* 1998/10/06 By M.Kuwahara */
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Onetouch[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Speed[0],
//							(UDWORD)SYB_NumberDisplay[nd_warp_no].WarpData.Group);
// #else
//			CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Direct[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Onetouch[0],
//							(UBYTE *)&SYB_NumberDisplay[nd_warp_no].WarpData.Speed[0],
//							(UDWORD)SYB_NumberDisplay[nd_warp_no].WarpData.Group);
// #endif
//		}
//	}
 #endif
	if (is_nd_warp_enable) {
 #if (0) /* comment by H.Hirao 1999/01/12 */
//		CMN_SetDialData((struct SYS_DialData_t *)&comp->DialNumber,
//						(UBYTE *)table->WarpData.Direct,
//						(UBYTE *)table->WarpData.Onetouch,
//						(UBYTE *)table->WarpData.Speed,
//						(UDWORD)table->WarpData.Group);
 #else
		/* 
		** CMN_SetDialData()�́A�R�[�����閈�ɏ㏑������Ă��܂��܂��̂ŁA���ǍŌ�̈ꌏ�����]���ł��܂���
		** by H.Hirao 1999/01/12
		*/
		if (exec_no < SYS_COM_DIRECT_DIAL_MAX) {
			for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
				comp->DialNumber.Direct[exec_no][i] = table->WarpData.Direct[i];
			}
			for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Onetouch[i] |= table->WarpData.Onetouch[i];
			}
			for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
				comp->DialNumber.Speed[i] |= table->WarpData.Speed[i];
			}
			comp->DialNumber.Group |= table->WarpData.Group;
		}
 #endif
	}
#endif
	CMN_EnableInterrupt();	/** ���荞�݋��� */
	comp -> Option.Item = SYS_RELAYED_TX;	/** TBD ���p�z�M�̃A�C�e�� */
	comp -> Option.ConfirmationReport	= NO;
	comp -> TitleMessage				= 0xFF;
/*	comp -> Ability						= NO;*/	/* 1998/10/06 By M.Kuwahara */
	if (is_print) {	/* 1998/10/21 H.Yoshikawa */
		comp -> Ability						&= ~SYS_WARP_PRINT;
	}
	else {
		comp -> Ability						|= SYS_WARP_PRINT;
	}
#if (PRO_DEPARTMENT == ENABLE)
	comp -> DepartmentCode				= 0xFFFF;
#endif
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp -> PIN_AccessMode			= PIN_ACCESS_MODE1;
	}
	else {
		comp -> PIN_AccessMode			= 0;
	}
#endif
	/*---------------------------------------------------------------------
	** Warp�̃`�F�b�N���b�Z�[�W�̂Ƃ��́A�P�y�[�W�ڂɃ`�F�b�N���b�Z�[�W�i�L�����N�^���j
	** �Q�y�[�W�ڈȍ~�ɂ́A�摜���������v�����g���܂��B
	** �v�����g����JAM�����������ꍇ�ɂ́A�ăv�����g�ł���悤�ɁA
	** �L�����N�^�����O�y�[�W�ڂƃJ�E���g����悤�ɂ��܂��B
	** ������A���������O�Ƃ��܂��B�v�����g���ɂ́A����ɑΉ������\�t�g���K�v�ł�
	** 1998/10/20 H.Yoshikawa
	*/
	if (is_print) {
		comp -> PrintPage					= 1;
	}
	else {
		comp -> PrintPage					= 0;
	}		
#if (0) /* TBD �R�}���h�t�@�C���̒��p��ID�o�b�t�@�ɕW��ID���Z�b�g�i�s�B�ʒm�p�j*/
	if(SetTransmitStationID() == NO) {
		return (FALSE); /** TSI �s�ǃG���[ */
	}
#endif
	/*------------------------------------*/
	/* ��������M���e�t�@�C���A�C�e���ύX */
	/*------------------------------------*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;	/** SYS_MEM_RX_FILE -> SYS_MEM_TX_FILE */
	SYS_RxMemoryFileNo = RelayedCommandNo;				/* 1998/11/06 H.Yoshikawa */
	SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;			/* 1998/11/06 H.Yoshikawa */
	SYS_RxPrintFileBoxNumber = MEM_IGNORE_BOX_NUMBER;	/* 1998/11/06 H.Yoshikawa */

#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif

	return (0);
}


/*************************************************************************
	module		:[���[�v��M���f]
	function	:[1.���[�v�@�\�����ԓ����ǂ����̃`�F�b�N �S�Ď��ԊO�̏ꍇ���������Ƀ��^�[��
				  2.�R�}���h�t�@�C���̋󂫂����� �󂫂������ꍇ���������Ƀ��^�[��
	]
	return		:[
		TRUE
		FALSE
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1998/11/06]
	author		:[�v�۔�]
*************************************************************************/
UBYTE CheckWarpRx(void)
{
	struct	SYS_CommandData_t	 *comp;
	struct SYS_NumberDisplayTable *table;
	BYTE	is_warp_enable[SYS_WARP_MAX],
			is_nd_warp_enable,
			warp_no,
			command_no,
			is_print;

	is_print	= 0;	/* 1998/10/07 By M.Kuwahara */
	/*--------------------------------------------------*/
	/* ���[�v�@�\���L�������e���󎚂��邩�ۂ��̃`�F�b�N */
	/*--------------------------------------------------*/
	CMN_DisableInterrupt();	/* ���荞�݋֎~ */
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
		if (!CHK_WarpFunctionON()) {
			is_warp_enable[warp_no] = FALSE;
			continue;
		}
#endif
		is_warp_enable[warp_no] = CMN_CheckWarpRange((struct SYS_SubDialData_t *)&SYB_WarpFile[warp_no], FaxComStartTime);
		if (is_warp_enable[warp_no]) {
			is_print |= CMN_CheckWarpPrint(SYB_WarpFile[warp_no].Option);
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	is_nd_warp_enable = FALSE;
 #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL && CHK_ND_WarpON()) {	/* ���ް�ި���ڲ���M�̎� */
 #else
	if (SYS_ND_CurrentJournalPoint != SYS_ND_NO_JOURNAL) {	/* ���ް�ި���ڲ���M�̎� */
 #endif
		/** �i���o�[�f�B�X�v���C���M�ԍ����A�o�^����Ă��邩�̃`�F�b�N 	1998/10/16 By M.Kuwahara */
		/** ���������ԍ����o�^����Ă��Ă��A��Ԏn�߂Ɍ��o���ꂽ���̂������Z�b�g���� */
		table = CMN_ND_FindNdTableByPhoneNumber( SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial,
												 (UBYTE)CMN_StringLength(SYB_NumberDisplayJournal[SYS_ND_CurrentJournalPoint].Dial));
		if (table != NULL) {
			/** �����ŁA���ݎ�M���̃i���o�[�f�B�X�v���C�Ɠo�^����Ă���i���o�[�f�B�X�v���C�̔�r������ */
			is_nd_warp_enable = 
						CMN_CheckWarpRange(&table->WarpData, FaxComStartTime);
			if (is_nd_warp_enable) {
				is_print |= CMN_CheckWarpPrint(table->WarpData.Option);
			}
		}
	}
#endif
	for (warp_no = 0; warp_no < SYS_WARP_MAX; warp_no++) {
		if (is_warp_enable[warp_no]) {
			break;
		}
	}
#if (PRO_NUMBER_DISPLAY == ENABLE)
	if (warp_no == SYS_WARP_MAX && is_nd_warp_enable == FALSE) {	/** ���[�v�@�\�����ׂĎ��ԊO */
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		return (FALSE);
	}
#else
	if (warp_no == SYS_WARP_MAX) {	/** ���[�v�@�\�����ׂĎ��ԊO */
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		return (FALSE);
	}
#endif
	/*------------------------------*/
	/* �R�}���h�t�@�C���̋󂫂����� */
	/*------------------------------*/
#if (0)
**		/* �P�O�P���ځiSYS_COM_FILE_MAX + 1�j�̃��[�v�ŁA�K���A�h���X�G���[�Ń��Z�b�g
**		** �`�F�b�N�֐��Ȃ̂ɁA�R�}���h�t�@�C���̃X�e�[�^�X�����������Ă��܂��B
**		** by H.Hirao 1999/03/04
**		*/
**	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
**		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
**			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
**#if (PRO_COMMANDFILE_SRAM == DISABLE)
**			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
**#endif
**			RelayedCommandNo = command_no;
**			comp = &SYB_CommandFile[RelayedCommandNo];
**			break;
**		}
**	}
**	if (RelayedCommandNo == 0xFF) {	/** �󂫃R�}���h���� */
**		CMN_EnableInterrupt();	/** ���荞�݋��� */
**		return (FALSE);
**	}
#endif
	CMN_EnableInterrupt();
	return TRUE;
}

#endif /* (PRO_RX_DOC_TRANSFER == ENABLE) */

 /** #if (PRO_KEYPANEL == PANEL_HINOKI) **/	/**���̋@������q�n�l�Ή� 1999.4.21 K.Kawata **/
  #if (PRO_SPECIAL_REPLAY_TRANS == ENABLE)
/*************************************************************************
	module		:[�s�r�h�𔻒f���A���̔ԍ��ɂe�`�w��܂�Ԃ����߂̃R�}���h�t�@�C���̍쐬]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[���q�n�l(RDC-D83-002)]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[FCM]
	date		:[1999/04/02]
	author		:[���� �p�T]
*************************************************************************/
void SetUpSpecialReplayTrans(void)
{
	struct	SYS_CommandData_t	 *comp;
	UBYTE	is_print;
	UBYTE	command_no;
	
#if (0)
** 	/* �b�r����܂�Ԃ����q�n�l�ɂ����āA�Z���^�[���ł���M���e���v�����g���Ăق����Ƃ����q�c�b��
** 	** ���s���ꂽ���߁A�������X�C�b�`�iUNISWJ-5-5�j��ON/OFF�ł���悤�ɂ��Ă����B�iRDC200100059)
** 	** by O.Kimoto 2001/02/22
** 	*/
** 	is_print = 0;	/* ���e�̓v�����g���Ȃ� */
#else
	if (CHK_UNI_TSI_RelayTxCenterPrint()) {
		is_print = 1;	/* ���e�̓v�����g���� */
	}
	else {
		is_print = 0;	/* ���e�̓v�����g���Ȃ� */
	}
#endif
	
	CMN_DisableInterrupt();	/* ���荞�݋֎~ */
	/*------------------------------*/
	/* �R�}���h�t�@�C���̋󂫂����� */
	/*------------------------------*/
	for (command_no = 0; command_no < SYS_COM_FILE_MAX; command_no++) {
		if (SYB_CommandFile[command_no].Status == SYS_CMD_EMPTY) {
			SYB_CommandFile[command_no].Status = SYS_CMD_SETTING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
			SYB_CommandStatus[command_no] = SYS_CMD_SETTING;
#endif
			comp = &SYB_CommandFile[command_no];
			RelayedCommandNo = command_no;
			break;
		}
	}
	CMN_EnableInterrupt();	/** ���荞�݋��� */
	if (RelayedCommandNo == 0xFF) {	/** �󂫃R�}���h���� */
		return;
	}
	if (SetTransmitStationID() == NO) {
		CMN_DisableInterrupt();	/* ���荞�݋֎~ */
		SYB_CommandFile[RelayedCommandNo].Status = SYS_CMD_EMPTY;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
		SYB_CommandStatus[RelayedCommandNo] = SYS_CMD_EMPTY;
#endif
		CMN_EnableInterrupt();	/** ���荞�݋��� */
		RelayedCommandNo = 0xFF;
		return;
	}
	/*--------------------------*/
	/* ���e���v�����g���邩�ۂ� */
	/*--------------------------*/
	if (is_print) {
		SYS_RxPrintFileItem		= SYS_MEM_RX_FILE;
		SYS_RxPrintFileNo		= SYB_MemoryRxPrintWritePoint;
		SYS_RxPrintFilePage		= SYS_RxTotalPage + 1;
	}
	/*------------------------------*/
	/* �R�}���h�t�@�C���̃����o�o�^ */
	/*------------------------------*/
	ClearDialNumber((struct SYS_DialData_t *)&comp->DialNumber);	/** �_�C�����f�[�^������ */
	CMN_MemorySet(&comp->DialNumber.Direct[0][0], SYS_DIRECT_DIAL_MAX, 0xFF);
	CMN_ASC_ToBCD_StringNum(&comp->DialNumber.Direct[0][0], &comp->Option.OptionNumber.RelaySourceID[0], (SYS_DIRECT_DIAL_MAX-1));
	comp -> Option.Item = SYS_MEMORY_TX;
	comp -> Option.ConfirmationReport	= NO;
	comp -> TitleMessage				= 0xFF;
	comp -> Ability						= NO;
#if (PRO_DEPARTMENT == ENABLE)
	comp -> DepartmentCode				= 0xFFFF;
#endif
#if (PRO_PIN_ACCESS == ENABLE)
	if (CHK_PIN_AccessMode() == PIN_ACCESS_MODE1) {
		comp -> PIN_AccessMode			= PIN_ACCESS_MODE1;
	}
	else {
		comp -> PIN_AccessMode			= 0;
	}
#endif
	if (is_print) {
		comp -> PrintPage				= 1;
	}
	else {
		comp -> PrintPage				= 0;
	}
	/*------------------------------------*/
	/* ��������M���e�t�@�C���A�C�e���ύX */
	/*------------------------------------*/
	SYS_RxMemoryFileItem = SYS_MEM_TX_FILE;
	SYS_RxMemoryFileNo = RelayedCommandNo;
	SYS_RxMemoryFilePage = SYS_RxTotalPage + 1;
	SYS_RxPrintFileBoxNumber = MEM_IGNORE_BOX_NUMBER;

#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
	SYB_FcodeBoxNoByRelayedTxComNo[RelayedCommandNo] = 0;
#endif

	return;
}
  #endif
 /**#endif**/	/**���̋@������q�n�l�Ή� 1999.4.21 K.Kawata **/
/* SetUpSecureMailRx(WORD pos) ��肱���܂łl�l�k��p */
#endif	/* (PRO_MAKER == MML) */
