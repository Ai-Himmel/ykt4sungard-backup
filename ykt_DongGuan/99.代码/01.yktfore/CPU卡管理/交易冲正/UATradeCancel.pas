unit UATradeCancel;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,CardDll,
  RzStatus;

type
  TfaqhTradeCancel = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtBeginDate: TWVEdit;
    edtEndDate: TWVEdit;
    edtCustName: TWVEdit;
    WVEdit4: TWVEdit;
    WVEdit6: TWVEdit;
    WVEdit8: TWVEdit;
    WVEdit10: TWVEdit;
    WVEdit11: TWVEdit;
    WVComboBox1: TWVComboBox;
    cbbDept: TWVComboBox;
    WVComboBox2: TWVComboBox;
    Label9: TLabel;
    edtAppSerialNo: TWVEdit;
    btnReadCard: TBitBtn;
    WVRTradeCancel: TWVRequest;
    WVTradeCancel: TWorkView;
    RzStatusPane2: TRzStatusPane;
    Label13: TLabel;
    WVComboBox3: TWVComboBox;
    WVComboBox4: TWVComboBox;
    Label14: TLabel;
    procedure btnQueryClick(Sender: TObject);
    procedure btnReadCardClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhTradeCancel: TfaqhTradeCancel;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhTradeCancel.Init;
begin
  inherited;
  edtBeginDate.Text := sysDate;
  edtEndDate.Text := sysDate;
end;

procedure TfaqhTradeCancel.btnQueryClick(Sender: TObject);
begin
  if (Trim(edtBeginDate.Text)='') or (Trim(edtEndDate.Text)='') then
  begin
    Context.GetDialogSystem.ShowMessage('�����뿪ʼ���ںͽ������ڣ�');
    Exit;
  end;
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
      Context.GetDialogSystem.ShowMessage('��ʼ���ڲ��ܴ��ڽ������ڣ�');
  if Trim(edtCustName.Text)='' then
    edtCustName.Text := '0';
  inherited;

end;

procedure TfaqhTradeCancel.btnReadCardClick(Sender: TObject);
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

procedure TfaqhTradeCancel.btnPrintClick(Sender: TObject);
var
  sDate,sTime:string;
  accDate,sNo:string;
  tOperId:Integer;
  tMoney:Double;
begin
  if psamTermId='' then
  begin
    Context.GetDialogSystem.ShowMessage('���ȴ򿪴��ڣ�����PSAM������');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����ѡ�еĽ�����',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=Idno then
    Exit;
  try
    accDate := Grid.DataSource.DataSet.fieldbyname('sdate3').AsString;
    sNo := Grid.DataSource.DataSet.fieldbyname('scert_no').AsString;
    tOperId := Grid.DataSource.DataSet.fieldbyname('semp').AsInteger;
    tMoney := Grid.DataSource.DataSet.fieldbyname('damt2').AsFloat;
  except
    on e:Exception do
    begin
      Context.GetDialogSystem.ShowMessage('�ֶδ���-'+e.Message);
      Exit;
    end;
  end;
  sDate := FormatDateTime('yyyymmdd',Date);
  sTime := FormatDateTime('hhmmss',Now);
  WVTradeCancel.FieldByName('��������').Data.SetString(sDate);
  WVTradeCancel.FieldByName('����ʱ��').Data.SetString(sTime);
  WVTradeCancel.FieldByName('sam�ն˺�').Data.SetString(psamTermId);
  WVTradeCancel.FieldByName('��������').Data.SetString(accDate);
  WVTradeCancel.FieldByName('���ײο���').Data.SetString(sNo);
  WVTradeCancel.FieldByName('��������Ա').Data.SetInteger(tOperId);
  WVTradeCancel.FieldByName('�������').Data.SetFloat(tMoney);
  WVRTradeCancel.SendCommand;
  Context.GetDialogSystem.ShowMessage(WVTradeCancel.fieldbyname('������Ϣ').Data.AsString);
  RzStatusPane2.Caption := WVTradeCancel.fieldbyname('������Ϣ').Data.AsString;
end;

initialization
  TUIStdClassFactory.Create('���׳���',TfaqhTradeCancel);

end.