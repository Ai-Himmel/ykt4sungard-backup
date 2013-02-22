// SupCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "SupCardDlg.h"
#include "MainFrm.h"
#include "InputPwd.h"
#include "des.h"
#include <vector>
#include "global_func.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupCardDlg dialog
IMPLEMENT_DYNCREATE(CSupCardDlg, CDialog)

CSupCardDlg::CSupCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSupCardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSupCardDlg)
	//}}AFX_DATA_INIT
	bGetKey=false;
}


void CSupCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSupCardDlg)
	DDX_Control(pDX, IDC_CMB_SAM, m_cbxSamNo);
	DDX_CBIndex(pDX, IDC_CMB_SAM, m_iSamNo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSupCardDlg, CDialog)
	//{{AFX_MSG_MAP(CSupCardDlg)
	ON_BN_CLICKED(IDC_BTN_READKEYCARD, OnBtnReadkeycard)
	ON_BN_CLICKED(IDC_PUBLISHSUPERCARD, OnPublishsupercard)
	ON_BN_CLICKED(IDC_BTN_RECYCLESUPERCARD, OnBtnRecyclesupercard)
	ON_BN_CLICKED(IDC_BTN_PSAMRESET, OnBtnPsamreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSupCardDlg message handlers

void CSupCardDlg::OnBtnReadkeycard() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
	char sKeyCardPin[7]={0};
	CInputPwd dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	
	CString cs;
	int nRet=0;
	char sMsg[128];
	unsigned long _Snr;
	byte rlen=0,rBuff[256];
	unsigned char sSendData[256];
	unsigned char nSendDatalen=0;
	unsigned char sRespData[256];
	unsigned char nRespDatalen=0;
	char sCardPhyID[9];

	_Snr=0;
	memset(rBuff,0,sizeof rBuff);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	rlen=0;
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
		pMainFrame->ShowLog("����Կ��ʧ��,�����Կ��");
		//		AfxMessageBox("����Կ��ʧ��,�����Կ��");
		return ;
	}
	memset(&CardMainKey,0,sizeof(CardMainKey));
	Sleep(100);
	bGetKey=false;
	ks_beep();
	pMainFrame->ShowLog("ȡ��Կ�ɹ�");
}

void CSupCardDlg::OnPublishsupercard() 
{
	/*
	UpdateData();
	if(!bGetKey)
	{
		AfxMessageBox("���ȶ���Կ��װ����Կ");
		return ;
	}
	ST_SUPERCARDKEY SuperCardKey;
	unsigned char *KeyArray[]={
		 CardMainKey.DPK1,	//��������Կ1
		 CardMainKey.DPK2,	//��������Կ2
		 SuperCardKey.DPK3,	////��������Կ3
		 CardMainKey.DTAC1,	//TAC����Կ1
		 CardMainKey.DTAC2,	//TAC����2
		 SuperCardKey.DTAC3,//TAC����3
		 CardMainKey.DUK,	//PIN����
		 CardMainKey.DRPK,	//PIN��װ
		 CardMainKey.DAMK,	//Ӧ��ά����Կ����Կ
		 CardMainKey.DACK,	//Ӧ��������Կ����Կ
		 CardMainKey.DLK1,	//Ȧ������Կ1
		 SuperCardKey.DLK2, //Ȧ������Կ2
		 SuperCardKey.DLK3,	//Ȧ������Կ3
		 SuperCardKey.NPK1,	//�ڲ���֤����Կ
		 SuperCardKey.EPK1, //�ⲿ����Կ1
		 SuperCardKey.EPK2, //�ⲿ����Կ2
		 SuperCardKey.EPK2, //�ⲿ����Կ3
		 CardMainKey.DAMK,  //Ӧ��ά����Կ����Կ
		 SuperCardKey.EPK4 //�ⲿ����Կ4
	};
	int iArraySize=sizeof(KeyArray)/sizeof(unsigned char*);
	memset(&SuperCardKey,0xFF,sizeof(SuperCardKey));
	int ret=0;
	vector<string> CmdVector;
	string sMsg;
	string sCmd;
	char sHexStr[64];
	int uCmdLen=0;
	BYTE uCmd[256],uResp[256],uRespLen;
	memset(sHexStr,0,sizeof(sHexStr));
	memset(uCmd,0,sizeof(uCmd));
	memset(uResp,0,sizeof(uResp));
	//��λ�ϵ�
	BYTE rlen,rbuf[256];
	CmdVector.push_back("ATR");
	sCmd="808A00002A3F00 10  00 FFFF 01   00 0082  FF 81 FFFFFF 0F 7378312E73682EC9E7BBE1B1A3D5CFFF 00180100010002030300";
	CmdVector.push_back(sCmd);
	//DIR�ļ�
	sCmd="80800000  080001 34  00 0040 00 02";
	//;��Ƭ������Ϣ�ļ�
	sCmd="80800000  080015 31  00 0015 00 02";
	CmdVector.push_back(sCmd);
	//Ӧ�ù�����Ϣ�ļ�
	sCmd="80800000  080017 31  00 0026 00 02";
	CmdVector.push_back(sCmd);
	//д�빫����Ϣ�ļ�����
	sCmd="00D69700 19 01 2900ffffffffffff 403fffffffffffff 20050701 20201231";
	CmdVector.push_back(sCmd);
	//
	sCmd="80800000  08EF11 30  30 0034 FF 04";
	CmdVector.push_back(sCmd);
	//PBOCDESӦ��
	sCmd="80800000  2ADF01 20  00 FFFF 00   00 0482  FF 81      FFFFFF 06 D15600000590FFFFFFFFFFFFFFFFFFFF 00180100010002030300";
	CmdVector.push_back(sCmd);
	//�ϵ縴λ
	sCmd="ATR";
	CmdVector.push_back(sCmd);
	//
	sCmd="00A40000 02DF01";
	CmdVector.push_back(sCmd);
	//
	sCmd="80800000  08EF11 30  30 0282 FF 04";
	CmdVector.push_back(sCmd);
	//�ϵ縴λ
	sCmd="ATR";
	CmdVector.push_back(sCmd);
	//
	sCmd="00A40000 02DF01";
	CmdVector.push_back(sCmd);
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λ����");
				return;
			}
			continue;
		}
		string_replace(sCmd," ","");
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
		if(ret)
		{
			sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
			((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
			return;
		}
		sMsg=">>"+sCmd+"OK";
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	}
	BYTE uBuf[256];	
	BYTE uMacData[128];
	BYTE uOutBuf[128];
	int  iOutLen=0;
	BYTE uMac[4];
	des3_context ctx3;
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);

	for(i=0;i<iArraySize;i++)
	{
		//ȡ�����
		memset(uCmd,0,sizeof(uCmd));
		memset(uResp,0,sizeof(uResp));
		memset(uBuf,0,sizeof(uBuf));
		memset(uOutBuf,0,sizeof(uOutBuf));
		memset(uMacData,0,sizeof(uMacData));
		sCmd="0084000008";
		hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
		ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
		if(ret)
		{
			sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
			((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
			return;
		}
		sMsg=">>"+sCmd+"OK";
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
		memcpy(uBuf,"\x18\x27",2);
		uBuf[2]=i+1;
		memcpy(uBuf+3,"\x00\x00\x00\x00\x00\x00",6);
		memcpy(uBuf+9,KeyArray[i],16);//test
		//����
		////////////////////////////////
		ks_encryptkey(uKey,2,uBuf,25,uOutBuf,iOutLen);
		memcpy(uCmd,"\x84\xD4\x00\x11\x24",5);
		memcpy(uCmd+5,uOutBuf,iOutLen);
		memcpy(uMacData,uCmd,37);
		ks_calcmac(uResp,uKey,2,uMacData,37,uMac);
		memcpy(uCmd+37,uMac,4);
		ret=ks_cpuapdu4sam(uCmd,41,uResp,uRespLen);
		if(ret)
		{
			sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
			((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
			return;
		}
	}
	//����DF01���˻�
	//�ϵ縴λ
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λ����");
		return;
	}
	sCmd="00A4000002DF01";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());

	sCmd="0084000008";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ks_calcmac(uResp,uKey,2,uCmd,uCmdLen,uMac);
	memcpy(uCmd+5,uMac,4);
	ret=ks_cpuapdu4sam(uCmd,9,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	//����MF���˻�
	//�ϵ縴λ
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λ����");
		return;
	}
	sCmd="0084000008";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ks_calcmac(uResp,uKey,2,uCmd,uCmdLen,uMac);
	memcpy(uCmd+5,uMac,4);
	ret=ks_cpuapdu4sam(uCmd,9,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	((CMainFrame*)AfxGetMainWnd())->ShowLog("����ĸ��OK");
	ks_beep();
	*/
}
void CSupCardDlg::OnBtnRecyclesupercard() 
{
	int ret=0;
	vector<string> CmdVector;
	char sHexStr[64];
	int uCmdLen=0;
	BYTE uCmd[256],uResp[256],uRespLen,rlen,rbuf[256];
	memset(sHexStr,0,sizeof(sHexStr));
	memset(uCmd,0,sizeof(uCmd));
	memset(uResp,0,sizeof(uResp));
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λ����");
		return;
	}
	string sMsg;
	string sCmd="0084000008";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+":"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	//����MAC
	///////////////////////////////////////////
	memset(uCmd,0,sizeof(uCmd));
	memcpy(uCmd,"\x84\x8A\x01\x00\x04\x80\x00\x00",8);
	for(int i=0;i<8;i++)
		uCmd[i]=uCmd[i]^uResp[i];
	//����
	des3_context ctx3;
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
	des3_set_2keys(&ctx3,uKey,uKey+8);
	des3_encrypt(&ctx3,uCmd,uResp);
	
	memset(uCmd,0,sizeof(uCmd));
	memcpy(uCmd,"\x84\x8A\x01\x00\x04",5);
	memcpy(uCmd+5,uResp,4);
	ret=ks_cpuapdu4sam(uCmd,9,uResp,uRespLen);
	if(ret)
	{
		if(ret==0x6985)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog("��PSAM���ѻ���");
			
		}
		//		sMsg=">>"+sCmd+":"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("PSAM�����ճɹ�");
//	UpdateData();	
}

void CSupCardDlg::OnBtnPsamreset() 
{
	int ret=0;
	UpdateData();
	BYTE rlen;
	BYTE rbuf[256];
	int SAMID=m_iSamNo+1;
	if(m_cbxSamNo.GetCurSel()==3)
		SAMID=0;
	ks_reset(2);
	ret=ks_setcpupara4sam(SAMID);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("����SAM����������");
		return ;
	}
	
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λ����");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM��Ƭ��λOK");
	ks_beep();	
}

BOOL CSupCardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbxSamNo.SetCurSel(3);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
