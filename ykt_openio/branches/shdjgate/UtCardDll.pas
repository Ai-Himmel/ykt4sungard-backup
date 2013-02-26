{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation

    <Unit>UtCardDll
    <What>ʵ��Ӳ�������ṩ�Ŀ��������dll��װ
    <Written By> Wang SuNa (������)

    <History>-------------------------------------------------------------------
    2004��12��14�� �������
    2006-07-20 �����еײ�ĵ��÷�װ��carddll��ͳһ����
*******************************************************************************}

unit UtCardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
    KSFrameWorks,WorkViews,KSClientConsts,WVCmdReq,utcarddll;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //��ǰ��¼��Ƭĳ��������ʹ��KEY-A����KEY-B
  CurrentControlBit = 'FF078069';
  DefaultKeyA = 'FFFFFFFFFFFF';
  DefaultKeyB = 'FFFFFFFFFFFF';

type
  PSmallInt = ^SmallInt;
  
  TPublishCardMes = packed record
    ShowCardNo: array[1..11] of char;       //�û�����ʾ����
    CardNo: array[1..8] of char;            //�û������׿���
    DeadLineDate: array[1..9] of Char;      //�û���ʹ�ý�ֹ����
    CardRightType: longint;                 //Ȩ�����ͣ�1--254���շ����
    ucName: array[1..9] of Char;            //����
    ucDutyNo: array[1..9] of Char;          //ְ�����
    ucCertificateNo: array[1..21] of Char;  //���֤����
    ucDepartmentNo: array[1..11] of Char;   //��λ���
    ucIdentifyNo: array[1..5] of Char;      //�ͻ����
    ucSexNo: array[1..2] of Char;           //�Ա����
    ucCardNo: array[1..21] of Char;         //���Ż�ѧ��
    ucPwd: array[1..6] of Char;             //����
    ucLibraryNo: array[1..21] of Char;      //ͼ��֤��
    Money: longint;                         //���֣�
    isFormat: Char;                         //�Ƿ��ʽ����һ����
  end;

type
  LOOPPURSEINFO = packed record
    RemainMoney: DWORD;                     // ����Ǯ�����
    DealTimes: WORD;                        // �û���������ˮ��
    DealYear: BYTE;                         // ��������
    DealMonth: BYTE;
    DealDay: BYTE;
    DealHour: BYTE;
    DealMin: BYTE;
    DealTimes_CurTime: BYTE;                // �ۼƽ��״���(��ǰʱ�����)
    DealTimes_CurDay: BYTE;                 // �ۼƽ��״���(������)
  end;

type
  TCardInfo = packed record
    DeadLineDate: array[1..9] of char;      //�û���ʹ�ý�ֹ����
    CardRightType: longint;                 //�û���ʹ��Ȩ�����ͣ�1--254��
    ucName: array[1..9] of Char;            //����
    ucDutyNo: array[1..9] of Char;          //ְ�����
    ucCertificateNo: array[1..21] of Char;  //֤������
    ucDepartmentNo: array[1..11] of Char;   //���ű��
    ucIdentifyNo: array[1..21] of Char;     //��ݴ���
    ucSexNo: array[1..2] of Char;           //�Ա����
    ucCardNo: array[1..21] of Char;         //���ţ����Ż�ѧ�ţ�
  end;

//�����SMT_CheckForCard();
//����1��ʾ�㿨��2��ʾ��ʼ�����Ŀ�, 3��ʾ����ʶ��Ŀ�
function SMT_CheckForCard(): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_CheckForCard';

//��ʼ������ *
function ConnectMF(port: longint; baud: longint): longint;
  stdcall;far; external 'CardDLL.dll' name 'ConnectMF';

//����������
function SMT_ControlBuzzer: longint;
  stdcall;far; external 'CardDLL.dll' name 'ControlBuzzer';

//����Ȩ��
function DLLReadCardMainKey(OutMainKey: PByte;swith:SmallInt;flag:PSmallInt):LongInt;
  stdcall;far; external 'CardDLL.dll' name 'ReadCardMainKey' ;

//���ÿ�ƬΪ����������ҡ��ⶳ��
function SMT_SetNormalFlag: longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetNormalFlag';

//���ÿ�ƬΪ����������ң��ⶳ������汾��2005-06-08����
function SMT_SetNormalFlagByVer(ver:PChar): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetNormalFlagByBlkVerion';

//���տ�
function SMT_ClearCard: longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ClearCard';

//��д����Ȩ *
function ReaderAuthor(MoneyBuf: pchar): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_AutoDll';

function Load_Dll: longint;
  stdcall;far; external 'CardDLL.dll' name 'Load_Dll';

// ���ùرմ��� *
function CloseMF: SmallInt;
  stdcall;far; External 'CardDll.dll' name 'CloseMF';

//���п�   *
function PublishCard(const PCM: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'PublishCard';

//������Ϣ   *
function ReadCardInfo(const PCM: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardInfo';

//�������к� *
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'RequestCard';

//�û�����Ǯ
function PacketAddMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external 'CardDLL.dll' name 'SMT_PacketAddMomey';

//�û���ȡ�� *
function PacketDelMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external 'CardDLL.dll' name 'SMT_PacketDelMomey';

//���û���������Ϣ
function ReadPacketInfo(const LPI: LOOPPURSEINFO): longint;
  stdcall;external 'CardDLL.dll' name 'ReadPacketInfo';

//�û������������ȡ  *
function ReadPersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardPwd';

//�û�������������� *
function ChangePersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'WriteCardPwd';

//�����׿���  *
function ReadExchCardNo(ExchCardNo: PInteger): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardNO';

//������Ϣ *
function GetLastErrMsg(errcode:pointer;msg:pchar ):longint;
  stdcall;external 'CardDLL.dll' name 'GetLastErrMsg';

//���¿���Ϣ   *
function UpdateCardInfo(const CardInfo: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'UpdateCardInfo';
//������Ȩĸ�� *
function CreateMonKeyCard(nKey1: longint; nKey2: longint): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_CreateMonKeyCard';

//������Ȩĸ��  *
function ClearMonKeyCard: smallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearMonKeyCard';
  
//����������Կ�ӿ�  *
function PublishComsumeChildCard(year, month, day, hour: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'PublishComsumeChildCard';

//����������Կ�ӿ�  *
function ClearComsumeChildCard: SmallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearComsumeChildCard';

//���г�ֵ��Կ�ӿ�  *
function PublishAddMoneyChildCard(year, month, day, hour: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'PublishAddMoneyChildCard';

//���ճ�ֵ��Կ�ӿ�  *
function ClearAddMoneyChildCard: SmallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearAddMoneyChildCard';

function get_check_char(InCheckSumString: PChar): longint;
  stdcall;far; external 'desdll.dll' name 'get_check_char';

function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

function SleepCard: longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

//���½��׿���
function SMT_ChangeDealCardNo(dealCardNo:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ChangeDealCardNo';

//���¿����
function SMT_PacketSetMoney(nPacketNo,dealCardNo:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_PacketSetMoney';

//д�����״���
function SMT_SetTxCnt(nPacketNo,tx_cnt:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetTxCnt';
//�����������汾
function SMT_ReadBlackNameListVersion(flag:Pointer;version:string): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ReadBlackNameListVersion';
//���Ǯ����Ϣ
function SMT_PacketReset(PackNo:Integer): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_PacketReset';
//��ȡ����Ϣ
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

//��ʼ��������
function InitNewCard(err_code:PInteger;showcardno:PChar;test:Pointer):longint;
  stdcall;far; external 'CardDLL.dll' name 'InitNewCard';

function HaltCard: LongInt;
  stdcall;far;external 'CardDLL.dll' name 'HaltCard';

//������Ȩ��--------------------------------------------------------------------
function InitNewAuthCard(mainKey:PChar;flag:Byte;callBack:Pointer): LongInt;
  stdcall;external 'CardDLL.dll' name 'InitNewAuthCard';
function SMT_ModifyDeadLineDateAndFlag(mainKey:PChar;flag:Byte): LongInt;
  stdcall;external 'CardDLL.dll' name 'SMT_ModifyDeadLineDateAndFlag';
function SMT_ReadAuthorWorkKeyAndFlag(mainKey:PChar;flag:PByte): LongInt;
  stdcall;external 'CardDLL.dll' name 'SMT_ReadAuthorWorkKeyAndFlag';
function PublishAuthCard(const PCM: TPublishCardMes) : LongInt;
  stdcall;external 'CardDLL.dll' name 'PublishAuthCard';
function ResetNewAuthCard(err_code:Integer;callBack:Pointer) : LongInt;
  stdcall;external 'CardDLL.dll' name 'ResetNewAuthCard';
function SMT_SetAuthNormalFlagByBlkVerion(ver:PChar) : LongInt;
  stdcall;far;external 'CardDLL.dll' name 'SMT_SetAuthNormalFlagByBlkVerion';
function ReadAuthCardInfo(const PCM: TPublishCardMes) : LongInt;
  stdcall;external 'CardDLL.dll' name 'ReadAuthCardInfo';
//------------------------------------------------------------------------------

//******************************************************************************
type
  TCardManage = class
  public
    //����⺯��
    function CheckForCard: longint;
    function Load_Dll: longint;
    //����������
    function ControlBuzzer:longint;
    //��ҡ��ⶳ��
    function SetNormalFlag: longint;
    //��ң��ⶳ
    function SetNormalFlagbyVer(ver:PChar):LongInt;
    //���տ�
    function ClearCard: longint;
    //sleep
    function SleepCardByTime: longint;
    //��ʼ������
    function IniSerialPort(CommId: longint; BaudRate: longint): smallint;
    //�رմ���
    function CloseSerialPort: smallint;
    //��д����Ȩ
    function ReadMachineAuth(MoneyBuf: pchar): smallint;
    //�����������к�
    function ReadCardPhyID(var CardIdString: string): smallint;
    //�û������������ȡ
    function ReadCardPsw: string;
    //���û���������Ϣ
    function ReadCardConsumeInfo(var LPI: LOOPPURSEINFO; nPacketNo: smallint):boolean;
    //����������Ϣ
    function ReadCardInfo(var PCM: TPublishCardMes): smallint;
    //�����׿���
    function ReadExCardID(var ExCardId: string): smallint;
    //���п�
    function PublishACard(const PCM: TPublishCardMes): integer;
    //�������
    function ChangeCardPsw(PassWord: string): smallint;
    //ȡ��
    function DelCardMoney(m: string): boolean;
    //�ӿ�
    function AddCardMoney(m: string): boolean;
    //���¿�������Ϣ
    function UpdateCardBasicInfo(var CardInfo: TPublishCardMes): integer;
    //��ȡ���й�����Կ
    function ReadCardMainkey(var OutMainKey: string;flag:PSmallInt): longint;

    {��һ���ڴ�ת��Ϊһ��ʮ�������ַ���}
    function ConvertPCharToHexStr(BInChar: PChar; StringLength: longint; var FResultString: string; var ErrorMsg: string): Longint;
    function ConvertHexStrToPChar(BInString: string; StringLength: longint; var FResultChar: PChar; var ErrorMsg: string): Longint;

    function ReadSectionCardData(Cardno: string; Sectionno: longint; SectionKey: Pchar; var Data1: string; var Data2: string; var Data3: string; var Data4: string; var Data5:string;var Data6: string): longint;

    {�ж��Ƿ���Է���Ĭ�ϵ�δ��ʼ������Ȩ����ָ����Ƭ��ָ������}
    function CanLoginSelSection(FCardno: string; FSectionNo: longint;FSectionKey: Pchar; var ErrorMsg: string): Longint;

    {��ȡ����Ϣ}
    function ReaderBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):longint;

    //���½��׿���
    function ChangeDealCardNo(dealCardno:LongInt):LongInt;

    //���¿����
    function PacketSetMoney(m:string):Boolean;

    //���¿��Ľ��״���
    function changeTradeNum(Num:LongInt): LongInt;

    //�����������汾
    function readCardBlackVer(flag:Pointer;version:string): LongInt;

    //���Ǯ����Ϣ
    function clearMoneyInfo(packNo:Integer):LongInt ;

    function InitCard(const showcardno:string):LongInt ;

    function HaltCard: LongInt;

    function PublishAuthCard(const PCM: TPublishCardMes): integer;

    function SMT_ModifyDeadLineDateAndFlag(sDate:string;flag:Integer): integer;

    function InitNewAuthCard(mainKey:PChar;flag:Integer): integer;

    function SMT_ReadAuthorWorkKeyAndFlag(var mainKey:string;var flag:Byte): integer;

    function ResetNewAuthCard(err_code:Integer): integer;

    function SMT_SetAuthNormalFlagByBlkVerion(ver:PChar): Integer;

    function ReadAuthCardInfo(const PCM: TPublishCardMes): Integer;
  end;

function SimpleReadCardPhyID(var CardIdString: string): smallint;
//����������Ƿ���ϱ�׼
function Checkedt(key:Char;dot:string): Boolean;

//����ֵ��Ϣ��ȡ
function getReturn(s1:string;wv:TWorkView):string ;

//���п�ʱ�ж��Ƿ�ſ����ſ��Ƿ�����Ч��
function releaseCardJudge: Boolean;

//���п�����ģ��
function pubCard(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;tradeCode:Integer): string;

//���������Ƿ�Ϊ����
function inputNum(key:Char): Boolean;

//��ʽ������ʾ���
function formatCardShow(bCard:Byte):string;

//����׼��
function PrepareReadCardInfo: Boolean;

//��ȡ����
function readCardNo: string;

//����ʾ����
function readShowCarNo: string;

implementation

function SimpleReadCardPhyID(var CardIdString: string): smallint;
var
  ucSerialNo: pchar;
  ucType: pchar;
begin
  ucSerialNo := nil;
  ucType := nil;
  ReallocMem(ucSerialNo, 9);
  ReallocMem(ucType, 3);
  Result := RequestCard(ucSerialNo, ucType);
  if Result = 0 then
  begin
    CardIdString := ucSerialNo;
  end;
end;

function TCardManage.ReadExCardID(var ExCardId: string): smallint;
var
  ucSerialNo: Integer;
begin
  Result := ReadExchCardNo(@ucSerialNo);
  if Result = 0 then
  begin
    ExCardId := IntToStr(ucSerialNo);
  end;
end;

function TCardManage.AddCardMoney(m: string): boolean;
var
  DW: DWORD;
  st: smallint;
begin
  DW := StrToInt64(m);
  st := PacketAddMomey(1, DW);
  if st <> 0 then
  begin
    result := False;
  end
  else
  begin
    result := True;
  end;
end;

//���¿����
function TCardManage.PacketSetMoney(m: string): Boolean;
var
  DW: DWORD;
  st: smallint;
begin
  Result:=True;
  DW := StrToInt64(m);
  st := SMT_PacketSetMoney(1, DW);
  if st <> 0 then
  begin
    result := False;
  end
  else
  begin
    result := True;
  end;
end;

function TCardManage.CanLoginSelSection(FCardno: string;
  FSectionNo: Integer; FSectionKey: Pchar; var ErrorMsg: string): Longint;
var
  TmpStr: string;
  ResInt: smallint;
begin
  Result := 0;
  ResInt := SimpleReadCardPhyID(TmpStr);
  if ResInt <> 0 then
  begin
    ErrorMsg := '����ID���޷���ȡ��';
    ShowMessage(ErrorMsg);
    Result := -1;
    exit;
  end;

  if FCardno <> Trim(TmpStr) then
  begin
    ErrorMsg := '��ǰ�����������ŵĿ�Ƭ����ȷ��';
    Result := -1;
    Exit;
  end;

  if SMT_Login_With_UserKey(FSectionNo, FSectionKey, CurrentUserKeyA) <> 0 then
  begin
    Result := -1;
    ErrorMsg := '������' + Inttostr(FSectionNo) + '��Key��֤ʧ�ܣ�';
    ShowMessage(ErrorMsg);
    Exit;
  end;
end;

function TCardManage.ChangeCardPsw(PassWord: string): smallint;
var
  pchPersonalPsdar: pchar;
begin
  pchPersonalPsdar := nil;
  ReallocMem(pchPersonalPsdar, 13);
  pchPersonalPsdar := PChar(PassWord);
  Result := ChangePersonalPassword(pchPersonalPsdar);
end;

function TCardManage.CloseSerialPort: smallint;
begin
  //0:�رմ��ڳɹ��� -1���رմ���ʧ�ܣ�-2�������̬�����ʧ��
  Result := CloseMF;
end;

function TCardManage.ConvertHexStrToPChar(BInString: string;
  StringLength: Integer; var FResultChar: PChar;
  var ErrorMsg: string): Longint;
var
  tmpstr: string;
  i: integer;
  ptr, pOKeyStr: Pchar;
begin
  try
    Result := 0;
    pOkeystr := Pchar(BInString);
    tmpstr := '';
    SetLength(tmpstr, 3);
    ZeroMemory(pchar(tmpstr), 3);

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

function TCardManage.ConvertPCharToHexStr(BInChar: PChar;
  StringLength: Integer; var FResultString, ErrorMsg: string): Longint;
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

function TCardManage.DelCardMoney(m: string): boolean;
var
  DW: DWORD;
  st: smallint;
begin
  DW := StrToInt(m);
  st := PacketDelMomey(1, DW);
  if st <> 0 then
  begin
    result := False;
  end
  else
  begin
    result := True;
  end;
end;

function TCardManage.IniSerialPort(CommId: longint; BaudRate: longint):smallint;
begin
  // 0: �򿪴��ڳɹ���
  //-1��Ӳ����̬�����ʧ�ܣ�
  //-2����д����ʼ��ʧ�ܣ�
  //-3�������̬�����ʧ��
  Result := ConnectMF(CommId, BaudRate);
end;

function TCardManage.Load_Dll: longint;
begin
  Result := Load_Dll;
end;

function TCardManage.PublishACard(const PCM: TPublishCardMes): integer;
begin
  Result := PublishCard(PCM);
end;

function TCardManage.ReadCardConsumeInfo(var LPI: LOOPPURSEINFO; nPacketNo:smallint): boolean;
var
  st: smallint;
begin
  LPI.RemainMoney := 0;
  LPI.DealTimes := 0;
  LPI.DealYear := 0;
  LPI.DealMonth := 0;
  LPI.DealDay := 0;
  LPI.DealHour := 0;
  LPI.DealMin := 0;
  LPI.DealTimes_CurTime := 0;
  LPI.DealTimes_CurDay := 0;
  st := ReadPacketInfo(LPI);
  if st = 0 then
  begin
    Result := True;
  end
  else
  begin
    Result := False;
  end;
end;

function TCardManage.ReadCardInfo(var PCM: TPublishCardMes): smallint;
begin
  FillChar(PCM.ShowCardNo, SizeOf(PCM.ShowCardNo), Ord('0'));
  FillChar(PCM.CardNo, SizeOf(PCM.CardNo), Ord('0'));
  FillChar(PCM.DeadLineDate, SizeOf(PCM.DeadLineDate), Ord('0'));
  FillChar(PCM.ucName, SizeOf(PCM.ucName), Ord('0'));
  FillChar(PCM.ucDutyNo, SizeOf(PCM.ucDutyNo), Ord('0'));
  FillChar(PCM.ucCertificateNo, SizeOf(PCM.ucCertificateNo), Ord('0'));
  FillChar(PCM.ucDepartmentNo, SizeOf(PCM.ucDepartmentNo), Ord('0'));
  FillChar(PCM.ucLibraryNo, SizeOf(PCM.ucLibraryNo), Ord('0'));
  FillChar(PCM.ucSexNo, SizeOf(PCM.ucSexNo), Ord('0'));
  FillChar(PCM.ucCardNo, SizeOf(PCM.ucCardNo), Ord('0'));
  Result := UtCardDll.ReadCardInfo(PCM);
end;

function TCardManage.ReadCardMainkey(var OutMainKey: string;flag:PSmallInt): longint;
var
  ResInt: smallint;
  TmpStr: string;
  keybuf : array[0..8] of Byte;
begin
  Result := 1;
  ResInt := DLLReadCardMainKey(PByte(@keybuf),1,flag);
  if ResInt <> 0 then
  begin
    Exit;
  end;
  SetLength(OutMainKey,16);
  ConvertPCharToHexStr(PChar(@keybuf),8,OutMainKey,TmpStr);
  Result := 0;
end;

function TCardManage.ReadCardPhyID(var CardIdString: string): smallint;
var
  ucSerialNo: pchar;
  ucType: pchar;
begin
  ucSerialNo := nil;
  ucType := nil;
  ReallocMem(ucSerialNo, 9);
  ReallocMem(ucType, 3);
  Result := RequestCard(ucSerialNo, ucType);
  if Result = 0 then
  begin
    CardIdString := ucSerialNo;
  end;
end;

function TCardManage.ReadCardPsw: string;
var
  pcPersonalPsd: pchar;
  st: smallint;
begin
  pcPersonalPsd := nil;
  ReallocMem(pcPersonalPsd, 13);
  st := ReadPersonalPassword(pcPersonalPsd);
  if st = 0 then
  begin
    Result := pcPersonalPsd;
  end
  else
  begin
    Result := 'error';
  end;
end;

function TCardManage.ReaderBlock(Sector, BlockNo: Integer;
  BlockBuf: PChar): longint;
begin
  Result := SMT_ReadBlock(Sector, BlockNo, BlockBuf);
end;

function TCardManage.ReadMachineAuth(MoneyBuf: pchar): smallint;
begin
  Result := ReaderAuthor(MoneyBuf);
end;

function TCardManage.ReadSectionCardData(Cardno: string;
  Sectionno: Integer; SectionKey: Pchar; var Data1, Data2, Data3, Data4,
  Data5, Data6: string): longint;
var
  TmpChar: string;
  C: PChar;
  TmpStr, tmpStr1: string;
  ResInt: Integer;
begin
  Result := 0;
  CanLoginSelSection(Cardno, Sectionno, SectionKey, TmpStr); 

  TmpChar := '';
  SetLength(tmpChar, 19);
  C := PChar(TmpChar);
  ResInt := ReaderBlock(sectionno, 0, C);
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

function TCardManage.SleepCardByTime: longint;
begin
  Result := SleepCard;
end;

function TCardManage.UpdateCardBasicInfo(
  var CardInfo: TPublishCardMes): integer;
begin
  Result := UpdateCardInfo(CardInfo);
end;

function TCardManage.ClearCard: longint;
begin
  Result := SMT_ClearCard;
end;

function TCardManage.SetNormalFlag: longint;
begin
  Result := SMT_SetNormalFlag;
end;

function TCardManage.ControlBuzzer: longint;
begin
  Result:=SMT_ControlBuzzer;
end;

//���ÿ�Ϊ����״̬����д�汾��
function TCardManage.SetNormalFlagbyVer(ver: PChar): LongInt;
begin
  Result:=SMT_SetNormalFlagByVer(ver);
end;

//���½��׿���
function TCardManage.ChangeDealCardNo(dealCardno: LongInt): LongInt;
begin
  Result := SMT_ChangeDealCardNo(dealCardno);
end;

//���¿��Ľ��״���
function TCardManage.changeTradeNum(Num:LongInt): LongInt;
begin
  Result := SMT_SetTxCnt(1,Num);
end;

//��ȡ���������汾
function TCardManage.readCardBlackVer(flag:Pointer;version:string): LongInt;
begin
  Result := SMT_ReadBlackNameListVersion(flag,version);
end;

//���Ǯ����Ϣ
function TCardManage.clearMoneyInfo(packNo: Integer): LongInt;
begin
  Result := SMT_PacketReset(packNo);
end;

{-------------------------------------------------------------------------------
  ������:    Checkedt���������������������Ƿ���ȷ
  ����:      Administrator
  ����:      2005.07.19
  ����:      key:Char;dot:string
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function Checkedt(key:Char;dot:string): Boolean;
begin
  if (Key in ['0'..'9','.',#8,#13]) then
    Result:=True
  else
    result:=False;


  {if (key in ['.']) and (pos('.',dot)>0) then
    Result:=False
  else
    Result:=True;
  if (pos('.',dot)>0) and (Length(Copy(dot,POS('.',dot),Length(dot)-pos('.',dot)))>=2) then
    Result := false
  else
    Result:=True;}

end;


{-------------------------------------------------------------------------------
  ������:    inputNum�ô�У��ֻ����������
  ����:      ����ΰ
  ����:      2005.08.10
  ����:      key:Char
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function inputNum(key:Char): Boolean;
begin
  if (Key in ['0'..'9',#8,#13]) then
    Result:=True
  else
    result:=False;
end;

{-------------------------------------------------------------------------------
  ������:    formatCardShow��ʽ������ʾ���
  ����:      ����ΰ
  ����:      2005.08.10
  ����:      bCard:Byte
  ����ֵ:    ��
-------------------------------------------------------------------------------}
function formatCardShow(bCard:Byte):string;
begin
  if length(format('%d', [bCard])) = 1 then
    Result := '0' + format('%d', [bCard])
  else
    Result :=format('%2d', [bCard]);
end;

{-------------------------------------------------------------------------------
  ������:    getReturn���ú�̨������Ϣ
  ����:      Administrator����ΰ
  ����:      2005.07.19
  ����:      s1:string;wv:TWorkView
  ����ֵ:    string
-------------------------------------------------------------------------------}
function getReturn(s1:string;wv:TWorkView):string ;
begin
  ConText.GetDialogSystem.showmessage(s1+wv.FieldByName('������Ϣ').Data.AsString);
end;

{-------------------------------------------------------------------------------
  ������:    releaseCardJudeg���п�ʱ�ж��Ƿ�ſ����ſ��Ƿ�����Ч��
  ����:      Administrator����ΰ
  ����:      2005.07.19
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function releaseCardJudge: Boolean;
var
  cardmanage:TCardManage;
  resint:SmallInt;
  cardId,PCardID:string;
  Cid:Integer;
begin
  Result:=True;
  if PrepareReadCardInfo=False then
  begin
    Result:=False;
    Exit;
  end;
  cardmanage := nil;
  try
    CardManage := TCardManage.Create;
    ResInt := CardManage.ReadExCardID(CardID);
    if ResInt <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�����׿���ʧ�ܣ��ÿ�û�г�ʼ����');
      Result := False;
      Exit;
    end;
    if Trim(cardId)='' then
      Cid:=0
    else
      Cid:=StrToInt(cardId);
    if Cid>0 then
    begin
      Context.GetDialogSystem.ShowMessage('�ÿ����׿����Ѿ����ڣ����һ���¿���');
      Result := False;
      Exit;
    end; 
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ��ÿ��Ѿ��𻵣�');
      Result := False;
      Exit;
    end;
  finally
    cardmanage.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  ������:    TCardManage.pubCard��������ģ��
  ����:      ����ΰ
  ����:      2005.08.08
  ����:      workviewIn, workviewOut: TWorkView������ͼ��traceCode:���״���
  ����ֵ:    String
-------------------------------------------------------------------------------}
function pubCard(workviewIn, workviewOut: TWorkView;
          wvRequest:TWVRequest;tradeCode:Integer): string;
var
  tradeCardNo:Integer;      //���׿���
  showCardNo:string;        //��ʾ����
  cardEndDate:string;       //��ʹ�ý�������
  limitType:Integer;        //��ʹ��Ȩ��
  custType:Integer;         //�ͻ����
  custName:string;          //�ͻ�����
  dutyNo:string;            //ְ�����
  cardID:string;            //���֤��
  depNo:string;             //���Ŵ���
  bookID:string;            //ͼ��֤��
  sex:string;               //�Ա�
  ID:string;                //ѧ����
  cardBalance:Real;         //�����
  cardPWD:string;           //������
  isFormation:Char;         //�Ƿ��ʽ����һ����

  backTradeID:Integer;      //��̨������ˮ��
  outMoney:LongInt;         //����ֵ
  re:Integer;
  PCM: TPublishCardMes;
  CardManage: TCardManage;
begin
  tradeCardNo:=workviewIn.fieldbyname('���׿���').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('��ʾ����').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('��������').Data.AsString;
  limitType:=workviewIn.fieldbyname('�շ�����').Data.AsInteger;
  custType:=workviewIn.fieldbyname('�ͻ�����').Data.AsInteger;
  custName:=workviewIn.fieldbyname('�ͻ�����').Data.AsString;
  dutyNo:='';
  cardID:=workviewIn.fieldbyname('���֤��').Data.AsString;
  depNo:=workviewIn.fieldbyname('���Ŵ���').Data.AsString;
  bookID:=workviewIn.fieldbyname('ͼ��֤��').Data.AsString;
  sex:=workviewIn.fieldbyname('�Ա�').Data.AsString;
  ID:=workviewIn.fieldbyname('ѧ����').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('����ֵ').Data.AsFloat;
  cardPWD:=workviewIn.fieldbyname('������').Data.AsString;
  isFormation := Char('N');
  outMoney:=StrToInt(FloatToStr(cardBalance * 100));
  backTradeID:=workviewIn.fieldbyname('��̨������ˮ��').Data.AsInteger;

  strcopy(@PCM.CardNo, PChar(IntToStr(tradeCardNo)));         //���׿���
  strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //��ʾ����
  strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //��ֹ����
  PCM.CardRightType := limitType;                             //�շ�����
  strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //�ͻ�����
  strcopy(@PCM.ucName, PChar(custName));                      //����
  strcopy(@PCM.ucDutyNo, PChar(dutyNo));                      //ְ��
  strcopy(@PCM.ucCertificateNo, PChar(cardID));               //���֤��
  strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //����
  strcopy(@PCM.ucLibraryNo, PChar(bookID));                   //ͼ��֤��
  strcopy(@PCM.ucSexNo, PChar(sex));                          //�Ա�
  strcopy(@PCM.ucCardNo, PChar(ID));                          //ѧ����
  PCM.Money := outMoney;                                      //�����
  strcopy(@PCM.ucPwd, PChar(cardPWD));                        //������
  PCM.isFormat := isFormation;                                //�Ƿ��ʽ����һ����
  re := 0;
  try
    re := CardManage.PublishACard(PCM);
  finally
    if re = 0 then
    begin
      Context.GetDialogSystem.ShowSuccess('д����Ϣ�ɹ������Ŀ���Ϊ:' +
        IntToStr(tradeCardNo));
      Result:=workviewIn.FieldByName('������Ϣ').Data.AsString;
    end
    else
    begin
      workviewOut.FieldByName('����ʶ').Data.SetInteger(tradeCardNo);
      workviewOut.FieldByName('��̨������ˮ��').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('������').Data.SetInteger(tradeCode);
      wvRequest.SendCommand;
      Context.GetDialogSystem.ShowSuccess('д��ʧ��:'+inttostr(re)+'--��״̬Ϊд��ʧ��״̬���벹д����Ϣ��');
      Result:='д��ʧ��:'+inttostr(re)+'--��״̬Ϊд��ʧ��״̬��'
    end;
  end;

end;

{-------------------------------------------------------------------------------
  ������:    PrepareReadCardInfo����ǰ׼������
  ����:      ����ΰ
  ����:      2005.08.31
  ����:      ��
  ����ֵ:    Boolean
-------------------------------------------------------------------------------}
function PrepareReadCardInfo: Boolean;
begin
  Result:=True;
  if not SmartCardPortStatus then
  begin
    raise Exception.Create('���ȴ򿪴��ڣ�');
    Result:=False;
  end;
  if not SmartCardAuthStatus then
  begin
    raise Exception.Create('����Ϊ��д����Ȩ��');
    Result:=False;
  end;

end;

{-------------------------------------------------------------------------------
  ������:    readCardNo��ȡ���ţ��������ʧ�ܣ�����0
  ����:      ����ΰ
  ����:      2005.08.31
  ����:      ��
  ����ֵ:    Integer
-------------------------------------------------------------------------------}
function readCardNo: string;
var
  cardmanage:TCardManage;
  resint:SmallInt;
  cardId,PCardID:string;
begin
  if PrepareReadCardInfo=False then
  begin
    Result := '0';
    Exit;
  end;
  cardmanage := nil;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ��ÿ��Ѿ��𻵣�');
      Result := '0';
      Exit;
    end;

    ResInt := CardManage.ReadExCardID(CardID);
    if ResInt <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('�����׿���ʧ�ܣ�');
      Result := '0';
      Exit;
    end
    else
    begin
      Result := cardId;
    end;
  finally
    cardmanage.Destroy;
  end;
end;
{-------------------------------------------------------------------------------
  ������:    readShowCarNo��ȡ��ʾ����
  ����:      ����ΰ
  ����:      2005.11.24
  ����:      ��
  ����ֵ:    string
-------------------------------------------------------------------------------}
function readShowCarNo: string;
var
  cardmanage:TCardManage;
  st: smallint;
  PCM: TPublishCardMes;
  PCardID:string;
begin
  if PrepareReadCardInfo=False then
    Exit;
  cardmanage := nil;
  try
    CardManage := TCardManage.Create;
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ�û�зſ���ÿ��Ѿ��𻵣�');
      Result := '0';
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������: ' + IntToStr(st));
      Exit;
    end
    else
    Result:=Copy(PCM.ShowCardNo,1,10);
  finally
    CardManage.Destroy;
  end;
end;

{*******************************************************************************
 ������Ȩ����غ�������������ʼ
 ����:      ����ΰ
 ����:      2007.01.24
*******************************************************************************}
function TCardManage.HaltCard: LongInt;
begin
  Result:=utcarddll.HaltCard();
end;

function TCardManage.InitCard(const showcardno: string): LongInt;
var
  errcode : integer;
begin
  if (showcardno = '') or (Length(showcardno)<>10) then
  begin
    Result:=InitNewCard(PInteger(@errcode),nil,nil);
  end
  else
    Result:=InitNewCard(PInteger(@errcode),PChar(showcardno),nil);
end;

function TCardManage.InitNewAuthCard(mainKey: PChar;
  flag: Integer): integer;
begin
  Result := utcarddll.InitNewAuthCard(mainKey,Byte(flag),nil);
end;

function TCardManage.PublishAuthCard(const PCM: TPublishCardMes): integer;
begin
  Result:= utcarddll.PublishAuthCard(PCM);
end;

function TCardManage.ReadAuthCardInfo(const PCM: TPublishCardMes): Integer;
begin
  Result:=utcarddll.ReadAuthCardInfo(pcm);
end;

function TCardManage.ResetNewAuthCard(err_code: Integer): integer;
begin
  Result:=utcarddll.ResetNewAuthCard(err_code,nil);
end;

function TCardManage.SMT_ModifyDeadLineDateAndFlag(sDate: string;
  flag: Integer): integer;
begin
  Result := utcarddll.SMT_ModifyDeadLineDateAndFlag(PChar(sDate),Byte(flag));
end;

function TCardManage.SMT_ReadAuthorWorkKeyAndFlag(var mainKey: string;
  var flag: Byte): integer;
var
  ResInt: LongInt;
  keybuf : array[0..7] of Char;
begin
  Result := 1;
  ResInt := utcarddll.SMT_ReadAuthorWorkKeyAndFlag(PChar(@keybuf),@flag);
  mainKey:=keybuf;
  if ResInt <> 0 then
    Exit;
  Result := 0;
end;

function TCardManage.SMT_SetAuthNormalFlagByBlkVerion(ver: PChar): Integer;
begin
  Result:=utcarddll.SMT_SetAuthNormalFlagByBlkVerion(ver);
end;

function TCardManage.CheckForCard: longint;
begin
  result := SMT_CheckForCard;
end;
{*******************************************************************************
 ������Ȩ����غ���������������
*******************************************************************************}


end.
