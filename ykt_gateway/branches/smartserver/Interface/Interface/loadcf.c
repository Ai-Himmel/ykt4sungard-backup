
/* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include "loadcf.h"


/* ------------------------------------------------------------------------- */
/* 引用的变量：
   hConfig:		需要在主程序定义，主程序打开
   bQuietFlag:	需要在主程序定义，TRUE,则不显示配置资料，FALSE显示
   fConfig:		需要在主程序定义，配置文件名
   bCreateFlag:	需要在主程序定义，如果遇到找不到的项目，是否创建之
*/

FILE	*	hConfig = NULL;
BOOL		bQuietFlag = FALSE;
char		fConfig[80];
BOOL		bCreateFlag = FALSE;
/* ------------------------------------------------------------------------- */
/* 静态定义的变量
   LineCount: 行号
   curPos: 当前位置
   strText: 使用的字符串
*/
static int   LineCount = 0;
static long  curPos;
static char  strText[3096];
/* ------------------------------------------------------------------------- */


/*
  CF_GetCurPos:

*/
long CF_GetCurPos(char *pReadBuffer)
{
	long Pos;

	fseek(hConfig,0L,SEEK_CUR);
	Pos=ftell(hConfig);
	while(CF_GetLine(pReadBuffer)==0)
	{
		if (CF_InString(pReadBuffer,"["))
			return Pos;
		else
			Pos=ftell(hConfig);
	}
	return Pos;
}

/*
	CF_GetLine:
		取得一行
*/
int  CF_GetLine(char *pReadBuffer)
{
	char *pReadPointer;

    do {
		pReadPointer=fgets(pReadBuffer,2549,hConfig);
		LineCount ++;
		if((pReadPointer==NULL)||(strlen(pReadBuffer)>=2200))
			return -1;

		/*strupr(pReadBuffer);*/
		CF_FilterChar(pReadBuffer,pReadBuffer,' ');
		CF_FilterChar(pReadBuffer,pReadBuffer,'\t');
		CF_FilterChar(pReadBuffer,pReadBuffer,'\n');
		CF_FilterChar(pReadBuffer,pReadBuffer,'\r');
		CF_FilterChar(pReadBuffer,pReadBuffer,'=');
	} while (pReadBuffer[0] ==';'|| pReadBuffer[0] == 0);
	return 0;
}
/*
	CF_FilterChar:
		过滤字符
*/
void CF_FilterChar(char *pInBuffer,char *pOutBuffer,char cSkip)
{
	while (*pInBuffer!='\0')
	{
		if (*pInBuffer==';')
			*pInBuffer='\0';   /* 允许注释 */
		if (*pInBuffer!=cSkip)
			*pOutBuffer++=*pInBuffer++;
		else
			pInBuffer++;
	}
	*pOutBuffer='\0';
}
/*
	CF_InString:
		判断是否在字符串中
*/
int CF_InString(char *pBuffer,char *pShortBuffer)
{
	while (*pShortBuffer!='\0')
	{
		if (toupper(*pBuffer)==toupper(*pShortBuffer))
		{
			pBuffer++;
			pShortBuffer++;
		}
		else
			return 0;
	}
	return 1;
}

/*
	CF_GetConfigString:
	取得配置的字符串
*/
char *CF_GetConfigString(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice)
{
L_RELOAD:
	CF_LocateGroupName(pReadBuffer,pGroupName);
	while ( CF_GetLine( pReadBuffer) ==0 )
	{
		if (CF_InString(pReadBuffer,"[") )
			goto L_CNT;
		if (CF_InString(pReadBuffer,pCommandString))
		{
			if (bQuietFlag == FALSE)
				printf("%s[%s][%s]\r\n",pGroupName,pCommandString,pReadBuffer+strlen(pCommandString));
			return pReadBuffer+strlen(pCommandString);
		}
	}
L_CNT:
	CF_LocateGroupName(pReadBuffer,pGroupName);
	sprintf(strText,"%s=%s\r\n",pCommandString,notice);
	curPos = CF_GetCurPos(pReadBuffer);
	fclose(hConfig);

	if(bCreateFlag == FALSE)
		CF_ShowError(pReadBuffer,pCommandString);

	CF_AddConfig(fConfig,strText,curPos);
	hConfig=fopen(fConfig,"rb");
	if(hConfig==NULL)
		CF_ShowError(pReadBuffer,pCommandString);
	goto L_RELOAD;
}

/*
	CF_LocateGroupName:
	定位组节名字
*/
int CF_LocateGroupName(char *pReadBuffer,char *pGroupName)
{
L_RELOAD:
	fseek(hConfig,0L,SEEK_SET);
	while ( CF_GetLine(pReadBuffer) ==0 )
	{
		if (CF_InString(pReadBuffer,pGroupName))
			return 0;
	}
	fclose(hConfig);

	if(bCreateFlag == FALSE)
		CF_ShowError(pReadBuffer,pGroupName);

	CF_AddConfigGroup(fConfig,pGroupName);
	hConfig=fopen(fConfig,"rb");
	if(hConfig==NULL)
		CF_ShowError(pReadBuffer,pGroupName);
	goto L_RELOAD;
}
/*
	CF_ShowError:
		显示错误信息
*/
void  CF_ShowError(char *pReadBuffer,char *pCommandString)
{
	printf(" Can not find keyword :");
	printf(pCommandString);
	printf("\r\n");
	printf(" please use main /C to auto add this Config !!\r\n");
	exit(1);
}
/*
	CF_AddConfig:
		增加配置项目
*/
void CF_AddConfig(char *filename,char *str,long pos)
{
	FILE *f1;
	FILE *f2;
	char buf[4096];
	int cntPerRead=4000;
	long cnt,cntRead;
	int len;

	if (CF_CopyFile(filename,"CONFIG.___"))
		return ;

	f1=fopen("CONFIG.___","rb");
	unlink(filename);
	f2=fopen(filename,"wb");
	if (f1==NULL || f2==NULL)
	{
		if (f1!=NULL)
			fclose(f1);
		if (f2!=NULL)
			fclose(f2);
		return ;
	}
	cntRead=0;
	if (pos<4000)
		cntPerRead=pos;
	if (pos==0)
		goto L_CNT;

	cnt=fread(buf,1,cntPerRead,f1);
	cntRead+=cnt;
	fwrite(buf,1,cnt,f2);
	while (cntRead<pos)
	{
		if (cntPerRead+cntRead>pos)
			cntPerRead=pos-cntRead;
		cnt=fread(buf,1,cntPerRead,f1);
		cntRead+=cnt;
		fwrite(buf,1,cnt,f2);
	}
L_CNT:
	len=strlen(str);
	fwrite(str,1,len,f2);
	cntPerRead=4000;
	cnt=fread(buf,1,cntPerRead,f1);
	while (cnt>0)
	{
		fwrite(buf,1,cnt,f2);
		cnt=fread(buf,1,cntPerRead,f1);
	}
	fclose(f1);
	fclose(f2);
	unlink("CONFIG.___");
	return;
}
/*
	CF_AddConfigGroup:
		增加配置组
*/
void CF_AddConfigGroup(char *filename,char *str)
{
	FILE *f1;
	FILE *f2;
	char buf[4096];
	int cntPerRead=4000;
	long cnt;
	int len;

	if (CF_CopyFile(filename,"CONFIG.___"))
		return ;

	f1=fopen("CONFIG.___","rb");
	unlink(filename);
	f2=fopen(filename,"wb");
	if (f1==NULL || f2==NULL)
	{
		if (f1!=NULL)
			fclose(f1);
		if (f2!=NULL)
			fclose(f2);
		return ;
	}
	sprintf(buf,"%s\r\n",str);
	len=strlen(buf);
	fwrite(buf,1,len,f2);
	cntPerRead=4000;
	cnt=fread(buf,1,cntPerRead,f1);
	while (cnt>0)
	{
		fwrite(buf,1,cnt,f2);
		cnt=fread(buf,1,cntPerRead,f1);
	}
	fclose(f1);
	fclose(f2);
	unlink("CONFIG.___");
	return;
}
/*
	CF_CopyFile:
		拷贝文件
*/
int CF_CopyFile(char *src,char *dst)
{
	FILE *f1;
	FILE *f2;
	char buf[2550];
	long cnt;

	f1=fopen(src,"rb");
	f2=fopen(dst,"wb");
	if (f1==NULL || f2==NULL)
	{
		if (f1!=NULL)
			fclose(f1);
		if (f2!=NULL)
			fclose(f2);
		return -1;
	}
	cnt=fread(buf,1,2550,f1);
	while (cnt>0)
	{
		fwrite(buf,1,cnt,f2);
		cnt=fread(buf,1,2550,f1);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
#ifdef __RS6000__
int unlink(char *filename)
{
	remove(filename);
}
#endif
/*
	CF_GetConfigDigit:
		取得配置整数
*/
int CF_GetConfigDigit(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice)
{
L_RELOAD:
	CF_LocateGroupName(pReadBuffer,pGroupName);
	while ( CF_GetLine( pReadBuffer) == 0 )
	{
		if (CF_InString(pReadBuffer,"["))
			goto L_CNT;
		if (CF_InString(pReadBuffer,pCommandString))
		{
			if (bQuietFlag == FALSE)
				printf("%s[%s][%d]\r\n",pGroupName,pCommandString,atoi(pReadBuffer+strlen(pCommandString)));
			return atoi(pReadBuffer+strlen(pCommandString));
		}
	}
L_CNT:
	CF_LocateGroupName(pReadBuffer,pGroupName);
	sprintf(strText,"%s=%s\r\n",pCommandString,notice);
	curPos = CF_GetCurPos(pReadBuffer);
	fclose(hConfig);

	if(bCreateFlag == FALSE)
		CF_ShowError(pReadBuffer,pCommandString);

	CF_AddConfig(fConfig,strText,curPos);
	hConfig=fopen(fConfig,"rb");
	if(hConfig==NULL)
		CF_ShowError(pReadBuffer,pCommandString);
	goto L_RELOAD;
}
/*
	CF_GetConfigDouble:
		取得配置浮点数
*/
double CF_GetConfigDouble(char *pReadBuffer,char *pGroupName,char *pCommandString,char *notice)
{
L_RELOAD:
	CF_LocateGroupName(pReadBuffer,pGroupName);
    while ( CF_GetLine( pReadBuffer) == 0 )
	{
		if (CF_InString(pReadBuffer,"["))
			goto L_CNT;
		if (CF_InString(pReadBuffer,pCommandString))
		{
			if (bQuietFlag == FALSE)
				printf("%s[%s][%4.3f]\r\n",pGroupName,pCommandString,atof(pReadBuffer+strlen(pCommandString)));
			return atof(pReadBuffer+strlen(pCommandString));
		}
	}
L_CNT:
	CF_LocateGroupName(pReadBuffer,pGroupName);
	sprintf(strText,"%s=%s\r\n",pCommandString,notice);
	curPos = CF_GetCurPos(pReadBuffer);
	fclose(hConfig);

	if(bCreateFlag == FALSE)
		CF_ShowError(pReadBuffer,pCommandString);

	CF_AddConfig(fConfig,strText,curPos);
	hConfig=fopen(fConfig,"rb");
	if(hConfig==NULL)
		CF_ShowError(pReadBuffer,pCommandString);
	goto L_RELOAD;
}

/*
	CF_SetQuietMode:
		设置安静模式
*/
BOOL CF_SetQuietMode(BOOL bNewMode)
{
	BOOL bRet;

	bRet = bQuietFlag;
	bQuietFlag = bNewMode;
	return bRet;
}
/*
	CF_SetCreateMode:
		设置是否自动补配置
*/
BOOL CF_SetCreateMode(BOOL bNewMode)
{
	BOOL bRet;

	bRet = bCreateFlag;
	bCreateFlag = bNewMode;
	return bRet;
}
/*
	CF_OpenConfig:
		打开配置文件
*/
BOOL CF_OpenConfig(char *filename)
{
	if ( hConfig != NULL)
	{
		printf("上次打开的配置文件没有关闭!");
		return FALSE;
	}
	hConfig = fopen(filename,"rb");
	if (hConfig == NULL)
	{
		printf("loadcf:不能打开配置文件[%s]\n",filename);
		return FALSE;
	}
	strcpy(fConfig,filename);
	return TRUE;
}
/*
	CF_CloseConfig:
		关闭配置文件
*/
BOOL CF_CloseConfig(void)
{
	if (hConfig == NULL)
		return TRUE;
	fclose(hConfig);
	hConfig=NULL;
	return TRUE;
}
/*
	trim
		压缩空格
*/

void trim(char *s)
{
	int i,len;

	len=strlen(s);
	for(i=len-1;i>=0;i--)
	{
		if(s[i]!=' ')
			break;
		else
			s[i]=0;
	}
	for(i=0;i<len;i++)
	{
		if(s[i]!=' ')
			break;
	}
	if(i!=0)
	{
		strncpy(s,s+i,len-i);
		s[len-i]=0;
	}
}


