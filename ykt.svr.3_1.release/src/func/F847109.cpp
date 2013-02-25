/* --------------------------------------------
 * 程序名称: F47109.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 商户开户
 * --------------------------------------------
 * 修改日期:2004-10-12
 * 修改人员:	闻剑
 * 修改描述: 增加记账交易处理
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "fdsqc.h"
#include "pubdef.h"
#include "errdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "dictionary.h"

int F847109(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    int ret = 0;
    char seed_key[17] = "";							//种子密钥
    char logicdate[11]="";
    T_t_aif_account  tAccount;
    T_t_customer	tCustomer;

    ST_CPACK aPack;
    ST_PACK *pp = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    memset(&tAccount,0,sizeof(tAccount));
    memset(&tCustomer,0,sizeof(tCustomer));

    memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));			//读种子密钥
    tCustomer.custid = in_pack->lvol1;				        					//客户号

    ret=GetLogicDate(logicdate);							//业务日期
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=DB_t_customer_read_by_custid(tCustomer.custid,&tCustomer);
    if(ret) {
        writelog(LOG_ERR,"custid[%d]",tCustomer.custid);
        if(DB_NOTFOUND==ret)
            *pRetCode=E_CUSTOMER_NOT_EXIST;
        else
            *pRetCode=E_DB_CUSTOMER_R;
        goto L_RETU;
    }
    if(CUSTSTAT_LOGOUT==tCustomer.cut_state) {
        *pRetCode=E_CUSTOMER_LOGOUT;
        goto L_RETU;
    }
    ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCustomer.custid,ACCTYPE_SHOPMAIN, &tAccount);
    if(ret) {
        writelog(LOG_ERR,"custid[%d]",tCustomer.custid);
        if(DB_NOTFOUND!=ret) {
            *pRetCode=E_DB_ACCOUNT_R;
            goto L_RETU;
        }
    } else {
        if(tAccount.current_state!=ACCOUNTSTAT_LOGOUT) {
            *pRetCode=E_ACTNO_EXIST;
            goto L_RETU;
        }
    }
    memset(&tAccount,0,sizeof(tAccount));
    des2src(tAccount.open_date,logicdate);									//开户日期
    des2src(tAccount.custname,in_pack->sname);							//客户名称
    tAccount.custid=tCustomer.custid;									//客户号
    tAccount.custtype = in_pack->lvol2;									//客户类别
    des2src(tAccount.stuempno,in_pack->sname2); 						//客户学号或员工号
    tAccount.current_state = ACCOUNTSTAT_REGIST;							//当前状态

    ret = getNewActno(tAccount.account_id);								//获得新帐号
    if (ret) {
        *pRetCode = ret;
        goto L_RETU;
    }

    tAccount.act_type = ACCTYPE_SHOPMAIN;				        			//帐号类别
    tAccount.cardno = 0; 													//关联卡号
    tAccount.purseno = 0;													//关联卡钱包号
//	tAccount.card_state = 0;												//卡状态
    tAccount.card_type = 0;												//卡类别
    des2src(tAccount.subno,SUBJECT_SHOPSAVING);							//所属科目
    EncodePwd(seed_key,in_pack->sserial0,tAccount.password,0);				//帐户密码
    Strncpy_t(tAccount.isautotra,in_pack->scust_type,sizeof(tAccount.isautotra)); 	//是否自动转帐
    tAccount.last_bala = 0.00;					//前次帐户总余额
    tAccount.last_freebala = 0.00;				//前次帐户可用余额
    tAccount.last_frozebala = 0.00;				//前次帐户冻结余额
    tAccount.cur_bala = 0.00;					//当前帐户总余额
    tAccount.cur_freebala = 0.00;				//当前帐户可用余额
    tAccount.cur_frozebala = 0.00;				//当前帐户冻结余额
    tAccount.out_bala = 0.00;					//借方发生总额
    tAccount.in_bala = 0.00;					//贷方发生总额
    tAccount.out_count = 0;					//借方发生总数
    tAccount.in_count = 0;						//贷方发生总数
    tAccount.card_balance = 0.00;				//当前卡中帐户余额
    tAccount.consume_count = 0;				//当前卡中帐户消费次数

    //	插入帐户信息表
    ret = DB_t_aif_account_add(&tAccount);
    if (ret) {
        if(DB_REPEAT==ret)
            *pRetCode = E_DB_ACCOUNT_E;
        else
            *pRetCode = E_DB_ACCOUNT_I;
        goto L_RETU;
    }
    //	返回帐号到前台
    SetCol(handle,0);
    SetCol(handle,F_SSTATION0,0);
    des2src(pp->sstation0, tAccount.account_id);			//帐号
    PutRow(handle,pp,pRetCode,szMsg);
    return 0;
L_RETU:
    return -1;
}
