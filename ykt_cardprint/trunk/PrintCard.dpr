program PrintCard;

uses
  Forms,
  UMain in 'UMain.pas' {Form1},
  Udb in 'Udb.pas' {dm: TDataModule},
  UPrintCard in 'UPrintCard.pas' {FrmPrintCard},
  UConfigs in 'UConfigs.pas',
  UStuPrintCard in 'UStuPrintCard.pas' {StuPrintForm},
  USetPix in 'USetPix.pas' {SetPix},
  UEditName in 'UEditName.pas' {EditNameForm},
  UAPrint in 'UAPrint.pas' {APrintForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := '÷∆ø®π‹¿Ì';
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(Tdm, dm);
  Application.CreateForm(TStuPrintForm, StuPrintForm);
  Application.CreateForm(TSetPix, SetPix);
  Application.CreateForm(TEditNameForm, EditNameForm);
  Application.CreateForm(TAPrintForm, APrintForm);
  Application.Run;
end.
