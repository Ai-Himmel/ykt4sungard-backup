// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "MyDlg.h"
#include "MainFrm.h"
#include "InputPwd.h"
#include "kscard_imp.h"
#include "des.h"
#include <vector>
#include ".\mydlg.h"
#include "global_func.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

IMPLEMENT_DYNCREATE(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_iSamNo =0;
	m_sCmdStr = _T("");
	m_sTermID = _T("");
	//}}AFX_DATA_INIT
	bGetKey=false;
}


void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_CMB_SAM, m_cbxSamNo);
	DDX_CBIndex(pDX, IDC_CMB_SAM, m_iSamNo);
	DDX_Text(pDX, IDC_EDIT_CMDSTR, m_sCmdStr);
	DDX_Text(pDX, IDC_EDIT_TERMID, m_sTermID);
	DDV_MaxChars(pDX, m_sTermID, 12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_BN_CLICKED(IDC_BTN_READKEYCARD, OnBtnReadkeycard)
	ON_BN_CLICKED(IDC_PUBLISHPSAMCARD, OnPublishpsamcard)
	ON_BN_CLICKED(IDC_BTN_RECYCLEPSAMCARD, OnBtnRecyclepsamcard)
	ON_BN_CLICKED(IDC_BTN_PSAMRESET, OnBtnPsamreset)
	ON_BN_CLICKED(IDC_BTN_RUNAPDU, OnBtnRunapdu)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_READPSAMCARD, OnBnClickedBtnReadpsamcard)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CMyDlg::OnBtnReadkeycard() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
	//if(ks_checkloadkeys())
	//{
	//	pMainFrame->ShowLog("密钥已装载");
	//	return ;
	//}
	char sKeyCardPin[7]={0};
	CInputPwd dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_loadcardkeys(sKeyCardPin);
	if(ret)
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
/*	
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
		pMainFrame->ShowLog("读密钥卡失败,请放密钥卡");
		//		AfxMessageBox("读密钥卡失败,请放密钥卡");
		return ;
	}
	memset(&CardMainKey,0,sizeof(CardMainKey));
	Sleep(100);
	for( int i=1; i<10; i++ )
	{	
		memset(sMsg,0,sizeof sMsg);
		nRet=ks_getkey(i,sKeyCardPin,sMsg);
		if( nRet!=0 )
		{
			ks_geterrmsg(sMsg);
			pMainFrame->ShowLog(sMsg);
			//sprintf(sMsg,"KNG_Get_Key=%ld",nRet);
			//	MessageBox(sMsg,"error",MB_OK);			
			return;
		}
		if( i==1 ) memcpy(CardMainKey.DPK1,sMsg,16);
		if( i==2 ) memcpy(CardMainKey.DPK2,sMsg,16);
		if( i==3 ) memcpy(CardMainKey.DLK,sMsg,16);
		if( i==4 ) memcpy(CardMainKey.DTAC1,sMsg,16);
		if( i==5 ) memcpy(CardMainKey.DTAC2,sMsg,16);
		if( i==6 ) memcpy(CardMainKey.DUK,sMsg,16);
		if( i==7 ) memcpy(CardMainKey.DRPK,sMsg,16);
		if( i==8 ) memcpy(CardMainKey.DAMK,sMsg,16);
		if( i==9 ) memcpy(CardMainKey.DACK,sMsg,16);
		//APP_BcdToAsc((byte*)sMsg,16,(byte*)sMsg);	
	}
	bGetKey=true;
	ks_beep();
	pMainFrame->ShowLog("取密钥成功");
	*/
}
void CMyDlg::OnPublishpsamcard() 
{
	if(!ks_checkloadkeys())
	{
		AfxMessageBox("请先读密钥卡装入密钥");
		return ;
	}
	UpdateData();
	if(m_sTermID.GetLength()<1||m_sTermID=="0")
	{
		GetDlgItem(IDC_EDIT_TERMID)->SetFocus();
		AfxMessageBox("请设置终端编号");
		return ;
	}
	for(;m_sTermID.GetLength()<12;)
	{
		m_sTermID="0"+m_sTermID;
	}
	ST_PSAMCARD PSAMCard;
	memset(&PSAMCard,0,sizeof(PSAMCard));
	
	PSAMCard.nCardType=2;
	PSAMCard.nCardVer=1;
	strcpy(PSAMCard.sPublishID,"20");
	strcpy(PSAMCard.sUserID,"10");
	strcpy(PSAMCard.sCardNo,"1234567");
	strcpy(PSAMCard.sTermID,(LPCTSTR)m_sTermID);
	strcpy(PSAMCard.sStartDate,"20090101");
	strcpy(PSAMCard.sExpireDate,"20201231");

	int ret=ks_publishpsamcard(&PSAMCard);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("发行SAM失败");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("发行SAM成功");

	/*
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
// 	/////////////////////////////////test XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// 	sCmd="EA82771593425E79";
// 	hex2dec(sCmd.c_str(),sCmd.size(),uResp,uCmdLen);
// 	sCmd="841C000004";
// 	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
// 	BYTE uKey2[16];
// 	memcpy(uKey2,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
// 	BYTE uMac2[4];
// 	ks_calkeymac4psam(uResp,uKey2,2,uCmd,uCmdLen,uMac2);
// 	return;
// 	//////////////////////////////////
	//复位上电
	BYTE rlen,rbuf[256];
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位错误");
		return;
	}
	sCmd="808A0000 2A 3F00 10  00 FFFF 0A   00 012A  FF 81 FFFFFF 00 315041592E5359532E4444463031FFFF 00180100010002030300";
	string_replace(sCmd," ","");
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	ret=ks_cpuapdu4sam(uCmd,uCmdLen,uResp,uRespLen);
	if(ret)
	{
		sMsg=">>"+sCmd+"ERR:"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		if(ret==0x6985)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog("该卡已使用");
		}
		return;
	}
	sMsg=">>"+sCmd+"OK";
	((CMainFrame*)AfxGetMainWnd())->ShowLog(sCmd.c_str());
	//DIR文件
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000080001 34  00 0040 00 02";
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
	//卡片公共信息文件
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000080015 31  00 000E 00 02";
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
	//终端信息文件	
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000080016 31  00 0006 00 FF";
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
	//建公共信息文件
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000080017 31  00 0026 00 02";
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
	//修改公共信息文件
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="00D697000E0100000000000000000001010203";
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
	//写终端机编号
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="00D6960006"+m_sTermID;
	//sCmd
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

	//写外部认证密钥
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80D000001A0E180000010002030300 FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";

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
	//建立
	uCmdLen=0;
	memset(uCmd,0,sizeof(uCmd));
	sCmd="80800000  2ADF03 20  00 FFFF 0A   FF 01C8  00 81 FFFFFF 00 D156000001BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
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
	//建立DF03下EF文件
	//选择文件目录
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//建立交易序号文件
	sCmd="80800000  080019 31  00 0004 00 FF";
	CmdVector.push_back(sCmd);
	//写终端交易序号文件
	sCmd="00D699000400000000";
	CmdVector.push_back(sCmd);
	//选择文件目录	
	sCmd="00A40000 02DF03";
	CmdVector.push_back(sCmd);
	//消费密钥1
	dec2hex(CardMainKey.DPK1,16,sHexStr);
	sCmd="80D00000 1A22180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//消费密钥2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DPK2,16,sHexStr);
	sCmd="80D00000 1A22180200010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//消费密钥3
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DPK2,16,sHexStr);		//临时 fixme
	sCmd="80D00000 1A22180300010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	//16字节应用维护主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节口令解锁主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DUK,16,sHexStr);
	sCmd="80D00000 1A28180200010010030300";
					
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节口令重装主密钥
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DRPK,16,sHexStr);
	sCmd="80D00000 1A28180300010010030300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//16字节内部认证主密钥
//	memset(sHexStr,0,sizeof(sHexStr));
//	dec2hex(CardMainKey.DACK,16,sHexStr);
	sCmd="80D00000 1A28180400010010030300";
	sCmd+="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";//16字节内部认证主密钥
	CmdVector.push_back(sCmd);
	CmdVector.push_back("ATR");
	sCmd="80800000  2ADF04 20  00 FFFF 0A   FF 01C8  00 81 FFFFFF 00 D156000004BDF0CACBB4EFD6A7B8B6FF 00180100010002030300";
	CmdVector.push_back(sCmd);
	sCmd="00A4000002DF04";
	CmdVector.push_back(sCmd);
	sCmd="80D00000 1A27180100010010030300";
	sCmd+="FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";//16字节外部认证主密钥
	CmdVector.push_back(sCmd);
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(CardMainKey.DAMK,16,sHexStr);
	sCmd="80D00000 1A28180100010010030300";
	sCmd+=sHexStr;	//16字节应用维护主密钥
	sCmd="00A4000002DF03";
	CmdVector.push_back(sCmd);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	for(int i=0;i<CmdVector.size();i++)
	{
		sCmd=CmdVector[i];
		if("ATR"==sCmd)
		{
			ret=ks_cpureset4sam(&rlen,rbuf);
			if(ret)
			{
				((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位错误");
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
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//取随机数
	sCmd="0084000008";
	CmdVector.push_back(sCmd);	
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
	//结束DF03个人化计算指令MAC
	sCmd="841C000004";
	hex2dec(sCmd.c_str(),sCmd.size(),uCmd,uCmdLen);
	BYTE uKey[16];
	memcpy(uKey,"\x01\x02\x03\x04\x05\x06\x07\x08\x11\x12\x13\x14\x15\x16\x17\x18",16);
	BYTE uMac[4];
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
	/////////////////////////////////////////////////////

	sCmd="00A4000002DF04";
	////////////////////////////////////////////////////////////////////////////////////////////////////
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
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//取随机数
	sCmd="0084000008";
	CmdVector.push_back(sCmd);	
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
	//结束DF04个人化计算指令MAC
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
	//结束MF个人化
	//上电复位
	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位错误");
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
	((CMainFrame*)AfxGetMainWnd())->ShowLog("发行PSAM卡OK");
	ks_beep();
	*/
}

void CMyDlg::OnBtnRecyclepsamcard() 
{
	/*
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
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位错误");
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
	//计算MAC
	///////////////////////////////////////////
	memset(uCmd,0,sizeof(uCmd));
	memcpy(uCmd,"\x84\x8A\x01\x00\x04\x80\x00\x00",8);
	for(int i=0;i<8;i++)
		uCmd[i]=uCmd[i]^uResp[i];
	//加密
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
			((CMainFrame*)AfxGetMainWnd())->ShowLog("该PSAM卡已回收");

		}
//		sMsg=">>"+sCmd+":"+ltohex(ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg.c_str());
		return;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("PSAM卡回收成功");
//	UpdateData();
	*/
	int ret=ks_recyclepsamcard();
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("回收PSAM卡成功");	

}

void CMyDlg::OnBtnPsamreset() 
{
	// TODO: Add your control notification handler code here

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
		((CMainFrame*)AfxGetMainWnd())->ShowLog("设置SAM卡参数错误");
		return ;
	}

	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位错误");
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位OK");
}

BOOL CMyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbxSamNo.SetCurSel(3);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlg::OnBtnRunapdu() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	char *pstr=(char*)m_sCmdStr.GetBuffer(0);
	BYTE slen,rlen,apducmd[256],rbuf[256];
	char hex[256];
	int cmdlen;
	memset(apducmd,0,sizeof(apducmd));
	memset(rbuf,0,sizeof(rbuf));
	memset(hex,0,sizeof(hex));
	hex2dec(pstr,m_sCmdStr.GetLength(),apducmd,cmdlen);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(">"+m_sCmdStr);
	slen=cmdlen;
	int ret=ks_cpuapdu4sam(apducmd,slen,rbuf,rlen);
	if(ret)
	{
		char szMsg[256];
		sprintf(szMsg,"%s retcode=%x",pstr,ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(szMsg);
		return;
	}
	dec2hex(rbuf,rlen,hex);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(CString("<")+hex);
	return;
}

void CMyDlg::OnBnClickedBtnReadpsamcard()
{
	// TODO: 在此添加控件通知处理程序代码
	ST_PSAMCARD PsamCard;
	
	memset(&PsamCard,0,sizeof(PsamCard));
	int nRet=0;
	nRet=ks_readpsamcard(&PsamCard);
	if(nRet)
	{
		AfxMessageBox("读PSAM卡失败");
		return;
	}
	ks_beep();
}

void CMyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMyDlg::OnBnClickedButton2()
{
	char termno[20] = "";
	if(ks_readpsamtermno(termno,1)!=0)
	{
		AfxMessageBox("读PSAM卡失败");
		return;
	}
	ks_beep();
}
