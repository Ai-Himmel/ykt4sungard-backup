unit redcard;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, IniFiles, inppat,CommU;

type
  Tredcardfrm = class(TForm)
    inputinf: TButton;
    procedure inputinfClick(Sender: TObject);
    //收费登记
    procedure procinppat;

  private
  CardNo:pchar;
  Balance:integer;
    { Private declarations }
  public
    { Public declarations }

  end;

var
  redcardfrm: Tredcardfrm;


implementation

{$R *.dfm}

procedure Tredcardfrm.inputinfClick(Sender: TObject);
var
  hand: integer;
begin
 { hand:=-1;
  hand := SMT_ConnectMF280(posport, baud);
  if (hand <> 0) then
  begin
    FuncShowMessage(handle, '串口打开失败！', 2);
    Exit;
  end;
 hand:=SMT_ReadCardNo(CardNo);
  if hand<>0 then
  begin
  FuncShowMessage(handle, '读取学工号失败！', 2);
  end;
   hand:=SMT_ReadBalance(Balance);
  if hand<>0 then
  begin
  FuncShowMessage(handle, '读取金额失败！', 2);
  end;
  SMT_CloseMF280; }
  procinppat;
end;
procedure Tredcardfrm.procinppat;
var
  frm: Tinppatfrm;
begin
 // if not (DBQuery.Active) or (DBQuery.RecordCount = 0) then exit;
  Screen.Cursor := crHourGlass;
  try
    frm := Tinppatfrm.Create(self);
    try
      frm.CardNo := CardNo;
      frm.Balance :=Balance;
      frm.ShowModal;
    finally
      frm.Free;
    end;
  finally
    Screen.Cursor := crDefault;
  end;
end;



end.

