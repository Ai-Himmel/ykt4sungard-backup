#ifndef _KSG_GWDLL_H_
#define _KSG_GWDLL_H_

#ifdef __cplusplus
extern "C" {
#endif
// 注意, 数据包结构体必须字节对齐
#pragma pack(1)

typedef struct _tagCardInfo
{
	//<! 交易卡号
	int cardid;
	//<! 学工号
	char stuemp_no[21];
	//<! 姓名
	char name[41];
	//<! 物理卡号
	char phyid[9];
	//<! 显示卡号
	char cardno[11];
	//<! 单位代码
	char deptno[11];
	//<! 单位名称
	char deptname[51];
	//<! 类别代码
	int cut_type;
	//<! 类型名称
	char cut_name[51];
	//<! 性别 , 1 男 2 女 ,9 其它
	int sex;
	//<! 卡类别代码
	int card_type_id;
	//<! 卡类别名称
	char card_type_name[51];
}CardInfo_t;

typedef struct _tSerialRec
{
	//<! 系统标识
	char sys_id[6];
	//<! 物理卡号
	char phy_card[12];
	//<! 交易卡号
	int	 card_id;
	//<! 交易日期
	char tx_date[9];
	//<! 交易日期1
	char tx_date1[9];
	//<! 交易时间
	char tx_time[7];
	//<! 交易时间1
	char tx_time1[7];
	//<! 设备物理ID
	char device_id[21];
	//<1 设备名称
	char device_name[41];
	//<! 设备名称2
	char device_name2[41];
	//<! 事件代码
	char event_code[5];
	//<! 事件描述
	char event_des[61];
	//<! 密码1
	char pwd1[17];
	//<! 密码2
	char pwd2[17];
	//<! 卡号
	char card_no[21];
	//<! 卡号
	char card_no2[21];
	/*以下为浮点型域*/
	double amt1;
	double amt2;
	double amt3;
	double amt4;
	double amt5;
	/*以下为整型域*/
	int	   lvol1;
	int	   lvol2;
	int	   lvol3;
	int	   lvol4;
	int	   lvol5;
}SerialRecord_t;

typedef struct _hCustomerInfo 
{
	char szName[20 + 1];					// 联系人姓名
	char szStuempNo[20 + 1];			    // 学工号
	char szSex[1 + 1];					    // 性别
	char szManId[20 + 1];					// 身份证号
	char szClassDeptName[150 + 1];		    // 部门名称
	char szTel[20 + 1];						// 联系电话
	int  nMendFeeType;						// 医疗收费类型(1为公费, 2为自费)
	int  nCustomerId;						// 客户号(换卡不变)
}CustomerInfo;

typedef struct _hTradeSerial 
{
	int	   nSerialNo;						// 流水号
	int	   nOtherSerialNo;					// 上传端流水号
	int    nSerialType;						// 流水类型
	int    nSerialState;					// 流水状态
	char   szOperateDate[10 + 1];			// 发生日期
	char   szOperateTime[8 + 1];			// 发生时间
	char   szCollectDate[10 + 1];			// 采集日期
	char   szCollectTime[8 + 1];			// 采集时间
	char   szEnteractDate[10 + 1];			// 入账日期
	char   szEnteractTime[8 + 1];			// 入账时间
	int    nMainDeviceId;					// 上传工作站标识
	int    nDeviceId;						// 交易发生设备标识
	char   szDevphy999Id[8 + 1];			// 三九设备物理ID
	char   szShowId[10 + 1];				// 显示卡号
	int    nCardId;							// 交易卡号
	int    nPurseId;						// 钱包号
	int	   nTradeCount;						// 交易次数
	double dTradeFee;						// 交易金额
	double dInBalance;						// 入卡值
	double dOutBalance;						// 出卡值
	double dDepositFee;						// 押金金额
	double dInFee;							// 手续费
	double dCostFee;						// 卡成本费
	double dBoardFee;						// 搭伙费
	int    nCoustomerId;					// 客户ID号
	char   szOperCode[10 + 1];				// 操作员号
	char   szOutAccountId[16 + 1];			// 出帐帐号
	char   szInAccountId[16 + 1];			// 入账帐号
	int    nSysId;							// 外部系统标识
	int    nTmark;							// 交易标记
	int    nErrCode;						// 返回码
	int    nReviseSerialNo;					// 冲正流水号
}TradeSerial;

#pragma pack()

#ifdef GWDLL_EXPORTS
#define API_EXPORT __stdcall //__declspec(dllexport) __stdcall
#else
#define API_EXPORT __declspec(dllimport) __stdcall
#endif // GWDLL_EXPORT

#ifndef BYTE
#define BYTE unsigned char
#endif // BYTE

/// 错误码定义
//<! 成功
#define KE_SUCCESS 0
//<! 未知错误 
#define KE_UNKNOWN_ERR		9999
//<! 不允许登录,可能IP与MAC地址信息不正确
#define KE_PERMISSION_DENY	1001
//<! 不能连接到应用服务器,可能网络故障
#define KE_CONNECT_ERROR	1002
//<! 请求功能号不存在
#define KE_REQ_FUNC_NOT_EXISTS 1003
//<! 查询失败, 可能服务器忙
#define KE_QUERY_ERROR	1004
//<! 检验失败,需要重新登录
#define KE_NOT_LOGIN	1005
//<! 读取本机MAC地址错误
#define KE_READ_LOCAL_MAC 1006
//<! 请求频率太快
#define KE_REQUEST_INTERVAL 1007

//<! 指定的卡不存在
#define KE_CARD_NO_EXIST	1010

//<! 保存记录失败
#define KE_SAVE_SERIAL		1011

//! 登录注册到应用服务器
/*
 \return 返回 0 表示登录成功,失败返回错误码
 */
int API_EXPORT KLogin();
//! 返回错误码
int API_EXPORT KGetErrorNo();
//! 读取错误信息
void API_EXPORT KGetErrorMsg(char msg[512]);
//! 通过物理卡号读取人员信息
/*
 \param phyid 物理卡号,必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */
int API_EXPORT KGetCardInfoByPhyId(const char phyid[9],CardInfo_t* tCard);
//! 通过显示卡号读取人员信息
/*
 \param cardno 显示卡号, 必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */
int API_EXPORT KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard);

//! 通过学工号读取人员信息
/*
 \param stuempno 显示卡号, 必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */
int API_EXPORT KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard);

//! 读取人员信息
/*
 \brief 检查顺序, phyid , cardno, stuempno ,如是一个为空,检查下一个
 \param phyid
 \param cardno
 \param stuempno
 \param tCard
 \return 返回 0 表示读取成功,失败返回错误码
 */
int API_EXPORT KGetCardInfo(const char phyid[9],const char cardno[21]
							,const char stuempno[21],CardInfo_t* tCard);
//! 上传流水
/*
 \brief 上传流水
 \param serial 流水结构
 \return 返回 0 表示成功, 失败返回错误码
 */
int API_EXPORT KSaveRecord(const SerialRecord_t * serial);
//! 通过学工号进行挂失
/*
\param stuempno 学工号
\param passwod 卡密码
\param validate_pwd 验证卡密码, 1表示使用密码，0表示不使用密码
\return 返回为0表示读取成功, 失败返回错误码
*/
//int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd);

//! 进行解挂
/*
\ 
\return 返回为0表示接挂成功, 失败返回错误码
*/
int API_EXPORT KGetRescind();

//!请求交易
/*
 \brief 请求交易功能
 \param req_no 交易功能号
 \param request 请求交易数据包
 \param response 交易应答数据包
 \return 返回 0 表示交易成功, 失败返回错误码.
 */
int API_EXPORT KSendRequest(int req_no,SerialRecord_t* request,SerialRecord_t* response);

//!初始化本地配置
/*
\brief				初始化本地配置功能
\return				返回 0 表示获取信息成功, 失败返回错误码.
*/
int API_EXPORT KInitLocal();

//!获取客户信息
/*
\brief				获取客户信息功能
\param szStuempNo	学工号
\param CutInfo		获取的客户信息
\return				返回 0 表示获取信息成功, 失败返回错误码.
*/
int API_EXPORT KCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo);

//!获取当前卡余额信息
/*
\brief				获取卡当前余额功能
\param szStuempNo	学工号
\param dCurBalance	获取的卡当前余额
\return				返回 0 表示获取信息成功, 失败返回错误码.
*/
int API_EXPORT KGetCurBalance(const char szStuempNo[21], double *dCurBalance);

//!获取流水信息
/*
\brief					获取流水信息功能
\param nDeviceId		学工号
\param Serial			获取的流水信息
\param nNextFlag		获取是否有下一次包的标记
\param nInputFlag		输入可以获取的下一次包标记
\param szBeginDate		开始日期(年:月:日)
\param szEndDate		结束日期(年:月:日)

\param szSerialYear		流水发生年份
\param szSerialMonth	流水发生月份
\param szBeginDay		流水开始日期
\param szEndDay			流水结束日期
\return					返回 0 表示获取信息成功, 失败返回错误码.
*/
//int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, const char szSerialYear[5], const char szSerialMonth[3], const char szBeginDay[3], const char szEndDay[3]);
int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11]);

//!获取部门名称信息
/*
\brief					获取部门名称功能
\param szClassDeptNo	部门编号
\param szClassDeptName  获取的部门名称
\return					返回 0 表示获取信息成功, 失败返回错误码.
*/
int API_EXPORT KGetDeptNameFromDeptNo(const char szClassDeptNo[10 + 1], char szClassDeptName[150 + 1]);

//!获取医疗类型信息
/*
\brief					获取医疗类型功能
\param nCustomerId		客户号
\param nMendFeeType     医疗类型
\return					返回 0 表示获取信息成功, 失败返回错误码.
*/
int API_EXPORT KGetMendFeeTypeFromCutId(int nCustomerId, int *nMendFeeType);

#ifdef __cplusplus
}
#endif

#endif // _KSG_GWDLL_H_
