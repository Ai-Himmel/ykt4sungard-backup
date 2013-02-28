unit UAReturnMoney;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqhReturnMoney = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtAppSerialNo: TWVEdit;
    edtCardNo: TWVEdit;
    WVEdit6: TWVEdit;
    cbbIDType: TWVComboBox;
    WVRtnMoney: TWorkView;
    WVRRtnMoney: TWVRequest;
    RzStatusPane2: TRzStatusPane;
    btnReadCard: TBitBtn;
    chkPrint: TCheckBox;
    btnRePrint: TBitBtn;
    lbl1: TLabel;
    edtReason: TWVEdit;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox1: TWVComboBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnRePrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhReturnMoney: TfaqhReturnMoney;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhReturnMoney.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('初始化连接后台失败，请重新打开该界面！');
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhReturnMoney.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('结束日期输入不正确，格式：yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期输入不正确，格式：yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('开始日期不能大于结束日期，请重新输入！');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  inherited;

end;

procedure TfaqhReturnMoney.btnPrintClick(Sender: TObject);
var
  sDate,sTime:string;
  samNo:string;
  appSerialNo:string;
  phyId:string;
  bDptNum,bPayNum,money:Integer;
  ptradecode,pmoney:Integer;
  pDate,pTime,pSamNo:string;
  operId,operSeriNo:Integer;
  hostDate:string;
  cm: TCM;
  st:Integer;
  tmpData:TDataSet;

  rTradeDate:string;
  rTradeTime:string;
  rSerialNo:string;
  rMoney:Integer;
  rOperSerialNo:Integer;
  tp:TTRANSPACK;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  //serialNo:string;
  cardType:string;
  fMoney:string;
  rCardNo:string;
  refNo:string;

  inRefNo:string;
  inTradeDate:string;
begin
  if preReadCard=False then
    Exit;
  tmpData := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  operId := tmpData.fieldbyname('lbank_acc_type2').AsInteger;
  operSeriNo := tmpData.fieldbyname('lserial0').AsInteger;
  hostDate := tmpData.fieldbyname('sdate1').AsString;
  fMoney := tmpData.fieldbyname('damt0').AsString;
  rCardNo := tmpData.fieldbyname('lvol0').AsString;
  sDate := tmpData.fieldbyname('sdate0').AsString;//FormatDateTime('yyyymmdd',Date);
  sTime := tmpData.fieldbyname('stime0').AsString;//FormatDateTime('hhmmss',Now);
  
  inTradeDate := tmpData.fieldbyname('sdate3').AsString;
  inRefNo := tmpData.fieldbyname('scert_no').AsString;
  samNo := psamTermId;
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
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CF_APPSERIALNO);

    cm.setfieldreadmode(TRANS_AMT);
    cm.setfieldreadmode(TRANS_TYPE);
    cm.setfieldreadmode(TERM_ID);
    cm.setfieldreadmode(TRANS_DATE);
    cm.setfieldreadmode(TRANS_TIME);
    //cm.setfieldreadmode(CF_APPSERIALNO);
    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败-'+geterrmsg);
      Exit;
    end;
    try
      appSerialNo := cm.getAppSerialNo;
      pSamNo := cm.getTermId;
      pDate := cm.getTransDate;
      pTime := cm.getTransTime;
      bDptNum := StrToInt(cm.getDptCardCnt);
      bPayNum := StrToInt(cm.getPayCardCnt);
      money := StrToInt(cm.getCardBalance);
      ptradecode := StrToInt(cm.getTransType);
      pmoney := StrToInt(cm.getTransAmt);
    except
      bDptNum := 0;
      bPayNum := 0;
      money := 0;
      ptradecode := 0;
      pmoney := 0;
    end;
    WVRtnMoney.FieldByName('参考号').Data.SetString(inRefNo);
    WVRtnMoney.FieldByName('记账日期').Data.SetString(inTradeDate);

    WVRtnMoney.FieldByName('交易日期').Data.SetString(sDate);
    WVRtnMoney.FieldByName('交易时间').Data.SetString(sTime);
    WVRtnMoney.FieldByName('sam终端号').Data.SetString(samNo);
    WVRtnMoney.FieldByName('应用序列号').Data.SetString(appSerialNo);
    WVRtnMoney.FieldByName('卡物理编号').Data.SetString(phyId);
    WVRtnMoney.FieldByName('交易前充值次数').Data.SetInteger(bDptNum);
    WVRtnMoney.FieldByName('交易前消费次数').Data.SetInteger(bPayNum);
    WVRtnMoney.FieldByName('卡余额').Data.SetInteger(money);
    WVRtnMoney.FieldByName('上笔sam终端号').Data.SetString(pSamNo);
    WVRtnMoney.FieldByName('上笔类型').Data.SetInteger(ptradecode);
    WVRtnMoney.FieldByName('上笔金额').Data.SetInteger(pmoney);
    WVRtnMoney.FieldByName('上笔日期').Data.SetString(pDate);
    WVRtnMoney.FieldByName('上笔时间').Data.SetString(pTime);
    WVRtnMoney.FieldByName('操作员编号').Data.SetInteger(operId);
    WVRtnMoney.FieldByName('操作员流水').Data.SetInteger(operSeriNo);
    WVRtnMoney.FieldByName('主机日期').Data.SetString(hostDate);
    try
      WVRRtnMoney.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        Exit;
      end;
    end;
    rMoney := WVRtnMoney.FieldByName('卡余额').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('卡号').Data.AsString;
    rTradeDate := WVRtnMoney.FieldByName('主机日期').Data.AsString;
    rtradetime := WVRtnMoney.FieldByName('主机时间').Data.AsString;
    rSerialNo := WVRtnMoney.FieldByName('sam终端号').Data.AsString;
    refNo := WVRtnMoney.FieldByName('参考号').Data.AsString;
    rOperSerialNo := WVRtnMoney.FieldByName('操作员流水').Data.AsInteger;
    
    ZeroMemory(@tp,SizeOf(tp));
    //终端交易序列号
    tp.TermSeqno := rOperSerialNo;
    //终端编号
    StrCopy(@tp.Termno,PChar(rSerialNo));
    //交易卡号
    tp.CardNo := 0;//rCardNo;
    //物理编号
    StrCopy(@tp.CardPhyID,PChar(phyId));

    //交易日期
    StrCopy(@tp.TransDate,PChar(rTradeDate));
    //ShowMessage(tp.TransDate);
    //交易时间
    StrCopy(@tp.TransTime,PChar(rtradeTime));
    //交易参考号
    StrCopy(@tp.RefNo,PChar(refNo));
    //ShowMessage(tp.RefNo);
    //交易前金额
    tp.BefBalance := money;
    //交易后金额
    tp.AftBalance := rMoney;
    //交易前充值次数
    tp.DptCardCnt := bDptNum;
    //交易前消费次数
    tp.PayCardCnt := bPayNum;
    //交易前补助次数
    //tp.SubsidyNo := subsidyNo;
    //修改设置金额方式
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    cm.beep;
    RzStatusPane2.Caption:=WVRtnMoney.FieldByName('返回信息').Data.AsString;
    
    if chkPrint.Checked then
    begin
      try
        //serialNo := WorkView.fieldbyname('交易流水').Data.AsString;
        cardType := WVRtnMoney.fieldbyname('卡类别').Data.AsString;
        phoneNo := WVRtnMoney.fieldbyname('手机').Data.AsString;
        custName := WVRtnMoney.fieldbyname('姓名').Data.AsString;
        rptReport := TRMReport.Create(Self);
        rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
        rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
        rptReport.Dictionary.Variables.AsString['custName'] := custName;
        rptReport.Dictionary.Variables.AsString['titleType'] := '充值回退';
        rptReport.Dictionary.Variables.AsString['serialNo'] := IntToStr(rOperSerialNo);
        rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
        rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
        rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
        rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
        rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
        rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
        rptReport.Dictionary.Variables.AsString['param1'] := '卡内余额：';
        rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [rMoney / 100.0])+'元';
        rptReport.Dictionary.Variables.AsString['param2'] := '回退金额：';
        rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f',[strtofloat(fMoney)])+'元';
        rptReport.Dictionary.Variables.AsString['param3'] := '回退时间：';
        rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\returnmoney.rmp');
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

procedure TfaqhReturnMoney.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppSerialNo.Text:='';
  try
    cardNo := readCardOneInfo(CF_APPSERIALNO);
  except
    Exit;
  end;
  if (cardNo='') or (cardNo='0') then
  begin
    Context.GetDialogSystem.ShowMessage('读卡查询失败，应用序列号为零或不存在!');
    Exit;
  end;
  edtAppSerialNo.Text:=cardNo;
  btnQuery.Click();
end;

procedure TfaqhReturnMoney.btnRePrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\returnmoney.rmp');
end;

initialization
  TUIStdClassFactory.Create('充值回退',TfaqhReturnMoney);

end.