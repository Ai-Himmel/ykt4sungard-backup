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
  WorkView.FieldByName('����Ա').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('������ȷ��').DefaultValue := '';
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
  if Context.GetDialogSystem.Confirm('�Ƿ��������øò���Ա������?') = uaNo then
        exit;
  if Trim(WVEditnewpwd2.Text)='' then
  begin
    ShowMessage('���ò���Ա���벻��Ϊ�գ�');
    Exit;
  end;
  if(WVEditnewpwd2.Text <> WVEdit1.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('����У��ʧ��');
    WVEditnewpwd2.SetFocus;
    WVEditnewpwd2.SelectAll;
  end
  else
  begin
    operCode := Copy(WVComboBox1.Text,1,Pos('-',WVComboBox1.Text)-1);
    operPwd := encOperPwd(operCode,Trim(WVEditnewpwd2.Text));
    WorkView.FieldByName('������').Data.SetString(operPwd);
    inherited;
    if Workview.FieldByName('������').data.AsInteger = 0 then
        Context.GetDialogSystem.ShowMessage('����Ա�������óɹ�');
    WVEditnewpwd2.Text := '';
    WVEdit1.Text := '';
  end
end;

initialization
  TUIStdClassFactory.Create('����Ա��������',TfaqhResetOperPwd);
end.