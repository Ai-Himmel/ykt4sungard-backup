program KSClient50;

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
  UBrowser in 'UBrowser.pas' {faBrowser: TKSFrame},
  UHTMLBrowser in 'UHTMLBrowser.pas' {faHTMLBrowser: TFrame},
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
  UQhClientConsts in 'UQhClientConsts.pas';

{$R *.RES}

begin
  if not CheckProgramRunning then Halt(0);
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
  CloseStartFlash;
  Application.Run;
  finally
    ReleaseShareMem;
  end;

end.
