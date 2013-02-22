program KSFtp;

uses
  Forms,
  Umain in 'Umain.pas' {frmMain},
  Umd5 in 'Umd5.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
