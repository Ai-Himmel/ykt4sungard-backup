program SuperSecure;

uses
  Forms,
  UCommon in 'UCommon.pas',
  UCardDll in 'UCardDll.pas',
  USuperSecure in 'USuperSecure.pas' {FrmSuperSecure},
  UOtherCommon in 'UOtherCommon.pas',
  UDB in 'UDB.pas' {FrmDB: TDataModule},
  UTest in 'UTest.pas' {FrmTest};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := '校园一卡通卡片安全策略';
  Application.CreateForm(TFrmDB, FrmDB);
  Application.CreateForm(TFrmSuperSecure, FrmSuperSecure);
  Application.Run; 
  end.

