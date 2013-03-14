unit UAinAccountByMan;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, RzStatus, UIncrementComboBox,
  Buttons,CardDll, sncCurrency;

type
  TfaqhinAccountByMan = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    edtJNo: TWVEdit;
    edtDNO: TWVEdit;
    edtpass: TWVEdit;
    Label4: TLabel;
    edtJName: TWVEdit;
    Label9: TLabel;
    edtDName: TWVEdit;
    RzStatusPane1: TRzStatusPane;
    cbbErrOperNo: TWVComboBox;
    WorkView1: TWorkView;
    WVRequest1: TWVRequest;
    edtMoney: TsncCurrencyEdit;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure edtJNoExit(Sender: TObject);
    procedure edtDNOExit(Sender: TObject);
  private

    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhinAccountByMan: TfaqhinAccountByMan;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils;
     
{$R *.DFM}

procedure TfaqhinAccountByMan.Init;
begin
  inherited;
  {
  WorkView.FieldByName('借方账号').DefaultValue := '';
  WorkView.FieldByName('贷方账号').DefaultValue := '';
  WorkView.FieldByName('发生金额').DefaultValue := 0.00;
  WorkView.FieldByName('工作站号').DefaultValue := 0;
  WorkView.FieldByName('操作员号').DefaultValue := '';
  WorkView.FieldByName('错账操作员号').DefaultValue := '';
  WorkView.FieldByName('错账操作员密码').DefaultValue := '';
  WorkView.Reset;
  }
  btnQuery.Caption:='&O 确定';
  cbbErrOperNo.ItemIndex:=0;
end;

procedure TfaqhinAccountByMan.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  //btnQuery.Enabled:=Valid;
end;



procedure TfaqhinAccountByMan.btnQueryClick(Sender: TObject);
var
  OperatorID:string;
  operCode:string;
  operPwd:string;

begin
  if trim(edtJNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('借方账号不能为空，请输入！');
    //edtJNo.SetFocus;
    Exit;
  end;
  if trim(edtDNO.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('贷方账号不能为空，请输入！');
    //edtDNO.SetFocus;
    Exit;
  end;
  if edtMoney.Value=0 then
  begin
    Context.GetDialogSystem.ShowMessage('发生金额不能为零，请输入！');
    //edtMoney.SetFocus;
    Exit;
  end;
  OperatorID := Context.ParamData(svOperatorNoName).AsString;
  operCode := Copy(cbbErrOperNo.Text,1,Pos('-',cbbErrOperNo.Text)-1);
  operPwd := encOperPwd(operCode,Trim(edtpass.Text));
  WorkView.FieldByName('错账操作员密码').Data.SetString(operPwd);
  WorkView.FieldByName('工作站号').Data.SetInteger(SmartCardSubSystemNo);
  WorkView.FieldByName('发生金额').Data.setfloat(edtMoney.Value);
  WorkView.FieldByName('操作员号').Data.SetString(OperatorID);
  //inherited;
  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger=0 then
  begin
    ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    edtpass.Text:='';
    cbbErrOperNo.ItemIndex:=0;
  end;
end;

procedure TfaqhinAccountByMan.edtJNoExit(Sender: TObject);
begin
  inherited;
  if Trim(edtJNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('借方账号不能为空，请输入！');
    //edtJNo.SetFocus;
    Exit;
  end;
  WorkView1.FieldByName('账号').Data.SetString(edtJNo.Text);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    edtJName.Text:=WorkView1.fieldbyname('名称').Data.AsString
  else
    RzStatusPane1.Caption:=WorkView1.fieldbyname('返回信息').Data.AsString;
end;

procedure TfaqhinAccountByMan.edtDNOExit(Sender: TObject);
begin
  inherited;
  if Trim(edtDNo.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('贷方账号不能为空，请输入！');
    //edtDNo.SetFocus;
    Exit;
  end;
  WorkView1.FieldByName('账号').Data.SetString(edtDNo.Text);
  WVRequest1.SendCommand;
  if WorkView1.FieldByName('返回码').Data.AsInteger=0 then
    edtDName.Text:=WorkView1.fieldbyname('名称').Data.AsString
  else
    RzStatusPane1.Caption:=WorkView1.fieldbyname('返回信息').Data.AsString;

end;

initialization
  TUIStdClassFactory.Create('科目帐务手工调整',TfaqhinAccountByMan);

end.