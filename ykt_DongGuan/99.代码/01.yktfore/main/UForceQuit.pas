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
    WriteLog(Format('ϵͳ�ӵ�ǿ��¼��ָ�%s����', [Msg]), lcException);
  finally
    Free;
  end;
end;

procedure TfmForceQuit.FormCreate(Sender: TObject);
begin
  FHoldSecs := DefaultHoldSecs;
  with lblShine do
  begin
    Caption := Format('ϵͳ�Ѿ��յ�ǿ��¼��ָ�����%d�����Զ��رգ�',
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
    Caption := Format('ϵͳ�Ѿ��յ�ǿ��¼��ָ�����%d�����Զ��رգ�',
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
        tempSL[1] := '��';
      Memo.Lines[0] :=
        Format('        ����Ա%s��ϵͳ�����ǿ��¼�����㣬ԭ��(%s)���������ʣ�����֮��ϵ��'
        , [tempSL[0], tempSL[1]]);
    end
    else
      Memo.Lines[0] :=
        Format('        ����Ա��ϵͳ�����ǿ��¼�����㣬ԭ��(%s)���������ʣ�����֮��ϵ��'
        , [tempSL[0]]);

  finally
    tempSL.Free;
  end;
end;

end.
