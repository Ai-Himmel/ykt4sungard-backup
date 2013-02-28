unit UMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  Mask, WVCtrls, WVDBBinders, Db, 
  RzStatus, EditExts, RzEdit, Buttons, CardDll, RM_Common, RM_Class;

type
  TfaMoney = class(TfaInputTemp)
    DataSource1: TDataSource;
    WVDBBinder1: TWVDBBinder;
    btnReadCardInfo: TBitBtn;
    btnMoneyOut: TBitBtn;
    RzStatusPane2: TRzStatusPane;
    UIPnlQueryCount: TUIPanel;
    grp2: TGroupBox;
    edtmoney: TWVDigitalEdit;
    WVLabel1: TWVLabel;
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
    RzStatusPane7: TRzStatusPane;
    WVcashOperCancel: TWorkView;
    WVRcashOperCancel: TWVRequest;
    chkPrint: TCheckBox;
    rpt1: TRMReport;
    procedure btnReadCardInfoClick(Sender: TObject);
    procedure btnMoneyOutClick(Sender: TObject);
  private
    { Private declarations }
    oldPhyId:string;

    procedure writeSuccess(wv:TWorkView;money:Integer;cm:TCM);

    procedure printDestVoucher(rtn,custName,custId,cardNo,stempNO,lastDate,regDate:String);
  protected
     procedure Init; override;
  public
    { Public declarations }
  end;

var
  faMoney: TfaMoney;
  OldMoney: string;

implementation
uses KsFrameworks, KSClientConsts,KSDataDictionary;

{$R *.DFM}

procedure TfaMoney.Init;
begin
  inherited;
  btnMoneyOut.Enabled:=false;
  btnreadcardinfo.setfocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaMoney.btnReadCardInfoClick(Sender: TObject);
var
  CardExID: string;
  cm: TCM;
  CardPhyID:string;
  st:integer;
  //ResInt: SmallInt;
begin
  //CardExID:=readCardOneInfo(CARD_NO);
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

procedure TfaMoney.btnMoneyOutClick(Sender: TObject);
var
  CardPhyID: string;
  balance:Integer;
  OutMoney: Integer;
  cm:TCM;
  //rStationNo:Integer;
  //SeilID: integer;
  //TOF: Integer;
  //NewMoney: Integer;
  payCnt,dptCnt,subsidyNo:Integer;
  tp:TTRANSPACK;
  tradeDate,tradeTime:string;
  st:Integer;
  custType:string;
  //reErrMsg:array[0..255] of Char;
  //reSt : PChar;
begin
  if preReadCard=False then
    Exit;

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
    cm.setfieldreadmode(CARD_SERI_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CUST_TYPE);
    cm.setfieldreadmode(PATCH_NO);
    if cm.readCard(cardPhyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重试！');
      Exit;
    end;

    if oldPhyId <> CardPhyID then
    begin
      ShowMessage('请使用同一张卡进行支取金额！');
      btnReadCardInfo.SetFocus;
      btnMoneyOut.Enabled := False;
      Exit;
    end;
    //交易次数
    try
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
      custType := GetIdObjectName(-34,Trim(cm.getCustType));
    except
      Context.GetDialogSystem.ShowMessage('读取卡消费次数失败，操作取消！');
      Exit;
    end;

    if (StrToFloat(edtCardMoney.Text))<(StrToFloat(Trim(edtMoney.Text))) then
    begin
      Context.GetDialogSystem.ShowMessage('你支取的余额超出可用余额！');
      Exit;
    end;
    //发送功能号
    WorkView.SynchronizeCtrlsToFields;
    WorkView.FieldByName('卡号').Data.SetInteger(StrToInt(edtCardNo.Text));
    WorkView.FieldByName('物理卡号').Data.SetString(CardPhyID);
    WorkView.FieldByName('充值次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('交易次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.asinteger<>0 then
    begin
      getReturn('卡支取失败－－',WorkView);
      RzStatusPane2.Caption:=WorkView.FieldByName('返回信息').Data.AsString;
      Exit;
    end;

    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    //SeilID := WorkView.FieldByName('流水号').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('卡号').Data.AsInteger;
    tradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    tradeTime := WorkView.fieldbyname('业务时间').Data.AsString;
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
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      //Context.GetDialogSystem.ShowMessage(reSt);
      RzStatusPane2.Caption:=cashOperCancel(WVcashOperCancel,WVRcashOperCancel,TradeDate,SeilID,StrToInt(scsiteno));
    end;
    }
    //cm.halt;
    try
      if chkPrint.Checked then
        printDestVoucher(edtmoney.Text,edtName.Text,'',edtCardNo.Text,edtStuempNo.Text,custType,'');
    except

    end;
  finally
    cm.Destroy;
  end;

end;

procedure TfaMoney.writeSuccess(wv: TWorkView; money: Integer;
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
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;

procedure TfaMoney.printDestVoucher(rtn, custName, custId, cardNo, stempNO,
  lastDate, regDate: String);
begin
  try
    rpt1.LoadFromFile(sPreAppPath+'report\支取凭证.rmf');
    rpt1.Dictionary.Variables.AsString['rtnInfo'] := rtn+' 元';
    rpt1.Dictionary.Variables.AsString['custName'] := custName;
    rpt1.Dictionary.Variables.AsString['custId'] := custId;
    rpt1.Dictionary.Variables.AsString['cardNo'] := cardNo;
    rpt1.Dictionary.Variables.AsString['stuempNo'] := stempNO;
    rpt1.Dictionary.Variables.AsString['custType'] := lastDate;
    rpt1.Dictionary.Variables.AsString['regDate'] := regDate;
    rpt1.Dictionary.Variables.AsString['rptTitle'] := rptTitle;
    rpt1.Dictionary.Variables.AsString['operName'] := Context.ParamData(svOperatorNameName).AsString;
    rpt1.DoublePass := True;
    //rpt1.Preview := rmprvwP;
    rpt1.ShowReport;
    
  except
    Context.GetDialogSystem.ShowMessage('你没有安装打印机，请先安装(可以是虚拟打印机)！');
  end;
end;

initialization
  TUIStdClassFactory.Create('卡现金支取',TfaMoney);

end.
