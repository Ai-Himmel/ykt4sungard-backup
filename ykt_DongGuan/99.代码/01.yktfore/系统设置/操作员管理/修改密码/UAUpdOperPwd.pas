unit UAUpdOperPwd;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhInputTemp, WVCmdReq, WorkViews, StdCtrls, ImageCtrls, ExtCtrls, UICtrls,
  WVCtrls, Mask, WVCommands, CheckLst,DataTypes,UIncrementComboBox, Buttons,
  RzStatus,CardDll;

type
  TfaqhUpdOperPwd = class(TfaqhInputTemp)
    Panel1: TPanel;
    grp1: TGroupBox;
    WVEditpwd2: TWVEdit;
    WVEditnewpwd3: TWVEdit;
    WVEdit1: TWVEdit;
    RzStatusPane1: TRzStatusPane;
    RzStatusPane2: TRzStatusPane;
    RzStatusPane3: TRzStatusPane;
    RzStatusPane4: TRzStatusPane;
    edtOper: TEdit;
    procedure btnOKClick(Sender: TObject);
    procedure MainRequestAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    private
    { Private declarations }
    protected
    { protected declarations }
    procedure Init; override;
  public
    { Public declarations }
  end;

var
  faqhUpdOperPwd: TfaqhUpdOperPwd;

implementation

uses KsFrameworks, KSFrameWorkUtils, 
     KSClientConsts,  
    {UMenu,}
  KSFrames, SmartCardCommon;

{$R *.DFM}

procedure TfaqhUpdOperPwd.Init;
begin
  inherited;

  WorkView.FieldByName('����Ա����').DefaultValue := context.GetParamValue(svOperatorNoName);
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('������').DefaultValue := '';
  WorkView.FieldByName('������ȷ��').DefaultValue := '';
  WorkView.Reset;
  edtOper.Text := context.GetParamValue(svOperatorNoName);
end;

procedure TfaqhUpdOperPwd.btnOKClick(Sender: TObject);
var
  operCode:string;
  newOperPwd:string;
  operPwd:string;
begin
  if(WVEditnewpwd3.Text <> WVEdit1.Text) then
  begin
    Context.GetDialogSystem.ShowMessage('������������벻һ��');
    WVEditnewpwd3.SetFocus;
    WVEditnewpwd3.SelectAll;
    Exit;
  end;
  if Trim(WVEditnewpwd3.Text)='' then
  begin
    Context.GetDialogSystem.ShowMessage('������ʹ�ÿ����룡');
    WVEditnewpwd3.SetFocus;
    WVEditnewpwd3.SelectAll;
    Exit;
  end;
  if Length(Trim(WVEditnewpwd3.Text))>8 then
  begin
    Context.GetDialogSystem.ShowMessage('�����ð�λ���ȵ����룡');
    WVEditnewpwd3.SetFocus;
    WVEditnewpwd3.SelectAll;
    Exit;
  end;
 if not CheckCodeValid(Trim(WVEditnewpwd3.Text)) then
  begin
    Context.GetDialogSystem.ShowMessage('������������֡�Ӣ����ĸ���Լ� "-","_"��ɣ�');
    WVEditnewpwd3.SetFocus;
    WVEditnewpwd3.SelectAll;
    Exit;
  end;
  operCode := Trim(edtOper.Text);
  operPwd := encOperPwd(operCode,Trim(WVEditpwd2.Text));
  newOperPwd := encOperPwd(operCode,Trim(WVEditnewpwd3.Text));
  WorkView.FieldByName('������').Data.SetString(newOperPwd);
  WorkView.FieldByName('������').Data.SetString(OperPwd);
  inherited;
  if Workview.FieldByName('������').data.AsInteger = 0 then
    Context.GetDialogSystem.ShowMessage('����Ա��'+edtoper.Text+'�������޸ĳɹ���')
  else
    Context.GetDialogSystem.ShowWarning('����Ա��'+edtoper.Text+'�������޸�ʧ�ܣ�');
  WVEditpwd2.Text := '';
  WVEditnewpwd3.Text := '';
  WVEdit1.Text := '';
end;

procedure TfaqhUpdOperPwd.MainRequestAfterExec(Request: TWVRequest;
  Command: TWVCommand);
var
  Error : ECommandError;
  ReturnCode : Integer;
  DataObj : TKSDataObject;
  ErrorMsg : string;
begin
  if Command.Error<>nil then
    FreeDataSetForCommand(Command);
  Command.CheckError;
  DataObj := Command.FindParamData(cpReturnCodeParamName);
  if DataObj<>nil then
  begin
    ReturnCode := DataObj.AsInteger;
    if ReturnCode<>0 then
    begin
      FreeDataSetForCommand(Command);
      DataObj := Command.FindParamData(cpReturnMessageParamName);
      if DataObj<>nil then
        ErrorMsg := DataObj.AsString else
        ErrorMsg := '';
      if (0<=ReturnCode) and (ReturnCode<=WarningReturnCode) then
      begin
        if true and (ReturnCode<>1) then
          Context.GetDialogSystem.ShowWarning(Format('���� : %d, %s',[ReturnCode,ErrorMsg]));
      end else
      begin
        ErrorMsg := '�����벻��ȷ';
        Error := ECommandError.Create(ErrorMsg);
//       Error.FReturnCode := ReturnCode;
        raise Error;
      end;
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('����Ա�����޸�',TfaqhUpdOperPwd);
end.