// 下列 ifdef 块是创建使从 DLL 导出更简单的
//宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ADVANSTA_EXPORTS
// 符号编译的。在使用此 DLL 的
//任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将 
// ADVANSTA_API 函数视为是从此 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。

#include "Pubdef.h"

#ifdef ADVANSTA_EXPORTS
#define ADVANSTA_API __declspec(dllexport)
#else
#define ADVANSTA_API __declspec(dllimport)
#endif

#ifndef EXTER_C
#define EXTERN_C    extern "C"
//#define EXTERN_C
#endif

//======================================================================================================
// 接口名称：	ConfigParamters
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	char *	lpAddrServer			// 服务器IP地址，以0结尾的字符串
//				int		nPortHost				// Socket通讯端口		
//												// 交易记录和相关配置文件的目录
//												// 以0结尾的字符串
//				char *	lpDeviceID				// 商户ID，16进制字符串,以0结尾
//				char * lpEplink_AddrServer		// E票联服务期IP
//				int nEplink_PortHost			// E票联服务期Socket端口	
// 功    能：									// 保存传入的参数，并判断合法性
//												// 申请资源
// 调用说明：									// 加载该DLL后第一个调用的函数，
//												// 如果调用失败，应终止后续操作				
//======================================================================================================
EXTERN_C int ADVANSTA_API ConfigParamters(char * lpAddrServer, int nPortHost,					// 普通钱包服务器地址
								 char * lpCommTickAddrServer, int nCTPortHost,			// 月票钱包服务器地址
								 char * lpEplink_AddrServer, int nEplink_HostPort,		// 易票联后台服务器地址
								 char * lpDeviceID);



//======================================================================================================
// 接口名称：	Common_Initialize_RW
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	int				nPort			// 通讯端口
//				int				Baud			// 通讯波特率
//				int				nSamSlot		// PSAM卡槽，SAM1\SAM2
//				char *			lpPKIPin		// PKI卡pin码
//				LPBYTE			lpInitKey		// 初始键值
//              int             hdVersion       // 硬件版本,用于区分不同厂家的读写器
//				char *			ServCode		// 设置服务商代码(2byte,BCD码)
//              int             Only            // 功能选择
// 功    能：									// 初始化通讯端口，申请资源
// 调用说明：									// 紧接着ConfigParamters后调用，
//												// 如果调用失败，应终止后续操作				
//======================================================================================================
EXTERN_C int ADVANSTA_API Common_Initialize_RW(const int nPort, int Baud, int nSamSlot, char * lpPKIPin, LPBYTE lpInitKey, int hdVersion, char * SvrCode, int Only);
//EXTERN_C int ADVANSTA_API Common_Initialize_RW(const int nPort, int Baud, int nSamSlot, char * lpPKIPin, LPBYTE lpInitKey, int hdVersion, char * SvrCode, int Only, HANDLE Comm = 0);



//======================================================================================================
// 接口名称：	Common_Destroy_RW
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	int		nPort					// 通讯端口
// 功    能：									// 关闭通讯端口，释放资源
// 调用说明：									// 卸载DLL前的操作		
//======================================================================================================
EXTERN_C int ADVANSTA_API Common_Destroy_RW(const int nPort);



//======================================================================================================
// 接口名称：	QueryBalance
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	int			nPort				// 通讯端口
//				PPURCHSEARCH preqPurchase		// 消费查询结构
// 功    能：									// 查询余额并在POS上显示
// 调用说明：									// 随机
//======================================================================================================
EXTERN_C int ADVANSTA_API QueryBalance(const int nPort,PPURCHSEARCH pPurSearch);



//======================================================================================================
// 接口名称：	Consumption
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	int			nPort				// 通讯端口
//				DWORD		dwValue				// 消费金额
// 功    能：									// 消费，并在终端形成消费记录
//												// 并在POS上显示相关信息
// 调用说明：									// 随机
//======================================================================================================
EXTERN_C int ADVANSTA_API Consumption(const int nPort, const DWORD dwValue, PPURCHPREPARE ppurPrepare);

//======================================================================================================
// 接口名称：	CashIncrease
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	int			nPort				// 通讯端口
//				DWORD		dwValue				// 充值金额
//              PPURCHASEINCREASE pIncrease     // 充值数据接口
//              BOOL bMustCmp                   // 是否必须完成未完整流程
// 功    能：									// 充值，并完成未完整流程
//												// 并在POS上显示相关信息
// 调用说明：									// 随机
//======================================================================================================
EXTERN_C int ADVANSTA_API CashIncrease(const int nPort, const DWORD dwValue, PPURCHASEINCREASE pIncrease, BOOL bMustCmp);


//======================================================================================================
// 接口名称：	GetAPIVersion
// 返回类型：	int								// 0－成功，
//												// 非0－失败
// 参数说明：	char *Version					// 返回的版本号 VX.XX
// 功    能：									// 获取API版本号
// 调用说明：									// 随机
//======================================================================================================
EXTERN_C int ADVANSTA_API GetAPIVersion(char *Version);


//======================================================================================================
// 接口名称：	CommutationTicket_SignIn
// 返回类型：	int										// 0－成功，
//														// 非0－失败
// 参数说明：	const int nPort							// 通讯端口
//				pCommTicket_SignIn_Info_t pSignInInfo	// 签到信息
// 功    能：											// 月票充值前签到
// 调用说明：											// 调用月票充值功能之前调用
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_SignIn(const int nPort, pCommTicket_SignIn_Info_t pSignInInfo);

//======================================================================================================
// 接口名称：	CommutationTicket_Query
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	const int nPort								// 通讯端口
//				const char OperaType
//				pCommTicket_Increase_t pCommTickParam
//				pCommTicket_Info_t pCommTickInfo
// 功    能：												// 月票充值\撤销查询
// 调用说明：												// 调用CommutationTicket_SignIn成功后调用
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Query(const int nPort, const char OperaType,
												pCommTicket_Increase_t pCommTickParam, 
												pCommTicket_Info_t pCommTickInfo);

//======================================================================================================
// 接口名称：	CommutationTicket_Increase
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	const int nPort								// 通讯端口
//				const char OperaType
//				pCommTicket_Increase_t pCommTickParam
//				pCommTicket_Info_t pCommTickInfo
// 功    能：												// 月票充值
// 调用说明：												// 调用CommutationTicket_Query成功后调用
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Increase(const int nPort,
												pCommTicket_Info_t pCommTickInfo, 
												pCommTicket_Charge_Info pCommTickChargeInfo);

//======================================================================================================
// 接口名称：	CommutationTicket_Rcharge
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	const int nPort								// 通讯端口
//				const char OperaType
//				char *pSysCounts
// 功    能：	充值冲正/撤销冲正
// 调用说明：												// 
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Rcharge(const int nPort, 
												const char OperaType, 
												char *pSysCounts);

// 
//======================================================================================================
// 接口名称：	CommutationTicket_ReadInfo_offline
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	const int nPort								// 通讯端口
//				char *pDealCounts
//				pCommTicket_ReadInfo_Offline_t pCommTickInfo
// 功    能：	脱机查询月票
// 调用说明：												// 随时
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_ReadInfo_offline(const int nPort, 
														char *pDealCounts, 
														pCommTicket_ReadInfo_Offline_t pCommTickInfo);


// 
//======================================================================================================
// 接口名称：	CommutationTicket_ReadInfo_online
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	const int nPort								// 通讯端口
//				char Rdtype									// 查询类型
//				char *pKey									// 会话密钥
//				pCommTicket_Online_Info_t pInfo				// 返回查询信息
// 功    能：	联机查询月票
// 调用说明：												// 随时
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_ReadInfo_online(const int nPort, char Rdtype, char *pKey, pCommTicket_Online_Info_t pInfo);

// 
//======================================================================================================
// 接口名称：	CommutationTicket_Epaylinks_Deduction
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	pCommTicket_Info_t pCommTickInfo			// 充值申请信息
//				char *pcEpalinkSysNo						// 返回的易票联帐号流水
// 功    能：	易票联帐户扣费
// 调用说明：												// 随时
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Epaylinks_Deduction(pCommTicket_Info_t pCommTickInfo,
																char *pcEpalinkSysNo);
//
//======================================================================================================
// 接口名称：	CommutationTicket_Epaylinks_Back
// 返回类型：	int											// 0－成功，
//															// 非0－失败
// 参数说明：	char *pcEpalinkSysNo						// 需要冲正的易票联帐号流水
// 功    能：	易票联帐户冲正
// 调用说明：												// 随时
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Epaylinks_Back(char *pcEpalinkSysNo);

//#pragma comment(lib, "AdvanSta.lib")
