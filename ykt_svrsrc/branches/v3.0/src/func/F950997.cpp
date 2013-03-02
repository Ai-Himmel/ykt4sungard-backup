/* --------------------------------------------
 * 程序名称: F950997.cpp
 * 创建日期: 2009-7-24
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 获取对账文件到后台，实施对账
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "svrlink.h"
#include "bupub.h"

char full_path[512] = "";
char temp_path[512] = "";

static int Endfile(int file_len)
{
	struct stat fst;
	memset(&fst,0,sizeof fst);
	stat(temp_path, &fst);
	if(fst.st_size != file_len)
	{
		writelog(LOG_DEBUG,"upload file[%s] length error,orign[%d],[%d]!"
			,full_path,file_len,fst.st_size);
		return E_UPLOAD_FILE_CRC;		
	}
	// 重命名文件	
	if(rename(temp_path,full_path))
	{
		return E_UPLOAD_CONFLICT;
	}
	
	return 0;
}

static int WriteFile(char *pBuf)
{	
	FILE *fp =NULL;
	char end_flag;
	char tmp[11] = "";
	int pack_len = 0;
	
	end_flag = pBuf[0];				//结束标志
	if(end_flag == '1')
	{
		strncpy(tmp,pBuf+1,10);
		tmp[10] = '\0';
		pack_len= strtoul(tmp,NULL,16);
		return Endfile(pack_len);
	}	
	fp = fopen(temp_path, "a+b");
	if (fp == NULL)
	{
		writelog(LOG_DEBUG,"Cannot open the file:<%s>!", temp_path);
		return 9980;
	}
	else
	{
		strncpy(tmp,pBuf+1,4);
		tmp[4] = '\0';
		pack_len= strtoul(tmp,NULL,16);
		fwrite(pBuf+5,pack_len,1,fp);	
		fclose(fp);
	}
	return 0;
}


int F950997(TRUSERID *handle, int iRequest, ST_PACK *rpack, int *pRetCode, char *szMsg)
{
	char szfile[256]="";
	char chkacc_date[9] = "";
	int row = 0;
	int ret = 0;
	int chkfilepath_paraid = 0;
	int drtbranch_paraid = 0;
	int bccbasefuncno_paraid = 0;
	int requestType = 0;	
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	char drtbranch[10]="";
	char bccbasefuncno[10]="";
	char sysdate[11]="";
	char remotefilepath[256]="";
	char temp_name[11] = "";
	char *pBuf = NULL;

	char exc_path[256]="";						//对账程序路径
	char exc_name[64]="";						// 对账程序名称

	ST_PACK ArrayPack[5];		// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包
	
	des2src(chkacc_date,rpack->sdate0);
	chkfilepath_paraid = rpack->lsafe_level;				//对账文件在前置服务器上的路径对应的全局参数号
	GetFileName(rpack->lsafe_level2,chkacc_date,szfile,exc_name);	//获取对账文件名，后台对账程序名称		
	if(strlen(szfile)==0 || strlen(exc_name)==0)
	{
		writelog("获取文件名失败");
		goto L_RETU;
	}

	drtbranch_paraid = rpack->lvol3;
	bccbasefuncno_paraid = rpack->lvol4;
	requestType = 950996;									// 前置上读文件，传输文件的功能号

	ret=GetSysParaVal(drtbranch_paraid,drtbranch);			// drtbranch
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], drtbranch[%s]",drtbranch_paraid,drtbranch);
	ret=GetSysParaVal(bccbasefuncno_paraid,bccbasefuncno);  //主功能号
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], bccbasefuncno[%s]",bccbasefuncno_paraid,bccbasefuncno);
	ret=GetSysParaVal(chkfilepath_paraid,remotefilepath);		//前置存放文件路径
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], remotefilepath[%s]",chkfilepath_paraid,remotefilepath);
	DRTP_BRANCH = atoi(drtbranch);
	BCC_BASEFUNCNO = atoi(bccbasefuncno);
	
	// 获取文件存放路径
	ret = GetSysParaVal(GLOBAL_UPLOAD_PATH,full_path);		//后台存放获取的对账文件路径
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}	
	writelog(LOG_INFO,"get_parameter[%d], full_path[%s]",GLOBAL_UPLOAD_PATH,full_path);
	ret = GetSysParaVal(GOLBAL_EXC_ACC_CHK_PATH, exc_path);	//对账可执行程序存放路径
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(exc_path,"%s/%s",exc_path,exc_name);

	strcat(full_path,"/");
	strcpy(temp_path,full_path);
	strcat(full_path,szfile);

	// 先删除原始文件
	unlink(full_path);
	writelog(LOG_DEBUG,"begin upload file[%s]!",full_path);
	// 生成session id
	gen_session_id(temp_name,10);		
	strcat(temp_path,temp_name);

	ResetNormalCPack(&sPack, 0, 1);
	SetPackHeadCol(&sPack.head,F_LVOL5,F_VSVARSTR0, F_VSMESS,0);
	sPack.head.RequestType = requestType;
	des2src(sPack.pack.vsvarstr0,remotefilepath);						// 路径
	des2src(sPack.pack.vsmess,szfile);								    // 文件名
	sPack.pack.lvol5 = rpack->lvol5;									// 删除对账文件
	
	writelog(LOG_INFO,"get remote check file [%s]/[%s]",remotefilepath,szfile);
	memset(&ArrayPack,0,sizeof(ArrayPack));
	row = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, 30, &sPack, &aPack, ArrayPack);
	if (row < 0||aPack.head.retCode!=0)
	{
		if(row<0)
		{
			writelog(LOG_ERR,"Call 950996 error,errcode=[%d],retCode=[%d]Msg[%s]",ret,aPack.head.retCode,aPack.pack.vsmess);
			*pRetCode=ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 950996 error,errcode=[%d],retCode=[%d]Msg[%s]",ret,aPack.head.retCode,aPack.pack.vsmess);
			*pRetCode= aPack.head.retCode;
		}
		goto L_RETU;	
	}
	while(row >0)
	{		
		pBuf = (char *)&aPack.pack;
		ret = WriteFile(pBuf);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		for(int i=0;i<aPack.head.recCount-1;i++)
		{
			pBuf = (char *)&ArrayPack[i];
			ret = WriteFile(pBuf);
			if(ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
		}
		memset(&ArrayPack,0,sizeof(ArrayPack));
		row=ExtCallNext(30,&aPack,ArrayPack);		
		writelog(LOG_INFO,"ExtCallNext row [%d]",row);
		if(-3==row||0==row)
		{
			break;
		}	
		if(ret<0)
			goto L_RETU;
	}

	signal(SIGCHLD,SIG_IGN);
	pid_t pid = fork();
	if(pid<0)
	{
		writelog(LOG_ERR,"创建进程失败");
		return -1;
	}
	else if(pid)			// 父进程应答前台
	{
		ST_PACK* out_pack = &(sPack.pack);

		ResetNormalCPack(&sPack,0,1);
		SetCol(handle,0);	
		SetCol(handle,F_SDATE0,F_VSVARSTR0,F_VSMESS,0);
		des2src(out_pack->vsvarstr0, exc_path);
		des2src(out_pack->vsmess, full_path);
		des2src(out_pack->sdate0, chkacc_date);		

		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}
	else				// 子进程进行对账
	{
		writelog(LOG_INFO,"exc_path[%s],exc_name[%s],chkdate[%s],full_path[%s]",exc_path,exc_name,chkacc_date,full_path);
		execl(exc_path,exc_name,chkacc_date,full_path,NULL);
		writelog(LOG_ERR,"不能返回吧???");	
	}
	
L_RETU:
	writelog(LOG_ERR,"获取对账文件失败");	
	return -1;

}
