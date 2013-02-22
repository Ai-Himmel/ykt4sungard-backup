
#include "stdafx.h"
#include "Application.h"

//*=================================================================================
//*ԭ��: long ReadSmartDocInfo(void **pSmartDoc, long *nDocCount);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      lpKeyBuffer, ��Ȩ�ַ���(����)
//*      dwFlag, ҵ���ܵı�־
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*====================================================================================
extern "C" long __stdcall ReadSmartDocInfo(TSSmartDoc **pSmartDoc, long *nDocCount)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.ReadSmartDoc(pSmartDoc, nDocCount);
}


//*=================================================================================
//*ԭ��: long ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
//*����: �ͷ��豸������Ϣ
//*����: 
//*      pSmartDoc -- �豸�����ڴ�
//*����: 
//*      =  RET_OK:  �ɹ�
//*      <> RET_OK:  ʧ��
//*====================================================================================
extern "C" long __stdcall ReleaseSmartDoc(TSSmartDoc *pSmartDoc)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.ReleaseSmartDoc(pSmartDoc);
}

//*=================================================================================
//*ԭ��: long InitModule(TSSmartFixInfo *pSmartFixInfo, long *nFlag);
//*����: ��ʼ��ҵ����ģ��, ��װ������/��ʼ������
//*����: 
//*      pFunction, �����������API��ַ
//*      nFlag, ҵ���ܵı�־
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall InitModuleDLL(TSSmartFunction *pFunction, TSSmartSupport *pSupport)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0248");

	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "01");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "02");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "03");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "09");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "12");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "16");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "18");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "70");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "71");	
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "72");	
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "73");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "74");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "75");

	return theApp.ImportFunc(pFunction);
}

//*=================================================================================
//*����: ���ҵ����ģ��, �˳�DLLʱ����
//*����: 
//*      ��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall DestoryModuleDLL()
{
	return RET_OK;
}

//*=================================================================================
//*����: ������һ������ʱ����, ��ʱ����������������
//*����: 
//*       pSmartDoc:     �ն���Ϣ
//*       pDocArray:     �ն˼�������
//*       nArrayLength:  ��������
//*       pSmartBuffer:  ���ص���Ϣ
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.CreateTaskBuffer(pDocEx, pTask, pBuffer);
}

//*=================================================================================
//*����: ���ն˽������ݺ�Ĵ���(ʵ�ֽ��, ����SQL��)
//*����: 
//*      �������˵��
//*����: 
//*      RET_OK:  ��ʼ���ɹ�
//*      RET_NG:  ��ʼ��ʧ��
//*=================================================================================
extern "C" long __stdcall SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer)
{ 
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return theApp.SmartTaskProcess(pDocEx, pTask, pBuffer);
}

extern "C" long __stdcall DLLSupportInfo(TSSmartSupport *pSupport)
{
    pSupport->nMacCount = 0 ;
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5301");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0201");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0226");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0228");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0230");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0232");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0234");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0240");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0130");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0140");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0121");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0224");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0236");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1055");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "5501");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "1056");
	strcpy(pSupport->MacType[pSupport->nMacCount++], "0248");
	
	pSupport->nTaskCount = 0 ;
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "01");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "02");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "09");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "12");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "16");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "18");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "70");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "71");
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "72");//���������汾�´�
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "73");//���������������´�����
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "74");//����
	strcpy(pSupport->TaskCode[pSupport->nTaskCount++], "75");//�豸״̬���
	return RET_OK;
}
