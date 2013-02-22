//---------------------------------------------------------------------------

#ifndef testsmartdllH
#define testsmartdllH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//#include "CSIntf.hpp"
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *BtnReadCardSerialNo;
        TButton *BtnConnCom;
        TGroupBox *GroupBox1;
        TEdit *EdtCardSerialNo;
        TLabel *Label1;
        TButton *BtnCleanCard;
        TButton *BtnGrantRight;
        TButton *BtnReadCardStateInfo;
    TEdit *edtCardNo;
        TLabel *Label2;
        TButton *BtnPublishCard;
        TButton *BtnReadPersonInfo;
        TLabel *Label3;
    TEdit *edtLibraryNo;
    TLabel *lbl1;
    TComboBox *cbbWorkKey;
    TLabel *lbl;
    TEdit *edtID;
    TLabel *lblDealLineDate;
    TEdit *edtDealLineDate;
    TLabel *lblCardType;
    TEdit *edtCardType;
    TLabel *lbl2;
    TEdit *edtName;
    TLabel *lbl3;
    TEdit *edtStudentNo;
    TLabel *lblSex;
    TEdit *edtSex;
    TLabel *lblDept;
    TEdit *edtDept;
    TLabel *lblBalance;
    TEdit *edtBalance;
    TLabel *lbl4;
    TEdit *edtTxCnt;
    TLabel *lbl5;
    TEdit *edtDayBala;
    TLabel *lbl6;
    TEdit *edtPwd;
    TLabel *lblTxDate;
    TEdit *edtTxDate;
    TLabel *lbl7;
    TEdit *edtTxTime;
    TButton *btnAddMoney;
    TEdit *edtAddMoney;
    TButton *btnDecMoney;
    TEdit *edtDecMoney;
    TButton *btnReadPackMoney;
    TButton *btnUpdCardNo;
    TButton *btnUpdPwd;
    TButton *btnClear;
    TLabel *lblShowCardNo;
    TEdit *edtShowCardNo;
    TButton *btnDecode;
    TButton *btnEnCode;
    TEdit *edtWorkKey;
    TCheckBox *chkDebug;
    TButton *btnFmtCard;
    TButton *btnReset;
    TButton *btnCloseCom;
    TButton *btnSetMoney;
    TEdit *edtSetMoney;
    TButton *btnReadAuthCard;
    TButton *btnCheckCard;
    TStaticText *txtMsg;
    TButton *btnReadBlock;
    TEdit *edtSectorNo;
    TLabel *lbl8;
    TLabel *lbl9;
    TEdit *edtBlockNo0;
    TEdit *edtBlockNo1;
    TLabel *lbl10;
    TEdit *edtBlockNo2;
    TLabel *lbl11;
    TLabel *lbl12;
    TEdit *edtBlockNo3;
    TLabel *lbl13;
    TRadioGroup *rg1;
    TEdit *edtKeyA;
    TEdit *edtKeyB;
    TButton *btnCalKey;
    TButton *btnReadVersion;
    TEdit *edtVersion;
    TLabel *lblVersion;
    TCheckBox *chkVersion;
    TButton *btnCardInit;
    TButton *btnResetPack;
    TButton *btnSetPacket;
        TBitBtn *BitBtn1;
        void __fastcall BtnConnComClick(TObject *Sender);
        void __fastcall BtnReadCardSerialNoClick(TObject *Sender);
        void __fastcall BtnGrantRightClick(TObject *Sender);
        void __fastcall BtnReadCardStateInfoClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall BtnPublishCardClick(TObject *Sender);
        void __fastcall BtnReadPersonInfoClick(TObject *Sender);
    void __fastcall btnAddMoneyClick(TObject *Sender);
    void __fastcall btnDecMoneyClick(TObject *Sender);
    void __fastcall btnReadPackMoneyClick(TObject *Sender);
    void __fastcall btnUpdCardNoClick(TObject *Sender);
    void __fastcall btnUpdPwdClick(TObject *Sender);
    void __fastcall btnClearClick(TObject *Sender);
    void __fastcall BtnCleanCardClick(TObject *Sender);
    void __fastcall btnDecodeClick(TObject *Sender);
    void __fastcall btnEnCodeClick(TObject *Sender);
    void __fastcall chkDebugClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnFmtCardClick(TObject *Sender);
    void __fastcall btnResetClick(TObject *Sender);
    void __fastcall btnCloseComClick(TObject *Sender);
    void __fastcall btnSetMoneyClick(TObject *Sender);
    void __fastcall btnReadAuthCardClick(TObject *Sender);
    void __fastcall btnCheckCardClick(TObject *Sender);
    void __fastcall btnReadBlockClick(TObject *Sender);
    void __fastcall rg1Click(TObject *Sender);
    void __fastcall btnCalKeyClick(TObject *Sender);
    void __fastcall btnReadVersionClick(TObject *Sender);
    void __fastcall btnCardInitClick(TObject *Sender);
    void __fastcall btnResetPackClick(TObject *Sender);
    void __fastcall btnSetPacketClick(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#pragma pack(1)

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
		DWORD RemainMoney;			// 电子钱包余额
		WORD DealTimes;				// 用户卡交易流水号
		BYTE DealYear;				// 交易日期
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// 累计交易次数(当前时间段内)
		BYTE DealTimes_CurDay;		// 累计交易次数(当日内)
} LOOPPURSEINFO ,*LPLOOPPURSEINFO;
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
#pragma pack()

typedef void (CALLBACK* LPSMT_GetLastErr)(int* pErrCode,char *Msg);
typedef INT (CALLBACK* LPSMT_Login_Card)(int sector);
typedef INT (CALLBACK* LPSMT_WriteBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
typedef INT (CALLBACK* LPSMT_ReadBlock)(int Sector,int BlockNo, unsigned char *BlockBuf);
typedef INT (CALLBACK* LPSMT_Login_With_UserKey)(int Sector,unsigned char *Buffer,int PaDSelect);

typedef INT (CALLBACK* LPSMT_ConnectMF280)(int ,int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);
typedef INT (CALLBACK* LPSMT_CreateGreyCard)(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8]);
typedef INT (CALLBACK* LPSMT_ResetCard)();
typedef INT (CALLBACK* LPSMT_WriteCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_PacketAddMomey)(int ,int );
typedef INT (CALLBACK* LPSMT_PacketDelMomey)(int ,int );
typedef INT (CALLBACK* LPSMT_PacketSetMoney)(int ,int );
typedef INT (CALLBACK* LPSMT_AutoDll)(unsigned char *);
typedef INT (CALLBACK* LPSMT_JudgeAutoFlag)();
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo[20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1], unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ReadPersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo [20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1] ,unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeName)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDutyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCerificateNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeDepartmentNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeIdentifyNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeSexNo)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ReadPacketInfo)(int,LOOPPURSEINFO *LoopPurseInfo);
typedef INT (CALLBACK* LPSMT_ChangeDeadLineDate)(unsigned char *);
typedef INT (CALLBACK* LPSMT_ChangeCardRightType)(unsigned char ucCardRightType[1]);
typedef INT (CALLBACK* LPSMT_WritePersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ReadPersonalPassword)(unsigned char PersonalPsd[3]);
typedef INT (CALLBACK* LPSMT_ClearCard)();
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef INT (CALLBACK* LPSMT_ReadAuthCard)(unsigned char ucWorkKey[8]);
typedef INT (CALLBACK* LPSMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_WriteLibraryNo)(unsigned char ucLibraryNo[13]);
typedef INT (CALLBACK* LPSMT_ChangeCardNo)(unsigned char ucCardNo[20]);
typedef INT (CALLBACK* LPSMT_ChangeDealCardNo)(int nDealCardNo);
typedef INT (CALLBACK* LPSMT_ResetPacketInfo)(int nPacketNo);
typedef INT (CALLBACK* LPSMT_GetPacketInfo)(int nPacketNo,MONEY_PACK_INFO *pPackInfo);
typedef INT (CALLBACK* LPSMT_SetPacketInfo)(int nPacketNo,MONEY_PACK_INFO *pPackInfo);
typedef INT (CALLBACK* LPSMT_SetNormalFlagByBlkVerion)(char *blkver);
typedef INT (CALLBACK* LPSMT_ReadBlackNameListVersion)(int *flag,char *version);
//KS DLL
////////////////////////////////////////////////////////////////////////////////
typedef int (CALLBACK* LPKS_ConnectMF)(int com,int baud);
typedef int (CALLBACK* LPKS_PublishCard)(TPublishCard *pc);
typedef int (CALLBACK* LPKS_GetLastErrMsg)(int ecode[1],char *errmsg);
#endif
