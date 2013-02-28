unit UAChangeCardOper;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,RM_Class,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus;

type
  TfaqhChangeCardOper = class(TfaqhSimpleQueryTemp)
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
    edtCardNo: TWVEdit;
    cbbDept: TWVComboBox;
    cbbIDType: TWVComboBox;
    btnLoss: TBitBtn;
    WVChangeCardOper: TWorkView;
    WVRChangeCardOper: TWVRequest;
    btnReadCard: TBitBtn;
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
  faqhChangeCardOper: TfaqhChangeCardOper;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhChangeCardOper.Init;
begin
  inherited;
  if ks_comminit(PChar(scIP),scPORT,scFUNCNO)<>0 then
    Context.GetDialogSystem.ShowMessage('��ʼ�����Ӻ�̨ʧ�ܣ������´򿪸ý��棡');
end;

procedure TfaqhChangeCardOper.btnQueryClick(Sender: TObject);
begin
  inherited;
  btnLoss.Enabled := True;
end;

procedure TfaqhChangeCardOper.btnLossClick(Sender: TObject);
var
  sDate,sTime:string;
  appSerialNo:string;
  phyId:string;
  //cardNo:Integer;
  bDptNum,bPayNum,money:Integer;
  cm: TCM;
  st:Integer;

  rTradeDate:string;
  rTradeTime:string;
  rSerialNo:string;
  rMoney:Integer;
  rOperSerialNo:Integer;
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
  
  if Application.MessageBox('��ȷ��Ҫ������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
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
    //cm.setfieldreadmode(CARD_NO);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
      Exit;
    end;
    try
      appSerialNo := cm.getAppSerialNo;
      //cardNo := StrToInt(cm.getCardNo);
      bDptNum := StrToInt(cm.getDptCardCnt);
      bPayNum := StrToInt(cm.getPayCardCnt);
      money := StrToInt(cm.getCardBalance);
    except
      //cardNo := 0;
      bDptNum := 0;
      bPayNum := 0;
      money := 0;
    end;
    sDate := FormatDateTime('yyyymmdd',Date);
    sTime := FormatDateTime('hhmmss',Now);
    WVChangeCardOper.FieldByName('��������').Data.SetString(sDate);
    WVChangeCardOper.FieldByName('����ʱ��').Data.SetString(sTime);
    WVChangeCardOper.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
    WVChangeCardOper.FieldByName('��Ӧ�����к�').Data.SetString(Grid.DataSource.DataSet.fieldbyname('sphone3').AsString);
    WVChangeCardOper.FieldByName('Ӧ�����к�').Data.SetString(appSerialNo);
    WVChangeCardOper.FieldByName('����').Data.SetInteger(Grid.DataSource.DataSet.fieldbyname('scard0').AsInteger);
    WVChangeCardOper.FieldByName('������').Data.SetString(phyId);
    WVChangeCardOper.FieldByName('��ֵ����').Data.SetInteger(bDptNum);
    WVChangeCardOper.FieldByName('���Ѵ���').Data.SetInteger(bPayNum);
    WVChangeCardOper.FieldByName('�����').Data.SetInteger(money);
    try
      WVRChangeCardOper.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage(e.Message);
        Exit;
      end;
    end;
    rMoney := WVChangeCardOper.FieldByName('����ֵ').Data.AsInteger;
    rTradeDate := WVChangeCardOper.FieldByName('��������').Data.AsString;
    rtradetime := WVChangeCardOper.FieldByName('����ʱ��').Data.AsString;
    rSerialNo := WVChangeCardOper.FieldByName('�ն˺�').Data.AsString;
    rOperSerialNo := WVChangeCardOper.FieldByName('��ˮ��').Data.AsInteger;
    //д����Ϣ��������Ч�ں�״̬
    cm.clearallfieldwritemode;
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    cm.setDeadLineDate(rTradeDate);
    st := cm.writeData(phyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('д��״̬ʧ��<'+getErrMsg+'>,������:'+inttostr(st));
      Exit;
    end;

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
    RzStatusPane2.Caption:=WVChangeCardOper.FieldByName('������Ϣ').Data.AsString;
    if chkPrint.Checked then
    begin
      try
        serialNo := WVChangeCardOper.fieldbyname('��ˮ��').Data.AsString;
        cardType := WVChangeCardOper.fieldbyname('������').Data.AsString;
        phoneNo := WVChangeCardOper.fieldbyname('�ֻ�').Data.AsString;
        custName := WVChangeCardOper.fieldbyname('����').Data.AsString;
        rCardNo  := WVChangeCardOper.fieldbyname('����').Data.AsString;
        rptReport := TRMReport.Create(Self);
        rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
        rptReport.Dictionary.Variables.AsString['phoneNo'] := phoneNo;
        rptReport.Dictionary.Variables.AsString['custName'] := custName;
        rptReport.Dictionary.Variables.AsString['titleType'] := '����������';
        rptReport.Dictionary.Variables.AsString['serialNo'] := IntToStr(rOperSerialNo);
        rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
        rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
        rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
        rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
        rptReport.Dictionary.Variables.AsString['cardNo'] := rCardNo;
        rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
        rptReport.Dictionary.Variables.AsString['param1'] := '������';
        rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [rmoney / 100.0])+' Ԫ';
        rptReport.Dictionary.Variables.AsString['param2'] := '����ʱ�䣺';
        rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
        rptReport.Dictionary.Variables.AsString['param3'] := '';
        rptReport.Dictionary.Variables.AsString['pValue3'] := '';
        rptReport.ShowPrintDialog := False;
        rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\changeoper.rmp');
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
  btnQuery.Click;
end;

procedure TfaqhChangeCardOper.btnReadCardClick(Sender: TObject);
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

procedure TfaqhChangeCardOper.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\changeoper.rmp');
end;

initialization
  TUIStdClassFactory.Create('����������',TfaqhChangeCardOper);

end.