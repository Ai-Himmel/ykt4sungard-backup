unit ULongText;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Spin, ExtCtrls;

type
  TdlgLongText = class(TForm)
    mmText: TMemo;
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    edStart: TSpinEdit;
    edLength: TSpinEdit;
    btnSelect: TButton;
    procedure btnSelectClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure Execute(const ACaption, AText : string);
  end;

var
  dlgLongText: TdlgLongText;

procedure ShowLongText(const ACaption, AText : string);

implementation

{$R *.DFM}

procedure ShowLongText(const ACaption, AText : string);
var
  Dialog : TdlgLongText;
begin
  Dialog := TdlgLongText.Create(Application);
  try
    Dialog.Execute(ACaption,AText);
  finally
    Dialog.Free;
  end;

end;

{ TdlgLongText }

procedure TdlgLongText.Execute(const ACaption, AText: string);
begin
  Caption := ACaption;
  mmText.Lines.Text := AText;
  ShowModal;
end;

procedure TdlgLongText.btnSelectClick(Sender: TObject);
begin
  mmText.SelStart := edStart.Value;
  mmText.SelLength := edLength.Value;
end;

end.
