program mbltermdemo;

uses
  Forms,
  mobiletermdemo in 'mobiletermdemo.pas' {frmMain},
  serialdetail in 'serialdetail.pas' {frmDetail},
  smartterminterface in 'smartterminterface.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := '39�ֻ���Demo';
  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(TfrmDetail, frmDetail);
  Application.Run;
end.
