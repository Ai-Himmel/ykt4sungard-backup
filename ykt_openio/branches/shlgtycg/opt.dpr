program opt;

uses
  Forms,
  SysUtils,
  main in 'src\main.pas' {mainfrm},
  LoginU in 'src\LoginU.pas' {LoginFrm},
  SQLite3 in 'src\SQLite3.pas',
  SQLiteTable3 in 'src\SQLiteTable3.pas',
  CommU in 'src\CommU.pas',
  AES in 'src\AES.pas',
  AES2010 in 'src\AES2010.pas';

{$R *.res}

begin
    Application.Initialize;
    Application.Title := '上海理工体育场馆收费系统';


    Application.CreateForm(TLoginFrm, LoginFrm);
  try
        LoginFrm.ShowModal;
        if LoginFrm.isTerminate then begin
            Application.Terminate;
            exit;
        end;
    finally
        LoginFrm.Free;
    end;

    Application.CreateForm(TMainFrm, MainFrm);
    Application.Run;
end.

