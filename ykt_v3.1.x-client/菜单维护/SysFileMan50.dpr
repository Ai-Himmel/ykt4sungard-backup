program SysFileMan50;

uses
  Forms,
  USysFileMan in 'USysFileMan.pas' {fmSysFileMan},
  KSClientConsts in '..\Framework\KSClientConsts.pas',
  KSMenuFiles in '..\Framework\KSMenuFiles.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfmSysFileMan, fmSysFileMan);
  Application.Run;
end.
