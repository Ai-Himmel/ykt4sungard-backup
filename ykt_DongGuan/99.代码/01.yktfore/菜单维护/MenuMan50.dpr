program MenuMan50;

uses
  Forms,
  UMenuMan in 'UMenuMan.pas' {fmSysFileMan},
  KSClientConsts in '..\Framework\KSClientConsts.pas',
  KSMenuFiles in '..\Framework\KSMenuFiles.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfmSysFileMan, fmSysFileMan);
  Application.Run;
end.
