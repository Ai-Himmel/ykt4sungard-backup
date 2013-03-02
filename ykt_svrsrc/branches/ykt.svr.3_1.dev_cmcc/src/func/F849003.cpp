/* --------------------------------------------
 * ��������: F49003.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:POS ������ֵ
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
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
static int doCard(TRANS& trans,T_t_card& tCard)
{
	int ret=0;
	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",trans.cardno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_CARDNO;
		else 
			return E_DB_CARD_R;
	}
	trans.cardtype=tCard.cardtype;
	trans.feetype=tCard.feetype;
	if(tCard.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==tCard.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==tCard.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==tCard.badflag[0])
	{
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	//�ȽϿ�����ID�Ƿ���ͬ
//	if(strcmp(tCard.cardphyid,trans.cardphyid)!=0)
//	{
//		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,trans.cardphyid);
//		return E_CARD_PHYNO_DIFFER;
//	}
	//��鿨����Ч��
	if(strcmp(tCard.expiredate,trans.transdate)<=0)
		return E_CARD_EXPIRED;
	return 0;
}
int F849003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret =0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
		return ret;
	T_t_authcard 	tAuthCard;
	T_t_transdtl 	transdtl;
	T_t_dpsoper   	tDepositOper;
	T_t_dpsoperpos 	tDepositOperpos;
	T_t_dpsshoppos 	tDepositShoppos;
	T_t_shop 		tDepositShop;
	T_t_account	tAccount;		//�ʻ���

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tAuthCard,0,sizeof(tAuthCard));
	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tDepositOperpos,0,sizeof(tDepositOperpos));
	memset(&tDepositShoppos,0,sizeof(tDepositShoppos));
	memset(&tDepositShop,0,sizeof(tDepositShop));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&transdtl,0,sizeof(transdtl));
	int opercardno=rPack->lvol3;			//����Ա��
	if(!opercardno)
		return E_INPUTNULL_CARDNO;
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.cardno=rPack->lvol5;
	trans.purseno=PURSE_NO_ONE;
	trans.cardbefbal=rPack->lvol9/100.0;			//�뿨���
	trans.cardaftbal=trans.cardbefbal;				
	trans.dpscnt= rPack->lvol7;					//�뿨���
	trans.inputamt= rPack->lvol8/100.0;			//��ֵ���	
	trans.unusedamt = trans.inputamt;
	trans.fundtype=1;

	T_t_card tCard;
	memset(&tCard,0,sizeof(tCard));
	ret=doCard(trans,tCard);
	if(ret)
	{
		return ret;
	}
	trans.feetype=tCard.feetype;
	trans.cardtype=tCard.cardtype;
//	ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_INC,0);
//	if(ret)
//		return ret;
	transdtl.sysid= rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	des2src(transdtl.devphyid, rPack->sphone3);		//�����豸ID
	transdtl.devseqno=rPack->lvol4;					//�ϴ�����ˮ��
	// ��ȡ����Ա��
	ret = DB_t_authcard_read_by_cardno(opercardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"get operator code from auth card error, auth_card_id[%d]",opercardno);
		if(DB_NOTFOUND == ret)
			 return E_DB_AUTHCARD_N;
		else
			 return  E_DB_OPERATOR_R;
	}
	if(tAuthCard.status[0]!=STATUS_NORMAL)
	{
		return E_OPERLOGON_UNREG;
	}
	des2src(trans.opercode,tAuthCard.opercode);
	ret=GetDevIdByDevPhyId(&(trans.termid),transdtl.devphyid);
	if (ret)
	{
		writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] devphy999_id[%s]",ret,transdtl.devphyid);
		return ret;
	}
	ret=DB_t_dpsoper_read_lock_by_c0_and_opercode(trans.opercode,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_DEPOSITOPER_R;
		else
			return E_DB_DEPOSITOPER_N;
	}
	if(tDepositOper.status[0]!=STATUS_NORMAL)
	{
		DB_t_dpsoper_free_lock_by_c0();
		return E_DEPOSITOPER_STOP;
	}
	//�ж��Ƿ����ظ�����
	if(tDepositOper.lastdevseqno==transdtl.devseqno)
	{
		DB_t_dpsoper_free_lock_by_c0();
		ret=DB_t_transdtl_read_by_accdate_and_termid_and_devseqno(trans.accdate,trans.termid,tDepositOper.lastdevseqno,&transdtl);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_TRANSDTL_N;
			else
				return E_DB_TRANSDTL_R;
		}
		//if(transdtl.revflag[0]=='1')
		//	return E_TRANSDTL_REV;
		ResetNormalCPack(&aPack,0,1);
		SetCol(handle,0);
		SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

		out_pack->lvol5 = transdtl.cardno;
		out_pack->lvol10 = (int)D4U5(transdtl.cardaftbal*100,0);
		out_pack->lcert_code = transdtl.termseqno;
		writelog(LOG_INFO,"�ý����ѳɹ�,����[%d]��ֵ���[%.2lf]�����[%.2lf]",transdtl.cardno,transdtl.amount,transdtl.cardaftbal);
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;		
	}
	if(strncmp(tDepositOper.lasttransdate,trans.transdate,8)!=0)
	{
		des2src(tDepositOper.lasttransdate,trans.transdate);
		tDepositOper.depositcnt=0;
		tDepositOper.depositamt=0;
	}
	tDepositOper.depositcnt++;
	tDepositOper.depositamt+=trans.inputamt;
	tDepositOper.lastdevseqno=transdtl.devseqno;
	des2src(tDepositOper.lastdevphyid,transdtl.devphyid);
	des2src(tDepositOper.lastsaved,trans.sysdatetime);
	if(amtcmp(tDepositOper.maxdepositamt,0)>0)
	{
		DB_t_dpsoper_free_lock_by_c0();
		if(amtcmp(tDepositOper.depositamt,tDepositOper.maxdepositamt)>0)
		{
			return E_OPER_OVER_MAX_DEPOSIT_AMT;
		}
	}
	ret=DB_t_dpsoper_update_lock_by_c0(&tDepositOper);
	if(ret)
	{
			return E_DB_DEPOSITOPER_U;
	}
	if('1'==tDepositOper.shopoperflag[0])
	{
		ret=DB_t_dpsshoppos_read_by_deviceid(trans.termid, &tDepositShoppos);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				writelog(LOG_INFO,"PosDeposit termid[%d] ",trans.termid);
				return E_DB_DEPOSITSHOPPOS_N;
			}
			else
			{
				return E_DB_DEPOSITSHOPPOS_R;
			}
		}
		ret=DB_t_shop_read_by_shopid(tDepositShoppos.shopid, &tDepositShop);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return ERRINFO(E_NOTEXIST_SHOPID,tDepositShoppos.shopid);
			else
				return E_DB_SHOP_R;
		}
		if(tDepositShop.status[0]!=STATUS_NORMAL)
		{
			return ERRINFO(E_SHOP_LOGOUT,tDepositShop.shopid);
		}
		trans.transcode = TC_SHOPPOSDEPOSIT;
		des2src(trans.shopaccno,tDepositShop.accno);		
		writelog(LOG_INFO,"��ֵ�̻���ֵ");
	}
	else
	{
		ret=DB_t_dpsshoppos_read_by_deviceid(trans.termid, &tDepositShoppos);
		if(ret)
		{
			if(DB_NOTFOUND!=ret)
			{
				writelog(LOG_INFO,"PosDeposit termid[%d] ",trans.termid);
				return E_DB_DEPOSITSHOPPOS_R;
			}
		}
		else
		{
			ERRTIP("�豸��[%d]�������ڳ�ֵ�̻�,�ǳ�ֵ�̻�����Ա����ʹ�ø��豸",trans.termid);
			return E_COMMON_ERR;

		}
		trans.transcode = TC_POSDEPOSIT;
	}
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_account_read_by_accno(tCard.accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_account_read_by_accno ret[%d]cardno[%d]accno[%s]",ret,trans.cardno,tCard.accno);
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_ACCNO,tCard.accno);
		else
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.lastdpscnt>trans.dpscnt)
	{
		return ERRINFO(E_CARDCNT_LT_LASTCARDCNT,trans.dpscnt,tAccount.lastdpscnt);
	}
//	double CardMaxBal=0;
//	ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
//	if(ret)
//		return ret;
//	if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
//		return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
	trans.custid=tCard.custid;
	des2src(trans.cardaccno,tAccount.accno);
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	des2src(transdtl.transdate,trans.transdate);
	des2src(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,trans.accdate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	transdtl.paytype=trans.fundtype;
	des2src(transdtl.voucherno,trans.voucherno);
	transdtl.cardno=trans.cardno;
	transdtl.purseno=trans.purseno;
	transdtl.transflag=TF_DPS;
	transdtl.cardcnt=trans.dpscnt;
	transdtl.cardbefbal=trans.cardbefbal;
	transdtl.amount=trans.totaltransamt;
	transdtl.managefee=trans.totalfeeamt;
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.custid=trans.custid;
    des2src(transdtl.showcardno,tCard.showcardno);
	des2src(transdtl.custname,tAccount.accname);
	des2src(transdtl.opercode,trans.opercode);
	GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);	
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_TRANSDTL_E;
		else
			return E_DB_TRANSDTL_I;
	} 	
	sprintf(trans.remark,"����%d ��ֵǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",trans.cardno,trans.cardbefbal,trans.cardaftbal);
	writelog(LOG_INFO,trans.remark);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

	out_pack->lvol5 = trans.cardno;
	out_pack->lvol10 = (int)D4U5(trans.cardaftbal*100,0);
	out_pack->lcert_code = trans.termseqno;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
