#ifndef __PUB_FUNC_H__
#define __PUB_FUNC_H__

#pragma once

//////////////////////////////////////////////////////////////////////////
// 1.字符串转换类
//////////////////////////////////////////////////////////////////////////
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

int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
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

char *ntrim(char *str,int len)
{
	char *p1 = str;
	char *p2 = NULL;

	if (str == NULL)
		return NULL;
	p2 = str + len - 1;
	*p2=0;
	p2 = str + strlen(str) - 1;
	if(p2<str)
		return str;
	while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
	{
		p1++;
	}
	while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r')
	{
		*p2 = 0;
		p2--;
		if(p2<p1)
			break;
	}
	if(p1!=str)
		strcpy(str, p1);
	return str;
}

//////////////////////////////////////////////////////////////////////////
// 2.目录操作类
//////////////////////////////////////////////////////////////////////////
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

void GetIniFileExt(char *FilePathBuf, const char *PurposeFileBuf)
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
	strncat(pathBuf, PurposeFileBuf, 13);		// PurposeFileBuf == "\\Skin.ini"
	strcpy(FilePathBuf, pathBuf);
}

void GetIniFileFromDll(char *FilePathBuf)
{
	char *cpPose = NULL;
	if (cpPose = strrchr(FilePathBuf, '\\'))
		strcpy(cpPose + 1, "CardDll.ini");
	
	cpPose += sizeof("CardDll.ini") + 1;
	cpPose = '\0';
}

//////////////////////////////////////////////////////////////////////////
//3.数学计算类
//////////////////////////////////////////////////////////////////////////
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