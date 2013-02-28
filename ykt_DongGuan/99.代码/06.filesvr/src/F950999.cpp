/* --------------------------------------------
 * ��������: F950999.cpp
 * ��������: 2010-12-07
 * ��������: ����
 * ������: �ϴ������ļ�
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "filesvr.h"

static void gen_session_id(char *session,int len)
{
	const char session_tbl[] = {'1','2','3','4','5','6','7','8','9','0',
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
	'r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H',
	'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y',
	'Z','-','=','~','+'};
	int idx,i;
	double tbl_len = sizeof(session_tbl);
	srand((unsigned)time(NULL));
	for(i = 0;i < len;++i)
	{
		idx = (tbl_len * rand()/(RAND_MAX+1.0));
		session[i] = session_tbl[idx];
	}
}
static void get_dest_file_name(const char *filepath,char *realpath)
{
	const char* startp;
	if(strstr(filepath,"..") != NULL)
	{
		startp = strrchr(filepath,FILE_SEP[0]);
	}
	else
	{
		if(filepath[0] == FILE_SEP[0])
		{
			startp = filepath+1;
		}
		else
		{
			startp = filepath;
		}
	}
	strcpy(realpath,startp);
}

int F950999(BCCHandle &handle, char *szMsg)
{
	char szfile[256];
	char full_path[512] = "";
	char temp_path[512] = "";
	char session_id[256] = {0};
	int maxlen,ret,head_len;
	char temp[5] = "";
	char *pend;
	char data[8096];
	int file_len,flag,datalen;
	FILE *fp;
	struct stat fst;
	memset(&fst,0,sizeof fst);

	maxlen = 4096;
	handle.GetIntFieldByName("lvol1",&flag);
	//writelog(LOG_DEBUG,"orign file[%s]total[%d]",rpack->vsmess,rpack->lvol0);
	ret = KSConfiguration::getInstance()->GetStringPara("uploaddir",full_path);
	if(ret)
	{
		strcpy(szMsg,"δ������Ŀ¼");
		return ret;
	}
	// ��Ϊ�ǵ�һ������������һ�������
	if(BSGetXPackType(handle.bcc_handle_) == 0)
	{
		// ��ȡ�ļ���, ȥ��·��
		//file_len = rpack->lvol0;
		handle.GetIntFieldByName("lvol0",&file_len);
		handle.GetStringFieldByName("vsmess",szfile);
		pend = strrchr(szfile,FILE_SEP[0]);
		if(pend)
		{
			if(pend >= strlen(szfile) + szfile)
			{
				strcpy(szMsg,"������ļ����ȴ���");
				return -1;
			}
			get_dest_file_name(szfile,szfile);
		}
		else
			strcpy(szfile,szfile);
		
		strcat(full_path,FILE_SEP);
		strcpy(temp_path,full_path);
		strcat(full_path,szfile);
		
		//SetCol(handle,F_LVOL0,F_SCUST_LIMIT, F_VSMESS, 0);
		
		if(flag == 0xFF)
		{
			handle.GetStringFieldByName("scust_limit",session_id);
			strcat(temp_path,session_id);
			// �ļ�����,�ж��ļ���С
			stat(temp_path, &fst);
			if(fst.st_size != file_len)
			{
				sprintf(szMsg,"upload file[%s] length error,orign[%d],[%d]!"
					,full_path,file_len,fst.st_size);
				return -1;
			}
			// �������ļ�
			
			if(rename(temp_path,full_path))
			{
				strcpy(szMsg,"�������ļ�����");
				return -1;
			}
		}
		else
		{
			// ��һ����ɾ��ԭʼ�ļ�
			unlink(full_path);
			// ����session id
			gen_session_id(session_id,10);
			handle.SetStringFieldByName("scust_limit",session_id);
		}
		// �����ļ���
		//rpack->lvol0 = file_len;
		//des2src(rpack->vsmess,szfile);
		//PutRow(handle, rpack, pRetCode, szMsg);
		handle.SetIntFieldByName("lvol0",file_len);
		handle.SetStringFieldByName("vsmess",szfile);
		handle.PutRow(0);
		return 0;
	}
	// ��Ϊ�Ǻ�����
	// ȡ��ͷ����
	datalen = BSGetRawRecord(handle.bcc_handle_,0,data,sizeof(data));
	if(datalen < 0)
	{
		strcpy(szMsg,"���ݴ���");
		return -1;
	}
	strncpy(temp,data,4);
	temp[4] = '\0';
	head_len = strtoul(temp,NULL,16);
	if(head_len > datalen)
	{
		strcpy(szMsg,"�ļ����Ȳ���ȷ");
		return -1;
	}
	// �ļ���
	strncpy(szfile,data+4,head_len-5);
	szfile[head_len-5] = '\0';
	// ���ı�־
	flag = data[head_len-1];
	// �ļ�ȫ·��
	strcat(full_path,FILE_SEP);
	strcat(full_path,szfile);
	//writelog(LOG_DEBUG,"write file[%s]",full_path);
	
	if(flag != 0xFF)
	{
		// �Զ����ƴ��ļ�
		fp = fopen(full_path, "a+b");
		if (fp == NULL)
		{
			sprintf(szMsg, "Cannot open the file:<%s>!", szfile);
			return 9980;
		}
		else
		{
			fwrite(data+head_len,datalen-head_len,1,fp);
			fclose(fp);
			stat(full_path, &fst);
			sprintf(szMsg, "%ld", fst.st_mtime);
			if(flag == 0xFF)
			{
				// �ļ��ϴ����,У���ļ�
			}
		}
	}
	//SetCol(handle,F_LVOL0, F_VSMESS, 0);
	// �ļ���С
	//rpack->lvol0 = fst.st_size;
	//des2src(rpack->vsmess, szMsg);
	//PutRow(handle, rpack, pRetCode, szMsg);
	handle.SetStringFieldByName("vsmess",szMsg);
	handle.SetIntFieldByName("lvol0",fst.st_size);
	handle.PutRow(0);
	return 0;

}

