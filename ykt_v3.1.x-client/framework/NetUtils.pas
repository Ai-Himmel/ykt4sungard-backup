unit NetUtils;

{$I KSConditions.INC }

{$ifdef VCL60_UP }
{$WARN SYMBOL_PLATFORM OFF}
{$else}

{$endif}

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit> NetUtils
   <What> 有关网络的工具
   <Written By> Huang YanLai
   <History>
**********************************************}


interface

uses Windows, SysUtils, WinSock, Nb30, Classes;

procedure Startup;

procedure Cleanup;

type
  TAdapter = packed record
     adapt : TADAPTERSTATUS;
     NameBuff : array[0..30-1] of Char;
  end;

{
  <Function>GetMACAddr
  <What>获得网卡地址，用XXXXXXXXXXXX (12Char的16进制字符串)表示
  <Params>
    -
  <Return>
  <Exception>
}
function GetMACAddr : string;

{
  <Function>GetMACAddrInt64
  <What>获得网卡地址,用64bit的整数表示。其中前6Byte是网卡地址，后2Byte是0。
  <Params>
    -
  <Return>
  <Exception>
}
function GetMACAddrInt64 : Int64;

procedure SocketError(ErrorCode : Integer; const Msg : string='');

procedure CheckSocketCall(ReturnCode : Integer; const Msg : string='');

procedure CheckValidSocket(Socket : TSocket; const Msg : string='');

function  GetLocalName : string;

function  GetLocalIp : LongWord;

function  GetLocalIpAddr : string;

function  IpToString(Ip : LongWord) : string;

function  StringToIp(const IpAddr : string) : LongWord;

const
  DefaultMaxLength = 8*1024;

type
  EKSSocketError = class(Exception);

  TKSSocket = class(TObject)
  private
    FSocket: TSOCKET;
  public
    constructor Create(ASocket : TSOCKET = 0); overload;
    destructor  Destroy; override;
    // 关闭
    procedure   Close;
    function    Send(Buffer : Pointer; Count : Longword) : Integer; overload;
    function    Receive(Buffer : Pointer; MaxCount : Longword) : Integer; overload;
    function    IsDataArrived(TimeOut : LongWord) : Boolean;
    property    Socket : TSOCKET read FSocket;

    //
    class function CreateTCPClient(const IP : string; Port : Word) : TKSSocket;
  end;

  TKSUDPMessage = class(TObject)
  private
    FAddr    :  TSockAddr;
    FMessage: string;
    function    GetIP: string;
    function    GetPort: Word;
    procedure   SetIP(const Value: string);
    procedure   SetPort(const Value: Word);
  public
    constructor Create;
    property    Message : string read FMessage write FMessage;
    property    IP : string read GetIP write SetIP;
    property    Port : Word read GetPort write SetPort;
  end;

  TKSUDPSocket = class
  private
    FPort: Word;
    FSocket : TSOCKET;
    FAddr : TSockAddr;
    FPeerPort: Integer;
    FPeerIP: string;
    FMaxMessageLength: LongWord;
  public
    // 创建套接字，绑定到指定的端口
    constructor Create(APort : Word=0; ABind : Boolean=True);
    destructor  Destroy; override;
    // 设置需要通讯的目的地址，方便使用Send
    procedure   SetPeer(const ToIP : string; ToPort : Word);
    // 向SetPeer设定的目的地址发送消息，返回实际发送的字节数。
    function    Send(Buffer : Pointer; Count : Longword) : Integer; overload;
    // 向指定的目的地址发送消息，地址由ToIP,ToPort指定，返回实际发送的字节数。
    function    SendTo(const ToIP : string; ToPort : Word; Buffer : Pointer; Count : Longword) : Integer; overload;
    // 向指定的目的地址发送消息，地址由ToAddr指定，返回实际发送的字节数。
    function    SendTo(var ToAddr : TSockAddr; Buffer : Pointer; Count : Longword) : Integer; overload;
    // 检查是否有数据到达,TimeOut的单位是毫秒
    function    IsDataArrived(TimeOut : LongWord) : Boolean;
    // 阻塞方式接收数据，返回接收到的字节数
    function    Receive(Buffer : Pointer; MaxCount : Longword) : Integer; overload;
    // 阻塞方式接收数据，返回接收到的字节数。FromAddr返回消息的来源地址
    function    Receive(Buffer : Pointer; MaxCount : Longword; var FromAddr : TSockAddr) : Integer; overload;
    // 发送字符串消息，目的地址已经由SetPeer设置好了
    function    SendMessage(const Msg : string) : Integer;
    // 接收字符串消息，MaxLength代表最大的字符串长度
    function    ReceiveMessage(MaxLength : Integer=DefaultMaxLength) : string;
    // 发送一个字符串消息，目的地址和消息由MsgObj对象指定
    procedure   Send(MsgObj : TKSUDPMessage); overload;
    // 返回接收到的消息，消息和来源地址保存到MsgObj对象里面。
    procedure   Receive(MsgObj : TKSUDPMessage); overload;
    // 使得可以广播消息
    procedure   EnableBroadcast;
    // 获得最大的消息大小
    function    GetMaxPackageSize : Integer;
    // 广播消息
    function    Broadcast(ToPort : Word; Buffer : Pointer; Count : Longword) : Integer;
    property    Port : Word read FPort;
    property    Socket : TSOCKET read FSocket;
    property    PeerIP : string read FPeerIP;
    property    PeerPort : Integer read FPeerPort;
    property    MaxMessageLength : LongWord read FMaxMessageLength write FMaxMessageLength;
  end;

  TKSTCPClientSocket = class
  public

  end;

  TKSTCPServerThread = class;

  TKSAcceptTCPClientEvent = procedure (Sender : TKSTCPServerThread; ClientSocket : TSocket) of object;
  {
    <Class>TKSTCPServerThread
    <What>一个简单的侦听指定端口的TCP服务器线程。在创建的时候线程处于暂停状态。
    当一个来自客户端的连接以后，在该线程里面触发OnAcceptClient事件。可以在该事件响应里面创建线程完成服务。
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TKSTCPServerThread = class(TThread)
  private
    FPort: Word;
    FSocket :   TSOCKET;
    FOnAcceptClient: TKSAcceptTCPClientEvent;
  protected
    procedure   Execute; override;
  public
    constructor Create(APort : Word);
    destructor  Destroy; override;
    procedure   Start;
    procedure   Stop;
    property    Port : Word read FPort;
    property    OnAcceptClient : TKSAcceptTCPClientEvent read FOnAcceptClient write FOnAcceptClient;
  end;

  IKSSocketStream = interface
    function    Receive(Buffer : PChar; BufferLen : Integer) : Integer;
    procedure   Send(Buffer : PChar; BufferLen : Integer);
    procedure   Close;
  end;

  TKSSocketStream = class(TInterfacedObject, IKSSocketStream)
  private
    FSocket: TSocket;
    FAutoClose : Boolean;
  public
    constructor Create(ASocket : TSocket; aAutoClose : Boolean=True);
    destructor  Destroy;override;
    function    Receive(Buffer : PChar; BufferLen : Integer) : Integer;
    procedure   Send(Buffer : PChar; BufferLen : Integer);
    procedure   Close;
    property    Socket : TSocket read FSocket;
    property    AutoClose : Boolean read FAutoClose;
  end;

type
  {
    <Class>TKSReceiveThread
    <What>
    This thread is for receive data from the socket-stream.
    Program do the following :
    1. create a instance TKSReceiveThread
    2. set a thread-safed event handler for OnReceive.
    3. the thread-safed event handler may copy the received data to a queue
        and notify other thread to handle this
    4. call "resume" method to start the thread.

    How to manually stop the thread: close the socket stream.

    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TKSReceiveThread = class(TThread)
  private
    FStream : IKSSocketStream;
    FBuffer : PChar;
    FReceiveLength: Integer;
    FBufferSize: Integer;
    FOnReceive: TNotifyEvent;
  protected
    procedure   Execute; override;
  public
    constructor Create(AStream : IKSSocketStream; ABufferSize : Integer=1024);
    destructor  Destroy;override;
    property    Buffer : PChar read FBuffer;
    property    ReceiveLength : Integer read FReceiveLength;
    property    BufferSize : Integer read FBufferSize;
    property    OnReceive : TNotifyEvent read FOnReceive write FOnReceive;
    property    Stream : IKSSocketStream read FStream;
  end;

resourcestring
  SSendOutOfLength = '发送数据的长度超过允许的范围';
  sWindowsSocketError = 'Windows socket error: %s (%d), on API ''%s''';

implementation

uses Registry, LogFile;

{
function GetMACAddr : string;
const
  MaxLength = 6;
var
  reg : TRegistry;
  Buffer : array[0..MaxLength-1] of char;
  TextBuffer : array[0..MaxLength*2] of char;
  count : integer;
begin
  reg := TRegistry.Create(KEY_READ);
  try
    reg.RootKey := HKEY_LOCAL_MACHINE;
    reg.OpenKeyReadOnly('\Software\Description\Microsoft\Rpc\UuidTemporaryData');
    fillChar(Buffer,MaxLength,0);
    fillChar(TextBuffer,MaxLength*2+1,0);
    count := reg.ReadBinaryData('NetworkAddress',Buffer,MaxLength);
    assert(count=MaxLength);
    BinToHex(Buffer,TextBuffer,count);
    Result := TextBuffer;
  finally
    reg.free;
  end;
end;
}

(*
function GetMACAddr : string;
var
  Ncb : TNCB ;
  uRetCode : Char;
  lenum : TLANAENUM;
  I, Len : Integer;
  Adapter : TAdapter;
begin
  Result := '';

  FillChar(Ncb, sizeof(Ncb), 0);
  Ncb.ncb_command := Char(NCBENUM);
  Ncb.ncb_buffer := @lenum;
  Ncb.ncb_length := SizeOf(lenum);
  {uRetCode := }Netbios(@Ncb);
  Len := Byte(lenum.length);

  for I:=0 to Len do
  begin
    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBRESET);
    Ncb.ncb_lana_num := lenum.lana[i];

    {uRetCode := }Netbios(@Ncb);

    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBASTAT);
    Ncb.ncb_lana_num := lenum.lana[i];

    strcopy(PChar(@Ncb.ncb_callname),'*               ' );
    Ncb.ncb_buffer := @Adapter;
    Ncb.ncb_length := sizeof(Adapter);

    uRetCode := Netbios(@Ncb);

    if (Byte(uRetCode)= 0) then
    begin
      Result := Format('%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x',
          [
            Byte(Adapter.adapt.adapter_address[0]),
            Byte(Adapter.adapt.adapter_address[1]),
            Byte(Adapter.adapt.adapter_address[2]),
            Byte(Adapter.adapt.adapter_address[3]),
            Byte(Adapter.adapt.adapter_address[4]),
            Byte(Adapter.adapt.adapter_address[5])
          ]);
      Break;
    end;
  end;
end;
*)

function GetMACAddr : string;
{
var
  Ncb : TNCB ;
  uRetCode : Char;
  I : Integer;
  Adapter : TAdapter;
begin
  Result := '';

  for I:=0 to 255 do
  begin
    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBRESET);
    Ncb.ncb_lana_num := Char(I);

    Netbios(@Ncb);

    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBASTAT);
    Ncb.ncb_lana_num := Char(I);

    strcopy(PChar(@Ncb.ncb_callname),'*               ' );
    Ncb.ncb_buffer := @Adapter;
    Ncb.ncb_length := sizeof(Adapter);

    uRetCode := Netbios(@Ncb);

    if (Byte(uRetCode)= 0) then
    begin
      Result := Format('%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x',
          [
            Byte(Adapter.adapt.adapter_address[0]),
            Byte(Adapter.adapt.adapter_address[1]),
            Byte(Adapter.adapt.adapter_address[2]),
            Byte(Adapter.adapt.adapter_address[3]),
            Byte(Adapter.adapt.adapter_address[4]),
            Byte(Adapter.adapt.adapter_address[5])
          ]);
      Break;
    end;
  end;
end;
}
var
  AdapterAddress : Int64;
  AdapterAddressBytes : array[0..5] of Byte;
begin
  AdapterAddress := GetMACAddrInt64;
  Move(AdapterAddress,AdapterAddressBytes,SizeOf(AdapterAddressBytes));
  Result := Format('%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x',
          [
            (AdapterAddressBytes[0]),
            (AdapterAddressBytes[1]),
            (AdapterAddressBytes[2]),
            (AdapterAddressBytes[3]),
            (AdapterAddressBytes[4]),
            (AdapterAddressBytes[5])
          ]);
end;

function GetMACAddrInt64 : Int64;
var
  Ncb : TNCB ;
  uRetCode : Char;
  I : Integer;
  Adapter : TAdapter;
begin
  Result := 0;

  for I:=0 to 255 do
  begin
    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBRESET);
    Ncb.ncb_lana_num := Char(I);

    Netbios(@Ncb);

    FillChar(Ncb, sizeof(Ncb), 0);
    Ncb.ncb_command := Char(NCBASTAT);
    Ncb.ncb_lana_num := Char(I);

    strcopy(PChar(@Ncb.ncb_callname),'*               ' );
    Ncb.ncb_buffer := @Adapter;
    Ncb.ncb_length := sizeof(Adapter);

    uRetCode := Netbios(@Ncb);

    if (Byte(uRetCode)= 0) then
    begin
      Result := 0;
      Move(Adapter.adapt.adapter_address,Result,SizeOf(Adapter.adapt.adapter_address));
      Break;
    end;
  end;
end;

procedure SocketError(ErrorCode : Integer; const Msg : string);
begin
  if ErrorCode=0 then
    ErrorCode:=WSAGetLastError;
  raise EKSSocketError.CreateResFmt(@sWindowsSocketError,
      [SysErrorMessage(ErrorCode), ErrorCode, Msg]);
end;

procedure CheckSocketCall(ReturnCode : Integer; const Msg : string);
begin
  if ReturnCode=SOCKET_ERROR then
    SocketError(0,Msg);
end;

procedure CheckValidSocket(Socket : TSocket; const Msg : string='');
begin
  if Socket=INVALID_SOCKET then
    SocketError(0,Msg);
end;

procedure Startup;
var
  ErrorCode: Integer;
  WSAData : TWSAData;
begin
  ErrorCode := WSAStartup($0101, WSAData);
  if ErrorCode <> 0 then
    SocketError(ErrorCode, 'WSAStartup');
end;

procedure Cleanup;
var
  ErrorCode: Integer;
begin
  ErrorCode := WSACleanup;
  if ErrorCode <> 0 then
    SocketError(ErrorCode, 'WSACleanup');
end;

{ TKSUDPSocket }

constructor TKSUDPSocket.Create(APort: Word; ABind : Boolean);
var
  Addr : TSockAddr;
begin
  FPort := APort;
  FSocket := WinSock.socket(AF_INET, SOCK_DGRAM	, IPPROTO_IP);
  if FSocket=INVALID_SOCKET then
    SocketError(0, 'socket');
  if ABind then
  begin
    with Addr do
    begin
      sin_family := AF_INET;
      sin_port := htons(FPort);
      sin_addr.S_addr  := INADDR_ANY;
      fillchar(sin_zero,sizeof(sin_zero),0);
    end;
    CheckSocketCall(
      WinSock.bind(FSocket,Addr,Sizeof(Addr)),
      'bind');
  end;
  FMaxMessageLength := GetMaxPackageSize;
  if FMaxMessageLength>DefaultMaxLength then
    FMaxMessageLength:=DefaultMaxLength;
end;

destructor TKSUDPSocket.Destroy;
begin
  WinSock.closesocket(FSocket);
  inherited;
end;

function TKSUDPSocket.IsDataArrived(TimeOut : LongWord): Boolean;
var
  FDSet: TFDSet;
  TimeVal: TTimeVal;
  I : Integer;
begin
  FD_ZERO(FDSet);
  FD_SET(FSocket, FDSet);
  TimeVal.tv_sec := TimeOut div 1000;
  TimeVal.tv_usec := TimeOut mod 1000;
  I := WinSock.select(0, @FDSet, nil, nil, @TimeVal);
  Result := I>0;
  CheckSocketCall(I,'select');
end;

function TKSUDPSocket.Receive(Buffer: Pointer;
  MaxCount: Longword): Integer;
var
  Addr : TSockAddr;
begin
  Result := Receive(Buffer,MaxCount, Addr);
end;

function TKSUDPSocket.Receive(Buffer: Pointer; MaxCount: Longword;
  var FromAddr: TSockAddr): Integer;
var
  FromSize : Integer;
begin
  FromSize := SizeOf(FromAddr);
  Result := WinSock.recvfrom(FSocket,Buffer^,MaxCount, 0, FromAddr,FromSize);
  CheckSocketCall(Result,'recvfrom');
end;

function TKSUDPSocket.ReceiveMessage(MaxLength: Integer): string;
var
  Len : Integer;
begin
  SetLength(Result,MaxLength);
  Len := Receive(PChar(Result),MaxLength);
  SetLength(Result,Len);
end;

function TKSUDPSocket.Send(Buffer: Pointer; Count: Longword): Integer;
begin
  Result := SendTo(FAddr, Buffer, Count);
end;

function TKSUDPSocket.SendTo(const ToIP: string; ToPort: Word;
  Buffer: Pointer; Count: Longword): Integer;
var
  ToAddr: TSockAddr;
begin
  with ToAddr do
  begin
    sin_family := AF_INET;
    sin_port := htons(ToPort);
    sin_addr.S_addr  := inet_addr(PChar(ToIP));
    Fillchar(sin_zero,sizeof(sin_zero),0);
  end;
  Result := SendTo(ToAddr, Buffer, Count);
end;

function TKSUDPSocket.SendMessage(const Msg: string): Integer;
begin
  Result := Send(PChar(Msg),Length(Msg));
end;

function TKSUDPSocket.SendTo(var ToAddr: TSockAddr; Buffer: Pointer;
  Count: Longword): Integer;
begin
  Result := WinSock.sendto(FSocket,
          Buffer^,
          Count,
          0,
          ToAddr,
          Sizeof(ToAddr));
  CheckSocketCall(Result, 'sendto');
end;

procedure TKSUDPSocket.SetPeer(const ToIP: string; ToPort: Word);
begin
  FPeerIP := ToIP;
  FPeerPort := ToPort;
  with FAddr do
  begin
    sin_family := AF_INET;
    sin_port := htons(ToPort);
    sin_addr.S_addr  := inet_addr(PChar(ToIP));
    Fillchar(sin_zero,sizeof(sin_zero),0);
  end;
end;

procedure TKSUDPSocket.Receive(MsgObj: TKSUDPMessage);
var
  Len : Integer;
begin
  SetLength(MsgObj.FMessage,MaxMessageLength);
  Len := Receive(PChar(MsgObj.FMessage),MaxMessageLength,MsgObj.FAddr);
  SetLength(MsgObj.FMessage,Len);
end;

procedure TKSUDPSocket.Send(MsgObj: TKSUDPMessage);
var
  Len1,Len2 : Integer;
begin
  Len1 := Length(MsgObj.FMessage);
  Len2 := SendTo(MsgObj.FAddr,PChar(MsgObj.FMessage),Len1);
  if Len2<Len1 then
    raise EKSSocketError.Create(SSendOutOfLength);
end;

procedure TKSUDPSocket.EnableBroadcast;
var
  EnableFlag : integer;
begin
  EnableFlag := 1;
  CheckSocketCall(
    WinSock.setsockopt(FSocket,SOL_SOCKET,SO_BROADCAST,@EnableFlag,sizeof(EnableFlag)),
    'setsockopt');
end;

const
  SO_MAX_MSG_SIZE =  $2003;

function TKSUDPSocket.GetMaxPackageSize: Integer;
var
  ASize : Integer;
begin
  ASize := SizeOf(Result);
  CheckSocketCall(
    WinSock.getsockopt(FSocket,SOL_SOCKET,SO_MAX_MSG_SIZE,PChar(@Result), ASize),
    'getsockopt'
    );
end;

function TKSUDPSocket.Broadcast(ToPort: Word; Buffer: Pointer;
  Count: Longword): Integer;
var
  ToAddr: TSockAddr;
begin
  with ToAddr do
  begin
    sin_family := AF_INET;
    sin_port := htons(ToPort);
    //LongWord(sin_addr.S_addr) := INADDR_BROADCAST;
    sin_addr.S_addr := LongInt(INADDR_BROADCAST);
    Fillchar(sin_zero,sizeof(sin_zero),0);
  end;
  Result := SendTo(ToAddr, Buffer, Count);
end;

{ TKSUDPMessage }

constructor TKSUDPMessage.Create;
begin
  with FAddr do
  begin
    sin_family := AF_INET;
    sin_port := WinSock.htons(0);
    sin_addr.S_addr := INADDR_ANY;
    fillchar(sin_zero,sizeof(sin_zero),0);
  end;
end;

function TKSUDPMessage.GetIP: string;
begin
  Result := WinSock.inet_ntoa(FAddr.sin_addr);
end;

function TKSUDPMessage.GetPort: Word;
begin
  Result := WinSock.ntohs(FAddr.sin_Port);
end;

procedure TKSUDPMessage.SetIP(const Value: string);
begin
  FAddr.sin_addr.S_addr := WinSock.inet_addr(PChar(Value));
end;

procedure TKSUDPMessage.SetPort(const Value: Word);
begin
  FAddr.sin_Port := WinSock.htons(Value);
end;

{ TKSTCPServerThread }

constructor TKSTCPServerThread.Create(APort: Word);
var
  Addr : TSockAddr;
begin
  inherited Create(True);
  FPort := APort;
  FSocket := WinSock.socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if FSocket=INVALID_SOCKET then
    SocketError(0, 'socket');
  with Addr do
  begin
    sin_family := AF_INET;
    sin_port := htons(FPort);
    sin_addr.S_addr  := INADDR_ANY;
    fillchar(sin_zero,sizeof(sin_zero),0);
  end;
  CheckSocketCall(
    WinSock.bind(FSocket,Addr,Sizeof(Addr)),
    'bind');
end;

destructor TKSTCPServerThread.Destroy;
begin
  Stop;
  inherited;
end;

procedure TKSTCPServerThread.Execute;
var
  FDSet: TFDSet;
  TimeVal: TTimeVal;
  I : Integer;
  ClientSocket : TSocket;
  FromAddr: TSockAddr;
  FromSize : Integer;
begin
  try
    WinSock.listen(FSocket,SOMAXCONN);
    while not Terminated do
    begin
      FD_ZERO(FDSet);
      FD_SET(FSocket, FDSet);
      TimeVal.tv_sec := 1;
      TimeVal.tv_usec := 0;
      I := WinSock.select(0, @FDSet, nil, nil, @TimeVal);
      if (I>0) and not Terminated then
      begin
        FromSize := SizeOf(FromAddr);
        ClientSocket := WinSock.accept(FSocket,@FromAddr,@FromSize);
        if FSocket=INVALID_SOCKET then
          SocketError(0, 'accept');
        if Assigned(FOnAcceptClient) then
          FOnAcceptClient(Self,ClientSocket) else
          WinSock.closesocket(ClientSocket);
      end;
    end;
  except
    //WriteException;
  end;
end;

procedure TKSTCPServerThread.Start;
begin
  Resume;
end;

procedure TKSTCPServerThread.Stop;
begin
  if FSocket<>0 then
  begin
    WinSock.closesocket(FSocket);
    FSocket := 0;
  end;
  Terminate;
  WaitFor;
end;

{ TKSSocketStream }

constructor TKSSocketStream.Create(ASocket: TSocket; aAutoClose : Boolean);
begin
  inherited Create;
  FSocket := ASocket;
  FAutoClose := aAutoClose;
end;

destructor TKSSocketStream.Destroy;
begin
  if FAutoClose then
    Close;
  inherited;
end;

function TKSSocketStream.Receive(Buffer : PChar; BufferLen: Integer): Integer;
begin
  Result := WinSock.recv(FSocket, Buffer^, BufferLen, 0);
  CheckSocketCall(Result, 'recv');
end;

procedure TKSSocketStream.Send(Buffer : PChar; BufferLen: Integer);
var
  SendBuffer : PChar;
  SendLen : Integer;
begin
  SendBuffer := Buffer;
  while BufferLen>0 do
  begin
    SendLen := WinSock.send(FSocket, SendBuffer^, BufferLen, 0);
    CheckSocketCall(SendLen, 'send');
    Dec(BufferLen, SendLen);
    Inc(SendBuffer, SendLen);
  end;
end;

procedure TKSSocketStream.Close;
begin
  if FSocket<>INVALID_SOCKET then
    WinSock.closesocket(FSocket);
  FSocket := INVALID_SOCKET;
end;


{ TKSReceiveThread }

constructor TKSReceiveThread.Create(AStream: IKSSocketStream; ABufferSize : Integer);
begin
  inherited Create(True);
  FStream := AStream;
  FBufferSize := ABufferSize;
  GetMem(FBuffer, FBufferSize);
end;

destructor TKSReceiveThread.Destroy;
begin
  FreeMem(FBuffer);
  inherited;
end;

procedure TKSReceiveThread.Execute;
begin
  try
    while not Terminated do
    begin
      FReceiveLength := FStream.Receive(FBuffer,FBufferSize);
      if FReceiveLength=0 then
        Break;
      if Assigned(FOnReceive) then
        OnReceive(Self);
    end;
  except
    WriteException;
  end;
end;

function  GetLocalName : string;
var
  name: array[0..255] of char;
begin
  Result := '';
  if gethostname(name, sizeof(name)) = 0 then
    Result := name;
end;

function  GetLocalIp : LongWord;
var
  hn : string;
  {$ifdef VCL60_UP }
  temp : Integer;
  {$else}
  temp : LongWord;
  {$endif}
  h : PHostEnt;
begin
  Result := 0;
  hn := GetLocalName;
  if hn <> '' then
  begin
    if hn[1] in ['0'..'9'] then
    begin
      temp := inet_addr(pchar(hn));
      if temp<>INADDR_NONE then
      begin
        Result := temp;
        Exit;
      end;
    end;
    h := gethostbyname(pchar(hn));
    if h <> nil then
      Result := PLongWord(h^.h_addr^)^;
  end;
end;

function  GetLocalIpAddr : string;
begin
  Result := IpToString(GetLocalIp);
end;

function  IpToString(Ip : LongWord) : string;
var
  addr : TInAddr;
begin
  addr.S_addr := Ip;
  Result := string(PChar(inet_ntoa(addr)));
end;

function  StringToIp(const IpAddr : string) : LongWord;
begin
  Result := inet_addr(PChar(IpAddr));
end;

{ TKSSocket }

constructor TKSSocket.Create(ASocket: TSOCKET);
begin
  FSocket := ASocket;
end;

destructor TKSSocket.Destroy;
begin
  Close;
  inherited;
end;

procedure TKSSocket.Close;
begin
  if FSocket<>0 then
  begin
    WinSock.closesocket(FSocket);
    FSocket := 0;
  end;
end;

function TKSSocket.Send(Buffer: Pointer; Count: Longword): Integer;
begin
  Result := WinSock.Send(FSocket, Buffer^, Count, 0);
  CheckSocketCall(Result,'send');
end;

function TKSSocket.Receive(Buffer: Pointer; MaxCount: Longword): Integer;
begin
  Result := WinSock.recv(FSocket, Buffer^, MaxCount, 0);
  CheckSocketCall(Result,'recv');
end;

function TKSSocket.IsDataArrived(TimeOut: LongWord): Boolean;
var
  FDSet: TFDSet;
  TimeVal: TTimeVal;
  I : Integer;
begin
  FD_ZERO(FDSet);
  FD_SET(FSocket, FDSet);
  TimeVal.tv_sec := TimeOut div 1000;
  TimeVal.tv_usec := TimeOut mod 1000;
  I := WinSock.select(0, @FDSet, nil, nil, @TimeVal);
  Result := I>0;
  CheckSocketCall(I,'select');
end;

class function TKSSocket.CreateTCPClient(const IP: string;
  Port: Word): TKSSocket;
var
  Socket : TSocket;
  Addr : TSockAddr;
begin
  Socket := WinSock.socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if Socket=INVALID_SOCKET then
    SocketError(0, 'socket');
  Result := TKSSocket.Create(Socket);
  try
    with Addr do
    begin
      sin_family := AF_INET;
      sin_port := htons(Port);
      sin_addr.S_addr  := inet_addr(PChar(IP));;
      fillchar(sin_zero,sizeof(sin_zero),0);
    end;
    CheckSocketCall(
      WinSock.connect(Socket,Addr,Sizeof(Addr)),
      'bind');
  except
    Result.Free;
    raise;
  end;
end;

initialization
  Startup;

finalization
  Cleanup;

end.
