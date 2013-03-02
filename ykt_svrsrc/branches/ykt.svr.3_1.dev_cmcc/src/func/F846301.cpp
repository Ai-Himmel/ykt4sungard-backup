/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通开户
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
#include "dbfunc_foo.h"
#include "busqc.h"
#include "acctrans.h"
#include "transfunc.h"

static int doCustomer(int custid,T_t_cardtype& tCardtype,T_t_customer& tCustomer)
{
    int ret=0;
    ret=DB_t_customer_read_lock_by_cur_and_custid(custid,&tCustomer);
    if (ret)
    {
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CUSTOMER,custid);
        else
            return E_DB_CUSTOMER_R;
    }
    if (tCustomer.status[0]==STATUS_DELETE)
    {
        DB_t_customer_free_lock_cur();
        return ERRINFO(E_CUSTOMER_LOGOUT,tCustomer.custid);
    }
    if (tCustomer.feetype<1)
    {
        DB_t_customer_free_lock_cur();
        return ERRINFO(E_NOSET_CUSTOMER_FEETYPE,tCustomer.custid);
    }
    //检查该客户是否存在状态正常的卡
    ret=IsExistNormalCardByCustid(tCustomer.custid);
    if (ret)
    {
        DB_t_customer_free_lock_cur();
        if (DB_EXIST==ret)
            return ERRINFO(E_CUSTOMER_HAVE_CARD,tCustomer.custid);
        else
            return E_DB_CARD_R;
    }
    ret=DB_t_cardtype_read_by_cardtype(tCardtype.cardtype,&tCardtype);
    if (ret)
    {
        DB_t_customer_free_lock_cur();
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDTYPE,tCardtype.cardtype);
        else
            return E_DB_CARDTYPE_R;
    }
    tCustomer.useflag[0]='1';
    tCustomer.holdcardcnt++;
    des2src(tCustomer.lastsaved,CAccTrans::getInstance()->trans.sysdatetime);
    ret=DB_t_customer_update_lock_by_cur(&tCustomer);
    if (ret)
    {
        if (DB_NOTFOUND==ret)
            return E_NOTEXIST_CUSTOMER;
        else
            return E_DB_CUSTOMER_U;
    }
    return 0;
}

static int doCard(T_t_customer& tCustomer,T_t_cardtype& tCardtype,T_t_card& tCard)
{
    //检查卡是否已经使用
    int ret=0;

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    int cardtype=0;
	T_t_card  tCardTest;
	if(pAccTrans->sysPara.bEnableCardMgr)
	{
	    if (!strlen(tCard.showcardno))
    	    return E_INPUT_SHOWCARDNO;
		ret=DB_t_card_read_by_showcardno_and_status(tCard.showcardno,"1",&tCardTest);
		if (ret!=DB_NOTFOUND)
		{
			if (DB_SUCCESS==ret)
				return ERRINFO(E_EXIST_SHOWCARDNO,tCard.showcardno);
			else
				return E_DB_CARD_R;
		}
	    ret=UseShowCardNo(trans.opercode,tCard.showcardno,cardtype);
	    if (ret)
	    {
	        return ret;
	    }
	    if (cardtype!=tCard.cardtype)
	    {
	        return ERRINFO(E_DIFF_CARDTYPE,cardtype,tCard.cardtype);
	    }
	    T_t_carddtl carddtl;
	    memset(&carddtl,0,sizeof(carddtl));

	    des2src(carddtl.accdate,trans.accdate);
	    des2src(carddtl.acctime,trans.acctime);
	    carddtl.termid=trans.termid;
	    carddtl.termseqno=trans.termseqno;
	    des2src(carddtl.opercode,trans.opercode);
	    carddtl.cardtype=tCard.cardtype;
	    carddtl.usetype=CARDUSETYPE_USE;
	    carddtl.inoutflag=INOUTFLAG_OUT;
	    carddtl.transcnt=1;
	    strcpy(carddtl.summary,"卡片发行");
	    des2src(carddtl.cardphyid,tCard.cardphyid);
	    des2src(carddtl.showcardno,tCard.showcardno);

	    ret=DB_t_carddtl_add(&carddtl);
	    if (ret)
	    {
	        if (DB_REPEAT==ret)
	            return E_DB_CARDDTL_E;
	        else
	            return E_DB_CARDDTL_I;
	    }
	}
    tCard.status[0]=STATUS_NORMAL;
    ret=DB_t_card_read_by_cardphyid_and_status(tCard.cardphyid,"1",&tCardTest);
    if (ret!=DB_NOTFOUND)
    {
        if (DB_SUCCESS==ret)
            return ERRINFO(E_EXIST_CARDPHYID,tCard.cardphyid);
        else
            return E_DB_CARD_R;
    }
    //判断到期日期
    if (strlen(tCard.expiredate)<1)
    {
        ret=IsInvalidDateTime(tCustomer.outdate,"YYYYMMDD");
        if (ret==0)
        {
            if (strncmp(tCustomer.outdate,trans.transdate,8)>0)
            {

                des2src(tCard.expiredate,tCustomer.outdate);
            }
            else
                return ERRINFO(E_CARD_EXPIREDATE,tCustomer.outdate,pAccTrans->trans.accdate);
        }
        else
        {
            if (tCardtype.fixdaycnt<1)
                return ERRINFO(E_NOSET_CARDTYPE_VALIDDAYS,tCardtype.cardtype);
            ret=calcEndDate(trans.transdate,tCardtype.fixdaycnt,tCard.expiredate);
            if (ret)
                return ret;
        }
    }
    else
    {
        ret=IsInvalidDateTime(tCard.expiredate,"YYYYMMDD");
        if (ret)
            return ERRINFO(E_INPUT_EXPIREDATE,tCard.expiredate);
        if (strncmp(tCard.expiredate,trans.transdate,8)<0)
            return ERRINFO(E_INPUT_EXPIREDATE,tCard.expiredate);
    }
    char cardpwd[33]="";
    char key[17]="";
    get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
    strcpy(key,STATIC_SEED_KEY);
    EncodePwd(key,cardpwd,tCard.cardpwd, 0);
    tCard.custid=tCustomer.custid;

	//if(strlen(tCard.showcardno)<1||atof(tCard.showcardno)<1)
	//sprintf(tCard.showcardno,"%010d",tCard.custid);
	tCard.lossflag[0]='0';
	tCard.frozeflag[0]='0';
	tCard.badflag[0]='0';
	tCard.lockflag[0]='0';
    ret=getCardVerNo(tCard.cardverno);
    if (ret)
        return ret;
    des2src(tCard.opendate,trans.accdate);
    des2src(tCard.lastsaved,trans.sysdatetime);
    ret = getNewUniqNo(KEYTYPE_CARDNO,&tCard.cardno);	//获取最大卡号
    if (ret)
    {
        return ret;
    }
    ret = GetNewCardAccno(tCard.accno);  	    			//获得最大帐号
    if (ret)
    {
        return ret;
    }
    ret=DB_t_card_add(&tCard);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_CARD_E;
        else
            return E_DB_CARD_I;
    }
    /*
    	//添加卡片使用明细记录
    	T_t_carddtl tCarddtl;

    	memset(&tCarddtl,0,sizeof(tCarddtl));
    	des2src(tCarddtl.accdate,pAccTrans->sysPara.sSettleDate);
    	tCarddtl.termid=trans.termid;
    	tCarddtl.termseqno=trans.termseqno;
    	tCarddtl.cardtype=tCard.cardtype;
    	des2src(tCarddtl.showcardno,tCard.showcardno);
    	des2src(tCarddtl.cardphyid,tCard.cardphyid);
    	tCarddtl.cardusetype=CARDUSETYPE_OPENCARD;
    	des2src(tCarddtl.opercode,trans.opercode);
    	ret=DB_t_carddtl_add(&tCarddtl);
    	if(ret)
    	{
    		if(DB_REPEAT==ret)
    			return E_DB_CARDDTL_E;
    		else
    			return E_DB_CARDDTL_I;
    	}
    	*/
    T_t_cardver cardver;

    memset(&cardver,0,sizeof(cardver));
    cardver.cardno=tCard.cardno;
    des2src(cardver.accdate,pAccTrans->trans.accdate);
    cardver.termid=trans.termid;
    cardver.termseqno=trans.termseqno;
    cardver.cardno=tCard.cardno;
    cardver.status[0]=STATUS_NORMAL;
    des2src(cardver.cardphyid,tCard.cardphyid);
    des2src(cardver.stuempno,tCustomer.stuempno);
    cardver.cardvertype=CARDVERTYPE_CARDOPEN;
    des2src(cardver.cardverno,tCard.cardverno);
    ret=DB_t_cardver_add(&cardver);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_CARDVER_E;
        else
            return E_DB_CARDVER_I;
    }
    //插入卡位图表
    T_t_cardbitmap tCardBitmap;

	memset(&tCardBitmap,0,sizeof(tCardBitmap));
    tCardBitmap.cardno=tCard.cardno;
    tCardBitmap.baseno=0;
    memset(tCardBitmap.bitmap0,'0',sizeof(tCardBitmap.bitmap0)-1);
    memset(tCardBitmap.bitmap1,'0',sizeof(tCardBitmap.bitmap1)-1);
    memset(tCardBitmap.bitmap2,'0',sizeof(tCardBitmap.bitmap2)-1);
    memset(tCardBitmap.bitmap3,'0',sizeof(tCardBitmap.bitmap3)-1);
    memset(tCardBitmap.bitmap4,'0',sizeof(tCardBitmap.bitmap4)-1);
    memset(tCardBitmap.bitmap5,'0',sizeof(tCardBitmap.bitmap5)-1);
    memset(tCardBitmap.bitmap6,'0',sizeof(tCardBitmap.bitmap6)-1);
    memset(tCardBitmap.bitmap7,'0',sizeof(tCardBitmap.bitmap7)-1);
    memset(tCardBitmap.bitmap8,'0',sizeof(tCardBitmap.bitmap8)-1);
    memset(tCardBitmap.bitmap9,'0',sizeof(tCardBitmap.bitmap9)-1);
    ret=DB_t_cardbitmap_add(&tCardBitmap);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_CARDBITMAP_E;
        else
            return E_DB_CARDBITMAP_I;
    }
    return 0;
}
int F846301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_CARDOPEN;
    ret=pAccTrans->InitTrans();
    if (ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    int i=0;
    char anonymflag[2]="";
	trans.custid=rPack->lvol1;
    trans.cardtype=rPack->lsafe_level;
    trans.cardflag=1;
    trans.usecardflag=1;
    trans.purseno=PURSE_NO_ONE;
	trans.dpscnt=rPack->lvol5;
	trans.paycnt=rPack->lvol6;
    trans.cardbefbal=0;
    trans.inputamt=rPack->damt0;
	trans.unusedamt = trans.inputamt;
    if (amtcmp(trans.inputamt,0)>0)
    {
        trans.fundtype=rPack->lvol9;
        des2src(trans.voucherno,rPack->scust_auth2);
    }

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    memset(&aPack,0,sizeof(aPack));

    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);

    des2src(anonymflag,rPack->sstatus1);

    //检查客户
    T_t_customer tCustomer;
    T_t_cardphytype tCardphytype;
    T_t_cardtype tCardtype;

    memset(&tCustomer,0,sizeof(tCustomer));
    memset(&tCardphytype,0,sizeof(tCardphytype));
    memset(&tCardtype,0,sizeof(tCardtype));
    tCustomer.custid=trans.custid;


	// 必须上传卡类型

	//对于已发过卡的客户
    ret=DB_t_cardtype_read_by_cardtype(trans.cardtype,&tCardtype);
    if (ret)
    {
        writelog(LOG_ERR,"cardtype[%d]",trans.cardtype);
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDTYPE,trans.cardtype);
        else
            return E_DB_CARDTYPE_R;
    }

    memset(&tCardphytype,0,sizeof tCardphytype);
    ret=DB_t_cardphytype_read_by_cardphytype(tCardtype.cardphytype,&tCardphytype);
    if(ret)
    {
    	writelog(LOG_ERR,"cardphytype[%d]",tCardphytype.cardphytype);
    	if(DB_NOTFOUND==ret)
    		return ERRINFO(E_NOTEXIST_CARDTYPE,tCardphytype.cardphytype);
    	else
    		return E_DB_CARDPHYTYPE_R;
    }
    
    if(tCardtype.cardphytype != tCardphytype.cardphytype)
	{
		ERRTIP("【发卡类别】与【卡类型】不一致");
		return E_COMMON_ERR;
		
	}
	if(rPack->lvol3 !=0)
	{
		if(tCardphytype.cardphytypecode != rPack->lvol3)
		{
			ERRTIP("卡物理类型代码%X与系统代码%X不符",rPack->lvol3,tCardphytype.cardphytypecode);
			return E_COMMON_ERR;
		}
	}
	
    if (tCustomer.custid)
    {
        tCardtype.cardtype=trans.cardtype;
        ret=doCustomer(tCustomer.custid,tCardtype,tCustomer);
        if (ret)
            return ret;
        // 判断同一个客户不能发行同一种类型的卡
       	ret = CheckExistsMoreCard(tCustomer.custid,tCardphytype.cardphytype);
       	if(ret)
       	{
       		ERRTIP("同一个客户不能有两张同一类型的卡");
       		return ret;
       	}
       		
        trans.feetype=tCustomer.feetype;
        des2src(trans.custname,tCustomer.custname);
        
		T_t_cardtyperight cardtyperight;
		
		memset(&cardtyperight,0,sizeof(cardtyperight));
		ret=DB_t_cardtyperight_read_by_cardtype_and_feetype(trans.cardtype,trans.feetype,&cardtyperight);
		if (ret)
		{
			writelog(LOG_ERR,"cardtype[%d]feetype[%d]",trans.cardtype,trans.feetype);
			if (DB_NOTFOUND==ret)
				return ERRINFO(E_NOCARDTYPERIGHT,trans.feetype);
			else
				return E_DB_CARDTYPERIGHT_R;
		}
    }
    else
    {
        if (anonymflag[0]!='1')
            return E_NOTEXIST_CUSTOMER;

        ret=DB_t_cardtype_read_by_anonymflag(anonymflag,&tCardtype);
        if (ret)
        {
            if (DB_NOTFOUND==ret)
                return E_NOCFG_ANONYMCARDTYPE;
            else
                return E_DB_CARDTYPE_R;
        }
        trans.feetype=tCardtype.feetype;
        trans.cardtype=tCardtype.cardtype;
        if (!trans.feetype)
            return ERRINFO(E_NOCFG_ANONYMCARD_FEETYPE,trans.cardtype);
    }
    T_t_card tCard;
    memset(&tCard,0,sizeof(tCard));

	tCard.cardphytype = tCardphytype.cardphytype;
    des2src(tCard.cardphyid,rPack->sstation0);
    des2src(tCard.showcardno,rPack->sorder0);
    if (!strlen(tCard.cardphyid))
        return E_INPUT_CARDPHYID;
//广州大学城客户号即为显示卡号
//	if(strlen(tCard.showcardno)<1)
//	{
//		sprintf(tCard.showcardno,"%10d",trans.custid);
//	}

    des2src(tCard.expiredate,rPack->sdate0);
    tCard.cardtype=trans.cardtype;
    tCard.feetype=trans.feetype;

    char cardpwd[33]="";
    char key[17]="";

    get_init_passwd_by_man_id(tCustomer.idno,cardpwd);
    strcpy(key,STATIC_SEED_KEY);
    EncodePwd(key,cardpwd,tCard.cardpwd, 0);

    ret=doCard(tCustomer,tCardtype,tCard);
    if (ret)
        return ret;
	double CardMaxBal=0;
	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
	if(ret)
		return ret;
    T_t_account tCardaccount;
    memset(&tCardaccount,0,sizeof(tCardaccount));
    des2src(tCardaccount.accno,tCard.accno);
    des2src(tCardaccount.accname,tCustomer.custname);
    des2src(tCardaccount.subjno,SUBJECT_CARDSAVING);
    des2src(tCardaccount.accpwd,tCard.cardpwd);
    tCardaccount.custid=tCustomer.custid;
    tCardaccount.cardno=tCard.cardno;
    tCardaccount.purseno=PURSE_NO_ONE;
//    tCardaccount.cardmaxbal=CardMaxBal;
    tCardaccount.lastcardbal=0;
    tCardaccount.status[0]=STATUS_NORMAL;
    strcpy(tCardaccount.lasttransdate,trans.accdate);
    strcpy(tCardaccount.opendate,trans.accdate);
//    tCardaccount.acctype=ACCTYPE_CARD;
	//读取单次消费限额
	char sysparaval[21]="";
	ret=GetSysParaVal(SYSPARA_SINGLEMAXAMT,sysparaval);
	if(ret)
	{
		ERRTIP("查询系统参数表单次消费限额参数错误");
		return E_COMMON_ERR;
	}
	tCardaccount.singlemaxamt=atof(sysparaval);
	//读取日消费限额
	ret=GetSysParaVal(SYSPARA_DAYMAXAMT,sysparaval);
	if(ret)
	{
		ERRTIP("查询系统参数表日消费限额参数错误");
		return E_COMMON_ERR;
	}
	tCardaccount.daycostmaxamt=atof(sysparaval);
    ret=DB_t_account_add(&tCardaccount);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_ACCOUNT_E;
        else
            return E_DB_ACCOUNT_I;
    }
    trans.cardno=tCardaccount.cardno;
    trans.purseno=tCardaccount.purseno;
    trans.termseqno=trans.termseqno;
    des2src(trans.cardaccno,tCardaccount.accno);
	ret=pAccTrans->doTrans();
	if(ret)
	{
		writelog(LOG_ERR," doMainTrans ret[%d]",ret);		
		return ret;
	}
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		writelog(LOG_ERR," doTransEnd ret[%d]",ret);		
		return ret;
	}
	if(amtcmp(trans.cardaftbal,CardMaxBal)>=0)
	{
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
	}
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    transdtl.purseno=trans.purseno;
    transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
    transdtl.paytype=trans.fundtype;
    des2src(transdtl.voucherno,trans.voucherno);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.revflag[0]='0';
    transdtl.errcode=0;
    transdtl.custid=tCard.custid;
    des2src(transdtl.stuempno,tCustomer.stuempno);
    strcpy(transdtl.custname,tCustomer.custname);
    strcpy(transdtl.transdate,trans.transdate);
    strcpy(transdtl.transtime,trans.transtime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    des2src(transdtl.opercode,trans.opercode);
    transdtl.cardno=tCard.cardno;
    transdtl.cardbefbal=trans.cardbefbal;
    transdtl.cardaftbal=trans.cardaftbal;
    des2src(transdtl.showcardno,tCard.showcardno);	
	transdtl.transflag=TF_DPS;
	transdtl.cardcnt =trans.dpscnt;
	if(amtcmp(transdtl.cardaftbal,0)>0)
		++transdtl.cardcnt;
    ret=DB_t_transdtl_add(&transdtl);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL5,
           F_SNAME,F_SALL_NAME,F_SPAGER,F_SCERT_NO,F_SHOLDER_AC_NO,
           F_SEMAIL2,F_SMARKET_CODE,F_SMARKET_CODE2,F_SDATE0,F_SNOTE,
           F_SSTAT_TYPE,F_SSTAT_TYPE2,F_SNATION_CODE,F_SBRANCH_CODE0,
           F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL11,F_LVOL12,
           F_SORDER0,F_SDATE3,F_SEMP,
		   F_SORDER1,F_SORDER2,F_STIME3,F_LSAFE_LEVEL,
           F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,F_SNAME2,0);
//大学城
//	sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);	//客户号
//	sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);	//客户号
	sprintf(outPack->sholder_ac_no,"%d",17);				//发行方标识
	des2src(outPack->sstat_type,tCustomer.idtype);			//证件类型
	des2src(outPack->snation_code,tCustomer.country);		//国籍
	des2src(outPack->sstat_type2,tCustomer.nation);			//民族
	des2src(outPack->sbranch_code0,tCustomer.areacode);		//院校代码	
	strcpy(outPack->snote,CARD_STRUCT_VERSION);				//制卡版本号
	strcpy(outPack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//发卡注册标识号
	strcpy(outPack->sorder2,CARD_REGISTER_SERVICE_CODE);	//服务注册标识号
//大学城  
    outPack->lvol1=tCustomer.custid;
    outPack->lsafe_level2=tCustomer.custtype;
    outPack->lvol5=tCard.feetype;
    des2src(outPack->sall_name,tCustomer.custname);
    des2src(outPack->sname,tCustomer.custname);
    des2src(outPack->spager,tCustomer.stuempno);
    des2src(outPack->scert_no,tCustomer.deptcode);
    des2src(outPack->smarket_code2,tCustomer.idtype);
    des2src(outPack->semail2,tCustomer.idno);
    des2src(outPack->smarket_code,tCustomer.sex);
    des2src(outPack->sdate0,tCard.expiredate);
    outPack->lvol0=tCard.cardno;
    outPack->lsafe_level=tCard.cardtype;
    des2src(outPack->stx_pwd,cardpwd);	
     outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
    outPack->lvol11=D4U5(tCardaccount.singlemaxamt*100,0);
    outPack->lvol12=D4U5(tCardaccount.daycostmaxamt*100,0);
    des2src(outPack->sorder0,tCard.showcardno);	
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->stime3,pAccTrans->trans.acctime);
    des2src(outPack->semp,trans.opercode);
    des2src(outPack->sname2,tCard.cardverno);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

