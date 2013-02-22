program ConvertCard;

uses
  Forms,
  Windows,
  unitMain in 'unitMain.pas' {frmMain},
  UtCardDll in 'UtCardDll.pas';

{$R *.res}

begin
  CreateMutex(nil, false, '804CC63A-BA09-475C-A876-50E7BDA58A50');
  if GetLastError <> 0 then
  begin
    ExitCode:=STILL_ACTIVE;
    Application.Terminate;
  end;
  Application.Initialize;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
