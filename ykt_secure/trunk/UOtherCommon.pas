unit UOtherCommon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  Buttons, ExtCtrls, StdCtrls, IniFiles, Forms, Grids;

const
  PhysicalCardIDLen = 4;
  SaveCypherKeySqlString = 'update YKT_CUR.t_syspara ' +
    ' set ';
  GetPhyCardIdSqlString = 'select paraval from YKT_CUR.t_syspara ' +
    ' where paraid=2006';

var
  FLogList: TStringList;

  {去掉币符}
function DeleteMoneySign(cMoneyString: string): string;

{十六进制数字组成的字符串－－>十六进制实型}
function StrToNum(Str: string; s: integer): real;

{十进制数字－－>十六进制数字组成的字符}
function Numtoch(x: real): char;

{数字-->十六进制字符串}
function NumTostr(x: real; haob: real): string;

{将字符串按位取反
返回结果：
０：失败
１：成功}
function GetNotChar(inChar: string; var outChar: string): integer;

{检查一个字符串中各个字符是否都是数字}
function IsNumber(in_str: string): Boolean;

{计算校验和}
function CheckSum(addr: PWord; len: Integer): Word;

{写入配置文件信息}
function CardSaveLog: longint;

implementation

function CardSaveLog: longint;
var
  my: tinifile;
  temp: string;
begin
  Result := 0;
  if FileExists(ExtractFileDir(application.ExeName) + '\ExceptInfo.log') = false
    then
  begin
    Result := -1;
    //ErrorMsg:='系统配置文件已经被破坏，请与系统管理员联系！';
    exit;
  end
  else
  begin
    FLogList.SaveToFile(ExtractFileDir(application.ExeName) +
      '\ExceptInfo.log');
  end;
end;

function CheckSum(addr: PWord; len: Integer): Word;
var
  nleft, sum: Integer;
  w: PWord;
begin
  nleft := len; //完全可以不用中间变量nleft而直接使用len
  sum := 0;
  w := addr;
  Result := 0; //answer=0

  while nleft > 1 do
  begin
    Inc(sum, w^); //求和
    Inc(w); //指针后移
    Dec(nleft, 2); //长度减少( Word = 2 Byte )
  end;
  if nleft = 1 then //长度为奇数
  begin
    PByte(@Result)^ := PByte(w)^;
    Inc(sum, Result); //这两句可以合并为 Inc(sum,PByte(w)^);
  end;

  sum := sum shr 16 + sum and $FFFF;
  Inc(sum, sum shr 16);
  Result := not sum;
end;

{
function checksum(var buffer:pointer;size:integer):word; // 算校验和的子函数
var
cksum:longword;
buffer1:^word;
begin
  cksum:=0;
  buffer1:=buffer;
  while size > 1 do
  begin
    cksum:=cksum+buffer1^;
    buffer1:=pointer(integer(buffer1)+2);
    size:=size-sizeof(word);
  end;
  if size =0 then
  begin
    buffer1:=pointer(integer(buffer1)+2);
    cksum:=buffer1^+cksum;
  end;
  cksum:= (cksum shr 16) +  (cksum and $ffff);
  cksum:=(cksum shr 16) + cksum;
  result:= not  cksum;
end;
 }

function IsNumber(in_str: string): Boolean;
var
  i: Integer;
  TmpStr: string;
begin
  result := True;
  if Trim(in_str) = '' then
    Exit;
  for i := 0 to length(Trim(in_str)) do
  begin
    TmpStr := Copy(Trim(in_str), i + 1, 1);
    if (TmpStr = '0') or (TmpStr = '1') or (TmpStr = '2') or
      (TmpStr = '3') or (TmpStr = '4') or (TmpStr = '5') or
      (TmpStr = '6') or (TmpStr = '.') or
      (TmpStr = '7') or (TmpStr = '8') or (TmpStr = '9') then
    begin
      //  continue
    end
    else if (TmpStr <> '') then
    begin
      result := False;
      Exit;
    end;
  end;
end;

function GetNotChar(inChar: string; var outChar: string): integer;
var
  len: integer;
  i: integer;
begin
  Result := 0;
  len := length(inChar);
  outChar := '';
  if len > PhysicalCardIDLen then
    Exit;
  for i := 1 to len do
  begin

  end;
  Result := 1;
end;

function NumTostr(x: real; haob: real): string;
var
  s1, s: array[0..40] of char;
  s2: pchar;
  s3: string;
  c: char;
  i, j: integer;
  x1, x2, k: real;
begin
  x1 := int(x);
  i := 1;
  while x1 >= haob do
  begin
    k := x1 - int(x1 / haob) * haob;
    c := numtoch(k);
    s1[i] := c;
    i := i + 1;
    x1 := int(x1 / haob);
  end;
  s1[i] := numtoch(x1);
  for j := 1 to i do
    s[j] := s1[i + 1 - j];
  i := i + 1;
  x2 := x - int(x);
  if x2 <> 0 then
  begin
    s[i] := '.';
    i := i + 1;
    x2 := x2 * haob;
    j := 1;
    while (x2 <> 0) and (j < 8) do
    begin
      k := int(x2);
      s[i] := numtoch(k);
      i := i + 1;
      x2 := (x2 - k) * haob;
      j := j + 1;
    end;
  end;
  i := i - 1;
  getmem(s2, i);
  s3 := s;
  freemem(s2);
  numtostr := s3;
end;

function DeleteMoneySign(cMoneyString: string): string;
var
  i: Integer;
begin
  Result := '';
  for i := 1 to Length(cMoneyString) do
  begin
    if isNumber(cMoneyString[i]) then
      Result := Result + cMoneyString[i];
  end;
end;

function StrToNum(Str: string; s: integer): real;
var
  i, j, k, dec: integer;
  c, sign: char;
  sum: real;
begin
  j := strlen(pchar(str));
  sign := '*';
  sum := 0;
  for i := 1 to j do
  begin
    c := str[i];
    if c = '0' then
      k := 0
    else if c = '1' then
      k := 1
    else if c = '2' then
      k := 2
    else if c = '3' then
      k := 3
    else if c = '4' then
      k := 4
    else if c = '5' then
      k := 5
    else if c = '6' then
      k := 6
    else if c = '7' then
      k := 7
    else if c = '8' then
      k := 8
    else if c = '9' then
      k := 9
    else if c = 'A' then
      k := 10
    else if c = 'B' then
      k := 11
    else if c = 'C' then
      k := 12
    else if c = 'D' then
      k := 13
    else if c = 'E' then
      k := 14
    else if c = 'F' then
      k := 15
    else
    begin
      sign := '/';
      dec := 1;
      k := 0;
    end;
    if sign = '*' then
      sum := sum * s + k
    else
    begin
      sum := sum + k / dec;
      dec := dec * S;
    end;
  end;
  StrToNum := sum;
end;

function Numtoch(x: real): char;
begin
  if x = 0 then
    numtoch := '0'
  else if x = 1 then
    numtoch := '1'
  else if x = 2 then
    numtoch := '2'
  else if x = 3 then
    numtoch := '3'
  else if x = 4 then
    numtoch := '4'
  else if x = 5 then
    numtoch := '5'
  else if x = 6 then
    numtoch := '6'
  else if x = 7 then
    numtoch := '7'
  else if x = 8 then
    numtoch := '8'
  else if x = 9 then
    numtoch := '9'
  else if x = 10 then
    numtoch := 'A'
  else if x = 11 then
    numtoch := 'B'
  else if x = 12 then
    numtoch := 'C'
  else if x = 13 then
    numtoch := 'D'
  else if x = 14 then
    numtoch := 'E'
  else
    numtoch := 'F';
end;

initialization
  begin
    FLogList := TStringList.Create;
    FLogList.LoadFromFile(ExtractFileDir(application.ExeName) + '\ExceptInfo.log');
    CardSaveLog;
  end;

finalization
  begin
    CardSaveLog;
    FLogList.free;
  end;

end.
