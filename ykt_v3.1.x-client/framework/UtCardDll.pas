{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation

    <Unit>UtCardDll
    <What>实现硬件厂商提供的卡户管理的dll封装
    <Written By> Wang SuNa (王苏娜)

    <History>-------------------------------------------------------------------
    2004年12月14日 冯君整理
    2006-07-20 把所有底层的调用封装成carddll，统一调用
    20080711  韩纪伟整理，增加水控相关函数，
              并把单元文件专业到framework下，实现所有包统一调用
*******************************************************************************}

unit UtCardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
    KSFrameWorks,WorkViews,KSClientConsts,WVCmdReq;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //当前登录卡片某个扇区是使用KEY-A或是KEY-B
  CurrentControlBit = 'FF078069';
  DefaultKeyA = 'FFFFFFFFFFFF';
  DefaultKeyB = 'FFFFFFFFFFFF';
  smlPacketNo3 = 4;
  smlPacketNo2 = 3;
  SmlPacketNo = 2;
  bgPacketNo = 1;
  Carddll = 'CardDLL.dll';
  desDll = 'desdll.dll';

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
    DealTimes: WORD;                        // 交易次数
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
  
//水控相关定义结构体------------------------------------------------------------
// 当前权限的费率个数
type
  TFeeRate = packed record
  time_ladder :Byte ;				                              // 时间阶梯
	deduct_time :Byte ;				                              // 扣费的单位时间，以秒为单位
	deduct_fee :Byte ;				                              // 扣费的单位金额，以分为单位
  end;


// 当前权限的费率个数
  TFeeRightNo = packed record
	right_flag : SHORT;					                            // 权限标志, 1打开, 0关闭
	right_num : SHORT;					                            // 传入当前权限下的费率个数
	fee_rate : array[1..5] of TFeeRate;				              // 最大设置为5个
  end;
  
// 费率卡结构说明
  TFeeRateCardInfo = packed record
	water_card_flag : array[1..5] of Byte;			            // 水控卡标志
	packet_num : Char;					                            // 水控钱包号
	main_work_key : array[1..9] of Byte;			              // 主工作密钥(明文)
	packet_work_key : array[1..9] of Byte;			            // 小钱包工作密钥(明文)
  work_model:Byte;                                        // 工作模式
  water_packet_limit : Integer;				                    // 水控钱包限额-----
	transfer_limit : Integer;					                      // 水控转账限额-----
	data_length : array[1..3] of Byte;				              // 数据长度
	check_crc : array[1..2] of Byte;				                // 效验字节
	fee_right_num : array[1..256] of TFeeRightNo;	          // 设置费率的个数
  end;
  PFeeRateCardInfo = ^TFeeRateCardInfo;

  Tcollect_balance = packed record
  devId :array[1..9] of Char;
  sum_balance :Double;
  end;
  Pcollect_balance = ^Tcollect_balance;
//水控结构体定义相关end---------------------------------------------------------

//卡检测SMT_CheckForCard();
//返回1表示裸卡，2表示初始化过的卡, 3表示不可识别的卡
function SMT_CheckForCard(): longint;
  stdcall;far; external Carddll name 'SMT_CheckForCard';

//初始化串口 *
function ConnectMF(port: longint; baud: longint): longint;
  stdcall;far; external Carddll name 'ConnectMF';

//读卡器鸣声
function SMT_ControlBuzzer: longint;
  stdcall;far; external Carddll name 'ControlBuzzer';

//读授权卡
function DLLReadCardMainKey(OutMainKey: PByte;swith:SmallInt;flag:PSmallInt):LongInt;
  stdcall;far; external Carddll name 'ReadCardMainKey' ;

//设置卡片为正常卡（解挂、解冻）
function SMT_SetNormalFlag: longint;
  stdcall;far; external Carddll name 'SMT_SetNormalFlag';

//设置卡片为正常卡（解挂，解冻）并设版本号2005-06-08加入
function SMT_SetNormalFlagByVer(ver:PChar): longint;
  stdcall;far; external Carddll name 'SMT_SetNormalFlagByBlkVerion';

//回收卡
function SMT_ClearCard: longint;
  stdcall;far; external Carddll name 'SMT_ClearCard';

//读写器授权 *
function ReaderAuthor(MoneyBuf: pchar): longint;
  stdcall;far; external Carddll name 'SMT_AutoDll';

function Load_Dll: longint;
  stdcall;far; external Carddll name 'Load_Dll';

// 调用关闭串口 *
function CloseMF: SmallInt;
  stdcall;far; External Carddll name 'CloseMF';

//发行卡   *
function PublishCard(const PCM: TPublishCardMes): longint;
  stdcall;external Carddll name 'PublishCard';

//读卡信息   *
function ReadCardInfo(const PCM: TPublishCardMes): longint;
  stdcall;external Carddll name 'ReadCardInfo';

//读卡序列号 *
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint;
  stdcall;external Carddll name 'RequestCard';

//用户卡存钱
function PacketAddMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external Carddll name 'SMT_PacketAddMomey';

//用户卡取款 *
function PacketDelMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external Carddll name 'SMT_PacketDelMomey';

//读用户卡消费信息
function ReadPacketInfo(const LPI: LOOPPURSEINFO): longint;
  stdcall;external Carddll name 'ReadPacketInfo';

//用户卡个人密码读取  *
function ReadPersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external Carddll name 'ReadCardPwd';

//用户卡个人密码更改 *
function ChangePersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external Carddll name 'WriteCardPwd';

//读交易卡号  *
function ReadExchCardNo(ExchCardNo: PInteger): longint;
  stdcall;external Carddll name 'ReadCardNO';

//错误信息 *
function GetLastErrMsg(errcode:pointer;msg:pchar ):longint;
  stdcall;external Carddll name 'GetLastErrMsg';

//更新卡信息   *
function UpdateCardInfo(const CardInfo: TPublishCardMes): longint;
  stdcall;external Carddll name 'UpdateCardInfo';
//发行授权母卡 *
function CreateMonKeyCard(nKey1: longint; nKey2: longint): longint;
  stdcall;far; external Carddll name 'SMT_CreateMonKeyCard';

//回收授权母卡  *
function ClearMonKeyCard: smallInt;
  stdcall;far; External Carddll name 'SMT_ClearMonKeyCard';
  
//发行消费密钥子卡  *
function PublishComsumeChildCard(year, month, day, hour: pchar): longint;
  stdcall;external Carddll name 'PublishComsumeChildCard';

//回收消费密钥子卡  *
function ClearComsumeChildCard: SmallInt;
  stdcall;far; External Carddll name 'SMT_ClearComsumeChildCard';

//发行充值密钥子卡  *
function PublishAddMoneyChildCard(year, month, day, hour: pchar): longint;
  stdcall;external Carddll name 'PublishAddMoneyChildCard';

//回收充值密钥子卡  *
function ClearAddMoneyChildCard: SmallInt;
  stdcall;far; External Carddll name 'SMT_ClearAddMoneyChildCard';

function get_check_char(InCheckSumString: PChar): longint;
  stdcall;far; external 'desdll.dll' name 'get_check_char';

function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

function SleepCard: longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

//更新交易卡号
function SMT_ChangeDealCardNo(dealCardNo:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_ChangeDealCardNo';

//更新卡余额
function SMT_PacketSetMoney(nPacketNo,dealCardNo:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_PacketSetMoney';

//更新卡余额2
function SMT_PacketSetMoney2(nPacketNo,dealCardNo,nCnt:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_PacketSetMoney2';

//读取单次消费额(max_per_count),日累计消费额(max_per_day)
function SMT_ReadConsumeLimit(max_per_count,max_per_day:PInteger): longint;
  stdcall;far; external Carddll name 'ReadConsumeLimit';

//写入单次消费额(max_per_count),日累计消费额(max_per_day)
function SMT_SetConsumeLimit(max_per_count,max_per_day:LongInt): longint;
  stdcall;far; external Carddll name 'SetConsumeLimit';

//卡的锁定和解锁(0x00 表示正常， 0xFF表示锁定)
function SMT_ReadCardLockFlag(lock_flag:PInteger): longint;
  stdcall;far; external Carddll name 'ReadCardLockFlag';

//动态库版本号
procedure YKT_get_version(ver:PChar);
  stdcall;far; external Carddll name 'YKT_get_version';

function SMT_SetCardLockFlag(lock_flag:LongInt): longint;
  stdcall;far; external Carddll name 'SetCardLockFlag';

//更新卡有效期
function SMT_ChangeDeadLineDate(ucDeadLineDate:PChar): longint;
  stdcall;far; external Carddll name 'SMT_ChangeDeadLineDate';

//写卡交易次数
function SMT_SetTxCnt(nPacketNo,tx_cnt:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_SetTxCnt';
//写补助批次号
function SMT_WriteSubsidy(nPacketNo,batch_no:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_WriteSubsidy';

//读卡黑名单版本
function SMT_ReadBlackNameListVersion(flag:Pointer;version:string): longint;
  stdcall;far; external Carddll name 'SMT_ReadBlackNameListVersion';
//清空钱包信息
function SMT_PacketReset(PackNo:Integer): longint;
  stdcall;far; external Carddll name 'SMT_PacketReset';
//读取卡信息
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

//初始化卡函数
function InitNewCard(err_code:PInteger;showcardno:PChar;test:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewCard';

function HaltCard: LongInt;
  stdcall;far;external Carddll name 'HaltCard';

//发行授权卡--------------------------------------------------------------------
function InitNewAuthCard(mainKey:PChar;flag:Byte;callBack:Pointer): LongInt;
  stdcall;external Carddll name 'InitNewAuthCard';
function SMT_ModifyDeadLineDateAndFlag(mainKey:PChar;flag:Byte): LongInt;
  stdcall;external Carddll name 'SMT_ModifyDeadLineDateAndFlag';
function SMT_ReadAuthorWorkKeyAndFlag(mainKey:PChar;flag:PByte): LongInt;
  stdcall;external Carddll name 'SMT_ReadAuthorWorkKeyAndFlag';
function PublishAuthCard(const PCM: TPublishCardMes) : LongInt;
  stdcall;external Carddll name 'PublishAuthCard';
function ResetNewAuthCard(err_code:Integer;callBack:Pointer) : LongInt;
  stdcall;external Carddll name 'ResetNewAuthCard';
function SMT_SetAuthNormalFlagByBlkVerion(ver:PChar) : LongInt;
  stdcall;far;external Carddll name 'SMT_SetAuthNormalFlagByBlkVerion';
function ReadAuthCardInfo(const PCM: TPublishCardMes) : LongInt;
  stdcall;external Carddll name 'ReadAuthCardInfo';
//------------------------------------------------------------------------------
//水控相关----------------------------------------------------------------------
//发行采集卡
function InitNewCollectionCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewCollectionCard';

//回收采集卡和费率设置卡
function RefineWaterCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'RefineWaterCard';

//初始化费率设置卡
function InitNewFeeRateCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewFeeRateCard';

//发行费率设置卡
function PublishFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;
  stdcall;far; external Carddll name 'PublishFeeRateCard';

//读取费率设置卡
function ReadFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;
  stdcall;far; external Carddll name 'ReadCollectCardInfo';

//读钱包信息
function ReadBalance(nPacketNo:Integer;nBalance:pInteger;nCnt:PInteger):longint;
  stdcall;far; external Carddll name 'ReadBalance';

//读采集卡信息
function CollectionCardReceiveData(err_code:PInteger;collectBalance:Pcollect_balance;collect_count:PInteger):longint;
  stdcall;far; external Carddll name 'CollectionCardReceiveData';

//读采集卡信息
function SMT_ClearCollectCardData:longint;
  stdcall;far; external Carddll name 'SMT_ClearCollectCardData';

//卡信息类型
function ReadWaterCardFlag(WaterCardFlag:pByte):longint;
  stdcall;far; external Carddll name 'SMT_ReadWaterCardFlag';

//水控相关end-------------------------------------------------------------------
//加密电子钱包
function YKT_encrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const pwd:pchar;mpwd:pchar): LongInt;
  stdcall;far;external Carddll name 'YKT_encrypt_cardpwd';
//解密电子钱包
function YKT_decrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const mpwd:pchar;pwd:pchar): LongInt;
  stdcall;far;external Carddll name 'YKT_decrypt_cardpwd';

//******************************************************************************

//语音报价器--------------(保留)
function dsbdll(ComPort:integer;OutString:string):integer;stdcall;external 'Tdbjq.dll';

function calc_oper_pwd(const oper_code :pChar;const pwd:pchar;text:pchar): LongInt;
  stdcall;far;external desDll name 'calc_oper_pwd';

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
    function PacketSetMoney(m:string):Integer;

    //更新卡余额并判断是否更新成功
    function packetSetMoneyAndChk(m:string;inMoney:Integer): Integer;

    //更新卡余额2
    function PacketSetMoney2(money,ncnt:Integer):LongInt;

    //读取单次消费次数和日累计消费次数
    function ReadConsumeLimit(var max_per_count,max_per_day:Integer): LongInt;

    //设置单次消费次数和日累计消费次数
    function SetConsumeLimit(max_per_count,max_per_day:Integer): LongInt;

    //读取卡的锁定状态
    function ReadCardLockFlag(var lock_flag:Integer): LongInt;

    //设置卡的锁定状态
    function SetCardLockFlag(lock_flag:Integer): LongInt;

    //读取动态库版本号
    procedure readCardDllVer(var ver:string);
    
    //更新卡有效期
    function ChangeDeadLineDate(dealDate:string): LongInt;

    //更新卡的交易次数
    function changeTradeNum(Num:LongInt): LongInt;

    //读取卡余额信息
    function  readCardMoney(packNo:Integer): Integer;


    //更新卡批次号
    function changePatchNo(Num:LongInt): LongInt;

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

    //水控相关******************************************************************
    //初始化采集卡
    function InitNewCollectionCard(err_code:Integer): LongInt;

    //回收采集卡和费率设置卡
    function RefineWaterCard(err_code:Integer): LongInt;

    //初始化费率设置卡
    function InitNewFeeRateCard(err_code:Integer): LongInt;

    //发行费率设置卡
    function PublishFeeRateCard(feeRateCardInfo : PFeeRateCardInfo): LongInt;

    function ReadFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;

    function ReadBalance(nPacketNo:Integer;nBalance:pInteger;nCnt:pInteger):longint;

    function setCardMoney(nPacketNo:Integer;money:Integer): LongInt;

    function CollectionCardReceiveData(err_code:PInteger;collectBalance: Pcollect_balance;collect_count:PInteger):longint;

    function ClearCollectCardData:longint;

    function ReadWaterCardFlag(WaterCardFlag:PByte):longint;
    //水控相关end***************************************************************
    function encryptCardpwd(cut_id:Integer;const seedKey,pwd:pchar;var mpwd:string): longint;
    function decryptCardpwd(cut_id:Integer;const seedKey,mpwd:pchar;var pwd:string): longint;

  end;

function SimpleReadCardPhyID(var CardIdString: string): smallint;
//检查输入金额是否符合标准
function Checkedt(key:Char;dot:string): Boolean;

//返回值信息提取
function getReturn(s1:string;wv:TWorkView):string ;

//发行卡时判断是否放卡，放卡是否是有效卡
function releaseCardJudge: Boolean;

//发行卡公用模块--new
function pubCardNew(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;phyCardId:string;showTip:Integer): string;

//写水控钱包信息
function writeWaterMoney(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest):string;

//充值，支取失败冲正业务处理
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;

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

//??
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;
function decCardpwd(custId:Integer;inseedkey,outpwd:string): string;

//语音报价器
function bj(comport:Integer;outString:string): Integer;

//加密操作员密码
function encOperPwd(operCode,operPwd:string):string;
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
function TCardManage.PacketSetMoney(m: string): Integer;
var
  DW: DWORD;
  st: smallint;
begin
  DW := StrToInt64(m);
  st := SMT_PacketSetMoney(bgPacketNo, DW);
  Result := st;
end;

//更新卡余额并判断是否更新成功
//更新卡余额,0成功，-10不确定，其他结果均为失败
function  TCardManage.packetSetMoneyAndChk(m:string;inMoney:Integer): Integer;
var
  DW: DWORD;
  st: smallint;
  newMoney:Integer;
  LPI: LOOPPURSEINFO;
begin
  DW := StrToInt64(m);
  st := SMT_PacketSetMoney(bgPacketNo, DW);
  if st = 0 then
  begin
    Result := 0;
  end
  else if st = -10 then
  begin
    if ReadCardConsumeInfo(LPI, bgPacketNo) then
      newMoney := LPI.RemainMoney
    else
      Result := -100;
      
    if newMoney = inMoney then
      Result := 0;
  end
  else
    Result := -100
end;

//更新卡余额
function TCardManage.PacketSetMoney2(money,ncnt:Integer):LongInt;
begin
  Result := utCardDll.SMT_PacketSetMoney2(bgPacketNo, money,ncnt);
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
  st := PacketDelMomey(bgPacketNo, DW);
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

  FillChar(PCM.ShowCardNo, SizeOf(PCM.ShowCardNo), 0);
  FillChar(PCM.CardNo, SizeOf(PCM.CardNo), 0);
  FillChar(PCM.DeadLineDate, SizeOf(PCM.DeadLineDate), 0);
  FillChar(PCM.ucName, SizeOf(PCM.ucName), 0);
  FillChar(PCM.ucDutyNo, SizeOf(PCM.ucDutyNo), 0);
  FillChar(PCM.ucCertificateNo, SizeOf(PCM.ucCertificateNo), 0);
  FillChar(PCM.ucDepartmentNo, SizeOf(PCM.ucDepartmentNo), 0);
  FillChar(PCM.ucLibraryNo, SizeOf(PCM.ucLibraryNo), 0);
  FillChar(PCM.ucSexNo, SizeOf(PCM.ucSexNo),0);
  FillChar(PCM.ucCardNo, SizeOf(PCM.ucCardNo), 0);
  
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
  Result := SMT_SetTxCnt(bgPacketNo,Num);
end;

function  TCardManage.readCardMoney(packNo:Integer): Integer;
var
  LPI: LOOPPURSEINFO;
begin
  if ReadCardConsumeInfo(LPI, packNo) then
    Result := LPI.RemainMoney;
end;

//更新补助批次号
function TCardManage.changePatchNo(Num:LongInt): LongInt;
begin
  Result := SMT_WriteSubsidy(bgPacketNo,Num);
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
  if (Key in ['0'..'9','.',#8,#13,'-']) then
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

{TODO:     调用后台返回信息}
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
  日期:      2008.06.04
  参数:      workviewIn, workviewOut: TWorkView工作视图，traceCode:交易代码,showTip是否显示提示提示框，0不显示，1显示
  返回值:    String
-------------------------------------------------------------------------------}
function pubCardNew(workviewIn, workviewOut: TWorkView;
          wvRequest:TWVRequest;phyCardId:string;showTip:Integer): string;
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
  cardBalance:Integer;      //卡余额
  cardPWD:string;           //卡密码
  isFormation:Char;         //是否格式化第一扇区
  sOper:string;             //开户操作员
  sOperDate:string;         //操作日期
  stationId:Integer;        //终端编号

  backTradeID:Integer;      //后台交易流水号
  maxPerCount:Integer;      //单次消费限额
  maxPerDay:Integer;        //日消费限额
  //outMoney:LongInt;       //出卡值
  re,ret:Integer;
  ResInt:Integer;
  readCardNo:string;
  PCM: TPublishCardMes;
  CardManage: TCardManage;
begin
  tradeCardNo:=workviewIn.fieldbyname('卡号').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('显示卡号').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('到期日期').Data.AsString;
  limitType:=workviewIn.fieldbyname('收费类别').Data.AsInteger;
  custType:=workviewIn.fieldbyname('客户类别').Data.AsInteger;
  custName:=workviewIn.fieldbyname('客户姓名').Data.AsString;
  dutyNo:='';
  cardID:=workviewIn.fieldbyname('证件号码').Data.AsString;
  depNo:=workviewIn.fieldbyname('部门代码').Data.AsString;
  bookID:='';
  sex:=workviewIn.fieldbyname('性别').Data.AsString;
  ID:=workviewIn.fieldbyname('学工号').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('出卡值').Data.AsInteger;
  cardPWD:=workviewIn.fieldbyname('卡密码').Data.AsString;
  isFormation := Char('N');
  backTradeID:=workviewIn.fieldbyname('流水号').Data.AsInteger;
  sOper := workviewIn.fieldbyname('操作员').Data.AsString;
  sOperDate := workviewIn.fieldbyname('业务日期').Data.AsString;
  stationId := workviewIn.fieldbyname('终端编号').Data.AsInteger;

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
  PCM.Money := cardBalance;                                   //卡余额
  strcopy(@PCM.ucPwd, PChar(cardPWD));                        //卡密码
  PCM.isFormat := isFormation;                                //是否格式化第一扇区
  re := 0;
  ResInt := 0;
  CardManage := nil;
  try
    try
      CardManage := TCardManage.Create;
      re := CardManage.PublishACard(PCM);
      //设置单次消费限额和日消费限额
      if maxPer=1 then
      begin
        maxPerCount := workviewIn.fieldbyname('单次限额').Data.AsInteger;
        maxPerDay := workviewIn.fieldbyname('日限额').Data.AsInteger;
        ret := CardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      //发卡成功，读卡号成功，读取卡号大于零才确定该卡已经发行成功，否则重新发行
      ResInt := CardManage.ReadExCardID(readCardNo);
    except
    end;
  finally
    CardManage.Destroy;
    if ((re = 0) and (ResInt=0) and (StrToInt(readCardNo)>0))and (ret=0) then
    begin
      if showTip=1 then
        context.GetDialogSystem.ShowMessage('写卡信息成功！该卡的卡号为:' + IntToStr(tradeCardNo));
      Result:=workviewIn.FieldByName('返回信息').Data.AsString;
    end
    //写卡失败冲正操作
    else
    begin
      Result:='写卡失败【'+inttostr(re)+'】--补办卡业务到更新卡信息操作，发卡到开户冲正界面进行冲正操作！'
      {
      workviewOut.FieldByName('终端编号').Data.SetInteger(stationId);
      workviewOut.FieldByName('流水号').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('业务日期').Data.SetString(sOperDate);
      workviewOut.FieldByName('开户操作员').Data.SetString(sOper);
      wvRequest.SendCommand;
      if workviewOut.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        context.GetDialogSystem.ShowMessage('冲正失败，请在交易冲正中处理该条记录并重新发行该卡！');
        Result:= '冲正失败--'+
        workviewOut.FieldByName('返回信息').Data.AsString+
        ',请在交易冲正中处理该条记录并重新发行该卡!';
      end
      else
      begin
        context.GetDialogSystem.ShowMessage('写卡失败【'+inttostr(re)+'】--请重新发行该卡！');
        Result:='写卡失败【'+inttostr(re)+'】--请重新发行该卡！'
      end;
      }
    end;

  end;

end;

function writeWaterMoney(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest):string;
var
  CardManage: TCardManage;
  sOperDate:string;         //操作日期
  st:SmallInt;
  backTradeID:Integer;      //后台交易流水号
  outSmlMoney:Integer;
begin
  backTradeID:=workviewIn.fieldbyname('流水号').Data.AsInteger;
  sOperDate := workviewIn.fieldbyname('业务日期').Data.AsString;
  outSmlMoney := workviewIn.fieldbyname('出卡金额').Data.AsInteger;
  try
    CardManage := TCardManage.Create;
    //加钱
    st :=CardManage.setCardMoney(SmlPacketNo2,outSmlMoney);
    if st<>0 then
    begin
      //写卡余额进行回滚交易
      workviewOut.FieldByName('终端编号').Data.SetInteger(StrToInt(scSiteNo));
      workviewOut.FieldByName('流水号').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('业务日期').Data.SetString(sOperDate);
      wvRequest.SendCommand;
      Context.GetDialogSystem.ShowMessage('补助开水钱包加钱失败，请直接到补助开水金额设置里设置金额！');
      Exit;
    end
    else
      SMT_ControlBuzzer;
    Result := '水控钱包充值成功！';
  finally
    CardManage.Destroy;
  end;
end;
{-------------------------------------------------------------------------------
  过程名:    cashOperCancel充值、支取失败做冲正交易
  作者:      hanjiwei
  日期:      2008.07.04
  参数:      workviewIn: TWorkView;wvRequest:TWVRequest
  返回值:    string
-------------------------------------------------------------------------------}
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
begin
  workviewIn.FieldByName('终端编号').Data.SetInteger(stationId);
  workviewIn.FieldByName('流水号').Data.SetInteger(seriId);
  workviewIn.FieldByName('业务日期').Data.SetString(operDate);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('冲正失败，请在交易冲正中处理该记录并重新做该业务！');
    Result := '冲正失败--'+
    workviewIn.fieldbyname('返回信息').Data.AsString+
    ',请在交易冲正中处理该记录并重新做该业务！';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('业务失败，请重新操作该项业务！');
    Result := '业务失败，请重新操作该项业务！';
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
      context.GetDialogSystem.ShowMessage('读卡序列号失败，没有放卡或该卡已经损坏！');
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
      Result := '-1';
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('读卡信息失败！错误号: ' + IntToStr(st));
      Result := '-1';
      Exit;
    end
    else
    Result:=trim(PCM.ShowCardNo);
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

function bj(comport:Integer;outString:string): Integer;
begin
  Result := utcarddll.dsbdll(comport,outString);
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

//水控相关----------------------------------------------------------------------
function TCardManage.InitNewCollectionCard(err_code: Integer): LongInt;
begin
  Result := utcarddll.InitNewCollectionCard(err_code,nil);
end;

function TCardManage.InitNewFeeRateCard(err_code: Integer): LongInt;
begin
  Result := utcarddll.InitNewFeeRateCard(err_code,nil);
end;

function TCardManage.PublishFeeRateCard(feeRateCardInfo: PFeeRateCardInfo): LongInt;
begin
  Result := utcarddll.PublishFeeRateCard(feeRateCardInfo);
end;

function TCardManage.RefineWaterCard(err_code: Integer): LongInt;
begin
  Result := utcarddll.RefineWaterCard(err_code,nil);
end;

function TCardManage.ReadBalance(nPacketNo: Integer;nBalance,nCnt:PInteger): longint;
begin
  Result := utcarddll.ReadBalance(nPacketNo,nBalance,nCnt);
end;

function TCardManage.setCardMoney(nPacketNo, money: Integer): LongInt;
begin
  Result := utcarddll.SMT_PacketSetMoney(nPacketNo, money);
end;

function TCardManage.ReadFeeRateCard(feeRateCardInfo: PFeeRateCardInfo): longint;
begin
  Result := utcarddll.ReadFeeRateCard(feeRateCardInfo);
end;

function TCardManage.CollectionCardReceiveData(err_code: PInteger;
  collectBalance:Pcollect_balance;
  collect_count: PInteger): longint;
begin
  Result := utcarddll.CollectionCardReceiveData(err_code,collectBalance,collect_count);
end;

function TCardManage.ClearCollectCardData: longint;
begin
  Result := utcarddll.SMT_ClearCollectCardData;
end;

function TCardManage.ReadWaterCardFlag(WaterCardFlag: PByte): longint;
begin
  Result := utcarddll.ReadWaterCardFlag(WaterCardFlag);
end;
//水控相关end-------------------------------------------------------------------


function TCardManage.encryptCardpwd(cut_id: Integer; const seedKey,
  pwd: pchar; var mpwd: string): longint;
var
  smpwd:array[0..64] of Char;
begin
  Result := UtCardDll.YKT_encrypt_cardpwd(cut_id,seedKey,pwd,smpwd);
  if Result=0 then
    mpwd := StrPas(smpwd);
end;

function TCardManage.decryptCardpwd(cut_id: Integer; const seedKey,
  mpwd: pchar; var pwd: string): longint;
var
  spwd:array[0..9] of Char;
begin
  Result := UtCardDll.YKT_decrypt_cardpwd(cut_id,seedKey,mpwd,spwd);
  if Result=0 then
    pwd := StrPas(spwd);
end;

//加密
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;
var
  cardmanage:TCardManage;
  seedkey:array[0..31] of Char;
  outmpwd:string;
  pwd:array[0..63] of Char;
  st:Integer;
begin
  //cardmanage := nil;
  FillChar(seedkey,32,0);
  FillChar(pwd,64,0);
  try
    cardmanage := TCardManage.Create;
    if Load_Dll<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('调用动态库失败！');
      Exit;
    end;
    StrPCopy(seedkey,inseedkey);
    StrPCopy(pwd,inpwd);
    st := cardmanage.encryptCardpwd(custId,seedkey,pwd,outmpwd);
    if st=0 then
      Result := outmpwd;
  finally
    cardmanage.Destroy;
    
  end;

end;

function decCardpwd(custId:Integer;inseedkey,outpwd:string): string;
var
  cardmanage:TCardManage;
  seedkey:array[0..31] of Char;
  outmpwd:string;
  pwd:array[0..63] of Char;
  st:Integer;
begin
  FillChar(seedkey,32,0);
  FillChar(pwd,64,0);
  try
    cardmanage := TCardManage.Create;
    if Load_Dll<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('调用动态库失败！');
      Exit;
    end;
    StrPCopy(seedkey,inseedkey);
    StrPCopy(pwd,outpwd);
    st := cardmanage.decryptCardpwd(custId,seedkey,pwd,outmpwd);
    if st=0 then
      Result := outmpwd;
  finally
    cardmanage.Destroy;

  end;

end;

//设置卡有效期
function TCardManage.ChangeDeadLineDate(dealDate: string): LongInt;
var
  sDate:array[0..3] of Char;
begin
  //FillChar(sDate,3,0);
  sDate[0] := chr(StrToInt(Copy(dealDate,3,2)));
  sDate[1] := chr(strtoint(Copy(dealDate,5,2)));
  sDate[2] := chr(strtoint(Copy(dealDate,7,2)));
  //StrPCopy(sDate,dealDate);
  Result := utCardDll.SMT_ChangeDeadLineDate(sDate);
end;

function TCardManage.ReadCardLockFlag(var lock_flag: Integer): LongInt;
var
  lockFlag:Integer;
begin
  Result := utcarddll.SMT_ReadCardLockFlag(@lockFlag);
  if Result=0 then
    lock_flag := lockFlag;
end;

function TCardManage.ReadConsumeLimit(var max_per_count,max_per_day: Integer): LongInt;
var
  maxPerCount,maxPerDay:Integer;
begin
  Result := utcarddll.SMT_ReadConsumeLimit(@maxPerCount,@maxPerDay);
  if Result = 0 then
  begin
    max_per_count := maxPerCount;
    max_per_day := maxPerDay;
  end;
end;

function TCardManage.SetCardLockFlag(lock_flag: Integer): LongInt;
begin
  Result := utcarddll.SMT_SetCardLockFlag(lock_flag);
end;

function TCardManage.SetConsumeLimit(max_per_count,max_per_day: Integer): LongInt;
begin
  Result := utcarddll.SMT_SetConsumeLimit(max_per_count,max_per_day);
end;

procedure TCardManage.readCardDllVer(var ver: string);
var
  returnVer:array[0..512] of Char;
begin
  utcarddll.YKT_get_version(PChar(@returnVer));
  ver := returnVer;
end;

function encOperPwd(operCode,operPwd:string):string;
var
  outOperPwd:array[0..16] of Char;
  st:Integer;
begin
  st := calc_oper_pwd(PChar(operCode),PChar(Trim(operPwd)),@outOperPwd);
  if st<>0 then
  begin
    Context.GetDialogSystem.ShowMessage('加密操作员密码失败'+inttostr(st));
    Result := '';
    Exit;
  end;
  Result := outOperPwd;
end;

end.
