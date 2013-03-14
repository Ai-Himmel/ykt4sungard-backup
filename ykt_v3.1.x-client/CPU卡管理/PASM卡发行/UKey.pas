unit UKey;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TfrmKey = class(TForm)
    lbl1: TLabel;
    edtPwd: TEdit;
    btnOk: TButton;
    btnCancle: TButton;
    procedure btnOkClick(Sender: TObject);
    procedure btnCancleClick(Sender: TObject);
  private
    { Private declarations }
    FPwd:string;
    procedure setPwd(pwd:string);
  public
    { Public declarations }
    function getPwd: string;
  end;

var
  frmKey: TfrmKey;

implementation

{$R *.DFM}

{ TfrmKey }

function TfrmKey.getPwd: string;
begin
  Result := FPwd;
end;

procedure TfrmKey.setPwd(pwd:string);
begin
  if pwd<>FPwd then
    FPwd := pwd;
end;

procedure TfrmKey.btnOkClick(Sender: TObject);
begin
  if Length(edtPwd.Text)<>6 then
  begin
    ShowMessage('«Î ‰»Î6Œªø⁄¡Ó£°');
    Exit;
  end;
  setPwd(edtPwd.Text);
  Close;
end;

procedure TfrmKey.btnCancleClick(Sender: TObject);
begin
  setPwd('');
  Close;
end;

end.
