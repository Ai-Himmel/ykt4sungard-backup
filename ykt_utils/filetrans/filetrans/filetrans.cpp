#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include "XGetopt.h"
#include <windows.h>
#pragma comment(lib ,"..\\bin\\filetrans.lib")
#else
#include <unistd.h>
#endif
#include <iostream>
using namespace std;
#include "libfiletrans.h"

#ifndef MAX_PATH
#define MAX_PATH 1025
#endif // MAX_PATH

static int g_index;
void APIDEF mycallback(int total_len,int pack_len)
{
	printf("pack index[%d][%d]length[%d]\n",++g_index,total_len,pack_len);
}

class KSFileTrans
{
private:
	string is_upload_;
	string xpack_path_;
	string src_file_;
	string dest_file_;
	string filesvr_ip_;
	int filesvr_port_;
	int filesvr_mainfunc_;
	int doTransFile();
	void printUsage();
	int checkFilePath();
public:
	KSFileTrans();
	~KSFileTrans();
	int process(int argc,char * const argv[]);
};
////////////////////////////////////////////////////////////////
KSFileTrans::KSFileTrans():is_upload_("0"),xpack_path_("cpack.dat"),
		filesvr_port_(4000),filesvr_mainfunc_(0)
{
}
KSFileTrans::~KSFileTrans()
{

}
void KSFileTrans::printUsage()
{
	cout<<"filetrans [-h] |[-u upload file] [-i server ip] [-p port]"
		<<" [-m mainfunc] [-x xpack path] srcfile destfile"
		<<endl;
}
int KSFileTrans::checkFilePath()
{
	if(src_file_.length() == 0 || src_file_.length() > MAX_PATH)
	{
		cout<<"Source file path must less than "<<MAX_PATH<<endl;
		return -1;
	}
	if(dest_file_.length() == 0 || dest_file_.length() > MAX_PATH)
	{
		cout<<"Destination file path must less than "<<MAX_PATH<<endl;
		return -1;
	}
	return 0;
}
int KSFileTrans::process(int argc,char * const argv[])
{
	const char short_opts[]="hux:i:p:m:";
	int option;
	while((option = getopt(argc,argv,short_opts))!=EOF)
	{
		switch(option)
		{
		case 'u':
			is_upload_ = "1";
			break;
		case 'h':
			printUsage();
			return 0;
		case 'x':
			xpack_path_ = optarg;
			break;
		case 'i':
			filesvr_ip_ = optarg;
			break;
		case 'p':
			filesvr_port_ = atoi(optarg);
			break;
		case 'm':
			filesvr_mainfunc_ = atoi(optarg);
			break;
		default:
			return -1;
		}
	}
	if(optind + 2 > argc)
	{
		printUsage();
		return -1;
	}
	src_file_ = argv[optind];
	dest_file_ = argv[optind+1];
	if(checkFilePath())
	{
		return -1;
	}
	return doTransFile();
}
int KSFileTrans::doTransFile()
{
	int ret;
	char upload[2]="0";
	char source_file[1024] = "";
	KSG_init(filesvr_ip_.c_str(),filesvr_port_,filesvr_mainfunc_);
	KSG_set_param(NULL,"xpack_path",xpack_path_.c_str(),0);
	KSG_File_Handle handle = KSG_begin_request();
	if(handle == NULL)
	{
		return -1;
	}
	KSG_set_param(handle,"upload",is_upload_.c_str(),0);
	KSG_set_param(handle,"src_filename",src_file_.c_str(),0);
	KSG_set_param(handle,"dest_filename",dest_file_.c_str(),0);
	ret = KSG_send_request(handle);
	KSG_free_request(handle);
	KSG_uninit();
	if(!ret)
		cout<<"Success transfer file"<<endl;
	else
		cout<<"Failed transfer file : "<<KSG_get_errmsg()<<endl;
	return ret;
}

int main(int argc,char * const argv[])
{
	KSFileTrans trans;
	trans.process(argc,argv);
	return 0;
}

