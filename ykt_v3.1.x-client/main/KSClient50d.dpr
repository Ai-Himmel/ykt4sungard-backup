program KSClient50d;

{%File '..\SYSMONSERVER\SysMonServer.dpr'}
{%ToDo 'KSClient50d.todo'}

uses
  Windows,
  Forms,
  UMain in 'UMain.pas' {fmMain},
  KSFrameWorks in '..\Framework\KSFrameWorks.pas',
  KSFrames in '..\Framework\KSFrames.pas',
  UStyles in 'UStyles.pas' {dmStyles: TDataModule},
  KSClientConsts in '..\Framework\KSClientConsts.pas',
  UDatabase in 'UDatabase.pas' {dmDatabase: TDataModule},
  UContext in 'UContext.pas' {dmContext: TDataModule},
  USearch in 'USearch.pas' {faSearch: TKSFrame},
  ULogin in 'ULogin.pas' {dlgLogin},
  UCommData in 'UCommData.pas' {dmCommData: TDataModule},
  KSFrameWorkUtils in '..\Framework\KSFrameWorkUtils.pas',
  UInputTextDlg in 'UInputTextDlg.pas' {dlgInputText},
  UStartFlash in 'UStartFlash.pas' {fmStartFlash},
  UConfirmDlg in 'UConfirmDlg.pas' {dlgConfirm},
  UAdSelCust in 'UAdSelCust.pas' {dlgAdvancedSelectCustomer},
  UCMMenu in 'UCMMenu.pas' {dmMenu: TDataModule},
  KSMenuAdmin in '..\Framework\KSMenuAdmin.pas',
  UDoubleCheck in 'UDoubleCheck.pas' {dlgDoubleCheck},
  KSMenuFiles in '..\Framework\KSMenuFiles.pas',
  KSConfigUtils in '..\Framework\KSConfigUtils.pas',
  UConfigUserMenu in 'UConfigUserMenu.pas' {dlgManagePersonalMenu},
  UPersonalMenus in 'UPersonalMenus.pas',
  KSBranchInfo in '..\Framework\KSBranchInfo.pas',
  KsBranchTree in '..\Framework\KSBranchTree.pas',
  UQhClientConsts in 'UQhClientConsts.pas',
  UForceQuit in 'UForceQuit.pas' {fmForceQuit},
  KSRECVPUSH in '..\特殊\KSRECVPUSH.PAS',
  UPushRevThread in '..\特殊\UPushRevThread.pas',
  KSComCmdDefs in '..\FRAMEWORK\KSComCmdDefs.pas' {ComCmdDefinition: TDataModule},
  KCDataPack in '..\特殊\KCDataPack.pas',
  UCheckOutUser in 'UCheckOutUser.pas' {FrmCheckOutUser},
  CnHardWareInfo in 'CnHardWareInfo.pas',
  UWelcome in 'UWelcome.pas' {faWelcome: TKSFrame};

{$R *.RES}

begin
  if not CheckProgramRunning then
    Halt(0);
  try
    StartTime := GetTickCount;
    ShowStartFlash;
    Application.Initialize;
    Application.CreateForm(TdmStyles, dmStyles);
    Application.CreateForm(TdmDatabase, dmDatabase);
    Application.CreateForm(TfmMain, fmMain);
    Application.CreateForm(TdmCommData, dmCommData);
    Application.CreateForm(TdmMenu, dmMenu);
    Application.CreateForm(TdmContext, dmContext);
    Application.CreateForm(TComCmdDefinition, ComCmdDefinition);
    Application.CreateForm(TfaWelcome, faWelcome);
    //20090803hanjiwei add it 初始化完整体窗口后加载包
    if not dmContext.Terminated then
    begin
      if dmContext <> nil then
        dmContext.WaitForInit;
    end;
    //showm('ddd');
    CloseStartFlash;
    Application.Run;
  finally
    ReleaseShareMem;
  end;
end.

