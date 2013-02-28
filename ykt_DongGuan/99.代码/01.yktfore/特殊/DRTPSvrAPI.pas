unit DRTPSvrAPI;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>DRTPSvrAPI
   <What>KingstarͨѶƽ̨������API
   <Written By> Huang YanLai (������)
   <History>
**********************************************}


interface
uses
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}


{=> d:\��ʱ�ĵ�\DRTPAPPDLL.H <=}

{+// }
{-ver 2.0 }
{-DRTPAPPDLL_API WORD App_GetVer(); }
{-DRTPAPPDLL_API int App_Init(int QueueLen = 20 , int ErrorMode = 0 , void*lp = NULL); }
{-DRTPAPPDLL_API bool App_Connect(int index , LPSTR ServerIp , short ServerPort , WORD FunctionCount , void*func , int EncryptMode = 0); }
{-DRTPAPPDLL_API bool App_Recv(int index); }
{-DRTPAPPDLL_API bool App_ReConnect(int index , int ReConnectDelay = 1); }
{-DRTPAPPDLL_API int App_Pop(APPHANDLE*handle , LPSTR Data , int len); }
{-DRTPAPPDLL_API bool App_Send(APPHANDLE*handle , LPSTR Data , int len); }
{-DRTPAPPDLL_API void App_Close(int index,APPHANDLE*handle = NULL); }
{-DRTPAPPDLL_API void App_GetLastError(LPSTR error); }
{-ver 2.01 }
{-DRTPAPPDLL_API bool App_RecvDone(LPSTR ServerIp , short ServerPort , WORD FunctionCount , WORD*func); }
{-ver 2.02 }
{-DRTPAPPDLL_API int App_Pop2(APPHANDLE*handle , LPSTR Data , int len); }
{-DRTPAPPDLL_API bool App_Send2(APPHANDLE*handle , LPSTR Data , int len ,int ColNum , int flag); }
{-ver 2.03 }
{-DRTPAPPDLL_API bool App_Transmit(APPHANDLE*handle , LPSTR Data , int len , int DestNo , WORD MainFunc); }
{-DRTPAPPDLL_API void App_SetLogFileName(char*filename) }
{-DRTPAPPDLL_API void App_GetUserHandle(APPHANDLE*handle , char*UserHandle) }
{= }

const
  APPENOREPORT = 0;
  APPEPRINTF = 1;
  APPEWRITEBUF = 2;
  APPEMSGDLG = 3;
  USER_MESSAGE_RESULT = 2; {//���ؽ����������Ӧ������}
  USER_MESSAGE_REPORT = 5; {//���ر�����Ϣ�����ش�����Ϣ}
  USER_MESSAGE_ENDPACK = 12; {//�����������������ݷ�����֮�󣬱��뷢�ͽ��������ð������ݣ�len=0}

type
  TAPPHANDLE = record
    buf: Array[0..64-1] of Char;
  end {APPHANDLE};

  PAppHandle = ^TAPPHANDLE;

{///�õ��汾�� }
var
  App_GetVer: function: WORD; stdcall;

{///��ʼ����������socket�����ý��ն��г��ȣ����õ�һ����������index�� }
{///ͨ��������������ͨѶ,(���ñ���ʽ,��δʵ��) }
{///����-1��ʾʧ�� }
var
  App_Init: function(QueueLen : Integer= 20 ;
                              ErrorMode : Integer=0;
                              lp : PChar = nil) : Integer; stdcall;

{///����index�������أ�������Կ��ע�Ṧ�ܺ� }
{///index��App_Init���ص��������� }
{///����ʧ�ܷ���false; }
var
  App_Connect: function(index : Integer;
                        ServerIp : PChar  ;
                        ServerPort : short  ;
                        FunctionCount : WORD  ;
                        Func : PWord;
                        EncryptMode : Integer  = 0) : bool; stdcall;

{///������������index�������Ͻ���һ�����ݰ����������յ�������������ն��� }
{///���û�н��յ��������������գ�������<0���ɹ��򷵻�0 }
var
  iApp_Recv: function(index: Integer): Integer; stdcall;

{///������������index�������Ͻ���һ�����ݰ����������յ�������������ն��� }
{///���û�н��յ��������������գ�������false���ɹ��򷵻�true }
var
  App_Recv: function(index: Integer): bool; stdcall;

{///�������أ�����ʧ��ʱ��ʱReConnectDelay������ԣ�ֱ�����ӳɹ� }
{///��� ReConnectDelay <= 0 ������ʧ�ܺ����ԣ���false���� }
var
  App_ReConnect: function(index : Integer  ;
                          ReConnectDelay : Integer  = 1) : bool; stdcall;

{///�ӽ��ն�����ȡ���ݣ�APPHANDLE�ɺ��������߷����ڴ棬 }
{///������Ϣ�����浽���ڴ���У��ڷ�����ȫ������֮ǰ�����ڴ治���ͷ� }
{///����ֵ <= 0 ��ʾ���������ʾȡ�������ݳ��� }
var
  App_Pop: function(var handle : TAPPHANDLE;
                    Data : PChar ;
                    len : Integer;
                    TimeOut : DWORD=0) : Integer; stdcall;

{///�����ط������ݣ�handle������Pop�������صľ�� }
var
  App_Send: function(var handle: TAPPHANDLE;
                     Data: PChar; 
                     len: Integer): bool; stdcall;

{///�ر������ص�����,���handle��ΪNULL��رվ���ϵ����ӣ�����ر�indexָ�������� }
var
  App_Close: procedure(index : Integer; handle: Pointer=nil); stdcall;

var
  App_GetLastError: procedure(error: PChar) stdcall;

//{//////////////////////////////////////////////////////////////////////// }
//{///DRTPAPPDLL ver 2.01 }
//
//{///ʹ��ȱʡ�������������̣߳�ʵ����App_Init,App_Connect,App_Recv��App_ReConnect�Ĺ��� }
//{///ServerIp ���ص�ַ,ServerPort ���Ӷ˿ں�,FunctionCount �����ܺ���Ŀ,func ���ܺ����� }
//{///�ú���������һ���������̸߳������ݵĽ��� }
//var
//  App_RecvDone: function(ServerIp: PChar;
//                         ServerPort: SmallInt;
//                         FunctionCount: Word;
//                         var func: Word): DRTPAPPDLL_API stdcall;
//
//{//////////////////////////////////////////////////////////////////////// }
//{///DRTPAPPDLL ver 2.02 }
//
//{///�ӽ��ն�����ȡ���ݣ�APPHANDLE�ɺ��������߷����ڴ棬 }
//{///������Ϣ�����浽���ڴ���У��ڷ�����ȫ������֮ǰ�����ڴ治���ͷ� }
//{///����ֵ <= 0 ��ʾ���������ʾȡ�������ݳ��� }
//{///ע�⣺���ص�����Data�в�����Ӧ��ͷ����һ����|�ָ����ַ�������App_Pop���������а���Ӧ��ͷ }
//var
//  App_Pop2: function(var handle: APPHANDLE;
//                     Data: PChar;
//                     len: Integer;
//                     0: DWORD TIMEOUT =): DRTPAPPDLL_API stdcall;
//
//{///�����ط������ݣ�handle������Pop�������صľ�� }
//{///ע�⣬��������Data������Ӧ��ͷ����һ����|�ָ����ַ�������App_Send�������ݰ���Ӧ��ͷ }
//{///ColNum ��ʾ���͵��ֶ���Ŀ����|�ָ����ַ�����Ŀ���磺���� A|123|11 ��ColNum = 3 }
//{///flag ������ʾ�������ݵ����ͣ������¼���: }
//{/// USER_MESSAGE_RESULT ���ؽ����������Ӧ������ }
//{/// USER_MESSAGE_REPORT ���ر�����Ϣ�����ش�����Ϣ }
//{/// USER_MESSAGE_ENDPACK �����������������ݷ�����֮�󣬱��뷢�ͽ��������ð������ݣ�len=0 }
//var
//  App_Send2: function(var handle: APPHANDLE;
//                      Data: PChar;
//                      len: Integer;
//                      ColNum: Integer;
//                      flag: Integer): DRTPAPPDLL_API stdcall;
//
//{//////////////////////////////////////////////////////////////////////// }
//{///DRTPAPPDLL ver 2.03 }
//
//{///������һ��Ӧ��ת���������ݰ� }
//{///DestNo ת�����ݵ�Ŀ��Ӫҵ������ }
//{///����������App_Send��ͬ }
//{///�ú��������㽫����Ӧ���޷����������������Ӧ�õ���Ҫ }
//var
//  App_Transmit: function(var handle: APPHANDLE;
//                         Data: PChar;
//                         len: Integer;
//                         DestNo: Integer;
//                         0: WORD MAINFUNC =): DRTPAPPDLL_API stdcall;
//
//{///���ü�¼������־���ļ��� }
//{///�粻���øú�����ȱʡ����־�ļ����ǿ�ִ���ļ�����Ŀ¼�µ�liblog.txt�ļ� }
//{///���filename��������·�������Զ���ӿ�ִ���ļ����ڵ�Ŀ¼ }
//var
//  App_SetLogFileName: function(filename: PChar) stdcall;
//
//{///�õ��ͻ��˱�־ }
//{///UserHandle�������ĳ���Ϊ64�ֽڣ��ɺ����������ṩ }
//var
//  App_GetUserHandle: function(var handle: APPHANDLE;
//                              UserHandle: PChar) stdcall;
//
//
//{/// ������: App_GetConnectIndex }
//{/// ��� : ������ 2002-5-26 11:14:07 }
//{/// ���� : ����APPHANDLE ȡ��ʹ�õ�Index(��App_Init()���ص�������) }
//{/// ���� : DRTPAPPDLL_API int }
//{/// ���� : APPHANDLE*handle }
//var
//  App_GetConnectIndex: function(var handle: APPHANDLE): DRTPAPPDLL_API stdcall;

var
  DLLLoaded: Boolean { is DLL (dynamically) loaded already? }
    {$IFDEF WIN32} = False; {$ENDIF}

implementation

var
  SaveExit: pointer;
  DLLHandle: THandle;
{$IFNDEF MSDOS}
  ErrorMode: Integer;
{$ENDIF}

  procedure NewExit; far;
  begin
    ExitProc := SaveExit;
    FreeLibrary(DLLHandle)
  end {NewExit};

procedure LoadDLL;
begin
  if DLLLoaded then Exit;
{$IFNDEF MSDOS}
  ErrorMode := SetErrorMode($8000{SEM_NoOpenFileErrorBox});
{$ENDIF}
  DLLHandle := LoadLibrary('QHDRTPAPPDLL.DLL');
  if DLLHandle >= 32 then
  begin
    DLLLoaded := True;
    SaveExit := ExitProc;
    ExitProc := @NewExit;
    @App_GetVer := GetProcAddress(DLLHandle,'QH_App_GetVer');
  {$IFDEF WIN32}
    Assert(@App_GetVer <> nil);
  {$ENDIF}
    @App_Init := GetProcAddress(DLLHandle,'QH_App_Init');
  {$IFDEF WIN32}
    Assert(@App_Init <> nil);
  {$ENDIF}
    @App_Connect := GetProcAddress(DLLHandle,'QH_App_Connect');
  {$IFDEF WIN32}
    Assert(@App_Connect <> nil);
  {$ENDIF}
    @iApp_Recv := GetProcAddress(DLLHandle,'iQH_App_Recv');
  {$IFDEF WIN32}
    Assert(@iApp_Recv <> nil);
  {$ENDIF}
    @App_Recv := GetProcAddress(DLLHandle,'QH_App_Recv');
  {$IFDEF WIN32}
    Assert(@App_Recv <> nil);
  {$ENDIF}
    @App_ReConnect := GetProcAddress(DLLHandle,'QH_App_ReConnect');
  {$IFDEF WIN32}
    Assert(@App_ReConnect <> nil);
  {$ENDIF}
    @App_Pop := GetProcAddress(DLLHandle,'QH_App_Pop');
  {$IFDEF WIN32}
    Assert(@App_Pop <> nil);
  {$ENDIF}
    @App_Send := GetProcAddress(DLLHandle,'QH_App_Send');
  {$IFDEF WIN32}
    Assert(@App_Send <> nil);
  {$ENDIF}
    @App_Close := GetProcAddress(DLLHandle,'QH_App_Close');
  {$IFDEF WIN32}
    Assert(@App_Close <> nil);
  {$ENDIF}
    @App_GetLastError := GetProcAddress(DLLHandle,'QH_App_GetLastError');
  {$IFDEF WIN32}
    Assert(@App_GetLastError <> nil);
  {$ENDIF}
//    @App_RecvDone := GetProcAddress(DLLHandle,'App_RecvDone');
//  {$IFDEF WIN32}
//    Assert(@App_RecvDone <> nil);
//  {$ENDIF}
//    @App_Pop2 := GetProcAddress(DLLHandle,'App_Pop2');
//  {$IFDEF WIN32}
//    Assert(@App_Pop2 <> nil);
//  {$ENDIF}
//    @App_Send2 := GetProcAddress(DLLHandle,'App_Send2');
//  {$IFDEF WIN32}
//    Assert(@App_Send2 <> nil);
//  {$ENDIF}
//    @App_Transmit := GetProcAddress(DLLHandle,'App_Transmit');
//  {$IFDEF WIN32}
//    Assert(@App_Transmit <> nil);
//  {$ENDIF}
//    @App_SetLogFileName := GetProcAddress(DLLHandle,'App_SetLogFileName');
//  {$IFDEF WIN32}
//    Assert(@App_SetLogFileName <> nil);
//  {$ENDIF}
//    @App_GetUserHandle := GetProcAddress(DLLHandle,'App_GetUserHandle');
//  {$IFDEF WIN32}
//    Assert(@App_GetUserHandle <> nil);
//  {$ENDIF}
//    @App_GetConnectIndex := GetProcAddress(DLLHandle,'App_GetConnectIndex');
//  {$IFDEF WIN32}
//    Assert(@App_GetConnectIndex <> nil);
//  {$ENDIF}
  end
  else
  begin
    DLLLoaded := False;
    { Error: DRTPAPPDLL.DLL could not be loaded !! }
  end;
{$IFNDEF MSDOS}
  SetErrorMode(ErrorMode)
{$ENDIF}
end {LoadDLL};

begin
  LoadDLL;
end.
