unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Image1: TImage;
    Timer1: TTimer;
    Edit1: TEdit;
    Button3: TButton;
    Label1: TLabel;
    procedure Button2Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
    str:string;
    st:integer;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Button2Click(Sender: TObject);
begin
  close;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  if st=0 then
    str:=''
  else
    dec(st);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  if str='' then
    showmessage('超时！');
  if (trim(edit1.Text)<>str)and(str<>'') then
    showmessage('验证码错误！');
  if trim(edit1.text)=str then
    showmessage('成功了');
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  S: string;
  I: Integer;
  vPoint: TPoint;
  vLeft: Integer;

begin
  Randomize;
  S := Format('%.4d', [Random(10000)]);
  vLeft := 0;
  Image1.picture:=nil;
  for I := 1 to Length(S) do
  begin
    Image1.Canvas.Font.Size := Random(4) + 9;
    Image1.Canvas.Font.Color := RGB(Random(256) and $C0,
      Random(256) and $C0, Random(256) and $C0);
    if Random(2) = 1 then
      Image1.Canvas.Font.Style := [fsBold]
    else Image1.Canvas.Font.Style := [];
    Image1.Canvas.Font.Name := Screen.Fonts[6];
    vPoint.X := Random(4) + vLeft;
    vPoint.Y := Random(10);
    Image1.Canvas.TextOut(vPoint.X, vPoint.Y, S[I]);
    str:=str+s[i];
    vLeft := vPoint.X + Image1.Canvas.TextWidth(S[I]);
  end;
  self.Caption:='';
  self.Caption:='验证码为:'+str;
  st:=60;
end;

end.
