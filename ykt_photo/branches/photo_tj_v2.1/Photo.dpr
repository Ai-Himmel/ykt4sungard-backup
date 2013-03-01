program Photo;

uses
  Forms,
  mainUnit in 'mainUnit.pas' {frmMain},
  uCardPrintTemp in 'uCardPrintTemp.pas' {frmCardPrintTemp},
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
  uPhotoQuery in 'uPhotoQuery.pas' {frmPhotoQuery},
  PSCAMLIB in 'PSCAMLIB.PAS',
  uModifyPwd in 'uModifyPwd.pas' {frmModifyPwd},
  uPhotoPatchCopy in 'uPhotoPatchCopy.pas' {frmPhotoPatchCopy},
  uGetPhotoSet in 'uGetPhotoSet.pas' {frmGetPhotoSet},
  phtImportData in 'phtImportData.pas' {frmImportData},
  phtImportForm in 'phtImportForm.pas' {frmImportForm},
  phtComplete in 'phtComplete.pas' {frmComplete},
  phtDBConnect in 'phtDBConnect.pas' {frmDBConnect},
  phtDefaultValue in 'phtDefaultValue.pas' {frmDefaultValue},
  phtFieldLink in 'phtFieldLink.pas' {frmFieldLink},
  ksPicHandler in 'ksPicHandler.pas',
  UPhotoCopy in 'UPhotoCopy.pas' {frmPhotoCopy},
  DBGrid2Excel in 'DBGrid2Excel.pas',
  uCustImport in 'uCustImport.pas' {frmCustImport};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '拍照/制卡管理系统';
  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(Tfrmdm, frmdm);
  Application.CreateForm(TfrmIfRepalce, frmIfRepalce);
  Application.CreateForm(TloginForm, loginForm);
  Application.CreateForm(TfrmPhotoCopy, frmPhotoCopy);
  Application.CreateForm(TfrmCustImport, frmCustImport);
  Application.Run;
end.
