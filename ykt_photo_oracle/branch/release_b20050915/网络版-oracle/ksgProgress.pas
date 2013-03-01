unit ksgProgress;
  
{ ***********************************************************************
  Copyright (c) 2005 上海复旦金仕达计算机有限公司
  描    述: 一个通用的进度条。<Esc> 的捕获未完成，多线程
  作    者: Haifeng Zhu
  创建日期: '2005-05-30'
  修改日期:
  版    本: Ver 1.0
  改    进:
  ************************************************************************ }

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls;

type
  TfrmProgress = class(TForm)
    pnlBoard: TPanel;
    ProgressBar: TProgressBar;
    Label1: TLabel;
    lblTitle: TLabel;
    lblPosition: TLabel;
    procedure FormShortCut(var Msg: TWMKey; var Handled: Boolean);
  private
    { Private declarations }
    FEscape: Boolean;    // 是否按了 <Esc> 键
  public
    { Public declarations }
    procedure BeginHandle(Title: string; Min, Max: Integer);
    procedure Progress;
    procedure EndHandle;

    property Escape: Boolean read FEscape;
  end;

var
  frmProgress: TfrmProgress;

implementation

{$R *.DFM}

{ TfrmProgress }

procedure TfrmProgress.BeginHandle(Title: string; Min, Max: Integer);
begin
  FEscape := False;
  lblTitle.Caption := Title;
  ProgressBar.Min := Min;
  ProgressBar.Max := Max;
  ProgressBar.Position := Min;
  Self.Show;
  Screen.Cursor := crHourGlass;
  Refresh;
end;

procedure TfrmProgress.EndHandle;
begin
  Close;
  Screen.Cursor := crDefault;
end;

procedure TfrmProgress.Progress;
begin
  ProgressBar.Position := ProgressBar.Position + 1;
  lblPosition.Caption := '第' + IntToStr(ProgressBar.Position) + '条记录。';
  Refresh;
end;

procedure TfrmProgress.FormShortCut(var Msg: TWMKey; var Handled: Boolean);
begin
  if Msg.CharCode = 27 then
  begin
    FEscape := True;
    EndHandle;
  end; 
end;

end.
