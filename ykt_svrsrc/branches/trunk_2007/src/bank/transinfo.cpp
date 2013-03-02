/* ----------------------------------------------------------
 * 程序名称：transinfo.h
 * 创建日期：2004-09-09 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：银行转帐各种交易函数实现
 * ----------------------------------------------------------
 * 修改日期: 2005-03-10
 * 修改人员: 林钦
 * 修改描述: 将与银行通信部分移到bank.h，以与bu代码分离，供bankguard调用
 *           此处只保留pos请求处理（包含银行接口调用）
 * 版本信息：1.0.1.1
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
int SetHeadCol(ST_CPACK *in_cpack, ...);


//查询转帐流水
int Pos_QuerySerial(INNER_TRANS_REQUEST * pNode,TRUSERID * handle,int *pRetCode,char *szMsg);
int DelTrans(INNER_TRANS_REQUEST * pnode,int other_serial_no)
{
	int ret=0;
	ret=call_240003();
	if(ret)
	{
		return ret;
	}
	return 0;
}

//POS登陆	240101
int Pos_Login(INNER_TRANS_REQUEST * pNode)
{
	//double unique=0;
	int ret=0;
	INNER_TRANS_REQUEST  from_pos;


	//银行未签到成功，POS不能登陆授予密钥
	if(!BANK_LOGIN)
	{
		writelog(LOG_ERR,"System not login to bank,pos login forbidden!shm[1]=[%d]",shm[1]);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_NETERR);
		return	E_TRANS_BANK_NETERR;
	}

	ret=call_240008();
	if(ret)
	{
		return -1;
	}
	//填充应答包－－－pNode,返回读卡密钥和银行通讯密钥
	memcpy(pNode->BankCardPwd,shm+2+8,sizeof(pNode->BankCardPwd));
	memcpy(pNode->BankCardNewPwd,t_syspara.value,sizeof(pNode->BankCardNewPwd));
	writelog(LOG_INFO,"shm=[%s],pNode->bankcardpwd[%s]",shm,pNode->BankCardPwd);
	return 0;
}


//查询银行卡余额
int Pos_QueryBank(INNER_TRANS_REQUEST * pNode)
{

	int ret=0;
	double bank_balance=0;
	//判断设备是否登录

	//判断操作方式(AUTH_MODE)，如果绑定关系，判断校园卡密码是否正确

	//发送银行查询余额申请包
	ret=Bank_QueryBalance(pNode,&bank_balance);
	if(ret)	return -1;

	sprintf(pNode->Balance,"%9f",bank_balance);
	writelog(LOG_INFO,"Query bank card balance succeed!Balance=[%f]",bank_balance);
	return 0;

}

//修改校园卡密码
int Pos_ChangePwd(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	//判断设备是否登录

	//判断输入密码是否正确

	ret=call_847111();
	if(ret)	return -1;
	return 0;
}

//挂失校园卡

int Pos_LostCard(INNER_TRANS_REQUEST * pNode)
{

  	int ret = 0;
	//判断设备是否登录

	//判断输入密码是否正确

	ret=call_847102();
	if(ret)	return -1;
	return 0;
}

int Pos_UnlostCard(INNER_TRANS_REQUEST * pNode)
{

  	int ret = 0;
	//判断设备是否登录

	//判断输入密码是否正确

	ret=call_847103();
	if(ret)	return -1;
	return 0;

}

//POS转帐
int Pos_Transfer(INNER_TRANS_REQUEST * pNode)
{
	int ret=0;
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));

	//判断设备是否登录

	//判断操作方式(AUTH_MODE)，如果绑定关系，判断校园卡密码是否正确

	//发起模拟入账申请

	ST_CPACK sPack;			 	// 设置发送包
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 240002;
	SetHeadCol(&sPack, F_SORDER2,F_SCUST_AUTH,F_SEMP_PWD,F_SSERIAL0,F_LVOL5,F_LVOL0,F_LVOL6,F_LVOL1,F_LVOL2, 0);       // 设置发送windows BU的头部视图信息
	//memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
	des2src(sPack.pack.sorder2,pNode->TerminalId);
	des2src(sPack.pack.scust_auth,pNode->BankCardNo);
	des2src(sPack.pack.semp_pwd,pNode->AccountPwd);
	des2src(sPack.pack.sserial0,pNode->CardNo);
	sPack.pack.lvol5=atoi(pNode->TransMoney);
	sPack.pack.lvol0=pNode->SendNo;
	sPack.pack.lvol6=atoi(pNode->AccountMoney);
	sPack.pack.lvol1=pNode->RecvNo+1;

	ret = ExtCall(0, 7000, 9000, 0, 4, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
	    if (-2 == ret)
	        return E_TRANS_INNER_TIMEOUT;
	    else
	        return E_TRANS_INNER_TIMEOUT;
	}	
	//如果后台失败,则此处返回后台返回的错误码
	if(aPack.head.retCode)
	{
		return aPack.head.retCode;
	}
	//调用银行接口函数,按照不同的银行转帐接口发送报文并接受应答
	//该函数为通用结构,不同银行接口按照该函数名进行封装转帐报文
	//
	ret=Bank_Transfer(pNode);
	if(ret)
	{
		if(E_TRANS_BANK_NOANSWER==ret)			//如果银行没有返回包，进行冲正处理
		{
			ret=call_240003();		//DelTrans(&from_pos,temp_serial_no);
			if(ret)	writelog(LOG_ERR,"DelTrans error,error code=[%d]",ret);
			return E_TRANS_BANK_NOANSWER;
		}
		else
		{
			writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
			return ret;
		}
	}

	//调用后台正式入账接口
	ResetNormalCPack(&aPack, 0, 1);
	sPack.head.RequestType = 240001;
	ret = ExtCall(0, 7000, 9000, 0, 4, &sPack, &aPack, &ArrayPack);
	if (ret < 0)
	{
	    if (-2 == ret)
	        return E_TRANS_INNER_TIMEOUT;
	    else
	        return E_TRANS_INNER_TIMEOUT;
	}	
	if(aPack.head.retCode)
	{
		return aPack.head.retCode;
	}
	
	sprintf(pNode->TransMoney,"%f",aPack.pack.damt1);
	sprintf(pNode->ExtraMoney,"%f",aPack.pack.damt2);
	pNode->RecvNo=aPack.pack.lvol1;
	pNode->MngFeeFlag='1';
	//writelog(LOG_INFO,"transfer succeed!");
	return 0;
}
//POS缴费
int Pos_Fee(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Pay fee function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//增加对应关系
int Pos_AddRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Add realation function is not support for a while!");

	return E_TRANS_FUNC_NONSUPPORT;
}

//删除对应关系
int Pos_DelRelation(INNER_TRANS_REQUEST * pNode)
{
	//sprintf(pNode->RetCode,"%d",E_TRANS_FUNC_NONSUPPORT);
	writelog(LOG_INFO,"Delete relation function is not support for a while!");
	return E_TRANS_FUNC_NONSUPPORT;
}
//查询校园卡转帐流水
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
	T_t_tif_tradeserial  tradeserial;		//卡操作流水表
	T_t_aif_account account;
	T_t_pif_card card;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&from_pos,0,sizeof(from_pos));
	memset(&account,0,sizeof(account));
	memset(&card,0,sizeof(card));
	memcpy(&from_pos,pNode,sizeof(from_pos));


	//判断设备是否登陆
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

	//判断卡密码是否正确
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
			sprintf(from_pos.RetCode,"%s","失败");
		}
		else sprintf(from_pos.RetCode,"%s","成功");

		//开始返回应答包
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
				sprintf(from_pos.RetCode,"%s","失败");
			}
			else sprintf(from_pos.RetCode,"%s","成功");

			//开始返回应答包
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
//圈存机写卡失败冲正(实际并不冲正，只是改写卡状态)
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
	ret=GetLogicDate(logicdate);								//业务日期
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
	//修改原卡状态为发卡写卡失败状态
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



int Do_Compare( BANK_TRANS_REQUEST *pBankTrans )
{
	char mac_key[32]="";
	char mac[16]="";
	int ret;

	BANK_TRANS_REQUEST BankTransPak;

	memcpy(mac_key,STATIC_KEY,sizeof(mac_key));
	memset(&BankTransPak,0,BANK_TRANS_PACKLEN);

	//写交易代码
	memcpy( BankTransPak.TradeCode,TRADE_BANK_COMP, sizeof(BankTransPak.TradeCode));
	//写交易日期和交易时间
	getsysdate(BankTransPak.TradeDate);
	getsystime(BankTransPak.TradeTime);
	//写院校代码
	sprintf(BankTransPak.CustNo,"%-16s",SCHOOL_CODE);
	//写校验mac码

	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)(&BankTransPak),sizeof(BankTransPak),BankTransPak.MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(&BankTransPak,"send compare package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)(&BankTransPak),BANK_TRANS_PACKLEN, (char*)&BankTransPak,BANK_TRANS_PACKLEN,0);

	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}

	TRACE_BANK_TRANS(&BankTransPak,"recv compare package");


	ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,mac);
	ret=memcmp(mac,BankTransPak.MAC,8);
	if(ret)
	{
		writelog(LOG_INFO,"Mac vertify fail,source_mac=[%s],true_mac[%s]",BankTransPak.MAC,mac);
		return	E_TRANS_BANK_RECVERR;
	}

	memcpy(pBankTrans, &BankTransPak, BANK_TRANS_PACKLEN);

	writelog(LOG_INFO,"Congratulation, compare succeed!");

	return 0;


}
int Do_Compare_file()
{
///*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//配置环境变量
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//不知道为什么，必须要跳一个才能对?
		if((cnt+2)%2==0)	continue;
		//开始进行赋值
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//读取对帐文件结束，关闭对仗文件，提交事务
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//开始进行对帐
	cnt=0;

	//对总数
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		//增加对于非01交易码的交易的排出(比如:冲正)
		if(1!=atoi(bank_comp.tx_code)) 	{continue;}
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	//*/
}
int Do_Compare_file_shoudong()
{
///*
	FILE *fp;
	TIniFile tf;
	char path_name[256]="";
	char file_name[256]="";
	int ret=0;
	int cnt=0;
	int i=0;

	BANK_COMPARE_RECODE compare,compare1;
	T_t_tif_bank_comp	bank_comp;
	T_t_tif_report_trans_comp trans_comp;
	T_t_tif_tradeserial	tradeserial;
	T_t_tif_tradeserial_his his_tradeserial;
	T_t_tif_diff_transfer  diff_transfer;

	char logicdate[10]="";
	char tmp_date[10]="";
	char forward_date[10]="";

	double trans_count=0;
	double bank_count=0;
	double trans_amt=0;
	double bank_amt=0;
	double second=0;

	double temp=0;
	char *p=getenv("BIN_PATH");

	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=datetime2second(logicdate, "YYYYMMDD", &second);
	if(ret)
	{
		writelog(LOG_ERR,"datetime2second error,errcode=[%d]",ret);
		return 	ret;
	}
	 //trans_count=0;
	 //bank_count=0;
	 //trans_amt=0;
	// bank_amt=0;

	second=second-24*60*60;
	ret=second2datetime(second, forward_date, "YYYYMMDD");
	if(ret)
	{
		writelog(LOG_ERR,"second2datetime error,errcode=[%d]",ret);
		return 	ret;
	}

	memset(&bank_comp,0,sizeof(bank_comp));
	memset(&compare,0,sizeof(compare));
	memset(&trans_comp,0,sizeof(trans_comp));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&his_tradeserial,0,sizeof(his_tradeserial));

	memset(&compare1,0x30,sizeof(compare1));

	ret=DB_t_tif_report_trans_comp_read_by_cmp_date(forward_date,&trans_comp);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_report_trans_comp_read_by_cmp_date error,errcode=[%d]",ret);
		goto LRet;
	}
	if(1==trans_comp.cmp_flag)
	{
		writelog(LOG_ERR,"trans_comp.cmp_flag =1,already compare!");
		goto LRet;
	}
	//配置环境变量
	if(p==NULL)
	{
	   	writelog(LOG_ERR,"Cann't get env HOME PATH\n");
	   	return -1;
	}
	//sprintf(path_name,"%s/ftp",p);
	sprintf(path_name,"%s",p);
	//strcpy(path_name,"/bank/ykt/src/bank/ftp");
	sprintf(file_name,"%s/XYK00002.%8.8s",path_name,forward_date);
	writelog(LOG_ERR,"Open indirect file=[%s]",file_name);
	if((fp = fopen(file_name,"rb"))==NULL)
	{
		writelog(LOG_ERR,"Open indirect file error,file=[%s]",file_name);
		return	-1;
	}

	while(!feof(fp))
	{
		memset(&bank_comp,0,sizeof(bank_comp));
		memset(&compare,0,sizeof(compare));
		cnt++;
		if(NULL==fgets((char *)(&compare),sizeof(compare),fp))
		{
			writelog(LOG_ERR,"fgets error,");
			continue;
		}
		//不知道为什么，必须要跳一个才能对?
		if((cnt+2)%2==0)	continue;
		//开始进行赋值
		if(memcmp(&compare,&compare1,10)==0)	break;
		else
		{
			strncpy(bank_comp.op_date,forward_date,sizeof(bank_comp.op_date)-1);
			memcpy(bank_comp.tx_code,compare.TradeCode,2);
			bank_comp.card_id=atoi(compare.GDCAccount);
			memcpy(bank_comp.bankcard,compare.BankCard,20);
			bank_comp.local_sn=atoi(compare.LocalSn);
			//printf("--------local_sn[%d]=[%d]\n",cnt,bank_comp.local_sn);
			memcpy(bank_comp.bank_sn,compare.BankSn,20);
			strncpy(bank_comp.trans_money,compare.TransMomoy,9);

			ret=DB_t_tif_bank_comp_add(&bank_comp);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_tif_bank_comp_add rows[%d] error,errcode=[%d]",cnt,ret);
				goto LRet;
			}
		}
	}
	//读取对帐文件结束，关闭对仗文件，提交事务
	//printf("Line=[%d]\n",__LINE__);
	if(fclose(fp))
	{
		writelog(LOG_ERR,"Close file error,file=[%s]",file_name);
		goto LRet;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}

	//开始进行对帐
	cnt=0;

	//对总数
	ret=DB_his_t_tif_tradeserial_get_count_by_serial_type(&temp,240001,forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_t_tif_tradeserial_get_count_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_count=trans_count+temp;
	trans_comp.localself_num=trans_count;

	ret=DB_his_t_tif_tradeserial_get_sum_by_serial_type(&temp, 240001, forward_date);
	if(ret!=100&&ret!=0)
	{
		writelog(LOG_ERR,"DB_his_t_tif_tradeserial_get_sum_by_serial_type err,errcode=[%d]",ret);
		goto LRet;
	}
	trans_amt=trans_amt+temp;
	trans_comp.localself_amt=trans_amt;

	ret=DB_t_tif_bank_comp_open_select_by_cur1_and_op_date(forward_date);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_bank_comp_open_select_by_cur1_and_op_date err,errcode=[%d]",ret);
		goto LRet;
	}
	while(1)
	{
		ret=DB_t_tif_bank_comp_fetch_select_by_cur1(&bank_comp);
		if(ret)
		{
			DB_t_tif_bank_comp_close_select_by_cur1();
			if(ret==DB_NOTFOUND)
			{
				if(cnt==0)
					{
						writelog(LOG_DEBUG,"There havn't record from t_tif_bankcomp table!");
						break;
					}
				else		break;
			}
			else
				goto LRet;
		}
		cnt++;
		bank_count=bank_count+1;
		bank_amt=bank_amt+atof(bank_comp.trans_money)/100.00;
		memset(&diff_transfer,0,sizeof(diff_transfer));
		//printf("Line=[%d],cnt=[%d]\n",__LINE__,cnt);

		ret=DB_t_tif_tradeserial_his_read_by_bak_date_and_serial_no(forward_date,bank_comp.local_sn,&his_tradeserial);
		//流水表中没有记录的情况
		if(ret)
		{
			if(100==ret)
			{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
				continue;
			}
			else
			{
				writelog(LOG_ERR,"DB_t_tif_tradeserial_his_read_lock_by_c0_and_enteract_date_and_serial_no error,errcode=[%d]!",ret);
				break;
			}
		}
		//流水表中存在，但是没有入账的情况
		if(his_tradeserial.serial_state!=2)
		{
				strncpy(diff_transfer.op_date,forward_date,sizeof(diff_transfer.op_date)-1);
				strncpy(diff_transfer.bankcard,bank_comp.bankcard,sizeof(diff_transfer.bankcard)-1);
				diff_transfer.bank_amt=atoi(bank_comp.trans_money)/100.00;
				strncpy(diff_transfer.bank_sn,bank_comp.bank_sn,sizeof(diff_transfer.bank_sn)-1);
				diff_transfer.card_id=bank_comp.card_id;
				diff_transfer.local_amt=0;
				diff_transfer.local_sn=bank_comp.local_sn;
				diff_transfer.diff_amt=diff_transfer.bank_amt-diff_transfer.local_amt;
				diff_transfer.status=1;
				ret=DB_t_tif_diff_transfer_add(&diff_transfer);
				if(ret)
				{
					writelog(LOG_ERR,"DB_t_tif_diff_transfer_add error,errcode=[%d]!",ret);
					break;
				}
		}
	}

	trans_comp.bankself_amt=bank_amt;
	trans_comp.bankself_num=bank_count;
	trans_comp.localself_amt=trans_amt;
	trans_comp.localself_num=trans_count;
	trans_comp.cmp_flag=1;
	strncpy(trans_comp.cmp_date,forward_date,sizeof(trans_comp.cmp_date)-1);
	ret=DB_t_tif_report_trans_comp_add(&trans_comp);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_tif_report_trans_comp_add error,errcode=[%d]",ret);
		goto LRet;

	}

	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		goto LRet;
	}
	return 0;

LRet:
	db_rollback();
	return ret;

	//*/
}

int Do_Transfer(BANK_TRANS_REQUEST *pBankTrans)
{

	//char buffer[20]="";
	char temp[128]="";
	int ho_OpCount=0;
	int delay_time=0;
	double ho_Fee_Change=0;
	int ret=0;
	FILE *fp;
	TIniFile tf;
	int nrows=0;
	char path_name[128]="";
	char file_name[128]="";
	BANK_TRANSFER_HEAD		trans_head;
	BANK_TRANSFER_RECORD	trans_record;
	T_v_tif_shopdeptfee	v_shopdeptfee;
	T_t_cif_shop		t_shop;

	//系统正在结算，可以生成划拨文件
	//sleep(1);
	//ret=DB_v_tif_shopdeptfee_read_sum_fee(&ho_OpCount,&ho_Fee_Change);
	if(ret)
	{
		writelog(LOG_ERR,"DB_v_tif_shopdeptfee_read_sum_fee err [%d]",ret);
		return ret;
	}
	ho_OpCount=4;
	ho_Fee_Change=12345.98;
	strcpy(path_name,"/ykt/ykt/src/bank/ftp");
	sprintf(file_name,"%s/fd_%8.8s",path_name,getsysdate(NULL));

	#ifdef DEBUG
	//	strcpy(path_name,"./ftp/fd_20041009");
		writelog(LOG_ALERT,"file_name2=[%s]",file_name);
	#endif

	fp = fopen(file_name,"wb");
	if (fp==NULL)
	{
		writelog(LOG_ALERT,"Open indicate file fail");
		return -1;
	}
	memcpy(trans_head.rmb_batch_no,BATCH_NO,sizeof(trans_head.rmb_batch_no));
	fprintf(fp,"%-14.14s",trans_head.rmb_batch_no);		//批量编号

	memcpy(trans_head.rmb_start_seq,"000000",6);
	fprintf(fp,"%-6.6s",trans_head.rmb_start_seq);			//填000000

	trans_head.rmb_acc_status='0';
	fprintf(fp,"%c",trans_head.rmb_acc_status);			//记帐状态（填0）

	trans_head.rmb_chk_status='2';
	fprintf(fp,"%c",trans_head.rmb_chk_status);			//检查状态（填2）

	sprintf(trans_head.rmb_total_amount,"%-13d",int(ho_Fee_Change*100));
	fprintf(fp,"%-13.13s",trans_head.rmb_total_amount);		//总金额(11位整数2位小数，无小数点)

	sprintf(trans_head.rmb_total_num,"%-6d",ho_OpCount);
	fprintf(fp,"%-6.6s",trans_head.rmb_total_num);			//总笔数

	fprintf(fp,"%-13.13s",trans_head.rmb_enter_amount);	//入帐金额

	fprintf(fp,"%-6.6s",trans_head.rmb_enter_num);			//入帐笔数

	sprintf(trans_head.rmb_unit_name,"%-40s",UNIT_NAME);
	fprintf(fp,"%-40.40s",trans_head.rmb_unit_name);		//单位名称
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_name=[%s]",trans_head.rmb_unit_name);
#endif

	strcpy(trans_head.rmb_unit_account,UNIT_ACCOUNT);
	//sprintf(trans_head.rmb_unit_account,"%-20s"UNIT_ACCOUNT);
	fprintf(fp,"%-20.20s",trans_head.rmb_unit_account);		//单位帐号
#ifdef DEBUG
	writelog(LOG_ALERT,"trans_head.rmb_unit_account=[%s]",trans_head.rmb_unit_account);
#endif

	memcpy(trans_head.rmb_apply_date,getsysdate(NULL),sizeof(trans_head.rmb_apply_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_apply_date);			//申请入帐日期（当天日期）

	//memcpy(trans_head.rmb_send_date,trans_head.rmb_apply_date,sizeof(trans_head.rmb_apply_date));
	memcpy(trans_head.rmb_send_date,getsystime(NULL),sizeof(trans_head.rmb_send_date));
	fprintf(fp,"%-8.8s",trans_head.rmb_send_date);			//上传日期（当天日期）

#ifdef DEBUG
	printf("[%14.14s]\n",trans_head.rmb_batch_no      ); 	//批量编号
	printf("[%6.6s]\n",trans_head.rmb_start_seq      ); 		//填000000
	printf("[%c]\n",trans_head.rmb_acc_status        ); 		//记帐状态（填0）
	printf("[%c]\n",trans_head.rmb_chk_status        ); 		//检查状态（填2）
	printf("[%13.13s]\n",trans_head.rmb_total_amount  ); 	//总金额(11位整数2位小数，无小数点)
	printf("[%6.6s]\n",trans_head.rmb_total_num      ); 	//总笔数
	printf("[%13.13s]\n",trans_head.rmb_enter_amount ); 	//入帐金额(11位整数2位小数，无小数点)
	printf("[%6.6s]\n",trans_head.rmb_enter_num     ); 	//入帐笔数
	printf("[%40.40s]\n",trans_head.rmb_unit_name    ); 	//单位名称
	printf("[%20.20s]\n",trans_head.rmb_unit_account  ); 	//单位帐号
	printf("[%8.8s]\n",trans_head.rmb_apply_date     ); 	//申请入帐日期（当天日期）
	printf("[%8.8s]\n",trans_head.rmb_send_date     );  	//上传日期（当天日期）
#endif

	//写入划拨文件
	// fprintf(fp,(char*)(&trans_head));
	strcpy(temp,"1");
	ret=DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep(temp);
	if(ret)
	{
		//db_chk_err(__FILE__,__LINE__,&sqlca);
		writelog(LOG_ALERT,"DB_v_tif_shopdeptfee_open_select_by_c6_and_is_indep[%d]",ret);
		return ret;
	}

	while(1)
	{
		//初始化宿主变量
		ho_Fee_Change=0;
		memset(&v_shopdeptfee,0,sizeof(v_shopdeptfee));
		memset(&t_shop,0,sizeof(t_shop));
		ret=DB_v_tif_shopdeptfee_fetch_select_by_c6(&v_shopdeptfee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(0==nrows)
				{
					writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
					break;
				}
				else		break;	//循环记录结束
			}
			else
			{
				//db_chk_err(__FILE__,__LINE__,&sqlca);
				writelog(LOG_ERR,"DB_v_tif_shopdeptfee_fetch_select_by_c6[%d]",ret);
				return ret;
			}
		}
		ret=DB_t_cif_shop_read_by_shop_id(v_shopdeptfee.shop_id,&t_shop);
		if(ret)
		{
			//db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ALERT,"DB_t_cif_shop_read_by_shop_id[%d]",ret);
			return ret;
		}
		strcpy(trans_record.rmb_batch_no1,BATCH_NO);
		sprintf(trans_record.rmb_seq_no,"%d",nrows);
		trans_record.rmb_acc_status1='0';
		trans_record.rmb_tran_kind='2';
		strncpy(trans_record.rmb_cust_name,t_shop.b_act_name,sizeof(trans_record.rmb_cust_name));
		strncpy(trans_record.rmb_acc_no,t_shop.b_act_id,sizeof(trans_record.rmb_acc_no));
		trans_record.rmb_cb_cr='0';
		sprintf(trans_record.rmb_tran_amt,"%f",ho_Fee_Change);
		strcpy(trans_record.rmb_cur_code,"001");
		strcpy(trans_record.rmb_host_no,"00000000");
		memcpy(trans_record.rmb_ret_code,"    ",sizeof(trans_record.rmb_ret_code));
		strcpy(trans_record.rmb_acc_date,"00000000");
		strcpy(trans_record.rmb_host_no1,"000000000");
		strcpy(trans_record.rmb_open_branch,"0000000");
		memcpy(trans_record.rmb_vcho_kind,"  ",sizeof(trans_record.rmb_vcho_kind));
		strcpy(trans_record.rmb_vcho_bat_no,"00");
		strcpy(trans_record.rmb_vcho_no,"000000000");
		strcpy(trans_record.rmb_memo,"  ");
		strcpy(trans_record.rmb_tran_info,"  ");

		fprintf(fp,(char*)(&trans_record));

		nrows++;
	}
	fclose(fp);
	memset(pBankTrans,0,BANK_TRANS_PACKLEN);
	//开始银行发送清算报文
	memcpy( pBankTrans->TradeCode,TRADE_BANK_BALANCE, sizeof(pBankTrans->TradeCode));	//写交易代码
	//写交易日期和交易时间
	getsysdate(pBankTrans->TradeDate);
	getsystime(pBankTrans->TradeTime);
	//写院校代码
	sprintf(pBankTrans->CustNo,"%-16s",SCHOOL_CODE);
	//写银行卡号-此处约定为划拨文件名
	sprintf(pBankTrans->BankCardNo,"%8.8s",getsysdate(NULL));
	//写校验mac码
	//写校验mac码----林钦此处应该用银行回传回来的动态密钥做mac密钥，此处改过来了
	generate_mac((char*)pBankTrans,sizeof(pBankTrans),pBankTrans->MAC);
	//ANSIX99(mac_key,(char*)(&BankTransPak), BANK_TRANS_PACKLEN-LEN_MAC,BankTransPak.MAC);

	TRACE_BANK_TRANS(pBankTrans,"send transfer package");

	//发送数据到银行并同时接收银行数据，此处不判断返回的mac校验
	ret=send_to_and_recv_from_bank((char*)pBankTrans,BANK_TRANS_PACKLEN, (char*)pBankTrans,BANK_TRANS_PACKLEN,delay_time);
	if(ret)
	{
		writelog(LOG_ERR,"send_to_and_recv_from_bank error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	TRACE_BANK_TRANS(pBankTrans,"recv transfer package");

	//农行暂时未校验该mac,所以暂时屏蔽掉

	ret=check_mac((char*)pBankTrans,BANK_TRANS_PACKLEN);
	if(ret)
	{
		writelog(LOG_ERR,"Receive data mac verify error,error code is [%d] ",ret);
		//sprintf(pNode->RetCode,"%d",E_TRANS_BANK_RECVERR);
		return	E_TRANS_BANK_RECVERR;
	}
	writelog(LOG_INFO,"Congratulation, transer succeed!");

	return 0;
}

//判断该设备是否签到过
int device_login_yes_or_no(int device_id)
{
	int ret=0;
	T_t_pif_device t_device;

	memset(&t_device,0,sizeof(t_device));
	ret=DB_t_pif_device_read_by_device_id(device_id,&t_device);
	if(ret)
	{
		writelog( LOG_ERR,"DB_t_pif_device_read_by_device_id error,errcode=[%d],device_id=[%d]",ret,device_id);
		return ret;
	}
	//writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",device_id,t_device.state_id);
	if(DEVISTAT_ONLINE!=t_device.state_id)
	{
		writelog( LOG_ERR,"Device don't login,device_id=[%d],login_flag=[%d]",device_id,t_device.state_id);
		return 9999;
	}
	return 0;
}

int SetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) != 0)
	{
		SetParmBit(&(in_cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}
