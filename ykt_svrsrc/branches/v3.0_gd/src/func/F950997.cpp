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
#include "acctrans.h"

char temp_path[512] = "/tmp";
/*
static int Endfile(int file_len)
{
	struct stat fst;
	memset(&fst,0,sizeof fst);
	stat(temp_path, &fst);
	if(fst.st_size != file_len)
	{
		writelog(LOG_ERR,"upload file[%s] length error,orign[%d],[%d]!"
			,temp_path,file_len,fst.st_size);
		return E_UPLOAD_FILE_CRC;		
	}
	// �������ļ�	
	if(rename(temp_path,full_path))
	{
		return E_UPLOAD_CONFLICT;
	}
	
	return 0;
}
static int WriteFile(const void *data,int length)
{	
	FILE *fp =NULL;
	fp = fopen(temp_path, "ab+");
	if (fp == NULL)
	{
		writelog(LOG_ERR,"Cannot open the file:<%s>!", temp_path);
		ERRTIP("���������ļ�ʧ��");
		return E_COMMON_ERR;
	}
	if(fwrite(data,length,1,fp)!=1)
		{
			fclose(fp);
			ERRTIP("д��¼�������ļ�ʧ��");
			return E_COMMON_ERR;
		}
		fclose(fp);
	return 0;
}
*/


int F950997(TRUSERID *handle, int iRequest, ST_PACK *rpack, int *pRetCode, char *szMsg)
{
	char szChkfile[256]="";
	char chkacc_date[9] = "";
	char delflag[2] = "";
	int row = 0;
	int ret = 0;
	int requestType = 0;	
	int bccdrtpno =0;
	int bccfuncno =0;
	int bcctimeout = 0;
	char sysdate[11]="";
	char remotefilepath[256]="";
	char temp_name[11] = "";

	char exc_path[256]="";						//���˳���·��
	char exc_name[64]="";						// ���˳�������

	ST_PACK ArrayPack[5];		// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	T_t_cfgaccchk cfgaccchk;
	memset(&cfgaccchk,0,sizeof cfgaccchk);
	
	des2src(chkacc_date,rpack->sdate0);
	sprintf(szChkfile,"%s/bank_accchk%s.circle",temp_path,chkacc_date);				// �����ļ�������������ǰ���ϵĽű�������
	
	ret = DB_t_cfgaccchk_read_by_accchktype(rpack->lsafe_level2,&cfgaccchk);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_CFGACCCHK_N;
		else
			return E_DB_CFGACCCHK_R;
	}
	bccdrtpno = cfgaccchk.bccdrtpno;
	bccfuncno = cfgaccchk.bccfuncno;
	bcctimeout = cfgaccchk.bcctimeout;
	des2src(remotefilepath,cfgaccchk.accchkfilepath);
	des2src(exc_name,cfgaccchk.accchkexcname);
	des2src(delflag,cfgaccchk.delflag);
	
	requestType = 950996;									// ǰ���϶��ļ��������ļ��Ĺ��ܺ�
		
	char *BinPath=NULL;
	BinPath=getenv("BIN_PATH");
	if(!BinPath)
	{
		fprintf(stderr,"genenv bin_path error");
		exit(-1);
	}
	sprintf(exc_path,"%s/%s",BinPath,exc_name);

	// ��ɾ��ԭʼ�ļ�
	writelog(LOG_DEBUG,"begin upload file[%s]!",szChkfile);
	// ����session id
//	gen_session_id(temp_name,10);	
//	char tmpfile[256];
//	sprintf(tmpfile,"/tmp/%s",temp_name);

	ResetNormalCPack(&sPack, 0, 1);
	SetPackHeadCol(&sPack.head,F_LVOL5,F_VSVARSTR0,F_VSMESS,F_SDATE1,0);
	sPack.head.RequestType = requestType;
	des2src(sPack.pack.vsvarstr0,remotefilepath);						// ·��
	des2src(sPack.pack.vsmess,szChkfile);								    // �ļ���
	des2src(sPack.pack.sdate1,chkacc_date);								// ��������
	sPack.pack.lvol5 = (delflag[0]=='1'?1:0);							// ɾ�������ļ�
	
	writelog(LOG_INFO,"get remote check file [%s]/[%s]",remotefilepath,szChkfile);
	memset(&ArrayPack,0,sizeof(ArrayPack));
	row = ExtCall(0, bccdrtpno, bccfuncno, 0, bcctimeout, &sPack, &aPack, ArrayPack);
	if (row < 0||aPack.head.retCode!=0)
	{
		if(row<0)
		{
			writelog(LOG_ERR,"Call 950996 error,errcode=[%d],retCode=[%d]Msg[%s]",ret,aPack.head.retCode,aPack.pack.vsmess);
			return ret;
		}
		else
		{
			strcpy(szMsg,aPack.pack.vsmess);
			writelog(LOG_ERR,"Call 950996 error,errcode=[%d],retCode=[%d]Msg[%s]",ret,aPack.head.retCode,aPack.pack.vsmess);
			return  E_COMMON_ERR;
		}
	}
	FILE *fp =NULL;
	fp = fopen(szChkfile, "wb");
	if (fp == NULL)
	{
		writelog(LOG_ERR,"Cannot open the file:<%s>!", szChkfile);
		ERRTIP("���������ļ�%sʧ��",szChkfile);
		return E_COMMON_ERR;
	}
	
	ST_SDPACK *psd=NULL;
	while(row >0)
	{		
		psd=(ST_SDPACK *)&(aPack.pack);
		if(fwrite(psd->data,psd->usDataLength,1,fp)!=1)
		{
			fclose(fp);
			ERRTIP("д��¼�������ļ�ʧ��");
			return E_COMMON_ERR;
		}
		for(int i=0;i<aPack.head.recCount-1;i++)
		{
			psd=(ST_SDPACK *)&ArrayPack[i];
			if(fwrite(psd->data,psd->usDataLength,1,fp)!=1)
			{
				fclose(fp);
				ERRTIP("д��¼�������ļ�ʧ��");
				return E_COMMON_ERR;
			}
		}
		memset(&ArrayPack,0,sizeof(ArrayPack));
		row=ExtCallNext(bcctimeout,&aPack,ArrayPack);		
		if(-3==row||0==row)
		{
			break;
		}	
		if(row<0)
		{
			writelog(LOG_ERR,"ExtCallNext ret=%d",row);			
			fclose(fp);
			return ret;
		}
	}
	fclose(fp);
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
		des2src(out_pack->vsvarstr0, szChkfile);
		des2src(out_pack->vsmess, "ȡ�����ļ��ɹ�����ʼ���ˣ����Ժ��ѯ���˽��");
		des2src(out_pack->sdate0, chkacc_date);		

		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}
	else				// �ӽ��̽��ж���
	{
		//writelog(LOG_DEBUG,"exc_path[%s],exc_name[%s],chkdate[%s],full_path[%s]",exc_path,exc_name,chkacc_date,BinPath);
		execl(exc_path,exc_name,chkacc_date,szChkfile,NULL);
        exit(0);
	}
	return 0;	
}
