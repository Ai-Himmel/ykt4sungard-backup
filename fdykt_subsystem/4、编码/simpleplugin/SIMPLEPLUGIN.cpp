// SIMPLEPLUGIN.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "XMLFile.h"	// 必须在此 include,顺序不能颠倒
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
// 功能函数
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
//// 用户编写代码部分
/** 
* @brief 模块初始化函数，该函数只会在模块被加载的第一次被调用
* 
* @return - 成功返回 0 ， 否则返回 -1
*/
static int CALLBACK_API module_init()
{
	// TODO : 完成初始化的代码
	AfxMessageBox("初始化");
	return 0;
}

/** 
* @brief 模块释放函数，该函数只会在模块被释放时调用。
* 
* @return - 成功返回 0 ，否则返回 -1
*/
static int CALLBACK_API module_release()
{
	// TODO : 完成释放的代码
	AfxMessageBox("释放");
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
		
		// 保存名单信息
		if(!strncmp(pNode->nodeName,KP_CARD,sizeof(KP_CARD)))
		{
			// save into text
			// 取得卡 ID 号
			string value;
			if(ksf_get_node_param_value(pNode,KP_CARD_ID,value) == 0)
				AfxMessageBox(value.c_str());
		}
		// 下一个结点
		pNode = pNode->GetnextSibling();
	}
	*/
	AfxMessageBox(data->data);
	// 必须指明处理结果。常量定义见 def.h 文件
	ret->ret = RET_OK;
	return 0;
}

/** 
* @brief 功能函数对应关系数组
*/
static ksf_do_receive_func recv_funcs[] =
{
    /* 功能号 ， 对应处理函数 */
	{400000,do_receive_blk},			// 接收黑白名单
	{400002,do_receive_blk},			// 接收增加客户名单
	{-1,NULL}						// 结束标志,必须保留
};




//////////////////////////////////////////////////////////////////////////
// 接口   　********  以下函数不需要修改
/** 
* @brief 每次收取数据时会调用该函数
* 
* @param svr_conf - 服务器的配置
* @param data - 数据包
* @param ret - 返回结果集
* 
* @return - 成功返回 0 ， 否则返回 -1
*/
static int CALLBACK_API module_receive(ksf_server_conf * svr_conf,ksf_xml_data * data,
						  ksf_card_result * ret)
{
	int i = 0;
	LPDoReceiveFunc lpFunc = NULL;
	while( recv_funcs[i].func_no != -1)
	{
		// 找到对应的功能号
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
					// 调用出错直接返回 
					return -2;
				}
			}
		}
		++i;
	}
    return -1;
}

/** 
* @brief 模块信息定义
*/
ksf_plugin_module plugin_module = 
{
	"测试模块",			// 模块名称，模块名称
	"simplemodule",					// 模块路径，可以为空
	"20050629"	  ,					// 发行日期，格式为 yyyyMMdd
	"汤成",							// 发行人，
	1,1,						// 主版本号、次版本号
	module_init,						// 模块初始化函数指针
	module_release,					// 模块释放函数指针
	module_receive	// 模块主功能函数，用与保存数据
};

/** 
* @brief DLL 入口函数，用于注册模块
* 
* @param module - 模块结构
* 
* @return - 成功返回 0 ，否则返回 -1
*/
int WINAPI registe_module(ksf_plugin_module * module)
{
	sizeof(ksf_plugin_module);
	memcpy(module,&plugin_module,sizeof(ksf_plugin_module));
	return 0;
}
/** 
* @brief - DLL 入口函数，用于删除模块
* 
* @param module - 模块结构
* 
* @return - 成功返回 0，否则返回 -1
*/
int WINAPI unregiste_module(ksf_plugin_module * module)
{
	return 0;
}
