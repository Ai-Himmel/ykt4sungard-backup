unit UticketCodeEdit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, RzButton;

type
  TfrmTicketCodeEdit = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    edtOldCode: TEdit;
    edtNewCode: TEdit;
    RzButton1: TRzButton;
    RzButton2: TRzButton;
    procedure RzButton1Click(Sender: TObject);
    procedure RzButton2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    iType:Integer;
  end;

var
  frmTicketCodeEdit: TfrmTicketCodeEdit;

implementation

{$R *.DFM}

procedure TfrmTicketCodeEdit.RzButton1Click(Sender: TObject);
begin
  iType := 1;
  Close;

end;

procedure TfrmTicketCodeEdit.RzButton2Click(Sender: TObject);
begin
  iType := 0;
  Close;

end;

end.
  