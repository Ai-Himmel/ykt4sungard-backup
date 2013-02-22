// extracardDlg.h : header file
//

#if !defined(AFX_EXTRACARDDLG_H__59C71837_3494_4A0C_80D8_BA98F4A4F0F3__INCLUDED_)
#define AFX_EXTRACARDDLG_H__59C71837_3494_4A0C_80D8_BA98F4A4F0F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExtracardDlg dialog

class CExtracardDlg : public CDialog
{
private:
	bool _comOpen;
// Construction
public:
	CExtracardDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExtracardDlg)
	enum { IDD = IDD_EXTRACARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtracardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExtracardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnCom();
	afx_msg void OnBtnReadauthcard();
	afx_msg void OnBtnReadcard();
	afx_msg void OnBtnInitcard();
	afx_msg void OnBtnTrans();
	afx_msg void OnBtnNewcard();
	afx_msg void OnBtnInitcommcard();
	afx_msg void OnBtnInitclearcard();
	afx_msg void OnBtnInitauthcard();
	afx_msg void OnBtnReadstudentno();
	afx_msg void OnBtnReadpassword();
	afx_msg void OnBtnReadphyid();
	afx_msg void OnBtnReadblakflag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnVerifypwd();
};


#ifdef __cplusplus
extern "C" {
#endif

#pragma  pack(1)
typedef struct _LOOPPURSEINFO
{
		DWORD RemainMoney;// 电子钱包余额
		WORD DealTimes;// 卡片交易流水号
		BYTE DealYear; //交易日期
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime; // 累计交易次数(当前时间段内)
		BYTE DealTimes_CurDay;// 累计交易次数(当日内)
} LOOPPURSEINFO,*LPLOOPPURSEINFO;
typedef struct 
{
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct               
{
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char CardNo[8];				//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						//用户卡使用权限类型（1--254）
	unsigned char ucName[9];				//姓名
	unsigned char ucDutyNo[9];				//职务代码
	unsigned char ucCertificateNo[21];		//证件号码
	unsigned char ucDepartmentNo[11];		//部门编号
	unsigned char ucIdentifyNo[5];			//身份代码
	unsigned char ucSexNo[2];				//性别代码
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					//卡密码
	unsigned char ucLibraryNo[21];			//图书证号
	int Money;								//金额（分）
	unsigned char isFormat;					//是否格式化第一扇区
}TPublishCard;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5

#pragma  pack()

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
		return -1

//////////////////////////////////////////////////////////////////////////
//接口函数
/** 
 * @brief 加载39提供的接口动态库
 * 
 * @return 成功返回 0 ，失败返回 -1
 */
int LoadSmartCom411DXQ();
/** 
 * @brief 释放39动态库
 */
void CloseSmartCom411DXQ();
//////////////////////////////////////////////////////////////////////////
// 导入函数
DCLR_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_DLLFUNC(int,CloseMF,());
//DCLR_DLLFUNC(int,SMT_ControlBuzzer,());
DCLR_DLLFUNC(int,SMT_AutoDll,(unsigned char *ucWorkingKey));
//DCLR_DLLFUNC(int,SMT_ReadBlackNameListVersion,(int *flag, char *version));
//DCLR_DLLFUNC(int,SMT_PacketAddMomey,(int nPacketNo,int nMoney));
//DCLR_DLLFUNC(int,SMT_PacketDelMomey,(int nPacketNo,int nMoney));
//DCLR_DLLFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
//DCLR_DLLFUNC(int,SMT_ReadPacketInfo,(int nPacketNo,LOOPPURSEINFO *LoopPurseInfo));
//DCLR_DLLFUNC(int,SMT_SetPacketInfo,(int nPacketNo,MONEY_PACK_INFO *pPackInfo));
//DCLR_DLLFUNC(int,SMT_GetPacketInfo,(int nPacketNo,MONEY_PACK_INFO *pPackInfo));
DCLR_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_DLLFUNC(int,SMT_VerifyPersonalPassword,(unsigned char PersonalPsd[3]));
// DCLR_DLLFUNC(int,SMT_ReadCardStateInfo,(unsigned char ucShowCardNo[5],
// 								   int nDealCardNo[1],
// 								   unsigned char ucDeadLineDate[3],
// 								   unsigned char ucCardRightType[1]));
//DCLR_DLLFUNC(int,SMT_ReadBlock,(int Sector,int BlockNo, unsigned char *BlockBuf));
//DCLR_DLLFUNC(int,SMT_WriteBlock,(int Sector,int BlockNo,unsigned char *BlockBuf));
//DCLR_DLLFUNC(int,Login_Card,(int sector));
//DCLR_DLLFUNC(int,SMT_ReadAuthCard2,(unsigned char ucWorkKey[8],short * flag));
// DCLR_DLLFUNC(int,SMT_ReadWaterPackInfo,(WATER_PACK_INFO* info));
// DCLR_DLLFUNC(int,SMT_InitWaterInfo,(const WATER_PACK_INFO* info));
// DCLR_DLLFUNC(int,SMT_WriteWaterPackInfo,(WATER_PACK_INFO* info));
// DCLR_DLLFUNC(int,SMT_WaterSetCapability,(int value));
// DCLR_DLLFUNC(int,SMT_WaterNewAuthCard,());
//DCLR_DLLFUNC(int,SMT_ReadPersonalPassword,(unsigned char PersonalPsd[3]));
DCLR_DLLFUNC(int,ReadCardInfo,(TPublishCard *pc));
DCLR_DLLFUNC(int,bcd2dec,(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr));
DCLR_DLLFUNC(int,dec2bcd,(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len));

#ifdef __cplusplus
}
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTRACARDDLG_H__59C71837_3494_4A0C_80D8_BA98F4A4F0F3__INCLUDED_)
