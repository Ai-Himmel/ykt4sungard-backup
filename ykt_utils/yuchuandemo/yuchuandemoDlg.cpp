// yuchuandemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yuchuandemo.h"
#include "yuchuandemoDlg.h"
#include "yuchuandef.h"
#include "Public.h"
//#include "logfile.h"
#include ".\yuchuandemodlg.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string> 
#include <vector> 
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CyuchuandemoDlg �Ի���



CyuchuandemoDlg::CyuchuandemoDlg()
	: CPropertyPage(CyuchuandemoDlg::IDD)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyuchuandemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CyuchuandemoDlg, CPropertyPage)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_CONN, OnBnClickedBtnConn)
	ON_BN_CLICKED(ID_BTN_VERIFY_CLOCK, OnBnClickedBtnVerifyClock)
	ON_BN_CLICKED(ID_BTN_READ_CLOCK, OnBnClickedBtnReadClock)
	ON_BN_CLICKED(ID_BTN_READ_BLKVER, OnBnClickedBtnReadBlkver)
	ON_BN_CLICKED(ID_BTN_CLOSE, OnBnClickedBtnClose)
	ON_BN_CLICKED(ID_BTN_SETBLKVER, OnBnClickedBtnSetblkver)
	
	ON_EN_CHANGE(IDC_EDITAD, OnEnChangeEditad)
	ON_BN_CLICKED(IDC_BUTTONSIG, OnBnClickedButtonsig)
	ON_BN_CLICKED(IDC_BUTBAT, OnBnClickedButbat)
	ON_EN_CHANGE(ID_EDT_MACHINENO, OnEnChangeEdtMachineno)
	ON_BN_CLICKED(IDC_BUTTONVER, OnBnClickedButtonver)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTONCHECKALLTIME, OnBnClickedButtoncheckalltime)
END_MESSAGE_MAP()


// CyuchuandemoDlg ��Ϣ�������

BOOL CyuchuandemoDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetDlgItemText(ID_CMB_COMPORT,_T("COM1"));
	SetDlgItemText(ID_EDT_BAUD,_T("19200"));
	 AfxInitRichEdit();
	 CButton*  m_Check1   =   (CButton*)GetDlgItem(IDC_CHECK1);      
	if(m_Check1->GetCheck()   ==   BST_UNCHECKED)   
		m_Check1->SetCheck(BST_CHECKED);   
    else   
        m_Check1->SetCheck(BST_UNCHECKED);
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CyuchuandemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CyuchuandemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CyuchuandemoDlg::OnBnClickedBtnConn()
{
	CString v;
	CString csAppend;
	GetDlgItemText(ID_CMB_COMPORT,v);
	int  nLen=0;
	if(strncmp((LPCTSTR)v,"COM",3)!=0)
	{
		AfxMessageBox("��������ȷ�Ķ˿ں�");
		return;
	}
	int port;
	port = atoi((LPCTSTR)v.Mid(3))-1;
	int baud = GetDlgItemInt(ID_EDT_BAUD,FALSE);
	g_comhandle = OpenCommAuto(port,baud);
	if(g_comhandle==NULL)
	{
		AfxMessageBox("�򿪴���ʧ��...");
		return;
	}
	else 
	{
	   csAppend="�򿪴��ڳɹ�!";
	   WriteLog(0,csAppend);
	}
}
void CyuchuandemoDlg::SetTime(int NodId)
{
int termid;
	int hd=0;
	unsigned char DateTimes[255];
	int COM_Time=200;
	int nLen;
	CString v;
	char temp[20]="";
	CString IDstr;
	CString csAppend;
	char ss[15]="";
	SYSTEMTIME sys; 
	termid = GetDlgItemInt(IDC_EDITTIME,FALSE);
//	CTime now = CTime::GetCurrentTime();
    GetLocalTime( &sys ); 
    sprintf( ss,"%02d%02d%02d%02d%02d%02d",sys.wYear-2000,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond); 
    CPublic::Str2Hex(ss,DateTimes,6);
	sprintf(temp, "%d", NodId);
	IDstr.Format("%s",temp);
    hd=JS_SetNodeTime(g_comhandle,NodId,DateTimes,COM_Time);
   if (hd)
   {
	   csAppend=IDstr;
	   csAppend =csAppend+"�Ż�����ʱ��ʧ�ܣ�";
	   WriteLog(hd,csAppend);
   }
   else
   {   csAppend=IDstr;
	   csAppend =csAppend+"�Ż�����ʱ��ɹ���";
	   WriteLog(hd,csAppend);
   
   }

}
void CyuchuandemoDlg::WriteLog(int hd,CString WriteLog)
	{	
	CEdit *pEdit;	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITLOG);
	int  nLen=0;
	nLen = pEdit->GetWindowTextLength ();
	pEdit->SetFocus ();
    pEdit->SetSel(nLen, nLen);

	if (hd==DAS_OK)
	WriteLog=WriteLog+"    ���ݽ�������";
	else if (hd==Comm_Init_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺴��ڳ�ʼ������";
	else if (hd==CommPort_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺶˿ڴ���";
	else if (hd==CommPort_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺶˿ڴ���";
	else if (hd==Chksum_Err)
	WriteLog=WriteLog+"    ����ԭ��ͨѶ����Ч�����";
	else if (hd==Rev_Data_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺽�������ʧ�ܣ�";
	else if (hd==TIME_OUT_Err)
	WriteLog=WriteLog+"    ����ԭ��ͨѶ��ʱ����";
	else if (hd==Para_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺲�������";
	else if (hd==Send_Data_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺷�������ʧ�ܣ�";
	else if (hd==Get_status_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺽���״̬λ����";
	else if ((hd==No_Data_Return)||(hd==No_BIN_Files)||(hd==Read_Files_ERR))
	WriteLog=WriteLog+"    ����ԭ��û�����ݷ��أ�";
	else if (hd==CRC_ERR)
	WriteLog=WriteLog+"    ����ԭ��CRCЧ�����";
	else if (hd==Rev_LEN_Err)
	WriteLog=WriteLog+"    ����ԭ�򣺽��ճ��������";
	else if (hd==Password_Err)
	WriteLog=WriteLog+"    ����ԭ����Ȩ�������";
	else if (hd==Password_Para_Err)
	WriteLog=WriteLog+"    ����ԭ�������ʽ����";
	else if (hd==Encrypt_Err)
	WriteLog=WriteLog+"    ����ԭ�����ݼ��ܴ���";
	else if (hd==Wrong_DEV_Err)
	WriteLog=WriteLog+"    ����ԭ���豸����ID�Ų�����";
	else if (hd==No_Record_Err)
	WriteLog=WriteLog+"    ����ԭ��û����ˮ��";
	else
    WriteLog=WriteLog+"    ";
	WriteLog = WriteLog+"\r\n";
	pEdit->ReplaceSel (WriteLog);
	nLen = pEdit->GetLineCount();
	//pEdit->LineScroll(nLen, nLen);
	//pEdit->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_BOTTOM,0),0);
	if( nLen >= 150 )
	{
		pEdit->SetWindowText("");
	}
	}
void CyuchuandemoDlg::OnBnClickedBtnVerifyClock()
{
	int NodId;
	TEST_COM_OPEN_NORET;
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
	SetTime(NodId);
}

void CyuchuandemoDlg::OnBnClickedBtnReadClock()
{
    char s[100];
	int NodId;
	int hd=0;
	CString ss;
	unsigned char DateTimes[13]="";
	char ww[20]="";
	int COM_Time=500;
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
	TEST_COM_OPEN_NORET;
	memset(DateTimes,0,sizeof(DateTimes));
    hd=JS_GetNodeTime(g_comhandle,NodId,DateTimes,COM_Time);
    CPublic::Hex2Str(DateTimes,6,s);
	ss=s[0];
	ss=ss+s[1];
	ss=ss+"��";
	ss=ss+s[2];
	ss=ss+s[3];
	ss=ss+"��";
	ss=ss+s[4];
	ss=ss+s[5];
	ss=ss+"��";
	ss=ss+s[6];
	ss=ss+s[7];
	ss=ss+"��";
	ss=ss+s[8];
	ss=ss+s[9];
	ss=ss+"��";
	ss=ss+s[10];
	ss=ss+s[11];
	ss=ss+"��";
    if (hd)
   { 
     ss="��ȡ�豸ʱ��ʧ��!";
	 WriteLog(hd,ss);
   }
	else
	{
	WriteLog(hd,ss);
	}
/*
	int NodId=1;
	int hd=0;
	unsigned int Addressdata;
    unsigned long Device_UID=0x85004F83;
	unsigned long REC_Number=2;
	int COM_Time=200;
	JS_RECORD ss;
	memset(&ss,0,sizeof(ss));
  hd=JS_GET_APPOINTED_RECORD(g_comhandle,NodId,REC_Number,Device_UID,ss,COM_Time);
 
    if (hd)
   {
   AfxMessageBox("��ȡ�汾ʧ��...");
   }
*/

}

void CyuchuandemoDlg::OnBnClickedBtnReadBlkver()
{
	int NodId=0;
	int hd=0;
	unsigned char verdata[50]="";
	unsigned long Device_UID;
    CString v;
	char s[100]="";
	CString log;
	char UID[20]="";
	int COM_Time=200;
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
	GetDlgItemText(ID_EDT_MACHINENO,v);
	memcpy(UID,v,strlen(v));
	Device_UID=strtoul(UID,NULL,16);
	TEST_COM_OPEN_NORET;
    hd=JS_GET_Black_Version(g_comhandle,NodId,verdata,Device_UID,COM_Time);
	 CPublic::Hex2Str(verdata,6,s);
       if (hd)
   {
	   log="��ȡ�汾ʧ��";
       WriteLog(hd,log);
   }
	   else
   {
	 log="�汾��";
	 v.Format("%s",s);
     log=log+v;
     WriteLog(hd,log);
    }
}

void CyuchuandemoDlg::OnBnClickedBtnClose()
{
	int hd;
	CString csAppend;
	hd=CloseComm(g_comhandle);
	g_comhandle = NULL;
	if (hd)
	{
	csAppend="�رմ���ʧ��!";
	WriteLog(hd,csAppend);
	}
	else
	{
    csAppend="�رմ��ڳɹ�!";
	WriteLog(hd,csAppend);
	}
}

void CyuchuandemoDlg::OnBnClickedBtnSetblkver()
{
    int NodId=0;
	int hd=0;
	unsigned char verdata[12]="";
	unsigned long Device_UID=0;
    CString v;
	CString log;
	char UID[20]="";
	int COM_Time=200;
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
	GetDlgItemText(ID_EDT_MACHINENO,v);
	memcpy(UID,v,strlen(v));
	Device_UID=strtoul(UID,NULL,16);
	GetDlgItemText(IDC_EDITBLACK,v);
	CPublic::Str2Hex(v,verdata,12);
   hd=JS_SET_Black_Version(g_comhandle,NodId,verdata,Device_UID,COM_Time);
       if (hd)
   {
	   log="���ú������汾ʧ��";
       WriteLog(hd,log);
   }
	   else
   {
	 log="�汾��";
     log=log+v;
     WriteLog(hd,log);
    }

}





void CyuchuandemoDlg::OnEnChangeEditad()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CyuchuandemoDlg::OnBnClickedButtonsig()
{
	int NodId;
	int hd=0;
	CString v;
	CString log;
    int Addressdata;
    unsigned long   Device_UID;
	int result;
	int COM_Time=200;
	char uid[20]="";
	Addressdata=GetDlgItemInt(IDC_EDITNODID2,FALSE);
	 CButton*  m_Check1   =   (CButton*)GetDlgItem(IDC_CHECK1);      
	if(m_Check1->GetCheck() ==BST_UNCHECKED) 
	{
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
	}
	else
	{
	NodId=0XFFFF;
	}
	TEST_COM_OPEN_NORET;
	GetDlgItemText(ID_EDT_MACHINENO,v);
	memcpy(uid,v,strlen(v));
	Device_UID=strtoul(uid,NULL,16);
//	unsigned long   Device_UID=0x85004f83;
   hd=JS_UID_SET_Address(g_comhandle,NodId,Addressdata,Device_UID,COM_Time);
   
   //hd=JS_SET_Address(g_comhandle,1,11,COM_Time);
   if (hd)
   {
       log="���û��ųɹ�ʧ��";
       WriteLog(hd,log);
   }
   else
   {
        log="���û��ųɹ�";
       WriteLog(hd,log);
   }
}

void CyuchuandemoDlg::OnBnClickedButbat()
{
  CString csAppend;
  CString SS;
  CString errwritelog;
  CString sucwritelog;
   string linestr;
   unsigned long Device_UID;
   unsigned char DateTimes[13]="";
   int NodId=0XFFFF;
   unsigned int Addressdata;
   char  *PhiId;
   char  *AddId;
   int    hd;
   int COM_Time=1000;
   char delim[] = ",";
   char str[20]="";
   char *token;
   char ph[20]="";
   char ad[20]="";
   CString   g_CurrentPath;   
   char   buf[1000];  
   vector <string> v; 
   TEST_COM_OPEN_NORET;
   CFileDialog   DlgOpenFile( TRUE, ".csv", NULL,OFN_EXPLORER,"Text Files(*.csv)|*.csv|All Files(*.*)|*.*",this);   
   int iResult =DlgOpenFile.DoModal();   
    if( iResult !=IDOK)   
   {   
     return;   
    }       
    CString cstrFilePath = DlgOpenFile.GetPathName(); 
	g_CurrentPath=cstrFilePath;
   ifstream in(cstrFilePath);  
    while(getline(in, linestr)) 
    v.push_back(linestr); 
    for(int i = 0; i<v.size(); i++) 
     {	
	  linestr=v[i];
      strcpy( str,linestr.c_str());
      AddId   = strtok(str, delim);  
      PhiId  = strtok(NULL, delim);
	  strcpy(ad,AddId);
	  strcpy(ph,PhiId);
	  Addressdata=(unsigned int)strtol(ad, NULL, 10); 
	 // Device_UID=(unsigned long)strtol(ph, NULL, 16); 
	  Device_UID=strtoul(ph,NULL,16);
	  hd=JS_UID_SET_Address(g_comhandle,NodId,Addressdata,Device_UID,COM_Time);
	  hd=JS_GetNodeTime(g_comhandle,Addressdata,DateTimes,COM_Time);
	  if (hd)
	  {
		  //������û��Ų��ɹ���������10��
		  for (int reset=0;reset<10;reset++)
		  {
           hd=JS_UID_SET_Address(g_comhandle,NodId,Addressdata,Device_UID,COM_Time);
		    hd=JS_GetNodeTime(g_comhandle,Addressdata,DateTimes,COM_Time);
			if (hd==0)
				break;
		  }
	  }
	  if (hd)
	    {
	   SS.Format("%s",ad);
	   csAppend=SS;
	   SS.Format("%s",ph);
	   csAppend=csAppend+"," +SS;
	   errwritelog=errwritelog+csAppend+"\r\n";
	   WriteLog(hd,csAppend);
	    } 
	    else 
		{ 
	    SS.Format("%s",ad);
		csAppend=SS;
	    SS.Format("%s",ph);
	    csAppend=csAppend+"," +SS+",  �ɹ���";
		sucwritelog=sucwritelog+csAppend+"\r\n";
		 WriteLog(hd,csAppend);
		}
      } 
    //   GetCurrentDirectory(1000,buf);   
    //   g_CurrentPath = buf;  
	  // g_CurrentPath=g_CurrentPath+"result.csv";
	 if (hd)
	 {
		 g_CurrentPath=g_CurrentPath+"err.csv";
		  CStdioFile  File;
        File.Open(g_CurrentPath,CFile::modeCreate|CFile::modeReadWrite);
        File.WriteString(errwritelog);
	 }
	 else
	 {
      g_CurrentPath=g_CurrentPath+"success.csv";
	   CStdioFile  File;
        File.Open(g_CurrentPath,CFile::modeCreate|CFile::modeReadWrite);
        File.WriteString(sucwritelog);
	 }
       
	


 // m_editSrcPath.SetWindowText(   cstrFilePath   );
}

void CyuchuandemoDlg::OnEnChangeEdtMachineno()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CyuchuandemoDlg::OnBnClickedButtonver()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString v;
	CString log;
	int hd;
	int COM_Time=200;
	CString ss;
	int NodId;
	char uid[10]="";
	unsigned char passwd[15]="";
    unsigned char Device_UID[20];
	//wchar_t VER[6] ;
	char VER[20]; 
    //char	verstr[20]="";
    //wchar_t   MCU_TYP[12];
	//char MCU[20]="";
	char  MCU_TYP[12];
    unsigned int Addressdata;
	TEST_COM_OPEN_NORET;
	GetDlgItemText(ID_EDT_MACHINENO,v);
	memcpy(Device_UID,v,strlen(v));
	NodId=GetDlgItemInt(IDC_EDITAD,FALSE);
    hd=JS_ShakeHand(g_comhandle,NodId,(unsigned char *)passwd,(LPSTR)VER,(LPSTR)MCU_TYP,(unsigned char *)Device_UID,COM_Time);

   if (hd)
   {
       log="��ȡ�汾ʧ��";
       WriteLog(hd,log);
   }
   else
   {
	log="��ȡ�汾�ɹ�,UID:";
	//sprintf(uid,"%s",10,Device_UID);
	memcpy(uid,Device_UID,sizeof(uid));
	uid[10]='\0';
    ss.Format("%s",uid);
	log=log+ss;
	log=log+"�汾��";
	//wchar_t to char   
//	CPublic::wcharTochar(VER, verstr, sizeof(verstr));  
//	sprintf(uid,"%s",verstr);
	//WideCharToMultiByte(CP_ACP,0,ss,100,VER.GetBuffer(0),100,NULL,NULL);
   // WideCharToMultiByte( CP_ACP, 0, VER, -1,verstr, 100, NULL, NULL );  
	VER[12]='\0';
	ss.Format("%s",VER);   
	log=log+ss;
	log=log+"MCU:";
	MCU_TYP[10]='\0';
	ss.Format("%s",MCU_TYP);
	log=log+ss;
    WriteLog(hd,log);
   }
}


void CyuchuandemoDlg::OnBnClickedButtonclear()
{
	 CEdit *pEdit;	
	pEdit = (CEdit *)GetDlgItem(IDC_EDITLOG);
    pEdit->SetWindowText("");
}

void CyuchuandemoDlg::OnBnClickedButtoncheckalltime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int BeginNodId;
	int EndNodId;
	BeginNodId=GetDlgItemInt(IDC_EDITBG,FALSE);
	EndNodId=GetDlgItemInt(IDC_EDITED,FALSE);
	TEST_COM_OPEN_NORET;
	for(int i=BeginNodId;i<=EndNodId;i++)
	{
	SetTime(i);
	}
}
