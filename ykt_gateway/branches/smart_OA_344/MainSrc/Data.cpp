
#include "stdafx.h"
#include "Data.h"


unsigned int crctab[256]=
{
 0x0000,0x1021,0x2042,0x3063,0x4084,0x50A5,0x60C6,0x70E7,
 0x8108,0x9129,0xA14A,0xB16B,0xC18C,0xD1AD,0xE1CE,0xF1EF,
 0x1231,0x0210,0x3273,0x2252,0x52B5,0x4294,0x72F7,0x62D6,
 0x9339,0x8318,0xB37B,0xA35A,0xD3BD,0xC39C,0xF3FF,0xE3DE,
 0x2462,0x3443,0x0420,0x1401,0x64E6,0x74C7,0x44A4,0x5485,
 0xA56A,0xB54B,0x8528,0x9509,0xE5EE,0xF5CF,0xC5AC,0xD58D,
 0x3653,0x2672,0x1611,0x0630,0x76D7,0x66F6,0x5695,0x46B4,
 0xB75B,0xA77A,0x9719,0x8738,0xF7DF,0xE7FE,0xD79D,0xC7BC,
 0x48C4,0x58E5,0x6886,0x78A7,0x0840,0x1861,0x2802,0x3823,
 0xC9CC,0xD9ED,0xE98E,0xF9AF,0x8948,0x9969,0xA90A,0xB92B,
 0x5AF5,0x4AD4,0x7AB7,0x6A96,0x1A71,0x0A50,0x3A33,0x2A12,
 0xDBFD,0xCBDC,0xFBBF,0xEB9E,0x9B79,0x8B58,0xBB3B,0xAB1A,
 0x6CA6,0x7C87,0x4CE4,0x5CC5,0x2C22,0x3C03,0x0C60,0x1C41,
 0xEDAE,0xFD8F,0xCDEC,0xDDCD,0xAD2A,0xBD0B,0x8D68,0x9D49,
 0x7E97,0x6EB6,0x5ED5,0x4EF4,0x3E13,0x2E32,0x1E51,0x0E70,
 0xFF9F,0xEFBE,0xDFDD,0xCFFC,0xBF1B,0xAF3A,0x9F59,0x8F78,
 0x9188,0x81A9,0xB1CA,0xA1EB,0xD10C,0xC12D,0xF14E,0xE16F,
 0x1080,0x00A1,0x30C2,0x20E3,0x5004,0x4025,0x7046,0x6067,
 0x83B9,0x9398,0xA3FB,0xB3DA,0xC33D,0xD31C,0xE37F,0xF35E,
 0x02B1,0x1290,0x22F3,0x32D2,0x4235,0x5214,0x6277,0x7256,
 0xB5EA,0xA5CB,0x95A8,0x8589,0xF56E,0xE54F,0xD52C,0xC50D,
 0x34E2,0x24C3,0x14A0,0x0481,0x7466,0x6447,0x5424,0x4405,
 0xA7DB,0xB7FA,0x8799,0x97B8,0xE75F,0xF77E,0xC71D,0xD73C,
 0x26D3,0x36F2,0x0691,0x16B0,0x6657,0x7676,0x4615,0x5634,
 0xD94C,0xC96D,0xF90E,0xE92F,0x99C8,0x89E9,0xB98A,0xA9AB,
 0x5844,0x4865,0x7806,0x6827,0x18C0,0x08E1,0x3882,0x28A3,
 0xCB7D,0xDB5C,0xEB3F,0xFB1E,0x8BF9,0x9BD8,0xABBB,0xBB9A,
 0x4A75,0x5A54,0x6A37,0x7A16,0x0AF1,0x1AD0,0x2AB3,0x3A92,
 0xFD2E,0xED0F,0xDD6C,0xCD4D,0xBDAA,0xAD8B,0x9DE8,0x8DC9,
 0x7C26,0x6C07,0x5C64,0x4C45,0x3CA2,0x2C83,0x1CE0,0x0CC1,
 0xEF1F,0xFF3E,0xCF5D,0xDF7C,0xAF9B,0xBFBA,0x8FD9,0x9FF8,
 0x6E17,0x7E36,0x4E55,0x5E74,0x2E93,0x3EB2,0x0ED1,0x1EF0
}; 
void crcupdata(unsigned char in,unsigned short *accum,unsigned int *crctab)
{
	*accum=(*accum<<8)^crctab[(*accum>>8)^in];
}

CData::CData()
{

	memset(m_clock,0,sizeof m_clock);
}

CData::~CData()
{

}
//计算时, len为传入长度，in为传入数据,out[0],out[1]为计算出的两字节结果
//验证时，将两位CRC也记入,返回0表示CRC正确,返回非零表示不对
int CData::CRC_CCITT(unsigned char len, unsigned char *in, BYTE *out)
{
	unsigned char i;
	unsigned short crc;	
	int stat;
	stat=0;
	crc=0xc78c;
	for(i=0;i<len;in++,i++)
	{
		crcupdata(*in,&crc,crctab);
	}	
    out[0]=(unsigned char)(crc>>8);
	out[1]=(unsigned char)crc;
	if(crc)
	stat=1;
	return(stat);
}
/***************************************************************************
  SUPPOSE dsp CONTAINS THE ASSCII ARRAY "12345F" AND WE EXECUTE THIS FUNCTION
  THEN THE ARRAY  AT hex WILL CONTAIN 12H,34H, 5FH
****************************************************************************/

void CData::SVC_DSP_2_HEX(unsigned char *dsp, unsigned char *hex, int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		hex[i]=((dsp[i*2]<=0x39)?dsp[i*2]-0x30:dsp[i*2]-0x41+10);
		hex[i]=hex[i]<<4;
		hex[i]+=(((dsp[i*2+1]<=0x39)?dsp[i*2+1]-0x30:dsp[i*2+1]-0x41+10)&0x0f);
	}
}
/**************************************************************************
 SUPPOSE HEX CONTAINS THREE BYTES:12H 34H, 5FH AND WE EXECUTE THIS FUNCTION
 THEN dsp WILL CONTAIN ASCII BYTES "12345F"(Input:hex,count;Ouput:dsp)
	Hex->ASC
 **************************************************************************/

void CData::SVC_HEX_2_DSP(unsigned char *hex, unsigned char *dsp, int count)
{
	int i;
	char ch;
	for(i=0;i<count;i++)
	{
		ch=(hex[i]&0xf0)>>4;
		dsp[i*2]=(ch>9)?ch+0x41-10:ch+0x30;
		ch=hex[i]&0x0f;
		dsp[i*2+1]=(ch>9)?ch+0x41-10:ch+0x30;
	}
}


//打包命令
int CData::PackData(int Addr, int Port, unsigned char *Buffer, int Len)
{
	unsigned char Crc1,Crc2,Out[10];
	int ReLen;
	unsigned char buffer1[512];	

	memset(buffer1,0x00,sizeof buffer1);
	buffer1[0] = STX1;
	buffer1[1] = (unsigned char)Addr;
	buffer1[2] = 0;       //包打包
	buffer1[3] = (unsigned char)Len+1;
	buffer1[4] = (unsigned char)Port;
	ReLen=Len+5;
	if(Len>0)
	   memcpy(buffer1+5,Buffer,Len);	

    if(!CRC_CCITT(ReLen,buffer1,Out)) 
    {
	    Crc1 = 0;
	    Crc2 = 0;
	}
	else 
	{
	    Crc1 = Out[0];
	    Crc2 = Out[1];
	}

	buffer1[ReLen] = Crc1;
	ReLen++;
	buffer1[ReLen] = Crc2;
	ReLen++;

	buffer1[ReLen] = ETX1;
	ReLen++;
	if(ReLen>0)
	{
        memcpy(Buffer,buffer1,ReLen);
	}	
	return(ReLen);
}
// 生成通信数据
//MacNum---机号(0-255)
//Flag ----是否使用授权号(0--不使用 非0--使用)
//CommByte--命令字 (0-255)
//InDataLen--传入数据长度
//InData----传入数据
//OutData---传出数据
//Level ----服务器级数 0--无服务器，终端与PC直接相连
                      //1--服务器与PC相连，终端与服务器某口线相连
//Level_Array---服务器级联参数
//Return  传出数据长度
int CData::BuildData(unsigned char MacNum, int Flag, unsigned char *commision,unsigned char CommByte, int InDataLen, unsigned char *InData, unsigned char *OutData,int Level,unsigned char *Level_Array)
{
	int i,Slen,j,CommsionLen=0;
	int	iPP1,iPP2;
	unsigned char Crc1,Crc2,sourcebuffer[512],Out[10];
	
	memset(sourcebuffer,0x00,sizeof sourcebuffer);
	sourcebuffer[0]=STX1;
	sourcebuffer[1]=MacNum;
	sourcebuffer[2]=CommByte;
	sourcebuffer[3]=(unsigned char)InDataLen; 
	Slen = 4;

	if(Flag)
	{
		sourcebuffer[3] += 4;
		memcpy(sourcebuffer+4,commision,4);
		Slen = Slen+4;
	}	

	if(InDataLen!=0)
	{
		memcpy(sourcebuffer+Slen,&InData[0],InDataLen);
		Slen = Slen + InDataLen;
	}
	
	if(!CRC_CCITT(Slen,sourcebuffer,Out)) 
    {
	    Crc1 = 0;
	    Crc2 = 0;
	}
	else 
	{
	    Crc1 = Out[0];
	    Crc2 = Out[1];
	}
	
	sourcebuffer[Slen]=Crc1;
	Slen++;
	sourcebuffer[Slen]=Crc2;
    Slen++;
	sourcebuffer[Slen]=ETX1;
	Slen++;

	j=Level*2;
    while(j>0)
	{
		iPP1=(int)Level_Array[j-2];
		iPP2=(int)Level_Array[j-1];
		i=PackData(iPP1,iPP2,sourcebuffer,Slen);
		Slen=i;

		j-=2;
	}
	
	memcpy(OutData,sourcebuffer,Slen);
	return(Slen);
}


BYTE* CData::AscToBcd(BYTE* ascbuf, int ascbuf_len, BYTE* bcdbuf)
{
	BYTE	str[2048];	
	BYTE	buf[2048];	
	BYTE	mid=0,ch=0;
	int		i=0,j=0,asc=0;

	memset(buf, 0x00, sizeof buf );
	memset(str, 0x00, sizeof str );	

	if( ascbuf_len == 0 || ascbuf_len > 2048 )
	{
		return NULL;
	}

	if( ascbuf_len%2 )
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

BYTE* CData::BcdToAsc(BYTE* bcdbuf, int bcdbuf_len,BYTE* ascbuf )
{
	BYTE	ch =0;
	BYTE	mid=0;
	BYTE	ascstr[1024];
	int		i=0,j=0,k=0;

	memset(ascstr, 0x00, sizeof ascstr );

	if( bcdbuf_len == 0 )
	{
		return NULL;
	}

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

char* CData::IntToHex(int data, char* buf)
{	
	int		ret;
	char	*p=NULL;

	ret = data;
	memset(buf, 0x00, sizeof buf );

	p=(char*)&ret;
	buf[3]=*(p+0);
	buf[2]=*(p+1);
	buf[1]=*(p+2);
	buf[0]=*(p+3);	

	return buf;
}
char* CData::ltrim(char* str)
{
	char buf[2048];
	int  i=0;
	int	 len=0;

	memset(buf, 0x00, sizeof buf );

	strcpy(buf, str);	
	len = strlen(buf);
	for(i=0; i<len; i++)
	{
		if( buf[i] !=' ')
			break;		
	}

	memset(str, 0x00, len );
	memcpy(str,buf+i,len-i);
	return str;
}


char* CData::rtrim(char* str)
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

char* CData::trim(char* str)
{
	rtrim(str);
	ltrim(str);
	return str;
}

char* CData::HeadAddStr(char* str, int num, char type)
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


BOOL CData::CheckStrHex(char* str )
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
				return FALSE;
		}
	}
	return TRUE;
}


int CData::HexToInt(unsigned char* HexData,  int len)
{
	unsigned int data=0;

	if( len > 4 || len == 0  ) return data;
	if( len ==1 )
	{
		data = (*HexData>>4)*16;
		data+= *HexData&0x0F;
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
		data += (*HexData>>4)*16;
		data += *HexData&0x0F;
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
* Function ID :  GetWeek
* Input       :  void
* Output      :  void
* Author      :  DengJun
* Date        :  Dec  12  2004
* Return	   :  返回本机的星期几
* Description :  
* Notice	   :  取本机的星期
*					
*=================================================================*/
int CData::GetWeek()
{
	int		nWeek=0;
	time_t 			timebuf;
	struct tm		*tmptr=NULL;	
	
	timebuf = time((time_t *) 0);
	if( timebuf >0 )
	{	
		tmptr   = localtime(&timebuf);		
	}
	if( tmptr!=NULL )
	{	
		nWeek = tmptr->tm_wday;	
	}
	if(nWeek==0) nWeek=7; //星期日，终端需要为7
	return nWeek;
}

/*=================================================================
* Function ID :  GetSysTime
* Input       :  void
* Output      :  void
* Author      :  DengJun
* Date        :  Dec  12  2004
* Return	   :  返回本机的时间(格式:YYYYMMDDHHMMSS)
* Description :  
* Notice	   :  取本机时间
*					
*=================================================================*/
BYTE* CData::GetSysTime()
{
	static BYTE		buf[20];
	time_t 			timebuf;
	struct tm		*tmptr=NULL;	
	
	memset(buf, 0x00, sizeof buf );
	timebuf=time((time_t *) 0);
	tmptr=localtime(&timebuf);
	while( tmptr==NULL )
	{
		Sleep(2);
		timebuf=time((time_t *) 0);
		tmptr=localtime(&timebuf);		
	}
	sprintf( (char*)m_clock, "%.4d%.2d%.2d%.2d%.2d%.2d",
		tmptr->tm_year+1900, tmptr->tm_mon+1, tmptr->tm_mday,
		tmptr->tm_hour, tmptr->tm_min,tmptr->tm_sec);	
	return m_clock;
}

/*=================================================================
* Function ID :  GetSysTime
* Input       :  void
* Output      :  void
* Author      :  DengJun
* Date        :  Dec  12  2004
* Return	   :  返回本机的时间(格式:YYYYMMDDHHMMSS)
* Description :  
* Notice	   :  取本机时间
*					
*=================================================================*/
BYTE* CData::GetSysTimeHex()
{
	static BYTE		buff[20];
	time_t 			timebuf;
	struct tm		*tmptr=NULL;	
	
	memset(buff, 0x00, sizeof buff );

	timebuf = time((time_t *) 0);
	tmptr   = localtime(&timebuf);
	while( tmptr==NULL )
	{
		Sleep(2);
		timebuf=time((time_t *) 0);
		tmptr=localtime(&timebuf);		
	}	
	buff[0]=tmptr->tm_year-100; //年
	buff[1]=tmptr->tm_mon+1;		//月
	buff[2]=tmptr->tm_mday;		//日
	buff[3]=tmptr->tm_hour;		//时
	buff[4]=tmptr->tm_min;		//分
	buff[5]=tmptr->tm_sec;		//秒
	return buff;
}
/*=================================================================
* Function ID :  GetSysWeek
* Input       :  void
* Output      :  void
* Author      :  DengJun
* Date        :  Dec  12  2004
* Return	   :  
* Description :  
* Notice	   :  取本机当天星期
*					
*=================================================================*/
int CData::GetSysWeek()
{	
	int nWeek=0;
	time_t 			timebuf;
	struct tm		*tmptr=NULL;	

	timebuf = time((time_t *) 0);
	tmptr   = localtime(&timebuf);		
	nWeek=tmptr->tm_wday;
	return nWeek;
	
}
/*=================================================================
* Function ID :  GetCurPath
* Input       :  void
*				  
* Output      :  char* pszDir
* Author      :  DengJun
* Date        :  2005.08.01
* Return	   :  void
* Description :  获取当前运行路径
* Notice	   :  
*				  	
*=================================================================*/
char* CData::GetCurPath()
{
	static char pszDir[128];
	
	memset(pszDir, 0x00, sizeof pszDir );
	
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
	return pszDir;	
}

/*=================================================================
* Function ID :  FileIsExist
* Input       :  char* pszFileName
*				  
* Output      :  
* Author      :  DengJun
* Date        :  2005.08.01
* Return	   :  void
* Description :  获取当前运行路径
* Notice	   :  
*				  	
*=================================================================*/
bool CData::FileIsExist(char* pszFileName)
{
	WIN32_FIND_DATA fd;
	
	HANDLE hFind = FindFirstFile(pszFileName, &fd);
	if( hFind != INVALID_HANDLE_VALUE )
	{
		FindClose(hFind);
		return TRUE;
	}
	
	return FALSE;
}


/*=================================================================
* Function ID :  GetDataBasePara
* Input       :  void
*				  
* Output      :  char* ServiceName,char* UserID,char* Pwd
* Author      :  DengJun
* Date        :  2005.08.01
* Return	   :  void
* Description :  从注册表中获取数据库登录的相关参数
* Notice	   :  
*				  	
*=================================================================*/
bool CData::GetDataBasePara( char* ServiceName,char* UserID,char* Pwd,char* DataBaseName)
{
	
	HKEY lpKey=0;		
	int  ret=0;
	char lpValueName[128],lpValue[128];
	long nValue=0;
	unsigned long nnValue=0;
	
	memset(lpValueName,0x00,sizeof lpValueName);
	memset(lpValue,0x00,sizeof lpValue);
	memset(&lpKey,0x00,sizeof lpKey);	
	
	ret=RegOpenKey(HKEY_LOCAL_MACHINE,"software\\999smart\\dbpw",&lpKey);
	if( ret )
	{
		if( lpKey) RegCloseKey(lpKey);		
		return false;
	}
	
	//数据库用户名
	memset(lpValue,0x00,sizeof lpValue);
	memset(lpValueName,0x00,sizeof lpValueName);
	strcpy(lpValueName,"UserID");	
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,NULL,&nnValue);//先查询出字节空间   
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,(unsigned char *)lpValue,&nnValue); 
	if( ret )
	{
		if( lpKey) RegCloseKey(lpKey);		
		return false;
	}	
	strcpy(UserID,lpValue);
	
	//创建数据库密码
	memset(lpValue,0x00,sizeof lpValue);
	memset(lpValueName,0x00,sizeof lpValueName);
	strcpy(lpValueName,"_PassWord");		
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,NULL,&nnValue);//先查询出字节空间   
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,(unsigned char *)lpValue,&nnValue); 
	if( ret )
	{
		if( lpKey) RegCloseKey(lpKey);
		return false;
	}	
	AscToBcd((unsigned char*)lpValue,16,(unsigned char*)lpValue);	
	Smart_UserDes((unsigned char*)lpValue,(unsigned char*)Pwd,'d');
	trim(Pwd);	
	
	//创建数据库服务名
	memset(lpValueName,0x00,sizeof lpValueName);
	memset(lpValue,0x00,sizeof lpValue);
	strcpy(lpValueName,"DataSource");
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,NULL,&nnValue);//先查询出字节空间   
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,(unsigned char *)lpValue,&nnValue); 
	if( ret )
	{
		if( lpKey) RegCloseKey(lpKey);		
		return false;
	}	
	strcpy(ServiceName,lpValue);

	//创建数据库名
	memset(lpValueName,0x00,sizeof lpValueName);
	memset(lpValue,0x00,sizeof lpValue);
	strcpy(lpValueName,"DataBaseName");
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,NULL,&nnValue);//先查询出字节空间   
	ret=RegQueryValueEx(lpKey,lpValueName,0,NULL,(unsigned char *)lpValue,&nnValue); 
	if( ret )
	{
		if( lpKey) RegCloseKey(lpKey);		
		return false;
	}	
	strcpy(DataBaseName,lpValue);	
	RegCloseKey(lpKey);	
	return true;
}

/*=================================================================
* Function ID :  SetIPAddrToID
* Input       :  char *cAddrIP
* Output      :  void
* Author      :  DengJun
* Date        :  2006 5  30
* Return	  :  返回8字符的字符串
* Description :  
* Notice	  :  将IP地址转换为4字节的字符
*					
*=================================================================*/
char *CData::SetIPAddrToID( char * cAddrIP)
{
	static char cID[10];
	int len=0,j=0,n=0;
	CData cData;
	char cTmp[40];
	char uctmp[9];
	int  nData[8];
	
	memset(cID,  0x00,sizeof cID);
	memset(cTmp, 0x00,sizeof cTmp);
	memset(uctmp,0x00,sizeof uctmp);
	memset(nData,0x00,sizeof nData);

	strcpy(cTmp,cAddrIP);
	cData.trim(cTmp);
	len=strlen(cTmp);	
	
	if( cTmp[0] == 'C' || cTmp[0] == 'c' )
	{
		sprintf(cID,"%02X%02X%02X%02X",cTmp[0],cTmp[1],cTmp[2],cTmp[3]);
		return cID;
	}
	int i=0;
	for( ; i<len; i++)
	{
		if( cTmp[i] == '.')
		{
			memcpy(uctmp,cTmp+j,i-j);
			j=i;
			j++;
			nData[n++]=atol(uctmp);
			memset(uctmp,0x00,sizeof uctmp);
		}
	}
	memcpy(uctmp,cTmp+j,i-j);
	nData[n++]=atol(uctmp);
	memset(uctmp,0x00,sizeof uctmp);
	sprintf(cID,"%02X%02X%02X%02X",nData[0],nData[1],nData[2],nData[3]);
	return cID;
}

bool CData::SetCardKind( byte *nCardKind,int nCardNo )
{
	int nCount=0;
	int nMod  =0;
	int nArr=0;
	if( nCardNo<=0) return true;

	nCount=nCardNo/8;
	nMod=nCardNo%8;

	if( nCount>32) return true;	
	if( nCount==32 )
	{
		nCardKind[0]=nCardKind[0]|0x80;
		return true;
	}
	if( nMod == 0 )
	{	
		nArr=32-nCount;	
	}
	else
	{
		nArr=31-nCount;	
	}
	if( nMod==1 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x01;
	}
	else if( nMod==2 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x02;
	}
	else if( nMod==3 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x04;
	}
	else if( nMod==4 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x08;
	}
	else if( nMod==5 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x10;
	}
	else if( nMod==6 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x20;
	}
	else if( nMod==7 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x40;
	}
	else if( nMod==0 )
	{
		nCardKind[nArr]=nCardKind[nArr]|0x80;
	}	
	return true;
}


/*=================================================================
* Function ID :  GetColValues
* Input       :  void
*				  
* Output      :  char* ServiceName,char* UserID,char* Pwd
* Author      :  DengJun
* Date        :  2005.08.01
* Return	   :  void
* Description :  GetColValues
* Notice	   :  
*				  	
*=================================================================*/
char* CData::GetColValues( char* InData)
{
	int i=0,len=0;
	char buffer[1024];
	static char	str[256];

	memset(str, 0,sizeof str);
	memset(buffer,0,sizeof buffer);
	
	strcpy(buffer,InData);
	len=strlen(buffer);
	
	for( i=0; i<len;i++)
	{
		if( buffer[i]==',' )
		{
			if( i>sizeof(str) )
			{
				return NULL;
			}
			memcpy(str,buffer,i);
			if( len>=i+1)
			{			
				memset(InData,0,strlen(InData));
				memcpy(InData,buffer+i+1,len-i-1);
			}
			break;
		}		
	}
	if( len==i)
	{
		strcpy(str,buffer);
		memset(buffer,0,strlen(buffer));
	}
	return str;
}