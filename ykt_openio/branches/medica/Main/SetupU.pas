unit SetupU;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ComCtrls, IdCoderMIME, Printers;

type
  TSetupFrm = class(TForm)
    PageControl1: TPageControl;
    BitBtn1: TBitBtn;
    procedure BitBtn2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  SetupFrm: TSetupFrm;
   opcom:boolean;
implementation

uses CommU, MainU;

{$R *.dfm}

procedure TSetupFrm.BitBtn2Click(Sender: TObject);
begin
  close;
end;




procedure TSetupFrm.FormShow(Sender: TObject);
begin


 if opcom then
    BitBtn1.Caption := '关闭串口'
  else
    BitBtn1.Caption := '打开串口';

end;

procedure TSetupFrm.BitBtn1Click(Sender: TObject);
var
  hand: integer;
begin
  if BitBtn1.Caption = '打开串口' then
  begin
    hand := -1;
    hand := SMT_ConnectMF280(posport, baud);
    if (hand <> 0) then
    begin
      FuncShowMessage(handle, '串口打开失败！', 2);
      Exit;
    end
    else begin
        opcom:= true;
      SMT_ControlBuzzer();
      BitBtn1.Caption := '关闭串口';
    end;
  end
  else
  begin
    BitBtn1.Caption := '打开串口';
    SMT_CloseMF280;
     opcom:= false;
  end;

end;

end.

