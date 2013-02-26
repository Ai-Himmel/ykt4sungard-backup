program medical;

uses
  Forms,
  MainU in 'MainU.pas' {MainFrm},
  LoginU in 'LoginU.pas' {LoginFrm},
  AboutU in 'AboutU.pas' {AboutFrm},
  CommU in '..\Share\CommU.pas',
  SetupU in 'SetupU.pas' {SetupFrm};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := '医疗收费系统';
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

