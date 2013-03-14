// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "../filetrans.h"
#pragma comment(lib ,"..\\bin\\filetrans.lib")

static int g_index;
void __stdcall mycallback(int total_len,int pack_len)
{
	//printf("pack index[%d][%d]length[%d]\n",++g_index,total_len,pack_len);
}
int main(int argc, char* argv[])
{
	int ret;
	KSG_init("10.49.118.250",4000,7100);
	KSG_File_Handle handle = KSG_begin_request();
	if(handle == NULL)
	{
		printf("请求失败!\n");
		exit(1);
	}
	//KSG_set_param(handle,"src_filename","/home/yktsj/ykt/bin/ksmbcc",0);
	//KSG_set_param(handle,"dest_filename","d:\\ksmbcc",0);
	KSG_set_param(handle,"upload","1",0);
	KSG_set_param(handle,"src_filename","d:\\test.txt",0);
	KSG_set_param(handle,"dest_filename","text.txt",0);
	KSG_set_param(handle,"callback",mycallback,0);
	g_index = 0;
	ret = KSG_send_request(handle);
	if(ret)
	{
		printf("下载文件失败,ret[%d]\n",ret);
	}
	else
		printf("下载文件成功\n");
	KSG_free_request(handle);
	KSG_uninit();
	system("pause");
	return 0;
}

