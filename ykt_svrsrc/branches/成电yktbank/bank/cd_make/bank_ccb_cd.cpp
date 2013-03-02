/* ----------------------------------------------------------
 * 程序名称：bank_ccb_nm.cpp
 * 创建日期：2010-10-26
 * 程序作者：xlh
 * 版本信息：1.0.0.0
 * 程序功能：成电建行转账接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_cd.h"
#include "tcp.h"
#include "bank.h"
#include "CI_Datatype.h"
#include "Custom_Interface.h"

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))
  void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02x",k);
	}
}
char change(unsigned char c) 
{ 
	if(c <=128) 
	return c; 
	else 
	return c-127; 

}
static void leftzstr(int len,char *intstr,char *outstr)
{
	int totallength=0;
	int strlength=0;
	strlength=strlen(intstr);
	totallength=len-strlength;
	strlength=strlen(intstr);
	for(int i=1;i<totallength;i++)
	{
		strcat(outstr,"0");
	}
	strcat(outstr,intstr);

}
//按照通用接口规范进行封装各自银行的接口
int Bank_CheckLine()
{
	return 0;
}
int SignInOut(INNER_TRANS_REQUEST * inner_trans,ST_BANK_CONFIG *g_Bank,char *signo)
{
	int ret=0;
       char packlen[6]="";
       char len[5]="";
	char host[16]="";		//对方机器的ip
	char szMsg[1024]="";
	int stplen=0;
	int headlen=0;
	short port = 0;			
	int timeout = 0;
       char temp[3096]="";
	char sysdate[11]="";
	char systime[9]="";
	CTcpSocket tcpsocket ;
	char buf[4096] = " ";
	char rcvbuf[4096]="";
	char tmp[8] = "";
	char lenstr[6]="";
	int plen=0;
	unsigned int		dataLen,  encDataLen,newDataLen;
	unsigned char       data[1024+16]; 
	unsigned char       encData[1024+16];
	unsigned char       newData[1024+16];
	unsigned char       entity1[12]="CA_CCBSC";
	unsigned char       entity2[12]="0009";
	dataLen=0;
	writelog(LOG_ERR,"ip[%s][%d]",g_Bank->BankUnit[0].szBankIP,g_Bank->BankUnit[0].iBankPort);
	des2src(host,g_Bank->BankUnit[0].szBankIP);					// 银行ip
	port=g_Bank->BankUnit[0].iBankPort;									// 银行端口
	timeout =g_Bank->BankUnit[0].iBankTimeout;								// 等待银行超时时间
  	getsysdate(sysdate);
	getsystime(systime);
	//******************************************************************
	//包头
	//******************************************************************
      	SignInOut_REQ tran;
 	memset(&tran,0x20,sizeof tran);			// 填充空格
	memcpy(tran.head.Txcode,REGISTRATION_CODE,6);    //交易码
	memcpy(tran.head.TxDate, sysdate,8); //交易日期
	memcpy(tran.head.TxTime,systime,8);//交易时间
	memcpy(tran.head.TxChannel,"2021",4);//待定
	des2src(tran.head.Operator,"system");
	des2src(tran.head.Checker,"system2");
	leftzstr(16,systime,temp);
	memcpy(tran.head.Serial,temp,(int)sizeof (tran.head.Serial));//交易参考号
	memcpy(tran.head.RespCode,"E9999",8);//初始请求
	//******************************************************************
	//包体
	//******************************************************************
	memcpy(tran.body.SignInOut,signo,1);//签入签出
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
#ifdef _CI_DEGUG_DES_
	//因加密不适合结构体，修改包头
		//包体部分，加密
	memcpy(data,tran.body.SignInOut,sizeof(tran.body.SignInOut));
	CI_RV				 rv;
	encDataLen=0;
	dataLen=sizeof(tran.body);
	rv  = CI_DeviceInit();
	if(rv  != CI_OK)
   	 {
        printf("CI_DeviceInit error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1,data,dataLen, NULL, &encDataLen);
   	 if(rv  != CI_OK)
   	 {
   		 CI_DeviceFinal();
       	 printf("get cipher length error. Error code is [%08x]\n",rv);
	    	 return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, encData, &encDataLen);
   	 if(rv  != CI_OK)
    	{
    	    CI_DeviceFinal();
         printf("SymEncrypt error. Error code is [%08x]\n",rv );
         return rv;
	}
	  plen=sizeof (tran.head)+encDataLen;
#else
         plen=sizeof (tran.head)+strlen(tran.body.SignInOut);
#endif
	
        sprintf(len,"%d",plen);
       writelog(LOG_ERR,"trans len[%s],[%d]",len,encDataLen);
	 leftzstr(6,len,packlen);
	memcpy(buf+stplen,packlen,5);
	stplen=stplen+5;                                     //包长度                                //包长度
 	 writelog(LOG_ERR,"trans len[%d],packlen[%s]",stplen,packlen);
	memcpy(buf+stplen,tran.head.Txcode,sizeof tran.head.Txcode);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.Txcode);                                     //交易码
      writelog(LOG_ERR,"trans len[%d],tran.head.Txcode[%s]",stplen,tran.head.Txcode);
	memcpy(buf+stplen,tran.head.TxDate,sizeof tran.head.TxDate);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.TxDate);                                     //交易日期
        writelog(LOG_ERR,"trans len[%d],tran.head.TxDate[%s]",stplen,tran.head.TxDate);
	memcpy(buf+stplen,tran.head.TxTime,sizeof tran.head.TxTime);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.TxTime);                                     //交易时间
       writelog(LOG_ERR,"trans len[%d],tran.head.TxTime[%s]",stplen,tran.head.TxTime);
	memcpy(buf+stplen,tran.head.Operator,sizeof tran.head.Operator);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.Operator);                                   //操作员
       writelog(LOG_ERR,"trans len[%d],tran.head.Operator[%s]",stplen,tran.head.Operator);
	memcpy(buf+stplen,tran.head.Checker,sizeof tran.head.Checker);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.Checker);                                   //审核员
	writelog(LOG_ERR,"trans len[%d],tran.head.Checker[%s]",stplen,tran.head.Checker);
	memcpy(buf+stplen,tran.head.TxChannel,sizeof tran.head.TxChannel);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.TxChannel);                                 //校园代码
       writelog(LOG_ERR,"trans len[%d],tran.head.TxChannel[%s]",stplen,tran.head.TxChannel);
	memcpy(buf+stplen,tran.head.TxOrgNo,sizeof tran.head.TxOrgNo);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.TxOrgNo);                                   //交易机构
       writelog(LOG_ERR,"trans len[%d],tran.head.TxOrgNo[%s]",stplen,tran.head.TxOrgNo);
	memcpy(buf+stplen,tran.head.BankSerial,sizeof tran.head.BankSerial);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.BankSerial);                               //银行流水号
       writelog(LOG_ERR,"trans len[%d],tran.head.BankSerial[%s]",stplen,tran.head.BankSerial);
	memcpy(buf+stplen,tran.head.Serial,sizeof tran.head.Serial);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.Serial);                                      //一卡通流水号
        writelog(LOG_ERR,"trans len[%d],tran.head.Serial[%s]",stplen,tran.head.Serial);
	memcpy(buf+stplen,tran.head.FileNames,sizeof tran.head.FileNames);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.FileNames);                               //文件名称
	writelog(LOG_ERR,"trans len[%d],tran.head.FileNames[%s]",stplen,tran.head.FileNames);
	memcpy(buf+stplen,tran.head.RespCode,sizeof tran.head.RespCode);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.RespCode);                                //响应码
       writelog(LOG_ERR,"trans len[%d],tran.head.RespCode[%s]",stplen,tran.head.RespCode);
	memcpy(buf+stplen,tran.head.RespMess,sizeof tran.head.RespMess);
	 writelog(LOG_ERR,"buf[%s]",buf);
	stplen=stplen+sizeof (tran.head.RespMess);                                //响应信息
       writelog(LOG_ERR,"trans len[%d],tran.head.RespMess[%s]",stplen,tran.head.RespMess);
	
#ifdef _CI_DEGUG_DES_
       memcpy(buf+stplen,encData,encDataLen);
      writelog(LOG_ERR,"encData[%s] ",encData);
	stplen=stplen+encDataLen;
#else
	memcpy(buf+stplen,tran.body.SignInOut,sizeof(tran.body.SignInOut));
	stplen=stplen+strlen(tran.body.SignInOut);
#endif
       writelog(LOG_ERR,"trans len[%d],tran.body.SignInOut[%s]",stplen,tran.body.SignInOut);
        writelog(LOG_ERR,"sendbuf[%s][%d][%d]",buf,stplen,strlen(buf));
	ret = tcpsocket.Send(buf,stplen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
              tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
       memset(lenstr,0,sizeof(lenstr));
	 plen=0;
	ret = tcpsocket.Recv(lenstr,5, timeout);	
	if (strlen(lenstr)>0)
		{
         	  plen=atoi(lenstr);
		}
	else
		{
		writelog(LOG_INFO,"接收数据失败，接收长度plen[%d]",plen);
		return -1;
		}

	if (plen-headlen)
	{
	       memset(&buf,0,sizeof(buf));
		ret = tcpsocket.Recv(buf,plen-sizeof(tran.head), timeout);
		writelog(LOG_INFO,"plen-sizeof(tran.head)[%d],sizeof(tran.head)[%d]",plen-sizeof(tran.head),sizeof(tran.head));
		writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);
		if (ret!=plen-sizeof(tran.head))
		{
			strcpy(szMsg,"接收银行数据错误");
			printf(szMsg);
			return ret;  
		}
#ifdef _CI_DEGUG_DES_
		memcpy(encData,buf,strlen(buf));
		rv = CI_SymDecrypt ( 1, entity2, encData, plen, NULL, &newDataLen); 
	  	 if(rv != CI_OK)
	  	 {
	      		  printf("get plain length error. Error code is [%08x]\n",rv);
			  return rv;
		}
		rv = CI_SymDecrypt ( 1, entity2, encData, plen,newData, &newDataLen);
	   	if(rv != CI_OK)
	   	{
	        printf("SymDecrypt error. Error code is [%08x]\n",rv);
	        return rv;
		}
		CI_DeviceFinal();
		 tcpsocket.Close();
#endif	
	}
	else
	{
         tcpsocket.Close();
	}

	if(strncmp(tran.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,tran.head.RespMess,64);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // 银行端处理错误
		return ret;
	}
	
	return 0;
}

int ToRegister(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
       char packlen[6]="";
       char len[5]="";
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;
	int stplen=0;
	int headlen=0;
       char temp[512]="";
	char sysdate[11]="";
	char systime[9]="";
	int plen=0;
	char lenstr[6]="";
	unsigned int		 dataLen, encDataLen,newDataLen;
	unsigned char       data[1024+16]; 
	unsigned char       encData[1024+16];
	unsigned char       newData[1024+16];
	unsigned char       entity1[12]="CA_CCBSC";
	unsigned char       entity2[12]="0009";
	dataLen=0;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCARD0,F_SCERT_NO,0);
	char buf[2048] = " ";
	char tmp[8] = "";
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间
    	getsysdate(sysdate);
	getsystime(systime);
	//******************************************************************
	//包头
	//******************************************************************
       ToRegister_REQ tran;
	headlen=sizeof(tran.head);
	memset(&tran,0x20,sizeof tran);			// 填充空格
	memcpy(tran.head.Txcode,SIGNED_CODE,6);    //交易码
	memcpy(tran.head.TxDate, sysdate,8); //交易日期
	memcpy(tran.head.TxTime,systime,8);//交易时间
	memcpy(tran.head.TxChannel,"2021",4);//待定
	des2src(tran.head.Operator,"system");
	des2src(tran.head.Checker,"system2");
	leftzstr(16,systime,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//交易参考号
	memcpy(tran.head.RespCode,"E9999",5);//初始请求
	//******************************************************************
	//包体
	//******************************************************************

       switch(rPack->sstatus0[0])
	{
		case 'A':
			memcpy(tran.body.Func,"0",1);//签约解约 0，1
			break;
		case 'D':
			memcpy(tran.body.Func,"1",1);//签约解约 0，1
			break;
		default:
			break;
	}
	des2src(tran.body.BankCard,rPack->scard0);
	des2src(tran.body.SchoolCard,rPack->spager);
	des2src(tran.body.SchoolNo,rPack->semail2);
	des2src(tran.body.SchoolName,rPack->sall_name);	

	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
#ifdef _CI_DEGUG_DES_
        //因加密不适合结构体，修改包头
	//包体部分，加密
	stplen=0;
	memcpy(data+stplen,tran.body.Func,sizeof(tran.body.Func));
	stplen=stplen+sizeof(tran.body.Func);
	memcpy(data+stplen,tran.body.SchoolCard,sizeof(tran.body.SchoolCard));
	stplen=stplen+sizeof(tran.body.SchoolCard);
	memcpy(data+stplen,tran.body.SchoolName,sizeof(tran.body.SchoolName));
	stplen=stplen+sizeof(tran.body.SchoolName);
	memcpy(data+stplen,tran.body.SchoolNo,sizeof(tran.body.SchoolNo));
	stplen=stplen+sizeof(tran.body.SchoolNo);
	memcpy(data+stplen,tran.body.BankCard,sizeof(tran.body.BankCard));
	stplen=stplen+sizeof(tran.body.BankCard);
	encDataLen=0;
	dataLen=sizeof(tran.body);
	CI_RV				 rv;
	rv  = CI_DeviceInit();
	if(rv  != CI_OK)
   	 {
        printf("CI_DeviceInit error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, NULL, &encDataLen);
   	 if(rv  != CI_OK)
   	 {
   	 	 CI_DeviceFinal();
        printf("get cipher length error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data,dataLen, encData, &encDataLen);
   	 if(rv  != CI_OK)
    	{
    		 CI_DeviceFinal();
         printf("SymEncrypt error. Error code is [%08x]\n",rv );
         return rv;
	}
	 plen=sizeof (tran.head)+encDataLen;
#else
	 plen=sizeof (tran);
#endif
        sprintf(len,"%d",plen);
	 leftzstr(6,len,packlen);
	 stplen=0;
	memcpy(buf+stplen,packlen,5);
	stplen=stplen+5;                                     //包长度                                //包长度
 	 writelog(LOG_ERR,"trans len[%d],packlen[%s]",stplen,packlen);
	memcpy(buf+stplen,tran.head.Txcode,sizeof tran.head.Txcode);
	stplen=stplen+sizeof (tran.head.Txcode);                                     //交易码
      writelog(LOG_ERR,"trans len[%d],tran.head.Txcode[%s]",stplen,tran.head.Txcode);
	memcpy(buf+stplen,tran.head.TxDate,sizeof tran.head.TxDate);
	stplen=stplen+sizeof (tran.head.TxDate);                                     //交易日期
        writelog(LOG_ERR,"trans len[%d],tran.head.TxDate[%s]",stplen,tran.head.TxDate);
	memcpy(buf+stplen,tran.head.TxTime,sizeof tran.head.TxTime);
	stplen=stplen+sizeof (tran.head.TxTime);                                     //交易时间
       writelog(LOG_ERR,"trans len[%d],tran.head.TxTime[%s]",stplen,tran.head.TxTime);
	memcpy(buf+stplen,tran.head.Operator,sizeof tran.head.Operator);
	stplen=stplen+sizeof (tran.head.Operator);                                   //操作员
       writelog(LOG_ERR,"trans len[%d],tran.head.Operator[%s]",stplen,tran.head.Operator);
	memcpy(buf+stplen,tran.head.Checker,sizeof tran.head.Checker);
	stplen=stplen+sizeof (tran.head.Checker);                                   //审核员
	writelog(LOG_ERR,"trans len[%d],tran.head.Checker[%s]",stplen,tran.head.Checker);
	memcpy(buf+stplen,tran.head.TxChannel,sizeof tran.head.TxChannel);
	stplen=stplen+sizeof (tran.head.TxChannel);                                 //校园代码
       writelog(LOG_ERR,"trans len[%d],tran.head.TxChannel[%s]",stplen,tran.head.TxChannel);
	memcpy(buf+stplen,tran.head.TxOrgNo,sizeof tran.head.TxOrgNo);
	stplen=stplen+sizeof (tran.head.TxOrgNo);                                   //交易机构
       writelog(LOG_ERR,"trans len[%d],tran.head.TxOrgNo[%s]",stplen,tran.head.TxOrgNo);
	memcpy(buf+stplen,tran.head.BankSerial,sizeof tran.head.BankSerial);
	stplen=stplen+sizeof (tran.head.BankSerial);                               //银行流水号
       writelog(LOG_ERR,"trans len[%d],tran.head.BankSerial[%s]",stplen,tran.head.BankSerial);
	memcpy(buf+stplen,tran.head.Serial,sizeof tran.head.Serial);
	stplen=stplen+sizeof (tran.head.Serial);                                      //一卡通流水号
        writelog(LOG_ERR,"trans len[%d],tran.head.Serial[%s]",stplen,tran.head.Serial);
	memcpy(buf+stplen,tran.head.FileNames,sizeof tran.head.FileNames);
	stplen=stplen+sizeof (tran.head.FileNames);                               //文件名称
	writelog(LOG_ERR,"trans len[%d],tran.head.FileNames[%s]",stplen,tran.head.FileNames);
	memcpy(buf+stplen,tran.head.RespCode,sizeof tran.head.RespCode);
	stplen=stplen+sizeof (tran.head.RespCode);                                //响应码
       writelog(LOG_ERR,"trans len[%d],tran.head.RespCode[%s]",stplen,tran.head.RespCode);
	memcpy(buf+stplen,tran.head.RespMess,sizeof tran.head.RespMess);
	stplen=stplen+sizeof (tran.head.RespMess);                                //响应信息
       writelog(LOG_ERR,"trans len[%d],tran.head.RespMess[%s]",stplen,tran.head.RespMess);
#ifdef _CI_DEGUG_DES_
//	dec2hex(encData,1040,temp);
	memcpy(buf+stplen,encData,encDataLen);
	stplen=stplen+encDataLen;
#else
	memcpy(buf+stplen,tran.body.Func,sizeof(tran.body.Func));
	stplen=stplen+sizeof(tran.body.Func);
	 writelog(LOG_ERR,"trans len[%d],tran.body.Func[%s]",stplen,tran.body.Func);
	memcpy(buf+stplen,tran.body.SchoolCard,sizeof(tran.body.SchoolCard));
	stplen=stplen+sizeof(tran.body.SchoolCard);
	 writelog(LOG_ERR,"trans len[%d],tran.head.SchoolCard[%s]",stplen,tran.body.SchoolCard);
	memcpy(buf+stplen,tran.body.SchoolName,sizeof(tran.body.SchoolName));
	stplen=stplen+sizeof(tran.body.SchoolName);
	 writelog(LOG_ERR,"trans len[%d],tran.body.SchoolName[%s]",stplen,tran.body.SchoolName);
	memcpy(buf+stplen,tran.body.SchoolNo,sizeof(tran.body.SchoolNo));
	stplen=stplen+sizeof(tran.body.SchoolNo);
	 writelog(LOG_ERR,"trans len[%d],tran.body.SchoolNo[%s]",stplen,tran.body.SchoolNo);
	memcpy(buf+stplen,tran.body.BankCard,sizeof(tran.body.BankCard));
	stplen=stplen+sizeof(tran.body.BankCard);
	 writelog(LOG_ERR,"trans len[%d],tran.body.BankCard[%s]",stplen,tran.body.BankCard);
	//包体部分，加密
#endif
      writelog(LOG_INFO,"trans send[%s]",buf);	
	ret = tcpsocket.Send(buf,stplen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
	       tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
              tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
       memset(lenstr,0,sizeof(lenstr));
	 plen=0;
	ret = tcpsocket.Recv(lenstr,5, timeout);	
	if (strlen(lenstr)>0)
		{
         	  plen=atoi(lenstr);
		}
	else
		{
		writelog(LOG_INFO,"接收数据失败，接收长度plen[%d]",plen);
		return -1;
		}
	writelog(LOG_INFO,"plen[%d][%d]",plen,sizeof(tran.head));	
	ret = tcpsocket.Recv((char*)&tran.head,sizeof(tran.head), timeout);
	if (plen-headlen)
	{
		ret = tcpsocket.Recv(buf,plen-sizeof(tran.head), timeout);	
		writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);
		if (ret!=plen-sizeof(tran.head))
		{
			strcpy(szMsg,"接收银行数据错误");
			printf(szMsg);
			return ret;  
		}
#ifdef  _CI_DEGUG_DES_
		memcpy(encData,buf,strlen(buf));
		rv = CI_SymDecrypt ( 1, entity2, encData, plen, NULL, &newDataLen); 
	  	 if(rv != CI_OK)
	  	 {
	  	 	 CI_DeviceFinal();
	      		  printf("get plain length error. Error code is [%08x]\n",rv);
			  return rv;
		}
		rv = CI_SymDecrypt ( 1, entity2, encData, plen,newData, &newDataLen);
	   	if(rv != CI_OK)
	   	{
	   		 CI_DeviceFinal();
	        printf("SymDecrypt error. Error code is [%08x]\n",rv);
	        return rv;
		}
		CI_DeviceFinal();
		tcpsocket.Close();
#endif
	
	}
	else
	{
          tcpsocket.Close();
	}
	if(strncmp(tran.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,tran.head.RespMess,64);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // 银行端处理错误
		return ret;
	}					
	else    
	{
		if (plen>headlen)
			{
#ifdef  _CI_DEGUG_DES_
	       memcpy(&tran.body,newData,sizeof newData);
#else
 		memcpy(&tran.body,buf,sizeof buf);
#endif
			}
		out_pack->lvol1 = 1;
		memcpy(out_pack->scard0,tran.body.BankCard,sizeof tran.body.BankCard);
		memcpy(out_pack->sdate0,tran.head.RespMess,sizeof out_pack->sdate1 );						// 银行流水号
		memcpy(out_pack->scert_no,tran.body.SchoolCard,sizeof out_pack->scert_no);					// 银行返回信息
	}
	writelog(LOG_INFO,"bankretinfo[%s],BankCard[%s]",out_pack->scert_no,tran.body.BankCard);
	PutRow(handle,out_pack,pRetCode,szMsg);	
	return 0;
}

int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
       char packlen[6]="";
       char len[6]="";
	char host[16]="";		//对方机器的ip
	short port = 0;	
	int    headlen=0;
	int timeout = 0;
       char temp[512]="";
	 int stplen=0;
	 int plen=0;
	 char lenstr[6]="";
	unsigned int		 dataLen, encDataLen,newDataLen;
	unsigned char       data[1024+16]; 
	unsigned char       encData[1024+16];
	unsigned char       newData[1024+16];
	unsigned char       entity1[12]="CA_CCBSC";
	unsigned char       entity2[12]="0009";
	dataLen=0;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_DAMT1,F_SCUST_AUTH2,F_SCUST_LIMIT2,F_SCUST_AUTH,F_SCUST_LIMIT,F_SPHONE,0);
	char buf[2048] = " ";
	char tmp[8] = "";
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间

	//******************************************************************
	//包头
	//******************************************************************
	 writelog(LOG_ERR,"mess[%s]","开始转账!");
       TRANS_REQ tran;
	headlen=sizeof(tran.head);
	memset(&tran,0x20,sizeof tran);			// 填充空格
	memcpy(tran.head.Txcode,TRANS_CODE,6);    //交易码
	memcpy(tran.head.TxDate, rPack->sdate0,8); //交易日期
	memcpy(tran.head.TxTime,rPack->stime0,8);//交易时间
	memcpy(tran.head.TxChannel,"2021",4);//待定	
	des2src(tran.head.Operator,"system");
	des2src(tran.head.Checker,"system2");
	leftzstr(16,rPack->sholder_ac_no,temp);//交易 参考号
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//交易参考号
	memcpy(tran.head.RespCode,"E9999",5);//初始请求
	//******************************************************************
	//包体
	//******************************************************************
	des2src(tran.body.SchoolCard,rPack->sphone);//我们用学工号
	des2src(tran.body.SchoolName,rPack->scust_limit);//姓名
	des2src(tran.body.SchoolNo,rPack->scust_auth2);//身份证号
	des2src(tran.body.BankCard,rPack->scust_limit2);//银行卡号
	memset(temp,0,sizeof temp);
	sprintf(temp,"%6.0lf",rPack->damt0);
	des2src(tran.body.RopAmt,temp);
	 writelog(LOG_ERR,"packlen[%s]","发送数据");
/*
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
#ifdef  _CI_DEGUG_DES_
	stplen=0;
       memcpy(data+stplen,tran.body.SchoolCard,sizeof(tran.body.SchoolCard));
	stplen=stplen+sizeof(tran.body.SchoolCard);
	memcpy(data+stplen,tran.body.SchoolName,sizeof(tran.body.SchoolName));
	stplen=stplen+sizeof(tran.body.SchoolName);
	memcpy(data+stplen,tran.body.SchoolNo,sizeof(tran.body.SchoolNo));
	stplen=stplen+sizeof(tran.body.SchoolNo);
	memcpy(data+stplen,tran.body.RopAmt,sizeof(tran.body.RopAmt));
	stplen=stplen+sizeof(tran.body.RopAmt);
	memcpy(data+stplen,tran.body.BankCard,sizeof(tran.body.BankCard));
	stplen=stplen+sizeof(tran.body.BankCard);
	//因加密不适合结构体，修改包头
	//包体部分，加密
	encDataLen=0;
	dataLen=sizeof(tran.body);
	CI_RV				 rv;
	rv  = CI_DeviceInit();
	if(rv  != CI_OK)
   	 {
        printf("CI_DeviceInit error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, NULL, &encDataLen);
   	 if(rv  != CI_OK)
   	 {
   	    CI_DeviceFinal();
        printf("get cipher length error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data,dataLen, encData, &encDataLen);
   	 if(rv  != CI_OK)
    	{
    	    CI_DeviceFinal();
         printf("SymEncrypt error. Error code is [%08x]\n",rv );
         return rv;
	}
        plen=0;
	 plen=sizeof (tran.head)+encDataLen;
#else
	 plen=sizeof (tran);
#endif
        sprintf(len,"%d",plen);  
        memset(temp,0,sizeof temp);
	 leftzstr(6,len,temp);
	 writelog(LOG_ERR,"plen[%s],len[%s]",temp,len);
	 stplen=0;
       memset(buf,0,sizeof(buf));
       memcpy(buf,temp,5);
	stplen=stplen+5;                                     //包长度                                //包长度
 	 writelog(LOG_ERR,"trans len[%d],buf[%s]",stplen,buf);
	memcpy(buf+stplen,tran.head.Txcode,sizeof tran.head.Txcode);
	stplen=stplen+sizeof (tran.head.Txcode);                                     //交易码
      writelog(LOG_ERR,"trans len[%d],tran.head.Txcode[%s]",stplen,tran.head.Txcode);
	memcpy(buf+stplen,tran.head.TxDate,sizeof tran.head.TxDate);
	stplen=stplen+sizeof (tran.head.TxDate);                                     //交易日期
        writelog(LOG_ERR,"trans len[%d],tran.head.TxDate[%s]",stplen,tran.head.TxDate);
	memcpy(buf+stplen,tran.head.TxTime,sizeof tran.head.TxTime);
	stplen=stplen+sizeof (tran.head.TxTime);                                     //交易时间
       writelog(LOG_ERR,"trans len[%d],tran.head.TxTime[%s]",stplen,tran.head.TxTime);
	memcpy(buf+stplen,tran.head.Operator,sizeof tran.head.Operator);
	stplen=stplen+sizeof (tran.head.Operator);                                   //操作员
       writelog(LOG_ERR,"trans len[%d],tran.head.Operator[%s]",stplen,tran.head.Operator);
	memcpy(buf+stplen,tran.head.Checker,sizeof tran.head.Checker);
	stplen=stplen+sizeof (tran.head.Checker);                                   //审核员
	writelog(LOG_ERR,"trans len[%d],tran.head.Checker[%s]",stplen,tran.head.Checker);
	memcpy(buf+stplen,tran.head.TxChannel,sizeof tran.head.TxChannel);
	stplen=stplen+sizeof (tran.head.TxChannel);                                 //校园代码
       writelog(LOG_ERR,"trans len[%d],tran.head.TxChannel[%s]",stplen,tran.head.TxChannel);
	memcpy(buf+stplen,tran.head.TxOrgNo,sizeof tran.head.TxOrgNo);
	stplen=stplen+sizeof (tran.head.TxOrgNo);                                   //交易机构
       writelog(LOG_ERR,"trans len[%d],tran.head.TxOrgNo[%s]",stplen,tran.head.TxOrgNo);
	memcpy(buf+stplen,tran.head.BankSerial,sizeof tran.head.BankSerial);
	stplen=stplen+sizeof (tran.head.BankSerial);                               //银行流水号
       writelog(LOG_ERR,"trans len[%d],tran.head.BankSerial[%s]",stplen,tran.head.BankSerial);
	memcpy(buf+stplen,tran.head.Serial,sizeof tran.head.Serial);
	stplen=stplen+sizeof (tran.head.Serial);                                      //一卡通流水号
        writelog(LOG_ERR,"trans len[%d],tran.head.Serial[%s]",stplen,tran.head.Serial);
	memcpy(buf+stplen,tran.head.FileNames,sizeof tran.head.FileNames);
	stplen=stplen+sizeof (tran.head.FileNames);                               //文件名称
	writelog(LOG_ERR,"trans len[%d],tran.head.FileNames[%s]",stplen,tran.head.FileNames);
	memcpy(buf+stplen,tran.head.RespCode,sizeof tran.head.RespCode);
	stplen=stplen+sizeof (tran.head.RespCode);                                //响应码
       writelog(LOG_ERR,"trans len[%d],tran.head.RespCode[%s]",stplen,tran.head.RespCode);
	memcpy(buf+stplen,tran.head.RespMess,sizeof tran.head.RespMess);
	stplen=stplen+sizeof (tran.head.RespMess);                                //响应信息
       writelog(LOG_ERR,"trans len[%d],tran.head.RespMess[%s]",stplen,tran.head.RespMess);
#ifdef  _CI_DEGUG_DES_   
//	dec2hex(encData,1040,temp);
	memcpy(buf+stplen,encData,encDataLen);
	stplen=stplen+encDataLen;
#else
	memcpy(buf+stplen,tran.body.SchoolCard,sizeof(tran.body.SchoolCard));
	stplen=stplen+sizeof(tran.body.SchoolCard);
	writelog(LOG_ERR,"trans len[%d],tran.body.SchoolCard[%s]",stplen,tran.body.SchoolCard);
	memcpy(buf+stplen,tran.body.SchoolName,sizeof(tran.body.SchoolName));
	stplen=stplen+sizeof(tran.body.SchoolName);
	  writelog(LOG_ERR,"trans len[%d],tran.body.SchoolName[%s]",stplen,tran.body.SchoolName);
	memcpy(buf+stplen,tran.body.SchoolNo,sizeof(tran.body.SchoolNo));
	stplen=stplen+sizeof(tran.body.SchoolNo);
	  writelog(LOG_ERR,"trans len[%d],tran.body.SchoolNo[%s]",stplen,tran.body.SchoolNo);
	memcpy(buf+stplen,tran.body.RopAmt,sizeof(tran.body.RopAmt));
	stplen=stplen+sizeof(tran.body.RopAmt);
	  writelog(LOG_ERR,"trans len[%d],tran.body.RopAmt[%s]",stplen,tran.body.RopAmt);
	memcpy(buf+stplen,tran.body.BankCard,sizeof(tran.body.BankCard));
	stplen=stplen+sizeof(tran.body.BankCard);
	  writelog(LOG_ERR,"trans len[%d],tran.body.BankCard[%s]",stplen,tran.body.BankCard);
#endif
	writelog(LOG_ERR,"stplen[%d],buf[%s]",stplen,buf);
	ret = tcpsocket.Send(buf,stplen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}
         writelog(LOG_ERR,"timeout[%d]",timeout);
   memset(lenstr,0,sizeof(lenstr));
	 plen=0;
	ret = tcpsocket.Recv(lenstr,5, timeout);	
	if (strlen(lenstr)>0)
		{
         	  plen=atoi(lenstr);
		}
	else
		{
		writelog(LOG_INFO,"接收数据失败，接收长度plen[%d]",plen);
		return -1;
		}
	ret = tcpsocket.Recv((char*)&tran.head,sizeof(tran.head), timeout);	
	if (plen-headlen)
	{
		ret = tcpsocket.Recv(buf,plen-sizeof(tran.head), timeout);	
		writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);
		if (ret!=plen-sizeof(tran.head))
		{
			strcpy(szMsg,"接收银行数据错误");
			printf(szMsg);
			return ret;  
		}
#ifdef  _CI_DEGUG_DES_ 		
		memcpy(encData,buf,strlen(buf));
		rv = CI_SymDecrypt ( 1, entity2, encData, plen, NULL, &newDataLen); 
	  	 if(rv != CI_OK)
	  	 {
	      		  printf("get plain length error. Error code is [%08x]\n",rv);
			  return rv;
		}
		rv = CI_SymDecrypt ( 1, entity2, encData, plen,newData, &newDataLen);
	   	if(rv != CI_OK)
	   	{
	        printf("SymDecrypt error. Error code is [%08x]\n",rv);
	        return rv;
		}
	       CI_DeviceFinal();
#endif
	}
	else
	{
		tcpsocket.Close();
	}
	if(strncmp(tran.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,tran.head.RespMess,64);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // 银行端处理错误
		return ret;
	}
	else
	{
	if ((plen-headlen)>0)
		{
#ifdef  _CI_DEGUG_DES_ 
             memcpy(&tran.body,newData,sizeof(newData));
#else
             memcpy(&tran.body,buf,sizeof(buf));
#endif
		}

	*/
		out_pack->lvol1 = 1;
		out_pack->damt1=atof(tran.body.RopAmt);
		memcpy(out_pack->scust_auth,tran.head.Serial,sizeof out_pack->scust_auth);
		memcpy(out_pack->scust_limit,tran.head.BankSerial,sizeof out_pack->scust_limit);
		memcpy(out_pack->sphone,tran.body.SchoolCard,sizeof out_pack->sphone);
		memcpy(out_pack->scust_limit2,tran.body.BankCard,sizeof out_pack->scust_limit2);
		memcpy(out_pack->scust_auth2,tran.body.SchoolNo,sizeof out_pack->scust_auth2 );		
		memcpy(out_pack->sdate0,tran.head.RespMess,sizeof out_pack->sdate1 );						// 银行流水号
		memcpy(out_pack->scust_limit2,tran.body.BankCard,sizeof out_pack->scust_limit2);					// 银行返回信息

	//}
	PutRow(handle,out_pack,pRetCode,szMsg);	
	writelog(LOG_INFO,"bankretinfo[%s],lvol1[%d]",out_pack->scust_limit2,out_pack->lvol1);
	return 0;
}

int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;
       char packlen[5]="";
       char len[5]="";
	char buf[2048]="";
	char inbody[256]="";
	char outbody[256]="";
	 int stplen=0;
	 int headlen=0;
	 int plen=0;
	 char lenstr[6]="";
	 unsigned int		 dataLen, encDataLen,newDataLen;
	unsigned char       data[1024+16]; 
	unsigned char       encData[1024+16];
	unsigned char       newData[1024+16];
	unsigned char       entity1[12]="CA_CCBSC";
	unsigned char       entity2[12]="0009";
	dataLen=0;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE0,F_SCUST_AUTH2,F_SCUST_LIMIT2,0);

	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间
	 char temp[512]="";

	//******************************************************************
	//包头
	//******************************************************************
       REVTRANS_REQ tran;
	headlen=sizeof(tran.head);
	memset(&tran,0x20,sizeof tran);			// 填充空格
	memcpy(tran.head.Txcode,REV_TRANS_CODE,6);    //交易码
	memcpy(tran.head.TxDate, rPack->sdate0,8); //交易日期
	memcpy(tran.head.TxTime,rPack->stime0,8);//交易时间
	memcpy(tran.head.TxChannel,"2021",4);//待定
	des2src(tran.head.Operator,"system");
	des2src(tran.head.Checker,"system2");
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.BankSerial,temp,sizeof (tran.head.BankSerial));//交易参考号
	memcpy(tran.head.RespCode,"E9999",5);//初始请求
	//******************************************************************
	//包体
	//******************************************************************
	des2src(tran.body.OldTxdate, rPack->sdate1);    //原交易日期
	des2src(tran.body.OldTransBankId, temp);
	memset(temp,0,sizeof temp);
	sprintf(temp,"%6.0lf",rPack->damt0);
	des2src(tran.body.OldRopAmt, temp);
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
#ifdef  _CI_DEGUG_DES_ 	
        	//因加密不适合结构体，修改包头
		//包体部分，加密
	memcpy(data+stplen,tran.body.OldTxdate,sizeof(tran.body.OldTxdate));
	stplen=stplen+sizeof(tran.body.OldTxdate);
	memcpy(data+stplen,tran.body.OldTransBankId,sizeof(tran.body.OldTransBankId));
	 writelog(LOG_ERR,"OldTransBankId[%s]",tran.body.OldTransBankId);
	stplen=stplen+sizeof(tran.body.OldTransBankId);
	memcpy(data+stplen,tran.body.OldRopAmt,sizeof(tran.body.OldRopAmt));
	stplen=stplen+sizeof(tran.body.OldRopAmt);
	encDataLen=0;
	dataLen=sizeof(tran.body);
	CI_RV				 rv;
	rv  = CI_DeviceInit();
	if(rv  != CI_OK)
   	 {
        printf("CI_DeviceInit error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, NULL, &encDataLen);
   	 if(rv  != CI_OK)
   	 {
   	     CI_DeviceFinal();
        printf("get cipher length error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data,dataLen, encData, &encDataLen);
   	 if(rv  != CI_OK)
    	{
    	    CI_DeviceFinal();
         printf("SymEncrypt error. Error code is [%08x]\n",rv );
         return rv;
	}
	 plen=sizeof (tran.head)+encDataLen;
#else
        plen=sizeof(tran);
#endif
        sprintf(len,"%d",plen);
	 writelog(LOG_ERR,"len[%s]",len);
	 leftzstr(6,len,packlen);
	 stplen=0;
	memcpy(buf+stplen,packlen,5);
	stplen=stplen+5;                                     //包长度                                //包长度
 	 writelog(LOG_ERR,"trans len[%d],packlen[%s]",stplen,packlen);
	memcpy(buf+stplen,tran.head.Txcode,sizeof tran.head.Txcode);
	stplen=stplen+sizeof (tran.head.Txcode);                                     //交易码
      writelog(LOG_ERR,"trans len[%d],tran.head.Txcode[%s]",stplen,tran.head.Txcode);
	memcpy(buf+stplen,tran.head.TxDate,sizeof tran.head.TxDate);
	stplen=stplen+sizeof (tran.head.TxDate);                                     //交易日期
        writelog(LOG_ERR,"trans len[%d],tran.head.TxDate[%s]",stplen,tran.head.TxDate);
	memcpy(buf+stplen,tran.head.TxTime,sizeof tran.head.TxTime);
	stplen=stplen+sizeof (tran.head.TxTime);                                     //交易时间
       writelog(LOG_ERR,"trans len[%d],tran.head.TxTime[%s]",stplen,tran.head.TxTime);
	memcpy(buf+stplen,tran.head.Operator,sizeof tran.head.Operator);
	stplen=stplen+sizeof (tran.head.Operator);                                   //操作员
       writelog(LOG_ERR,"trans len[%d],tran.head.Operator[%s]",stplen,tran.head.Operator);
	memcpy(buf+stplen,tran.head.Checker,sizeof tran.head.Checker);
	stplen=stplen+sizeof (tran.head.Checker);                                   //审核员
	writelog(LOG_ERR,"trans len[%d],tran.head.Checker[%s]",stplen,tran.head.Checker);
	memcpy(buf+stplen,tran.head.TxChannel,sizeof tran.head.TxChannel);
	stplen=stplen+sizeof (tran.head.TxChannel);                                 //校园代码
       writelog(LOG_ERR,"trans len[%d],tran.head.TxChannel[%s]",stplen,tran.head.TxChannel);
	memcpy(buf+stplen,tran.head.TxOrgNo,sizeof tran.head.TxOrgNo);
	stplen=stplen+sizeof (tran.head.TxOrgNo);                                   //交易机构
       writelog(LOG_ERR,"trans len[%d],tran.head.TxOrgNo[%s]",stplen,tran.head.TxOrgNo);
	memcpy(buf+stplen,tran.head.BankSerial,sizeof tran.head.BankSerial);
	stplen=stplen+sizeof (tran.head.BankSerial);                               //银行流水号
       writelog(LOG_ERR,"trans len[%d],tran.head.BankSerial[%s]",stplen,tran.head.BankSerial);
	memcpy(buf+stplen,tran.head.Serial,sizeof tran.head.Serial);
	stplen=stplen+sizeof (tran.head.Serial);                                      //一卡通流水号
        writelog(LOG_ERR,"trans len[%d],tran.head.Serial[%s]",stplen,tran.head.Serial);
	memcpy(buf+stplen,tran.head.FileNames,sizeof tran.head.FileNames);
	stplen=stplen+sizeof (tran.head.FileNames);                               //文件名称
	writelog(LOG_ERR,"trans len[%d],tran.head.FileNames[%s]",stplen,tran.head.FileNames);
	memcpy(buf+stplen,tran.head.RespCode,sizeof tran.head.RespCode);
	stplen=stplen+sizeof (tran.head.RespCode);                                //响应码
       writelog(LOG_ERR,"trans len[%d],tran.head.RespCode[%s]",stplen,tran.head.RespCode);
	memcpy(buf+stplen,tran.head.RespMess,sizeof tran.head.RespMess);
	stplen=stplen+sizeof (tran.head.RespMess);                                //响应信息
       writelog(LOG_ERR,"trans len[%d],tran.head.RespMess[%s]",stplen,tran.head.RespMess);
#ifdef  _CI_DEGUG_DES_ 
//	dec2hex(encData,1040,temp);
	memcpy(buf+stplen,encData,encDataLen);
	stplen=stplen+encDataLen;
#else
	memcpy(buf+stplen,tran.body.OldTxdate,sizeof(tran.body.OldTxdate));
	stplen=stplen+sizeof(tran.body.OldTxdate);
	 writelog(LOG_ERR,"trans len[%d],tran.body.OldTxdate[%s]",stplen,tran.body.OldTxdate);
	memcpy(buf+stplen,tran.body.OldTransBankId,sizeof(tran.body.OldTransBankId));
	stplen=stplen+sizeof(tran.body.OldTransBankId);
	 writelog(LOG_ERR,"trans len[%d],tran.body.OldTransBankId[%s]",stplen,tran.body.OldTransBankId);
	memcpy(buf+stplen,tran.body.OldRopAmt,sizeof(tran.body.OldRopAmt));
	stplen=stplen+sizeof(tran.body.OldRopAmt);
	 writelog(LOG_ERR,"trans len[%d],tran.body.OldRopAmt[%s]",stplen,tran.body.OldRopAmt);
#endif
       writelog(LOG_ERR,"stplen[%d],buf[%s]",stplen,buf);
	ret = tcpsocket.Send(buf,stplen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		tcpsocket.Close();
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
             tcpsocket.Close();
		return E_TRANS_REQUEST;
	}

  	 memset(lenstr,0,sizeof(lenstr));
	 plen=0;
	ret = tcpsocket.Recv(lenstr,5, timeout);	
	if (strlen(lenstr)>0)
		{
         	  plen=atoi(lenstr);
		}
	else
		{
		writelog(LOG_INFO,"接收数据失败，接收长度plen[%d]",plen);
		return -1;
		}
	  writelog(LOG_ERR,"stplen[%d],headlen[%d]",plen,headlen);
	ret = tcpsocket.Recv((char*)&tran.head,headlen, timeout);
	if (plen-headlen)
	{
		ret = tcpsocket.Recv(buf,plen-headlen, timeout);	
		writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

		if (ret!=plen-sizeof(tran.head))
		{
			strcpy(szMsg,"接收银行数据错误");
			printf(szMsg);
			return ret;  
		}
#ifdef  _CI_DEGUG_DES_ 
		memcpy(encData,buf,strlen(buf));
		rv = CI_SymDecrypt ( 1, entity2, encData, plen, NULL, &newDataLen); 
	  	 if(rv != CI_OK)
	  	 {
	      		  printf("get plain length error. Error code is [%08x]\n",rv);
			  return rv;
		}
		rv = CI_SymDecrypt ( 1, entity2, encData, plen,newData, &newDataLen);
	   	if(rv != CI_OK)
	   	{
	        printf("SymDecrypt error. Error code is [%08x]\n",rv);
	        return rv;
		}
		CI_DeviceFinal();
		 tcpsocket.Close();
#endif
	}
	else
	{
        tcpsocket.Close();
	}
	
        writelog(LOG_INFO,"trans RespCode[%s]",tran.head.RespCode);
	if(strncmp(tran.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,tran.head.RespMess,34);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // 银行端处理错误
		return ret;
	}
	else
	{
	
	if ((plen-headlen)>0)
		{
#ifdef  _CI_DEGUG_DES_ 
             memcpy(&tran.body,newData,sizeof(newData));
#else
             memcpy(&tran.body,buf,sizeof(buf));
#endif
		}	
		out_pack->lvol1 = 1;	
		out_pack->damt1=atof(tran.body.OldRopAmt);		
		memcpy(out_pack->scust_auth2,tran.head.RespMess,sizeof out_pack->scust_auth2 );		
		memcpy(out_pack->sdate0,tran.body.OldTxdate,sizeof out_pack->sdate0 );						// 银行流水号
		memcpy(out_pack->scust_limit2,tran.body.OldTransBankId,sizeof out_pack->scust_limit2);	
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


int ListDown(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;
       char packlen[5]="";
	int stplen=0;
	char buf[2048]="";
	char inbody[256]="";
	char outbody[256]="";
       char len[5]="";
	  int plen=0;
	  char lenstr[6]="";
	 unsigned int		 dataLen, encDataLen,newDataLen;
	unsigned char       data[1024+16]; 
	unsigned char       encData[1024+16];
	unsigned char       newData[1024+16];
	unsigned char       entity1[12]="CA_CCBSC";
	unsigned char       entity2[12]="0009";
	dataLen=0;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间
	 char temp[512]="";

	//******************************************************************
	//包头
	//******************************************************************
	ListDown_ans head;
       ListDown_REQ tran;
	memset(&tran,0x20,sizeof tran);			// 填充空格
	memcpy(tran.head.Txcode,TRANS_CODE,6);    //交易码
	memcpy(tran.head.TxDate, rPack->sdate0,8); //交易日期
	memcpy(tran.head.TxTime,rPack->stime0,8);//交易时间
	memcpy(tran.head.TxChannel,"2021",4);//待定	
	des2src(tran.head.Operator,"system");
	des2src(tran.head.Checker,"system2");
	leftzstr(16,rPack->sholder_ac_no,temp);
	memcpy(tran.head.Serial,temp,sizeof (tran.head.Serial));//交易参考号
	memcpy(tran.head.RespCode,"E9999",5);//初始请求
	//******************************************************************
	//包体
	//******************************************************************
	des2src(tran.body.CompareDate, rPack->sdate0);    //原交易日期
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
#ifdef  _CI_DEGUG_DES_ 
        	//因加密不适合结构体，修改包头
		//包体部分，加密
	memcpy(data,tran.body.CompareDate,sizeof(tran.body.CompareDate));
       encDataLen=0;
	dataLen=sizeof(tran.body);
       CI_RV				 rv;
	rv  = CI_DeviceInit();
	if(rv  != CI_OK)
   	 {
        printf("CI_DeviceInit error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, NULL, &encDataLen);
   	 if(rv  != CI_OK)
   	 {
   	     CI_DeviceFinal();
        printf("get cipher length error. Error code is [%08x]\n",rv);
	     return rv;
	}
	rv  = CI_SymEncrypt( 1, entity1, data, dataLen, encData, &encDataLen);
   	 if(rv  != CI_OK)
    	{
    	    CI_DeviceFinal();
         printf("SymEncrypt error. Error code is [%08x]\n",rv );
         return rv;
	}
	 plen=sizeof (tran.head)+encDataLen;
#else
	 plen=sizeof (tran);
#endif
	printf((char*)&tran);
        sprintf(len,"%d",plen);
	 leftzstr(5,len,packlen);
	memcpy(buf+stplen,packlen,5);
	stplen=stplen+5;                                     //包长度                                //包长度
 	 writelog(LOG_ERR,"trans len[%d],packlen[%s]",stplen,packlen);
	memcpy(buf+stplen,tran.head.Txcode,sizeof tran.head.Txcode);
	stplen=stplen+sizeof (tran.head.Txcode);                                     //交易码
      writelog(LOG_ERR,"trans len[%d],tran.head.Txcode[%s]",stplen,tran.head.Txcode);
	memcpy(buf+stplen,tran.head.TxDate,sizeof tran.head.TxDate);
	stplen=stplen+sizeof (tran.head.TxDate);                                     //交易日期
        writelog(LOG_ERR,"trans len[%d],tran.head.TxDate[%s]",stplen,tran.head.TxDate);
	memcpy(buf+stplen,tran.head.TxTime,sizeof tran.head.TxTime);
	stplen=stplen+sizeof (tran.head.TxTime);                                     //交易时间
       writelog(LOG_ERR,"trans len[%d],tran.head.TxTime[%s]",stplen,tran.head.TxTime);
	memcpy(buf+stplen,tran.head.Operator,sizeof tran.head.Operator);
	stplen=stplen+sizeof (tran.head.Operator);                                   //操作员
       writelog(LOG_ERR,"trans len[%d],tran.head.Operator[%s]",stplen,tran.head.Operator);
	memcpy(buf+stplen,tran.head.Checker,sizeof tran.head.Checker);
	stplen=stplen+sizeof (tran.head.Checker);                                   //审核员
	writelog(LOG_ERR,"trans len[%d],tran.head.Checker[%s]",stplen,tran.head.Checker);
	memcpy(buf+stplen,tran.head.TxChannel,sizeof tran.head.TxChannel);
	stplen=stplen+sizeof (tran.head.TxChannel);                                 //校园代码
       writelog(LOG_ERR,"trans len[%d],tran.head.TxChannel[%s]",stplen,tran.head.TxChannel);
	memcpy(buf+stplen,tran.head.TxOrgNo,sizeof tran.head.TxOrgNo);
	stplen=stplen+sizeof (tran.head.TxOrgNo);                                   //交易机构
       writelog(LOG_ERR,"trans len[%d],tran.head.TxOrgNo[%s]",stplen,tran.head.TxOrgNo);
	memcpy(buf+stplen,tran.head.BankSerial,sizeof tran.head.BankSerial);
	stplen=stplen+sizeof (tran.head.BankSerial);                               //银行流水号
       writelog(LOG_ERR,"trans len[%d],tran.head.BankSerial[%s]",stplen,tran.head.BankSerial);
	memcpy(buf+stplen,tran.head.Serial,sizeof tran.head.Serial);
	stplen=stplen+sizeof (tran.head.Serial);                                      //一卡通流水号
        writelog(LOG_ERR,"trans len[%d],tran.head.Serial[%s]",stplen,tran.head.Serial);
	memcpy(buf+stplen,tran.head.FileNames,sizeof tran.head.FileNames);
	stplen=stplen+sizeof (tran.head.FileNames);                               //文件名称
	writelog(LOG_ERR,"trans len[%d],tran.head.FileNames[%s]",stplen,tran.head.FileNames);
	memcpy(buf+stplen,tran.head.RespCode,sizeof tran.head.RespCode);
	stplen=stplen+sizeof (tran.head.RespCode);                                //响应码
       writelog(LOG_ERR,"trans len[%d],tran.head.RespCode[%s]",stplen,tran.head.RespCode);
	memcpy(buf+stplen,tran.head.RespMess,sizeof tran.head.RespMess);
	stplen=stplen+sizeof (tran.head.RespMess);                                //响应信息
       writelog(LOG_ERR,"trans len[%d],tran.head.RespMess[%s]",stplen,tran.head.RespMess);
#ifdef  _CI_DEGUG_DES_ 
    	// dec2hex(encData,1040,temp);
	memcpy(buf+stplen,encData,encDataLen);
	stplen=stplen+encDataLen;
#else
	memcpy(buf+stplen,tran.body.CompareDate,sizeof(tran.body.CompareDate));
	stplen=stplen+sizeof (tran.body.CompareDate);                                //响应信息
#endif
       writelog(LOG_ERR,"trans len[%d],tran.body.CompareDate[%s]",stplen,tran.body.CompareDate);
	ret = tcpsocket.Send(buf,stplen);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}
	   memset(lenstr,0,sizeof(lenstr));
	 plen=0;
	ret = tcpsocket.Recv(lenstr,5, timeout);	
	if (strlen(lenstr)>0)
		{
         	  plen=atoi(lenstr);
		}
	else
		{
		writelog(LOG_INFO,"接收数据失败，接收长度plen[%d]",plen);
		return -1;
		}
	ret = tcpsocket.Recv((char*)&tran.head,sizeof(tran.head), timeout);
	if (plen-sizeof(tran.head))
	{
		ret = tcpsocket.Recv(buf,plen-sizeof(tran.head), timeout);	
		writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

		if (ret!=plen-sizeof(tran.head))
		{
			strcpy(szMsg,"接收银行数据错误");
			printf(szMsg);
			return ret;  
		}
#ifdef  _CI_DEGUG_DES_ 	
		memcpy(encData,buf,strlen(buf));
		rv = CI_SymDecrypt ( 1, entity2, encData, plen, NULL, &newDataLen); 
	  	 if(rv != CI_OK)
	  	 {
	  	          CI_DeviceFinal();
	      		  printf("get plain length error. Error code is [%08x]\n",rv);
			  return rv;
		}
		rv = CI_SymDecrypt ( 1, entity2, encData, plen,newData, &newDataLen);
	   	if(rv != CI_OK)
	   	{
	   	   CI_DeviceFinal();
	        printf("SymDecrypt error. Error code is [%08x]\n",rv);
	        return rv;
		}
		CI_DeviceFinal();
#endif
		tcpsocket.Close();
	}
	else
	{
	tcpsocket.Close();
	}	
	if(strncmp(tran.head.RespCode,"00000",5)!=0)
	{
		memcpy(szMsg,tran.head.RespMess,34);
		ret = E_TRANS_BANK_RECVERR;
		return printf(szMsg);;  // 银行端处理错误
		return ret;
	}
	else
	{
#ifdef  _CI_DEGUG_DES_ 	
		memcpy(&tran.body,newData,sizeof (newData));
#else
             memcpy(&tran.body,buf,sizeof (buf));
#endif
		out_pack->lvol1 = 1;
	//	memcpy(out_pack->scert_no,head.head.RespMess,sizeof out_pack->scert_no);
		//memcpy(out_pack->scert_no2,head.AnsNumSuc,sizeof out_pack->scert_no2);
	//	memcpy(out_pack->snote,head.AnsNumFal,sizeof out_pack->snote);
		//memcpy(out_pack->snote2,head.RopeCntAmt,sizeof out_pack->snote2);//总金额
	}
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


