/* --------------------------------------------
 * ��������: F3002.sqc
 * ��������: 2009-03-02
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: ���ѳ�ֵ
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


//���ܷ�����֧���ַ�������Ϊ[1,16]�ļ���
int encrypt(const char * sourceStr,char * loginPwd,  int sLen, char * desStr, int dLen, char * randomStr);
	
//���ܷ�����֧�ֽ��ܺ󳤶Ȳ�����16���ַ�����
int decrypt(char * sourceStr,char * loginPwd, int sLen, char * desStr, int dLen, char * randomStr);
	

int login(CamsWebServiceSoapBinding & service, char * randomStr, bool isSecurity ,char * loginName,char * loginPwd);

int logout(CamsWebServiceSoapBinding & service);

int F3002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

//	char endpointaddr[200]="";//�Է������ַ

	long userId=0; //�ʺ�ID 
	//string userName=""; //�ʺ��� 
	//string fullName=""; //�û����� 
	int feeType=2; //�ʺ�����(2 -- Ԥ���ѣ�3 -- �󸶷�) 
	//string state="1"; //�ʺ�״̬��1 -- ������2 -- ��ͣ��3 -- ע���� 
	double curBalance=0; //�ʺŵ�ǰ��� 

		
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SALL_NAME,F_DAMT0,F_LVOL0,F_LVOL1,F_SSECTYPES,0);

	char * endpointaddr = rPack->vsvarstr0;
	char * stuempno = rPack->saddr;//ת���˺�
	char transamount[33]="";		
	sprintf(transamount,"%d",rPack->lvol1);
	strcat(transamount,".00");
	char * loginName = rPack->snote;
	char * logingPwd = rPack->snote2;
	ns2__PayParam param;



	//��ʼ��SOAPӦ��
	CamsWebServiceSoapBinding service;	
	service.endpoint =endpointaddr;


//	service.endpoint = "http://10.153.21.106/csi/services/CamsWebService";

	g_LogFile.WriteLogEx(1001,"3002 Connect to net trans  system endpointaddr[%s]",service.endpoint);	

	//����Ĳ����������õ����ʺ��û������Ǹ�userName
	//string userName = "CppClient01";
	//�������ַ���������
	char randomStr[17];
	//��ʶ�Ƿ����
	bool isSecurity = true;
	//����Ա��¼��������ݼ��
	//���ܴ�����μ�login������ʵ��
	ret = login(service, randomStr, isSecurity,loginName,logingPwd);
	//-1 ��ʾ�������˲��������Ĵ����������ݵ�����
	if(ret == -1){
		isSecurity = false;
		//���������ٴε�¼
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
