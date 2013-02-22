unit UEditName;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TEditNameForm = class(TForm)
    Label1: TLabel;
    edtName: TEdit;
    btnOk: TButton;
    btnCancle: TButton;
    procedure btnCancleClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  EditNameForm: TEditNameForm;

implementation

uses UConfigs, UPrintCard, UStuPrintCard;

{$R *.DFM}

procedure TEditNameForm.btnCancleClick(Sender: TObject);
begin
  Close;
end;

procedure TEditNameForm.btnOkClick(Sender: TObject);
begin
  if cardtype='T' then
    frmprintcard.QRLabel4.Caption:=edtName.Text;
  if cardtype='S' then
    StuPrintForm.QRLabel4.Caption:=edtName.Text;
  Close;
end;

procedure TEditNameForm.FormShow(Sender: TObject);
begin
  edtName.Text:=sname;
end;

end.
