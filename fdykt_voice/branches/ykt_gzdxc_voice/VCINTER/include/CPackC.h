
/* ------------------------------------------------------------------------- */
/*
CPACKC.H

  创建日期：	2002/6/6
  作者：		彭铭
  版本信息：	V1.0
  功能： 
	对大集中的CPACK进行封装
*/
/* ------------------------------------------------------------------------- */
#ifndef __CPACKC_H__
#define __CPACKC_H__

#ifdef CPACK_EXPORTS
#define CPACK_API __declspec(dllexport)
#else
#define CPACK_API __declspec(dllimport)
#pragma comment(lib,"..\\Lib\\CPackC.lib") 
#pragma message("Automatically linking with CPackC.dll") 
#endif

   /* 定义了PARMBITS的最大大小了每字节的BITS数 */
#define PARMBITS	(256)
#define BITSPERBYTE	(8)
#define PARMBYTES	(32)       // PARMBITS/BITSPERBYTE -- 应该可以提高系统处理速度
#define FID_RETCODE PARMBITS
#define FID_RECCOUNT (PARMBITS+1)

enum PDLTYPES
{
   PDL_CHAR=1,
   PDL_VCHAR=2,
   PDL_UCHAR=3,
   PDL_LONG=4,
   PDL_DOUBLE=5
};


typedef struct {
   char szName[16];
   WORD wType;    // 0 - None; 1-char; 2-vs_char; 3-unsigned char; 4-int(long); 5-double
   WORD nLength;  // 0 - None.
   DWORD dwOffset; // 
} ST_PDATALIST;

extern CPACK_API ST_PDATALIST gstPDataList[PARMBITS];

#ifdef __cplusplus
extern "C" {
#endif
   
   /* 以下代码是用来字节对齐使用的 */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#pragma options align=packed
#else
#define __PACKED__	__attribute__ ((packed))
#pragma pack(push,1)
#endif
#else
#define __PACKED__ 
#pragma pack(push,1)
#endif
   

   // DRTPBUFLEN － 通讯平台的发送接收长度限制
#define DRTPBUFLEN   4096   // PC Version
   
   /*
   地址资料
   */
   typedef struct st_addr_c
   {
      unsigned char addr[6];
   }__PACKED__ ST_ADDR_C;
   
   
   // CYH:这部分在PC版应用服务器中成为另外一种使用方式，包括：
   //　
   //
   typedef struct st_hook_c
   {
      unsigned int	UserID;					/* 请求者的ID号码*/
      char hostname[33];						/* 主机名 */
      char queuename[33];						/* 队列名 */
      unsigned int	queuetype;				/* 队列类型 */
   }__PACKED__ ST_HOOK_C;
   
   /* 
   包头结构
   */

   typedef struct st_packhead_c
{
	unsigned int	RequestType;
	unsigned char	firstflag;				/* 是否第一个请求（首包请求）*/
	unsigned char	nextflag;					/* 是否后续包请求*/
	unsigned int	recCount;					/* 本包的记录数*/
	unsigned int	retCode;					/* 返回代码*/
	
	ST_ADDR_C			addr;						/* 请求着的地址（6个子节）*/
	ST_HOOK_C         hook;	                    /*                    */
	unsigned int    userdata;					/*					*/

	unsigned char ParmBits[PARMBITS/BITSPERBYTE];
}__PACKED__ ST_PACKHEAD_C;

   /*
   定义了每一个pack成员的设置值，格式如下：
   0xAABB
   AA:	成员在PARMBITS中的字节号(0开始)
   BB: 成员在这个字节的位图
   */
   // FIELDID:

#define F_SCUST_NO			0x0001
#define F_SCUST_NO2			0x0002
#define F_SHOLDER_AC_NO		0x0004
#define	F_SHOLDER_AC_NO2	0x0008
#define	F_SHOLDER_TYPE		0x0010
#define	F_SHOLDER_TYPE2		0x0020
#define F_SNAME				0x0040
#define	F_SNAME2			0x0080

#define	F_SALL_NAME			0x0101
#define F_SMARKET_CODE		0x0102
#define F_SMARKET_CODE2		0x0104
#define F_SDATE0			0x0108
#define F_SDATE1			0x0110
#define F_SDATE2			0x0120
#define F_SDATE3			0x0140
#define F_STIME0			0x0180

#define F_STIME1			0x0201
#define F_STIME2			0x0202
#define F_STIME3			0x0204
#define	F_LVOL0				0x0208
#define F_LVOL1				0x0210
#define F_LVOL2				0x0220
#define F_LVOL3				0x0240
#define F_LVOL4				0x0280

#define F_LVOL5				0x0301
#define F_LVOL6				0x0302
#define F_LVOL7				0x0304
#define F_LVOL8				0x0308
#define F_LVOL9				0x0310
#define F_LVOL10			0x0320
#define F_LVOL11			0x0340
#define F_LVOL12			0x0380

#define F_DAMT0				0x0401
#define F_DAMT1				0x0402
#define F_DAMT2				0x0404
#define F_DAMT3				0x0408
#define F_DAMT4				0x0410
#define F_DAMT5				0x0420
#define F_DAMT6				0x0440
#define F_DAMT7				0x0480

#define F_DAMT8				0x0501
#define F_DAMT9				0x0502
#define F_DAMT10			0x0504
#define F_DAMT11			0x0508
#define F_DAMT12			0x0510
#define F_DAMT13			0x0520
#define F_DAMT14			0x0540
#define F_DAMT15			0x0580

#define F_DAMT16			0x0601
#define F_DAMT17			0x0602
#define F_DAMT18			0x0604
#define F_DAMT19			0x0608
#define F_DAMT20			0x0610
#define F_DAMT21			0x0620
#define F_DAMT22			0x0640
#define	F_DAMT23			0x0680

#define F_DAMT24			0x0701
#define F_DAMT25			0x0702
#define F_DAMT26			0x0704
#define F_DAMT27			0x0708
#define F_DAMT28			0x0710
#define F_DAMT29			0x0720
#define F_DAMT30			0x0740
#define F_DAMT31			0x0780

#define F_DAMT32			0x0801
#define F_DAMT33			0x0802
#define F_SSTOCK_CODE		0x0804
#define F_SSTOCK_CODE2		0x0808
#define F_SCUST_TYPE		0x0810
#define F_SCUST_TYPE2		0x0820
#define F_SSTAT_TYPE		0x0840
#define F_SSTAT_TYPE2		0x0880

#define F_SROOM_NO			0x0901
#define F_SROOM_NO2			0x0902
#define F_SOPEN_EMP			0x0904
#define F_SCLOSE_EMP		0x0908
#define F_SCHANGE_EMP		0x0910
#define F_SCHECK_EMP		0x0920
#define F_SEMP				0x0940
#define F_SNATION_CODE		0x0980

#define F_LCERT_CODE		0x0A01
#define F_STX_PWD			0x0A02
#define F_STX_PWD2			0x0A04
#define F_SWITHDRAW_PWD		0x0A08
#define F_SWITHDRAW_PWD2	0x0A10
#define F_SEMP_PWD			0x0A20
#define F_SEMP_PWD2			0x0A40
#define F_SBANK_PWD			0x0A80

#define F_SBANK_PWD2		0x0B01
#define F_SCUST_AUTH		0x0B02
#define F_SCUST_AUTH2		0x0B04
#define F_SCUST_LIMIT		0x0B08
#define F_SCUST_LIMIT2		0x0B10
#define F_LSAFE_LEVEL		0x0B20
#define F_LSAFE_LEVEL2		0x0B40
#define F_SPOST_CODE		0x0B80

#define F_SPOST_CODE2		0x0C01
#define F_SPHONE			0x0C02
#define F_SPHONE2			0x0C04
#define F_SPHONE3			0x0C08
#define F_SPAGER			0x0C10
#define F_SEMAIL			0x0C20
#define F_SEMAIL2			0x0C40
#define F_SNOTE				0x0C80

#define F_SNOTE2			0x0D01
#define F_SCERT_NO			0x0D02
#define F_SCERT_NO2			0x0D04
#define F_SCERT_ADDR		0x0D08
#define F_SSTATUS0			0x0D10
#define F_SSTATUS1			0x0D20
#define F_SSTATUS2			0x0D40
#define F_SSTATUS3			0x0D80

#define F_SSTATUS4			0x0E01
#define F_LWITHDRAW_FLAG	0x0E02
#define F_SADDR				0x0E04
#define F_SADDR2			0x0E08
#define F_SSERIAL0			0x0E10
#define F_SSERIAL1			0x0E20
#define F_SSERIAL2			0x0E40
#define F_SSERIAL3			0x0E80

#define F_SSERIAL4			0x0F01
#define F_SCURRENCY_TYPE	0x0F02
#define F_SCURRENCY_TYPE2	0x0F04
#define F_SBRANCH_CODE0		0x0F08
#define F_SBRANCH_CODE1		0x0F10
#define F_SBRANCH_CODE2		0x0F20
#define F_USSET0			0x0F40
#define F_USSET1			0x0F80

#define F_USSET2			0x1001
#define F_USSET3			0x1002
#define F_USSET4			0x1004
#define F_USSET5			0x1008
#define F_USSET6			0x1010
#define F_SSTATION0			0x1020
#define F_SSTATION1			0x1040
#define F_SBANK_ACC			0x1080

#define F_SBANK_ACC2		0x1101
#define F_LBANK_ACC_TYPE	0x1102
#define F_LBANK_ACC_TYPE2	0x1104
#define F_SMAIN_FLAG		0x1108
#define F_SMAIN_FLAG2		0x1110
#define F_SBANK_CODE		0x1120
#define F_SBANK_CODE2		0x1140
#define F_SEMP_NO		0x1180
#define F_SEMP_NO2			0x1201
#define F_DRATE0			0x1202
#define F_DRATE1			0x1204
#define F_LSERIAL0			0x1208
#define F_LSERIAL1			0x1210
#define F_SBANKNAME			0x1220
#define F_SBANKNAME2			0x1240
#define F_SCARD0			0x1280

#define F_SCARD1			0x1301
#define F_SORDER0			0x1302
#define F_SORDER1			0x1304
#define F_SORDER2			0x1308
#define F_SCUSTTYPES			0x1310
#define F_SSECTYPES			0x1320

#define F_VSMESS			0x1601
#define F_VSVARSTR0			0x1602
#define F_VSVARSTR1			0x1604
#define F_VSVARSTR2			0x1608
#define F_VSVARSTR3			0x1610

typedef struct {
	char scust_no[11];			/*1 客户号 */
	char scust_no2[11];			/* 第二客户号 */
	char sholder_ac_no[16];		/* 股东代码 */
	char sholder_ac_no2[16];	/* 第二股东代码 */
	char sholder_type[3];		/* 股东代码类别 */
	char sholder_type2[3];		/* 第二股东代码类别 */
	char sname[21];				/* 姓名 */
	char sname2[21];			/* 第二姓名 */

	char sall_name[81];			/*2 全名 */
	char smarket_code[2];		/* 市场代码 */
	char smarket_code2[2];		/* 市场代码2 */
	char sdate0[9];				/* 日期 委托日期*/
	char sdate1[9];				/* 日期 成交日期*/
	char sdate2[9];				/* 日期 报盘日期*/
	char sdate3[9];				/* 日期 发生日期*/
	char stime0[9];				/* 时间 委托时间*/

	char stime1[9];				/*3 时间 成交时间*/
	char stime2[9];				/* 时间 包盘时间*/
	char stime3[9];				/* 时间 发生时间*/
	long	lvol0;				/* 数量0 委托数量		买量1*/
	long	lvol1;				/* 数量1 成交数量		买量2*/
	long	lvol2;				/* 数量2 可用数量		买量3*/
	long	lvol3;				/* 数量3 手工冻结数量	买量4*/
	long	lvol4;				/* 数量4 委托冻结数量	卖量1*/

	long	lvol5;				/*4 数量5 买入成交数量	卖量2*/
	long	lvol6;				/* 数量6 卖出成交数量	卖量3*/
	long	lvol7;				/* 数量7 清算后余额		卖量4*/
	long	lvol8;				/* 数量8 手工解冻数量 */
	long	lvol9;				/* 数量9 存入数量 */
	long	lvol10;				/* 数量10 取出数量 */
	long	lvol11;				/* 数量11 买入未过户数量 */
	long	lvol12;				/* 数量12 卖出未过户数量 */

	double	damt0;				/*5 金额0 委托价格 */
	double	damt1;				/* 金额1 委托金额 */
	double	damt2;				/* 金额2 成交价格 */
	double	damt3;				/* 金额3 成交金额 */
	double	damt4;				/* 金额4 清算后余额 */
	double	damt5;				/* 金额5 存入金额 */
	double  damt6;				/* 金额6 取出金额 */
	double	damt7;				/* 金额7 现金金额 */

	double	damt8;				/*6 金额8 支汇票金额 */
	double	damt9;				/* 金额9 异常冻结金额 */
	double	damt10;				/* 金额10 买入冻结金额 */
	double	damt11;				/* 金额11 卖出冻结金额 */
	double	damt12;				/* 金额12 买入成交金额 */
	double	damt13;				/* 金额13 卖出成交金额 */
	double	damt14;				/* 金额14 手工冻结金额 */
	double	damt15;				/* 金额15 手工解冻金额 */

	double	damt16;				/*7 金额16 贷款金额 */
	double	damt17;				/* 金额17 发生金额 */
	double	damt18;				/* 金额18 买入未过户金额 */
	double	damt19;				/* 金额19 卖出未过户金额 */
	double	damt20;				/* 金额20 利息积数 */
	double	damt21;				/* 金额21 罚息积数 */
	double	damt22;				/* 金额22 贷款利息9积数 */
	double	damt23;				/* 金额23 信用金额 */

	double	damt24;				/*8 金额24 禁用资金 */
	double	damt25;				/* 金额25 禁取资金 */
	double	damt26;				/* 金额26 利息 */
	double	damt27;				/* 金额27 罚息 */
	double	damt28;				/* 金额28 贷款利息 */
	double	damt29;				/* 金额29 市值 */
	double	damt30;				/* 金额30 虚增保证金 */
	double	damt31;				/* 金额31 手续费 */

	double	damt32;				/*9 金额32 印花税 */
	double	damt33;				/* 金额33 过户费 */
	char	sstock_code[9];		/* 证券代码 */
	char	sstock_code2[9];	/* 证券代码2 */
	char	scust_type[3];		/* 客户类别 */
	char	scust_type2[3];		/* 客户类别2 */
	char	sstat_type[3];		/* 统计类别 */
	char	sstat_type2[3];		/* 统计类别2 */

	char	sroom_no[4];		/*10 客户组号 */
	char	sroom_no2[4];		/* 客户组号2 */
	char	sopen_emp[7];		/* 职工 */
	char	sclose_emp[7];		/* 职工 */
	char	schange_emp[7];		/* 职工 */
	char	scheck_emp[7];		/* 复核职工 */
	char	semp[7];			/* 职工 */
	char	snation_code[4];	/* 国籍代码 */

	long	lcert_code;			/*11 证件类别 */
	char	stx_pwd[9];			/* 交易密码 */
	char	stx_pwd2[9];		/* 交易密码2 */
	char	swithdraw_pwd[9];	/* 取款密码 */
	char	swithdraw_pwd2[9];	/* 取款密码2 */
	char	semp_pwd[9];		/* 柜员密码 */
	char	semp_pwd2[9];		/* 柜员密码2 */
	char	sbank_pwd[9];		/* 银行密码 */

	char	sbank_pwd2[9];		/*12 银行密码2 */
	char	scust_auth[21];		/* 客户权限 */
	char	scust_auth2[21];	/* 客户权限2 */
	char	scust_limit[33];	/* 客户限制 */
	char	scust_limit2[33];	/* 客户限制2 */
	long	lsafe_level;		/* 安全级别 */
	long	lsafe_level2;		/* 安全级别2 */
	char	spost_code[7];		/* 邮政编码 */

	char	spost_code2[7];		/*13 邮政编码2 */
	char	sphone[31];			/* 联系电话 */
	char	sphone2[31];		/* fax */
	char	sphone3[31];		/* 移动电话 */
	char	spager[31];			/* 传呼 */
	char	semail[61];			/* email */
	char	semail2[61];		/* email2 */
	char	snote[81];			/* 备注 */

	char	snote2[81];			/*14 备注2 */
	char	scert_no[51];		/* 身份证号码 */
	char	scert_no2[51];		/* 身份证号码2 */
	char	scert_addr[81];		/* 身份证地址 */
	char	sstatus0[2];		/* 状态，客户状态 */
	char	sstatus1[2];		/* 状态1 */
	char	sstatus2[2];		/* 状态2 */
	char	sstatus3[2];		/* 状态3 */

	char	sstatus4[2];		/*15 状态4 */
	long	lwithdraw_flag;		/* 提款方式 */
	char	saddr[81];			/* 联系地址 */
	char	saddr2[81];			/* 联系地址2 */
	char	sserial0[13];		/* 序号0 */
	char	sserial1[13];		/* 序号1 */
	char	sserial2[13];		/* 序号2 */
	char	sserial3[13];		/* 序号3 */

	char	sserial4[13];		/*16 序号4 */
	char	scurrency_type[3];	/* 货币类型 */
	char	scurrency_type2[3];	/* 货币类型2 */
	char	sbranch_code0[4];	/* 开户营业部号码 */
	char	sbranch_code1[4];	/* 发生营业部号码 */
	char	sbranch_code2[4];	/* 营业部号码2 */
	unsigned char usset0[100];	/* 管理权限集合 */
	unsigned char usset1[100];	/* 授权权限集合 */

	unsigned char usset2[100];	/*17 操作权限集合 */
	unsigned char usset3[100];	/* 菜单权限集合 */
	unsigned char usset4[100];	/* 岗位集合 */
	unsigned char usset5[100];	/* 市场集合 */
	unsigned char usset6[100];	/* 货币集合 */
	char	sstation0[17];		/* 工作站地址 */
	char	sstation1[17];		/* 工作站地址2 */
	char	sbank_acc[41];		/* 银行账号 */

	char	sbank_acc2[41];		/*18 银行账号2 */
	long	lbank_acc_type;		/* 银行账号类别 */
	long	lbank_acc_type2;	/* 银行账号类别2 */
	char	smain_flag[2];		/* 主副标志 */
	char	smain_flag2[2];		/* 主副标志 */
	char	sbank_code[7];		/* 银行代码 */
	char	sbank_code2[7];		/* 银行代码2 */
	char	semp_no[9];			/* 工号 */

	char	semp_no2[9];		/*19 工号2 */
	double	drate0;				/* 比率 */
	double	drate1;				/* 比率1 */
	long	lserial0;			/* 序列号 0 */
	long	lserial1;			/* 序列号 1 */
	char	sbankname[81];		/* 银行名称 */
	char	sbankname2[81];		/* 银行名称2 */
	char	scard0[51];			/* 磁卡号码 */

	char	scard1[51];			/*20 磁卡号码 */
	char	sorder0[11];			/* 合同序号 */
	char	sorder1[11];			/* 合同序号 */
	char	sorder2[11];			/* 合同序号 */
	char    scusttypes[201];	        /* 客户类别集合 */
	char    ssectypes[201];	                /* 证券类别集合 */

	char	vsmess[256];		/* 23 信息 */
	char	vsvarstr0[256];		/* 变长的字符串 */
	char	vsvarstr1[256];		/* 变长的字符串 */
	char	vsvarstr2[256];		/* 变长的字符串 */
	char	vsvarstr3[256];		/* 变长的字符串 */
}__PACKED__ ST_PACKDATA_C;


typedef struct st_cpack_c
{
	ST_PACKHEAD_C head;
	ST_PACKDATA_C		pack;
}__PACKED__ ST_CPACK_C;


#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#pragma pack(pop)
#endif
#else
#pragma pack(pop)
#endif

//在将要传送的数据的结构中加入一个字段
//入口参数：pack：将要写入的结构
//          fieldid：将要加入字段的位图
//          data：字段内容，统一用字符串表示
//返回值：成功：TRUE
//        失败：FALSE
CPACK_API bool AddField_C(ST_CPACK_C *pack, int fieldid, char *data);

// 函数名: AddFieldI
// 编程  : 陈永华 2002-1-14 12:14:52
// 描述  : 以整型方式输入加pack字段内容
// 返回  : bool 
// 参数  : ST_CPACK *pack
// 参数  : int fieldid
// 参数  : int idata
CPACK_API bool AddFieldI_C(ST_CPACK_C *pack, int fieldid, int idata);


// 函数名: AddFieldD
// 编程  : 陈永华 2002-1-14 12:15:38
// 描述  : 以double方式输入加pack字段内容
// 返回  : bool 
// 参数  : ST_CPACK *pack
// 参数  : int fieldid
// 参数  : double ddata
CPACK_API bool AddFieldD_C(ST_CPACK_C *pack, int fieldid, double ddata);


//清除某个字段的位图, 
// 在实际使用中似乎没有用处
//入口参数：head：包头
//          fieldParam：将要清除的字段的位图
//返回值：成功：TRUE
//        失败：FALSE
CPACK_API bool ClearParmBit_C(ST_PACKHEAD_C *head, int fieldid);

//设置某个字段的位图
//入口参数：head：包头
//          fieldid：将要设置的字段的位图
//返回值：成功：TRUE
//        失败：FALSE
CPACK_API bool SetParmBit_C(ST_PACKHEAD_C *head, int fieldid);

CPACK_API BOOL DecodeBuf_C(unsigned char *buf,int len,ST_CPACK_C *pPack,char *eMsg);
CPACK_API BOOL DecodeBufWithArray_C(unsigned char *buf,int len,ST_CPACK_C *pPack,ST_PACKDATA_C *packArray,
                        int *recCount,char *eMsg);
CPACK_API BOOL EncodeBuf_C(ST_CPACK_C *pPack,unsigned char *buf,int *len,char *eMsg);
CPACK_API BOOL EncodeBufArray_C(ST_CPACK_C *pack,ST_PACKDATA_C *packArray,unsigned char *pbuf,int *size,char *eMsg);

#ifdef __cplusplus
}
#endif

#endif //__CPACKC_H__
