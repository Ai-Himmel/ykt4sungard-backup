unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, OleServer, DRCOMINTERFACELib_TLB;

type
  TForm1 = class(TForm)
    edt1: TEdit;
    lbl1: TLabel;
    btn1: TButton;
    bsns1: TBusiness;
    btn2: TButton;
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.btn1Click(Sender: TObject);
var
  stuempno : WideString;
  state,ret : Integer;
  money : Double;
begin
  stuempno := edt1.Text;
  if length(stuempno) = 0 then
  begin
    ShowMessage('error');
    Exit;
  end;
  ret := bsns1.GetState(stuempno,state);
  if ret <> 0 then
  begin
    ShowMessage('��ȡ״̬���� [ ' + IntToStr(ret) + '] ');
  end
  else
  begin

    ShowMessage('�˻�״̬ [' + IntToStr(state) + ']');

    ret := bsns1.GetBalance(stuempno,money);
    if ret <> 0 then
    begin
      ShowMessage('��ȡ���ʧ�� [' + IntToStr(ret) + ']');
    end
    else
    begin
      ShowMessage(Format('��� %f',[money]));
    end;
  end;
end;

procedure TForm1.btn2Click(Sender: TObject);
var
  stuempno : WideString;
  ret : Integer;
begin
  stuempno := edt1.Text;
  if length(stuempno) = 0 then
  begin
    ShowMessage('error');
    Exit;
  end;
  if Application.MessageBox('ȷ����ֵ1Ԫ��','',MB_YESNO) = IDOK then
  begin
    ret := bsns1.Deposit(stuempno,1.00,'','',0);
    if ret <> 0 then
    begin
      ShowMessage(Format('��ֵʧ�ܣ�����[%d]',[ret]));
    end;
  end;
end;

end.
