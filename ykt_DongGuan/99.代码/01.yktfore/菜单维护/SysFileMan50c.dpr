program SysFileMan50c;

uses
  Forms,
  USysFileMan in 'USysFileMan.pas' {fmSysFileMan},
  KSClientConsts in '..\Framework\KSClientConsts.pas',
  KSMenuFiles in '..\Framework\KSMenuFiles.pas',
  UQhClientConsts in '..\MAIN\UQhClientConsts.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfmSysFileMan, fmSysFileMan);
  Application.Run;
end.
