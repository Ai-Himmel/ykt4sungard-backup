program PhotoTran;

uses
  Forms,
  PhotoTrans in 'PhotoTrans.pas' {Form1},
  UtConfigs in 'UtConfigs.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
