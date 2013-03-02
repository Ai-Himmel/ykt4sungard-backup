unit UCommon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  Buttons, ExtCtrls, StdCtrls, UCardDll, UOtherCommon;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //当前登录卡片某个扇区是使用KEY-A或是KEY-B
  //CurrentControlBit='7F078800';
  CurrentControlBit = 'FF078069';
  DefaultKeyA = 'FFFFFFFFFFFF';
  DefaultKeyB = 'FFFFFFFFFFFF';

  {授权卡发行时根据用户输入的信息生成两套工作密钥}
procedure GetTwoPrivacyKey(AuthCardSeedKey: PChar; SectionNO: PChar;
  BlockNo: PChar; BitNo: PChar; var KeyA: PChar; KeyB: PChar; var ErrorMsg:
  string);

{得到授权卡中所需要的主业务工作密钥}
procedure GetMainWorkKey(var MainKey: PChar; var ErrorMsg: string);

{格式化指定扇区}
procedure FormatCardSection(CardNo: PChar; SectionNo: longint; var ErrorMsg:
  string);

{发行授权卡}
procedure IssueAuthCard(CardNo: PChar; KeyA: PChar; KeyB: PChar; MainKey: PChar;
  CheckSum: PChar; SectionNO: longint; BlockNo: longint; BitNo: longint;
  var ErrorMsg: string);

{发行授权卡－根据KEY-A和KEY-A的位置生成需要向KEY-A所在块写入的数据}
//procedure GetAuthCardKeyAData(KeyA:PChar;WritePosInfo:PChar;SectionNO:longint;BlockNo:longint;
//            BitNo:longint;var keyAData:PChar;var ErrorMsg:String);

{发行授权卡－写入KEY-A}
procedure WriteAuthCardKeyA(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  KeyAData: PChar; WritePosInfo: longint;
  SectionNO: longint; BlockNo: longint; var ErrorMsg: string);

{发行授权卡－根据KEY-B和KEY-B的位置生成需要向KEY-B所在块写入的数据}
procedure GetAuthCardKeyBData(KeyB: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var keyBData: PChar; var ErrorMsg: string);

{发行授权卡－写入KEY-B}
procedure WriteAuthCardKeyB(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  keyBData: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var ErrorMsg: string);

{发行授权卡－根据主业务工作密钥和它的位置信息生成需要在该位置以块为单位写入的数据}
procedure GetAuthCardMainWorkKey(MainKey: PChar; SectionNO: PChar; BlockNo:
  PChar;
  BitNo: PChar; var MainkeyData: PChar; var ErrorMsg: string);

{发行授权卡－写入主业务工作密钥}
procedure WriteAuthCardMainKey(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  MainkeyData: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var ErrorMsg: string);

{ 发行授权卡－写入KEY-A＋存取控制＋KEY-B}
procedure WriteCardMainKeyFourBlock(CardNo: PChar; ReadKeyA: PChar; ReadkeyB:
  PChar;
  keyA: PChar; KeyB: PChar; SectionNO: longint;
  BlockNo: longint; var ErrorMsg: string);

{发行授权卡－生成KEY-A的加密过程}
procedure AuthCardEncryption(UserCardSeedKey: PChar; var KeyA: PChar);

{向卡中指定块写入数据}
function WriteCardSelectBlock(CardNo: Pchar; SectionNO: longint; BlockNo:
  longint;
  WriteData: PChar; var ErrorMsg: string): longint;

{根据指定长度指定位置的一个串生成补齐随机数构成一个块数据（每次最小写卡单位）}
function GetCanWriteBlockData(BitNo: longint; WriteDataLen: Longint; BlockLen:
  longint;
  OldData: PChar; var OutData: PChar; var ErrorMsg: string): longint;

{检测当前在感应区内的卡是否正确，在每个对卡的操作前都应该使用该函数进行确认}
function CheckCardValid(inCardId: string; var ErrorMsg: string): longint;
//procedure AuthCardDecipherment

{生成密钥明文}
function GenPrivacyKeyPlainText(KeyStr1, KeyStr2, KeyStr3: string;
  var OKeyStr: string; var OSeKeyStr: string; var ErrorMsg: string): longint;

{生成密钥密文－加密}
function GenEncryptPrivacyKey(oldtext: string; var enctext: string; var
  ErrorMsg: string): longint;

function ReadSectionCardData(Cardno: string; Sectionno: longint; SectionKey:
  Pchar; var Data1: string;
  var Data2: string; var Data3: string; var Data4: string; var Data5: string;
  var Data6: string): longint;

{DES算法－>KEY-A}
function GenDESToKeyA(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;

{3DES算法－>KEY-B}
function Gen3DESToKeyB(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;

{生成两套密钥－－KEY-A}
function GenAuthCardTwoKeyA(BInString: string; var FResultKey: string): string;

{生成两套密钥－－KEY-B}
function GenAuthCardTwoKeyB(BInString: string; var FResultKey: string): string;

{将一段内存转化为一个十六进制字符串}
function ConvertPCharToHexStr(BInChar: PChar; StringLength: longint; var
  FResultString: string; var ErrorMsg: string): Longint;
function ConvertHexStrToPChar(BInString: string; StringLength: longint; var
  FResultChar: PChar; var ErrorMsg: string): Longint;

{判断是否可以访问默认的未初始化的授权卡的指定卡片的指定扇区}
function CanLoginSelSection(FCardno: string; FSectionNo: longint; FSectionKey:
  Pchar; var ErrorMsg: string): Longint;

{得到某个扇区的标准KEY-A
FCardFormat：卡是否格式化}
function GetBlockStandardKeyA(FCardNo: string; FSectionNo: longint; FCardFormat:
  longint;
  var SectionKeyA: Pchar; var ErrorMsg: string): longint;

{检验授权卡有效性并得到授权卡主工作密钥}
function CheckCardMainkey(var OutMainKey: string): integer;

implementation

function CheckCardMainkey(var OutMainKey: string): integer;
var
  ResStr: string;
  Str1, str2, str3, str4, str5, str6: string;
  ResInt: longint;
  GenKeyA, GenKeyB: string;
  KeyA, KeyB, MainKey, CheckSum, CCheckSum: string;
  Section, Blockno, bitno: longint;
  CardStr: string; //卡号
  C, C1, C3: PChar;
  arr: array[0..1] of char;
  arr1: array[0..0] of char;
  TmpMsg: string;
  arr2: array[0..5] of char;
  arr3: array[0..15] of char;
  sect: string;
  TmpStr: string;
  TmpCheckChar: Char;

begin
  //ResStr:=ReadCardPhyID2(CardStr);
  ResStr := ReadCardPhyID(ResStr);
  CardStr := ResStr;
  ShowMessage('物理ID号:' + CardStr);
  if Trim(ResStr) = 'error' then
  begin
    Showmessage('读取物理ID号失败！');
    Exit;
  end;

  //*****************************读取KEY-B******************
  ZeroMemory(@arr2, 6);
  C := @arr2;
  ConvertHexStrToPChar(Pchar(CardStr), 8, C, TmpMsg);
  inc(C, 4);
  sect := inttohex(7, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  C := @arr2;
  ResInt := ReadSectionCardData(CardStr, 7, C, str1, GenKeyB, str3, str4, str5,
    str6);
  if ResInt <> 0 then
  begin
    ShowMessage('读取KEY-B失败！');
    Exit;
  end;
  GenKeyB := Copy(GenKeyB, 1, 16);

  ZeroMemory(@arr1, 1);
  C := @arr1;
  ConVertHexStrToPchar(Copy(GenKeyB, 13, 2), 2, C, TmpMsg);
  Tmpstr := Char(arr1);
  blockno := StrToInt(TmpStr);

  ZeroMemory(@arr1, 1);
  C := @arr1;
  ConVertHexStrToPchar(Copy(GenKeyB, 15, 2), 2, C, TmpMsg);
  tmpstr := Char(arr1);
  bitno := StrToInt(TmpStr);
  //*****************************读取KEY-b******************

  //*****************************读取校验位******************
  ZeroMemory(@arr2, 6);
  C := @arr2;
  ConvertHexStrToPChar(Pchar(CardStr), 8, C, TmpMsg);
  inc(C, 4);
  sect := inttohex(30, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  C := @arr2;
  ResInt := ReadSectionCardData(CardStr, 30, C, CheckSum, str2, str3, str4,
    str5, str6);
  if ResInt <> 0 then
  begin
    ShowMessage('读取校验位失败！');
    Exit;
  end;
  CheckSum := Copy(CheckSum, 23, 2);
  //*****************************读取校验位******************

  //*****************************读取KEY-A******************
  ZeroMemory(@arr2, 6);
  C := @arr2;
  ConvertHexStrToPChar(Pchar(CardStr), 8, C, TmpMsg);
  inc(C, 4);
  sect := inttohex(15, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  C := @arr2;
  ResInt := ReadSectionCardData(CardStr, 15, C, str1, str2, GenKeyA, str4, str5,
    str6);
  if ResInt <> 0 then
  begin
    ShowMessage('读取KEY-A失败！');
    Exit;
  end;
  GenKeyA := Copy(GenKeyA, 17, 16);
  //*****************************读取KEY-A******************

  ZeroMemory(@arr, 2);
  C := @arr;
  ConVertHexStrToPchar(Copy(GenKeyA, 13, 4), 4, C, TmpMsg);
  tmpstr := string(arr);
  Section := 0;
  section := StrToInt(tmpstr);

  KeyA := Copy(GenKeyA, 1, 12);
  KeyB := Copy(GenKeyB, 1, 12);

  //*****************************校验******************
  TmpStr := '';
  TmpStr := GenKeyB + Copy(GenKeyA, 13, 4) + KeyA;
  ZeroMemory(@arr3, 16);
  C := @arr3;
  if ConvertHexStrToPChar(TmpStr, 32, C, TmpMsg) <> 0 then
  begin
    ShowMessage(TmpMsg);
    Exit;
  end;
  TmpCheckChar := Chr(get_check_char(C));
  ConvertPCharToHexStr(Pchar(@TmpCheckChar), 1, CCheckSum, TmpMsg);
  if CCheckSum <> CheckSum then
  begin
    ShowMessage('CChecksum:' + CCheckSum + #13 +
      ' CheckSum:' + CheckSum + ' 校验结果与卡中信息不符！');
    Exit;
  end;
  //*****************************校验******************

  ZeroMemory(@arr2, 6);
  C := @arr2;
  ConvertHexStrToPChar(Pchar(KeyA), 12, C, TmpMsg);
  inc(C, 6);

  MainKey := '';
  SetLength(MainKey, 19);
  C := PChar(MainKey);
  if CanLoginSelSection(CardStr, Section, @arr2, TmpStr) <> 0 then
  begin
    ShowMessage('无权读取第 ' + inttostr(Section) + ' 扇区！');
    Exit;
  end;
  SMT_ReadBlock(Section, blockno, C);

  ResInt := ConvertPCharToHexStr(C, 16, MainKey, TmpMsg);
  if ResInt <> 0 then
  begin
    exit;
  end;
  MainKey := Copy(Mainkey, BitNo * 2 + 1, 16);
  OutMainKey := MainKey;
end;

function GetBlockStandardKeyA(FCardNo: string; FSectionNo: longint; FCardFormat:
  longint;
  var SectionKeyA: Pchar; var ErrorMsg: string): longint;
var
  C1: PChar;
  TmpMsg, sect: string;
  arr, arr1: array[0..5] of char;
  ptr: pchar;
  j: integer;
begin
  case FCardFormat of
    1:
      begin
        ZeroMemory(@arr, 6);
        SectionKeyA := @arr;
        ConvertHexStrToPChar(Pchar(FCardNo), 8, SectionKeyA, TmpMsg);
        inc(SectionKeyA, 4);
        sect := inttohex(FSectionNo, 2);
        c1 := Pchar(sect);
        SectionKeyA^ := C1^;
        Inc(SectionKeyA);
        Inc(C1);
        SectionKeyA^ := C1^;
        Inc(SectionKeyA);
        SectionKeyA := @arr;
      end;
    2:
      begin
        ZeroMemory(@arr1, 6);
        SectionKeyA := @arr1;
        for j := 0 to 5 do
        begin
          SectionKeyA^ := chr(255);
          Inc(SectionKeyA);
        end;
        SectionKeyA^ := chr(0);
        SectionKeyA := @arr1;
      end;
    3:
      begin

      end;
  end;
end;

procedure WriteCardMainKeyFourBlock(CardNo: PChar; ReadKeyA: PChar; ReadkeyB:
  PChar;
  keyA: PChar; KeyB: PChar; SectionNO: longint;
  BlockNo: longint; var ErrorMsg: string);
var
  WriteKey: PChar;
  tmpstr: string;
  C: PChar;
  arrC: array[0..15] of char;
  sect: string;
begin
  ErrorMsg := '';
  if CanLoginSelSection(Cardno, Sectionno, ReadKeyA, ErrorMsg) <> 0 then
    Exit;
  ZeroMemory(@arrC, 16);
  C := @arrC;
  CopyMemory(C, KeyA, 6);
  Inc(C, 6);
  ConvertHexStrToPChar(Pchar(CurrentControlBit), 8, C, ErrorMsg);
  inc(C, 4);
  CopyMemory(C, KeyB, 6);
  //C:=@arrC;
  SMT_WriteBlock(SectionNO, BlockNo, @arrC);
  //WriteCardSelectBlock(CardNo,SectionNO,BlockNo,C,ErrorMsg);
  sect := '';
  ConvertPCharToHexStr(C, 16, sect, ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ':  ' + '写入主工作密钥扇区第三块：' + sect);
end;

function ConvertHexStrToPChar(BInString: string; StringLength: longint;
  var FResultChar: PChar; var ErrorMsg: string): Longint;
var
  tmpstr: string;
  i: integer;
  ptr, pOKeyStr: Pchar;
begin
  try
    Result := 0;
    pOkeystr := Pchar(BInString);
    tmpstr := '';
    //    SetLength (tmpstr, trunc(StringLength/2));
    //    ZeroMemory(pchar(tmpstr),trunc(StringLength/2));

    SetLength(tmpstr, StringLength + 1);
    ZeroMemory(pchar(tmpstr), StringLength + 1);

    ptr := FResultChar;
    for I := 0 to trunc(StringLength / 2) - 1 do
    begin
      copymemory(pchar(tmpstr), pOKeyStr, 2);
      ptr^ := chr(StrToInt('$' + tmpstr));
      Inc(pOkeystr, 2);
      Inc(ptr);
    end;
  except
    result := -1;
    ErrorMsg := '十六进制串:' + BInString + '转换到内存块出错！';
  end;
end;

function ConvertPCharToHexStr(BInChar: PChar; StringLength: longint;
  var FResultString: string; var ErrorMsg: string): Longint;
var
  s: string;
  C: Pchar;
  i: integer;
begin
  try
    s := '';
    ErrorMsg := '';
    Result := 0;
    c := pchar(BInChar);
    for I := 0 to StringLength - 1 do
    begin
      s := s + inttohex(Ord(C^), 2);
      inc(C);
    end;
    FResultString := s;
  except
    ErrorMsg := '内存信息转换到十六进制字符串过程出错！';
    Result := -1;
  end;
end;

function CanLoginSelSection(FCardno: string; FSectionNo: longint;
  FSectionKey: PChar; var ErrorMsg: string): Longint;
var
  TmpStr, ResStr: string;
  arr: array[0..7] of char;
  ptr: pchar;
  i: integer;
  C, C1: PChar;
  TmpMsg, sect: string;
begin
  Result := 0;
  ResStr := ReadCardPhyID(TmpStr);
  if Trim(ResStr) <> '' then
  begin
    ErrorMsg := '卡号无法读取！';
    Result := -1;
    exit;
  end;
  if FCardno <> Trim(TmpStr) then
  begin
    ErrorMsg := '当前读卡器上所放的卡片不正确！';
    Result := -1;
    Exit;
  end;

  {  ptr:=@arr;
    for i:=0 to 5
    do
    begin
       ptr^:=chr(255);
       Inc(ptr);
    end;

    ptr^:=chr(0);
    ptr:=@arr; }

  if SMT_Login_With_UserKey(FSectionNo, FSectionKey, CurrentUserKeyB) <> 0 then
  begin
    Result := -1;
    ErrorMsg := '扇区：' + Inttostr(FSectionNo) + '的Key验证失败！';
    Exit;
  end;
end;

function GenAuthCardTwoKeyB(BInString: string; var FResultKey: string): string;
var
  IString, OString: string;
  TmpMsg: string;
  RSign: integer;
  arr: array[0..15] of char;
  C: PChar;
begin
  Result := '';
  setlength(OString, 6);
  //  C:=PChar(OString);
  ZeroMemory(@arr, 16);
  C := @arr;
  RSign := GenAuthCardKeyB(PChar(BInString), C);
  if RSign = 0 then
  begin
    ConvertPCharToHexStr(C, 6, FResultKey, TmpMsg);
  end
  else
  begin
    Result := '生成密钥A错误！';
  end;
end;

function GenAuthCardTwoKeyA(BInString: string; var FResultKey: string): string;
var
  IString, OString: string;
  TmpMsg: string;
  RSign: longint;
  arr: array[0..15] of char;
  C: PChar;
begin
  Result := '';
  setlength(OString, 6);
  ZeroMemory(@arr, 16);
  C := @arr;
  RSign := GenAuthCardKeyA(PChar(BInString), C);
  if RSign = 0 then
  begin
    ConvertPCharToHexStr(C, 6, FResultKey, TmpMsg);
  end
  else
  begin
    Result := '生成密钥A错误！';
  end;
end;

function Gen3DESToKeyB(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;
var
  iWorkKey, iBaseCardNo, iResultKey: Pchar;
  st: integer;
  C: PChar;
  arr: array[0..7] of char;
  arr1: array[0..3] of char;
  arr2: array[0..7] of char;
begin
  Result := '';
  ZeroMemory(@arr, 8);
  iWorkKey := @arr;
  ConvertHexStrToPChar(BaseWorkKey, 16, iWorkKey, Result);
  ZeroMemory(@arr1, 4);
  iBaseCardNo := @arr1;
  ConvertHexStrToPChar(BaseCardNo, 8, iBaseCardNo, Result);
  ZeroMemory(@arr2, 8);
  C := @arr2;
  st := gen_user_card_keyB(iWorkKey, iBaseCardNo, C);
  if st = 0 then
  begin
    ConvertPCharToHexStr(C, 6, ResultKey, Result);
  end
  else
  begin
    Result := '3DES算法计算失败！请检查操作！';
  end;
end;

function GenDESToKeyA(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;
var
  iWorkKey, iBaseCardNo: Pchar;
  st: integer;
  arr: array[0..7] of char;
  arr1: array[0..3] of char;
  arr2: array[0..7] of char;
  C: PChar;
begin
  Result := '';
  ZeroMemory(@arr, 8);
  iWorkKey := @arr;
  ConvertHexStrToPChar(BaseWorkKey, 16, iWorkKey, Result);
  ZeroMemory(@arr1, 4);
  iBaseCardNo := @arr1;
  ConvertHexStrToPChar(BaseCardNo, 8, iBaseCardNo, Result);
  ZeroMemory(@arr2, 8);
  C := @arr2;
  st := gen_user_card_keyA(iWorkKey, iBaseCardNo, C);
  if st = 0 then
  begin
    ConvertPCharToHexStr(C, 6, ResultKey, Result);
  end
  else
  begin
    Result := 'DES算法计算失败！请检查操作！';
  end;
end;

function ReadSectionCardData(Cardno: string; Sectionno: longint; SectionKey:
  Pchar;
  var Data1: string; var Data2: string; var Data3: string; var Data4: string;
  var Data5: string; var Data6: string): longint;
var
  TmpChar, TmpChar1: string;
  C: PChar;
  TmpStr, tmpStr1: string;
  ResInt: Integer;
  i: integer;
  arr: array[0..5] of char;
begin
  Result := 0;
  if CanLoginSelSection(Cardno, Sectionno, SectionKey, TmpStr) <> 0 then
  begin
    ShowMessage('无权读取第 ' + inttostr(Sectionno) + ' 扇区！');
    Result := -1;
    Exit;
  end;

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := ReaderBlock(sectionno, 0, C);
  FLogList.Add(TimeToStr(Now) + ':' + '读取扇区' + IntTostr(sectionno) +
    '   块' + IntToStr(0) + '   返回：' + IntToStr(Result));
  if ResInt = 0 then
  begin
    ResInt := ConvertPCharToHexStr(C, 16, TmpStr1, TmpStr);
    if ResInt = 0 then
      Data1 := TmpStr1;
  end;

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := SMT_ReadBlock(sectionno, 1, C);
  FLogList.Add(TimeToStr(Now) + ':' + '读取扇区' + IntTostr(sectionno) +
    '   块' + IntToStr(1) + '   返回：' + IntToStr(Result));
  if ResInt = 0 then
  begin
    ResInt := ConvertPCharToHexStr(C, 16, TmpStr1, TmpStr);
    if ResInt = 0 then
      Data2 := TmpStr1;
  end;

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := ReaderBlock(sectionno, 2, C);
  FLogList.Add(TimeToStr(Now) + ':' + '读取扇区' + IntTostr(sectionno) +
    '   块' + IntToStr(2) + '   返回：' + IntToStr(Result));
  if ResInt = 0 then
  begin
    ResInt := ConvertPCharToHexStr(C, 16, TmpStr1, TmpStr);
    if ResInt = 0 then
      Data3 := TmpStr1;
  end;

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := ReaderBlock(sectionno, 3, C);
  FLogList.Add(TimeToStr(Now) + ':' + '读取扇区' + IntTostr(sectionno) +
    '   块' + IntToStr(3) + '   返回：' + IntToStr(Result));
  if ResInt = 0 then
  begin
    setlength(tmpstr1, 32);
    ResInt := ConvertPCharToHexStr(C, 16, TmpStr1, TmpStr);
    if ResInt = 0 then
    begin
      Data4 := Copy(TmpStr1, 1, 12);
      Data5 := Copy(TmpStr1, 13, 8);
      Data6 := Copy(TmpStr1, 21, 12);
    end;
  end;
end;

function GenEncryptPrivacyKey(oldtext: string; var enctext: string; var
  ErrorMsg: string): longint;
var
  tmptext1, tmptext2: pchar;
begin
  ErrorMsg := '';
  tmptext1 := nil;
  tmptext1 := pchar(oldtext);
  tmptext2 := nil;
  ReallocMem(tmptext2, 8);
  if EncryptPrivacyKey(tmptext1, tmptext2) <> 0 then
  begin
    showmessage('加密失败！请检查操作步骤是否有误！');
  end;
end;

function GenPrivacyKeyPlainText(KeyStr1, KeyStr2, KeyStr3: string;
  var OKeyStr: string; var OSeKeyStr: string; var ErrorMsg: string): longint;
var
  UKey1, UKey2, UKey3, tmptext2: string;
  UOutKey: string;
  s: string;
  C: Pchar;
  i: integer;
  TmpMsg: string;
begin
  ErrorMsg := '';
  Result := 0;
  SetLength(UOutKey, 8);
  c := Pchar(UOutKey);
  if GetPrivacyKeyPlainText(PChar(KeyStr1), Pchar(KeyStr2), Pchar(KeyStr3), c) <> 0
    then
  begin
    ErrorMsg := '生成密钥明文错误！';
    Result := -1;
    Exit;
  end;

  Setlength(tmptext2, 9);
  c := Pchar(tmptext2);
  if EncryptPrivacyKey(Pchar(UOutKey), C) <> 0 then
  begin
    showmessage('加密失败！请检查操作步骤是否有误！');
    Result := -1;
    exit;
  end;

  s := '';
  if ConvertPCharToHexStr(PChar(UOutKey), 8, s, TmpMsg) <> 0 then
  begin
    Result := -1;
    exit;
  end;
  OKeyStr := s;
  s := '';
  if ConvertPCharToHexStr(PChar(tmptext2), 8, s, TmpMsg) <> 0 then
  begin
    Result := -1;
    exit;
  end;
  OSeKeyStr := s;
end;

function CheckCardValid(inCardId: string; var ErrorMsg: string): longint;
var
  TmpBuffer: pchar;
begin
  ErrorMsg := '';
  TmpBuffer := nil;
  ReallocMem(TmpBuffer, 4);
  TmpBuffer := PChar(inCardId);
  if RequestCardExist(TmpBuffer, SelectSmartCardType) <> 0 then
  begin
    ErrorMsg := '请更换正确的卡片再进行本次操作！';
    exit;
  end;
  FreeMem(TmpBuffer);
end;

{根据指定长度指定位置的一个串生成补齐随机数构成一个块数据（每次最小写卡单位）}

function GetCanWriteBlockData(BitNo: longint; WriteDataLen: Longint; BlockLen:
  longint;
  OldData: PChar; var OutData: PChar; var ErrorMsg: string): longint;
var
  FWriteData: PChar;
  ptr: pchar;
begin
  try
    Result := 0;
    ptr := OutData;
    Zeromemory(ptr, BlockLen);
    ptr := ptr + BitNo;
    copyMemory(ptr, oldData, WriteDataLen);
  except
    Result := -1;
  end;
end;

{向卡中指定块写入数据}

function WriteCardSelectBlock(CardNo: Pchar; SectionNO: longint; BlockNo:
  longint;
  WriteData: PChar; var ErrorMsg: string): longint;
begin
  FLogList.Add(TimeToStr(Now) + ': 试图向卡中第 ' + Inttostr(sectionNo) +
    ' 扇区;  第 ' +
    Inttostr(Blockno) + ' 块  写入数据');
  Result := SMT_WriteBlock(SectionNo, BlockNo, WriteData);
end;

{授权卡发行时根据用户输入的信息生成两套工作密钥}

procedure GetTwoPrivacyKey(AuthCardSeedKey: PChar; SectionNO: PChar;
  BlockNo: PChar; BitNo: PChar; var KeyA: PChar; KeyB: PChar; var ErrorMsg:
  string);
begin

end;

{得到授权卡中所需要的主业务工作密钥}

procedure GetMainWorkKey(var MainKey: PChar; var ErrorMsg: string);
begin

end;

{格式化指定扇区}

procedure FormatCardSection(CardNo: PChar; SectionNo: longint; var ErrorMsg:
  string);
var
  ftmp: pchar;
  i: integer;
begin
  for i := 0 to 2 do
  begin
    ftmp := nil;
    ReallocMem(ftmp, 16);
    SMT_WriteBlock(SectionNo, i, ftmp);
    freemem(ftmp);
  end;
end;

{发行授权卡}

procedure IssueAuthCard(CardNo: PChar; KeyA: PChar; KeyB: PChar; MainKey: PChar;
  CheckSum: PChar; SectionNO: longint; BlockNo: longint; BitNo: longint;
  var ErrorMsg: string);
var
  C, C1: PChar;
  TmpMsg, sect: string;
  arr: array[0..5] of char;
  j: integer;
begin
  //  C:=@arr;
  //  GetBlockStandardKeyA(CardNo,SectionNo,1,C,TmpMsg);

  {  ConvertHexStrToPChar(Pchar(CurrentControlBit),8,C,TmpMsg);
    inc(C,4);
    CopyMemory(C,@arr,6);
    C:=@arr;
  {  C:=@arr;
    ZeroMemory(C,7);
    FillMemory(C,6,byte(#255)); }

  WriteAuthCardKeyA(CardNo, @arr, Pchar(''), KeyA, 8, 15, 2, ErrorMsg);
  ConvertPCharToHexStr(KeyA, 8, sect, ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ': 为卡－' + CardNo + '成功写入KEY-A!' + #13 +
    '   ' + sect);

  ZeroMemory(@arr, 6);
  C := @arr;
  ConvertHexStrToPChar(Pchar(CardNo), 8, C, TmpMsg);
  inc(c, 4);
  sect := inttohex(7, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  WriteAuthCardKeyA(CardNo, @arr, Pchar(''), KeyB, 0, 7, 1, ErrorMsg);
  sect := '';
  ConvertPCharToHexStr(KeyB, 8, sect, ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ': 为卡－' + CardNo + '成功写入KEY-B!' + #13 +
    '   ' + sect);

  ZeroMemory(@arr, 6);
  C := @arr;
  ConvertHexStrToPChar(Pchar(CardNo), 8, C, TmpMsg);
  inc(c, 4);
  sect := inttohex(SectionNo, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  WriteAuthCardMainKey(CardNo, @arr, Pchar(''), MainKey, SectionNo, blockNo,
    BitNo, ErrorMsg);
  sect := '';
  ConvertPCharToHexStr(MainKey, 8, sect, ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ': 为卡－' + CardNo + '成功写入主工作密钥!' + #13
    + '   ' + sect);

  ZeroMemory(@arr, 6);
  C := @arr;
  ConvertHexStrToPChar(Pchar(CardNo), 8, C, TmpMsg);
  inc(c, 4);
  sect := inttohex(30, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  WriteAuthCardKeyB(CardNo, @arr, Pchar(''), CheckSum, 30, 0, 11, ErrorMsg);
  sect := '';
  ConvertPCharToHexStr(CheckSum, 1, sect, ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ': 为卡－－' + CardNo + '成功写入KEY-A校验位!' +
    #13 + '   ' + sect);

  ZeroMemory(@arr, 6);
  C := @arr;
  ConvertHexStrToPChar(Pchar(CardNo), 8, C, TmpMsg);
  inc(c, 4);
  sect := inttohex(SectionNo, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);
  WriteCardMainKeyFourBlock(CardNo, @arr, Pchar(''), KeyA, KeyB, SectionNo, 3,
    ErrorMsg);
  FLogList.Add(TimeToStr(Now) + ': 为卡－－' + CardNo +
    '成功写入KEY-A写入工作密钥扇区的第三块！!');
end;

{发行授权卡－写入KEY-A}

procedure WriteAuthCardKeyA(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  keyAData: PChar; WritePosInfo: longint;
  SectionNO: longint; BlockNo: longint; var ErrorMsg: string);
var
  arr: array[0..16] of char;
  WriteKey: PChar;
  arr1: array[0..5] of char;
  C, C1: PChar;
  sect: string;
begin
  ErrorMsg := '';

  C := @arr1;
  ConvertHexStrToPChar(Pchar(CardNo), 8, C, ErrorMsg);
  inc(c, 4);
  sect := inttohex(SectionNO, 2);
  c1 := Pchar(sect);
  C^ := C1^;
  Inc(C);
  Inc(C1);
  C^ := C1^;
  Inc(C);

  if CanLoginSelSection(Cardno, Sectionno, @arr1, ErrorMsg) <> 0 then
  begin
    FLogList.Add(TimeToStr(Now) + ': ' + ErrorMsg);
    ShowMessage(ErrorMsg);
    CardSaveLog;
    Exit;
  end;
  Writekey := @arr;
  ZeroMemory(@arr, 16);
  if GetCanWriteBlockData(WritePosInfo, 8, 16, keyAData, WriteKey, ErrorMsg) <> 0
    then
  begin
    FLogList.Add(TimeToStr(Now) + ': ' + ErrorMsg);
    CardSaveLog;
    ShowMessage(ErrorMsg);
    Exit;
  end;
  WriteCardSelectBlock(CardNo, SectionNo, BlockNo, WriteKey, ErrorMsg);
end;

{发行授权卡－根据KEY-B和KEY-B的位置生成需要向KEY-B所在块写入的数据}

procedure GetAuthCardKeyBData(KeyB: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var keyBData: PChar; var ErrorMsg: string);
begin

end;

{发行授权卡－写入KEY-B}

procedure WriteAuthCardKeyB(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  keyBData: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var ErrorMsg: string);
var
  WriteKey, C: PChar;
  arr, arr1: array[0..15] of char;
  Tmpstr: string;
begin
  ErrorMsg := '';
  if CanLoginSelSection(Cardno, Sectionno, ReadKeyA, ErrorMsg) <> 0 then
  begin
    FLogList.Add(TimeToStr(Now) + ': ' + ErrorMsg);
    CardSaveLog;
    ShowMessage(ErrorMsg);
    Exit;
  end;
  ZeroMemory(@arr, 16);
  WriteKey := @arr;
  if GetCanWriteBlockData(BitNo, 1, 16, keyBData, WriteKey, ErrorMsg) <> 0 then
  begin
    FLogList.Add(TimeToStr(Now) + ': ' + ErrorMsg);
    CardSaveLog;
    ShowMessage(ErrorMsg);
    Exit;
  end;
  ZeroMemory(@arr1, 16);
  C := @arr1;
  ConvertPCharToHexStr(C, 16, Tmpstr, ErrorMsg);
  WriteCardSelectBlock(CardNo, SectionNo, BlockNo, WriteKey, ErrorMsg);
end;

{发行授权卡－根据主业务工作密钥和它的位置信息生成需要在该位置以块为单位写入的数据}

procedure GetAuthCardMainWorkKey(MainKey: PChar; SectionNO: PChar; BlockNo:
  PChar;
  BitNo: PChar; var MainkeyData: PChar; var ErrorMsg: string);
begin

end;

{发行授权卡－写入主业务工作密钥}

procedure WriteAuthCardMainKey(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  MainkeyData: PChar; SectionNO: Longint; BlockNo: Longint;
  BitNo: Longint; var ErrorMsg: string);
var
  WriteKey: PChar;
  arr: array[0..15] of char;
begin
  ErrorMsg := '';
  if CanLoginSelSection(Cardno, Sectionno, ReadKeyA, ErrorMsg) <> 0 then
    Exit;
  ZeroMemory(@arr, 16);
  WriteKey := @arr;
  if GetCanWriteBlockData(BitNo, 8, 16, MainkeyData, WriteKey, ErrorMsg) <> 0
    then
    Exit;
  WriteCardSelectBlock(CardNo, SectionNo, BlockNo, WriteKey, ErrorMsg);
end;

{发行授权卡－生成KEY-A的加密过程}

procedure AuthCardEncryption(UserCardSeedKey: PChar; var KeyA: PChar);
begin

end;

end.

