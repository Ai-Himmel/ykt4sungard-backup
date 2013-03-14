unit UAqueryOperLog;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, Buttons, UIncrementComboBox,
  EditExts;

type
  TfaqhqueryOperLog = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    edtBDate: TWVEdit;
    WVComboBox6: TWVComboBox;
    WVComboBox1: TWVComboBox;
    WVComboBox2: TWVComboBox;
    WVComboBox3: TWVComboBox;
    Label7: TLabel;
    edtEDate: TWVEdit;
    edtMoney: TWVDigitalEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhqueryOperLog: TfaqhqueryOperLog;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon;
     
{$R *.DFM}

procedure TfaqhqueryOperLog.Init;
begin
  inherited;
  //currDate := FormatDateTime('yyyymmdd',Date);
  edtBDate.Text := sysDate;
  edtEDate.Text := sysDate;
end;

procedure TfaqhqueryOperLog.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhqueryOperLog.btnQueryClick(Sender: TObject);
begin
  if Trim(edtBDate.Text)<>'' then
    if (CheckInputDateFormat(edtBDate.Text)=False) then
    begin
      ShowMessage('请输入有效的开始日期！');
      Exit;
    end;
  if Trim(edtEDate.Text)<>'' then
    if (CheckInputDateFormat(edtEDate.Text)=False) then
    begin
      ShowMessage('请输入有效的结束日期！');
      Exit;
    end;
  if edtBDate.Text>edteDate.Text then
  begin
    ShowMessage('开始日期不能大于结束日期！');
    Exit;
  end;
  inherited;

end;

initialization
  TUIStdClassFactory.Create('操作日志查询',TfaqhqueryOperLog);

end.