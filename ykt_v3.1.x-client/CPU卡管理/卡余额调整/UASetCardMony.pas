unit UASetCardMony;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons, RzPanel, RzRadGrp;

type
  TfaqhSetCardMony = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    grp2: TGroupBox;
    WVLabel3: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane7: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    edtmoneymoneymoney: TRzNumericEdit;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    rzstspn1: TRzStatusPane;
    rgDirection: TRzRadioGroup;
    edtMoney: TRzEdit;
    rzstspn2: TRzStatusPane;
    edtTradeNum: TRzEdit;
    rzstspn3: TRzStatusPane;
    rzstspn4: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    edtPwd: TWVEdit;
    rzstspn5: TRzStatusPane;
    edtLibMoney: TRzEdit;
    rzstspn6: TRzStatusPane;
    edtCardBal: TRzEdit;
    RzStatusPane8: TRzStatusPane;
    edtPayNum: TRzEdit;
    RzStatusPane5: TRzStatusPane;
    edtBeforeMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    RzStatusPane6: TRzStatusPane;
    WVLabel10: TWVLabel;
    WVLabel5: TWVLabel;
    WVLabel1: TWVLabel;
    WVLabel2: TWVLabel;
    procedure btnMoneyInClick(Sender: TObject);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtMoneyChange(Sender: TObject);
    procedure rgDirectionClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;
    function readCardInfo(cm:TCM): Boolean;
    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);
    procedure calcMoney;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSetCardMony: TfaqhSetCardMony;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaqhSetCardMony.Init;
begin
  inherited;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhSetCardMony.btnMoneyInClick(Sender: TObject);
var
  cm:TCM;
  st:Integer;
  payCnt,dptCnt:Integer;
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  tp:TTRANSPACK;
  //tof:Integer;
  rTradeDate:string;
  rtradetime:string;
  //SeilID: integer;
  ragion:Integer;
  operCode:string;
  operPwd:string;
  subsidyNo:Integer;
begin
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0')
    or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('输入的金额小数位数不能为空或0！');
    edtMoney.SetFocus;
    Exit;
  end;
  try
    if StrToFloat(edtMoney.Text)>0 then

  except
    Context.GetDialogSystem.ShowMessage('请输入有效的调整金额！');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    {
    cardPhyId := readCardOneInfo(CARD_SERI_NO);
    if cardPhyId = '' then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败,该卡已经损坏！');
      btnReadCardInfo.SetFocus;
      Exit;
    end
    else
    begin
      WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    end;
    }
    if oldPhyId <> CardPhyID then
    begin
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行设置卡余额！');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;

    //先清除所有的读取权限
    cm.clearallfieldreadmode;
    //设置要读取内容的权限
    setOperReadMode(cm);
    st := cm.readCard(cardPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败--'+inttostr(st));
      Exit;
    end;
    if cm.getBlackCardSign<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage('该卡不是正常状态的卡，不能转账，请到读卡信息中读取卡状态！');
      Exit;
    end;

    //读取充值的交易次数
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;

    if rgDirection.ItemIndex=0 then
      ragion := 1
    else
      ragion := -1;
    operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
    operPwd := encOperPwd(operCode,Trim(edtPwd.Text));
    //WorkView.FieldByName('新密码').Data.SetString(operPwd);
    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    WorkView.FieldByName('交易次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('验证密码').Data.SetString(operPwd);
    WorkView.FieldByName('方向').Data.SetInteger(ragion);
    WorkView.FieldByName('调整金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('返回码').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    //SeilID := WorkView.FieldByName('流水号').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('卡号').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    rtradetime := WorkView.FieldByName('业务时间').Data.AsString;
    //rStationNo := WorkView.FieldByName('终端编号').Data.AsInteger;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := StrToInt(edtCardNo.Text);
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(CardPhyID));
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

    if setCardBal(tp,cm,cardPhyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    {
    tof := ks_setcardbal(@tp);
    if tof = 0 then
    begin
      writeSuccess(WorkView,OutMoney,cm);
    end
    else
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,StrToInt(scsiteno));
    }
    edtPwd.Text := '';
    //cm.halt;
  finally
    cm.Destroy;
  end;
end;

function TfaqhSetCardMony.readCardInfo(cm: TCM): Boolean;
var
  cardPhyId:string;
  st:Integer;
  CardExID: string;
  tradeNum:Integer;
begin
  Result := False;
  if preReadCard=False then
    Exit;
  {
  cardPhyId := readCardOneInfo(CARD_SERI_NO);
  if cardPhyId = '' then
  begin
    Context.GetDialogSystem.ShowMessage('读取物理卡号失败,该卡已经损坏！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  st := cm.card(cardPhyId);
  if st<>0 then
  begin
    context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
    exit;
  end;

  oldPhyId := CardPhyID;
  //先清除所有的读取权限
  cm.clearallfieldreadmode;
  //设置要读取内容的权限
  cm.setfieldreadmode(CARD_NO);
  cm.setfieldreadmode(CUST_NAME);
  cm.setfieldreadmode(STUEMP_NO);
  cm.setfieldreadmode(CARD_BALANCE);
  cm.setfieldreadmode(PAY_CARD_CNT);
  cm.setfieldreadmode(DPT_CARD_CNT);
  //setOperReadMode(cm);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('读卡信息失败--'+inttostr(st));
    Exit;
  end;


  CardExID := cm.getCardNo;
  edtCardNo.Text := CardExID;
  
  edtName.Text := cm.getCustName;
  edtStuempNo.Text := cm.getStuempNo;
  
  OldMoney := cm.getCardBalance;
  edtBeforeMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtCardBal.Text := edtBeforeMoney.Text;
  //edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  tradeNum := StrToInt(cm.getDptCardCnt);
  edtTradeNum.Text := IntToStr(tradeNum);
  edtpayNum.text := cm.getPayCardCnt;

  //发送查询交易，查看该卡是否为正常卡，如果不正常则鸣叫两声，退出
  WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(CardExID));
  WorkView1.FieldByName('客户号').Data.SetInteger(0);
  WorkView1.FieldByName('客户类别').Data.SetInteger(0);
  WorkView1.FieldByName('收费类别').Data.SetInteger(0);
  WorkView1.FieldByName('钱包号').Data.SetInteger(0);
  WorkView1.FieldByName('物理卡号').Data.SetString(CardPhyID);
  try
    WVRequest1.SendCommand;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowWarning(e.message);
      btnReadCardInfo.SetFocus;
      Exit;
    end;
  end;
  
  edtLibMoney.Text := (WorkView1.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('damt1').AsString;
  //
  try
    edtAfterMoney.Text := edtLibMoney.Text;
    edtMoney.Text := FloatToStr(Abs(StrToFloat(edtCardBal.Text)-strtofloat(edtLibMoney.Text)));
  except

  end;
  {
  if Copy(CardState,1,4) <> '1000' then
  begin
    CardManage.ControlBuzzer;
    CardManage.ControlBuzzer;
    Context.GetDialogSystem.ShowMessage('该卡不是正常状态的卡，不能调整卡余额！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
  Result := True;
end;

procedure TfaqhSetCardMony.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    btnMoneyIn.Enabled := True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhSetCardMony.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('你确定要为该卡设置金额['+edtmoney.Text+'元]吗？'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhSetCardMony.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

procedure TfaqhSetCardMony.edtMoneyChange(Sender: TObject);
begin
  calcMoney;
end;

procedure TfaqhSetCardMony.rgDirectionClick(Sender: TObject);
begin
  calcMoney;
end;

procedure TfaqhSetCardMony.calcMoney;
begin
  if edtMoney.Text='' then
  begin
    edtMoney.Text := '0';
  end;
  try
    if rgDirection.ItemIndex=0 then
    begin
      edtAfterMoney.Text := FloatToStr(StrToFloat(edtBeforeMoney.Text)+strtofloat(edtMoney.Text));
    end
    else
    begin
      edtAfterMoney.Text := FloatToStr(StrToFloat(edtBeforeMoney.Text)-strtofloat(edtMoney.Text));
    end;
  except
    Context.GetDialogSystem.ShowMessage('请输入有效的数字！');
    Exit;
  end;
end;

initialization
  TUIStdClassFactory.Create('卡余额调整', TfaqhSetCardMony);

end.
