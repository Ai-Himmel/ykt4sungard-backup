unit UAcardLibNotBalance;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox;

type
  TfaqhcardLibNotBalance = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    edtCardNo: TWVEdit;
    edtCustNo: TWVEdit;
    edtValue: TWVEdit;
    edtStatDate: TWVEdit;
    edtBalanceDate: TWVEdit;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label9: TLabel;
    cbbBalanceType: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    btnBalance: TBitBtn;
    Label10: TLabel;
    WVComboBox4: TWVComboBox;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnBalanceClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhcardLibNotBalance: TfaqhcardLibNotBalance;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhcardLibNotBalance.Init;
begin
  inherited;
end;

procedure TfaqhcardLibNotBalance.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhcardLibNotBalance.btnQueryClick(Sender: TObject);
begin
  if Trim(edtCardNo.Text)='' then
    edtCardNo.Text := '0';
  if Trim(edtCustNo.Text)='' then
    edtCustNo.Text := '0';
  if Trim(edtValue.Text)='' then
    edtValue.Text := '0';

  if Trim(edtStatDate.Text)<>'' then
    if CheckInputDateFormat(edtStatDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('ͳ���������벻��ȷ����ʽ��yyyymmdd');
      edtStatDate.SetFocus;
      Exit;
    end;
  if Trim(edtBalanceDate.Text)<>'' then
    if CheckInputDateFormat(edtBalanceDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('�����������벻��ȷ����ʽ��yyyymmdd');
      edtBalanceDate.SetFocus;
      Exit;
    end;

  inherited;
  if WorkView.FieldByName('��ѯ�����').Data.IsEmpty then
    btnBalance.Enabled := False
  else
    btnBalance.Enabled := True;
end;

procedure TfaqhcardLibNotBalance.btnBalanceClick(Sender: TObject);
var
  bType:string;
  statDate:string;
  cardNo:Integer;
  rInfo:string;
begin
  //inherited;
  bType := Copy(cbbBalanceType.Text,1,Pos('-',cbbBalanceType.Text)-1);
  if (bType='') or (bType='-') then
  begin
    Context.GetDialogSystem.ShowMessage('��ѡ��ƽ�ʷ�ʽ��');
    Exit;
  end;
  try
    statDate := Grid.DataSource.DataSet.fieldbyname('sdate1').AsString;
    cardNo := grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('���Ȳ�ѯ��ѡ��һ��Ҫƽ�ʴ���ļ�¼��');
    Exit;
  end;
  if Application.MessageBox('��ȷ��Ҫ����������ⲻƽ��¼��',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;

  WorkView1.FieldByName('ͳ������').Data.SetString(statDate);
  WorkView1.FieldByName('����').Data.SetInteger(cardNo);
  WVRequest1.SendCommand;
  rInfo := WorkView1.fieldbyname('������Ϣ').Data.AsString;
  if WorkView1.FieldByName('������').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(rInfo)
  else
    Context.GetDialogSystem.ShowMessage('����ɹ�--'+rinfo);
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('���ⲻƽ����',TfaqhcardLibNotBalance);

end.