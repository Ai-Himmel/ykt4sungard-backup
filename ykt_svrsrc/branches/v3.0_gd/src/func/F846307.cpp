/* --------------------------------------------
 * 创建日期: 2008-06-23
 * 程序作者:闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通挂失解挂
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"

int DoLossCard(int cardno)
{
    int ret=0;
    T_t_card tCard;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
	
    memset(&tCard,0,sizeof(tCard));
    ret=DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
    if (ret)
    {
        writelog(LOG_ERR,"cardno[%d]",cardno);
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDNO,cardno);
        else
            return E_DB_CARD_R;
    }
	des2src(trans.showcardno,tCard.showcardno);
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==tCard.badflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	//去掉锁定标志
	tCard.lockflag[0]='0';
	tCard.lockdate[0]=0;
    tCard.lossflag[0]='1';
    des2src(tCard.lossdate,trans.transdate);
	double second = 0;
	char lossdatetime[21]="";
	strncpy(lossdatetime,trans.transdate,8);
	strncat(lossdatetime,trans.transtime,6);
	ret=datetime2second(lossdatetime, "YYYYMMDDHHMMSS", &second);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
	second += pAccTrans->sysPara.iLossEffectTime*60;
	ret=second2datetime(second,tCard.lossefttime, "YYYYMMDDHHMMSS");
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
    ret=getCardVerNo(tCard.cardverno);
	if(ret)
	{
		DB_t_card_free_lock_by_cur();
		return ret;
	}
    des2src(tCard.lastsaved,trans.sysdatetime);
    ret=DB_t_card_update_lock_by_cur(&tCard);
    if (ret)
    {
        writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
        if (DB_NOTFOUND==ret)
            return E_NOTEXIST_CARDNO;
        else
            return E_DB_CARD_U;
    }
	T_t_customer customer;
	memset(&customer,0,sizeof(customer));
    if (tCard.custid)
    {
        ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
        if (ret)
        {
            if (DB_NOTFOUND==ret)
                return E_NOTEXIST_CUSTOMER;
            else
                return E_DB_CUSTOMER_R;
        }
        trans.custid=tCard.custid;
        des2src(trans.custname,customer.custname);
        des2src(trans.stuempno,customer.stuempno);
    }
    //修改以前的解挂记录为删除状态
    UpdCardVerStatus(cardno,CARDVERTYPE_CARDUNLOSS);
	//更新系统黑名单最大版本号
	ret=SetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,tCard.cardverno);
	if(ret)
	{
		return ret;
	}
    T_t_cardver cardver;
    memset(&cardver,0,sizeof(cardver));
    cardver.cardno=tCard.cardno;
    des2src(cardver.accdate,pAccTrans->trans.accdate);
    cardver.termid=trans.termid;
    cardver.termseqno=trans.termseqno;
    cardver.cardno=tCard.cardno;
    des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,customer.stuempno);	
    cardver.cardvertype=CARDVERTYPE_CARDLOSS;
    cardver.adddelflag[0]=ADDDELFLAG_ADD;
    cardver.status[0]=STATUS_NORMAL;
    des2src(cardver.cardverno,tCard.cardverno);
    ret=DB_t_cardver_add(&cardver);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_CARDVER_E;
        else
            return E_DB_CARDVER_I;
    }
    des2src(trans.summary,cardver.cardverno);
	char broadcastblkflag[20]={0};
	ret=GetSysParaVal(SYSPARA_BROADCASTBLKLIST,broadcastblkflag);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_SYSKEY_R;
	}
	if(broadcastblkflag[0]!='1')
		return 0;	T_t_msglist tMsgList;
	memset(&tMsgList,0,sizeof(tMsgList));
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDID,tCard.cardno);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_VERNUM,tCard.cardverno);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_ADDDELSIGN,0);	//增删标志

	tMsgList.funcno = 930005;
	tMsgList.pfuncno = 846307;
	tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
	tMsgList.msgtype = MESLIST_TYPE_ORDER;
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}
    return 0;
}
int DoUnlossCard(int cardno)
{
    int ret=0;
    T_t_card tCard;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    trans.transcode=TC_CARDUNLOSS;

    memset(&tCard,0,sizeof(tCard));
    ret=DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
    if (ret)
    {
        writelog(LOG_ERR,"cardno[%d]",cardno);
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDNO,cardno);
        else
            return E_DB_CARD_R;
    }
	des2src(trans.showcardno,tCard.showcardno);
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
//	if('1'!=tCard.lossflag[0])
//	{
//		DB_t_card_free_lock_by_cur();
//		return ERRINFO(E_CARDNO_NOLOST,trans.cardno);
//	}	
	if('1'==tCard.frozeflag[0])
	{
		DB_t_card_free_lock_by_cur();
		ERRTIP("请先解冻后再解挂");
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.badflag[0])
	{
		DB_t_card_free_lock_by_cur();
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	//判断是否存在过渡临时卡
	if(CARDTYPE_TEMP!=tCard.cardtype)
	{
		ret=IsExistNormalTmpCardByCustid(tCard.custid);
		if(ret)
		{
			DB_t_card_free_lock_by_cur();
			if(DB_EXIST==ret)
			{
				//锁定该卡,该卡只能销户
				ERRTIP("该客户存在卡状态正常的过渡临时卡,请先退掉过卡状态正常的渡临时卡再解挂");
				return E_EXIST_NORMALCARD;
			}
			else
				return ret;
		}
	}
	else
	{
		//检查是否存在其他正常的卡
		ret=IsExistOtherNormalCardByCustid(tCard.custid,tCard.cardno);
		if(ret)
		{
			if(DB_EXIST==ret)
			{
				//锁定该卡,该卡只能销户
				TIPINFO("该客户存在卡状态正常的其他卡,该卡解挂后将不能再使用,请解挂后注销该卡!");
				tCard.lockflag[0]='1';		
				des2src(tCard.lockdate,trans.accdate);
			}
			else
			{	
				DB_t_card_free_lock_by_cur();
				return ret;
			}
		}
	}
	tCard.lossflag[0]='0';
    tCard.lossdate[0]=0;
	tCard.lossefttime[0]=0;
    ret=getCardVerNo(tCard.cardverno);
    if (ret)
    {		
		DB_t_card_free_lock_by_cur();
        return ret;
    }
    des2src(tCard.lastsaved,trans.sysdatetime);
    ret=DB_t_card_update_lock_by_cur(&tCard);
    if (ret)
    {
        writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
        if (DB_NOTFOUND==ret)
            return E_NOTEXIST_CARDNO;
        else
            return E_DB_CARD_U;
    }
	T_t_customer customer;
	memset(&customer,0,sizeof(customer));
    if (tCard.custid)
    {
        ret=DB_t_customer_read_by_custid(tCard.custid,&customer);
        if (ret)
        {
            if (DB_NOTFOUND==ret)
                return E_NOTEXIST_CUSTOMER;
            else
                return E_DB_CUSTOMER_R;
        }
        trans.custid=tCard.custid;
        des2src(trans.custname,customer.custname);
        des2src(trans.stuempno,customer.stuempno);
    }
    UpdCardVerStatus(cardno,CARDVERTYPE_CARDLOSS);
	if('1'==tCard.lockflag[0])
	{
		//不下发名单
		strcpy(trans.summary,"000101010101");
		return 0;
	}
	//更新系统黑名单最大版本号
	ret=SetSysParaVal(SYSPARA_MAXBLACKCARDVERNO,tCard.cardverno);
	if(ret)
	{
		return ret;
	}
    T_t_cardver cardver;
    memset(&cardver,0,sizeof(cardver));
    cardver.cardno=tCard.cardno;
    des2src(cardver.accdate,pAccTrans->trans.accdate);
    cardver.termid=trans.termid;
    cardver.termseqno=trans.termseqno;
    cardver.cardno=tCard.cardno;
    des2src(cardver.cardphyid,tCard.cardphyid);
	des2src(cardver.stuempno,customer.stuempno);	
    cardver.cardvertype=CARDVERTYPE_CARDUNLOSS;
    cardver.adddelflag[0]=ADDDELFLAG_DEL;
    cardver.status[0]=STATUS_NORMAL;
    des2src(cardver.cardverno,tCard.cardverno);
    ret=DB_t_cardver_add(&cardver);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_CARDVER_E;
        else
            return E_DB_CARDVER_I;
    }
    des2src(trans.summary,cardver.cardverno);
	char broadcastblkflag[20]={0};
	ret=GetSysParaVal(SYSPARA_BROADCASTBLKLIST,broadcastblkflag);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_SYSKEY_R;
	}
	if(broadcastblkflag[0]!='1')
		return 0;
	T_t_msglist tMsgList;
	memset(&tMsgList,0,sizeof(tMsgList));
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_CARDID,tCard.cardno);
	AddXmlItemStr(tMsgList.reqdata, XML_KEY_VERNUM,tCard.cardverno);
	AddXmlItemInt(tMsgList.reqdata, XML_KEY_ADDDELSIGN,1);	//增删标志

	tMsgList.funcno = 930005;
	tMsgList.pfuncno = 846307;
	tMsgList.msglevel = MESLIST_PRIORITY_REALTIME;
	tMsgList.msgtype = MESLIST_TYPE_ORDER;
	ret=AddMsgLst(&tMsgList);
	if(ret)
	{
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}
    return 0;
}
int F846307(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
//    ret=pAccTrans->checkCfgUpdate();
//    if (ret)
//        return ret;
    des2src(pAccTrans->trans.opercode,rPack->semp);
    TRANS& trans=pAccTrans->trans;
    char lossflag=rPack->sstatus1[0];
    if ('1'==lossflag)
        trans.transcode=TC_CARDLOSS;
    else
        trans.transcode=TC_CARDUNLOSS;
    trans.termid=rPack->lwithdraw_flag;

    ret=pAccTrans->InitTrans();
    if (ret)
        return ret;
    trans.cardno = rPack->lvol0;
    if ('1'==lossflag)
        ret=DoLossCard(trans.cardno);
    else
        ret=DoUnlossCard(trans.cardno);
    if (ret)
        return ret;
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    transdtl.cardno=trans.cardno;
    transdtl.custid=trans.custid;
    des2src(transdtl.custname,trans.custname);
    des2src(transdtl.stuempno,trans.stuempno);
    strcpy(transdtl.transdate,trans.transdate);
    strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    des2src(transdtl.opercode,trans.opercode);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.errcode=0;
	transdtl.showcardno=atol(trans.showcardno);
    ret=DB_t_transdtl_add(&transdtl);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));

    ResetNormalCPack(&aPack,0,1);


    SetCol(handle,0);
    SetCol(handle,F_LWITHDRAW_FLAG,F_LVOL0,F_SSERIAL0,F_VSMESS,0);
	outPack->lvol0=trans.cardno;
	outPack->lwithdraw_flag=trans.termid;
    strncpy(outPack->sserial0,trans.summary,12);
	sprintf(outPack->vsmess,pAccTrans->GetTip().c_str());
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}
