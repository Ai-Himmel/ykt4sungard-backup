#ifndef _GW_GETCARDINFO_H_
#define _GW_GETCARDINFO_H_

#pragma once
#pragma pack(1)

typedef struct _tagCardInfo
{
	// <! 交易卡号
	int cardid;
	// <! 学工号
	char stuemp_no[21];
	// <! 姓名
	char name[4];
	// <! 物理卡号
	char phyid[9];
	// <! 显示卡号
	char cardno[11];
	// <! 单位代码
	char deptno[11];
	// <! 单位名称
	char deptname[51];
	// <! 类别代码
	int cut_name[51];
	// <! 性别, 1男， 2女， 9 其它
	int sex;
	// <! 卡类别名称
	char card_type_name[51];
}CardInfo_t;

#pragma pack()

/// 错误码定义
// <! 成功
#define KE_SUCCESS 0

// <! 未知错误
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

// ! 登陆注册到应用服务器
/*
\return 返回0表示登陆成功, 失败返回错误码
*/
int KGetErrorNo();

//! 读取错误信息
void KGetErrorMsg(char msg[512]);

//! 通过物理卡号读取人员信息
/*
 \param phyid 物理卡号,必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */
int KGetCardInfoByPhyId(const char phyid[9],CardInfo_t* tCard);

//! 通过显示卡号读取人员信息
/*
 \param cardno 显示卡号, 必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */
int KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard);

//! 通过学工号读取人员信息
/*
 \param stuempno 显示卡号, 必须是以 '\0' 结束
 \param tCard 人员信息
 \return 返回 0 表示读取成功,失败返回错误码
 */

int KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard);
//! 读取人员信息
/*
 \brief 检查顺序, phyid , cardno, stuempno ,如是一个为空,检查下一个
 \param phyid
 \param cardno
 \param stuempno
 \param tCard
 \return 返回 0 表示读取成功,失败返回错误码
 */
int KGetCardInfo(const char phyid[9],const char cardno[21]
							,const char stuempno[21],CardInfo_t* tCard);

//! 通过物理卡号读取学工号
/*
\ param phyid 需要输入的物理卡号
\ param stuempno 需要获得的学工号
\ return 返回0表示成功，否则失败返回错误码
*/
int KGetStuempNoByPhyid(const char phyid[9], char stuemp_no[21]);

// !函数初始化程序
/*
\ 函数实现错误信息和DRTP的初始化工作
\ reutn 返回TURE表示初始化成功, 反之表示失败
*/
BOOL KInitFunc();

// !从服务器上获取密钥
/*
\ 函数实现从服务器上获取密钥
\ return返回0为成功，返回非0不成功
*/
int KRecPwdFromSvr();

#endif