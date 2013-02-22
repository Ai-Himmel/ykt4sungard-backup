/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  �Զ��ļ����ع���
 *
 *        Version:  1.0
 *        Created:  2008-8-8 15:06:59
 *       Revision:  $Id$
 *       Compiler:  msvc
 *
 *         Author:  ���� (tc), cheng.tang@sungard.com
 *        Company:  Sungard China
 *
 * =====================================================================================
 */

#include <string>
#include <time.h>
#include <windows.h>
#include <vector>
#include <map>
#include "logfile.h"
#include "CInifile.h"
#include "yktclt.h"
#include "Filetrans.h"

#define YKTDATADL_VER "1.1"
using namespace std;

#define src2des(d,s) do { memcpy(d,s,sizeof(d)-1); d[sizeof(d)-1]='\0'; } while(0)
/** 
 * @brief �����ļ���
 */
static const char g_config_file[] = "yktdata.ini";

/** 
 * @brief ��ѯ���������ܺ�
 */
static const int g_query_data_func = 950103;
/** 
 * @brief �ϴ��������ݹ��ܺ�
 */
static const int g_process_data_func = 950104;

/** 
 * @brief ���������ļ�����·��
 */
static const char g_data_file_dir[] = "data";
/** 
 * @brief ������·��
 */
static string g_exe_path;

/** 
 * @brief ���̨����ĳ�ʱʱ��
 */
static int g_req_timeout = 3; // 3��

/** 
 * @brief ȫ����־����
 */
KSYkt_Log_Writer g_logger("YktDataDL");

typedef struct {
	char req_type[20];
	char rec_date[9];
	char begin_time[7];
	char end_time[7];
	char comments[512];
	int area;
	char local_name[64];
	char suffix[8];
	int is_upload;
	int del_local;
	char src_path[1024];
	char param[256];
	char ext_call_path[1024]; // ���������
	char ext_call_param[1024]; // ����������
}auto_dl_rec_t;

/** 
 * @brief ȡ�õ�ǰ����
 * 
 * @param time_str 
 */
static void get_current_time(char time_str[15])
{
	time_t curr;
	struct tm curr_tm;
	time(&curr);
	curr_tm = *localtime(&curr);
	sprintf(time_str,"%.04d%.02d%.02d%.02d%.02d%.02d",curr_tm.tm_year+1900
		,curr_tm.tm_mon+1,curr_tm.tm_mday,curr_tm.tm_hour
		,curr_tm.tm_min,curr_tm.tm_sec);
}

/** 
 * @brief ȡ��ָ�����ڵ��Ժ�����
 * 
 * @param start - ��ʼ����
 * @param span - ���
 * @param next - 
 * 
 * @return 
 */
static int GetNextDay(const char start[9],int span,char next[9])
{
	char tmp[5] = "";
	time_t t;
	struct tm *ptm;
	int ch;
	int i;
	for(i = 0;i < 8;++i)
	{
		ch = start[i];
		if(!isdigit(ch) )
		{
			return -2;
		}
	}
	time(&t);
	ptm = localtime(&t);
	memcpy(tmp,start,4);
	ptm->tm_year = atoi(tmp) - 1900;
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,start+4,2);
	ptm->tm_mon = atoi(tmp) - 1;
	memcpy(tmp,start+6,2);
	ptm->tm_mday = atoi(tmp);

	t = mktime(ptm);
	t += 3600 * 24 * span;
	ptm = localtime(&t);
	sprintf(next,"%.04d%.02d%.02d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday);

	return 0;
}

/** 
 * @brief ��ʼ���������
 * 
 * @return 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
static int init()
{
	DWORD ret;
	char path[1024] = "";
	ret = GetModuleFileName(NULL,path,(sizeof path)-1);
	if(ret == 0)
	{
		printf("��ȡ����·��ʧ��!\n");
		return -1;
	}
	char *p;
	p = strrchr(path,'\\');
	if(p)
		*p = '\0';
	g_exe_path = path;
	sprintf(path,"%s\\logs",g_exe_path.c_str());
	ret  = g_logger.openlog(path);
	if(ret)
	{
		printf("����־�ļ�ʧ��!\n");
		return -1;
	}
	//TODO : ��ʼ�� BCCCLT
	sprintf(path,"%s\\%s",g_exe_path.c_str(),g_config_file);
	DEBUG_LOG(("���������ļ�[%s]",path));
	CCIniFile inifile(path);
	string ip;
	int port,mainfunc;
	ip = inifile.ReadString("SERVER","ip","");
	if(ip.empty())
	{
		DEBUG_LOG(("��ȡ������IPʧ��"));
		return -1;
	}
	port = inifile.ReadInteger("SERVER","port",0);
	if(port == 0)
	{
		DEBUG_LOG(("��ȡ�������˿�ʧ��"));
		return -1;
	}
	mainfunc = inifile.ReadInteger("SERVER","mainfunc",0);
	if(mainfunc == 0)
	{
		DEBUG_LOG(("��ȡ�����ܺ�ʧ��"));
		return -1;
	}
	g_req_timeout = inifile.ReadInteger("SERVER","timeout",3);
	g_req_timeout *= 1000;

	if((ret = KSG_init(ip.c_str(),port,mainfunc))!=0)
	{
		DEBUG_LOG(("��ʼ���ļ���������ʧ��,ret[%d]",ret));
		return -1;
	}
	int drtp_no = KSG_Get_DRTPNO();
	sprintf(path,"%s\\cpack.dat",g_exe_path.c_str());
	KS_YKT_Clt::set_xpack_path(path);
	//if(!KS_YKT_Clt::Initialize(ip.c_str(),port,mainfunc))
	if(!KS_YKT_Clt::Initialize2(drtp_no,mainfunc))
	{
		DEBUG_LOG(("��ʼ��BCCCLTʧ��,ret[%d]",ret));
		return -1;
	}
	
	DEBUG_LOG(("��ʼ���ɹ�!"));
	return 0;
}
static int do_ext_call(auto_dl_rec_t *rec,const char *localpath)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL ret;
	char *p;
	int i;
	char exe_arg[4096] = "";
	// û���������
	if(strlen(rec->ext_call_path)==0)
		return 0;
	memset(&si,0,sizeof si);
	memset(&pi,0,sizeof pi);

	si.cb = sizeof(si);

	//sprintf(exe_arg,"%s")
	p = strstr(rec->ext_call_param,"$datafile");
	if(p)
	{
		i = p-rec->ext_call_param;
		strncpy(exe_arg,rec->ext_call_param,i);
		strcpy(exe_arg+i,localpath);
		i += strlen(localpath);
		strcpy(exe_arg+i,p+strlen("$datafile"));
	}
	else
	{
		strcpy(exe_arg,rec->ext_call_param);
	}
	strcat(rec->ext_call_path," ");
	strcat(rec->ext_call_path,exe_arg);
	ret = CreateProcess(NULL,rec->ext_call_path,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);
	if(!ret)
	{
		DEBUG_LOG(("[%s]����������",rec->comments));
		return -1;
	}
	else
	{
		DEBUG_LOG(("[%s]�������ɹ�",rec->comments));
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return 0;
}

static int do_download_record(auto_dl_rec_t *rec)
{
	int ret;
	char *post = NULL;
	char local_name[1024]="";
	char download_path[1024]="";
	char msg[512];
	char local_path[1024];
	DEBUG_LOG(("��ʼ���������ļ�[%s]����[%s]...",rec->comments,rec->rec_date));
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("sall_name",rec->req_type);
	clt.SetStringFieldByName("sdate0",rec->rec_date);
	clt.SetStringFieldByName("stime0",rec->begin_time);
	clt.SetStringFieldByName("stime1",rec->end_time);
	clt.SetIntFieldByName("lvol0",rec->area);
	clt.SetStringFieldByName("vsmess",rec->param);
	if(clt.SendRequest(g_query_data_func,g_req_timeout))
	{
		// ����ɹ�
		memset(msg,0,sizeof msg);
		ret = clt.GetReturnCode();
		if(ret)
		{
			// ���ش�����Ϣ
			clt.GetReturnMsg(msg);
			DEBUG_LOG(("��ѯ����ʧ��,����[%d][%s]",ret,msg));
			return -1;
		}
		if(strlen(rec->src_path)>0)
		{
			sprintf(download_path,"%s",rec->src_path);
		}
		else
		{
			sprintf(download_path,"%s\\%s",g_exe_path.c_str(),g_data_file_dir);
		}
		// �����ļ�
		if(clt.HasMoreRecord())		
		{
			char param[64] = "";
			clt.GetNextPackage();
			clt.GetStringFieldByName("vsvarstr0",msg,sizeof(msg)-1);
			memset(local_path,0,sizeof local_path);
			if (strlen(rec->local_name))
			{	
				if (NULL != (post = strstr(rec->local_name,"date")))	
				{
					memset(local_name,0,sizeof local_name);
					strncpy(local_name,rec->local_name,post - rec->local_name);
					strcat(local_name,rec->rec_date);
				}
				else
				{
					strcpy(local_name,rec->local_name);
				}
									
				sprintf(local_path,"%s\\%s.%s",download_path,local_name,rec->suffix);
			}
			else
				sprintf(local_path,"%s\\%s",download_path,msg);
			DEBUG_LOG(("�����ļ�[%s]",local_path));
			KSG_File_Handle request = KSG_begin_request();
			KSG_set_param(request,"src_filename",msg,strlen(msg));
			KSG_set_param(request,"dest_filename",local_path,strlen(local_path));
			param[0] = '0';
			KSG_set_param(request,"upload",param,strlen(param));
			// �Ƿ�ɾ�����������ļ�
			if(rec->del_local)
				param[0] = '1';
			else
				param[0] = '0';
			KSG_set_param(request,"del_svrfile",param,1);
			sprintf(param,"%d",g_req_timeout);
			KSG_set_param(request,"timeout",param,strlen(param));
			ret = KSG_send_request(request);
			KSG_free_request(request);
			if(ret)
			{
				DEBUG_LOG(("����[%s]�����ļ�ʧ��,ret[%d]",rec->comments,ret));
				return -1;
			}
			else
			{
				DEBUG_LOG(("����[%s]����[%s]",rec->comments,local_path));
				do_ext_call(rec,local_path);
				return 0;
			}
		}

	}
	clt.GetReturnMsg(msg);
	DEBUG_LOG(("���Ͳ�ѯ����ʧ��,����������æ,���������Ժ�����...[%s]",msg));
	return -2;
}

static int do_upload_record(auto_dl_rec_t *rec)
{
	char local_path[1024] = "";
	char file_name[512] = "";
	int ret;
	char param[10] = "";
	char msg[1024] = "";
	char *post = NULL;
	if(strlen(rec->src_path)==0)
	{
		// ȡĬ��·��
		sprintf(local_path,"%s\\%s",g_exe_path.c_str(),g_data_file_dir);
	}
	else
	{
		strcpy(local_path,rec->src_path);
	}

	// ȡ�ļ���
	if(NULL != (post = strstr(rec->local_name,"date")))
	{
		strncpy(file_name,rec->local_name,post-rec->local_name);
		strcat(file_name,rec->rec_date);
		strcat(file_name,".");
		strcat(file_name,rec->suffix);
	}
	else
	{
		sprintf(file_name,"%s.%s",rec->local_name,rec->suffix);
	}
	// �����ļ�·��
	strcat(local_path,"\\");
	strcat(local_path,file_name);
	do_ext_call(rec,local_path);
	// �ϴ��ļ� 
	KSG_File_Handle request = KSG_begin_request();
	KSG_set_param(request,"src_filename",local_path,strlen(local_path));
	KSG_set_param(request,"dest_filename",file_name,strlen(file_name));
	param[0] = '1';
	KSG_set_param(request,"upload",param,strlen(param));
	sprintf(param,"%d",g_req_timeout);
	KSG_set_param(request,"timeout",param,strlen(param));
	ret = KSG_send_request(request);
	KSG_free_request(request);
	if(ret)
	{
		DEBUG_LOG(("�ϴ�[%s]�����ļ�ʧ��[%s],ret[%d]",rec->comments,local_path,ret));
		ret = -1;
	}
	else
	{
		DEBUG_LOG(("�ϴ�[%s]����[%s]",rec->comments,file_name));
		ret = 0;
	}
	if(!ret)
	{
		// �ϴ��ļ��ɹ������� 950104
		KS_YKT_Clt clt;
		clt.SetStringFieldByName("sall_name",rec->req_type);
		clt.SetStringFieldByName("sdate0",rec->rec_date);
		clt.SetStringFieldByName("stime0",rec->begin_time);
		clt.SetStringFieldByName("stime1",rec->end_time);
		clt.SetIntFieldByName("lvol0",rec->area);
		clt.SetStringFieldByName("vsvarstr0",file_name); // �ϴ��ļ���
		clt.SetStringFieldByName("vsmess",rec->param); // ����
		ret = -1;
		if(clt.SendRequest(g_process_data_func,g_req_timeout))
		{
			// ����ɹ�
			memset(msg,0,sizeof msg);
			ret = clt.GetReturnCode();
			if(ret)
			{
				// ���ش�����Ϣ
				clt.GetReturnMsg(msg);
				DEBUG_LOG(("��������ʧ��,����[%d][%s]",ret,msg));
				return -1;
			}
			else
			{
				DEBUG_LOG(("��������[%s][%s]�ɹ�!",rec->comments,file_name));
				if(rec->del_local)
					unlink(local_path); // ɾ�������ļ�
				ret = 0;
			}
		}
	}
	return ret;
}
static int do_request_record(auto_dl_rec_t *rec)
{
	int ret = 0;
	if(rec->is_upload)
	{
		ret = do_upload_record(rec);
		if(ret)
			DEBUG_LOG(("�ϴ������ļ�ʧ��,ret[%d]",ret));
	}
	else
	{
		ret = do_download_record(rec);
		if(ret)
			DEBUG_LOG(("���������ļ�ʧ��,ret[%d]",ret));
	}
	return ret;
}

/** 
 * @brief �����ڵĿ�ʼ��Χ��������Χ�����ļ�
 * 
 * @param rec  
 * @param begin_date 
 * @param end_date 
 * 
 * @return 
 */
static int do_request_record_span_date(auto_dl_rec_t *rec,const char *begin_date,const char *end_date)
{
	int ret,count;
	static const int max_day = 30;
	bool flag = false;
	src2des(rec->rec_date,begin_date);
	count = 0;
	do{
		if(strcmp(rec->rec_date,end_date) > 0)
			return 0;
#if 1
		ret = do_request_record(rec);
#else
		ret = 0;
		DEBUG_LOG(("����[%s]ָ������[%s]����",rec->comments,rec->rec_date));
#endif
		count++;
		if(ret)
		{
			DEBUG_LOG(("����[%s]ָ������[%s]����ʧ��!",rec->comments,rec->rec_date));
			// ����ʧ��,�˳�ѭ��
			if(-2 == ret)
				return -1;
		}
		GetNextDay(rec->rec_date,1,rec->rec_date);
		if(count >= max_day)
		{
			DEBUG_LOG(("���������ļ��������ܳ���%d��",max_day));
			return 0;
		}
	}while(1);
	return 0;
}

static int do_read_sect_config(auto_dl_rec_t *rec,const string &sect_name,CCIniFile &inifile)
{		
	string val;
	// ����
	val = inifile.ReadString(sect_name.c_str(),"name","");
	if(val.empty())
		return -1;
	strcpy(rec->req_type,val.c_str());
	// У��
	rec->area = inifile.ReadInteger(sect_name.c_str(),"area",0);
	// ��ʼʱ��
	val = inifile.ReadString(sect_name.c_str(),"begintime","");
	memcpy(rec->begin_time,val.c_str(),6);
	// ����ʱ��
	val = inifile.ReadString(sect_name.c_str(),"endtime","");
	memcpy(rec->end_time,val.c_str(),6);
	// ��ע˵��
	val = inifile.ReadString(sect_name.c_str(),"comments","");
	memcpy(rec->comments,val.c_str(),sizeof(rec->comments) - 1);
	//�ļ����ص����غ�������
	val = inifile.ReadString(sect_name.c_str(),"localname","");
	memcpy(rec->local_name, val.c_str(), sizeof(rec->local_name)-1);	
	val = inifile.ReadString(sect_name.c_str(),"suffix","");
	memcpy(rec->suffix, val.c_str(), sizeof(rec->suffix)-1);
	// �ϴ��ļ�·��
	val = inifile.ReadString(sect_name.c_str(),"srcpath","");
	if(!val.empty())
		strcpy(rec->src_path,val.c_str());
	// ���ϴ���������
	rec->is_upload = inifile.ReadInteger(sect_name.c_str(),"upload",0);
	// �ϴ�֮���Ƿ�ɾ�������ļ� 
	rec->del_local = inifile.ReadInteger(sect_name.c_str(),"dellocal",0);
	// ���ز���
	val = inifile.ReadString(sect_name.c_str(),"param","");
	memcpy(rec->param, val.c_str(), sizeof(rec->param)-1);
	// ���������
	val = inifile.ReadString(sect_name.c_str(),"execpath","");
	memcpy(rec->ext_call_path,val.c_str(),sizeof(rec->ext_call_path)-1);
	// ����������
	val = inifile.ReadString(sect_name.c_str(),"execarg","");
	memcpy(rec->ext_call_param,val.c_str(),sizeof(rec->ext_call_param)-1);
	return 0;

}
/** 
 * @brief ͨ�������ļ��Զ���������
 * 
 * @return - 0 ��ʾ�ɹ� �� ʧ�ܷ��ش�����
 */
static int process_config_file()
{
	auto_dl_rec_t dl_rec;
	char path[1025];
	char curr_datetime[15];
	sprintf(path,"%s\\%s",g_exe_path.c_str(),g_config_file);
	CCIniFile inifile(path);
	vector<string> all_sects;
	inifile.ReadSections(all_sects);
	vector<string>::const_iterator iter;
	get_current_time(curr_datetime);
	for(iter = all_sects.begin(); iter != all_sects.end(); ++iter)
	{
		string sect_name = *iter;
		if(sect_name == "SERVER")
			continue;
		memset(&dl_rec,0,sizeof dl_rec);
		string val;
		int flag;
		val = inifile.ReadString(sect_name.c_str(),"name","");
		if(val.empty())
			continue;
		flag = inifile.ReadInteger(sect_name.c_str(),"auto",0);
		if(flag == 0)
		{
			DEBUG_LOG(("����[%s]����Ҫ�Զ�����",val.c_str()));
			continue;
		}
		// ��ǰ����
		memcpy(dl_rec.rec_date,curr_datetime,8);
		// ��ȡ����
		do_read_sect_config(&dl_rec,sect_name,inifile);
		flag = do_request_record(&dl_rec);
		if(flag)
		{
			//DEBUG_LOG(("�����ļ�ʧ��,����[%d]",flag));
			if(-2 == flag)
			{
				// �������,ֱ���˳�
				return -1;
			}
		}
		else
		{
			//DEBUG_LOG(("���������ļ��ɹ�!"));
		}
	}
	return 0;
}

static void print_usage()
{
	printf("ʹ�÷���: ");
	printf("ver: %s Copyright SunGard China All rights reserved 2008\n",YKTDATADL_VER);
	printf("YktDataDL [-s sect_name -d YYYYMMDD YYYYMMDD]\n");
	exit(1);
}
/** 
 * @brief ������
 * 
 * @param argc 
 * @param argv 
 * 
 * @return 
 */
int main(int argc,const char **argv)
{
	int i,ret;
	 char begin_date[9],end_date[9];
	auto_dl_rec_t rec;
	char path[1025];
	// ��ʼ��
	
	if(argc <= 1)
	{
		if(init())
		{
			return -1;
		}
		// ��ȡ�����ļ����д���
		return process_config_file();
	}
	else
	{
		memset(&rec,0,sizeof rec);
		memset(begin_date,0,sizeof begin_date);
		memset(end_date,0,sizeof end_date);
		// ���ݲ��������ļ�
		for(i = 1;i < argc;++i)
		{
			if(strcmp(argv[i],"-s") == 0)
			{
				// ����������������
				if(++i >= argc)
					print_usage();
				src2des(rec.req_type,argv[i]);
			}
			else if(strcmp(argv[i],"-d")==0)
			{
				if(++i >= argc)
					print_usage();
				src2des(begin_date,argv[i]);
				if(++i >= argc)
					print_usage();
				src2des(end_date,argv[i]);
			}
		}
		if(strlen(rec.req_type) == 0 || strlen(begin_date) == 0
			|| strlen(end_date)==0)
			print_usage();
		if(init())
		{
			return -1;
		}
		sprintf(path,"%s\\%s",g_exe_path.c_str(),g_config_file);
		CCIniFile inifile(path);
		if((ret = do_read_sect_config(&rec,rec.req_type,inifile) != 0))
		{
			DEBUG_LOG(("��ȡ[%s]������ʧ��,���������ļ�",rec.req_type));
			return -1;
		}
		return do_request_record_span_date(&rec,begin_date,end_date);
	}
	return 0;
}

