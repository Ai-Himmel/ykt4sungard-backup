/* --------------------------------------------
 * 程序名称: F930007.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 下传设备主参数
 * --------------------------------------------
 * 修改日期:2004-12-14
 * 修改人员:	闻剑
 * 修改描述: 修改业务逻辑
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_                    
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "fdsqc.h"

int F930007(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
 	int cnt=0;
	int mesid=0;
       T_t_tif_meslist tMesList;
	T_t_pif_device tDevice;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);
	memset(&tMesList,0,sizeof(tMesList));
	memset(&tDevice,0,sizeof(tDevice));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	ret=get_devinfo_by_phyid(tMesList.devphy999_id,&tDevice);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"get_devinfo_by_phyid err[%d]",ret);
		goto L_RETU;
	}
	AddXmlItemInt(tMesList.incontent, XML_KEY_DEV999_NO, tDevice.dev999_no);		//机号
	AddXmlItemStr(tMesList.incontent, XML_KEY_DEV999_ID, tDevice.dev999_id);		//注册号	
	AddXmlItemInt(tMesList.incontent, XML_KEY_BAUDRATE, tDevice.baudrate);		//波特率
	AddXmlItemStr(tMesList.incontent, XML_KEY_SYSPWD, tDevice.syspwd);			//系统员密码	
	AddXmlItemStr(tMesList.incontent, XML_KEY_ADMPWD,tDevice.admpwd);			//管理员密码
	AddXmlItemInt(tMesList.incontent, XML_KEY_PWDONOFF,tDevice.pwdonoff);		//密码开关	
	AddXmlItemStr(tMesList.incontent, XML_KEY_CARDSTR, "100");					//卡片结构	
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDUSENUM,tDevice.cardusenum);	//卡的最大使用次数\允许最大消费次数	
	AddXmlItemInt(tMesList.incontent, XML_KEY_MAXDEPOSIT, tDevice.maxdeposit);	//钱包最高存款限额
	AddXmlItemInt(tMesList.incontent, XML_KEY_MINDEPOSIT, tDevice.mindeposit);		//钱包最低剩余款限额	
	AddXmlItemInt(tMesList.incontent, XML_KEY_RATION, tDevice.ration);				//定值收费方式使用的定值额\定值金额
	AddXmlItemStr(tMesList.incontent, XML_KEY_PUSERNO, tDevice.puserno);			//钱包代码\钱包号	
	AddXmlItemInt(tMesList.incontent, XML_KEY_MAXTRADE, tDevice.maxtrade);		//每次交易最高额\大额消费限额	
	AddXmlItemStr(tMesList.incontent, XML_KEY_VCARDSET, tDevice.cardtype);		//终端机适用用户卡类别	
	AddXmlItemStr(tMesList.incontent, XML_KEY_FUNONOFF, tDevice.funonoff);			//收费机增强功能开关	
	AddXmlItemInt(tMesList.incontent, XML_KEY_FEETYPE, tDevice.feetype);			//收费方式

	tMesList.funid = 930007;
	tMesList.level = 2;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=tMesList.funid)
		return 0;	
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		*pRetCode=E_DB_COMMIT;
		goto  L_RETU;
	}
	mesid=tMesList.mesid;
	des2src(out_pack->sdate0,in_pack->sdate0);
	for(cnt=0;(cnt<10)&&(tMesList.ecode!=0);cnt++)
	{
		sleep(1);
		memset(&tMesList,0,sizeof(tMesList));
		ret=DB_t_tif_meslist_read_by_mesid(mesid, &tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_meslist_read_by_mesid err[%d]",ret);
			*pRetCode=E_DB_MESLIST_R;
			goto L_RETU;
		}
	}
	switch(tMesList.ecode)
	{
		case 0:		//成功
			des2src(out_pack->vsvarstr0,"成功");
			break;
		case 9999:		//交易未处理
			des2src(out_pack->vsvarstr0,"前置机无应答");
			break;
		default:			//交易已经处理,但结果是失败
			des2src(out_pack->vsvarstr0,tMesList.emsg);				
			break;
	}	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return  -1;	
}





