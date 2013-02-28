unit UMain;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation
   <Unit>UMain
   <What>主程序
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ImgList, ToolWin, ExtCtrls, Buttons,Commctrl,
  Contnrs, KSMenuAdmin, KSFrameWorks, ActnList,IniFiles,
  UICtrls, ImageCtrls, Menus, KSHints, WorkViews,
  FilterCombos, RPProcessors, UPersonalMenus, KSClientConsts, DataTypes,
  UQhClientConsts, UPushRevThread, RzTreeVw, RzButton, RzRadChk,
  RzTabs,KCDataPack, WinSkinData, WinSkinStore, SkinCaption, RzPanel,
  RzSplit, AAFont, AACtrls, jpeg,CardDll,NativeXml, IdBaseComponent,
  IdComponent, IdTCPConnection, IdTCPClient, IdHTTP;

const
  WM_ShowMenu = WM_User + 1234;
  WM_Start = WM_ShowMenu + 1;
  //在主程序外调用界面创建函数的消息
  KS_SetCustPara1 = WM_User + $1000;
  KS_WarningInfo = WM_User + $2000;

  MaxStyles = 2;

  //DepartPanelIndex = 1;
  OperatorPanelIndex = 1;
  HintPanelIndex = 2;
  InvalidFieldsPanelIndex = 3;

  //wsn 20040114 添加一个错误提示
  WarningHintIndex = 0;

  MenuGroupChar = '+';
  MenuIdent = 14;
  RootImageIndex = 0;
  MenuGroupImageIndex = 1;
  MenuItemImageIndex = 2;

  MinGuideWidth = 10;

  //DropDownChar = #130; // wingding3
  DropDownChar = #209; // symbol

  AutoLockFormat = '%d秒以后自动锁定[&B]';

type
  TWorkSpace = class(TCustomWorkSpace)
  protected
    procedure FitSize(W, H: Integer); override;
    procedure UIStatusChanged(InstanceRecord: TUIInstanceRecord); override;
    procedure Release(InstanceRecord: TUIInstanceRecord); override;
  end;

  TFormWorkSpace = class(TCustomWorkSpace)
  protected
    procedure FitSize(W, H: Integer); override;
    procedure UIStatusChanged(InstanceRecord: TUIInstanceRecord); override;
    procedure Release(InstanceRecord: TUIInstanceRecord); override;
  end;

  TViewStatus = (vsNone, vsMenu, vsHelp);

  TRunStatus = (
    rsCreate, // 创建
    rsStart, // start阶段
    rsFirstShow, // 第一次显示
    rsWaitInit, // 等待context的初始化
    rsRun, // 执行阶段
    rsLocked, // 锁定
    rsShutdown, // 关闭
    rsDestroy // 释放
    );

  TfmMain = class(TForm, IKSMainForm)
    TitleBar: TUIPanel;
    PositionBar: TUIPanel;
    StatusBar: TStatusBar;
    WorkContainer: TUIPanel;
    alSystem: TActionList;
    acUseMenu: TAction;
    acZoom: TAction;
    acHelp: TAction;
    acGoGuideHome: TAction;
    acSearch: TAction;
    acCloseWork: TAction;
    acLogout: TAction;
    acSetPrinter: TAction;
    acPrint: TAction;
    acAdjustGrid: TAction;
    acFind: TAction;
    acNextFind: TAction;
    PrinterSetupDialog: TPrinterSetupDialog;
    alCommon: TActionList;
    acMin: TAction;
    acExit: TAction;
    mnDebug: TPopupMenu;
    miDebugDataset: TMenuItem;
    acDebugDataset: TAction;
    acDebugWorkView: TAction;
    acDebugUI: TAction;
    miDebugWorkView: TMenuItem;
    miDebugUI: TMenuItem;
    acDebugDataSource: TAction;
    miDebugDataSource: TMenuItem;
    acDebugDatabase: TAction;
    miDebugDatabase: TMenuItem;
    acShowLog: TAction;
    miShowLog: TMenuItem;
    WorkViewCenter: TWorkViewCenter;
    HintMan: THintMan;
    acSearchMenuBySpell: TAction;
    mnSystem: TPopupMenu;
    mnCommon: TPopupMenu;
    N1: TMenuItem;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    N6: TMenuItem;
    N7: TMenuItem;
    N8: TMenuItem;
    N9: TMenuItem;
    N10: TMenuItem;
    N11: TMenuItem;
    acRestore: TAction;
    N12: TMenuItem;
    N13: TMenuItem;
    acUpdateDataDict: TAction;
    N14: TMenuItem;
    Timer: TTimer;
    acLockApp: TAction;
    N15: TMenuItem;
    mnCatelogMenus: TPopupMenu;
    acFocusGrid: TAction;
    N16: TMenuItem;
    miAddCurToPersonalMenu: TMenuItem;
    miManagePersonalMenu: TMenuItem;
    N19: TMenuItem;
    alPersonMenu: TActionList;
    acAddCurToPersonalMenu: TAction;
    acManagePersonalMenu: TAction;
    alPageSwitch: TActionList;
    acPrevPage: TAction;
    acNextPage: TAction;
    acBrowseLocalDir: TAction;
    N17: TMenuItem;
    acWhatFocused: TAction;
    acWhatFocused1: TMenuItem;
    lbDepartmentName: TLabel;
    acClearLog: TAction;
    miClearLog: TMenuItem;
    N18: TMenuItem;
    acSmartFind: TAction;
    test1: TMenuItem;
    WorkArea: TRzPageControl;
    ilButtons: TImageList;
    StatusBar1: TStatusBar;
    N20: TMenuItem;
    N21: TMenuItem;
    N2: TMenuItem;
    N22: TMenuItem;
    N23: TMenuItem;
    N24: TMenuItem;
    N25: TMenuItem;
    N26: TMenuItem;
    N27: TMenuItem;
    SkinCaption1: TSkinCaption;
    SkinData1: TSkinData;
    spnlTree: TRzSizePanel;
    MenuTree: TRzTreeView;
    ilTree: TImageList;
    bvl1: TBevel;
    bvl2: TBevel;
    img2: TImage;
    btnMin: TRzToolbarButton;
    btnExit: TRzToolbarButton;
    btnLock: TRzToolbarButton;
    btnLogout: TRzToolbarButton;
    btnAbout: TRzToolbarButton;
    btnDebug: TRzMenuToolbarButton;
    btnSystem: TRzMenuToolbarButton;
    btnCommon: TRzMenuToolbarButton;
    imgTitle2: TImage;
    lbDropDownOpMenu: TUILabel;
    Label3: TLabel;
    MenuCaptionSpell: TKSFilterComboBox;
    lbSystemDate: TLabel;
    ckAutoLock: TRzCheckBox;
    btnCloseWork: TRzToolbarButton;
    imgKingstar: TImage;
    albl1: TAALabel;
    idhtp1: TIdHTTP;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnViewGuideBarClick(Sender: TObject);
    procedure btnViewMenuClick(Sender: TObject);
    procedure btnViewHelpClick(Sender: TObject);
    //procedure MenuClick(Sender : TObject);
    procedure MenuTreeClick(Sender: TObject);
    procedure MenuTreeKeyPress(Sender: TObject; var Key: Char);
    procedure acUseMenuExecute(Sender: TObject);
    procedure WorkAreaChange(Sender: TObject);
    procedure acSearchExecute(Sender: TObject);
    procedure acGoGuideHomeExecute(Sender: TObject);
    procedure acCloseWorkExecute(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure acLogoutExecute(Sender: TObject);
    procedure acSetPrinterExecute(Sender: TObject);
    procedure acPrintExecute(Sender: TObject);
    procedure acAdjustGridExecute(Sender: TObject);
    procedure acFindExecute(Sender: TObject);
    procedure acNextFindExecute(Sender: TObject);
    procedure alCommonUpdate(Action: TBasicAction;
      var Handled: Boolean);
    procedure acMinExecute(Sender: TObject);
    procedure acExitExecute(Sender: TObject);
    procedure acDebugDatasetExecute(Sender: TObject);
    procedure acDebugWorkViewExecute(Sender: TObject);
    procedure acDebugUIExecute(Sender: TObject);
    procedure acDebugDataSourceExecute(Sender: TObject);
    procedure acDebugDatabaseExecute(Sender: TObject);
    procedure acShowLogExecute(Sender: TObject);
    procedure WorkViewCenterException(Sender: TObject; E: Exception);
    procedure WorkViewCenterInvalidInput(WorkField: TWVField;
      Target: TObject);
    procedure Splitter1CanResize(Sender: TObject; var NewSize: Integer;
      var Accept: Boolean);
    procedure MenuCaptionSpellFilterItems(Sender: TObject);
    procedure MenuCaptionSpellGetSelectedText(
      Sender: TKSCustomFilterComboBox; var AText: string);
    procedure MenuCaptionSpellSelected(Sender: TObject);
    procedure acSearchMenuBySpellExecute(Sender: TObject);
    procedure acRestoreExecute(Sender: TObject);
    procedure acUpdateDataDictExecute(Sender: TObject);
    procedure DropDownMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure TimerTimer(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure MenuTreeKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure acLockAppExecute(Sender: TObject);
    procedure RPGlobeAfterPrint(Sender: TObject);
    procedure acFocusGridExecute(Sender: TObject);
    procedure acAddCurToPersonalMenuExecute(Sender: TObject);
    procedure acManagePersonalMenuExecute(Sender: TObject);
    procedure MenuTreeKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure acPrevPageExecute(Sender: TObject);
    procedure acNextPageExecute(Sender: TObject);
    procedure acBrowseLocalDirExecute(Sender: TObject);
    procedure PositionBarDblClick(Sender: TObject);
    procedure acWhatFocusedExecute(Sender: TObject);
    procedure acClearLogExecute(Sender: TObject);
    procedure acSmartFindExecuteExecute(Sender: TObject);
    procedure test1Click(Sender: TObject);
    procedure WorkContainerCanResize(Sender: TObject; var NewWidth,
      NewHeight: Integer; var Resize: Boolean);
    procedure N21Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure MenuTreeCustomDraw(Sender: TCustomTreeView;
      const ARect: TRect; var DefaultDraw: Boolean);
    procedure N23Click(Sender: TObject);
    procedure btnAboutClick(Sender: TObject);
  private
    { Private declarations }

    RevPushThread: TPushRevThread;
    //FStartpage: T;
    //FHTMLBrowser: TfaHTMLBrowser;
    //FHasHTMLBrowser: Boolean;
    //FNoHTMLHint: string;
    FMenuCatalogs: TUIMenuGroup;
    FFavorites: TUIMenuGroup;
    FReferences: TUIMenuGroup;
    FCurrentMenu: TUIMenu;
    FHelpIDs: TStringList;
    FViewStatus: TViewStatus;
    FUIInstanceRecords: TObjectList;
    FMaxUICount: Integer;
    FNestedMenu: Boolean;
    FFirst: Boolean;
    FConfirmClose: Boolean;
    FStyleIndex: Integer;
    FTreeRootFont: TFont;
    FTreeLeaveFont: TFont;
    FWarningFont: TFont;
    FHaveDebugSystem: Boolean;
    FReady: Boolean;
    FShowTutorial: Boolean;
    FRunStatus: TRunStatus;
    FMenuAuth: string;
    FShowMenuIcon: Boolean;
    FGroupChar: string;
    FMenuList: TList;
    FShowGroupChar: Boolean;
    FLastOperateTime: Longword;
    FAutoLockSeconds: Integer;
    FAutoFitSize: Boolean;
    FPersonalMenu: TPersonalMenus;
    //避免只有KeyUp事件造成打开新的界面
    FEnterKeyDown: Boolean;

    { 控制用户登录是否成功变量 2005-4-4}
    FLoginSuccess : Boolean;
    //FCardManage:TCardManage;

    FLocalDate : String;  //用于保存本地时间，用于替换lblocaldate

    FSkinFile : String;  //保存界面
    FExePath:string;

    FUpdateFileName:string;   //要自动更新文件的文件名
    FXmlDoc:TNativeXml;

    procedure ShowMenu(AMenu: TUIMenu; Force: Boolean = False);
    procedure ShowInterface(AMenu: TUIMenuItem);

    function InternalShowUI(const UICode: string): Boolean;

    procedure SetViewStatus(const Value: TViewStatus);
    procedure UpdateWorkArea;
    procedure CloseUI(InstanceRecord: TUIInstanceRecord);
    procedure ReadConfig;
    //function GetHelpFileName(Help: THelpID): string;
    procedure WMStart(var Message: TMessage); message WM_Start;
    procedure ActiveControlChange(Sender: TObject);
    procedure DoCommonAction(const ActionID: TCommonActionID);
    procedure InstallDebugTools;
    procedure DebugToolMenuClick(Sender: TObject);
    procedure UpdateWorkViewStatus;
    procedure DoApplicationIdle(Sender: TObject; var Done: Boolean);
    procedure DoApplicationMessage(var Msg: TMsg; var Handled: Boolean);
    procedure SetRunStatus(const Value: TRunStatus);
    procedure LoadMenus(const CatelogName: string = ''; const
      FavaritesCatelogName: string = '');
    procedure CloseMenus;
    procedure Login;
    procedure Logout;
    procedure LockApp;
    procedure UpdateStatusBar;
    procedure UpdateCommonMenuButton(Sender: TObject);
    procedure UpdateSystemMenuButton(Sender: TObject);
    procedure UpdateDataDict;
    procedure UpdateSystemDate;
    procedure WMGetMinMaxInfo(var Message: TWMGetMinMaxInfo); message
      WM_GETMINMAXINFO;
    procedure InstallMenuCatelogs;
    procedure CatelogMenuClick(Sender: TObject);
    procedure FitSize(W, H: Integer);
    procedure ShowAbout;
    procedure DoHandleException(Sender: TObject; E: Exception);
    procedure AfterLogin;
    procedure BeforeLogout;
    procedure CheckReloadMenu;
    function GetFavoriteMenuRootID(const MainMenuID: string): string;
    procedure PageSwitchTo(GoForward: Boolean);
    procedure ShowWhatFocused;
    procedure RestoreFormSize;
    procedure CreateUI(const ACaption, UICode: string);
    procedure ForceQuit(var message: TMessage); message Msg_ForceQuit;

    function AutoUpdate:Integer;

  protected
    property RunStatus: TRunStatus read FRunStatus write SetRunStatus;
  public
    { Public declarations }
    // IKSModule
    procedure Start;
    procedure ShutDown;
    procedure CloseAllWorkAreas;
    // IKSMainForm
    procedure ShowHelp(const Help: THelpID);
    function NewWorkSpace: IWorkSpace;
    procedure ShowHintFor(Control: TControl; const HintStr: string);
    function ShowUI(const AUICode: TUICode): Boolean;
    procedure SetupPrinter;
    procedure SystemNotify(NotifyCode: Integer);
    function GetInstanceRecordCount: Integer;
    function GetInstanceRecord(Index: Integer): TUIInstanceRecord;
    function GetActiveInstanceRecord: TUIInstanceRecord;

    procedure RecievePushData(RequestType: LongWord; PBody: PTSTPack);
    //实际执行接收推送

    property ViewStatus: TViewStatus read FViewStatus write SetViewStatus;
    property ActiveInstanceRecord: TUIInstanceRecord read
      GetActiveInstanceRecord;
    property StyleIndex: Integer read FStyleIndex;

    procedure ShowGuide;

  end;

var
  fmMain: TfmMain;

implementation

uses LogFile, UContext, UIStyles, KSFrameWorkUtils, 
  SafeCode, KSDataDictionary, KSKeyboard, RPDefines,
  UConfigUserMenu, ExtUtils, KSStrUtils, UUIPlate, UForceQuit, UCommData,
  UStartFlash, UDownLoadProg;

{$R *.DFM}

type
  TWinControlAccess = class(TWinControl);
  TControlAccess = class(TControl);

  { TWorkSpace }

procedure TWorkSpace.FitSize(W, H: Integer);
begin
  fmMain.FitSize(W, H);
end;

procedure TWorkSpace.Release(InstanceRecord: TUIInstanceRecord);
begin
  fmMain.CloseUI(InstanceRecord);
end;

procedure TWorkSpace.UIStatusChanged(InstanceRecord: TUIInstanceRecord);
begin
  TTabSheet(Container).Caption := InstanceRecord.InstanceInterface.GetCaption;
  if fmMain.WorkArea.PageCount = fmMain.FUIInstanceRecords.Count then
    fmMain.UpdateWorkArea;
end;

{ TfmMain }
procedure TfmMain.FormCreate(Sender: TObject);
var
  myfile:TIniFile;
  skinTag:Integer;
begin
  WriteLog('fmMain Created', lcConstruct_Destroy);

  RunStatus := rsCreate;
  Application.Title := SApplicationTitle;
  Caption := SApplicationTitle;
  MainForm := Self;
  FTreeRootFont := TFont.Create;
  FTreeLeaveFont := TFont.Create;
  FWarningFont := TFont.Create;
  //FHTMLBrowser := nil;
  FReady := False;
  FMenuCatalogs := nil;
  FFavorites := nil;
  FUIInstanceRecords := nil;
  FLoginSuccess := False;
  FMenuList := TList.Create;
  lbDropDownOpMenu.Caption := DropDownChar;
  FPersonalMenu := TPersonalMenus.Create;
{$IFDEF Release}
  lbDropDownDebug.Visible := False;
  btnDebug.Visible := False;
  ToolBar.Left := ToolBar.Left + lbDropDownDebug.Width + btnDebug.Width;

  //if Context.GetDebugSystem<>nil then
  Context.GetDebugSystem.DebugDatabase;
  Context.BringToFront;
{$ENDIF}

  //加入初始化界面代码hanjiwei add it 20080331----------------------------------
  myfile := nil;
  try
    try
      appPath := ExtractFilePath(Application.ExeName);
      FExePath:= appPath;
      imgKingstar.Picture.LoadFromFile(FExePath+'../configs/mTitle.jpg');
      myfile := TIniFile.Create(FExePath+'../configs/SetPara.ini');
      maxPer := myfile.ReadInteger('maxlimit','maxlimit',-1);
      showphoto := myfile.ReadInteger('showphoto','showphoto',-1);
      rptTitle := myfile.ReadString('rpttitle','rpttitle','');
      rptOper := myfile.ReadString('rpttitle','rptoper','');
      skinTag := myfile.ReadInteger('skins','skin',0);
      ifDebug := myfile.ReadInteger('debug','ifdebug',0);
      showRpt := myfile.ReadInteger('debug','showrpt',0);
      yktMenu := myfile.ReadString('menu','menu','');
      pasmSeat := myfile.ReadInteger('psamseat','psamseat',-1);
      //useWater := myfile.ReadInteger('water','usewater',0);
      //waterType := myfile.ReadInteger('water','watertype',0);
      {
      waterIfDef := myfile.ReadInteger('water','ifdefault',0);
      waterDefMoney := myfile.ReadFloat('water','defaultmoney',0);
      waterExpiredate := myfile.ReadInteger('water','expiredate',90);
      verIfTip := myfile.ReadInteger('progupdate','iftip',0);
      verHttpPath := myfile.ReadString('progupdate','httppath','');
      buSmlVer := myfile.ReadString('progupdate','busmlver','');
      buCurrVer := myfile.ReadString('progupdate','bucurrver','');
      }
      FSkinFile := FExePath + '../skins/'+inttostr(skinTag)+'.skn';
      SkinData1.SkinFile := FSkinFile;
      if not SkinData1.Active then
        SkinData1.Active := True;
    except
      on e:Exception do
      begin
        ShowMessage('setPara配置文件读取错误，请先修复，然后再使用--'+e.Message);
        Application.Terminate;
      end;
    end;
  //----------------------------------------------------------------------------
  finally
    myfile.Destroy;
    WriteLog('sgykt--Form Create Success',lcConstruct_Destroy);
  end;

end;

procedure TfmMain.FormDestroy(Sender: TObject);
begin
  WriteLog('fmMain Destroying...', lcConstruct_Destroy);
  if RevPushThread <> nil then
  begin
    RevPushThread.Close;
    FreeAndNil(RevPushThread);
  end;

  RunStatus := rsDestroy;
  MainForm := nil;
  fmMain := nil;
  FreeAndNil(FWarningFont);
  FreeAndNil(FTreeRootFont);
  FreeAndNil(FTreeLeaveFont);
  FreeAndNil(FMenuList);
  FreeAndNil(FPersonalMenu);

  WriteLog('fmMain Destroyed', lcConstruct_Destroy);

end;

procedure TfmMain.Start;
var
  ConfigSystem: IConfigSystem;
  tmpi:Integer;
  function ifincludehz(strtxt:string):boolean;
  var
    i:integer;
  begin
    //先判断要截取的字符串最后一个字节的类型
    //如果为汉字的第一个字节则减(加)一位
    result:=false;
    for i:=0 to length(strtxt) do
    begin
      if ByteType(strtxt,i) = mbLeadByte then
      begin
        result:=true;
        break;
      end;
    end;
  end;
begin
  //比较版本信息
  tmpi := AutoUpdate;
  if tmpi<>0 then
  begin
    if tmpi=-5 then
    begin
      //Context.GetDialogSystem.ShowMessage('你要下载最新的程序才能继续使用，点击确定下载！');
      DoDownLoad(FUpdateFileName);
    end;
    Exit;
  end;
  //修改系统日期和时间格式
  //SetLocaleInfo(LOCALE_SLONGDATE,   LOCALE_SDATE,   '-');
  SetLocaleInfo(LOCALE_SYSTEM_DEFAULT,   LOCALE_SSHORTDATE,   'yyyy-MM-dd');
  SetLocaleInfo(LOCALE_SYSTEM_DEFAULT,   LOCALE_SLONGDATE,   'yyyy-MM-dd');

  //SetLocaleInfo(LOCALE_SLONGDATE,   LOCALE_SDATE,   ':');
  SetLocaleInfoa(LOCALE_SYSTEM_DEFAULT, LOCALE_STIMEFORMAT, PChar('HH:mm:ss'));//settime
  FFirst := True;
  WriteLog('Starting Main...', lcKSClientStart);
  RunStatus := rsStart;
  Screen.OnActiveControlChange := ActiveControlChange;
  Application.OnMessage := DoApplicationMessage;
  Application.OnIdle := DoApplicationIdle;
  Application.OnException := DoHandleException;
  // 读取配置
  ReadConfig;

  FUIInstanceRecords := TObjectList.Create;
  FViewStatus := vsMenu;

  WriteLog('yktfore ver： '+yktVersion, lcKSClientStart);

  {
  if ifincludehz(sAppPath)=True then
    Context.GetDialogSystem.ShowMessage('安装目录含有中文，报表部分不能正常使用！');
  }  
  {del it 20090108，加载帮助文件
  WriteLog('Loading HelpIDs', lcKSClientStart);
  FHelpIDs := TStringList.Create;
  try
    FHelpIDs.LoadFromFile(GetFileName(dkHelp, HelpIDsFile));
  except
    WriteException;
  end;
  }
  try
    FStyleIndex := -1;

    //wsn 20050325 当前端口状态 、当前授权状态
    SmartCardPortStatus := False;
    SmartCardAuthStatus := False;
    {
    if FHasHTMLBrowser then
    begin
      FHTMLBrowser := TfaHTMLBrowser.Create(Self);
      //FHTMLBrowser.Align := alClient;
      //FHTMLBrowser.HomePage := GetHelpFileName(HIDIndex);
      //FHTMLBrowser.HandleNeeded;
    end;
    }
    //保存登陆后的IP，Port,FuncNo
    ConfigSystem := Context.GetConfigSystem;
    scIP := ConfigSystem.ReadString(ccServer, ckIP, cdIP);
    scPORT := ConfigSystem.ReadInteger(ccServer, ckPort, cdPort);
    scFUNCNO := ConfigSystem.ReadInteger(ccServer, ckFuncNo, cdFuncNo);

    ksLicence;
    FLoginSuccess := True;
  except
    on e : Exception do
    begin
      ShowMessage(e.Message);
      FLoginSuccess := False;
    end;
  end;
  WriteLog('sgykt--Form Start Success',lcConstruct_Destroy);
end;

procedure TfmMain.ShutDown;
begin
  WriteLog('Shuting down Main...', lcKSClientShutDown);
  RunStatus := rsShutdown;
  Screen.OnActiveControlChange := nil;
  Application.OnMessage := nil;
  Application.OnIdle := nil;
  Application.OnException := nil;
  CloseAllWorkAreas;
  FreeAndNil(FUIInstanceRecords);
  FreeAndNil(FFavorites);
  FreeAndNil(FReferences);
  FreeAndNil(FMenuCatalogs);
  FreeAndNil(FHelpIDs);
  WriteLog('Shut down Main.', lcKSClientShutDown);
end;

procedure TfmMain.btnViewGuideBarClick(Sender: TObject);
begin
  ViewStatus := vsNone;
end;

procedure TfmMain.ShowMenu(AMenu: TUIMenu; Force: Boolean);
var
  //OldMenu : TUIMenu;
  Path: string;
  AParent: TUIMenu;
  I: Integer;
  Item: TUIMenu;
  Stack: TStack;
  Node: TTreeNode;

  function AddTreeNode(TheMenu: TUIMenu; ParentNode: TTreeNode): TTreeNode;
  var
    ACaption: string;
  begin
    if (TheMenu is TUIMenuGroup) and (ParentNode <> nil) then
      ACaption := FGroupChar + TheMenu.Caption
    else
      ACaption := TheMenu.Caption;
    Result := MenuTree.Items.AddChild(ParentNode, ACaption);
    Result.Data := TheMenu;
    if TheMenu = AMenu then
      Result.Selected := True;
    if TheMenu is TUIMenuGroup then
      if ParentNode = nil then
        Result.ImageIndex := RootImageIndex
      else
        Result.ImageIndex := MenuGroupImageIndex
    else
      Result.ImageIndex := MenuItemImageIndex;
    Result.SelectedIndex := Result.ImageIndex;
  end;

  procedure CreateFavorites;
  var
    FavoritesRoot: TTreeNode;
    I: Integer;
  begin
    if FFavorites.Count > 0 then
    begin
      FavoritesRoot := AddTreeNode(FFavorites, nil);
      FavoritesRoot.ImageIndex := RootImageIndex;
      FavoritesRoot.SelectedIndex := RootImageIndex;
      for I := 0 to FFavorites.Count - 1 do
      begin
        AddTreeNode(FFavorites.Items[I], FavoritesRoot);
      end;
    end;
  end;

  procedure CreateReferences;
  var
    ReferencesRoot: TTreeNode;
    I: Integer;
  begin
    FreeAndNil(FReferences);
    FReferences := CreateUIMenuGroupFromIDs('相关功能', AMenu.MetaMenu.See);
    DeleteUnauthParts(FReferences, FMenuAuth);
    if FReferences.Count > 0 then
    begin
      //ReferencesRoot := MenuTree.Items.AddChildObject(nil,FReferences.Caption,FReferences);
      ReferencesRoot := AddTreeNode(FReferences, nil);
      ReferencesRoot.ImageIndex := RootImageIndex;
      ReferencesRoot.SelectedIndex := RootImageIndex;
      for I := 0 to FReferences.Count - 1 do
      begin
        AddTreeNode(FReferences.Items[I], ReferencesRoot);
      end;
    end;
  end;

begin
  Assert((FFavorites <> nil) and (FMenuCatalogs <> nil));
  // 检查不需要的重新构造
  if Force or not ((AMenu = nil) or (FCurrentMenu = AMenu) or (FFavorites =
    AMenu) or (FReferences = AMenu)) then
  begin
    // 构造新的菜单树
    // OldMenu := FCurrentMenu;
    FCurrentMenu := AMenu;
    Stack := nil;
    try
      Stack := TStack.Create;
      MenuTree.Items.BeginUpdate;
      MenuTree.Items.Clear;
      // 产生当前的菜单路径
      Path := AMenu.Caption;
      if AMenu is TUIMenuGroup then
        Stack.Push(AMenu);
      AParent := AMenu.Parent;
      while (AParent <> nil) and (AParent <> FMenuCatalogs.Parent) do
      begin
        Stack.Push(AParent);
        Path := AParent.Caption + Separator + Path;
        AParent := AParent.Parent;
      end;
      if (Stack.Count = 0) or (Stack.Peek <> FMenuCatalogs) then
      begin
        while Stack.Count > 0 do
          Stack.Pop;
        Stack.Push(FMenuCatalogs);
      end
      else
      begin
        //lbPosition.Caption := Path;
      end;
      Item := AMenu;
      // 产生菜单树的树枝
      Node := nil;
      while Stack.Count > 0 do
      begin
        Item := TUIMenu(Stack.Pop);
        if FNestedMenu then
          Node := AddTreeNode(Item, Node)
        else
          Node := AddTreeNode(Item, nil);
      end;
      AParent := Item;

      // 产生菜单树的树叶
      with TUIMenuGroup(AParent) do
      begin
        for I := 0 to Count - 1 do
        begin
          Item := Items[I];
          AddTreeNode(Item, Node);
        end;
      end;

      // 生成相关功能
      if AMenu is TUIMenuItem then
        CreateReferences;

      // 生成常用功能
      CreateFavorites;

      // 展开树状菜单
      Node := MenuTree.Items.GetFirstNode;
      while Node <> nil do
      begin
        Node.Expand(True);
        Node := Node.getNextSibling;
      end;
    finally
      MenuTree.Items.EndUpdate;
      Stack.Free;
    end;

    MenuTree.Selected := MenuTree.Items.GetFirstNode;
    if MenuTree.Selected <> nil then
      MenuTree.Selected.MakeVisible;
  end;

  // 显示操作界面
  if Amenu is TUIMenuItem then
  begin
    ShowInterface(TUIMenuItem(Amenu));
  end;
end;

procedure TfmMain.ShowInterface(AMenu: TUIMenuItem);
begin
  with AMenu do
    CreateUI(Caption, UICode);
end;

procedure TfmMain.CreateUI(const ACaption, UICode: string);
var
  NewInstanceRecord: TUIInstanceRecord;
  Factory: TUIClassFactory;
  ExtInit: Boolean;
begin
  ExtInit := Keyboard.IsDown(VK_CONTROL);
  //CheckUnNeedUI;
  try
    // 检查操作界面的唯一性
    Factory := FindUIClassFactory(UICode);
    if (Factory <> nil) and Factory.GetIsSingleton then
    begin
      // 如果要求唯一性，查找是否已经打开这个操作界面
      if InternalShowUI(UICode) then
        Exit;
    end;
    if FUIInstanceRecords.Count >= FMaxUICount then
    begin
      Context.GetDialogSystem.ShowError(Format('正在使用的操作界面超过最大允许的数量%d,请先关闭其他操作界面', [FMaxUICount]));
      Exit;
    end;
    // 创建新的操作界面
    NewInstanceRecord := CreateUserInterface(UICode);
    if NewInstanceRecord = nil then
      ShowHelp(HIDNotImp)
    else
    begin
      FUIInstanceRecords.Add(NewInstanceRecord);
      if ExtInit then
        NewInstanceRecord.InstanceInterface.InitEx
      else
        NewInstanceRecord.InstanceInterface.Init;
      if ACaption <> '' then
        NewInstanceRecord.InstanceInterface.SetCaption(ACaption);
      {if (NewInstanceRecord.Instance is TWinControl) then
        TWinControlAccess(NewInstanceRecord.Instance).SelectFirst;}
      UpdateWorkArea;

      //创建窗体后加载界面,hanjiwei add it 20080331
      SkinData1.SkinFile := FSkinFile;
      SkinData1.UpdateSkinControl(self);
      if not SkinData1.Active then
        SkinData1.Active := True;

    end;
  except
    on E: Exception do
    begin
      //Dialogs.ShowMessage('Exception:'+E.message);
      WriteException;
      Context.GetExceptionHandler.HandleException(E);
      while FUIInstanceRecords.Count < WorkArea.PageCount do
        WorkArea.Pages[WorkArea.PageCount - 1].Free;
    end;
  end;
end;

procedure TfmMain.btnViewMenuClick(Sender: TObject);
begin
  ViewStatus := vsMenu;
end;

procedure TfmMain.btnViewHelpClick(Sender: TObject);
begin
  ViewStatus := vsHelp;
end;

procedure TfmMain.CloseAllWorkAreas;
begin
  if FUIInstanceRecords <> nil then
    FUIInstanceRecords.Clear;
end;

function TfmMain.NewWorkSpace: IWorkSpace;
var
  Page: TRzTabSheet;
  fmUIPlate: TfmUIPlate;
begin
  if TMainContext(Context).UseFormSpace then
  begin
    fmUIPlate := TfmUIPlate.Create(Self);
    Result := TFormWorkSpace.Create(fmUIPlate, True);
  end
  else
  begin
    Page := TRzTabSheet.Create(Self);
    Page.PageControl := WorkArea;
    WorkArea.ActivePage := Page;
    Result := TWorkSpace.Create(Page, True);
  end;
end;

procedure TfmMain.MenuTreeClick(Sender: TObject);
var
  Obj: TObject;
  Menu: TUIMenu;
  RootMenu: TUIMenuGroup;
  SameMenu: TUIMenu;
begin
  Assert(FMenuCatalogs <> nil);
  if MenuTree.Selected <> nil then
  begin
    Obj := TObject(MenuTree.Selected.Data);
    if Obj is TUIMenu then
    begin
      Menu := TUIMenu(Obj);
      if Menu is TUIMenuItem then
      begin
        // 如果该菜单的根节点不是标准菜单FMenuCatalogs，而是相关菜单或者常用菜单，应该定位到标准菜单的对应菜单上
        RootMenu := TUIMenuGroup(Menu.Parent);
        while (RootMenu <> nil) and (RootMenu <> FMenuCatalogs) do
          RootMenu := TUIMenuGroup(RootMenu.Parent);
        if RootMenu <> FMenuCatalogs then
        begin
          SameMenu := FMenuCatalogs.FindMenuItem(TUIMenuItem(Menu).UICode);
          if SameMenu <> nil then
            Menu := SameMenu;
        end;
      end;
      if (FReferences <> nil) and FReferences.Containes(Menu) then
      begin
        // 如果找到的菜单项目是相关菜单的项目并且不是标准菜单的项目，应该使用CreateUI
        // 如果调用ShowMenu，会产生失败。因为在ShowMenu里面释放了这个对象
        if Menu <> FReferences then
        begin
          CreateUI(Menu.Caption, Menu.UICode);
        end;
      end
      else
      begin
        ShowMenu(Menu);
      end;
    end;
  end;
end;

procedure TfmMain.MenuTreeKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key = #13) or (Key = #10) then
  begin
    Key := #0;
  end;
end;

procedure TfmMain.SetViewStatus(const Value: TViewStatus);
begin
end;

procedure TfmMain.ShowHelp(const Help: THelpID);
begin
  {
  if FHTMLBrowser <> nil then
  begin
    FHTMLBrowser.OpenPage('');
  end
  else
    Context.GetDialogSystem.ShowMessage(SNoOnlineHelp + FNoHTMLHint);
    }
end;

procedure TfmMain.acUseMenuExecute(Sender: TObject);
begin
  ViewStatus := vsMenu;
  if MenuTree.Focused then
  begin
    if ActiveInstanceRecord <> nil then
      TWinControlAccess(ActiveInstanceRecord.Instance).SelectFirst;
  end
  else if MenuTree.CanFocus then
    MenuTree.SetFocus;
end;

function TfmMain.GetActiveInstanceRecord: TUIInstanceRecord;
begin
  if (WorkArea.ActivePageIndex >= 0) and (WorkArea.ActivePageIndex <
    FUIInstanceRecords.Count) then
    Result := TUIInstanceRecord(FUIInstanceRecords[WorkArea.ActivePageIndex])
  else
    Result := nil;
end;

procedure TfmMain.WorkAreaChange(Sender: TObject);
begin
  UpdateWorkArea;
end;

procedure TfmMain.UpdateWorkArea;
begin
  if ActiveInstanceRecord = nil then
  begin
    acCloseWork.Enabled := False;
    acCloseWork.Enabled := False;
    acPrint.Enabled := False;
    acAdjustGrid.Enabled := False;
    acFind.Enabled := False;
    acFocusGrid.Enabled := False;
    acNextFind.Enabled := False;
    acDebugDataset.Enabled := False;
    acDebugWorkView.Enabled := False;
    acDebugUI.Enabled := False;
    acDebugDataSource.Enabled := False;
    acAddCurToPersonalMenu.Enabled := False;
  end
  else
  begin
    //WorkArea.ActivePage.Caption := ActiveInstanceRecord.InstanceInterface.GetCaption;
    acAddCurToPersonalMenu.Enabled := True;
    with ActiveInstanceRecord do
    begin
      acCloseWork.Enabled := InstanceInterface.CanClose;
      acPrint.Enabled := InstanceInterface.CanDoAction(caPrint);
      acAdjustGrid.Enabled := InstanceInterface.CanDoAction(caAdjustGrid);
      acFind.Enabled := InstanceInterface.CanDoAction(caSearchData);
      acNextFind.Enabled := InstanceInterface.CanDoAction(caNextSearchData);
      //wsn 20041013　一卡通所需追加查询
      acSmartFind.Enabled := InstanceInterface.CanDoAction(caSmartSearchData);

      acFocusGrid.Enabled := InstanceInterface.CanDoAction(caFocusGrid);
      acDebugDataset.Enabled := FHaveDebugSystem and
        InstanceInterface.CanDoAction(caDebugDataset);
      acDebugWorkView.Enabled := FHaveDebugSystem and
        InstanceInterface.CanDoAction(caDebugWorkView);
      acDebugUI.Enabled := FHaveDebugSystem and
        InstanceInterface.CanDoAction(caDebugUI);
      acDebugDataSource.Enabled := FHaveDebugSystem and
        InstanceInterface.CanDoAction(caDebugDataSource);

    end;
  end;
end;

procedure TfmMain.CloseUI(InstanceRecord: TUIInstanceRecord);
var
  SavedActiveIndex: Integer;
begin
  if InstanceRecord <> nil then
  begin
    SavedActiveIndex := WorkArea.ActivePageIndex;
    FUIInstanceRecords.Remove(InstanceRecord);
    if SavedActiveIndex >= WorkArea.PageCount then
      SavedActiveIndex := WorkArea.PageCount - 1;
    if SavedActiveIndex >= 0 then
      WorkArea.ActivePageIndex := SavedActiveIndex;
  end;
  UpdateWorkArea;
  WorkArea.Invalidate; // 校正关闭一个操作界面以后，tab的文字没有相应的更新。
end;

procedure TfmMain.acSearchExecute(Sender: TObject);
begin
  CreateUI(SearchCaption, UISearch);
  //UpdateSystemMenuButton(Sender);
end;

procedure TfmMain.acGoGuideHomeExecute(Sender: TObject);
begin
  ShowGuide;
  //UpdateSystemMenuButton(Sender);
end;

function TfmMain.InternalShowUI(const UICode: string): Boolean;
var
  I: Integer;
  InstanceRecord: TUIInstanceRecord;
begin
  for I := 0 to FUIInstanceRecords.Count - 1 do
  begin
    InstanceRecord := TUIInstanceRecord(FUIInstanceRecords[I]);
    if SameText(InstanceRecord.UIClassFactory.UICode, UICode) then
    begin
      Result := True;
      WorkArea.ActivePageIndex := I;
      if InstanceRecord.Instance is TWinControl then
        TWinControlAccess(InstanceRecord.Instance).SelectFirst;
      Exit;
    end;
  end;
  Result := False;
end;

procedure TfmMain.ReadConfig;
var
  ConfigSystem: IConfigSystem;
begin
  ConfigSystem := Context.GetConfigSystem;

  FMaxUICount := ConfigSystem.ReadInteger(ccMain, ckMaxUICount, cdMaxUICount);
  if FMaxUICount < MinMaxUICount then
    FMaxUICount := MinMaxUICount;

  FNestedMenu := ConfigSystem.ReadBoolean(ccMain, ckNestedMenu, cdNestedMenu);

  FShowTutorial := ConfigSystem.ReadBoolean(ccMain, ckShowTutorial,
    cdShowTutorial);
  FConfirmClose := ConfigSystem.ReadBoolean(ccMain, ckConfirmClose,
    cdConfirmClose);

  FShowMenuIcon := ConfigSystem.ReadBoolean(ccMain, ckShowMenuIcon,
    cdShowMenuIcon);
  FShowGroupChar := ConfigSystem.ReadBoolean(ccMain, ckShowGroupChar,
    cdShowGroupChar);
  if not FShowMenuIcon then
  begin
    MenuTree.Images := nil;
    MenuTree.Indent := MenuIdent;
    if FShowGroupChar then
      FGroupChar := MenuGroupChar
    else
      FGroupChar := '';
  end
  else
  begin
    MenuTree.Images := ilTree;
    FGroupChar := '';
  end;

  FAutoLockSeconds := ConfigSystem.ReadInteger(ccMain, ckAutoLockSeconds,
    cdAutoLockSeconds);
  ckAutoLock.Checked := FAutoLockSeconds > 0;
  if FAutoLockSeconds < 0 then
    FAutoLockSeconds := -FAutoLockSeconds;
  if FAutoLockSeconds < MinAutoLogoutSeconds then
    FAutoLockSeconds := MinAutoLogoutSeconds;

  FAutoFitSize := ConfigSystem.ReadBoolean(ccMain, ckAutoFitSize,
    cdAutoFitSize);

  //FHasHTMLBrowser := not FindCmdLineSwitch(NoHTMLSwitch,['-','/'],True);
  {
  FHasHTMLBrowser := ConfigSystem.ReadBoolean(ccRunEnvir, ckHTML, True);
  if not FHasHTMLBrowser then
    FNoHTMLHint := ConfigSystem.ReadString(ccRunEnvir, ckNoHTMLHint, '');
  }
  //wsn 20050106 读入一卡通数据
  SmartCardSubSystemNo :=
    ConfigSystem.ReadInteger(SmartCardSubSystemCata, SmartCardSubSystemName,
    SmartCardSubSystemNo);
end;

procedure TfmMain.acCloseWorkExecute(Sender: TObject);
var
  Cur: TUIInstanceRecord;
begin
  if Keyboard.IsDown(VK_MENU) then
    CloseAllWorkAreas
  else
  begin
    Cur := ActiveInstanceRecord;
    if (Cur <> nil) and (not FConfirmClose
      or (Context.GetDialogSystem.Confirm(Format('关闭%s?',
      [Cur.InstanceInterface.GetCaption])) = uaYes)) then
      CloseUI(Cur);
  end;
end;
{hanjiwei delete it 20080821
function TfmMain.GetHelpFileName(Help: THelpID): string;
var
  HelpFile: string;
begin
  HelpFile := FHelpIDs.Values[Help];
  if Trim(HelpFile) = '' then
    HelpFile := Help + '.htm';
  Result := GetFileName(dkHelp, HelpFile);
end;
}
procedure TfmMain.FormActivate(Sender: TObject);
begin
  if FFirst then
  begin
    FFirst := False;
    RunStatus := rsFirstShow;
    PostMessage(Handle, WM_Start, 0, 0);
    RestoreFormSize;
  end;
end;

procedure TfmMain.acLogoutExecute(Sender: TObject);
begin
  if Context.GetDialogSystem.Confirm('注销登录？') = uaYes then
  begin
    Logout;
    Login;
  end;
end;

procedure TfmMain.WMStart(var Message: TMessage);
begin
  Assert(RunStatus = rsFirstShow);
  // add by 汤成 2005-4-4
  if not  FLoginSuccess then
  begin
    Close;
    Exit;
  end;
  {
  try
    if FShowTutorial and FHasHTMLBrowser then
      ExecuteTutorial;
  except
  
  end;}
  RunStatus := rsWaitInit;
  try
    dmContext.DoLogin; // 不能调用 Login,因为没有判断dmContext.WaitForInit;
  finally
    if not FReady and not dmContext.Terminated then
    begin
      //20090804hanjiwei注释掉，在创建窗体后加载改部分
      //if dmContext <> nil then
        //dmContext.WaitForInit;
      FReady := True;
      RunStatus := rsRun;
      // 个人菜单
      InstallMenuCatelogs;
      InstallDebugTools;
      AfterLogin;
    end;
  end;
end;

procedure TfmMain.acSetPrinterExecute(Sender: TObject);
begin
  SetupPrinter;
  UpdateSystemMenuButton(Sender);
end;

procedure TfmMain.acPrintExecute(Sender: TObject);
begin
  DoCommonAction(caPrint);
  UpdateCommonMenuButton(Sender);
end;

procedure TfmMain.acAdjustGridExecute(Sender: TObject);
begin
  DoCommonAction(caAdjustGrid);
  UpdateCommonMenuButton(Sender);
end;

procedure TfmMain.acFindExecute(Sender: TObject);
begin
  DoCommonAction(caSearchData);
  UpdateCommonMenuButton(Sender);
end;

procedure TfmMain.acNextFindExecute(Sender: TObject);
begin
  DoCommonAction(caNextSearchData);
  UpdateCommonMenuButton(Sender);
end;

procedure TfmMain.alCommonUpdate(Action: TBasicAction;
  var Handled: Boolean);
begin
  Handled := True;
  FHaveDebugSystem := Context.GetDebugSystem <> nil;
  UpdateWorkArea;
  acDebugDatabase.Enabled := FHaveDebugSystem;
  acShowLog.Enabled := FHaveDebugSystem;
end;

procedure TfmMain.acMinExecute(Sender: TObject);
begin
  Application.Minimize;
end;

procedure TfmMain.acExitExecute(Sender: TObject);
begin
  Close;
end;

procedure TfmMain.ActiveControlChange(Sender: TObject);
begin
  UpdateWorkViewStatus;
end;

procedure TfmMain.DoCommonAction(const ActionID: TCommonActionID);
begin
  if (ActiveInstanceRecord <> nil) then
    with ActiveInstanceRecord do
      if InstanceInterface.CanDoAction(ActionID) then
        InstanceInterface.DoAction(ActionID);
end;

procedure TfmMain.acDebugDatasetExecute(Sender: TObject);
begin
  DoCommonAction(caDebugDataset);
end;

procedure TfmMain.acDebugWorkViewExecute(Sender: TObject);
begin
  DoCommonAction(caDebugWorkView);
end;

procedure TfmMain.acDebugUIExecute(Sender: TObject);
begin
  DoCommonAction(caDebugUI);
end;

procedure TfmMain.acDebugDataSourceExecute(Sender: TObject);
begin
  DoCommonAction(caDebugDataSource);
end;

procedure TfmMain.acDebugDatabaseExecute(Sender: TObject);
begin
  if Context.GetDebugSystem <> nil then
    Context.GetDebugSystem.DebugDatabase;
end;

procedure TfmMain.acShowLogExecute(Sender: TObject);
begin
  if Context.GetDebugSystem <> nil then
    Context.GetDebugSystem.ShowLog;
end;

procedure TfmMain.InstallDebugTools;
var
  Names: TStringList;
  DebugSystem: IDebugSystem;
  I: Integer;
  MenuItem: TMenuItem;
begin
  DebugSystem := Context.GetDebugSystem;
  if DebugSystem <> nil then
  begin
    Names := TStringList.Create;
    try
      DebugSystem.GetDebugToolNames(Names);
      for I := 0 to Names.Count - 1 do
      begin
        MenuItem := TMenuItem.Create(Self);
        MenuItem.Caption := Names[I];
        MenuItem.Hint := Names[I];
        MenuItem.OnClick := DebugToolMenuClick;
        mnDebug.Items.Add(MenuItem);
      end;
    finally
      Names.Free;
    end;
  end;
end;

procedure TfmMain.DebugToolMenuClick(Sender: TObject);
var
  DebugSystem: IDebugSystem;
  MenuItem: TMenuItem;
begin
  DebugSystem := Context.GetDebugSystem;
  if DebugSystem <> nil then
  begin
    MenuItem := TMenuItem(Sender);
    DebugSystem.ExecuteDebugTool(ActiveInstanceRecord, MenuItem.Hint);
  end;
end;

procedure TfmMain.WorkViewCenterException(Sender: TObject; E: Exception);
begin
  if Context <> nil then
    Context.GetExceptionHandler.HandleException2(Sender, E);
end;

procedure TfmMain.WorkViewCenterInvalidInput(WorkField: TWVField;
  Target: TObject);
var
  HintStr: string;
  FieldHint: string;
begin
  if Target is TControl then
  begin
    if WorkField.ErrorMessage <> '' then
      HintStr := Format(SFullFieldError, [WorkField.Caption,
        WorkField.ErrorMessage])
    else
      HintStr := Format(SSimpleFieldError, [WorkField.Caption]);
    FieldHint := Trim(WorkField.GetHint);
    if FieldHint <> '' then
      HintStr := Format(SFieldErrorFormat, [HintStr, FieldHint]);
    HintMan.ShowHintFor(TControl(Target), HintStr);
  end;
end;

procedure TfmMain.UpdateWorkViewStatus;
var
  WorkView: TWorkView;
  InvalidFields: string;
begin
  if Screen.ActiveControl <> nil then
  begin
    StatusBar.Panels[HintPanelIndex].Text := Screen.ActiveControl.Hint;
    WorkView := FindAssociatedWorkView(Screen.ActiveControl);
    if WorkView <> nil then
    begin
      InvalidFields := WorkView.GetInvalidFieldCaptions;
      if InvalidFields <> '' then
        InvalidFields := {'未正确输入:'+} InvalidFields;
      StatusBar.Panels[InvalidFieldsPanelIndex].Text := InvalidFields;
    end
    else
      StatusBar.Panels[InvalidFieldsPanelIndex].Text := '';
  end
  else
  begin
    StatusBar.Panels[HintPanelIndex].Text := '';
    StatusBar.Panels[InvalidFieldsPanelIndex].Text := '';
  end;
end;

procedure TfmMain.DoApplicationIdle(Sender: TObject; var Done: Boolean);
begin
  Done := True;
  UpdateWorkViewStatus;
end;

procedure TfmMain.ShowHintFor(Control: TControl; const HintStr: string);
begin
  HintMan.ShowHintFor(Control, HintStr);
end;

procedure TfmMain.SetRunStatus(const Value: TRunStatus);
var
  Running: Boolean;
begin
  FRunStatus := Value;
  Running := RunStatus = rsRun;
  //GuideBar.Enabled := Running;
  Timer.Enabled := Running;
  WorkArea.Visible := RunStatus = rsRun;//rsLocked;
  MenuTree.Visible := RunStatus = rsRun;//rsLocked;
  spnlTree.Visible := RunStatus = rsRun;//rsLocked;
end;

procedure TfmMain.LoadMenus(const CatelogName: string = ''; const
  FavaritesCatelogName: string = '');
var
  ARoot: TUIMenuGroup;
begin
  CheckObject(MenuAdmin.Root, SMenuError);
  CheckTrue(MenuAdmin.Root.Count > 0, SMenuError);
  // 取得操作员权限
  FMenuAuth := Context.GetParamValue(svOperatorMenuAuthName);
  // 生成菜单
  FreeAndNil(FMenuCatalogs);
  if CatelogName <> '' then
    if CatelogName = UserMenuRootID then
      ARoot := FPersonalMenu.PersonalMenus
    else
      ARoot := MenuAdmin.Root.FindMenuGroup(CatelogName)
  else
    ARoot := nil;
  if (ARoot = nil) then
  begin
    if IsCenterDepartment then
      ARoot := MenuAdmin.Root.FindMenuGroup(CenterMenuRootID)
    else
      ARoot := MenuAdmin.Root.FindMenuGroup(DepartMenuRootID);
  end;
  CheckObject(ARoot, SMenuError);
  FMenuCatalogs := ARoot.Clone(nil);
  // 删除没有权限的菜单功能
  DeleteUnauthParts(FMenuCatalogs, FMenuAuth);
  // 增加个人的 Favorites 菜单
  FreeAndNil(FFavorites);
  if FavaritesCatelogName <> '' then
    ARoot := MenuAdmin.Root.FindMenuGroup(FavaritesCatelogName)
  else
    ARoot := nil;
  if (ARoot = nil) then
  begin
    if IsCenterDepartment then
      ARoot := MenuAdmin.Root.FindMenuGroup(CenterFavoritesMenuRootID)
    else
      ARoot := MenuAdmin.Root.FindMenuGroup(DepartFavoritesMenuRootID);
  end;
  CheckObject(ARoot, SMenuError);
  FFavorites := ARoot.Clone(nil);
  // 同样删除没有权限的菜单项
  DeleteUnauthParts(FFavorites, FMenuAuth);
  // 显示菜单
  MenuAdmin.MenuList.GetAuthedItems(FMenuAuth, FMenuList);
  MenuCaptionSpell.FilterList(True);
  ShowMenu(FMenuCatalogs, True);
end;

procedure TfmMain.Login;
begin
  UpdateStatusBar;
  dmContext.DoLogin;
  AfterLogin;
  Timer.Enabled := True;
end;

function TfmMain.ShowUI(const AUICode: TUICode): Boolean;
var
  UIMenu: TUIMenu;
begin
  Result := False;
  if FMenuCatalogs <> nil then
  begin
    UIMenu := FMenuCatalogs.FindMenuItem(AUICode);
    if UIMenu <> nil then
    begin
      ShowMenu(UIMenu);
      Result := True;
    end;
  end;
end;

procedure TfmMain.CloseMenus;
begin
  MenuTree.Items.Clear;
  FreeAndNil(FMenuCatalogs);
  FreeAndNil(FFavorites);
  FreeAndNil(FReferences);
end;

procedure TfmMain.UpdateStatusBar;
begin
  if OperatorPanelIndex >= 0 then
  begin
    if Context.GetParamValue(svOperatorNoName) <> DefaultSystemOperatorNO then
    begin
      StatusBar.Panels[OperatorPanelIndex].Text := Format('%s-%s',
        [Context.ParamData(svOperatorNoName).AsString,
        Context.ParamData(svOperatorNameName).AsString]);
    end
    else
    begin
      StatusBar.Panels[OperatorPanelIndex].Text := '';
    end;
  end;
end;

procedure TfmMain.Splitter1CanResize(Sender: TObject; var NewSize: Integer;
  var Accept: Boolean);
begin
  if NewSize < MinGuideWidth then
    NewSize := MinGuideWidth;
end;

procedure TfmMain.MenuCaptionSpellFilterItems(Sender: TObject);
const
  MaxSpellLength = 10;
var
  I, Len: Integer;
  S: string;
  MetaMenu: TKSMetaMenu;
  ACaption: string;
begin
  //if MenuCaptionSpell.Text='' then
  if FMenuList = nil then
    Exit;
  S := MenuCaptionSpell.Text;
  Len := Length(S);
  try
    MenuCaptionSpell.Items.BeginUpdate;
    MenuCaptionSpell.Items.Clear;
    for I := 0 to FMenuList.Count - 1 do
    begin
      MetaMenu := TKSMetaMenu(FMenuList[I]);
      //if not MetaMenu.VirtualMenu then
      if (Len = 0) or (Pos(S, MetaMenu.CaptionSpell) > 0) then
      begin
        ACaption := Copy(MetaMenu.CaptionSpell + StringOfChar(' ',
          MaxSpellLength), 1, MaxSpellLength) +
          MetaMenu.Caption;
        MenuCaptionSpell.Items.AddObject(ACaption, MetaMenu);
      end;
    end;
  finally
    MenuCaptionSpell.Items.EndUpdate;
  end;
  MenuCaptionSpell.ItemIndex := 0;
end;

procedure TfmMain.MenuCaptionSpellGetSelectedText(
  Sender: TKSCustomFilterComboBox; var AText: string);
begin
  AText := '';
end;

procedure TfmMain.MenuCaptionSpellSelected(Sender: TObject);
var
  MetaMenu: TKSMetaMenu;
  MenuItem: TUIMenu;
begin
  if MenuCaptionSpell.ItemIndex >= 0 then
  begin
    MetaMenu :=
      TKSMetaMenu(MenuCaptionSpell.Items.Objects[MenuCaptionSpell.ItemIndex]);
    MenuItem := FMenuCatalogs.FindMenuItem(MetaMenu.ID);
    if MenuItem <> nil then
      ShowMenu(MenuItem)
    else
      CreateUI(MetaMenu.Caption, MetaMenu.ID);
  end;
end;

procedure TfmMain.acSearchMenuBySpellExecute(Sender: TObject);
begin
  if MenuCaptionSpell.CanFocus then
  begin
    MenuCaptionSpell.SetFocus;
  end;
end;

procedure TfmMain.UpdateCommonMenuButton(Sender: TObject);
begin
  {
  if Sender is TAction then
  begin
    UpdateWorkArea;
    if (Sender = acFind) and acNextFind.Enabled then
      btnCommonMenu.Action := acNextFind
    else if (Sender = acNextFind) and not acNextFind.Enabled then
      btnCommonMenu.Action := acFind
    else
      btnCommonMenu.Action := TAction(Sender);
  end; }
end;

procedure TfmMain.UpdateSystemMenuButton(Sender: TObject);
begin  {
  if Sender is TAction then
  begin
    btnSystemMenu.Action := TAction(Sender);
  end;   }
end;

procedure TfmMain.acRestoreExecute(Sender: TObject);
begin
  CloseAllWorkAreas;
  ViewStatus := vsMenu;
  RestoreFormSize;
  acGoGuideHome.Execute;
end;

procedure TfmMain.acUpdateDataDictExecute(Sender: TObject);
begin
  UpdateDataDict;
end;

procedure TfmMain.UpdateDataDict;
var
  I: Integer;
begin
  CloseAllWorkAreas;
  FreeIdObjects(deDictionaryCategory);
  FreeIdObjects(deBusinessFlag);
  for I := -100 to 4000 do
    FreeIdObjects(I);
end;

procedure TfmMain.DropDownMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
var
  P: TPoint;
begin
  if (Sender is TControl) and (TControlAccess(Sender).PopupMenu <> nil) then
  begin
    P := Point(20, TControl(Sender).Height);
    P := TControl(Sender).ClientToScreen(P);
    TControlAccess(Sender).PopupMenu.Popup(P.X, P.Y);
  end;
end;

procedure TfmMain.TimerTimer(Sender: TObject);
var
  TheTime: Integer;
begin
  //ShowMessage(IntToStr(FLastOperateTime));
  if ckAutoLock.Checked  and
    (FAutoLockSeconds > 0) and
    (FLastOperateTime > 0) and
    Context.GetLogined and
    (RunStatus = rsRun)
      then
  begin
    //ShowMessage(IntToStr(FAutoLockSeconds));
    TheTime := (GetTickCount - FLastOperateTime) div 1000;
    if TheTime > FAutoLockSeconds then
    begin
      LockApp;
    end
    else
    begin
      ckAutoLock.Caption := Format(AutoLockFormat, [FAutoLockSeconds - TheTime]);
    end;
  end;
end;

procedure TfmMain.Logout;
  var
  tempRe: smallint;
  //CardManage: TCardManage;
begin
  Timer.Enabled := False;
  BeforeLogout;
  dmContext.DoLogout;
  RunStatus := rsLocked;
  {
  try
  //关闭打开的串口
  CardManage := nil;
  try
    CardManage := TCardManage.Create;
    tempRe := CardManage.CloseSerialPort;
  finally
    if tempRe = 0 then
      SmartCardPortStatus := False;
    CardManage.Destroy;
  end;
  except
  end;
  }
end;

procedure TfmMain.DoApplicationMessage(var Msg: TMsg;
  var Handled: Boolean);
begin

  Handled := False;
  if ((Msg.Message >= WM_KEYFIRST) and (Msg.Message <= WM_KEYLAST)) or
    ((Msg.Message >= WM_MOUSEFIRST) and (Msg.Message <= WM_MOUSELAST)) then
  begin
    FLastOperateTime := GetTickCount;
  end;
  HintMan.DoApplicationMessage(Msg, Handled);
end;

procedure TfmMain.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
  if not FLoginSuccess then
  begin
    CanClose := True;
    Exit;
  end;
  
  CanClose := Context.GetDialogSystem.Confirm('退出程序？') = uaYes;
  if CanClose then
  begin
    if Context.GetLogined then
      Logout;
  end;
end;

procedure TfmMain.MenuTreeKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (key = VK_RETURN) and FEnterKeyDown then
  begin
    FEnterKeyDown := False;
    MenuTreeClick(Sender);
    MenuTree.FullExpand;
    Key := 0;
  end;
end;

procedure TfmMain.LockApp;
begin
  RunStatus := rsLocked;
  dmContext.DoLock;
  RunStatus := rsRun;
end;

procedure TfmMain.acLockAppExecute(Sender: TObject);
begin
  UpdateSystemMenuButton(Sender);
  LockApp;
end;

procedure TfmMain.UpdateSystemDate;
var
  SysDate: string;
  LocalDate: string;
begin
  SysDate := GetSystemDateStr;
  //accountDate := dmContext.FSystemDate;
  LocalDate := FormatDateTime(NormalDateTimeFormat, Now);
  lbSystemDate.Caption := Format(SSyetemDateFormat, [SysDate]);
  FLocalDate := FormatDateTime(SLocalDateFormat, Now);
  if Trim(SysDate) <> Trim(FormatDBStrDate(FullDateFormat, LocalDate)) then
  begin

    Context.GetDialogSystem.ShowWarning(
      Format('系统业务日期和您的电脑日期不相同，'#13#10 +
      '可能是您的电脑日期设置不正确，'#13#10 +
      '也可能是系统工作在一个特殊状态。'#13#10'%s'#13#10'%s',
      [lbSystemDate.Caption, FLocalDate]));
  end;
end;

procedure TfmMain.WMGetMinMaxInfo(var Message: TWMGetMinMaxInfo);
var
  R: TRect;
begin
  inherited;
  SystemParametersInfo(SPI_GETWORKAREA, 0, @R, 0);
  with Message.MinMaxInfo^ do
  begin
    ptMaxTrackSize.X := R.Right - R.Left;
    ptMaxTrackSize.Y := R.Bottom - R.Top;
    ptMaxSize.X := ptMaxTrackSize.X;
    ptMaxSize.Y := ptMaxTrackSize.Y;
  end;
end;

procedure TfmMain.SetupPrinter;
begin
  if PrinterSetupDialog.Execute then
  begin
    SystemNotify(snPrinterChanged);
  end;
end;

procedure TfmMain.SystemNotify(NotifyCode: Integer);
var
  I: Integer;
  Count: Integer;
begin
  // 处理部分通知
  case NotifyCode of
    snDateUpdated: lbSystemDate.Caption := Format(SSyetemDateFormat,
        [GetSystemDate]);
  end;
  // 将通知发送给所有的界面
  Count := GetInstanceRecordCount;
  for I := 0 to Count - 1 do
  begin
    GetInstanceRecord(I).InstanceInterface.SystemNotify(NotifyCode);
  end;
end;

function TfmMain.GetInstanceRecord(Index: Integer): TUIInstanceRecord;
begin
  Result := TUIInstanceRecord(FUIInstanceRecords[Index]);
end;

function TfmMain.GetInstanceRecordCount: Integer;
begin
  Result := FUIInstanceRecords.Count;
end;

//初始化用户菜单
procedure TfmMain.InstallMenuCatelogs;
var
  I: Integer;
  UIMenu: TUIMenu;
  NeedFilterCenterMenus: Boolean;

  function AddMenu(UIMenu: TUIMenu): TMenuItem;
  var
    MenuItem: TMenuItem;
  begin
    MenuItem := TMenuItem.Create(Self);
    MenuItem.Caption := UIMenu.Caption;
    MenuItem.Tag := Integer(UIMenu);
    MenuItem.OnClick := CatelogMenuClick;
    mnCatelogMenus.Items.Add(MenuItem);
    Result := MenuItem;
  end;
begin
  CheckObject(MenuAdmin.Root, SMenuError);
  NeedFilterCenterMenus := not IsCenterDepartment;
  for I := 0 to MenuAdmin.Root.Count - 1 do
  begin
    UIMenu := MenuAdmin.Root.Items[I];
    {
     判断条件：
     1.必须是 TUIMenuGroup
     2.不能是‘常用’
     3.如果没有设置过滤‘总部’，就加入。否则要过滤
     4.必须不是VirtualMenu
    }
    if (UIMenu is TUIMenuGroup) and
      (Pos(FavoritesIDPart, UIMenu.UICode) <= 0) and
      (not NeedFilterCenterMenus or (Pos(CenterRootIDPart, UIMenu.UICode) <= 0))
      and
      not UIMenu.MetaMenu.VirtualMenu then
    begin
      // 增加到个人菜单
      AddMenu(UIMenu);
    end;
  end;
  AddMenu(FPersonalMenu.PersonalMenus).MenuIndex := 0;
end;

procedure TfmMain.CatelogMenuClick(Sender: TObject);
var
  UIMenu: TUIMenu;
  UICode: string;
  Favarites: string;
begin
  Assert(Sender is TMenuItem);
  ViewStatus := vsMenu;
  UIMenu := TUIMenu(TMenuItem(Sender).Tag);
  UICode := UIMenu.UICode;
  Favarites := GetFavoriteMenuRootID(UICode);
  LoadMenus(UICode, Favarites);
  Context.GetConfigSystem.WriteString(
    ccUser,
    ckRoot,
    UICode);
end;

procedure TfmMain.FitSize(W, H: Integer);
begin
end;

procedure TfmMain.ShowAbout;
begin
  if Context.GetCopyRight <> nil then
    Context.GetCopyRight.ShowAbout;
end;

procedure TfmMain.RPGlobeAfterPrint(Sender: TObject);
begin
  if not (TCustomReportProcessor(Sender).ReportStatus
    in [rsRunning, rsDone]) then
    Context.GetDialogSystem.ShowMessage(SReportCancelled);
end;

procedure TfmMain.DoHandleException(Sender: TObject; E: Exception);
begin
  if Context <> nil then
    Context.GetExceptionHandler.HandleException(E);
end;

procedure TfmMain.acFocusGridExecute(Sender: TObject);
begin
  DoCommonAction(caFocusGrid);
end;

procedure TfmMain.AfterLogin;
var
  UICode: string;
begin
  //wlj 20040331 显示公司名称 ,如果配置文件中的值和数据库的值不同，则更新配置文件
  lbDepartmentName.caption := Context.ParamData(svCompanyNameName).AsString;
  if Context.ParamData(svCompanyNameName).AsString <> GetIdObjectName(1000,'FullName') then
    Context.GetConfigSystem.WriteString(ccDepartment, ckCompanyName,
      GetIdObjectName(1000, 'FullName'));

  UpdateSystemDate;
  UpdateStatusBar;
  FPersonalMenu.AfterLogin;
  UICode := Context.GetConfigSystem.ReadString(
    ccUser,
    ckRoot,
    cdRoot);
  // 加载菜单
  LoadMenus(UICode, GetFavoriteMenuRootID(UICode));

  RevPushThread :=
    TPushRevThread.Create(StrToInt(Context.ParamData(svBatchNoName).AsString),
    Context.GetConfigSystem.ReadString(ccServer, 'IP', ''),
    StrToInt(Context.GetConfigSystem.ReadString(ccServer, 'Port', '')),
    StrToInt(Context.ParamData(svFuncNoName).AsString));
  RevPushThread.Open;
  RunStatus := rsRun;
  //打开首页面
  ShowGuide;
end;

procedure TfmMain.BeforeLogout;
begin
  CloseAllWorkAreas;
  CloseMenus;
  FPersonalMenu.BeforeLogout;
end;

procedure TfmMain.acAddCurToPersonalMenuExecute(Sender: TObject);
var
  UICode: TUICode;
begin
  if ActiveInstanceRecord <> nil then
  begin
    UICode := ActiveInstanceRecord.UIClassFactory.UICode;
    if FPersonalMenu.AddMenu(UICode) then
      CheckReloadMenu;
  end;
end;

procedure TfmMain.CheckReloadMenu;
begin
  if (FMenuCatalogs <> nil) and (FMenuCatalogs.UICode = UserMenuRootID) then
    LoadMenus(UserMenuRootID, EmptyFavoritesMenuRootID);
end;

procedure TfmMain.acManagePersonalMenuExecute(Sender: TObject);
begin
  if ManagePersonMenu(FPersonalMenu.PersonalMenuIDs) then
    CheckReloadMenu;
end;

function TfmMain.GetFavoriteMenuRootID(const MainMenuID: string): string;
begin
  if (MainMenuID = DepartMenuRootID) or (MainMenuID = CenterMenuRootID) or
    (MainMenuID = '') then
    Result := ''
  else
    Result := EmptyFavoritesMenuRootID;
end;

procedure TfmMain.MenuTreeKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_RETURN then
    FEnterKeyDown := True;
end;

procedure TfmMain.acPrevPageExecute(Sender: TObject);
begin
  PageSwitchTo(False);
end;

procedure TfmMain.acNextPageExecute(Sender: TObject);
begin
  PageSwitchTo(True);
end;

procedure TfmMain.PageSwitchTo(GoForward: Boolean);
var
  Ctrl: TWinControl;
  PageControl: TRzPageControl;

  procedure SwitchPage(PageControl: TRzPageControl; Delta: Integer);
  var
    NewIndex: Integer;
    Count: Integer;
  begin
    NewIndex := PageControl.ActivePageIndex + Delta;
    Count := PageControl.PageCount;
    while (NewIndex >= 0) and (NewIndex < Count) do
    begin
      if PageControl.Pages[NewIndex].Enabled then
      begin
        PageControl.ActivePageIndex := NewIndex;
        Break;
      end;
      NewIndex := NewIndex + Delta;
    end;
  end;

begin
  PageControl := nil;
  Ctrl := ActiveControl;
  while Ctrl <> nil do
  begin
    if Ctrl is TPageControl then
    begin
      PageControl := TRzPageControl(Ctrl);
      Break;
    end;
    Ctrl := Ctrl.Parent;
  end;
  if PageControl = WorkArea then
    PageControl := nil;
  if PageControl <> nil then
    if GoForward then
      SwitchPage(PageControl, 1)
    else
      SwitchPage(PageControl, -1);
end;

procedure TfmMain.acBrowseLocalDirExecute(Sender: TObject);
begin
  OpenFolder(Context.GetDir(dkLocalBase));
end;

procedure TfmMain.PositionBarDblClick(Sender: TObject);
begin
  ShowWhatFocused;
end;

procedure TfmMain.acWhatFocusedExecute(Sender: TObject);
begin
  ShowWhatFocused;
end;

procedure TfmMain.ShowWhatFocused;
var
  Ctrl: TWinControl;
  Path: string;
begin
  Ctrl := Screen.ActiveControl;
  Path := '';
  while Ctrl <> nil do
  begin
    Path := Format('%s.%s', [Ctrl.Name, Path]);
    Ctrl := Ctrl.Parent;
  end;
  ShowMessage(Path);
end;

procedure TfmMain.RestoreFormSize;
var
  R: TRect;
begin
  SystemParametersInfo(SPI_GETWORKAREA, 0, @R, 0);
  SetBounds(R.Left, R.Top, R.Right - R.Left, R.Bottom - R.Top);
end;

procedure TfmMain.acClearLogExecute(Sender: TObject);
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

procedure TfmMain.ForceQuit(var message: TMessage);
begin
  ForceSystemQuit(PChar(message.LParam));
  Logout;
  Application.Terminate;
end;

procedure TfmMain.RecievePushData(RequestType: LongWord; PBody: PTSTPack);
var
  tempStr: string;
begin
  case RequestType of
    Exe_force_login_logout:
      begin
        tempStr := PBody^.scust_no;
        tempStr := tempStr + ',' + PBody^.vsvarstr0;
        SendMessage(Self.Handle, Msg_ForceQuit, 0, Integer(PChar(tempStr)));
      end;
{$IFDEF Debug}
  else
    WriteLog(Format('收到推送（%d），未处理！', [RequestType]), lcException);
{$ENDIF}
  end;
end;

procedure TfmMain.ShowGuide;
begin
  {
  if FHasHTMLBrowser then
  begin
    WriteLog('Guide =' + GuideCaption, lcKSClient);
    CreateUI(GuideCaption, UIGuide);
  end
  else
    Context.GetDialogSystem.ShowMessage(SNoGuide + FNoHTMLHint);
  }
  CreateUI('欢迎页面', '欢迎页面');
end;

function TfmMain.AutoUpdate: Integer;
var
  MyStream:TMemoryStream;
  verFileName:string;
  myfile:TIniFile;
  verHttpPath:string;
  ifcheck:Integer;
  useProxy,proxyPort:Integer;
  proxyServer,proxyUser,proxyPwd:string;
begin
  Result := 0;
  verFileName := sAppPath+'updatever.xml';
  myfile := nil;
  if FileExists(verFileName) then
    DeleteFile(verFileName);
  try
    try
      myfile := TIniFile.Create(FExePath+'../configs/update.ini');
      verHttpPath := myfile.ReadString('progupdate','httppath','');
      ifcheck := myfile.ReadInteger('progupdate','ifcheck',-1);
      useProxy := myfile.ReadInteger('progupdate','useproxy',0);
      proxyServer := myfile.ReadString('progupdate','proxyserver','');
      proxyPort := myfile.ReadInteger('progupdate','proxyport',0);
      proxyUser := myfile.ReadString('progupdate','proxyuser','');
      proxyPwd := myfile.ReadString('progupdate','proxypwd','');
    except
      on e:exception do
      begin
        Context.GetDialogSystem.Showmessage('配置文件读取错误,不能完成版本检测--'+e.Message);
        Result := -1;
        Exit;
      end;
    end;
    if ifcheck=0 then
    begin
      Result := 0;
      Exit;
    end;
    if useProxy=1 then
    begin
      idhtp1.ProxyParams.ProxyServer := proxyServer;
      idhtp1.ProxyParams.ProxyPort := proxyPort;
      idhtp1.ProxyParams.ProxyUsername := proxyUser;
      idhtp1.ProxyParams.ProxyPassword := proxyPwd;
    end
    else
    begin
      idhtp1.ProxyParams.ProxyServer := '';
      idhtp1.ProxyParams.ProxyPort := 0;
      idhtp1.ProxyParams.ProxyUsername := '';
      idhtp1.ProxyParams.ProxyPassword := '';
    end;
    try
      MyStream:=TMemoryStream.Create;
      idhtp1.Get(verHttpPath+'updatever.xml',MyStream);
    except
      on e:exception do
      begin
        Context.GetDialogSystem.Showmessage('更新版本信息失败，不能完成版本检测--'+e.Message);
        Result := -2;
        Exit;
      end;
    end;
    MyStream.SaveToFile(verFileName);
    try
      FXmlDoc:= TNativeXml.Create;
      FXmlDoc.XmlFormat:=xfReadable;
      FXmlDoc.LoadFromFile(verFileName);
      FUpdateFileName := sdUtf8ToAnsi(FXmlDoc.Root.findnode('/update/forever').ValueAsString);
    except
      on e:exception do
      begin
        Context.GetDialogSystem.Showmessage('取版本信息失败，不能完成版本检测--'+e.Message);
        Result := -3;
        Exit;
      end;
    end;
    if Trim(FUpdateFileName)<>Trim(yktVersion) then
      Result := -5
    else
      Result := 0;
  finally
    MyStream.Free;
    myfile.Free;
  end;

end;

{ TFormWorkSpace }

procedure TFormWorkSpace.FitSize(W, H: Integer);
var
  fmUIPlate: TfmUIPlate;
begin
  fmUIPlate := TfmUIPlate(Container);
  fmUIPlate.ClientWidth := W;
  fmUIPlate.ClientHeight := H;
end;

procedure TFormWorkSpace.Release(InstanceRecord: TUIInstanceRecord);
begin
  (InstanceRecord.WorkSpace.GetContainer as TForm).Close;
end;

procedure TFormWorkSpace.UIStatusChanged(
  InstanceRecord: TUIInstanceRecord);
begin
  TfmUIPlate(Container).Caption := InstanceRecord.InstanceInterface.GetCaption;
  TfmUIPlate(Container).InstanceRecord := InstanceRecord;
end;

procedure TfmMain.acSmartFindExecuteExecute(Sender: TObject);
begin
  DoCommonAction(caSmartSearchData);
end;

procedure TfmMain.test1Click(Sender: TObject);
begin
  MenuTree.FullExpand;
end;

procedure TfmMain.WorkContainerCanResize(Sender: TObject; var NewWidth,
  NewHeight: Integer; var Resize: Boolean);
begin
  WorkArea.Align := AlClient;
end;

procedure TfmMain.N21Click(Sender: TObject);
begin
  CreateUI('签出操作员', '签出操作员');
end;

procedure TfmMain.FormShow(Sender: TObject);
begin
  {
  if FHTMLBrowser <> nil then
  begin
    //FHTMLBrowser.GoHome;
  end;
  }
end;

procedure TfmMain.MenuTreeCustomDraw(Sender: TCustomTreeView;
  const ARect: TRect; var DefaultDraw: Boolean);
begin

end;

//hanjiwei add it 20080325
procedure TfmMain.N23Click(Sender: TObject);
var
  myfile:TIniFile;
begin
  try
    myfile := TIniFile.Create(FExePath + '../configs/SetPara.ini');
    myfile.WriteInteger('skins','skin',Tcomponent(sender).tag);
    FSkinFile := FExePath + '../skins/'+inttostr(Tcomponent(sender).tag)+'.skn';
    if SkinData1.Active then
      SkinData1.Active := False;

    SkinData1.SkinFile := FSkinFile;
    if not SkinData1.Active then
      SkinData1.Active := True;

  finally
  end;
end;

procedure TfmMain.btnAboutClick(Sender: TObject);
begin
  ShowAbout;
end;

end.

