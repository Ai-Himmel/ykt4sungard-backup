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


#ifndef	DEBUG	
	#define	DEBUG	
#endif
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);


 
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
	tradeserial.maindevice_id=WORKSTATION_NO;				//×ÓÏµÍ³ºÅÂë
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

static int process(InAcc *IA,T_t_tif_tradeserial *p,double *trade_fee,double *board_fee)
{
	int ret=0;
	double boardfee=0.00;			//´î»ï·Ñ
	double maxfeeratio = 0;			//±ÈÂÊ
	T_t_pif_card card;					//¿¨ÐÅÏ¢±í
	T_t_cif_shop		shop;			//ÉÌ»§ÐÅÏ¢±í
	T_t_aif_account	account;		//ÕÊ»§±í
	T_t_cif_cuttypefee cuttypefee;		//¿Í»§Àà±ðÊÕ·Ñ±í
	
	memset(&cuttypefee,0,sizeof(cuttypefee));
	memset(&card,0,sizeof(card));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));

	//¸ù¾Ý¿¨ºÅºÍÇ®°üºÅµÃµ½Ïû·ÑÕßÕËºÅ(½è·½)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(p->card_id, p->purse_id,&account);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret=[%d]card_id=[%d]purse_id=[%d]",ret,p->card_id, p->purse_id);
		if(DB_NOTFOUND==ret)
			return	E_ACTNO_NOT_EXIST;
		else
			return	E_DB_ACCOUNT_R;
	}	
	ret=DB_t_cif_cuttypefee_read_by_cut_type(account.cut_type,&cuttypefee);
	if(ret)
	{
		writelog(LOG_ERR,"cuttype[%d]",account.cut_type);
		if(DB_NOTFOUND==ret)
			return E_CUTTYPEFEE_N;
		else
			return E_CUTTYPEFEE_R;
	}
	if(amtcmp(account.cur_bala+p->trade_fee,cuttypefee.max_bala)>=0)
	{
		return E_AMT_EXCEED_MAX;
	}
	if(strncmp(cuttypefee.is_outfee,TYPE_YES,1)==0)
	{
		ret=GetMaxFeeRatioFromShop(&maxfeeratio);
		if(ret)
			return ret;
		boardfee=D4U5(p->trade_fee *maxfeeratio,2);
		p->trade_fee=D4U5(p->trade_fee-boardfee,2);
		p->boardfee=boardfee;
	}
	*trade_fee=p->trade_fee;
	*board_fee=p->boardfee;
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
	strcpy(IA->sTalOper,p->oper_code);				//²Ù×÷Ô±

	strcpy(IA->sActno[0],account.account_id);			//ÕËºÅ

	IA->iUseCardFlag=IS_YES;						//¿¨½»Ò×
	IA->dInCardBala=p->in_balance;				//Èë¿¨Öµ
	IA->dAmt[0]=p->trade_fee;					//·¢Éú¶î
	IA->dAmt[1]=p->boardfee;						//´î»ï·Ñ
	
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
	T_t_pif_cur_syspara t_syspara;


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
//	char buffer[1024]="";


	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	struct SockNode SockNode;
	
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
		

	//×éÖ¯ÒøÐÐ°ü
	//Ð´½»Ò×´úÂë
	memcpy( BankReqPak.TradeCode,TRADE_BANK_QUERY, BANK_TRADE_CODE_LEN);
	//Ð´½»Ò×ÈÕÆÚºÍ½»Ò×Ê±¼ä
	ret=get_datetime_from_db(BankReqPak.TradeDate,BankReqPak.TradeDate);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
		memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	}
	//memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	//memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//Ð´ÒøÐÐ¿¨ºÅ×Ö¶Î
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//Ð´ÒøÐÐ¿¨ºÅ×Ö¶Î
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);
	//Ð´ÒøÐÐ¿¨ÃÜÂë×Ö¶Î
	//Í¨¹ý16½øÖÆ¸ñÊ½´«Êä£¬ÔÙ½âÃÜ
	hex2dec(from_pos.BankCardPwd, (unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));
	#ifdef DEBUG
		char buffer[100]="";
		int k=0;
		for(int i=0;i<16;i++)
		{
			k=(unsigned char)BankReqPak.BankCardPwd[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		writelog(LOG_INFO,"BankCardNo=[%s],BankCardPwd=[%s]",BankReqPak.BankCardNo,buffer);
		writelog(LOG_INFO,"BankCardNo=[%s],fromCardPwd=[%s]",BankReqPak.BankCardNo,from_pos.BankCardPwd);
	#endif

	//Ð´Ð£Ô°¶ËÁ÷Ë®ºÅ
	sprintf(BankReqPak.CustSn,"%-8f",unique);
	//Ð´ÔºÐ£´úÂë
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);
	BankReqPak.AutoFlag='0';
	//Ð´Ð£ÑémacÂë
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);
	
	//memcpy(SockNode.Buf,&BankReqPak,sizeof(BankReqPak));
	TRACE_BANK_TRANS(&BankReqPak,"send query bank package");

	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	

	TRACE_BANK_TRANS(&BankAnsPak,"receivce query bank package");

	//Å©ÐÐÔÝÊ±Î´Ð£Ñé¸Ãmac,ËùÒÔÔÝÊ±ÆÁ±Îµô
	/*
	ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	*/
	//¸ü¸ÄÊý¾Ý¿âÁ÷Ë®ÈÕÖ¾,°üÀ¨ÌîÐ´Ò»Ð©¶îÍâ×Ö¶ÎÒÔ¼°ÌîÐ´ÒøÐÐ·µ»ØÐÅÏ¢µÈ£­£­£­£­ÔÝÊ±ÆÁ±ÎÃ»×÷
	/*	
	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(int(unique), &tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"read from t_tif_tradeserial table error,error code=[%d]",ret);
		sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
		db_rollback();
		return 	E_TRANS_UNKNOW_ERROR;	
	}
	*/
	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//ÒøÐÐ¿¨¹ÒÊ§
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//ÒøÐÐ¿¨×´Ì¬´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//ÒøÐÐ¿¨½ð¶î²»×ã
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//ÒøÐÐÎ´Öª´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//ÒøÐÐÃÜÂë´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//Í¨Ñ¶»òÃÜÔ¿´í
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//ÆäËûÎ´Öª´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}

	//Ìî³äÓ¦´ð°ü
	//sprintf(pNode->RetCode,"%d",SUCCEED);
	memcpy(pNode->Balance,BankAnsPak.Balance,sizeof(pNode->Balance));
	writelog(LOG_INFO,"query bank card balance succeed!bank card money=[%s]",BankAnsPak.Balance);
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
	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
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
	char		sCardState[5] = "";

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
	maindevice_id = WORKSTATION_NO;											//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	device_id = atoi(from_pos.TerminalId);										//²É¼¯Éè±¸±êÊ¶

	//ÅÐ¶Ï¿¨ÃÜÂëÊÇ·ñÕýÈ·
	strcpy(key,STATIC_SEED_KEY);
	Strncpy_t(account_pwd, from_pos.AccountPwd,sizeof(account_pwd));
	EncodePwd(key,account_pwd,pwd, 0);

	if(0!=memcmp(pwd,card.password,sizeof(pwd)))
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"Card password error,clear_pwd[%s],input_pwd=[%s],db_pwd=[%s]",account_pwd,pwd,card.password);
		//sprintf(pNode->RetCode,"%d",E_TRANS_SCHCARD_PWDERR);
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
	//	²åÈë¿¨¹ÒÊ§ÓÐÐ§ÆÚÏÞ±í
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
	//Èç¹û¸Ã¿¨ºÅ±»¶³½á,Ôò¹ÒÊ§Ê±¶ÔºÚÃûµ¥²»´¦Àí
	if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//	²åÈëºÚÃûµ¥±í
		black_sheet.card_id = card_id;
		black_sheet.is_ad = ADD_BLACKLIST;
		des2src(black_sheet.operate_date,sysdate);									
		des2src(black_sheet.operate_time,systime);									
		memcpy(black_sheet.volume,sysdate+2,6);
		memcpy(black_sheet.volume+6,systime,6);
		strcpy(black_sheet.validdate,VALIDDATE);
		black_sheet.state_id = STATE_VALID;

		ret = DB_t_tif_black_sheet_add(&black_sheet);
		if (ret)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"DB_t_tif_black_sheet_add=[%d]",ret);
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
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"AddMsgLst=[%d]",ret);
			return E_TRANS_UNKNOW_ERROR;
		}			
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
	tradeserial.maindevice_id = WORKSTATION_NO;						//ÉÏ´«¹¤×÷Õ¾±êÊ¶
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
	maindevice_id = WORKSTATION_NO;											//ÉÏ´«¹¤×÷Õ¾±êÊ¶
	device_id = atoi(from_pos.TerminalId);										//²É¼¯Éè±¸±êÊ¶

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
	tradeserial.maindevice_id = WORKSTATION_NO;										//ÉÏ´«¹¤×÷Õ¾±êÊ¶
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
	char buffer[16]="";

	INNER_TRANS_REQUEST  from_pos;
	BANK_TRANS_REQUEST BankReqPak,BankAnsPak;
	T_t_tif_tradeserial  tradeserial;		//¿¨²Ù×÷Á÷Ë®±í
	T_t_tif_tradeserial  tradeserial_bak;		
	T_t_pif_card		card;
	InAcc	IA;

	memset(&tradeserial_bak,0,sizeof(tradeserial_bak));
	memset(&from_pos,0,sizeof(from_pos));
	memset(&BankReqPak,0,sizeof(BankReqPak));
	memset(&BankAnsPak,0,sizeof(BankAnsPak));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&card,0,sizeof(card));

	memcpy(&from_pos,pNode,sizeof(from_pos));


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
	Strncpy_t(tradeserial.enteract_date,tradeserial.operate_date,sizeof(tradeserial.enteract_date));	//ÈëÕÊÈÕÆÚ
	Strncpy_t(tradeserial.enteract_time,tradeserial.operate_time,sizeof(tradeserial.enteract_time));	//ÈëÕÊÊ±¼ä
	tradeserial.maindevice_id=WORKSTATION_NO;	//×ÓÏµÍ³ºÅÂë
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
	memset(&IA,0,sizeof(IA));
	ret=process(&IA,&tradeserial_bak,&trade_fee,&board_fee);
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
	
	//×éÖ¯ÒøÐÐ°ü
	memcpy( BankReqPak.TradeCode,TRADE_BANK_TRANS, BANK_TRADE_CODE_LEN);	//Ð´½»Ò×´úÂë
	memcpy(BankReqPak.TradeDate,from_pos.TradeDate,sizeof(BankReqPak.TradeDate));
	memcpy(BankReqPak.TradeTime,from_pos.TradeTime,sizeof(BankReqPak.TradeTime));
	//ÓÉÓÚÒøÐÐ¸øµÄ½Ó¿ÚÖÐµÄÐ£Ô°¿¨ÕËºÅ×Ö¶ÎÖ»ÓÐ10¸ö³¤¶È
	//ËùÒÔÕâÀïÔÚÐ£Ô°¿¨ÕËºÅ×Ö¶ÎÉÏÌîÐ´Ð£Ô°¿¨¿¨ºÅ
	sprintf(BankReqPak.CustAccountNo,"%-10d",atoi(from_pos.CardNo));
	/*
	//Ð´Ð£Ô°¿¨ÕÊºÅ
	ret=GetActnoByCardIdAndPurseId(BankReqPak.CustAccountNo,atoi(from_pos.CardNo),from_pos.Notecase);
	if(ret)
	{
		writelog(LOG_ERR,"GetActnoByCardIdAndPurseId error,CardNo=[%s],Notecase=[%d]",from_pos.CardNo,from_pos.Notecase);
		return E_TRANS_UNKNOW_ERROR;
	}
	*/
	//sprintf(BankReqPak.BankCardNo,"%-20s","1030399110000001042");	//Ð´ÒøÐÐ¿¨ºÅ×Ö¶Î
	sprintf(BankReqPak.BankCardNo,"%-20s",from_pos.BankCardNo);	//Ð´ÒøÐÐ¿¨ºÅ×Ö¶Î
	memcpy(BankReqPak.MercAccount,SCHOOL_ACCOUNT_NO,sizeof(BankReqPak.MercAccount));	//Ð´ÉÌ»§ºÅ×Ö¶Î
	sprintf(BankReqPak.TransMoney,"%-9s",from_pos.TransMoney);	//Ð´×ªÕÊ½ð¶î×Ö¶Î
	//Í¨¹ý16½øÖÆ´«Êä£¬È»ºó½âÃÜ
	hex2dec(from_pos.BankCardPwd,(unsigned char*)BankReqPak.BankCardPwd, 8);
	//memcpy(BankReqPak.BankCardPwd,from_pos.BankCardPwd,sizeof(BankReqPak.BankCardPwd));	//Ð´ÒøÐÐ¿¨ÃÜÂë×Ö¶Î
	sprintf(BankReqPak.CustSn,"%-d",tradeserial.serial_no);	//Ð´Ð£Ô°¶ËÁ÷Ë®ºÅ
	sprintf(BankReqPak.CustNo,"%-16s",SCHOOL_CODE);	//Ð´ÔºÐ£´úÂë
	BankReqPak.AutoFlag='0';	//Ð´×Ô¶¯×ÔÖú±êÖ¾
	generate_mac((char*)(&BankReqPak),sizeof(BankReqPak),BankReqPak.MAC);//Ð´Ð£ÑémacÂë

	TRACE_BANK_TRANS(&BankReqPak,"send transfer package");

	//·¢ËÍÊý¾Ýµ½ÒøÐÐ²¢Í¬Ê±½ÓÊÕÒøÐÐÊý¾Ý£¬´Ë´¦²»ÅÐ¶Ï·µ»ØµÄmacÐ£Ñé
	ret=send_to_and_recv_from_bank((char*)(&BankReqPak),sizeof(BankReqPak),(char*)(&BankAnsPak),sizeof(BankAnsPak),0);
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

	TRACE_BANK_TRANS(&BankAnsPak,"receive transfer package");

	//Ð£Ñémac£¬ÅÐ¶ÏÒøÐÐ½ÓÊÕ°üÊÇ·ñÕýÈ·
	//ret=check_mac((char*)(&BankAnsPak), sizeof(BankAnsPak));
	ret=0;
	if(ret)
	{
			writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
			ret=DelTrans(&from_pos,temp_serial_no);
			if(ret)
			{
				writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return E_TRANS_UNKNOW_ERROR;	
			}
			ret=db_commit();
			if(ret)
			{
				writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
				return E_TRANS_UNKNOW_ERROR;
			}
			//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
			return	E_TRANS_BANK_RECVERR;
	}

	if(0!=strncmp(BankAnsPak.RetCode,RET_BANK_OK,2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%s] ",BankAnsPak.RetCode);
		BankAnsPak.RetCode[2]=0;
		switch(atoi(BankAnsPak.RetCode))
		{
			case 1:		//ÒøÐÐ¿¨¹ÒÊ§
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_LOST);
				return	E_TRANS_BANKCARD_LOST;
			case 2:		//ÒøÐÐ¿¨×´Ì¬´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_STATERR);
				return	E_TRANS_BANKACC_STATERR;
			case 3:		//ÒøÐÐ¿¨½ð¶î²»×ã
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKACC_NOMONEY);
				return	E_TRANS_BANKACC_NOMONEY;
			case 4:		//ÒøÐÐÎ´Öª´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NODECIDE);
				return	E_TRANS_BANK_NODECIDE;
			case 5:		//ÒøÐÐÃÜÂë´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANKCARD_PWDERR;
			case 6:		//Í¨Ñ¶»òÃÜÔ¿´í
				//sprintf(pNode->RetCode,"%d",E_TRANS_BANKCARD_PWDERR);
				return	E_TRANS_BANK_NETERR;
			default:		//ÆäËûÎ´Öª´íÎó
				//sprintf(pNode->RetCode,"%d",E_TRANS_UNKNOW_ERROR);
				return	E_TRANS_UNKNOW_ERROR;
		}
	}
	//½øÐÐÈëÕÊ²Ù×÷
	trade_fee=0;
	board_fee=0;
	memset(&IA,0,sizeof(IA));
	ret=process(&IA,&tradeserial,&trade_fee,&board_fee);
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

	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(tradeserial.serial_no,&tradeserial);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;	
	}
	tradeserial.serial_state=SERISTAT_DEBT;
	tradeserial.out_balance=tradeserial.in_balance+trade_fee;
	tradeserial.boardfee=board_fee;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		writelog(LOG_ERR,"DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;	
	}
	DB_t_tif_tradeserial_free_lock_cur();
	
	sprintf(pNode->TransMoney,"%f",trade_fee);
	sprintf(pNode->ExtraMoney,"%f",board_fee);
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

