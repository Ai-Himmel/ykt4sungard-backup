unit UAAnonGetCardNew;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus,RM_Class;

type
  TfaqAnonGetCardNew = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtCustNo: TWVEdit;
    WVEdit2: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit7: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit9: TWVEdit;
    WVEdit11: TWVEdit;
    edtAppNo: TWVEdit;
    cbbDept: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    WVRequest2: TWVRequest;
    WorkView2: TWorkView;
    btnReadCard: TBitBtn;
    btnGetCard: TBitBtn;
    chkPrint: TCheckBox;
    Label13: TLabel;
    edtMoney: TWVEdit;
    rzstspn1: TRzStatusPane;
    procedure btnQueryClick(Sender: TObject);
    procedure GridCellClick(Column: TColumn);
    procedure btnGetCardClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqAnonGetCardNew: TfaqAnonGetCardNew;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqAnonGetCardNew.Init;
begin
  inherited;
  {
  WorkView.FieldByName('�ͻ���').DefaultValue := 0;
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('֤������').DefaultValue := '';
  WorkView.FieldByName('֤������').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('�绰').DefaultValue := '';
  WorkView.FieldByName('�ֻ�').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := 0;
  WorkView.FieldByName('�ƿ�����').DefaultValue := '';
  WorkView.FieldByName('�������κ�').DefaultValue := 0;
  WorkView.Reset;
  }
end;

procedure TfaqAnonGetCardNew.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  btnGetCard.Enabled := False;
  //ʵ����Ϊ1��2Ϊ��ʵ��
  WorkView.FieldByName('��ѯ���').Data.SetString('2');
  //��ѯ���
  inherited;
  btnGetCard.Enabled := True;
end;

procedure TfaqAnonGetCardNew.GridCellClick(Column: TColumn);
var
  custId:Integer;
  cardNo:string;
  cardType:Integer;
begin
  try
    custId:=Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
    cardType:=Grid.DataSource.DataSet.fieldbyname('lvol1').AsInteger;
    cardNo:=Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  except
    custId := 0;
    cardType :=0;
  end;
  WorkView2.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView2.FieldByName('����').Data.SetString(cardNo);
  WorkView2.FieldByName('�����').Data.SetInteger(cardType);
  WVRequest2.SendCommand;
  if WorkView2.FieldByName('������').Data.AsInteger=0 then
  begin
    rzstspn1.Caption := WorkView2.fieldbyname('�ɷ���Ϣ').Data.AsString;
    edtMoney.Text := WorkView2.fieldbyname('Ԥ�����').Data.AsString;
  end
  else
    rzstspn1.Caption := WorkView2.fieldbyname('������Ϣ').Data.AsString;
end;

procedure TfaqAnonGetCardNew.btnGetCardClick(Sender: TObject);
var
  custId:Integer;
  cardNo:string;
  cm: TCM;
  st:integer;
  phyId,appSerialNo:string;
  loDate,loTime:string;
  payCnt,DptCnt,cardBal:Integer;
  rptReport:TRMReport;
  //custName:string;
  //phoneNo:string;
  serialNo:string;
  cardType:string;
begin
  if not preReadCard then
    Exit;
  if Application.MessageBox('��ȷ��Ҫ�����쿨������',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
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
    cm.setfieldreadmode(CF_APPSERIALNO);
    cm.setfieldreadmode(CARD_BALANCE);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(DPT_CARD_CNT);

    if cm.readCard(phyId)<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ��-'+geterrmsg);
      Exit;
    end;
    appSerialNo := cm.getAppSerialNo;
    payCnt := StrToInt(cm.getPayCardCnt);
    DptCnt := StrToInt(cm.getDptCardCnt);
    cardBal := StrToInt(cm.getCardBalance);
  finally
    cm.Destroy;
  end;
  loDate := FormatDateTime('yyyymmdd',Date);
  loTime := FormatDateTime('hhmmss',Now);
  custId := Grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  cardNo := Grid.DataSource.DataSet.fieldbyname('scard0').AsString;
  WorkView1.FieldByName('������־').Data.SetString('N');
  WorkView1.FieldByName('����').Data.SetString(cardNo);
  WorkView1.FieldByName('�ͻ���').Data.SetInteger(custId);
  WorkView1.FieldByName('Ԥ����').Data.SetFloat(StrToFloat(edtMoney.text));
  WorkView1.FieldByName('�����к�').Data.SetString(appSerialNo);
  WorkView1.FieldByName('psam����').Data.SetString(psamTermId);
  WorkView1.FieldByName('������ˮ��').Data.SetString(loTime);
  WorkView1.FieldByName('��������').Data.SetString(loDate);
  WorkView1.FieldByName('����ʱ��').Data.SetString(loTime);
  WorkView1.FieldByName('��������').Data.SetString(phyId);
  WorkView1.FieldByName('�����').Data.SetString(scSiteNo);
  WorkView1.FieldByName('��ֵ����').Data.SetInteger(DptCnt);
  WorkView1.FieldByName('���Ѵ���').Data.SetInteger(payCnt);
  WorkView1.FieldByName('�����').Data.SetInteger(cardBal);
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(WorkView1.FieldByName('������Ϣ').Data.AsString)
  else
  begin
    rptReport := nil;
    if chkPrint.Checked then
    begin
      try
        try
          serialNo := WorkView1.fieldbyname('������ˮ').Data.AsString;
          cardType := WorkView1.fieldbyname('������').Data.AsString;
          rptReport := TRMReport.Create(Self);
          rptReport.LoadFromFile(sPreAppPath+'report\RtnTicket\printTemp.rmf');
          rptReport.Dictionary.Variables.AsString['phoneNo'] := '';
          rptReport.Dictionary.Variables.AsString['custName'] := '';
          rptReport.Dictionary.Variables.AsString['titleType'] := '��ʵ��������';
          rptReport.Dictionary.Variables.AsString['serialNo'] := serialNo;
          rptReport.Dictionary.Variables.AsString['netId'] := scNetNo;
          rptReport.Dictionary.Variables.AsString['netName'] := scNetName;
          rptReport.Dictionary.Variables.AsString['termId'] := psamTermId;
          rptReport.Dictionary.Variables.AsString['operId'] := scOperNo;
          rptReport.Dictionary.Variables.AsString['cardNo'] := cardNo;
          rptReport.Dictionary.Variables.AsString['cardType'] := cardType;
          rptReport.Dictionary.Variables.AsString['param1'] := '������';
          rptReport.Dictionary.Variables.AsString['pValue1'] := format('%f', [cardBal / 100.0])+'Ԫ';
          rptReport.Dictionary.Variables.AsString['param2'] := '����ʱ�䣺';
          rptReport.Dictionary.Variables.AsString['pValue2'] := FormatDateTime('yyyy-MM-dd hh:MM:ss',Now);
          rptReport.Dictionary.Variables.AsString['param3'] := '';
          rptReport.Dictionary.Variables.AsString['pValue3'] := '';
          rptReport.ShowPrintDialog := False;
          rptReport.SaveToFile(sPreAppPath+'report\RtnTicket\getcard.rmp');
          if showrpt=1 then
            rptReport.ShowReport
          else
            rptReport.PrintReport;
        except
          Context.GetDialogSystem.ShowMessage('��û�а�װ��ӡ�������ܴ�ӡ��');
        end;
      finally
        rptReport.Free;
      end;
    end;
    Context.GetDialogSystem.ShowMessage('�쿨�ɹ���');
  end;
end;

procedure TfaqAnonGetCardNew.btnReadCardClick(Sender: TObject);
var
  cardNo:string;
begin
  edtAppNo.Text:='';
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
  edtAppNo.Text:=cardNo;
end;

procedure TfaqAnonGetCardNew.btnPrintClick(Sender: TObject);
begin
  rePrintOrder(sPreAppPath+'report\RtnTicket\getcard.rmp');

end;

initialization
  TUIStdClassFactory.Create('��������ȡ',TfaqAnonGetCardNew);

end.