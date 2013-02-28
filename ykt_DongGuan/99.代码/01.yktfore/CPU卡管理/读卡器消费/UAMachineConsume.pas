unit UAMachineConsume;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons,RM_Class;

type
  TfaqhMachineConsume = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    WVLabel3: TWVLabel;
    edtAfterMoney: TRzEdit;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    RzStatusPane8: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    chkPrint: TCheckBox;
    btnRePrint: TBitBtn;
    WorkView2: TWorkView;
    WVRequest2: TWVRequest;
    procedure btnMoneyInClick(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbTypeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure btnRePrintClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(cm:TCM): Boolean;

    procedure writeSuccess(wv: TWorkView;money:Integer;cm:TCM);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhMachineConsume: TfaqhMachineConsume;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhMachineConsume.Init;
begin
  inherited;
  lblTip.Caption := '';
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhMachineConsume.btnMoneyInClick(Sender: TObject);
var
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  OutMoney: Integer;
  rCardNo:string;
  appSerialNo:string;

  rTradeDate:string;
  rTradeTime:string;
  //rStationNo:string;
  cm: TCM;
  tp:TTRANSPACK;
  st:integer;
  phyId:string;
  loDate,loTime:string;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  //cardNo1:string;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0') or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('输入的金额小数位数不能为空或0！');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
  rptReport := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请先放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    //setOperReadMode(cm);
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;
    
    if oldPhyId <> phyId then
    begin
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行消费！');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    //读取卡的交易次数
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      appSerialNo := cm.getAppSerialNo;
    except
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;
    loDate := FormatDateTime('yyyymmdd',Date);
    loTime := FormatDateTime('hhmmss',Now);
    fMoney := edtMoney.Text;
    //发送功能号
    WorkView.FieldByName('交易标志').Data.SetString('1');
    WorkView.FieldByName('交易日期').Data.SetString(loDate);
    WorkView.FieldByName('交易时间').Data.SetString(loTime);
    WorkView.FieldByName('sam终端号').Data.SetString(psamTermId);
    WorkView.FieldByName('sam流水号').Data.SetInteger(StrToInt(loTime));
    WorkView.FieldByName('应用序列号').Data.SetString(appSerialNo);
    WorkView.FieldByName('物理卡号').Data.SetString(phyId);
    WorkView.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('消费次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('消费金额').Data.SetFloat(StrToFloat(fMoney));
    WorkView.FieldByName('卡余额').Data.SetInteger(balance);
    try
      MainRequest.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        exit;
      end;
    end;
    if WorkView.fieldbyname('返回码').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('出卡值').Data.AsInteger;
    serialNo := WorkView.FieldByName('交易参考号').Data.AsString;
    rTradeDate := WorkView.FieldByName('记账日期').Data.AsString;
    rtradetime := WorkView.FieldByName('记账时间').Data.AsString;
    //rStationNo := WorkView.FieldByName('终端编号').Data.AsString;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //终端交易序列号
    tp.TermSeqno := StrToInt(FormatDateTime('hhmmss',Now));
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := 0;//rCardNo;
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //交易日期
    StrCopy(@tp.TransDate,PChar(rTradeDate));
    //交易时间
    StrCopy(@tp.TransTime,PChar(rtradeTime));
    //交易前金额
    tp.BefBalance := balance;
    //交易后金额
    tp.AftBalance := OutMoney;
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
    tp.SubsidyNo := subsidyNo;
    //修改设置金额方式
    if setCardBal(tp,cm,phyId)=0 then
    begin
      WorkView2.FieldByName('交易标志').Data.SetString('2');
      WorkView2.FieldByName('交易日期').Data.SetString(loDate);
      WorkView2.FieldByName('交易时间').Data.SetString(loTime);
      WorkView2.FieldByName('sam终端号').Data.SetString(psamTermId);
      WorkView2.FieldByName('sam流水号').Data.SetInteger(StrToInt(loTime));
      WorkView2.FieldByName('应用序列号').Data.SetString(appSerialNo);
      WorkView2.FieldByName('记账日期').Data.SetString(rTradeDate);
      WorkView2.FieldByName('交易参考号').Data.SetString(serialNo);
      WorkView2.FieldByName('TAC码').Data.SetString(tp.Mac);
      WVRequest2.SendCommand;
      //Context.GetDialogSystem.ShowMessage('消费失败，请重新操作！');
      //Exit;
    end
    else
    begin
      Context.GetDialogSystem.ShowMessage('消费失败，请重新操作！');
      Exit;
    end;
    writeSuccess(WorkView,OutMoney,cm);
    
    if chkPrint.Checked then
    begin
      try
        //serialNo := WorkView.fieldbyname('交易流水').Data.AsString;
        rCardNo := WorkView2.FieldByName('卡号').Data.AsString;
        cardType := WorkView2.fieldbyname('卡类型').Data.AsString;
        phoneNo := WorkView2.fieldbyname('手机').Data.AsString;
        custName := WorkView2.fieldbyname('姓名').Data.AsString;
        rptReport := TRMReport.Create(Self);
        rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
        rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
        rptReport.Dictionary.Variables.AsString['custName'] := custName;
        rptReport.Dictionary.Variables.AsString['titleType'] := '消  费';
        rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
        rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
        rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
        rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
        rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
        rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
        rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
        rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
        rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [OutMoney / 100.0])+'元';
        rptReport.Dictionary.Variables.AsString['param2'] := '消费金额：';
        rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f', [strtofloat(fMoney)])+' 元';
        rptReport.Dictionary.Variables.AsString['param3'] := '消费时间：';
        rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\cardmoneyout.rmp');
        if showrpt=1 then
          rptReport.ShowReport
        else
          rptReport.PrintReport;
      except
        on e:Exception do
        Context.GetDialogSystem.ShowMessage('你没有安装打印机，不能打印--'+e.Message);
      end;
    end;
  finally
    rptReport.Free;
    cm.Free;
  end;
end;

procedure TfaqhMachineConsume.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhMachineConsume.readCardInfo(cm: TCM): Boolean;
var
  //CardExID: string;
  cardPhyId:string;
  //CardState:string;
  st:Integer;

begin
  Result := False;
  if preReadCard=False then
    Exit;
  st := cm.card(cardPhyId);
  if st<>0 then
  begin
    context.GetDialogSystem.ShowMessage('寻卡失败-'+geterrmsg);
    exit;
  end;

  oldPhyId := CardPhyID;
  //先清除所有的读取权限
  cm.clearallfieldreadmode;
  //设置要读取内容的权限
  cm.setfieldreadmode(CF_APPSERIALNO);
  cm.setfieldreadmode(CARD_BALANCE);
  cm.setfieldreadmode(PAY_CARD_CNT);
  cm.setfieldreadmode(DPT_CARD_CNT);
  cm.setfieldreadmode(CERTIFICATE_NO);

  //setOperReadMode(cm);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
    Exit;
  end;
  //CardExID := readCardOneInfo(CARD_NO);
  edtCardNo.Text := cm.getAppSerialNo;
  edtName.Text := cm.getCustName;
  edtStuempNo.Text := cm.getCertNo;

  OldMoney := cm.getCardBalance;
  if OldMoney='' then
  begin
    Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  Result := True;
end;

procedure TfaqhMachineConsume.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    btnMoneyIn.Enabled := True;
    lblTip.Caption := '';
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhMachineConsume.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    edtmoney.SetFocus;
  end;
end;

procedure TfaqhMachineConsume.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('你确定要使用该卡消费['+edtmoney.Text+'元]吗？'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhMachineConsume.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

procedure TfaqhMachineConsume.btnRePrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\cardmoneyout.rmp');
end;

initialization
  TUIStdClassFactory.Create('读卡器消费', TfaqhMachineConsume);

end.

