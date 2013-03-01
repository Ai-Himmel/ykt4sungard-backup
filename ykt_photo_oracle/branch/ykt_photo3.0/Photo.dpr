program Photo;

uses
  Forms,
  SysUtils,
  mainUnit in 'mainUnit.pas' {frmMain},
  uCardPrintTemp_W in 'uCardPrintTemp_W.pas' {frmCardPrintTemp_W},
  Udm in 'Udm.pas' {frmdm: TDataModule},
  AES in 'AES.pas',
  ElAES in 'ElAES.pas',
  uCommon in 'uCommon.pas',
  uImport in 'uImport.pas' {frmImport},
  phtIfRepalce in 'phtIfRepalce.pas' {frmIfRepalce},
  uExport in 'uExport.pas' {frmExport},
  uAddCustInfo in 'uAddCustInfo.pas' {frmAddCustInfo},
  uPhotoStat in 'uPhotoStat.pas' {frmPhotoStat},
  uAbout in 'uAbout.pas' {frmAbout},
  uLimit in 'uLimit.pas' {frmLimit},
  Ulogin in 'Ulogin.pas' {loginForm},
  uPatchMakeCard in 'uPatchMakeCard.pas' {frmPatchMakeCard},
  PSCAMLIB in 'PSCAMLIB.PAS',
  uModifyPwd in 'uModifyPwd.pas' {frmModifyPwd},
  uCustImport in 'uCustImport.pas' {frmCustImport},
  uGetPhotoSet in 'uGetPhotoSet.pas' {frmGetPhotoSet},
  uPhotoQuery in 'uPhotoQuery.pas' {frmPhotoQuery},
  TAppenderUnit in 'delphi\TAppenderUnit.pas',
  TBDELogInserterUnit in 'delphi\TBDELogInserterUnit.pas',
  TConfiguratorUnit in 'delphi\TConfiguratorUnit.pas',
  TConsoleUnit in 'delphi\TConsoleUnit.pas' {TConsole},
  TDBAppenderUnit in 'delphi\TDBAppenderUnit.pas',
  TDBLogInserterUnit in 'delphi\TDBLogInserterUnit.pas',
  TDBXLogInserterUnit in 'delphi\TDBXLogInserterUnit.pas',
  TErrorHandlerUnit in 'delphi\TErrorHandlerUnit.pas',
  TFileAppenderUnit in 'delphi\TFileAppenderUnit.pas',
  THTMLLayoutUnit in 'delphi\THTMLLayoutUnit.pas',
  TIBXLogInserterUnit in 'delphi\TIBXLogInserterUnit.pas',
  TLayoutUnit in 'delphi\TLayoutUnit.pas',
  TLevelUnit in 'delphi\TLevelUnit.pas',
  TLoggerUnit in 'delphi\TLoggerUnit.pas',
  TLoggingEventUnit in 'delphi\TLoggingEventUnit.pas',
  TLogLogUnit in 'delphi\TLogLogUnit.pas',
  TNullAppenderUnit in 'delphi\TNullAppenderUnit.pas',
  TOnlyOnceErrorHandlerUnit in 'delphi\TOnlyOnceErrorHandlerUnit.pas',
  TOptionConverterUnit in 'delphi\TOptionConverterUnit.pas',
  TPatternLayoutUnit in 'delphi\TPatternLayoutUnit.pas',
  TPropertyConfiguratorUnit in 'delphi\TPropertyConfiguratorUnit.pas',
  TRollingFileAppenderUnit in 'delphi\TRollingFileAppenderUnit.pas',
  TSimpleLayoutUnit in 'delphi\TSimpleLayoutUnit.pas',
  TWriterAppenderUnit in 'delphi\TWriterAppenderUnit.pas',
  TXMLLayoutUnit in 'delphi\TXMLLayoutUnit.pas',
  uCardPrintTemp in 'uCardPrintTemp.pas' {frmCardPrintTemp},
  DCConfiguration in 'delphi\util\DCConfiguration.pas',
  TPrintWriterUnit in 'delphi\util\TPrintWriterUnit.pas',
  TPropertiesUnit in 'delphi\util\TPropertiesUnit.pas',
  TStringUnit in 'delphi\util\TStringUnit.pas',
  TIniConfiguratorUnit in 'delphi\TIniConfiguratorUnit.pas';

{$R *.res}

begin
  Application.Initialize;
  TConfiguratorUnit.doPropertiesConfiguration(ExtractFileDir(Application.ExeName) + '\log4delphi.properties');
  Application.Title := '拍照/制卡管理系统';
  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(Tfrmdm, frmdm);
  Application.CreateForm(TfrmIfRepalce, frmIfRepalce);
  Application.CreateForm(TloginForm, loginForm);
  Application.CreateForm(TfrmPhotoQuery, frmPhotoQuery);
  Application.CreateForm(TTConsole, TConsole);
  Application.CreateForm(TfrmCardPrintTemp, frmCardPrintTemp);
  Application.Run;
end.
