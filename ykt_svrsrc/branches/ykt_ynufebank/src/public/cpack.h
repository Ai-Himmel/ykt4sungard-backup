/********************************************************************
created:	2005/01/25 14:33:52
filename:cpack.h
author:chenyh
purpose:	ST_PACK data structure defined file 
		 created from cpack.dbf
*********************************************************************/
#ifndef __CPACK_H
#define __CPACK_H

#include "PackB.h"

// 用字段序号代替原来设计使用的字段位图
// Define F_xxxx as field index number
#define F_SCUST_NO		0
#define F_SCUST_NO2		1
#define F_SHOLDER_AC_NO		2
#define F_SHOLDER_AC_NO2		3
#define F_SHOLDER_TYPE		4
#define F_SHOLDER_TYPE2		5
#define F_SNAME		6
#define F_SNAME2		7
#define F_SALL_NAME		8
#define F_SMARKET_CODE		9
#define F_SMARKET_CODE2		10
#define F_SDATE0		11
#define F_SDATE1		12
#define F_SDATE2		13
#define F_SDATE3		14
#define F_STIME0		15
#define F_STIME1		16
#define F_STIME2		17
#define F_STIME3		18
#define F_LVOL0		19
#define F_LVOL1		20
#define F_LVOL2		21
#define F_LVOL3		22
#define F_LVOL4		23
#define F_LVOL5		24
#define F_LVOL6		25
#define F_LVOL7		26
#define F_LVOL8		27
#define F_LVOL9		28
#define F_LVOL10		29
#define F_LVOL11		30
#define F_LVOL12		31
#define F_DAMT0		32
#define F_DAMT1		33
#define F_DAMT2		34
#define F_DAMT3		35
#define F_DAMT4		36
#define F_DAMT5		37
#define F_DAMT6		38
#define F_DAMT7		39
#define F_DAMT8		40
#define F_DAMT9		41
#define F_DAMT10		42
#define F_DAMT11		43
#define F_DAMT12		44
#define F_DAMT13		45
#define F_DAMT14		46
#define F_DAMT15		47
#define F_DAMT16		48
#define F_DAMT17		49
#define F_DAMT18		50
#define F_DAMT19		51
#define F_DAMT20		52
#define F_DAMT21		53
#define F_DAMT22		54
#define F_DAMT23		55
#define F_DAMT24		56
#define F_DAMT25		57
#define F_DAMT26		58
#define F_DAMT27		59
#define F_DAMT28		60
#define F_DAMT29		61
#define F_DAMT30		62
#define F_DAMT31		63
#define F_DAMT32		64
#define F_DAMT33		65
#define F_SSTOCK_CODE		66
#define F_SSTOCK_CODE2		67
#define F_SCUST_TYPE		68
#define F_SCUST_TYPE2		69
#define F_SSTAT_TYPE		70
#define F_SSTAT_TYPE2		71
#define F_SROOM_NO		72
#define F_SROOM_NO2		73
#define F_SOPEN_EMP		74
#define F_SCLOSE_EMP		75
#define F_SCHANGE_EMP		76
#define F_SCHECK_EMP		77
#define F_SEMP		78
#define F_SNATION_CODE		79
#define F_LCERT_CODE		80
#define F_STX_PWD		81
#define F_STX_PWD2		82
#define F_SWITHDRAW_PWD		83
#define F_SWITHDRAW_PWD2		84
#define F_SEMP_PWD		85
#define F_SEMP_PWD2		86
#define F_SBANK_PWD		87
#define F_SBANK_PWD2		88
#define F_SCUST_AUTH		89
#define F_SCUST_AUTH2		90
#define F_SCUST_LIMIT		91
#define F_SCUST_LIMIT2		92
#define F_LSAFE_LEVEL		93
#define F_LSAFE_LEVEL2		94
#define F_SPOST_CODE		95
#define F_SPOST_CODE2		96
#define F_SPHONE		97
#define F_SPHONE2		98
#define F_SPHONE3		99
#define F_SPAGER		100
#define F_SEMAIL		101
#define F_SEMAIL2		102
#define F_SNOTE		103
#define F_SNOTE2		104
#define F_SCERT_NO		105
#define F_SCERT_NO2		106
#define F_SCERT_ADDR		107
#define F_SSTATUS0		108
#define F_SSTATUS1		109
#define F_SSTATUS2		110
#define F_SSTATUS3		111
#define F_SSTATUS4		112
#define F_LWITHDRAW_FLAG		113
#define F_SADDR		114
#define F_SADDR2		115
#define F_SSERIAL0		116
#define F_SSERIAL1		117
#define F_SSERIAL2		118
#define F_SSERIAL3		119
#define F_SSERIAL4		120
#define F_SCURRENCY_TYPE		121
#define F_SCURRENCY_TYPE2		122
#define F_SBRANCH_CODE0		123
#define F_SBRANCH_CODE1		124
#define F_SBRANCH_CODE2		125
#define F_USSET0		126
#define F_USSET1		127
#define F_USSET2		128
#define F_USSET3		129
#define F_USSET4		130
#define F_USSET5		131
#define F_USSET6		132
#define F_SSTATION0		133
#define F_SSTATION1		134
#define F_SBANK_ACC		135
#define F_SBANK_ACC2		136
#define F_LBANK_ACC_TYPE		137
#define F_LBANK_ACC_TYPE2		138
#define F_SMAIN_FLAG		139
#define F_SMAIN_FLAG2		140
#define F_SBANK_CODE		141
#define F_SBANK_CODE2		142
#define F_SEMP_NO		143
#define F_SEMP_NO2		144
#define F_DRATE0		145
#define F_DRATE1		146
#define F_LSERIAL0		147
#define F_LSERIAL1		148
#define F_SBANKNAME		149
#define F_SBANKNAME2		150
#define F_SCARD0		151
#define F_SCARD1		152
#define F_SORDER0		153
#define F_SORDER1		154
#define F_SORDER2		155
#define F_SCUSTTYPES		156
#define F_SSECTYPES		157
#define F_VSMESS		176
#define F_VSVARSTR0		177
#define F_VSVARSTR1		178
#define F_VSVARSTR2		179
#define F_VSVARSTR3		180
/* 以下代码是用来字节对齐使用的 */
#ifdef WIN32
   #define __PACKED__ 
   #pragma pack(push,1)
#else
   #ifdef __GNUC__
      #define __PACKED__	__attribute__ ((packed))
      //#pragma pack(push,1)
   #else
      #ifdef HP_UX
         #define __PACKED__
         #pragma pack 1
      #else
         #define __PACKED__
         #pragma options align=packed
      #endif
   #endif
#endif
typedef struct _ST_PACK 
{
	char	scust_no[11];		//0.1 客户号
	char	scust_no2[11];		//1.第二客户号
	char	sholder_ac_no[16];		//2.股东代码
	char	sholder_ac_no2[16];		//3.第二股东代码
	char	sholder_type[3];		//4.股东代码类别
	char	sholder_type2[3];		//5.第二股东代码类别
	char	sname[21];		//6.姓名
	char	sname2[21];		//7.第二姓名
	char	sall_name[81];		//8.2 全名
	char	smarket_code[2];		//9.市场代码
	char	smarket_code2[2];		//10.市场代码2
	char	sdate0[9];		//11.日期 委托日期
	char	sdate1[9];		//12.日期 成交日期
	char	sdate2[9];		//13.日期 报盘日期
	char	sdate3[9];		//14.日期 发生日期
	char	stime0[9];		//15.时间 委托时间
	char	stime1[9];		//16.3 时间 成交时间
	char	stime2[9];		//17.时间 包盘时间
	char	stime3[9];		//18.时间 发生时间
	int	lvol0;		//19.数量0 委托数量 买量1
	int	lvol1;		//20.数量1 成交数量 买量2
	int	lvol2;		//21.数量2 可用数量 买量3
	int	lvol3;		//22.数量3 手工冻结数量 买量4
	int	lvol4;		//23.数量4 委托冻结数量 卖量1
	int	lvol5;		//24.数量5 买入成交数量 卖量2
	int	lvol6;		//25.数量6 卖出成交数量 卖量3
	int	lvol7;		//26.数量7 清算后余额 卖量4
	int	lvol8;		//27.数量8 手工解冻数量
	int	lvol9;		//28.数量9 存入数量
	int	lvol10;		//29.数量10 取出数量
	int	lvol11;		//30.数量11 买入未过户数量
	int	lvol12;		//31.数量12 卖出未过户数量
	double	damt0;		//32.5 金额0 委托价格
	double	damt1;		//33.金额1 委托金额
	double	damt2;		//34.金额2 成交价格
	double	damt3;		//35.金额3 成交金额
	double	damt4;		//36.金额4 清算后余额
	double	damt5;		//37.金额5 存入金额
	double	damt6;		//38.金额6 取出金额
	double	damt7;		//39.金额7 现金金额
	double	damt8;		//40.6 金额8 支汇票金额
	double	damt9;		//41.金额9 异常冻结金额
	double	damt10;		//42.金额10 买入冻结金额
	double	damt11;		//43.金额11 卖出冻结金额
	double	damt12;		//44.金额12 买入成交金额
	double	damt13;		//45.金额13 卖出成交金额
	double	damt14;		//46.金额14 手工冻结金额
	double	damt15;		//47.金额15 手工解冻金额
	double	damt16;		//48.7 金额16 贷款金额
	double	damt17;		//49.金额17 发生金额
	double	damt18;		//50.金额18 买入未过户金额
	double	damt19;		//51.金额19 卖出未过户金额
	double	damt20;		//52.金额20 利息积数
	double	damt21;		//53.金额21 罚息积数
	double	damt22;		//54.金额22 贷款利息9积数
	double	damt23;		//55.金额23 信用金额
	double	damt24;		//56.8 金额24 禁用资金
	double	damt25;		//57.金额25 禁取资金
	double	damt26;		//58.金额26 利息
	double	damt27;		//59.金额27 罚息
	double	damt28;		//60.金额28 贷款利息
	double	damt29;		//61.金额29 市值
	double	damt30;		//62.金额30 虚增保证金
	double	damt31;		//63.金额31 手续费
	double	damt32;		//64.9 金额32 印花税
	double	damt33;		//65.金额33 过户费
	char	sstock_code[9];		//66.证券代码
	char	sstock_code2[9];		//67.证券代码2
	char	scust_type[3];		//68.客户类别
	char	scust_type2[3];		//69.客户类别2
	char	sstat_type[3];		//70.统计类别
	char	sstat_type2[3];		//71.统计类别2
	char	sroom_no[4];		//72.10 客户组号
	char	sroom_no2[4];		//73.客户组号2
	char	sopen_emp[7];		//74.职工
	char	sclose_emp[7];		//75.职工
	char	schange_emp[7];		//76.职工
	char	scheck_emp[7];		//77.复核职工
	char	semp[7];		//78.职工
	char	snation_code[4];		//79.国籍代码
	int	lcert_code;		//80.11 证件类别
	char	stx_pwd[9];		//81.交易密码
	char	stx_pwd2[9];		//82.交易密码2
	char	swithdraw_pwd[9];		//83.取款密码
	char	swithdraw_pwd2[9];		//84.取款密码2
	char	semp_pwd[9];		//85.柜员密码
	char	semp_pwd2[9];		//86.柜员密码2
	char	sbank_pwd[9];		//87.银行密码
	char	sbank_pwd2[9];		//88.12 银行密码2
	char	scust_auth[21];		//89.客户权限
	char	scust_auth2[21];		//90.客户权限2
	char	scust_limit[33];		//91.客户限制
	char	scust_limit2[33];		//92.客户限制2
	int	lsafe_level;		//93.安全级别
	int	lsafe_level2;		//94.安全级别2
	char	spost_code[7];		//95.邮政编码
	char	spost_code2[7];		//96.13 邮政编码2
	char	sphone[31];		//97.联系电话
	char	sphone2[31];		//98.fax
	char	sphone3[31];		//99.移动电话
	char	spager[31];		//100.传呼
	char	semail[61];		//101.email
	char	semail2[61];		//102.email2
	char	snote[81];		//103.备注
	char	snote2[81];		//104.14 备注2
	char	scert_no[51];		//105.身份证号码
	char	scert_no2[51];		//106.身份证号码2
	char	scert_addr[81];		//107.身份证地址
	char	sstatus0[2];		//108.状态，客户状态
	char	sstatus1[2];		//109.状态1
	char	sstatus2[2];		//110.状态2
	char	sstatus3[2];		//111.状态3
	char	sstatus4[2];		//112.15 状态4
	int	lwithdraw_flag;		//113.提款方式
	char	saddr[81];		//114.联系地址
	char	saddr2[81];		//115.联系地址2
	char	sserial0[13];		//116.序号0
	char	sserial1[13];		//117.序号1
	char	sserial2[13];		//118.序号2
	char	sserial3[13];		//119.序号3
	char	sserial4[13];		//120.16 序号4
	char	scurrency_type[3];		//121.货币类型
	char	scurrency_type2[3];		//122.货币类型2
	char	sbranch_code0[4];		//123.开户营业部号码
	char	sbranch_code1[4];		//124.发生营业部号码
	char	sbranch_code2[4];		//125.营业部号码2
	unsigned char	usset0[100];		//126.管理权限集合
	unsigned char	usset1[100];		//127.授权权限集合
	unsigned char	usset2[100];		//128.17 操作权限集合
	unsigned char	usset3[100];		//129.菜单权限集合
	unsigned char	usset4[100];		//130.岗位集合
	unsigned char	usset5[100];		//131.市场集合
	unsigned char	usset6[100];		//132.货币集合
	char	sstation0[17];		//133.工作站地址
	char	sstation1[17];		//134.工作站地址2
	char	sbank_acc[41];		//135.银行账号
	char	sbank_acc2[41];		//136.18 银行账号2
	int	lbank_acc_type;		//137.银行账号类别
	int	lbank_acc_type2;		//138.银行账号类别2
	char	smain_flag[2];		//139.主副标志
	char	smain_flag2[2];		//140.主副标志
	char	sbank_code[7];		//141.银行代码
	char	sbank_code2[7];		//142.银行代码2
	char	semp_no[9];		//143.工号
	char	semp_no2[9];		//144.19 工号2
	double	drate0;		//145.比率
	double	drate1;		//146.比率1
	int	lserial0;		//147.序列号 0
	int	lserial1;		//148.序列号 1
	char	sbankname[81];		//149.银行名称
	char	sbankname2[81];		//150.银行名称2
	char	scard0[51];		//151.磁卡号码
	char	scard1[51];		//152.20 磁卡号码
	char	sorder0[11];		//153.合同序号
	char	sorder1[11];		//154.合同序号
	char	sorder2[11];		//155.合同序号
	char	scusttypes[201];		//156.客户类别集合
	char	ssectypes[201];		//157.证券类别集合
	char	vsmess[256];		//176.23 信息
	char	vsvarstr0[256];		//177.变长的字符串
	char	vsvarstr1[256];		//178.变长的字符串
	char	vsvarstr2[256];		//179.变长的字符串
	char	vsvarstr3[256];		//180.变长的字符串
} __PACKED__ ST_PACK;
typedef struct _ST_CPACK
{
	ST_PACKHEAD head;
	ST_PACK     pack;
} __PACKED__ ST_CPACK;
#ifdef WIN32
   #pragma pack(pop)
#else
   #ifdef __GNUC__
   #else
      #ifdef HP_UX
         #pragma pack 0
      #else
         #pragma options align=reset
      #endif
   #endif
#endif
#undef __PACKED__

#include "PackC.h"

#endif
