unit UForceQuit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Buttons;

type
  TfmForceQuit = class(TForm)
    Timer: TTimer;
    lblShine: TLabel;
    btnOK: TBitBtn;
    Memo: TMemo;
    procedure FormCreate(Sender: TObject);
    procedure TimerTimer(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
  private
    { Private declarations }
    FHoldSecs: Integer;
  public
    { Public declarations }
    constructor Create(Msg: string); reintroduce;
  end;

procedure ForceSystemQuit(Msg: string);

implementation

uses
  LogFile;

const
  DefaultHoldSecs = 10;
  DefaultBgColor = clYellow;
  DefaultFontColor = clRed;

{$R *.DFM}

procedure ForceSystemQuit(Msg: string);
begin
  SendMessage(Application.Handle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
  SendMessage(Application.Handle, WM_SYSCOMMAND, SC_RESTORE, 0);
  with TfmForceQuit.Create(Msg) do
  try
    ShowModal;
    WriteLog(Format('系统接到强制录出指令（%s）！', [Msg]), lcException);
  finally
    Free;
  end;
end;

procedure TfmForceQuit.FormCreate(Sender: TObject);
begin
  FHoldSecs := DefaultHoldSecs;
  with lblShine do
  begin
    Caption := Format('系统已经收到强制录出指令，将在%d秒内自动关闭！',
      [FHoldSecs]);
    Self.Caption := Caption;
    Color := DefaultBgColor;
    Font.Color := DefaultFontColor;
    btnOK.Font.Color := Font.Color;
  end;

  Timer.Enabled := True;
end;

procedure TfmForceQuit.TimerTimer(Sender: TObject);
begin
  Beep;
  if FHoldSecs = 1 then
    btnOK.Click
  else
    Dec(FHoldSecs);
  with lblShine do
  begin
    Caption := Format('系统已经收到强制录出指令，将在%d秒内自动关闭！',
      [FHoldSecs]);
    Self.Caption := Caption;
    if Color = DefaultBgColor then
    begin
      Color := DefaultFontColor;
      Font.Color := DefaultBgColor;
      btnOK.Font.Color := Font.Color;
    end
    else
    begin
      Color := DefaultBgColor;
      Font.Color := DefaultFontColor;
      btnOK.Font.Color := Font.Color;
    end;
  end;
end;

procedure TfmForceQuit.btnOKClick(Sender: TObject);
begin
  ModalResult := mrOK;
  //  Self.Free;
end;

constructor TfmForceQuit.Create(Msg: string);
var
  tempSL: TStringList;
begin
  inherited Create(Application);
  tempSL := TStringList.Create;
  try
    tempSL.CommaText := Msg;
    Memo.Lines.Add('');
    if tempSL.Count = 2 then
    begin
      if tempSL[1] = '' then
        tempSL[1] := '无';
      Memo.Lines[0] :=
        Format('        操作员%s在系统监控中强制录出了你，原因(%s)。如有疑问，请与之联系！'
        , [tempSL[0], tempSL[1]]);
    end
    else
      Memo.Lines[0] :=
        Format('        操作员在系统监控中强制录出了你，原因(%s)。如有疑问，请与之联系！'
        , [tempSL[0]]);

  finally
    tempSL.Free;
  end;
end;

end.
