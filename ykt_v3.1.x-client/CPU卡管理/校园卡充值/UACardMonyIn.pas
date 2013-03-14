unit UACardMonyIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons;

type
  TfaqhCardMonyIn = class(TfaqhSimpleQueryTemp)
    btnReadCardInfo: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    grp2: TGroupBox;
    cbbType: TWVComboBox;
    edtTicketNo: TWVEdit;
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
    RzStatusPane9: TRzStatusPane;
    btnMoneyIn: TBitBtn;
    lblTip: TLabel;
    WVRcashOperCancel: TWVRequest;
    WVcashOperCancel: TWorkView;
    WVLabel1: TWVLabel;
    edtmoneymoneymoney: TRzNumericEdit;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
    procedure WVEdit6KeyPress(Sender: TObject; var Key: Char);
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure cbbTypeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure edtmoneyKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
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
  faqhCardMonyIn: TfaqhCardMonyIn;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon;

{$R *.DFM}

procedure TfaqhCardMonyIn.Init;
begin
  inherited;
  lblTip.Caption := '';
  cbbType.ItemIndex:=0;
  edtTicketNo.Enabled := False;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhCardMonyIn.btnMoneyInClick(Sender: TObject);
var
  //CardPhyID: string;
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  OutMoney: Integer;
  rCardNo:Integer;

  rTradeDate:string;
  rTradeTime:string;
  rStationNo:string;
  //SeilID: integer;
  cm: TCM;
  //TOF: Integer;
  //NewMoney: Integer;
  tp:TTRANSPACK;
  //reErrMsg:array[0..255] of Char;
  //reSt : PChar;
  st:integer;
  phyId:string;
begin
  if StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1))<>1 then
    if Trim(edtTicketNo.Text)='' then
    begin
      Context.GetDialogSystem.ShowMessage('请输入票据号码！');
      edtTicketNo.SetFocus;
      Exit;
    end;
  if ((trim(edtmoney.Text) = '') or (edtMoney.text = '0') or (edtMoney.text = '0.0') or (edtMoney.text = '0.00')) then
  begin
    Context.GetDialogSystem.ShowMessage('输入的金额小数位数不能为空或0！');
    edtMoney.SetFocus;
    Exit;
  end;
  cm := nil;
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

    //cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(BLACK_CARD_SIGN);
    cm.setfieldreadmode(DEADLINE_DATE);
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;
    if (cm.getDeadLineDate<FormatDateTime('yyyymmdd',Date()))then
    begin
      Context.GetDialogSystem.ShowMessage('卡已过期，不能充值！');
      Exit;
    end;
    if cm.getBlackCardSign<>'0' then
    begin
      Context.GetDialogSystem.ShowMessage('该卡不是正常状态的卡，不能转账，请到读卡信息中读取卡状态！');
      Exit;
    end;
    {
    CardPhyID := cm.getCardSeriNo;
    if CardPhyID='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取物理卡号失败！');
      Exit;
    end
    else
    begin
      WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    end;
    }
    if oldPhyId <> phyId then
    begin
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行充值！');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
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
    //发送功能号
    WorkView.FieldByName('物理卡号').Data.SetString(phyId);
    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    WorkView.FieldByName('交易次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('消费次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('充值类型').Data.SetInteger(StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1)));
    WorkView.FieldByName('充值金额').Data.SetFloat(StrToFloat(edtMoney.Text));
    MainRequest.SendCommand;
    if WorkView.fieldbyname('返回码').data.asinteger<>0 then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    //SeilID := WorkView.FieldByName('流水号').Data.AsInteger;
    rCardNo := WorkView.FieldByName('卡号').Data.AsInteger;
    rTradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    rtradetime := WorkView.FieldByName('业务时间').Data.AsString;
    rStationNo := WorkView.FieldByName('终端编号').Data.AsString;
    //preSetMoney(tp);
    ZeroMemory(@tp,SizeOf(tp));
    //终端交易序列号
    tp.TermSeqno := 1;
    //终端编号
    StrCopy(@tp.Termno,PChar(scSiteNo));
    //交易卡号
    tp.CardNo := rCardNo;
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
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    {
    tof := ks_setcardbal(@tp);
    if tof = 0 then
    begin
      writeSuccess(WorkView,OutMoney,cm);
    end
    else
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      Context.GetDialogSystem.ShowMessage(reSt);
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,rTradeDate,SeilID,StrToInt(scsiteno));
    end;
    }
    //cm.halt;
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeChange(Sender: TObject);
begin
  inherited;
  edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := False;
  end
  else
  begin
    edtmoneymoneymoney.Enabled := True;
    edtTicketNo.Enabled := True;
  end;
end;

procedure TfaqhCardMonyIn.WVEdit6KeyPress(Sender: TObject; var Key: Char);
begin
  //inherited;
  if Checkedt(Key,edtMoney.Text)=False then
    Key := #0;
end;

function TfaqhCardMonyIn.readCardInfo(cm: TCM): Boolean;
var
  //CardExID: string;
  cardPhyId:string;
  CardState:string;
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
  cm.setfieldreadmode(CARD_NO);
  cm.setfieldreadmode(CUST_NAME);
  cm.setfieldreadmode(STUEMP_NO);
  cm.setfieldreadmode(CARD_BALANCE);

  //setOperReadMode(cm);
  st := cm.readCard(cardPhyId);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
    Exit;
  end;
  //CardExID := readCardOneInfo(CARD_NO);
  edtCardNo.Text := cm.getCardNo;
  edtName.Text := cm.getCustName;
  edtStuempNo.Text := cm.getStuempNo;

  OldMoney := cm.getCardBalance;
  if OldMoney='' then
  begin
    Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  edtAfterMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
  //发送查询交易，查看该卡是否为正常卡，如果不正常则鸣叫两声，退出
  WorkView1.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
  WorkView1.FieldByName('客户号').Data.SetInteger(0);
  WorkView1.FieldByName('客户类别').Data.SetInteger(0);
  WorkView1.FieldByName('收费类别').Data.SetInteger(0);
  WorkView1.FieldByName('钱包号').Data.SetInteger(0);
  WorkView1.FieldByName('物理卡号').Data.SetString(CardPhyID);
  //WorkView1.FieldByName('物理卡号').Data.SetString(CardPhyID);
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
  CardState := (WorkView1.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  if Copy(CardState,1,4) <> '1000' then
  begin
    cm.beep;
    cm.beep;
    Context.GetDialogSystem.ShowMessage('该卡已经挂失或注销，不能充值！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  Result := True;
end;

procedure TfaqhCardMonyIn.btnReadCardInfoClick(Sender: TObject);
var
  cm:TCM;
begin
  cm := nil;
  try
    cm := TCM.Create;
    if readCardInfo(cm)=False then
      Exit;
    if bjopen=1 then
    begin
      {
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额：'+trim(edtCardMoney.Text)+'元$');
      }
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名:'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额:'+trim(edtCardMoney.Text)+'?$');
      bj(bjcomport, 't');
      bj(bjcomport, trim(edtCardMoney.Text)+'P'); //
    end;
    btnMoneyIn.Enabled := True;
    cbbType.SetFocus;
    lblTip.Caption := '';
  finally
    cm.Destroy;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus
    else
      edtmoney.SetFocus;
  end;
end;

procedure TfaqhCardMonyIn.edtmoneyKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_return then
  begin
    if Application.MessageBox(PChar('你确定要为该卡充值['+edtmoney.Text+'元]吗？'), PChar(Application.Title),MB_OKCANCEL + MB_ICONQUESTION) = IDCANCEL then
    begin
      edtmoney.SetFocus;
      Exit;
    end;
    btnMoneyIn.Click;
  end;
end;

procedure TfaqhCardMonyIn.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if bjopen=1 then
  begin
    {
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21充  值：'+trim(edtmoney.Text)+'元$');
    bj(bjcomport,'&C31卡余额：'+trim(edtAfterMoney.Text)+'元$');
    }
        bj(bjcomport,'&Sc$');
        bj(bjcomport,'&C11姓  名:'+trim(edtName.Text)+'$');
        bj(bjcomport,'&C21充  值:'+trim(edtmoney.Text)+'?$');
        bj(bjcomport, 'B');    //发声，预收
        bj(bjcomport, trim(edtmoney.Text)+'P');//发声，多少钱

        bj(bjcomport,'&C31卡余额:'+trim(edtAfterMoney.Text)+'?$');

        bj(bjcomport, 't'); //发声，账户余额
        bj(bjcomport, trim(edtAfterMoney.Text)+'P');   //发声，多少钱
        bj(bjcomport,'&C41谢谢'+'X');

  end;

  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('卡现金充值', TfaqhCardMonyIn);

end.

