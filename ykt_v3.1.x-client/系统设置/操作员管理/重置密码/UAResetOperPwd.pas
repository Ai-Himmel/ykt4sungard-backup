unit UAResetOperPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVCtrls, ComCtrls, Mask, WVCmdProc, KCWVProcBinds, WVCmdTypeInfo,
  EditExts, DB, WVDBBinders, Grids,CardDll,
  USetParamsTemp, UIncrementComboBox, Buttons, RzStatus;


type
  TfaqhResetOperPwd = class(TfaqhInputTemp)
    Panel2: TPanel;
    GroupBox1: TGroupBox;
    RzStatusPane1: TRzStatusPane;
    WVComboBox1: TWVComboBox;
    RzStatusPane2: TRzStatusPane;
    WVEditnewpwd2: TWVEdit;
    RzStatusPane3: TRzStatusPane;
    WVEdit1: TWVEdit;
    procedure btnOKClick(Sender: TObject);
    private
    { Private declarations }
    protected
    { protected declarations }
    procedure Init; override;
  public
    { Public declarations }
  end;

var
  faqhResetOperPwd: TfaqhResetOperPwd;

implementation

uses LogFile,KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts, KSDataDictionary;
{$R *.DFM}

procedure TfaqhResetOperPwd.Init;
begin
  inherited;
  {
  WorkView.FieldByName('操作员').DefaultValue := '';
  WorkView.FieldByName('新密码').DefaultValue := '';
  WorkView.FieldByName('新密码确认').DefaultValue := '';
  WorkView.Reset;
  }
  {
  FreeIdObjects(-30);
  WVComboBox1.ItemsDataEntry := '';
  WVComboBox1.ItemsDataEntry := '-30';
  }
end;

procedure TfaqhResetOperPwd.btnOKClick(Sender: TObject);
var
  operCode:string;
  operPwd:string;
begin
  if Context.GetDialogSystem.Confirm('是否重新设置该操作员的密码?') = uaNo then
        exit;
  if Trim(WVEditnewpwd2.Text)='' then
  begin
    ShowMessage('重置操作员密码不能为空！');
    Exit;
  end;
  if(WVEditnewpwd2.Text <> WVEdit1.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('密码校验失败');
    WVEditnewpwd2.SetFocus;
    WVEditnewpwd2.SelectAll;
  end
  else
  begin
    operCode := Copy(WVComboBox1.Text,1,Pos('-',WVComboBox1.Text)-1);
    operPwd := encOperPwd(operCode,Trim(WVEditnewpwd2.Text));
    WorkView.FieldByName('新密码').Data.SetString(operPwd);
    inherited;
    if Workview.FieldByName('返回码').data.AsInteger = 0 then
        Context.GetDialogSystem.ShowMessage('操作员密码重置成功');
    WVEditnewpwd2.Text := '';
    WVEdit1.Text := '';
  end
end;

initialization
  TUIStdClassFactory.Create('操作员密码重置',TfaqhResetOperPwd);
end.