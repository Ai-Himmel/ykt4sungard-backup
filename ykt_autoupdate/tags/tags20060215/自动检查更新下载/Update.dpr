program Update;

uses
  Forms,
  Umain in 'Umain.pas' {frmMain},
  Umd5 in 'Umd5.pas';

{$R *.res}
var
  I : Integer;
  param : string;
  isMinimal : Boolean;
begin
  Application.Initialize;
  for I := 1 to ParamCount do
  begin
    param := ParamStr(I);
    if param = '/m' then
      isMinimal := True;
    //else if param = '/'
  end;
  Application.Title := '自动升级程序监控';
  Application.CreateForm(TfrmMain, frmMain);
  if isMinimal then
  begin
    Application.ShowMainForm := False;
    Application.Minimize;
    frmMain.TrayIcon1.HideMainForm;
  end;

  Application.Run;
end.
