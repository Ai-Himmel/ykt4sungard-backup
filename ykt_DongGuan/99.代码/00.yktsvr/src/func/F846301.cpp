/* --------------------------------------------
 * ��������: 2008-06-04
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: һ��ͨ����
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
    //���ÿͻ��Ƿ����״̬�����Ŀ�
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
    des2src(tCustomer.lastsaved,CAccTrans::GetInst().hostdatetime);
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
    //��鿨�Ƿ��Ѿ�ʹ��
    int ret=0;

    CAccTrans& ats=CAccTrans::GetInst();
    TRANS& trans=ats.trans;
    int cardtype=0;
	T_t_card  tCardTest;
	if(ats.sysPara.bEnableCardMgr)
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
	    strcpy(carddtl.summary,"��Ƭ����");
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
    //�жϵ�������
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
                return ERRINFO(E_CARD_EXPIREDATE,tCustomer.outdate,ats.trans.accdate);
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
    ret = getNewUniqNo(KEYTYPE_CARDNO,&tCard.cardno);	//��ȡ��󿨺�
    if (ret)
    {
        return ret;
    }
    ret = GetNewCardAccno(tCard.accno);  	    			//�������ʺ�
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
    	//��ӿ�Ƭʹ����ϸ��¼
    	T_t_carddtl tCarddtl;

    	memset(&tCarddtl,0,sizeof(tCarddtl));
    	des2src(tCarddtl.accdate,ats.sysPara.sSettleDate);
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
    des2src(cardver.accdate,ats.trans.accdate);
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
    //���뿨λͼ��
    T_t_cardbitmap tCardBitmap;

	memset(&tCardBitmap,0,sizeof(tCardBitmap));
    tCardBitmap.cardno=tCard.cardno;
    
	int num=(trans.paycnt-1)/1000;	
	if(num<1)
	{
		if(trans.paycnt>500)
			tCardBitmap.baseno=500;
		else
			tCardBitmap.baseno=0;
	}
	else
	{
		int offsetcnt= trans.paycnt - num*1000;
		if(offsetcnt<100)
			tCardBitmap.baseno = num*1000-500;
		else if(offsetcnt>500)
			tCardBitmap.baseno = num*1000+500;
		else
			tCardBitmap.baseno = num*1000;
	}
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
    CAccTrans& ats=CAccTrans::GetInst();
    des2src(ats.trans.opercode,rPack->semp);
    ats.trans.transcode=TC_CARDOPEN;
    ret=ats.InitTrans();
    if (ret)
        return ret;
    TRANS& trans=ats.trans;

    int i=0;
    char anonymflag[2]={0};
	trans.custid=rPack->lvol1;
    trans.cardtype=rPack->lsafe_level;
    trans.cardflag=1;
    trans.usecardflag=1;
	trans.calccardbalflag=1;   
    ats.SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,0);
	ats.SetInputAmt(rPack->damt0);

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

    //���ͻ�
    T_t_customer tCustomer;
    memset(&tCustomer,0,sizeof(tCustomer));
    tCustomer.custid=trans.custid;
	//�����ѷ������Ŀͻ�
    T_t_cardtype tCardtype;
    memset(&tCardtype,0,sizeof(tCardtype));
    ret=DB_t_cardtype_read_by_cardtype(trans.cardtype,&tCardtype);
    if (ret)
    {
        writelog(LOG_ERR,"cardtype[%d]",trans.cardtype);
        if (DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDTYPE,trans.cardtype);
        else
            return E_DB_CARDTYPE_R;
    }
    T_t_cardphytype tCardphytype;
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
		ERRTIP("[�������]��[������]��һ��");
		return E_COMMON_ERR;	
	}
	if(rPack->lvol3 !=0)
	{
		if(tCardphytype.cardphytypecode != rPack->lvol3)
		{
			ERRTIP("���������ʹ���%d��ϵͳ����%d����",rPack->lvol3,tCardphytype.cardphytypecode);
			return E_COMMON_ERR;
		}
	}
    if (tCustomer.custid)
    {
        tCardtype.cardtype=trans.cardtype;
        ret=doCustomer(tCustomer.custid,tCardtype,tCustomer);
        if (ret)
            return ret;
        // �ж�ͬһ���ͻ����ܷ���ͬһ�����͵Ŀ�
       	ret = CheckExistsMoreCard(tCustomer.custid,tCardphytype.cardphytype);
       	if(ret)
       	{
       		ERRTIP("ͬһ���ͻ�����������ͬһ���͵Ŀ�");
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
//���ݴ�ѧ�ǿͻ��ż�Ϊ��ʾ����
//	if(strlen(tCard.showcardno)<1)
//	{
//		sprintf(tCard.showcardno,"%10d",trans.custid);
//	}

    des2src(tCard.expiredate,rPack->sdate0);
    tCard.cardtype=trans.cardtype;
    tCard.feetype=trans.feetype;

    char cardpwd[33]={0};
    char key[17]={0};

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
    tCardaccount.status[0]=STATUS_NORMAL;
    strcpy(tCardaccount.transtime,trans.sysdatetime);
    strcpy(tCardaccount.opendate,trans.accdate);
	//��ȡ���������޶�
	char sysparaval[21]={0};
	ret=GetSysParaVal(SYSPARA_SINGLEMAXAMT,sysparaval);
	if(ret)
	{
		ERRTIP("��ѯϵͳ�������������޶��������");
		return E_COMMON_ERR;
	}
	tCardaccount.singlemaxamt=atof(sysparaval);
	//��ȡ�������޶�
	ret=GetSysParaVal(SYSPARA_DAYMAXAMT,sysparaval);
	if(ret)
	{
		ERRTIP("��ѯϵͳ�������������޶��������");
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
    trans.termseqno=trans.termseqno;
    des2src(trans.cardaccno,tCardaccount.accno);
	ret=ats.doTrans();
	if(ret)
	{
		writelog(LOG_ERR," doMainTrans ret[%d]",ret);		
		return ret;
	}
	ret=ats.doTransEnd();
	if(ret)
	{
		writelog(LOG_ERR," doTransEnd ret[%d]",ret);		
		return ret;
	}
	if(amtcmp(trans.cardaftbal,CardMaxBal)>0)
	{
		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
	}
	//���㿨���
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));
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
	if(amtcmp(transdtl.cardaftbal,0)>0)
		trans.aftdpscnt=trans.dpscnt+1;
	transdtl.cardcnt =trans.aftdpscnt;
    ret=DB_t_transdtl_add(&transdtl);
    if (ret)
    {
        if (DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    ret=SaveCardTransInfo();
    if(ret)
    {
		writelog(LOG_ERR,"SaveCardTransInfo ret=%d",ret);
    }
    SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL5,
           F_SNAME,F_SALL_NAME,F_SPAGER,F_SCERT_NO,F_SHOLDER_AC_NO,
           F_SEMAIL2,F_SMARKET_CODE,F_SMARKET_CODE2,F_SDATE0,F_SNOTE,
           F_SSTAT_TYPE,F_SSTAT_TYPE2,F_SNATION_CODE,F_SBRANCH_CODE0,
           F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL11,F_LVOL12,
           F_SORDER0,F_SDATE3,F_SEMP,
		   F_SORDER1,F_SORDER2,F_STIME3,F_LSAFE_LEVEL,
           F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,F_SNAME2,0);
//��ѧ��
//	sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);	//�ͻ���
//	sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);	//�ͻ���
	sprintf(outPack->sholder_ac_no,"%d",17);				//���з���ʶ
	des2src(outPack->sstat_type,tCustomer.idtype);			//֤������
	des2src(outPack->snation_code,tCustomer.country);		//����
	des2src(outPack->sstat_type2,tCustomer.nation);			//����
	des2src(outPack->sbranch_code0,tCustomer.areacode);		//ԺУ����	
	strcpy(outPack->snote,CARD_STRUCT_VERSION);				//�ƿ��汾��
	strcpy(outPack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//����ע���ʶ��
	strcpy(outPack->sorder2,CARD_REGISTER_SERVICE_CODE);	//����ע���ʶ��
//��ѧ��  
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
     outPack->lvol8=D4U5(ats.trans.cardaftbal*100,0);
    outPack->lvol11=D4U5(tCardaccount.singlemaxamt*100,0);
    outPack->lvol12=D4U5(tCardaccount.daycostmaxamt*100,0);
    des2src(outPack->sorder0,tCard.showcardno);	
    des2src(outPack->sdate3,ats.trans.accdate);
    des2src(outPack->stime3,ats.trans.acctime);
    des2src(outPack->semp,trans.opercode);
    des2src(outPack->sname2,tCard.cardverno);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(trans.remark,"%s�����%.2lfԪ",ats.remark.c_str(),ats.trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}

