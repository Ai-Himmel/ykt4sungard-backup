/* --------------------------------------------
 * 程序名称: F3001.sqc
 * 创建日期: 2009-03-02
 * 程序作者: 何林青
 * 版本信息: 1.0.0.0
 * 程序功能: 网络转账查询帐户合法性
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
#include "CamsWebServiceSoapBinding.nsmap"
#include "soapCamsWebServiceSoapBindingProxy.h"
#include <string>
#include "des.h"
#include "base64.h"



#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;
#ifdef __cplusplus
}
#endif


//加密方法，支持字符串长度为[1,16]的加密
int encrypt(const char * sourceStr,char * loginPwd, int sLen, char * desStr, int dLen, char * randomStr){
	symmetric_key des;
	unsigned char expertKey[16];
	memset(expertKey, 0, 16);
	memcpy(expertKey, loginPwd, strlen(loginPwd));
	expertKey[15] = '\0';

	if (des_setup(expertKey, &des) != CRYPT_OK)
	{
		std::cout << "des_setup() error!" << std::endl;
		return -1;
	}
	else{
		unsigned char sourceStrCopy[17];
		memset(sourceStrCopy, 0, 17);
		memcpy(sourceStrCopy, sourceStr, sLen);
		for(int i = 0; i < sLen; i++){
			sourceStrCopy[i] ^= randomStr[i];
		}
		unsigned char curStr[32];
		memset(curStr, 0, 32);
		int outLen = des_encrypt(sourceStrCopy, sLen, curStr, 32, &des);
		if (outLen > 0)
		{
			std::cout << "encrypt password:" << curStr << std::endl;
			if(base64_encode(curStr, outLen, desStr, dLen) == 1){
				return outLen;
			}
			else{
				std::cout << "base64_encode() error!"<< std::endl;
				return 0;
			}			
		}
		else{
			std::cout << "encrypt error" << curStr << std::endl;
			return 0;
		}
		
	}
}
//解密方法，支持解密后长度不超过16的字符串。
int decrypt(char * sourceStr,char * loginPwd, int sLen, char * desStr, int dLen, char * randomStr){
	symmetric_key des;
	unsigned char expertKey[16];
	memset(expertKey, 0, 16);
	memcpy(expertKey, loginPwd, strlen(loginPwd));
	expertKey[15] = '\0';

	if (des_setup(expertKey, &des) != CRYPT_OK)
	{
		std::cout << "des_setup() error!" << std::endl;
		return -1;
	}
	else{
		unsigned char sourceStrCopy[25];
		memset(sourceStrCopy, 0, 25);
		base64_decode(sourceStr, sourceStrCopy, 25);

		unsigned char curStr[25];
		memset(curStr, 0, 25);
		int outLen = des_decrypt(sourceStrCopy, 24, curStr, 24, &des);
		if (outLen > 0)
		{	
			for(int i = 0; i < dLen; i++){
				desStr[i] = curStr[i] ^ randomStr[i];
			}
			return outLen;
		}
		else{
			return 0;
		}
		
	}
}

int login(CamsWebServiceSoapBinding & service, char * randomStr, bool isSecurity ,char * loginName,char * loginPwd){
	int ret = SOAP_OK;
	ns37__randomReqResponse randomResponse;
	g_LogFile.WriteLogEx(1001, "here goes loginName=[%s],password=[%s]",loginName,loginPwd);		
	if(isSecurity){
		//invoke the method "randomReq"
		ret = service.ns37__randomReq(randomResponse);
		if(ret == SOAP_OK){
			if(randomResponse.randomReqReturn){
				//print the random string
				g_LogFile.WriteLogEx(1001, "The method 'randomReq' return:[%s]",randomResponse.randomReqReturn->random);		
			}
			else{
				return -1;//do not need to invoke the randomReq method
			}
		}
		else{
			soap_print_fault(service.soap, stderr);
			ret = -100;
			return ret;
		}
	}	
	
	if ( ret == SOAP_OK){	
		//init the parameter of the method "login"
		ns23__OperatorInfo operatorInfo;
		operatorInfo.name = loginName;
		//from the line to invoking the method "login",
		//encrypt the password and Base64 encode it.			
		if(isSecurity){
			memcpy(randomStr, randomResponse.randomReqReturn->random, 16);
			randomStr[16] = '\0';
			
			char newPassword[33];
			memset(newPassword, 0, 33);
			if(encrypt(loginPwd,loginPwd, strlen(loginPwd), newPassword, 33, randomStr) > 0){
				operatorInfo.password = newPassword;

			}
			else{
				return -2; //have the error when encrypt the password
			}
		}
		else{
			operatorInfo.password = loginPwd;
		}
		ns37__loginResponse loginResponse;
		ret = service.ns37__login(&operatorInfo, loginResponse);
		if(ret == SOAP_OK){
			ret = loginResponse._loginReturn->errorCode;
			if(ret != 0){
				g_LogFile.WriteLogEx(1001,"return error code[%d] error[%s]",ret,loginResponse._loginReturn->errorMsg);	
			}
			else{
				g_LogFile.WriteLogEx(1001,"userName[%s]  login success",loginName);	
			}
		}
		else{
			soap_print_fault(service.soap, stderr);
			ret = -100;
		}
	}		
	return ret;
}

int logout(CamsWebServiceSoapBinding & service){
	std::cout << "The method 'logout'..."<< std::endl;

	ns37__logoutResponse response;
	int ret = service.ns37__logout(response);
	if(ret == SOAP_OK){
		ret = response.logoutReturn->errorCode;
		if(ret == 0){
			g_LogFile.WriteLogEx(1001,"logout successfully");	
		}
		else{
			g_LogFile.WriteLogEx(1001,"return error code[%d] error[%s]",ret, response.logoutReturn->errorMsg);	
		}		
	}
	else{
		soap_print_fault(service.soap, stderr);		
	}
	return ret;
}

int F3001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

//	char endpointaddr[200]="";//对方服务地址

	long userId=0; //帐号ID 
	std::string userName=""; //帐号名 
	std::string fullName=""; //用户姓名 
	int feeType=2; //帐号类型(2 -- 预付费；3 -- 后付费) 
	std::string state="1"; //帐号状态（1 -- 正常；2 -- 暂停；3 -- 注销） 
	double curBalance=0; //帐号当前余额 

		
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SALL_NAME,F_DAMT0,F_LVOL0,F_LVOL1,F_SSECTYPES,0);

	char * endpointaddr = rPack->vsvarstr0;
	char * stuempno = rPack->saddr;//转账账号
	char * loginName = rPack->snote;
	char * logingPwd = rPack->snote2;




	//初始化SOAP应用
	CamsWebServiceSoapBinding service;	
	service.endpoint =endpointaddr;


//	service.endpoint = "http://10.153.21.106/csi/services/CamsWebService";

	g_LogFile.WriteLogEx(1001,"Connect to net trans  system endpointaddr[%s]",service.endpoint);	

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

	ns37__queryAcctByNameResponse response;
	ret = service.ns37__queryAcctByName(stuempno, response);
	if(ret == SOAP_OK){
		ret = response._queryAcctByNameReturn->errorCode;
		if(ret == 0){
			g_LogFile.WriteLogEx(1001,"query the user successfully,Full Name:[%s],Balance:[%.2lf]",response._queryAcctByNameReturn->fullName, *(response._queryAcctByNameReturn->curBalance));	
			fullName = response._queryAcctByNameReturn->fullName;
			curBalance = *(response._queryAcctByNameReturn->curBalance);
			feeType =  *(response._queryAcctByNameReturn->feeType);
			state = response._queryAcctByNameReturn->state;
			strcpy(out_pack->sall_name,fullName.c_str());
			out_pack->damt0=curBalance;
			out_pack->lvol0=feeType;
			out_pack->lvol1=atol(state.c_str());
		}
		else{
			g_LogFile.WriteLogEx(1001,"return error code[%d] error[%s]",ret,response._queryAcctByNameReturn->errorMsg);	
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
