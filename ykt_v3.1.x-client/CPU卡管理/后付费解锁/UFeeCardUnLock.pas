unit UFeeCardUnLock;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll;

type
  TfaFeeCardUnlock = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp1: TGroupBox;
    WVLabel5: TWVLabel;
    WVLabel10: TWVLabel;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    RzStatusPane5: TRzStatusPane;
    RzStatusPane6: TRzStatusPane;
    edtName: TRzEdit;
    edtCardNo: TRzEdit;
    edtStuempNo: TRzEdit;
    edtCardMoney: TRzEdit;
    edtAfterMoney: TRzEdit;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    RzStatusPane7: TRzStatusPane;
    edtMoney: TRzEdit;
    lbl1: TWVLabel;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faFeeCardUnlock: TfaFeeCardUnlock;
  OldMoney: string;

implementation
uses KsFrameworks, KSClientConsts;

{$R *.DFM}

procedure TfaFeeCardUnlock.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  btnreadcardinfo.setfocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaFeeCardUnlock.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  cm: TCM;
  CardPhyID:string;
  st:integer;
  cardSign:Integer;
begin
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
      exit;
    end;
    cm.clearallfieldreadmode;
    setOperReadMode(cm);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;
    oldPhyId := CardPhyID;
    CardExID := cm.getCardNo;
    if CardExID='' then
    begin
      Context.GetDialogSystem.ShowMessage('读取卡号失败,请重新读取！');
      Exit;
    end;

    try
      cardSign := StrToInt(cm.getBlackCardSign);
    except
      Context.GetDialogSystem.ShowMessage('读取卡标志失败-'+geterrmsg);
      Exit;
    end;

    if cardSign<>FEE_LOCK_CARD then
    begin
      Context.GetDialogSystem.ShowMessage('该卡状态不是后付费锁卡状态，不用在此界面操作！');
      Exit;
    end;
    
    edtCardNo.Text := CardExID;
    edtName.Text := cm.getCustName;
    edtStuempNo.Text := cm.getStuempNo;
    try
      OldMoney := cm.getCardBalance;
      edtCardMoney.Text := format('%f', [StrToInt(OldMoney) / 100.0]);
      edtAfterMoney.Text :=format('%f', [StrToInt(OldMoney) / 100.0]);
    except
      Context.GetDialogSystem.ShowWarning('读取卡余额失败！');
      Exit;
    end;

    if bjopen=1 then
    begin
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额：'+trim(edtCardMoney.Text)+'元$');
    end;

    btnMoneyOut.Enabled:=True;
  finally
    cm.Destroy;
  end;
end;

procedure TfaFeeCardUnlock.btnMoneyOutClick(Sender: TObject);
var
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  cm:TCM;
  payCnt,dptCnt,lockCnt:Integer;
  lockDev,lockDate,lockTime:string;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  rtnCardNo,rtnTradeMoney:Integer;
  st:Integer;

begin
  if preReadCard=False then
    Exit;

  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(cardPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败-'+geterrmsg);
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(LOCK_TERMID);
    cm.setfieldreadmode(LOCK_TRANSDATE);
    cm.setfieldreadmode(LOCK_TRANSTIME);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(LOCK_CARDCNT);
    //cm.setfieldreadmode();
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('请使用同一张卡进行操作！');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
      Exit;
    end;
    //交易次数
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      balance := StrToInt(cm.getCardBalance);
      lockDev:=cm.getLockTermId;
      lockDate:=cm.getLockTransDate;
      lockTime:=cm.getLockTransTime;
      lockCnt := StrToInt(cm.getLockCardCnt);
    except
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;

    //发送功能号
    //WorkView.SynchronizeCtrlsToFields;

    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(cm.getCardNo));
    WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WorkView.FieldByName('消费次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    WorkView.FieldByName('锁卡设备').Data.SetString(lockDev);
    WorkView.FieldByName('锁卡日期').Data.SetString(lockDate);
    WorkView.FieldByName('锁卡时间').Data.SetString(lockTime);
    WorkView.FieldByName('锁卡次数').Data.SetInteger(lockCnt);
    
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsString<>'0' then
    begin
      getReturn('',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;
    rtnCardNo := WorkView.FieldByName('卡号').Data.AsInteger;
    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    rtnTradeMoney := WorkView.FieldByName('扣款金额').Data.AsInteger;
    tradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    tradeTime := WorkView.fieldbyname('业务时间').Data.AsString;
    if rtnTradeMoney<>0 then
    begin
      ZeroMemory(@tp,SizeOf(tp));
      //终端交易序列号
      tp.TermSeqno := 1;
      //终端编号
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //交易卡号
      tp.CardNo := rtnCardNo;
      //物理编号
      StrCopy(@tp.CardPhyID,PChar(CardPhyID));
      //交易日期
      StrCopy(@tp.TransDate,PChar(TradeDate));
      //交易时间
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //交易前金额
      tp.BefBalance := balance;
      //交易后金额
      tp.AftBalance := OutMoney;
      //交易前充值次数
      tp.DptCardCnt := dptCnt;
      //交易前消费次数
      tp.PayCardCnt := payCnt;
      //交易前补助次数
      //tp.SubsidyNo := subsidyNo;

      if setCardBal(tp,cm,cardPhyId)<>0 then
        Exit;
    end;
    //开始解锁
    cm.clearallfieldwritemode;
    //cm.setfieldwritemode(BLACK_CARD_SIGN);
    //cm.setfieldwritemode(BLACK_VER);
    //cm.setBlackVer(WVCardLose.FieldByName('卡版本号').Data.AsString);
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    st := cm.writeData(cardPhyId);
    if st <> 0 then
    begin
      Context.GetDialogSystem.ShowWarning('解锁失败-'+geterrmsg);
    end
    else
    begin
      edtMoney.Text := format('%f', [rtnTradeMoney / 100]);
      writeSuccess(WorkView,OutMoney,cm);
      //cm.halt;
    end;
  finally
    cm.Destroy;
  end;

end;

procedure TfaFeeCardUnlock.writeSuccess(wv: TWorkView; money: Integer;
  cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if bjopen=1 then
  begin
    bj(bjcomport,'&Sc$');
    bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
    bj(bjcomport,'&C21充  值：'+trim(edtmoney.Text)+'元$');
    bj(bjcomport,'&C31卡余额：'+trim(edtAfterMoney.Text)+'元$');
  end;

  btnMoneyOut.Enabled := False;
  btnReadCardInfo.SetFocus;
  Context.GetDialogSystem.ShowMessage('后付费扣款成功！');
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('后付费扣款',TfaFeeCardUnlock);

end.
