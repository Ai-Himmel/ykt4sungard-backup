{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation
    <Unit>CardDll
    <What>ʵ��Ӳ�������ṩ�Ŀ��������dll��װ
*******************************************************************************}

unit CardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,
  WVCmdReq,KSClientConsts,Db,WaterDll;

const
  //****************************************************************************
  //��̬�ⶨ��
  CARD_DLL ='kscard.dll';
  DESDLL = 'desdll.dll';

  PACKETTYPE_XT=2;    //����ˮ��
  PACKETTYPE_HD=3;    //���ˮ��
  PACKETTYPE_39=4;    //����ˮ��
  overTime = 30000;   //�ȴ���ʱʱ�䣬Ĭ��10��

  //usb�ڶ˿ں�
  USB_PORT = 100;

  //��д��ģʽ����
  READ_MODE = 0;            //����ģʽ
  WRITE_MODE = 1;           //д��ģʽ

  //��״̬��־
  NORMAL_CARD = 0;          //����״̬
  LOCK_CARD = 1;            //����״̬
  LOSE_CARD = 2;            //��ʧ״̬
  FREEZE_CARD = 3;          //����״̬
  DESTORY = 4;              //ע��״̬
  DEAL_CARD = 5;            //����״̬
  FEE_LOCK_CARD=6;          //�󸶷�����

  //cpu���������壬���ṹ������
  CARD_SERI_NO = 1;         //�����к�
  CARD_NO = 2;              //���׿���
  SHOW_CARDNO = 3;          //��ʾ����
  CARD_LIMIT_TYPE = 4;      //��Ȩ�����
  PATCH_NO = 5;             //�����κ�
  BLACK_VER = 6;            //�������汾
  BLACK_CARD_SIGN = 7;      //��״̬��־���ڿ���־
  START_USE_DATE = 8;       //��������
  DEADLINE_DATE = 9;        //��Ч��
  REL_CARD_SIGN = 10;       //��������ʶ
  CARD_TYPE = 11;           //�����
  APP_TYPE = 12;            //Ӧ�����
  CARD_STRUCT_VER = 13;     //���ṹ�汾����ǰΪ12

  SCHOOL_CODE = 20;         //У������
  CUST_NO = 21;             //�ͻ���

  CUST_TYPE = 22;           //�ͻ����
  STUEMP_NO = 23;           //ѧ����
  CUST_NAME = 24;           //�ͻ�����
  CUST_SEX = 25;            //�ͻ��Ա�
  DEPT_NO = 26;             //���Ŵ���
  CERTIFICATE_NO = 27;      //֤������
  CERTIFICATE_TYPE = 28;    //֤������

  BANK_NO = 30;             //���п���

  LOCK_TERMID = 34;         //��������ʱ�ն˻���
  LOCK_TRANSDATE = 35;      //������������
  LOCK_TRANSTIME = 36;      //��������ʱ��

  DAYSUM_AMT = 37;		      //�����ۼƽ��׽��
  LOCK_CARDCNT = 38;		    //��������ʱ���״���

  MAX_PER_COUNT = 41;       //���������ѽ������
  MAX_PER_DAY = 42;         //�����ۼ����ѽ������

  //���һ�ν���
  CARD_CNT = 44;            //�����״���31
  TRANS_AMT = 45;           //���׽��32
  TRANS_TYPE = 46;          //��������33
  TERM_ID = 47;             //�����ն˻����34
  TRANS_DATE = 48;          //��������35
  TRANS_TIME = 49;          //����ʱ��36
  //LOCK_CARD_CNT=38;       //�������״���

  CARD_BALANCE = 50;        //�����
  CARD_PWD = 51;            //������

  DPT_CARD_CNT = 64;        //��ֵ���״���
  PAY_CARD_CNT = 65;        //֧�����״���
  //SSD_CARD_CNT = 66;      //������ȡ����

  CF_NORMALLYOPEN = 80;     //��������־0x99������0x00����

type
  //�������ý��ṹ��
  TTRANSPACK = packed record
    TermID :Integer;		              //�豸�ն˱��+++
    CardNo : LongWord;		            //���׿���
    CardPhyID : array[0..16] of Char;	//�����к�
	  DptCardCnt : LongWord;	          //����ǰ����ֵ��
	  PayCardCnt : LongWord;	          //����ǰ���Ѵ���
	  SubsidyNo : LongWord;		          //�������κ�
    BefBalance : Integer;	            //����ǰ������λ��
    AftBalance : Integer;	            //���׺�����λ��
    TransAmt : Integer;		            //��ֵ����λ��
    TransDate : array[0..8] of Char;	//��������
    TransTime : array[0..6] of Char;	//����ʱ��
    Termno : array[0..12] of Char;	  //�ն˺�
    TermSeqno : LongWord;		          //�ն˽������к�
    Random : array[0..8] of Char;		  //�����
    OperCode : array[0..8] of Char;	  //����Ա����
    FundType : LongWord;		          //��ֵ���� 1 �ֽ�2 ֧Ʊ 3 ���ѱ� 4 ����
    VoucherNo : array[0..23] of Char;	//��ֵƱ�ݺ�
    sCardPwd : array[0..6] of Char;   //������
    TransType : Integer;		          //�������� 0-��ֵ 1�ۿ�
    PayCode :integer;		              //֧������+++
    PayType : Integer;		            //֧������,������ʹ��

    RefNo : array[0..14] of Char;		  //���ײο���+++
    cRetryFlag:Char;		              //���Ա�־
    cGetProveFlag:Char;	              //����ȷ�ϱ�־
    Mac : array[0..8] of Char;		    //MAC+++
    HostSeqno : LongWord;		          //����������ˮ��
    ErrCode : Integer;		            //������
    ErrMsg : array[0..255] of Char;	  //������Ϣ
  end;
  PTRANSPACK = ^TTRANSPACK;

  //������ϸ�ṹ
  TPAYDTL = packed record
    recordno : Integer;		            //��¼��
    exist : Integer;			            //�����¼���ڣ���Ϊ1������Ϊ0
    transdate : array[0..8] of Char;	//��������(YYYYMMDD)
    transtime : array[0..6] of Char;	//����ʱ��(HHMMSS)
    paycnt : Integer;			            //���Ѵ���
    cardbefbal : Integer;		          //����ǰ���
    transamt : Integer;		            //���׽��(��������)
    otherfee : Integer;		            //����
    extamt : Integer;			            //��д���(��ǮΪ����ǮΪ��)
    shopid : Integer;			            //�̻���
    termno : array[0..12] of Char;	  //�ն˻����(PSAM���е��ն˺�)
    termsno : Integer;		            //�ն˽������(����TAC��)
  end;
  PPAYDTL = ^TPAYDTL;


  //����pasm���ṹ��
  TPUBPSAMCARD = packed record
    CardNo : array[0..20] of Char;		  //PSAM����
    CardType : LongWord;		            //PSAM������
    CardVer : LongWord;                 //���汾��
    TermID : array[0..12] of Char;		  //�ն˱��
    TermSeqno : LongWord;		            //�ն˽�����ţ�ֻ�ܶ�ȡ
    KeyIndex : LongWord;		            //��Կ������,��Կ����ȡֵ��Χ��1��2��3��Ŀǰ����������Ϊ��1
    StartDate : array[0..8] of Char;	  //��������
    ExpireDate : array[0..8] of Char;   //��Ч����
    PublishID : array[0..16] of Char;	  //���з���ʶ
    UserID : array[0..16] of Char;	    //ʹ�÷���ʶ
  end;
  PPUBPSAMCARD = ^TPUBPSAMCARD;

  //****************************************************************************
//���ܵ���Ǯ��
{
function YKT_encrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const pwd:pchar;mpwd:pchar): LongInt;
  stdcall;far;external CARD_DLL name 'YKT_encrypt_cardpwd';
}
//����������
function dsbdll(ComPort:integer;OutString:string):integer;stdcall;external 'Tdbjq.dll';
//��usb�豸���ļ�
function  info2text(filename:String): Integer;
  stdcall;far; external 'usbUpload.dll' name 'info2text';

//��̬��汾��
procedure ks_getversioninfo(const ver,builddate,desc:PChar);
  stdcall;far; external CARD_DLL name 'ks_getversioninfo';

{**cpu card function begin-----------------------------------------------------}
//���������--------------------------------------------------------------------
//
function  ks_licence(lisence,pwd:String): Integer;
  stdcall;far; external CARD_DLL name 'ks_licence';

//�򿪶�����
function  ks_openport(port: Integer; band: Integer): Integer;
  stdcall;far; external CARD_DLL name 'ks_openport';

//�رն�����
function ks_closeport: Integer;
  stdcall;far; external CARD_DLL name 'ks_closeport';

//����������
function KNG_beep: Integer;
  stdcall;far; external CARD_DLL name 'ks_beep';

//��Կ�����--------------------------------------------------------------------
//������Կ��
function ks_publishkeycard(sMasterKey,sPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishkeycard';

{//������Կ��
function ks_getkey(nKeySerial:Integer;sPin:PChar;const sKey:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_getkey';
}

//��ֹ�Ըÿ�����
//���_Mode=0���ڶԿ����в�����Ϻ�ִ��ks_halt();��ÿ�����HALTģʽ�������ѿ��ƿ���Ӧ���ٽ�������Ѱ�����ſ���
function ks_halt: Integer;
  stdcall;far; external CARD_DLL name 'ks_halt';

//��������ؽӿ�----------------------------------------------------------------
//���ø��ֶζ�ģʽ
function ks_setfieldreadmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldreadmode';
//���ø��ֶ�дģʽ
function ks_setfieldwritemode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldwritemode';
//���ø��ֶζ�дģʽ
function ks_setfieldallmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldallmode';
//������ֶζ�ģʽ
function ks_clearfieldreadmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldreadmode';
//������ֶ�дģʽ
function ks_clearfieldwritemode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldwritemode';
//������ֶ�����ģʽ
function ks_clearfieldallmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldallmode';
//��������ֶεĶ�ģʽ
function ks_clearallfieldreadmode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldreadmode';
//��������ֶε�дģʽ
function ks_clearallfieldwritemode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldwritemode';
//��������ֶεĶ�дģʽ
function ks_clearallfieldallmode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldallmode';

//Ѱ��
function ks_card(phyId:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_card';

//���ڲ����
function ks_cardtype():Integer;
  stdcall;far; external CARD_DLL name 'ks_cardtype';

//mfѰ��
function ks_mf_card(phyId:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_mf_card';

//����mfone����Կ
function ks_setmifare1key(sWorkKey:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_setmifare1key';
  
//��ȡ����Ϣ
function ks_readcard():Integer;
  stdcall;far; external CARD_DLL name 'ks_readcard';

//��ȡ����Ϣ�ֶ�
function ks_getfieldval(mask:Integer;const data:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_getfieldval';

//����д�ֶ�����
function ks_setfieldval(mask:Integer;data:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldval';

//д����Ϣ
function ks_writecard(phyId:pchar):Integer;
  stdcall;far; external CARD_DLL name 'ks_writecard';

//��֤����
function ks_verifypin(phyId,pin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_verifypin';

//����Ǯ�����
function ks_setcardbal(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_setcardbal';

//�ۿ�

function ks_payment(transpack:PTRANSPACK;must_online:Integer=1):Integer;
  stdcall;far; external CARD_DLL name 'ks_payment';

//�ۿ��ʼ��
function ks_payinit(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_payinit';

//�ۿ�
function ks_pay(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_pay';

//ȡ������֤��1��ֵ��2���ѣ�cardcnt���׺��ֵ���������Ѵ���
function ks_gettransprove(transflag,short:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_gettransprove';

//����ȷ��
function ks_dotransunprove(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_dotransunprove';

//��ֵ��ʼ��
function ks_comminit(svrip:PChar;svrport,svrfunc:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_comminit';

//��ֵ
function ks_deposit(transpack:PTRANSPACK;must_online:Integer=1):Integer;
  stdcall;far; external CARD_DLL name 'ks_deposit';

//��ȡ������ˮ
function ks_readpaydtl(recordno:Integer;paydtl:PPAYDTL):Integer;
  stdcall;far; external CARD_DLL name 'ks_readpaydtl';

//�޸Ŀ�����
function ks_modifypasswd(phyId,oldPin,newPin:pChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_modifypasswd';

//��������
function ks_resetpasswd(phyId,newPin:pChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_resetpasswd';

//�޸Ŀ�״̬
function ks_modifystatus(state:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_modifystatus';

//���ش�����
function ks_geterrmsg(errmsg:PChar):PChar;
  stdcall;far; external CARD_DLL name 'ks_geterrmsg';

//��ʼ����
function ks_publishusercard(sCardPhyID,szShowCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishusercard';

//����Ƿ���Կ�Ѿ�����
//����ֵ0- δ����1����
function ks_checkloadkeys():Integer;
  stdcall;far; external CARD_DLL name 'ks_checkloadkeys';

//װ����Կ
function ks_loadcardkeys(sKeyCardPwd:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_loadcardkeys';
  
//����Ҫ������SAM����,0Ϊ������1�� 2�� 3 ��ΪSAM1 SAM2 SAM3 
function ks_setcpupara4sam(SAMID:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setcpupara4sam';

//PSAM���ϵ縴λ
function ks_samcpureset():Integer;
  stdcall;far; external CARD_DLL name 'ks_samcpureset';

//����PSAM��
function ks_publishpsamcard(PubPSAMCard:PPUBPSAMCARD):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishpsamcard';

//����PSAM��
function ks_recyclepsamcard():Integer;
  stdcall;far; external CARD_DLL name 'ks_recyclepsamcard';

//��ȡPSAM��
function ks_readpsamcard(PublishPSAMCard:PPUBPSAMCARD):Integer;
  stdcall;far; external CARD_DLL name 'ks_readpsamcard';

//����Ƿ��¡��Կ�Ѿ�����
//����ֵ0- δ����1����
function ks_checkloadclonekeys():Integer;
  stdcall;far; external CARD_DLL name 'ks_checkloadclonekeys';

//װ����Կ����¡��ʹ��
function ks_loadkeys4clone(sKeyCardPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_loadkeys4clone';

////��¡��Կ��
function ks_clonekeycard(sKeyCardPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_clonekeycard';
{
//���տ�����
function ks_recycleusercard(flag:Integer;showCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';
}
//���տ�����
function ks_refineusercard(flag:Integer;showCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';

//���տ�������״̬
function ks_recycleusercard():Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';

function calc_oper_pwd(const oper_code :pChar;const pwd:pchar;text:pchar): LongInt;
  stdcall;far;external DESDLL name 'calc_oper_pwd';

//��������
type

  TCM = class
  private
    Fcard_serialno:string;

    function encryptCardpwd(cut_id:Integer;const seedKey,pwd:pchar;var mpwd:string): longint;
    function Load_Dll: longint;
  public
    //�������������ú���ԭ��
    procedure getVersion(var ver,builddate,desc: string);
    function openDevice(port: Integer; band: Integer): Integer;
    function closeDevice: Integer;
    function beep: Integer;
    function keyCardPublish(sMasterKey,sPin:string): Integer;
    function halt: Integer;
    //function getKey(nKeySerial:Integer;sPin:string;var sKey:string):Integer;

    //���ø��ֶζ�ģʽ
    function setfieldreadmode(mode:Integer):Integer;
    //���ø��ֶ�дģʽ
    function setfieldwritemode(mode:Integer):Integer;
    //���ø��ֶζ�дģʽ
    function setfieldallmode(mode:Integer):Integer;
    //������ֶζ�ģʽ
    function clearfieldreadmode(mode:Integer):Integer;
    //������ֶ�дģʽ
    function clearfieldwritemode(mode:Integer):Integer;
    //������ֶ�����ģʽ
    function clearfieldallmode(mode:Integer):Integer;
    //��������ֶεĶ�ģʽ
    function clearallfieldreadmode():Integer;
    //��������ֶε�дģʽ
    function clearallfieldwritemode():Integer;
    //��������ֶεĶ�дģʽ
    function clearallfieldallmode():Integer;

    //Ѱ��
    function card(var phyId:string):Integer;
    function readCard(phyId:string):Integer;
    function getCardData(mask:Integer;var data:string):Integer;
    function setCardData(mask:Integer;data:string):Integer;
    function writeData(phyId:string):Integer;
    function verifyPin(phyId,pin:string):Integer;

    function clearCard(wv:Tworkview): Integer;
    function changePwd(phyId,oldPin,newPin:String):Integer;
    function resetpasswd(phyId,newPing:string): Integer;
    function modifystatus(status:Integer): Integer;
    function geterrmsg(var errmsg:string):string;

    //����Ϊget��set����
    function getCardSeriNo: string;
    procedure setCardSeriNo(strData: string);

    function getCardNo: string;
    procedure setCardNo(strData: string);

    function getShowCardNo: string;
    procedure setShowCardNo(strData: string);

    function getCardLimitType: string;
    procedure setCardLimitType(strData: string);

    function getPatchNo: string;
    procedure setPatchNo(strData: string);

    function getBlackVer: string;
    procedure setBlackVer(strData: string);

    function getBlackCardSign: string;
    procedure setBlackCardSign(strData: string);

    function getStartUseDate: string;
    procedure setStartUseDate(strData: string);
 
    function getDeadLineDate: string;
    procedure setDeadLineDate(strData: string);
 
    function getReaCardSign: string;
    procedure setReaCardSign(strData: string);
 
    function getCardType: string;
    procedure setCardType(strData: string);

    function getAppType: string;
    procedure setAppType(strData: string);
    function getCardStructVer: string;
    procedure setCardStructVer(strData: string);
    function getSchoolCode: string;
    procedure setSchoolCode(strData: string);
    function getCustNo: string;
    procedure setCustNo(strData: string);
 
    function getCustType: string;
    procedure setCustType(strData: string);
 
    function getStuempNo: string;
    procedure setStuempNo(strData: string);

    function getCustName: string;
    procedure setCustName(strData: string);
 
    function getCustSex: string;
    procedure setCustSex(strData: string);
 
    function getDeptNo: string;
    procedure setDeptNo(strData: string);
 
    function getCertNo: string;
    procedure setCertNo(strData: string);

    function getCertType: string;
    procedure setCertType(strData: string);

    function getBankNo: string;
    procedure setBankNo(strData: string);

    function getCardCnt: string;
    procedure setCardCnt(strData: string);

    function getTransAmt: string;
    procedure setTransAmt(strData: string);
 
    function getTransType: string;
    procedure setTransType(strData: string);

    function getTermId: string;
    procedure setTermId(strData: string);
 
    function getTransDate: string;
    procedure setTransDate(strData: string);

    function getTransTime: string;
    procedure setTransTime(strData: string);
 
    function getMaxPerCount: string;
    procedure setMaxPerCount(strData: string);

    function getMaxPerDay: string;
    procedure setMaxPerDay(strData: string);

    function getCardBalance: string;
    procedure setCardBalance(strData: string);

    function getCardPwd: string;
    procedure setCardPwd(strData: string);

    function getDptCardCnt: string;
    procedure setDptCardCnt(strData: string);

    function getPayCardCnt: string;
    procedure setPayCardCnt(strData: string);

    function getLockCardCnt: string;
    procedure setLockCardCnt(strData: string);

    function getLockTermId: string;
    procedure setLockTermId(strData: string);

    function getLockTransDate: string;
    procedure setLockTransDate(strData: string);
    
    function getLockTransTime: string;
    procedure setLockTransTime(strData: string);

    function getDaySumAmt: string;
    procedure setDaySumAmt(strData: string);

    function getWaterNorOpen: string;
    procedure setWaterNorOpen(strData: string);
  end;

//------------------------------------------------------------------------------
//���ܵ���Ǯ��
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;

//����������
function bj(comport:Integer;outString:string): Integer;

//���п�����ģ��--new
function pubCardNew(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;phyCardId:string;showTip:Integer;var reCode:Integer): string;

//��ֵ��֧ȡʧ�ܳ���ҵ����
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
//���׳�����ʹ�ý��ײο���
function CancelOper(workviewIn: TWorkView;wvRequest:TWVRequest;tradeCode,mac:string): string;

//���СǮ��ȡˮ��
procedure setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);

function getReturn(s1:string;wv:TWorkView):string ;

//����ǰ׼��
function preReadCard: Boolean;

//��ȡPASM��׼��
//function preReadPASM(pasm:TPUBPSAMCARD): Boolean;

//
//procedure preSetMoney(transPack:TTRANSPACK);
//���ض�̬��ʧ����Ϣ
procedure getDllErr;

//����ǰ�жϷ��õ��Ƿ���Ч��
function relCardJudge: Boolean;

//����������ȡһ������Ϣ
function readCardOneInfo(idxNo:Integer): String;

function setOperReadMode(cm:tcm):string;
function setOperWriteMode(cm:tcm):string;

function ksLicence:Integer;

//procedure preReadPayDtl(paydtl:TPAYDTL);

function mfcard(var phyId:string):Integer;

function setMainWorkKey(workKey:string):Integer;
//���ܲ���Ա����
function encOperPwd(operCode,operPwd:string):string;

function setCardBal(tp:TTRANSPACK;cm: TCM;CardPhyID:string):Integer;

function pubSmlBag(cardno,custId,custType:Integer;cardEndDate,oldPhyId:string):Integer;

function getErrMsg:string;

implementation

function setMainWorkKey(workKey:string):Integer;
begin
  Result := ks_setmifare1key(PChar(workKey));
end;
function TCM.encryptCardpwd(cut_id: Integer; const seedKey,pwd: pchar; var mpwd: string): longint;
var
  smpwd:array[0..64] of Char;
begin
  //Result := CardDll.YKT_encrypt_cardpwd(cut_id,seedKey,pwd,smpwd);
  if Result=0 then
    mpwd := StrPas(smpwd);
end;

//����
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;
var
  cm:TCM;
  seedkey:array[0..32] of Char;
  outmpwd:string;
  pwd:array[0..64] of Char;
  st:Integer;
begin
  cm := nil;
  FillChar(seedkey,32,0);
  FillChar(pwd,64,0);
  try
    cm := TCM.Create;
    StrPCopy(seedkey,inseedkey);
    StrPCopy(pwd,inpwd);
    st := cm.encryptCardpwd(custId,seedkey,pwd,outmpwd);
    if st=0 then
      Result := outmpwd;
  finally
    cm.Destroy;    
  end;

end;

function bj(comport:Integer;outString:string): Integer;
begin
  Result := CardDll.dsbdll(comport,outString);
end;

function TCM.Load_Dll: longint;
begin
  Result := Load_Dll;
end;

function TCM.openDevice(port, band: Integer): Integer;
begin
  Result :=  ks_openport(port,band);
end;

function TCM.beep: Integer;
begin
  Result := KNG_beep;
end;

function TCM.closeDevice: Integer;
begin
  Result := ks_closeport;
end;

function TCM.keyCardPublish(sMasterKey,sPin:string): Integer;
begin
  Result := ks_publishkeycard(PChar(sMasterKey),PChar(sPin));
end;

function tcm.halt: Integer;
begin
  Result := ks_halt;
end;
{
function TCM.getKey(nKeySerial: Integer; sPin: string;var sKey: string): Integer;
var
  strKey:array[0..15] of Char;
  st:Integer;
begin
  st := ks_getkey(nKeySerial,PChar(sPin),PChar(@strKey));
  sKey := strKey;
  if st=0 then
    Result := 0
  else
    Result := st;
end;
}
function TCM.clearallfieldallmode: Integer;
begin
  Result := ks_clearallfieldallmode;
end;

function TCM.clearallfieldreadmode: Integer;
begin
  Result := ks_clearallfieldreadmode;
end;

function TCM.clearallfieldwritemode: Integer;
begin
  Result := ks_clearallfieldwritemode;
end;

function TCM.clearfieldallmode(mode: Integer): Integer;
begin
  Result := ks_clearfieldallmode(mode);
end;

function TCM.clearfieldreadmode(mode: Integer): Integer;
begin
  Result := ks_clearfieldreadmode(mode);
end;

function TCM.clearfieldwritemode(mode: Integer): Integer;
begin
  Result := ks_clearfieldwritemode(mode);
end;

function TCM.setfieldallmode(mode: Integer): Integer;
begin
  Result := ks_setfieldallmode(mode);
end;

function TCM.setfieldreadmode(mode: Integer): Integer;
begin
  Result := ks_setfieldreadmode(mode);
end;

function TCM.setfieldwritemode(mode: Integer): Integer;
begin
  Result := ks_setfieldwritemode(mode);
end;

function TCM.card(var phyId: string): Integer;
var
  rePhyid : array[0..16] of Char;
  st:Integer;
begin
  FillChar(rePhyid,17,0);
  st := ks_card(PChar(@rePhyid));
  if st=0 then
  begin
    phyId := rePhyid;
    Result := 0;
  end
  else
    Result := st;
end;

function mfcard(var phyId: string): Integer;
var
  rePhyid : array[0..16] of Char;
  st:Integer;
begin
  FillChar(rePhyid,17,0);
  st := ks_card(PChar(@rePhyid));
  if st=0 then
  begin
    phyId := rePhyid;
    Result := 0;
  end
  else
    Result := st;
end;

function TCM.readCard(phyId:string): Integer;
//var
  //phyId:string;
  //st:Integer;
begin
{
  st := card(phyId);
  if st=0 then
  begin
    setCardSeriNo(phyId);
    Result := ks_readcard;
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ���źÿ����ԣ�������:'+inttostr(st));
    Result := st;
  end;
  }
  setCardSeriNo(phyId);
  Result := ks_readcard;

end;

function TCM.getCardData(mask: Integer; var data: string): Integer;
var
  reData:array[0..128] of Char;
  st : Integer;
begin
  FillChar(reData,128,0);
  st := ks_getfieldval(mask,PChar(@reData));
  if st=0 then
  begin
    data := reData;
    Result := 0;
  end
  else
  begin
    data := '';
    Result := st;
  end;

end;

function TCM.setCardData(mask: Integer; data: string): Integer;
begin
  Result := ks_setfieldval(mask,PChar(data));
end;

function TCM.writeData(phyId:string): Integer;
//var
  //phyId:string;
  //st:Integer;
begin
  {
  //phyId := 0;
  st := card(phyId);
  if st=0 then
    Result := ks_writecard(PChar(phyId))
  else
    Result := st;
  }
  Result := ks_writecard(PChar(phyId));
end;

function TCM.verifyPin(phyId,pin: string): Integer;
var
  cPin:array[0..6] of Char;
begin
  FillChar(cPin,7,0);
  StrPCopy(cPin,pin);
  Result := ks_verifypin(PChar(phyId),cpin);
end;

function TCM.clearCard(wv:Tworkview): Integer;
var
  cm:TCM;
  tradeDate,tradeTime:string;
  payCnt,dptCnt,subsidyNo,balance:Integer;
  st:Integer;
  tp:TTRANSPACK;
  //reErrMsg:array[0..255] of Char;
  //reSt : PChar;
  phyId:string;
begin
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ���ѿ����úã�');
      result := -1;
      exit;
    end;
    cm.clearallfieldwritemode;
    cm.setfieldwritemode(BLACK_CARD_SIGN);
    cm.setBlackCardSign(IntToStr(DESTORY));
    st := cm.writeData(phyid);
    if st<>0 then
    begin
      Result := st;
      Exit;
    end;
    //��ȡ����Ϣ
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(PATCH_NO);
    cm.setfieldreadmode(CARD_BALANCE);
    try
      st := cm.readCard(phyid);
    except
      Result := -1;
      Exit;
    end;
    if st<>0 then
    begin
      Result := st;
      Exit;
    end;
    try
      payCnt := StrToInt(cm.getPayCardCnt);
      dptCnt := StrToInt(cm.getDptCardCnt);
      subsidyNo := StrToInt(cm.getPatchNo);
      balance := StrToInt(cm.getCardBalance);
    except
      payCnt := 0;
      dptCnt := 0;
      subsidyNo := 0;
      balance := 0;
    end;
    if balance<>0 then
    begin
      tradeDate := wv.fieldbyname('ҵ������').Data.AsString;
      tradeTime := wv.fieldbyname('ҵ��ʱ��').Data.AsString;
      //preSetMoney(tp);
      ZeroMemory(@tp,SizeOf(tp));
      //�ն˽������к�
      tp.TermSeqno := 1;
      //�ն˱��
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //���׿���
      tp.CardNo := StrToInt(cm.getCardNo);
      //������
      StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
      //��������
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //����ʱ��
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //����ǰ���
      tp.BefBalance := balance;
      //���׺���
      tp.AftBalance := 0;
      //����ǰ��ֵ����
      tp.DptCardCnt := dptCnt;
      //����ǰ���Ѵ���
      tp.PayCardCnt := payCnt;
      //����ǰ��������
      tp.SubsidyNo := subsidyNo;
      try
        st := setCardBal(tp,cm,phyId);//ks_setcardbal(@tp);
        if st<>0 then
        begin
          Result := st;
          Exit;
        end;
      except
        Result := -3;
        Exit;
      end;
    end;
    Result := 0;
  finally
    cm.Destroy;
  end;
end;

function TCM.changePwd(phyId,oldPin,newPin:String):Integer;
var
  cOldPin : array[0..6] of Char;
  cNewPin : array[0..6] of char;
begin
  FillChar(cOldPin,6,0);
  FillChar(cNewPin,6,0);
  StrPCopy(cOldPin,OldPin);
  StrPCopy(cNewPin,newPin);
  Result := ks_modifypasswd(PChar(phyId),coldPin,cnewPin);
end;

function TCM.modifystatus(status: Integer): Integer;
begin
  Result := ks_modifystatus(status);
end;

function TCM.geterrmsg(var errmsg: string): string;
var
  reErrMsg:array[0..255] of Char;
  reSt : PChar;//array[0..255] of Char;
begin
  reSt := ks_geterrmsg(PChar(@reErrMsg));
  errmsg := reErrMsg;
  Result := reSt;
end;

function TCM.resetpasswd(phyId,newPing: string): Integer;
var
  cnewpin:array[0..6] of char;
begin
  FillChar(cnewpin,6,0);
  StrPCopy(cnewpin,newPing);
  Result := ks_resetpasswd(PChar(phyId),cnewpin);
end;

{-------------------------------------------------------------------------------
  ������:    TCM.cashOperCancel��������ģ��
  ����:      hanjiwei
  ����:      2009.04.16
  ����:      workviewIn: TWorkView; wvRequest: TWVRequest; operDate: string; seriId, stationId: Integer
  ����ֵ:    string
-------------------------------------------------------------------------------}
function pubCardNew(workviewIn,workviewOut: TWorkView;
  wvRequest:TWVRequest;phyCardId:string;showTip:Integer;var reCode:Integer): string;
var
  cardNo:Integer;           //���׿���
  showCardNo:string;        //��ʾ����
  cardEndDate:string;       //��ʹ�ý�������
  cardLimitType:string;     //��ʹ��Ȩ��
  custType:string;          //�ͻ����
  custName:string;          //�ͻ�����
  certType:string;          //֤������
  cardID:string;            //���֤��
  depNo:string;             //���Ŵ���
  custSex:string;           //�Ա�
  stuempNo:string;          //ѧ����
  cardBalance:Real;         //�����
  cardPWD:string;           //������
  sOper:string;             //��������Ա
  sOperDate:string;         //��������
  maxPerCount:string;       //���������޶�
  maxPerDay:string;         //�������޶�
  relCardSign:string;       //���з���ʶ
  cardType:string;          //������
  custId:string;            //�ͻ���
  tradeDate:string;         //��������
  tradeTime : string;       //����ʱ��
  //areaCode:string;          //У������
  cardVer:string;           //���汾��
  
  tp:TTRANSPACK;
  //tof:Integer;
  cm:TCM;
  re:Integer;
  readCardNo:Integer;
  phyId:string;
  //rst:integer;
  payCnt,dptCnt:Integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  cardNo:=workviewIn.fieldbyname('����').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('��ʾ����').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('��������').Data.AsString;
  cardLimitType:=workviewIn.fieldbyname('�շ����').Data.AsString;
  custType:=workviewIn.fieldbyname('�ͻ����').Data.AsString;
  custName:=workviewIn.fieldbyname('�ͻ�����').Data.AsString;
  certType:=workviewIn.fieldbyname('֤������').Data.AsString;
  cardID:=workviewIn.fieldbyname('֤������').Data.AsString;
  depNo:=workviewIn.fieldbyname('���Ŵ���').Data.AsString;
  custSex:=workviewIn.fieldbyname('�Ա�').Data.AsString;
  stuempNo:=workviewIn.fieldbyname('ѧ����').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('����ֵ').Data.AsFloat;
  cardPWD:=workviewIn.fieldbyname('������').Data.AsString;
  relCardSign := workviewIn.fieldbyname('���з���ʶ').Data.AsString;

  cardVer := workviewIn.fieldbyname('�汾��').Data.AsString;

  //areacode:=workviewIn.fieldbyname('ԺУ����').Data.AsString;
  sOper := workviewIn.fieldbyname('����Ա').Data.AsString;
  sOperDate := workviewIn.fieldbyname('ҵ������').Data.AsString;
  cardType := workviewIn.fieldbyname('������').Data.AsString;
  custId := workviewIn.fieldbyname('�ͻ���').Data.AsString;
  tradeDate := workviewIn.fieldbyname('ҵ������').Data.AsString;
  tradeTime := workviewIn.fieldbyname('ҵ��ʱ��').Data.AsString;
  cm := nil;
  try
    cm := TCM.Create;
    re := cm.card(phyId);
    if re<>0 then
    begin
      reCode := -3;
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�������ý��ף�');
      exit;
    end;
    if phyId<>phyCardId then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('���õĿ������źͷ��ͽ��׵Ŀ������Ų�����������ý��ף�');
      exit;
    end;
    cm.clearallfieldwritemode;
    //����Ҫд������Ϣ
    cm.setCardNo(IntToStr(cardNo));
    cm.setShowCardNo(showCardNo);
    cm.setDeadLineDate(cardEndDate);
    cm.setCardLimitType(cardLimitType);
    cm.setCustType(custType);
    cm.setDeptNo(depNo);
    cm.setCustName(custName);
    cm.setCertType(certType);
    cm.setCertNo(cardID);
    cm.setCustSex(custSex);
    cm.setStuempNo(stuempNo);
    cm.setReaCardSign(relCardSign);
    cm.setCardType(cardType);
    //cm.setSchoolCode(areaCode);
    cm.setCustNo(custId);
    cm.setCardPwd(cardPWD);
    cm.setBlackCardSign(IntToStr(NORMAL_CARD));
    cm.setBlackVer(cardVer);
    //���õ��������޶���������޶�
    if maxPer=1 then
    begin
      maxPerCount := workviewIn.fieldbyname('�����޶�').Data.AsString;
      maxPerDay := workviewIn.fieldbyname('���޶�').Data.AsString;
      cm.setMaxPerCount(maxPerCount);
      cm.setMaxPerDay(maxPerDay);
    end;
    re := cm.writeData(phyId);

    cm.clearallfieldreadmode;
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    cm.setfieldreadmode(CARD_NO);
    if cm.readCard(phyId)<>0 then
    begin
      payCnt:=0;
      dptCnt:=0;
      readCardNo := 0;
    end
    else
    begin
      dptCnt:=StrToInt(cm.getDptCardCnt);
      payCnt := StrToInt(cm.getPayCardCnt);
      readCardNo := StrToInt(cm.getCardNo);
    end;
    //�������Ϊ�㣬����Ϣû��д�ϣ���ʾ���¿���Ϣ�����
    if ((readCardNo=0) or (re<>0)) then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      reCode := -1;
      Result:='д��������Ϣʧ��['+reSt+']������¿���Ϣ�������';
      Exit;
    end
    else
    begin
      //д���ɹ�����ó�ֵ�����������ý��--------
      if (cardBalance = 0) then
      begin
        re := 0;
      end
      else
      begin
        ZeroMemory(@tp,SizeOf(tp));
        //�ն˽������к�
        tp.TermSeqno := 1;
        //�ն˱��
        StrCopy(@tp.Termno,PChar(scSiteNo));
        //���׿���
        tp.CardNo := cardNo;
        //������
        StrCopy(@tp.CardPhyID,PChar(phyId));
        //��������
        StrCopy(@tp.TransDate,PChar(tradeDate));
        //����ʱ��
        StrCopy(@tp.TransTime,PChar(tradeTime));
        //����ǰ���
        tp.BefBalance := 0;
        //���׺���
        tp.AftBalance := StrToInt(floattostr(cardBalance));
        //����ǰ��ֵ����
        tp.DptCardCnt := dptCnt;
        //����ǰ���Ѵ���
        tp.PayCardCnt := payCnt;
        //����ǰ��������
        tp.SubsidyNo := 0;
        re := setCardBal(tp,cm,phyId);
      end;
      
      if re=0 then
      begin
        reCode := 0;
        if showTip=1 then
        begin
          context.GetDialogSystem.ShowMessage('д����Ϣ�ɹ�,�ÿ��Ŀ���Ϊ:' + IntToStr(cardNo));
        end;
        Result:=workviewIn.FieldByName('������Ϣ').Data.AsString;
      end
      else
      begin
        //д���ɹ��������ý��ʧ��
        reCode := 1;
        if showTip=1 then
        begin
          context.GetDialogSystem.ShowMessage('д��������Ϣ�ɹ������ý��ʧ�ܣ����������');
        end;
        Result:=workviewIn.FieldByName('������Ϣ').Data.AsString+',���ý��ʧ�ܣ�����������';
      end;
    end;
  finally
    cm.Destroy;
  end;
end;


{-------------------------------------------------------------------------------
  ������:    TCM.pubCardNew��ֵ��֧ȡʧ������������
  ����:      hanjiwei
  ����:      2009.04.16
  ����:      workviewIn, workviewOut: TWorkView; wvRequest: TWVRequest; phyCardId: string; showTip: Integer
  ����ֵ:    string
-------------------------------------------------------------------------------}
function cashOperCancel(
  workviewIn: TWorkView;
  wvRequest:TWVRequest;operDate:string;
  seriId:Integer;stationId:Integer): string;
begin
  workviewIn.FieldByName('�ն˱��').Data.SetInteger(stationId);
  workviewIn.FieldByName('��ˮ��').Data.SetInteger(seriId);
  workviewIn.FieldByName('ҵ������').Data.SetString(operDate);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('������').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('����ʧ�ܣ����ڽ��׳����д���ü�¼����������ҵ��');
    Result := '����ʧ��--'+
    workviewIn.fieldbyname('������Ϣ').Data.AsString+',���ڽ��׳����д���ü�¼����������ҵ��';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('ҵ��ʧ�ܣ������²�������ҵ��');
    Result := 'ҵ��ʧ�ܣ������²�������ҵ��';
  end;

end;

{-------------------------------------------------------------------------------
  ������:    TCM.pubCardNew��ֵ��֧ȡʧ������������
  ����:      hanjiwei
  ����:      2009.04.16
  ����:      workviewIn, workviewOut: TWorkView; wvRequest: TWVRequest; phyCardId: string; showTip: Integer
  ����ֵ:    string
-------------------------------------------------------------------------------}
function CancelOper(workviewIn: TWorkView;wvRequest:TWVRequest;tradeCode,mac:string): string;
begin
  workviewIn.FieldByName('���ײο���').Data.SetString(tradeCode);
  workviewIn.FieldByName('�����').Data.SetString(mac);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('������').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('����ʧ�ܣ����ڽ��׳����д���ü�¼����������ҵ��');
    Result := '����ʧ��--'+
    workviewIn.fieldbyname('������Ϣ').Data.AsString+',���ڽ��׳����д���ü�¼����������ҵ��';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('ҵ��ʧ�ܣ������²�������ҵ��');
    Result := 'ҵ��ʧ�ܣ������²�������ҵ��';
  end;

end;

procedure setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);
var
  tempData:TDataSet;
begin
  wvWater.FieldByName('�շ����').Data.SetInteger(feeType);
  wvWater.FieldByName('������־').Data.SetString('R');
  try
    wvrWater.SendCommand;
    //ShowMessage('111');
    if wvWater.FieldByName('������').Data.AsString<>'0' then
    begin
      cpuWaterPrice1 := 0;
      cpuWaterPrice2 := 0;
      cpuWaterPrice3 := 0;
    end;
    ///ShowMessage('222');
    tempData := TDataSet(wvWater.FieldByName('��ѯ�����').Data.AsObject);
    //ShowMessage('333');
    //tempData.First;
    cpuWaterPrice1 := tempData.fieldbyname('lvol0').AsInteger;
    //ShowMessage('444');
    cpuWaterPrice2 := tempData.fieldbyname('lvol1').AsInteger;
    cpuWaterPrice3 := tempData.fieldbyname('lvol2').AsInteger;
  except
    on e:Exception do
    begin
      //ShowMessage(e.Message);
    cpuWaterPrice1 := 0;
    cpuWaterPrice2 := 0;
    cpuWaterPrice3 := 0;
    end;
  end;
end;

function getReturn(s1:string;wv:TWorkView):string ;
begin
  ConText.GetDialogSystem.showmessage(s1+wv.FieldByName('������Ϣ').Data.AsString);
end;

procedure getDllErr;
var
  reErr:string;
begin
  ks_geterrmsg(PChar(reErr));
  Context.GetDialogSystem.ShowMessage(reErr);
end;

function setCardBal(tp:TTRANSPACK;cm: TCM;CardPhyID:string):Integer;
var
  st:Integer;
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
  newPhyId: string;
  nowTime:Cardinal;
  writeMoney:Integer;
begin
  st := ks_setcardbal(@tp);
  writeMoney := tp.AftBalance;
  if st<>0 then
  begin
    while (1>0) do
    begin
      //�ж��Ƿ���;�ο�
      if tp.cGetProveFlag>Char(0) then
      begin
        //ѭ��Ѱ��
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>overTime then
          begin
            //ʱ�����10�룬��ʾ��ʱ���˳�
            ks_dotransunprove(@tp);
            Context.GetDialogSystem.ShowMessage('Ѱ����ʱ����ʹ�ÿ����������ÿ���');
            Result := -2;
            Exit;
          end;

          st := cm.card(newPhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
          end
          else
          begin
            //Ѱ�������ж��Ƿ�Ϊͬһ�ſ���������ǣ���ʾ���·ſ�
            if newPhyId<>CardPhyID then
              Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ��������·��ã�')
            else
              Break;
          end;
          Continue;
        end;
        Sleep(50);
        st:=ks_gettransprove(2,tp.PayCardCnt+1);
        if st=0 then
          Break;
        st:=ks_setcardbal(@tp);
        if st=0 then
          Break;
      end
      else
      begin
        //�ۿ�ʧ�ܣ�1�����ԡ�0������Ϣ���˳�
        if tp.cRetryFlag=Char(1) then
        begin
          //ѭ��Ѱ��
          nowTime := GetTickCount;
          while (1>0) do
          begin
            if (GetTickCount-nowTime)>overTime then
            begin
              //ʱ�����10�룬��ʾ��ʱ���˳�
              ks_dotransunprove(@tp);
              Context.GetDialogSystem.ShowMessage('Ѱ����ʱ����ʹ�ÿ����������ÿ���');
              Result := -1;
              Exit;
            end;

            st := cm.card(newPhyId);
            if st<>0 then
            begin
              Context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ���');
            end
            else
            begin
              //Ѱ�������ж��Ƿ�Ϊͬһ�ſ���������ǣ���ʾ���·ſ�
              if newPhyId<>CardPhyID then
                Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ��������·��ã�')
              else
                Break;
            end;
            Continue;
          end;
          Sleep(50);
          //����һ��
          st := ks_setcardbal(@tp);
          if st = 0 then
            Break;
        end
        else if tp.cRetryFlag=Char(0) then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('д���ʧ�ܣ���ʹ�ÿ����������ÿ����-'+reSt);
          Result := -3;
          Exit;
        end;
      end;
      Continue;
    end;
  end;
  //���¶������жϽ���Ƿ�д�ɹ������û��д�ɹ�����ʾ��������

  try
    st := cm.card(newPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ�����ȡ�������Ϣ���Ƿ�д���ɹ���');
      Result := -4;
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_BALANCE);

    if newPhyId<>CardPhyID then
    begin
      Context.GetDialogSystem.ShowMessage('���õĿ��͸ղŷ��õĲ���ͬһ�ſ�����ȡ�������Ϣ���Ƿ�д���ɹ���');
      Result := -5;
      Exit;
    end;
    st := cm.readCard(newPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ������·ſ�����ȡ�����Ƿ�д���ɹ���');
      Result := -6;
      Exit;
    end;
    if StrToInt(cm.getCardBalance)<>writeMoney then
    begin
      Context.GetDialogSystem.ShowMessage('������Ҫд������ȣ���鿴��д���Ƿ���������ʹ�ÿ����������ÿ���');
      Result := -7;
      Exit;
    end;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowMessage('����ʧ�ܣ������·ſ�����ȡ�����Ƿ�д���ɹ�-'+e.Message);
      Result := -8;
      Exit;
    end;
  end;
  
  Result := 0;
end;

function pubSmlBag(cardno,custId,custType:Integer;cardEndDate,oldPhyId:string):Integer;
var
  waterCard:TWATERCOMMPACK;
  st:Integer;
  phyId:string;
  i:Integer;
  smlBagNo:Integer;
begin
  st := mfcard(phyId);
  if st<>0 then
  begin
    //Ѱ��ʧ��
    result := -100;
    Exit;
  end;
  if phyId<>oldPhyId then
  begin
    //Ҫ��ʼ����СǮ������������ͬһ�ſ�
    Result := -200;
    Exit;
  end;
  for i:= 0 to waterStrings.Count-1 do
  begin
    try
      smlBagNo := StrToInt(waterStrings[i]);
    except
      smlBagNo :=0;
    end;
    waterCard.cardno := cardNo;
    waterCard.custno := custId;
    watercard.custtype := custType;
    StrCopy(@waterCard.expireddate,PChar(cardEndDate));
    waterCard.lockflag := 255;
    waterCard.money := 0;
    waterCard.totalmoney := 0;
    StrCopy(@waterCard.addtime,PChar('00000000000000'));
    waterCard.addcount := 0;
    waterCard.price1 := cpuWaterPrice1;
    waterCard.price2 := cpuWaterPrice2;
    waterCard.price3 := cpuWaterPrice3;
    //ShowMessage(waterStrings[i]);
    st := ks_water_publishcard(smlBagNo,@waterCard);    
    if st<>0 then
    begin
      Result := st;
      Exit;
    end;
  end;
  result := 0;
end;

function getErrMsg:string;
var
  reErrMsg:array[0..255] of Char;
  reSt : PChar;
begin
  reSt := ks_geterrmsg(PChar(@reErrMsg));
  result := rest;
end;
{
//��ȡPASM��׼��
function preReadPASM(pasm:TPUBPSAMCARD): Boolean;
begin
  try
    FillChar(pasm.CardNo,SizeOf(pasm.CardNo),0);
    FillChar(pasm.TermID,SizeOf(pasm.TermID),0);
    FillChar(pasm.StartDate,SizeOf(pasm.StartDate),0);
    FillChar(pasm.ExpireDate,SizeOf(pasm.ExpireDate),0);
    FillChar(pasm.PublishID,SizeOf(pasm.PublishID),0);
    FillChar(pasm.UserID,SizeOf(pasm.UserID),0);
    Result := True;
  except
    Result := False;
  end;
end;

procedure preReadPayDtl(paydtl:TPAYDTL);
begin
  FillChar(paydtl.transdate,SizeOf(paydtl.transdate),0);
  FillChar(paydtl.transtime,SizeOf(paydtl.transtime),0);
  FillChar(paydtl.termno,SizeOf(paydtl.termno),0);
end;

procedure preSetMoney(transPack:TTRANSPACK);
begin
  FillChar(transPack.CardPhyID,SizeOf(transPack.CardPhyID),0);
  FillChar(transPack.TransDate,SizeOf(transPack.TransDate),0);
  FillChar(transPack.TransTime,SizeOf(transPack.TransTime),0);
  FillChar(transPack.Termno,SizeOf(transPack.Termno),0);
  FillChar(transPack.Random,SizeOf(transPack.Random),0);
  FillChar(transPack.OperCode,SizeOf(transPack.OperCode),0);
  FillChar(transPack.VoucherNo,SizeOf(transPack.VoucherNo),0);
  FillChar(transPack.RefNo,SizeOf(transPack.RefNo),0);
  FillChar(transPack.Mac,SizeOf(transPack.Mac),0);
  //ShowMessage(IntToStr(SizeOf(transPack.Termno)));
  //ShowMessage(transPack.Termno);
end;
}
function preReadCard: Boolean;
begin
  Result:=True;
  if not SmartCardPortStatus then
  begin
    Context.GetDialogSystem.ShowMessage('���ȴ򿪴���,Ȼ���ٽ��в�����');
    Result:=False;
  end;
end;

function ksLicence:Integer;
begin
  Result := ks_licence('','123456');
end;

function relCardJudge: Boolean;
var
  cm:TCM;
  cardNo:string;
  cardStatus:string;
  dptCardCnt,payCardCnt:string;
  //Cid:Integer;
  phyId:string;
  st:integer;
begin
  Result:=True;
  if preReadCard=False then
  begin
    Result:=False;
    Exit;
  end;
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ�!');
      result := false;
      exit;
    end;

    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_NO);
    cm.setfieldreadmode(DPT_CARD_CNT);
    cm.setfieldreadmode(PAY_CARD_CNT);
    //cm.setfieldreadmode(SSD_CARD_CNT);
    cm.setfieldreadmode(BLACK_CARD_SIGN);
    try
      cm.readCard(phyId);
    except
      Result := False;
      Exit;
    end;
    {
    if cm.getCardSeriNo='' then
    begin
      context.GetDialogSystem.ShowMessage('�������к�ʧ�ܣ��ÿ��Ѿ��𻵣�');
      Result := False;
      Exit;
    end;
    }
    cardNo := cm.getCardNo;
    if cardNo='-1' then
    begin
      Context.GetDialogSystem.ShowMessage('�����׿���ʧ�ܣ��ÿ�û�г�ʼ����');
      Result := False;
      Exit;
    end;
    //�ж��Ƿ�Ϊ�����Ŀ������Ϊ�����Ŀ�����ֵ���������Ѵ�����Ϊ0�������·���
    //����ֻ���Ȼ��տ���Ȼ���ʼ���������ܷ���
    cardStatus := cm.getBlackCardSign;
    dptCardCnt := cm.getDptCardCnt;
    payCardCnt := cm.getPayCardCnt;
    if cardStatus=IntToStr(DESTORY) then
      if (dptCardCnt<>'0')or(payCardCnt<>'0') then
      begin
        Context.GetDialogSystem.ShowMessage('�ÿ��Ѿ�ע�������Ȼ��ոÿ���Ȼ���ٷ��У�');
        Result := False;
        Exit;
      end;
  finally
    cm.Destroy;
  end;
end;

//��������ֵ��ȡ����Ϣ
function readCardOneInfo(idxNo:Integer): String;
var
  cm:TCM;
  st:Integer;
  strData:string;
  phyId:string;
begin
  cm := nil;
  try
    cm := TCM.Create;
    st := cm.card(phyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('Ѱ��ʧ�ܣ�����úÿ�!');
      result := '';
      exit;
    end;

    cm.clearallfieldreadmode;
    cm.setfieldreadmode(idxNo);
    if idxNo = CARD_SERI_NO then
    begin
      //cm.card(phyId);
      Result := phyId;
    end
    else
    begin
      st := cm.readCard(PhyId);
      if st<>0 then
      begin
        //Context.GetDialogSystem.ShowMessage('������Ϣʧ�ܣ����鿨�Ƿ�ź�-'+inttostr(st));
        Exit;
      end;
      st := cm.getCardData(idxNo,strData);
      if st=0 then
        Result := strData
      else
        Result := '';
    end;
  finally
    cm.Destroy;           
  end;
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

{-------------------------------------------------------------------------------
  ������:    TCM.getVersionȡ��̬��汾��
  ����:      hanjiwei
  ����:      2009.04.20
  ����:      var ver: string
  ����ֵ:    ��
-------------------------------------------------------------------------------}
procedure TCM.getVersion(var ver,builddate,desc: string);
var
  returnVer:array[0..128] of Char;
  reBuildDate:array[0..20] of Char;
  reDesc:array[0..128] of char;
begin
  ks_getversioninfo(PChar(@returnVer),PChar(@reBuildDate),PChar(@reDesc));
  ver := returnVer;
  builddate := reBuildDate;
  desc := reDesc;
end;

//******************************************************************************get��set����
//setOperReadMask���ö�ȡ��д��Ȩ��
//����û�ж�ȡ������Ȩ�޵Ĺ������Ӵ�
function setOperReadMode(cm:tcm):string;
var
  retStr :string;
  st:Integer;
begin
  st := cm.setfieldreadmode(CARD_SERI_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_SERI_NO);
  st := cm.setfieldreadmode(CARD_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_NO);
  st := cm.setfieldreadmode(SHOW_CARDNO);
  if st<>0 then
    retStr := retstr+','+IntToStr(SHOW_CARDNO);
  st := cm.setfieldreadmode(CARD_LIMIT_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_LIMIT_TYPE);
  st := cm.setfieldreadmode(PATCH_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(PATCH_NO);
  st := cm.setfieldreadmode(BLACK_VER);
  if st<>0 then
    retStr := retstr+','+IntToStr(BLACK_VER);
  st := cm.setfieldreadmode(BLACK_CARD_SIGN);
  if st<>0 then
    retStr := retstr+','+IntToStr(BLACK_CARD_SIGN);
  st := cm.setfieldreadmode(START_USE_DATE);
  if st<>0 then
    retStr := retstr+','+IntToStr(START_USE_DATE);
  st := cm.setfieldreadmode(DEADLINE_DATE);
  if st<>0 then
    retStr := retstr+','+IntToStr(DEADLINE_DATE);
  st := cm.setfieldreadmode(REL_CARD_SIGN);
  if st<>0 then
    retStr := retstr+','+IntToStr(REL_CARD_SIGN);
  st := cm.setfieldreadmode(CARD_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_TYPE);
  st := cm.setfieldreadmode(APP_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(APP_TYPE);

  st := cm.setfieldreadmode(CARD_STRUCT_VER);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_STRUCT_VER);
  st := cm.setfieldreadmode(SCHOOL_CODE);
  if st<>0 then
    retStr := retstr+','+IntToStr(SCHOOL_CODE);
  st := cm.setfieldreadmode(CUST_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(CUST_NO);
  st := cm.setfieldreadmode(CUST_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(CUST_TYPE);
  st := cm.setfieldreadmode(STUEMP_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(STUEMP_NO);
  st := cm.setfieldreadmode(CUST_NAME);
  if st<>0 then
    retStr := retstr+','+IntToStr(CUST_NAME);
  st := cm.setfieldreadmode(CUST_SEX);
  if st<>0 then
    retStr := retstr+','+IntToStr(CUST_SEX);
  st := cm.setfieldreadmode(DEPT_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(DEPT_NO);
  st := cm.setfieldreadmode(CERTIFICATE_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(CERTIFICATE_NO);
  st := cm.setfieldreadmode(CERTIFICATE_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(CERTIFICATE_TYPE);
  st := cm.setfieldreadmode(BANK_NO);
  if st<>0 then
    retStr := retstr+','+IntToStr(BANK_NO);
  {
  st := cm.setfieldreadmode(CARD_CNT);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_CNT);
  st := cm.setfieldreadmode(TRANS_AMT);
  if st<>0 then
    retStr := retstr+','+IntToStr(TRANS_AMT);
  st := cm.setfieldreadmode(TRANS_TYPE);
  if st<>0 then
    retStr := retstr+','+IntToStr(TRANS_TYPE);
  st := cm.setfieldreadmode(TERM_ID);
  if st<>0 then
    retStr := retstr+','+IntToStr(TERM_ID);
  st := cm.setfieldreadmode(TRANS_DATE);
  if st<>0 then
    retStr := retstr+','+IntToStr(TRANS_DATE);
  st := cm.setfieldreadmode(TRANS_TIME);
  if st<>0 then
    retStr := retstr+','+IntToStr(TRANS_TIME);
  }
  st := cm.setfieldreadmode(MAX_PER_COUNT);
  if st<>0 then
    retStr := retstr+','+IntToStr(MAX_PER_COUNT);
  st := cm.setfieldreadmode(MAX_PER_DAY);
  if st<>0 then
    retStr := retstr+','+IntToStr(MAX_PER_DAY);
  st := cm.setfieldreadmode(CARD_BALANCE);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_BALANCE);
  {
  st := cm.setfieldreadmode(CARD_PWD);
  if st<>0 then
    retStr := retstr+','+IntToStr(CARD_PWD);
  }
  st := cm.setfieldreadmode(DPT_CARD_CNT);
  if st<>0 then
    retStr := retstr+','+IntToStr(DPT_CARD_CNT);
  st := cm.setfieldreadmode(PAY_CARD_CNT);
  if st<>0 then
    retStr := retstr+','+IntToStr(PAY_CARD_CNT);

  {
  st := cm.setfieldreadmode(LOCK_CARD_CNT);
  if st<>0 then
    retStr := retstr+','+IntToStr(LOCK_CARD_CNT);
  }
  Result := retStr;
end;

function setOperWriteMode(cm:tcm):string;
begin
  //һ���յ�ʵ�ַ���������дģʽ��setֵ֮ǰ��ֻ�������˸�ֵ������дģʽ
  //ȫ�����������дֵ���������е�ֵ
end;


//CardSeriNo--get����(�����к�)
function TCM.getCardSeriNo: string;
begin
  Result := Fcard_serialno;
end;

//CardSeriNo--set����(�����к�)
procedure TCM.setCardSeriNo(strData: string);
begin
  Fcard_serialno := strData;
end;

//CardNo--get����(���׿���)
function TCM.getCardNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '-1';
end;
 
//CardNo--set����(���׿���)
procedure TCM.setCardNo(strData: string);
begin
  setfieldwritemode(CARD_NO);
  setCardData(CARD_NO,strData);
end;
 
//ShowCardNo--get����(��ʾ����)
function TCM.getShowCardNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(SHOW_CARDNO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//ShowCardNo--set����(��ʾ����)
procedure TCM.setShowCardNo(strData: string);
begin
  setfieldwritemode(SHOW_CARDNO);
  setCardData(SHOW_CARDNO,strData);
end;
 
//CardLimitType--get����(�շ����)
function TCM.getCardLimitType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_LIMIT_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CardLimitType--set����(�շ����)
procedure TCM.setCardLimitType(strData: string);
begin
  setfieldwritemode(CARD_LIMIT_TYPE);
  setCardData(CARD_LIMIT_TYPE,strData);
end;
 
//PatchNo--get����(�������κ�)
function TCM.getPatchNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(PATCH_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//PatchNo--set����(�������κ�)
procedure TCM.setPatchNo(strData: string);
begin
  setfieldwritemode(PATCH_NO);
  setCardData(PATCH_NO,strData);
end;
 
//BlackVer--get����(���汾��)
function TCM.getBlackVer: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(BLACK_VER,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//BlackVer--set����(���汾��)
procedure TCM.setBlackVer(strData: string);
begin
  setfieldwritemode(BLACK_VER);
  setCardData(BLACK_VER,strData);
end;
 
//BlackCardSign--get����(��״̬)
function TCM.getBlackCardSign: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(BLACK_CARD_SIGN,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//BlackCardSign--set����(��״̬)
procedure TCM.setBlackCardSign(strData: string);
begin
  setfieldwritemode(BLACK_CARD_SIGN);
  setCardData(BLACK_CARD_SIGN,strData);
end;
 
//StartUseDate--get����(��������)
function TCM.getStartUseDate: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(START_USE_DATE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//StartUseDate--set����(��������)
procedure TCM.setStartUseDate(strData: string);
begin
  setfieldwritemode(START_USE_DATE);
  setCardData(START_USE_DATE,strData);
end;
 
//DeadLineDate--get����(��������)
function TCM.getDeadLineDate: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(DEADLINE_DATE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//DeadLineDate--set����(��������)
procedure TCM.setDeadLineDate(strData: string);
begin
  setfieldwritemode(DEADLINE_DATE);
  setCardData(DEADLINE_DATE,strData);
end;
 
//ReaCardSign--get����(��������ʶ)
function TCM.getReaCardSign: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(REL_CARD_SIGN,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//ReaCardSign--set����(��������ʶ)
procedure TCM.setReaCardSign(strData: string);
begin
  setfieldwritemode(REL_CARD_SIGN);
  setCardData(REL_CARD_SIGN,strData);
end;
 
//CardType--get����(�����)
function TCM.getCardType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CardType--set����(�����)
procedure TCM.setCardType(strData: string);
begin
  setfieldwritemode(CARD_TYPE);
  setCardData(CARD_TYPE,strData);
end;

//APP_TYPE--get����(Ӧ�����)
function TCM.getAppType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(APP_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//APP_TYPE--set����(���ṹ�汾)
procedure TCM.setAppType(strData: string);
begin
  setfieldwritemode(APP_TYPE);
  setCardData(APP_TYPE,strData);
end;
 
//CardStructVer--get����(���ṹ�汾)
function TCM.getCardStructVer: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_STRUCT_VER,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CardStructVer--set����(���ṹ�汾)
procedure TCM.setCardStructVer(strData: string);
begin
  setfieldwritemode(CARD_STRUCT_VER);
  setCardData(CARD_STRUCT_VER,strData);
end;

//SCHOOL_CODE--get����(У������)
function TCM.getSchoolCode: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(SCHOOL_CODE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//SCHOOL_CODE--set����(У������)
procedure TCM.setSchoolCode(strData: string);
begin
  setfieldwritemode(SCHOOL_CODE);
  setCardData(SCHOOL_CODE,strData);
end;

//CustNo--get����(�ͻ���)
function TCM.getCustNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CUST_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CustNo--set����(�ͻ���)
procedure TCM.setCustNo(strData: string);
begin
  setfieldwritemode(CUST_NO);
  setCardData(CUST_NO,strData);
end;
 
//CustType--get����(�ͻ����)
function TCM.getCustType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CUST_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CustType--set����(�ͻ����)
procedure TCM.setCustType(strData: string);
begin
  setfieldwritemode(CUST_TYPE);
  setCardData(CUST_TYPE,strData);
end;
 
//StuempNo--get����(ѧ����)
function TCM.getStuempNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(STUEMP_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//StuempNo--set����(ѧ����)
procedure TCM.setStuempNo(strData: string);
begin
  setfieldwritemode(STUEMP_NO);
  setCardData(STUEMP_NO,strData);
end;
 
//CustName--get����(�ͻ�����)
function TCM.getCustName: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CUST_NAME,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CustName--set����(�ͻ�����)
procedure TCM.setCustName(strData: string);
begin
  setfieldwritemode(CUST_NAME);
  setCardData(CUST_NAME,strData);
end;
 
//CustSex--get����(�ͻ��Ա�)
function TCM.getCustSex: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CUST_SEX,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CustSex--set����(�ͻ��Ա�)
procedure TCM.setCustSex(strData: string);
begin
  setfieldwritemode(CUST_SEX);
  setCardData(CUST_SEX,strData);
end;
 
//DeptNo--get����(���Ŵ���)
function TCM.getDeptNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(DEPT_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//DeptNo--set����(���Ŵ���)
procedure TCM.setDeptNo(strData: string);
begin
  setfieldwritemode(DEPT_NO);
  setCardData(DEPT_NO,strData);
end;
 
//CertNo--get����(֤������)
function TCM.getCertNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CERTIFICATE_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CertNo--set����(֤������)
procedure TCM.setCertNo(strData: string);
begin
  setfieldwritemode(CERTIFICATE_NO);
  setCardData(CERTIFICATE_NO,strData);
end;
 
//CertType--get����(֤������)
function TCM.getCertType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CERTIFICATE_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CertType--set����(֤������)
procedure TCM.setCertType(strData: string);
begin
  setfieldwritemode(CERTIFICATE_TYPE);
  setCardData(CERTIFICATE_TYPE,strData);
end;
 
//BankNo--get����(���п���)
function TCM.getBankNo: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(BANK_NO,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//BankNo--set����(���п���)
procedure TCM.setBankNo(strData: string);
begin
  setfieldwritemode(BANK_NO);
  setCardData(BANK_NO,strData);
end;
 
//CardCnt--get����(�����״���)
function TCM.getCardCnt: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_CNT,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CardCnt--set����(�����״���)
procedure TCM.setCardCnt(strData: string);
begin
  setfieldwritemode(CARD_CNT);
  setCardData(CARD_CNT,strData);
end;
 
//TransAmt--get����(���׽��)
function TCM.getTransAmt: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(TRANS_AMT,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//TransAmt--set����(���׽��)
procedure TCM.setTransAmt(strData: string);
begin
  setfieldwritemode(TRANS_AMT);
  setCardData(TRANS_AMT,strData);
end;
 
//TransType--get����(��������)
function TCM.getTransType: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(TRANS_TYPE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//TransType--set����(��������)
procedure TCM.setTransType(strData: string);
begin
  setfieldwritemode(TRANS_TYPE);
  setCardData(TRANS_TYPE,strData);
end;
 
//TermId--get����(�����ն˻����)
function TCM.getTermId: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(TERM_ID,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//TermId--set����(�����ն˻����)
procedure TCM.setTermId(strData: string);
begin
  setfieldwritemode(TERM_ID);
  setCardData(TERM_ID,strData);
end;
 
//TransDate--get����(��������)
function TCM.getTransDate: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(TRANS_DATE,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//TransDate--set����(��������)
procedure TCM.setTransDate(strData: string);
begin
  setfieldwritemode(TRANS_DATE);
  setCardData(TRANS_DATE,strData);
end;
 
//TransTime--get����(����ʱ��)
function TCM.getTransTime: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(TRANS_TIME,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//TransTime--set����(����ʱ��)
procedure TCM.setTransTime(strData: string);
begin
  setfieldwritemode(TRANS_TIME);
  setCardData(TRANS_TIME,strData);
end;
 
//MaxPerCount--get����(���������ѽ������)
function TCM.getMaxPerCount: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(MAX_PER_COUNT,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//MaxPerCount--set����(���������ѽ������)
procedure TCM.setMaxPerCount(strData: string);
begin
  setfieldwritemode(MAX_PER_COUNT);
  setCardData(MAX_PER_COUNT,strData);
end;
 
//MaxPerDay--get����(�����ۼ����ѽ������)
function TCM.getMaxPerDay: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(MAX_PER_DAY,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//MaxPerDay--set����(�����ۼ����ѽ������)
procedure TCM.setMaxPerDay(strData: string);
begin
  setfieldwritemode(MAX_PER_DAY);
  setCardData(MAX_PER_DAY,strData);
end;
 
//CardBalance--get����(�����)
function TCM.getCardBalance: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_BALANCE,strData);
  if st=0 then
    Result := strData
  else
    Result := '0';
end;
 
//CardBalance--set����(�����)
procedure TCM.setCardBalance(strData: string);
begin
  setfieldwritemode(CARD_BALANCE);
  setCardData(CARD_BALANCE,strData);
end;
 
//CardPwd--get����(������)
function TCM.getCardPwd: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(CARD_PWD,strData);
  if st=0 then
    Result := strData
  else
    Result := '';
end;
 
//CardPwd--set����(������)
procedure TCM.setCardPwd(strData: string);
begin
  setfieldwritemode(CARD_PWD);
  setCardData(CARD_PWD,strData);
end;
 
//DptCardCnt--get����(��ֵ���״���)
function TCM.getDptCardCnt: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(DPT_CARD_CNT,strData);
  if st=0 then
    Result := strData
  else
    Result := '0';
end;
 
//DptCardCnt--set����(��ֵ���״���)
procedure TCM.setDptCardCnt(strData: string);
begin
  setfieldwritemode(DPT_CARD_CNT);
  setCardData(DPT_CARD_CNT,strData);
end;
 
//PayCardCnt--get����(֧�����״���)
function TCM.getPayCardCnt: string;
var
  st:Integer;
  strData:string;
begin
  st := getCardData(PAY_CARD_CNT,strData);
  if st=0 then
    Result := strData
  else
    Result := '0';
end;
 
//PayCardCnt--set����(֧�����״���)
procedure TCM.setPayCardCnt(strData: string);
begin
  setfieldwritemode(PAY_CARD_CNT);
  setCardData(PAY_CARD_CNT,strData);
end;

//SsdCardCnt--get����(�������״���)
function TCM.getLockCardCnt: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(LOCK_CARDCNT,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

//SsdCardCnt--set����(�������״���)
procedure TCM.setLockCardCnt(strData: string);
begin
  setfieldwritemode(LOCK_CARDCNT);
  setCardData(LOCK_CARDCNT,strData);
end;

function TCM.getDaySumAmt: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(DAYSUM_AMT,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

function TCM.getLockTermId: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(LOCK_TERMID,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

function TCM.getLockTransDate: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(LOCK_TRANSDATE,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

function TCM.getLockTransTime: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(LOCK_TRANSTIME,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

function TCM.getWaterNorOpen: string;
var
  st:Integer;
  strData:string;
begin

  st := getCardData(CF_NORMALLYOPEN,strData);
  if st=0 then
  begin
    if strData='' then
      Result := '0'
    else
      Result:= strData;
  end
  else
    Result := '0';
end;

procedure TCM.setWaterNorOpen(strData: string);
begin
  setfieldwritemode(CF_NORMALLYOPEN);
  setCardData(CF_NORMALLYOPEN,strData);
end;

procedure TCM.setDaySumAmt(strData: string);
begin
  setfieldwritemode(DAYSUM_AMT);
  setCardData(DAYSUM_AMT,strData);
end;

procedure TCM.setLockTermId(strData: string);
begin
  setfieldwritemode(LOCK_TERMID);
  setCardData(LOCK_TERMID,strData);
end;

procedure TCM.setLockTransDate(strData: string);
begin
  setfieldwritemode(LOCK_TRANSDATE);
  setCardData(LOCK_TRANSDATE,strData);
end;

procedure TCM.setLockTransTime(strData: string);
begin
  setfieldwritemode(LOCK_TRANSTIME);
  setCardData(LOCK_TRANSTIME,strData);
end;

end.
