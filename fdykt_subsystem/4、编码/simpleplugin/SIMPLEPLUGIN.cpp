// SIMPLEPLUGIN.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "XMLFile.h"	// �����ڴ� include,˳���ܵߵ�
#include <string>
#include "SIMPLEPLUGIN.h"
#include "ksf_pack.h"
#include "../include/def.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using std::string;

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEPLUGINApp

BEGIN_MESSAGE_MAP(CSIMPLEPLUGINApp, CWinApp)
//{{AFX_MSG_MAP(CSIMPLEPLUGINApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSIMPLEPLUGINApp construction

CSIMPLEPLUGINApp::CSIMPLEPLUGINApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSIMPLEPLUGINApp object

CSIMPLEPLUGINApp theApp;
//////////////////////////////////////////////////////////////////////////
// ���ܺ���
int ksf_get_node_param_value(MSXML2::IXMLDOMNodePtr & pNode,
							const string & param,string & value)
{
	MSXML2::IXMLDOMNodePtr child = NULL;
	child = pNode->GetfirstChild();
	while (child!= NULL)
	{
		if(!strcmp(child->nodeName,param.c_str()))
		{
			value = string(child->Gettext());
			return 0;
		}
		child = child->GetnextSibling();
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
//// �û���д���벿��
/** 
* @brief ģ���ʼ���������ú���ֻ����ģ�鱻���صĵ�һ�α�����
* 
* @return - �ɹ����� 0 �� ���򷵻� -1
*/
static int CALLBACK_API module_init()
{
	// TODO : ��ɳ�ʼ���Ĵ���
	AfxMessageBox("��ʼ��");
	return 0;
}

/** 
* @brief ģ���ͷź������ú���ֻ����ģ�鱻�ͷ�ʱ���á�
* 
* @return - �ɹ����� 0 �����򷵻� -1
*/
static int CALLBACK_API module_release()
{
	// TODO : ����ͷŵĴ���
	AfxMessageBox("�ͷ�");
	return 0;
}

static int do_receive_blk(ksf_server_conf * svr_conf,ksf_xml_data * data,
						  ksf_card_result * ret)
{
	/*
	CXMLFile xml_file;
	if(!xml_file.loadstring(data->data))
	{
		return -1;
	}
	//AfxMessageBox(data->data);
	MSXML2::IXMLDOMNodePtr pNode = NULL;
	MSXML2::IXMLDOMNodePtr pNdAttr=NULL;
	xml_file.GetNode(KP_CARD_INFO,pNode);
	if( pNode == NULL )
		return -1;
	pNode = pNode->GetfirstChild();
	while(pNode != NULL)
	{
		
		// ����������Ϣ
		if(!strncmp(pNode->nodeName,KP_CARD,sizeof(KP_CARD)))
		{
			// save into text
			// ȡ�ÿ� ID ��
			string value;
			if(ksf_get_node_param_value(pNode,KP_CARD_ID,value) == 0)
				AfxMessageBox(value.c_str());
		}
		// ��һ�����
		pNode = pNode->GetnextSibling();
	}
	*/
	AfxMessageBox(data->data);
	// ����ָ������������������� def.h �ļ�
	ret->ret = RET_OK;
	return 0;
}

/** 
* @brief ���ܺ�����Ӧ��ϵ����
*/
static ksf_do_receive_func recv_funcs[] =
{
    /* ���ܺ� �� ��Ӧ������ */
	{400000,do_receive_blk},			// ���պڰ�����
	{400002,do_receive_blk},			// �������ӿͻ�����
	{-1,NULL}						// ������־,���뱣��
};




//////////////////////////////////////////////////////////////////////////
// �ӿ�   ��********  ���º�������Ҫ�޸�
/** 
* @brief ÿ����ȡ����ʱ����øú���
* 
* @param svr_conf - ������������
* @param data - ���ݰ�
* @param ret - ���ؽ����
* 
* @return - �ɹ����� 0 �� ���򷵻� -1
*/
static int CALLBACK_API module_receive(ksf_server_conf * svr_conf,ksf_xml_data * data,
						  ksf_card_result * ret)
{
	int i = 0;
	LPDoReceiveFunc lpFunc = NULL;
	while( recv_funcs[i].func_no != -1)
	{
		// �ҵ���Ӧ�Ĺ��ܺ�
		if( recv_funcs[i].func_no == data->func_no)
		{
			lpFunc = recv_funcs[i].lpFunc;
			if(lpFunc)
			{
				try
				{
					return lpFunc(svr_conf,data,ret);
				}
				catch(...)
				{
					// ���ó���ֱ�ӷ��� 
					return -2;
				}
			}
		}
		++i;
	}
    return -1;
}

/** 
* @brief ģ����Ϣ����
*/
ksf_plugin_module plugin_module = 
{
	"����ģ��",			// ģ�����ƣ�ģ������
	"simplemodule",					// ģ��·��������Ϊ��
	"20050629"	  ,					// �������ڣ���ʽΪ yyyyMMdd
	"����",							// �����ˣ�
	1,1,						// ���汾�š��ΰ汾��
	module_init,						// ģ���ʼ������ָ��
	module_release,					// ģ���ͷź���ָ��
	module_receive	// ģ�������ܺ��������뱣������
};

/** 
* @brief DLL ��ں���������ע��ģ��
* 
* @param module - ģ��ṹ
* 
* @return - �ɹ����� 0 �����򷵻� -1
*/
int WINAPI registe_module(ksf_plugin_module * module)
{
	sizeof(ksf_plugin_module);
	memcpy(module,&plugin_module,sizeof(ksf_plugin_module));
	return 0;
}
/** 
* @brief - DLL ��ں���������ɾ��ģ��
* 
* @param module - ģ��ṹ
* 
* @return - �ɹ����� 0�����򷵻� -1
*/
int WINAPI unregiste_module(ksf_plugin_module * module)
{
	return 0;
}
