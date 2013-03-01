unit ksgProgress;
  
{ ***********************************************************************
  Copyright (c) 2005 �Ϻ��������˴��������޹�˾
  ��    ��: һ��ͨ�õĽ�������<Esc> �Ĳ���δ��ɣ����߳�
  ��    ��: Haifeng Zhu
  ��������: '2005-05-30'
  �޸�����:
  ��    ��: Ver 1.0
  ��    ��:
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
    FEscape: Boolean;    // �Ƿ��� <Esc> ��
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
  lblPosition.Caption := '��' + IntToStr(ProgressBar.Position) + '����¼��';
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
