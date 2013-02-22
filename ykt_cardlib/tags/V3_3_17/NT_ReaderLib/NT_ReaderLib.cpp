// NT_ReaderLib.cpp : Defines the initialization routines for the DLL.
//

//#include "stdafx.h"
#include "NT_ReaderLib.h"
#include "NT_Comm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _CLASSINDLL
#define _CLASSINDLL		//不可删除
#endif
//HANDLE				g_nHandle=INVALID_HANDLE_VALUE;
//static CComSmart	NT_Comm;

static void Ascii2Hex(const unsigned char *uAscBuf,int iAscLen,char *sHexStr)
{
	int i=0;
	int k=0;
	for(i=0;i<iAscLen;i++)
	{
		k=uAscBuf[i];
		sprintf(&sHexStr[2*i],"%02X",k);
	}
}
static void Hex2Ascii(const char *sHexStr,short iHexLen,unsigned char *uAscBuf,short& iDecBUfLen)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];
	int offset=0;
	int dlen=iHexLen/2;
	
	memset(sHexTmp,0,sizeof(sHexTmp));
	if(iHexLen%2)
	{
		sHexTmp[0]='0';
		sHexTmp[1]=sHexStr[0];
		ul=strtoul(sHexTmp,NULL,16);
		uAscBuf[0]=(unsigned char)ul;
		offset++;
	}
	for(i=0;i<dlen;i++)
	{
		memcpy(sHexTmp,&sHexStr[2*i+offset],2);
		ul=strtoul(sHexTmp,NULL,16);
		uAscBuf[i+offset]=(unsigned char)ul;
	}
	iDecBUfLen=i+offset;
}
static BYTE XOR(const unsigned char *sbuff,int nbufflen )
{
	byte sCh=0;	
	sCh=sbuff[0];
	for( int i=1; i<nbufflen; i++ )
	{
		sCh=sCh^sbuff[i];
	}
	return sCh;
}
CNTReader::CNTReader():CComSmart()
{
	memset(m_szErrMsg,0,sizeof(m_szErrMsg));
//	CComSmart();
}
CNTReader::~CNTReader()
{
	Close();
}
//打开串口,大于0表示成功,返回句柄,
int CNTReader::OpenPort(int port,int band)
{
	if (!(port>=1 && port<=1024))
		return NULL;
	if(IsOpen())
		Close();
	char sCom[20];
	memset(sCom,0,sizeof sCom);
	sprintf(sCom,"\\\\.\\COM%ld",port);
	if( Open(sCom,band) ) 
		return 0;
	return PORT_OPEN_ERROR;
}
int CNTReader::SendCommand(const byte *sbuff,short slen,unsigned char * rbuff,short *rlen,int timeout)
{
	unsigned char sCmd[512]={0},sResp[512]={0};
	int  nCmdLen=0;
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	sCmd[0]=0x02;
	sCmd[1]=slen/256;
	sCmd[2]=slen%256;
	memcpy(sCmd+3,sbuff,slen);
	nCmdLen=3+slen;
	sCmd[nCmdLen]=XOR(sbuff,slen);
	nCmdLen++;
	sCmd[nCmdLen]=0x03;
	nCmdLen++;
	if( !PostSend(sCmd,nCmdLen,timeout))
	{
		return SEND_DATA_ERROR;
	}
	//Sleep(80);
	if( !PostRecv(sResp,sizeof(sResp),timeout))
	{
		return RECV_DATA_ERROR;
	}
//Resp:数据长度(2字节)+状态码(2字节)+数据
	*rlen=sResp[0]*256+sResp[1]-2;	//去掉2字节状态码
	if(*rlen>256)
		*rlen=256;
	if(*rlen>0) memcpy(rbuff,sResp+4,*rlen);
	return sResp[2]*256+sResp[3];
}
//上电复位
int CNTReader::PowerOn()
{
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	/*
	unsigned char sbuff[]="\xA1\x12";
	unsigned char rbuff[256]={0};
	short rlen=0;
	int ret=SendCommand(sbuff,2,rbuff,&rlen,500);
	if(ret)
	{
		if(SEND_DATA_ERROR==ret)
			return ret;
	}
	Sleep(500);
	*/
	return 0;
}
//寻卡
int CNTReader::RequestCard(char *CardPhyID)
{
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	unsigned char sbuff[]="\xA2\x31\x03\xE8";//最多等待1秒钟
	unsigned char rbuff[256]={0};
	short rlen=0;
	int ret=SendCommand(sbuff,4,rbuff,&rlen,2000);
	if(ret)
	{
		return ret;
	}
	if(rbuff[0]>8)
		return SELECT_CARD_ERROR;
	Ascii2Hex(rbuff+1,rbuff[0],CardPhyID);
	return 0;
}
//卡片断开
int CNTReader::PowerOff()
{
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	unsigned char sbuff[]="\xA2\x32\x00\x0A";//最多等待1秒钟
	unsigned char rbuff[256]={0};
	short rlen=0;
	int ret=SendCommand(sbuff,4,rbuff,&rlen);
	if(ret)
	{
		return ret;
	}
	return 0;
}
//CPU卡直通指令
int CNTReader::Apdu(const byte *sSendData,byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen)
{
	*nRespCode=0;
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	unsigned char sbuff[256]={0};
	unsigned char rbuff[256]={0};
	memcpy(sbuff,"\xA2\x33",2);
	memcpy(sbuff+2,sSendData,nSendDatalen);
	short slen=2+nSendDatalen;
	short rlen=0;
	int ret=SendCommand(sbuff,slen,rbuff,&rlen);
	if(ret)
		return ret;
	nRespDatalen=(unsigned char)rlen;
	memcpy(sRespData,rbuff,nRespDatalen);
	if( (sRespData[nRespDatalen-2]*256+sRespData[nRespDatalen-1])!=0x9000 )
	{
		*nRespCode= (sRespData[nRespDatalen-2]*256+sRespData[nRespDatalen-1]);
	}
	return 0;
}
//CPU卡直通指令
int CNTReader::Apdu4Hex(const char *sSendData, byte nSendDatalen,int* nRespCode,byte *sRespData,byte &nRespDatalen)
{
	*nRespCode=0;
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	short slen=0;
	short rlen=0;
	unsigned char sbuff[256]={0};
	unsigned char rbuff[256]={0};
	memcpy(sbuff,"\xA2\x33",2);
	memcpy(sbuff+2,sSendData,nSendDatalen);
	Hex2Ascii(sSendData,nSendDatalen,sbuff+2,slen);
	slen+=2;
	int ret=SendCommand(sbuff,slen,rbuff,&rlen);
	if(ret)
		return ret;
	nRespDatalen=(unsigned char)rlen;
	memcpy(sRespData,rbuff,nRespDatalen);
	if( (sRespData[nRespDatalen-2]*256+sRespData[nRespDatalen-1])!=0x9000 )
	{
		*nRespCode= (sRespData[nRespDatalen-2]*256+sRespData[nRespDatalen-1]);
	}
	return 0;
}
//错误信息
char* CNTReader::GetErrMsg(int retcode, char *sMsg)
{
//	static char szMsg[256];
	memset(m_szErrMsg,0,sizeof(m_szErrMsg));
	switch(retcode)
	{
		case 0:
			strcpy(m_szErrMsg,"成功");
			break;
		case PORT_NOTOPEN_ERROR:	//		-1	 //端口未打开
			strcpy(m_szErrMsg,"读卡器端口未打开");
			break;
		case SEND_DATA_ERROR:		//	-2   //数据发送错
			strcpy(m_szErrMsg,"发送串口数据错误");
			break;									
		case RECV_DATA_ERROR:		//			-3   //接收数据错误
			strcpy(m_szErrMsg,"接收串口数据错误");
			break;
		case SELECT_CARD_ERROR:		//-4   //选择卡错误
			strcpy(m_szErrMsg,"寻卡错误");
			break;
		////////////////////////////////////////////////////////////
		case 0xA001:
			sprintf(m_szErrMsg,"Err-%04X:RFID-SIM卡未连接",retcode);
			break;
		case 0xA002:
			sprintf(m_szErrMsg,"Err-%04X:RFID-SIM卡连接失败",retcode);
			break;
		case 0xA003:
			sprintf(m_szErrMsg,"Err-%04X:不支持的操作",retcode);
			break;
		case 0xA004:
			sprintf(m_szErrMsg,"Err-%04X:关闭操作失败",retcode);
			break;
		case 0xA005:
			sprintf(m_szErrMsg,"Err-%04X:操作数据格式错误",retcode);
			break;
		case 0xA006:
			sprintf(m_szErrMsg,"Err-%04X:操作RFID-SIM卡无回应(等待超时)",retcode);
			break;
		case 0xA007:
			sprintf(m_szErrMsg,"Err-%04X:操作RFID-SIM卡数据出现错误",retcode);
			break;
		case 0xA008:
			sprintf(m_szErrMsg,"Err-%04X:未知错误",retcode);
			break;
		case 0xA009:
			sprintf(m_szErrMsg,"Err-%04X:读卡器自检未通过",retcode);
			break;
		case 0xA00A:
			sprintf(m_szErrMsg,"Err-%04X:卡片校准参数异常",retcode);
			break;
		case 0xA00B:
			sprintf(m_szErrMsg,"Err-%04X:刷卡环境受到异物的干扰和影响",retcode);
			break;
		default:
			sprintf(m_szErrMsg,"Err-%04X:未知错误",retcode);
			break;
	}
	if(sMsg!=NULL)
		strcpy(sMsg,m_szErrMsg);
	return m_szErrMsg;
}