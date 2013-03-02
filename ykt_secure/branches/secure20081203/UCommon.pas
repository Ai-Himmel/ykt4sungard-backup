unit UCommon;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
  Buttons, ExtCtrls, StdCtrls, UCardDll, UOtherCommon;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //��ǰ��¼��Ƭĳ��������ʹ��KEY-A����KEY-B
  //CurrentControlBit='7F078800';
  CurrentControlBit = 'FF078069';
  DefaultKeyA = 'FFFFFFFFFFFF';
  DefaultKeyB = 'FFFFFFFFFFFF';

  {��Ȩ������ʱ�����û��������Ϣ�������׹�����Կ}
procedure GetTwoPrivacyKey(AuthCardSeedKey: PChar; SectionNO: PChar;
  BlockNo: PChar; BitNo: PChar; var KeyA: PChar; KeyB: PChar; var ErrorMsg:
  string);

{�õ���Ȩ��������Ҫ����ҵ������Կ}
procedure GetMainWorkKey(var MainKey: PChar; var ErrorMsg: string);

{��ʽ��ָ������}
procedure FormatCardSection(CardNo: PChar; SectionNo: longint; var ErrorMsg:
  string);

{������Ȩ��}
procedure IssueAuthCard(CardNo: PChar; KeyA: PChar; KeyB: PChar; MainKey: PChar;
  CheckSum: PChar; SectionNO: longint; BlockNo: longint; BitNo: longint;
  var ErrorMsg: string);

{������Ȩ��������KEY-A��KEY-A��λ��������Ҫ��KEY-A���ڿ�д�������}
//procedure GetAuthCardKeyAData(KeyA:PChar;WritePosInfo:PChar;SectionNO:longint;BlockNo:longint;
//            BitNo:longint;var keyAData:PChar;var ErrorMsg:String);

{������Ȩ����д��KEY-A}
procedure WriteAuthCardKeyA(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  KeyAData: PChar; WritePosInfo: longint;
  SectionNO: longint; BlockNo: longint; var ErrorMsg: string);

{������Ȩ��������KEY-B��KEY-B��λ��������Ҫ��KEY-B���ڿ�д�������}
procedure GetAuthCardKeyBData(KeyB: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var keyBData: PChar; var ErrorMsg: string);

{������Ȩ����д��KEY-B}
procedure WriteAuthCardKeyB(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  keyBData: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var ErrorMsg: string);

{������Ȩ����������ҵ������Կ������λ����Ϣ������Ҫ�ڸ�λ���Կ�Ϊ��λд�������}
procedure GetAuthCardMainWorkKey(MainKey: PChar; SectionNO: PChar; BlockNo:
  PChar;
  BitNo: PChar; var MainkeyData: PChar; var ErrorMsg: string);

{������Ȩ����д����ҵ������Կ}
procedure WriteAuthCardMainKey(CardNo: PChar; ReadKeyA: Pchar; ReadKeyB: Pchar;
  MainkeyData: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var ErrorMsg: string);

{ ������Ȩ����д��KEY-A����ȡ���ƣ�KEY-B}
procedure WriteCardMainKeyFourBlock(CardNo: PChar; ReadKeyA: PChar; ReadkeyB:
  PChar;
  keyA: PChar; KeyB: PChar; SectionNO: longint;
  BlockNo: longint; var ErrorMsg: string);

{������Ȩ��������KEY-A�ļ��ܹ���}
procedure AuthCardEncryption(UserCardSeedKey: PChar; var KeyA: PChar);

{����ָ����д������}
function WriteCardSelectBlock(CardNo: Pchar; SectionNO: longint; BlockNo:
  longint;
  WriteData: PChar; var ErrorMsg: string): longint;

{����ָ������ָ��λ�õ�һ�������ɲ������������һ�������ݣ�ÿ����Сд����λ��}
function GetCanWriteBlockData(BitNo: longint; WriteDataLen: Longint; BlockLen:
  longint;
  OldData: PChar; var OutData: PChar; var ErrorMsg: string): longint;

{��⵱ǰ�ڸ�Ӧ���ڵĿ��Ƿ���ȷ����ÿ���Կ��Ĳ���ǰ��Ӧ��ʹ�øú�������ȷ��}
function CheckCardValid(inCardId: string; var ErrorMsg: string): longint;
//procedure AuthCardDecipherment

{������Կ����}
function GenPrivacyKeyPlainText(KeyStr1, KeyStr2, KeyStr3: string;
  var OKeyStr: string; var OSeKeyStr: string; var ErrorMsg: string): longint;

{������Կ���ģ�����}
function GenEncryptPrivacyKey(oldtext: string; var enctext: string; var
  ErrorMsg: string): longint;

function ReadSectionCardData(Cardno: string; Sectionno: longint; SectionKey:
  Pchar; var Data1: string;
  var Data2: string; var Data3: string; var Data4: string; var Data5: string;
  var Data6: string): longint;

{DES�㷨��>KEY-A}
function GenDESToKeyA(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;

{3DES�㷨��>KEY-B}
function Gen3DESToKeyB(BaseWorkKey: string; BaseCardNo: string; var ResultKey:
  string): string;

{����������Կ����KEY-A}
function GenAuthCardTwoKeyA(BInString: string; var FResultKey: string): string;

{����������Կ����KEY-B}
function GenAuthCardTwoKeyB(BInString: string; var FResultKey: string): string;

{��һ���ڴ�ת��Ϊһ��ʮ�������ַ���}
function ConvertPCharToHexStr(BInChar: PChar; StringLength: longint; var
  FResultString: string; var ErrorMsg: string): Longint;
function ConvertHexStrToPChar(BInString: string; StringLength: longint; var
  FResultChar: PChar; var ErrorMsg: string): Longint;

{�ж��Ƿ���Է���Ĭ�ϵ�δ��ʼ������Ȩ����ָ����Ƭ��ָ������}
function CanLoginSelSection(FCardno: string; FSectionNo: longint; FSectionKey:
  Pchar; var ErrorMsg: string): Longint;

{�õ�ĳ�������ı�׼KEY-A
FCardFormat�����Ƿ��ʽ��}
function GetBlockStandardKeyA(FCardNo: string; FSectionNo: longint; FCardFormat:
  longint;
  var SectionKeyA: Pchar; var ErrorMsg: string): longint;

{������Ȩ����Ч�Բ��õ���Ȩ����������Կ}
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
  CardStr: string; //����
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
  ShowMessage('����ID��:' + CardStr);
  if Trim(ResStr) = 'error' then
  begin
    Showmessage('��ȡ����ID��ʧ�ܣ�');
    Exit;
  end;

  //*****************************��ȡKEY-B******************
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
    ShowMessage('��ȡKEY-Bʧ�ܣ�');
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
  //*****************************��ȡKEY-b******************

  //*****************************��ȡУ��λ******************
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
    ShowMessage('��ȡУ��λʧ�ܣ�');
    Exit;
  end;
  CheckSum := Copy(CheckSum, 23, 2);
  //*****************************��ȡУ��λ******************

  //*****************************��ȡKEY-A******************
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
    ShowMessage('��ȡKEY-Aʧ�ܣ�');
    Exit;
  end;
  GenKeyA := Copy(GenKeyA, 17, 16);
  //*****************************��ȡKEY-A******************

  ZeroMemory(@arr, 2);
  C := @arr;
  ConVertHexStrToPchar(Copy(GenKeyA, 13, 4), 4, C, TmpMsg);
  tmpstr := string(arr);
  Section := 0;
  section := StrToInt(tmpstr);

  KeyA := Copy(GenKeyA, 1, 12);
  KeyB := Copy(GenKeyB, 1, 12);

  //*****************************У��******************
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
      ' CheckSum:' + CheckSum + ' У�����뿨����Ϣ������');
    Exit;
  end;
  //*****************************У��******************

  ZeroMemory(@arr2, 6);
  C := @arr2;
  ConvertHexStrToPChar(Pchar(KeyA), 12, C, TmpMsg);
  inc(C, 6);

  MainKey := '';
  SetLength(MainKey, 19);
  C := PChar(MainKey);
  if CanLoginSelSection(CardStr, Section, @arr2, TmpStr) <> 0 then
  begin
    ShowMessage('��Ȩ��ȡ�� ' + inttostr(Section) + ' ������');
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
  FLogList.Add(TimeToStr(Now) + ':  ' + 'д����������Կ���������飺' + sect);
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
    ErrorMsg := 'ʮ�����ƴ�:' + BInString + 'ת�����ڴ�����';
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
    ErrorMsg := '�ڴ���Ϣת����ʮ�������ַ������̳���';
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
    ErrorMsg := '�����޷���ȡ��';
    Result := -1;
    exit;
  end;
  if FCardno <> Trim(TmpStr) then
  begin
    ErrorMsg := '��ǰ�����������ŵĿ�Ƭ����ȷ��';
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
    ErrorMsg := '������' + Inttostr(FSectionNo) + '��Key��֤ʧ�ܣ�';
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
    Result := '������ԿA����';
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
    Result := '������ԿA����';
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
    Result := '3DES�㷨����ʧ�ܣ����������';
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
    Result := 'DES�㷨����ʧ�ܣ����������';
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
    ShowMessage('��Ȩ��ȡ�� ' + inttostr(Sectionno) + ' ������');
    Result := -1;
    Exit;
  end;

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := ReaderBlock(sectionno, 0, C);
  FLogList.Add(TimeToStr(Now) + ':' + '��ȡ����' + IntTostr(sectionno) +
    '   ��' + IntToStr(0) + '   ���أ�' + IntToStr(Result));
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
  FLogList.Add(TimeToStr(Now) + ':' + '��ȡ����' + IntTostr(sectionno) +
    '   ��' + IntToStr(1) + '   ���أ�' + IntToStr(Result));
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
  FLogList.Add(TimeToStr(Now) + ':' + '��ȡ����' + IntTostr(sectionno) +
    '   ��' + IntToStr(2) + '   ���أ�' + IntToStr(Result));
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
  FLogList.Add(TimeToStr(Now) + ':' + '��ȡ����' + IntTostr(sectionno) +
    '   ��' + IntToStr(3) + '   ���أ�' + IntToStr(Result));
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
    showmessage('����ʧ�ܣ�������������Ƿ�����');
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
    ErrorMsg := '������Կ���Ĵ���';
    Result := -1;
    Exit;
  end;

  Setlength(tmptext2, 9);
  c := Pchar(tmptext2);
  if EncryptPrivacyKey(Pchar(UOutKey), C) <> 0 then
  begin
    showmessage('����ʧ�ܣ�������������Ƿ�����');
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
    ErrorMsg := '�������ȷ�Ŀ�Ƭ�ٽ��б��β�����';
    exit;
  end;
  FreeMem(TmpBuffer);
end;

{����ָ������ָ��λ�õ�һ�������ɲ������������һ�������ݣ�ÿ����Сд����λ��}

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

{����ָ����д������}

function WriteCardSelectBlock(CardNo: Pchar; SectionNO: longint; BlockNo:
  longint;
  WriteData: PChar; var ErrorMsg: string): longint;
begin
  FLogList.Add(TimeToStr(Now) + ': ��ͼ���е� ' + Inttostr(sectionNo) +
    ' ����;  �� ' +
    Inttostr(Blockno) + ' ��  д������');
  Result := SMT_WriteBlock(SectionNo, BlockNo, WriteData);
end;

{��Ȩ������ʱ�����û��������Ϣ�������׹�����Կ}

procedure GetTwoPrivacyKey(AuthCardSeedKey: PChar; SectionNO: PChar;
  BlockNo: PChar; BitNo: PChar; var KeyA: PChar; KeyB: PChar; var ErrorMsg:
  string);
begin

end;

{�õ���Ȩ��������Ҫ����ҵ������Կ}

procedure GetMainWorkKey(var MainKey: PChar; var ErrorMsg: string);
begin

end;

{��ʽ��ָ������}

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

{������Ȩ��}

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
  FLogList.Add(TimeToStr(Now) + ': Ϊ����' + CardNo + '�ɹ�д��KEY-A!' + #13 +
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
  FLogList.Add(TimeToStr(Now) + ': Ϊ����' + CardNo + '�ɹ�д��KEY-B!' + #13 +
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
  FLogList.Add(TimeToStr(Now) + ': Ϊ����' + CardNo + '�ɹ�д����������Կ!' + #13
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
  FLogList.Add(TimeToStr(Now) + ': Ϊ������' + CardNo + '�ɹ�д��KEY-AУ��λ!' +
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
  FLogList.Add(TimeToStr(Now) + ': Ϊ������' + CardNo +
    '�ɹ�д��KEY-Aд�빤����Կ�����ĵ����飡!');
end;

{������Ȩ����д��KEY-A}

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

{������Ȩ��������KEY-B��KEY-B��λ��������Ҫ��KEY-B���ڿ�д�������}

procedure GetAuthCardKeyBData(KeyB: PChar; SectionNO: longint; BlockNo: longint;
  BitNo: longint; var keyBData: PChar; var ErrorMsg: string);
begin

end;

{������Ȩ����д��KEY-B}

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

{������Ȩ����������ҵ������Կ������λ����Ϣ������Ҫ�ڸ�λ���Կ�Ϊ��λд�������}

procedure GetAuthCardMainWorkKey(MainKey: PChar; SectionNO: PChar; BlockNo:
  PChar;
  BitNo: PChar; var MainkeyData: PChar; var ErrorMsg: string);
begin

end;

{������Ȩ����д����ҵ������Կ}

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

{������Ȩ��������KEY-A�ļ��ܹ���}

procedure AuthCardEncryption(UserCardSeedKey: PChar; var KeyA: PChar);
begin

end;

end.

