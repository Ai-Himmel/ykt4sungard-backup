{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation

    <Unit>UtCardDll
    <What>ʵ��Ӳ�������ṩ�Ŀ��������dll��װ
    <Written By> Wang SuNa (������)

    <History>-------------------------------------------------------------------
    2004��12��14�� �������
    2006-07-20 �����еײ�ĵ��÷�װ��carddll��ͳһ����
    20080711  ����ΰ��������ˮ����غ�����
              ���ѵ�Ԫ�ļ�רҵ��framework�£�ʵ�����а�ͳһ����
*******************************************************************************}

unit UtCardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Dialogs,
    KSFrameWorks,WorkViews,KSClientConsts,WVCmdReq;

const
  CurrentUserKeyA = 0;
  CurrentUserKeyB = 1; //��ǰ��¼��Ƭĳ��������ʹ��KEY-A����KEY-B
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
    DealTimes: WORD;                        // ���״���
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
  
//ˮ����ض���ṹ��------------------------------------------------------------
// ��ǰȨ�޵ķ��ʸ���
type
  TFeeRate = packed record
  time_ladder :Byte ;				                              // ʱ�����
	deduct_time :Byte ;				                              // �۷ѵĵ�λʱ�䣬����Ϊ��λ
	deduct_fee :Byte ;				                              // �۷ѵĵ�λ���Է�Ϊ��λ
  end;


// ��ǰȨ�޵ķ��ʸ���
  TFeeRightNo = packed record
	right_flag : SHORT;					                            // Ȩ�ޱ�־, 1��, 0�ر�
	right_num : SHORT;					                            // ���뵱ǰȨ���µķ��ʸ���
	fee_rate : array[1..5] of TFeeRate;				              // �������Ϊ5��
  end;
  
// ���ʿ��ṹ˵��
  TFeeRateCardInfo = packed record
	water_card_flag : array[1..5] of Byte;			            // ˮ�ؿ���־
	packet_num : Char;					                            // ˮ��Ǯ����
	main_work_key : array[1..9] of Byte;			              // ��������Կ(����)
	packet_work_key : array[1..9] of Byte;			            // СǮ��������Կ(����)
  work_model:Byte;                                        // ����ģʽ
  water_packet_limit : Integer;				                    // ˮ��Ǯ���޶�-----
	transfer_limit : Integer;					                      // ˮ��ת���޶�-----
	data_length : array[1..3] of Byte;				              // ���ݳ���
	check_crc : array[1..2] of Byte;				                // Ч���ֽ�
	fee_right_num : array[1..256] of TFeeRightNo;	          // ���÷��ʵĸ���
  end;
  PFeeRateCardInfo = ^TFeeRateCardInfo;

  Tcollect_balance = packed record
  devId :array[1..9] of Char;
  sum_balance :Double;
  end;
  Pcollect_balance = ^Tcollect_balance;
//ˮ�ؽṹ�嶨�����end---------------------------------------------------------

//�����SMT_CheckForCard();
//����1��ʾ�㿨��2��ʾ��ʼ�����Ŀ�, 3��ʾ����ʶ��Ŀ�
function SMT_CheckForCard(): longint;
  stdcall;far; external Carddll name 'SMT_CheckForCard';

//��ʼ������ *
function ConnectMF(port: longint; baud: longint): longint;
  stdcall;far; external Carddll name 'ConnectMF';

//����������
function SMT_ControlBuzzer: longint;
  stdcall;far; external Carddll name 'ControlBuzzer';

//����Ȩ��
function DLLReadCardMainKey(OutMainKey: PByte;swith:SmallInt;flag:PSmallInt):LongInt;
  stdcall;far; external Carddll name 'ReadCardMainKey' ;

//���ÿ�ƬΪ����������ҡ��ⶳ��
function SMT_SetNormalFlag: longint;
  stdcall;far; external Carddll name 'SMT_SetNormalFlag';

//���ÿ�ƬΪ����������ң��ⶳ������汾��2005-06-08����
function SMT_SetNormalFlagByVer(ver:PChar): longint;
  stdcall;far; external Carddll name 'SMT_SetNormalFlagByBlkVerion';

//���տ�
function SMT_ClearCard: longint;
  stdcall;far; external Carddll name 'SMT_ClearCard';

//��д����Ȩ *
function ReaderAuthor(MoneyBuf: pchar): longint;
  stdcall;far; external Carddll name 'SMT_AutoDll';

function Load_Dll: longint;
  stdcall;far; external Carddll name 'Load_Dll';

// ���ùرմ��� *
function CloseMF: SmallInt;
  stdcall;far; External Carddll name 'CloseMF';

//���п�   *
function PublishCard(const PCM: TPublishCardMes): longint;
  stdcall;external Carddll name 'PublishCard';

//������Ϣ   *
function ReadCardInfo(const PCM: TPublishCardMes): longint;
  stdcall;external Carddll name 'ReadCardInfo';

//�������к� *
function RequestCard(ucSerialNo: pchar; ucType: pchar): longint;
  stdcall;external Carddll name 'RequestCard';

//�û�����Ǯ
function PacketAddMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external Carddll name 'SMT_PacketAddMomey';

//�û���ȡ�� *
function PacketDelMomey(nPacketNo: smallint; nMoney: longint): longint;
  stdcall;external Carddll name 'SMT_PacketDelMomey';

//���û���������Ϣ
function ReadPacketInfo(const LPI: LOOPPURSEINFO): longint;
  stdcall;external Carddll name 'ReadPacketInfo';

//�û������������ȡ  *
function ReadPersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external Carddll name 'ReadCardPwd';

//�û�������������� *
function ChangePersonalPassword(PersonalPsd: pchar): longint;
  stdcall;external Carddll name 'WriteCardPwd';

//�����׿���  *
function ReadExchCardNo(ExchCardNo: PInteger): longint;
  stdcall;external Carddll name 'ReadCardNO';

//������Ϣ *
function GetLastErrMsg(errcode:pointer;msg:pchar ):longint;
  stdcall;external Carddll name 'GetLastErrMsg';

//���¿���Ϣ   *
function UpdateCardInfo(const CardInfo: TPublishCardMes): longint;
  stdcall;external Carddll name 'UpdateCardInfo';
//������Ȩĸ�� *
function CreateMonKeyCard(nKey1: longint; nKey2: longint): longint;
  stdcall;far; external Carddll name 'SMT_CreateMonKeyCard';

//������Ȩĸ��  *
function ClearMonKeyCard: smallInt;
  stdcall;far; External Carddll name 'SMT_ClearMonKeyCard';
  
//����������Կ�ӿ�  *
function PublishComsumeChildCard(year, month, day, hour: pchar): longint;
  stdcall;external Carddll name 'PublishComsumeChildCard';

//����������Կ�ӿ�  *
function ClearComsumeChildCard: SmallInt;
  stdcall;far; External Carddll name 'SMT_ClearComsumeChildCard';

//���г�ֵ��Կ�ӿ�  *
function PublishAddMoneyChildCard(year, month, day, hour: pchar): longint;
  stdcall;external Carddll name 'PublishAddMoneyChildCard';

//���ճ�ֵ��Կ�ӿ�  *
function ClearAddMoneyChildCard: SmallInt;
  stdcall;far; External Carddll name 'SMT_ClearAddMoneyChildCard';

function get_check_char(InCheckSumString: PChar): longint;
  stdcall;far; external 'desdll.dll' name 'get_check_char';

function SMT_Login_With_UserKey(Sector: longint; key: PChar; keyFlag: longint):longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_Login_With_UserKey';

function SleepCard: longint;
  stdcall;far; external 'SmartCom411DXQ.dll' name 'SMT_SleepCard';

//���½��׿���
function SMT_ChangeDealCardNo(dealCardNo:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_ChangeDealCardNo';

//���¿����
function SMT_PacketSetMoney(nPacketNo,dealCardNo:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_PacketSetMoney';

//���¿����2
function SMT_PacketSetMoney2(nPacketNo,dealCardNo,nCnt:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_PacketSetMoney2';

//��ȡ�������Ѷ�(max_per_count),���ۼ����Ѷ�(max_per_day)
function SMT_ReadConsumeLimit(max_per_count,max_per_day:PInteger): longint;
  stdcall;far; external Carddll name 'ReadConsumeLimit';

//д�뵥�����Ѷ�(max_per_count),���ۼ����Ѷ�(max_per_day)
function SMT_SetConsumeLimit(max_per_count,max_per_day:LongInt): longint;
  stdcall;far; external Carddll name 'SetConsumeLimit';

//���������ͽ���(0x00 ��ʾ������ 0xFF��ʾ����)
function SMT_ReadCardLockFlag(lock_flag:PInteger): longint;
  stdcall;far; external Carddll name 'ReadCardLockFlag';

//��̬��汾��
procedure YKT_get_version(ver:PChar);
  stdcall;far; external Carddll name 'YKT_get_version';

function SMT_SetCardLockFlag(lock_flag:LongInt): longint;
  stdcall;far; external Carddll name 'SetCardLockFlag';

//���¿���Ч��
function SMT_ChangeDeadLineDate(ucDeadLineDate:PChar): longint;
  stdcall;far; external Carddll name 'SMT_ChangeDeadLineDate';

//д�����״���
function SMT_SetTxCnt(nPacketNo,tx_cnt:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_SetTxCnt';
//д�������κ�
function SMT_WriteSubsidy(nPacketNo,batch_no:LongInt): longint;
  stdcall;far; external Carddll name 'SMT_WriteSubsidy';

//�����������汾
function SMT_ReadBlackNameListVersion(flag:Pointer;version:string): longint;
  stdcall;far; external Carddll name 'SMT_ReadBlackNameListVersion';
//���Ǯ����Ϣ
function SMT_PacketReset(PackNo:Integer): longint;
  stdcall;far; external Carddll name 'SMT_PacketReset';
//��ȡ����Ϣ
function SMT_ReadBlock(Sector: longint; BlockNo: longint; BlockBuf: PChar):
  longint; stdcall;
far; external 'SmartCom411DXQ.dll' name 'SMT_ReadBlock';

//��ʼ��������
function InitNewCard(err_code:PInteger;showcardno:PChar;test:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewCard';

function HaltCard: LongInt;
  stdcall;far;external Carddll name 'HaltCard';

//������Ȩ��--------------------------------------------------------------------
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
//ˮ�����----------------------------------------------------------------------
//���вɼ���
function InitNewCollectionCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewCollectionCard';

//���ղɼ����ͷ������ÿ�
function RefineWaterCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'RefineWaterCard';

//��ʼ���������ÿ�
function InitNewFeeRateCard(err_code: Integer; callBack:Pointer):longint;
  stdcall;far; external Carddll name 'InitNewFeeRateCard';

//���з������ÿ�
function PublishFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;
  stdcall;far; external Carddll name 'PublishFeeRateCard';

//��ȡ�������ÿ�
function ReadFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;
  stdcall;far; external Carddll name 'ReadCollectCardInfo';

//��Ǯ����Ϣ
function ReadBalance(nPacketNo:Integer;nBalance:pInteger;nCnt:PInteger):longint;
  stdcall;far; external Carddll name 'ReadBalance';

//���ɼ�����Ϣ
function CollectionCardReceiveData(err_code:PInteger;collectBalance:Pcollect_balance;collect_count:PInteger):longint;
  stdcall;far; external Carddll name 'CollectionCardReceiveData';

//���ɼ�����Ϣ
function SMT_ClearCollectCardData:longint;
  stdcall;far; external Carddll name 'SMT_ClearCollectCardData';

//����Ϣ����
function ReadWaterCardFlag(WaterCardFlag:pByte):longint;
  stdcall;far; external Carddll name 'SMT_ReadWaterCardFlag';

//ˮ�����end-------------------------------------------------------------------
//���ܵ���Ǯ��
function YKT_encrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const pwd:pchar;mpwd:pchar): LongInt;
  stdcall;far;external Carddll name 'YKT_encrypt_cardpwd';
//���ܵ���Ǯ��
function YKT_decrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const mpwd:pchar;pwd:pchar): LongInt;
  stdcall;far;external Carddll name 'YKT_decrypt_cardpwd';

//******************************************************************************

//����������--------------(����)
function dsbdll(ComPort:integer;OutString:string):integer;stdcall;external 'Tdbjq.dll';

function calc_oper_pwd(const oper_code :pChar;const pwd:pchar;text:pchar): LongInt;
  stdcall;far;external desDll name 'calc_oper_pwd';

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
    function PacketSetMoney(m:string):Integer;

    //���¿����ж��Ƿ���³ɹ�
    function packetSetMoneyAndChk(m:string;inMoney:Integer): Integer;

    //���¿����2
    function PacketSetMoney2(money,ncnt:Integer):LongInt;

    //��ȡ�������Ѵ��������ۼ����Ѵ���
    function ReadConsumeLimit(var max_per_count,max_per_day:Integer): LongInt;

    //���õ������Ѵ��������ۼ����Ѵ���
    function SetConsumeLimit(max_per_count,max_per_day:Integer): LongInt;

    //��ȡ��������״̬
    function ReadCardLockFlag(var lock_flag:Integer): LongInt;

    //���ÿ�������״̬
    function SetCardLockFlag(lock_flag:Integer): LongInt;

    //��ȡ��̬��汾��
    procedure readCardDllVer(var ver:string);
    
    //���¿���Ч��
    function ChangeDeadLineDate(dealDate:string): LongInt;

    //���¿��Ľ��״���
    function changeTradeNum(Num:LongInt): LongInt;

    //��ȡ�������Ϣ
    function  readCardMoney(packNo:Integer): Integer;


    //���¿����κ�
    function changePatchNo(Num:LongInt): LongInt;

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

    //ˮ�����******************************************************************
    //��ʼ���ɼ���
    function InitNewCollectionCard(err_code:Integer): LongInt;

    //���ղɼ����ͷ������ÿ�
    function RefineWaterCard(err_code:Integer): LongInt;

    //��ʼ���������ÿ�
    function InitNewFeeRateCard(err_code:Integer): LongInt;

    //���з������ÿ�
    function PublishFeeRateCard(feeRateCardInfo : PFeeRateCardInfo): LongInt;

    function ReadFeeRateCard(feeRateCardInfo : PFeeRateCardInfo):longint;

    function ReadBalance(nPacketNo:Integer;nBalance:pInteger;nCnt:pInteger):longint;

    function setCardMoney(nPacketNo:Integer;money:Integer): LongInt;

    function CollectionCardReceiveData(err_code:PInteger;collectBalance: Pcollect_balance;collect_count:PInteger):longint;

    function ClearCollectCardData:longint;

    function ReadWaterCardFlag(WaterCardFlag:PByte):longint;
    //ˮ�����end***************************************************************
    function encryptCardpwd(cut_id:Integer;const seedKey,pwd:pchar;var mpwd:string): longint;
    function decryptCardpwd(cut_id:Integer;const seedKey,mpwd:pchar;var pwd:string): longint;

  end;

function SimpleReadCardPhyID(var CardIdString: string): smallint;
//����������Ƿ���ϱ�׼
function Checkedt(key:Char;dot:string): Boolean;

//����ֵ��Ϣ��ȡ
function getReturn(s1:string;wv:TWorkView):string ;

//���п�ʱ�ж��Ƿ�ſ����ſ��Ƿ�����Ч��
function releaseCardJudge: Boolean;

//���п�����ģ��--new
function pubCardNew(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;phyCardId:string;showTip:Integer): string;

//дˮ��Ǯ����Ϣ
function writeWaterMoney(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest):string;

//��ֵ��֧ȡʧ�ܳ���ҵ����
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;

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

//??
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;
function decCardpwd(custId:Integer;inseedkey,outpwd:string): string;

//����������
function bj(comport:Integer;outString:string): Integer;

//���ܲ���Ա����
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

//���¿����
function TCardManage.PacketSetMoney(m: string): Integer;
var
  DW: DWORD;
  st: smallint;
begin
  DW := StrToInt64(m);
  st := SMT_PacketSetMoney(bgPacketNo, DW);
  Result := st;
end;

//���¿����ж��Ƿ���³ɹ�
//���¿����,0�ɹ���-10��ȷ�������������Ϊʧ��
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

//���¿����
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
  Result := SMT_SetTxCnt(bgPacketNo,Num);
end;

function  TCardManage.readCardMoney(packNo:Integer): Integer;
var
  LPI: LOOPPURSEINFO;
begin
  if ReadCardConsumeInfo(LPI, packNo) then
    Result := LPI.RemainMoney;
end;

//���²������κ�
function TCardManage.changePatchNo(Num:LongInt): LongInt;
begin
  Result := SMT_WriteSubsidy(bgPacketNo,Num);
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

{TODO:     ���ú�̨������Ϣ}
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
  ����:      2008.06.04
  ����:      workviewIn, workviewOut: TWorkView������ͼ��traceCode:���״���,showTip�Ƿ���ʾ��ʾ��ʾ��0����ʾ��1��ʾ
  ����ֵ:    String
-------------------------------------------------------------------------------}
function pubCardNew(workviewIn, workviewOut: TWorkView;
          wvRequest:TWVRequest;phyCardId:string;showTip:Integer): string;
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
  cardBalance:Integer;      //�����
  cardPWD:string;           //������
  isFormation:Char;         //�Ƿ��ʽ����һ����
  sOper:string;             //��������Ա
  sOperDate:string;         //��������
  stationId:Integer;        //�ն˱��

  backTradeID:Integer;      //��̨������ˮ��
  maxPerCount:Integer;      //���������޶�
  maxPerDay:Integer;        //�������޶�
  //outMoney:LongInt;       //����ֵ
  re,ret:Integer;
  ResInt:Integer;
  readCardNo:string;
  PCM: TPublishCardMes;
  CardManage: TCardManage;
begin
  tradeCardNo:=workviewIn.fieldbyname('����').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('��ʾ����').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('��������').Data.AsString;
  limitType:=workviewIn.fieldbyname('�շ����').Data.AsInteger;
  custType:=workviewIn.fieldbyname('�ͻ����').Data.AsInteger;
  custName:=workviewIn.fieldbyname('�ͻ�����').Data.AsString;
  dutyNo:='';
  cardID:=workviewIn.fieldbyname('֤������').Data.AsString;
  depNo:=workviewIn.fieldbyname('���Ŵ���').Data.AsString;
  bookID:='';
  sex:=workviewIn.fieldbyname('�Ա�').Data.AsString;
  ID:=workviewIn.fieldbyname('ѧ����').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('����ֵ').Data.AsInteger;
  cardPWD:=workviewIn.fieldbyname('������').Data.AsString;
  isFormation := Char('N');
  backTradeID:=workviewIn.fieldbyname('��ˮ��').Data.AsInteger;
  sOper := workviewIn.fieldbyname('����Ա').Data.AsString;
  sOperDate := workviewIn.fieldbyname('ҵ������').Data.AsString;
  stationId := workviewIn.fieldbyname('�ն˱��').Data.AsInteger;

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
  PCM.Money := cardBalance;                                   //�����
  strcopy(@PCM.ucPwd, PChar(cardPWD));                        //������
  PCM.isFormat := isFormation;                                //�Ƿ��ʽ����һ����
  re := 0;
  ResInt := 0;
  CardManage := nil;
  try
    try
      CardManage := TCardManage.Create;
      re := CardManage.PublishACard(PCM);
      //���õ��������޶���������޶�
      if maxPer=1 then
      begin
        maxPerCount := workviewIn.fieldbyname('�����޶�').Data.AsInteger;
        maxPerDay := workviewIn.fieldbyname('���޶�').Data.AsInteger;
        ret := CardManage.SetConsumeLimit(maxPerCount,maxPerDay);
      end;
      //�����ɹ��������ųɹ�����ȡ���Ŵ������ȷ���ÿ��Ѿ����гɹ����������·���
      ResInt := CardManage.ReadExCardID(readCardNo);
    except
    end;
  finally
    CardManage.Destroy;
    if ((re = 0) and (ResInt=0) and (StrToInt(readCardNo)>0))and (ret=0) then
    begin
      if showTip=1 then
        context.GetDialogSystem.ShowMessage('д����Ϣ�ɹ����ÿ��Ŀ���Ϊ:' + IntToStr(tradeCardNo));
      Result:=workviewIn.FieldByName('������Ϣ').Data.AsString;
    end
    //д��ʧ�ܳ�������
    else
    begin
      Result:='д��ʧ�ܡ�'+inttostr(re)+'��--���쿨ҵ�񵽸��¿���Ϣ��������������������������г���������'
      {
      workviewOut.FieldByName('�ն˱��').Data.SetInteger(stationId);
      workviewOut.FieldByName('��ˮ��').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('ҵ������').Data.SetString(sOperDate);
      workviewOut.FieldByName('��������Ա').Data.SetString(sOper);
      wvRequest.SendCommand;
      if workviewOut.FieldByName('������').Data.AsInteger<>0 then
      begin
        context.GetDialogSystem.ShowMessage('����ʧ�ܣ����ڽ��׳����д��������¼�����·��иÿ���');
        Result:= '����ʧ��--'+
        workviewOut.FieldByName('������Ϣ').Data.AsString+
        ',���ڽ��׳����д��������¼�����·��иÿ�!';
      end
      else
      begin
        context.GetDialogSystem.ShowMessage('д��ʧ�ܡ�'+inttostr(re)+'��--�����·��иÿ���');
        Result:='д��ʧ�ܡ�'+inttostr(re)+'��--�����·��иÿ���'
      end;
      }
    end;

  end;

end;

function writeWaterMoney(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest):string;
var
  CardManage: TCardManage;
  sOperDate:string;         //��������
  st:SmallInt;
  backTradeID:Integer;      //��̨������ˮ��
  outSmlMoney:Integer;
begin
  backTradeID:=workviewIn.fieldbyname('��ˮ��').Data.AsInteger;
  sOperDate := workviewIn.fieldbyname('ҵ������').Data.AsString;
  outSmlMoney := workviewIn.fieldbyname('�������').Data.AsInteger;
  try
    CardManage := TCardManage.Create;
    //��Ǯ
    st :=CardManage.setCardMoney(SmlPacketNo2,outSmlMoney);
    if st<>0 then
    begin
      //д�������лع�����
      workviewOut.FieldByName('�ն˱��').Data.SetInteger(StrToInt(scSiteNo));
      workviewOut.FieldByName('��ˮ��').Data.SetInteger(backTradeID);
      workviewOut.FieldByName('ҵ������').Data.SetString(sOperDate);
      wvRequest.SendCommand;
      Context.GetDialogSystem.ShowMessage('������ˮǮ����Ǯʧ�ܣ���ֱ�ӵ�������ˮ������������ý�');
      Exit;
    end
    else
      SMT_ControlBuzzer;
    Result := 'ˮ��Ǯ����ֵ�ɹ���';
  finally
    CardManage.Destroy;
  end;
end;
{-------------------------------------------------------------------------------
  ������:    cashOperCancel��ֵ��֧ȡʧ������������
  ����:      hanjiwei
  ����:      2008.07.04
  ����:      workviewIn: TWorkView;wvRequest:TWVRequest
  ����ֵ:    string
-------------------------------------------------------------------------------}
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
begin
  workviewIn.FieldByName('�ն˱��').Data.SetInteger(stationId);
  workviewIn.FieldByName('��ˮ��').Data.SetInteger(seriId);
  workviewIn.FieldByName('ҵ������').Data.SetString(operDate);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('������').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('����ʧ�ܣ����ڽ��׳����д���ü�¼����������ҵ��');
    Result := '����ʧ��--'+
    workviewIn.fieldbyname('������Ϣ').Data.AsString+
    ',���ڽ��׳����д���ü�¼����������ҵ��';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('ҵ��ʧ�ܣ������²�������ҵ��');
    Result := 'ҵ��ʧ�ܣ������²�������ҵ��';
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
      context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ�û�зſ���ÿ��Ѿ��𻵣�');
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
      Result := '-1';
      Exit;
    end;
    st := CardManage.ReadCardInfo(PCM);
    if st <> 0 then
    begin
      context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������: ' + IntToStr(st));
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
 ������Ȩ����غ���������������
*******************************************************************************}

//ˮ�����----------------------------------------------------------------------
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
//ˮ�����end-------------------------------------------------------------------


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

//����
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
      Context.GetDialogSystem.ShowMessage('���ö�̬��ʧ�ܣ�');
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
      Context.GetDialogSystem.ShowMessage('���ö�̬��ʧ�ܣ�');
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

//���ÿ���Ч��
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
    Context.GetDialogSystem.ShowMessage('���ܲ���Ա����ʧ��'+inttostr(st));
    Result := '';
    Exit;
  end;
  Result := outOperPwd;
end;

end.
