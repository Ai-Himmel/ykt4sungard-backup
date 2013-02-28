unit UContext;
{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UContext
   <What>实现了上下文对象，提供运行环境
   负责启动和关闭系统
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UContext
   <What>加入一卡通系统所需的前台子系统注册、签到、签出的功能

   <Written By> Wang SuNa (王苏娜)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  KSFrameWorks, DataTypes, IniFiles, DB, WorkViews, ExtCtrls, KSFileSystem,
  KSConfigUtils,
  WVCmdReq, WVCommands, WVCmdTypeInfo, WVCmdProc, KCWVProcBinds, NB30, Winsock,
  BDAImpEx, KCDataAccess, NetUtils;

type
  TMainContext = class(TKSContext)
  private
    FStartDir: string;
    FBaseDir: string;
    FLocalBaseDir: string;
    FProtectedStr: string;
    FDepartNo, FDepartName, FOperatorNo, FOperatorName, FOperatorPassword,
      FOperatorMenuAuth, FMACAddress, FLoginStatus, FSystemDate, FWorkDate,
      FReportDate, FProhibitMarkets, FProhibitMoney, FCompanyName, FSeatNo,
      FBatchNo, FFuncNo: TKSDataObject;
    FSystemTime: TKSDataObject;
    FDebugSystem: IDebugSystem;
    FRobotSystem: IRobotSystem;
    FConfigSystem: TKSConfigSystem;
    FCurrentUserConfig: IConfigSystem;
    FCopyRight: ICopyRightSystem;
    FRunMode: TKSClientRunMode;
    procedure BeginUpdate;
    procedure EndUpdate;
    function GetMacAddress: string;
    procedure InstallUserConfig;
  public
    UseFormSpace: Boolean; //程用明 20030711
    constructor Create;
    destructor Destroy; override;
    procedure Init;
    procedure Reset;
    function GetHelpSystem: IHelpSystem; override;
    function GetExceptionHandler: IExceptionHandler; override;
    function GetDialogSystem: IDialogSystem; override;
    function GetConfigSystem: IConfigSystem; override;
    function GetSystemObject(const ObjectName: string): TObject; override;
    function GetDebugSystem: IDebugSystem; override;
    procedure SetDebugSystem(NewDebugSystem: IDebugSystem); override;
    function GetRobotSystem: IRobotSystem; override;
    procedure SetRobotSystem(NewRobotSystem: IRobotSystem); override;
    function GetCopyRight: ICopyRightSystem; override;
    procedure SetCopyRight(NewCopyRight: ICopyRightSystem); override;
    function NewWorkSpace: IWorkSpace; override;
    function GetDir(DirKey: Integer): string; override;
    function GetParamValue(const ParamName: string): string; override;
    function GetLogined: Boolean; override;
    procedure RefreshSysParams(var FSysDate: string); override;
    property RunMode: TKSClientRunMode read FRunMode;
  end;

  TSysInitThread = class(TThread)
  protected
    procedure Execute; override;
  public
    constructor Create;
  end;

  TdmContext = class(TDataModule, IHelpSystem, IExceptionHandler, IDialogSystem)
    Timer: TTimer;
    rqLogout: TWVRequest;
    WorkView: TWorkView;
    wvInfo: TWorkView;
    rqInfo: TWVRequest;
    rqSubsystemRegedit: TWVRequest;
    wvSubsystemRegedit: TWorkView;
    rqSubsystemLogin: TWVRequest;
    wvSubsystemLogin: TWorkView;
    rqSubsystemLogout: TWVRequest;
    wvSubsystemLogout: TWorkView;
    cpSubsystemRegedit: TKCWVProcessor;
    ctSubsystemRegedit: TWVCommandTypeInfo;
    cpSubsystemLogin: TKCWVProcessor;
    ctSubsystemLogin: TWVCommandTypeInfo;
    cpSubsystemLogout: TKCWVProcessor;
    ctSubsystemLogout: TWVCommandTypeInfo;
    KCDataset1: TKCDataset;
    procedure StartSystem(Sender: TObject);
    procedure ShutDownSystem(Sender: TObject);
    procedure LoadOnePackage(Sender: TObject);
    procedure DoCheckReturnValue(Request: TWVRequest; Command: TWVCommand);
    procedure rqSubsystemRegeditAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure rqSubsystemLoginAfterExec(Request: TWVRequest;
      Command: TWVCommand);
    procedure rqSubsystemLogoutAfterExec(Request: TWVRequest;
      Command: TWVCommand);
  private
    { Private declarations }
    FSysInitThread: TSysInitThread;
    FUseThread: Boolean;
    FTerminated: Boolean;
    FStartError: Boolean;
    FLoadPackages: TStringList;
    procedure LoadPackages;
    procedure SearchFile(path: string;pagList:TStringList);
    procedure SetupLogFile;
    procedure StartModule(const Module: IKSModule; const ACaption: string = '');
    procedure ShutDownModule(const Module: IKSModule; const ACaption: string =
      '');
    procedure SomeSysInit;
    function GetDialoagFlags(AllowActions: TUserActions): LongInt;
    procedure LoadPackage(const PackageFileName: string);
    function DoLoadOnePackage: Boolean;
    procedure BuidProPerDD(SourceSL: TStringList; SourceDDEntry, BeginDDEntry:
      Integer);
  public
    { Public declarations }
    // IHelpSystem
    procedure ShowHelp(const Help: THelpID);
    // IExceptionHandler
    procedure HandleException(E: Exception);
    procedure HandleException2(Sender: TObject; E: Exception);
    // IDialogSystem
    function Confirm(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    function Confirm2(const Msg: string; const HelpID: THelpID = ''): Boolean;
    function Warning(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    procedure ShowMessage(const Msg: string; const HelpID: THelpID = '');
    function ShowError2(const Msg: string; const HelpID: THelpID = '';
      AllowActions: TUserActions = [uaYes, uaNo]): TUserAction;
    procedure ShowError(const Msg: string; const HelpID: THelpID = '');
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
    // 返回是否成功
    procedure DoLogin;
    procedure DoGetInfo;
    procedure DoLogout;
    procedure DoLock;
    // Wait For Data
    procedure WaitForInit;
    property Terminated: Boolean read FTerminated;

    //wsn 20050119 加入前台程序子系统注册功能
    procedure SmartCardSubsystemRegedit;
    //wsn 20050119 判断前台程序是否注册
    function IsSmartCardSubsystemRegedit: Boolean;
    //wsn 20050119 加入前台程序子系统签到
    procedure SmartCardSubsystemLogin;
    //wsn 20050119 加入前台程序子系统签出
    procedure SmartCardSubsystemLogout;
    {**********************************************
            Kingstar Delphi Library
       Copyright (C) Kingstar Corporation
       <Unit>
       <What> 登录成功后，进行一些 必须以 当前 操作员 为条件的 个性化查询。
              具体就是在系统里面引用 Application.MainForm.Tag 的 TObjectList
              对象， 开始初始化。
       <Written By> Zhu pengfei (朱朋飞)
       <History>
    **********************************************}
    procedure DoBaseInitAferLogin(OnlyCustNO: Boolean);
    procedure DoTraderInitAfterLogin(OnlyCustNO: Boolean);
  end;

function GetSysNow: TDateTime;

var
  dmContext: TdmContext;
  LoadPackageCategory: string;

implementation

uses KSClientConsts, UQhClientConsts, LogFile, DBAHelper, KCDataPack, ULogin, SafeCode, BDAImp,
  KSComCmdDefs, UStartFlash, WVCtrls, UConfirmDlg, ProgressShowing,
  UDoubleCheck, KSStrUtils, KSFrameWorkUtils, Printers,
  UInputTextDlg, FileCtrl, ExtUtils, KsBranchTree, Contnrs,
  UCommData, {UMainPop,} KSDataDictionary, DBAIntf;

{$R *.DFM}

function GetSysNow: TDateTime;
begin
  Result := Now;
end;

{ TMainContext }

constructor TMainContext.Create;
var
  Filter: TWVLogFilter;
begin
  inherited;
  UseFormSpace := False;
  FRunMode := KSFileSystem.GetDirs(FStartDir, FLocalBaseDir, FBaseDir);
  Filter := TWVLogFilter.Create(Self);
  Filter.FilterName := 'BeforeExec';
  CommandBus.AddBeforeFilter(Filter);
  Filter := TWVLogFilter.Create(Self);
  Filter.FilterName := 'AfterExec';
  CommandBus.AddAfterFilter(Filter);
  Randomize;
  FProtectedStr := IntToHex(Round(Random($6FFFFFFF)), 8);
  AddParam(svDepartNoName, svDepartNoType, FProtectedStr);
  AddParam(svDepartNameName, svDepartNameType, FProtectedStr);
  AddParam(svOperatorNoName, svOperatorNoType, FProtectedStr);
  AddParam(svOperatorNameName, svOperatorNameType, FProtectedStr);
  AddParam(svOperatorPasswordName, svOperatorPasswordType, FProtectedStr);
  AddParam(svOperatorMenuAuthName, svOperatorMenuAuthType, FProtectedStr);
  AddParam(svLoginStatusName, svLoginStatusType, FProtectedStr);
  AddParam(svMACAddressName, svMACAddressType, FProtectedStr);
  AddParam(svSystemDateName, svSystemDateType, FProtectedStr);
  AddParam(svWorkDateName, svWorkDateType, FProtectedStr);
  AddParam(svReportDateName, svReportDateType, FProtectedStr);
  AddParam(svProhibitMarketsName, svProhibitMarketsType, FProtectedStr);
  AddParam(svProhibitMoneyName, svProhibitMoneyType, FProtectedStr);
  AddParam(svCompanyNameName, svCompanyNameType, FProtectedStr);

  //ADD BY ZKJ 2003-11-30
  AddParam(svSeatNoName, svSeatNoType, FProtectedStr);
  //ADD BY ZKJ 2003-12-03
  AddParam(svBatchNoName, svBatchNoType, FProtectedStr);
  AddParam(svFuncNoName, svFuncNoType, FProtectedStr);

  //rding,20040602,增加“系统时间”
  AddParam(svSystemTimeName, svSystemTimeType, FProtectedStr);

  FDebugSystem := nil;
  FRobotSystem := nil;
  FConfigSystem := nil;
end;

destructor TMainContext.Destroy;
begin
  FCopyRight := nil;
  FRobotSystem := nil;
  FDebugSystem := nil;
  FConfigSystem.DefaultConfigSystem := nil;
  FreeAndNil(FConfigSystem);
  inherited;
end;

procedure TMainContext.BeginUpdate;
begin
  //FDepartNo.BeginUpdate(FProtectedStr);
  FDepartName.BeginUpdate(FProtectedStr);
  FOperatorNo.BeginUpdate(FProtectedStr);
  FOperatorName.BeginUpdate(FProtectedStr);
  FOperatorPassword.BeginUpdate(FProtectedStr);
  FOperatorMenuAuth.BeginUpdate(FProtectedStr);
  FLoginStatus.BeginUpdate(FProtectedStr);
  FSystemDate.BeginUpdate(FProtectedStr);
  FWorkDate.BeginUpdate(FProtectedStr);
  FReportDate.BeginUpdate(FProtectedStr);
  FProhibitMoney.BeginUpdate(FProtectedStr);
  FProhibitMarkets.BeginUpdate(FProtectedStr);
  FCompanyName.BeginUpdate(FProtectedStr);

  //ADD BY ZKJ  2003-11-30
  FSeatNo.BeginUpdate(FProtectedStr);

  //ADD BY ZKJ  2003-12-03
  FBatchNo.BeginUpdate(FProtectedStr);
  FFuncNo.BeginUpdate(FProtectedStr);

  //rding,20040602
  FSystemTime.BeginUpdate(FProtectedStr);
end;

procedure TMainContext.EndUpdate;
begin
  //FDepartNo.EndUpdate(FProtectedStr);
  FDepartName.EndUpdate(FProtectedStr);
  FOperatorNo.EndUpdate(FProtectedStr);
  FOperatorName.EndUpdate(FProtectedStr);
  FOperatorPassword.EndUpdate(FProtectedStr);
  FOperatorMenuAuth.EndUpdate(FProtectedStr);
  FLoginStatus.EndUpdate(FProtectedStr);
  FSystemDate.EndUpdate(FProtectedStr);
  FWorkDate.EndUpdate(FProtectedStr);
  FReportDate.EndUpdate(FProtectedStr);
  FProhibitMarkets.EndUpdate(FProtectedStr);
  FProhibitMoney.EndUpdate(FProtectedStr);
  FCompanyName.EndUpdate(FProtectedStr);
  //ADD BY ZKJ 2003-11-30
  FSeatNo.EndUpdate(FProtectedStr);

  //ADD BY ZKJ 2003-12-03
  FBatchNo.EndUpdate(FProtectedStr);
  FFuncNo.EndUpdate(FProtectedStr);

  //rding,20040602
  FSystemTime.EndUpdate(FProtectedStr);

  InstallUserConfig;
end;

function TMainContext.GetConfigSystem: IConfigSystem;
begin
  Result := FConfigSystem;
  Assert(Result <> nil);
end;

function TMainContext.GetDebugSystem: IDebugSystem;
begin
  Result := FDebugSystem;
end;

function TMainContext.GetDialogSystem: IDialogSystem;
begin
  Result := dmContext;
end;

function TMainContext.GetExceptionHandler: IExceptionHandler;
begin
  Result := dmContext;
end;

function TMainContext.GetHelpSystem: IHelpSystem;
begin
  Result := dmContext;
end;

function TMainContext.GetDir(DirKey: Integer): string;
begin
  case DirKey of
    dkStart: Result := FStartDir;
    dkBase: Result := FBaseDir;
    dkLocalBase: Result := FLocalBaseDir;
    dkConfig: Result := FBaseDir + ConfigPath;
    dkReadOnlyConfig: Result := FBaseDir + ConfigPath;
    dkSavedConfig: Result := FLocalBaseDir + UserPath;
    // Result := FLocalBaseDir+ConfigPath;
    dkOutput: Result := FLocalBaseDir + OutputPath;
    dkReport: Result := FBaseDir + ReportPath;
    dkHelp: Result := FBaseDir + HelpPath;
    dkUser: Result := FLocalBaseDir + UserPath;
  else
    Result := '';
  end;
end;

function TMainContext.GetSystemObject(const ObjectName: string): TObject;
begin
  Result := nil;
  if ObjectName = SODatabase then
    Result := DatabaseModule.GetDatabase;
end;

procedure TMainContext.Init;
var
  TheConfigFileName: string;
  CommandLineFileName: string;
  Msg: string;
  RunNotesFile: string;
begin

  // 显示运行说明文件。该文件位于bin目录下
  RunNotesFile := GetFileName(dkStart, RunNotesFileName);
  ShellOpenFile(RunNotesFile);

  WriteLog('Run Mode=' + IntToStr(Ord(FRunMode)), lcKSClientStart);
  FConfigSystem := TKSConfigSystem.Create;
  // 可能存在的获取命令行指定的配置文件名
  if System.ParamCount >= 1 then
  begin
    CommandLineFileName := Trim(System.ParamStr(1));
    if (CommandLineFileName <> '') and (CommandLineFileName[1] in ['-', '/',
      '\']) then
      CommandLineFileName := '';
  end
  else
    CommandLineFileName := '';
  if CommandLineFileName <> '' then
    // 打开配置文件
    TheConfigFileName := GetFileName(dkConfig, CommandLineFileName)
  else
    TheConfigFileName := GetFileName(dkConfig, ConfigFileName);
  WriteLog('Config File=' + TheConfigFileName, lcKSClientStart);
  if SameText(ExtractFileExt(TheConfigFileName), '.ini') then
  begin
    Msg := '请使用加密以后的配置文件。'#13#10'使用SysFileMan50.exe程序里面的"配置文件文本->二进制"';
    //WriteLog(Msg,lcKSClientStart);
    ShowMessage(Msg);
    raise Exception.Create(Msg);
  end;
  if not FileExists(TheConfigFileName) then
  begin
    Msg := Format('配置文件不存在', [TheConfigFileName]);
    //WriteLog(Msg,lcKSClientStart);
    ShowMessage(Msg);
    raise Exception.Create(Msg);
    //Halt;
  end; 
  WriteLog('Use Config File ' + TheConfigFileName, lcKSClientStart);
  //wlj 20031230 wlj 将in 设置为可以修改的。
  FConfigSystem.DefaultConfigSystem :=
    TIniFileConfigSystem.Create(TheConfigFileName, True,
    SKingStarFutureBinCfgKey);
  //------------
  //改过程会把IExplorer启动，一卡通系统中不需要，delete it 20090908
  {
  FConfigSystem.AddConfigSystem(
    CategorySeperateChar + ccRunEnvir + CategorySeperateChar,
    TKSRunEnvirSystem.Create
    );
  
  //-------------
  FConfigSystem.AddConfigSystem(
    AllUsersCategories,
    TIniFileConfigSystem.Create(GetFileName(dkUser, AllUsersFileName), True)
    );
  }
  FDepartNo := ParamData(svDepartNoName);
  FDepartNo.BeginUpdate(FProtectedStr);
  FDepartNo.AsString := GetConfigSystem.ReadString(ccDepartment, ckDepartmentID,'');
  FDepartNo.EndUpdate(FProtectedStr);

  FDepartName := ParamData(svDepartNameName);
  FDepartName.BeginUpdate(FProtectedStr);
  FDepartName.AsString := GetConfigSystem.ReadString(ccDepartment,ckDepartmentName, '');
  FDepartName.EndUpdate(FProtectedStr);

  FOperatorNo := ParamData(svOperatorNoName);
  FOperatorNo.BeginUpdate(FProtectedStr);
  FOperatorNo.SetString(DefaultSystemOperatorNO);
  FOperatorNo.EndUpdate(FProtectedStr);

  FOperatorName := ParamData(svOperatorNameName);
  FOperatorName.BeginUpdate(FProtectedStr);
  FOperatorName.SetString(DefaultSystemOperatorName);
  FOperatorName.EndUpdate(FProtectedStr);

  FOperatorPassword := ParamData(svOperatorPasswordName);
  FOperatorPassword.BeginUpdate(FProtectedStr);
  FOperatorPassword.Clear;
  FOperatorPassword.EndUpdate(FProtectedStr);

  FOperatorMenuAuth := ParamData(svOperatorMenuAuthName);
  FOperatorMenuAuth.BeginUpdate(FProtectedStr);
  FOperatorMenuAuth.SetString(StringOfChar('1', 800));
  FOperatorMenuAuth.EndUpdate(FProtectedStr);

  FLoginStatus := ParamData(svLoginStatusName);
  FLoginStatus.BeginUpdate(FProtectedStr);
  FLoginStatus.SetBoolean(False);
  FLoginStatus.EndUpdate(FProtectedStr);

  FMACAddress := ParamData(svMACAddressName);
  FMACAddress.BeginUpdate(FProtectedStr);
  FMACAddress.SetString(GetMacAddress);
  FMACAddress.EndUpdate(FProtectedStr);

  FSystemDate := ParamData(svSystemDateName);
  FSystemDate.BeginUpdate(FProtectedStr);
  FSystemDate.SetString(FormatDateTime(NormalDateTimeFormat, Now));
  FSystemDate.EndUpdate(FProtectedStr);

  FWorkDate := ParamData(svWorkDateName);
  FWorkDate.BeginUpdate(FProtectedStr);
  FWorkDate.SetString(FormatDateTime(NormalDateTimeFormat, Now));
  FWorkDate.EndUpdate(FProtectedStr);


  FReportDate := ParamData(svReportDateName);
  FReportDate.BeginUpdate(FProtectedStr);
  FReportDate.SetString(FormatDateTime(NormalDateTimeFormat, Now));
  FReportDate.EndUpdate(FProtectedStr);

  FProhibitMarkets := ParamData(svProhibitMarketsName);
  FProhibitMarkets.BeginUpdate(FProtectedStr);
  FProhibitMarkets.Clear;
  FProhibitMarkets.EndUpdate(FProtectedStr);

  FProhibitMoney := ParamData(svProhibitMoneyName);
  FProhibitMoney.BeginUpdate(FProtectedStr);
  FProhibitMoney.Clear;
  FProhibitMoney.EndUpdate(FProtectedStr);

  FCompanyName := ParamData(svCompanyNameName);
  FCompanyName.BeginUpdate(FProtectedStr);
  //wlj 20040331 从配置文件取公司名称
  FCompanyName.SetString(GetConfigSystem.ReadString(ccDepartment, ckCompanyName,''));
  FCompanyName.EndUpdate(FProtectedStr);

  //ADD BY ZKJ  2003-11-30
  FSeatNo := ParamData(svSeatNoName);
  FSeatNo.BeginUpdate(FProtectedStr);
  FSeatNo.Clear;
  FSeatNo.EndUpdate(FProtectedStr);

  //ADD BY ZKJ  2003-12-03
  FBatchNo := ParamData(svBatchNoName);
  FBatchNo.BeginUpdate(FProtectedStr);
  FBatchNo.Clear;
  FBatchNo.EndUpdate(FProtectedStr);

  FFuncNo := ParamData(svFuncNoName);
  FFuncNo.BeginUpdate(FProtectedStr);
  FFuncNo.Clear;
  FFuncNo.EndUpdate(FProtectedStr);

  //rding,20040602,增加“系统时差”
  FSystemTime := ParamData(svSystemTimeName);
  FSystemTime.BeginUpdate(FProtectedStr);
  FSystemTime.SetInteger(0);
  FSystemTime.EndUpdate(FProtectedStr);
  
end;

function TMainContext.NewWorkSpace: IWorkSpace;
begin
  if MainForm <> nil then
    Result := MainForm.NewWorkSpace
  else
    Result := nil;
end;

procedure TMainContext.SetDebugSystem(NewDebugSystem: IDebugSystem);
begin
{$IFNDEF Release}
  FDebugSystem := NewDebugSystem;
{$ENDIF}
end;

function TMainContext.GetMacAddress: string;
begin
  { TODO : 获得网卡地址。 }
  //Result := '123456789';
  Result := NetUtils.GetMACAddr;
end;

function TMainContext.GetParamValue(const ParamName: string): string;
begin
  Result := ParamData(ParamName).AsString;
end;

procedure TMainContext.Reset;
begin
  BeginUpdate;
  try
    FLoginStatus.SetBoolean(False);
    FOperatorNo.SetString(DefaultSystemOperatorNO);
    FOperatorName.SetString(DefaultSystemOperatorName);
    FOperatorPassword.Clear;
    FOperatorMenuAuth.SetString(StringOfChar('1', 800));
  finally
    EndUpdate;
  end;
end;

function TMainContext.GetLogined: Boolean;
begin
  Result := FLoginStatus.AsBoolean;
end;

function TMainContext.GetRobotSystem: IRobotSystem;
begin
  Result := FRobotSystem;
end;

procedure TMainContext.SetRobotSystem(NewRobotSystem: IRobotSystem);
begin
  FRobotSystem := NewRobotSystem;
end;

procedure TMainContext.InstallUserConfig;
var
  FileName: string;
begin
  if FConfigSystem <> nil then
  begin
    if FCurrentUserConfig <> nil then
    begin
      FConfigSystem.RemoveConfigSystem(FCurrentUserConfig);
      FCurrentUserConfig := nil;
    end;
    if GetLogined then
    begin
      FileName := Format(UserFileNameFormat, [GetParamValue(svOperatorNoName)]);
      FileName := GetFileName(dkUser, FileName);
      FCurrentUserConfig := TIniFileConfigSystem.Create(FileName, True);
      FConfigSystem.AddConfigSystem(UserCategories, FCurrentUserConfig);
    end;
  end;
end;

function TMainContext.GetCopyRight: ICopyRightSystem;
begin
  Result := FCopyRight;
end;

procedure TMainContext.SetCopyRight(NewCopyRight: ICopyRightSystem);
begin
  FCopyRight := NewCopyRight;
end;

procedure TMainContext.RefreshSysParams(var FSysDate: string);
var
  Command: TWVCommand;
  TempStr: string;
begin
  CheckObject(Context, 'Invalid Context');
  Command := Context.CommandFactory.NewCommand('取得系统日期', 1);
  try
    Command.ParamData('发生营业部').SetString('0');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command, False);
    BeginUpdate;
    FWorkDate.AsString := Command.ParamData('系统日期').AsString;
    FSystemDate.AsString := Command.ParamData('当前记账日期').AsString;
    FReportDate.AsString := Command.ParamData('前记账日期').AsString;
    //rding,20040602，运算，取系统时间
    FSysDate := FSystemDate.AsString;
    TempStr := Command.ParamData('系统时间').AsString;
    try
      //86400=24*3600  datetime--->second
      //FSystemTime.SetInteger(trunc((StrToTime(TempStr)-time)*86400));
    except
      FSystemTime.SetInteger(0);
    end;
    EndUpdate;
    //if MainForm<>nil then
    //  MainForm.SystemNotify(snDateUpdated);
  finally
    Command.Free;
  end;
end;

{ TSysInitThread }

constructor TSysInitThread.Create;
begin
  inherited Create(True);
  FreeOnTerminate := False;
  Resume;
end;

procedure TSysInitThread.Execute;
begin
  Assert(dmContext <> nil);
  try
    dmContext.SomeSysInit;
  except
    WriteException;
  end;
  if dmContext.Terminated then
    Application.Terminate;
end;

{ TdmContext }

procedure TdmContext.SmartCardSubsystemLogout;
var
  FContext: TMainContext;
begin
  FContext := TMainContext(Context);
  FContext.BeginUpdate;
  try
    if TMainContext(Context).GetLogined then
    begin
      try
        try
          rqSubsystemLogout.SendCommand;
        finally
          TMainContext(Context).Reset;
          with Application do
          begin
            MainForm.Caption := SApplicationTitle;
            Title := SApplicationTitle;
          end;
        end;
      except
        WriteException;
      end;
    end;
  finally
    FContext.EndUpdate;
  end;
end;

procedure TdmContext.SmartCardSubsystemLogin;
begin
  {  Try
      wvSubsystemLogin.FieldByName('子系统注册号').Data.SetString('1');
      wvSubsystemLogin.FieldByName('初始密钥').Data.SetString('00-00-00-00-00-00');
      wvSubsystemLogin.SynchronizeCtrlsToFields;
      //ShowMessage('1');
      rqSubsystemLogin.SendCommand;
      //ShowMessage('2');
      ConfigSystem  := Context.GetConfigSystem;

      if  (((wvSubsystemLogin.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('lcert_code').AsInteger>0) then
      begin
        TmpStr:=((wvSubsystemLogin.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('lcert_code').AsString;
        ConfigSystem.WriteString(ccSmartcard,ckSubSystemNo,TmpStr);
        TmpStr:=((wvSubsystemLogin.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('scust_limit').AsString;
        ConfigSystem.WriteString(ccSmartcard,ckInitialKey,TmpStr);
        ConfigSystem.WriteString(ccSmartcard,ckCurrentSubSystemRegedit,'1');
      end;
    Finally
    end; }
end;

function TdmContext.IsSmartCardSubsystemRegedit: Boolean;
var
  ConfigSystem: IConfigSystem;
  FSubSystemNo: string;
  FCurrentSubSystemRegedit: string;
  ds : TDataSet;
begin
  Result := False;
  ConfigSystem := Context.GetConfigSystem;
  FSubSystemNo := ConfigSystem.ReadString(ccSmartcard, ckSubSystemNo, '');
  FCurrentSubSystemRegedit := ConfigSystem.ReadString(ccSmartcard,
    ckCurrentSubSystemRegedit, '');
    //ccSmartcard,ckInitialKey
  if (FSubSystemNo <> '') and (FCurrentSubSystemRegedit = '1') then
  begin
    Result := True;
    // 已注册，
    Try
      ConfigSystem := Context.GetConfigSystem;
      // param 1
      wvSubsystemLogin.FieldByName('子系统注册号').Data.SetInteger(
        StrToInt(ConfigSystem.ReadString(ccSmartcard,ckSubSystemNo,''))
        );
      // param 2
      wvSubsystemLogin.FieldByName('初始密钥').Data.SetString(
        ConfigSystem.ReadString(ccSmartcard,ckInitialKey,'')
        );

      wvSubsystemLogin.SynchronizeCtrlsToFields;
      rqSubsystemLogin.SendCommand;
      //ShowMessage('2');
      ds := (wvSubsystemLogin.FieldByName('查询结果集').Data.AsObject) as TDataSet;
      SmartCardSubSystemDynamicKey := ds.FieldbyName('scust_limit2').AsString;
      //ShowMessage(SmartCardSubSystemDynamickey);
    Finally
    end;
  end;
end;

procedure TdmContext.SmartCardSubsystemRegedit;
type
  TaPInAddr = array[0..10] of PInAddr;
  PaPInAddr = ^TaPInAddr;

var
  phe: PHostEnt;
  Buffer: array[0..254] of char;
  I: Integer;
  GInitData: TWSADATA;
  res_ip: string;
  res_mac,tmp_mac: string;

  ConfigSystem: IConfigSystem;
  TmpStr: string;
  TmpInt: Integer;
  //FContext: TMainContext;
  TmpData: TDataSet;
begin
  try
    WSAStartup(MakeWord(2,1), GInitData);
    Res_ip := '';
    GetHostName(Buffer, SizeOf(Buffer));
    phe := GetHostByName(buffer);
    res_ip := inet_ntoa((PInAddr(phe.h_addr^))^);
    res_mac := GetMACAddr;
    tmp_mac := res_mac;
    res_mac := Copy(tmp_mac,1,2);
    i := 3;
    while i < length(tmp_mac) do
    begin
      res_mac := Format('%s-%s',[res_mac,Copy(tmp_mac,i,2)]);
      inc(i,2);
    end;
    wvSubsystemRegedit.FieldByName('网卡地址').Data.SetString(res_mac);
    wvSubsystemRegedit.FieldByName('ip地址').Data.SetString(res_ip);

    wvSubsystemRegedit.SynchronizeCtrlsToFields;
    rqSubsystemRegedit.SendCommand;
    ConfigSystem  := Context.GetConfigSystem;

    TmpData:=TDataSet(wvSubsystemRegedit.FieldByName('查询结果集').Data.AsObject);
    if (not TmpData.isEmpty)and(TmpData.Active) then
    begin
      // 前置机注册号
      TmpInt:=TmpData.FieldbyName('lcert_code').AsInteger;
      ConfigSystem.WriteString(ccSmartcard,ckSubSystemNo,IntToStr(TmpInt));;
      // 初始密钥
      TmpStr:=TmpData.FieldbyName('scust_limit').AsString;
      ConfigSystem.WriteString(ccSmartcard,ckInitialKey,TmpStr);
      // 已注册标志
      ConfigSystem.WriteString(ccSmartcard,ckCurrentSubSystemRegedit,'1');
    end;
{
  ShowMessage('1');
  FContext := TMainContext(Context);
  ShowMessage('2');
  FContext.BeginUpdate;
  ShowMessage('3');
  try
    if TMainContext(Context).GetLogined then
    begin
      ShowMessage('4');
      try
        try
          //wvSubsystemRegedit.FieldByName('子系统名称').Data.SetString('111');
          wvSubsystemRegedit.FieldByName('网卡地址').Data.SetString(res_mac);
          wvSubsystemRegedit.FieldByName('ip地址').Data.SetString(res_ip);
          wvSubsystemRegedit.SynchronizeCtrlsToFields;
          ShowMessage('5');
          rqSubsystemRegedit.SendCommand;
          ShowMessage('6');
          ConfigSystem  := Context.GetConfigSystem;
          ShowMessage('7');
          if  (((wvSubsystemRegedit.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('lcert_code').AsInteger>0) then
          begin
            TmpStr:=((wvSubsystemRegedit.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('lcert_code').AsString;
            ConfigSystem.WriteString(ccSmartcard,ckSubSystemNo,TmpStr);
            TmpStr:=((wvSubsystemRegedit.FieldByName('查询结果集').Data.AsObject) as TDataSet).FieldbyName('scust_limit').AsString;
            ConfigSystem.WriteString(ccSmartcard,ckInitialKey,TmpStr);
            ConfigSystem.WriteString(ccSmartcard,ckCurrentSubSystemRegedit,'1');
          end;
        finally
          TMainContext(Context).Reset;
          with Application do
          begin
            MainForm.Caption := SApplicationTitle;
            Title := SApplicationTitle;
          end;
        end;
      except
        WriteException;
      end;
    end;
  finally
    FContext.EndUpdate;
  end;
}  
  except
    on e:Exception do
    begin
      raise Exception.Create(e.message);
      //ShowMessage(e.Message);
      //DoLogout;
    end;
  end ;
{  finally
    //ShowMessage(res_ip);
  end;
  }
end;

// IDialogSystem

function TdmContext.Confirm(const Msg: string; const HelpID: THelpID;
  AllowActions: TUserActions): TUserAction;
begin
  case Application.MessageBox(PChar(Msg), PChar(SShowConfirm),
    GetDialoagFlags(AllowActions) or MB_ICONQUESTION or MB_TASKMODAL) of
    IDYES: Result := uaYes;
    IDNO: Result := uaNo;
  else
    Result := uaCancel;
  end;
end;

procedure TdmContext.ShowError(const Msg: string; const HelpID: THelpID);
begin
  Application.MessageBox(PChar(Msg), PChar(SShowError), MB_OK or MB_ICONERROR or
    MB_TASKMODAL);
end;

procedure TdmContext.ShowMessage(const Msg: string; const HelpID: THelpID);
begin
  Application.MessageBox(PChar(Msg), PChar(SShowMessage), MB_OK or
    MB_ICONINFORMATION or MB_TASKMODAL);
end;

function TdmContext.ShowError2(const Msg: string; const HelpID: THelpID;
  AllowActions: TUserActions): TUserAction;
begin
  case Application.MessageBox(PChar(Msg), PChar(SShowMessage),
    GetDialoagFlags(AllowActions) or MB_ICONINFORMATION or MB_TASKMODAL) of
    IDYES: Result := uaYes;
    IDNO: Result := uaNo;
  else
    Result := uaCancel;
  end;
end;

function TdmContext.Warning(const Msg: string; const HelpID: THelpID;
  AllowActions: TUserActions): TUserAction;
begin
  case Application.MessageBox(PChar(Msg), PChar(SShowWarning),
    GetDialoagFlags(AllowActions) or MB_ICONWARNING or MB_TASKMODAL) of
    IDYES: Result := uaYes;
    IDNO: Result := uaNo;
  else
    Result := uaCancel;
  end;
end;

function TdmContext.Confirm2(const Msg: string;
  const HelpID: THelpID): Boolean;
begin
  Result := SpecialConfirm(Msg);
end;

procedure TdmContext.ShowWarning(const Msg: string; const HelpID: THelpID);
begin
  Application.MessageBox(PChar(Msg), PChar(SShowWarning), MB_OK or MB_ICONWARNING
    or MB_TASKMODAL);
end;

procedure TdmContext.ShowSuccess(const Msg: string);
begin
  Application.MessageBox(PChar(Msg), PChar(SShowSuccess), MB_OK or
    MB_ICONINFORMATION or MB_TASKMODAL);
end;

function TdmContext.InputText(const ACaption, APrompt: string;
  HideText, CustomerPassword: Boolean; var Value: string; MaxLength: Integer =
  0): Boolean;
begin
  Result := KSInputText(ACaption, APrompt, HideText, CustomerPassword, Value,
    MaxLength);
end;

// IExceptionHandler

procedure TdmContext.HandleException(E: Exception);
begin
  WriteException;
  if not (E is EAbort) then
  begin
    //Application.HandleException(Self);
    //Add EDBNoDataSet exception的处理
    //对于EDbNoDataSet，不调用ShowError
    if (E is EDbNoDataSet) then
      Exit;
    if E is EPrinter then
      ShowError(SPrinterError)
    else
      ShowError(E.Message);
  end;
end;

procedure TdmContext.HandleException2(Sender: TObject; E: Exception);
var
  Handled: Boolean;
  Field: TWVField;
  DataTypeDesc: string;
begin
  Handled := False;
  if (E is EConvertError) and (Sender is TControl) then
  begin
    Field := GetCtrlWorkField(TControl(Sender));
    if Field <> nil then
    begin
      Handled := True;
      case Field.DataType of
        kdtInteger, kdtInt64: DataTypeDesc := '整数';
        kdtFloat, kdtCurrency: DataTypeDesc := '浮点数';
        kdtChar, kdtWideChar, kdtString, kdtWideString: DataTypeDesc := '字符';
        kdtDateTime: DataTypeDesc := '日期';
        kdtBoolean: DataTypeDesc := '逻辑';
        kdtObject: DataTypeDesc := '对象';
      else
        Handled := False;
      end;
      if Handled then
      begin
        WriteException;
        ShowError(Format('需要为“%s”输入一个有效的%s值', [Field.Caption,
          DataTypeDesc]));
      end;
    end;
  end;
  if not Handled then
    HandleException(E);
end;

// IHelpSystem

procedure TdmContext.ShowHelp(const Help: THelpID);
begin
  if MainForm <> nil then
    MainForm.ShowHelp(Help);
end;

{
procedure TdmContext.StartSystem(Sender: TObject);
var
  TheConfigFileName : string;
begin
  FTerminated := False;
  FSysInitThread := nil;
  try
    WriteLog('Starting KSClient...',lcKSClientStart);
    // 创建上下文对象
    WriteLog('Create Context',lcKSClientStart);
    WriteStartProgress('创建上下文对象');
    SetContext(TMainContext.Create);
  except
    WriteException;
  end;
  try
    // 打开配置文件
    if ParamCount>=1 then
      TheConfigFileName := Context.GetStartDir + ConfigPath + ParamStr(1) else
      TheConfigFileName := Context.GetStartDir + ConfigPath +ConfigFileName;
    WriteLog('Use Config File '+TheConfigFileName,lcKSClientStart);
    FIniFile := TIniFile.Create(TheConfigFileName);
    // 初始化上下文对象（需要配置文件支持）
    TMainContext(Context).Init;
    // 设置日志类型
    SetupLogFile;
  except
    WriteException;
  end;
  StartModule(DatabaseModule,'初始化数据库连接');
  try
    // 初始化公共模块,必须在初始化其他模块以前初始化。
    WriteStartProgress('初始化公共模块');
    WriteLog('Start TComCmdDefinition',lcKSClientStart);
    ComCmdDefinition := TComCmdDefinition.Create(Application);
  except
    WriteException;
  end;

  // 初始化基本数据
  if FUseThread then
  begin
    FSysInitThread := TSysInitThread.Create;
    WriteLog('Use SysInitThread.',lcKSClientStart);
  end else
  begin
    WriteLog('Not Use SysInitThread.',lcKSClientStart);
  end;

  StartModule(MainForm,'初始化主界面');

  try
    // 装载程序包
    WriteStartProgress('装载程序包');
    LoadPackages;
  except
    WriteException;
  end;

  //WaitForInit;
  if not FUseThread then
    SomeSysInit;

  try
    WriteLog('Started KSClient.',lcKSClientStart);
    if DatabaseModule<>nil then
      DatabaseModule.ReadyForUse;
  except
    WriteException;
  end;
end;
}

procedure TdmContext.StartSystem(Sender: TObject);
begin
  FTerminated := False;
  FStartError := False;
  FSysInitThread := nil;
  FLoadPackages := nil;
  WriteLog('Starting KSClient...', lcKSClientStart);
  try
    WriteLog('Starting KSClient...', lcKSClientStart);
    // 创建上下文对象
    WriteStartProgress('创建上下文对象');
    WriteLog('Create Context', lcKSClient);
    SetContext(TMainContext.Create);

    // 初始化上下文对象（需要配置文件支持）
    TMainContext(Context).Init;

    RegisterModule(Self);

    // 设置日志类型
    SetupLogFile;

    StartModule(DatabaseModule, '初始化数据库连接');

    // 初始化公共模块,必须在初始化其他模块以前初始化。
    WriteStartProgress('初始化公共模块');
    WriteLog('Start TComCmdDefinition', lcKSClientStart);
    ComCmdDefinition := TComCmdDefinition.Create(Application);

    // 初始化基本数据
    if FUseThread then
    begin
      FSysInitThread := TSysInitThread.Create;
      WriteLog('Use SysInitThread.', lcKSClientStart);
    end
    else
    begin
      WriteLog('Not Use SysInitThread.', lcKSClientStart);
    end;

    StartModule(MainForm, '初始化主界面');

    try
      // 装载程序包
      WriteStartProgress('正在初始化程序包，请稍等...');
      LoadPackages;
    except
      WriteException; // 允许错误
    end;

    //WaitForInit;
    if not FUseThread then
      SomeSysInit;

    WriteLog('Started KSClient.', lcKSClientStart);
    if DatabaseModule <> nil then
      DatabaseModule.ReadyForUse;
    WriteLog('Started pwd end.', lcKSClientStart);
  except
    WriteException;
    FTerminated := True;
    FStartError := True;
    WaitForInit;
  end;
end;

procedure TdmContext.ShutDownSystem(Sender: TObject);
var
  Temp: TObject;
begin
  WriteLog('Shuting down KSClient...', lcKSClientShutDown);
  if DatabaseModule <> nil then
    TKCDatabase(DatabaseModule.GetDatabase).Close;
  // 关闭主界面
  ShutDownModule(MainForm, 'Shutdown MainForm...');
  // 关闭其他
  ShutDownModule(SysModule1, 'Shutdown SysModule1...');
  ShutDownModule(SysModule2, 'Shutdown SysModule2...');
  ShutDownModule(SysModule3, 'Shutdown SysModule3...');
  //
  FreeAndNil(ComCmdDefinition);
  // 释放数据库连接
  ShutDownModule(DatabaseModule, 'Shutdown DatabaseModule...');
  // 释放上下文对象
  WriteLog('Destroy Context', lcKSClientShutDown);
  Temp := Context;
  SetContext(nil);
  Temp.Free;
  dmContext := nil;
  WriteLog('Shut down KSClient.', lcKSClientShutDown);
end;

procedure TdmContext.LoadPackages;
var
  ConfigSystem: IConfigSystem;
  Count: Integer;
  I: Integer;
  Key: string;
  PackageFile: string;
  FLoadPackageCategory: string;
begin
  ConfigSystem := Context.GetConfigSystem;
  if LoadPackageCategory = '' then
    FLoadPackageCategory := ccPackages
  else
    FLoadPackageCategory := LoadPackageCategory;
  Count := ConfigSystem.ReadInteger(FLoadPackageCategory, ckPackageCount, 0);
  FLoadPackages := TStringList.Create;
  for I := 1 to Count do
  begin
    Key := IntToStr(I);
    PackageFile := ConfigSystem.ReadString(FLoadPackageCategory, Key, '');
    if PackageFile <> '' then
    begin
      FLoadPackages.Add(PackageFile);
    end;
    //FLoadPackages.Add('..\bin\model\test.bpl');
    //Sleep(100); //在这里sleep没有什么用途
  end;
  //加载完成后加载特有的模块包,0为非调试模式
  if ifDebug=0 then
    SearchFile(appPath+'module\',FLoadPackages)
  else
    SearchFile(appPath+'moduledebug\',FLoadPackages);

  Timer.Enabled := True;
end;

procedure TdmContext.SearchFile(path: string; pagList: TStringList);
var
  SearchRec:TSearchRec;
  found:integer;
begin
  found:=FindFirst(path+'*.*',faanyFile,SearchRec);
  while found=0 do
  begin
    if (SearchRec.Name<>'.') and (SearchRec.name<>'..') and (SearchRec.Attr=faDirectory) then
    begin
      SearchFile(SearchRec.Name+'\',pagList);
    end
    else
    begin
      if ExtractFileExt(SearchRec.Name)='.bpl' then
      begin
        pagList.Add(path+SearchRec.Name);
      end;
    end;
    found:=FindNext(SearchREc);
  end;
  FindClose(SearchRec);
end;

procedure TdmContext.ShowWaiting(const Msg: string);
begin
  if DatabaseModule <> nil then
    DatabaseModule.ShowWaiting(Msg);
end;

procedure TdmContext.CloseWaiting;
begin
  if DatabaseModule <> nil then
    DatabaseModule.CloseWaiting;
end;

procedure TdmContext.SetupLogFile;
var
  ConfigSystem: IConfigSystem;
begin
  LogCatalogs := [lcException, lcKCProcessor, lcKCDataset];
  ConfigSystem := Context.GetConfigSystem;
  if ConfigSystem.ReadBoolean(ccLog, ckObjectLife, cdObjectLife) then
    Include(LogCatalogs, lcConstruct_Destroy);
  if ConfigSystem.ReadBoolean(ccLog, ckDataset, cdDataset) then
  begin
    Include(LogCatalogs, lcDBAIntfHelper);
    Include(LogCatalogs, lcDataset);
  end;
  if ConfigSystem.ReadBoolean(ccLog, ckKsClientPreQuery, cdKsClientPreQuery)
    then
  begin
    Include(LogCatalogs, lcKsClientPreQuery);
  end;

{$IFNDEF Release}
  if ConfigSystem.ReadBoolean(ccLog, ckDataPack, cdDataPack) then
    Include(LogCatalogs, lcKCPack);
  if ConfigSystem.ReadBoolean(ccLog, ckKCDataset, cdKCDataset) then
    Include(LogCatalogs, lcKCDatasetDetail);
  if ConfigSystem.ReadBoolean(ccLog, ckCommand, cdCommand) then
    Include(LogCatalogs, lcCommand);
{$ENDIF}
  if ConfigSystem.ReadBoolean(ccLog, ckApplication, cdApplication) then
  begin
    Include(LogCatalogs, lcKSClient);
    Include(LogCatalogs, lcKSClientStart);
    Include(LogCatalogs, lcKSClientShutDown);
    Include(LogCatalogs, lcKSClientLoadPackage);
    Include(LogCatalogs, lcKSClientUnLoadPackage);
  end;
  if ConfigSystem.ReadBoolean(ccLog, ckDebug, cdDebug) then
    Include(LogCatalogs, lcDebug);

  FUseThread := ConfigSystem.ReadBoolean(ccMain, ckUseThread, cdUseThread);
end;

procedure TdmContext.DoLogin;
var
  FContext: TMainContext;
  ExitApp: Boolean;
begin
  if FTerminated then
    Exit;
  if FirstLogin = 0 then
    FirstLogin := GetTickCount;
  FContext := TMainContext(Context);
  FContext.BeginUpdate;
  repeat
    try
      ULogin.DoLogin(ExitApp);
      if ExitApp then
      begin
        Application.Terminate;
        FTerminated := True;
        Break;
      end;
    except
      on E: Exception do
        Context.GetExceptionHandler.HandleException(E);
    end;
  until not FContext.FLoginStatus.IsEmpty and (FContext.FLoginStatus.AsBoolean =
    True);
  FContext.EndUpdate;

  //登录成功后，进行一些 必须以 当前 操作员 为条件的 个性化查询,结果放在内存。
  if not ExitApp then
  begin
    try
      Context.GetDialogSystem.ShowWaiting(SWait);
      try
        WriteLog('Before DoBaseInitAferLogin', lcKsClientPreQuery);

        with Application do
        begin
          MainForm.Caption := MainForm.Caption + '-' +
            Context.ParamData(svOperatorNoName).AsString;
          Title := MainForm.Caption;
        end;
{$IFNDEF KSMONCLIENT}
        DoBaseInitAferLogin(False);
        WriteLog('Done DoBaseInitAferLogin', lcKsClientPreQuery);
{$ENDIF}
{$IFDEF KSTRADER}
        WriteLog('Before DoTraderInitAfterLogin', lcKsClientPreQuery);
        DoTraderInitAfterLogin(False);
        WriteLog('Done DoTraderInitAfterLogin', lcKsClientPreQuery);
{$ENDIF}
{$IFDEF KSREPORT}
        WriteLog('Before DoTraderInitAfterLogin', lcKsClientPreQuery);
        DoTraderInitAfterLogin(False);
        WriteLog('Done DoTraderInitAfterLogin', lcKsClientPreQuery);
{$ENDIF}
      finally
        Context.GetDialogSystem.CloseWaiting;
      end;
    except
      on E: Exception do
      begin
        Context.GetExceptionHandler.HandleException(E);
      end;
    end;
    Context.GetConfigSystem.WriteString(
      ccAllUsers,
      Format(ckUser, [Context.GetParamValue(svDepartNoName)]),
      Context.GetParamValue(svOperatorNoName));
    if (Context.GetRobotSystem <> nil) then
      Context.GetRobotSystem.OperatorChanged(Context.GetParamValue(svOperatorNoName));
  end;
end;

procedure TdmContext.DoLogout;
var
  FContext: TMainContext;
begin
  FContext := TMainContext(Context);
  FContext.BeginUpdate;
  try
    if TMainContext(Context).GetLogined then
    begin
      try
        try
          rqLogout.SendCommand;
        finally
          TMainContext(Context).Reset;
          with Application do
          begin
            MainForm.Caption := SApplicationTitle;
            Title := SApplicationTitle;
          end;
        end;
      except
        WriteException;
      end;
    end;
  finally
    FContext.EndUpdate;
  end;
end;

procedure TdmContext.StartModule(const Module: IKSModule;
  const ACaption: string);
begin
  if Module <> nil then
  begin
    {
    try
      if ACaption<>'' then
        WriteStartProgress(ACaption);
      Module.Start;
    except
      WriteException;
    end;
    }
    if ACaption <> '' then
      WriteStartProgress(ACaption);
    Module.Start;
  end;
end;

procedure TdmContext.ShutDownModule(const Module: IKSModule;
  const ACaption: string);
begin
  if Module <> nil then
  begin
    try
      if ACaption <> '' then
        WriteLog(ACaption, lcKSClientShutDown);
      Module.ShutDown;
    except
      WriteException;
    end;
  end;
end;

procedure TdmContext.SomeSysInit;
//var
  //s: string;
begin
  try
    if MainThreadID = GetCurrentThreadId then
      WriteStartProgress('初始化基本数据');
    WriteLog('Start SysModule1', lcKSClientStart);
    StartModule(SysModule1); //TdmCommData
    WriteLog('Start SysModule2', lcKSClientStart);
    StartModule(SysModule2);
    WriteLog('Start SysModule3', lcKSClientStart);
    StartModule(SysModule3);
    WriteLog('Done SomeSysInit', lcKSClientStart);

    WriteLog('RefreshSysParams... ', lcKSClientStart);
    TMainContext(Context).RefreshSysParams(SmartCardSystemDate);
    WriteLog('RefreshSysParams OK', lcKSClientStart);

    //    InfoAdmin := TInfoAdmin.Create;
  except
    WriteException;
    FTerminated := True;
    FStartError := True;
  end;
  FinishSomeSysInit := GetTickCount;
end;

procedure TdmContext.WaitForInit;
var
  H: THandle;
  R: LongWord;
begin
  while DoLoadOnePackage do
    ;
  FreeAndNil(FLoadPackages);

  if FUseThread and (FSysInitThread <> nil) then
  begin
    ShowProgress('等待系统初始化', False, '', '', 0);
    try
      //FSysInitThread.WaitFor;
      H := FSysInitThread.Handle;
      repeat
        R := MsgWaitForMultipleObjects(1, H, False, 1000,
          QS_ALLINPUT {QS_SENDMESSAGE});
        UpdateProgress;
      until R = WAIT_OBJECT_0;
      FreeAndNil(FSysInitThread);
    finally
      CloseProgress;
    end;
  end;

  if Terminated then
  begin
    if FStartError then
      ShowError('程序启动错误，可能是无法连接到服务器，请依次检查日志文件、网络状态、系统配置。');
    Application.Terminate;
  end;
  if FirstWaitForInit = 0 then
    FirstWaitForInit := GetTickCount;
  WriteLog(Format('System Initialized, FinishSomeSysInit=%d,FirstWaitForInit=%d,FirstLogin=%d.',
    [FinishSomeSysInit - StartTime, FirstWaitForInit - StartTime, FirstLogin -
    StartTime]),
      lcKSClientStart);
end;

function TdmContext.DoSingleStationCheck(const AOperation: string;
  var CheckerNo, CheckerPassword: string;
  FuncNo: Integer = 0;
  const CustomerNo: string = '';
  const CurrentType: string = '';
  const ACaption: string = ''
  ): Boolean;
begin
  Result := UDoubleCheck.DoSingleStationCheck(
    AOperation,
    CheckerNo,
    CheckerPassword,
    FuncNo,
    CustomerNo,
    CurrentType,
    ACaption);
end;

function TdmContext.GetDialoagFlags(AllowActions: TUserActions): LongInt;
begin
  if AllowActions = [uaYes, uaNo, uaCancel] then
    Result := MB_YESNOCANCEL
  else if AllowActions = [uaYes, uaNo] then
    Result := MB_YESNO
  else
    Result := MB_YESNOCANCEL;
end;

procedure TdmContext.ShowHintFor(Control: TControl; const HintStr: string);
begin
  if MainForm <> nil then
    MainForm.ShowHintFor(Control, HintStr);
end;

procedure TdmContext.LoadOnePackage(Sender: TObject);
begin
  DoLoadOnePackage;
end;

procedure TdmContext.LoadPackage(const PackageFileName: string);
var
  Handle: THandle;
begin
    WriteLog('Loading Package begin', lcKSClientLoadPackage);

  WriteLog('Loading Package ' + PackageFileName, lcKSClientLoadPackage);
  try
    Handle := SysUtils.LoadPackage(PackageFileName);
    Sleep(50);
    if Handle <= 32 then
      WriteLog('Load Package Error!', lcKSClientLoadPackage)
    else
      WriteLog('Loaded Package ' + PackageFileName, lcKSClientLoadPackage);
  except
    WriteException;
  end;
end;

function TdmContext.DoLoadOnePackage: Boolean;
var
  PackageFileName: string;
begin
  if (FLoadPackages <> nil) and (FLoadPackages.Count > 0) then
  begin
    PackageFileName := FLoadPackages[0];
    FLoadPackages.Delete(0);
    LoadPackage(PackageFileName);
  end;
  Result := (FLoadPackages <> nil) and (FLoadPackages.Count > 0);
  Timer.Enabled := Result;
end;

procedure TdmContext.DoLock;
var
  ExitApp: Boolean;
begin
  try
    ULogin.DoUnLock(ExitApp);
    if ExitApp then
    begin
      Application.Terminate;
      FTerminated := True;
    end;
  except
    on E: Exception do
      Context.GetExceptionHandler.HandleException(E);
  end;
end;

procedure InitLogFile;
const
  FileNameSize = 256;
var
  Buffer: array[0..FileNameSize - 1] of Char;
  WindowsDir: string;
begin
  FillChar(Buffer, SizeOf(Buffer), 0);
  GetWindowsDirectory(PChar(@Buffer), FileNameSize - 1);
  WindowsDir := string(PChar(@Buffer));
  ProgramLogFileName := AddPathAndName(ExtractFileDir(WindowsDir), 'KSManageSys.Log');
  // 打开日志文件
  openLogFile(ProgramLogFileName, False, True);
end;

procedure TdmContext.DoCheckReturnValue(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TdmContext.DoGetInfo;
var
  ds: TDataset;
  str: string;
begin
  try
    rqInfo.SendCommand;
    if wvInfo.FieldByName('返回码').Data.AsInteger = 0 then
    begin
      ds := TDataset.Create(nil);
      try
        ds := TDataset(wvInfo.FieldByName('查询结果集').Data.AsObject);
        while not ds.Eof do
        begin
          str := str + ds.FieldByName('vsvarstr0').AsString + #13 + #10;
          ds.Next;
        end;
        Context.GetDialogSystem.ShowMessage(str);
      except
      end;
      ds.Free;
    end;
  except
    Context.GetDialogSystem.ShowError(wvInfo.FieldByName('返回信息').Data.AsString);
  end;
end;

procedure TdmContext.DoTraderInitAfterLogin(OnlyCustNO: Boolean);
var
  tempList: TObjectList;
  //tempSL: TStringList;
  OperatorNo: string;
  //Command: TWVCommand;
  //Seat_No: string;
  //tempDS: TKCDataset;
begin
  CheckObject(Context, 'Invalid Context');
  tempList := UIShareObjList;
  Assert(tempList <> nil);
  OperatorNo := Context.ParamData(svOperatorNoName).AsString;

  {**********************************************
          Kingstar Delphi Library
     Copyright (C) Kingstar Corporation
     <Unit>
     <What>  ObjectList.Items[0]: 交易所/席位号对应列表    851236 操作员，交易所代码  交易所代码   ＝席位号1,席位号2
             ObjectList.Items[1]: 可交易合约/币种对应列表  854044 交易所代码  合约号       ＝交易所代码,币种
             ObjectList.Items[2]: 多交易编号客户列表    854040  操作员    客户号,席位号＝交易编码1,交易编码2
             ObjectList.Items[3]: 可交易客户号列表      854052  操作员    操作员＝客户号
             ObjectList.Items[4]: 查询参数传递列表

             这个仅仅是创建的顺序，具体哪个按名来读写。
     <Written By> Zhu pengfei (朱朋飞)
     <History>
  **********************************************}

    //ObjectList.Items[3]: 可交易客户号列表      854052  操作员    客户号＝操作员
  //初始化的时候，不查询，防止网络堵塞。
  {
  tempSL := CreateOneStringList(tempList,SLName_CustNO_CanTrade);
  if OnlyCustNO = True then
  begin
    Command := Context.CommandFactory.NewCommand(dmCommData.ctquery_oper_manage_cust.ID,dmCommData.ctquery_oper_manage_cust.Version);
    try
      Command.ParamData('操作员').SetString(OperatorNo);
      Command.ParamData('显示详细信息标记').SetString('1');
      Context.CommandBus.Process(Command);
      CheckCommandReturnValue(Command,False);
      tempDS := TKCDataset(Command.ParamData('返回结果集').AsObject);
      try
        tempDS.First;
        while not tempDS.Eof do
        begin
          tempSL.Add(tempDS.FieldByName('sholder_ac_no').AsString + '=' + tempDS.FieldByName('scust_no').AsString);
          tempDS.Next;
        end;
      except
        WriteLog(dmCommData.ctquery_oper_manage_cust.ID + cpReturnEmptyDataSet,lcKsClientPreQuery);
      end;

    finally
      Command.Free;
    end;
    Exit;
  end;
  }

  //ObjectList.Items[0]: 交易所/席位号对应列表    851236 操作员，交易所代码  交易所代码   ＝席位号1,席位号2
 { tempSL := CreateOneStringList(tempList,SLName_Enturst_Exchange_Seat);
  Command := Context.CommandFactory.NewCommand(dmCommData.ctQueryExchSeat.ID,dmCommData.ctQueryExchSeat.Version);
  try
    Command.ParamData('操作员').SetString('');
    Command.ParamData('交易所代码').SetString('');
    Command.ParamData('可交易席位标志').SetString('1');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    tempDS := TKCDataset(Command.ParamData('返回结果集').AsObject);
    try
      tempDS.First;
      while not tempDS.Eof do
      begin
        if tempSL.Values[tempDS.FieldByName('smarket_code').AsString] <> '' then
           begin
          //要求把主席位放在第一个。
          if tempDS.FieldByName('sstatus1').AsString = '1' then
            tempSL.Values[tempDS.FieldByName('smarket_code').AsString] :=
              tempDS.FieldByName('sserial2').AsString + ',' +
                tempSL.Values[tempDS.FieldByName('smarket_code').AsString]
          else
            tempSL.Values[tempDS.FieldByName('smarket_code').AsString] :=
             tempSL.Values[tempDS.FieldByName('smarket_code').AsString] + ',' +
               tempDS.FieldByName('sserial2').AsString;
        end
        else
          tempSL.Values[tempDS.FieldByName('smarket_code').AsString] := tempDS.FieldByName('sserial2').AsString;
        tempDS.Next;
      end;
    except
      WriteLog(dmCommData.ctQueryExchSeat.ID + cpReturnEmptyDataSet,lcKsClientPreQuery);
    end;
  finally
    FreeAndNil(tempDS);
    Command.Free;
  end;
}
{
  //ObjectList.Items[1]: 可交易合约/币种对应列表  854044 交易所代码  合约号       ＝交易所代码,币种
  tempSL := CreateOneStringList(tempList,SLName_Compact_Money);
  Command := Context.CommandFactory.NewCommand(dmCommData.ctquery_tradeable_type.ID,dmCommData.ctquery_tradeable_type.Version);
  try
//    Command.ParamData('操作员').SetString('');
    Seat_No := (Context.ParamData(svSeatNoName)).AsString ;
    if Seat_No <> 'all_seat' then
    begin
        Command.ParamData('席位号').SetString(Seat_No);
    end
    else
    begin
        Command.ParamData('席位号').SetString('');
    end;
    Command.ParamData('交易所代码').SetString('');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    tempDS := TKCDataset(Command.ParamData('返回结果集').AsObject);
    try
      tempDS.First;
      while not tempDS.Eof do
      begin
        tempSL.Add(tempDS.FieldByName('scust_auth').AsString + '=' + tempDS.FieldByName('smarket_code').AsString
          + ',' + tempDS.FieldByName('scurrency_type').AsString);
        tempDS.Next;
      end;
    except
      WriteLog(dmCommData.ctquery_tradeable_type.ID + cpReturnEmptyDataSet,lcKsClientPreQuery);
    end;
  finally
    FreeAndNil(tempDS);
    Command.Free;
  end;
}
{
  //ObjectList.Items[2]: 多交易编号客户列表    854040  操作员    客户号,席位号＝交易编码1,交易编码2
  tempSL := CreateOneStringList(tempList,SLName_CustNO_MulTraderNO);
  Command := Context.CommandFactory.NewCommand(
    dmCommData.ctquery_multi_exch_code_cust_according_oper.ID,dmCommData.ctquery_multi_exch_code_cust_according_oper.Version);
  try
    Command.ParamData('操作员').SetString(OperatorNo);
//    Command.ParamData('交易所代码').SetString('');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    tempDS := TKCDataset(Command.ParamData('返回结果集').AsObject);
    try
      tempDS.First;
      while not tempDS.Eof do
      begin

        if tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
          tempDS.FieldByName('sserial2').AsString] <> '' then
        begin
        //要求把主交易编码放在第一个。
          if tempDS.FieldByName('smain_flag').AsString = '1' then
            tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
            tempDS.FieldByName('sserial2').AsString] :=
              tempDS.FieldByName('sholder_ac_no2').AsString + ',' +
                tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
                 tempDS.FieldByName('sserial2').AsString]
          else
            tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
            tempDS.FieldByName('sserial2').AsString] :=
               tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
               tempDS.FieldByName('sserial2').AsString] + ',' +
                 tempDS.FieldByName('sholder_ac_no2').AsString;
        end
        else
          tempSL.Values[tempDS.FieldByName('sholder_ac_no').AsString + ',' +
                tempDS.FieldByName('sserial2').AsString] := tempDS.FieldByName('sholder_ac_no2').AsString;
        tempDS.Next;
      end;
    except
      WriteLog(dmCommData.ctquery_multi_exch_code_cust_according_oper.ID + cpReturnEmptyDataSet,lcKsClientPreQuery);
    end;

  finally
    FreeAndNil(tempDS);
    Command.Free;
  end;

}
//  ObjectList.Items[4]: 查询参数传递列表      先创建一个空的参数列表对象。
  CreateOneStringList(tempList, SLName_QueryParm);
  //ADD BY ZKJ
  CreateOneStringList(tempList, SLName_CustNO_Transfer);
  //用于下单界面的客户号列表
  CreateOneStringList(tempList, SLName_EntrustParam);
  CreateOneStringList(tempList, SLName_PreEntrust);
  CreateOneStringList(tempList, SLName_WithDrawEntrust);

  //rding,20040602,初始化席位时间差列表
  //ObjectList.Items[9]: 席位/时间差对应列表    854046 席位号=席位名称，时间差
{  tempSL := CreateOneStringList(tempList,SLName_Seat_TimeDelta);
  Command := Context.CommandFactory.NewCommand(dmCommData.ctSeatTimeDelta.ID,dmCommData.ctSeatTimeDelta.Version);
  try
    Command.ParamData('席位号').SetString('');
    Context.CommandBus.Process(Command);
    CheckCommandReturnValue(Command,False);
    tempDS := TKCDataset(Command.ParamData('返回结果集').AsObject);
    try
      tempDS.First;
      while not tempDS.Eof do
      begin
        tempSL.Add(tempDS.FieldByName('SSERIAL2').AsString + '=' + tempDS.FieldByName('SNAME').AsString
                        + ',' + tempDS.FieldByName('LVOL9').AsString);
        tempDS.Next;
      end;
    except
      WriteLog(dmCommData.ctSeatTimeDelta.ID + cpReturnEmptyDataSet,lcKsClientPreQuery);
    end;
  finally
    FreeAndNil(tempDS);
    Command.Free;
  end;
}
end;

procedure TdmContext.DoBaseInitAferLogin(OnlyCustNO: Boolean);
//var
  //tempList: TObjectList;
  //tempSL: TStringList;
  //OperatorNo: string;
  //Command: TWVCommand;
  //tempDS: TKCDataset;
  //CodeField, NameField: TField;
  //IdObjectList: TIdObjectList;
  //I: Integer;
begin

end;

procedure TdmContext.BuidProPerDD(SourceSL: TStringList;
  SourceDDEntry, BeginDDEntry: Integer);
var
  DataSourceSL: TStringList;
  ExchangeIDObj, NewExchangeIDObj: TIdObjectList;
  I, J: Integer;
  tempValue: string;
begin
  //根据传入的数据，构造数据字典，并且将输入的列表变为：
  //结构是：交易所＝字典号
  ExchangeIDObj := NeedIdObjectList(deExchange);
  Assert(ExchangeIDObj <> nil);
  if ExchangeIDObj.Count < 1 then
    Exit;

  DataSourceSL := TStringList.Create;
  try
    DataSourceSL.Assign(SourceSL);
    SourceSL.Clear;
    SourceSL.Add(DataSourceSL[0]);
    for J := BeginDDEntry downto BeginDDEntry - (ExchangeIDObj.Count - 1) do
    begin
      FreeIdObjects(J);
      NewExchangeIDObj := TIdObjectList.Create(J, CurrentDepartmentNo);
      for I := 0 to DataSourceSL.Count - 1 do
        if DataSourceSL.Names[I] = ExchangeIDObj.Items[BeginDDEntry - J].ID then
        begin
          tempValue := Copy(DataSourceSL[I], Pos('=', DataSourceSL[I]) + 1,
            Length(DataSourceSL[I]));
              //DataSourceSL.Values[DataSourceSL.Names[I]];
          NewExchangeIDObj.Add(TIdObject.Create(Copy(tempValue, 1, Pos(',',
            tempValue) - 1),
            Copy(tempValue, Pos(',', tempValue) + 1, Length(DataSourceSL[I]))));
        end;
      SourceSL.Add(ExchangeIDObj.Items[BeginDDEntry - J].ID + '=' +
        IntToStr(J));
    end;
  finally
    DataSourceSL.Free;
  end;

end;

procedure TdmContext.rqSubsystemRegeditAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TdmContext.rqSubsystemLoginAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

procedure TdmContext.rqSubsystemLogoutAfterExec(Request: TWVRequest;
  Command: TWVCommand);
begin
  CheckCommandReturnValue(Command);
end;

initialization
  InitLogFile;
  isOutputDebugString := False;
  LoadPackageCategory := ccPackages;

end.

