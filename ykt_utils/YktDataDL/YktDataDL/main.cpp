/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  自动文件下载功能
 *
 *        Version:  1.0
 *        Created:  2008-8-8 15:06:59
 *       Revision:  $Id$
 *       Compiler:  msvc
 *
 *         Author:  汤成 (tc), cheng.tang@sungard.com
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
 * @brief 配置文件名
 */
static const char g_config_file[] = "yktdata.ini";

/** 
 * @brief 查询数据请求功能号
 */
static const int g_query_data_func = 950103;
/** 
 * @brief 上传后处理数据功能号
 */
static const int g_process_data_func = 950104;

/** 
 * @brief 下载数据文件保存路径
 */
static const char g_data_file_dir[] = "data";
/** 
 * @brief 主程序路径
 */
static string g_exe_path;

/** 
 * @brief 向后台请求的超时时间
 */
static int g_req_timeout = 3; // 3秒

/** 
 * @brief 全局日志对象
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
	char ext_call_path[1024]; // 外调程序名
	char ext_call_param[1024]; // 外调程序参数
}auto_dl_rec_t;

/** 
 * @brief 取得当前日期
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
 * @brief 取得指定日期的以后日期
 * 
 * @param start - 开始日期
 * @param span - 跨度
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
 * @brief 初始化程序参数
 * 
 * @return 0 表示成功，-1 表示失败
 */
static int init()
{
	DWORD ret;
	char path[1024] = "";
	ret = GetModuleFileName(NULL,path,(sizeof path)-1);
	if(ret == 0)
	{
		printf("获取程序路径失败!\n");
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
		printf("打开日志文件失败!\n");
		return -1;
	}
	//TODO : 初始化 BCCCLT
	sprintf(path,"%s\\%s",g_exe_path.c_str(),g_config_file);
	DEBUG_LOG(("加载配置文件[%s]",path));
	CCIniFile inifile(path);
	string ip;
	int port,mainfunc;
	ip = inifile.ReadString("SERVER","ip","");
	if(ip.empty())
	{
		DEBUG_LOG(("读取服务器IP失败"));
		return -1;
	}
	port = inifile.ReadInteger("SERVER","port",0);
	if(port == 0)
	{
		DEBUG_LOG(("读取服务器端口失败"));
		return -1;
	}
	mainfunc = inifile.ReadInteger("SERVER","mainfunc",0);
	if(mainfunc == 0)
	{
		DEBUG_LOG(("读取主功能号失败"));
		return -1;
	}
	g_req_timeout = inifile.ReadInteger("SERVER","timeout",3);
	g_req_timeout *= 1000;

	if((ret = KSG_init(ip.c_str(),port,mainfunc))!=0)
	{
		DEBUG_LOG(("初始化文件下载引擎失败,ret[%d]",ret));
		return -1;
	}
	int drtp_no = KSG_Get_DRTPNO();
	sprintf(path,"%s\\cpack.dat",g_exe_path.c_str());
	KS_YKT_Clt::set_xpack_path(path);
	//if(!KS_YKT_Clt::Initialize(ip.c_str(),port,mainfunc))
	if(!KS_YKT_Clt::Initialize2(drtp_no,mainfunc))
	{
		DEBUG_LOG(("初始化BCCCLT失败,ret[%d]",ret));
		return -1;
	}
	
	DEBUG_LOG(("初始化成功!"));
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
	// 没有配置外调
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
		DEBUG_LOG(("[%s]外调程序错误",rec->comments));
		return -1;
	}
	else
	{
		DEBUG_LOG(("[%s]外调程序成功",rec->comments));
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
	DEBUG_LOG(("开始下载数据文件[%s]日期[%s]...",rec->comments,rec->rec_date));
	KS_YKT_Clt clt;
	clt.SetStringFieldByName("sall_name",rec->req_type);
	clt.SetStringFieldByName("sdate0",rec->rec_date);
	clt.SetStringFieldByName("stime0",rec->begin_time);
	clt.SetStringFieldByName("stime1",rec->end_time);
	clt.SetIntFieldByName("lvol0",rec->area);
	clt.SetStringFieldByName("vsmess",rec->param);
	if(clt.SendRequest(g_query_data_func,g_req_timeout))
	{
		// 请求成功
		memset(msg,0,sizeof msg);
		ret = clt.GetReturnCode();
		if(ret)
		{
			// 返回错误信息
			clt.GetReturnMsg(msg);
			DEBUG_LOG(("查询数据失败,返回[%d][%s]",ret,msg));
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
		// 下载文件
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
			DEBUG_LOG(("下载文件[%s]",local_path));
			KSG_File_Handle request = KSG_begin_request();
			KSG_set_param(request,"src_filename",msg,strlen(msg));
			KSG_set_param(request,"dest_filename",local_path,strlen(local_path));
			param[0] = '0';
			KSG_set_param(request,"upload",param,strlen(param));
			// 是否删除服务器上文件
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
				DEBUG_LOG(("下载[%s]数据文件失败,ret[%d]",rec->comments,ret));
				return -1;
			}
			else
			{
				DEBUG_LOG(("下载[%s]保存[%s]",rec->comments,local_path));
				do_ext_call(rec,local_path);
				return 0;
			}
		}

	}
	clt.GetReturnMsg(msg);
	DEBUG_LOG(("发送查询请求失败,可能网络正忙,请检查网络稍后重试...[%s]",msg));
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
		// 取默认路径
		sprintf(local_path,"%s\\%s",g_exe_path.c_str(),g_data_file_dir);
	}
	else
	{
		strcpy(local_path,rec->src_path);
	}

	// 取文件名
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
	// 完整文件路径
	strcat(local_path,"\\");
	strcat(local_path,file_name);
	do_ext_call(rec,local_path);
	// 上传文件 
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
		DEBUG_LOG(("上传[%s]数据文件失败[%s],ret[%d]",rec->comments,local_path,ret));
		ret = -1;
	}
	else
	{
		DEBUG_LOG(("上传[%s]保存[%s]",rec->comments,file_name));
		ret = 0;
	}
	if(!ret)
	{
		// 上传文件成功，调用 950104
		KS_YKT_Clt clt;
		clt.SetStringFieldByName("sall_name",rec->req_type);
		clt.SetStringFieldByName("sdate0",rec->rec_date);
		clt.SetStringFieldByName("stime0",rec->begin_time);
		clt.SetStringFieldByName("stime1",rec->end_time);
		clt.SetIntFieldByName("lvol0",rec->area);
		clt.SetStringFieldByName("vsvarstr0",file_name); // 上传文件名
		clt.SetStringFieldByName("vsmess",rec->param); // 参数
		ret = -1;
		if(clt.SendRequest(g_process_data_func,g_req_timeout))
		{
			// 请求成功
			memset(msg,0,sizeof msg);
			ret = clt.GetReturnCode();
			if(ret)
			{
				// 返回错误信息
				clt.GetReturnMsg(msg);
				DEBUG_LOG(("处理数据失败,返回[%d][%s]",ret,msg));
				return -1;
			}
			else
			{
				DEBUG_LOG(("处理数据[%s][%s]成功!",rec->comments,file_name));
				if(rec->del_local)
					unlink(local_path); // 删除本地文件
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
			DEBUG_LOG(("上传数据文件失败,ret[%d]",ret));
	}
	else
	{
		ret = do_download_record(rec);
		if(ret)
			DEBUG_LOG(("下载数据文件失败,ret[%d]",ret));
	}
	return ret;
}

/** 
 * @brief 从日期的开始范围到结束范围下载文件
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
		DEBUG_LOG(("下载[%s]指定日期[%s]数据",rec->comments,rec->rec_date));
#endif
		count++;
		if(ret)
		{
			DEBUG_LOG(("下载[%s]指定日期[%s]数据失败!",rec->comments,rec->rec_date));
			// 连接失败,退出循环
			if(-2 == ret)
				return -1;
		}
		GetNextDay(rec->rec_date,1,rec->rec_date);
		if(count >= max_day)
		{
			DEBUG_LOG(("连续下载文件数量不能超过%d天",max_day));
			return 0;
		}
	}while(1);
	return 0;
}

static int do_read_sect_config(auto_dl_rec_t *rec,const string &sect_name,CCIniFile &inifile)
{		
	string val;
	// 名称
	val = inifile.ReadString(sect_name.c_str(),"name","");
	if(val.empty())
		return -1;
	strcpy(rec->req_type,val.c_str());
	// 校区
	rec->area = inifile.ReadInteger(sect_name.c_str(),"area",0);
	// 开始时间
	val = inifile.ReadString(sect_name.c_str(),"begintime","");
	memcpy(rec->begin_time,val.c_str(),6);
	// 结束时间
	val = inifile.ReadString(sect_name.c_str(),"endtime","");
	memcpy(rec->end_time,val.c_str(),6);
	// 备注说明
	val = inifile.ReadString(sect_name.c_str(),"comments","");
	memcpy(rec->comments,val.c_str(),sizeof(rec->comments) - 1);
	//文件下载到本地后重命名
	val = inifile.ReadString(sect_name.c_str(),"localname","");
	memcpy(rec->local_name, val.c_str(), sizeof(rec->local_name)-1);	
	val = inifile.ReadString(sect_name.c_str(),"suffix","");
	memcpy(rec->suffix, val.c_str(), sizeof(rec->suffix)-1);
	// 上传文件路径
	val = inifile.ReadString(sect_name.c_str(),"srcpath","");
	if(!val.empty())
		strcpy(rec->src_path,val.c_str());
	// 是上传还是下载
	rec->is_upload = inifile.ReadInteger(sect_name.c_str(),"upload",0);
	// 上传之后是否删除本地文件 
	rec->del_local = inifile.ReadInteger(sect_name.c_str(),"dellocal",0);
	// 下载参数
	val = inifile.ReadString(sect_name.c_str(),"param","");
	memcpy(rec->param, val.c_str(), sizeof(rec->param)-1);
	// 外调程序名
	val = inifile.ReadString(sect_name.c_str(),"execpath","");
	memcpy(rec->ext_call_path,val.c_str(),sizeof(rec->ext_call_path)-1);
	// 外调程序参数
	val = inifile.ReadString(sect_name.c_str(),"execarg","");
	memcpy(rec->ext_call_param,val.c_str(),sizeof(rec->ext_call_param)-1);
	return 0;

}
/** 
 * @brief 通过配置文件自动处理数据
 * 
 * @return - 0 表示成功 ， 失败返回错误码
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
			DEBUG_LOG(("数据[%s]不需要自动下载",val.c_str()));
			continue;
		}
		// 当前日期
		memcpy(dl_rec.rec_date,curr_datetime,8);
		// 读取配置
		do_read_sect_config(&dl_rec,sect_name,inifile);
		flag = do_request_record(&dl_rec);
		if(flag)
		{
			//DEBUG_LOG(("下载文件失败,返回[%d]",flag));
			if(-2 == flag)
			{
				// 网络故障,直接退出
				return -1;
			}
		}
		else
		{
			//DEBUG_LOG(("下载数据文件成功!"));
		}
	}
	return 0;
}

static void print_usage()
{
	printf("使用方法: ");
	printf("ver: %s Copyright SunGard China All rights reserved 2008\n",YKTDATADL_VER);
	printf("YktDataDL [-s sect_name -d YYYYMMDD YYYYMMDD]\n");
	exit(1);
}
/** 
 * @brief 主函数
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
	// 初始化
	
	if(argc <= 1)
	{
		if(init())
		{
			return -1;
		}
		// 读取配置文件进行处理
		return process_config_file();
	}
	else
	{
		memset(&rec,0,sizeof rec);
		memset(begin_date,0,sizeof begin_date);
		memset(end_date,0,sizeof end_date);
		// 根据参数下载文件
		for(i = 1;i < argc;++i)
		{
			if(strcmp(argv[i],"-s") == 0)
			{
				// 下载数据内容名称
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
			DEBUG_LOG(("读取[%s]的配置失败,不能下载文件",rec.req_type));
			return -1;
		}
		return do_request_record_span_date(&rec,begin_date,end_date);
	}
	return 0;
}

