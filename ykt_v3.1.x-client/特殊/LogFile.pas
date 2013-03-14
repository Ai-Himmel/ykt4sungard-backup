unit LogFile;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit> LogFile
   <What> ʵ����־�ļ�(һ��Ҫ����debug����)
   <Written By> Huang YanLai
   <History>
**********************************************}

{
  you must use the unit before writelog
}

interface

uses windows;

{
  Notes :
    In the previouse version this unit automatically call OpenLogFile if you uses the unit,
  while in the curren version, if you want write log to file, you must manullay call OpenLogFile
  in initialization section of your main unit.

}

type
  TLogCatalog = byte; //��־����
  TLogCatalogs = set of TLogCatalog; //��־���ͼ���

  {
    <Interface>ILogSystem
    <What>��־�ӿ�
    <Properties>
      -
    <Methods>
      WriteLog-д��־��ע����־�Ѿ������ˣ�ͬʱ������ʱ���
      UpdateLogMedia-���±�����־��ý��
  }
  ILogSystem = interface
    // д��־��ע����־�Ѿ������ˣ�ͬʱ������ʱ���
    procedure WriteLog(const S:string; Catalog : byte = 0);
    // ���±�����־��ý��
    procedure UpdateLogMedia;
  end;

const
  // ��׼����־����
  lcOther = 0;
  lcConstruct_Destroy = 1;
  lcMemoey = 2;
  lcException = 3;
  lcDebug = 4;
  // application Log Catalog
  lcAppLogStart = 128;
{
  // ����������������Ԫ�������־����

  // RPDefines
  lcReport = 5;

  // WVCommands.pas
  lcCommand = 6;

  // KCDataPack.pas
  lcKCPack = 7;
  lcKCPackDetail = 13;

  // DBAHelper.pas
  lcDBAIntfHelper = 8;

  // KSFrameWorks
  lcRegisterUI = 9;

  // BDAImp
  lcDataset= 10;
  lcRender = 11;

  // KCDataAccess
  lcKCDataset = 12;

  // BDAImpEx
  lcHDatabase = 13;

  // MSSQLAcs
  lcMSSQL = 14;

  // TxtDBEx
  lcTextDataset = 15;

  // CompUtils
  lcSimulateKey = 16;

  // SrvUtils
  lcSrvApp = 17;

  // KCWVProcBinds
  lcKCProcessor = 18;

  // KCDataAccess
  lcKCDatasetDetail = 19;

  // USynComm
  lcSynComm = 20;

  // KSXMLDS
  lcHttpRequest = 21;
  lcHttpResponse = 22;
  lcHttpCookie = 23;
  lcHttpDataset = 24;

  // UCommonDef
  lcMonitorClient = 25;
  lcMonitorClientField = 27;
  lcMonitorServer = 26;
  lcDRTPNodeLog = 28;
  lcBasicDrawing = 29;
  lcGraphDrawers = 30;

  // NetUtils2
  lcMulticastSocket = 31;

  // UCommonDef
  lcMonitorRelayServer = 32;
  lcMonitorRelayServerDetail = 33;
  lcRSNodeLog = 34;
  lcMonitorService = 35;
  lcActiveServerChecker = 36;

  // BDAViewers
  lcDatasetViewer = 37;

  // BDAImpEx
  lcHQuery = 38;

  // KSEval
  lcEvaluateDetail = 39;
}

  LineBreak = #13#10;
  UpdateLogMsg = 'Update Log File.'#13#10;

var
  // �������־����־���ͼ���
  LogCatalogs : TLogCatalogs = [lcException];
  // �Ƿ����ʱ���
  isLogTime : Boolean = true;
  // �Ƿ�ͬʱʹ��OutputDebugString���
  isOutputDebugString : Boolean = True;
  // ��ǰʹ�õ���־ϵͳ
  LogSystem : ILogSystem = nil;

// ��һ����־�ļ���Ϊ��־ϵͳ
procedure OpenLogFile(const alogFileName : string=''; awithDate:Boolean=false; aoverwrite:Boolean=false);

// д��־
procedure WriteLog(const S:string; Catalog : byte = 0);

// д���⵽��־
procedure WriteException;

procedure EnableLogCatalog(LogCatalog : TLogCatalog; Enabled : Boolean=True);

function  IsLogThis(LogCatalog : TLogCatalog) : Boolean;

//procedure WriteBuffer(Buffer : Pchar; BufferSize : Integer);

type
  TFileLogSystem = class(TInterfacedObject,ILogSystem)
  private

  protected
    FLogLock : TRTLCriticalSection;
    FHLogFile : THandle;
    FLogFileName,FBaseFileName : string;
    FLogFileAvailable : Boolean;
    FLogDay : Integer;
    FWithDate :  Boolean;
    FOverwrite:  Boolean;
    // ILogSystem
    procedure   WriteLog(const S:string; Catalog : byte = 0);
    procedure   UpdateLogMedia;
    // Support Methods
    procedure   GenLogFileName;
    procedure   InternalOpenLogFile;
    procedure   UpdateLogFile;
  public
    constructor Create(const ALogFileName : string=''; AWithDate:Boolean=False; AOverwrite:Boolean=False);
    destructor  Destroy;override;
    property    LogFileName : string read FLogFileName;
    property    BaseFileName : string read FBaseFileName;
    property    LogFileAvailable : Boolean read FLogFileAvailable;
    property    LogDay : Integer read FLogDay;
    property    WithDate :  Boolean read FWithDate;
    property    Overwrite:  Boolean read FOverwrite;
  end;


implementation

uses sysUtils,math;

procedure EnableLogCatalog(LogCatalog : TLogCatalog; Enabled : Boolean);
begin
  if Enabled then
    Include(LogCatalogs,LogCatalog) else
    Exclude(LogCatalogs,LogCatalog);
end;

function  IsLogThis(LogCatalog : TLogCatalog) : Boolean;
begin
  Result := LogCatalog in LogCatalogs;
end;

var
  oldExceptHandler : Pointer;

procedure OpenLogFile(const alogFileName : string=''; awithDate:Boolean=false; aoverwrite:Boolean=false);
var
  FileLogSystem : TFileLogSystem;
begin
  FileLogSystem := TFileLogSystem.Create(alogFileName,awithDate,aoverwrite);
  if FileLogSystem.LogFileAvailable then
    LogSystem := FileLogSystem else
    FreeAndNil(FileLogSystem);
end;

procedure WriteLog(const S:string; Catalog : byte = 0);
var
  s1,s2 : string;
begin
  // ������־
  if not (Catalog in LogCatalogs) then
    Exit;
  // �Ż�
  if (LogSystem=nil) and not isOutputDebugString then
    Exit;
  // ����ʱ���
  if isLogTime then
    s2 := formatDateTime('hh:nn:ss ',now)+ s  else
    s2 := s ;
  s1 := s2 + lineBreak;
  if LogSystem<>nil then
    LogSystem.WriteLog(S1,Catalog);
  if isOutputDebugString then
    outputDebugString(pchar(s2));
end;

{
procedure WriteBuffer(Buffer : Pchar; BufferSize : Integer);
var
  wbytes : DWORD;
begin
  if FLogFileAvailable then
  begin
    EnterCriticalSection(FLogLock);
    try
      WriteFile(FHLogFile,Buffer^,BufferSize,wbytes,nil);
    finally
      LeaveCriticalSection(FLogLock);
    end;
  end;
end;
}
procedure MyExceptHandler(ExceptObject: TObject; ExceptAddr: Pointer); far;
begin
  if ExceptObject is Exception then
    WriteLog(Format('Unhandled Exception:%s at %8.8x,%s',
      [ExceptObject.className,Integer(ExceptAddr),Exception(ExceptObject).Message]),lcException) else
    WriteLog(Format('Unhandled Exception:%s at %8.8x',
      [ExceptObject.className,Integer(ExceptAddr)]),lcException);
end;

procedure WriteException;
var
  obj : TObject;
begin
  obj := ExceptObject;
  if obj<>nil then
  begin
    if obj is Exception then
      WriteLog(obj.className+' '+Exception(obj).Message,lcException) else
      WriteLog(obj.className,lcException);
  end;
end;

{ TFileLogSystem }

constructor TFileLogSystem.Create(const ALogFileName: string; AWithDate,
  AOverwrite: Boolean);
var
  ModuleName: array[0..255] of Char;
  p : Pchar;
begin
  inherited Create;
  try
    InitializeCriticalSection(FLogLock);

    FillChar(ModuleName,sizeof(ModuleName),0);
    if (aLogFileName<>'') then
      move(pchar(aLogFileName)^,ModuleName,SizeOf(ModuleName)-1)  else
      begin
        GetModuleFileName(0, ModuleName, SizeOf(ModuleName)-1-4); // -4 for '.log'
        // change extension
        P := AnsiStrRScan(ModuleName, '.');
        if p=nil then
          p:=StrEnd(ModuleName);
        move('.log',p^,4);
      end;

    FWithDate := awithDate;
    if FWithDate then
    begin
      P := AnsiStrRScan(ModuleName, '.');
      if p=nil then
        p:=StrEnd(ModuleName);
      move(p[0],p[2],StrLen(p));
      move('%s',p[0],2);
    end;
    FBaseFileName:=string(ModuleName);

    FOverwrite:=aoverwrite;
    InternalOpenLogFile;
  except
    FLogFileAvailable := false;
  end;
end;

procedure TFileLogSystem.WriteLog(const S: string; Catalog: byte);
var
  wbytes : DWORD;
begin
  if FLogFileAvailable then
  begin
    EnterCriticalSection(FLogLock);
    try
      WriteFile(FHLogFile,pchar(s)^,length(s),wbytes,nil);
    finally
      LeaveCriticalSection(FLogLock);
    end;
  end;
end;

procedure TFileLogSystem.GenLogFileName;
var
  DateStr : string;
  thisTime : TDatetime;
begin
  if FWithDate then
  begin
    thisTime := now;
    FLogDay := Floor(thistime);
    DateStr := FormatDateTime('yymmdd',thisTime);
    FLogFileName := format(FBaseFileName,[DateStr]);
  end else
  begin
    FLogFileName := FBaseFileName;
  end;
end;

procedure TFileLogSystem.InternalOpenLogFile;
var
  openMode : Integer;
begin
  genLogFileName;
  if FOverwrite then
    openMode := CREATE_ALWAYS else
    openMode := OPEN_ALWAYS;
  FHLogFile := CreateFile(pchar(FLogFileName),
              GENERIC_WRITE,
              FILE_SHARE_READ	or FILE_SHARE_WRITE,
              nil,
              openMode,
              FILE_ATTRIBUTE_NORMAL or FILE_FLAG_WRITE_THROUGH,
              0);
  FLogFileAvailable := FHLogFile<>INVALID_HANDLE_VALUE;
  if FLogFileAvailable and not FOverwrite then
    SetFilePointer(FHLogFile,0,nil,FILE_END) else
    SetFilePointer(FHLogFile,0,nil,FILE_BEGIN);
end;

procedure TFileLogSystem.UpdateLogFile;
var
  wbytes : DWORD;
begin
  if FWithDate and (FLogDay<Floor(now)) then
  try
    EnterCriticalSection(FLogLock);
    try
      if FHLogFile<>INVALID_HANDLE_VALUE then
      begin
        WriteFile(FHLogFile,UpdateLogMsg,length(UpdateLogMsg),wbytes,nil);
        CloseHandle(FHLogFile);
      end;
      internalOpenLogFile;
    except
      FLogFileAvailable := false;
    end;
  finally
    LeaveCriticalSection(FLogLock);
  end;
end;

destructor TFileLogSystem.Destroy;
begin
  if FLogFileAvailable then
  begin
    if FHLogFile<>INVALID_HANDLE_VALUE then
      CloseHandle(FHLogFile);
  end;
  DeleteCriticalSection(FLogLock);
  inherited;
end;

procedure TFileLogSystem.UpdateLogMedia;
begin
  UpdateLogFile;
end;

initialization
  oldExceptHandler := ExceptProc;
  ExceptProc := @MyExceptHandler;

finalization
  ExceptProc := oldExceptHandler;

end.
