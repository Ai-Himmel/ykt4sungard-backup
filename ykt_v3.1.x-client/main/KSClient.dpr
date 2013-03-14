program KSClient;

uses
  Forms,
  UMain in 'UMain.pas' {fmMain},
  KSFrameWorks in '..\Framework\KSFrameWorks.pas',
  KSFrames in '..\Framework\KSFrames.pas',
  KSMenus in '..\Framework\KSMenus.pas',
  UStyles in 'UStyles.pas' {dmStyles: TDataModule},
  KSClientConsts in '..\Framework\KSClientConsts.pas',
  UDatabase in 'UDatabase.pas' {dmDatabase: TDataModule},
  UContext in 'UContext.pas' {dmContext: TDataModule},
  UFieldDomains in 'UFieldDomains.pas' {dmFieldDomains: TDataModule},
  UWait in 'UWait.pas' {fmWaiting},
  USearch in 'USearch.pas' {faSearch: TKSFrame},
  UBrowser in 'UBrowser.pas' {faBrowser: TKSFrame},
  UHTMLBrowser in 'UHTMLBrowser.pas' {faHTMLBrowser: TFrame},
  ULogin in 'ULogin.pas' {dlgLogin},
  UCommData in 'UCommData.pas' {dmCommData: TDataModule},
  KSFrameWorkUtils in '..\Framework\KSFrameWorkUtils.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TdmStyles, dmStyles);
  Application.CreateForm(TdmDatabase, dmDatabase);
  Application.CreateForm(TfmMain, fmMain);
  Application.CreateForm(TfmWaiting, fmWaiting);
  Application.CreateForm(TdmContext, dmContext);
  Application.CreateForm(TdmFieldDomains, dmFieldDomains);
  Application.CreateForm(TdmCommData, dmCommData);
  Application.CreateForm(TdlgLogin, dlgLogin);
  Application.Run;
end.
