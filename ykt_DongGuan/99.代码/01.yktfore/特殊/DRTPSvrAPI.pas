unit DRTPSvrAPI;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>DRTPSvrAPI
   <What>Kingstar通讯平台服务器API
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}


interface
uses
{$IFDEF WIN32}
  Windows;
{$ELSE}
  Wintypes, WinProcs;
{$ENDIF}


{=> d:\临时文档\DRTPAPPDLL.H <=}

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
  USER_MESSAGE_RESULT = 2; {//返回结果集，返回应答数据}
  USER_MESSAGE_REPORT = 5; {//返回报告消息，返回错误信息}
  USER_MESSAGE_ENDPACK = 12; {//结束包，在所有数据发送完之后，必须发送结束包，该包无数据，len=0}

type
  TAPPHANDLE = record
    buf: Array[0..64-1] of Char;
  end {APPHANDLE};

  PAppHandle = ^TAPPHANDLE;

{///得到版本号 }
var
  App_GetVer: function: WORD; stdcall;

{///初始化接收数据socket，设置接收队列长度，并得到一个连接索引index， }
{///通过该索引与网关通讯,(设置报错方式,暂未实现) }
{///返回-1表示失败 }
var
  App_Init: function(QueueLen : Integer= 20 ;
                              ErrorMode : Integer=0;
                              lp : PChar = nil) : Integer; stdcall;

{///根据index连接网关，交换密钥，注册功能号 }
{///index是App_Init返回的连接索引 }
{///连接失败返回false; }
var
  App_Connect: function(index : Integer;
                        ServerIp : PChar  ;
                        ServerPort : short  ;
                        FunctionCount : WORD  ;
                        Func : PWord;
                        EncryptMode : Integer  = 0) : bool; stdcall;

{///根据连接索引index从网关上接收一个数据包，并将接收到的数据填入接收队列 }
{///如果没有接收到数据则阻塞接收，出错返回<0，成功则返回0 }
var
  iApp_Recv: function(index: Integer): Integer; stdcall;

{///根据连接索引index从网关上接收一个数据包，并将接收到的数据填入接收队列 }
{///如果没有接收到数据则阻塞接收，出错返回false，成功则返回true }
var
  App_Recv: function(index: Integer): bool; stdcall;

{///重连网关，连接失败时延时ReConnectDelay秒后重试，直到连接成功 }
{///如果 ReConnectDelay <= 0 则连接失败后不重试，以false返回 }
var
  App_ReConnect: function(index : Integer  ;
                          ReConnectDelay : Integer  = 1) : bool; stdcall;

{///从接收队列中取数据，APPHANDLE由函数调用者分配内存， }
{///连接信息被保存到该内存块中，在发送完全部数据之前，该内存不能释放 }
{///返回值 <= 0 表示出错，否则表示取到的数据长度 }
var
  App_Pop: function(var handle : TAPPHANDLE;
                    Data : PChar ;
                    len : Integer;
                    TimeOut : DWORD=0) : Integer; stdcall;

{///向网关发送数据，handle必须是Pop函数返回的句柄 }
var
  App_Send: function(var handle: TAPPHANDLE;
                     Data: PChar; 
                     len: Integer): bool; stdcall;

{///关闭与网关的连接,如果handle不为NULL则关闭句柄上的连接，否则关闭index指定的连接 }
var
  App_Close: procedure(index : Integer; handle: Pointer=nil); stdcall;

var
  App_GetLastError: procedure(error: PChar) stdcall;

//{//////////////////////////////////////////////////////////////////////// }
//{///DRTPAPPDLL ver 2.01 }
//
//{///使用缺省参数创建接收线程，实现了App_Init,App_Connect,App_Recv和App_ReConnect的功能 }
//{///ServerIp 网关地址,ServerPort 连接端口号,FunctionCount 主功能号数目,func 功能号数组 }
//{///该函数创建了一个单独的线程负责数据的接收 }
//var
//  App_RecvDone: function(ServerIp: PChar;
//                         ServerPort: SmallInt;
//                         FunctionCount: Word;
//                         var func: Word): DRTPAPPDLL_API stdcall;
//
//{//////////////////////////////////////////////////////////////////////// }
//{///DRTPAPPDLL ver 2.02 }
//
//{///从接收队列中取数据，APPHANDLE由函数调用者分配内存， }
//{///连接信息被保存到该内存块中，在发送完全部数据之前，该内存不能释放 }
//{///返回值 <= 0 表示出错，否则表示取到的数据长度 }
//{///注意：返回的数据Data中不包括应用头，是一串用|分隔的字符串，而App_Pop返回数据中包括应用头 }
//var
//  App_Pop2: function(var handle: APPHANDLE;
//                     Data: PChar;
//                     len: Integer;
//                     0: DWORD TIMEOUT =): DRTPAPPDLL_API stdcall;
//
//{///向网关发送数据，handle必须是Pop函数返回的句柄 }
//{///注意，发送数据Data不包括应用头，是一串用|分隔的字符串，而App_Send发送数据包括应用头 }
//{///ColNum 表示发送的字段数目，即|分隔的字符串数目，如：发送 A|123|11 则ColNum = 3 }
//{///flag 参数表示发送数据的类型，有以下几种: }
//{/// USER_MESSAGE_RESULT 返回结果集，返回应答数据 }
//{/// USER_MESSAGE_REPORT 返回报告消息，返回错误信息 }
//{/// USER_MESSAGE_ENDPACK 结束包，在所有数据发送完之后，必须发送结束包，该包无数据，len=0 }
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
//{///向另外一个应用转发请求数据包 }
//{///DestNo 转发数据的目的营业部代码 }
//{///其它参数与App_Send相同 }
//{///该函数可满足将本地应用无法处理的请求发往其它应用的需要 }
//var
//  App_Transmit: function(var handle: APPHANDLE;
//                         Data: PChar;
//                         len: Integer;
//                         DestNo: Integer;
//                         0: WORD MAINFUNC =): DRTPAPPDLL_API stdcall;
//
//{///设置记录错误日志的文件名 }
//{///如不调用该函数，缺省的日志文件名是可执行文件所在目录下的liblog.txt文件 }
//{///如果filename参数不带路径，则自动添加可执行文件所在的目录 }
//var
//  App_SetLogFileName: function(filename: PChar) stdcall;
//
//{///得到客户端标志 }
//{///UserHandle缓冲区的长度为64字节，由函数调用者提供 }
//var
//  App_GetUserHandle: function(var handle: APPHANDLE;
//                              UserHandle: PChar) stdcall;
//
//
//{/// 函数名: App_GetConnectIndex }
//{/// 编程 : 陈永华 2002-5-26 11:14:07 }
//{/// 描述 : 根据APPHANDLE 取得使用的Index(由App_Init()返回的索引号) }
//{/// 返回 : DRTPAPPDLL_API int }
//{/// 参数 : APPHANDLE*handle }
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
