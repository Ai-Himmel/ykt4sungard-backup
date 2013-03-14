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
      Context.GetDialogSystem.ShowMessage('统计日期输入不正确，格式：yyyymmdd');
      edtStatDate.SetFocus;
      Exit;
    end;
  if Trim(edtBalanceDate.Text)<>'' then
    if CheckInputDateFormat(edtBalanceDate.Text)=False then
    begin
      Context.GetDialogSystem.ShowMessage('处理日期输入不正确，格式：yyyymmdd');
      edtBalanceDate.SetFocus;
      Exit;
    end;

  inherited;
  if WorkView.FieldByName('查询结果集').Data.IsEmpty then
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
    Context.GetDialogSystem.ShowMessage('请选择平帐方式！');
    Exit;
  end;
  try
    statDate := Grid.DataSource.DataSet.fieldbyname('sdate1').AsString;
    cardNo := grid.DataSource.DataSet.fieldbyname('lvol0').AsInteger;
  except
    Context.GetDialogSystem.ShowMessage('请先查询并选择一条要平帐处理的记录！');
    Exit;
  end;
  if Application.MessageBox('你确定要处理该条卡库不平记录吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;

  WorkView1.FieldByName('统计日期').Data.SetString(statDate);
  WorkView1.FieldByName('卡号').Data.SetInteger(cardNo);
  WVRequest1.SendCommand;
  rInfo := WorkView1.fieldbyname('返回信息').Data.AsString;
  if WorkView1.FieldByName('返回码').Data.AsInteger<>0 then
    Context.GetDialogSystem.ShowMessage(rInfo)
  else
    Context.GetDialogSystem.ShowMessage('处理成功--'+rinfo);
  btnQueryClick(Sender);
end;

initialization
  TUIStdClassFactory.Create('卡库不平处理',TfaqhcardLibNotBalance);

end.