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
#define _CLASSINDLL		//����ɾ��
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
//�򿪴���,����0��ʾ�ɹ�,���ؾ��,
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
//Resp:���ݳ���(2�ֽ�)+״̬��(2�ֽ�)+����
	*rlen=sResp[0]*256+sResp[1]-2;	//ȥ��2�ֽ�״̬��
	if(*rlen>256)
		*rlen=256;
	if(*rlen>0) memcpy(rbuff,sResp+4,*rlen);
	return sResp[2]*256+sResp[3];
}
//�ϵ縴λ
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
//Ѱ��
int CNTReader::RequestCard(char *CardPhyID)
{
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	unsigned char sbuff[]="\xA2\x31\x03\xE8";//���ȴ�1����
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
//��Ƭ�Ͽ�
int CNTReader::PowerOff()
{
	if(!IsOpen())
		return PORT_NOTOPEN_ERROR;
	unsigned char sbuff[]="\xA2\x32\x00\x0A";//���ȴ�1����
	unsigned char rbuff[256]={0};
	short rlen=0;
	int ret=SendCommand(sbuff,4,rbuff,&rlen);
	if(ret)
	{
		return ret;
	}
	return 0;
}
//CPU��ֱָͨ��
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
//CPU��ֱָͨ��
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
//������Ϣ
char* CNTReader::GetErrMsg(int retcode, char *sMsg)
{
//	static char szMsg[256];
	memset(m_szErrMsg,0,sizeof(m_szErrMsg));
	switch(retcode)
	{
		case 0:
			strcpy(m_szErrMsg,"�ɹ�");
			break;
		case PORT_NOTOPEN_ERROR:	//		-1	 //�˿�δ��
			strcpy(m_szErrMsg,"�������˿�δ��");
			break;
		case SEND_DATA_ERROR:		//	-2   //���ݷ��ʹ�
			strcpy(m_szErrMsg,"���ʹ������ݴ���");
			break;									
		case RECV_DATA_ERROR:		//			-3   //�������ݴ���
			strcpy(m_szErrMsg,"���մ������ݴ���");
			break;
		case SELECT_CARD_ERROR:		//-4   //ѡ�񿨴���
			strcpy(m_szErrMsg,"Ѱ������");
			break;
		////////////////////////////////////////////////////////////
		case 0xA001:
			sprintf(m_szErrMsg,"Err-%04X:RFID-SIM��δ����",retcode);
			break;
		case 0xA002:
			sprintf(m_szErrMsg,"Err-%04X:RFID-SIM������ʧ��",retcode);
			break;
		case 0xA003:
			sprintf(m_szErrMsg,"Err-%04X:��֧�ֵĲ���",retcode);
			break;
		case 0xA004:
			sprintf(m_szErrMsg,"Err-%04X:�رղ���ʧ��",retcode);
			break;
		case 0xA005:
			sprintf(m_szErrMsg,"Err-%04X:�������ݸ�ʽ����",retcode);
			break;
		case 0xA006:
			sprintf(m_szErrMsg,"Err-%04X:����RFID-SIM���޻�Ӧ(�ȴ���ʱ)",retcode);
			break;
		case 0xA007:
			sprintf(m_szErrMsg,"Err-%04X:����RFID-SIM�����ݳ��ִ���",retcode);
			break;
		case 0xA008:
			sprintf(m_szErrMsg,"Err-%04X:δ֪����",retcode);
			break;
		case 0xA009:
			sprintf(m_szErrMsg,"Err-%04X:�������Լ�δͨ��",retcode);
			break;
		case 0xA00A:
			sprintf(m_szErrMsg,"Err-%04X:��ƬУ׼�����쳣",retcode);
			break;
		case 0xA00B:
			sprintf(m_szErrMsg,"Err-%04X:ˢ�������ܵ�����ĸ��ź�Ӱ��",retcode);
			break;
		default:
			sprintf(m_szErrMsg,"Err-%04X:δ֪����",retcode);
			break;
	}
	if(sMsg!=NULL)
		strcpy(sMsg,m_szErrMsg);
	return m_szErrMsg;
}