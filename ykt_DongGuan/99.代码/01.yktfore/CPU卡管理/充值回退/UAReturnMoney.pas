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
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhReturnMoney.btnQueryClick(Sender: TObject);
begin
  if Trim(edtEndDate.Text)<>'' then
    if CheckInputDateFormat(edtEndDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtEndDate.SetFocus;
      Exit;
    end;
  if Trim(edtBeginDate.Text)<>'' then
    if CheckInputDateFormat(edtBeginDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ�������벻��ȷ����ʽ��yyyymmdd');
      edtBeginDate.SetFocus;
      Exit;
    end;
  if (Trim(edtEndDate.Text)<>'') and (Trim(edtBeginDate.Text)<>'') then
    if Trim(edtBeginDate.Text)>Trim(edtEndDate.Text) then
    begin
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ����������룡');
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
  tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
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
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ����ȷ��úÿ���');
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
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
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
    WVRtnMoney.FieldByName('�ο���').Data.SetString(inRefNo);
    WVRtnMoney.FieldByName('��������').Data.SetString(inTradeDate);

    WVRtnMoney.FieldByName('��������').Data.SetString(sDate);
    WVRtnMoney.FieldByName('����ʱ��').Data.SetString(sTime);
    WVRtnMoney.FieldByName('sam�ն˺�').Data.SetString(samNo);
    WVRtnMoney.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
    WVRtnMoney.FieldByName('��������').Data.SetString(phyId);
    WVRtnMoney.FieldByName('����ǰ��ֵ����').Data.SetInteger(bDptNum);
    WVRtnMoney.FieldByName('����ǰ���Ѵ���').Data.SetInteger(bPayNum);
    WVRtnMoney.FieldByName('�����').Data.SetInteger(money);
    WVRtnMoney.FieldByName('�ϱ�sam�ն˺�').Data.SetString(pSamNo);
    WVRtnMoney.FieldByName('�ϱ�����').Data.SetInteger(ptradecode);
    WVRtnMoney.FieldByName('�ϱʽ��').Data.SetInteger(pmoney);
    WVRtnMoney.FieldByName('�ϱ�����').Data.SetString(pDate);
    WVRtnMoney.FieldByName('�ϱ�ʱ��').Data.SetString(pTime);
    WVRtnMoney.FieldByName('����Ա���').Data.SetInteger(operId);
    WVRtnMoney.FieldByName('����Ա��ˮ').Data.SetInteger(operSeriNo);
    WVRtnMoney.FieldByName('��������').Data.SetString(hostDate);
    try
      WVRRtnMoney.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        Exit;
      end;
    end;
    rMoney := WVRtnMoney.FieldByName('�����').Data.AsInteger;
    //rCardNo := WorkView.FieldByName('����').Data.AsString;
    rTradeDate := WVRtnMoney.FieldByName('��������').Data.AsString;
    rtradetime := WVRtnMoney.FieldByName('����ʱ��').Data.AsString;
    rSerialNo := WVRtnMoney.FieldByName('sam�ն˺�').Data.AsString;
    refNo := WVRtnMoney.FieldByName('�ο���').Data.AsString;
    rOperSerialNo := WVRtnMoney.FieldByName('����Ա��ˮ').Data.AsInteger;
    
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := rOperSerialNo;
    //�ն˱��
    StrCopy(@tp.Termno,PChar(rSerialNo));
    //���׿���
    tp.CardNo := 0;//rCardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(phyId));

    //��������
    StrCopy(@tp.TransDate,PChar(rTradeDate));
    //ShowMessage(tp.TransDate);
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(rtradeTime));
    //���ײο���
    StrCopy(@tp.RefNo,PChar(refNo));
    //ShowMessage(tp.RefNo);
    //����ǰ���
    tp.BefBalance := money;
    //���׺���
    tp.AftBalance := rMoney;
    //����ǰ��ֵ����
    tp.DptCardCnt := bDptNum;
    //����ǰ���Ѵ���
    tp.PayCardCnt := bPayNum;
    //����ǰ��������
    //tp.SubsidyNo := subsidyNo;
    //�޸����ý�ʽ
    if setCardBal(tp,cm,phyId)<>0 then
      Exit;
    cm.beep;
    RzStatusPane2.Caption:=WVRtnMoney.FieldByName('������Ϣ').Data.AsString;
    
    if chkPrint.Checked then
    begin
      try
        //serialNo := WorkView.fieldbyname('������ˮ').Data.AsString;
        cardType := WVRtnMoney.fieldbyname('�����').Data.AsString;
        phoneNo := WVRtnMoney.fieldbyname('�ֻ�').Data.AsString;
        custName := WVRtnMoney.fieldbyname('����').Data.AsString;
        rptReport := TRMReport.Create(Self);
        rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
        rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
        rptReport.Dictionary.Variables.AsString['custName'] := custName;
        rptReport.Dictionary.Variables.AsString['titleType'] := '��ֵ����';
        rptReport.Dictionary.Variables.AsString['serialNo'] := IntToStr(rOperSerialNo);
        rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
        rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
        rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
        rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
        rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
        rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
        rptReport.Dictionary.Variables.AsString['param1'] := '������';
        rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [rMoney / 100.0])+'Ԫ';
        rptReport.Dictionary.Variables.AsString['param2'] := '���˽�';
        rptReport.Dictionary.Variables.AsString['pValue2'] := format('%f',[strtofloat(fMoney)])+'Ԫ';
        rptReport.Dictionary.Variables.AsString['param3'] := '����ʱ�䣺';
        rptReport.Dictionary.Variables.AsString['pValue3'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\returnmoney.rmp');
        if showrpt=1 then
          rptReport.ShowReport
        else
          rptReport.PrintReport;
      except
        on e:Exception do

        Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ--'+e.Message);
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
    Context.GetDialogSystem.ShowMessage('������ѯʧ�ܣ�Ӧ�����к�Ϊ��򲻴���!');
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
  TUIStdClassFactory.Create('��ֵ����',TfaqhReturnMoney);

end.