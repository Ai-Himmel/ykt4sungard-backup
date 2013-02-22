unit USetPix;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  TSetPix = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Label4: TLabel;
    Edit3: TEdit;
    Label5: TLabel;
    Edit4: TEdit;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    Label6: TLabel;
    Label7: TLabel;
    procedure Button3Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Edit1Exit(Sender: TObject);
    procedure Edit2Exit(Sender: TObject);
  private
    { Private declarations }
    procedure SetCardInfo;
  public
    { Public declarations }
    flag:integer;
  end;

var
  SetPix: TSetPix;

implementation

uses
  UPrintCard, UStuPrintCard;

{$R *.DFM}

{ TSetPix }



procedure TSetPix.Button3Click(Sender: TObject);
begin
  Close();
end;

procedure TSetPix.SetCardInfo;
begin
  if flag=1 then
  begin
    FrmPrintCard.Image1.Size.Height:=StrToFloat(Edit1.Text);
    FrmPrintCard.Image1.Size.Width:=StrToFloat(Edit2.Text);
    FrmPrintCard.Image1.Size.Top:=StrToFloat(Edit3.Text);
    FrmPrintCard.Image1.Size.Left:=StrToFloat(Edit4.Text);
    if CheckBox2.Checked=True then
    begin
      FrmPrintCard.QRLabel1.Width:=0;
      FrmPrintCard.QRLabel3.Width:=0;
    end else
    begin
      FrmPrintCard.QRLabel1.Width:=50;
      FrmPrintCard.QRLabel3.Width:=50;
    end;
  end else
  if flag=2 then
  begin
    StuPrintForm.Image1.Size.Height:=StrToFloat(Edit1.Text);
    StuPrintForm.Image1.Size.Width:=StrToFloat(Edit2.Text);
    StuPrintForm.Image1.Size.Top:=StrToFloat(Edit3.Text);
    StuPrintForm.Image1.Size.Left:=StrToFloat(Edit4.Text);
    if CheckBox2.Checked=True then
    begin
      StuPrintForm.QRLabel1.Width:=0;
      StuPrintForm.QRLabel2.Width:=0;
      StuPrintForm.QRLabel3.Width:=0;
    end else
    begin
      StuPrintForm.QRLabel1.Width:=50;
      StuPrintForm.QRLabel2.Width:=50;
      StuPrintForm.QRLabel3.Width:=50;
    end;
  end;
end;

procedure TSetPix.Button1Click(Sender: TObject);
begin
  SetCardInfo;
  Close();
end;

procedure TSetPix.Button2Click(Sender: TObject);
begin
  SetCardInfo;
end;

procedure TSetPix.Edit1Exit(Sender: TObject);
begin
  if CheckBox1.Checked=True then
  begin
    Edit2.Text:=FloatToStr(StrToFloat(Edit1.text)*0.75);
  end;
end;

procedure TSetPix.Edit2Exit(Sender: TObject);
begin
  if CheckBox1.Checked=True then
  begin
    Edit1.Text:=FloatToStr(StrToFloat(Edit2.text)*4/3);
  end;
end;

end.
