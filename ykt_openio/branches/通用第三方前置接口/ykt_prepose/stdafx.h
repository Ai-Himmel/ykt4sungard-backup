// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>
#include <list>
#include <fstream>
#include   <time.h> 
#include <curl.h>
//define	  ALDDK  1			//�����µ��
//#define	  YUNZZSJSW  1		 //�ƽ�ְ�ϻ�����
#define	  ANGDSJSW  1		//�������ϻ�����
//#define AGDCGDK 1				 //�����󳤹����

#pragma comment(lib, "WS2_32")
#pragma warning(disable: 4786)
using namespace std;
#ifndef FAIL
#define	  FAIL  -1
#endif

#ifndef SUCCESS
#define   SUCCESS 0
#endif
extern char	g_sCommRec[256];
extern  CRITICAL_SECTION g_cs;//
extern char remotehost[21];
extern curl_slist* headerlist;
extern  int port;
extern  int remoteport;
extern void WriteLog(char* msg);
extern void Readdata(char* filename,char* msg);
extern void Writedata(char* filename,char* msg);
extern void Deledata( char* filename);
extern char * sendnetpay(char *sendstr);
extern char httppath[256];
extern char localip[256];
extern char runpath[256];
extern char Connectstr[512];
extern char school[200];
extern bool diabwork;
extern int connsqlsign;
extern int exnum;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") 
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
//extern _ConnectionPtr m_pConnection;
//extern _RecordsetPtr pPtr;
int makestr(char *type,char *data,char *rtdata);
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);
void CalcMD5(unsigned char* buf,unsigned int len,unsigned char md5[16]);
char * trim(char * ptr);
char *getnextstr(char *s, const char *delim,char *rtstr );
 void reverse_str(char *ch);
 void WriteLog( char* msg);
void Writedata( char* filename, char* msg);
 int file2memory(char **bufp, size_t *size, FILE *file);
 char * addrightsqace(char * ptr,int len);
 char * addleftzero(char * ptr,int len);