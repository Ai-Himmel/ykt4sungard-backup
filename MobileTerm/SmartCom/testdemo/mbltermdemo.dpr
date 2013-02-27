program mbltermdemo;

uses
  Forms,
  mobiletermdemo in 'mobiletermdemo.pas' {frmMain},
  serialdetail in 'serialdetail.pas' {frmDetail},
  smartterminterface in 'smartterminterface.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := '39ÊÖ»ú»úDemo';
  Application.CreateForm(TfrmMain, frmMain);
  Application.CreateForm(TfrmDetail, frmDetail);
  Application.Run;
end.
