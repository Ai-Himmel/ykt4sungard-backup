#ifndef _KSG_GWDLL_H_
#define _KSG_GWDLL_H_

#ifdef __cplusplus
extern "C" {
#endif

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
//! 通过学工号进行挂失
/*
\ param stuempno 学工号
\ param passwod 卡密码
\ param validate_pwd 验证卡密码, 1表示使用密码，0表示不使用密码
\ return 返回为0表示读取成功, 失败返回错误码
*/
int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd);

//! 进行解挂
/*
\ 
\ return 返回为0表示接挂成功, 失败返回错误码
*/
int API_EXPORT KGetRescind();

#ifdef __cplusplus
}
#endif

#endif // _KSG_GWDLL_H_
