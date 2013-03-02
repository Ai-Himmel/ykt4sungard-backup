/* ----------------------------------------------------------
 * ³ÌÐòÃû³Æ£ºtransinfo.h
 * ´´½¨ÈÕÆÚ£º2004-09-09 14:58
 * ³ÌÐò×÷Õß£ºº«º£¶«
 * °æ±¾ÐÅÏ¢£º1.0.0.0
 * ³ÌÐò¹¦ÄÜ£ºÒøÐÐ×ªÕÊ¸÷ÖÖ½»Ò×º¯ÊýÊµÏÖ
 * ----------------------------------------------------------
 * ÐÞ¸ÄÈÕÆÚ: 2005-03-10
 * ÐÞ¸ÄÈËÔ±: ÁÖÇÕ
 * ÐÞ¸ÄÃèÊö: ½«ÓëÒøÐÐÍ¨ÐÅ²¿·ÖÒÆµ½bank.h£¬ÒÔÓëbu´úÂë·ÖÀë£¬¹©bankguardµ÷ÓÃ
 *           ´Ë´¦Ö»±£ÁôposÇëÇó´¦Àí£¨°üº¬ÒøÐÐ½Ó¿Úµ÷ÓÃ£©
 * °æ±¾ÐÅÏ¢£º1.0.1.1
 * ----------------------------------------------------------*/
#include <stdlib.h>
#include "fdsqc.h"
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "errdef.h"
#include "mypub.h"
#include "tcp.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "account.h"
#include "bank.h"
#include "txntyp.h"
#include "typdef.h"


#ifndef	DEBUG
	#define	DEBUG
#endif
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);


static void dump_hex_str(unsigned char* buf,int len)
{
	int i ;
	for( i =0 ;i < len;++i)
	{
		if( i % 20 == 0)
		{
			printf("\n");
		}
		printf("[%02x]",buf[i]);
	}
}

//²éÑ¯×ªÕÊÁ÷Ë®
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no)
{
	int ret=0;
	T_t_tif_tradeserial  tradeserial;
	INNER_TRANS_REQUEST from_pos;
	double unique=0;
	memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//Çå¿ÕÁ÷Ë®½á¹¹Ìå
	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pnode,sizeof(from_pos));
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);			//Á÷Ë®ºÅ
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.serial_no=int(unique);
	tradeserial.serial_type=TRADE_INNER_DETRANS;			//½»Ò×´úÂë
	tradeserial.serial_state=SERISTAT_NONEEDDEBT;			//Á÷Ë®×´Ì¬
	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//½»Ò×ÈÕÆÚ
		memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//½»Ò×Ê±¼ä
	}
	//memcpy(tradeserial.operate_date,from_pos.TradeDate,sizeof(from_pos.TradeDate));		//½»Ò×ÈÕÆÚ
	//memcpy(tradeserial.operate_time,from_pos.TradeTime,sizeof(from_pos.TradeTime));		//½»Ò×Ê±¼ä
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));//²É¼¯ÈÕÆÚ
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));//²É¼¯Ê±¼ä
	tradeserial.maindevice_id=GetTransferSystemId();				//×ÓÏµÍ³ºÅÂë
	tradeserial.device_id=atoi(from_pos.TerminalId);			//ÖÕ¶ËID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100;			//×ªÕÊ½ð¶î
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));	//ÒøÐÐ¿¨ºÅ£­£­£­£­¸ü¸ÛÌí¼ÓÊý¾Ý¿â×Ö¶Î
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;				//Íâ²¿ÏµÍ³±êÊ¶£¬´Ë´¦ÎªÇø·Ö¶à¸öÒøÐÐ--- Å©ÒµÒøÐÐÎª1
	tradeserial.condition_id=SELF_TRANS;						//×Ô¶¯/×ÔÖú×ªÕÊ±êÊ¶
	strcpy(tradeserial.oper_code,"system");						//²Ù×÷Ô±´úÂë
	tradeserial.other_seri_no=other_serial_no;					//Ô­Ê¼Á÷Ë®ºÅ
	tradeserial.tmark=0;									//ÓÃÀ´¼ÇÂ¼³åÕý·¢ËÍ´ÎÊý£¿

	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_ERR,"detrans ok");
	return	0;


}

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//¹¤×÷Õ¾±êÊ¶
	IA->iDevId=p->device_id;						//Éè±¸ID
	IA->iSerialNo=p->serial_no;					//Á÷Ë®ºÅ
	IA->iTradeNo=p->serial_type;					//½»Ò×Âë
	strcpy(IA->sTxDate,p->operate_date);			//½»Ò×ÈÕÆÚ
	strcpy(IA->sTxTime,p->operate_time);			//½»Ò×Ê±¼ä
	strcpy(IA->sTxCollectDate,p->collect_date);		//²É¼¯ÈÕÆÚ
	strcpy(IA->sTxCollectTime,p->collect_time);		//²É¼¯Ê±¼ä
	strcpy(IA->sTxAccDate,p->enteract_date);		//¼ÇÕËÈÕÆÚ
	strcpy(IA->sTxAccTime,p->enteract_time);		//¼ÇÕËÊ±¼ä
	strcpy(IA->sMdeOper,p->oper_code);			//²Ù×÷Ô±
	strcpy(IA->sChkOper,p->reserve_1);			//¸´ºË²Ù×÷Ô±

	IA->iUseCardFlag=IS_YES;						//¿¨½»Ò×
	IA->iTxCnt=p->trade_count;					//½»Ò×´ÎÊý
	IA->dInCardBala=p->in_balance;				//Èë¿¨Öµ
	IA->dOutCardBala=-1;							//³ö¿¨Öµ

	//ÐÞ¸Ä½è·½ºÍ´û·½ÕÊ»§Óà¶î£¬¼Ç»á¼Æ·ÖÂ¼ÕÊ
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//³ö¿¨Öµ
	return 0;
}

//POSµÇÂ½	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode)
{
	//double unique=0;
	int ret=0;
	INNER_TRANS_REQUEST  from_pos;


	//ÒøÐÐÎ´Ç©µ½³É¹¦£¬POS²»ÄÜµÇÂ½ÊÚÓèÃÜÔ¿
	if(!BANK_LOGIN)
	{
		writelog(LOG_ERR,"System not login to bank,pos login forbidden!shm[1]=[%d]",shm[1]);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NETERR);
		return	E_TRANS_BANK_NETERR;
	}

	memcpy(&from_pos,pNode,sizeof(from_pos));
	T_t_tif_tradeserial  	tradeserial;		//¿¨²Ù×÷Á÷Ë®±í 	tradeserial;
	T_t_pif_device 		t_pif_device;
	T_t_pif_cur_syspara 	t_syspara;


	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&t_pif_device,0,sizeof(t_pif_device));
	memset(&t_syspara,0,sizeof(t_syspara));

	ret=DB_t_pif_cur_syspara_read_by_id(2006, &t_syspara);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	ret=DB_t_pif_device_read_lock_by_cur_and_device_id(atoi(from_pos.TerminalId),&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_lock_by_cur_and_device_id error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	t_pif_device.state_id=DEVISTAT_ONLINE;		//¸ü¸ÄÉè±¸×¢²á±í×´Ì¬ÎªÔÚÏß×´Ì¬
	ret=DB_t_pif_device_update_lock_by_cur(&t_pif_device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_update_lock_by_cur error,error code=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

    	ret=db_commit();
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return 	E_TRANS_UNKNOW_ERROR;
	}

	//Ìî³äÓ¦´ð°ü£­£­£­pNode
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	memcpy(pNode->BankCardNewPwd,t_syspara.value,sizeof(pNode->BankCardNewPwd));
	writelog(LOG_INFO,"shm=[%s],pNode->bankcardpwd[%s]",shm,pNode->BankCardPwd);
	return 0;
}


//²éÑ¯Ð£Ô°¿¨Óà¶î
//ÔÝÊ±¸Ã¹¦ÄÜÈ¡Ïû£¬ÖÕ¶ËÍ¨¹ý¶ÁÐ´¿¨È¡µÃÓà¶î
int Pos_QuerySchool(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	//T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}


	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	//¸ù¾Ý¿¨ºÅºÍÇ®°üºÅ£¬·µ»ØÕÊºÅ
	ret=GetActnoByCardIdAndPurseId(account_id,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId err,CardNo=[%s],Notecase=[%s]",from_pos.CardNo,from_pos.Notecase);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	ret=DB_t_aif_account_read_by_account_id(account_id, &account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_account_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	//Ìî³äÓ¦´ð°ü
	memset(pNode,0,sizeof(from_pos));
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	//printf("¿¨Óà¶î= [%f]\n",account.cur_freebala);
	sprintf(pNode->AccountMoney,"%f",account.cur_freebala);
	writelog(LOG_INFO,"query school card balance succeed!");

	return 0;

}

//²éÑ¯ÒøÐÐ¿¨Óà¶î
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	double unique=0;
	unsigned char buffer[1024]="";
	char tmp_buf[4+1]="";


	INNER_TRANS_REQUEST  from_pos;
	MSG8583 BankReqPak,BankAnsPak;
	H_MSG8583 head,head_rsp;

	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	struct SockNode SockNode;

	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&head,0,sizeof(head));
	memset(&head_rsp,0,sizeof(head_rsp));
	memset(&head,0x20,84);
	memset(&head_rsp,0x20,84);

	memset(&SockNode,0,sizeof(SockNode));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));

	memcpy(&from_pos,pNode,sizeof(from_pos));


	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	char		ho_dbdate[8 + 1] = "";				//Êý¾Ý¿âÈÕÆÚ
	char 	ho_dbtime[6+1]="";				//Êý¾Ý¿âÊ±¼ä
	memset(ho_dbdate,0,sizeof(ho_dbdate));
	memset(ho_dbtime,0,sizeof(ho_dbtime));

	//×éÖ¯ÒøÐÐ°ü
	//Ð´½»Ò×´úÂë
	memcpy( BankReqPak.msgType,"0240", sizeof(BankReqPak.msgType)-1);					//0//½»Ò×´úÂë   
	BankReqPak.bitMapExt=0;															//1//À©Õ¹Î»Í¼
	//¸ù¾Ý¶ÔÓ¦¹ØÏµ»¹ÊÇÖ±½ÓË¢¿¨
	strncpy(BankReqPak.priActNum,"4563516107002318007",sizeof(BankReqPak.priActNum)-1);	//2//Ö÷ÕËºÅ--ÒøÐÐ¿¨ºÅ
	strncpy(BankReqPak.procCode,"880108",sizeof(BankReqPak.procCode)-1);					//3//¹ý³ÌÂë
	//²éÑ¯½»Ò×£¬ÎªÁËÂú×ãÎ»Í¼ÒªÇó£¬ÌîÐ´0
	BankReqPak.txnAmunt=0.00;														//4//½»Ò×½ð¶î
	strncpy(BankReqPak.txnDatTim,"0000000000",sizeof(BankReqPak.txnDatTim));				//7//ÒøÐÐºóÌ¨½»Ò×ÈÕÆÚ--ÌîÐ´0
	strncpy(BankReqPak.companyid,"44630021",sizeof(BankReqPak.companyid)-1);				//8//¹«Ë¾´úÂë
	//²éÑ¯½»Ò×£¬ÎªÁËÂú×ãÎ»Í¼ÒªÇó£¬ÌîÐ´0
	BankReqPak.tracAudNum=10000;														//11//Á÷Ë®ºÅ
	ret=get_datetime_from_db(ho_dbdate, ho_dbtime);//½»Ò×ÈÕÆÚ----´ý¶¨
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
	}
	strncpy(BankReqPak.txnLocDat,ho_dbdate+2,4);										//13//½»Ò×ÈÕÆÚ--mmdd
	strncpy(BankReqPak.txnDatTim,ho_dbtime,sizeof(BankReqPak.txnDatTim)-1);				//12//½»Ò×Ê±¼ä--hhmmmm
	strncpy(BankReqPak.datCap,ho_dbdate+2,4);											//17//Ö÷»ú½»Ò×Ê±¼ä--´ý¶¨
	strncpy(BankReqPak.teller,"00",sizeof(BankReqPak)-1);									//19//¹ñÔ±ºÅ
	strncpy(BankReqPak.srvTyp,"118",sizeof(BankReqPak.srvTyp)-1);							//21//·þÎñÀàÐÍ
	strncpy(BankReqPak.actTyp,"01",sizeof(BankReqPak.actTyp)-1);							//23//ÕÊºÅÀà±ð
	BankReqPak.pSrvCdCod=11;														//25//·þÎñµã´úÂë
	BankReqPak.mainTrcNo=1234;														//28//ÒøÐÐÁ÷Ë®ºÅ
	strncpy(BankReqPak.pinDat1,"123456",sizeof(BankReqPak.pinDat1) -1);						//29//ÒøÐÐ¿¨ÃÜÂë
	strncpy(BankReqPak.acqInstID,"4446301",sizeof(BankReqPak.acqInstID)-1);					//32//ÊÕµ¥»ú¹¹ºÅ
	strncpy(BankReqPak.rspCod,"00",sizeof(BankReqPak.rspCod)-1);							//39//ÒøÐÐ·µ»ØÂë
	strncpy(BankReqPak.termID,"00",sizeof(BankReqPak.termID)-1);							//41//½»Ò×ÖÕ¶ËºÅ
	strncpy(BankReqPak.idenCod,"4446301",sizeof(BankReqPak.idenCod)-1);					//42//½»Ò×ÍøµãºÅ
	
	//¿Í»§±êÊ¶£¬ÒªÐÞ¸ÄÎª¿Í»§ºÅ£¬»òÕßÑ§¹¤ºÅ
	strncpy(BankReqPak.agtcus,"4002699752",sizeof(BankReqPak.agtcus)-1);					//43//¿Í»§±êÊ¶
	BankReqPak.pinDat=100;															//52//pindat

	ret=Pack8583((unsigned char*)head.msg, BankReqPak, 2);
	if(ret<0)
	{
		writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	dump_hex_str((unsigned char*)head.msg,ret);
	//Ð´°üÍ·ÐÅÏ¢
	int length=ret;
	sprintf(tmp_buf,"%04d",length+84);
	memcpy(head.length,tmp_buf,4);
	head.pkgtyp[0]=0x30;
	memcpy(head.msgtyp,"0240",sizeof(head.msgtyp));
	memcpy(head.prccde,"880108",sizeof(head.prccde));
	memcpy(head.acqInstID,"44630021",sizeof(head.acqInstID));
	memcpy(head.termID,"00",2);
	memcpy(head.trcno,"00001",5);
	memcpy(head.custyp,"OV",2);
	//ÐÞ¸ÄÎªÐ£Ô°¿¨¿Í»§ºÅ»òÕßÑ§¹¤ºÅ
	memcpy(head.cusidt,"52525253",8);
	memcpy(head.apcode,"01",2);
	memcpy(head.srvuID,"44630021",sizeof(head.srvuID));
	memcpy(head.rspcde,"00",sizeof(head.rspcde));
	memcpy(head.pkgseq,"01",sizeof(head.pkgseq));
	memcpy(head.filler,"000000",sizeof(head.filler));
	sprintf(tmp_buf,"%04d",ret);
	memcpy(head.msgLen,tmp_buf,4);
	int recv_length=0;
	ret=send_to_and_recv_from_bank_of_boc((char*)&head,88+length,(char*)&head_rsp,&recv_length,2500,5000);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	ret=UnPack8583((unsigned char*)head_rsp.msg,&BankAnsPak,2);
	dump_hex_str((unsigned char*)head.msg,ret);
	if(ret < 0)
	{
		writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

		
	//TRACE_BANK_TRANS(&BankAnsPak,"receivce query bank package");

	if(0!=strncmp(BankAnsPak.rspCod,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",BankAnsPak.rspCod);
		BankAnsPak.rspCod[2]=0;
		ret = BOC_RET_NO(BankAnsPak.rspCod);
		writelog(LOG_DEBUG,"bank response return code [%d]",ret);
		return ret;
	}

	//Ìî³äÓ¦´ð°ü
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	sprintf(pNode->Balance,"%9.9f",BankAnsPak.txnAmunt);
	writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%s]",pNode->Balance);
	return 0;

}

//ÐÞ¸ÄÐ£Ô°¿¨ÃÜÂë
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
//	double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
//	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	T_t_aif_account account;
	T_t_pif_card card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

	Strncpy_t(account_pwd, from_pos.AccountNewPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);
	memcpy(card.password,pwd,sizeof(card.password));
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_update_lock_by_cur error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}
	//Ìî³äÓ¦´ð°ü

	memset(pNode,0,sizeof(from_pos));
	writelog(LOG_INFO,"Change school card password succeed!");
	return 0;

}

//¹ÒÊ§Ð£Ô°¿¨

int Pos_LostCard(INNER_TRANS_REQUEST * pNode)
{
	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	char enddate[10 + 1] = "";
	int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memcpy(&from_pos,pNode,sizeof(from_pos));

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));

	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}

	ret=GetLogicDate(logicdate);								//ÒµÎñÈÕÆÚ
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	ret=get_tradecard_no_by_stupid(from_pos.CardNo,&card_id);			//¿¨±êÊ¶
	if(ret)
	{
		if(100==ret)
		{
			writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d]",ret);
			return E_TRANS_SCHACC_NOEXIT;
		}
		if(-811==ret)
		{
			writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
			return E_TRANS_SCHCARD_TWICE;
		}
		writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//writelog(LOG_INFO,"card_id=[%d]",*pCardid);


	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id,&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	Cut_id = card.cosumer_id;														//¿Í»§ºÅ
	des2src(Operator,"system");												//²Ù×÷Ô±ºÅ
	maindevice_id = GetTransferSystemId();											//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	device_id = atoi(from_pos.TerminalId);										//²É¼¯Éè±¸±êÊ¶

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		return E_TRANS_SCHCARD_PWDERR;
	}
	/*
	//	¼ì²é¿Í»§ÐÅÏ¢£¬ÅÐ¶ÏÊÇ·ñ¿ÉÒÔ¹ÒÊ§
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetCardState error,errcode=[%d],card_id=[%d]",ret,card_id);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	//	ÐÞ¸Ä¿¨×´Ì¬Îª¹ÒÊ§¡
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_TRUE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	²åÈë¿¨¹ÒÊ§ÓÐÐ§ÆÚÏÞ±í
	/*
	ret=GetLostCardValiddate(sysdate,enddate);											//»ñµÃ¹ÒÊ§ÓÐÐ§ÆÚÏÞ
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"GetLostCardValiddate=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.card_id = card_id;													//¿¨ºÅ
	des2src(cardlossinfo.begin_date,sysdate);											//ÆðÊ¼ÈÕÆÚ
	des2src(cardlossinfo.end_date,enddate);											//½ØÖÁÈÕÆÚ
	des2src(cardlossinfo.operate_date,sysdate);										//²Ù×÷ÈÕÆÚ
	des2src(cardlossinfo.operate_time,systime);										//²Ù×÷Ê±¼ä
	cardlossinfo.state_id=STATE_VALID;												//ÓÐÐ§
	ret = DB_t_pif_cardlossinfo_add(&cardlossinfo);
	if (ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_add=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//Èç¹û¸Ã¿¨ºÅ±»¶³½á,Ôò¹ÒÊ§Ê±¶ÔºÚÃûµ¥²»´¦Àí
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(card.card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				writelog(LOG_ERR,"DB_t_tif_black_sheet_del_by_card_id_and_is_ad error,errcode=[%d],card_id=[%d]",ret,card.card_id);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		ret=InsertToBlkList(card.card_id,ADD_BLACKLIST);
		if(ret)
		{
			writelog(LOG_ERR,"InsertToBlkList error,errcode=[%d],card_id=[%d]",ret,card.card_id);
			return E_TRANS_UNKNOW_ERROR;
		}

		//¹ã²¥ºÚÃûµ¥
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card.card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//ÔöÉ¾±êÖ¾

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"AddMsgLst=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}

	}


	//	×¼±¸Êý¾Ý²åÈë½»Ò×Á÷Ë®±í
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//»ñµÃ×î´óÁ÷Ë®ºÅ
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//·¢ÉúÈÕÆÚ
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//²É¼¯ÈÕÆÚ
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//²É¼¯Ê±¼ä
	des2src(tradeserial.enteract_date,logicdate);							//´¦ÀíÈÕÆÚ
	des2src(tradeserial.enteract_time,tradeserial.operate_time);							//´¦ÀíÊ±¼ä
	tradeserial.serial_no = (int)dUniqno;									//Á÷Ë®ºÅ
	tradeserial.serial_type = TXCODE_CARD_LOSS;							//¹ÒÊ§
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;						//Á÷Ë®×´Ì¬
	tradeserial.maindevice_id = GetTransferSystemId();						//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	tradeserial.device_id = atoi(from_pos.TerminalId);						//²É¼¯Éè±¸±êÊ¶
	tradeserial.card_id = card_id;										//½»Ò×¿¨ºÅ
	tradeserial.customer_id=Cut_id;										//¿Í»§ºÅ
	des2src(tradeserial.oper_code,Operator);
	tradeserial.other_seri_no=from_pos.SendNo;

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	return 0;
}

int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode)
{

	char key[32+1]="";
	char pwd[32+1]="";
	char account_pwd[6+1]="";

  	int ret = 0;
	//char enddate[10 + 1] = "";
	//int	card_id = 0;
	char	Operator[33+1] = "";
	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
//	char		sCardState[5] = "";

	INNER_TRANS_REQUEST  from_pos;

	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_aif_account	account;
	T_t_pif_card	card;

	memset(&from_pos,0,sizeof(from_pos));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	ret=GetLogicDate(logicdate);								//ÒµÎñÈÕÆÚ
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_UNKNOW_ERROR;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}

	Cut_id = card.cosumer_id;													//¿Í»§ºÅ
	des2src(Operator,"system");												//²Ù×÷Ô±ºÅ
	//maindevice_id = GetTransferSystemId();										//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	//device_id = atoi(from_pos.TerminalId);										//²É¼¯Éè±¸±êÊ¶

	//des2src(sysdate,from_pos.TradeDate);
	//des2src(systime,from_pos.TradeTime);

	//des2src(black_sheet.operate_date,sysdate);
	//des2src(black_sheet.operate_time,systime);

	//des2src(hi_enddate,sysdate);
	//des2src(hi_endtime,systime);

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHCARD_FREEZE;
	//	return E_TRANS_SCHCARD_UNLOSTING;
	}

	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return 0;
	//	return E_TRANS_SCHCARD_UNLOSTING;
	}
	ret=IsExistNoLostCardByCustomId(Cut_id);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		return E_TRANS_SCHCARD_TWICE;
	}
	//ÐÞ¸Ä¹ÒÊ§±í×´Ì¬ÎªÎÞÐ§
	/*
	ret=DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id(card.card_id,STATE_VALID,&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_read_lock_by_cur1_and_card_id_and_state_id error,card_id=[%d],errcode=[%d]",card.card_id,ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	cardlossinfo.state_id=STATE_INVALID;
	des2src(cardlossinfo.end_date,sysdate);
	ret=DB_t_pif_cardlossinfo_update_lock_by_cur1(&cardlossinfo);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"DB_t_pif_cardlossinfo_update_lock_by_cur1 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//×´Ì¬×÷ÎªºÚÃûµ¥µÄÓÐÐ§×´Ì¬,²»×÷Îª¿¨×´Ì¬
		//ÐÞ¸ÄÔ­À´µÄºÚÃûµ¥µÄ×´Ì¬±êÖ¾ÎªÎÞÐ§
		//	²åÈëºÚÃûµ¥±í
		black_sheet.card_id = card.card_id;
		black_sheet.is_ad = DELETE_BLACKLIST;
		des2src(black_sheet.operate_date,sysdate);
		des2src(black_sheet.operate_time,systime);
		memcpy(black_sheet.volume,sysdate+2,6);
		memcpy(black_sheet.volume+6,systime,6);
		strcpy(black_sheet.validdate,VALIDDATE);
		black_sheet.state_id = STATE_VALID;
		ret = DB_t_tif_black_sheet_add(&black_sheet);
		if (ret)
		{
			writelog(LOG_ERR,"DB_t_tif_black_sheet_add error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
		//¹ã²¥ºÚÃûµ¥
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,black_sheet.card_id);
		AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, black_sheet.volume);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,black_sheet.is_ad);	//ÔöÉ¾±êÖ¾

		tMesList.funid = 930005;
		tMesList.level = 1;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"AddMsgLst error,errcode=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//	ÐÞ¸Ä¿¨×´Ì¬Îª½â¹Ò×´Ì¬
	card.state_id[CARDSTAT_TYPE_LOST]=STATE_FALSE;
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	×¼±¸Êý¾Ý²åÈë½»Ò×Á÷Ë®±í
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//»ñµÃ×î´óÁ÷Ë®ºÅ
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	strncpy(tradeserial.operate_date,sysdate,sizeof(sysdate)-1);				//·¢ÉúÈÕÆÚ
	strncpy(tradeserial.operate_time,systime,sizeof(systime)-1);				//·¢ÉúÊ±¼ä
	des2src(tradeserial.collect_date,sysdate);												//²É¼¯ÈÕÆÚ
	des2src(tradeserial.collect_time,systime);												//²É¼¯Ê±¼ä
	des2src(tradeserial.enteract_date,logicdate);											//´¦ÀíÈÕÆÚ
	des2src(tradeserial.enteract_time,systime);											//´¦ÀíÊ±¼ä
	tradeserial.serial_no = (int)dUniqno;													//Á÷Ë®ºÅ
	tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;								//½â¹Ò
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;										//Á÷Ë®×´Ì¬
	tradeserial.maindevice_id = GetTransferSystemId();									//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	tradeserial.device_id = atoi(from_pos.TerminalId);										//²É¼¯Éè±¸±êÊ¶
	tradeserial.card_id = card.card_id;														//½»Ò×¿¨ºÅ
	tradeserial.customer_id = Cut_id;
	des2src(tradeserial.oper_code, "system");
	//	²åÈë¿¨²Ù×÷Á÷Ë®±í
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_add error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	return 0;
}

//POS×ªÕÊ
int Pos_Transfer(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	double unique=0;
	int temp_serial_no=0;
	char logicdate[11]="";
	char buffer[16]="";
	int i=0;

	INNER_TRANS_REQUEST  from_pos;
	MSG8583 BankReqPak,BankAnsPak;
	H_MSG8583 head,head_rsp;
	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	T_t_tif_tradeserial  tradeserial_bak;
	T_t_pif_card		card;
	InAcc	IA;

	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&head,0,sizeof(head));
	memset(&head_rsp,0,sizeof(head_rsp));
	memset(&head,0x20,84);
	memset(&head_rsp,0x20,84);


	memset(&tradeserial_bak,0,sizeof(tradeserial_bak));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//ÒµÎñÈÕÆÚ
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}
	//ÅÐ¶ÏÊÇ·ñ´¦ÓÚÈÕÖÕ½áËã×´Ì¬
 	ret=GetParameter(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}

	if(strncmp(card.state_id,CARDSTAT_LOGOUT,4)==0)
	{
		writelog(LOG_ERR,"card.state_id=[%d]",card.card_id);
		return E_TRANS_SCHACC_DESTORY;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_WFAIL])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_WFAIL;
	}

	//×ªÕË²»ÔÊÐí×ªÐ¡Êý½ð¶î
	if(0!=memcmp(from_pos.TransMoney+7,"00",2))
	{
		writelog(LOG_ERR,"Trans money is not a integer!,transmoney=[%f]",atol(from_pos.TransMoney)/100.00);
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}

	//¿ªÊ¼Ìî³äÁ÷Ë®Êý¾Ý
	//Á÷Ë®ºÅ

	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &unique);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}


	tradeserial.serial_no=int(unique);
	//¼ÍÂ¼Á÷Ë®ºÅ£¬×÷Îª³åÕýÊ¹ÓÃ
	temp_serial_no=tradeserial.serial_no;

	tradeserial.other_seri_no=from_pos.SendNo;	//ÉÏ´«¶ËÁ÷Ë®ºÅ
	tradeserial.serial_type=TRADE_INNER_TRANS;	//½»Ò×´úÂë
	tradeserial.serial_state=SERISTAT_NODEBT;	//Á÷Ë®×´Ì¬
	tradeserial.card_id=atoi(from_pos.CardNo);
	tradeserial.purse_id=0;
	tradeserial.in_balance=double(atoi(from_pos.AccountMoney)/100.00);	//Èë¿¨½ð¶î
	tradeserial.out_balance=tradeserial.in_balance;						//³ö¿¨½ð¶î
	tradeserial.trade_count=from_pos.RecvNo+1;							//µ±Ç°¿¨ÖÐ½»Ò×´ÎÊý

	ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(tradeserial.operate_date);
		getsystime(tradeserial.operate_time);
	}
	Strncpy_t(tradeserial.collect_date,tradeserial.operate_date,sizeof(tradeserial.collect_date));	//²É¼¯ÈÕÆÚ
	Strncpy_t(tradeserial.collect_time,tradeserial.operate_time,sizeof(tradeserial.collect_time));	//²É¼¯Ê±¼ä
	Strncpy_t(tradeserial.enteract_date,logicdate,sizeof(tradeserial.enteract_date));	//ÈëÕÊÈÕÆÚ
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//ÈëÕÊÊ±¼ä
	tradeserial.maindevice_id=GetTransferSystemId();	//×ÓÏµÍ³ºÅÂë
	tradeserial.device_id=atoi(from_pos.TerminalId);	//ÖÕ¶ËID
	tradeserial.trade_fee=atol(from_pos.TransMoney)/100.00;	//×ªÕÊ½ð¶î
	//ÒøÐÐ¿¨ºÅ£­£­£­£­¸ü¸ÛÌí¼ÓÊý¾Ý¿â×Ö¶Î
	memcpy(tradeserial.b_act_id,from_pos.BankCardNo,sizeof(from_pos.BankCardNo));
	tradeserial.sys_id=AGRICULTURE_BANK_CODE;	//Íâ²¿ÏµÍ³±êÊ¶£¬´Ë´¦ÎªÇø·Ö¶à¸öÒøÐÐ--- Å©ÒµÒøÐÐÎª1
	tradeserial.condition_id=SELF_TRANS;	//×Ô¶¯/×ÔÖú×ªÕÊ±êÊ¶
	//tradeserial.out_account_id=;
	//tradeserial.in_account_id=;
	tradeserial.customer_id=card.cosumer_id;
	strncpy(tradeserial.oper_code,"system",sizeof(tradeserial.oper_code));	//²Ù×÷Ô±´úÂë
	//½áÊøÌî³äÁ÷Ë®Êý¾Ý
	ret=DB_t_tif_tradeserial_add(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
		return 	E_TRANS_UNKNOW_ERROR;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//°ÑÁ÷Ë®½á¹¹±¸·ÝÆðÀ´£¬×÷Îª²âÊÔÈëÕÊºóµÄÊý¾Ý
	//·ÀÖ¹ÖØ¸´ÔËËã´î»ï·Ñ
	memcpy(&tradeserial_bak,&tradeserial,sizeof(tradeserial_bak));

	double trade_fee=0;
	double board_fee=0;
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	T_t_aif_account	tAccount;		//ÕÊ»§±í
	T_t_cif_customer	tCustomer;
	T_t_pif_spefee 	tSpeFee;

	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));

	//ÅÐ¶Ï×ªÕÊ½ð¶îÊÇ·ñ³¬³öÇ®°ü×î´óÏÞ¶î
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card.card_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter GLOBE_MAXCARDBALANCE error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		return E_TRANS_TRANSMONEY_OUTRANGE;
	}
	//¶ÁÈ¡¿Í»§ÊÕ·ÑÀà±ð×Ö¶Î
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",card.cosumer_id);
		if(DB_NOTFOUND==ret)
			return E_TRANS_UNKNOW_ERROR;
		else
			return E_TRANS_UNKNOW_ERROR;
	}

	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				writelog(LOG_ERR,"DB_t_pif_spefee_read_by_dept_code_and_cut_type error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	//ÌîÐ´ÈëÕË½á¹¹,ÎÊÎÊÎÅ½£
	des2src(IA.sArrInActno[0],tAccount.account_id);						//ÕÊ»§
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	//½áÊø--ÊÇ·ñprocessÒ²ÒªÐÞ¸Ä

	ret=process(&IA,&tradeserial_bak);
	if(ret)
	{
		writelog(LOG_ERR,"test process err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}
	//Èç¹û²âÊÔ³É¹¦ÈÔÈ»»Ø¹ö
	ret=db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_rollback err,errcode[%d]",ret);
		return	E_TRANS_UNKNOW_ERROR;
	}

	char		dbdate[8 + 1] = "";			//Êý¾Ý¿âÈÕÆÚ
	char 	dbtime[6+1]="";				//Êý¾Ý¿âÊ±¼ä

	//×éÖ¯ÒøÐÐ°ü
		
	memcpy( BankReqPak.msgType,"0200", sizeof(BankReqPak.msgType)-1);					//0//½»Ò×´úÂë   
	BankReqPak.bitMapExt=1;
	//1//À©Õ¹Î»Í¼
	memcpy(BankReqPak.priActNum,from_pos.BankCardNo,19);								//2//Ö÷ÕËºÅ--ÒøÐÐ¿¨ºÅ
	strncpy(BankReqPak.procCode,"488833",sizeof(BankReqPak.procCode)-1);					//3//¹ý³ÌÂë
	BankReqPak.txnAmunt=atol(from_pos.TransMoney);										//4//½»Ò×½ð¶î
	strncpy(BankReqPak.txnDatTim,"0000000000",sizeof(BankReqPak.txnDatTim));				//7//ÒøÐÐºóÌ¨½»Ò×ÈÕÆÚ--ÌîÐ´0
	strncpy(BankReqPak.companyid,"44630021",sizeof(BankReqPak.companyid)-1);				//8//¹«Ë¾´úÂë
	BankReqPak.tracAudNum=(unsigned long)tradeserial.serial_no;								//11//Á÷Ë®ºÅ

	ret=get_datetime_from_db(dbdate, dbtime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		strncpy(dbdate,from_pos.TradeDate,sizeof(dbdate)-1);
		strncpy(dbtime,from_pos.TradeTime,sizeof(dbtime)-1);
	}
	strncpy(BankReqPak.txnLocDat,dbdate+2,4);										//13//½»Ò×ÈÕÆÚ--mmdd
	strncpy(BankReqPak.txnDatTim,dbtime,sizeof(BankReqPak.txnDatTim)-1);				//12//½»Ò×Ê±¼ä--hhmmmm

	memcpy(BankReqPak.datCap,dbdate+4,sizeof(BankReqPak.datCap)-1);						//17//Ö÷»ú½»Ò×Ê±¼ä--´ý¶¨
	strncpy(BankReqPak.teller,"00",sizeof(BankReqPak)-1);									//19//¹ñÔ±ºÅ
	strncpy(BankReqPak.srvTyp,"118",sizeof(BankReqPak.srvTyp)-1);							//21//·þÎñÀàÐÍ
	strncpy(BankReqPak.actTyp,"01",sizeof(BankReqPak.actTyp)-1);							//23//ÕÊºÅÀà±ð
	BankReqPak.pSrvCdCod=11;														//25//·þÎñµã´úÂë
	//strncpy(BankReqPak.pinDat1,"88888888",sizeof(BankReqPak.pinDat1)-1);		//pinÃÜÂë
	strncpy(BankReqPak.acqInstID,"4446301",sizeof(BankReqPak.acqInstID)-1);					//32//ÊÕµ¥»ú¹¹ºÅ
	strncpy(BankReqPak.rspCod,"00",sizeof(BankReqPak.rspCod)-1);							//39//ÒøÐÐ·µ»ØÂë
	strncpy(BankReqPak.termID,"00",sizeof(BankReqPak.termID)-1);							//41//½»Ò×ÖÕ¶ËºÅ
	strncpy(BankReqPak.idenCod,"4446301",sizeof(BankReqPak.idenCod)-1);					//42//½»Ò×ÍøµãºÅ
	strncpy(BankReqPak.agtcus,"4002699752",sizeof(BankReqPak.agtcus)-1);					//43//¿Í»§±êÊ¶
	BankReqPak.pinDat=100;															//52//pindat
	//BankReqPak.
	//strncpy(BankReqPak.chkAct,"23232232",sizeof(BankReqPak.chkAct));
	memcpy(BankReqPak.addAcNo103,from_pos.BankCardNo,19);								//103//ÒøÐÐÕÊºÅ
	
	memset(&head,0,sizeof(head));
	memset(&head_rsp,0,sizeof(head_rsp));

	ret=Pack8583((unsigned char*)head.msg, BankReqPak, 2);
	if(ret<0)
	{
		writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//Ð´°üÍ·
	int recv_length=0;
	int length=ret;
	char tmp_buf[4+1]="";
	sprintf(tmp_buf,"%04d",length+84);
	memcpy(head.length,tmp_buf,4);
	head.pkgtyp[0]=0x30;
	memcpy(head.msgtyp,"0200",sizeof(head.msgtyp));
	memcpy(head.prccde,"488833",sizeof(head.prccde));
	memcpy(head.acqInstID,"44630021",sizeof(head.acqInstID));
	memcpy(head.termID,"00",2);
	memcpy(head.trcno,"00001",5);
	memcpy(head.custyp,"OV",2);
	sprintf(head.cusidt,"%25d",tradeserial.card_id);
	memcpy(head.apcode,"01",2);
	memcpy(head.srvuID,"44630021",sizeof(head.srvuID));
	memcpy(head.rspcde,"00",sizeof(head.rspcde));
	memcpy(head.pkgseq,"01",sizeof(head.pkgseq));
	memcpy(head.filler,"000000",sizeof(head.filler));
	sprintf(tmp_buf,"%04d",ret);
	memcpy(head.msgLen,tmp_buf,4);

	
	//TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//·¢ËÍÊý¾Ýµ½ÒøÐÐ²¢Í¬Ê±½ÓÊÕÒøÐÐÊý¾Ý£¬´Ë´¦²»ÅÐ¶Ï·µ»ØµÄmacÐ£Ñé
	ret=send_to_and_recv_from_bank_of_boc((char*)&head,88+length,(char*)&head_rsp,&recv_length,2500,5000);
	if(ret)
	{
		if(E_TRANS_BANK_NOANSWER==ret)							//Èç¹ûÒøÐÐÃ»ÓÐ·µ»Ø°ü£¬½øÐÐ³åÕý´¦Àí
		{
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;
			}
			writelog(LOG_INFO,"This trade have detrans!");
			return E_TRANS_BANK_NOANSWER;
		}
		else
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
			return ret;
		}
	}
	ret=UnPack8583((unsigned char*)head_rsp.msg,&BankAnsPak,2);
	if(ret)
	{
		writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	if(0!=strncmp(BankAnsPak.rspCod,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.rspCod);
		BankAnsPak.rspCod[2]=0;
		return BOC_RET_NO(BankAnsPak.rspCod);
	}
	//½øÐÐÈëÕÊ²Ù×÷
	//trade_fee=0;
	//board_fee=0;

	//ÌîÐ´ÈëÕË½á¹¹,ÎÊÎÊÎÅ½£
	memset(&IA,0,sizeof(IA));
	des2src(IA.sArrInActno[0],tAccount.account_id);						//ÕÊ»§
	IA.iCardNo=card.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process err,errcode[%d]",ret);
		ret=DelTrans(&from_pos, temp_serial_no);
		if(ret)
		{
			writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
			//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
			return E_TRANS_UNKNOW_ERROR;
		}
		return	E_TRANS_UNKNOW_ERROR;
	}
	char sMsg[255]="";
	char sDebugMsg[255]="";
	sprintf(sDebugMsg,"Á÷Ë®ºÅ:%d ",IA.iSerialNo);
	double trans_amt=0.0;
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		switch(IA.iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial.deposit_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
				tradeserial.boardfee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
				tradeserial.in_fee=IA.dArrOutAmt[i];
				break;
			case TXTYPE_BANK_TRANSFER:
				trans_amt=IA.dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfÔª ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(sDebugMsg,sMsg);
		}
	}
    	sprintf(sMsg,"³äÖµÇ°¿¨Óà¶î:%.2lf ×ªÕÊºó¿¨Óà¶î:%.2lf ",IA.dInCardBala,IA.dOutCardBala);
    	strcat(sDebugMsg,sMsg);
	writelog(LOG_DEBUG,sDebugMsg);
	//double tmp_fee=0;
	//tmp_fee=tradeserial.out_balance;

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(tradeserial.serial_no,&tradeserial_bak);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	//tradeserial.out_balance=tmp_fee;
	tradeserial.serial_state=SERISTAT_DEBT;
	//tradeserial.out_balance=tradeserial.in_balance+tradeserial.trade_fee;
	//tradeserial.boardfee=board_fee;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_tif_tradeserial_free_lock_cur();
	writelog(LOG_ERR,"ou error,error code=[%d]",ret);
	sprintf(pNode->TransMoney,"%f",trans_amt);
	sprintf(pNode->ExtraMoney,"%f",tradeserial.boardfee);
	pNode->RecvNo=tradeserial.serial_no;
	pNode->MngFeeFlag='1';
	writelog(LOG_INFO,"transfer succeed!");
	return 0;
		
}
//POS½É·Ñ
int Pos_Fee(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Pay fee function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//Ôö¼Ó¶ÔÓ¦¹ØÏµ
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Add realation function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//É¾³ý¶ÔÓ¦¹ØÏµ
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Delete relation function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//²éÑ¯Ð£Ô°¿¨×ªÕÊÁ÷Ë®
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID *handle,int *pRetCode,char *szMsg)
{

	char key[32+1]="";
	char pwd[32+1]="";
	//char account_id[16+1]="";
	char account_pwd[6+1]="";
	int ret=0;
	int cnt=0;
	//double unique=0.0;
	INNER_TRANS_REQUEST  from_pos;
	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	T_t_aif_account account;
	T_t_pif_card card;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	//ÅÐ¶ÏÉè±¸ÊÇ·ñµÇÂ½
	if(0!=device_login_yes_or_no(atoi(from_pos.TerminalId)))
	{
		writelog(LOG_ERR,"Device don't login");
		return E_TRANS_TERM_NOLOGIN;
	}

	ret=DB_t_pif_card_read_by_card_id(atoi(from_pos.CardNo),&card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		return E_TRANS_SCHACC_NOEXIT;
	}

	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
		return E_TRANS_SCHCARD_PWDERR;
	}
	if(strncmp(card.state_id,TYPE_YES,1)!=0)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}
	if(STATE_TRUE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}
	ret=DB_t_tif_tradeserial_open_select_by_cur3_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
	if(ret)
	{
			db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
	}
	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	while(1)
	{
		ret=DB_t_tif_tradeserial_fetch_select_by_cur3(&tradeserial);
		if(ret)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial table!");
						break;
					}
				else		break;
			}
			else
				return   E_TRANS_UNKNOW_ERROR;
		}
		cnt++;

		memcpy(from_pos.TradeDate,tradeserial.operate_date,sizeof(from_pos.TradeDate));
		memcpy(from_pos.TradeTime,tradeserial.operate_time,sizeof(from_pos.TradeTime));
		sprintf(from_pos.CardNo,"%d",tradeserial.card_id);
		memcpy(from_pos.BankCardNo,tradeserial.b_act_id,sizeof(from_pos.BankCardNo));
		sprintf(from_pos.TransMoney,"%d",int(tradeserial.trade_fee)*100);
		if(tradeserial.serial_state!=2)
		{
			sprintf(from_pos.RetCode,"%s","Ê§°Ü");
		}
		else sprintf(from_pos.RetCode,"%s","³É¹¦");

		//¿ªÊ¼·µ»ØÓ¦´ð°ü
		Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
		Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
		Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
		Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
		out_pack->lvol0=from_pos.SendNo;
		out_pack->lvol1=from_pos.RecvNo;
		memcpy(out_pack->sdate0,from_pos.TradeDate,sizeof(from_pos.TradeDate));
		memcpy(out_pack->stime0,from_pos.TradeTime,sizeof(from_pos.TradeTime));
		memcpy(out_pack->sdate1,from_pos.BankDate,sizeof(from_pos.BankDate));
		memcpy(out_pack->stime1,from_pos.BankTime,sizeof(from_pos.BankTime));
		Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
		Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
		Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
		out_pack->lvol2=from_pos.Notecase;
		Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
		sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
		Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
		Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
		Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
		Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
		Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));
//	printf("LINE:%d\n",__LINE__);

		PutRow(handle,out_pack,pRetCode,szMsg);
		if(cnt>=10)
		{
			DB_t_tif_tradeserial_close_select_by_cur3();
			break;
		}
	}
//	printf("LINE:%d\n",__LINE__);


	T_t_tif_tradeserial_his tradeserial_his;
	memset(&tradeserial_his,0,sizeof(tradeserial_his));

	if(cnt<10)
	{
		ret=DB_t_tif_tradeserial_his_open_select_by_cur1_and_serial_type_and_card_id(TRADE_INNER_TRANS,card.card_id);
		if(ret)
		{
				db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ALERT,"declare cursor err sqlcode[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
		}
	//	printf("LINE:%d\n",__LINE__);

		while(1)
		{
			ret=DB_t_tif_tradeserial_his_fetch_select_by_cur1(&tradeserial_his);
			if(ret)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				if(ret==DB_NOTFOUND)
				{
					writelog(LOG_DEBUG,"There havn't record from t_tif_tradeserial_his table!");
					break;
				}
				else
					return   E_TRANS_UNKNOW_ERROR;
			}
			cnt++;

			memcpy(from_pos.TradeDate,tradeserial_his.operate_date,sizeof(from_pos.TradeDate));
			memcpy(from_pos.TradeTime,tradeserial_his.operate_time,sizeof(from_pos.TradeTime));
			sprintf(from_pos.CardNo,"%d",tradeserial_his.card_id);
			memcpy(from_pos.BankCardNo,tradeserial_his.b_act_id,sizeof(from_pos.BankCardNo));
			sprintf(from_pos.TransMoney,"%d",int(tradeserial_his.trade_fee)*100);
			if(tradeserial_his.serial_state!=2)
			{
				sprintf(from_pos.RetCode,"%s","Ê§°Ü");
			}
			else sprintf(from_pos.RetCode,"%s","³É¹¦");

			//¿ªÊ¼·µ»ØÓ¦´ð°ü
			Strncpy_t(out_pack->sclose_emp,from_pos.TradeCode,sizeof(out_pack->sclose_emp));
			Strncpy_t(out_pack->sorder0,from_pos.TransMoney,sizeof(out_pack->sorder0));
			Strncpy_t(out_pack->sorder1,from_pos.ExtraMoney,sizeof(out_pack->sorder1));
			Strncpy_t(out_pack->sserial1,from_pos.AccountMoney,sizeof(out_pack->sserial1));
			out_pack->lvol0=from_pos.SendNo;
			out_pack->lvol1=from_pos.RecvNo;
			Strncpy_t(out_pack->sdate0,from_pos.TradeDate,sizeof(out_pack->sdate0));
			Strncpy_t(out_pack->stime0,from_pos.TradeTime,sizeof(out_pack->stime0));
			Strncpy_t(out_pack->sdate1,from_pos.BankDate,sizeof(out_pack->sdate1));
			Strncpy_t(out_pack->stime1,from_pos.BankTime,sizeof(out_pack->stime1));
			Strncpy_t(out_pack->scust_no,from_pos.Balance,sizeof(out_pack->scust_no));
			Strncpy_t(out_pack->schange_emp,from_pos.RetCode,sizeof(out_pack->schange_emp));
			Strncpy_t(out_pack->sserial0,from_pos.CardNo,sizeof(out_pack->sserial0));
			out_pack->lvol2=from_pos.Notecase;
			Strncpy_t(out_pack->scust_auth,from_pos.BankCardNo,sizeof(out_pack->scust_auth));
			sprintf(out_pack->sstatus1,"%c",from_pos.MngFeeFlag);
			Strncpy_t(out_pack->semp_pwd,from_pos.AccountPwd,sizeof(out_pack->semp_pwd));
			Strncpy_t(out_pack->semp_pwd2,from_pos.AccountNewPwd,sizeof(out_pack->semp_pwd2));
			Strncpy_t(out_pack->sstation0,from_pos.BankCardPwd,sizeof(out_pack->sstation0));
			Strncpy_t(out_pack->sstation1,from_pos.BankCardNewPwd,sizeof(out_pack->sstation1));
			Strncpy_t(out_pack->sorder2,from_pos.TerminalId,sizeof(out_pack->sorder2));

			PutRow(handle,out_pack,pRetCode,szMsg);
			if(cnt>=10)
			{
				DB_t_tif_tradeserial_his_close_select_by_cur1();
				break;
			}

		}
	}


	writelog(LOG_INFO,"query trans record succeed!");
	return 0;
}
//È¦´æ»úÐ´¿¨Ê§°Ü³åÕý(Êµ¼Ê²¢²»³åÕý£¬Ö»ÊÇ¸ÄÐ´¿¨×´Ì¬)
int Pos_WriteErrCard(INNER_TRANS_REQUEST * pNode)
{

	int ret = 0;
	int card_id = 0;
	char logicdate[11]="";
	int serial_no=0;
	T_t_pif_card  card;
	T_t_tif_tradeserial tradeserial;

	INNER_TRANS_REQUEST from_pos;

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));
	ret=GetLogicDate(logicdate);								//ÒµÎñÈÕÆÚ
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"GetLogicDate err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	serial_no=from_pos.RecvNo;
	ret=DB_t_tif_tradeserial_read_by_serial_no(serial_no,&tradeserial);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_tif_tradeserial_read_by_serial_no err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	//ÐÞ¸ÄÔ­¿¨×´Ì¬Îª·¢¿¨Ð´¿¨Ê§°Ü×´Ì¬
	card_id = tradeserial.card_id;

	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_read_lock_by_cur_and_card_id err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	memset(card.comments,0,sizeof(card.comments));
	AddXmlItemStr(card.comments, XML_KEY_OPERATEDATE,logicdate);
	AddXmlItemInt(card.comments,XML_KEY_SERIALNO,serial_no);
	AddXmlItemInt(card.comments,XML_KEY_TRADECODE,TRADE_INNER_TRANS);

	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_t_pif_card_update_lock_by_cur err,sqlcode[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	DB_t_pif_card_free_lock_by_cur();

	writelog(LOG_INFO,"update card status succeed!");

	return 0;

}
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

