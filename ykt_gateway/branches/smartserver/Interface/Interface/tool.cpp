#include "stdafx.h"
#include "tool.h"

/*=================================================================
Copyright (C) 2002 - 2004 广东三九智慧电子信息产业有限公司
File name:    tool.cpp
Author:       DengJun
Version:      1.0
Date:         2005.03.12
Description:  相关字符串处理的类
Others:       
Revision history:	
	Date:
	Author:
	Modifiacation:	
=================================================================*/

/*=================================================================
 * Function ID :  Tool
 * Input       :  void
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  void
 * Description :  构造函数
 * Notice	   :  
 *					
 *=================================================================*/
Tool::Tool()
{

}

/*=================================================================
 * Function ID :  ~Tool
 * Input       :  void
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  void
 * Description :  析构函数
 * Notice	   :  
 *					
 *=================================================================*/
Tool::~Tool()
{
}
/*=================================================================
 * Function ID :  HexToInt
 * Input       :  int data
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  返回转换成的10进制数
 * Description :  将一个16进制的数换成整数形式
 * Notice	   :  由于整数的长度为4字节，故16进制的数只能少于或等4字节
 *					
 *=================================================================*/
unsigned int Tool::HexToInt(uchar* HexData, int len)
{
	static unsigned int data=0;
	data = 0;
	
	if( len > 4 || len == 0  ) return data;
	if( len ==1 )
	{
		data = *HexData&0xF0+*HexData&0x0F;
	}
	else if( len == 2 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	else if( len == 3 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	else if( len == 4 )
	{
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16*16*16;
		HexData++;
		data+= ((*HexData>>4)*16+(*HexData&0x0F))*16*16;
		HexData++;
		data+= (*HexData>>4)*16+(*HexData&0x0F);
	}
	return data;
}


/*=================================================================
 * Function ID :  AscToBcd
 * Input       :  uchar* ascbuf, int ascbuf_len
 * Output      :  uchar* bcdbuf
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  返回转换的字符BCD
 * Description :  将ASC码转换成BCD码
 * Notice	   :  如"11223344aaBB"  > "\x11\x22\x33\x44\xAA\xBB"
 *					
 *=================================================================*/
uchar* Tool::AscToBcd(uchar* ascbuf, int ascbuf_len, uchar* bcdbuf)
{
	uchar	str[2048];	
	uchar	buf[2048];	
	uchar	mid=0,ch=0;
	int		i=0,j=0,asc=0;

	memset(buf, 0x00, sizeof buf );
	memset(str, 0x00, sizeof str );	

	if( ascbuf_len == 0 ) return NULL;
	if( ascbuf_len%2 == 1 )
	{
		ascbuf_len++;	
		str[0]='0';
		memcpy( str+1, ascbuf, ascbuf_len );
	}
	else
	{
		memcpy( str, ascbuf, ascbuf_len );
	}

	for(i=1; i<ascbuf_len+1; i++)
	{
		if( str[asc]>='a' )
		{
			ch=((str[asc]-'a')+10);
		}
		else if( str[asc]>='A')
		{
			ch=((str[asc]-'A')+10);
		}
		else if( str[asc] >='0' )
		{
			ch=str[asc]-'0';
		}
		else
			ch = 0;
		if( i%2 == 1 )
		{
			ch=ch<<4;
			mid = ch;
		}
		else
		{			
			buf[j]=mid+ch;			
			j++;
		}	
		asc++;
	}
	memcpy((char*)bcdbuf,(char*)buf,(ascbuf_len+1)/2);
	
	return bcdbuf;
}

/*=================================================================
 * Function ID :  BcdToAsc
 * Input       :  uchar* bcdbuf, int bcdbuf_len
 * Output      :  uchar* ascbuf
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  返回转换的字符
 * Description :  将BCD码转换成ASC码
 * Notice	   :  如 "\x11\x22\x33\x44\xAA\xBB" > "11223344AABB"   
 *					
 *=================================================================*/
uchar* Tool::BcdToAsc(uchar* bcdbuf, int bcdbuf_len,uchar* ascbuf )
{
	uchar	ch =0;
	uchar	mid=0;
	uchar	ascstr[1024];
	int		i=0,j=0,k=0;

	memset(ascstr, 0x00, sizeof ascstr );

	if( bcdbuf_len <= 0 ) return NULL;

	for(i=0; i<bcdbuf_len; i++)
	{
		ch  = *bcdbuf>>4;
		mid = *bcdbuf&0x0F;
		if( ch >9 )		ch+=55;
		else			ch+='0';
		ascstr[j]=ch;
		j++;
		if( mid > 9 )	mid+=55;
		else			mid+='0';
		ascstr[j]=mid;
		j++;			
		bcdbuf++;
	}
	memcpy((char*)ascbuf,(char*)ascstr,(2*bcdbuf_len));
	return ascbuf;
}

/*=================================================================
 * Function ID :  IntToHex
 * Input       :  int data
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  返回转换成的16进制数
 * Description :  将一个整数转换成4字节的16进制
 * Notice	   :  
 *					
 *=================================================================*/
uchar* Tool::IntToHex(unsigned int data)
{
	static uchar buf[5];
	int		ret;
	uchar	*p=NULL;

	ret = data;
	memset(buf, 0x00, sizeof buf );

	p=(uchar*)&ret;
	buf[3]=*(p+0);
	buf[2]=*(p+1);
	buf[1]=*(p+2);
	buf[0]=*(p+3);	
	return buf;
}
/*=================================================================
 * Function ID :  l_trim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串左边的空格
 *					
 *=================================================================*/
char* Tool::ltrim(char* str)
{
	char buf[2048];
	int  i=0;
	int	 len=0;

	memset(buf, 0x00, sizeof buf );
	strcpy(buf, str);	
	memset(str, 0x00, sizeof str );
	len = strlen(buf);
	for(i=0; i<len; i++)
	{
		if( buf[i] !=' ')
			break;		
	}
	memcpy(str,buf+i,len-i);
	return str;
}

/*=================================================================
 * Function ID :  rtrim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串右边的空格
 *					
 *=================================================================*/
char* Tool::rtrim(char* str)
{
	int	 len;	
	len = strlen(str)-1;
	while(len)
	{
		if(str[len]!=' ')
			break;
		len--;
	}
	str[len+1]=0x00;
	return str;
}

/*=================================================================
 * Function ID :  trim
 * Input       :  char* str
 * Output      :  char* str
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  去掉字符串左右两边的空格
 *					
 *=================================================================*/
char* Tool::trim(char* str)
{
	rtrim(str);
	ltrim(str);
	return str;
}


/*=================================================================
 * Function ID :  HeadAddStr
 * Input       :  char* str,int num, char type
 * Output      :  char* str
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  在字符串前面增加num个type字符
 *					
 *=================================================================*/
char* Tool::HeadAddStr(char* str, int num, char type)
{
	char buf[2048];
	int len=0;

	memset(buf, 0x00, sizeof buf );

	len = strlen(str);
	for(int i=0; i<num; i++)
	{
		buf[i]=type;
	}
	memcpy(buf+num,str,len);
	memset(str, 0x00, strlen(str) );
	memcpy(str,buf,len+num);
	return str;
}

/*=================================================================
 * Function ID :  GetSysTime
 * Input       :  void
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  返回本机的时间(格式:YYYYMMDDHHMMSS)
 * Description :  
 * Notice	   :  取本机时间
 *					
 *=================================================================*/
uchar* Tool::GetSysTime()
{
	time_t 		 timebuf;
	struct tm    *tmptr=NULL;
	static uchar buf[20];

	memset(buf, 0x00, sizeof buf );

	timebuf = time((time_t *) 0);
	tmptr   = localtime(&timebuf);		
	sprintf( (char*)buf, "%.4d%.2d%.2d%.2d%.2d%.2d",
			 tmptr->tm_year+1900, tmptr->tm_mon+1, tmptr->tm_mday,
			 tmptr->tm_hour, tmptr->tm_min,tmptr->tm_sec	
		   );
	return buf;
}


/*=================================================================
 * Function ID :  CheckStrHex
 * Input       :  char* str
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  检查输入的字符串是否为HEX字符
 * Notice	   :  0~9和A(a)~F(f)
 *					
 *=================================================================*/
bool Tool::CheckStrHex(char* str )
{
	int len=0,i=0;

	len = strlen( str );
	for( i=0; i<len; i++)
	{
		switch( *(str++) )
		{
			case '0' :
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
			case '8' :
			case '9' :
			case 'a' :
			case 'b' :
			case 'c' :
			case 'd' :
			case 'e' :
			case 'f' :
			case 'A' :
			case 'B' :
			case 'C' :
			case 'D' :
			case 'E' :
			case 'F' :
				break;
			default:
				return false;
		}
	}
	return true;
}
/*=================================================================
 * Function ID :  AddLineToFile
 * Input       :  
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  
 *					
 *=================================================================*/
void Tool::AddLineToFile( char* buf, int buf_len )
{
	int     len=0;
	int		ret=0;	
	char	*ptr=NULL;
	
	if( buf_len <=0 )
	{
		return ;
	}
	FILE* p=NULL;
	if( (p=fopen("TestData.txt","a")) == NULL )
	{
		return ;
	}
	len=buf_len+19;
	ptr = (char*)malloc(len);
	if( ptr == NULL )
	{
		return ;
	}
	
	memset(ptr, 0x00, len );
	memcpy(ptr,(char*)GetSysTime(),14);
	strcat(ptr,"  ");
	strcat(ptr,buf);
	ptr[len-1]='\n';	
	len=fwrite(ptr,1,len,p);	
	fclose(p);		
	free(ptr);
	ptr = NULL;
	return ;
}

/*=================================================================
 * Function ID :  AddLineToFile
 * Input       :  
 * Output      :  void
 * Author      :  DengJun
 * Date        :  Mar  01  2005
 * Return	   :  str
 * Description :  
 * Notice	   :  
 *					
 *=================================================================*/
void Tool::AddLineToFile( char *lpfilename,char* buf, int buf_len )
{
	int     len=0;
	int		ret=0;	
	char	*ptr=NULL;
	char    filename[30];
	char    cpath[256];

	memset(cpath,0x00,sizeof cpath);
	memset(filename,0x00,sizeof filename);
	if( buf_len <=0 )
	{
		return ;
	}
	GetCurPath(cpath);
	strcat(cpath,"\\Black");
	CreateDirectory(cpath,NULL);
	strcat(cpath,"\\");
	strcat(cpath,lpfilename);
	strcat(cpath,".txt");
	FILE* p=NULL;
	if( (p=fopen(cpath,"a")) == NULL )
	{
		Sleep(10);
		if( (p=fopen(cpath,"a")) == NULL )
			return ;
	}
	len=buf_len+19;
	ptr = (char*)malloc(len);
	if( ptr == NULL )
	{
		fclose(p);
		return ;
	}
	
	memset(ptr, 0x00, len );
	memcpy(ptr,(char*)GetSysTime(),14);
	strcat(ptr,"  ");
	strcat(ptr,buf);
	ptr[len-1]='\n';	
	ret=fwrite(ptr,1,len,p);	
	fclose(p);		
	free(ptr);
	ptr = NULL;
	return ;	
}

void Tool::GetCurPath(char* pszDir)
{
	HANDLE  hHandle = GetCurrentProcess();
	GetModuleFileName(NULL, pszDir, MAX_PATH);
	for(int i=lstrlen(pszDir)-1; i>=0 ; i--)
	{
		if( pszDir[i] == '\\' )
		{
			pszDir[i] = 0;
			break;
		}
	}
}
