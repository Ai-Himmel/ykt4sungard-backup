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

//获取错误码信息
char* CYCTReaderInterface::CPU_GetErrorCode(char *sMsg )
{	
	switch(  RetCode[0] ) 
	{
		case 0x00:
			strcpy(sMsg,"操作正常");
			break;
		case 0x60://	
			strcpy(sMsg,"没有安装SAM卡");
			break;			
		case 0x61://	
			strcpy(sMsg,"SAM卡初始化错误或未初始化");
			break;			
		case 0x62://	
			strcpy(sMsg,"SAM卡检验PIN错误");
			break;
		case 0x63://	
			strcpy(sMsg,"SAM卡类型与交易类型不匹配");
			break;
		case 0x64://	
			strcpy(sMsg,"SAM卡选择文件错误");
			break;
		case 0x65://	
			strcpy(sMsg,"SAM卡读错误");
			break;
		case 0x66://	
			strcpy(sMsg,"SAM卡写错误");
			break;						
		case 0x67://	
			strcpy(sMsg,"SAM卡认证错误");
			break;
		case 0x68://		
			strcpy(sMsg,"SAM卡随机数错误");
			break;
		case 0x69://	
			strcpy(sMsg,"SAM卡DES计算错误");
			break;
		case 0x6A://	KEY	
			strcpy(sMsg,"SAM卡生成钱包密钥错误");
			break;
		case 0x71://	
			strcpy(sMsg,"PKI卡RSA计算错误");
			break;
		case 0x72://	
			strcpy(sMsg,"PKI卡DES计算错误");
			break;
		case 0x7E://	
			strcpy(sMsg,"SAM卡执行APDU命令错误");
			break;
		case 0x7F://		
			strcpy(sMsg,"SAM卡操作超时");
			break;
		case 0x80://	
			strcpy(sMsg,"没有卡");
			break;
		case 0x81://		
			strcpy(sMsg,"选择卡片错误");
			break;
		case 0x82://	
			strcpy(sMsg,"停用卡片错误");
			break;
		case 0x83://	
			strcpy(sMsg,"认证卡片错误");
			break;
		case 0x84://	
			strcpy(sMsg,"卡片读操作错误");
			break;
		case 0x85://	
			strcpy(sMsg,"卡片写操作错误");
			break;
		case 0x86://		
			strcpy(sMsg,"卡片写操作中途中断");
			break;
		case 0x87://		
			strcpy(sMsg,"充值卡片无响应");
			break;
		case 0x90://		
			strcpy(sMsg,"不是本系统标准的卡片");
			break;
		case 0x91://		
			strcpy(sMsg,"卡片超出有效期");
			break;
		case 0x92://	
			strcpy(sMsg,"城市代码或应用代码错误");
			break;
		case 0x93://		
			strcpy(sMsg,"非法卡");
			break;
		case 0x94://		
			strcpy(sMsg,"黑名单卡");
			break;
		case 0x95://		
			strcpy(sMsg,"钱包余额不足");
			break;
		case 0x96://		
			strcpy(sMsg,"钱包余额超出上限");
			break;
		case 0x97://		
			strcpy(sMsg,"钱包未启用");
			break;
		case 0x98://		
			strcpy(sMsg,"钱包已停用");
			break;
		case 0x99://		
			strcpy(sMsg,"钱包正本被破坏");
			break;
		case 0x9A://		
			strcpy(sMsg,"钱包已停用");
			break;
		case 0x9F://		
			strcpy(sMsg,"公共信息区被破坏");
			break;
		case 0xAF://		
			strcpy(sMsg,"卡片操作超时");
			break;
		case 0xB0://	
			strcpy(sMsg,"交易操作中途中断");
			break;
		case 0xB1://	
			strcpy(sMsg,"交易中断");
			break;
		case 0xB2://	
			strcpy(sMsg,"前一步指令未执行或执行失败");
			break;
		case 0xC1://		
			strcpy(sMsg,"联机充值请求被拒绝");
			break;
		case 0xC2://	
			strcpy(sMsg,"联机充值认证失败");
			break;
		case 0xC3://		
			strcpy(sMsg,"交易结果提交错误");
			break;
		case 0xCE://		
			strcpy(sMsg,"联机充值协议错误");
			break;
		case 0xCF://		
			strcpy(sMsg,"交易操作超时");
			break;
		case 0xD0://		
			strcpy(sMsg,"远程读写器执行错");
			break;
		case 0xE0://		
			strcpy(sMsg,"MIFARE硬件初始化错误");
			break;
		case 0xE1://	
			strcpy(sMsg,"SAM硬件初始化错误");
			break;
		case 0xE2://		
			strcpy(sMsg,"命令错误");
			break;
		case 0xE3://		
			strcpy(sMsg,"参数错误");
			break;
		case 0xE4://	
			strcpy(sMsg,"检验和错误");
			break;
		case 0xE5://		
			strcpy(sMsg,"线路通讯超时");
			break;
		case 0xE6://		
			strcpy(sMsg,"内部FLASH写错误");
			break;
		case 0x30://		
			strcpy(sMsg,"报文头错");
			break;
		case 0x31://		
			strcpy(sMsg,"卡片不一致");
			break;
		case 0x32://		
			strcpy(sMsg,"流水号不一致");
			break;
		case 0x33://		
			strcpy(sMsg,"MAC错");
			break;
		case 0x3F://		
			strcpy(sMsg,"不支持的命令");
			break;
	}
	return sMsg;
}

//打开串口
bool CYCTReaderInterface::CPU_Open(char *sCom, int nBaudRate)
{
	return Open(sCom,nBaudRate);
}

//关闭串口
void CYCTReaderInterface::CPU_Close()
{
	Close();
}

//上电
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

//下电
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

//上电
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
//下电
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

//寻卡
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

//选卡
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

//执行PBOC指令
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

//执行PBOC指令 SAM
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
//接数数据
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
			strcpy(sErrMsg,"成功");
			break;
		case 0x6200:
			strcpy(sErrMsg,"6200=读卡设备中卡未插入到位");
			break;
		case 0x6281:
			strcpy(sErrMsg,"6281=回送的数据可能错误");
			break;
		case 0x6283:
			strcpy(sErrMsg,"6283=选择文件无效，文件或密钥校验错误");
			break;
		case 0x63C1:
			strcpy(sErrMsg,"63C1=密码错,还有1次机会");
			break;
		case 0x63C2:
			strcpy(sErrMsg,"63C2=密码错,还有2次机会");
			break;
		case 0x63C3:
			strcpy(sErrMsg,"63C3=密码错,还有3次机会");
			break;
		case 0x63C4:
			strcpy(sErrMsg,"63C4=密码错,还有4次机会");
			break;
		case 0x63C5:
			strcpy(sErrMsg,"63C5=密码错,还有5次机会");
			break;
		case 0x63C6:
			strcpy(sErrMsg,"63C6=密码错,还有6次机会");
			break;
		case 0x63C7:
			strcpy(sErrMsg,"63C7=密码错,还有7次机会");
			break;
		case 0x63C8:
			strcpy(sErrMsg,"63C8=密码错,还有8次机会");
			break;
		case 0x63C9:
			strcpy(sErrMsg,"63C9=密码错,还有9次机会");
			break;
		case 0x63CA:
			strcpy(sErrMsg,"63CA=密码错,还有10次机会");
			break;
		case 0x63CB:
			strcpy(sErrMsg,"63CB=密码错,还有11次机会");
			break;
		case 0x63CC:
			strcpy(sErrMsg,"63CC=密码错,还有12次机会");
			break;
		case 0x63CD:
			strcpy(sErrMsg,"63CD=密码错,还有13次机会");
			break;
		case 0x63CE:
			strcpy(sErrMsg,"63CE=密码错,还有14次机会");
			break;
		case 0x6400:
			strcpy(sErrMsg,"6400=状态标志未改变");
			break;
		case 0x6581:
			strcpy(sErrMsg,"6581=写EEPROM不成功");
			break;
		case 0x6700:
			strcpy(sErrMsg,"6700=指令的命令长度不正确");
			break;
		case 0x6900:
			strcpy(sErrMsg,"6900=CLA与线路保护要求不匹配");
			break;
		case 0x6901:
			strcpy(sErrMsg,"6901=无效的状态");
			break;
		case 0x6981:
			strcpy(sErrMsg,"6981=命令与文件结构不相容");
			break;
		case 0x6982:
			strcpy(sErrMsg,"6982=不满足写或修改卡片的安全状态");
			break;
		case 0x6983:
			strcpy(sErrMsg,"6983=密钥已经被锁死");
			break;
		case 0x6984:
			strcpy(sErrMsg,"6984=随机数无效,请先取随机数");
			break;
		case 0x6985:
			strcpy(sErrMsg,"6985=使用条件不满足");
			break;
		case 0x6986:
			strcpy(sErrMsg,"6986=不满足命令执行条件,当前文件不是EF");
			break;
		case 0x6987:
			strcpy(sErrMsg,"6987=无安全报文或MAC丢失");
			break;
		case 0x6988:
			strcpy(sErrMsg,"6988=安全报文数据MAC不正确");
			break;
		case 0x6A80:
			strcpy(sErrMsg,"6A80=数据域参数错误");
			break;
		case 0x6A81:
			strcpy(sErrMsg,"6A81=功能不支持或卡中无MF或卡片已经锁定");
			break;
		case 0x6A82:
			strcpy(sErrMsg,"6A82=卡片中文件未找到");
			break;
		case 0x6A83:
			strcpy(sErrMsg,"6A83=卡片中记录未找到");
			break;
		case 0x6A84:
			strcpy(sErrMsg,"6A84=文件无足够空间");
			break;
		case 0x6A86:
			strcpy(sErrMsg,"6A86=参数P1P2错误");
			break;
		case 0x6A87:
			strcpy(sErrMsg,"6A87=无安全报文");
			break;
		case 0x6A88:
			strcpy(sErrMsg,"6A88=密钥未找到");
			break;
		case 0x6B00:
			strcpy(sErrMsg,"6B00=在达到Le/Lc字节之前文件结束,偏移量错误");
			break;
		case 0x6D00:
			strcpy(sErrMsg,"6D00=无效的INS");
			break;
		case 0x6E00:
			strcpy(sErrMsg,"6E00=无效的CLA");
			break;
		case 0x6F00:
			strcpy(sErrMsg,"6F00=数据无效");
			break;
		case 0x6FF0:
			strcpy(sErrMsg,"6FF0=读卡器系统错误");
			break;
		case 0xFFFF:
			strcpy(sErrMsg,"FFFF=无法判断的错误");
			break;
		case 0x9210:
			strcpy(sErrMsg,"9210=卡片该DF下内存不足");
			break;
		case 0x9220:
			strcpy(sErrMsg,"9220=文件ID已存在");
			break;
		case 0x9240:
			strcpy(sErrMsg,"9240=卡片内存问题");
			break;
		case 0x9400:
			strcpy(sErrMsg,"9400=没有选择当前的EF文件ID");
			break;
		case 0x9402:
			strcpy(sErrMsg,"9402=超出范围或没有该记录");
			break;
		case 0x9404:
			strcpy(sErrMsg,"9404=EF的文件ID没有找到");
			break;
		case 0x9802:
			strcpy(sErrMsg,"9802=没有所要的密钥");
			break;
		case 0x9804:
			strcpy(sErrMsg,"9804=存在条件没有满足或MAC错");
			break;
		case 0x9810:
			strcpy(sErrMsg,"9810=KMC的应用被锁定");
			break;
		case 0x9835:
			strcpy(sErrMsg,"9835=没有取随机数");
			break;
		case 0x9840:
			strcpy(sErrMsg,"9840=该KEY被锁住");
			break;
		case 0x9302:
			strcpy(sErrMsg,"9302=MAC错误");
			break;
		case 0x9303:
			strcpy(sErrMsg,"9303=应用已被锁定");
			break;
		case 0x9401:
			strcpy(sErrMsg,"9401=电子钱包或电子存折金额不足");
			break;
		case 0x9403:
			strcpy(sErrMsg,"9403=密钥未找到");
			break;
		case 0x9406:
			strcpy(sErrMsg,"9406=所需的MAC不可用");
			break;
		default:
			sprintf(sErrMsg,"不知道的错误[%X]",nErrCode);
			break;
			
	}
	strcpy(sErrInfo,sErrMsg);
	return sErrInfo;
}