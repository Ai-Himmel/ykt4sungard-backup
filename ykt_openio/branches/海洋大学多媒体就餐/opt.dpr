program opt;

uses
  Forms,
  SysUtils,
  main in 'main.pas' {mainfrm},
  LoginU in 'LoginU.pas' {LoginFrm},
  SQLite3 in 'SQLite3.pas',
  SQLiteTable3 in 'SQLiteTable3.pas',
  CommU in 'CommU.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '��ʦ�Ͳ͵Ǽ�ϵͳ';
  slDBPath := ExtractFilepath(application.exename) + 'lunch.db';
  sldb := TSQLiteDatabase.Create(slDBPath);

  Application.CreateForm(TLoginFrm, LoginFrm);
  try
    LoginFrm.ShowModal;
    if LoginFrm.isTerminate then
    begin
      Application.Terminate;
      exit;
    end;
  finally
    LoginFrm.Free;
  end;

  Application.CreateForm(TMainFrm, MainFrm);
  Application.Run;
end.

