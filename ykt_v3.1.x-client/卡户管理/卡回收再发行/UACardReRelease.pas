unit UACardReRelease;

interface
              
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls,
  UICtrls, WVCtrls, Mask, UtCardDll, SmartCardCommon,Db,
  RzPanel, RzStatus, RzButton, RzRadChk, Buttons, UIncrementComboBox,
  RzEdit;

type
  TfaqhCardReRelease = class(TfaqhInputTemp)
    UIPanel3: TUIPanel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    LabRecordCount: TLabel;
    WVLabel3: TWVLabel;
    WVLabel4: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel6: TWVLabel;
    WVLabel11: TWVLabel;
    WVLabel12: TWVLabel;
    WVLabel10: TWVLabel;
    WVLabel9: TWVLabel;
    WVLabel8: TWVLabel;
    WVLabel7: TWVLabel;
    grp1: TGroupBox;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    WVRelCardOk: TWorkView;
    WVRRelCardOk: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    btnReleaseCard: TBitBtn;
    RzStatusPane4: TRzStatusPane;
    edtPhyId: TRzEdit;
    edtCardId: TRzEdit;
    edtEndDate: TRzEdit;
    edtBalance: TRzEdit;
    edtPwd: TRzEdit;
    edtFeeType: TRzEdit;
    RzStatusPane5: TRzStatusPane;
    procedure btnReleaseCardClick(Sender: TObject);
  private
    { Private declarations }
    phyId:string;
    cardId:string;
    balance:Integer;
    tradeNum:Integer;

    function readCardInfo: Boolean;
  public
    { Public declarations }
    procedure Init;override;
  end;

var
  faqhCardReRelease: TfaqhCardReRelease;

implementation
uses KSFrameWorks, KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaqhCardReRelease.Init;
begin
  inherited;
end;

procedure TfaqhCardReRelease.btnReleaseCardClick(Sender: TObject);
var
  //rCardId:Integer;
  rBalance:Integer;
  rFeeType:Integer;
  rPwd:string;
  rEndDate:string;
  rTradeNum:Integer;
  cardManage: TCardManage;
  CardInfo: TPublishCardMes;
  perCoutMoney,perDayMoney:Integer;
begin
  phyId:='';
  cardId:='';
  balance:=0;
  tradeNum:=0;
  if Application.MessageBox('你确定要回收然后再重新发行该卡吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  if readCardInfo=False then
    Exit;
  WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(cardId));
  WorkView.FieldByName('物理编号').Data.SetString(phyId);
  WorkView.FieldByName('交易次数').Data.SetInteger(tradeNum);
  WorkView.FieldByName('卡余额').Data.SetInteger(balance);
  MainRequest.SendCommand;
  if (WorkView.FieldByName('返回码').Data.AsInteger = 0) then
  begin
    //rCardId := WorkView.fieldbyname('卡号').Data.AsInteger;
    rBalance := WorkView.fieldbyname('卡余额').Data.AsInteger;
    rFeeType := WorkView.fieldbyname('收费类别').Data.AsInteger;
    rPwd := WorkView.fieldbyname('卡密码').Data.AsString;
    rEndDate := WorkView.fieldbyname('有效期').Data.AsString;
    rTradeNum := WorkView.fieldbyname('交易次数').Data.AsInteger;
    cardManage := nil;
    try
      cardManage := TCardManage.Create;
      strcopy(@CardInfo.DeadLineDate, PChar(rEndDate)); //截至日期*
      CardInfo.CardRightType := rFeeType;               //收费类别*
      strcopy(@CardInfo.ucPwd, PChar(rPwd));            //密码*
      strcopy(@CardInfo.ucName, PChar(''));             //客户名称
      strcopy(@CardInfo.ucDutyNo, PChar(''));           //职位代码
      strcopy(@CardInfo.ucCertificateNo, PChar(''));    //身份证号
      strcopy(@CardInfo.ucDepartmentNo, PChar(''));     //部门代码
      strcopy(@CardInfo.ucLibraryNo, PChar(''));        //图书证号
      strcopy(@CardInfo.ucSexNo, PChar(''));            //性别
      strcopy(@CardInfo.ucIdentifyNo, PChar(''));       //客户类别
      strcopy(@CardInfo.ucCardNo, PChar(''));           //学工号
      //ShowMessage(CardInfo.ucPwd);
      //strcopy(@CardInfo.ShowCardNo, PChar(sshowCardNo));//显示卡号
      if CardManage.UpdateCardBasicInfo(CardInfo)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('写卡信息失败，请放好卡后重新执行该操作！');
        exit;
      end;
      if (CardManage.ChangeCardPsw(rPwd))<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('更新卡密码失败，请放好卡后重新操作！');
        exit;
      end;

      if CardManage.packetSetMoneyAndChk(inttostr(rBalance),rBalance)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('写卡余额失败，请放好卡后重新执行该操作！');
        exit;
      end;

      if cardManage.changeTradeNum(rTradeNum)<>0 then
      begin
        Context.GetDialogSystem.ShowWarning('更新卡交易次数失败，请放好卡后重新执行该操作！');
        exit;
      end;
      //设置单次消费限额和日消费限额
      if maxper=1 then
      begin
        perCoutMoney := WorkView.fieldbyname('单次限额').Data.AsInteger;
        perDayMoney := WorkView.fieldbyname('日限额').Data.AsInteger;
        if cardManage.SetConsumeLimit(perCoutMoney,perDayMoney)<>0 then
        begin
          Context.GetDialogSystem.ShowMessage('更新卡单次限额和当日限额失败,请重新操作!');
          Exit;
        end;
      end;

      edtPhyId.Text := phyId;
      edtCardId.Text := cardId;
      edtBalance.Text := FloatToStr(rBalance/100);
      edtEndDate.Text := rEndDate;
      edtFeeType.Text := GetIdObjectName(-43,IntToStr(rFeeType));
      edtPwd.Text := rPwd;

      CardManage.ControlBuzzer;
      Context.GetDialogSystem.ShowSuccess('重新写卡信息成功！');
    finally
      cardManage.Destroy;
    end;
  end
  else
  begin
    getReturn('',WorkView);
    RzStatusPane1.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
  end;
end;

function TfaqhCardReRelease.readCardInfo:Boolean;
var
  cardManage: TCardManage;
  LPI: LOOPPURSEINFO;
begin
  Result := False;
  if PrepareReadCardInfo=False then
    Exit;
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    //取物理卡号
    if CardManage.ReadCardPhyID(phyId) <> 0 then
    begin
      ShowMessage('读卡序列号失败，请重新把卡放置到读写器上！');
      exit;
    end;
    //读取交易卡号
    if CardManage.ReadExCardID(cardId) <> 0 then
    begin
      ShowMessage('读交易卡号失败，请放置好卡！');
      Exit;
    end;
    if CardManage.ReadCardConsumeInfo(LPI, 0)=False then
    begin
      ShowMessage('读用户卡消费信息失败！');
      Exit;
    end
    else
    begin
      balance := StrToInt(format('%d', [LPI.RemainMoney]));
      tradeNum := StrToInt(format('%d', [LPI.DealTimes]));
    end;
    Result := True;
  finally
    cardManage.Destroy;
  end;
end;

initialization
  TUIStdClassFactory.Create('卡回收再发行', TfaqhCardReRelease);
end.
