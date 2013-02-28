unit UInputTextDlg;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UInputTextDlg
   <What>通用文字数据输入界面
   如果要求输入客户密码，同时设置了全局对象PasswordInputMethod，那么使用全局对象PasswordInputMethod提供的密码输入方法。
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ImageCtrls, ExtCtrls, UICtrls;

type
  TdlgInputText = class(TForm)
    UIPanel1: TUIPanel;
    lbPrompt: TLabel;
    edText: TEdit;
    btnOk: TImageButton;
    btnCancel: TImageButton;
    Timer: TTimer;
    procedure TimerTimer(Sender: TObject);
  private
    { Private declarations }
    FFirst: Boolean;
    FUsePasswordInputMethod: Boolean;
    procedure FirePasswordKeyboard;
    procedure edTextKeyPress(Sender: TObject; var Key: Char);
  public
    { Public declarations }
    function Execute(const ACaption, APrompt: string; HideText,
      CustomerPassword: Boolean; var Value: string; MaxLength: Integer = 0):
      Boolean;
  end;

var
  dlgInputText: TdlgInputText = nil;

function KSInputText(const ACaption, APrompt: string; HideText,
  CustomerPassword: Boolean; var Value: string; MaxLength: Integer = 0): Boolean;

implementation

{$R *.DFM}

uses KsEdits, KSClientConsts;

function KSInputText(const ACaption, APrompt: string; HideText,
  CustomerPassword: Boolean; var Value: string; MaxLength: Integer = 0): Boolean;
begin
  if dlgInputText = nil then
    dlgInputText := TdlgInputText.Create(Application);
  Result := dlgInputText.Execute(ACaption, APrompt, HideText, CustomerPassword,
    Value, MaxLength);
end;

{ TdlgInputText }

function TdlgInputText.Execute(const ACaption, APrompt: string; HideText,
  CustomerPassword: Boolean;
  var Value: string; MaxLength: Integer = 0): Boolean;
begin
  Caption := ACaption;
  lbPrompt.Caption := APrompt;
  ActiveControl := edText;
  edText.OnKeyPress := nil;
  Timer.Enabled := False;
  FFirst := True;
  FUsePasswordInputMethod := HideText and CustomerPassword and
    (PasswordInputMethod <> nil);
  if HideText then
  begin
    edText.PasswordChar := '*';
    Value := '';
    if FUsePasswordInputMethod then
    begin
      edText.ReadOnly := True;
      edText.OnKeyPress := edTextKeyPress;
      Timer.Enabled := True;
    end
    else
    begin
      edText.ReadOnly := False;
    end;
    if MaxLength = 0 then
      edText.MaxLength := MaxCustomerPasswordLength
    else
      edText.MaxLength := MaxLength;
  end
  else
  begin
    edText.PasswordChar := #0;
    edText.MaxLength := 0;
  end;
  edText.Text := Value;
  Result := ShowModal = mrOk;
  if Result then
    Value := edText.Text;
  Timer.Enabled := False;
end;

procedure TdlgInputText.FirePasswordKeyboard;
var
  AText: string;
begin
  if (PasswordInputMethod <> nil) then
  begin
    btnOk.Enabled := False;
    btnCancel.Enabled := False;
    AText := '';
    try
      Update; // 先更新屏幕显示
      if PasswordInputMethod.InputPassword(MaxCustomerPasswordLength, AText)
        then
      begin
        edText.Text := AText;
        //ModalResult := mrOk;
      end;
    finally
      btnOk.Enabled := True;
      btnCancel.Enabled := True;
    end;
  end;
end;

procedure TdlgInputText.edTextKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key = ' ') and (PasswordInputMethod <> nil) then
  begin
    Key := #0;
    FirePasswordKeyboard;
  end;
end;

procedure TdlgInputText.TimerTimer(Sender: TObject);
begin
  Timer.Enabled := False;
  if FUsePasswordInputMethod then
    FirePasswordKeyboard;
end;

end.
