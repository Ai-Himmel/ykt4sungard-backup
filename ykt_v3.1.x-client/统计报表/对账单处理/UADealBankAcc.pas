unit UADealBankAcc;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhDealBankAcc = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label2: TLabel;
    edtBeginDate: TWVEdit;
    cbbOperTrans: TWVComboBox;
    lbl1: TLabel;
    lbl2: TLabel;
    edtEndDate: TWVEdit;
    lbl3: TLabel;
    cbb1: TWVComboBox;
    lbl4: TLabel;
    cbb2: TWVComboBox;
    grpResult: TGroupBox;
    Label1: TLabel;
    WVComboBox1: TWVComboBox;
    Label3: TLabel;
    edtMemo: TWVEdit;
    btnDeal: TBitBtn;
    WVDeal: TWorkView;
    WVRDeal: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDealClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhDealBankAcc: TfaqhDealBankAcc;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhDealBankAcc.Init;
begin
  inherited;
  edtBeginDate.Text := accountDate;
  edtEndDate.Text := accountDate;
end;

procedure TfaqhDealBankAcc.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhDealBankAcc.btnQueryClick(Sender: TObject);
begin
  if edtBeginDate.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('��ʼ���ڲ���Ϊ�գ�');
    edtBeginDate.SetFocus;
    Exit;
  end;
  if edtEndDate.Text='' then
  begin
    Context.GetDialogSystem.ShowMessage('�������ڲ���Ϊ�գ�');
    edtEndDate.SetFocus;
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
  //WorkView.FieldByName('������־').Data.SetString('Q');
  inherited;

end;

procedure TfaqhDealBankAcc.btnDealClick(Sender: TObject);
var
  tmpData:TDataSet;
  bankId:Integer;
  accDate:string;
begin
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
  begin
    Context.GetDialogSystem.ShowMessage('����ѡ��һ����¼��Ȼ���ٽ��д���');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ�Ը��˵����д�����',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  //tmpData := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  bankId := Grid.DataSource.DataSet.fieldbyname('lbank_acc_type').AsInteger;
  accDate := Grid.DataSource.DataSet.fieldbyname('sdate0').AsString;
  WVDeal.FieldByName('���б��').Data.SetInteger(bankId);
  WVDeal.FieldByName('�˵�����').Data.SetString(accDate);
  WVRDeal.SendCommand;
  if WVDeal.FieldByName('������').Data.AsString='0' then
    Context.GetDialogSystem.ShowMessage('������ɣ�')
  else
    Context.GetDialogSystem.ShowMessage(WVDeal.FieldByName('������Ϣ').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('���˵�����',TfaqhDealBankAcc);

end.