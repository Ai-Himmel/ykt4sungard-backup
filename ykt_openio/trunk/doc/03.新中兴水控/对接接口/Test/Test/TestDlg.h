// TestDlg.h : 头文件
//

#pragma once
#pragma pack(1)
typedef struct Data_Info 
{
	int		cut_id;             //客户ID号(帐号)
	char	physical_no[9];		//物理卡号
	char	old_physical_no[9];	//物理卡号
	int	    card_state;			//卡状态, 
	int     cut_type;			//客户类别, 客户的身份, 本科对
								//应11, 研究生对应13等等
	char	cut_type_name[51];  //客户类别名称, 本科生, 研究生
	char	cut_name[61];		//客户姓名
	char    volume[13];			//更新版本号
	char 	classdept_name[101];//联系人部门名称, 生物系,化学系等等
	char 	stuemp_no[21];		//学工号
	char	sex[2];				//性别(1为男, 2为女)
	int  	card_id;			//交易卡号
	int     type_id;            //卡类别: (1正式卡, 2临时卡, 3
								//非记名临时卡, 4VIP记名临时卡, //5记名临时卡)
	char 	show_id[11];		//显示卡号	
	int     area;				//客户所在区域
	char    area_name[51];		//客户所在区域名称
	char	main_id[21];		//身份证号
	char	reg_time[31];		//用户注册时间
	char	can_time[31];		//用户注销时间
} Data_Info;
typedef struct Save_Info
{
    int		cut_id;		//客户ID号(帐号)
    int     save_Money;	//转帐金额,精确到分
    int     save_type;	//0=存钱,1=冲正
}Save_Info;
#pragma pack()
typedef int (_stdcall *Third_InitDB)();
typedef int (_stdcall *Third_CloseDB)();
typedef int (_stdcall *Third_GetDataInfo) (Data_Info *in_pack, int *errcode);
typedef int (_stdcall *Third_SaveInfo) (Save_Info *in_pack,int *errcode);
// CTestDlg 对话框
class CTestDlg : public CDialog
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HINSTANCE			hTPECon;
	Third_CloseDB		TCloseDB;
	Third_InitDB		TInitDB;
	Third_GetDataInfo	TGetDataInfo;
	Third_SaveInfo		TSaveInfo;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
