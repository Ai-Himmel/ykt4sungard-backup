unit UAreConsumeBalance;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, UIncrementComboBox, Buttons;

type
  TfaqhreConsumeBalance = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    edtOperCode: TWVEdit;
    Label2: TLabel;
    WVEdit2: TWVEdit;
    Label13: TLabel;
    WVComboBox1: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
  private

    { Private declarations }
    sOperCode : string;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhreConsumeBalance: TfaqhreConsumeBalance;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhreConsumeBalance.Init;
begin
  inherited;
  {
  WorkView1.FieldByName('采集开始日期').DefaultValue := '';
  WorkView1.FieldByName('采集开始时间').DefaultValue := '';
  WorkView1.FieldByName('采集结束日期').DefaultValue := '';
  WorkView1.FieldByName('采集结束时间').DefaultValue := '';
  WorkView1.FieldByName('流水号').DefaultValue := 0;
  WorkView1.FieldByName('上传端流水号').DefaultValue := 0;
  WorkView1.FieldByName('交易代码').DefaultValue := 0;
  WorkView1.FieldByName('流水状态').DefaultValue := 0;
  WorkView1.FieldByName('上传工作站标识').DefaultValue := 0;
  WorkView1.FieldByName('交易发生设备标识').DefaultValue := 0;
  WorkView1.FieldByName('交易卡号').DefaultValue := 0;
  WorkView1.FieldByName('客户标识').DefaultValue := 0;
  WorkView.FieldByName('操作员号').DefaultValue := '';
  WorkView.FieldByName('密码').DefaultValue := '';
  WorkView.FieldByName('交易流水号').DefaultValue := 0;
  WorkView.Reset;
  }
  btnPrint.Caption := '结算冲正';
  sOperCode := Context.ParamData(svOperatorNoName).AsString;
  edtOperCode.Text := sOperCode;
end;

procedure TfaqhreConsumeBalance.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhreConsumeBalance.btnQueryClick(Sender: TObject);
var
  sDate:string;
begin
  sDate := FormatDateTime('yyyymmdd',Date);
  WorkView1.FieldByName('采集开始日期').Data.SetString(sDate);
  WorkView1.FieldByName('采集结束日期').Data.SetString(sDate);
  WorkView1.FieldByName('交易代码').Data.SetInteger(847222);
  WorkView1.FieldByName('流水号').Data.SetInteger(0);
  WorkView1.FieldByName('上传端流水号').Data.SetInteger(0);
  WorkView1.FieldByName('流水状态').Data.SetInteger(0);
  WorkView1.FieldByName('上传工作站标识').Data.SetInteger(0);
  WorkView1.FieldByName('交易发生设备标识').Data.SetInteger(0);
  WorkView1.FieldByName('交易卡号').Data.SetInteger(0);
  WorkView1.FieldByName('客户标识').Data.SetInteger(0);
  //inherited;
  WVRequest1.SendCommand;
end;

procedure TfaqhreConsumeBalance.btnPrintClick(Sender: TObject);
var
  serialNo:Integer;
begin
  if Application.MessageBox('你确定要进行消费结算冲正操作吗？',PChar(Application.Title),MB_ICONQUESTION+mb_yesno)=idno then
    Exit;
  if TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject).IsEmpty then
  begin
    ShowMessage('没有要冲正的交易！');
    Exit;
  end;
  serialNo := TDataSet(WorkView1.FieldByName('查询结果集').Data.AsObject).fieldbyname('lvol0').AsInteger;
  WorkView.FieldByName('交易流水号').Data.SetInteger(serialNo);
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
    ShowMessage(WorkView.FieldByName('返回信息').Data.AsString);
end;

initialization
  TUIStdClassFactory.Create('消费结算冲正',TfaqhreConsumeBalance);

end.