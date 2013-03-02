/* --------------------------------------------
 * 程序名称: F250003.sqc
 * 创建日期: 2007-09-17
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 移动充值对账
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"


int F250003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	char ftpserver_ip[31]="";		 //移动服务器的ip
	char ftpserver_filepath[256]="";   //移动服务端对账文件路径
	char chkacc_date[11]="";	//对帐日期
	char autoftpcmd[1024]="";
	char localfile[256]="";
	char remotefile[256]="";

	char	sFileName[256], sCommand[256], sBuffer[1024];
	FILE	*fp;
	char tx_date[9]="";
	char phone[31]="";
	char sSerialNo[20]="";
	char sCardId[20]="";
	int serial_no=0;
	int  card_id=0;
	int  amount=0;
	char sAmount[20]="";
	char *phead;
	char *ptail;
	int rows=0;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SDATE0,F_SPHONE,F_LSERIAL0,F_LVOL0,F_LVOL1,0);	
	des2src(ftpserver_ip,rPack->saddr);
	des2src(ftpserver_filepath,rPack->vsvarstr0);
	des2src(chkacc_date,rPack->sorder0);	
	//ftp取对账文件
	sprintf(remotefile,"%s/YKT_GZ.%s" ,ftpserver_filepath,chkacc_date);
	sprintf(localfile,"/tmp/YKT_GZ.%s",chkacc_date);


	/* 得到文件 */
	sprintf(sCommand,"autoftp.sh %s %s %s",ftpserver_ip,remotefile,localfile);

	if(system(sCommand) != 0)
	{
		writelog(LOG_ERR,"ftp error[%s]", sCommand);
		*pRetCode = E_TRANS_UNKNOW_ERROR;
		goto l_ret;
	}

	if((fp = fopen(localfile, "r")) == NULL)
	{
		writelog(LOG_ERR, "open filename[%s] error", localfile);
		*pRetCode = E_TRANS_UNKNOW_ERROR;
		goto l_ret;
	}
	while(1)
	{
		if(fgets(sBuffer, sizeof(sBuffer), fp) == NULL)
			break;
		serial_no=0;		
		card_id=0;
		amount=0;
			
		memset(tx_date,0,sizeof(tx_date));
		memset(phone,0,sizeof(phone));
		memset(sSerialNo,0,sizeof(sSerialNo));
		memset(sAmount,0,sizeof(sAmount));
		memset(sCardId,0,sizeof(sCardId));

		if(strncmp(sBuffer,"TAIL",4)==0)
			break;

		phead=sBuffer;
		memcpy(tx_date,phead,8);

		phead+=8;
		ptail=strchr(phead,'&');
		if(NULL==ptail)
		{
			fclose(fp);
			goto l_ret;
		}
		memcpy(sSerialNo,phead,ptail-phead);
		serial_no=atol(sSerialNo);

		phead=ptail+1;
		ptail=strchr(phead,'&');
		if(NULL==ptail)
		{
			fclose(fp);
			goto l_ret;
		}
		memcpy(phone,phead,ptail-phead);

		phead=ptail+1;
		ptail=strchr(phead,'&');
		if(NULL==ptail)
		{
			fclose(fp);
			goto l_ret;
		}
		memcpy(sAmount,phead,ptail-phead);
		amount=atol(sAmount);
		phead=ptail+1;
		strcpy(sCardId,phead);
		trim(sCardId);
		card_id=atol(sCardId);
		des2src(out_pack->sdate0,tx_date);
		des2src(out_pack->sphone,phone);
		out_pack->lserial0=serial_no;
		out_pack->lvol0=card_id;
		out_pack->lvol1=amount;
		writelog(LOG_DEBUG,"对账日期 [%s][%s]",tx_date,out_pack->sphone);
		PutRow(handle,out_pack,pRetCode,szMsg);	
		rows++;
		if(rows%10==0)
			AnswerDataPart(handle,*pRetCode,szMsg);
	}
	AnswerData(handle,*pRetCode,szMsg);
	fclose(fp);
	return 0;
l_ret:
	return -1;
}

