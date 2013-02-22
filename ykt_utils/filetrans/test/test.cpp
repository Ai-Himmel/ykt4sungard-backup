// test.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../filetrans.h"
#pragma comment(lib ,"..\\bin\\filetrans.lib")

static int g_index;
void APIDEF mycallback(int total_len,int pack_len)
{
	printf("pack index[%d][%d]length[%d]\n",++g_index,total_len,pack_len);
}
int main(int argc, char* argv[])
{
	int ret;
	char upload[2]="0";
	char source_file[1024] = "";
	KSG_init("10.253.42.200",4000,100);
	KSG_File_Handle handle = KSG_begin_request();
	if(handle == NULL)
	{
		printf("����ʧ��!\n");
		exit(1);
	}
	if(argc>1)
	{
		strcpy(source_file,argv[1]);
	}
	else
	{
		//strcpy(source_file,"full.lst");
		if(upload[0] == '0')
			strcpy(source_file,"libbccsvr.a");
		else
			strcpy(source_file,"c:\\KSManageSys.Log");
	}
	//KSG_set_param(handle,"src_filename","/home/yktsj/ykt/bin/ksmbcc",0);
	//KSG_set_param(handle,"dest_filename","d:\\ksmbcc",0);
	KSG_set_param(handle,"upload",upload,0);
	printf("�ļ�[%s]\n",source_file);
	KSG_set_param(handle,"src_filename",source_file,0);
	KSG_set_param(handle,"dest_filename",source_file,0);
	KSG_set_param(handle,"callback",(const void*)mycallback,0);
	g_index = 0;
	ret = KSG_send_request(handle);
	if(ret)
	{
		printf("�����ļ�ʧ��,ret[%d]\n",ret);
	}
	else
		printf("�����ļ��ɹ�\n");
	KSG_free_request(handle);
	KSG_uninit();
	system("pause");
	return 0;
}

