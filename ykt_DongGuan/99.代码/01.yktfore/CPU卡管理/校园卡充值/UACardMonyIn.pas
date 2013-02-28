unit UACardMonyIn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox,RzStatus, EditExts, CardDll, RzEdit,
  Buttons,RM_Class;

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
    WVLabel1: TWVLabel;
    edtmoneymoneymoney: TRzNumericEdit;
    edtmoney: TWVDigitalEdit;
    chkSaveMoney: TCheckBox;
    chkPrint: TCheckBox;
    btnRePrint: TBitBtn;
    WVRequest1: TWVRequest;
    WorkView1: TWorkView;
    WVRTradeCancel: TWVRequest;
    WVTradeCancel: TWorkView;
    procedure btnMoneyInClick(Sender: TObject);
    procedure cbbTypeChange(Sender: TObject);
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

    //procedure writeSuccess(wv: TWorkView;money:Integer;cm:TCM);
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhCardMonyIn: TfaqhCardMonyIn;
  OldMoney: string;

implementation

uses KsFrameworks, KSClientConsts,SmartCardCommon,KSDataDictionary;

{$R *.DFM}

procedure TfaqhCardMonyIn.Init;
begin
  inherited;
  lblTip.Caption := '';
  cbbType.ItemIndex:=0;
  //edtTicketNo.Enabled := False;
  btnMoneyIn.Enabled:=False;
  btnReadCardInfo.SetFocus;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
end;

procedure TfaqhCardMonyIn.btnMoneyInClick(Sender: TObject);
var
  payCnt,dptCnt,subsidyNo:Integer;
  balance:Integer;
  st:Integer;
  //OutMoney: Integer;
  //rCardNo:string;

  //rTradeDate:string;
  //rTradeTime:string;
  //rStationNo:string;
  nowTime:Cardinal;
  cm: TCM;
  tp:TTRANSPACK;
  phyId:string;
  loDate,loTime:string;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  fMoney:string;
  cardNo1:string;
  reErrMsg:array[0..255] of Char;
  rest:PChar;
  appSerialNo:string;
  tmpDataset:TDataSet;
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
      Context.GetDialogSystem.ShowMessage('请使用同一张卡进行充值！');
      btnReadCardInfo.SetFocus;
      btnMoneyIn.Enabled := False;
      Exit;
    end;
    if psamTermId='' then
    begin
      Context.GetDialogSystem.ShowMessage('请先设置PSAM卡座，然后再充值！');
      Exit;
    end;

    //读取充值的交易次数
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
    {
    //发送功能号
    WorkView.FieldByName('物理卡号').Data.SetString(phyId);
    WorkView.FieldByName('卡号').Data.SetString(edtCardNo.Text);
    WorkView.FieldByName('入卡金额').Data.SetInteger(balance);
    WorkView.FieldByName('交易次数').Data.SetInteger(dptCnt);
    WorkView.FieldByName('消费次数').Data.SetInteger(payCnt);
    WorkView.FieldByName('充值类型').Data.SetInteger(StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1)));
    WorkView.FieldByName('充值金额').Data.SetFloat(StrToFloat(fMoney));
    WorkView.FieldByName('psam卡号').Data.SetString(psamTermId);
    WorkView.FieldByName('本机流水号').Data.SetString(loTime);
    WorkView.FieldByName('本机日期').Data.SetString(loDate);
    WorkView.FieldByName('本机时间').Data.SetString(loTime);
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
    OutMoney := WorkView.FieldByName('出卡金额').Data.AsInteger;
    serialNo := WorkView.FieldByName('流水号').Data.AsString;
    rCardNo := WorkView.FieldByName('卡号').Data.AsString;
    cardNo1 := WorkView.FieldByName('卡号1').Data.AsString;
    rTradeDate := WorkView.FieldByName('业务日期').Data.AsString;
    rtradetime := WorkView.FieldByName('业务时间').Data.AsString;
    rStationNo := WorkView.FieldByName('终端编号').Data.AsString;
    }

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
    StrCopy(@tp.TransDate,PChar(loDate));
    //交易时间
    StrCopy(@tp.TransTime,PChar(loTime));
    //终端号
    StrCopy(@tp.Termno,PChar(psamTermId));
    //ShowMessage(tp.Termno);
    //充值操作员
    StrCopy(@tp.OperCode,PChar(Context.ParamData(svOperatorNoName).AsString));
    //充值类型
    tp.FundType := StrToInt(Copy(cbbType.Text,1,Pos('-',cbbType.Text)-1));
    //交易前金额
    tp.BefBalance := balance;
    //交易金额
    tp.TransAmt := Round(StrToFloat(fMoney)*100);
    //交易前充值次数
    tp.DptCardCnt := dptCnt;
    //交易前消费次数
    tp.PayCardCnt := payCnt;
    //交易前补助次数
    tp.SubsidyNo := subsidyNo;

    //修改设置金额方式
    {
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    writeSuccess(WorkView,OutMoney,cm);
    }
    //开始设置卡余额
    st := ks_load4card(@tp);
    if st<>0 then
    begin
      if tp.cGetProveFlag=Char(1) then
      begin
        //循环寻卡
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>30000 then
          begin
            Context.GetDialogSystem.ShowMessage('充值超时，请使用卡余额调整检查是否充值成功！');
            ks_dotransunprove(@tp);
            Exit;
          end;
          st := cm.card(PhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
          end
          else
          begin
            //寻到卡后，判断是否为同一张卡，如果不是，提示重新放卡
            if PhyId<>oldPhyId then
              Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，请重新放置！')
            else
              Break;
          end;
          Continue;
        end;
        Sleep(50);
        st:=ks_load4card_retry(@tp);
        if st=0 then
        begin
          cm.beep;
        end
        else
        begin
          //重新写卡失败，提示是否冲正该交易,冲正退出
          WVTradeCancel.FieldByName('交易日期').Data.SetString(tp.TransDate);
          WVTradeCancel.FieldByName('交易时间').Data.SetString(tp.TransTime);
          WVTradeCancel.FieldByName('sam终端号').Data.SetString(psamTermId);
          WVTradeCancel.FieldByName('记账日期').Data.SetString(tp.TransDate);
          WVTradeCancel.FieldByName('交易参考号').Data.SetString(tp.RefNo);
          //WVTradeCancel.FieldByName('冲正操作员').Data.SetInteger(tOperId);
          WVTradeCancel.FieldByName('冲正金额').Data.SetFloat(StrToFloat(fMoney));
          try
            WVRTradeCancel.SendCommand;
            RzStatusPane2.Caption := WVTradeCancel.fieldbyname('返回信息').Data.AsString;
          except

          end;
          Exit;
        end;
      end
      else
      begin
        reSt := ks_geterrmsg(PChar(@reErrMsg));
        Context.GetDialogSystem.ShowMessage(reErrMsg);
      end;
    end
    else
    begin
      edtAfterMoney.Text := format('%f', [tp.AftBalance / 100]);
      cm.beep;
      if chkPrint.Checked then
      begin
        try
          WorkView1.FieldByName('客户号').Data.SetInteger(0);
          WorkView1.FieldByName('卡序列号').Data.SetString(appSerialNo);
          WorkView1.FieldByName('卡类型').Data.SetInteger(0);
          WorkView1.FieldByName('卡状态').Data.SetInteger(0);
          try
            WVRequest1.SendCommand;
            if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
            begin
              tmpDataset := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject);
              cardType := GetIdObjectName(-1,tmpDataset.fieldbyname('lvol1').AsString);
              phoneNo := tmpDataset.fieldbyname('sphone2').AsString;
              custName := tmpDataset.fieldbyname('snote').AsString;
              cardNo1 := tmpDataset.fieldbyname('scard0').AsString;
            end;
          except

          end;
          serialNo := tp.RefNo;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '充  值';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo+'-'+Context.ParamData(svOperatorNameName).AsString;
          rptReport.Dictionary.Variables.AsString['cardNo'] := cardNo1;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [tp.AftBalance / 100.0])+'元';
          rptReport.Dictionary.Variables.AsString['param2'] := '充值金额：';
          rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f', [strtofloat(fMoney)])+' 元';
          rptReport.Dictionary.Variables.AsString['param3'] := '充值时间：';
          rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\cardmoneyin.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          on e:Exception do
          Context.GetDialogSystem.ShowMessage('你没有安装打印机，不能打印--'+e.Message);
        end;
      end;
    end;
  finally
    rptReport.Free;
    cm.Free;
  end;
end;

procedure TfaqhCardMonyIn.cbbTypeChange(Sender: TObject);
begin
  inherited;
  //edtTicketNo.Text:='';
  if (cbbType.ItemIndex = 0) then
  begin
    edtmoneymoneymoney.Enabled := True;
    //edtTicketNo.Enabled := False;
  end
  else
  begin
    edtmoneymoneymoney.Enabled := True;
    //edtTicketNo.Enabled := True;
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
  //发送查询交易，查看该卡是否为正常卡，如果不正常则鸣叫两声，退出
  {
  WorkView1.FieldByName('卡号').Data.SetInteger(0);
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
  CardState := (WorkView1.FieldByName('查询结果集').Data.AsObject as TDataSet).FieldByName('sserial0').AsString;
  if Copy(CardState,1,4) <> '1000' then
  begin
    cm.beep;
    cm.beep;
    Context.GetDialogSystem.ShowMessage('该卡不是正常状态的卡，不能充值！');
    btnReadCardInfo.SetFocus;
    Exit;
  end;
  }
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
      {
    if bjopen=1 then
    begin
      bj(bjcomport,'W');
      bj(bjcomport,'&C11姓  名：'+trim(edtName.Text)+'$');
      bj(bjcomport,'&C21卡余额：'+trim(edtCardMoney.Text)+'元$');
    end;
    }
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
    {
    if edtTicketNo.Enabled then
      edtTicketNo.SetFocus
    else
    }
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

{
procedure TfaqhCardMonyIn.writeSuccess(wv: TWorkView;money: Integer;cm: TCM);
begin
  edtAfterMoney.Text := format('%f', [money / 100]);
  cm.beep;
  if chkSaveMoney.Checked=False then
    edtmoney.Text := '0';
  btnMoneyIn.Enabled := False;
  btnReadCardInfo.SetFocus;
  RzStatusPane2.Caption:=wv.FieldByName('返回信息').Data.AsString;

end;
}
procedure TfaqhCardMonyIn.btnRePrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\cardmoneyin.rmp');
end;

initialization
  TUIStdClassFactory.Create('卡现金充值', TfaqhCardMonyIn);

end.

