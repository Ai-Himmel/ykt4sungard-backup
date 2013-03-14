unit UMonClientDataSet;

interface

uses
  windows, classes, messages, ComCtrls, MessageListeners, KCDataPack, SyncObjs, KCDataAccess,
  DBAIntf, Db, Contnrs, UKSBaseThread;

const
  MonClientDataFileExt = '.mcd';           //MonClientData

  //���峣��  ����ֱ�ӹ������͵Ľ�����²���
  REV_MIN_TIMEINTERVEL        = 30;       //��������ˢ�¼����

  REV_COUNT_FOR_CLIENTREFRESH = 5;        //�ܹ����������ݾ͸��¡�
  REV_TIMEOUT_FOR_CLIENTREFRESH = 3;       //�������룬����������ݾ�����ˢ��һ�¡�

  Refresh_Without_Switch = 1;

const
  //֪ͨ�������һЩ��Ϣ���塣
  WMMC_RefreshView = WM_USER+1;
  WMMC_ShowProperItem = WMMC_RefreshView+1;
  WMMC_CntStatusChanged = WMMC_ShowProperItem+1;

type
  TMonClientStyle = (mcsEntrust,mcsHold,mcsBaginOn,mcsMoney,mcsRisk,mcsEvent,mcsNull);
  TMCConditionStyle = (mccsUpdate,mccsFilt,mccsSort,mccsHeartBeat,mccsFindItem);
  TSortDir = (sdInc,sdDec);
  TLogicOperator = (loEqual,loLike,loBetween);
  TDDKinds = (ddkMarket,ddkTradeDir,ddkContractStatus,ddkEntrustType,ddkContractType,
    ddkKaiPing,ddkTouBao,ddkMoneyType,ddkSeat,ddkInfoType,ddkNO);
  TIndexKind = record
    Index : Integer;
    Kind  : TDDKinds;
  end;

type
  //һЩ�ӿڣ�����֧��Listner��ƺ�ֱ�ӵĵ��á�
  PItemHeader = ^TItemHeader;
  TItemHeader = packed record
    Size, Count: Integer;
    Items: record end;
  end;

  TColumnType = record
    Width : integer;
    Order : Integer;
    Name  : string;
    CPackName : string;
  end;

  TSortRec = packed record
    FieldIndex : Integer;
    Dir  : TSortDir;
    Name : string[255];
  end;
  PSrotRec = ^TSortRec;

  TConditionName = (cnOprt,cnCust,cnKinds,cnDeliverTime,cnTradeDir);

  TConditionRec = packed record
    Name : TConditionName;
    FieldIndex : Integer;
    Operator : TLogicOperator;
    Value : string[255];
  end;
  PConditionRec = ^TConditionRec;

  TConditionList = array of TConditionRec;

  TConditionObject = class(TComponent)
  private
    FConditions : TConditionList;
    FStyle: TMCConditionStyle;
    FSortCondition: TSortRec;
    FCount: Integer;
    //FTimerInterVal: Integer;
    function Get(Index: Integer): TConditionRec;
    procedure Put(Index: Integer; const Value: TConditionRec);

    procedure ReadData(Stream: TStream);
    procedure WriteData(Stream: TStream);
    procedure ProcessConditionRec(var Rec : TConditionRec);
  protected
    procedure DefineProperties(Filer: TFiler); override;
  public
    constructor Create;
    destructor Destroy; override;

    function Add(Condition : TConditionRec) : Integer;
    function Delete(Index : Integer) : Boolean;
    procedure Assign(ConditionObject : TConditionObject); reintroduce;
    function ConditionByName(Name : TConditionName) : PConditionRec;
    function ConditionValueByName(Name : TConditionName) : string;
    property SortCondition : TSortRec read FSortCondition write FSortCondition;
    property Conditions[Index : Integer] : TConditionRec read Get write Put; Default;
  published
    //property TimerInterVal : Integer read FTimerInterVal write FTimerInterVal;
    property Count : Integer read FCount write FCount;
    property Style : TMCConditionStyle read FStyle write FStyle;
  end;

  TMonClientDataArray = string;
  TDataAA = array of TMonClientDataArray;
  TMonClientColumnStyle = array of TColumnType;

  IMonClientView = Interface
    procedure AddListener(Listener : IMessageListener);
    function ClearListener(Listener : IMessageListener) : Integer;
    procedure CreateNewList(AConditionObject : TConditionObject);
    procedure AddItem(BookMark : TBookmark);
    procedure RefreshItem(BookMark : TBookmark);
    procedure SwitchData;
    function DataCount : Integer;
    procedure ListViewData(Sender: TObject; Item: TListItem);
    procedure ListViewDataHint(Sender: TObject; StartIndex,
      EndIndex: Integer);
    procedure ListViewDataFind(Sender: TObject; Find: TItemFind;
      const FindString: String; const FindPosition: TPoint;
      FindData: Pointer; StartIndex: Integer; Direction: TSearchDirection;
      Wrap: Boolean; var Index: Integer);
    procedure FindProperIndexByValue(const Value : string; ValueStyle : TConditionName = cnCust);
    procedure TellViewToUpdate;
  end;

  IMonClientData = Interface
    function CreateViewer(Listener : IMessageListener; ConditionObject : TConditionObject) : Cardinal;
    procedure ReleaseViewer(Listener : IMessageListener;ViewIndex : Cardinal);
    function GetView(ViewIndex : Cardinal) : IMonClientView;
    procedure ViewConditionChanged(ViewIndex : Cardinal; ConditionObject : TConditionObject);
    procedure SwitchDataSet;
    procedure RevPushData(RequestType : LongWord; PBody : PSTPack; IsAdd : Boolean = True);
    function MatchCondition(ConditionObject : TConditionObject) : Boolean;
    function GetProperSubStr(CPackFieldName : string) : string;
    procedure TellViewToUpdate;
  end;

type
  TKSInterfaceObject = class(TObject,IUnknown)
  protected
    FRefCount : Integer;
    { IUnknown }
    function QueryInterface(const IID: TGUID; out Obj): HResult; virtual; stdcall;
    function _AddRef: Integer; stdcall;
    function _Release: Integer; stdcall;
  public
    constructor Create;
  end;

  TMonClientDataList = class(TList)
  private
    FDataAA : TDataAA;
    FShareData : Boolean;
    FSortedStringList: TStringList;
    FHaveSorted : Boolean;

    procedure CreateSortStrList(const Index : Integer);
    procedure ReArrangeItem(const Dir: TSortDir;const FieldType : TFieldType);
  public
    constructor Create;
    function AddData(var MonClientData : TMonClientDataArray) : Integer;
    procedure RefreshData(Index : Integer; var MonClientData : TMonClientDataArray);
    function GetShareData : TDataAA;
    procedure CopyRefData(SrcList : TMonClientDataList);
    procedure ClearData;
    destructor Destroy; override;
    procedure SwitchItem(const Index1, Index2 : Integer);
    procedure SortedByDirInput(Dir : TSortDir; Index : Integer;
      FieldType : TFieldType; NeedToRebuild : Boolean = True);

    property SortedStr : TStringList read FSortedStringList;
  end;

type

  TMonClientDataSet = class;

  TMonClientViewer = class(TInterfacedObject,IMonClientView)
  private
    FLock : TCriticalSection;
    FRevCount : Integer;

    FNeedToSwitch : Boolean;
    FListenerList : TMessageListenerSurport;
    FConditionObject: TConditionObject;
    FViceConditionObject : TConditionObject;
    FMainList, FViceList : TMonClientDataList;
    FStyleArray : TMonClientColumnStyle;
    FOwnerDataSet : TMonClientDataSet;
    FStyleCloCount : Integer;

    MidSL : TStringList;

    function FFGetCurRecStr : TMonClientDataArray;
    procedure FRefreshOneData;
    procedure FAddOneData(List : TMonClientDataList);
    procedure GetInitViceList;
    function SetConditionGetWorkList(AConditionObject : TConditionObject) : TMonClientDataList;
    procedure SetFConditionObject(const Value: TConditionObject);
    procedure InternalSort(AList : TMonClientDataList);
    procedure TryToResponseHeartBeat;
    procedure TryToFindItem(AConditionObject : TConditionObject);
    procedure SetRevCount(const Value: Integer);
    function GetRevCount: Integer;
  protected
    { DONE -o����� -ca :
��������ฺ���ͨ�õĹ����������ƣ��޸�Ϊ��DataSet��Cpack��
FieldName�����ƣ���������ƥ����֤��ʱ��֤��ȷ�ԡ�Ŀǰ�����ڹ���������һ��������
������Բ���д�����Ч�ʡ� }
  public
    constructor Create(Owner : TMonClientDataSet; AConditionObject : TConditionObject;
      Listener : IMessageListener);
    destructor Destroy; override;

    //  IMonClientView
    procedure AddListener(Listener : IMessageListener);
    function ClearListener(Listener : IMessageListener) : Integer;
    procedure CreateNewList(AConditionObject : TConditionObject);
    procedure AddItem(BookMark : TBookmark);
    procedure RefreshItem(BookMark : TBookmark);
    procedure SwitchData;
    function DataCount : Integer;
    procedure ListViewData(Sender: TObject; Item: TListItem);
    procedure ListViewDataHint(Sender: TObject; StartIndex,
      EndIndex: Integer);
    procedure ListViewDataFind(Sender: TObject; Find: TItemFind;
      const FindString: String; const FindPosition: TPoint;
      FindData: Pointer; StartIndex: Integer; Direction: TSearchDirection;
      Wrap: Boolean; var Index: Integer);
    procedure FindProperIndexByValue(const Value : string; ValueStyle : TConditionName = cnCust);
    procedure TellViewToUpdate;

    procedure InternalCreateNewList(AConditionObject : TConditionObject);

    property RevCount : Integer read GetRevCount write SetRevCount;
    property ConditionObject : TConditionObject read FConditionObject write SetFConditionObject;
    property NeedToSwitch : Boolean read FNeedToSwitch;
  end;


  TMonClientDataSet = class(TKSInterfaceObject,IMonClientData)
  private
//    FFirstNeedSwitch : Boolean;
    FDDObjList : TList;

    FLastBookMark : TBookmark;
    FName : string;
    FReason : string;
    FCriticalSection : TCriticalSection;
    FMainDataSet : TKCDataSet;
    FViceDataSet : TKCDataSet;
    FKCDataSet1 : TKCDataSet;
    FKCDataSet2 : TKCDataSet;
    FNeedToSwitch: Boolean;
    FRequestType: Integer;
    FMonClientStyle: TMonClientStyle;
    FStyleArray : TMonClientColumnStyle;
    FViewerList : TInterfaceList;
    FIndexForcnOprt: Integer;
    FIndexForcnDeliverTime: Integer;
    FIndexForcnCust: Integer;
    FIndexForcnTradeDir: Integer;
    FIndexForcnKinds: Integer;
    function FindParamIndex(CPackName : string) : Integer;
    function FindColumnCpackName(ColName : string) : string;
    procedure InitStyleAry;
    function GetSameConditionViewer(ConditionObject : TConditionObject) : IMonClientView;
    procedure SwitchViewers;
    procedure TranslateConditionObject(AConditionObject : TConditionObject);// abstract;
    function GetDDNameByValue(const DDKind : TDDKinds;const Value : string) : string;
    procedure InitDDList;
  protected
    FIndexArray : array of TIndexKind;

    procedure AddOneIndexKind(IndexName : string; AKind : TDDKinds);
    procedure InitKindsIndex; virtual;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); virtual;

    function GetFieldIndex(FieldCPackName : string) : Integer;
    procedure BindOneParam(DataSet : TKCDataSet; ParamName : string;
      ParamDataType : TDBFieldType; ParamValue : Variant);
    procedure BindInput(DataSet : TKCDataSet); virtual;
    procedure TranslateOneCondition(var ConditionRec : TConditionRec); virtual;
    procedure InternalChangeMainArea;
    procedure QueryDrtp;

    //�õ���ͬ��DataSet�ĸ���Indexֵ�������ֵ�����͡�
    function GetDDKindsByIndex(const Index : Integer) : TDDKinds;
  public
    constructor Create(AName : string; DataBase : TKCDatabase; AMonClientStyle : TMonClientStyle; NeedToSwitch : Boolean = False);
    destructor Destroy; override;
    procedure Init;

    function GetTranslateStrByDD(const Index : Integer; const Value : string) : string;

    //����ʵ�� IMonClientData �ӿ�
    function CreateViewer(Listener : IMessageListener; ConditionObject : TConditionObject) : Cardinal;
    procedure ReleaseViewer(Listener : IMessageListener;ViewIndex : Cardinal);
    function GetView(ViewIndex : Cardinal) : IMonClientView;
    procedure ViewConditionChanged(ViewIndex : Cardinal; ConditionObject : TConditionObject);
    procedure SwitchDataSet;
    procedure RevPushData(RequestType : LongWord; PBody : PSTPack; IsAdd : Boolean = True);
    function MatchCondition(ConditionObject : TConditionObject) : Boolean; overload;
    function GetProperSubStr(CPackFieldName : string) : string;  overload; virtual;
    function GetProperSubStr(Index : Integer): string; overload;
    procedure TellViewToUpdate;

    property Name : string read FName;
    property DataSet : TKCDataset read FMainDataSet;
    property StyleArray : TMonClientColumnStyle read FStyleArray;
    property MonClientStyle : TMonClientStyle read FMonClientStyle;
    property NeedToSwitch : Boolean read FNeedToSwitch;
    property RequestType : Integer read FRequestType;
    property ErrorReason : string read FReason;
    property CriticalSection : TCriticalSection read FCriticalSection;

    property IndexForcnOprt : Integer read FIndexForcnOprt;
    property IndexForcnCust : Integer read FIndexForcnCust;
    property IndexForcnKinds : Integer read FIndexForcnKinds;
    property IndexForcnDeliverTime : Integer read FIndexForcnDeliverTime;
    property IndexForcnTradeDir : Integer read FIndexForcnTradeDir;
  end;

  TMonClientDataArea = class(TObjectList)
  public
    function  FindCriticalSectionDataSet(DataSetStyle : TMonClientStyle): TMonClientDataSet;
    procedure Init;
    function SwitchWorkArea : Boolean;
    procedure SaveAllData(const FilePath : string);
    procedure LoadAllData(const FilePath : string);
    {$IFDEF Debug}
    constructor Create(OwendObj : Boolean = True);
    destructor Destroy; override;
    {$ENDIF}
  end;

    //��ѯ���������߳�,�����л���������������ÿ�����ݼ��ϣ����Կ������������л���
  TQueryViceDataAreaThd = class(TMSBaseThread)
  private
    FSleepCount : Cardinal;
    FSleepPerTime : Cardinal;
    FSleepTime : Cardinal;

    FHaveSleepedCount : Cardinal;
    procedure FirstSwitchWorkArea;
  protected
    procedure InternalExecute; override;
  public
    constructor Create(SleepTimeInv : Cardinal);
  end;

type
  TEntrustMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  TBaginOnMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  TEventMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  TMoneyMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  TRiskMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  THoldMCDataSet = class(TMonClientDataSet)
  private

  protected
    procedure BindInput(DataSet : TKCDataSet); override;
    procedure InternalAddRevData(var BookMark : TBookmark; var NeedRefresh : Boolean;
      RequestType : LongWord; PBody : PSTPack); override;
    procedure InitKindsIndex; override;
//    procedure TranslateOneCondition(var ConditionRec : TConditionRec); override;
  public
    function GetProperSubStr(CPackFieldName : string) : string; override;
  end;

  THeartBeatMCDataSet = class(TMonClientDataSet)
  private
    FConnectStatus: TConnect_Status;
    procedure SetConnectStatus(const Value: TConnect_Status);
  protected
    procedure BindInput(DataSet : TKCDataSet); override;
  public
    {function GetProperSubStr(CPackFieldName : string) : string; override;}
    procedure SwitchDataSet;
    property  ConnectStatus : TConnect_Status read FConnectStatus write SetConnectStatus;
  end;

  procedure InitAll(OffLine : Boolean = False);
  procedure StarAllThreads;
  procedure CloseAll;

  procedure RecievePushData(RequestType: LongWord; PBody: PSTPack);

var
  WorkArea : TMonClientDataArea;

implementation

uses
  UMain, LogFile, BDAImpEx, DebugMemory, SysUtils, KSFrameWorks, TraderMSConsts,
  KSClientConsts, UStartFlash, UPushRevThread, Forms, UQhClientConsts, FileCtrl,
  KSDataDictionary;

const
//TDDKinds = (ddkMarket,ddkTradeDir,ddkContractStatus,ddkKaiPing,ddkTouBao,
//              ddkSeat,ddkNO);
  { DONE -o����� -ca : ����һЩ��Ҫ��ʼ�����ֵ���ֵ�š� }
  ddkMarketID         = -21;         //������
  ddkTradeDirID       = 4;
  ddkContractStatusID = 9;
  ddkEntrustTypeID    = 10;
  ddkContractTypeID    = 20;
  ddkKaiPingID        = 5;
  ddkTouBaoID         = 6;
  ddkMoneyTypeID      = 1008;
  ddkSeatID           = -23;
  ddkInfoTypeID       = 049;

var
  SwitchDataAreaThd : TQueryViceDataAreaThd;
  PushRevThread: TPushRevThread;
  HeartBeatDS : THeartBeatMCDataSet;

function TempStrToFloatFmt(S : string;DefaultValue : Double) : Double;
begin
  try
    Result := StrToFloat(S);
  except
    Result := DefaultValue;
  end;
end;
function SortFloat (List: TStringList; Index1, Index2: Integer): Integer;
var
  tempRlt : Double;
begin
  tempRlt := TempStrToFloatFmt(List[Index1],0) - TempStrToFloatFmt(List[Index2],0);
  if tempRlt < 0 then Result := -1
  else if tempRlt = 0 then Result := 0
    else Result := 1;
end;
function SortInt (List: TStringList; Index1, Index2: Integer): Integer;
begin
  Result := StrToIntDef(List[Index1],0) - StrToIntDef(List[Index2],0);
end;

function GetIndexStr(const StringToDevide : string; Index : Integer) : string;
var
  tempStr : string;
  I, J, tempLength : Integer;
  LeftPos,RightPos : Integer;
begin
  Result := '';
  LeftPos := 0;
  RightPos := 0;
  tempLength := Length(StringToDevide);
  if tempLength = 0 then Exit;
  J := Index + 1;
//  Inc(LeftPos);
  for I := 1 to tempLength do
  begin
    if StringToDevide[I] = ',' then
    begin
      Inc(RightPos);
      if RightPos < Index then continue;
      if RightPos = Index then LeftPos := I
      else if RightPos = J then
      begin
        Result := Copy(StringToDevide,LeftPos+1,I-1-LeftPos);
        Exit;
      end;
    end;
  end;

  if RightPos=0 then
  begin
    if Index=0 then Result := StringToDevide;
    Exit;
  end;
  
  if RightPos<Index then Exit
  else if RightPos=Index then
  begin
    Result := Copy(StringToDevide,LeftPos+1,tempLength);
  end;
end;

{ TKSInterfaceObject }

function TKSInterfaceObject._AddRef: Integer;
begin
  Result := 0;
end;

function TKSInterfaceObject._Release: Integer;
begin
  Result := 0;
end;

constructor TKSInterfaceObject.Create;
begin

end;

function TKSInterfaceObject.QueryInterface(const IID: TGUID;
  out Obj): HResult;
begin
  if GetInterface(IID, Obj) then Result := S_OK
    else Result := E_NOINTERFACE;
end;

{ TMonClientDataSet }

procedure TMonClientDataSet.BindInput(DataSet: TKCDataSet);
begin
  DataSet.Params.Clear;
  DataSet.Database := TKCDatabase(DatabaseModule.GetDataBase);
end;

procedure TMonClientDataSet.BindOneParam(DataSet: TKCDataSet;
  ParamName: string; ParamDataType: TDBFieldType; ParamValue: Variant);
var
  Param: THRPCParam;
begin
  if DataSet.Params.paramByName(ParamName) = nil then
  begin
    Param := Dataset.Params.Add;
    Param.Name := ParamName;
    Param.DataType := ParamDataType;
  end
  else Param := DataSet.Params.paramByName(ParamName);
  Param.Value := ParamValue;
end;

constructor TMonClientDataSet.Create(AName : string; DataBase: TKCDatabase;
  AMonClientStyle: TMonClientStyle; NeedToSwitch: Boolean);
begin
  inherited Create;
  FName := AName;
  FKCDataSet2 := nil;
//  FFirstNeedSwitch := NeedToSwitch;
//  FNeedToSwitch := True;
  FNeedToSwitch := NeedToSwitch;
  FMonClientStyle := AMonClientStyle;
  InitStyleAry;
  InitKindsIndex;

  FDDObjList := TList.Create;
  InitDDList;

  FCriticalSection := TCriticalSection.Create;
  FViewerList := TInterfaceList.Create;
  FKCDataSet1 := TKCDataset.Create(nil);
  FKCDataSet1.Database := DataBase;
  BindInput(FKCDataSet1);

  FRequestType := FKCDataSet1.RequestType;

//  if NeedToSwitch then
//  begin
    FKCDataSet2 := TKCDataset.Create(nil);
    FKCDataSet2.Database := DataBase;
    BindInput(FKCDataSet2);
//  end;

  FMainDataSet := FKCDataSet1;
  FViceDataSet := FKCDataSet2;

  {$IFDEF Debug}
  LogCreate(Self);
  {$ENDIF}
end;

function TMonClientDataSet.CreateViewer(Listener : IMessageListener;
  ConditionObject : TConditionObject) : Cardinal;
var
  tempViewer : IMonClientView;
begin
  FCriticalSection.Enter;
  try
    tempViewer := GetSameConditionViewer(ConditionObject);
    if tempViewer = nil then
    begin
      tempViewer := TMonClientViewer.Create(Self,ConditionObject,Listener);
      Result := FViewerList.Add(tempViewer);
    end
    else Result := FViewerList.IndexOf(tempViewer);
  finally
    FCriticalSection.Leave;
  end;
end;

destructor TMonClientDataSet.Destroy;
var
  tempObj : TObject;
begin
  FreeAndNil(FKCDataSet1);
  FreeAndNil(FKCDataSet2);
  FreeAndNil(FCriticalSection);
  tempObj := FViewerList;
  FViewerList := nil;
  tempObj.Free;
  FDDObjList.Free;
  inherited;

  {$IFDEF Debug}
  LogDestroy(Self);
  {$ENDIF}
end;

function TMonClientDataSet.FindParamIndex(CPackName: string): Integer;
var
  I : Integer;
begin
  for I:=0 to PARAMBITS-1 do
  begin
    if SameText(CPackName,KCPackDataNames[I]) then
    begin
      Result := I;
      Exit;
    end;
  end;
  Result := -1;
end;

function TMonClientDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  with DataSet.FindField(CPackFieldName) do
    case DataType of
      ftInteger : Result := IntToStr(AsInteger);
      ftFloat   : Result := FloatToStr(AsFloat);
    else Result := AsString;
    end;
end;

function TMonClientDataSet.GetFieldIndex(FieldCPackName: string): Integer;
begin
  Result := -1;
  if FieldCPackName = '' then Exit;
  for Result := 0 to High(StyleArray) do
  begin
    if AnsiSameText(StyleArray[Result].CPackName, FieldCPackName) then Exit;
  end;
end;

function TMonClientDataSet.GetProperSubStr(Index : Integer): string;
begin
  with DataSet.Fields[Index] do
    case DataType of
      ftInteger : Result := IntToStr(AsInteger);
      ftFloat   : Result := FloatToStr(AsFloat);
    else Result := AsString;
    end;
end;

function TMonClientDataSet.GetSameConditionViewer(ConditionObject : TConditionObject): IMonClientView;
begin
  Result := nil;
{ DONE -ozpf -ca :
����Viewer�б����Ƿ�����ͬ������Viewer���Ը��á�������򷵻أ�
���򷵻�nil�� }
end;

function TMonClientDataSet.GetView(ViewIndex: Cardinal): IMonClientView;
begin
  FCriticalSection.Enter;
  try
    Result := IMonClientView(FViewerList[ViewIndex]);
  finally
    FCriticalSection.Leave;
  end;
end;

procedure TMonClientDataSet.Init;
begin
  FCriticalSection.Enter;
  try
    FMainDataSet.Open;
//    FMainDataSet.Last;
  finally
    FCriticalSection.Leave;
  end;
  if FMainDataSet.ReturnCode <> 0 then
  begin
    FMainDataSet.First;
    if FMainDataSet.FindField('vsmess') <> nil then FReason := FMainDataSet.FindField('vsmess').AsString;
    WriteLog(Format('%s.MainDataSet has got an error Return code(%d),Reason:%s',
      [Self.ClassName,FMainDataSet.ReturnCode,FReason]),lcException);
  end;
end;

procedure TMonClientDataSet.InitStyleAry;
begin
  case MonClientStyle of
    mcsEntrust :
      begin
        FStyleArray := @EntrustView;
        SetLength(FStyleArray,High(EntrustView)+1);
      end;
    mcsHold :
      begin
        FStyleArray := @StorageView;
        SetLength(FStyleArray,High(StorageView)+1);
      end;
    mcsBaginOn :
      begin
        FStyleArray := @DoneView;
        SetLength(FStyleArray,High(DoneView)+1);
      end;
    mcsMoney :
      begin
        FStyleArray := @FundView;
        SetLength(FStyleArray,High(FundView)+1);
      end;
    mcsRisk :
      begin
        FStyleArray := @RiskView;
        SetLength(FStyleArray,High(RiskView)+1);
      end;
    mcsEvent :
      begin
        FStyleArray := @EventView;
        SetLength(FStyleArray,High(EventView)+1);
      end;
  end;

  FIndexForcnOprt := GetFieldIndex('scust_no');
  FIndexForcnCust := GetFieldIndex('sholder_ac_no');
  FIndexForcnKinds := GetFieldIndex('sstock_code');
  FIndexForcnDeliverTime := GetFieldIndex('sdate1');
  FIndexForcnTradeDir := GetFieldIndex('sstatus2');
end;

procedure TMonClientDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  { TODO -o����� -ca :
ʵ��ִ�н����ܵ����������ݸ��µ����ݼ��ϵ����񣬿��ܸ��£�
������ӡ��������Ҫ���£��ͽ�BookMark��Ϊnil���ɡ������߼��ͼ�ط�������ȫһ���� }
  BookMark := nil;
end;

procedure TMonClientDataSet.InternalChangeMainArea;
var
  tempDataSet : TKCDataset;
begin
  if FViceDataSet.ReturnCode <> 0 then
  begin
    FViceDataSet.First;
    if FViceDataSet.FindField('vsmess') <> nil then FReason := FViceDataSet.FindField('vsmess').AsString;
    WriteLog(Format('%s.MainDataSet has got an error Return code(%d),Reason:%s',
      [Self.ClassName,FViceDataSet.ReturnCode,FReason]),lcException);
    Exit;
  end;

  tempDataSet := FMainDataSet;
  FMainDataSet := FViceDataSet;
  {$IFDEF Debug}
  WriteLog(Format('%s[%8.8x] has been changed to MainDataSet!',
    [FMainDataSet.ClassName,Integer(FMainDataSet)]),lcDebug);
  {$ENDIF}
  FViceDataSet := tempDataSet;
  {$IFDEF Debug}
  WriteLog(Format('%s[%8.8x] has been changed to ViceDataSet!',
    [FViceDataSet.ClassName,Integer(FViceDataSet)]),lcDebug);
  {$ENDIF}
//  CreateParamBits;
end;

function TMonClientDataSet.MatchCondition(
  ConditionObject: TConditionObject): Boolean;
var
  tempRlt : Boolean;
  I : Integer;
  function MatchSingleCdtn(SingleCdtn : TConditionRec) : Boolean;
  begin
    //Result := (SingleCdtn.Value = '') or (SingleCdtn.FieldIndex < 0);
    //if Result then Exit;
    with SingleCdtn do
    begin
      case Operator of
        loEqual : Result := AnsiSameText(DataSet.Fields[FieldIndex].AsString,Value);
        loLike  : Result := Pos(DataSet.Fields[FieldIndex].AsString,Value) > 0;
      end;
    end;
  end;
begin
  Result := True;
  { DONE -ozpf -ca :
��View���������ж�DataSet�ĵ�ǰ��¼�Ƿ���Ϲ��˵��������߳�
�Ѿ���ȫ�������ɾ���Ŀͻ������� }
  for I := 0 to ConditionObject.Count-1 do
  begin
    Result := Result and MatchSingleCdtn(ConditionObject[I]);
    if not Result then Exit;
  end;
end;

procedure TMonClientDataSet.QueryDrtp;
begin
  FViceDataSet.Open;
  FViceDataSet.Last;
end;

procedure TMonClientDataSet.ReleaseViewer(Listener : IMessageListener; ViewIndex: Cardinal);
begin
  FCriticalSection.Enter;
  try
    if FViewerList.Count>ViewIndex then
      if IMonClientView(FViewerList[ViewIndex]).ClearListener(Listener)=0
        then FViewerList.Delete(ViewIndex);
  finally
    FCriticalSection.Leave;
  end;
end;

procedure TMonClientDataSet.RevPushData(RequestType: LongWord;
  PBody: PSTPack; IsAdd : Boolean);
var
  tempBookMark : TBookmark;
  tempNeedRefresh : Boolean;
  I : Integer;
begin
{ DONE -ozpf -ca :
�������������������ܵ�������д�������������������Ļ��߸��µ�
��¼��BookMark��Ȼ��֪ͨ���е�View��������Viewer���Ƿ���£�
��ô���£�����Viewer������ȫ�����������̰߳�ȫ�� }
  FCriticalSection.Enter;
  try
    tempNeedRefresh := not IsAdd;
    //���ж���û�����ݼ��ϣ����û�оͲ�ѯ��
    if DataSet.Active = False then
    begin
      while DataSet.Active = False do Self.SwitchDataSet;
//Debug      DataSet.SaveToFile('c:\zpfclient.db');
//      DataSet.Last;
      TellViewToUpdate;
      Exit;
      //tempBookMark := DataSet.GetBookmark;
    end
    else begin
      Assert(DataSet.Active = True);
      InternalAddRevData(tempBookMark,tempNeedRefresh,RequestType,PBody);
    end;
    if tempBookMark = nil then Exit;
    FLastBookMark := tempBookMark;
    if IsAdd then
      for I := 0 to FViewerList.Count-1 do IMonClientView(FViewerList[I]).AddItem(FLastBookMark)
    else for I := 0 to FViewerList.Count-1 do IMonClientView(FViewerList[I]).RefreshItem(FLastBookMark);
  finally
    FCriticalSection.Leave;
  end;
end;

procedure TMonClientDataSet.SwitchDataSet;
begin
//  if not NeedToSwitch then Exit;
//  if not FFirstNeedSwitch then FNeedToSwitch := FFirstNeedSwitch;
  Assert(FViceDataSet <> nil);

  FViceDataSet.Close;
  try
    QueryDrtp;
    FCriticalSection.Enter;
    try
      InternalChangeMainArea;
  //    SwitchViewers;
    finally
      FCriticalSection.Leave;
    end;
  //  FNeedToSwitch := not (FViewerList.Count = 0);
  except
    on E : Exception do
    begin
      WriteLog(Format('Exception[%s]: %s',[E.ClassName,E.Message]),lcException);
      //if E is EKCAccessRecv then
      Exit;
    end;
  end;

end;

procedure TMonClientDataSet.SwitchViewers;
var
  I : Integer;
begin
  for I := 0 to FViewerList.Count-1 do IMonClientView(FViewerList[I]).CreateNewList(nil);
end;

procedure TMonClientDataSet.TranslateConditionObject(
  AConditionObject: TConditionObject);
var
  I : Integer;
  tempRec : TConditionRec;
  tempSortRec : TSortRec;

  procedure DelEmptyConditions;
  begin
    if AConditionObject.Count < 1 then Exit;
    I := 0;
    while I < AConditionObject.Count do
      with AConditionObject[I] do
        if (Value = '') or (FieldIndex < 0) then AConditionObject.Delete(I)
          else Inc(I);
  end;
begin
  for I := 0 to AConditionObject.Count-1 do
  begin
    tempRec := AConditionObject[I];
    TranslateOneCondition(tempRec);
    AConditionObject[I] := tempRec;
  end;
  tempSortRec := AConditionObject.SortCondition;
  tempSortRec.FieldIndex := GetFieldIndex(Self.FindColumnCpackName(AConditionObject.SortCondition.Name));
  AConditionObject.SortCondition := tempSortRec;
  
  //ɾ���յĹ��������������Ż�����
  DelEmptyConditions;
end;

procedure TMonClientDataSet.TranslateOneCondition(
  var ConditionRec: TConditionRec);
begin
  case ConditionRec.Name of
    cnOprt : ConditionRec.FieldIndex := IndexForcnOprt; //GetFieldIndex('scust_no');
    cnCust : ConditionRec.FieldIndex := IndexForcnCust; //GetFieldIndex('sholder_ac_no');
    cnKinds : ConditionRec.FieldIndex := IndexForcnKinds; //GetFieldIndex('sstock_code');
    cnDeliverTime : ConditionRec.FieldIndex := IndexForcnDeliverTime; //GetFieldIndex('sdate1');
    cnTradeDir : ConditionRec.FieldIndex := IndexForcnTradeDir; //GetFieldIndex('sstatus2');
  else Raise Exception.CreateFmt('DataSet:%s meet an Unexpected Condition name:%d!',
    [Self.ClassName,Integer(ConditionRec.Name)]);
  end;
end;

procedure TMonClientDataSet.ViewConditionChanged(ViewIndex: Cardinal;
  ConditionObject: TConditionObject);
begin
{ DONE -ozpf -ca :
��ָ�������Ľӿڶ���ĸ����ݶ������°����������ɣ�Ȼ��
֪ͨ��Ӧ��Listener���л�������ж��Listener������֪ͨ����ȡ
�µ�Viewer�����������Ϊ���ӡ� }
end;

function TMonClientDataSet.FindColumnCpackName(ColName: string): string;
var
  I : Integer;
begin
  for I := 0 to High(StyleArray) do
  begin
    if AnsiSameText(StyleArray[I].Name, ColName) then
    begin
      Result := StyleArray[I].CPackName;
      Exit;
    end;
  end;
  Result := '';
end;

function TMonClientDataSet.GetDDNameByValue(const DDKind: TDDKinds;
  const Value: string): string;
begin
  //�����ڳ�ʼ����ʱ��ȡ��һ�����õ��ֵ�ĵ�ַ�б���cache���ӿ��ٶȡ�
  if DDKind = ddkNO then
  begin
    Result := Value;
    Exit;
  end;
  try
    Result := TIdObjectList(FDDObjList[Integer(DDKind)]).Find(Value).Name;
  except
    Result := Value;
  end;
end;

function TMonClientDataSet.GetTranslateStrByDD(const Index: Integer;
  const Value: string): string;
begin
  if Value = '' then
  begin
    Result := '';
    Exit;
  end;
  Result := GetDDNameByValue(GetDDKindsByIndex(Index),Value);
end;

procedure TMonClientDataSet.InitDDList;
{
var
  tempIDList : TIdObjectList;
  I : Integer;
}
begin
  { DONE -ozhupf -ca :
��ʼ�������õ������������ֵ�Ķ����б�ע�⣺Ϊ�����Ч�ʣ�
�б�Ķ������õ�˳���ǰ���ö�����͵�˳�����ġ� }
  with FDDObjList do
  begin
    Clear;
    Add(NeedIdObjectList(ddkMarketID));
    Add(NeedIdObjectList(ddkTradeDirID));
    Add(NeedIdObjectList(ddkContractStatusID));
    {
    tempIDList := TIdObjectList(Items[Count-1]);
    for I := 0 to tempIDList.Count - 1 do
    begin
      WriteLog(Format('Id(%s):Name(%s)',[tempIDList.Items[I].ID,tempIDList.Items[I].Name]),lcException);
    end;
    }
    Add(NeedIdObjectList(ddkEntrustTypeID));
    Add(NeedIdObjectList(ddkContractTypeID));
    Add(NeedIdObjectList(ddkKaiPingID));
    Add(NeedIdObjectList(ddkTouBaoID));
    Add(NeedIdObjectList(ddkMoneyTypeID));
    Add(NeedIdObjectList(ddkSeatID));
    Add(NeedIdObjectList(ddkInfoTypeID));  
  end;
end;

function TMonClientDataSet.GetDDKindsByIndex(
  const Index: Integer): TDDKinds;
var
  I : Integer;
begin
  for I := 0 to High(FIndexArray) do
    if Index = FIndexArray[I].Index then
    begin
      Result := FIndexArray[I].Kind;
      Exit;
    end;
  Result := ddkNO;
end;

procedure TMonClientDataSet.AddOneIndexKind(IndexName: string; AKind : TDDKinds);
var
  tempIndex : Integer;
begin
  tempIndex := GetFieldIndex(IndexName);
  if tempIndex <> -1 then
  begin
    SetLength(FIndexArray,Length(FIndexArray)+1);
    with FIndexArray[Length(FIndexArray)-1] do
    begin
      Index := tempIndex;
      Kind := AKind;
    end;
  end;
end;

procedure TMonClientDataSet.InitKindsIndex;
begin
  AddOneIndexKind('smarket_code',ddkMarket    );
  AddOneIndexKind('sstatus2',ddkTradeDir      );
  AddOneIndexKind('sstatus0',ddkContractStatus);
  AddOneIndexKind('sholder_type',ddkEntrustType  );
  AddOneIndexKind('sstat_type2',ddkContractType  );
  AddOneIndexKind('sstatus3',ddkKaiPing       );
  AddOneIndexKind('sstatus4',ddkTouBao        );
  AddOneIndexKind('sserial2',ddkSeat          );   
  AddOneIndexKind('scurrency_type',ddkMoneyType);
  AddOneIndexKind('sstat_type2',ddkContractStatus);
end;

procedure TMonClientDataSet.TellViewToUpdate;
var
  I : Integer;
begin
  for I := 0 to FViewerList.Count-1 do IMonClientView(FViewerList[I]).TellViewToUpdate;
end;

{ TMonClientViewer }

procedure TMonClientViewer.AddItem(BookMark: TBookmark);
begin
  FLock.Enter;
//  FOwnerDataSet.CriticalSection.Enter;
  try
    FOwnerDataSet.DataSet.GotoBookmark(BookMark);
    if FOwnerDataSet.MatchCondition(ConditionObject) then
    begin
      FAddOneData(FMainList);
      RevCount := RevCount + 1;
    end;
  finally
//    FOwnerDataSet.CriticalSection.Leave;
    FLock.Leave;
  end;  
end;

procedure TMonClientViewer.AddListener(Listener: IMessageListener);
begin
  FLock.Enter;
  try
    FListenerList.AddListener(Listener);
  finally
    FLock.Leave;
  end;
end;

function TMonClientViewer.ClearListener(Listener: IMessageListener) : Integer;
begin
  FLock.Enter;
  try
    FListenerList.RemoveListener(Listener);
    Result := FListenerList.Count;
  finally
    FLock.Leave;
  end;
end;

constructor TMonClientViewer.Create(Owner : TMonClientDataSet;
  AConditionObject : TConditionObject; Listener : IMessageListener);
begin
  FRevCount := 0;
  FLock := TCriticalSection.Create;
  MidSL := TStringList.Create;
  FNeedToSwitch := False;
  FStyleArray := Owner.StyleArray;
  FStyleCloCount := High(FStyleArray) + 1;
  FOwnerDataSet := Owner;
  Assert(FStyleArray<>nil);
  FListenerList := TMessageListenerSurport.Create(Self);
  FMainList := TMonClientDataList.Create;
  FViceList := TMonClientDataList.Create;
  if Listener <> nil then AddListener(Listener);
  ConditionObject := TConditionObject.Create;
  ConditionObject.Assign(AConditionObject);
  {$IFDEF Debug}
    LogCreate(Self);
  {$ENDIF}
end;

function TMonClientViewer.DataCount: Integer;
begin
//  SetLength(FMainList.FDataAA,FMainList.Count);
  Result := FMainList.Count;
end;

destructor TMonClientViewer.Destroy;
begin
  FListenerList.Free;
  FMainList.Free;
  FViceList.Free;
  FLock.Free;
  FreeAndNil(FConditionObject);
  MidSL.Free;
  inherited;
  {$IFDEF Debug}
    LogDestroy(Self);
  {$ENDIF}
end;

procedure TMonClientViewer.FAddOneData(List : TMonClientDataList);
var
  tempMonClientDataArray : TMonClientDataArray;
begin
  tempMonClientDataArray := FFGetCurRecStr;
  List.AddData(tempMonClientDataArray);
end;

procedure TMonClientViewer.FRefreshOneData;
var
  tempDataArray : TMonClientDataArray;
  I : Integer;
  function GetIndex(AFieldName : string) : Integer;
  var
    m,n : Integer;
    tempSL : TStringList;
    ValueToFind : string;
  begin
    Result := -1;
    tempSL := TStringList.Create;
    try
      m := FOwnerDataSet.DataSet.FindField(AFieldName).Index;
      Assert(m>-1);
      tempSL.CommaText := tempDataArray;
      if tempSL.Count <> FOwnerDataSet.DataSet.FieldCount then tempSL.Add('');
      ValueToFind := tempSL[m];
      for n := FMainList.Count-1 downto 0 do
      begin
        tempSL.CommaText := PChar(FMainList[n]);
        if tempSL[m] = ValueToFind then
        begin
          Result := n;
          Break;
        end;
      end;
    finally
      tempSL.Free;
    end;
  end;
begin
  { TODO -o����� -ca :
����DataSet�ĵ�ǰ�У�ͨ��һЩ�����жϣ�һ����ί�кŵȣ���
�ҵ����Ҹ���List,���û���ҵ�������ӡ�ʵ�ڲ��У���д���࣬����ʵ����󻯵�
���ơ������䡣 }
//  for I := 0 to FStyleCloCount -1 do
//    tempDataArray[I] := FOwnerDataSet.GetProperSubStr(FStyleArray[I].CPackName);
//  FMainList.AddData(tempDataArray);
//  tempDataArray := nil;
  tempDataArray := FFGetCurRecStr;
  case FOwnerDataSet.MonClientStyle  of
    mcsEntrust :
      begin
        I := GetIndex('lserial0');
        if I < 0 then FMainList.AddData(tempDataArray)
        else FMainList.RefreshData(I,tempDataArray);
      end;
    mcsBaginOn :
      begin
        I := GetIndex('lserial0');
        if I < 0 then FMainList.AddData(tempDataArray)
        else FMainList.RefreshData(I,tempDataArray);
      end;
    {
    mcsEvent :
      begin

      end;
    mcsHold :
      begin

      end;

    mcsMoney :
      begin

      end;
    mcsRisk :
      begin

      end;
    }
  end;
end;

procedure TMonClientViewer.GetInitViceList;
begin
{ TODO -ozpf -ca : �����Ƿ��л����ı�־����ò���DataList������Ҫ����MainData���ɡ� }
end;

procedure TMonClientViewer.CreateNewList(AConditionObject : TConditionObject);
var
  Thread : TDoSomeThingThread;
  Condtn : TConditionObject;
  procedure ThreadCreate(Viewer : TMonClientViewer; OperatedObj : TConditionObject);
  begin
    Viewer.InternalCreateNewList(OperatedObj);
  end;
begin
  Condtn := TConditionObject.Create;
  Condtn.Assign(AConditionObject);
  Thread := TDoSomeThingThread.Create(@ThreadCreate,Self,nil,Condtn);
  Thread.Resume;
end;

procedure TMonClientViewer.ListViewData(Sender: TObject; Item: TListItem);
var
  I, J : Integer;
  tempArray : TMonClientDataArray;
begin
{ DONE -o����� -ca :
ת�������γɶ��е�ʱ���ǰ������ݼ��ϵ�Field��˳�����γɵģ�
Ŀǰ�ǰ���CPack ��˳���γɵġ������ٶȱȽϿ죨��������10000
��ʱ��FindField������Ҫ10000ms���ң���������ֻ��Ҫ2300ms����
���ǣ��������ݱ���ʱ��Ҫ���ո����ĸ�ʽ������ת��һ�¡� }
  if Item.Index > FMainList.Count-1 then Exit;
//  tempArray := TMonClientDataArray(FMainList[Item.Index]);

  tempArray := PChar(FMainList[Item.Index]);

  MidSL.CommaText := tempArray;
//  Item.Caption := MidSL[0];
  J := FStyleArray[0].Order;
  Item.Caption := FOwnerDataSet.GetTranslateStrByDD(J,MidSL[J]);
  while MidSL.Count <> High(FStyleArray) + 1 do MidSL.Add('');
  for I := 1 to MidSL.Count-1 do
  begin
    J := FStyleArray[I].Order;
    Item.SubItems.Add(FOwnerDataSet.GetTranslateStrByDD(J,MidSL[J]));
  end;
//Item.SubItems.Add(FOwnerDataSet.GetTranslateStrByDD(I,MidSL[FStyleArray[I].Order]));
//    Item.SubItems.Add(MidSL[I]);
end;

procedure TMonClientViewer.ListViewDataFind(Sender: TObject;
  Find: TItemFind; const FindString: String; const FindPosition: TPoint;
  FindData: Pointer; StartIndex: Integer; Direction: TSearchDirection;
  Wrap: Boolean; var Index: Integer);
begin

end;

procedure TMonClientViewer.ListViewDataHint(Sender: TObject; StartIndex,
  EndIndex: Integer);
begin

end;

procedure TMonClientViewer.RefreshItem(Bookmark: TBookmark);
begin
  FLock.Enter;
//  FOwnerDataSet.CriticalSection.Enter;
  try
    FOwnerDataSet.DataSet.GotoBookmark(BookMark);
    if FOwnerDataSet.MatchCondition(ConditionObject) then
    begin
      FRefreshOneData;
      RevCount := RevCount + 1;
    end;
//      else FAddOneData(FMainList);
  finally
//    FOwnerDataSet.CriticalSection.Leave;
    FLock.Leave;
  end;
end;

procedure TMonClientViewer.SwitchData;
var
  tempList : TMonClientDataList;
begin
  tempList := FMainList;
  FMainList := FViceList;
  FViceList := tempList;
  FViceList.ClearData;
end;

function TMonClientViewer.SetConditionGetWorkList(
  AConditionObject: TConditionObject): TMonClientDataList;
var
  tempConObj : TConditionObject;
begin
  { DONE :
���ݴ������������ĸı䣬����Ϊ�µ����������ͷžɵĶ���
���ҷ�����Ҫ���и��ĵ�List�������в����� }
  ConditionObject.Free;
  //����Ĭ�ϵ���������
  if AConditionObject = nil then
  begin
    tempConObj := TConditionObject.Create;
    tempConObj.Style := mccsUpdate;
    ConditionObject := tempConObj;
  end
  else ConditionObject := AConditionObject;
  case ConditionObject.Style of
    mccsUpdate : Result := FViceList;
    mccsFilt   : Result := FViceList;
    mccsSort   :
      begin
        Result := FViceList;
        Result.CopyRefData(FMainList);
      end;
    else Result := FViceList;
  end;
end;

procedure TMonClientViewer.InternalCreateNewList(
  AConditionObject: TConditionObject);
var
  Msg : TMessage;
  List : TMonClientDataList;
  isLockDataSet : Boolean;
begin
  { DONE -ozpf -ca : ����MainDataSet�͹�������������MainData }
  //ע�����ﻥ�������˳��Ŀǰ�����Ӳ�������������
  //SendMessage������Ҳ��������������Ŀǰ����������֤�˼�ʱ���л�������֤���л���
  //�̰߳�ȫ��
  if AConditionObject.Style = mccsHeartBeat then
  begin
    try
      TryToResponseHeartBeat;
    finally
      AConditionObject.Free;
    end;
    Exit;
  end
  else if AConditionObject.Style = mccsFindItem then
  begin
    try
      TryToFindItem(AConditionObject);
    finally
      AConditionObject.Free;
    end;
    Exit;
  end;
  isLockDataSet := AConditionObject.Style <> mccsSort;
  if isLockDataSet then
    FOwnerDataSet.CriticalSection.Enter;
  FLock.Enter;
  try
    {$IFDEF Debug}
      WriteLog(Format('Begin Create ViewData:%d',[GetTickCount]),lcDebug);
    {$ENDIF}
    List := SetConditionGetWorkList(AConditionObject);
//    if FOwnerDataSet.DataSet.Active then
    if ConditionObject.Style = mccsSort then
    begin
      //�������ݼ��ϵ���������
      InternalSort(List);
    end
    else begin
//    begin
      List.ClearData;
      if not FOwnerDataSet.DataSet.Active then
      begin
        WriteLog(Format('DataSet(%s) is not active, so not any records will be added!',
          [FOwnerDataSet.Name]),lcException);
        Msg.Msg := WMMC_RefreshView;
        FListenerList.SendListenersMsg(Msg);
        Exit;
      end;
      FOwnerDataSet.DataSet.First;
      if ConditionObject.Count < 1 then
      begin
        while not FOwnerDataSet.DataSet.Eof do
        begin
          FAddOneData(List);
          FOwnerDataSet.DataSet.Next;
        end;
      end
      else begin
        while not FOwnerDataSet.DataSet.Eof do
        begin
          if FOwnerDataSet.MatchCondition(ConditionObject) then FAddOneData(List);
          FOwnerDataSet.DataSet.Next;
        end;
      end;
      {$IFDEF Debug}
        WriteLog(Format('Compl Create ViewData:%d',[GetTickCount]),lcDebug);
        WriteLog(Format('Have Added ViewData Count:%d',[List.Count]),lcDebug);
      {$ENDIF}
      InternalSort(List);
    end;
    Msg.Msg := WMMC_RefreshView;
    FListenerList.SendListenersMsg(Msg);
  finally
    FLock.Leave;
    if isLockDataSet then
      FOwnerDataSet.CriticalSection.Leave;
  end;
end;

function TMonClientViewer.FFGetCurRecStr: TMonClientDataArray;
var
//  tempDataArray : TMonClientDataArray;
  I : Integer;
begin
//  SetLength(tempDataArray,FStyleCloCount);
  Assert(FStyleCloCount>1);
  Result := FOwnerDataSet.GetProperSubStr(0);
  for I := 1 to FStyleCloCount -1 do
//    tempDataArray := tempDataArray + ',' + FOwnerDataSet.GetProperSubStr(FStyleArray[I].CPackName);
        Result := Result + ',' + FOwnerDataSet.GetProperSubStr(I);
//  if Result <> '' then Delete(Result,1,1);
//  Result := tempDataArray;
end;

procedure TMonClientViewer.SetFConditionObject(
  const Value: TConditionObject);
begin
  FConditionObject := Value;
  { DONE -o����� -ca : ����TranslateConditionObj��ת��Condition. }
  FOwnerDataSet.TranslateConditionObject(ConditionObject);
end;

procedure TMonClientViewer.InternalSort(AList: TMonClientDataList);
begin
  with ConditionObject.SortCondition do
  begin
    if FieldIndex < 0 then Exit;
    AList.SortedByDirInput(Dir,FieldIndex,FOwnerDataSet.DataSet.Fields[FieldIndex].DataType);
  end;
  {
//  tempSL := TStringList.Create;
//  try

    if ConditionObject.SortCondition.Dir = sdInc then
    begin
      for I := AList.Count-1 downto 0 do
        for J :=  0 to I-1 do
        begin
//          tempSL.CommaText := PChar(AList[J]);
//          tempPreValue := tempSL[ConditionObject.SortCondition.FieldIndex];
//          tempSL.CommaText := PChar(AList[J+1]);
//          tempNxtValue := tempSL[ConditionObject.SortCondition.FieldIndex];
//          if AnsiCompareText(tempPreValue,tempNxtValue) > 0 then
          tempPreValue := GetProIndexStr(PChar(AList[J]),ConditionObject.SortCondition.FieldIndex);
          tempNxtValue := GetProIndexStr(PChar(AList[J+1]),ConditionObject.SortCondition.FieldIndex));
          if AnsiCompareText(GetProIndexStr(PChar(AList[J]),ConditionObject.SortCondition.FieldIndex)
             ,GetProIndexStr(PChar(AList[J+1]),ConditionObject.SortCondition.FieldIndex)) > 0 then
          begin
            tempData := AList[J+1];
            AList[J+1] := AList[J];
            AList[J] := tempData;
          end;
        end;
    end
    else begin
      for I := 0 to AList.Count-1 do
        for J := AList.Count-1 downto I+1 do
        begin
        {
          tempSL.CommaText := PChar(AList[J]);
          tempNxtValue := tempSL[ConditionObject.SortCondition.FieldIndex];
          tempSL.CommaText := PChar(AList[J-1]);
          tempPreValue := tempSL[ConditionObject.SortCondition.FieldIndex];
          if AnsiCompareText(tempNxtValue,tempPreValue) > 0 then
        }
   {     if AnsiCompareText(GetProIndexStr(PChar(AList[J]),ConditionObject.SortCondition.FieldIndex)
             ,GetProIndexStr(PChar(AList[J-1]),ConditionObject.SortCondition.FieldIndex)) > 0 then
          begin
            tempData := AList[J-1];
            AList[J-1] := AList[J];
            AList[J] := tempData;
          end;
        end;
    end;
//  finally
//    tempSL.Free;
//  end;
   }
end;

procedure TMonClientViewer.SetRevCount(const Value: Integer);
var
  Msg : TMessage;
begin
  FLock.Enter;
  try
    FRevCount := Value;
    if FRevCount = REV_COUNT_FOR_CLIENTREFRESH then
    begin
      FRevCount := 0;
      Msg.Msg := WMMC_RefreshView;
      Msg.WParam := Refresh_Without_Switch;
      FListenerList.SendListenersMsg(Msg);
    end;
  finally
    FLock.Leave;
  end;
end;

function TMonClientViewer.GetRevCount: Integer;
begin
  FLock.Enter;
  try
    Result := FRevCount;
  finally
    FLock.Leave;
  end;
end;

procedure TMonClientViewer.TryToResponseHeartBeat;
var
  Msg : TMessage;
begin
  FLock.Enter;
  try
    if FRevCount > 0 then
    begin
      FRevCount := 0;
      Msg.Msg := WMMC_RefreshView;
      Msg.WParam := Refresh_Without_Switch;
      FListenerList.SendListenersMsg(Msg);
    end;
  finally
    FLock.Leave;
  end;
end;

procedure TMonClientViewer.FindProperIndexByValue(const Value: string;
  ValueStyle: TConditionName);
var
  tempCdn : TConditionObject;
  tempCdnRec : TConditionRec;
begin
  tempCdn := TConditionObject.Create;
  try
    tempCdn.Style := mccsFindItem;

    case ValueStyle of
      cnCust : tempCdnRec.FieldIndex := FOwnerDataSet.IndexForcnCust;
    else
      tempCdnRec.FieldIndex := -1;
    end;
    if tempCdnRec.FieldIndex < 0 then Exit;
    tempCdnRec.Value := Value;

    tempCdn.Add(tempCdnRec);
    CreateNewList(tempCdn);
  finally
    tempCdn.Free;
  end;
end;

procedure TMonClientViewer.TryToFindItem(
  AConditionObject: TConditionObject);
var
  Msg : TMessage;
  tempStr : string;
  I, tempIndex : Integer;
  FindedFlag : Boolean;
begin
  FLock.Enter;
  try
    tempStr := AConditionObject.Conditions[0].Value;
    FindedFlag := False;
    tempIndex := AConditionObject.Conditions[0].FieldIndex;
    for I := 0 to FMainList.Count - 1 do
      if AnsiSameText(GetIndexStr(PChar(FMainList[I]),tempIndex),tempStr) then
      begin
        FindedFlag := True;
        Break;
      end;

    if not FindedFlag then Exit;
    Msg.Msg := WMMC_ShowProperItem;
    Msg.WParam := I;
    FListenerList.SendListenersMsg(Msg);
  finally
    FLock.Leave;
  end;
end;

procedure TMonClientViewer.TellViewToUpdate;
var
  Msg : TMessage;
begin
  FLock.Enter;
  try
    Msg.Msg := WMMC_RefreshView;
    FListenerList.SendListenersMsg(Msg);
  finally
    FLock.Leave;
  end;
end;

{ TMonClientDataList }

function TMonClientDataList.AddData(var
  MonClientData: TMonClientDataArray): Integer;
begin
  Result := Add(PChar(MonClientData));
  if High(FDataAA) < Result then SetLength(FDataAA,(Result+1)*2);
  FDataAA[Result] := MonClientData;
end;

procedure TMonClientDataList.ClearData;
begin
  if FShareData then
  begin
    SetLength(FDataAA,0);
    FShareData := False;
  end
  else Finalize(FDataAA);
  Clear;
end;

procedure TMonClientDataList.CopyRefData(SrcList: TMonClientDataList);
var
  I : Integer;
  tempList : TDataAA;
//  tempData : TMonClientDataArray;
begin
  tempList := SrcList.GetShareData;
  SetLength(FDataAA,Length(tempList));
  for I := 0 to SrcList.Count-1 do
  begin
//    tempData := ;
    FDataAA[I] := tempList[I];
    Add(SrcList[I]);
  end;
end;

constructor TMonClientDataList.Create;
begin
  FShareData := False;
  FSortedStringList := TStringList.Create;
  FHaveSorted := False;
  {$IFDEF Debug}
    LogCreate(Self);
  {$ENDIF}
end;

procedure TMonClientDataList.CreateSortStrList(const Index: Integer);
var
  m : Integer;
begin
  FSortedStringList.Clear;
  FSortedStringList.Capacity := Self.Count;
  for m := 0 to Self.Count-1 do
    FSortedStringList.AddObject(GetIndexStr(PChar(Self.Items[m]),Index),TObject(m));
//  FSortedStringList.SaveToFile('c:\zpf.lst');
end;

destructor TMonClientDataList.Destroy;
begin
  ClearData;
  FSortedStringList.Free;
  inherited;
  {$IFDEF Debug}
    LogDestroy(Self);
  {$ENDIF}
end;

function TMonClientDataList.GetShareData: TDataAA;
begin
  FShareData := True;
  Result := FDataAA;
end;

procedure TMonClientDataList.ReArrangeItem(const Dir: TSortDir;const FieldType : TFieldType);
var
  I : Integer;
  tempList : TList;
begin
//  FSortedStringList.Sort;
  case FieldType of
    ftString : FSortedStringList.Sort;
    ftInteger : FSortedStringList.CustomSort(SortInt);
    ftFloat   : FSortedStringList.CustomSort(SortFloat);
  else Exit;
  end;

  tempList := TList.Create;
  tempList.Clear;
  tempList.Capacity := Self.Count;
  for I := 0 to Self.Count-1 do tempList.Add(nil);
  try
    if Dir = sdInc then
      for I := 0 to Self.Count-1 do
        tempList[I] := Self.Items[Integer(FSortedStringList.Objects[I])]
    else
      for I := 0 to Self.Count-1 do
        tempList[Self.Count-1-I] := Self.Items[Integer(FSortedStringList.Objects[I])];
    for I := 0 to Self.Count-1 do Self.Items[I] := tempList[I];
  finally
    tempList.Free;
  end;      
end;

procedure TMonClientDataList.RefreshData(Index: Integer;
  var MonClientData: TMonClientDataArray);
begin
  if Index = -1 then Exit;
  Assert(Index < Count);
  FDataAA[Index] := MonClientData;
  Items[Index] := PChar(MonClientData);
end;

procedure TMonClientDataList.SortedByDirInput(Dir: TSortDir;
  Index: Integer; FieldType : TFieldType; NeedToRebuild: Boolean);
begin
  if (not FHaveSorted) or NeedToRebuild then CreateSortStrList(Index);
  ReArrangeItem(Dir,FieldType);
end;

procedure TMonClientDataList.SwitchItem(const Index1, Index2: Integer);
var
  tempData : Pointer;
  tempStr : string;
begin
  tempData := Items[Index1];
  tempStr  := FSortedStringList[Index1];

  Items[Index1] := Items[Index2];
  FSortedStringList[Index1] := FSortedStringList[Index2];

  Items[Index2] := tempData;
  FSortedStringList[Index2] := tempStr;
end;

{ TEntrustMCDataSet }

procedure TEntrustMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_Entrust;

  //��ѯί�У�
  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);       //	����Ա	  ��ǰ����Ա
  BindOneParam(DataSet,'sserial2',ftChar,'');        //	ϯλ��	  ''
  BindOneParam(DataSet,'sholder_ac_no',ftChar,'');   //	�ͻ���	  ''
  BindOneParam(DataSet,'sserial1',ftChar,'');        //	�ͻ���	  ''
  BindOneParam(DataSet,'scust_auth',ftChar,'');      //	��Լ��	  ''
  BindOneParam(DataSet,'sbank_pwd2',ftChar,'');      //ί��״̬����
  BindOneParam(DataSet,'smain_flag',ftChar,'1');     //����ί�е����	'1'	--����
  BindOneParam(DataSet,'scurrency_type',ftChar,'');  //	����	  ''
end;

procedure TEntrustMCDataSet.InitKindsIndex;
begin
  inherited;
end;

function TEntrustMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

{ TMonClientDataArea }

{$IFDEF Debug}
constructor TMonClientDataArea.Create(OwendObj: Boolean);
begin
  inherited Create(OwendObj);
  LogCreate(Self);
end;

destructor TMonClientDataArea.Destroy;
begin
  inherited;
  LogDestroy(Self);
end;
{$ENDIF}

function TMonClientDataArea.FindCriticalSectionDataSet(DataSetStyle :
  TMonClientStyle): TMonClientDataSet;
var
  i : integer;
  CriticalSectionDataSet : TMonClientDataSet;
begin
  result:= nil;
  for i:=0 to count-1 do
  begin
    CriticalSectionDataSet := TMonClientDataSet(Items[i]);
    if CriticalSectionDataSet.MonClientStyle = DataSetStyle then
    begin
      result:= CriticalSectionDataSet;
      break;
    end;
  end;
end;

procedure TMonClientDataArea.Init;
var
  I : integer;
begin
  for I := 0 to Count - 1 do
  begin
    WriteStartProgress(Format('���ڳ�ʼ��%s������',[TMonClientDataSet(Items[I]).Name]));
    WriteLog(Format('���ڳ�ʼ��%s������',[TMonClientDataSet(Items[I]).Name]),lcKSClientStart);
    try
      TMonClientDataSet(Items[I]).Init;
    except
      on E : Exception do WriteLog(Format('Exception[%s]: %s',[E.ClassName,E.Message]),lcException);
    end;
  end;
end;

procedure TMonClientDataArea.LoadAllData(const FilePath: string);
var
  I : Integer;
  CurFilePath : string;
  tempDataSet : TMonClientDataSet;
begin
  if not DirectoryExists(FilePath) then Raise Exception.CreateFmt('FilePath: %s not exists!',[FilePath]);
  try
    if SwitchDataAreaThd <> nil then PushRevThread.Close;
    if SwitchDataAreaThd <> nil then SwitchDataAreaThd.Close;
    PushRevThread.Free;
    SwitchDataAreaThd.Free;
  except
    On E : Exception do
    begin
      WriteLog(Format('When Close PushRevThread and SwitchDataAreaThd Raise Error:%s',[E.Message]),lcException);
    end;
  end;
  CurFilePath := FilePath + '\';
  for I := 0 to Count - 1 do
  begin
    tempDataSet := TMonClientDataSet(Items[I]);
    if not FileExists(CurFilePath + Items[I].ClassName + MonClientDataFileExt) then Continue;
    tempDataSet.CriticalSection.Enter;
    try
      tempDataSet.DataSet.Close;
      tempDataSet.DataSet.LoadFromFile(CurFilePath + Items[I].ClassName + MonClientDataFileExt);
      tempDataSet.DataSet.FileOpenFlag := True;
      try
        tempDataSet.DataSet.Active := True;
      finally
        tempDataSet.DataSet.FileOpenFlag := False;
      end;
      tempDataSet.TellViewToUpdate;
    finally
      tempDataSet.CriticalSection.Leave;
    end;
  end;
end;

procedure TMonClientDataArea.SaveAllData(const FilePath: string);
var
  I : Integer;
  CurFilePath : string;
  fs : TFileStream;
  tempDataSet : TMonClientDataSet;
begin
  CurFilePath := FilePath + '\' + FormatDateTime('yyyymmdd',Now);
  ForceDirectories(CurFilePath);
  CurFilePath := CurFilePath + '\';
  for I := 0 to Count - 1 do
  begin
    tempDataSet := TMonClientDataSet(Items[I]);
    if not tempDataSet.DataSet.Active then Continue;
    tempDataSet.CriticalSection.Enter;
    try
      tempDataSet.DataSet.SaveToFile(CurFilePath + Items[I].ClassName + MonClientDataFileExt);
    finally
      tempDataSet.CriticalSection.Leave;
    end;
  end;
end;

function TMonClientDataArea.SwitchWorkArea: Boolean;
  procedure TellThreadSwitch(
    Sender: TMonClientDataSet);
  begin
    if Sender is TMonClientDataSet then
      if Sender.NeedToSwitch then Sender.SwitchDataSet;
  end;
var
  I, MaxCount, SMCount : integer;
  tempThreadList : TObjectList;
  tempSM : TSemaphore;
begin
  { DONE -o����� : ����л������� }
  tempThreadList := TObjectList.Create(False);
  MaxCount := Self.Count;
  tempSM := TSemaphore.Create(MaxCount,MaxCount*3,'');
  try
    for I := 0 to Count - 1 do
//      if TMonClientDataSet(Self.Items[I]).NeedToSwitch then
        tempThreadList.Add(TDoSomeThingThread.Create(
                              @TellThreadSwitch,
                              Self.Items[I],
                              tempSM
                              )
                           );
    for I := 0 to tempThreadList.Count - 1 do
      TDoSomeThingThread(tempThreadList.Items[I]).Resume;
    repeat
      try
        SMCount := tempSM.SelfReleaseSemaphore(1);
        if SMCount <> 0 then Sleep(100);
      except
        Break;
        Raise;
      end;
    until SMCount = 0;
  finally
    tempSM.Free;
    tempThreadList.Free;
  end;
  Result := True;
end;

procedure TEntrustMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
var
  EntrustNO : Integer;
  tempIndex : Integer;
//  tempField : TxtDB.TTextField;
  Finded : Boolean;
begin
  inherited;
  if not NeedRefresh then
  begin
    with DataSet.Data.TextDB do
    begin
      Append;
      with PBody^ do
      begin
        Move(lserial0      ,FindField('lserial0').GetDataBuffer^,SizeOf(Integer));              //out	ί�к�  	lserial0
        Move(sholder_ac_no ,FindField('sholder_ac_no').GetDataBuffer^,Length(sholder_ac_no));   //out	�ͻ���  	sholder_ac_no
        Move(sholder_ac_no2,FindField('sholder_ac_no2').GetDataBuffer^,Length(sholder_ac_no2)); //out	���ױ���	sholder_ac_no2
        Move(sstatus2      ,FindField('sstatus2').GetDataBuffer^,Length(sstatus2));             //out	��������	sstatus2
        Move(smarket_code  ,FindField('smarket_code').GetDataBuffer^,Length(smarket_code));     //out	����������	smarket_code
        Move(sstock_code   ,FindField('sstock_code').GetDataBuffer^,Length(sstock_code));       //out	Ʒ�ִ���	sstock_code
        Move(sdate1        ,FindField('sdate1').GetDataBuffer^,Length(sdate1));                 //out	������  	sdate1
        Move(lvol0         ,FindField('lvol0').GetDataBuffer^,SizeOf(Integer));                 //out	�걨����	lvol0
        Move(damt0         ,FindField('damt0').GetDataBuffer^,SizeOf(Double));                  //out	�걨�۸�	damt0
        Move(sstatus3      ,FindField('sstatus3').GetDataBuffer^,Length(sstatus3));             //out	��ƽ���	sstatus3
        Move(sstatus4      ,FindField('sstatus4').GetDataBuffer^,Length(sstatus4));             //out	Ͷ�����	sstatus4
        Move(sstat_type2   ,FindField('sstat_type2').GetDataBuffer^,Length(sstat_type2));       //out	ί������	sstat_type2
        Move(sholder_type  ,FindField('sholder_type').GetDataBuffer^,Length(sholder_type));     //out	ί�з�ʽ	sholder_type
        Move(stime0        ,FindField('stime0').GetDataBuffer^,Length(stime0));                 //out	ί��ʱ��	stime0
        Move(sserial2      ,FindField('sserial2').GetDataBuffer^,Length(sserial2));             //out	ϯλ��  	sserial2
        Move(sstatus0      ,FindField('sstatus0').GetDataBuffer^,Length(sstatus0));             //out	ί��״̬	sstatus0
        Move(lwithdraw_flag,FindField('lwithdraw_flag').GetDataBuffer^,SizeOf(LongInt));        //out	�޸�����	lwithdraw_flag
      end;
    end;
    DataSet.Last;
    BookMark := DataSet.GetBookmark;
  end
  else begin
    //�����ľ��Ǹ���ί�е���
    EntrustNO := PBody.lserial0;
    tempIndex := DataSet.FindField(DBFN_EntrustNO).Index;
    Finded := False;
    DataSet.First;
    while not DataSet.Eof do
    begin
      if DataSet.Fields[tempIndex].AsInteger = EntrustNO then
      begin
        Finded := True;
        //����ί�С�
        with DataSet.Data.TextDB do
        begin
          with PBody^ do
          begin
          {
            Move( lserial0,FindField('lserial0').GetDataBuffer^,SizeOf(Integer));              //out	ί�к�  	lserial0

            with FindField('sholder_ac_no') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sholder_ac_no ,GetDataBuffer^,Length(sholder_ac_no));   //out	�ͻ���  	sholder_ac_no
            end;

            with FindField('sholder_ac_no2') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sholder_ac_no2 ,GetDataBuffer^,Length(sholder_ac_no2));   //out	���ױ���	sholder_ac_no2
            end;

            with FindField('sstatus2') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sstatus2 ,GetDataBuffer^,Length(sstatus2));   //out	��������	sstatus2
            end;

            with FindField('smarket_code') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(smarket_code ,GetDataBuffer^,Length(smarket_code));   //out	����������	smarket_code
            end;

            with FindField('sstock_code') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sstock_code ,GetDataBuffer^,Length(sstock_code));   //out	Ʒ�ִ���	sstock_code
            end;

            with FindField('sdate1') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sdate1 ,GetDataBuffer^,Length(sdate1));   //out	������  	sdate1
            end;

            Move(lvol0         ,FindField('lvol0').GetDataBuffer^,SizeOf(Integer));                 //out	�걨����	lvol0
            Move(damt0         ,FindField('damt0').GetDataBuffer^,SizeOf(Double));                  //out	�걨�۸�	damt0

            with FindField('sstatus3') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sstatus3 ,GetDataBuffer^,Length(sstatus3));   //out	��ƽ���	sstatus3
            end;

            with FindField('sstatus4') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sstatus4 ,GetDataBuffer^,Length(sstatus4));   //out	Ͷ�����	sstatus4
            end;

            //Move(sstat_type2   ,FindField('sstat_type2').GetDataBuffer^,Length(sstat_type2));       //out	ί������	sstat_type2
            //Move(sholder_type  ,FindField('sholder_type').GetDataBuffer^,Length(sholder_type));     //out	ί�з�ʽ	sholder_type
            //Move(stime0        ,FindField('stime0').GetDataBuffer^,Length(stime0));                 //out	ί��ʱ��	stime0

            with FindField('sserial2') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sserial2 ,GetDataBuffer^,Length(sserial2));   //out	ϯλ��  	sserial2
            end;
           }

            with FindField('sstatus0') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sstatus0 ,GetDataBuffer^,Length(sstatus0));   //out	ί��״̬	sstatus0
            end;

            Move(lwithdraw_flag,FindField('lwithdraw_flag').GetDataBuffer^,SizeOf(LongInt));        //out	�޸�����	lwithdraw_flag

            with FindField('sorder0') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sorder0 ,GetDataBuffer^,Length(sorder0));   //out	ϵͳ��  	sorder0         @
            end;

            Move(lvol2         ,FindField('lvol2').GetDataBuffer^,SizeOf(Integer));                 //out	ʣ������	lvol2           @
            Move(lvol1         ,FindField('lvol1').GetDataBuffer^,SizeOf(Integer));                 //out	�ɽ�����	lvol1           @
            //ί�лر���damt2,�ɽ��ر���damt0.
            if damt2 <> 0 then
              Move(damt2         ,FindField('damt2').GetDataBuffer^,SizeOf(Double))                  //out	�ɽ��۸�	damt2           @
            else Move(damt0         ,FindField('damt2').GetDataBuffer^,SizeOf(Double));                  //out	�ɽ��۸�	damt2           @

            {
            with FindField('sholder_type2') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(sholder_type2 ,GetDataBuffer^,Length(sholder_type2));   //out	������	sholder_type2   @
            end;
            }
            with FindField('snote') do
            begin
              FillChar(GetDataBuffer^,Size,0);
              Move(saddr2 ,GetDataBuffer^,Length(saddr2));   //out	��ע    	saddr2          @
            end;
          end;
        end;
        BookMark := DataSet.GetBookmark;
        Exit;
      end;
      DataSet.Next;
    end;
    
    //û���ҵ����ί�У����Ӹ�ί�С�
    if not Finded then
      InternalAddRevData(BookMark,Finded,RequestType,PBody);
    {}
  end;
end;

{ TQueryViceDataAreaThd }

constructor TQueryViceDataAreaThd.Create(SleepTimeInv: Cardinal);
begin
  inherited Create(False);
  FSleepTime := SleepTimeInv;
  FSleepPerTime := TimeForPerSleep;
  FSleepCount := FSleepTime div FSleepPerTime;

  FHaveSleepedCount := 0;
  FirstSwitchWorkArea;
end;

procedure TQueryViceDataAreaThd.InternalExecute;
var
  BeginTime, OutedTime : Cardinal;
  SwitchRlt : Boolean;
begin
  Sleep(FSleepPerTime);
  Inc(FHaveSleepedCount);
  if FHaveSleepedCount >= FSleepCount then
  begin
    SwitchRlt := False;
    BeginTime := GetTickCount;
    FHaveSleepedCount := 0;

    HeartBeatDS.SwitchDataSet;
    if HeartBeatDS.ConnectStatus = cnsNormal then
    begin
      {$IFDEF Debug}
      WriteLog(Format('%s Begin SwitchWorkArea!',[Self.ClassName]),lcTempDebug);
      {$ENDIF}
      try
        try
          SwitchRlt := WorkArea.SwitchWorkArea;
        except
          Terminate;
          Raise;
        end;
      finally
      {$IFDEF Debug}
        WriteLog(Format('%s Complete SwitchWorkArea!',[Self.ClassName]),lcTempDebug);
      {$ENDIF}
        if not SwitchRlt then
        begin
          Terminate;
          {$IFDEF Debug}
          WriteLog(Format('Something wrong when %s try to Complete SwitchWorkArea, now close this thread!',
            [Self.ClassName]),lcException);
          {$ENDIF}
        end;
      end;
    end;
      
    OutedTime := GetTickCount - BeginTime;
    Inc(FHaveSleepedCount,OutedTime div FSleepPerTime + 1);
    Sleep(OutedTime mod FSleepPerTime);
  end;
end;

procedure InitAll(OffLine : Boolean);
  procedure InitWorkArea;
  begin
    WorkArea.Add(TEntrustMCDataSet.Create(DSN_Entrust,TKCDatabase(DatabaseModule.GetDataBase),mcsEntrust,True));
    WorkArea.Add(TBaginOnMCDataSet.Create(DSN_BaginOn,TKCDatabase(DatabaseModule.GetDataBase),mcsBaginOn,True));
    WorkArea.Add(THoldMCDataSet.Create(DSN_HoldGood,TKCDatabase(DatabaseModule.GetDataBase),mcsHold,True));
    WorkArea.Add(TMoneyMCDataSet.Create(DSN_Money,TKCDatabase(DatabaseModule.GetDataBase),mcsMoney,True));
    WorkArea.Add(TRiskMCDataSet.Create(DSN_Risk,TKCDatabase(DatabaseModule.GetDataBase),mcsRisk,True));
    WorkArea.Add(TEventMCDataSet.Create(DSN_Event,TKCDatabase(DatabaseModule.GetDataBase),mcsEvent,True));//
  end;
  procedure InitThreads;
  var
    ConfigSystem: IConfigSystem;
  begin
    HeartBeatDS := THeartBeatMCDataSet.Create(DSN_HeartBeat,
      TKCDatabase(DatabaseModule.GetDataBase),mcsEvent,True);//
    WriteStartProgress(Format('���ڽ�����%s����ԱΪ�����Ĳ�ѯ...',[Context.ParamData(svOperatorNoName).AsString]));
    SwitchDataAreaThd := TQueryViceDataAreaThd.Create(SleepTimeBetweenQuery);
    ////���������������߳�
    WriteStartProgress('���ڴ������������߳�...');
    ConfigSystem := Context.GetConfigSystem;
    PushRevThread := TPushRevThread.Create(
      Context.ParamData(svBatchNoName).AsInteger,
      PChar(ConfigSystem.ReadString(ccServer, ckIP, cdIP)),
      ConfigSystem.ReadInteger(ccServer, ckPort, cdPort),
      Context.ParamData(svFuncNoName).AsInteger);
  end;
begin
  WorkArea := TMonClientDataArea.Create(True);
  WriteStartProgress('���ڴ�����������...');
  InitWorkArea;
  if OffLine then Exit;
  WriteStartProgress('���ڴ����߳�...');
  InitThreads;
end;

procedure StarAllThreads;
begin
  SwitchDataAreaThd.Resume;
  PushRevThread.Open;
end;

procedure CloseAll;
  procedure FreeThreads;
  begin
    ////�رս������������߳�
    if PushRevThread <> nil then
    begin
      PushRevThread.Close;
      FreeAndNil(PushRevThread);
    end;
    if SwitchDataAreaThd <> nil then
    begin
      SwitchDataAreaThd.Close;
      SwitchDataAreaThd.Free;
    end;
  end;
begin
  FreeThreads;
  HeartBeatDS.Free;
  WorkArea.Free;
end;

procedure TQueryViceDataAreaThd.FirstSwitchWorkArea;
var
  SwitchRlt : Boolean;
begin
{$IFDEF Debug}
  WriteLog(Format('%s Begin SwitchWorkArea!',[Self.ClassName]),lcTempDebug);
{$ENDIF}
  try
    try
      SwitchRlt := WorkArea.SwitchWorkArea;
    except
      Terminate;
      Raise;
    end;
  finally
{$IFDEF Debug}
    WriteLog(Format('%s Complete SwitchWorkArea!',[Self.ClassName]),lcTempDebug);
{$ENDIF}
    if not SwitchRlt then
    begin
      Terminate;
{$IFDEF Debug}
      WriteLog(Format('Something wrong when %s try to Complete SwitchWorkArea, now close this thread!',
        [Self.ClassName]),lcException);
{$ENDIF}
    end;
  end;
end;

{ TConditionObject }

function TConditionObject.Add(Condition: TConditionRec): Integer;
var
  I : Integer;
begin
  ProcessConditionRec(Condition);
  for I := 0 to Count-1 do
    if FConditions[I].Name = Condition.Name then
    begin
      FConditions[I].FieldIndex := Condition.FieldIndex;
      FConditions[I].Operator := Condition.Operator;
      FConditions[I].Value := Condition.Value;
      if FConditions[I].Value = '' then
      begin
        Delete(I);
        Result := -1;
      end
      else Result := I;
      Exit;
    end;
  if Condition.Value = '' then
  begin
    Result := -1;
    Exit;
  end;
  Result := Count;
  SetLength(FConditions,Result+1);
  FConditions[Result] := Condition;
  FCount := Length(FConditions);
end;

procedure TConditionObject.Assign(ConditionObject: TConditionObject);
var
  I : Integer;
begin
  if ConditionObject = nil then Exit;
  FStyle := ConditionObject.Style;
  FSortCondition := ConditionObject.SortCondition;
  FCount := ConditionObject.Count;
  SetLength(FConditions,ConditionObject.Count);
  for I := 0 to ConditionObject.Count - 1 do
  begin
//    StrCopy(Pchar(FConditions[I].Name),Pchar(ConditionObject[I].Name));
//    StrCopy(Pchar(FConditions[I].Value),Pchar(ConditionObject[I].Value));
    FConditions[I].Name := ConditionObject[I].Name;
    FConditions[I].Value := ConditionObject[I].Value;
    FConditions[I].FieldIndex := ConditionObject[I].FieldIndex;
    FConditions[I].Operator := ConditionObject[I].Operator;
  end;
end;

{
function TConditionObject.Count: Integer;
begin
  Result := High(FConditions) + 1;
end;
}

function TConditionObject.ConditionByName(
  Name: TConditionName): PConditionRec;
var
  I : Integer;
  tempCdn : TConditionRec;
begin
  Result := nil;
  for I := 0 to Count-1 do
    if Conditions[I].Name = Name then
    begin
      tempCdn := Conditions[I];
      Result := @tempCdn;
      Exit;
    end;
end;

function TConditionObject.ConditionValueByName(Name: TConditionName): string;
var
  tempCondition : PConditionRec;
begin
  tempCondition := ConditionByName(Name);
  if tempCondition <> nil then Result := tempCondition.Value
    else Result := '';
end;

constructor TConditionObject.Create;
begin
  inherited Create(nil);
//  inherited;
  FCount := 0;
  {$IFDEF Debug}
//    LogCreate(Self);
  {$ENDIF}
end;

procedure TConditionObject.DefineProperties(Filer: TFiler);
begin
  inherited;
  Filer.DefineBinaryProperty('Data', ReadData, WriteData, True);
end;

function TConditionObject.Delete(Index : Integer): Boolean;
var
  I : Integer;
begin
  if Index >= Count then Result := False else Result := True;
  if not Result then Exit;
  for I := Index to Count-2 do Conditions[I] := Conditions[I+1];
  SetLength(FConditions,Count-1);
  Result := True;
  FCount := Length(FConditions);
end;

destructor TConditionObject.Destroy;
begin
  Finalize(FConditions);
  inherited;
  {$IFDEF Debug}
//    LogDestroy(Self);
  {$ENDIF}
end;

function TConditionObject.Get(Index: Integer): TConditionRec;
begin
  if Index > Count-1 then Raise Exception.CreateFmt('Conditions(%d) out of List(%d)!',[Index,Count]);
  Result := FConditions[Index];
end;

procedure TConditionObject.ProcessConditionRec(var Rec: TConditionRec);
const
  OrOperatorForMC = ',';

  function GetValidValue(const RawValue : string) : string;
  begin
    Result := '';
    if Length(Trim(RawValue)) = 0 then Exit;
    Result := Trim(RawValue);
    while Result[1] = OrOperatorForMC do
    begin
      System.Delete(Result,1,1);
      if Length(Result) = 0 then Exit;
    end;
    while Result[Length(Result)] = OrOperatorForMC do
    begin
      System.Delete(Result,Length(Result),1);
      if Length(Result) = 0 then Exit;
    end;
  end;
begin
  with Rec do
  begin
    Value := GetValidValue(Value);
    if Pos(OrOperatorForMC,Value) > 0 then Operator := loLike;
  end;
end;

procedure TConditionObject.Put(Index: Integer; const Value: TConditionRec);
begin
  if Index > Count-1 then Raise Exception.CreateFmt('Conditions(%d) out of List(%d)!',[Index,Count]);
  FConditions[Index] := Value;
end;

procedure TConditionObject.ReadData(Stream: TStream);
var
  Size : Integer;
  I : Integer;
  ItemHeader: PItemHeader;
  PSort : PSrotRec;
  PRec : PConditionRec;
  tempCondition : TConditionRec;
begin
  Finalize(FConditions);
  Stream.ReadBuffer(Size, SizeOf(Integer));

  ItemHeader := AllocMem(Size);
  try
    Stream.ReadBuffer(ItemHeader^.Count, Size - SizeOf(Integer));
    Assert(ItemHeader^.Count = Count);
    FCount := 0;
    PSort := @ItemHeader^.Items;
    with SortCondition do
    begin
      FieldIndex := PSort.FieldIndex;
      Dir := PSort.Dir;
      Name := PSort.Name;
    end;

    PRec := @ItemHeader^.Items;
    Inc(Integer(PRec),SizeOf(TSortRec) - 255 + Length(PSort.Name));
    for I := 0 to ItemHeader^.Count - 1 do
    begin
      with tempCondition do
      begin
        Name := PRec.Name;
        FieldIndex := PRec.FieldIndex;
        Operator := PRec.Operator;
        Value := PRec.Value;
        Inc(Integer(PRec),SizeOf(TConditionRec) - 255 + Length(PRec.Value));
      end;
      Add(tempCondition);
    end;
  finally
    FreeMem(ItemHeader,Size);
  end;
end;

procedure TConditionObject.WriteData(Stream: TStream);
var
  Size : Integer;
  I : Integer;
  ItemHeader: PItemHeader;
  PSort : PSrotRec;
  PRec : PConditionRec;
begin
  Size := SizeOf(TItemHeader);
  Size := Size + SizeOf(TSortRec) - 255 + Length(SortCondition.Name)
     + Count * (SizeOf(TConditionRec) - 255);
  for I := 0 to Count - 1 do Inc(Size,Length(Conditions[I].Value));

  ItemHeader := AllocMem(Size);
  try
    ItemHeader.Size := Size;
    ItemHeader.Count := Count;

    PSort := @ItemHeader^.Items;
    with SortCondition do
    begin
      PSort.FieldIndex := FieldIndex;
      PSort.Dir := Dir;
      PSort.Name := Name;
    end;

    PRec := @ItemHeader^.Items;
    Inc(Integer(PRec),SizeOf(TSortRec) - 255 + Length(PSort.Name));
    for I := 0 to Count - 1 do
    begin
      with Conditions[I] do
      begin
        PRec.Name := Name;
        PRec.FieldIndex := FieldIndex;
        PRec.Operator := Operator;
        PRec.Value := Value;
        Inc(Integer(PRec),SizeOf(TConditionRec) - 255 + Length(PRec.Value));
      end;
    end;
    Stream.WriteBuffer(ItemHeader^, Size);
  finally
    FreeMem(ItemHeader,Size);
  end;
end;

{ TBaginOnMCDataSet }

procedure TBaginOnMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_BaginOn;

  //��ѯ�ɽ���
  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);    // 	����Ա	    ��ǰ����Ա
  BindOneParam(DataSet,'sserial2',ftChar,'');          // 	ϯλ��	    ''
  BindOneParam(DataSet,'sholder_ac_no',ftChar,'');     // 	�ͻ���	    ''
  BindOneParam(DataSet,'sserial1',ftChar,'');          // 	�ͻ���	    ''
  BindOneParam(DataSet,'scust_auth',ftChar,'');        // 	��Լ��	    ''
  BindOneParam(DataSet,'sstatus1',ftChar,'0');          // �ϲ���־	    '0'    --���ϲ�
  BindOneParam(DataSet,'smain_flag',ftChar,'1');        // ���гɽ������    '1'    --����
  BindOneParam(DataSet,'scurrency_type',ftChar,'');    // 	����	    ''

end;

procedure TBaginOnMCDataSet.InitKindsIndex;
begin
  inherited;
end;

function TBaginOnMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

procedure TBaginOnMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  inherited;
  if not NeedRefresh then
  begin
    with DataSet.Data.TextDB do
      begin
        Append;
        with PBody^ do
        begin
          Move(lserial0      ,FindField('lserial0').GetDataBuffer^,SizeOf(Integer));              //out	ί�к�  	lserial0
          Move(sholder_ac_no ,FindField('sholder_ac_no').GetDataBuffer^,Length(sholder_ac_no));   //out	�ͻ���  	sholder_ac_no
          Move(sholder_ac_no2,FindField('sholder_ac_no2').GetDataBuffer^,Length(sholder_ac_no2)); //out	���ױ���	sholder_ac_no2
          Move(sstatus2      ,FindField('sstatus2').GetDataBuffer^,Length(sstatus2));             //out	��������	sstatus2
          Move(smarket_code  ,FindField('smarket_code').GetDataBuffer^,Length(smarket_code));     //out	����������	smarket_code
          Move(sstock_code   ,FindField('sstock_code').GetDataBuffer^,Length(sstock_code));       //out	Ʒ�ִ���	sstock_code
          Move(sdate1        ,FindField('sdate1').GetDataBuffer^,Length(sdate1));                 //out	������  	sdate1
          Move(lvol0         ,FindField('lvol1').GetDataBuffer^,SizeOf(Integer));                 //out	�걨����	lvol0
          Move(damt0         ,FindField('damt2').GetDataBuffer^,SizeOf(Double));                  //out	�걨�۸�	damt0
          Move(sstatus3      ,FindField('sstatus3').GetDataBuffer^,Length(sstatus3));             //out	��ƽ���	sstatus3
          Move(sstatus4      ,FindField('sstatus4').GetDataBuffer^,Length(sstatus4));             //out	Ͷ�����	sstatus4
          //Move(sstat_type2   ,FindField('sstat_type2').GetDataBuffer^,Length(sstat_type2));       //out	ί������	sstat_type2
          //Move(sholder_type  ,FindField('sholder_type').GetDataBuffer^,Length(sholder_type));     //out	ί�з�ʽ	sholder_type
          //Move(stime0        ,FindField('stime0').GetDataBuffer^,Length(stime0));                 //out	ί��ʱ��	stime0
          Move(sserial2      ,FindField('sserial2').GetDataBuffer^,Length(sserial2));             //out	ϯλ��  	sserial2
  //        Move(sstatus0      ,FindField('sstatus0').GetDataBuffer^,Length(sstatus0));             //out	ί��״̬	sstatus0
  //        Move(lwithdraw_flag,FindField('lwithdraw_flag').GetDataBuffer^,SizeOf(LongInt));        //out	�޸�����	lwithdraw_flag
          Move(sorder0       ,FindField('sorder0').GetDataBuffer^,Length(sorder0));              // out	ϵͳ��  	sorder0
          Move(lvol11         ,FindField('lvol11').GetDataBuffer^,SizeOf(Integer));                // out	�ɽ���  	lvol11
          Move(sserial0      ,FindField('sserial0').GetDataBuffer^,Length(sserial0));             // out	�������ɽ���	sserial0
  //        Move(lvol2         ,FindField('lvol2').GetDataBuffer^,SizeOf(Integer));                 // out	ʣ������	lvol2
  //        Move(damt5         ,FindField('damt5').GetDataBuffer^,SizeOf(Double));                  // out	�ɽ�����	damt5
        end;
    end;
    DataSet.Last;
    BookMark := DataSet.GetBookmark;
  end
  //��������ɹ�������ί�б�����ɽ���ͬһί�к��ж�����¼���������һ����״̬��
  else begin
   { DONE -o����� -ca : �ɽ���û��ί��״̬�������޸ġ� }
    Exit;
  {
    EntrustNO := PBody.lserial0;
    tempIndex := DataSet.FindField(DBFN_EntrustNO).Index;

    DataSet.Last;
    while not DataSet.Bof do
    begin
      if DataSet.Fields[tempIndex].AsInteger = EntrustNO then
      begin
      
      
        with DataSet.Data.TextDB do
        begin
          with PBody^ do
          begin
            Move(lserial0      ,FindField('lserial0').GetDataBuffer^,SizeOf(Integer));              //out	ί�к�  	lserial0
            Move(sholder_ac_no ,FindField('sholder_ac_no').GetDataBuffer^,Length(sholder_ac_no));   //out	�ͻ���  	sholder_ac_no
            Move(sholder_ac_no2,FindField('sholder_ac_no2').GetDataBuffer^,Length(sholder_ac_no2)); //out	���ױ���	sholder_ac_no2
            Move(sstatus2      ,FindField('sstatus2').GetDataBuffer^,Length(sstatus2));             //out	��������	sstatus2
            Move(smarket_code  ,FindField('smarket_code').GetDataBuffer^,Length(smarket_code));     //out	����������	smarket_code
            Move(sstock_code   ,FindField('sstock_code').GetDataBuffer^,Length(sstock_code));       //out	Ʒ�ִ���	sstock_code
            Move(sdate1        ,FindField('sdate1').GetDataBuffer^,Length(sdate1));                 //out	������  	sdate1
            Move(lvol0         ,FindField('lvol1').GetDataBuffer^,SizeOf(Integer));                 //out	�걨����	lvol0
            Move(damt0         ,FindField('damt2').GetDataBuffer^,SizeOf(Double));                  //out	�걨�۸�	damt0
            Move(sstatus3      ,FindField('sstatus3').GetDataBuffer^,Length(sstatus3));             //out	��ƽ���	sstatus3
            Move(sstatus4      ,FindField('sstatus4').GetDataBuffer^,Length(sstatus4));             //out	Ͷ�����	sstatus4
            //Move(sstat_type2   ,FindField('sstat_type2').GetDataBuffer^,Length(sstat_type2));       //out	ί������	sstat_type2
            //Move(sholder_type  ,FindField('sholder_type').GetDataBuffer^,Length(sholder_type));     //out	ί�з�ʽ	sholder_type
            //Move(stime0        ,FindField('stime0').GetDataBuffer^,Length(stime0));                 //out	ί��ʱ��	stime0
            Move(sserial2      ,FindField('sserial2').GetDataBuffer^,Length(sserial2));             //out	ϯλ��  	sserial2
    //        Move(sstatus0      ,FindField('sstatus0').GetDataBuffer^,Length(sstatus0));             //out	ί��״̬	sstatus0
    //        Move(lwithdraw_flag,FindField('lwithdraw_flag').GetDataBuffer^,SizeOf(LongInt));        //out	�޸�����	lwithdraw_flag
            Move(sorder0       ,FindField('sorder0').GetDataBuffer^,Length(sorder0));              // out	ϵͳ��  	sorder0
            Move(lvol11         ,FindField('lvol11').GetDataBuffer^,SizeOf(Integer));                // out	�ɽ���  	lvol11
            Move(sserial0      ,FindField('sserial0').GetDataBuffer^,Length(sserial0));             // out	�������ɽ���	sserial0
    //        Move(lvol2         ,FindField('lvol2').GetDataBuffer^,SizeOf(Integer));                 // out	ʣ������	lvol2
    //        Move(damt5         ,FindField('damt5').GetDataBuffer^,SizeOf(Double));                  // out	�ɽ�����	damt5
          end;
        end;
       
        Exit;
      end;
      DataSet.Prior;
    end;
    }
  end;
end;


{ TEventMCDataSet }

procedure TEventMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_Event;

  { DONE -o����� : �¼���ѯ��û�к�̨��û�а취�Ӳ����� }

  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);   // in	����Ա		scust_no
  BindOneParam(DataSet,'sstatus0',ftChar,'');                 // in	��Ϣ����	sstatus0
  BindOneParam(DataSet,'scust_no2',ftChar,'');                // in	Ŀ�Ĳ���Ա	scust_no2
  BindOneParam(DataSet,'sholder_ac_no',ftChar,'');            // in	�ͻ���		sholder_ac_no
  BindOneParam(DataSet,'sstatus4',ftChar,'0');                // in	���͸��ͻ����	sstatus4
  BindOneParam(DataSet,'sdate0',ftChar,''{FormatDateTime('yyyymmdd',GetSysNow)});// in     ��ʼ����	sdate0			��ǰϵͳ��������
  BindOneParam(DataSet,'sdate1',ftChar,'');                   // in     ��������	sdate1			''

end;

procedure TEventMCDataSet.InitKindsIndex;
begin
  AddOneIndexKind('sstatus0',ddkInfoType);
end;

function TEventMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

procedure TEventMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  //inherited;
//    854085	��ѯ�������Ϣ
//    in	����Ա		scust_no
//    in	��Ϣ����	sstatus0
//    in	Ŀ�Ĳ���Ա	scust_no2
//    in	�ͻ���		sholder_ac_no
//    in	���͸��ͻ����	sstatus4
//    in	��ʼ����	sdate0
//    in	��������	sdate1
//
//    out	����Ա		scust_no
//    out	��Ϣ����	vsvarstr0
//    out	��ϢժҪ	vsvarstr1
//    out	��Ϣ����	sstatus0
//    out	Ŀ�Ĳ���Ա	scust_no2
//    out	���͸��ͻ����	sstatus4
//    out	�ͻ���		sholder_ac_no
//    out	��������	sdate1
//    out	����ʱ��	stime3
  with DataSet.Data.TextDB do
  begin
    Append;
    with PBody^ do
    begin
      Move(scust_no,FindField('scust_no').GetDataBuffer^,Length(scust_no));//
      Move(vsvarstr0,FindField('vsvarstr0').GetDataBuffer^,Length(vsvarstr0));//
      Move(vsvarstr1,FindField('vsvarstr1').GetDataBuffer^,Length(vsvarstr1));//
      Move(sstatus0,FindField('sstatus0').GetDataBuffer^,Length(sstatus0));//
      Move(scust_no2,FindField('scust_no2').GetDataBuffer^,Length(scust_no2));//
      Move(sstatus4,FindField('sstatus4').GetDataBuffer^,Length(sstatus4));//
      Move(sholder_ac_no,FindField('sholder_ac_no').GetDataBuffer^,Length(sholder_ac_no));//
      Move(sdate1,FindField('sdate1').GetDataBuffer^,Length(sdate1));//
      Move(stime3,FindField('stime3').GetDataBuffer^,Length(stime3));//
    end;
  end;
  DataSet.Last;
  BookMark := DataSet.GetBookmark;
end;


{ TMoneyMCDataSet }

procedure TMoneyMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_Money;

  //��ѯ�ʽ�
  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);   // 	����Ա	  ��ǰ����Ա
  BindOneParam(DataSet,'sholder_ac_no',ftChar,'');   // 	�ͻ���	  ''
  BindOneParam(DataSet,'sserial1',ftChar,'');   // 	�ͻ���	  ''
  BindOneParam(DataSet,'scurrency_type',ftChar,'');   // 	����	  ''

end;

procedure TMoneyMCDataSet.InitKindsIndex;
begin
  AddOneIndexKind('smarket_code',ddkMarket    );
  AddOneIndexKind('sstatus2',ddkTradeDir      );
  AddOneIndexKind('sstatus0',ddkContractStatus);
  AddOneIndexKind('sholder_type',ddkEntrustType  );
  AddOneIndexKind('sstat_type2',ddkContractType  );
//  AddOneIndexKind('sstatus3',ddkKaiPing       );
  AddOneIndexKind('sstatus4',ddkTouBao        );
  AddOneIndexKind('sserial2',ddkSeat          );   
  AddOneIndexKind('scurrency_type',ddkMoneyType);
  AddOneIndexKind('sstat_type2',ddkContractStatus);
end;

function TMoneyMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

procedure TMoneyMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  inherited;

end;

{ TRiskMCDataSet }

procedure TRiskMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_CstRisk;

  //��ѯ����
  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);   // 	����Ա	  ��ǰ����Ա

end;

procedure TRiskMCDataSet.InitKindsIndex;
begin
  AddOneIndexKind('smarket_code',ddkMarket    );
  AddOneIndexKind('sstatus2',ddkTradeDir      );
  AddOneIndexKind('sstatus0',ddkContractStatus);
  AddOneIndexKind('sholder_type',ddkEntrustType  );
  AddOneIndexKind('sstat_type2',ddkContractType  );
//  AddOneIndexKind('sstatus3',ddkKaiPing       );
  AddOneIndexKind('sstatus4',ddkTouBao        );
  AddOneIndexKind('sserial2',ddkSeat          );   
  AddOneIndexKind('scurrency_type',ddkMoneyType);
  AddOneIndexKind('sstat_type2',ddkContractStatus);
end;

function TRiskMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

procedure TRiskMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  inherited;

end;

{ THoldMCDataSet }

procedure THoldMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  DataSet.RequestType := Qry_HoldGood;

   // ��ѯ�ֲ֣�
   BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);   // 	����Ա	  ��ǰ����Ա
   BindOneParam(DataSet,'sserial2',ftChar,'');   // 	ϯλ��	  ''
   BindOneParam(DataSet,'sdate2',ftChar,'');   // 	����	  ''
   BindOneParam(DataSet,'sholder_ac_no',ftChar,'');   // 	�ͻ���	  ''
   BindOneParam(DataSet,'sserial1',ftChar,'');   // 	�ͻ���	  ''
   BindOneParam(DataSet,'scust_auth',ftChar,'');   // 	��Լ��	  ''
   BindOneParam(DataSet,'sholder_ac_no2',ftChar,'');   //        ���ױ���  ''
end;

procedure THoldMCDataSet.InitKindsIndex;
begin
  inherited;
end;

function THoldMCDataSet.GetProperSubStr(CPackFieldName: string): string;
begin
  Result := inherited GetProperSubStr(CPackFieldName);
end;

procedure RecievePushData(RequestType: LongWord; PBody: PSTPack);
var
  I, J: Integer;
  ListItem: TListItem;
  tempStr : string;
begin
{ TODO -o����� -ca : �������͵�����ڣ���Ҫ��������Ϣ�ַ�������DataSet�� }
  case RequestType of
    RQTP_DoInit    :
    begin
      WorkArea.SwitchWorkArea;
      WorkArea.FindCriticalSectionDataSet(mcsEvent).RevPushData(RequestType,PBody);
    end;

    RQTP_BackOrder,RQTP_SendPreEntrust,RQTP_SendSerialEntrust,
      RQTP_SendSameOrderEntrust,RQTP_SameOrderEntrust,RQTP_SerialEntrust,
        RQTP_ScanConditionEntrust,RQTP_ForceSendConditionEntrust :
      WorkArea.FindCriticalSectionDataSet(mcsEntrust).RevPushData(RequestType,PBody);

    RQTP_DelEntrust,RQTP_Entrust :
        WorkArea.FindCriticalSectionDataSet(mcsEntrust).RevPushData(RequestType,PBody,False);

    RQTP_WithDraw,RQTP_PalaceDel :
      begin
        //������ɹ��Ͳ���������
        if PBody.sholder_type2[0] = '1' then
        begin
          WorkArea.FindCriticalSectionDataSet(mcsEntrust).RevPushData(RequestType,PBody,False);
          ///WorkArea.FindCriticalSectionDataSet(mcsBaginOn).AddOneNewRec(RevPushedData,False);
        end
        else Exit;
      end;
    RQTP_BaginOn :
      begin
        WorkArea.FindCriticalSectionDataSet(mcsBaginOn).RevPushData(RequestType,PBody);
        WorkArea.FindCriticalSectionDataSet(mcsEntrust).RevPushData(RequestType,PBody,False);
      end;

    RQTP_PublishInfo,RQTP_SetSeatStatus,RQTP_PalaceEntrustDel,
      RQTP_SetSeatTimeDif,RQTP_SeatStatusChanged,RQTP_SetReporterStatus :
      WorkArea.FindCriticalSectionDataSet(mcsEvent).RevPushData(RequestType,PBody);

    Exe_force_login_logout :
      begin
        tempStr := PBody^.scust_no;
        tempStr := tempStr + ',' + PBody^.vsvarstr0;
        SendMessage(Application.MainForm.Handle,Msg_ForceQuit,0,Integer(PChar(tempStr)));
      end;
{$IFDEF Debug}
  else
    WriteLog(Format('�յ����ͣ�%d����δ����',[RequestType]),lcException);
{$ENDIF}
  end;
end;

procedure THoldMCDataSet.InternalAddRevData(var BookMark: TBookmark;
  var NeedRefresh: Boolean; RequestType: LongWord; PBody: PSTPack);
begin
  inherited;
end;

{ THeartBeatMCDataSet }

procedure THeartBeatMCDataSet.BindInput(DataSet: TKCDataSet);
begin
  inherited;
  FConnectStatus := cnsNormal;
  DataSet.RequestType := Qry_ClientHeartBeat; //scust_no
  BindOneParam(DataSet,'scust_no',ftChar,Context.ParamData(svOperatorNoName).AsString);   // 	����Ա	  ��ǰ����Ա
end;

procedure THeartBeatMCDataSet.SetConnectStatus(
  const Value: TConnect_Status);
begin
  if FConnectStatus <> Value then
  begin
    FConnectStatus := Value;
    PostMessage(Application.MainForm.Handle,WMMC_CntStatusChanged,Integer(FConnectStatus),0);
  end;
end;

procedure THeartBeatMCDataSet.SwitchDataSet;
begin
//  if not NeedToSwitch then Exit;
//  if not FFirstNeedSwitch then FNeedToSwitch := FFirstNeedSwitch;
  Assert(FViceDataSet <> nil);

  FViceDataSet.Close;
  try
    QueryDrtp;
    ConnectStatus := cnsNormal;
//    FCriticalSection.Enter;
//    try
      InternalChangeMainArea;
  //    SwitchViewers;
//    finally
//      FCriticalSection.Leave;
//    end;
  //  FNeedToSwitch := not (FViewerList.Count = 0);
  except
    on E : Exception do
    begin
      {$IFDEF Debug}
      WriteLog(Format('Exception[%s]: %s',[E.ClassName,E.Message]),lcException);
      {$ENDIF}
      if E is EKCAccessRecv then ConnectStatus := cnsSvrDisConnect
        else ConnectStatus := cnsCmnDisConnect;
      Exit;
    end;
  end;

end;

end.
