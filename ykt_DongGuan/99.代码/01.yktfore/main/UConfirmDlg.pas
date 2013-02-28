unit UConfirmDlg;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UConfirmDlg
   <What>�����ȷ�϶Ի���
   <Written By> Huang YanLai (������)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, UICtrls;

type
  TdlgConfirm = class(TForm)
    pnText: TUIPanel;
    lbContent: TLabel;
    lbYesNo: TUILabel;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
    function Execute(const Msg: string): Boolean;
  end;

var
  dlgConfirm: TdlgConfirm;

function SpecialConfirm(const Msg: string): Boolean;

implementation

{$R *.DFM}

function SpecialConfirm(const Msg: string): Boolean;
var
  Dialog: TdlgConfirm;
begin
  Dialog := TdlgConfirm.Create(Application);
  try
    Result := Dialog.Execute(Msg);
  finally
    Dialog.Free;
  end;
end;

{ TdlgConfirm }

function TdlgConfirm.Execute(const Msg: string): Boolean;
const
  Margin = 12;
var
  ALabelWidth: Integer;
  AHeight: Integer;
  ALabelHeight: Integer;
  Delta: Integer;

  function GetTextHeight(AWidth: Integer): Integer;
  var
    ARect: TRect;
    Flags: LongWord;
  begin
    ARect := Rect(0, 0, AWidth, 0);
    Flags := DT_EXPANDTABS or DT_CALCRECT or DT_WORDBREAK or DT_NOPREFIX;
    DrawText(Canvas.Handle, PChar(Msg), Length(Msg), ARect, Flags);
    Result := ARect.Bottom;
  end;

begin
  // �����С���ָ߶�
  Canvas.Font := lbContent.Font;
  ALabelWidth := ClientWidth - 2 * pnText.BorderWidth - 2;
  ALabelHeight := GetTextHeight(ALabelWidth);

  lbContent.Width := ALabelWidth;
  lbContent.Caption := Msg;

  // ����Form��С
  Delta := Height - ClientHeight;
  AHeight := ALabelHeight + lbYesNo.Height + Delta + Margin + pnText.BorderWidth
    * 2;
  SetBounds(Left, Top, Width, AHeight);
  lbContent.Left := (ALabelWidth - lbContent.Width) div 2 + pnText.BorderWidth;
  lbContent.Top := (ALabelHeight - lbContent.Height) div 2 + pnText.BorderWidth;
  Result := ShowModal = mrYes;
end;

procedure TdlgConfirm.FormKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key = 'Y') or (Key = 'y') then
    ModalResult := mrYes
  else if (Key = 'N') or (Key = 'n') then
    ModalResult := mrNo;
end;

end.
