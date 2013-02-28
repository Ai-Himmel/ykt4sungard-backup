unit KSFrameWorks;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>KSFrameWorks
   <What>定义程序框架
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses SysUtils, Classes, Controls, WVCommands, IntfUtils, DB, WorkViews, menus,
ObjDir,Dialogs;

type
  THelpID = string; // 帮助ID的类型
  TUICode = string;
  TUIInstanceRecord = class;
  {
    <Interface>IHelpSystem
    <What>帮助系统的接口。用HelpID标志帮助入口。屏蔽了帮助系统的实现。
    <Properties>
      -
    <Methods>
      -
  }
  IHelpSystem = interface
    procedure ShowHelp(const Help: THelpID);
  end;

  {
    <Interface>IExceptionHandler
    <What>错误处理接口。
    <Properties>
      -
    <Methods>
      -
  }
  IExceptionHandler = interface
    procedure HandleException(E: Exception);
    procedure HandleException2(Sender: TObject; E: Exception);
  end;

  TUserAction = (uaYes, uaNo, uaCancel);
    // 用户的选择：确认（做），反对（不做），取消（中断）
  TUserActions = set of TUserAction;
  {
    <Interface>IDialogSystem
    <What>提供系统常用的标准对话框。
    <Properties>
      -
    <Methods>
      -
  }
  IDialogSystem = interface
    function Confirm(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    function Confirm2(const Msg: string; const HelpID: THelpID = ''): Boolean;
    function Warning(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    procedure ShowMessage(const Msg: string; const HelpID: THelpID = '');
    procedure ShowError(const Msg: string; const HelpID: THelpID = '');
    function ShowError2(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    procedure ShowWarning(const Msg: string; const HelpID: THelpID = '');
    procedure ShowWaiting(const Msg: string);
    procedure CloseWaiting;
    function DoSingleStationCheck(
      const AOperation: string;
      var CheckerNo, CheckerPassword: string;
      FuncNo: Integer = 0;
      const CustomerNo: string = '';
      const CurrentType: string = '';
      const ACaption: string = ''
      ): Boolean;
    procedure ShowHintFor(Control: TControl; const HintStr: string);
    procedure ShowSuccess(const Msg: string);
    function InputText(const ACaption, APrompt: string; HideText,
      CustomerPassword: Boolean; var Value: string; MaxLength: Integer = 0):
      Boolean;
  end;

  {
    <Interface>IConfigSystem
    <What>定义读取配置文件的接口
    <Properties>
      -
    <Methods>
      -
  }
  IConfigSystem = interface
    function ReadString(const Category, Key: string; const Default: string):
      string;
    function ReadInteger(const Category, Key: string; const Default: Integer):
      Integer;
    function ReadBoolean(const Category, Key: string; const Default: Boolean):
      Boolean;
    function ReadFloat(const Category, Key: string; const Default: Double):
      Double;
    function WriteString(const Category, Key: string; const Value: string):
      Boolean;
    function WriteInteger(const Category, Key: string; const Value: Integer):
      Boolean;
    function WriteBoolean(const Category, Key: string; const Value: Boolean):
      Boolean;
    function WriteFloat(const Category, Key: string; const Value: Double):
      Boolean;
  end;

  {
    <Interface>IWorkSpace
    <What>对任何一个操作界面提供工作环境的接口.
    <Properties>
      -
    <Methods>
      -
  }
  IWorkSpace = interface
    function GetContainer: TWinControl;
    procedure FitSize(W, H: Integer);
    procedure UIStatusChanged(InstanceRecord: TUIInstanceRecord);
    procedure Release(InstanceRecord: TUIInstanceRecord);
    // new added 2003-6-10
    // avoid workspace to re-free container
    procedure FreeContainer;
  end;

  TCommonActionID = type Integer;

  {
    <Interface>IUIInstance
    <What>定义操作界面的接口
    <Properties>
      -
    <Methods>
      -
  }
  IUIInstance = interface
    ['{9813FE24-469B-471E-B062-3A4CDC108C82}']
    function CanSave: Boolean;
    function CanClose: Boolean;
    function GetCaption: string;
    procedure SetCaption(const Value: string);
    function GetHelpID: THelpID;
    procedure SetInstanceRecord(InstanceRecord: TUIInstanceRecord);
    procedure Init;
    procedure InitEx;
    function CanDoAction(const ActionID: TCommonActionID): Boolean;
    procedure DoAction(const ActionID: TCommonActionID);
    procedure SystemNotify(NotifyCode: Integer);
    property Caption: string read GetCaption write SetCaption;
  end;

  {
    <Interface>IDebugSubSystem
    <What>调试程序的子系统接口
    <Properties>
      -
    <Methods>
      ExecuteDebugTool - 调用一个调试功能
  }
  IDebugSubSystem = interface
    function HaveDebugTool(const ToolName: string): Boolean;
    procedure GetDebugToolNames(ToolNames: TStrings);
    procedure ExecuteDebugTool(CurrentInstanceRecord: TUIInstanceRecord; const
      ToolName: string);
  end;

  {
    <Interface>IDebugSystem
    <What>调试程序的接口
    <Properties>
      -
    <Methods>
      -
  }

  IDebugSystem = interface
    procedure DebugDataSource(DataSource: TDataSource; const ACaption: string =
      '');
    procedure DebugDataset(Dataset: TDataset; const ACaption: string = '');
    procedure DebugWorkView(WorkView: TWorkView; const ACaption: string = '');
    procedure DebugUI(ARoot: TComponent; const ACaption: string = '');
    procedure DebugDatabase;
    procedure ShowLog;
    procedure GetDebugToolNames(ToolNames: TStrings);
    procedure ExecuteDebugTool(CurrentInstanceRecord: TUIInstanceRecord; const
      ToolName: string);
    procedure InstallSubSystem(SubSystem: IDebugSubSystem);
    procedure UnInstallSubSystem(SubSystem: IDebugSubSystem);
  end;

  IRobotSystem = interface
    {
    procedure MonitorControl(Control : TControl);
    procedure MonitorWorkView(WorkView : TWorkView);
    procedure InitControl(Control : TControl);
    }
    procedure MonitorComponent(AComponent: TComponent);
    procedure InitComponent(AComponent: TComponent);
    procedure SaveData(const DataCategory, ID, Caption: string);
    procedure OperatorChanged(const OperatorNo: string);
  end;

  ICopyRightSystem = interface
    procedure ShowAbout;
    function GetVersion: string;
  end;

  {
    <Class>TKSContext
    <What>定义运行环境。该环境包含需要的各种接口。
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TKSContext = class(TWVContext)
  public
    function GetHelpSystem: IHelpSystem; virtual; abstract;
    function GetExceptionHandler: IExceptionHandler; virtual; abstract;
    function GetDialogSystem: IDialogSystem; virtual; abstract;
    function GetConfigSystem: IConfigSystem; virtual; abstract;
    function GetSystemObject(const ObjectName: string): TObject; virtual;
      abstract;
    function GetDebugSystem: IDebugSystem; virtual; abstract;
    procedure SetDebugSystem(NewDebugSystem: IDebugSystem); virtual; abstract;
    function GetRobotSystem: IRobotSystem; virtual; abstract;
    procedure SetRobotSystem(NewRobotSystem: IRobotSystem); virtual; abstract;
    function GetCopyRight: ICopyRightSystem; virtual; abstract;
    procedure SetCopyRight(NewCopyRight: ICopyRightSystem); virtual; abstract;
    function NewWorkSpace: IWorkSpace; virtual; abstract;
    function GetDir(DirKey: Integer): string; virtual; abstract;
    function GetParamValue(const ParamName: string): string; virtual; abstract;
    function GetLogined: Boolean; virtual; abstract;
    procedure RefreshSysParams(var FSysDate: string); virtual; abstract;
  end;

  {
    <Class>TUIClassFactory
    <What>负责创建界面对象的实例
    <Properties>
      UICode - 唯一标志界面的编号
    <Methods>
      CreateUIInstanceRecord - 创建TUIInstanceRecord对象
    <Event>
      -
  }
  TUIClassFactory = class(TObject)
  private
    FUICode: TUICode;
  protected
    procedure InitUIInstanceRecord(InstanceRecord: TUIInstanceRecord); virtual;
    procedure UnInitUIInstanceRecord(InstanceRecord: TUIInstanceRecord);
      virtual;
    function CreateInstance: TObject; virtual; abstract;
  public
    constructor Create(const AUICode: TUICode);
    destructor Destroy; override;
    property UICode: TUICode read FUICode;
    function CreateUIInstanceRecord(AContext: TKSContext): TUIInstanceRecord;
      virtual;
    function GetIsSingleton: Boolean; virtual; abstract;
  end;

  TUIStdClassFactory = class(TUIClassFactory)
  private
    FInstanceClass: TControlClass;
    FIsSingleton: Boolean;
  protected
    function CreateInstance: TObject; override;
    function GetDefaultIsSingleton: Boolean;
  public
    constructor Create(const AUICode: TUICode; AInstanceClass: TControlClass;
      AIsSingleton: Boolean); overload;
    constructor Create(const AUICode: TUICode; AInstanceClass: TControlClass);
      overload;
    function GetIsSingleton: Boolean; override;
    property InstanceClass: TControlClass read FInstanceClass;
    property IsSingleton: Boolean read FIsSingleton write FIsSingleton;
  end;

  {
    <Class>TUIInstanceRecord
    <What>包含界面实例对象、相应的WorkSpace以及相应的其他信息
    在释放的时候，释放界面实例对象，释放WorkSpace
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TUIInstanceRecord = class(TObject)
  private
    FWorkSpace: IWorkSpace;
    FContext: TKSContext;
    FInstance: TObject;
    FUIClassFactory: TUIClassFactory;
    FIsSaved: Boolean;
    FInstanceInterface: IUIInstance;
  public
    constructor Create(AContext: TKSContext);
    destructor Destroy; override;
    procedure Release;
    property Context: TKSContext read FContext;
    property UIClassFactory: TUIClassFactory read FUIClassFactory;
    property WorkSpace: IWorkSpace read FWorkSpace;
    property InstanceInterface: IUIInstance read FInstanceInterface;
    property Instance: TObject read FInstance write FInstance;
    property IsSaved: Boolean read FIsSaved write FIsSaved;
  end;

  {
    <Class>TCustomWorkSpace
    <What>实现IWorkSpace的基类
    <Properties>
      -
    <Methods>
      -
    <Event>
      -
  }
  TCustomWorkSpace = class(TVCLInterfacedObject, IWorkSpace)
  private
    FContainer: TWinControl;
    FFreeContainerWhenDone: Boolean;
  protected
    function GetContainer: TWinControl; virtual;
    procedure FitSize(W, H: Integer); virtual;
    procedure UIStatusChanged(InstanceRecord: TUIInstanceRecord); virtual;
    procedure Release(InstanceRecord: TUIInstanceRecord); virtual; abstract;
    procedure FreeContainer;
  public
    constructor Create(AContainer: TWinControl; AFreeContainerWhenDone:
      Boolean);
    destructor Destroy; override;
    property Container: TWinControl read FContainer;
    property FreeContainerWhenDone: Boolean read FFreeContainerWhenDone;
  end;

  IKSModule = interface
    procedure Start;
    procedure ShutDown;
  end;

  IKSMainForm = interface(IKSModule)
    procedure ShowHelp(const Help: THelpID);
    function NewWorkSpace: IWorkSpace;
    procedure ShowHintFor(Control: TControl; const HintStr: string);
    function ShowUI(const AUICode: TUICode): Boolean;
    procedure SetupPrinter;
    procedure SystemNotify(NotifyCode: Integer);
      // 通知主程序和各个界面模块，(某些例如发生了改变)
    function GetInstanceRecordCount: Integer;
    function GetInstanceRecord(Index: Integer): TUIInstanceRecord;
    function GetActiveInstanceRecord: TUIInstanceRecord;
  end;

  IKSDatabaseModule = interface(IKSModule)
    procedure ShowWaiting(const Msg: string);
    procedure CloseWaiting;
    procedure ReadyForUse;
    function GetDatabase: TObject;
  end;

  // 与界面类工厂注册相关的过程
procedure RegisterUIClassFactory(Factory: TUIClassFactory);

procedure UnRegisterUIClassFactory(Factory: TUIClassFactory);

function FindUIClassFactory(const AUICode: TUICode): TUIClassFactory;

function CreateUserInterface(const AUICode: TUICode): TUIInstanceRecord;

// 返回当前的上下文对象（代表了运行环境）
function Context: TKSContext;

// 返回当前的各个模块的共享对象列表  zhupf
function UIShareObjList: TObjectCategory;

// 设置上下文对象(只能设置一次)
procedure SetContext(AContext: TKSContext);

procedure InstallSubSystem(SubSystem: IDebugSubSystem);

procedure UnInstallSubSystem(SubSystem: IDebugSubSystem);

var
  MainForm: IKSMainForm = nil;
  DatabaseModule: IKSDatabaseModule = nil;
  SysModule1: IKSModule = nil;
  SysModule2: IKSModule = nil;
  SysModule3: IKSModule = nil;

  ProgramLogFileName: string;

  // 统计启动时间
  StartTime: Integer = 0;
  FinishSomeSysInit: Integer = 0;
  FirstWaitForInit: Integer = 0;
  FirstLogin: Integer = 0;
  FirstShowTutorial: Integer = 0;

implementation

uses SafeCode, LogFile, KSClientConsts, UQueryTemp;

var
  FIsHaveSetContext: Boolean = False;
  FContext: TKSContext = nil;
  UIClassFactories: TObjectCategory;
  {**********************************************
          Kingstar Delphi Library
     Copyright (C) Kingstar Corporation
     <Unit>
     <What> 创建各个模块共享的对象列表 UIShareObjList。
     <Written By> Zhu pengfei (朱朋飞)
     <History>
  **********************************************}
  UIShareObjectList: TObjectCategory;

  // 返回当前的上下文对象（代表了运行环境）

function Context: TKSContext;
begin
  Result := FContext;
end;

// 设置上下文对象(只能设置一次)

procedure SetContext(AContext: TKSContext);
begin
  CheckTrue((not FIsHaveSetContext) or (AContext = nil),
    'Prohibit reset context');
  FIsHaveSetContext := True;
  FContext := AContext;
end;

// 与界面类工厂注册相关的过程

procedure RegisterUIClassFactory(Factory: TUIClassFactory);
begin
  WriteLog('Registe UI : ' + Factory.UICode, lcRegisterUI);
  AddObject(SUIClassFactoryCategory, Factory);
end;

procedure UnRegisterUIClassFactory(Factory: TUIClassFactory);
begin
  RemoveObject(SUIClassFactoryCategory, Factory);
end;

procedure CompareFactory(Obj: TObject; const Name: string; ID: integer; var
  Finded: Boolean);
begin
  Finded := SameText(TUIClassFactory(Obj).UICode, Name);
end;

function FindUIClassFactory(const AUICode: TUICode): TUIClassFactory;
begin
  Result := TUIClassFactory(UIClassFactories.FindObject(AUICode, 0,
    CompareFactory));
end;

function CreateUserInterface(const AUICode: TUICode): TUIInstanceRecord;
var
  Factory: TUIClassFactory;
begin
  Factory := FindUIClassFactory(AUICode);
  CheckObject(Factory, Format(SNoRegisterUI, [AUICode]));
  Result := Factory.CreateUIInstanceRecord(Context);
end;

procedure InstallSubSystem(SubSystem: IDebugSubSystem);
begin
  if (Context <> nil) and (Context.GetDebugSystem <> nil) then
    Context.GetDebugSystem.InstallSubSystem(SubSystem);
end;

procedure UnInstallSubSystem(SubSystem: IDebugSubSystem);
begin
  if (Context <> nil) and (Context.GetDebugSystem <> nil) then
    Context.GetDebugSystem.UnInstallSubSystem(SubSystem);
end;

{ TUIInstanceRecord }

constructor TUIInstanceRecord.Create(AContext: TKSContext);
begin
  Assert(AContext <> nil);
  FContext := AContext;
  FWorkSpace := FContext.NewWorkSpace;
end;

destructor TUIInstanceRecord.Destroy;
begin
  FUIClassFactory.UnInitUIInstanceRecord(Self);
  Self.FWorkSpace := nil;
  inherited;
end;

procedure TUIInstanceRecord.Release;
begin
  WorkSpace.Release(Self);
end;

{ TUIClassFactory }

constructor TUIClassFactory.Create(const AUICode: TUICode);
begin
  FUICode := AUICode;
  RegisterUIClassFactory(Self);
end;

function TUIClassFactory.CreateUIInstanceRecord(
  AContext: TKSContext): TUIInstanceRecord;
begin
  Result := TUIInstanceRecord.Create(AContext);
  Result.FUIClassFactory := Self;
  InitUIInstanceRecord(Result);
  CheckTrue(Result.FInstanceInterface <> nil, 'Invalid Interface');
end;

destructor TUIClassFactory.Destroy;
begin
  UnRegisterUIClassFactory(Self);
  inherited;
end;

procedure TUIClassFactory.InitUIInstanceRecord(
  InstanceRecord: TUIInstanceRecord);
begin
  InstanceRecord.FInstance := CreateInstance;
  CheckObject(InstanceRecord.FInstance, 'Invalid User Interface Instance');
  InstanceRecord.FInstance.GetInterface(IUIInstance,
    InstanceRecord.FInstanceInterface);
  if InstanceRecord.FInstance is TControl then
    with TControl(InstanceRecord.FInstance) do
    begin
      Parent := InstanceRecord.WorkSpace.GetContainer;
      InstanceRecord.WorkSpace.FitSize(Width, Height);
      Align := alClient;
      InstanceRecord.WorkSpace.UIStatusChanged(InstanceRecord);
    end;
  if InstanceRecord.FInstanceInterface <> nil then
    InstanceRecord.FInstanceInterface.SetInstanceRecord(InstanceRecord);
end;

procedure TUIClassFactory.UnInitUIInstanceRecord(
  InstanceRecord: TUIInstanceRecord);
begin
  try
    Pointer(InstanceRecord.FInstanceInterface) := nil;
    FreeAndNil(InstanceRecord.FInstance);
  except
    WriteException;
  end;
end;

{ TUIStdClassFactory }

constructor TUIStdClassFactory.Create(const AUICode: TUICode;
  AInstanceClass: TControlClass; AIsSingleton: Boolean);
begin
  Assert(AInstanceClass <> nil);
  inherited Create(AUICode);
  FInstanceClass := AInstanceClass;
  FIsSingleton := AIsSingleton;
end;

constructor TUIStdClassFactory.Create(const AUICode: TUICode;
  AInstanceClass: TControlClass);
begin
  Create(AUICode, AInstanceClass, True);
  FIsSingleton := GetDefaultIsSingleton;
end;

function TUIStdClassFactory.CreateInstance: TObject;
begin
  Result := FInstanceClass.Create(nil);
end;

function TUIStdClassFactory.GetDefaultIsSingleton: Boolean;
begin
  try
    Result := True;
    if FInstanceClass.InheritsFrom(TfaQueryTemp) then
    begin
      if Context <> nil then
        Result := not Context.GetConfigSystem.ReadBoolean(ccMain, ckMultiQuery,
          cdMultiQuery)
      else
        Result := False;
    end;
    if Context <> nil then
      Result := not Context.GetConfigSystem.ReadBoolean(ccMultiQuery, UICode, not
        Result);
  except
    Result := True;
  end;
end;

function TUIStdClassFactory.GetIsSingleton: Boolean;
begin
  Result := FIsSingleton;
end;

{ TCustomWorkSpace }

constructor TCustomWorkSpace.Create(AContainer: TWinControl;
  AFreeContainerWhenDone: Boolean);
begin
  Assert(AContainer <> nil);
  inherited Create(True);
  FContainer := AContainer;
  FFreeContainerWhenDone := AFreeContainerWhenDone;
end;

destructor TCustomWorkSpace.Destroy;
begin
  if FFreeContainerWhenDone then
    FreeAndNil(FContainer);
  inherited;
end;

procedure TCustomWorkSpace.FitSize(W, H: Integer);
begin

end;

procedure TCustomWorkSpace.FreeContainer;
begin
  FContainer := nil;
end;

function TCustomWorkSpace.GetContainer: TWinControl;
begin
  Result := FContainer;
end;

procedure TCustomWorkSpace.UIStatusChanged(InstanceRecord: TUIInstanceRecord);
begin

end;

function UIShareObjList: TObjectCategory;
begin
  Result := nil;
  if UIShareObjectList <> nil then
    Result := UIShareObjectList;
end;

initialization
  UIClassFactories := CreateCategory(SUIClassFactoryCategory, True);
  UIShareObjectList := CreateCategory(SUIShareObjList, True);

end.
