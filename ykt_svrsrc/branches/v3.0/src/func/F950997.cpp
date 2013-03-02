/* --------------------------------------------
 * ��������: F950997.cpp
 * ��������: 2009-7-24
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ȡ�����ļ�����̨��ʵʩ����
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
	// �������ļ�	
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
	
	end_flag = pBuf[0];				//������־
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

	char exc_path[256]="";						//���˳���·��
	char exc_name[64]="";						// ���˳�������

	ST_PACK ArrayPack[5];		// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�
	
	des2src(chkacc_date,rpack->sdate0);
	chkfilepath_paraid = rpack->lsafe_level;				//�����ļ���ǰ�÷������ϵ�·����Ӧ��ȫ�ֲ�����
	GetFileName(rpack->lsafe_level2,chkacc_date,szfile,exc_name);	//��ȡ�����ļ�������̨���˳�������		
	if(strlen(szfile)==0 || strlen(exc_name)==0)
	{
		writelog("��ȡ�ļ���ʧ��");
		goto L_RETU;
	}

	drtbranch_paraid = rpack->lvol3;
	bccbasefuncno_paraid = rpack->lvol4;
	requestType = 950996;									// ǰ���϶��ļ��������ļ��Ĺ��ܺ�

	ret=GetSysParaVal(drtbranch_paraid,drtbranch);			// drtbranch
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], drtbranch[%s]",drtbranch_paraid,drtbranch);
	ret=GetSysParaVal(bccbasefuncno_paraid,bccbasefuncno);  //�����ܺ�
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], bccbasefuncno[%s]",bccbasefuncno_paraid,bccbasefuncno);
	ret=GetSysParaVal(chkfilepath_paraid,remotefilepath);		//ǰ�ô���ļ�·��
	if(ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"get_parameter[%d], remotefilepath[%s]",chkfilepath_paraid,remotefilepath);
	DRTP_BRANCH = atoi(drtbranch);
	BCC_BASEFUNCNO = atoi(bccbasefuncno);
	
	// ��ȡ�ļ����·��
	ret = GetSysParaVal(GLOBAL_UPLOAD_PATH,full_path);		//��̨��Ż�ȡ�Ķ����ļ�·��
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}	
	writelog(LOG_INFO,"get_parameter[%d], full_path[%s]",GLOBAL_UPLOAD_PATH,full_path);
	ret = GetSysParaVal(GOLBAL_EXC_ACC_CHK_PATH, exc_path);	//���˿�ִ�г�����·��
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(exc_path,"%s/%s",exc_path,exc_name);

	strcat(full_path,"/");
	strcpy(temp_path,full_path);
	strcat(full_path,szfile);

	// ��ɾ��ԭʼ�ļ�
	unlink(full_path);
	writelog(LOG_DEBUG,"begin upload file[%s]!",full_path);
	// ����session id
	gen_session_id(temp_name,10);		
	strcat(temp_path,temp_name);

	ResetNormalCPack(&sPack, 0, 1);
	SetPackHeadCol(&sPack.head,F_LVOL5,F_VSVARSTR0, F_VSMESS,0);
	sPack.head.RequestType = requestType;
	des2src(sPack.pack.vsvarstr0,remotefilepath);						// ·��
	des2src(sPack.pack.vsmess,szfile);								    // �ļ���
	sPack.pack.lvol5 = rpack->lvol5;									// ɾ�������ļ�
	
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
		writelog(LOG_ERR,"��������ʧ��");
		return -1;
	}
	else if(pid)			// ������Ӧ��ǰ̨
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
	else				// �ӽ��̽��ж���
	{
		writelog(LOG_INFO,"exc_path[%s],exc_name[%s],chkdate[%s],full_path[%s]",exc_path,exc_name,chkacc_date,full_path);
		execl(exc_path,exc_name,chkacc_date,full_path,NULL);
		writelog(LOG_ERR,"���ܷ��ذ�???");	
	}
	
L_RETU:
	writelog(LOG_ERR,"��ȡ�����ļ�ʧ��");	
	return -1;

}
