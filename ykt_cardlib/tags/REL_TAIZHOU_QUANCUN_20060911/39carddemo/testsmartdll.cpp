//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testsmartdll.h"
#include "desdll.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma link "CSIntf"
#pragma resource "*.dfm"
TForm1 *Form1;

unsigned char ucWorkKey[16]="";
HINSTANCE hDLL = NULL;
HINSTANCE hCardDLL = NULL;
HINSTANCE hDesDLL = NULL;
#pragma comment(lib,"desdll.lib")
//SMART SMT_DLL
LPSMT_GetLastErr                SMT_GetLastErr=NULL;
LPSMT_Login_Card			    SMT_Login_Card=NULL;
LPSMT_WriteBlock                SMT_WriteBlock=NULL;
LPSMT_ReadBlock                 SMT_ReadBlock=NULL;
LPSMT_Login_With_UserKey        SMT_Login_With_UserKey=NULL;
LPSMT_ConnectMF280			    SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer			    SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280			    SMT_CloseMF280=NULL;
LPSMT_CreateGreyCard			SMT_CreateGreyCard=NULL;
LPSMT_ResetCard			        SMT_ResetCard=NULL;
LPSMT_WriteCardStateInfo		SMT_WriteCardStateInfo=NULL;
LPSMT_AutoDll				    SMT_AutoDll=NULL;
LPSMT_JudgeAutoFlag			    SMT_JudgeAutoFlag=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;
LPSMT_ReadCardStateInfo			SMT_ReadCardStateInfo=NULL;
LPSMT_WritePersonalInfo			SMT_WritePersonalInfo=NULL;
LPSMT_ReadPersonalInfo			SMT_ReadPersonalInfo=NULL;
LPSMT_ReadLibraryNo             SMT_ReadLibraryNo=NULL;
LPSMT_WriteLibraryNo		    SMT_WriteLibraryNo=NULL;
LPSMT_ChangeName			    SMT_ChangeName=NULL;
LPSMT_ChangeDutyNo			    SMT_ChangeDutyNo=NULL;
LPSMT_ChangeCerificateNo		SMT_ChangeCerificateNo=NULL;
LPSMT_ChangeDepartmentNo		SMT_ChangeDepartmentNo=NULL;
LPSMT_ChangeIdentifyNo			SMT_ChangeIdentifyNo=NULL;
LPSMT_ChangeSexNo				SMT_ChangeSexNo=NULL;
LPSMT_ChangeCardNo				SMT_ChangeCardNo=NULL;
LPSMT_ChangeDealCardNo          SMT_ChangeDealCardNo=NULL;
LPSMT_ChangeDeadLineDate		SMT_ChangeDeadLineDate=NULL;
LPSMT_ChangeCardRightType		SMT_ChangeCardRightType=NULL;
LPSMT_WritePersonalPassword		SMT_WritePersonalPassword=NULL;
LPSMT_ReadPersonalPassword		SMT_ReadPersonalPassword=NULL;
LPSMT_PacketAddMomey     SMT_PacketAddMomey=NULL;
LPSMT_PacketDelMomey     SMT_PacketDelMomey=NULL;
LPSMT_PacketSetMoney     SMT_PacketSetMoney=NULL;
LPSMT_ReadPacketInfo	 SMT_ReadPacketInfo=NULL;
LPSMT_ClearCard		    SMT_ClearCard=NULL;
LPSMT_SleepCard		    SMT_SleepCard=NULL;
LPSMT_ReadAuthCard      SMT_ReadAuthCard=NULL;
LPSMT_ResetPacketInfo   SMT_ResetPacketInfo=NULL;
LPSMT_GetPacketInfo     SMT_GetPacketInfo=NULL;
LPSMT_SetPacketInfo     SMT_SetPacketInfo=NULL;
LPSMT_SetNormalFlagByBlkVerion SMT_SetNormalFlagByBlkVerion=NULL;
LPSMT_ReadBlackNameListVersion SMT_ReadBlackNameListVersion=NULL;
//KSSTAR    CARDDLL
LPKS_ConnectMF            ConnectMF=NULL;
LPKS_PublishCard          PublishCard=NULL;
LPKS_GetLastErrMsg        GetLastErrMsg=NULL;

//KSSTAR    DESDLL

int  Load_SmartDll()
{
	if(hDLL)
		return 0;
        hDLL = LoadLibrary("SmartCom411DXQ.dll");
	if(!hDLL)
	{
	       //	SetErrMsg(-1,"装载SmartCom411DXQ.dll动态库失败");
		return -1;
	}
	SMT_GetLastErr = (LPSMT_GetLastErr)GetProcAddress(hDLL,"SMT_GetLastErr");
	SMT_Login_Card	 = (LPSMT_Login_Card)GetProcAddress(hDLL,"Login_Card");
	SMT_WriteBlock	 = (LPSMT_WriteBlock)GetProcAddress(hDLL,"SMT_WriteBlock");
	SMT_ReadBlock	 = (LPSMT_ReadBlock)GetProcAddress(hDLL,"SMT_ReadBlock");
    SMT_Login_With_UserKey=(LPSMT_Login_With_UserKey)GetProcAddress(hDLL,"SMT_Login_With_UserKey");
	SMT_ConnectMF280	 = (LPSMT_ConnectMF280)GetProcAddress(hDLL,"SMT_ConnectMF280");
	SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hDLL,"SMT_ControlBuzzer");
	SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hDLL,"SMT_CloseMF280");
	SMT_CreateGreyCard       = (LPSMT_CreateGreyCard)GetProcAddress(hDLL,"SMT_CreateGreyCard");
	SMT_ResetCard            = (LPSMT_ResetCard)GetProcAddress(hDLL,"SMT_ResetCard");
	SMT_WriteCardStateInfo   = (LPSMT_WriteCardStateInfo)GetProcAddress(hDLL,"SMT_WriteCardStateInfo");
	SMT_CreateGreyCard       = (LPSMT_CreateGreyCard)GetProcAddress(hDLL,"SMT_CreateGreyCard");
	SMT_PacketAddMomey       = (LPSMT_PacketAddMomey)GetProcAddress(hDLL,"SMT_PacketAddMomey");
	SMT_PacketDelMomey       = (LPSMT_PacketAddMomey)GetProcAddress(hDLL,"SMT_PacketDelMomey");
    SMT_PacketSetMoney       = (LPSMT_PacketSetMoney)GetProcAddress(hDLL,"SMT_PacketSetMoney");
	SMT_AutoDll		         = (LPSMT_AutoDll)GetProcAddress(hDLL,"SMT_AutoDll");
	SMT_JudgeAutoFlag  	     = (LPSMT_JudgeAutoFlag)GetProcAddress(hDLL,"SMT_JudgeAutoFlag");
    SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hDLL,"SMT_RequestCardExist");
	SMT_ReadCardStateInfo  	 = (LPSMT_ReadCardStateInfo)GetProcAddress(hDLL,"SMT_ReadCardStateInfo");
    SMT_WritePersonalInfo  	 = (LPSMT_WritePersonalInfo)GetProcAddress(hDLL,"SMT_WritePersonalInfo");
	SMT_ReadPersonalInfo     = (LPSMT_ReadPersonalInfo)GetProcAddress(hDLL,"SMT_ReadPersonalInfo");
    SMT_ChangeDealCardNo     = (LPSMT_ChangeDealCardNo)GetProcAddress(hDLL,"SMT_ChangeDealCardNo");
	SMT_ChangeName           = (LPSMT_ChangeName)GetProcAddress(hDLL,"SMT_ChangeName");
	SMT_ChangeDutyNo         = (LPSMT_ChangeDutyNo)GetProcAddress(hDLL,"SMT_ChangeDutyNo");
	SMT_ChangeCerificateNo   = (LPSMT_ChangeCerificateNo)GetProcAddress(hDLL,"SMT_ChangeCerificateNo");
	SMT_ChangeDepartmentNo   = (LPSMT_ChangeDepartmentNo)GetProcAddress(hDLL,"SMT_ChangeDepartmentNo");
	SMT_ChangeIdentifyNo     = (LPSMT_ChangeIdentifyNo)GetProcAddress(hDLL,"SMT_ChangeIdentifyNo");
	SMT_ChangeSexNo          = (LPSMT_ChangeSexNo)GetProcAddress(hDLL,"SMT_ChangeSexNo");
    SMT_ReadPacketInfo       = (LPSMT_ReadPacketInfo)GetProcAddress(hDLL,"SMT_ReadPacketInfo");
	SMT_ChangeDeadLineDate   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_ChangeDeadLineDate");
	SMT_ChangeCardRightType  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ChangeCardRightType");
	SMT_WritePersonalPassword = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_WritePersonalPassword");
	SMT_ReadPersonalPassword  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ReadPersonalPassword");
	SMT_SleepCard             = (LPSMT_SleepCard)GetProcAddress(hDLL,"SMT_SleepCard");
	SMT_ClearCard			  = (LPSMT_ClearCard)GetProcAddress(hDLL,"SMT_ClearCard");
	SMT_ReadAuthCard		  = (LPSMT_ReadAuthCard)GetProcAddress(hDLL,"SMT_ReadAuthCard");
	SMT_ReadLibraryNo		  = (LPSMT_ReadLibraryNo)GetProcAddress(hDLL,"SMT_ReadLibraryNo");
	SMT_WriteLibraryNo		  = (LPSMT_WriteLibraryNo)GetProcAddress(hDLL,"SMT_WriteLibraryNo");
	SMT_ChangeCardNo		  = (LPSMT_ChangeCardNo)GetProcAddress(hDLL,"SMT_ChangeCardNo");
    SMT_ResetPacketInfo	      = (LPSMT_ResetPacketInfo)GetProcAddress(hDLL,"SMT_ResetPacketInfo");
    SMT_GetPacketInfo	      = (LPSMT_GetPacketInfo)GetProcAddress(hDLL,"SMT_GetPacketInfo");
    SMT_SetPacketInfo	      = (LPSMT_SetPacketInfo)GetProcAddress(hDLL,"SMT_SetPacketInfo");
    SMT_SetNormalFlagByBlkVerion =(LPSMT_SetNormalFlagByBlkVerion)GetProcAddress(hDLL,"SMT_SetNormalFlagByBlkVerion");
    SMT_ReadBlackNameListVersion =(LPSMT_ReadBlackNameListVersion)GetProcAddress(hDLL,"SMT_ReadBlackNameListVersion");
 	if (
        (!SMT_GetLastErr)||
        (!SMT_Login_Card) ||
		(!SMT_WriteBlock) ||
        (!SMT_ConnectMF280) ||
		(!SMT_ReadBlock) ||
        (!SMT_Login_With_UserKey)||
		(!SMT_ControlBuzzer) ||
		(!SMT_CloseMF280) ||
		(!SMT_CreateGreyCard) ||
		(!SMT_ResetCard) ||
		(!SMT_WriteCardStateInfo) ||
		(!SMT_PacketAddMomey) ||
		(!SMT_PacketDelMomey) ||
        (!SMT_PacketSetMoney)||
		(!SMT_AutoDll) ||
		(!SMT_JudgeAutoFlag) ||
		(!SMT_RequestCardExist) ||
		(!SMT_ReadCardStateInfo) ||
		(!SMT_WritePersonalInfo) ||
		(!SMT_ReadPersonalInfo) ||
 		(!SMT_ChangeDealCardNo) ||
		(!SMT_ChangeName) ||
		(!SMT_ChangeDutyNo) ||
		(!SMT_ChangeCerificateNo) ||
		(!SMT_ChangeDepartmentNo) ||
		(!SMT_ChangeIdentifyNo) ||
		(!SMT_ChangeSexNo) ||
		(!SMT_ReadPacketInfo) ||
		(!SMT_ChangeDeadLineDate) ||
		(!SMT_ChangeCardRightType) ||
		(!SMT_WritePersonalPassword)||
		(!SMT_ReadPersonalPassword)||
		(!SMT_SleepCard)||
		(!SMT_ClearCard)||
        (!SMT_ReadAuthCard)||
	 	(!SMT_ReadLibraryNo)||
		(!SMT_WriteLibraryNo)||
		(!SMT_ChangeCardNo)||
        (!SMT_ResetPacketInfo)||
        (!SMT_GetPacketInfo) ||
        (!SMT_SetPacketInfo) ||
         (!SMT_SetNormalFlagByBlkVerion)||
         (!SMT_ReadBlackNameListVersion)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}
int  Load_CardDll()
{
	if(hCardDLL)
		return 0;
        hCardDLL = LoadLibrary("CardDll.dll");
	if(!hCardDLL)
	{
	       //	SetErrMsg(-1,"装载SmartCom411DXQ.dll动态库失败");
		return -1;
	}
	ConnectMF  = (LPKS_ConnectMF)GetProcAddress(hCardDLL,"ConnectMF");
	PublishCard  = (LPKS_PublishCard)GetProcAddress(hCardDLL,"PublishCard");
	GetLastErrMsg =(LPKS_GetLastErrMsg)GetProcAddress(hCardDLL,"GetLastErrMsg");
	if ( (!ConnectMF)||
             (!PublishCard)||
             (!GetLastErrMsg))
        {
		FreeLibrary(hCardDLL);
		hCardDLL = NULL;
		return -2;
	}
	return 0;
}
int  Load_DesDll()
{
	if(hDesDLL)
		return 0;
        hDesDLL = LoadLibrary("desdll.dll");
	if(!hDesDLL)
	{
	       //	SetErrMsg(-1,"装载SmartCom411DXQ.dll动态库失败");
		return -1;
	}
    /*
	ConnectMF  = (LPKS_ConnectMF)GetProcAddress(hDesDLL,"ConnectMF");
	PublishCard  = (LPKS_PublishCard)GetProcAddress(hDesDLL,"PublishCard");
	GetLastErrMsg =(LPKS_GetLastErrMsg)GetProcAddress(hDesDLL,"GetLastErrMsg");
	if ( (!ConnectMF)||
             (!PublishCard)||
             (!GetLastErrMsg))
        {
		FreeLibrary(hCardDLL);
		hCardDLL = NULL;
		return -2;
	}
    */
	return 0;
}

int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}

int  bcd2dec(unsigned char *sBcdStr,int bcd_len,char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}
void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}

int  GrantRight(char *sHexWorkKey)
{
    int ret;
//	char sHexWorkKey[17]="8E8BFC8FF68FF488";
//	unsigned char ucWorkKey[8];
    memset(ucWorkKey,0,sizeof(ucWorkKey));
	hex2dec(sHexWorkKey,ucWorkKey,8);
	ret=SMT_AutoDll(ucWorkKey);
	if(ret)
    {
        ShowMessage("授权失败");
        return ret;
    }
	SMT_ControlBuzzer();
    return 0;
 }
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        int ret=0;
        ret=Load_SmartDll();
        if(ret)
        {
                ShowMessage("装载Smart动态库失败");
                return ;
        }
        ret=Load_CardDll();
        if(ret)
        {
                ShowMessage("装载KS动态库失败");
                return ;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BtnConnComClick(TObject *Sender)
{
        int ret=0;
        try
        {
           // ret=SMT_CloseMF280();
            ////CodeSite->SendInteger("SMT_CloseMF280",ret);
           // if(ret)
                //    return ;
    //            Sleep(5);
            ret=ConnectMF(1,19200);
            //	ret=SMT_ConnectMF280(1,19200);
         //     //CodeSite->SendInteger("ConnectMF",ret);
            if(ret !=0)
                return;//卡片不在感应区
         // bopen=true;
   //         SMT_ControlBuzzer();
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
//          ShowMessage("串口已经关闭");
        }
 }
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnReadCardSerialNoClick(TObject *Sender)
{
    int ret=0;
	unsigned char ucSerialNo[4];
    unsigned char ucType[1];
    char SerialNo[9]="";
	ret=SMT_RequestCardExist(ucSerialNo,ucType);
	if(ret)
	{
                ShowMessage("卡不在读卡器感应区");
		return ;
	}
    for(int i=0;i<4;i++)
        sprintf(&SerialNo[2*i],"%02X",ucSerialNo[i]);
    EdtCardSerialNo->Text=String(SerialNo);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnGrantRightClick(TObject *Sender)
{
    cbbWorkKey->Text.Trim();
    if(cbbWorkKey->Text.Length()!=16)
    {
        ShowMessage("工作密钥必须是16位");
        return;
    }
//  //CodeSite->SendString("工作密钥",cbbWorkKey->Text);
    int ret=GrantRight(cbbWorkKey->Text.c_str());
    if(ret)
      return ;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnReadCardStateInfoClick(TObject *Sender)
{
        int ret=0;
        unsigned char ucSerialNo[4];
        unsigned char ucType[1];
        char SerialNo[9]="";
        ret=SMT_RequestCardExist(ucSerialNo,ucType);
        if(ret)
        {
            ShowMessage("卡不在读卡器感应区");
            return ;
        }
        for(int i=0;i<4;i++)
            sprintf(&SerialNo[2*i],"%02X",ucSerialNo[i]);
        EdtCardSerialNo->Text=String(SerialNo);
        unsigned char ucBcdShowCardNo[5]="";
        char sShowCardNo[12]="";
        int nCardNo[1]={0};
        unsigned char ucDeadLineDate[3]="";
        unsigned char ucCardRightType[1]="";
        char sDeadLineDate[20];
        ret=SMT_ReadCardStateInfo(ucBcdShowCardNo,nCardNo,ucDeadLineDate,ucCardRightType);
        if(ret)
        {
            //CodeSite->SendInteger("SMT_ReadCardStateInfo",ret);
            ShowMessage("读卡状态信息失败");
            return ;
        }
        bcd2dec(ucBcdShowCardNo,5,sShowCardNo);
        edtCardNo->Text=IntToStr(nCardNo[0]);
        edtShowCardNo->Text=AnsiString(sShowCardNo);
        edtCardType->Text=IntToStr(ucCardRightType[0]);
        sprintf(sDeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
        edtDealLineDate->Text=AnsiString(sDeadLineDate);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(hDLL)
        {
           FreeLibrary(hDLL);
        }
    //    //CodeSite->Destroying();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnPublishCardClick(TObject *Sender)
{
      int ret=0;
      int retcode[1];
      char errmsg[256];
      TPublishCard  p;

    ret=MessageDlg("发行新卡将会擦除该卡上的原有的所有信息，请确认",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    memset(&p,0,sizeof(p));
    if(edtShowCardNo->Text.Trim().Length()!=10)
    {
        ShowMessage("显示卡号长度不正确");
        return;
    }
    strcpy(p.ShowCardNo,edtShowCardNo->Text.c_str());
    int cardno=0;
    if(edtCardNo->Text.Trim().Length()==0)
        cardno=0;
    else
        cardno=edtCardNo->Text.ToInt();
    if(cardno>0xFFFFF)
    {
        ShowMessage("卡号不能超过最大值1048575");
        edtCardNo->SetFocus();
        return;
    }
    sprintf(p.CardNo,"%d",cardno);
    strcpy(p.DeadLineDate,edtDealLineDate->Text.c_str());
    if(edtCardType->Text.Trim().Length()==0)
       p.CardRightType=0;
    else
        p.CardRightType=edtCardType->Text.ToInt();
    strcpy(p.ucName,edtName->Text.c_str());
    strcpy(p.ucDutyNo,"5432");
    strcpy(p.ucDepartmentNo,edtDept->Text.c_str());
    strcpy(p.ucCertificateNo,edtID->Text.c_str());
    strcpy(p.ucIdentifyNo,"2345");
    strncpy(p.ucSexNo,edtSex->Text.c_str(),1);
    strcpy(p.ucCardNo,edtStudentNo->Text.c_str());
    strcpy(p.ucPwd,edtPwd->Text.c_str());
    strcpy(p.ucLibraryNo,edtLibraryNo->Text.c_str());
    if(edtBalance->Text.Trim().Length()==0)
        p.Money=0;
    else
        p.Money=edtBalance->Text.ToDouble()*100;
    ret=PublishCard(&p);
    if(ret)
    {
      GetLastErrMsg(retcode,errmsg);
      ShowMessage(errmsg);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnReadPersonInfoClick(TObject *Sender)
{
        unsigned char ucName[9]="";
        unsigned char ucDutyNo[5]="";
        unsigned char ucCertificateNo[21]="";
        unsigned char ucDepartmentNo[11]="";
        unsigned char ucIdentifyNo[5]="";
        unsigned char ucSexNo[2]="";
        unsigned char ucCardNo[21]="";
        unsigned char ucLibraryNo[14]="";
        int ret=0;
        ret=SMT_ReadPersonalInfo(ucName,ucDutyNo,ucCertificateNo,ucDepartmentNo,ucIdentifyNo,ucSexNo,ucCardNo);
        if(ret)
        {
            //CodeSite->SendInteger("SMT_ReadPersonalInfo",ret);
             ShowMessage("读卡人事信息失败");
        }
        edtName->Text=AnsiString((char*)ucName);
        edtID->Text=AnsiString((char*)ucCertificateNo);
        edtDept->Text=AnsiString((char*)ucDepartmentNo);
        edtSex->Text=AnsiString((char*)ucSexNo);
        edtStudentNo->Text=AnsiString((char*)ucCardNo);
        ret=SMT_ReadLibraryNo(ucLibraryNo);
        if(ret)
        {
            //CodeSite->SendInteger("SMT_ReadLibraryNo",ret);
            ShowMessage("读图书证号出错");
        }
        edtLibraryNo->Text=String((char*)ucLibraryNo);
    	unsigned char ucPwd[3]="";
        char sPwd[7]="";

    	ret=SMT_ReadPersonalPassword(ucPwd);
	    if(ret)
        {
            //CodeSite->SendInteger("SMT_ReadPersonalPassword",ret);
            return ;
        }
    	bcd2dec(ucPwd,3,sPwd);
        edtPwd->Text=AnsiString(sPwd);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnAddMoneyClick(TObject *Sender)
{
    edtAddMoney->Text.Trim();
    if(edtAddMoney->Text.Length()==0)
    {
        ShowMessage("请输入金额");
        return;
    }
    int ret=MessageDlg("你确认要向卡中加钱吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    int nMoney=edtAddMoney->Text.ToDouble()*100;
    ret=SMT_PacketAddMomey(1,nMoney);
    if(ret)
    {
        //CodeSite->SendInteger("SMT_PacketAddMomey",ret);
        ShowMessage("加钱失败");
        return ;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDecMoneyClick(TObject *Sender)
{
    edtDecMoney->Text.Trim();
    if(edtDecMoney->Text.Length()==0)
    {
        ShowMessage("请输入金额");
        return;
    }
    int ret=MessageDlg("你确认要从卡中扣钱吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    int nMoney=edtDecMoney->Text.ToDouble()*100;
    ret=SMT_PacketDelMomey(1,nMoney);
    if(ret)
    {
        //CodeSite->SendInteger("SMT_PacketDelMomey",ret);
        ShowMessage("减钱失败");
        return ;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReadPackMoneyClick(TObject *Sender)
{
    int ret;
    int ecode;
    char msg[1024]="";
//    LOOPPURSEINFO   PurseInfo;
    MONEY_PACK_INFO  PurseInfo;

	memset(&PurseInfo,0,sizeof(PurseInfo));
/*
	ret = SMT_ReadPacketInfo(1,&PurseInfo);
	if (ret !=0)
	{
        //CodeSite->SendInteger("SMT_ReadPacketInfo",ret);
        SMT_GetLastErr(&ecode,msg);
        ShowMessage(msg);
	//	return ;
	}
    edtBalance->Text=FloatToStr(PurseInfo.RemainMoney/100.0);
    edtTxCnt->Text=IntToStr(PurseInfo.DealTimes);
    edtDayTxCnt->Text=IntToStr(PurseInfo.DealTimes_CurDay);
    edtTxDate->Text=IntToStr(PurseInfo.DealYear)+"-"+IntToStr(PurseInfo.DealMonth)+"-"+IntToStr(PurseInfo.DealDay);
    edtTxTime->Text=IntToStr(PurseInfo.DealHour)+":"+IntToStr(PurseInfo.DealMin);
*/

	ret = SMT_GetPacketInfo(1,&PurseInfo);
	if (ret !=0)
	{
        //CodeSite->SendInteger("SMT_ReadPacketInfo",ret);
        SMT_GetLastErr(&ecode,msg);
        ShowMessage(msg);
	//	return ;
	}
    edtBalance->Text=FloatToStr(PurseInfo.bala/100.0);
    edtTxCnt->Text=IntToStr(PurseInfo.total_cnt);
    edtDayBala->Text=FloatToStr(PurseInfo.daybala/100.0);
    edtTxDate->Text=IntToStr(PurseInfo.date);
    edtTxTime->Text=IntToStr(PurseInfo.time/100)+":"+IntToStr(PurseInfo.time%100);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnUpdCardNoClick(TObject *Sender)
{
    int ret;
    ret=MessageDlg("你确认要修改卡号吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
     if(edtCardNo->Text.Trim().Length()==0)
    {
        ShowMessage("卡号不能空");
        return;
    }
    int nCardNo;
    nCardNo= edtCardNo->Text.ToInt();
    ret=SMT_ChangeDealCardNo(nCardNo);
    if(ret)
    {
        ////CodeSite->SendInteger("SMT_ChangeCardNo",ret);
        ShowMessage("更新卡号失败");
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnUpdPwdClick(TObject *Sender)
{
    int ret;
    char ucPwd[3],sPwd[7];
    ret=MessageDlg("你确认要修改密码吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    strcpy(sPwd,edtPwd->Text.c_str());
    dec2bcd(sPwd,ucPwd,3);
    ret=SMT_WritePersonalPassword(ucPwd);
    if(ret)
    {
        ShowMessage("修改卡密码失败");
        //CodeSite->SendInteger("SMT_WritePersonalPassword",ret);
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnClearClick(TObject *Sender)
{
    AnsiString namestring="TEdit";
    //CodeSite->SendInteger("ControlCount",Form1->ControlCount);
    //CodeSite->SendObject("form",Form1);
    for(int i=0;i<Form1->ControlCount;i++)
    {
        if(Form1->Controls[i]->ClassNameIs(namestring))
        {
            ////CodeSite->SendInteger("i",i);
            ////CodeSite->SendString("ComponentName",Form1->Controls[i]->Name);
            TEdit *p=dynamic_cast<TEdit*>(Form1->Controls[i]);
            if(p!=NULL)
                p->Text="";
        }
    }
    for(int i=0;i<GroupBox1->ControlCount;i++)
    {
        if(GroupBox1->Controls[i]->ClassNameIs(namestring))
        {
            ////CodeSite->SendInteger("i",i);
            ////CodeSite->SendString("ComponentName",GroupBox1->Controls[i]->Name);
            TEdit *p=dynamic_cast<TEdit*>(GroupBox1->Controls[i]);
            if(p!=NULL)
                p->Text="";
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnCleanCardClick(TObject *Sender)
{
    int ret=0;

    ret=MessageDlg("你真的要清空卡信息吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    ret=SMT_ClearCard();
    if(ret)
    {
        ShowMessage("清空卡失败");
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::btnDecodeClick(TObject *Sender)
{
    int ret=0;
    char sHexWorkKey[17]="";
    unsigned char ucKey[17]="",ucPlainKey[17]="",ucTmp[17]="";
    strcpy(ucTmp,cbbWorkKey->Text.c_str());
    hex2dec(ucTmp,ucKey,8);
    ret=decrypt_work_key(ucKey,ucPlainKey);
    if(ret)
    {
        ShowMessage("解密失败");
        return;
    }
    dec2hex(ucPlainKey,8,sHexWorkKey);
    cbbWorkKey->Text=AnsiString(sHexWorkKey);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnEnCodeClick(TObject *Sender)
{
    int ret=0;
    char sHexWorkKey[17]="";
    unsigned char ucKey[17]="",ucCipherKey[17]="",ucTmp[17]="";
    
    strcpy(ucTmp,cbbWorkKey->Text.c_str());
    hex2dec(ucTmp,ucKey,8);
    ret=encrypt_work_key(ucKey,ucCipherKey);
    if(ret)
    {
        ShowMessage("加密失败");
        return;
    }
    dec2hex(ucCipherKey,8,sHexWorkKey);
    edtWorkKey->Text=AnsiString(sHexWorkKey);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::chkDebugClick(TObject *Sender)
{
//    if(chkDebug->Checked)
//        //CodeSite->Enabled=true;
//    else
//        //CodeSite->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
//        //CodeSite->Enabled=false;
//        chkDebug->Checked=false;
    memset(ucWorkKey,0,sizeof(ucWorkKey));
}
//---------------------------------------------------------------------------



void __fastcall TForm1::btnFmtCardClick(TObject *Sender)
{
    int ret;
    BOOL bPersonalFlag=FALSE;
    BOOL bStateFlag=FALSE;
    BOOL bBankInfo=FALSE;
    BOOL bPacketFlag[8]={TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};
    ret=MessageDlg("你真的要初始化卡吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    ret=SMT_CreateGreyCard(bPersonalFlag,bStateFlag, bBankInfo,bPacketFlag);
    if(ret)
    {
        ShowMessage("初始化卡失败");
        return;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnResetClick(TObject *Sender)
{
    int ret;
    ret=MessageDlg("你真的要恢复卡出厂状态吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    ret=SMT_ResetCard();
    if(ret)
    {
        ShowMessage("恢复卡出厂状态失败");
        return;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCloseComClick(TObject *Sender)
{
    __try
    {
        SMT_CloseMF280();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
      //  ShowMessage("串口已经关闭");
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnSetMoneyClick(TObject *Sender)
{
    int ret;
    edtSetMoney->Text.Trim();
    if(edtSetMoney->Text.Length()==0)
    {
        ShowMessage("金额不能空");
        return;
    }
    ret=MessageDlg("你确认要修改卡余额吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    int nMoney=edtSetMoney->Text.ToDouble()*100;
    ret=SMT_PacketSetMoney(1,nMoney);
    if(ret)
    {
        //CodeSite->SendInteger("SMT_PacketDelMomey",ret);
        ShowMessage("修改余额失败");
        return ;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReadAuthCardClick(TObject *Sender)
{
    memset(ucWorkKey,0,sizeof(ucWorkKey));
    int ret=SMT_ReadAuthCard(ucWorkKey);
    if(ret)
    {
        ShowMessage("读授权卡失败");
        return ;
    }
    ret=SMT_AutoDll(ucWorkKey);
    if(ret)
    {
        ShowMessage("密钥装载失败");
        return ;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCheckCardClick(TObject *Sender)
{
    int ret=0;
    static int bFlag=0;
    unsigned char ucSerialNo[4],ucOldSerialNo[4];
    unsigned char ucType[1];
    char SerialNo[9]="";
    bFlag=!bFlag;
    if(!bFlag)
        btnCheckCard->Caption="继续循环检测";
    while(bFlag)
    {
        btnCheckCard->Caption="停止检测";
        Application->ProcessMessages();
        ret=SMT_RequestCardExist(ucSerialNo,ucType);
        if(ret)
        {
            txtMsg->Caption="没有检测到卡";
            Sleep(100);
            continue;
        }
        if(memcmp(ucOldSerialNo,ucSerialNo,4)==0)
        {
            //txtMsg->Caption="该卡已检测,请换卡检测";
            continue;
        }
        memcpy(ucOldSerialNo,ucSerialNo,4);
        txtMsg->Caption="";
        for(int i=0;i<4;i++)
            sprintf(&SerialNo[2*i],"%02X",ucSerialNo[i]);
        EdtCardSerialNo->Text=String(SerialNo);
        unsigned char ucBcdShowCardNo[5]="";
        char sShowCardNo[12]="";
        int nCardNo[1]={0};
        unsigned char ucDeadLineDate[3]="";
        unsigned char ucCardRightType[1]="";
        char sDeadLineDate[20];
        ret=SMT_ReadCardStateInfo(ucBcdShowCardNo,nCardNo,ucDeadLineDate,ucCardRightType);
        if(ret)
        {
            //CodeSite->SendInteger("SMT_ReadCardStateInfo",ret);
            txtMsg->Caption="读卡状态信息失败";
            continue; ;
        }
        bcd2dec(ucBcdShowCardNo,5,sShowCardNo);
        edtCardNo->Text=IntToStr(nCardNo[0]);
        edtShowCardNo->Text=AnsiString(sShowCardNo);
        edtCardType->Text=IntToStr(ucCardRightType[0]);
        sprintf(sDeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
        edtDealLineDate->Text=AnsiString(sDeadLineDate);
        txtMsg->Caption="检测通过";
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnReadBlockClick(TObject *Sender)
{
    int ret=0;
    char sKey[13]="";
    unsigned char ucKey[6]="";
    unsigned char ucBuf[17]="";
    char sBuf[33]="";
    unsigned char ucSerialNo[4]="";
    unsigned char ucType[1];
    int SectorNo=0;

    memset(sBuf,0,sizeof(sBuf));

    if(edtSectorNo->Text.Trim().Length()==0)
    {
        ShowMessage("请输入扇区号");
        return;
    }
    SectorNo=edtSectorNo->Text.ToInt();
    ret=SMT_RequestCardExist(ucSerialNo,ucType);
    if(ret)
    {
        ShowMessage("卡不在读卡器感应区");
        return ;
    }
    int index=rg1->ItemIndex;
    if(edtKeyA->Text.Trim().Length()!=12)
    {
        btnCalKeyClick(this);
        Sleep(100);
    }
    switch(index)
    {
    case 0:
            memcpy(sKey,edtKeyA->Text.c_str(),12);
            hex2dec(sKey,ucKey,6);
            ret=SMT_Login_With_UserKey(SectorNo,ucKey,0);
            if(ret)
            {
             ShowMessage("读第"+edtSectorNo->Text+"扇区失败");
            return ;
            }
            break;
    case 1:
            memcpy(sKey,edtKeyB->Text.c_str(),12);
            hex2dec(sKey,ucKey,6);
            ret=SMT_Login_With_UserKey(SectorNo,ucKey,1);
            if(ret)
            {
                ShowMessage("读第"+edtSectorNo->Text+"扇区失败");
                return ;
            }
            break;
        default:
             ShowMessage("请选择登录方式");
            return;
    }

    for (int i=0;i<4;i++)
    {
        memset(ucBuf,0,sizeof(ucBuf));
        memset(sBuf,0,sizeof(sBuf));
        ret=SMT_ReadBlock(SectorNo,i,ucBuf);
        if(ret)
        {
            ShowMessage("读第"+edtSectorNo->Text+"扇区第"+IntToStr(i)+"块失败");
            return ;
        }
        dec2hex(ucBuf,16,sBuf);
        switch(i)
        {
            case 0 :
                edtBlockNo0->Text=sBuf;
                break;
            case 1 :
                edtBlockNo1->Text=sBuf;
                break;
            case 2 :
                edtBlockNo2->Text=sBuf;
                break;
            case 3 :
                edtBlockNo3->Text=sBuf;
                break;
            default:
                break;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rg1Click(TObject *Sender)
{
    int index=rg1->ItemIndex;
    if(index==2)
    {
      //  edtKeyA->Visible=true;
        edtKeyA->SetFocus();
    }
    else
    {
      //  edtKeyA->Visible=false;
    }
    if(index==3)
    {
      //  edtKeyB->Visible=true;
        edtKeyB->SetFocus();
    }
    else
    {
       // edtKeyB->Visible=false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnCalKeyClick(TObject *Sender)
{
    int ret=0;
    unsigned char ucType[1];
    unsigned char ucSerialNo[4]="";
    unsigned char ucKeyA[8]="";
    unsigned char ucKeyB[8]="";
//    char SerialNo[9]="";
    char sKeyA[17]="";
    char sKeyB[17]="";
    memset(sKeyA,0,sizeof(sKeyA));
    memset(sKeyB,0,sizeof(sKeyB));    
    ret=SMT_RequestCardExist(ucSerialNo,ucType);
    if(ret)
    {
        ShowMessage("卡不在读卡器感应区");
        return ;
    }
    ret=gen_user_card_keyA(ucWorkKey,ucSerialNo,ucKeyA);
    if(ret)
    {
       ShowMessage("计算KeyA出错");
       return;
    }
    dec2hex(ucKeyA,6,sKeyA);
    edtKeyA->Text=sKeyA;
    ret=gen_user_card_keyB(ucWorkKey,ucSerialNo,ucKeyB);
    if(ret)
    {
       ShowMessage("计算KeyB出错");
       return;
    }
    dec2hex(ucKeyB,6,sKeyB);
    edtKeyB->Text=sKeyB;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReadVersionClick(TObject *Sender)
{
    int ret=0;
    int flag=0;
    char sVersion[13]="";
    
    ret=SMT_ReadBlackNameListVersion(&flag,sVersion);
    edtVersion->Text=sVersion;
    if(flag==1)
    {
        chkVersion->Checked=true;
    	SMT_ControlBuzzer();
    	SMT_ControlBuzzer();
    	SMT_ControlBuzzer();
    }
    else
        chkVersion->Checked=false;
 }
//---------------------------------------------------------------------------


void __fastcall TForm1::btnCardInitClick(TObject *Sender)
{
    int ret;
    ret=MessageDlg("你真的要恢复卡出厂状态吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    char sKey[13]="";
    unsigned char ucKey[6]="";
    unsigned char ucBuf[17]="";
    char sBuf[33]="";
    unsigned char ucSerialNo[4]="";
    unsigned char ucType[1];
    unsigned char ucInitKey[6]="";
    int SectorNo=0;

    memset(sBuf,0,sizeof(sBuf));
    memset(ucInitKey,0xFF,sizeof(ucInitKey));
    if(edtSectorNo->Text.Trim().Length()==0)
    {
        ShowMessage("请输入扇区号");
        return;
    }
    SectorNo=edtSectorNo->Text.ToInt();
    ret=SMT_RequestCardExist(ucSerialNo,ucType);
    if(ret)
    {
        ShowMessage("卡不在读卡器感应区");
        return ;
    }
    int index=rg1->ItemIndex;
    if(edtKeyA->Text.Trim().Length()!=12)
    {
        btnCalKeyClick(this);
        Sleep(100);
    }
    switch(index)
    {
    case 0:
            memcpy(sKey,edtKeyA->Text.c_str(),12);
            hex2dec(sKey,ucKey,6);
            ret=SMT_Login_With_UserKey(SectorNo,ucKey,0);
            if(ret)
            {
                ShowMessage("读第"+edtSectorNo->Text+"扇区失败");
                return ;
            }
            break;
    case 1:
            memcpy(sKey,edtKeyB->Text.c_str(),12);
            hex2dec(sKey,ucKey,6);
            ret=SMT_Login_With_UserKey(SectorNo,ucKey,1);
            if(ret)
            {
                ShowMessage("读第"+edtSectorNo->Text+"扇区失败");
                return ;
            }
            break;
        default:
             ShowMessage("请选择登录方式");
            return;
    }
    memset(ucBuf,0xFF,sizeof(ucBuf));
    ucBuf[6] = 0xFF;
	ucBuf[7] = 0x07;
	ucBuf[8] = 0x80;
	ucBuf[9] = 0x69;
    SMT_WriteBlock(SectorNo,3,ucBuf);
    ret=SMT_RequestCardExist(ucSerialNo,ucType);
    if(ret)
    {
        ShowMessage("卡不在读卡器感应区");
        return ;
    }
    ret=SMT_Login_With_UserKey(SectorNo,ucInitKey,0);
    if(ret)
    {
        ShowMessage("写第"+edtSectorNo->Text+"扇区第3块失败");
        return ;
    }
	SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnResetPackClick(TObject *Sender)
{
    int ret=0;
    int packetno=1;
    ret=MessageDlg("你真的要重设钱包吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    ret=SMT_ResetPacketInfo(packetno);
    if(ret)
    {
        ShowMessage("重设钱包失败");
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnSetPacketClick(TObject *Sender)
{
    int ret;
    int ecode;
    char msg[1024]="";
    int packetno=1;
    MONEY_PACK_INFO  PurseInfo;

	memset(&PurseInfo,0,sizeof(PurseInfo));
    ret=MessageDlg("你真的要修改钱包信息吗",
               mtConfirmation, TMsgDlgButtons()<<mbNo<<mbYes, 0);
    if(ret!=mrYes)
        return;
    PurseInfo.bala=-1;
    PurseInfo.daybala=-1;
    PurseInfo.total_cnt=-1;
    PurseInfo.date=-1;
    PurseInfo.time=-1;
    if(edtBalance->Text.Trim().Length()>0)
        PurseInfo.bala= edtBalance->Text.ToDouble()*100;
    if(edtTxCnt->Text.Trim().Length()>0)
        PurseInfo.total_cnt=edtTxCnt->Text.ToInt();
    if(edtDayBala->Text.Trim().Length()>0)
        PurseInfo.daybala= edtDayBala->Text.ToDouble()*100;
    if(edtTxDate->Text.Trim().Length()>0)
        PurseInfo.date=edtTxDate->Text.ToInt();
    if(edtTxTime->Text.Trim().Length()>0)
    {
        char buf[100]="";
        strcpy(buf,edtTxTime->Text.Trim().c_str());
        char *p=strchr(buf,':');
        strcpy(p,p+1);
        PurseInfo.time=StrToInt(buf);
    }
     int mon  = (20050818/1000000)%100;    
    ret=SMT_SetPacketInfo(packetno,&PurseInfo);
    if(ret)
    {
        ShowMessage("重设钱包失败");
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    int ret=0;
    char sBlkVer[13]="";
    if(edtVersion->Text.Trim().Length()==0)
    {
        ShowMessage("请输入版本号");
        edtVersion->SetFocus();
        return;
    }
    strcpy(sBlkVer,edtVersion->Text.c_str());
    ret=SMT_SetNormalFlagByBlkVerion(sBlkVer);
    if(ret)
    {
        ShowMessage("设置版本号失败");
        return;
    }
    SMT_ControlBuzzer();
}
//---------------------------------------------------------------------------

