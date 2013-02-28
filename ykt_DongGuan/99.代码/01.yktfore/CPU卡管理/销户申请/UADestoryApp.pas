unit UADestoryApp;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,RM_Class,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus;

type
  TfaqhDestoryApp = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    WVEdit3: TWVEdit;
    WVEdit5: TWVEdit;
    edtAppSerialNo: TWVEdit;
    Label1: TLabel;
    WVEdit1: TWVEdit;
    cbbDept: TWVComboBox;
    cbbIDType: TWVComboBox;
    btnLoss: TBitBtn;
    WVChangeCard: TWorkView;
    WVRChangeCard: TWVRequest;
    btnReadCard: TBitBtn;
    Label7: TLabel;
    edtReason: TWVEdit;
    lbl1: TLabel;
    RzStatusPane2: TRzStatusPane;
    chkPrint: TCheckBox;
    procedure btnQueryClick(Sender: TObject);
    procedure btnLossClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhDestoryApp: TfaqhDestoryApp;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhDestoryApp.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhDestoryApp.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhDestoryApp.btnLossClick(Sender: TObject);
var
  cardNo:Integer;
  sDate,sTime:string;

  appSerialNo:string;
  phyId:string;
  bDptNum,bPayNum,money:Integer;
  ptradecode,pmoney:Integer;
  pDate,pTime,pSamNo:string;
  cm: TCM;
  st:Integer;

  rTradeDate:string;
  rTradeTime:string;
  rSerialNo:string;
  rMoney:Integer;
  //rOperSerialNo:Integer;
  tp:TTRANSPACK;
  
  rptReport:TRMReport;
  custName:string;
  phoneNo:string;
  serialNo:string;
  cardType:string;
  //fMoney:string;
  rCardNo:string;
begin
  if preReadCard=False then
    Exit;
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('������PSAM����,Ȼ���ٽ��в�����');
    Exit;
  end;
  
  if Application.MessageBox('��ȷ��Ҫ����������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  cm := nil;
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
    cm.setfieldreadmode(CARD_NO);
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
      cardNo := StrToInt(cm.getCardNo);
    except
      bDptNum := 0;
      bPayNum := 0;
      money := 0;
      ptradecode := 0;
      pmoney := 0;
      cardNo := 0;
    end;
    sdate := FormatDateTime('yyyymmdd',Date);
    stime := FormatDateTime('hhmmss',now);
    WVChangeCard.FieldByName('��������').Data.SetString(sdate);
    WVChangeCard.FieldByName('����ʱ��').Data.SetString(stime);
    WVChangeCard.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
    WVChangeCard.FieldByName('����').Data.SetInteger(cardNo);
    WVChangeCard.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
    WVChangeCard.FieldByName('����ԭ��').Data.SetString(edtReason.Text);
    WVChangeCard.FieldByName('��ֵ����').Data.SetInteger(bDptNum);
    WVChangeCard.FieldByName('���Ѵ���').Data.SetInteger(bPayNum);
    WVChangeCard.FieldByName('�����').Data.SetInteger(money);
    WVChangeCard.FieldByName('�ϱ�sam�ն�').Data.SetString(pSamNo);
    WVChangeCard.FieldByName('�ϱ�����').Data.SetInteger(ptradecode);
    WVChangeCard.FieldByName('�ϱʽ��').Data.SetInteger(pmoney);
    WVChangeCard.FieldByName('�ϱ�����').Data.SetString(pDate);
    WVChangeCard.FieldByName('�ϱ�ʱ��').Data.SetString(pTime);
    try
      WVRChangeCard.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        Exit;
      end;
    end;
    rMoney := 0;//WVChangeCard.FieldByName('����ֵ').Data.AsInteger;
    rTradeDate := WVChangeCard.FieldByName('��������').Data.AsString;
    rtradetime := WVChangeCard.FieldByName('����ʱ��').Data.AsString;
    rSerialNo := WVChangeCard.FieldByName('�ն˺�').Data.AsString;
    serialNo := WVChangeCard.FieldByName('��ˮ��').Data.AsString;
    //д����Ϣ��������Ч�ں�״̬
    cm.clearallfieldwritemode;
    cm.setBlackCardSign(IntToStr(DESTORY));
    //ShowMessage(IntToStr(DESTORY));
    cm.setDeadLineDate(rTradeDate);
    st := cm.writeData(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('д��״̬ʧ��<'+getErrMsg+'>,������:'+inttostr(st));
      Exit;
    end;
    
    //�ѿ��������0
    ZeroMemory(@tp,SizeOf(tp));
    //�ն˽������к�
    tp.TermSeqno := StrToInt(serialNo);
    //�ն˱��
    StrCopy(@tp.Termno,PChar(rSerialNo));
    //���׿���
    tp.CardNo := 0;//rCardNo;
    //������
    StrCopy(@tp.CardPhyID,PChar(phyId));
    //��������
    StrCopy(@tp.TransDate,PChar(rTradeDate));
    //����ʱ��
    StrCopy(@tp.TransTime,PChar(rtradeTime));
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

    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WVChangeCard.fieldbyname('��ˮ��').Data.AsString;
          cardType := WVChangeCard.fieldbyname('������').Data.AsString;
          phoneNo := WVChangeCard.fieldbyname('�ֻ�').Data.AsString;
          custName := WVChangeCard.fieldbyname('����').Data.AsString;
          rCardNo  := WVChangeCard.fieldbyname('����').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
          rptReport.Dictionary.Variables.AsString['custName'] := custName;
          rptReport.Dictionary.Variables.AsString['titleType'] := '��������';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '������';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [money / 100.0])+' Ԫ';
          rptReport.Dictionary.Variables.AsString['param2'] := '����ʱ�䣺';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '';
          rptReport.Dictionary.Variables.AsString['pValue3'] := '';
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\destoryapp.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          on e:Exception do
          Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ--'+e.Message);
        end;
      finally
        rptReport.Free;
      end;
    end;

    RzStatusPane2.Caption:=WVChangeCard.FieldByName('������Ϣ').Data.AsString;
    btnQuery.Click;
  finally
    cm.Free;
  end;
end;

procedure TfaqhDestoryApp.btnReadCardClick(Sender: TObject);
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

procedure TfaqhDestoryApp.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\destoryapp.rmp');
end;

initialization
  TUIStdClassFactory.Create('��������',TfaqhDestoryApp);

end.