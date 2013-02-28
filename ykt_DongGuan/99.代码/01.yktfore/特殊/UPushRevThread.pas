unit UPushRevThread;

interface

uses
  Classes, Windows, KCDataPack;

type
  PTSTPack = KCDataPack.PSTPack;
  TRecievePushData = procedure(RequestType: LongWord; PBody: PTSTPack) of
    object;
  TPushRevThread = class(TThread)
  private
    { Private declarations }
    FRequestType: LongWord;
    FnBatch: Integer;
    FstrDrtpAddr: string;
    FnDrtpPort: Integer;
    FnMainFunc: Integer;

    procedure GetData;
    procedure ShowError;
    procedure CheckRtnValue(RtnCode: Integer);
  protected
    procedure Execute; override;

    procedure UpdateHQ;
  public
    Buffer: array[0..SizeOf(TSTDataHead) + SizeOf(TSTPack) - 1] of Byte;
    procedure Open;
    procedure Close;

    constructor Create(nBatch: Integer;
      strDrtpAddr: string;
      nDrtpPort: Integer;
      nMainFunc: Integer);
  end;

implementation

uses
  KSRECVPUSH, Sysutils, LogFile, KSClientConsts,
{$IFDEF MANAGESYS}
  UMain;
{$ENDIF}
{$IFDEF KSMONCLIENT}
UMonClientDataSet;
{$ENDIF}
{$IFDEF KSTRADER}
UMainPop;
{$ENDIF}
{$IFDEF KSRISK}
UMainPop;
{$ENDIF}
{$IFDEF KSREPORT}
UMainPop;
{$ENDIF}

{ TPushRevThread }

procedure TPushRevThread.CheckRtnValue(RtnCode: Integer);
begin
  if RtnCode = -1 then
    ShowError;
end;

procedure TPushRevThread.Close;
begin
  if not Terminated then
    Terminate;
  WaitFor;
  CheckRtnValue(RecvPush_Stop);
  CheckRtnValue(RecvPush_Uninitialize);
  WriteLog('RevPushThread have closed!', lcKSClientStart);
end;

constructor TPushRevThread.Create(nBatch: Integer; strDrtpAddr: string;
  nDrtpPort, nMainFunc: Integer);
begin
  inherited Create(True);

  FnBatch := nBatch;
  FstrDrtpAddr := strDrtpAddr;
  FnDrtpPort := nDrtpPort;
  FnMainFunc := nMainFunc;

  WriteLog('RevPushThread have created!', lcKSClientStart);
  WriteLog(Format('FnBatch=%d;FstrDrtpAddr=%s;FnDrtpPort:=%d;FnMainFunc:=%d;',
    [FnBatch, FstrDrtpAddr, FnDrtpPort, FnMainFunc]),
    lcKSClientStart);
end;

procedure TPushRevThread.Execute;
begin
  { Place thread code here }
  while not Terminated do
  begin
    GetData;
  end;
end;

procedure TPushRevThread.GetData;
var
  PBuffer: PByte;
  RtnCode: Integer;
begin
  try
    FillChar(buffer, SizeOf(buffer), 0);
    PBuffer := @Buffer;
    RtnCode := RecvPush_RecvPushPack(PChar(PBuffer), SizeOf(Buffer), 200);
    CheckRtnValue(RtnCode);
    if RtnCode > 0 then
    begin
      Move(Buffer, FRequestType, SizeOf(FRequestType));
{$IFDEF Debug}
      WriteLog(Format('RecvPush_RecvPushPack has Rev a Data(RequestType:%d)',
        [FRequestType]), lcDebug);
{$ENDIF}
{$IFDEF KSMONCLIENT}
      UMonClientDataSet.RecievePushData(FRequestType,
        PTSTPack(PByte(Integer(PBuffer) + SizeOf(TSTDataHead))));
      Exit;
{$ENDIF}
      Synchronize(UpdateHQ);
    end;
  except
    on E: Exception do
    begin
      WriteLog(Format('TPushRevThread Raise Error:%s', [E.Message]),
        lcException);
    end;
  end;
end;

procedure TPushRevThread.Open;
begin
  try
    CheckRtnValue(RecvPush_Initialize(FnBatch));
  except
    ShowError;
  end;
  CheckRtnValue(RecvPush_Start(PChar(FstrDrtpAddr), FnDrtpPort, FnMainFunc));
  WriteLog('RevPushThread have started!', lcKSClientStart);
  Resume;
end;

procedure TPushRevThread.ShowError;
var
  ErrorMessage: array[0..255] of char;
  msgCode: Integer;
begin
  RecvPush_GetLastError(msgCode, ErrorMessage);
  WriteLog(Format('RevPushThread Error(%d):%s', [MsgCode, Trim(ErrorMessage)]),
    lcKSClientStart);
end;

procedure TPushRevThread.UpdateHQ;
var
  Body: PByte;
begin
  Body := @Buffer;
  Inc(Body, SizeOf(TSTDataHead));
  {**********************************************
     <What>调用宿主程序里面的处理函数
     <Written By> Zhu pengfei (朱朋飞)
     函数类型：  TRecievePushData。
  **********************************************}
{$IFDEF MANAGESYS}
  fmMain.RecievePushData(FRequestType, PTSTPack(Body));
{$ENDIF}

{$IFDEF KSTRADER}
  fmMain.MainFrame.RecievePushData(FRequestType, PTSTPack(Body));
{$ENDIF}

{$IFDEF KSREPORT}
  fmMain.MainFrame.RecievePushData(FRequestType, PTSTPack(Body));
{$ENDIF}
{$IFDEF KSRISK}
  fmMain.MainFrame.RecievePushData(FRequestType, PTSTPack(Body));
{$ENDIF}

end;

end.
