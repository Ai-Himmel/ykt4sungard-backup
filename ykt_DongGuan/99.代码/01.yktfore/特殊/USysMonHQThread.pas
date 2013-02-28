unit USysMonHQThread;
{$DEFINE HQDebug}
interface

uses
  Classes, Windows, KCDataPack, Syncobjs;

type

  THQRecieveThread = class(TThread)
  private
    FiHqWay: Integer;
    FhWnd: THandle;
    FiMsg: Word;
    FstrOperCode: PChar;
    FwDestNo: Word;
    FwMainFunc: Word;
    FstrIP: PChar;
    FwPort: Word;
    FwLocalPort: Word;
    FwRegtimeval: Word;
    FRequestType : LongWord;
    Fitimeout: Integer;

    FBuffer : array [0..1024*8] of Byte;
    FData : TSTPack;

    FWaitForOP : TEvent;
    { Private declarations }
    procedure GetData;
    procedure ShowError;
  protected
    procedure Execute; override;
    procedure UpdateHQ;
  public
    constructor Create( strIP: PChar = nil;
                        strOperCode: PChar = nil;
                        iHqWay: Integer = 1;
                        hWnd: THandle = 0;
                        iMsg: Word = 0;
                        wDestNo: Word = 0;
                        wMainFunc: Word = 666;
                        wPort: Word = 2000;
                        wLocalPort: Word = 0;
                        wRegtimeval: Word = 15;
                        RequestType : LongWord = 854077;
                        itimeout: Integer = 200);
    destructor Destroy; override;
    procedure UpdateCaption;
    procedure Open;
    procedure Close;
    
  end;

implementation

uses
  KSHQDLL, Sysutils, LogFile, SysMonServerConsts;

procedure THQRecieveThread.Close;
begin
  Terminate;
  WaitFor;
  HQ_Stop;
  HQ_Uninit;
  WriteLog('HQThread have closed!',lcKSClientStart);
end;

constructor THQRecieveThread.Create(strIP: PChar ; strOperCode: PChar; 
  iHqWay: Integer; hWnd: THandle;iMsg: Word; wDestNo, wMainFunc: Word;
  wPort, wLocalPort, wRegtimeval: Word; RequestType: LongWord;
  itimeout: Integer);
begin
  inherited Create(True);

  FiHqWay      := iHqWay;
  FhWnd        := hWnd;
  FiMsg        := iMsg;
  FstrOperCode := strOperCode;
  FwDestNo     := wDestNo;
  FwMainFunc   := wMainFunc;
  FstrIP       := strIP;
  FwPort       := wPort;
  FwLocalPort  := wLocalPort;
  FwRegtimeval := wRegtimeval;
  FRequestType := RequestType;
  Fitimeout    := itimeout;

  WriteLog('HQThread have created!',lcKSClientStart);
  WriteLog(Format('FiHqWay=%d;FhWnd=%d;FiMsg=%d;FstrOperCode=%s;' +
                  'FwDestNo=%d;FwMainFunc=%d;FstrIP=%s;FwPort=%d;' +
                  'FwLocalPort=%d;FwRegtimeval=%d;FRequestType=%d;Fitimeout=%d;',
                  [ FiHqWay     ,FhWnd       ,FiMsg       ,FstrOperCode,FwDestNo,
                    FwMainFunc  ,FstrIP      ,FwPort      ,FwLocalPort ,
                    FwRegtimeval,FRequestType,Fitimeout]),
                    lcKSClientStart);

  //FLVSubItemCount := fmMain.MainFrame.ListViewTop.Columns.Count - 1;
  FWaitForOP := TEvent.Create(nil,False,True,'');
end;

destructor THQRecieveThread.Destroy;
begin
  FreeAndNil(FWaitForOP);
  inherited;
end;

procedure THQRecieveThread.Execute;
begin
  while not Terminated do
  begin
    GetData;
  end;

end;

procedure THQRecieveThread.GetData;
var
  PBuffer : PByte;
begin
  FillChar(FBuffer,SizeOf(FBuffer),0);
  FillChar(FData,SizeOf(TSTPack),0);
  PBuffer := @FBuffer;

  if HQ_GetRec(PBuffer^,SizeOf(FBuffer),Fitimeout) > 0 then
  begin
    WriteLog(Format('%20s At %d',['Data Arrived!',GetTickCount]),lcKSClientStart);
    if FWaitForOP.WaitFor(INFINITE) = wrSignaled then
    WriteLog(Format('%20s At %d',['Event Singaled!',GetTickCount]),lcKSClientStart);
    UpdateCaption;
    Synchronize(UpdateHQ);
  end;
end;

procedure THQRecieveThread.Open;
begin
  try
    HQ_Init(FiHqWay          ,
            FhWnd            ,
            FiMsg            ,
            FstrOperCode     ,
            FwDestNo         ,
            FwMainFunc       ,
            FstrIP           ,
            FwPort           ,
            FwLocalPort      ,
            FwRegtimeval      );
  except
    ShowError;
  end;
  HQ_Start;
  WriteLog('HQThread have started!',lcKSClientStart);
  Resume;
end;

procedure THQRecieveThread.ShowError;
var
  ErrorMessage : array [0..200] of char;
begin
  HQ_GetErrorMsg(ErrorMessage,SizeOf(ErrorMessage));
  WriteLog('HQThread Error : ' + Trim(ErrorMessage),lcKSClientStart);
end;

procedure THQRecieveThread.UpdateCaption;
var
  PHead : PSTDataHead;
  Body : PByte;
begin
  PHead := PSTDataHead(@FBuffer);
  Body := @FBuffer;
  Inc(Body,SizeOf(PHead^));
  KCUnPackData(PHead^.ParamBits,FData,Body);
end;

procedure THQRecieveThread.UpdateHQ;
var
  TempSL : TStringList;
begin

  TempSL := TStringList.Create;
  try

  finally
    TempSL.Free;
  end;

end;

end.
