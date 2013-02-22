unit UMain;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TForm1 = class(TForm)
    btnTeacher: TButton;
    btnStudent: TButton;
    btnExit: TButton;
    btnU: TButton;
    procedure btnTeacherClick(Sender: TObject);
    procedure btnStudentClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure btnUClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses UPrintCard,UStuPrintCard, UAPrint;

{$R *.DFM}

procedure TForm1.btnTeacherClick(Sender: TObject);
begin
  FrmPrintCard:=TFrmPrintCard.Create(application);
  FrmPrintCard.ShowModal;
end;

procedure TForm1.btnStudentClick(Sender: TObject);
begin
  StuPrintForm:=TStuPrintForm.Create(application);
  StuPrintForm.ShowModal;
end;

procedure TForm1.btnExitClick(Sender: TObject);
begin
  Application.Terminate;
end;

procedure TForm1.btnUClick(Sender: TObject);
begin
  AprintForm:=TAprintForm.Create(application);
  AprintForm.ShowModal;
end;

end.
