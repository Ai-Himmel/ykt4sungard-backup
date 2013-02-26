/* --------------------------------------------
 * 程序名称: F3002.sqc
 * 创建日期: 2009-03-02
 * 程序作者: 何林青
 * 版本信息: 1.0.0.0
 * 程序功能: 网费充值
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"
#include "logfile.h"
//#include "CamsWebServiceSoapBindingNsmap.h"
#include "soapCamsWebServiceSoapBindingProxy.h"

#include "des.h"
#include "base64.h"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
#ifdef __cplusplus
}
#endif


//加密方法，支持字符串长度为[1,16]的加密
int encrypt(const char * sourceStr,char * loginPwd,  int sLen, char * desStr, int dLen, char * randomStr);
	
//解密方法，支持解密后长度不超过16的字符串。
int decrypt(char * sourceStr,char * loginPwd, int sLen, char * desStr, int dLen, char * randomStr);
	

int login(CamsWebServiceSoapBinding & service, char * randomStr, bool isSecurity ,char * loginName,char * loginPwd);

int logout(CamsWebServiceSoapBinding & service);

int F3002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

//	char endpointaddr[200]="";//对方服务地址

	long userId=0; //帐号ID 
	//string userName=""; //帐号名 
	//string fullName=""; //用户姓名 
	int feeType=2; //帐号类型(2 -- 预付费；3 -- 后付费) 
	//string state="1"; //帐号状态（1 -- 正常；2 -- 暂停；3 -- 注销） 
	double curBalance=0; //帐号当前余额 

		
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SALL_NAME,F_DAMT0,F_LVOL0,F_LVOL1,F_SSECTYPES,0);

	char * endpointaddr = rPack->vsvarstr0;
	char * stuempno = rPack->saddr;//转账账号
	char transamount[33]="";		
	sprintf(transamount,"%d",rPack->lvol1);
	strcat(transamount,".00");
	char * loginName = rPack->snote;
	char * logingPwd = rPack->snote2;
	ns2__PayParam param;



	//初始化SOAP应用
	CamsWebServiceSoapBinding service;	
	service.endpoint =endpointaddr;


//	service.endpoint = "http://10.153.21.106/csi/services/CamsWebService";

	g_LogFile.WriteLogEx(1001,"3002 Connect to net trans  system endpointaddr[%s]",service.endpoint);	

	//下面的测试用例所用到的帐号用户名都是该userName
	//string userName = "CppClient01";
	//存放随机字符串的数组
	char randomStr[17];
	//标识是否加密
	bool isSecurity = true;
	//操作员登录，进行身份检查
	//加密处理请参见login方法的实现
	ret = login(service, randomStr, isSecurity,loginName,logingPwd);
	//-1 表示服务器端采用了明文传输敏感数据的配置
	if(ret == -1){
		isSecurity = false;
		//采用明文再次登录
		ret = login(service, randomStr, isSecurity,loginName,logingPwd);
		if( ret != 0){
			*pRetCode=ret;
			goto l_ret;
		}
	}
	else if(ret == -100){
		*pRetCode=ret;
		goto l_ret;
	}
	
	param.userName = stuempno;
	param.payAmount = transamount;
	g_LogFile.WriteLogEx(1001,"stuempno=[%s] TransAmout=[%s],[%d]",stuempno,transamount,strlen(transamount));	
	if(isSecurity){
		char newAmount[33];
		memset(newAmount, 0, 33);
		if(encrypt(transamount,logingPwd, strlen(transamount), newAmount, 33, randomStr) > 0){
			param.payAmount = newAmount;
		}
	}
	ns37__payResponse response;
	ret = service.ns37__pay(&param, response);
	if(ret == SOAP_OK){
		ret = response._payReturn->errorCode;
		if(ret == 0){
			g_LogFile.WriteLogEx(1001,"userName:[%s] pay successfully payment [%s]",stuempno,transamount);	

		}
		else{
			g_LogFile.WriteLogEx(1001,"return error code:[%d],return error:[%s]",ret,response._payReturn->errorMsg);	
			*pRetCode=ret;
			goto l_ret;
		}		
	}
	else{
		soap_print_fault(service.soap, stderr);		
	}


	logout(service);

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	logout(service);
	return -1;
}
