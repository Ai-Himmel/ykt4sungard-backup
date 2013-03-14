unit UKSBaseThread;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit> TraderMSThreads
   <What> 线程，队列类
   <Written By> Zhu pengfei (朱朋飞)
   <History>
**********************************************}

{$Define SwitchNoRevPush}   //用来区别接收推送的数据集是否需要切换。
                            // SwitchNoRevPush : 只切换不接收推送的数据集。
   { DONE -o朱朋飞 -csystem :
还有具体的，和UI线程显示有关的东西。初步建议是全部用消息机制
来进行处理。 }
interface

uses
  Classes, contnrs, syncobjs, SysUtils, KCDataPack, Windows, KCDataAccess, DRTPSvrAPI,
  TraderMSConsts, ExtCtrls;

type
  //发送包的结构。
  ToSendPkgBuf = array [0..SendPackageSize] of byte;
  PToSendPkgBuf = ^ToSendPkgBuf;

  //发送包的类型。
  TPackageType = (ptFirst,ptMid,ptLast);

  //操作员权限
  TOpratorPower =(opPart,opAll,opNoAny);

  //连接的状态。
  TConnect_Status = (cnsNormal,cnsSvrDisConnect,cnsCmnDisConnect);

  //队列名的内容 长度为 TSTCookie.queuename: array[0..33-1] of Char;  {= 队列名 }
  TQueuename = packed record
    QueueNameStr : array [0..28 - 1] of Char;
    {
    CreateTplime  : TDateTime;  //hh:nn:ss char[8]
    ProcessID   : Cardinal;   //char[10]
    QueSerialNO : Cardinal;   //char[10]
    }
    Seperator   : Char;       //一定是 #0。
    PackageNO   : Integer;
  end;

  TCustomNO = string;

//以下是基类（业务无关）。

type
  //以下是基类（业务无关）。

  EDesignForQuitMulInheritedException = class(Exception);


  TSemaphore = class
  private
    FHandle: THandle;
    FLastError: Integer;
  public
    constructor Create(IniCount, MaxCount : Integer; Name : string);
    destructor Destroy; override;
    property LastError: Integer read FLastError;
    property Handle: THandle read FHandle;
    function WaitFor(Timeout: DWORD): TWaitResult;
    function SelfReleaseSemaphore(Count : Integer) : Integer;
  published

  end;


  TThreadToDoMethod = procedure(Sender : TObject; AOperatedObj : TObject = nil);

  TDoSomeThingThread = class(TThread)
  private
    FThreadToDoMethod : TThreadToDoMethod;
    FSemaphore : TSemaphore;
    FSenderObj : TObject;
    FOperatedObj : TObject;
  protected
    procedure Execute; override;
  public
    constructor Create(ThreadToDoMethod : TThreadToDoMethod; SenderObj : TObject;
      SemaphoreToSingal : TSemaphore; OperatedObj : TObject=nil); reintroduce;
    destructor Destroy; override;
  end;


  TReceivedMessage = class;

  //线程基类
  TMSBaseThread = class(TThread)
  private
    { Private declarations }
    FEvent: TEvent;
    FOwnedEvent : Boolean;
    FHasEndCricle : Boolean;
  protected
    procedure SetOtherEventToClose; virtual;
    procedure BeforeInternalExecute; virtual;
    //procedure AfterInternalExecute; virtual;
    procedure InternalExecute; virtual;
    procedure Execute; override;
  public
    property  Event : TEvent read FEvent;
    constructor Create(EventManualReset : Boolean; SelfEvent : TEvent = nil);
    procedure Close; virtual;
    destructor  Destroy; override;
  end;

  //需要等待别人激活的线程
  TMSWaitForOtherThd = class(TMSBaseThread)
  protected
    FNameOfMsgsToPop : string;

    procedure PopMsgToExec;
    procedure InternalExecute; override;
    procedure ExcuteRvdMsg(RevPushedData : TReceivedMessage); virtual; abstract;
  public
    constructor Create(NameOfMsgsToPop : string; SelfEvent : TEvent = nil);
  end;

  //通用共享队列消息。
  TReceivedMessage = class
  private
    FPData: PByte;
    FPUnPackData : PByte;
    FDataSize: Integer;
    FHavePacked: Boolean;
    FPCPackHead: PSTDataHead;
    FPCPackBody: PSTPack;
    FAppHdl: TAPPHANDLE;
    FCustNO: string;
  public
    constructor Create(PBuffer : PByte; NeedToUnPack : Boolean = False;
      Size : Integer = (SizeOf(TSTDataHead) + Sizeof(TSTPack)));
    destructor  Destroy; override;

    property Head : PSTDataHead read FPCPackHead;
    property Body : PSTPack read FPCPackBody;
    property HaveUnPacked : Boolean read FHavePacked;
    property PData : PByte read FPData;
    property PUnPackData : PByte read FPUnPackData;
    property PBody : PSTPack read FPCPackBody;
    property DataSize : Integer read FDataSize write FDataSize;
    property AppHdl : TAPPHANDLE read FAppHdl write FAppHdl;
    property CustNO : string read FCustNO write FCustNO;
  end;
  {
  TUnPackMessage = class(TReceivedMessage)
  private
    FPCPackHead: PSTDataHead;
    FPCPackBody: PSTPack;
  public
    constructor Create(PBuffer : PByte; IsPacked : Boolean;
      Size : Integer = (SizeOf(TSTDataHead) + Sizeof(TSTPack)));
    function Head : TSTDataHead;
    function Body : TSTPack;
  end;
  }
  TMessagesList = class;

  TMessages = class
  private
    FName: string;
  public
    constructor Create(CallName : string; MessagesList : TMessagesList);
    {$IFDEF Debug}
    destructor Destroy; override;
    {$ENDIF}
    property    Name : string read FName;
  end;

  TCommanMessages = class(TMessages)
  private
    FWinHandle: LongWord;
    FWinMessage: LongWord;
    FQueue : TObjectList;
    FLock : TCriticalSection;
  public
    constructor Create(AWinHandle, AWinMessage : LongWord; CallName : string;
      MessagesList : TMessagesList);
    destructor  Destroy;override;
    procedure   Clear;
    function    Count : Integer;
    procedure   Lock;
    procedure   UnLock;
    property    WinHandle : LongWord read FWinHandle;
    property    WinMessage : LongWord read FWinMessage;
  end;

  //和金仕达通讯平台对应的共享队列。
  TReceivedMessages = class(TCommanMessages)
  public
    procedure   AddMessage(AMessage : TReceivedMessage; EventToSignal : TEvent;
                           CopyObj : Boolean = False);
    function    PopMessage : TReceivedMessage;
  end;

  //一般的消息相应对象队列
  TObjMessages = class(TCommanMessages)
  public
    procedure   AddMessage(AMessage : TObject);
    function    PopMessage : TObject;
  end;

  //查询结果队列
  TQueryResultMsgs = class(TMessages)
  private
    FQueue : TList;     //查询结果打包后的队列，存放Buffer指针，Buffer
                        //大小为 SendPackageSize, 现在是 8K。
//    FMaxRec : Longword;          //每个包的最大记录数。
    //FIndexToSend: Integer;      //下一个要发送的包。
    FLastPkgSize : Integer;

    FParamBits : TSTParamBits;  //打包的包头的压缩参数。
    //FNowRecNumber : Integer;    //当前包有几条记录。
//    FRecordSize : Word;      //每条记录的大小 字节数。
    FOffSetPointer : PByte;     //要写入的记录所在包的buffer的写入地址。
    FRequestType : Integer;     //包头的请求类型
    FPopSendHdl : TAPPHANDLE;      // Pop_Send 时候的Handle.

    FLock : TCriticalSection;

    FHaveSendFirstPkg : Boolean;
    FLastCouldSendPkgNo: Integer;
    FHaveChangeLastCouldSendPkgNoEvent : TEvent;

    FHaveAddedLastRec : Boolean;
    procedure SetLastCouldSendPkgNo(const Value: Integer);
    function GetLastCouldSendPkgNo: Integer;

    procedure SendFirstPkg;
  protected
    procedure CreatePackageHead(PBuffer : PByte; PackageType : TPackageType);
    function CreateNewPackage(PackageType : TPackageType = ptLast) : PToSendPkgBuf;
    function GetCurrentPkg : PToSendPkgBuf;
    procedure ReleasePackage;
  public
    constructor Create(MessagesList : TMessagesList; ParamBits : TSTParamBits;
      RequestType : Integer; SendHandle : TAPPHANDLE);
    destructor  Destroy; override;
    procedure   AddOneRec(PRecBuffer : PByte; Size : Integer);
    procedure   SendOnePackage(IndexToSend : Integer; ShareSendList : TReceivedMessages;
      EventToSignal : TEvent; SendHandle : TAPPHANDLE);
//    function    Count : Integer;
    procedure   AddedLastRec;
    property    LastCouldSendPkgNo : Integer  read GetLastCouldSendPkgNo write SetLastCouldSendPkgNo;
      //read FLastCouldSendPkgNo write FLastCouldSendPkgNo;//
    property    PopSendHdl : TAPPHANDLE read FPopSendHdl;
    //property    IndexToSend : Integer read FIndexToSend;
  end;

  //队列列表
  TMessagesList = class
  private
    FSeriaNo: Cardinal;
    FQuenue, FViceQuenue : TObjectList;
    FLock : TCriticalSection;
    FLockFindEvent : TEvent;
    function GetFSeriaNo: Cardinal;
  public
    constructor Create;
    destructor Destroy; override;
    function  FindMessages(const MessagesName: String): TMessages;
    procedure ClearTimeOutLists(TimerInterval : Cardinal);
    procedure SetOneObjNil(Obj : TObject);

    function Add(AObject: TObject): Integer;
//    function Count : Integer;
    property SeriaNo : Cardinal read GetFSeriaNo;
  end;

  //读写资源锁。  Count>0表示有线程在使用资源。
  TResourceCounter = class
  private
    FCount : Integer;
    FLock : TCriticalSection;
    FEvent : TEvent;
    procedure SetCount(const Value: Integer);
    function GetCount: Integer;
  public
    constructor Create;
    destructor Destroy; override;
    function CanWrite : Boolean;
    procedure SetEventToCloseThread;
    property Count : Integer read GetCount write SetCount;
  end;

  //处理查询线程类
  TDoClientQueryThread = class(TMSWaitForOtherThd)
  private
    AdvEvent : TEvent;
    FCounter : TResourceCounter;
    procedure InternalExcuteRvdMsg(RevPushedData: TReceivedMessage);
  protected
    FClientParamBits : TSTParamBits;
    procedure SetOtherEventToClose; override;
    function InternalDoQuery(RevPushedData: TReceivedMessage) : TQueryResultMsgs; virtual; abstract;
    {$IFDEF BILLDISPATCHSERVER}
    procedure InternalExecute; override;
    {$ENDIF}

    procedure ExcuteRvdMsg(RevPushedData : TReceivedMessage); override;
  public
    constructor Create(NameOfMsgsToPop : string; AdvancedEvent : TEvent;
                       ShareResource : TResourceCounter; SelfEvent : TEvent);
  end;

  TThdClass = class of TDoClientQueryThread;

  TThdList = class
  private
    FQuenue : TObjectList;
    FEvent: TEvent;
  public
    constructor Create(ThdClass : TThdClass; nCount : Integer;
                       NameOfMsgsToPop : string; AdvancedEvent : TEvent;
                       ShareResource : TResourceCounter);
    destructor Destroy; override;
    function Count : Integer;
    procedure ResumeAll;
    property ShareEvent : TEvent read FEvent;
  end;


//以下是线程子类，业务相关
type
  //接受客户端的查询，有数据到达就通知服务线程。
  TRevClientRequestThd = class(TMSBaseThread)
  private
    FConnectIndex : Integer;

    FServerIp : string  ;
    FServerPort : short  ;
    FFunctionCount : WORD  ;
    FFunc : Word;

    FTimeOut: Cardinal;
  protected
    procedure BeforeInternalExecute; override;
    procedure InternalExecute; override;
  public
    constructor Create( ServerIp : string  ;
                        ServerPort : short  ;
                        FunctionCount : WORD  ;
                        Func : Word);
    procedure Close; override;
    property TimeOut : Cardinal read FTimeOut write FTimeOut;
  end;

  //服务线程，负责取客户端的实际请求，将查询请求包放进查询请求队列。
  TExecRequstDataThd = class(TMSBaseThread)
  private
    FExecClientQryThdEvent : TEvent;
  protected
    procedure InternalExecute; override;
  public
    constructor Create(EventToSingal : TEvent);
  end;

  //具体负责向 发送查询结果队列 添加要发送给客户端的数据。

  //处理客户端的查询请求，将查询结果打包，并且发送首包。或者寻找查询结果队列，
  //发送后续包。或者具体处理其它的请求类型，例如 客户端 的注册等等。 还有推送
  //的处理，也是该连接接收到的。
  TExecClientQryThd = class(TMSWaitForOtherThd)
  private
    FnBatch : Integer;
    //function RegClient(ClientObj : TOpratorInf) : Boolean;
    //procedure UnRegClient();
  protected
    Timer : TTimer;

    function ProcRevPush(RevPushedData : TReceivedMessage; TheMngWorkAreaThd : TMSWaitForOtherThd) : Boolean;

    procedure ClearTimedOutList(TimeInterval : Cardinal);
    procedure BeforeInternalExecute; override;
    procedure ExcuteRvdMsg(RevPushedData : TReceivedMessage); override;
  public
    constructor Create(NameOfMsgsToPop : string; nBatch : Integer; SelfEvent : TEvent = nil);
    destructor Destroy; override;
    procedure OnTimer(Sender : TObject);
  end;

  //发送客户端的查询结果，已经打包
  TSendQryRltThd = class(TMSWaitForOtherThd)
  protected
    procedure ExcuteRvdMsg(RevPushedData : TReceivedMessage); override;
  end;

  function GetErrorPkgMsg(Error : string; RqtType : Cardinal;
    DrtpAppHdl : TAPPHANDLE; LaterPkg : Boolean = False) : TReceivedMessage;

  function LoadEmptyPkgFromFile(DataSet : TKCDataset; FileName : string) : Boolean;

  //一些函数，用来让主框架调用。
  {
  //初始化
  procedure InitAll;
  procedure StarAllThreads;
  procedure CloseAll;
  }

var
  MessageList : TMessagesList;
//  ExecClientQryThd     : TExecClientQryThd;       //处理客户端的查询请求，将查询结果打包，并且发送首包。或者寻找查询结果队列，
  QryRstMsgList : TMessagesList;

  SendQryRltThd        : TSendQryRltThd;          //发送客户端的查询结果，已经打包

implementation

uses
  LogFile, DebugMemory, KSPROCPUSH, DRTPAPI, QH_KCDataPack, FileCtrl
  {$IFDEF TRADERMONSERVER}
    ,TraderMSThreads
  {$ENDIF}
  ;

  {
  RevClientRequestThd  : TRevClientRequestThd;    //接受客户端的查询，有数据到达就通知服务线程。
  ExecRequstDataThd    : TExecRequstDataThd;      //服务线程，负责取客户端的实际请求，将查询请求包放进查询请求队列。
  }
  
  {
  SendQryRltThd        : TSendQryRltThd;          //发送客户端的查询结果，已经打包

//  RevPushDataThd       : TRevPushDataThd;         //接收AppServer推送，将结果放入更新队列
  MngWorkAreaThd       : TMngWorkAreaThd;         //管理主数据区，将推送信息加入合适的数据区然后分发给客户端。
  }

 {
procedure InitMsgList;
begin
  TReceivedMessages.Create(0,0,MLN_QueryRequest,MessageList);
  TReceivedMessages.Create(0,0,MLN_RevPushData ,MessageList);
  TReceivedMessages.Create(0,0,MLN_PushingData ,MessageList);
  TReceivedMessages.Create(0,0,MLN_SendData    ,MessageList);
end;
  

procedure InitWorkArea;
begin

end;

procedure InitThreads;
var
  tempSvrFunctionNo : Integer;
begin
  QueryViceDataAreaThd := TQueryViceDataAreaThd.Create(SleepTimeBetweenQuery);

  tempSvrFunctionNo := dmDataSet.GetConfigSystem.ReadInteger(ccServer,ccSelf_Func,0);
  RevClientRequestThd  := TRevClientRequestThd.Create(
    dmDataSet.GetConfigSystem.ReadString(ccServer,ccServer_ServerIp,''),
    dmDataSet.GetConfigSystem.ReadInteger(ccServer,ccServer_ServerPort,0),
    dmDataSet.GetConfigSystem.ReadInteger(ccServer,ccServer_FunctionCount,0),
    tempSvrFunctionNo
    );
  ExecRequstDataThd    := TExecRequstDataThd.Create(False);
  ExecClientQryThd     := TExecClientQryThd.Create(MLN_QueryRequest);
  SendQryRltThd        := TSendQryRltThd.Create(MLN_SendData);

//  RevPushDataThd       := TRevPushDataThd.Create(dmDataSet.RevPush_nBatch,
//    dmDataSet.RevPush_strDrtpAddr,dmDataSet.RevPush_nDrtpPort,dmDataSet.RevPush_nMainFunc);
  MngWorkAreaThd       := TMngWorkAreaThd.Create(MLN_RevPushData);
  PushMsgThd           := TPushMsgThd.Create(MLN_PushingData);
end;


//原则是先创建，初始化数据区，交换队列，然后初试化线程。
procedure InitAll;
begin
  MessageList := TMessagesList.Create;
  QryRstMsgList := TMessagesList.Create;
  WorkArea := TMonSvrDataArea.Create(True);
  WriteStartProgress('正在创建队列...');
  InitMsgList;
  WriteStartProgress('正在创建数据区...');
  InitWorkArea;
  WriteStartProgress('正在创建线程...');
  InitThreads;
end;

//启动线程，重要！ 顺序不能搞错！
//原则是先启动终端处理线程，然后依次向前启动处理线程，直到数据源。结束则相反。
procedure StarAllThreads;
begin
  QueryViceDataAreaThd.Resume;  //查询副数据区线程,负责切换数据区。锁定在每个数据集合，所以可以由它负责切换。

  SendQryRltThd.Resume;         //发送客户端的查询结果，已经打包
  PushMsgThd.Resume;            //发送推送队列里面的数据，进行推送

  MngWorkAreaThd.Resume;        //管理主数据区，将推送信息加入合适的数据区然后分发给客户端。
  ExecClientQryThd.Resume;      //处理客户端的查询请求，将查询结果打包，并且发送首包。或者寻找查询结果队列，
                                //发送后续包。

  RevClientRequestThd.Resume;   //接受客户端的查询，有数据到达就通知服务线程。
  ExecRequstDataThd.Resume;     //服务线程，负责取客户端的实际请求，将查询请求包放进查询请求队列。
////  RevPushDataThd.Resume;        //接收AppServer推送，将结果放入更新队列
end;

//结束线程，重要！ 资源合理释放！
//一些阻塞等待的线程，必须保证能够结束。
procedure FreeAllThreads;
//var
//  P : PAppHandle;

  procedure CloseAndFreeThread(ThrdObj : TMSBaseThread);
  begin
    try
      if ThrdObj <> nil then
      begin
        ThrdObj.Close;
        ThrdObj.Free;
      end;
    except
      WriteLog(Format('Thread(%d : %s) Raise Except!',[ThrdObj.ThreadID,ThrdObj.ClassName]),lcException);
    end;
  end;
begin
  CloseAndFreeThread(QueryViceDataAreaThd); //查询副数据区线程,负责切换数据区。锁定在每个数据集合，所以可以由它负责切换。

//  DRTPSvrAPI.App_Close(RevClientRequestThd.FConnectIndex,P^);

  CloseAndFreeThread(ExecRequstDataThd);    //服务线程，负责取客户端的实际请求，将查询请求包放进查询请求队列。
  CloseAndFreeThread(RevClientRequestThd);  //接受客户端的查询，有数据到达就通知服务线程。
  CloseAndFreeThread(ExecClientQryThd);     //处理客户端的查询请求，将查询结果打包，并且发送首包。或者寻找查询结果队列，
                                            //发送后续包。

  CloseAndFreeThread(MngWorkAreaThd);       //管理主数据区，将推送信息加入合适的数据区然后分发给客户端。

  CloseAndFreeThread(SendQryRltThd);        //发送客户端的查询结果，已经打包
  CloseAndFreeThread(PushMsgThd);           //发送推送队列里面的数据，进行推送

//  CloseAndFreeThread(RevPushDataThd);       //接收AppServer推送，将结果放入更新队列
end;

procedure CloseAll;
begin
  //先结束线程，然后结束 消息队列，数据区。
  try
    FreeAllThreads;
  finally
    MessageList.Free;
    QryRstMsgList.Free;
    WorkArea.Free;
  end;
end;
}

function LoadEmptyPkgFromFile(DataSet : TKCDataset; FileName : string) : Boolean;
begin
  if not DirectoryExists(FileName) then
    Raise Exception.CreateFmt('DataSetFilePath: %s not exists!',[FileName]);
  DataSet.Close;
  DataSet.LoadFromFile(FileName);
  DataSet.FileOpenFlag := True;
  try
    DataSet.Active := True;
  finally
    DataSet.FileOpenFlag := False;
  end;
  Result := True;
end;

{ MSBaseThread }

procedure TMSBaseThread.Execute;
begin
  WriteLog(Format('! %s has started!',[Self.ClassName]),lcKSClientStart);
  BeforeInternalExecute;
  try
    while not Terminated do
  //    try
        InternalExecute;
        {
      Except
        On E : Exception do
        begin
          if E is EDesignForQuitMulInheritedException then WriteLog(
            Format('System Raise Exception[%s],Msg-%s',[E.ClassName,E.Message]),lcException)
          else Raise;
        end;
      end;
      }
    //AfterInternalExecute;
  finally
    FHasEndCricle := True;
    WriteLog(Format('! %s[%8.8x] has stopped!',[Self.ClassName,Integer(Self)]),lcKSClientShutDown);
  end;
end;

procedure TMSBaseThread.InternalExecute;
begin
  {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] is waiting for being Singaled!',
        [Self.ClassName,Integer(Self)]),lcThreadEvent);
  {$ENDIF}
  Event.WaitFor(INFINITE);
//  if Self.Terminated then Raise EDesignForQuitMulInheritedException.CreateFmt(
//    'Object[%s-%8.8x] need to quit mutl program!',[Self.ClassName,Integer(Self)]);
  {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] has been Singaled!',
        [Self.ClassName,Integer(Self)]),lcThreadEvent);
  {$ENDIF}
end;

procedure TMSBaseThread.BeforeInternalExecute;
begin
end;
{
procedure TMSBaseThread.AfterInternalExecute;
begin
end;
}

constructor TMSBaseThread.Create(EventManualReset : Boolean; SelfEvent : TEvent = nil);
begin
  inherited Create(True);

  FHasEndCricle := False;
  if SelfEvent = nil then
  begin
    FEvent := TEvent.Create(nil,EventManualReset,False,'');
    FOwnedEvent := True;
  end
  else begin
    FEvent := SelfEvent;
    FOwnedEvent := False;
  end;
  {$IFDEF Debug}
  LogCreate(Self);
  {$ENDIF}
end;

destructor TMSBaseThread.Destroy;
begin
  if not Terminated then Close; 
  if FOwnedEvent then FreeAndNil(FEvent);
  inherited;

  {$IFDEF Debug}
  LogDestroy(Self);
  {$ENDIF}
end;

procedure TMSBaseThread.Close;
begin
  while not FHasEndCricle do
  begin
    if not Terminated then Terminate;
    Event.SetEvent;
    SetOtherEventToClose;
  end;
  WaitFor;
end;

{ TReceivedMessages }

procedure TReceivedMessages.AddMessage(AMessage : TReceivedMessage;
  EventToSignal : TEvent; CopyObj : Boolean = False);
var
  tempMsg : TReceivedMessage;
begin
  Lock;
  try
    if CopyObj then
    begin
      if AMessage.HaveUnPacked then tempMsg := TReceivedMessage.Create(AMessage.PUnPackData)
      else tempMsg := TReceivedMessage.Create(AMessage.PData,False,AMessage.DataSize);
      tempMsg.AppHdl := AMessage.AppHdl;
      FQueue.Add(tempMsg);
    end
    else FQueue.Add(AMessage);
    {$IFDEF Debug}
    WriteLog(Format('MsgList %s have received a message : message.apphdl(%s)',
      [Self.Name, AMessage.AppHdl.buf]),lcQuenueMsg);
    {$ENDIF}
    if (WinHandle<>0) then
      PostMessage(WinHandle,WinMessage,0,0);
  finally
    UnLock;
    if EventToSignal <> nil then EventToSignal.SetEvent;
  end;
end;

function TReceivedMessages.PopMessage: TReceivedMessage;
begin
  Lock;
  try
    if FQueue.Count>0 then
    begin
      Result := TReceivedMessage(FQueue.Items[0]);
      {$IFDEF Debug}
      WriteLog(Format('MsgList %s have extracted a message : message.apphdl(%s)',
        [Self.Name, Result.AppHdl.buf]),lcQuenueMsg);
      {$ENDIF}
      FQueue.Extract(Result);
    end
    else
    begin
      Result := nil;
    end;
  finally
    UnLock;
  end;
end;

{ TReceivedMessage }
constructor TReceivedMessage.Create(PBuffer: PByte; NeedToUnPack : Boolean; Size: Integer);
var
  Data : TSTPack;
begin
  inherited Create;
  FillChar(FAppHdl.buf,SizeOf(FAppHdl.buf),0);

  FDataSize := Size;
  FHavePacked := NeedToUnPack;

  GetMem(FPData,DataSize);
  FillChar(FPData^,DataSize,0);
  if PBuffer <> nil then Move(PBuffer^,PData^,DataSize);
  FPCPackHead := PSTDataHead(PData);
  FPCPackBody := PSTPack(Integer(PData) + SizeOf(TSTDataHead));
  FPUnPackData := nil;

  if HaveUnPacked then
    FHavePacked := not(FPCPackHead.NextFlag = 1);

  if HaveUnPacked then
  begin
    GetMem(FPUnPackData,SizeOf(TSTDataHead) + Sizeof(TSTPack));
    FillChar(FPUnPackData^,DataSize,0);
    Move(PBuffer^,FPUnPackData^,DataSize);
    FPCPackHead := PSTDataHead(FPUnPackData);
    FPCPackBody := PSTPack(Integer(FPUnPackData) + SizeOf(TSTDataHead));
    KCUnPackData(Head.ParamBits,Data,PByte(FPCPackBody));
    Move(Data,FPCPackBody^,SizeOf(TSTPack));
  end;
  {$IFDEF Debug}
//  LogCreate(Self);
  {$ENDIF}
end;

destructor TReceivedMessage.Destroy;
begin
  FreeMem(FPData,DataSize);
  if HaveUnPacked then FreeMem(FPUnPackData,SizeOf(TSTDataHead) + Sizeof(TSTPack));
  inherited;

  {$IFDEF Debug}
//  LogDestroy(Self);
  {$ENDIF}
end;

{ TUnPackMessage }
{
function TUnPackMessage.Body: TSTPack;
begin
  Result := FPCPackBody^;
end;

constructor TUnPackMessage.Create(PBuffer : PByte; IsPacked : Boolean;
      Size : Integer = (SizeOf(TSTDataHead) + Sizeof(TSTPack)));
var
  Data : TSTPack;
begin
  inherited Create(PBuffer,False);
  FPCPackHead := PSTDataHead(PData);
  FPCPackBody := PSTPack(Integer(PData) + SizeOf(TSTDataHead));
  if IsPacked then
  begin
    KCUnPackData(Head.ParamBits,Data,PByte(FPCPackBody));
    Move(Data,FPCPackBody^,SizeOf(TSTPack));
  end;
end;

function TUnPackMessage.Head: TSTDataHead;
begin
  Result := FPCPackHead^;
end;
}

{ TMessagesList }

function TMessagesList.Add(AObject: TObject): Integer;
var
  I : Integer;
begin
  Result := -1;
  FLock.Enter;
  try
    for I := 0 to FQuenue.Count - 1 do
      if FQuenue[I] = nil then
      begin
        FQuenue[I] := AObject;
        Result := I;
        Break;
      end;
    if Result = -1 then Result := FQuenue.Add(AObject);
  finally
    FLock.Leave;
  end;
  {$IFDEF Debug}
  WriteLog(Format('%s(Name:%s) have added to MessageList!',
    [AObject.ClassName,TMessages(AObject).Name]),lcQuenueMsg);
  {$ENDIF}
end;

procedure TMessagesList.ClearTimeOutLists(TimerInterval: Cardinal);
var
  I : Integer;
  tempList, ViceList : TObjectList;
  ThisMM : Cardinal;

  function IsPackageTimeOut(CreatedPkgName : string) : Boolean;
  var
    CreatedMM : Cardinal;
  begin
    CreatedMM := StrToIntDef(Copy(CreatedPkgName,4,2),0);
    if ThisMM < CreatedMM then Inc(ThisMM,60);
    Result := ThisMM > (CreatedMM + TimerInterval);
  end;
begin
  tempList := nil;
  FLock.Enter;
  FLockFindEvent.ResetEvent;
  try
    ViceList := TObjectList.Create(True);
    ViceList.Clear;
    ThisMM := StrToInt(Copy(FormatDateTime('hh:nn:ss',Now),4,2));
    try
      for I := 0 to Self.FQuenue.Count - 1 do
      begin
        if FQuenue.Items[I] = nil then Continue;
        if FQuenue.Items[I] is TQueryResultMsgs then
        begin
          if not IsPackageTimeOut(TQueryResultMsgs(FQuenue.Items[I]).Name) then
          begin
            ViceList.Add(FQuenue.Items[I]);
            FQuenue.Items[I] := nil;
          end
          {$IFDEF Debug}
          else begin
            WriteLog(Format('%s[%8.8x] name(%s) has been confirmed a timeout' +
              'QueryResultMsgs, Time Limited After Creation is %d Minutes!',
              [FQuenue.Items[I].ClassName,Integer(FQuenue.Items[I]),
              TQueryResultMsgs(FQuenue.Items[I]).Name,TimerInterval]),lcException);
          end;
          {$ENDIF}
        end;
      end;
    finally
      tempList := Self.FQuenue;
      Self.FQuenue := ViceList;
    end;
  finally
    FLockFindEvent.SetEvent;
    FLock.Leave;
    {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] is ready to kill timeout QueryResultMsgs!',
      [Self.ClassName,Integer(Self)]),lcKSClientStart);
    {$ENDIF}
      {**********************************************
              Kingstar Delphi Library
         Copyright (C) Kingstar Corporation
         <Unit>
         <What>
         <Written By> Zhu pengfei (朱朋飞)
         <History>
      //Find函数返回的，由其它线程正在操作的TQueryResultMsgs，不能立即删除。其它
      //线程现在正在操作他的引用。但是如果把Find和其它的TQueryResultMsgs的具体操作
      //做成一个原子操作，则会大大影响程序的效率。但是采用这种方式，在下个清除动作
      //的时候才最终删除TQueryResultMsgs，也可能会让那些操作TQueryResultMsgs引用的
      //耗时长过清除间隔的线程产生异常。毕竟，这个可能性很小，尤其是清除间隔很大的
      //时候，因此，这样设计，还是值得的。
      **********************************************}
      {
    if FViceQuenue <> nil then
    begin
      for I := 0 to FViceQuenue.Count - 1 do
      begin
        try
          FViceQuenue[I].Free;
        except
          On E : Exception do
          begin
            WriteLog(Format('ClearTimedOutMsg, kill viceQuenue''s Msg,Raise Error:%s',[E.Message]),lcException);
          end;
        end;
        FViceQuenue[I] := nil;
      end;
      if FViceQuenue.OwnsObjects then FViceQuenue.OwnsObjects := False;
    end;
       }
    try
      FViceQuenue.Free;
//    tempList.OwnsObjects := True;
    finally
      FViceQuenue := tempList;
    end;
    {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] had killed timedout QueryResultMsgs!',
      [Self.ClassName,Integer(Self)]),lcKSClientShutDown);
    {$ENDIF}
  end;
end;

{
function TMessagesList.Count: Integer;
begin
  FLock.Enter;
  try
    Result := FQuenue.Count;
  finally
    FLock.Leave;
  end;
end;
}
constructor TMessagesList.Create;
begin
  FLock := TCriticalSection.Create;
  FLockFindEvent := TEvent.Create(nil,True,True,'');
  FQuenue := TObjectList.Create(True);
  FQuenue.Clear;
  FViceQuenue := nil;
  FSeriaNo := 0;
  {$IFDEF Debug}
  LogCreate(Self);
  {$ENDIF}
end;

destructor TMessagesList.Destroy;
begin
  FLockFindEvent.SetEvent;
  FLock.Enter;
  try
    {
    if FQuenue <> nil then
    begin
      for I := 0 to FQuenue.Count -1 do
      begin
        if FQuenue[I] <> nil then FQuenue[I].Free;
      end;
      FQuenue.OwnsObjects := False;
    end;
    if FViceQuenue <> nil then
    begin
      for I := 0 to FViceQuenue.Count -1 do
      begin
        if FViceQuenue[I] <> nil then FViceQuenue[I].Free;
      end;
      FViceQuenue.OwnsObjects := False;
    end;
    }
    FViceQuenue.Free;
    FQuenue.Free;    
  finally
    FLock.Leave;
    FLock.Free;
    FLockFindEvent.Free;
  end;
  inherited;
  {$IFDEF Debug}
  LogDestroy(Self);
  {$ENDIF}
end;

function TMessagesList.FindMessages(const MessagesName: String): TMessages;
var
  I : Integer;
  Messages : TMessages;
begin
  FLockFindEvent.WaitFor(1000);
  result:= nil;
  for I := 0 to FQuenue.Count-1 do
  begin
    if FQuenue.Items[I] = nil then Continue;
    Messages := TMessages(FQuenue.Items[i]);
    if CompareText(Messages.Name,MessagesName) = 0 then
    begin
      result:= Messages;
      Exit;
    end;
  end;
end;

function TMessagesList.GetFSeriaNo: Cardinal;
begin
  FLock.Enter;
  try
    if FSeriaNo < High(Cardinal) then Inc(FSeriaNo)
      else FSeriaNo := 0;
    Result := FSeriaNo;
  finally
    FLock.Leave;
  end;
end;

procedure TMessagesList.SetOneObjNil(Obj: TObject);
var
  I : Integer;
begin
  FLock.Enter;
  try
    I := FQuenue.IndexOf(Obj);
    if I > -1 then
    begin
      FQuenue.Items[I] := nil;
      Obj.Free;
    end;
  finally
    FLock.Leave;
  end;
end;

{ TMessages }

constructor TMessages.Create(CallName: string;
  MessagesList: TMessagesList);
begin
  inherited Create;
  FName := CallName;
  if MessagesList <> nil then MessagesList.Add(Self);
  {$IFDEF Debug}
  LogCreate(Self);
  {$ENDIF}
end;

{$IFDEF Debug}
destructor TMessages.Destroy;
begin
  inherited;
  LogDestroy(Self);
end;
{$ENDIF}

{ TQueryResultMsgs }
constructor TQueryResultMsgs.Create(MessagesList : TMessagesList;
      ParamBits : TSTParamBits; RequestType : Integer; SendHandle : TAPPHANDLE);
begin
  FLock := TCriticalSection.Create;
  FHaveChangeLastCouldSendPkgNoEvent := TEvent.Create(nil,False,False,'');
  Inherited Create(Format('%s%10d%10d',[FormatDateTime('hh:nn:ss',Now),GetCurrentProcessId,MessagesList.SeriaNo]),
    MessagesList);

  {$IFDEF Debug}
  WriteLog(Format('QueryResultMsgs(Name: %s) Created!',[Self.Name]),lcQuenueMsg);
  {$ENDIF}

  FQueue := TList.Create;
  FQueue.Clear;
//  FLastPkgSize := 0;

  Move(ParamBits,FParamBits,SizeOf(TSTParamBits));
//  FRecordSize := RecordSize;
  FRequestType := RequestType;
  FPopSendHdl := SendHandle;

  LastCouldSendPkgNo := -2;
  FHaveAddedLastRec := False;
  FHaveSendFirstPkg := False;
//  FMaxRec := (SendPackageSize - SizeOf(TSTDataHead)) div FRecordSize;
//  Assert(FMaxRec > 0,'记录太大！');

  CreateNewPackage(ptFirst);


//  WriteLog(Format('Ready to begin Query! at %d',[GetTickCount]),lcTempDebug);
//  FIndexToSend := 0;
end;

destructor TQueryResultMsgs.Destroy;
begin
  FLock.Free;
  FHaveAddedLastRec := True;
  FHaveChangeLastCouldSendPkgNoEvent.SetEvent;
  FHaveChangeLastCouldSendPkgNoEvent.Free;
  ReleasePackage;
  FreeAndNil(FQueue);
  inherited;
end;

function TQueryResultMsgs.CreateNewPackage(PackageType : TPackageType): PToSendPkgBuf;
begin
  GetMem(Result,SendPackageSize);
  FillChar(Result^,SendPackageSize,0);
  FQueue.Add(Result);

  CreatePackageHead(PByte(Result),PackageType);

  FOffSetPointer := PByte(Integer(GetCurrentPkg) + SizeOf(TSTDataHead));
  FLastPkgSize := SizeOf(TSTDataHead);

  LastCouldSendPkgNo := LastCouldSendPkgNo + 1;
end;

procedure TQueryResultMsgs.AddOneRec(PRecBuffer: PByte; Size : Integer);
//var
//  I : Cardinal;
begin
//  if PSTDataHead(GetCurrentPkg).RecCount + 1 > FMaxRec then
  if FLastPkgSize + Size > SendPackageSize then
  begin
    CreateNewPackage;
    SendFirstPkg;
    AddOneRec(PRecBuffer, Size);
  end
  else begin
    Move(PRecBuffer^,FOffSetPointer^,Size);
    Inc(FOffSetPointer,Size);
    Inc(FLastPkgSize,Size);
    PSTDataHead(GetCurrentPkg).RecCount := PSTDataHead(GetCurrentPkg).RecCount + 1;
//    I := PSTDataHead(GetCurrentPkg).RecCount;
//    Inc(I);
//    PSTDataHead(GetCurrentPkg).RecCount := I;
    //Move(I,PSTDataHead(GetCurrentPkg).RecCount,SizeOf(I));
    //Inc(PSTDataHead(GetCurrentPkg).RecCount);
  end;
end;

{
function TQueryResultMsgs.Count: Integer;
begin
  Result := FQueue.Count;
end;
}

procedure TQueryResultMsgs.SendOnePackage(IndexToSend : Integer; ShareSendList : TReceivedMessages;
   EventToSignal : TEvent; SendHandle : TAPPHANDLE);
const
  SendThreadWaitForExecThdTimeInterval = 10;//ms
var
  MessageToSend : TReceivedMessage;
  tempStr : string;
//  tempStr : string;
//  QueryListName : TQueuename;
  procedure FSendNormalPkg;
  begin
    MessageToSend := TReceivedMessage.Create(PByte(FQueue[IndexToSend]),False,{FRecordSize * FMaxRec}SendPackageSize);
    MessageToSend.AppHdl := SendHandle;
    ShareSendList.AddMessage(MessageToSend,EventToSignal);
  end;
begin
//  WriteLog(Format('IndexToSend(%d) > LastCouldSendPkgNo(%d)',[IndexToSend,LastCouldSendPkgNo]),lcException);
//  Assert(not(IndexToSend > LastCouldSendPkgNo));
//  FPopSendHdl := SendHandle;
  {
  if Count = 0 then
  begin
    FillChar(QueryListName,SizeOf(QueryListName),0);
    Move(Pchar(Self.Name)^,QueryListName,SizeOf(QueryListName));
    tempStr := Format('QryRltMsgs(Name:%s) has no one Rec!',[QueryListName.QueueNameStr]);
    WriteLog(tempStr,lcException);
    tempStr := Format('%s-查询结果集合没有记录！',[tempStr]);
    MessageToSend := UKSBaseThread.GetErrorPkgMsg(tempStr,Self.FRequestType,
      Self.PopSendHdl);
    ShareSendList.AddMessage(MessageToSend,EventToSignal);
    QryRstMsgList.SetOneObjNil(Self);
    Exit;
  end;
  }
//  WriteLog(Format('Ready to Send Pkg(%d of %d)! at %d',[IndexToSend,LastCouldSendPkgNo,GetTickCount]),lcTempDebug);
  if IndexToSend < LastCouldSendPkgNo then FSendNormalPkg
  else if IndexToSend = LastCouldSendPkgNo then
  begin
    if FHaveAddedLastRec then
    begin
      MessageToSend := TReceivedMessage.Create(PByte(FQueue[IndexToSend]),False,{FRecordSize * PSTDataHead(FQueue.Last).RecCount}FLastPkgSize);
      MessageToSend.AppHdl := SendHandle;
      ShareSendList.AddMessage(MessageToSend,EventToSignal);
      QryRstMsgList.SetOneObjNil(Self);
      {$IFDEF Debug}
  //    WriteLog(Format('%s[%8.8x]:%s is to be destroyed!',[Self.ClassName,Integer(Self),Self.Name]),lcQuenueMsg);
      {$ENDIF}
  //    FreeAndNil(Self);
      Exit;
    end
    else FSendNormalPkg;
  end
  else begin //要发送的是正在处理的包，要等待，然后递归判断。
    if FHaveAddedLastRec then
    begin
      tempStr := Format('QryRltMsgs(Name:%s) has %d Pkg,but you request a %d Pkg,Return you Error Msg!',
        [Self.Name,FQueue.Count-1,IndexToSend+1]);
      WriteLog(tempStr,lcException);
      ShareSendList.AddMessage(
        UKSBaseThread.GetErrorPkgMsg(tempStr,FRequestType,SendHandle, True),
        EventToSignal);
    end
    else begin
      FHaveChangeLastCouldSendPkgNoEvent.WaitFor(SendThreadWaitForExecThdTimeInterval);
      SendOnePackage(IndexToSend,ShareSendList,EventToSignal,SendHandle);
    end;
  end;
end;

procedure TQueryResultMsgs.ReleasePackage;
var
  I : Integer;
begin
  for I := 0 to FQueue.Count - 1 do
  begin
    if FQueue[I] <> nil then
      FreeMem(FQueue[I],SendPackageSize);
  end;
end;

function TQueryResultMsgs.GetCurrentPkg: PToSendPkgBuf;
begin
  Assert(FQueue <> nil);
  Result := FQueue.Last;
  Assert(Result <> nil);
end;

procedure TQueryResultMsgs.CreatePackageHead(PBuffer: PByte;
  PackageType: TPackageType);
var
  tempQueueName : TQueuename;
  {$IFDEF Debug}
  I : Integer;
  tempStr : string;
  {$ENDIF}
begin
  with PSTDataHead(PBuffer)^ do
  begin
    Move(FParamBits,ParamBits,Sizeof(TSTParamBits));
    {$IFDEF Debug}
    tempStr := '';
    for I := 0 to SizeOf(TSTParamBits) - 1 do tempStr := Format('%s,',[tempStr + IntToStr(ParamBits[I])]);
    WriteLog(Format('PackageParamBits: %s',[tempStr]),lcCPackDetails);
    {$ENDIF}
    RequestType := FRequestType;
    RetCode := 0;
    RecCount := 0;
    Move(PChar(Self.Name)^,tempQueueName.QueueNameStr,Length(Self.Name));
    tempQueueName.Seperator := #0;
    tempQueueName.PackageNO := FQueue.Count - 1; //本包已经加入队列。
    Move(tempQueueName,Cookie.queuename,SizeOf(tempQueueName));

    case PackageType of
      ptFirst :
        begin
          FirstFlag := 1;
          NextFlag := 0;
        end;
      ptMid   :
        begin
        end;
      ptLast  :
        begin
          FirstFlag := 0;
          NextFlag := 0;
          //将上个包的 NextFlag 置为 1。
          if FQueue.Count > 1 then
            PSTDataHead(FQueue[FQueue.Count - 2])^.NextFlag := 1;
        end;
    end;
  end;
end;

{ TRevPushDataThd }
{
procedure TRevPushDataThd.BeforeInternalExecute;
begin
  try
    RecvPush_Initialize(FnBatch);
  except
    WriteError;
  end;
  RecvPush_Start(FstrDrtpAddr,FnDrtpPort,FnMainFunc);
  WriteLog('RevPushThread have started!',lcKSClientStart);
end;

procedure TRevPushDataThd.Close;
begin
  RecvPush_Stop;
  RecvPush_Uninitialize;
  inherited;
  WriteLog('RevPushThread have closed!',lcKSClientStart);
end;

constructor TRevPushDataThd.Create(nBatch: Integer; strDrtpAddr: PChar;
  nDrtpPort, nMainFunc: Integer);
begin
  inherited Create(False);

  FnBatch       :=    nBatch;
  FstrDrtpAddr  :=    strDrtpAddr;
  FnDrtpPort    :=    nDrtpPort;
  FnMainFunc    :=    nMainFunc;

  WriteLog('RevPushThread have created!',lcKSClientStart);
{  WriteLog(Format('FnBatch=%d;FstrDrtpAddr=%s;FnDrtpPort:=%d;FnDrtpPort:=%d;',
                  [ FnBatch,FstrDrtpAddr,FnDrtpPort,FnMainFunc]),
                    lcKSClientStart);
}
{
end;

procedure TRevPushDataThd.InternalExecute;
var
  PBuffer : PByte;
  Buffer : array [0..SizeOf(TSTDataHead) + SizeOf(TSTPack) - 1] of Byte;
begin
  FillChar(Buffer,SizeOf(Buffer),0);
  PBuffer := @Buffer;
  if RecvPush_RecvPushPack(PChar(PBuffer),SizeOf(Buffer),200) > 0 then
  begin
    Move(Buffer,FRequestType,SizeOf(Integer));
    TReceivedMessages(MessageList.FindMessages(MLN_RevPushData)).AddMessage(
      TReceivedMessage.Create(PBuffer),MngWorkAreaThd.Event);
  end;
end;

procedure TRevPushDataThd.WriteError;
var
  ErrorMessage : array [0..255] of char;
  msgCode : Integer;
begin
  RecvPush_GetLastError(msgCode,ErrorMessage);
  WriteLog('RevPushThread Error : ' + Trim(ErrorMessage),lcKSClientStart);
end;
}

procedure TQueryResultMsgs.AddedLastRec;
begin
  FHaveAddedLastRec := True;
  LastCouldSendPkgNo := FQueue.Count - 1;
  SendFirstPkg;
//  WriteLog(Format('Query Completed! at %d',[GetTickCount]),lcTempDebug);
end;

procedure TQueryResultMsgs.SetLastCouldSendPkgNo(const Value: Integer);
begin
  FLock.Enter;
  try
    FLastCouldSendPkgNo := Value;
  finally
    FLock.Leave;
    FHaveChangeLastCouldSendPkgNoEvent.SetEvent;
  end;
end;

function TQueryResultMsgs.GetLastCouldSendPkgNo: Integer;
begin
  FLock.Enter;
  try
    Result := FLastCouldSendPkgNo;
  finally
    FLock.Leave;
  end;
end;

procedure TQueryResultMsgs.SendFirstPkg;
begin
  if not FHaveSendFirstPkg then
    try
      //发送首包
      SendOnePackage(0,TReceivedMessages(MessageList.FindMessages(MLN_SendData)),
        SendQryRltThd.Event,PopSendHdl)
    finally
      FHaveSendFirstPkg := True;
    end;
end;

{ TMSWaitForOtherThd }

constructor TMSWaitForOtherThd.Create(NameOfMsgsToPop: string; SelfEvent : TEvent = nil);
begin
  inherited Create(False, SelfEvent);
  FNameOfMsgsToPop := NameOfMsgsToPop;
end;

procedure TMSWaitForOtherThd.InternalExecute;
begin
  inherited;
  PopMsgToExec;
end;

procedure TMSWaitForOtherThd.PopMsgToExec;
var
  MessagesRecieved : TReceivedMessages;
  RevPushedData : TReceivedMessage;
begin
  MessagesRecieved := TReceivedMessages(MessageList.FindMessages(FNameOfMsgsToPop));
  while MessagesRecieved.Count > 0 do
  begin
    {$IFDEF Debug}
    WriteLog(Format('Thread %s[%8.8x] is ready to receive a message!',
      [Self.ClassName,Integer(Self)]),lcThreadDetails);
    {$ENDIF}
    RevPushedData := MessagesRecieved.PopMessage;
    {$IFDEF Debug}
    WriteLog(Format('Thread %s[%8.8x] have got a message : message.apphdl(%s)',
      [Self.ClassName,Integer(Self), RevPushedData.AppHdl.buf]),lcThreadDetails);
    {$ENDIF}
    try
      ExcuteRvdMsg(RevPushedData);
    finally
      FreeAndNil(RevPushedData);
    end;
  end;
end;

{ TRevClientRequestThd }

procedure TRevClientRequestThd.BeforeInternalExecute;
var
  Connect_Rlt : Boolean;
begin
  //初始化DrtpPop。准备接受数据。

  FConnectIndex := DRTPSvrAPI.App_Init;
  Assert(FConnectIndex>-1,Format('DRTPSvrAPI.App_Init Failed(%d)!',[FConnectIndex]));
  try
    Connect_Rlt := DRTPSvrAPI.App_Connect(FConnectIndex,PChar(FServerIp),FServerPort,FFunctionCount,@FFunc);
    Assert(Connect_Rlt,'DRTPSvrAPI not Connected(%d)!');
  except
    WriteLog('DRTPSvrAPI not Connected!',lcException);
    Raise;
  end;
  WriteLog(Format('DRTPSvrAPI Connected !(ServerIP:%s,Port:%d,FuncNO:%d,ConnectIndex:%d)',
    [FServerIP,FServerPort,FFunc,FConnectIndex]),lcKSClientStart);
end;

procedure TRevClientRequestThd.Close;
//var
//  P : PAppHandle;
begin
//  P := nil;
  TimeOut := INFINITE;
  Event.SetEvent;
  DRTPSvrAPI.App_Close(FConnectIndex,nil);
  WriteLog(Format('DRTPSvrAPI Destroyed !(ConnectIndex:%d)',[FConnectIndex]),lcKSClientShutDown);
  inherited;
end;

constructor TRevClientRequestThd.Create(ServerIp: string; ServerPort: short;
  FunctionCount: WORD; Func: Word);
begin
  inherited Create(False);
  FFunctionCount := FunctionCount;
  FFunc := Func;
  FServerIp := ServerIp;
  FServerPort := ServerPort;

  TimeOut := DRTPAPP_RConnectTimeRev;
end;

procedure TRevClientRequestThd.InternalExecute;
var
  ErrorMsg : array [0..200] of Char;
begin
//  WriteLog(Format('@ %s has Excuted!',[Self.ClassName]),lcDebug);
  if DRTPSvrAPI.iApp_Recv(FConnectIndex) < 0 then
  begin
    FillChar(ErrorMsg,SizeOf(ErrorMsg),0);
    DRTPSvrAPI.App_GetLastError(@ErrorMsg);
    if ErrorMsg <> '' then WriteLog(Format('DrtpSvrAPI LastError : %s',[ErrorMsg]),lcException);
    WriteLog(Format('DRTPSvrAPI.App_Recv False, Reconnect!',[]),lcException);
    if Event.WaitFor(TimeOut) = wrTimeout then
    begin
      DRTPSvrAPI.App_Close(FConnectIndex,nil);
      FConnectIndex := DRTPSvrAPI.App_Init;
      if not DRTPSvrAPI.App_Connect(FConnectIndex,PChar(FServerIp),FServerPort,
        FFunctionCount,@FFunc) then
          WriteLog(Format('DRTPSvrAPI.App_Connect False, Ready to Reconnect!',[]),lcException);
    end
    else Terminate;
  end;
  {$IFDEF Debug}
    FillChar(ErrorMsg,SizeOf(ErrorMsg),0);
    DRTPSvrAPI.App_GetLastError(@ErrorMsg);
    if ErrorMsg <> '' then WriteLog(Format('DrtpSvrAPI LastError : %s',[ErrorMsg]),lcDebug)
      else WriteLog('DrtpSvrAPI_RecV Successed!',lcDebug);
  {$ENDIF}

end;

{ TExecClientQryThd }

procedure TExecClientQryThd.BeforeInternalExecute;
begin
  KSPROCPUSH.ProcPush_InitRes;
  KSPROCPUSH.ProcPush_Init(FnBatch);
  KSPROCPUSH.ProcPush_SetControlReqTypes(High(CtrlRequestType),@CtrlRequestType);
end;

procedure TExecClientQryThd.ClearTimedOutList(TimeInterval : Cardinal);
begin
  { DONE -o朱朋飞 : 按照时间的要求来清理队列。 }
  if QryRstMsgList <> nil then QryRstMsgList.ClearTimeOutLists(TimeInterval);
end;

constructor TExecClientQryThd.Create(NameOfMsgsToPop : string; nBatch : Integer; SelfEvent : TEvent = nil);
begin
  inherited Create(NameOfMsgsToPop, SelfEvent);
  FnBatch := nBatch;
  Timer := TTimer.Create(nil);
  with Timer do
  begin
    Interval := TimeIntervalForClearQryList;
    OnTimer := Self.OnTimer;
    Enabled := True;
  end;
end;

destructor TExecClientQryThd.Destroy;
begin
  KSPROCPUSH.ProcPush_FreeRes;
  Timer.Enabled := False;
  Timer.Free;
  inherited;
end;

procedure TExecClientQryThd.ExcuteRvdMsg(RevPushedData: TReceivedMessage);
begin

end;

procedure TExecClientQryThd.OnTimer(Sender: TObject);
begin
  ClearTimedOutList(TimedOutMinutesNum);
end;

function TExecClientQryThd.ProcRevPush(RevPushedData: TReceivedMessage;
  TheMngWorkAreaThd : TMSWaitForOtherThd): Boolean;
var
  MessageToSend : TReceivedMessage;
  Buffer : ToSendPkgBuf;
  ProcPushRlt : Integer;
  AnswerFlag, CtrlFlag : Integer;
  RltMsg : array [0..128-1] of char;
begin
  { DONE -o朱朋飞 ://先判断是否是服务器的推送信息，先处理推送，然后是客户端的具体请求。
  //如果是推送，那么批次号一定是dmDataSet的批次号。  }
  Result := False;
  //推送包的后续包标记一定是0。优化程序。
  if RevPushedData.Head.NextFlag <> 0 then Exit;
  Assert(RevPushedData.PUnPackData<>nil);
  if KSPROCPUSH.ProcPush_CheckValidPushData(PChar(RevPushedData.PUnPackData)) = 0 then
  begin
    Result := True;
    FillChar(Buffer,SizeOf(Buffer),0);
    FillChar(RltMsg,SizeOf(RltMsg),0);
    ProcPushRlt := KSPROCPUSH.ProcPush_ProcPushData(PChar(RevPushedData.PUnPackData)
      ,PChar(@Buffer),AnswerFlag,CtrlFlag,@RltMsg);

    if AnswerFlag = 1 then //需要确认应答。
    begin
      MessageToSend := TReceivedMessage.Create(@Buffer,False);
      with MessageToSend do
      begin
        AppHdl := RevPushedData.AppHdl;
        DataSize := SizeOf(TSTDataHead) + KCDataPack.KCPackData(Head.ParamBits,Body^,PByte(Integer(PData) + SizeOf(TSTDataHead)));
      end;
      TReceivedMessages(MessageList.FindMessages(MLN_SendData)).AddMessage(MessageToSend,SendQryRltThd.Event);
    end;

    if ProcPushRlt <> 0 then
    begin
      WriteLog(Format('KSPROCPUSH.ProcPush_ProcPushData Failed(%d):%s',
        [ProcPushRlt,RltMsg]),lcException);
    end
    else
      TReceivedMessages(MessageList.FindMessages(MLN_RevPushData)).AddMessage(
        RevPushedData,TheMngWorkAreaThd.Event,True);
  end;
end;


{ TSendQryRltThd }

procedure TSendQryRltThd.ExcuteRvdMsg(RevPushedData: TReceivedMessage);
var
  tempAppHdl : TAPPHANDLE;
begin
  tempAppHdl := RevPushedData.AppHdl;
  if not DRTPSvrAPI.App_Send(tempAppHdl,PChar(RevPushedData.PData),
    RevPushedData.DataSize) then
      WriteLog(Format('DRTPSvrAPI.App_Send Failed(RequestType:%d)!',
        [RevPushedData.Head.RequestType]),lcException);
  {$IFDEF Debug}
  WriteLog(Format('SendQryRltThd have sent a message : message.apphdl(%s)',[tempAppHdl.buf]),lcRevSendPkgDetails);
  WriteLog(Format('RequestType :%d;',[PSTDataHead(RevPushedData.PData)^.RequestType]),lcRevSendPkgDetails); //LongWord;			// 交易编码，4字节
  WriteLog(Format('FirstFlag   :%d;',[PSTDataHead(RevPushedData.PData)^.FirstFlag  ]),lcRevSendPkgDetails); //Byte ;				// 是否第一个请求（首包请求）
  WriteLog(Format('NextFlag    :%d;',[PSTDataHead(RevPushedData.PData)^.NextFlag   ]),lcRevSendPkgDetails); //Byte ;				// 是否后续包请求
  WriteLog(Format('RecCount    :%d;',[PSTDataHead(RevPushedData.PData)^.RecCount   ]),lcRevSendPkgDetails); //LongWord;			// 本包的记录数
  WriteLog(Format('RetCode     :%d;',[PSTDataHead(RevPushedData.PData)^.RetCode    ]),lcRevSendPkgDetails); //LongWord;		  // 返回代码
  //WriteLog(Format('Addr        :%d;',[PSTDataHead(RevPushedData.PData)^.Addr       ]),lcRevSendPkgDetails); //TSTADDR;			// 请求着的地址（6个子节）
  WriteLog(Format('queuename   :%s;',[PSTDataHead(RevPushedData.PData)^.Cookie.queuename]),lcRevSendPkgDetails); //TSTCookie;
  WriteLog(Format('userdata    :%d;',[PSTDataHead(RevPushedData.PData)^.userdata   ]),lcRevSendPkgDetails); //LongWord;
  //WriteLog(Format('ParamBits   :%d;',[PSTDataHead(RevPushedData.PData)^.ParamBits  ]),lcRevSendPkgDetails); //TSTParamBits;
  {$ENDIF}
end;

{ TExecRequstDataThd }

constructor TExecRequstDataThd.Create(EventToSingal: TEvent);
begin
  inherited Create(False);
  FExecClientQryThdEvent := EventToSingal;
  Assert(FExecClientQryThdEvent <> nil,'EventToSingal Is Nil!');
end;

procedure TExecRequstDataThd.InternalExecute;
var
  tempAppHandle : TAPPHANDLE;
  Buffer : ToSendPkgBuf;
  SendSize : Integer;
  tempReceivedMsg : TReceivedMessage;
begin
  //inherited;
  FillChar(Buffer,SizeOf(Buffer),0);
  SendSize := DRTPSvrAPI.App_Pop(tempAppHandle,PChar(@Buffer),SizeOf(Buffer),20);
  if SendSize > 0 then
  begin
    tempReceivedMsg := TReceivedMessage.Create(@Buffer,True,SendSize);

    {$IFDEF Debug}
    WriteLog(Format('DRTPSvrAPI.App_Pop Have Got a Message(RequestType : %d, apphdl: %s)!',
      [tempReceivedMsg.Head.RequestType,tempAppHandle.buf]),lcRevSendPkgDetails);
    WriteLog(Format('RequestType :%d;',[tempReceivedMsg.Head.RequestType]),lcRevSendPkgDetails); //LongWord;			// 交易编码，4字节
    WriteLog(Format('FirstFlag   :%d;',[tempReceivedMsg.Head.FirstFlag  ]),lcRevSendPkgDetails); //Byte ;				// 是否第一个请求（首包请求）
    WriteLog(Format('NextFlag    :%d;',[tempReceivedMsg.Head.NextFlag   ]),lcRevSendPkgDetails); //Byte ;				// 是否后续包请求
    WriteLog(Format('RecCount    :%d;',[tempReceivedMsg.Head.RecCount   ]),lcRevSendPkgDetails); //LongWord;			// 本包的记录数
    WriteLog(Format('RetCode     :%d;',[tempReceivedMsg.Head.RetCode    ]),lcRevSendPkgDetails); //LongWord;		  // 返回代码
    //WriteLog(Format('Addr        :%d;',[tempReceivedMsg.Head.Addr       ]),lcRevSendPkgDetails); //TSTADDR;			// 请求着的地址（6个子节）
    WriteLog(Format('queuename   :%s;',[PSTDataHead(@Buffer)^.Cookie.queuename]),lcRevSendPkgDetails); //TSTCookie;
    WriteLog(Format('userdata    :%d;',[tempReceivedMsg.Head.userdata   ]),lcRevSendPkgDetails); //LongWord;
    //WriteLog(Format('ParamBits   :%d;',[tempReceivedMsg.Head.ParamBits  ]),lcRevSendPkgDetails); //TSTParamBits;

    {$ENDIF}

    tempReceivedMsg.AppHdl := tempAppHandle;
    TReceivedMessages(MessageList.FindMessages(MLN_QueryRequest)).AddMessage(
      tempReceivedMsg,FExecClientQryThdEvent);
  end;
end;

function GetErrorPkgMsg(Error : string; RqtType : Cardinal;
  DrtpAppHdl : TAPPHANDLE; LaterPkg : Boolean = False) : TReceivedMessage;
begin
  Result := TReceivedMessage.Create(nil,False);
  with Result do
  begin
    AppHdl := DrtpAppHdl;

//    FillChar(PkgHead,SizeOf(PkgHead),0);
    with Head^ do
    begin
      RequestType := RqtType;
      RetCode := 999999;
      RecCount := 1;
      if not LaterPkg then
      begin
        FirstFlag := 1;
        NextFlag := 0;
      end
      else begin
        FirstFlag := 0;
        NextFlag := 0;
      end;
      //Move(dmDataSet.SelfIP_Int,Addr,SizeOf(dmDataSet.SelfIP_Int));
    end;
//    Move(PkgHead,PData^,SizeOf(PkgHead));

//    FillChar(PkgBody,SizeOf(PkgBody),0);
    //tempAddr := RevPushedData.Head.Addr;
    //Move(tempAddr,ClientIP,SizeOf(ClientIP));
    //tempStr := Format('MonClient(%s) Registed!',[NetUtils.IPToString(ClientIP)]);
    if Pchar(Error) <> nil then Move(PChar(Error)^,Body.vsmess,Length(Error));
//    Move(PkgBody,PBody^,SizeOf(PkgBody));

    DataSize := QH_KCDataPack.AddOneDataToPackedPkg('vsmess',PData,Body^);
  end;
end;


{ TCommanMessages }

procedure TCommanMessages.Clear;
begin
  Lock;
  try
    FQueue.Clear;
  finally
    UnLock;
  end;
end;

function TCommanMessages.Count: Integer;
begin
  Lock;
  try
    Result := FQueue.Count;
  finally
    UnLock;
  end;
end;

constructor TCommanMessages.Create(AWinHandle, AWinMessage: LongWord;
  CallName: string; MessagesList: TMessagesList);
begin
  inherited Create(CallName,MessagesList);
  FWinHandle := AWinHandle;
  FWinMessage := AWinMessage;
  FQueue := TObjectList.Create;
  FLock := TCriticalSection.Create;
end;

destructor TCommanMessages.Destroy;
begin
  Clear;
  FreeAndNil(FQueue);
  FreeAndNil(FLock);
  inherited;
end;

procedure TCommanMessages.Lock;
begin
  FLock.Enter;
end;

procedure TCommanMessages.UnLock;
begin 
  FLock.Leave;
end;

{ TObjMessages }

procedure TObjMessages.AddMessage(AMessage: TObject);
begin
  Lock;
  try
    FQueue.Add(AMessage);
    if (WinHandle<>0) then
      PostMessage(WinHandle,WinMessage,0,0);
  finally
    UnLock;
  end;
end;

function TObjMessages.PopMessage: TObject;
begin
  Lock;
  try
    if FQueue.Count>0 then
    begin
      Result := FQueue.Items[0];
      {$IFDEF Debug}
      WriteLog(Format('MsgList %s have extracted a message : message.apphdl(%s)',
        [Self.Name, Result.ClassName]),lcQuenueMsg);
      {$ENDIF}
      FQueue.Extract(Result);
    end
    else
    begin
      Result := nil;
    end;
  finally
    UnLock;
  end;
end;

{ TResourceCounter }

function TResourceCounter.CanWrite: Boolean;
begin
  if FCount = 0 then
  begin
    Result := True;
    {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] CanWrite Now, FCount=0!',[Self.ClassName,Integer(Self)]),lcThreadEvent);
    {$ENDIF}
    Exit;
  end
  else begin
    Result := FEvent.WaitFor(INFINITE) = wrSignaled;
    {$IFDEF Debug}
    WriteLog(Format('%s[%8.8x] CanWrite Now, Event=wrSignaled!',[Self.ClassName,Integer(Self)]),lcThreadEvent);
    {$ENDIF}
  end;
end;

constructor TResourceCounter.Create;
begin
  FEvent := TEvent.Create(nil,False,False,'');
  FCount := 0;
  FLock := TCriticalSection.Create;
end;

destructor TResourceCounter.Destroy;
begin
  FEvent.Free;
  FLock.Free;
  inherited;
end;

function TResourceCounter.GetCount: Integer;
begin
  Result := FCount;
  if Result = 0 then FEvent.SetEvent;
end;

procedure TResourceCounter.SetCount(const Value: Integer);
begin
  FLock.Enter;
  try
    FCount := Value;
    {$IFDEF Debug}
      WriteLog(Format('%s[%8.8x] SetCount FCount=%d!',[Self.ClassName,Integer(Self),FCount]),lcThreadEvent);
    {$ENDIF}
    Assert(FCount > -1,'TResourceCounter.FCount < 0 !资源的加锁和解锁没有对应！');
    if FCount = 0 then
    begin
      FEvent.SetEvent;
      {$IFDEF Debug}
      WriteLog(Format('%s[%8.8x] SetCount FCount=0,FEvent.SetEvent!',[Self.ClassName,Integer(Self)]),lcThreadEvent);
      {$ENDIF}
    end;
  finally
    FLock.Leave;
  end;
end;

procedure TResourceCounter.SetEventToCloseThread;
begin
  FEvent.SetEvent;
end;

{ TDoClientQueryThread }

constructor TDoClientQueryThread.Create(NameOfMsgsToPop : string;
  AdvancedEvent : TEvent; ShareResource : TResourceCounter; SelfEvent : TEvent);
begin
  Assert(SelfEvent <> nil);
  inherited Create(NameOfMsgsToPop,SelfEvent);
  AdvEvent := AdvancedEvent;
  Assert(AdvEvent <> nil);
  FCounter := ShareResource;
  Assert(FCounter <> nil);
end;

procedure TDoClientQueryThread.ExcuteRvdMsg(
  RevPushedData: TReceivedMessage);
begin
  {$IFDEF BILLDISPATCHSERVER}
  FCounter.Count := FCounter.Count + 1;
  try
  {$ENDIF}
    InternalExcuteRvdMsg(RevPushedData);
  {$IFDEF BILLDISPATCHSERVER}
  finally
    FCounter.Count := FCounter.Count - 1;
  end;
  {$ENDIF}

end;

procedure TDoClientQueryThread.InternalExcuteRvdMsg(
  RevPushedData: TReceivedMessage);
var
  QueryListName : TQueuename;
  Cookie : TSTCookie;
  tempQryRltMsgs : TQueryResultMsgs;
  tempStr : string;
  MessageToSend : TReceivedMessage;

  {$IFDEF TRADERMONSERVER}
  RevObj : TStringList;
  {$ENDIF}
begin
  { DONE -ozhupf -ca : 具体处理客户端的查询。具体包括建立查询结果包队列和发送后续包 }

  //入口线程已经认定该请求是一般的查询请求，来自客户端。但是还不知道是什么请求，
  //首包，还是后续包。
  //首包

  if RevPushedData.Head.FirstFlag = 1 then
  begin
  //然后判断请求包的类型。
    //ClearTimedOutList(Timer.Interval);  //清理已经过时的查询结果队列。

  {$IFDEF TRADERMONSERVER}
    //先判断这个操作员是否在列表里面。
    RevObj := TOprtNo_CustNoMessages(MessageList.FindMessages(MLN_OprtOwnCustom)).GetOprtList;
    Assert(RevObj <> nil);
    try
      if RevObj.IndexOf(RevPushedData.Body.scust_no) < 0 then
      begin
        tempStr := Format('Unregister Client(name:%s) RequestType(%d) from IP(%d.%d.%d.%d), Return client Error package!',
          [RevPushedData.Body.scust_no,RevPushedData.Head.RequestType,
            RevPushedData.Head.Addr[0],RevPushedData.Head.Addr[1],
            RevPushedData.Head.Addr[2],RevPushedData.Head.Addr[3]]);
        WriteLog(tempStr,lcException);
        TReceivedMessages(MessageList.FindMessages(MLN_SendData)).AddMessage(
          UKSBaseThread.GetErrorPkgMsg(tempStr,RevPushedData.Head.RequestType,RevPushedData.AppHdl),
          SendQryRltThd.Event);
        Exit;
      end;
    finally
      {$IFDEF Debug}
  //    LogDestroy(RevObj);
      {$ENDIF}
      RevObj.Free;
    end;
  {$ENDIF}

    tempQryRltMsgs := InternalDoQuery(RevPushedData);
//    Assert(tempQryRltMsgs <> nil,'查询结果集合对象为空！');
//    if tempQryRltMsgs <> nil then
//      tempQryRltMsgs.SendOnePackage(0,TReceivedMessages(MessageList.FindMessages(MLN_SendData)),
//        SendQryRltThd.Event,RevPushedData.AppHdl)
//    else begin

    //替换为：
    if tempQryRltMsgs = nil then
    begin
      tempStr := Format('Client(IP:%d.%d.%d.%d) Request(%d) meet Error, No Records or Other Reason!',
        [RevPushedData.Head.Addr[0],RevPushedData.Head.Addr[1],RevPushedData.Head.Addr[2],
        RevPushedData.Head.Addr[3],RevPushedData.Head.RequestType]);
      WriteLog(tempStr,lcException);
      TReceivedMessages(MessageList.FindMessages(MLN_SendData)).AddMessage(
        UKSBaseThread.GetErrorPkgMsg(tempStr,RevPushedData.Head.RequestType,RevPushedData.AppHdl),
        SendQryRltThd.Event);
    end;
  end
  //后续包,包括Cancel包
  else begin
    Cookie := RevPushedData.Head.Cookie;
    FillChar(QueryListName,SizeOf(QueryListName),0);
    Move(Cookie.queuename,QueryListName,SizeOf(QueryListName));

    tempQryRltMsgs := TQueryResultMsgs(QryRstMsgList.FindMessages(RevPushedData.Head.Cookie.queuename));
    if tempQryRltMsgs <> nil then
    begin
      if RevPushedData.Head.NextFlag = 0 then
      begin
        MessageToSend := TReceivedMessage.Create(RevPushedData.PData,False,RevPushedData.DataSize);
        MessageToSend.AppHdl := RevPushedData.AppHdl;
        TReceivedMessages(MessageList.FindMessages(MLN_SendData)).AddMessage(
          MessageToSend, SendQryRltThd.Event);

        QryRstMsgList.SetOneObjNil(tempQryRltMsgs);
        Exit;
      end;
      tempQryRltMsgs.SendOnePackage(QueryListName.PackageNO + 1,TReceivedMessages(MessageList.FindMessages(MLN_SendData)),
        SendQryRltThd.Event,RevPushedData.AppHdl);
    end
    else begin
      tempStr := Format('QryRltMsgs(Name:%s) is not exists now!',[QueryListName.QueueNameStr]);
      WriteLog(tempStr,lcException);
      tempStr := Format('%s-后续包已经被服务器删除，可能是取后续包超时（超时时限：%d秒）',
        [tempStr,TimeIntervalForClearQryList div 1000]);
      TReceivedMessages(MessageList.FindMessages(MLN_SendData)).AddMessage(
        UKSBaseThread.GetErrorPkgMsg(tempStr,RevPushedData.Head.RequestType,RevPushedData.AppHdl, True),
        SendQryRltThd.Event);
    end;
  end;
end;

{$IFDEF BILLDISPATCHSERVER}
procedure TDoClientQueryThread.InternalExecute;
var
  HdlArray : windows.TWOHandleArray;
begin
  HdlArray[0] := Event.Handle;
  HdlArray[1] := AdvEvent.Handle;
  if windows.WaitForMultipleObjects(2,@HdlArray,True,INFINITE) = WAIT_OBJECT_0 then
    PopMsgToExec;
end;
{$ENDIF}

procedure TDoClientQueryThread.SetOtherEventToClose;
begin
  Assert(AdvEvent <> nil,'AdvEvent is Nil, Can''t Release This Thread!');
//  Terminate;
  AdvEvent.SetEvent;
  Assert(Event <> nil,'Event is Nil, Can''t Release Other Thread!');
//  Event.SetEvent;
end;

{ TThdList }

function TThdList.Count: Integer;
begin
  Result := FQuenue.Count;
end;

constructor TThdList.Create(ThdClass : TThdClass; nCount : Integer;
                       NameOfMsgsToPop : string; AdvancedEvent : TEvent;
                       ShareResource : TResourceCounter);
var
  I : Integer;
begin
  FEvent := TEvent.Create(nil,False,False,'');
  FQuenue := TObjectList.Create(True);
  FQuenue.Clear;
  for I := 0 to nCount - 1 do FQuenue.Add(ThdClass.Create(NameOfMsgsToPop,AdvancedEvent,
    ShareResource,FEvent));
  Assert(Count = nCount,'创建的线程和要求的个数不一致！');
end;

destructor TThdList.Destroy;
var
  I : Integer;
begin
  for I := 0 to FQuenue.Count - 1 do TThread(FQuenue.Items[I]).Terminate;
//  for I := 0 to FQuenue.Count - 1 do FEvent.SetEvent;
  for I := 0 to FQuenue.Count - 1 do
  begin
    try
      TDoClientQueryThread(FQuenue.Items[I]).Close;
    except
      WriteException;
    end;
  end;
  FQuenue.Free;
  FEvent.Free;
  inherited;
end;

procedure TThdList.ResumeAll;
var
  I : Integer;
begin
  for I := 0 to FQuenue.Count - 1 do TThread(FQuenue[I]).Resume;
end;

{ TDoSomeThingThread }

constructor TDoSomeThingThread.Create(ThreadToDoMethod: TThreadToDoMethod; SenderObj : TObject;
  SemaphoreToSingal : TSemaphore; OperatedObj : TObject);
begin
  inherited Create(True);
  FreeOnTerminate := True;
  FThreadToDoMethod := ThreadToDoMethod;
  FSenderObj := SenderObj;
  FSemaphore := SemaphoreToSingal;
  FOperatedObj := OperatedObj;
  {$IFDEF Debug}
   LogCreate(self);
  {$ENDIF}
end;

destructor TDoSomeThingThread.Destroy;
begin
  inherited;
  {$IFDEF Debug}
  LogDestroy(self);
  {$ENDIF}
end;

procedure TDoSomeThingThread.Execute;
begin   
  try
    try
      if @FThreadToDoMethod <> nil then FThreadToDoMethod(FSenderObj,FOperatedObj);
    except
      on E : Exception do
      begin
        WriteLog(Format('Switch MainWorkArea(%s) has meeted Error:%s,Skipped this Error and Continue!',
          [FSenderObj.ClassName,E.Message]),lcException);
      end;
    end;
  finally
    if FSemaphore <> nil then Assert(FSemaphore.WaitFor(100)=wrSignaled);;
    Terminate;
  end;
end;

{ TSemaphore }

constructor TSemaphore.Create(IniCount, MaxCount: Integer; Name: string);
begin
  FHandle := CreateSemaphore(nil,IniCount,MaxCount,PChar(Name));
end;

destructor TSemaphore.Destroy;
begin
  CloseHandle(FHandle);
  inherited Destroy;
end;

function TSemaphore.SelfReleaseSemaphore(Count: Integer): Integer;
begin
  Assert(Count>0);
  try
    Assert(windows.ReleaseSemaphore(FHandle,Count,@Result));
  finally
    Assert(Self.WaitFor(INFINITE)=wrSignaled);
  end;
end;

function TSemaphore.WaitFor(Timeout: DWORD): TWaitResult;
begin
  case WaitForSingleObject(Handle, Timeout) of
    WAIT_ABANDONED: Result := wrAbandoned;
    WAIT_OBJECT_0: Result := wrSignaled;
    WAIT_TIMEOUT: Result := wrTimeout;
    WAIT_FAILED:
      begin
        Result := wrError;
        FLastError := GetLastError;
      end;
  else
    Result := wrError;
  end;
end;

procedure TMSBaseThread.SetOtherEventToClose;
begin
end;

end.
