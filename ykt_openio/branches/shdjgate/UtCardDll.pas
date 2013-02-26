{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation

    <Unit>UtCardDll
    <What>实现硬件厂商提供的卡户管理的dll封装
    <Written By> Wang SuNa (王苏娜)

    <History>-------------------------------------------------------------------
    2004年12月14日 冯君整理
    2006-07-20 把所有底层的调用封装成carddll，统一调用
*******************************************************************************}

unit UtCardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
    KSFrameWorks,WorkViews,KSClientConsts,WVCmdReq,utcarddll;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //当前登录卡片某个扇区是使用KEY-A或是KEY-B
  CurrentControlBit = 'FF078069';
  DefaultKeyA = 'FFFFFFFFFFFF';
  DefaultKeyB = 'FFFFFFFFFFFF';

type
  PSmallInt = ^SmallInt;
  
  TPublishCardMes = packed record
    ShowCardNo: array[1..11] of char;       //用户卡显示卡号
    CardNo: array[1..8] of char;            //用户卡交易卡号
    DeadLineDate: array[1..9] of Char;      //用户卡使用截止日期
    CardRightType: longint;                 //权限类型（1--254）收费类别
    ucName: array[1..9] of Char;            //姓名
    ucDutyNo: array[1..9] of Char;          //职务代码
    ucCertificateNo: array[1..21] of Char;  //身份证号码
    ucDepartmentNo: array[1..11] of Char;   //单位编号
    ucIdentifyNo: array[1..5] of Char;      //客户类别
    ucSexNo: array[1..2] of Char;           //性别代码
    ucCardNo: array[1..21] of Char;         //工号或学号
    ucPwd: array[1..6] of Char;             //密码
    ucLibraryNo: array[1..21] of Char;      //图书证号
    Money: longint;                         //金额（分）
    isFormat: Char;                         //是否格式化第一扇区
  end;

type
  LOOPPURSEINFO = packed record
    RemainMoney: DWORD;                     // 电子钱包余额
    DealTimes: WORD;                        // 用户卡交易流水号
    DealYear: BYTE;                         // 交易日期
    DealMonth: BYTE;
    DealDay: BYTE;
    DealHour: BYTE;
    DealMin: BYTE;
    DealTimes_CurTime: BYTE;                // 累计交易次数(当前时间段内)
    DealTimes_CurDay: BYTE;                 // 累计交易次数(当日内)
  end;

type
  TCardInfo = packed record
    DeadLineDate: array[1..9] of char;      //用户卡使用截止日期
    CardRightType: longint;                 //用户卡使用权限类型（1--254）
    ucName: array[1..9] of Char;            //姓名
    ucDutyNo: array[1..9] of Char;          //职务代码
    ucCertificateNo: array[1..21] of Char;  //证件号码
    ucDepartmentNo: array[1..11] of Char;   //部门编号
    ucIdentifyNo: array[1..21] of Char;     //身份代码
    ucSexNo: array[1..2] of Char;           //性别代码
    ucCardNo: array[1..21] of Char;         //卡号（工号或学号）
  end;

//卡检测SMT_CheckForCard();
//返回1表示裸卡，2表示初始化过的卡, 3表示不可识别的卡
function SMT_CheckForCard(): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_CheckForCard';

//初始化串口 *
function ConnectMF(port: longint; baud: longint): longint;
  stdcall;far; external 'CardDLL.dll' name 'ConnectMF';

//读卡器鸣声
function SMT_ControlBuzzer: longint;
  stdcall;far; external 'CardDLL.dll' name 'ControlBuzzer';

//读授权卡
function DLLReadCardMainKey(OutMainKey: PByte;swith:SmallInt;flag:PSmallInt):LongInt;
  stdcall;far; external 'CardDLL.dll' name 'ReadCardMainKey' ;

//设置卡片为正常卡（解挂、解冻）
function SMT_SetNormalFlag: longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetNormalFlag';

//设置卡片为正常卡（解挂，解冻）并设版本号2005-06-08加入
function SMT_SetNormalFlagByVer(ver:PChar): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetNormalFlagByBlkVerion';

//回收卡
function SMT_ClearCard: longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ClearCard';

//读写器授权 *
function ReaderAuthor(MoneyBuf: pchar): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_AutoDll';

function Load_Dll: longint;
  stdcall;far; external 'CardDLL.dll' name 'Load_Dll';

// 调用关闭串口 *
function CloseMF: SmallInt;
  stdcall;far; External 'CardDll.dll' name 'CloseMF';

//发行卡   *
function PublishCard(const PCM: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'PublishCard';

//读卡信息   *
function ReadCardInfo(const PCM: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardInfo';

//读卡序列号 *
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'RequestCard';

//用户卡存钱
function PacketAddMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external 'CardDLL.dll' name 'SMT_PacketAddMomey';

//用户卡取款 *
function PacketDelMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external 'CardDLL.dll' name 'SMT_PacketDelMomey';

//读用户卡消费信息
function ReadPacketInfo(const LPI: LOOPPURSEINFO): longint;
  stdcall;external 'CardDLL.dll' name 'ReadPacketInfo';

//用户卡个人密码读取  *
function ReadPersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardPwd';

//用户卡个人密码更改 *
function ChangePersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'WriteCardPwd';

//读交易卡号  *
function ReadExchCardNo(ExchCardNo: PInteger): longint;
  stdcall;external 'CardDLL.dll' name 'ReadCardNO';

//错误信息 *
function GetLastErrMsg(errcode:pointer;msg:pchar ):longint;
  stdcall;external 'CardDLL.dll' name 'GetLastErrMsg';

//更新卡信息   *
function UpdateCardInfo(const CardInfo: TPublishCardMes): longint;
  stdcall;external 'CardDLL.dll' name 'UpdateCardInfo';
//发行授权母卡 *
function CreateMonKeyCard(nKey1: longint; nKey2: longint): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_CreateMonKeyCard';

//回收授权母卡  *
function ClearMonKeyCard: smallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearMonKeyCard';
  
//发行消费密钥子卡  *
function PublishComsumeChildCard(year, month, day, hour: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'PublishComsumeChildCard';

//回收消费密钥子卡  *
function ClearComsumeChildCard: SmallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearComsumeChildCard';

//发行充值密钥子卡  *
function PublishAddMoneyChildCard(year, month, day, hour: pchar): longint;
  stdcall;external 'CardDLL.dll' name 'PublishAddMoneyChildCard';

//回收充值密钥子卡  *
function ClearAddMoneyChildCard: SmallInt;
  stdcall;far; External 'CardDLL.dll' name 'SMT_ClearAddMoneyChildCard';

function get_check_char(InCheckSumString: PChar): longint;
  stdcall;far; external 'desdll.dll' name 'get_check_char';

function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

function SleepCard: longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

//更新交易卡号
function SMT_ChangeDealCardNo(dealCardNo:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ChangeDealCardNo';

//更新卡余额
function SMT_PacketSetMoney(nPacketNo,dealCardNo:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_PacketSetMoney';

//写卡交易次数
function SMT_SetTxCnt(nPacketNo,tx_cnt:LongInt): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_SetTxCnt';
//读卡黑名单版本
function SMT_ReadBlackNameListVersion(flag:Pointer;version:string): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_ReadBlackNameListVersion';
//清空钱包信息
function SMT_PacketReset(PackNo:Integer): longint;
  stdcall;far; external 'CardDLL.dll' name 'SMT_PacketReset';
//读取卡信息
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

//初始化卡函数
function InitNewCard(err_code:PInteger;showcardno:PChar;test:Pointer):longint;
  stdcall;far; external 'CardDLL.dll' name 'InitNewCard';

function HaltCard: LongInt;
  stdcall;far;external 'CardDLL.dll' name 'HaltCard';

//发行授权卡--------------------------------------------------------------------
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
    //卡检测函数
    function CheckForCard: longint;
    function Load_Dll: longint;
    //读卡器鸣声
    function ControlBuzzer:longint;
    //解挂、解冻卡
    function SetNormalFlag: longint;
    //解挂，解冻
    function SetNormalFlagbyVer(ver:PChar):LongInt;
    //回收卡
    function ClearCard: longint;
    //sleep
    function SleepCardByTime: longint;
    //初始化串口
    function IniSerialPort(CommId: longint; BaudRate: longint): smallint;
    //关闭串口
    function CloseSerialPort: smallint;
    //读写器授权
    function ReadMachineAuth(MoneyBuf: pchar): smallint;
    //读卡物理序列号
    function ReadCardPhyID(var CardIdString: string): smallint;
    //用户卡个人密码读取
    function ReadCardPsw: string;
    //读用户卡消费信息
    function ReadCardConsumeInfo(var LPI: LOOPPURSEINFO; nPacketNo: smallint):boolean;
    //读卡基本信息
    function ReadCardInfo(var PCM: TPublishCardMes): smallint;
    //读交易卡号
    function ReadExCardID(var ExCardId: string): smallint;
    //发行卡
    function PublishACard(const PCM: TPublishCardMes): integer;
    //密码更改
    function ChangeCardPsw(PassWord: string): smallint;
    //取款
    function DelCardMoney(m: string): boolean;
    //加款
    function AddCardMoney(m: string): boolean;
    //更新卡基本信息
    function UpdateCardBasicInfo(var CardInfo: TPublishCardMes): integer;
    //读取卡中工作密钥
    function ReadCardMainkey(var OutMainKey: string;flag:PSmallInt): longint;

    {将一段内存转化为一个十六进制字符串}
    function ConvertPCharToHexStr(BInChar: PChar; StringLength: longint; var FResultString: string; var ErrorMsg: string): Longint;
    function ConvertHexStrToPChar(BInString: string; StringLength: longint; var FResultChar: PChar; var ErrorMsg: string): Longint;

    function ReadSectionCardData(Cardno: string; Sectionno: longint; SectionKey: Pchar; var Data1: string; var Data2: string; var Data3: string; var Data4: string; var Data5:string;var Data6: string): longint;

    {判断是否可以访问默认的未初始化的授权卡的指定卡片的指定扇区}
    function CanLoginSelSection(FCardno: string; FSectionNo: longint;FSectionKey: Pchar; var ErrorMsg: string): Longint;

    {读取卡信息}
    function ReaderBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):longint;

    //更新交易卡号
    function ChangeDealCardNo(dealCardno:LongInt):LongInt;

    //更新卡余额
    function PacketSetMoney(m:string):Boolean;

    //更新卡的交易次数
    function changeTradeNum(Num:LongInt): LongInt;

    //读卡黑名单版本
    function readCardBlackVer(flag:Pointer;version:string): LongInt;

    //清空钱包信息
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
//检查输入金额是否符合标准
function Checkedt(key:Char;dot:string): Boolean;

//返回值信息提取
function getReturn(s1:string;wv:TWorkView):string ;

//发行卡时判断是否放卡，放卡是否是有效卡
function releaseCardJudge: Boolean;

//发行卡公用模块
function pubCard(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;tradeCode:Integer): string;

//检查输入的是否为数字
function inputNum(key:Char): Boolean;

//格式化卡显示结果
function formatCardShow(bCard:Byte):string;

//读卡准备
function PrepareReadCardInfo: Boolean;

//读取卡号
function readCardNo: string;

//读显示卡号
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

//更新卡余额
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
    ErrorMsg := '物理ID号无法读取！';
    ShowMessage(ErrorMsg);
    Result := -1;
    exit;
  end;

  if FCardno <> Trim(TmpStr) then
  begin
    ErrorMsg := '当前读卡器上所放的卡片不正确！';
    Result := -1;
    Exit;
  end;

  if SMT_Login_With_UserKey(FSectionNo, FSectionKey, CurrentUserKeyA) <> 0 then
  begin
    Result := -1;
    ErrorMsg := '扇区：' + Inttostr(FSectionNo) + '的Key验证失败！';
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
  //0:关闭串口成功； -1：关闭串口失败；-2：软件动态库调用失败
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
    ErrorMsg := '十六进制串:' + BInString + '转换到内存块出错！';
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
    ErrorMsg := '内存信息转换到十六进制字符串过程出错！';
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
  // 0: 打开串口成功；
  //-1：硬件动态库调用失败；
  //-2：读写器初始化失败；
  //-3：软件动态库调用失败
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

//设置卡为正常状态，并写版本号
function TCardManage.SetNormalFlagbyVer(ver: PChar): LongInt;
begin
  Result:=SMT_SetNormalFlagByVer(ver);
end;

//更新交易卡号
function TCardManage.ChangeDealCardNo(dealCardno: LongInt): LongInt;
begin
  Result := SMT_ChangeDealCardNo(dealCardno);
end;

//更新卡的交易次数
function TCardManage.changeTradeNum(Num:LongInt): LongInt;
begin
  Result := SMT_SetTxCnt(1,Num);
end;

//读取卡黑名单版本
function TCardManage.readCardBlackVer(flag:Pointer;version:string): LongInt;
begin
  Result := SMT_ReadBlackNameListVersion(flag,version);
end;

//清空钱包信息
function TCardManage.clearMoneyInfo(packNo: Integer): LongInt;
begin
  Result := SMT_PacketReset(packNo);
end;

{-------------------------------------------------------------------------------
  过程名:    Checkedt检查数字输入框输入内容是否正确
  作者:      Administrator
  日期:      2005.07.19
  参数:      key:Char;dot:string
  返回值:    Boolean
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
  过程名:    inputNum用此校验只能输入数字
  作者:      韩纪伟
  日期:      2005.08.10
  参数:      key:Char
  返回值:    Boolean
-------------------------------------------------------------------------------}
function inputNum(key:Char): Boolean;
begin
  if (Key in ['0'..'9',#8,#13]) then
    Result:=True
  else
    result:=False;
end;

{-------------------------------------------------------------------------------
  过程名:    formatCardShow格式化卡显示结果
  作者:      韩纪伟
  日期:      2005.08.10
  参数:      bCard:Byte
  返回值:    无
-------------------------------------------------------------------------------}
function formatCardShow(bCard:Byte):string;
begin
  if length(format('%d', [bCard])) = 1 then
    Result := '0' + format('%d', [bCard])
  else
    Result :=format('%2d', [bCard]);
end;

{-------------------------------------------------------------------------------
  过程名:    getReturn调用后台返回信息
  作者:      Administrator韩纪伟
  日期:      2005.07.19
  参数:      s1:string;wv:TWorkView
  返回值:    string
-------------------------------------------------------------------------------}
function getReturn(s1:string;wv:TWorkView):string ;
begin
  ConText.GetDialogSystem.showmessage(s1+wv.FieldByName('返回信息').Data.AsString);
end;

{-------------------------------------------------------------------------------
  过程名:    releaseCardJudeg发行卡时判断是否放卡，放卡是否是有效卡
  作者:      Administrator韩纪伟
  日期:      2005.07.19
  参数:      无
  返回值:    Boolean
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
      Context.GetDialogSystem.ShowMessage('读交易卡号失败，该卡没有初始化！');
      Result := False;
      Exit;
    end;
    if Trim(cardId)='' then
      Cid:=0
    else
      Cid:=StrToInt(cardId);
    if Cid>0 then
    begin
      Context.GetDialogSystem.ShowMessage('该卡交易卡号已经存在，请放一张新卡！');
      Result := False;
      Exit;
    end; 
    if CardManage.ReadCardPhyID(PCardID) <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('读卡序列号失败，该卡已经损坏！');
      Result := False;
      Exit;
    end;
  finally
    cardmanage.Destroy;
  end;
end;

{-------------------------------------------------------------------------------
  过程名:    TCardManage.pubCard发卡公用模块
  作者:      韩纪伟
  日期:      2005.08.08
  参数:      workviewIn, workviewOut: TWorkView工作视图，traceCode:交易代码
  返回值:    String
-------------------------------------------------------------------------------}
function pubCard(workviewIn, workviewOut: TWorkView;
          wvRequest:TWVRequest;tradeCode:Integer): string;
var
  tradeCardNo:Integer;      //交易卡号
  showCardNo:string;        //显示卡号
  cardEndDate:string;       //卡使用截至日期
  limitType:Integer;        //卡使用权限
  custType:Integer;         //客户类别
  custName:string;          //客户姓名
  dutyNo:string;            //职务代码
  cardID:string;            //身份证号
  depNo:string;             //部门代码
  bookID:string;            //图书证号
  sex:string;               //性别
  ID:string;                //学工号
  cardBalance:Real;         //卡余额
  cardPWD:string;           //卡密码
  isFormation:Char;         //是否格式化第一扇区

  backTradeID:Integer;      //后台交易流水号
  outMoney:LongInt;         //出卡值
  re:Integer;
  PCM: TPublishCardMes;
  CardManage: TCardManage;
begin
  tradeCardNo:=workviewIn.fieldbyname('交易卡号').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('显示卡号').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('截至日期').Data.AsString;
  limitType:=workviewIn.fieldbyname('收费类型').Data.AsInteger;
  custType:=workviewIn.fieldbyname('客户类型').Data.AsInteger;
  custName:=workviewIn.fieldbyname('客户名称').Data.AsString;
  dutyNo:='';
  cardID:=workviewIn.fieldbyname('身份证号').Data.AsString;
  depNo:=workviewIn.fieldbyname('部门代码').Data.AsString;
  bookID:=workviewIn.fieldbyname('图书证号').Data.AsString;
  sex:=workviewIn.fieldbyname('性别').Data.AsString;
  ID:=workviewIn.fieldbyname('学工号').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('出卡值').Data.AsFloat;
  cardPWD:=workviewIn.fieldbyname('卡密码').Data.AsString;
  isFormation := Char('N');
  outMoney:=StrToInt(FloatToStr(cardBalance * 100));
  backTradeID:=workviewIn.fieldbyname('后台交易流水号').Data.AsInteger;

  strcopy(@PCM.CardNo, PChar(IntToStr(tradeCardNo)));         //交易卡号
  strcopy(@PCM.ShowCardNo, PChar(showCardNo));                //显示卡号
  strcopy(@PCM.DeadLineDate, PChar(cardEndDate));             //截止日期
  PCM.CardRightType := limitType;                             //收费类型
  strcopy(@PCM.ucIdentifyNo, PChar(IntToStr(custType)));      //客户类型
  strcopy(@PCM.ucName, PChar(custName));                      //姓名
  strcopy(@PCM.ucDutyNo, PChar(dutyNo));                      //职务
  strcopy(@PCM.ucCertificateNo, PChar(cardID));               //身份证号
  strcopy(@PCM.ucDepartmentNo, PChar(depNo));                 //部门
  strcopy(@PCM.ucLibraryNo, PChar(bookID));                   //图书证号
  strcopy(@PCM.ucSexNo, PChar(sex));                          //性别
  strcopy(@PCM.ucCardNo, PChar(ID));                          //学工号
  PCM.Money := outMoney;                                      //卡余额
  strcopy(@PCM.ucPwd, PChar(cardPWD));                        //卡密码
  PCM.isFormat := isFormation;                                //是否格式化第一扇区
  re := 0;
  try
    re := CardManage.PublishACard(PCM);
  finally
    if re = 0 then
    begin
      Context.GetDialogSystem.ShowSuccess('写卡信息成功！您的卡号为:' +
        IntToStr(tradeCardNo));
      Result:=workviewIn.FieldByName('返回信息').Data.AsString;
    end
    else
    begin
      workviewOut.FieldByName('卡标识').Data.SetInteger(tradeCardNo);
      workviewOut.FieldByName('后台交易流水号').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('交易码').Data.SetInteger(tradeCode);
      wvRequest.SendCommand;
      Context.GetDialogSystem.ShowSuccess('写卡失败:'+inttostr(re)+'--卡状态为写卡失败状态，请补写卡信息！');
      Result:='写卡失败:'+inttostr(re)+'--卡状态为写卡失败状态！'
    end;
  end;

end;

{-------------------------------------------------------------------------------
  过程名:    PrepareReadCardInfo读卡前准备条件
  作者:      韩纪伟
  日期:      2005.08.31
  参数:      无
  返回值:    Boolean
-------------------------------------------------------------------------------}
function PrepareReadCardInfo: Boolean;
begin
  Result:=True;
  if not SmartCardPortStatus then
  begin
    raise Exception.Create('请先打开串口！');
    Result:=False;
  end;
  if not SmartCardAuthStatus then
  begin
    raise Exception.Create('请先为读写器授权！');
    Result:=False;
  end;

end;

{-------------------------------------------------------------------------------
  过程名:    readCardNo读取卡号，如果读卡失败，返回0
  作者:      韩纪伟
  日期:      2005.08.31
  参数:      无
  返回值:    Integer
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
      context.GetDialogSystem.ShowMessage('读卡序列号失败，该卡已经损坏！');
      Result := '0';
      Exit;
    end;

    ResInt := CardManage.ReadExCardID(CardID);
    if ResInt <> 0 then
    begin
      Context.GetDialogSystem.ShowMessage('读交易卡号失败！');
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
  过程名:    readShowCarNo读取显示卡号
  作者:      韩纪伟
  日期:      2005.11.24
  参数:      无
  返回值:    string
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
      context.GetDialogSystem.ShowMessage('读卡序列号失败，没有放卡或该卡已经损坏！');
      Result := '0';
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('读卡信息失败！错误号: ' + IntToStr(st));
      Exit;
    end
    else
    Result:=Copy(PCM.ShowCardNo,1,10);
  finally
    CardManage.Destroy;
  end;
end;

{*******************************************************************************
 发行授权卡相关函数－－－－开始
 作者:      韩纪伟
 日期:      2007.01.24
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
 发行授权卡相关函数－－－－结束
*******************************************************************************}


end.
