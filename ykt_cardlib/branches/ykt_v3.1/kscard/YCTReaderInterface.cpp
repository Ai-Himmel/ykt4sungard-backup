// YCTReaderInterface.cpp: implementation of the CYCTReaderInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "YCTReaderInterface.h"
#include <stdio.h>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int GenMacData( unsigned char*sData, byte ucDataLen, unsigned char* OutData)
{
	int nMode=0;	
	nMode=ucDataLen%8;
	if( !nMode ) {memcpy(OutData,sData,ucDataLen);memcpy(OutData+ucDataLen,"\x80\x00\x00\x00\x00\x00\x00\x00",8);}	
	else {memcpy(OutData,sData,ucDataLen);memcpy(OutData+ucDataLen,"\x80\x00\x00\x00\x00\x00\x00\x00",8-nMode);}
	return ucDataLen+8-nMode;
}

CYCTReaderInterface::CYCTReaderInterface()
{
	SendDataLen=0;	
	RecvDataLen=0;	

	memset(m_sCom,0,sizeof m_sCom);
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
}

CYCTReaderInterface::~CYCTReaderInterface()
{

}


char* CYCTReaderInterface::ltrim(char* str)
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

char* CYCTReaderInterface::rtrim(char* str)
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

char* CYCTReaderInterface::trim(char* str)
{
	rtrim(str);
	ltrim(str);
	return str;
}

BYTE* CYCTReaderInterface::AscToBcd(BYTE* ascbuf, int ascbuf_len, BYTE* bcdbuf)
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

BYTE* CYCTReaderInterface::BcdToAsc(BYTE* bcdbuf, int bcdbuf_len,BYTE* ascbuf )
{
	BYTE	ch =0;
	BYTE	mid=0;
	char	ascstr[2048];
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

BYTE CYCTReaderInterface::XOR( unsigned char *sBuf,int nBufLen )
{
	byte sTmp[1024],sCh=0;

	memset(sTmp,0,sizeof sTmp);
	memcpy(sTmp,sBuf,nBufLen);
	sCh=sTmp[0];
	for( int i=1; i<nBufLen; i++ )
	{
		sCh=sCh^sTmp[i];
	}
	return sCh;
}

//��ȡ��������Ϣ
char* CYCTReaderInterface::CPU_GetErrorCode(char *sMsg )
{	
	switch(  RetCode[0] ) 
	{
		case 0x00:
			strcpy(sMsg,"��������");
			break;
		case 0x60://	
			strcpy(sMsg,"û�а�װSAM��");
			break;			
		case 0x61://	
			strcpy(sMsg,"SAM����ʼ�������δ��ʼ��");
			break;			
		case 0x62://	
			strcpy(sMsg,"SAM������PIN����");
			break;
		case 0x63://	
			strcpy(sMsg,"SAM�������뽻�����Ͳ�ƥ��");
			break;
		case 0x64://	
			strcpy(sMsg,"SAM��ѡ���ļ�����");
			break;
		case 0x65://	
			strcpy(sMsg,"SAM��������");
			break;
		case 0x66://	
			strcpy(sMsg,"SAM��д����");
			break;						
		case 0x67://	
			strcpy(sMsg,"SAM����֤����");
			break;
		case 0x68://		
			strcpy(sMsg,"SAM�����������");
			break;
		case 0x69://	
			strcpy(sMsg,"SAM��DES�������");
			break;
		case 0x6A://	KEY	
			strcpy(sMsg,"SAM������Ǯ����Կ����");
			break;
		case 0x71://	
			strcpy(sMsg,"PKI��RSA�������");
			break;
		case 0x72://	
			strcpy(sMsg,"PKI��DES�������");
			break;
		case 0x7E://	
			strcpy(sMsg,"SAM��ִ��APDU�������");
			break;
		case 0x7F://		
			strcpy(sMsg,"SAM��������ʱ");
			break;
		case 0x80://	
			strcpy(sMsg,"û�п�");
			break;
		case 0x81://		
			strcpy(sMsg,"ѡ��Ƭ����");
			break;
		case 0x82://	
			strcpy(sMsg,"ͣ�ÿ�Ƭ����");
			break;
		case 0x83://	
			strcpy(sMsg,"��֤��Ƭ����");
			break;
		case 0x84://	
			strcpy(sMsg,"��Ƭ����������");
			break;
		case 0x85://	
			strcpy(sMsg,"��Ƭд��������");
			break;
		case 0x86://		
			strcpy(sMsg,"��Ƭд������;�ж�");
			break;
		case 0x87://		
			strcpy(sMsg,"��ֵ��Ƭ����Ӧ");
			break;
		case 0x90://		
			strcpy(sMsg,"���Ǳ�ϵͳ��׼�Ŀ�Ƭ");
			break;
		case 0x91://		
			strcpy(sMsg,"��Ƭ������Ч��");
			break;
		case 0x92://	
			strcpy(sMsg,"���д����Ӧ�ô������");
			break;
		case 0x93://		
			strcpy(sMsg,"�Ƿ���");
			break;
		case 0x94://		
			strcpy(sMsg,"��������");
			break;
		case 0x95://		
			strcpy(sMsg,"Ǯ������");
			break;
		case 0x96://		
			strcpy(sMsg,"Ǯ����������");
			break;
		case 0x97://		
			strcpy(sMsg,"Ǯ��δ����");
			break;
		case 0x98://		
			strcpy(sMsg,"Ǯ����ͣ��");
			break;
		case 0x99://		
			strcpy(sMsg,"Ǯ���������ƻ�");
			break;
		case 0x9A://		
			strcpy(sMsg,"Ǯ����ͣ��");
			break;
		case 0x9F://		
			strcpy(sMsg,"������Ϣ�����ƻ�");
			break;
		case 0xAF://		
			strcpy(sMsg,"��Ƭ������ʱ");
			break;
		case 0xB0://	
			strcpy(sMsg,"���ײ�����;�ж�");
			break;
		case 0xB1://	
			strcpy(sMsg,"�����ж�");
			break;
		case 0xB2://	
			strcpy(sMsg,"ǰһ��ָ��δִ�л�ִ��ʧ��");
			break;
		case 0xC1://		
			strcpy(sMsg,"������ֵ���󱻾ܾ�");
			break;
		case 0xC2://	
			strcpy(sMsg,"������ֵ��֤ʧ��");
			break;
		case 0xC3://		
			strcpy(sMsg,"���׽���ύ����");
			break;
		case 0xCE://		
			strcpy(sMsg,"������ֵЭ�����");
			break;
		case 0xCF://		
			strcpy(sMsg,"���ײ�����ʱ");
			break;
		case 0xD0://		
			strcpy(sMsg,"Զ�̶�д��ִ�д�");
			break;
		case 0xE0://		
			strcpy(sMsg,"MIFAREӲ����ʼ������");
			break;
		case 0xE1://	
			strcpy(sMsg,"SAMӲ����ʼ������");
			break;
		case 0xE2://		
			strcpy(sMsg,"�������");
			break;
		case 0xE3://		
			strcpy(sMsg,"��������");
			break;
		case 0xE4://	
			strcpy(sMsg,"����ʹ���");
			break;
		case 0xE5://		
			strcpy(sMsg,"��·ͨѶ��ʱ");
			break;
		case 0xE6://		
			strcpy(sMsg,"�ڲ�FLASHд����");
			break;
		case 0x30://		
			strcpy(sMsg,"����ͷ��");
			break;
		case 0x31://		
			strcpy(sMsg,"��Ƭ��һ��");
			break;
		case 0x32://		
			strcpy(sMsg,"��ˮ�Ų�һ��");
			break;
		case 0x33://		
			strcpy(sMsg,"MAC��");
			break;
		case 0x3F://		
			strcpy(sMsg,"��֧�ֵ�����");
			break;
	}
	return sMsg;
}

//�򿪴���
bool CYCTReaderInterface::CPU_Open(char *sCom, int nBaudRate)
{
	return Open(sCom,nBaudRate);
}

//�رմ���
void CYCTReaderInterface::CPU_Close()
{
	Close();
}

//�ϵ�
bool CYCTReaderInterface::CPU_PowerOn( )
{	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendReaderCommand(m_sCom,0x44,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return false;
	return true;
}

//�µ�
bool CYCTReaderInterface::CPU_PowerOff( )
{	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendReaderCommand(m_sCom,0x43,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return false;	
	return true;
}

//�ϵ�
bool CYCTReaderInterface::SAM_PowerOn( )
{	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendDataLen=0x01;
	SendData[0]=0x01;
	int nRet=SendReaderCommand(m_sCom,0x30,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendDataLen=0x01;
	SendData[0]=0x02;
	nRet=SendReaderCommand(m_sCom,0x30,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	return true;
}
//�µ�
bool CYCTReaderInterface::SAM_PowerOff( )
{	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendData[0]=0x01;
	SendDataLen=0x01;
	SendReaderCommand(m_sCom,0x31,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	
	SendDataLen=0;	
	RecvDataLen=0;		
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendDataLen=0x01;
	SendData[0]=0x02;
	SendReaderCommand(m_sCom,0x31,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);	
	return true;
}

//Ѱ��
bool CYCTReaderInterface::CPU_RequestCard( )
{	
	SendDataLen=0;
	RecvDataLen=0;
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);
	SendReaderCommand(m_sCom,0x01,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return false;
	return true;
}

//ѡ��
bool CYCTReaderInterface::CPU_SelectCard( char sType,char* sSerialNo)
{	
	SendDataLen=0;	
	RecvDataLen=0;
	memset(SendData,0,sizeof SendData);
	memset(RetCode,0xFF,sizeof RetCode);
	memset(RecvData,0,sizeof RecvData);	
	SendData[0]=sType;
	SendDataLen=1;
	SendReaderCommand(m_sCom,0x45,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return false;		
	memcpy(sSerialNo,RecvData,RecvDataLen);
	return true;
}

//ִ��PBOCָ��
int CYCTReaderInterface::CPU_APDU_Cmd( unsigned char *sSendData, unsigned char nSendDatalen,
									  unsigned char* sRespData,unsigned char &nRespDatalen )
{	
	SendDataLen=0;
	RecvDataLen=0;
	memset(SendData,0,   sizeof SendData);
	memset(RetCode, 0xFF,sizeof RetCode);
	memset(RecvData,0,   sizeof RecvData);
	
	SendData[0]=nSendDatalen/2;
	AscToBcd(sSendData,nSendDatalen,SendData+1);
	SendDataLen=nSendDatalen/2;
	SendDataLen++;
	SendReaderCommand(m_sCom,0x47,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return RetCode[0];
	nRespDatalen=RecvData[0]-2;
	memcpy(sRespData,RecvData+1,nRespDatalen);
	if( RecvData[RecvDataLen-2]==0x90 && RecvData[RecvDataLen-1]==0x00 )
	{
		return 0;
	}
	return (int)(RecvData[RecvDataLen-2]*256+RecvData[RecvDataLen-1]);
}

//ִ��PBOCָ�� SAM
int CYCTReaderInterface::SAM_APDU_Cmd(int nSamSlot, unsigned char *sSendData, unsigned char nSendDatalen,
									  unsigned char* sRespData,unsigned char &nRespDatalen )
{	
	SendDataLen=0;
	RecvDataLen=0;
	memset(SendData,0,   sizeof SendData);
	memset(RetCode, 0xFF,sizeof RetCode);
	memset(RecvData,0,   sizeof RecvData);
	
	if( nSamSlot==0 ) nSamSlot=1;
	SendData[0]=nSamSlot;
	SendData[1]=nSendDatalen/2;
	AscToBcd(sSendData,nSendDatalen,SendData+2);
	SendDataLen=nSendDatalen/2;
	SendDataLen++;
	SendDataLen++;
	SendReaderCommand(m_sCom,0x32,SendData,SendDataLen,RetCode,RecvData,&RecvDataLen);
	if( RetCode[0] ) return RetCode[0];
	if( RecvDataLen>2 )nRespDatalen=RecvDataLen-2;	
	memcpy(sRespData,RecvData,nRespDatalen);
	if( RecvData[RecvDataLen-2]==0x90 && RecvData[RecvDataLen-1]==0x00 )
	{
		return 0;
	}
	return (int)(RecvData[RecvDataLen-2]*256+RecvData[RecvDataLen-1]);
}
//��������
int  CYCTReaderInterface::SendReaderCommand(char *ComPort,unsigned char Cmd,unsigned char *SendData,
											unsigned  char SendDataLen,unsigned char *RetCode,
											unsigned char *RecvData,unsigned char* RecvDataLen)
{
	char sCmd[256],sResp[256];
	int  nCmdLen=0;

	memset(sCmd,0,sizeof sCmd);
	memset(sResp,0,sizeof sResp);
	if( !m_bComStatus )
	{
		if( !CPU_Open(m_sCom,57600) )
		{
			RetCode[0]=0x4F;
			return 1;
		}
	}
	sCmd[0]=(char)0xBA;
	sCmd[1]=(char)(2+SendDataLen);
	sCmd[2]=Cmd;
	memcpy(sCmd+3,SendData,SendDataLen);
	nCmdLen=3+SendDataLen;
	sCmd[nCmdLen]=XOR((byte*)sCmd,nCmdLen);
	nCmdLen++;
	if( !PostSend(sCmd,nCmdLen,2000) )
	{
		return SEND_DATA_ERROR;
	}
	Sleep(80);
	if( !PostRecv(sResp,sizeof(sResp),2000) )
	{
		return RECV_DATA_ERROR;
	}
	*RetCode=sResp[3];
	*RecvDataLen=sResp[1]-3;	
	if(*RecvDataLen>0) memcpy(RecvData,sResp+4,*RecvDataLen);	
	return 0;
}
char * CYCTReaderInterface::Get_ErrorInfo( int nErrCode,char *sErrInfo )
{
	char sErrMsg[128];
	memset(sErrMsg,0,sizeof sErrMsg);
	switch( nErrCode)
	{
		case 0x9000:
		case 0x0000:
			strcpy(sErrMsg,"�ɹ�");
			break;
		case 0x6200:
			strcpy(sErrMsg,"6200=�����豸�п�δ���뵽λ");
			break;
		case 0x6281:
			strcpy(sErrMsg,"6281=���͵����ݿ��ܴ���");
			break;
		case 0x6283:
			strcpy(sErrMsg,"6283=ѡ���ļ���Ч���ļ�����ԿУ�����");
			break;
		case 0x63C1:
			strcpy(sErrMsg,"63C1=�����,����1�λ���");
			break;
		case 0x63C2:
			strcpy(sErrMsg,"63C2=�����,����2�λ���");
			break;
		case 0x63C3:
			strcpy(sErrMsg,"63C3=�����,����3�λ���");
			break;
		case 0x63C4:
			strcpy(sErrMsg,"63C4=�����,����4�λ���");
			break;
		case 0x63C5:
			strcpy(sErrMsg,"63C5=�����,����5�λ���");
			break;
		case 0x63C6:
			strcpy(sErrMsg,"63C6=�����,����6�λ���");
			break;
		case 0x63C7:
			strcpy(sErrMsg,"63C7=�����,����7�λ���");
			break;
		case 0x63C8:
			strcpy(sErrMsg,"63C8=�����,����8�λ���");
			break;
		case 0x63C9:
			strcpy(sErrMsg,"63C9=�����,����9�λ���");
			break;
		case 0x63CA:
			strcpy(sErrMsg,"63CA=�����,����10�λ���");
			break;
		case 0x63CB:
			strcpy(sErrMsg,"63CB=�����,����11�λ���");
			break;
		case 0x63CC:
			strcpy(sErrMsg,"63CC=�����,����12�λ���");
			break;
		case 0x63CD:
			strcpy(sErrMsg,"63CD=�����,����13�λ���");
			break;
		case 0x63CE:
			strcpy(sErrMsg,"63CE=�����,����14�λ���");
			break;
		case 0x6400:
			strcpy(sErrMsg,"6400=״̬��־δ�ı�");
			break;
		case 0x6581:
			strcpy(sErrMsg,"6581=дEEPROM���ɹ�");
			break;
		case 0x6700:
			strcpy(sErrMsg,"6700=ָ�������Ȳ���ȷ");
			break;
		case 0x6900:
			strcpy(sErrMsg,"6900=CLA����·����Ҫ��ƥ��");
			break;
		case 0x6901:
			strcpy(sErrMsg,"6901=��Ч��״̬");
			break;
		case 0x6981:
			strcpy(sErrMsg,"6981=�������ļ��ṹ������");
			break;
		case 0x6982:
			strcpy(sErrMsg,"6982=������д���޸Ŀ�Ƭ�İ�ȫ״̬");
			break;
		case 0x6983:
			strcpy(sErrMsg,"6983=��Կ�Ѿ�������");
			break;
		case 0x6984:
			strcpy(sErrMsg,"6984=�������Ч,����ȡ�����");
			break;
		case 0x6985:
			strcpy(sErrMsg,"6985=ʹ������������");
			break;
		case 0x6986:
			strcpy(sErrMsg,"6986=����������ִ������,��ǰ�ļ�����EF");
			break;
		case 0x6987:
			strcpy(sErrMsg,"6987=�ް�ȫ���Ļ�MAC��ʧ");
			break;
		case 0x6988:
			strcpy(sErrMsg,"6988=��ȫ��������MAC����ȷ");
			break;
		case 0x6A80:
			strcpy(sErrMsg,"6A80=�������������");
			break;
		case 0x6A81:
			strcpy(sErrMsg,"6A81=���ܲ�֧�ֻ�����MF��Ƭ�Ѿ�����");
			break;
		case 0x6A82:
			strcpy(sErrMsg,"6A82=��Ƭ���ļ�δ�ҵ�");
			break;
		case 0x6A83:
			strcpy(sErrMsg,"6A83=��Ƭ�м�¼δ�ҵ�");
			break;
		case 0x6A84:
			strcpy(sErrMsg,"6A84=�ļ����㹻�ռ�");
			break;
		case 0x6A86:
			strcpy(sErrMsg,"6A86=����P1P2����");
			break;
		case 0x6A87:
			strcpy(sErrMsg,"6A87=�ް�ȫ����");
			break;
		case 0x6A88:
			strcpy(sErrMsg,"6A88=��Կδ�ҵ�");
			break;
		case 0x6B00:
			strcpy(sErrMsg,"6B00=�ڴﵽLe/Lc�ֽ�֮ǰ�ļ�����,ƫ��������");
			break;
		case 0x6D00:
			strcpy(sErrMsg,"6D00=��Ч��INS");
			break;
		case 0x6E00:
			strcpy(sErrMsg,"6E00=��Ч��CLA");
			break;
		case 0x6F00:
			strcpy(sErrMsg,"6F00=������Ч");
			break;
		case 0x6FF0:
			strcpy(sErrMsg,"6FF0=������ϵͳ����");
			break;
		case 0xFFFF:
			strcpy(sErrMsg,"FFFF=�޷��жϵĴ���");
			break;
		case 0x9210:
			strcpy(sErrMsg,"9210=��Ƭ��DF���ڴ治��");
			break;
		case 0x9220:
			strcpy(sErrMsg,"9220=�ļ�ID�Ѵ���");
			break;
		case 0x9240:
			strcpy(sErrMsg,"9240=��Ƭ�ڴ�����");
			break;
		case 0x9400:
			strcpy(sErrMsg,"9400=û��ѡ��ǰ��EF�ļ�ID");
			break;
		case 0x9402:
			strcpy(sErrMsg,"9402=������Χ��û�иü�¼");
			break;
		case 0x9404:
			strcpy(sErrMsg,"9404=EF���ļ�IDû���ҵ�");
			break;
		case 0x9802:
			strcpy(sErrMsg,"9802=û����Ҫ����Կ");
			break;
		case 0x9804:
			strcpy(sErrMsg,"9804=��������û�������MAC��");
			break;
		case 0x9810:
			strcpy(sErrMsg,"9810=KMC��Ӧ�ñ�����");
			break;
		case 0x9835:
			strcpy(sErrMsg,"9835=û��ȡ�����");
			break;
		case 0x9840:
			strcpy(sErrMsg,"9840=��KEY����ס");
			break;
		case 0x9302:
			strcpy(sErrMsg,"9302=MAC����");
			break;
		case 0x9303:
			strcpy(sErrMsg,"9303=Ӧ���ѱ�����");
			break;
		case 0x9401:
			strcpy(sErrMsg,"9401=����Ǯ������Ӵ��۽���");
			break;
		case 0x9403:
			strcpy(sErrMsg,"9403=��Կδ�ҵ�");
			break;
		case 0x9406:
			strcpy(sErrMsg,"9406=�����MAC������");
			break;
		default:
			sprintf(sErrMsg,"��֪���Ĵ���[%X]",nErrCode);
			break;
			
	}
	strcpy(sErrInfo,sErrMsg);
	return sErrInfo;
}