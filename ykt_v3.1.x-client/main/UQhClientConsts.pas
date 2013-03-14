unit UQhClientConsts;

interface
uses windows;

type
  TForceQuitReason = array[0..255] of char;
  PForceQuitReason = ^TForceQuitReason;

const
  MaxLength_ForceQuitReason = 40;
  Msg_ForceQuit = $AAAA;
  Exe_force_login_logout = 856045; //	ǿ�Ʋ���Ա¼��

const

  // �����ļ�ת��
  SKingStarFutureBinCfgKey = '�������˴��ڻ�ϵͳ�����ļ���Կ';
  SKingStarFutureBinMnuKey = '�������˴��ڻ�ϵͳ�˵��ļ���Կ';

  //һЩ���õĲ�������
{$IFDEF MANAGESYS}
  SApplicationTitle = 'У԰һ��ͨ����ϵͳ';
  AppMark = 'B';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '0';
  LogFileName = 'KSManageSys.Log';
  ConfigFileName = 'SmartCardClient.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000001;
{$ENDIF}
{$IFDEF KSTRADER}
  SApplicationTitle = '���˴��ڻ�����Աϵͳ';
  AppMark = 'C';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '1';
  LogFileName = 'KSTrader.Log';
  ConfigFileName = 'KSClientPop.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000002;
{$ENDIF}
{$IFDEF KSREPORT}
  SApplicationTitle = '���˴��ڻ��ֹ�����ϵͳ';
  AppMark = 'M';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '1';
  LogFileName = 'KSReport.Log';
  ConfigFileName = 'KSClientPop.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000004;
{$ENDIF}
{$IFDEF KSRISK}
  SApplicationTitle = '���˴��ڻ��������ϵͳ';
  AppMark = 'N';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '0';
  LogFileName = 'KSRisk.Log';
  ConfigFileName = 'KSClientPop.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000008;
{$ENDIF}

{$IFDEF SYSMONSERVER}
  SApplicationTitle = '���˴��ڻ�ϵͳ���ϵͳ';
  AppMark = 'L';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '0';
  LogFileName = 'SysMonServer.Log';
  ConfigFileName = 'SysMonServer.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000010;
{$ENDIF}
{$IFDEF TRADERMONSERVER}
  SApplicationTitle = '���˴��ڻ����׼�ط�����';
  AppMark = 'J';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '1';
  LogFileName = 'MonitorServer.Log';
  ConfigFileName = 'MonitorServer.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000020;
{$ENDIF}
{$IFDEF KSMONCLIENT}
  SApplicationTitle = '���˴��ڻ����׼���ն�';
  AppMark = 'K';
  DefaultRevInfMark = '0';
  DefaultRevRptMark = '1';
  LogFileName = 'MonitorClient.Log';
  ConfigFileName = 'MonitorClient.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000040;
{$ENDIF}
{$IFDEF BILLDISPATCHSERVER}
  SApplicationTitle = '���˴��ڻ��˵��ַ�ϵͳ';
  AppMark = 'O';
  DefaultRevInfMark = '1';
  DefaultRevRptMark = '0';
  LogFileName = 'BillDispatchServer.Log';
  ConfigFileName = 'BillDispatchServer.in' {'ksclient.ini'}; // �����ļ�
  ByteMarkForConfirmInstanceExist = $00000080;
{$ENDIF}
{$IFDEF SysFileMan}
  SApplicationTitle = '���˴�У԰һ��ͨ����ϵͳ';//'���˴������ļ����ܳ���';
  ByteMarkForConfirmInstanceExist = $00000100;
{$ENDIF}

type

  THandledObject = class(TObject)
  protected
    FHandle: THandle;
  public
    destructor Destroy; override;
    property Handle: THandle read FHandle;
  end;

  TSharedMem = class(THandledObject)
  private
    FName: string;
    FSize: Integer;
    FCreated: Boolean;
    FFileView: Pointer;
    FHaveCreatedBefore: Boolean;
  public
    constructor Create(const Name: string; Size: Integer);
    destructor Destroy; override;
    property Name: string read FName;
    property Size: Integer read FSize;
    property Buffer: Pointer read FFileView;
    property Created: Boolean read FCreated;
    property HaveCreatedBefore: Boolean read FHaveCreatedBefore;
  end;

function CheckProgramRunning: Boolean;
procedure ReleaseShareMem;

implementation

uses
  SysUtils;

const
  KingStarGroupFuture60Mark = 'KingStarGroupFuture60Mark';

var
  GlobalShareMem: TSharedMem;

function IsKSFutureV60Running: Boolean;
var
  shareValue: Cardinal;
begin
  if GlobalShareMem <> nil then
  begin
    Result := True;
    Exit;
  end;
  GlobalShareMem := TSharedMem.Create(KingStarGroupFuture60Mark, 4);
  try
    Move(PByte(GlobalShareMem.Buffer)^, shareValue, 4);
    Result := (shareValue and ByteMarkForConfirmInstanceExist) > 0;
    if Result then
      Exit
    else
      shareValue := shareValue or ByteMarkForConfirmInstanceExist;
    Move(shareValue, PByte(GlobalShareMem.Buffer)^, 4);
  finally
    if Result then
      FreeAndNil(GlobalShareMem);
  end;
end;

procedure ClearKSProgramMark;
var
  shareValue: Cardinal;
begin
  Assert(GlobalShareMem <> nil);
  Move(PByte(GlobalShareMem.Buffer)^, shareValue, 4);
  shareValue := shareValue and (not ByteMarkForConfirmInstanceExist);
  Move(shareValue, PByte(GlobalShareMem.Buffer)^, 4);
  Assert((shareValue and ByteMarkForConfirmInstanceExist) = 0);
end;

function CheckProgramRunning: Boolean;
begin
  if IsKSFutureV60Running then
  begin
    MessageBox(0, Pchar(Format('�Ѿ���һ������ʵ�������У�������ͬʱ���ж��%s!'
      , [SApplicationTitle])), Pchar('����������!'), MB_OK or MB_ICONERROR);
    Result := False;
    Assert(GlobalShareMem = nil);
  end
  else
    Result := True;
end;

procedure ReleaseShareMem;
begin
  if GlobalShareMem <> nil then
    if IsKSFutureV60Running then
      ClearKSProgramMark;
  GlobalShareMem.Free;
end;

{ THandledObject }

destructor THandledObject.Destroy;
begin
  if FHandle <> 0 then
    CloseHandle(FHandle);
end;

{ TSharedMem }

constructor TSharedMem.Create(const Name: string; Size: Integer);
var
  ErrorRlt: DWORD;
begin
  try
    FName := Name;
    FSize := Size;
    { CreateFileMapping, when called with $FFFFFFFF for the hanlde value,
      creates a region of shared memory }
    FHandle := CreateFileMapping($FFFFFFFF, nil, PAGE_READWRITE, 0,
      Size, PChar(Name));
    if FHandle = 0 then
      abort;
    ErrorRlt := GetLastError;
    FCreated := ErrorRlt = 0;
    FHaveCreatedBefore := ErrorRlt = ERROR_ALREADY_EXISTS;
    { We still need to map a pointer to the handle of the shared memory region }
    FFileView := MapViewOfFile(FHandle, FILE_MAP_WRITE, 0, 0, Size);
    if FFileView = nil then
      abort;
  except
    raise Exception.Create(Format('Error creating shared memory %s (%d)', [Name,
      GetLastError]));
  end;
end;

destructor TSharedMem.Destroy;
begin
  if FFileView <> nil then
    UnmapViewOfFile(FFileView);
  inherited Destroy;
end;

initialization
  GlobalShareMem := nil;

end.
