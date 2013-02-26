program STADIUM;

uses
  Forms,
  MainU in 'MainU.pas' {MainFrm},
  LoginU in 'LoginU.pas' {LoginFrm},
  AboutU in 'AboutU.pas' {AboutFrm},
  CommU in '..\Share\CommU.pas',
 {$IFDEF VER210}
  AES2010 in '..\Share\AES2010.pas',
{$ELSE}
  AES in '..\Share\AES.pas',
{$ENDIF}
  SetupU in 'SetupU.pas' {SetupFrm};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '体育场馆管理系统';
  Application.CreateForm(TLoginFrm, LoginFrm);
  try
    //LoginFrm.Image1.Picture.LoadFromFile(GetAppPath+'Header.bmp');
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

