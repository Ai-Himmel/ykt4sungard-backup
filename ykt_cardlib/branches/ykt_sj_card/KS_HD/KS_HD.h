//ʹ��Ԥ����ָ�֤ͷ�ļ�ֻ�ܱ�����һ��
#ifndef __KS_HD_H__
#define __KS_HD_H__

#include <iostream>
#include "LogFile.h"
#pragma once

CLogFile g_log_file("card_log");
#define DEBUG_CARD_MSGOUT(ret, msg) { g_log_file.WriteLogEx(1000, "FILE:%s---LINE:%d---FUNCNAME:%s---RET:%d---MESSAGE:%s", __FILE__, __LINE__, __FUNCTION__, ret, msg); }
//�շ�ϵͳ���Ѽ�¼�ṹ
typedef struct
{
	int nInfoID;               	 //���׿���
	int nMoneyCent;           	 //���׽��(��)
	int nBalance;               //�����, �����Ժ�����(��)
	int nTotalTimes;  		     //�ۼ����Ѵ���
	int nOperatorNum;         	 //����Ա��, ���1��254��ʾ��ͬ�Ĳ���Ա
	int nYear; 				 //������ 2007����
	int nMonth;
	int nDay;                	 //����
	int nHour;
	int nMinute;
	int nSecond;                //ʱ��
	int bNormal;				 //�Ҽ�¼��־����Ϊ"false"����Ϊ"true"
	int bCancel;                //���ʽ����Ƿ���������, �Ƿ�ȡ��, ���ʽ���δȡ��"false"�����ʽ��ױ�����Աȡ��"true"
	int bReload;             	 //���ɱ�־��0�������ɼ���1�����ɼ�
	int nDMAdr;               	 //���ߵ�ַ 0~255
} POSRECORD;

//////////////////////////////////////////////////////////////////////////
// ��ȡָ��Ŀ¼���ļ�
void GetIniFile(char *FilePathBuf)
{
	char pathBuf[512] = "";
	int len = GetModuleFileName(NULL, pathBuf, sizeof(pathBuf));
	if (len <= 0)
	{
		MessageBox(NULL, "Get Path Err!", "", NULL);
		return ;
	}
	char *p = pathBuf + len;
	while (p >= pathBuf)
	{
		if (*p == '\\')
		{
			break;
		}
		p--;
	}
	if (p > pathBuf)
	{
		*p = '\0';
	}

	if (!strnicmp(p - 4, "\\dll", 4))
	{
		p -= 4;
		*p = '\0';
	}

	strncat(pathBuf, "\\CardDll.ini", 13);
	strcpy(FilePathBuf, pathBuf);
}
//////////////////////////////////////////////////////////////////////////
// ͨ����̬��CardDll.dll���ini�ļ�·�� 
void GetIniFileFromDll(char *FilePathBuf)
{
	char *cpPose = NULL;
	if (cpPose = strrchr(FilePathBuf, '\\'))
		strcpy(cpPose + 1, "CardDll.ini");

	cpPose += sizeof("CardDll.ini") + 1;
	cpPose = '\0';
}

int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}

int bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
	int k=0;
	for(i=0;i<dec_len;i++)
	{
		k=sDec[i];
		sprintf(&sHex[2*i],"%02X",k);
	}
}

void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

void hex2dec1(char *sHex, char *sDec)
{
	int hex_length = strlen(sHex);
	int card_id = 0;
	int num = 1;
	hex_length--;
	while (hex_length >= 0)
	{
		if ('A' == sHex[hex_length] ||
			'B' == sHex[hex_length] ||
			'C' == sHex[hex_length] ||
			'D' == sHex[hex_length] ||
			'E' == sHex[hex_length] ||
			'F' == sHex[hex_length]
			)
			{
				card_id += (sHex[hex_length] - 0x37) * num;
			}
		else
		{
			card_id += (sHex[hex_length] - 0x30) * num;
		}		
		
		num *= 16;
		hex_length--;
	}

	sprintf(sDec, "%d", card_id);
}

void round_float(double *f, int bits) 
{
	static const int DECIMAL_BASE = 10;    
	unsigned int n,scale,m;    
	int i;
	scale = 1;
	for (i = 0; i < bits + 1;  i++)
	{
		scale *= DECIMAL_BASE;
	}

	n = (*f) * scale;
	//	n += 5;
	m = n % 10;

	if (m < 5)
		n = n - m;
	else
		n = n - m + 10;    

	*f = ((double)n / scale);
}

#endif
