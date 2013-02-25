// VCInter.cpp : Defines the initialization routines for the DLL.
//

/*	修改记录

  20031217 dengcb: 增加69#-客户属性查询
  20040405 dengcb: 65#(客户退出)输入增加委托方式的赋值,
  因为switch在退出时会清空默认的bank_code2赋值
*/

#include "stdafx.h"
#include <afxdllx.h>
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////////////
//  我们所要加的文件内容：
#define SPXDLL_EXPORTS	    // 在功能模块编写开始就要加上这个定义
#include "SpxDllInfo.h"
#include "cpackc.h"

__declspec(dllimport) int GetZxjByScdmZqdm(char *scdm, char *zqdm, char *zxj, double &zxj2);

////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE VCInterDLL = { NULL, NULL };
double  ChangeDouble(double * pd,int len);
int GetInteger(const char * str);
void ChangeIdFromPhone(char *PhoneId, char sAccountsId[20]);
void ChangeIdFromPhone2(char *PhoneId, char sAccountsId[20]);

extern char *ltrim(char *str);
extern char *rtrim(char *str);
extern char *trim(char *str);

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);
	
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("VCInter.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(VCInterDLL, hInstance))
			return 0;
		
		new CDynLinkLibrary(VCInterDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("VCInter.DLL Terminating!\n");
		AfxTermExtensionModule(VCInterDLL);
	}
	return 1;   // ok
}

// 生成 CPack 包
BOOL CommFormPackFunc(int nFunction, char *buffer, CSList *plist, void *pvoid, int DestNO)
{
	ST_CPACK_C *pstpack=(ST_CPACK_C *)pvoid;
	//memset(&(pstpack->pack),0,sizeof(ST_PACKDATA_C));
	char sOldAppendPwd1[9]="", sOldAppendPwd2[9]="";
	char sNewAppendPwd1[9]="", sNewAppendPwd2[9]="";
	char sAccountsId[22] = "";						// 转换以后的帐号
	int  iLen=0;
	int tmp = 0;
	switch(nFunction) 
	{	
	case 11://交易明细查询	847184
		/*
		1.	功能号：11
		2.	发起地址
		3.	保留
		4.	暂时不用（填空）
		5.	卡号
		6.	货币代码
		7.	起始日期
		8.	终止日期
		9.	索引流水号
		10.	最多返回数量 - 10条
		11.	委托方式
		*/
		tmp = GetInteger(plist->GetAt(7));
		AddFieldI_C(pstpack, F_LVOL0, tmp);		// 卡号
		AddField_C(pstpack, F_SDATE0, plist->GetAt(9));		// 起始日期
		AddField_C(pstpack, F_SDATE1, plist->GetAt(10));	// 结束日期
		tmp = GetInteger(plist->GetAt(12));
		AddFieldI_C(pstpack, F_LVOL1, tmp);		// 查询返回记录数
		return TRUE;
	case 12: // 挂失卡  847102
		 /*
		 1.	功能号：12
		 2.	发起地址
		 3.	保留
		 4.	暂时不用（填空）
		 5.	卡号
		 6.	密码
		 7. 客户号
		 8.	委托方式
		*/
		// TODO : 修改挂失的限制
		tmp = GetInteger(plist->GetAt(7));
		AddFieldI_C(pstpack, F_LVOL1, tmp);	// 卡号
		AddField_C(pstpack, F_SCUST_LIMIT, "system");
		return TRUE;
	case 9:		//查询余额  700001
		/*
		*  1. 功能号 9 
		*  2. 发起地址
		*  3. 货币代码(不用)
		*  4. 不用
		*  5. 卡号
		*  6. 委托方式
		*/
		tmp = GetInteger(plist->GetAt(7));
        AddFieldI_C(pstpack, F_LVOL3, tmp);	// 卡号
		return TRUE;
	case 901:	//用户登录 700000
		//////////////////////////////////////////////////////////////////////////
		// 测试
		//AfxMessageBox(plist->GetAt(7));						
		//////////////////////////////////////////////////////////////////////////
		ChangeIdFromPhone2(plist->GetAt(7), sAccountsId);	// 转换帐号，从数字转字母, 通用设置
		AddField_C(pstpack, F_SSTATUS0, plist->GetAt(5));	// 账号类别
//		AddField_C(pstpack, F_SCUST_NO, plist->GetAt(7));	// 客户号
//		AddField_C(pstpack, F_SNAME, sAccountsId);			// 账号, 云南大学用
		AddField_C(pstpack, F_SCUST_AUTH, sAccountsId);		// 2008主干用
//		AfxMessageBox(sAccountsId);
		//AddField_C(pstpack, F_LVOL0, plist->GetAt(7));	// 卡号
		AddField_C(pstpack, F_SBANK_PWD, plist->GetAt(8));	// 密码
		return TRUE;
	}
	return FALSE;
}

// 分解 CPack 包成 SPX 协议
BOOL CommFormStrFunc(int nFunction, char *buffer, CSList *plist, void *pvoid, bool bFirstRow)
{
	// buffer 大小为 4k 
   	ST_CPACK_C *pstpack=(ST_CPACK_C *)pvoid;
	switch(nFunction) {
	case 9:		//余额查询
		sprintf(buffer, "A|%s|%s|%s|%.2f|%.2f|%s|%.2f|", plist->GetAt(1), plist->GetAt(2),
			"Y",					// 成功标志
			pstpack->pack.damt0,	// 总余额
			pstpack->pack.damt1,	// 可用余额
			"RMB",					// 货币名称
			pstpack->pack.damt2		// 冻结余额
			);
		return TRUE;
	case 11:// 交易明细查询	 847180
		sprintf(buffer,"A|%s|%s|%s|%d|%s|%.2f|%.2f|%s|%d|%d|%s|",plist->GetAt(1),plist->GetAt(2)
			,pstpack->pack.sdate0					// 交易日期
			,pstpack->pack.lvol0					// 交易类别
			,pstpack->pack.scusttypes				// 交易说明
			,pstpack->pack.damt0					// 交易金额
			,pstpack->pack.damt1					// 交易后余额
			,pstpack->pack.sbankname2				// 交易地点
			,pstpack->pack.lvol1					// 流水号
			,1										// 货币代码
			,"RMB"									// 货币名称
			);
		//sprintf(buffer,"%s|%s|%s|",plist->GetAt(1),plist->GetAt(2),"Y");
		return TRUE;
	case 12: // 卡挂失
		sprintf(buffer,"A|%s|%s|%s|",plist->GetAt(1),plist->GetAt(2)
			,"Y"									// 成功标志
			);
		return TRUE;
	case 901:	//用户登录
		sprintf(buffer,"A|%s|%s|%s|%s|%d|%s|%d|%d|%s|%s|%s|%s|%s|%d|%s|",plist->GetAt(1),plist->GetAt(2)
			,"Y"										// 成功标志
			,pstpack->pack.scusttypes					// 姓名
			,pstpack->pack.lvol2						// 账号类别
			,pstpack->pack.sbank_acc					// 原输入的完整帐号代码
			,1											// 货币代码
			,pstpack->pack.lvol0						// 卡号
			,pstpack->pack.scert_addr					// 保留
			,pstpack->pack.sbankname					// 部门班级名称
			,pstpack->pack.sdate0						// 系统工作日期
			,pstpack->pack.sstatus1						// 系统工作状态
			,pstpack->pack.sbankname2					// 系统工作状态名称
			,pstpack->pack.lvol1						// 客户号
			,pstpack->pack.scust_auth					// 学号
			);
		return TRUE;
	}
	return FALSE;
}

BOOL InitFunc(char *IniFileName)
{
	return TRUE;
}

BOOL ExitFunc(void)
{
	return TRUE;
}

DLLFUNCENTRY  DllFunctions[]={
	// { 5, "修改密码", 847111, 1, NULL, NULL},			// del 
	{ 9, "余额查询", 700001, 1, NULL, NULL},			// ok
	{ 11, "交易明细", 700002, 2, NULL, NULL},			// ok
	{ 12, "挂失", 847102, 1, NULL, NULL},				// test
	{ 901, "登录", 700000, 1, NULL, NULL},				// dev
};

DLLINFO  stDllInfo={
		4,
		DllFunctions,
		InitFunc,
		ExitFunc,
		CommFormPackFunc,
		CommFormStrFunc,
		9,901,
		"VCInter", // 表示是大集中柜台
		100,
		200505015,
		"汤成"
};

SPXDLL_API DLLINFO *GetDllInfo(void)
{
	return (&stDllInfo);
}


/* ------------------------------------------------------------------------- */
/*     四舍五入，保留两位有效位     */
double  ChangeDouble(double * pd,int len)

{
	double d=0.00,d2=0.00;
	d = *pd;
	d2 =floor(d*100);
	if ( (d*100 - d2) >=0.5 )
		*pd=ceil(d*100)/100;
	else
		*pd =floor(d*100)/100;
	return  *pd;
}

int GetInteger(const char * str)
{
	int ret = atoi(str);
	return ret;
}
//////////////////////////////////////////////////

char PhoIdToAccId[8][8] = 
{
		'A', 'B', 'C', 'a', 'b', 'c', '$', '$',
		'D', 'E', 'F', 'd', 'e', 'f', '$', '$',
		'G', 'H', 'I', 'g', 'h', 'i', '$', '$',
		'J', 'K', 'L', 'j', 'k', 'l', '$', '$',
		'M', 'N', 'O', 'm', 'n', 'o', '$', '$',
		'P', 'Q', 'R', 'S', 'p', 'q', 'r', 's',
		'T', 'U', 'V', 't', 'u', 'v', '$', '$',
		'W', 'X', 'Y', 'Z', 'w', 'x', 'y', 'z'
};		// $符号是没有这个数据

void ChangeIdFromPhone2(char *pcPhoneId, char sAccountsId[22])
{
	char *pcPosition = NULL;
	int nCountForAccounts = 0;
	int nRow = 0,
		nCol = 0;

	while (*pcPhoneId != '\0')
	{
		if (*pcPhoneId != '*')
		{
			pcPosition = pcPhoneId;		// 初始位置
			sAccountsId[nCountForAccounts] = *pcPosition;		// 没有不规则号码
		}
		else	// * + row + col存在不规则号码 *23 == C *26 == c ...........
		{
			pcPosition = ++pcPhoneId;
			if (*pcPosition != '\0' && *(++pcPhoneId) != '\0')	// *后面的2位不是'\0'
			{
				nRow = *pcPosition - 0x30;
				nCol = *pcPhoneId - 0x30;
				sAccountsId[nCountForAccounts] = PhoIdToAccId[nRow - 2][nCol - 1];	// 行-2, 列-1
			}
			else
			{
				sAccountsId[nCountForAccounts] = '$';
			}
		}
		pcPosition = ++pcPhoneId;
		nCountForAccounts++;
	}
	// 业务需要, 最后一个字符带个'#'
	if ('#' == *(--pcPosition))
	{
		sAccountsId[--nCountForAccounts] = '\0';
	}
	return ;
}

















