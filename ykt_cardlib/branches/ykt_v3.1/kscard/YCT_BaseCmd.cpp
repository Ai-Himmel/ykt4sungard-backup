#include "global.h"
#include "YCT_LibReader.h"
#include "YCTReaderInterface.h"
//选择MF
int CYCTReaderInterface::YCT_SelectMFDir(byte *ucRes)
{
	
	byte	ucCmd[256];
	byte	nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	strcpy((char*)ucCmd,"00A404000E315041592E5359532E4444463031");	
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}

//选择银行Easy Entry应用
int CYCTReaderInterface::YCT_SelectBankDir(byte *ucRes)
{
	byte	ucCmd[256];
	byte	nCmdLen=0;
	byte	nResLen=0;

	memset(ucCmd,0,sizeof ucCmd);		
	strcpy((char*)ucCmd,"00A4040010D15600000145415359454E5452590000");	
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}

//选择校园支付应用
int CYCTReaderInterface::YCT_SelectSchoolPacketDir(byte *ucRes)
{
	byte	nResLen=0;
	string sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	return ks_cpuapdu4hex(sCmd.c_str(),sCmd.size(),ucRes,nResLen);
}


//校园小钱包1应用
int CYCTReaderInterface::YCT_SelectPacketOneDir(byte *ucRes)
{
	byte	ucCmd[256];
	byte		nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	strcpy((char*)ucCmd,"00A4040010D156000001BDF0CACBB4EFC7AEB0FC32");
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}


int CYCTReaderInterface::YCT_VerifyPin( char* cPin)
{	
	byte	ucCmd[256],ucRes[128];
	byte	nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	memset(ucRes,0,sizeof ucRes);
	
	strcpy((char*)ucCmd,"0020000003");
	strcat((char*)ucCmd,cPin);
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}


int CYCTReaderInterface::YCT_ChangePin( char* coldPin, char* cnewPin)
{	
	byte	ucCmd[256],ucRes[128];
	byte	nCmdLen=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);	
	memset(ucRes,0,sizeof ucRes);
	
	strcpy((char*)ucCmd,"805E010007");
	memcpy(ucCmd+strlen((char*)ucCmd),coldPin,6);
	strcat((char*)ucCmd,"FF");
	memcpy(ucCmd+strlen((char*)ucCmd),cnewPin,6);	
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucRes,nResLen);
}



//读二进制文件//1字节SFI，1字节文件偏移地址，1字节交换数量N
int  CYCTReaderInterface::YCT_ReadBinaryFile(byte ucSFI,   byte ucOffset,
								    byte ucLength,byte *ucData)
{	
	byte	ucCmd[256];
	byte	nCmdLen=0;
	byte	ucShort=0;
	byte	nResLen=250;
	
	memset(ucCmd,0,sizeof ucCmd);
	
	sprintf((char*)ucCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);	
	nCmdLen=strlen((char*)ucCmd);
	return ks_cpuapdu(ucCmd,nCmdLen,ucData,nResLen);
}

//读记录文件//1字节SFI，1字节记录号 1字节长度
int CYCTReaderInterface::YCT_ReadRecordFile(byte ucSFI,
								byte ucRecordNo,
								byte ucLength,
								byte *ucData)
{
	byte	ucCmd[256],ucRes[256];
	byte	nCmdLen=0;
	byte	ucShort=0;
	byte	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);
	memset(ucRes,0,sizeof ucRes);	
	sprintf((char*)ucCmd,"00B2%02X%02X%02X",ucRecordNo,(ucSFI<<3)+4,ucLength);
	nCmdLen=strlen((char*)ucCmd);
	nResLen=128;
	return ks_cpuapdu(ucCmd,nCmdLen,ucData,nResLen);
}

/*=================================================================
 * Function ID :  SMT_UpdateBinaryFile
 * Input       :  
 * Output      :  void
 * Author      :  DengJun
 * Date        :  2005-10-10
 * Return	   :  
 * Description :  
 * Notice	   :  根据要求修改相应的二进制文件
 *					
 *=================================================================*/
int CYCTReaderInterface::SMT_MAC_UpdateBinaryFile(  byte ucSFI,
										byte ucOffset,
										byte ucLength,
										byte *ccAppSerailNo,
										byte *ucData )
{
	int   nRet=0;
	byte  len=0;
	byte  buffer[128],random[32];
	byte  mac[12];
	byte  ucRes[128],sCardNo[50];
	byte  sRandom[128],sSendData[1024],sRespData[1024];
	byte nResLen=0,nSendDatalen=0,nRespDatalen=0,sBuf[1024];

	memset(mac,    0x00, sizeof mac   );
	memset(buffer, 0x00, sizeof buffer);
	memset(random, 0x00, sizeof random);
	memset(ucRes,  0x00,sizeof ucRes);
	memset(sCardNo,0,sizeof sCardNo);
	
	strcpy((char*)sCardNo,(char*)ccAppSerailNo);
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"0084000004");
	nSendDatalen=strlen((char*)sSendData);
	APP_AscToBcd(sSendData,nSendDatalen,sSendData);
	nSendDatalen/=2;
	if( (nRet=ks_cpuapdu(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
	{
		return nRet;
	}	
	memcpy(sRandom,sRespData,4);
	memcpy(sRandom+4,"\x00\x00\x00\x00",4);
	
	
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,"801A250008");
	strcat((char*)sSendData,(char*)sCardNo);
	nSendDatalen=strlen((char*)sSendData);
	APP_AscToBcd(sSendData,nSendDatalen,sSendData);
	nSendDatalen/=2;
	if( (nRet=ks_cpuapdu4sam(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
	{
		return nRet;
	}
	memset(sRespData,0,sizeof sRespData);
	memset(sSendData,0,sizeof sSendData);
	sprintf((char*)sBuf,"04D6%02X%02X%02X%s",0x80+ucSFI,ucOffset,4+ucLength/2,(char*)ucData);
	strcpy((char*)sRespData,(char*)sBuf);
	APP_AscToBcd(sRespData,strlen((char*)sRespData),sRespData);
	len=GenMacData( sRespData, strlen((char*)sBuf),sRespData);
	
	memcpy(sSendData,"\x80\xFA\x05\x00",4);
	sSendData[4]=len+8;
	memcpy(sSendData+5,random,8);
	memcpy(sSendData+13,sRespData,len);	
	nSendDatalen=len+13;
	if( (nRet=ks_cpuapdu4sam(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
	{
		return nRet;
	}	
	memset(sRandom,0,sizeof sRandom);
	APP_BcdToAsc(sRespData,4,sRandom);
	
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	strcpy((char*)sSendData,(char*)sBuf);
	strcat((char*)sSendData,(char*)sRandom);
	nSendDatalen=strlen((char*)sSendData);
	APP_AscToBcd(sSendData,nSendDatalen,sSendData);
	nSendDatalen/=2;
	if( (nRet=ks_cpuapdu(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
	{
		return nRet;
	}	
	return 0;
}
#define YCT_PASM 0
/*
//用于计算MAC 手工和PSAM 
int __stdcall YCT_CalMAC_PSAMorAMT(byte *sCardNo,byte* sCmd,byte *sMac)
{
	int nRet=0,nLen=0;
	unsigned char sSendData[512],sRandom[30];
	unsigned char nSendDatalen=0x00,sKey[33];
	unsigned char sRespData[256],sBuf[1024];
	unsigned char nRespDatalen=0,sTmp[1024];
	DWORD		  lValue=0;
	
	
	memset(sTmp, 0,sizeof sTmp);	
	memset(sKey, 0,sizeof sKey);
	memset(sBuf, 0,sizeof sBuf);
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	
	
	memset(sRandom,0,sizeof sRandom);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	
	strcpy((char*)sSendData,"0084000004");
	nSendDatalen=strlen((char*)sSendData);
	APP_AscToBcd(sSendData,nSendDatalen,sSendData);
	nSendDatalen/=2;
	if( (nRet=ks_cpuapdu(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
	{
		return nRet;
	}	
	APP_BcdToAsc(sRespData,4,sRandom);
	memcpy(sRandom+8,"00000000",8);
	strcpy((char*)sBuf,(char*)sCmd);	
	
	//通过PSAM卡来计算
	if( YCT_PASM )
	{
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		strcpy((char*)sSendData,"801A250008");
		APP_BcdToAsc((byte*)sCardNo,8,sSendData+strlen((char*)sSendData));	
		nSendDatalen=strlen((char*)sSendData);
		APP_AscToBcd(sSendData,nSendDatalen,sSendData);
		nSendDatalen/=2;
		if( (nRet=ks_cpuapdu4sam(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
		{
			return nRet;
		}	
		
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		nSendDatalen=strlen((char*)sBuf);
		nSendDatalen/=2;
		if( nSendDatalen%8 ) memcpy(sBuf+nSendDatalen*2,"8000000000000000",(8-nSendDatalen%8)*2);
		else				 memcpy(sBuf+nSendDatalen*2,"8000000000000000",16);		
		strcpy((char*)sSendData,"80FA0500");
		sprintf((char*)sSendData+strlen((char*)sSendData),"%02X",8+strlen((char*)sBuf)/2);
		strcat((char*)sSendData,(char*)sRandom);
		strcat((char*)sSendData,(char*)sBuf);		
		nSendDatalen=strlen((char*)sSendData);
		APP_AscToBcd(sSendData,nSendDatalen,sSendData);
		nSendDatalen/=2;
		if( (nRet=ks_cpuapdu4sam(sSendData,nSendDatalen,sRespData,nRespDatalen))!=0 )
		{
			return nRet;
		}
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	else
	{
		
		//dengjun test
		//memset(&g_MainKey,0xFF,sizeof g_MainKey);
		//安全报文MAC		
		APP_AscToBcd(sRandom,16,sRandom);
		pboc_diver_key ((byte*)sCardNo,g_MainKey.DAMK,sKey);
		
		memset(sSendData,0,sizeof sSendData);
		memset(sRespData,0,sizeof sRespData);
		
		nSendDatalen=strlen((char*)sBuf);
		nSendDatalen/=2;
		if( nSendDatalen%8 ) memcpy(sBuf+nSendDatalen*2,"8000000000000000",(8-nSendDatalen%8)*2);
		else				 memcpy(sBuf+nSendDatalen*2,"8000000000000000",16);		
		
		nSendDatalen=strlen((char*)sBuf);
		APP_AscToBcd(sBuf,nSendDatalen,sSendData);
		nSendDatalen/=2;
		CalSecure_MAC(sKey,sRandom,nSendDatalen,sSendData,sRespData);		
		APP_BcdToAsc(sRespData,4,sMac);		
	}
	return 0;
}
*/
#if 0
//写记录文件
//1字节SFI，1字节记录号 1字节交换数量N，N字节交换的数据
int _stdcall SMT_MAC_WriteRecordFile(byte ucSFI,
									 byte ucRecordNo,
									 byte ucLength,
									 byte *ucData)
{
	byte	ucCmd[256],ucRes[256];
	int		nCmdLen=0;
	byte	ucShort=0;
	DWORD	nResLen=0;
	
	memset(ucCmd,0,sizeof ucCmd);
	memset(ucRes,0,sizeof ucRes);	
	sprintf((char*)ucCmd,"04DC%02X%02X%02X",ucRecordNo,(ucSFI<<3)+4,ucLength);
	nResLen=ucLength;
	return BJ_RunAPDU(ucCmd, nCmdLen, ucRes,nResLen);
}

/*=================================================================
 * Function ID :  SMT_MAC_WriteRecordFile
 * Input       :  
 * Output      :  void
 * Author      :  DengJun
 * Date        :  2005-10-10
 * Return	   :  
 * Description :  
 * Notice	   :  根据要求修改相应的定长记录 
 *=================================================================*/
int _stdcall SMT_MAC_WriteRecordFile(	byte ucSFI,
										byte ucRecordNo,
										byte ucLength,
										byte *ccAppSerailNo,
										byte *ucData )
{
	int   ret=0,len=0;
	byte  buffer[128],buf[256],random[32];
	byte  mac[12],str[128],ucSeedKey[128];
	byte  ucRes[128],cAppSerailNo[80];
	CData cData;
	DWORD nResLen=0;
	
	memset(buf,    0x00, sizeof buf   );
	memset(str,    0x00, sizeof str   );
	memset(mac,    0x00, sizeof mac   );
	memset(buffer, 0x00, sizeof buffer);
	memset(ucRes,  0x00,sizeof ucRes);
	memset(ucSeedKey,0x00,sizeof ucSeedKey);
	memset(cAppSerailNo,0,sizeof cAppSerailNo);
	
	cData.BcdToAsc(ccAppSerailNo,10,cAppSerailNo);
	//从用户卡取随机数
	memset(buffer, 0x00, sizeof buffer);
	strcpy((char*)buffer,"0084000004");	
	len = strlen((char*)buffer);
	if( (ret=BJ_RunAPDU(buffer,len,ucRes,nResLen))!=0x9000)
	{
		return ret;
	}
	memset(random, 0x00, sizeof random);
	memcpy(random,ucRes,8);	
	memcpy(random+8,"00000000",8);

	memset(buffer, 0x00,sizeof buffer );
	memcpy(buffer,"04DC",4);	
	sprintf((char*)buffer+4,"%02X",ucRecordNo);
	sprintf((char*)buffer+6,"%02X",12);
	ret=4+ucLength/2;
	sprintf((char*)buffer+8,"%02X",ret);
	memset(str,0,sizeof str);
	memcpy(buffer+10,ucData,ucLength);	
	
	memset(buf,0,sizeof buf);
	strcpy((char*)buf,(char*)random);
	strcat((char*)buf,(char*)buffer);
	len=strlen((char*)buffer);
	if( (g_nErrorCode=SMT_GetMac((char*)cAppSerailNo,(char*)buf, &len,g_nIndex)) != SUCCESS)
	{
		MessageBox(NULL,"加密机处理失败!!!","提示",MB_OK);
		return ret;
	}	
	//用户卡	
	memcpy(buffer+strlen((char*)buffer),buf,8);
	len = strlen((char*)buffer);
	return BJ_RunAPDU(buffer,len,ucRes,nResLen);
}
#endif

