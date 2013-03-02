unit UTest;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Spin, UOtherCommon, UCommon, UCardDll;

type
  TFrmTest = class(TForm)
    Label5: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    SpinEdit3: TSpinEdit;
    Edit16: TEdit;
    Edit15: TEdit;
    Edit14: TEdit;
    Edit11: TEdit;
    Edit12: TEdit;
    Edit13: TEdit;
    Button1: TButton;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    ListBox1: TListBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Label1: TLabel;
    Edit3: TEdit;
    Button9: TButton;
    Edit4: TEdit;
    Label2: TLabel;
    procedure Edit2Change(Sender: TObject);
    procedure Edit1Change(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button5Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
  private
    ModuleCardIdPhy: string;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FrmTest: TFrmTest;

implementation

{$R *.DFM}

procedure TFrmTest.Edit2Change(Sender: TObject);
begin
  if Length(Edit2.Text) > 12 then
  begin
    Edit2.Text := Copy(Trim(Edit2.Text), 1, 12);
  end;
end;

procedure TFrmTest.Edit1Change(Sender: TObject);
begin
  if Length(Edit1.Text) > 12 then
  begin
    Edit1.Text := Copy(Trim(Edit1.Text), 1, 12);
  end;
end;

procedure TFrmTest.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := cafree;
end;

procedure TFrmTest.Button5Click(Sender: TObject);
var
  TmpNoStr, ErrorMsg, TmpStr, TmpCardPhyNo: string;
begin
  SetLength(TmpCardPhyNo, 8);
  zeroMemory(pchar(TmpCardPhyNo), 8);
  ErrorMsg := Trim(ReadCardPhyID(TmpCardPhyNo));
  if Trim(ErrorMsg) <> '' then
  begin
    ListBox1.Items.Add(TimeToStr(Now) + ':' + ErrorMsg);
  end;
  ConvertPCharToHexStr(Pchar(inttohex(SpinEdit3.Value, 2)), 2, TmpNoStr,
    ErrorMsg);
  TmpStr := TmpCardPhyNo + TmpNoStr;
  Edit1.Text := tmpstr;
end;

procedure TFrmTest.Button1Click(Sender: TObject);
var
  C: PChar;
  TmpCardPhyNo, sect: string;
  TmpNoStr, TmpMsg, TmpMsgConfig: string;
  arr1: array[0..6] of char;
  ErrorMsg: string;
  TmpStr: string;
  ResInt: SmallInt;
  ptr: Pchar;
  i: integer;
begin
  SetLength(TmpCardPhyNo, 8);
  zeroMemory(pchar(TmpCardPhyNo), 8);
  ErrorMsg := Trim(ReadCardPhyID(TmpCardPhyNo));
  if Trim(ErrorMsg) <> '' then
  begin
    ListBox1.Items.Add(TimeToStr(Now) + ':' + ErrorMsg);
  end;
  ModuleCardIdPhy := TmpCardPhyNo;
  Ptr := @arr1;
  ZeroMemory(Ptr, 7);
  FillMemory(Ptr, 6, byte(#255));
  //  Ptr:=Chr(255)+Chr(255)+Chr(255)+Chr(255)+Chr(255)+Chr(255);
  ResInt := CanLoginSelSection(ModuleCardIdPhy, SpinEdit3.Value, ptr, ErrorMsg);
  if ResInt <> 0 then
  begin
    ListBox1.Items.Add(timetostr(now) + ':' + ErrorMsg);
    exit;
  end;
  ListBox1.Items.Add(timetostr(now) + ':' + '登录成功！');
end;

procedure TFrmTest.Button2Click(Sender: TObject);
var
  TmpStr, TmpStr1: string;
  ResStr: string;
  Str1, str2, str3, str4, str5, str6: string;
  tmpp: pchar;
  ResInt: longint;
  TmpFirstSector: longint;
  TmpSend: string;
  C, C1: PChar;
  TmpMsg, sect: string;
  arr: array[0..5] of char;
begin
  str1 := '';
  str2 := '';
  str3 := '';
  str4 := '';
  str5 := '';
  str6 := '';
  TmpFirstSector := SpinEdit3.Value;
  ZeroMemory(@arr, 6);
  C := @arr;
  TmpSend := Trim(Edit1.Text);
  ConvertHexStrToPChar(TmpSend, 12, C, TmpMsg);

  ResInt := ReadSectionCardData(ModuleCardIdPhy, TmpFirstSector, C, str1, str2,
    str3, str4, str5, str6);
  if ResInt = 0 then
  begin
    edit16.Text := str1;
    edit15.Text := str2;
    edit14.Text := str3;
    edit11.Text := str4;
    edit12.Text := str5;
    edit13.Text := str6;
  end;
end;

procedure TFrmTest.Button4Click(Sender: TObject);
var
  i, j: smallint;
  TmpStr, TmpMsg: string;
  ResStr: string;
  TmpSend: string;
  arr: array[0..15] of char;
  arr1: array[0..5] of char;
  C: PChar;
begin
  {  ResStr:=ReadCardPhyID(TmpStr);
    if Trim(ResStr)='' then
    begin
      ListBox1.Items.Add(timetostr(now)+':'+'物理ID： '+TmpStr);
    end
    else
    begin
      Showmessage(ResStr);
      exit;
    end;   }

  i := SpinEdit3.Value;
  ZeroMemory(@arr1, 16);
  C := @arr1;
  TmpSend := Trim(Edit1.Text);
  ConvertHexStrToPChar(TmpSend, 12, C, TmpMsg);

  if CanLoginSelSection(ModuleCardIdPhy, i, C, TmpStr) <> 0 then
  begin
    ShowMessage('无权操作第 ' + inttostr(i) + ' 扇区！');
    Exit;
  end;

  TmpStr := '';
  for j := 0 to 31 do
  begin
    TmpStr := TmpStr + '0';
  end;
  ZeroMemory(@arr, 16);
  C := @arr;
  ConvertHexStrToPChar(TmpStr, 32, C, TmpMsg);
  if i <> 0 then
    WriteCardSelectBlock(Pchar(ModuleCardIdPhy), i, 0, C, TmpMsg);
  WriteCardSelectBlock(Pchar(ModuleCardIdPhy), i, 1, C, TmpMsg);
  WriteCardSelectBlock(Pchar(ModuleCardIdPhy), i, 2, C, TmpMsg);
  TmpStr := '';
  TmpStr := DefaultKeyA + CurrentControlBit + DefaultKeyB;
  ZeroMemory(@arr, 16);
  C := @arr;
  ConvertHexStrToPChar(TmpStr, 32, C, TmpMsg);
  WriteCardSelectBlock(Pchar(ModuleCardIdPhy), i, 3, C, TmpMsg);
end;

procedure TFrmTest.Button6Click(Sender: TObject);
begin
  edit1.Text := 'FFFFFFFFFFFF';
end;

procedure TFrmTest.Button7Click(Sender: TObject);
begin
  edit2.Text := 'FFFFFFFFFFFF';
end;

procedure TFrmTest.Button8Click(Sender: TObject);
var
  TmpNoStr, ErrorMsg, TmpStr, TmpCardPhyNo: string;
  s1, s2: string;
begin
  GenDESToKeyA(Trim(Edit3.Text), Trim(Edit4.Text), s1);
  Edit1.Text := s1;
  Gen3DESToKeyB(Trim(Edit3.Text), Trim(Edit4.Text), s2);
  Edit2.Text := s2;
end;

procedure TFrmTest.Button9Click(Sender: TObject);
var
  TmpStr: string;
  ResStr: string;
begin
  TmpStr := '';
  if CheckCardMainkey(TmpStr) = 0 then
    Edit3.Text := TmpStr;

  ResStr := ReadCardPhyID(TmpStr);
  if Trim(ResStr) = '' then
    Edit4.Text := TmpStr
  else
    Showmessage(ResStr);
end;

end.
