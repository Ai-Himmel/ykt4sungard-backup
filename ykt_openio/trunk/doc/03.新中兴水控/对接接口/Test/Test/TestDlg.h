// TestDlg.h : ͷ�ļ�
//

#pragma once
#pragma pack(1)
typedef struct Data_Info 
{
	int		cut_id;             //�ͻ�ID��(�ʺ�)
	char	physical_no[9];		//������
	char	old_physical_no[9];	//������
	int	    card_state;			//��״̬, 
	int     cut_type;			//�ͻ����, �ͻ������, ���ƶ�
								//Ӧ11, �о�����Ӧ13�ȵ�
	char	cut_type_name[51];  //�ͻ��������, ������, �о���
	char	cut_name[61];		//�ͻ�����
	char    volume[13];			//���°汾��
	char 	classdept_name[101];//��ϵ�˲�������, ����ϵ,��ѧϵ�ȵ�
	char 	stuemp_no[21];		//ѧ����
	char	sex[2];				//�Ա�(1Ϊ��, 2ΪŮ)
	int  	card_id;			//���׿���
	int     type_id;            //�����: (1��ʽ��, 2��ʱ��, 3
								//�Ǽ�����ʱ��, 4VIP������ʱ��, //5������ʱ��)
	char 	show_id[11];		//��ʾ����	
	int     area;				//�ͻ���������
	char    area_name[51];		//�ͻ�������������
	char	main_id[21];		//���֤��
	char	reg_time[31];		//�û�ע��ʱ��
	char	can_time[31];		//�û�ע��ʱ��
} Data_Info;
typedef struct Save_Info
{
    int		cut_id;		//�ͻ�ID��(�ʺ�)
    int     save_Money;	//ת�ʽ��,��ȷ����
    int     save_type;	//0=��Ǯ,1=����
}Save_Info;
#pragma pack()
typedef int (_stdcall *Third_InitDB)();
typedef int (_stdcall *Third_CloseDB)();
typedef int (_stdcall *Third_GetDataInfo) (Data_Info *in_pack, int *errcode);
typedef int (_stdcall *Third_SaveInfo) (Save_Info *in_pack,int *errcode);
// CTestDlg �Ի���
class CTestDlg : public CDialog
{
// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HINSTANCE			hTPECon;
	Third_CloseDB		TCloseDB;
	Third_InitDB		TInitDB;
	Third_GetDataInfo	TGetDataInfo;
	Third_SaveInfo		TSaveInfo;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
