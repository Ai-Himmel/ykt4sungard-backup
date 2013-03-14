{*******************************************************************************
    SunGard Kingstar Delphi Library
    Copyright (C) Kingstar Corporation
    <Unit>CardDll
    <What>实现硬件厂商提供的卡户管理的dll封装
*******************************************************************************}

unit CardDll;

interface

uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,
  WVCmdReq,KSClientConsts,Db,WaterDll;

const
  //****************************************************************************
  //动态库定义
  CARD_DLL ='kscard.dll';
  DESDLL = 'desdll.dll';

  PACKETTYPE_XT=2;    //新天水控
  PACKETTYPE_HD=3;    //汇多水控
  PACKETTYPE_39=4;    //三九水控
  overTime = 30000;   //等待超时时间，默认10秒

  //usb口端口号
  USB_PORT = 100;

  //读写卡模式定义
  READ_MODE = 0;            //读卡模式
  WRITE_MODE = 1;           //写卡模式

  //卡状态标志
  NORMAL_CARD = 0;          //正常状态
  LOCK_CARD = 1;            //锁定状态
  LOSE_CARD = 2;            //挂失状态
  FREEZE_CARD = 3;          //冻结状态
  DESTORY = 4;              //注销状态
  DEAL_CARD = 5;            //过期状态
  FEE_LOCK_CARD=6;          //后付费锁卡

  //cpu卡新增定义，卡结构索引表
  CARD_SERI_NO = 1;         //卡序列号
  CARD_NO = 2;              //交易卡号
  SHOW_CARDNO = 3;          //显示卡号
  CARD_LIMIT_TYPE = 4;      //卡权限类别
  PATCH_NO = 5;             //助批次号
  BLACK_VER = 6;            //黑名单版本
  BLACK_CARD_SIGN = 7;      //卡状态标志，黑卡标志
  START_USE_DATE = 8;       //启用日期
  DEADLINE_DATE = 9;        //有效期
  REL_CARD_SIGN = 10;       //发卡方标识
  CARD_TYPE = 11;           //卡类别
  APP_TYPE = 12;            //应用类别
  CARD_STRUCT_VER = 13;     //卡结构版本，以前为12

  SCHOOL_CODE = 20;         //校区代码
  CUST_NO = 21;             //客户号

  CUST_TYPE = 22;           //客户类别
  STUEMP_NO = 23;           //学工号
  CUST_NAME = 24;           //客户姓名
  CUST_SEX = 25;            //客户性别
  DEPT_NO = 26;             //部门代码
  CERTIFICATE_NO = 27;      //证件号码
  CERTIFICATE_TYPE = 28;    //证件类型

  BANK_NO = 30;             //银行卡号

  LOCK_TERMID = 34;         //锁卡交易时终端机号
  LOCK_TRANSDATE = 35;      //锁卡交易日期
  LOCK_TRANSTIME = 36;      //锁卡交易时间

  DAYSUM_AMT = 37;		      //当日累计交易金额
  LOCK_CARDCNT = 38;		    //锁卡交易时交易次数

  MAX_PER_COUNT = 41;       //卡单次消费金额上限
  MAX_PER_DAY = 42;         //卡日累计消费金额上限

  //最后一次交易
  CARD_CNT = 44;            //卡交易次数31
  TRANS_AMT = 45;           //交易金额32
  TRANS_TYPE = 46;          //交易类型33
  TERM_ID = 47;             //交易终端机编号34
  TRANS_DATE = 48;          //交易日期35
  TRANS_TIME = 49;          //交易时间36
  //LOCK_CARD_CNT=38;       //锁卡交易次数

  CARD_BALANCE = 50;        //卡余额
  CARD_PWD = 51;            //卡密码

  DPT_CARD_CNT = 64;        //充值交易次数
  PAY_CARD_CNT = 65;        //支付交易次数
  //SSD_CARD_CNT = 66;      //补助领取次数

  CF_NORMALLYOPEN = 80;     //常开卡标志0x99常开，0x00正常

type
  //交易设置金额结构体
  TTRANSPACK = packed record
    TermID :Integer;		              //设备终端编号+++
    CardNo : LongWord;		            //交易卡号
    CardPhyID : array[0..16] of Char;	//卡序列号
	  DptCardCnt : LongWord;	          //交易前卡充值次
	  PayCardCnt : LongWord;	          //交易前消费次数
	  SubsidyNo : LongWord;		          //补助批次号
    BefBalance : Integer;	            //交易前卡余额，单位分
    AftBalance : Integer;	            //交易后卡余额，单位分
    TransAmt : Integer;		            //充值金额，单位分
    TransDate : array[0..8] of Char;	//交易日期
    TransTime : array[0..6] of Char;	//交易时间
    Termno : array[0..12] of Char;	  //终端号
    TermSeqno : LongWord;		          //终端交易序列号
    Random : array[0..8] of Char;		  //随机数
    OperCode : array[0..8] of Char;	  //操作员代码
    FundType : LongWord;		          //充值类型 1 现金，2 支票 3 经费本 4 其他
    VoucherNo : array[0..23] of Char;	//充值票据号
    sCardPwd : array[0..6] of Char;   //卡密码
    TransType : Integer;		          //交易类型 0-充值 1扣款
    PayCode :integer;		              //支付代码+++
    PayType : Integer;		            //支付类型,消费类使用

    RefNo : array[0..14] of Char;		  //交易参考号+++
    cRetryFlag:Char;		              //重试标志
    cGetProveFlag:Char;	              //交易确认标志
    Mac : array[0..8] of Char;		    //MAC+++
    HostSeqno : LongWord;		          //交易主机流水号
    ErrCode : Integer;		            //错误码
    ErrMsg : array[0..255] of Char;	  //错误信息
  end;
  PTRANSPACK = ^TTRANSPACK;

  //消费明细结构
  TPAYDTL = packed record
    recordno : Integer;		            //记录号
    exist : Integer;			            //如果记录存在，则为1，否则为0
    transdate : array[0..8] of Char;	//交易日期(YYYYMMDD)
    transtime : array[0..6] of Char;	//交易时间(HHMMSS)
    paycnt : Integer;			            //消费次数
    cardbefbal : Integer;		          //交易前余额
    transamt : Integer;		            //交易金额(包含搭伙费)
    otherfee : Integer;		            //搭伙费
    extamt : Integer;			            //补写金额(加钱为正减钱为负)
    shopid : Integer;			            //商户号
    termno : array[0..12] of Char;	  //终端机编号(PSAM卡中的终端号)
    termsno : Integer;		            //终端交易序号(计算TAC用)
  end;
  PPAYDTL = ^TPAYDTL;


  //发行pasm卡结构体
  TPUBPSAMCARD = packed record
    CardNo : array[0..20] of Char;		  //PSAM卡号
    CardType : LongWord;		            //PSAM卡类型
    CardVer : LongWord;                 //卡版本号
    TermID : array[0..12] of Char;		  //终端编号
    TermSeqno : LongWord;		            //终端交易序号，只能读取
    KeyIndex : LongWord;		            //密钥索引号,密钥索引取值范围是1、2、3，目前发卡必须设为是1
    StartDate : array[0..8] of Char;	  //启用日期
    ExpireDate : array[0..8] of Char;   //有效日期
    PublishID : array[0..16] of Char;	  //发行方标识
    UserID : array[0..16] of Char;	    //使用方标识
  end;
  PPUBPSAMCARD = ^TPUBPSAMCARD;

  //****************************************************************************
//加密电子钱包
{
function YKT_encrypt_cardpwd(cut_id:Integer;const seedKey :pChar;const pwd:pchar;mpwd:pchar): LongInt;
  stdcall;far;external CARD_DLL name 'YKT_encrypt_cardpwd';
}
//语音报价器
function dsbdll(ComPort:integer;OutString:string):integer;stdcall;external 'Tdbjq.dll';
//从usb设备传文件
function  info2text(filename:String): Integer;
  stdcall;far; external 'usbUpload.dll' name 'info2text';

//动态库版本号
procedure ks_getversioninfo(const ver,builddate,desc:PChar);
  stdcall;far; external CARD_DLL name 'ks_getversioninfo';

{**cpu card function begin-----------------------------------------------------}
//读卡器相关--------------------------------------------------------------------
//
function  ks_licence(lisence,pwd:String): Integer;
  stdcall;far; external CARD_DLL name 'ks_licence';

//打开读卡器
function  ks_openport(port: Integer; band: Integer): Integer;
  stdcall;far; external CARD_DLL name 'ks_openport';

//关闭读卡器
function ks_closeport: Integer;
  stdcall;far; external CARD_DLL name 'ks_closeport';

//读卡器鸣叫
function KNG_beep: Integer;
  stdcall;far; external CARD_DLL name 'ks_beep';

//密钥卡想过--------------------------------------------------------------------
//制作密钥卡
function ks_publishkeycard(sMasterKey,sPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishkeycard';

{//制作密钥卡
function ks_getkey(nKeySerial:Integer;sPin:PChar;const sKey:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_getkey';
}

//中止对该卡操作
//如果_Mode=0则在对卡进行操作完毕后，执行ks_halt();则该卡进入HALT模式，则必须把卡移开感应区再进来才能寻得这张卡。
function ks_halt: Integer;
  stdcall;far; external CARD_DLL name 'ks_halt';

//卡操作相关接口----------------------------------------------------------------
//设置该字段读模式
function ks_setfieldreadmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldreadmode';
//设置该字段写模式
function ks_setfieldwritemode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldwritemode';
//设置该字段读写模式
function ks_setfieldallmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldallmode';
//清除该字段读模式
function ks_clearfieldreadmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldreadmode';
//清除该字段写模式
function ks_clearfieldwritemode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldwritemode';
//清除该字段所有模式
function ks_clearfieldallmode(mode:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_clearfieldallmode';
//清除所有字段的读模式
function ks_clearallfieldreadmode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldreadmode';
//清除所有字段的写模式
function ks_clearallfieldwritemode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldwritemode';
//清除所有字段的读写模式
function ks_clearallfieldallmode():Integer;
  stdcall;far; external CARD_DLL name 'ks_clearallfieldallmode';

//寻卡
function ks_card(phyId:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_card';

//卡内部编号
function ks_cardtype():Integer;
  stdcall;far; external CARD_DLL name 'ks_cardtype';

//mf寻卡
function ks_mf_card(phyId:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_mf_card';

//设置mfone卡密钥
function ks_setmifare1key(sWorkKey:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_setmifare1key';
  
//读取卡信息
function ks_readcard():Integer;
  stdcall;far; external CARD_DLL name 'ks_readcard';

//获取卡信息字段
function ks_getfieldval(mask:Integer;const data:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_getfieldval';

//设置写字段数据
function ks_setfieldval(mask:Integer;data:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_setfieldval';

//写卡信息
function ks_writecard(phyId:pchar):Integer;
  stdcall;far; external CARD_DLL name 'ks_writecard';

//验证口令
function ks_verifypin(phyId,pin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_verifypin';

//设置钱包金额
function ks_setcardbal(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_setcardbal';

//扣款

function ks_payment(transpack:PTRANSPACK;must_online:Integer=1):Integer;
  stdcall;far; external CARD_DLL name 'ks_payment';

//扣款初始化
function ks_payinit(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_payinit';

//扣款
function ks_pay(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_pay';

//取交易认证，1充值，2消费，cardcnt交易后充值次数或消费次数
function ks_gettransprove(transflag,short:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_gettransprove';

//交易确认
function ks_dotransunprove(transpack:PTRANSPACK):Integer;
  stdcall;far; external CARD_DLL name 'ks_dotransunprove';

//充值初始化
function ks_comminit(svrip:PChar;svrport,svrfunc:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_comminit';

//充值
function ks_deposit(transpack:PTRANSPACK;must_online:Integer=1):Integer;
  stdcall;far; external CARD_DLL name 'ks_deposit';

//读取消费流水
function ks_readpaydtl(recordno:Integer;paydtl:PPAYDTL):Integer;
  stdcall;far; external CARD_DLL name 'ks_readpaydtl';

//修改卡密码
function ks_modifypasswd(phyId,oldPin,newPin:pChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_modifypasswd';

//重置密码
function ks_resetpasswd(phyId,newPin:pChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_resetpasswd';

//修改卡状态
function ks_modifystatus(state:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_modifystatus';

//返回错误码
function ks_geterrmsg(errmsg:PChar):PChar;
  stdcall;far; external CARD_DLL name 'ks_geterrmsg';

//初始化卡
function ks_publishusercard(sCardPhyID,szShowCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishusercard';

//检查是否密钥已经加载
//返回值0- 未加载1加载
function ks_checkloadkeys():Integer;
  stdcall;far; external CARD_DLL name 'ks_checkloadkeys';

//装载密钥
function ks_loadcardkeys(sKeyCardPwd:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_loadcardkeys';
  
//设置要操作的SAM卡座,0为大卡座，1、 2、 3 各为SAM1 SAM2 SAM3 
function ks_setcpupara4sam(SAMID:Integer):Integer;
  stdcall;far; external CARD_DLL name 'ks_setcpupara4sam';

//PSAM卡上电复位
function ks_samcpureset():Integer;
  stdcall;far; external CARD_DLL name 'ks_samcpureset';

//发行PSAM卡
function ks_publishpsamcard(PubPSAMCard:PPUBPSAMCARD):Integer;
  stdcall;far; external CARD_DLL name 'ks_publishpsamcard';

//回收PSAM卡
function ks_recyclepsamcard():Integer;
  stdcall;far; external CARD_DLL name 'ks_recyclepsamcard';

//读取PSAM卡
function ks_readpsamcard(PublishPSAMCard:PPUBPSAMCARD):Integer;
  stdcall;far; external CARD_DLL name 'ks_readpsamcard';

//检查是否克隆密钥已经加载
//返回值0- 未加载1加载
function ks_checkloadclonekeys():Integer;
  stdcall;far; external CARD_DLL name 'ks_checkloadclonekeys';

//装载密钥给克隆卡使用
function ks_loadkeys4clone(sKeyCardPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_loadkeys4clone';

////克隆密钥卡
function ks_clonekeycard(sKeyCardPin:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_clonekeycard';
{
//回收卡函数
function ks_recycleusercard(flag:Integer;showCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';
}
//回收卡函数
function ks_refineusercard(flag:Integer;showCardNo:PChar):Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';

//回收卡到出厂状态
function ks_recycleusercard():Integer;
  stdcall;far; external CARD_DLL name 'ks_recycleusercard';

function calc_oper_pwd(const oper_code :pChar;const pwd:pchar;text:pchar): LongInt;
  stdcall;far;external DESDLL name 'calc_oper_pwd';

//函数调用
type

  TCM = class
  private
    Fcard_serialno:string;

    function encryptCardpwd(cut_id:Integer;const seedKey,pwd:pchar;var mpwd:string): longint;
    function Load_Dll: longint;
  public
    //基本函数，调用函数原型
    procedure getVersion(var ver,builddate,desc: string);
    function openDevice(port: Integer; band: Integer): Integer;
    function closeDevice: Integer;
    function beep: Integer;
    function keyCardPublish(sMasterKey,sPin:string): Integer;
    function halt: Integer;
    //function getKey(nKeySerial:Integer;sPin:string;var sKey:string):Integer;

    //设置该字段读模式
    function setfieldreadmode(mode:Integer):Integer;
    //设置该字段写模式
    function setfieldwritemode(mode:Integer):Integer;
    //设置该字段读写模式
    function setfieldallmode(mode:Integer):Integer;
    //清除该字段读模式
    function clearfieldreadmode(mode:Integer):Integer;
    //清除该字段写模式
    function clearfieldwritemode(mode:Integer):Integer;
    //清除该字段所有模式
    function clearfieldallmode(mode:Integer):Integer;
    //清除所有字段的读模式
    function clearallfieldreadmode():Integer;
    //清除所有字段的写模式
    function clearallfieldwritemode():Integer;
    //清除所有字段的读写模式
    function clearallfieldallmode():Integer;

    //寻卡
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

    //以下为get和set函数
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
//加密电子钱包
function encCardpwd(custId:Integer;inseedkey,inpwd:string): string;

//语音报价器
function bj(comport:Integer;outString:string): Integer;

//发行卡公用模块--new
function pubCardNew(workviewIn, workviewOut: TWorkView;wvRequest:TWVRequest;phyCardId:string;showTip:Integer;var reCode:Integer): string;

//充值，支取失败冲正业务处理
function cashOperCancel(workviewIn: TWorkView;wvRequest:TWVRequest;operDate:string;seriId:Integer;stationId:Integer): string;
//交易冲正，使用交易参考号
function CancelOper(workviewIn: TWorkView;wvRequest:TWVRequest;tradeCode,mac:string): string;

//汇多小钱包取水价
procedure setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);

function getReturn(s1:string;wv:TWorkView):string ;

//读卡前准备
function preReadCard: Boolean;

//读取PASM卡准备
//function preReadPASM(pasm:TPUBPSAMCARD): Boolean;

//
//procedure preSetMoney(transPack:TTRANSPACK);
//返回动态库失败信息
procedure getDllErr;

//发卡前判断放置的是否有效卡
function relCardJudge: Boolean;

//根据索引读取一个卡信息
function readCardOneInfo(idxNo:Integer): String;

function setOperReadMode(cm:tcm):string;
function setOperWriteMode(cm:tcm):string;

function ksLicence:Integer;

//procedure preReadPayDtl(paydtl:TPAYDTL);

function mfcard(var phyId:string):Integer;

function setMainWorkKey(workKey:string):Integer;
//加密操作员密码
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

//加密
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
    context.GetDialogSystem.ShowMessage('寻卡失败，请放好卡重试，错误码:'+inttostr(st));
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
      context.GetDialogSystem.ShowMessage('寻卡失败，请把卡放置好！');
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
    //读取卡信息
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
      tradeDate := wv.fieldbyname('业务日期').Data.AsString;
      tradeTime := wv.fieldbyname('业务时间').Data.AsString;
      //preSetMoney(tp);
      ZeroMemory(@tp,SizeOf(tp));
      //终端交易序列号
      tp.TermSeqno := 1;
      //终端编号
      StrCopy(@tp.Termno,PChar(scSiteNo));
      //交易卡号
      tp.CardNo := StrToInt(cm.getCardNo);
      //物理编号
      StrCopy(@tp.CardPhyID,PChar(cm.getCardSeriNo));
      //交易日期
      StrCopy(@tp.TransDate,PChar(tradeDate));
      //交易时间
      StrCopy(@tp.TransTime,PChar(tradeTime));
      //交易前金额
      tp.BefBalance := balance;
      //交易后金额
      tp.AftBalance := 0;
      //交易前充值次数
      tp.DptCardCnt := dptCnt;
      //交易前消费次数
      tp.PayCardCnt := payCnt;
      //交易前补助次数
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
  过程名:    TCM.cashOperCancel发卡公用模块
  作者:      hanjiwei
  日期:      2009.04.16
  参数:      workviewIn: TWorkView; wvRequest: TWVRequest; operDate: string; seriId, stationId: Integer
  返回值:    string
-------------------------------------------------------------------------------}
function pubCardNew(workviewIn,workviewOut: TWorkView;
  wvRequest:TWVRequest;phyCardId:string;showTip:Integer;var reCode:Integer): string;
var
  cardNo:Integer;           //交易卡号
  showCardNo:string;        //显示卡号
  cardEndDate:string;       //卡使用截至日期
  cardLimitType:string;     //卡使用权限
  custType:string;          //客户类别
  custName:string;          //客户姓名
  certType:string;          //证件类型
  cardID:string;            //身份证号
  depNo:string;             //部门代码
  custSex:string;           //性别
  stuempNo:string;          //学工号
  cardBalance:Real;         //卡余额
  cardPWD:string;           //卡密码
  sOper:string;             //开户操作员
  sOperDate:string;         //操作日期
  maxPerCount:string;       //单次消费限额
  maxPerDay:string;         //日消费限额
  relCardSign:string;       //发行方标识
  cardType:string;          //卡类型
  custId:string;            //客户号
  tradeDate:string;         //交易日期
  tradeTime : string;       //交易时间
  //areaCode:string;          //校区代码
  cardVer:string;           //卡版本号
  
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
  cardNo:=workviewIn.fieldbyname('卡号').Data.AsInteger;
  showCardNo:=workviewIn.fieldbyname('显示卡号').Data.AsString;
  cardEndDate:=workviewIn.fieldbyname('到期日期').Data.AsString;
  cardLimitType:=workviewIn.fieldbyname('收费类别').Data.AsString;
  custType:=workviewIn.fieldbyname('客户类别').Data.AsString;
  custName:=workviewIn.fieldbyname('客户姓名').Data.AsString;
  certType:=workviewIn.fieldbyname('证件类型').Data.AsString;
  cardID:=workviewIn.fieldbyname('证件号码').Data.AsString;
  depNo:=workviewIn.fieldbyname('部门代码').Data.AsString;
  custSex:=workviewIn.fieldbyname('性别').Data.AsString;
  stuempNo:=workviewIn.fieldbyname('学工号').Data.AsString;
  cardBalance:=workviewIn.fieldbyname('出卡值').Data.AsFloat;
  cardPWD:=workviewIn.fieldbyname('卡密码').Data.AsString;
  relCardSign := workviewIn.fieldbyname('发行方标识').Data.AsString;

  cardVer := workviewIn.fieldbyname('版本号').Data.AsString;

  //areacode:=workviewIn.fieldbyname('院校代码').Data.AsString;
  sOper := workviewIn.fieldbyname('操作员').Data.AsString;
  sOperDate := workviewIn.fieldbyname('业务日期').Data.AsString;
  cardType := workviewIn.fieldbyname('卡类型').Data.AsString;
  custId := workviewIn.fieldbyname('客户号').Data.AsString;
  tradeDate := workviewIn.fieldbyname('业务日期').Data.AsString;
  tradeTime := workviewIn.fieldbyname('业务时间').Data.AsString;
  cm := nil;
  try
    cm := TCM.Create;
    re := cm.card(phyId);
    if re<>0 then
    begin
      reCode := -3;
      context.GetDialogSystem.ShowMessage('寻卡失败，请冲正该交易！');
      exit;
    end;
    if phyId<>phyCardId then
    begin
      reCode := -4;
      context.GetDialogSystem.ShowMessage('放置的卡物理编号和发送交易的卡物理编号不符，请冲正该交易！');
      exit;
    end;
    cm.clearallfieldwritemode;
    //设置要写卡的信息
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
    //设置单次消费限额和日消费限额
    if maxPer=1 then
    begin
      maxPerCount := workviewIn.fieldbyname('单次限额').Data.AsString;
      maxPerDay := workviewIn.fieldbyname('日限额').Data.AsString;
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
    //如果卡号为零，卡信息没有写上，提示更新卡信息或冲正
    if ((readCardNo=0) or (re<>0)) then
    begin
      reSt := ks_geterrmsg(PChar(@reErrMsg));
      reCode := -1;
      Result:='写卡基本信息失败['+reSt+']，请更新卡信息或冲正！';
      Exit;
    end
    else
    begin
      //写卡成功后调用充值函数进行设置金额--------
      if (cardBalance = 0) then
      begin
        re := 0;
      end
      else
      begin
        ZeroMemory(@tp,SizeOf(tp));
        //终端交易序列号
        tp.TermSeqno := 1;
        //终端编号
        StrCopy(@tp.Termno,PChar(scSiteNo));
        //交易卡号
        tp.CardNo := cardNo;
        //物理编号
        StrCopy(@tp.CardPhyID,PChar(phyId));
        //交易日期
        StrCopy(@tp.TransDate,PChar(tradeDate));
        //交易时间
        StrCopy(@tp.TransTime,PChar(tradeTime));
        //交易前金额
        tp.BefBalance := 0;
        //交易后金额
        tp.AftBalance := StrToInt(floattostr(cardBalance));
        //交易前充值次数
        tp.DptCardCnt := dptCnt;
        //交易前消费次数
        tp.PayCardCnt := payCnt;
        //交易前补助次数
        tp.SubsidyNo := 0;
        re := setCardBal(tp,cm,phyId);
      end;
      
      if re=0 then
      begin
        reCode := 0;
        if showTip=1 then
        begin
          context.GetDialogSystem.ShowMessage('写卡信息成功,该卡的卡号为:' + IntToStr(cardNo));
        end;
        Result:=workviewIn.FieldByName('返回信息').Data.AsString;
      end
      else
      begin
        //写卡成功，但设置金额失败
        reCode := 1;
        if showTip=1 then
        begin
          context.GetDialogSystem.ShowMessage('写卡基本信息成功，设置金额失败，请调整卡余额！');
        end;
        Result:=workviewIn.FieldByName('返回信息').Data.AsString+',设置金额失败，请调整卡余额';
      end;
    end;
  finally
    cm.Destroy;
  end;
end;


{-------------------------------------------------------------------------------
  过程名:    TCM.pubCardNew充值、支取失败做冲正交易
  作者:      hanjiwei
  日期:      2009.04.16
  参数:      workviewIn, workviewOut: TWorkView; wvRequest: TWVRequest; phyCardId: string; showTip: Integer
  返回值:    string
-------------------------------------------------------------------------------}
function cashOperCancel(
  workviewIn: TWorkView;
  wvRequest:TWVRequest;operDate:string;
  seriId:Integer;stationId:Integer): string;
begin
  workviewIn.FieldByName('终端编号').Data.SetInteger(stationId);
  workviewIn.FieldByName('流水号').Data.SetInteger(seriId);
  workviewIn.FieldByName('业务日期').Data.SetString(operDate);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('冲正失败，请在交易冲正中处理该记录并重新做该业务！');
    Result := '冲正失败--'+
    workviewIn.fieldbyname('返回信息').Data.AsString+',请在交易冲正中处理该记录并重新做该业务！';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('业务失败，请重新操作该项业务！');
    Result := '业务失败，请重新操作该项业务！';
  end;

end;

{-------------------------------------------------------------------------------
  过程名:    TCM.pubCardNew充值、支取失败做冲正交易
  作者:      hanjiwei
  日期:      2009.04.16
  参数:      workviewIn, workviewOut: TWorkView; wvRequest: TWVRequest; phyCardId: string; showTip: Integer
  返回值:    string
-------------------------------------------------------------------------------}
function CancelOper(workviewIn: TWorkView;wvRequest:TWVRequest;tradeCode,mac:string): string;
begin
  workviewIn.FieldByName('交易参考号').Data.SetString(tradeCode);
  workviewIn.FieldByName('随机数').Data.SetString(mac);
  wvRequest.SendCommand;
  if workviewIn.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    context.GetDialogSystem.ShowMessage('冲正失败，请在交易冲正中处理该记录并重新做该业务！');
    Result := '冲正失败--'+
    workviewIn.fieldbyname('返回信息').Data.AsString+',请在交易冲正中处理该记录并重新做该业务！';
  end
  else
  begin
    context.GetDialogSystem.ShowMessage('业务失败，请重新操作该项业务！');
    Result := '业务失败，请重新操作该项业务！';
  end;

end;

procedure setWaterPrice(wvWater: TWorkView;wvrWater:TWVRequest;feeType:Integer);
var
  tempData:TDataSet;
begin
  wvWater.FieldByName('收费类别').Data.SetInteger(feeType);
  wvWater.FieldByName('操作标志').Data.SetString('R');
  try
    wvrWater.SendCommand;
    //ShowMessage('111');
    if wvWater.FieldByName('返回码').Data.AsString<>'0' then
    begin
      cpuWaterPrice1 := 0;
      cpuWaterPrice2 := 0;
      cpuWaterPrice3 := 0;
    end;
    ///ShowMessage('222');
    tempData := TDataSet(wvWater.FieldByName('查询结果集').Data.AsObject);
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
  ConText.GetDialogSystem.showmessage(s1+wv.FieldByName('返回信息').Data.AsString);
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
      //判断是否中途拔卡
      if tp.cGetProveFlag>Char(0) then
      begin
        //循环寻卡
        nowTime := GetTickCount;
        while (1>0) do
        begin
          if (GetTickCount-nowTime)>overTime then
          begin
            //时间大于10秒，提示超时，退出
            ks_dotransunprove(@tp);
            Context.GetDialogSystem.ShowMessage('寻卡超时，请使用卡余额调整设置卡余额！');
            Result := -2;
            Exit;
          end;

          st := cm.card(newPhyId);
          if st<>0 then
          begin
            Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
          end
          else
          begin
            //寻到卡后，判断是否为同一张卡，如果不是，提示重新放卡
            if newPhyId<>CardPhyID then
              Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，请重新放置！')
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
        //扣款失败，1，重试。0错误信息，退出
        if tp.cRetryFlag=Char(1) then
        begin
          //循环寻卡
          nowTime := GetTickCount;
          while (1>0) do
          begin
            if (GetTickCount-nowTime)>overTime then
            begin
              //时间大于10秒，提示超时，退出
              ks_dotransunprove(@tp);
              Context.GetDialogSystem.ShowMessage('寻卡超时，请使用卡余额调整设置卡余额！');
              Result := -1;
              Exit;
            end;

            st := cm.card(newPhyId);
            if st<>0 then
            begin
              Context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡！');
            end
            else
            begin
              //寻到卡后，判断是否为同一张卡，如果不是，提示重新放卡
              if newPhyId<>CardPhyID then
                Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，请重新放置！')
              else
                Break;
            end;
            Continue;
          end;
          Sleep(50);
          //重试一次
          st := ks_setcardbal(@tp);
          if st = 0 then
            Break;
        end
        else if tp.cRetryFlag=Char(0) then
        begin
          reSt := ks_geterrmsg(PChar(@reErrMsg));
          Context.GetDialogSystem.ShowMessage('写金额失败，请使用卡余额调整设置卡余额-'+reSt);
          Result := -3;
          Exit;
        end;
      end;
      Continue;
    end;
  end;
  //重新读卡，判断金额是否写成功，如果没有写成功，提示卡余额调整

  try
    st := cm.card(newPhyId);
    if st<>0 then
    begin
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡，读取卡金额信息看是否写卡成功！');
      Result := -4;
      exit;
    end;
    cm.clearallfieldreadmode;
    cm.setfieldreadmode(CARD_BALANCE);

    if newPhyId<>CardPhyID then
    begin
      Context.GetDialogSystem.ShowMessage('放置的卡和刚才放置的不是同一张卡，读取卡金额信息看是否写卡成功！');
      Result := -5;
      Exit;
    end;
    st := cm.readCard(newPhyId);
    if st<>0 then
    begin
      Context.GetDialogSystem.ShowMessage('读卡信息失败，请重新放卡，读取卡金额看是否写卡成功！');
      Result := -6;
      Exit;
    end;
    if StrToInt(cm.getCardBalance)<>writeMoney then
    begin
      Context.GetDialogSystem.ShowMessage('卡余额和要写入的余额不等，请查看读写器是否正常，并使用卡余额调整设置卡余额！');
      Result := -7;
      Exit;
    end;
  except
    on e:exception do
    begin
      Context.GetDialogSystem.ShowMessage('读卡失败，请重新放卡，读取卡金额看是否写卡成功-'+e.Message);
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
    //寻卡失败
    result := -100;
    Exit;
  end;
  if phyId<>oldPhyId then
  begin
    //要初始化的小钱包和主卡不是同一张卡
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
//读取PASM卡准备
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
    Context.GetDialogSystem.ShowMessage('请先打开串口,然后再进行操作！');
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
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡!');
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
      context.GetDialogSystem.ShowMessage('读卡序列号失败，该卡已经损坏！');
      Result := False;
      Exit;
    end;
    }
    cardNo := cm.getCardNo;
    if cardNo='-1' then
    begin
      Context.GetDialogSystem.ShowMessage('读交易卡号失败，该卡没有初始化！');
      Result := False;
      Exit;
    end;
    //判断是否为销户的卡，如果为销户的卡，充值次数和消费次数都为0才能重新发行
    //否则只能先回收卡，然后初始化，最后才能发行
    cardStatus := cm.getBlackCardSign;
    dptCardCnt := cm.getDptCardCnt;
    payCardCnt := cm.getPayCardCnt;
    if cardStatus=IntToStr(DESTORY) then
      if (dptCardCnt<>'0')or(payCardCnt<>'0') then
      begin
        Context.GetDialogSystem.ShowMessage('该卡已经注销，请先回收该卡，然后再发行！');
        Result := False;
        Exit;
      end;
  finally
    cm.Destroy;
  end;
end;

//根据索引值读取卡信息
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
      context.GetDialogSystem.ShowMessage('寻卡失败，请放置好卡!');
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
        //Context.GetDialogSystem.ShowMessage('读卡信息失败，请检查卡是否放好-'+inttostr(st));
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
    Context.GetDialogSystem.ShowMessage('加密操作员密码失败'+inttostr(st));
    Result := '';
    Exit;
  end;
  Result := outOperPwd;
end;

{-------------------------------------------------------------------------------
  过程名:    TCM.getVersion取动态库版本号
  作者:      hanjiwei
  日期:      2009.04.20
  参数:      var ver: string
  返回值:    无
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

//******************************************************************************get和set函数
//setOperReadMask设置读取或写入权限
//返回没有读取或设置权限的功能连接串
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
  //一个空的实现方法，设置写模式在set值之前，只有设置了该值，才有写模式
  //全部设置如果不写值则会清空所有的值
end;


//CardSeriNo--get函数(卡序列号)
function TCM.getCardSeriNo: string;
begin
  Result := Fcard_serialno;
end;

//CardSeriNo--set函数(卡序列号)
procedure TCM.setCardSeriNo(strData: string);
begin
  Fcard_serialno := strData;
end;

//CardNo--get函数(交易卡号)
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
 
//CardNo--set函数(交易卡号)
procedure TCM.setCardNo(strData: string);
begin
  setfieldwritemode(CARD_NO);
  setCardData(CARD_NO,strData);
end;
 
//ShowCardNo--get函数(显示卡号)
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
 
//ShowCardNo--set函数(显示卡号)
procedure TCM.setShowCardNo(strData: string);
begin
  setfieldwritemode(SHOW_CARDNO);
  setCardData(SHOW_CARDNO,strData);
end;
 
//CardLimitType--get函数(收费类别)
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
 
//CardLimitType--set函数(收费类别)
procedure TCM.setCardLimitType(strData: string);
begin
  setfieldwritemode(CARD_LIMIT_TYPE);
  setCardData(CARD_LIMIT_TYPE,strData);
end;
 
//PatchNo--get函数(补助批次号)
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
 
//PatchNo--set函数(补助批次号)
procedure TCM.setPatchNo(strData: string);
begin
  setfieldwritemode(PATCH_NO);
  setCardData(PATCH_NO,strData);
end;
 
//BlackVer--get函数(卡版本号)
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
 
//BlackVer--set函数(卡版本号)
procedure TCM.setBlackVer(strData: string);
begin
  setfieldwritemode(BLACK_VER);
  setCardData(BLACK_VER,strData);
end;
 
//BlackCardSign--get函数(卡状态)
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
 
//BlackCardSign--set函数(卡状态)
procedure TCM.setBlackCardSign(strData: string);
begin
  setfieldwritemode(BLACK_CARD_SIGN);
  setCardData(BLACK_CARD_SIGN,strData);
end;
 
//StartUseDate--get函数(启用日期)
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
 
//StartUseDate--set函数(启用日期)
procedure TCM.setStartUseDate(strData: string);
begin
  setfieldwritemode(START_USE_DATE);
  setCardData(START_USE_DATE,strData);
end;
 
//DeadLineDate--get函数(过期日期)
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
 
//DeadLineDate--set函数(过期日期)
procedure TCM.setDeadLineDate(strData: string);
begin
  setfieldwritemode(DEADLINE_DATE);
  setCardData(DEADLINE_DATE,strData);
end;
 
//ReaCardSign--get函数(发卡方标识)
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
 
//ReaCardSign--set函数(发卡方标识)
procedure TCM.setReaCardSign(strData: string);
begin
  setfieldwritemode(REL_CARD_SIGN);
  setCardData(REL_CARD_SIGN,strData);
end;
 
//CardType--get函数(卡类别)
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
 
//CardType--set函数(卡类别)
procedure TCM.setCardType(strData: string);
begin
  setfieldwritemode(CARD_TYPE);
  setCardData(CARD_TYPE,strData);
end;

//APP_TYPE--get函数(应用类别)
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
 
//APP_TYPE--set函数(卡结构版本)
procedure TCM.setAppType(strData: string);
begin
  setfieldwritemode(APP_TYPE);
  setCardData(APP_TYPE,strData);
end;
 
//CardStructVer--get函数(卡结构版本)
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
 
//CardStructVer--set函数(卡结构版本)
procedure TCM.setCardStructVer(strData: string);
begin
  setfieldwritemode(CARD_STRUCT_VER);
  setCardData(CARD_STRUCT_VER,strData);
end;

//SCHOOL_CODE--get函数(校区代码)
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
 
//SCHOOL_CODE--set函数(校区代码)
procedure TCM.setSchoolCode(strData: string);
begin
  setfieldwritemode(SCHOOL_CODE);
  setCardData(SCHOOL_CODE,strData);
end;

//CustNo--get函数(客户号)
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
 
//CustNo--set函数(客户号)
procedure TCM.setCustNo(strData: string);
begin
  setfieldwritemode(CUST_NO);
  setCardData(CUST_NO,strData);
end;
 
//CustType--get函数(客户类别)
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
 
//CustType--set函数(客户类别)
procedure TCM.setCustType(strData: string);
begin
  setfieldwritemode(CUST_TYPE);
  setCardData(CUST_TYPE,strData);
end;
 
//StuempNo--get函数(学工号)
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
 
//StuempNo--set函数(学工号)
procedure TCM.setStuempNo(strData: string);
begin
  setfieldwritemode(STUEMP_NO);
  setCardData(STUEMP_NO,strData);
end;
 
//CustName--get函数(客户姓名)
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
 
//CustName--set函数(客户姓名)
procedure TCM.setCustName(strData: string);
begin
  setfieldwritemode(CUST_NAME);
  setCardData(CUST_NAME,strData);
end;
 
//CustSex--get函数(客户性别)
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
 
//CustSex--set函数(客户性别)
procedure TCM.setCustSex(strData: string);
begin
  setfieldwritemode(CUST_SEX);
  setCardData(CUST_SEX,strData);
end;
 
//DeptNo--get函数(部门代码)
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
 
//DeptNo--set函数(部门代码)
procedure TCM.setDeptNo(strData: string);
begin
  setfieldwritemode(DEPT_NO);
  setCardData(DEPT_NO,strData);
end;
 
//CertNo--get函数(证件号码)
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
 
//CertNo--set函数(证件号码)
procedure TCM.setCertNo(strData: string);
begin
  setfieldwritemode(CERTIFICATE_NO);
  setCardData(CERTIFICATE_NO,strData);
end;
 
//CertType--get函数(证件类型)
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
 
//CertType--set函数(证件类型)
procedure TCM.setCertType(strData: string);
begin
  setfieldwritemode(CERTIFICATE_TYPE);
  setCardData(CERTIFICATE_TYPE,strData);
end;
 
//BankNo--get函数(银行卡号)
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
 
//BankNo--set函数(银行卡号)
procedure TCM.setBankNo(strData: string);
begin
  setfieldwritemode(BANK_NO);
  setCardData(BANK_NO,strData);
end;
 
//CardCnt--get函数(卡交易次数)
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
 
//CardCnt--set函数(卡交易次数)
procedure TCM.setCardCnt(strData: string);
begin
  setfieldwritemode(CARD_CNT);
  setCardData(CARD_CNT,strData);
end;
 
//TransAmt--get函数(交易金额)
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
 
//TransAmt--set函数(交易金额)
procedure TCM.setTransAmt(strData: string);
begin
  setfieldwritemode(TRANS_AMT);
  setCardData(TRANS_AMT,strData);
end;
 
//TransType--get函数(交易类型)
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
 
//TransType--set函数(交易类型)
procedure TCM.setTransType(strData: string);
begin
  setfieldwritemode(TRANS_TYPE);
  setCardData(TRANS_TYPE,strData);
end;
 
//TermId--get函数(交易终端机编号)
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
 
//TermId--set函数(交易终端机编号)
procedure TCM.setTermId(strData: string);
begin
  setfieldwritemode(TERM_ID);
  setCardData(TERM_ID,strData);
end;
 
//TransDate--get函数(交易日期)
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
 
//TransDate--set函数(交易日期)
procedure TCM.setTransDate(strData: string);
begin
  setfieldwritemode(TRANS_DATE);
  setCardData(TRANS_DATE,strData);
end;
 
//TransTime--get函数(交易时间)
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
 
//TransTime--set函数(交易时间)
procedure TCM.setTransTime(strData: string);
begin
  setfieldwritemode(TRANS_TIME);
  setCardData(TRANS_TIME,strData);
end;
 
//MaxPerCount--get函数(卡单次消费金额上限)
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
 
//MaxPerCount--set函数(卡单次消费金额上限)
procedure TCM.setMaxPerCount(strData: string);
begin
  setfieldwritemode(MAX_PER_COUNT);
  setCardData(MAX_PER_COUNT,strData);
end;
 
//MaxPerDay--get函数(卡日累计消费金额上限)
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
 
//MaxPerDay--set函数(卡日累计消费金额上限)
procedure TCM.setMaxPerDay(strData: string);
begin
  setfieldwritemode(MAX_PER_DAY);
  setCardData(MAX_PER_DAY,strData);
end;
 
//CardBalance--get函数(卡余额)
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
 
//CardBalance--set函数(卡余额)
procedure TCM.setCardBalance(strData: string);
begin
  setfieldwritemode(CARD_BALANCE);
  setCardData(CARD_BALANCE,strData);
end;
 
//CardPwd--get函数(卡密码)
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
 
//CardPwd--set函数(卡密码)
procedure TCM.setCardPwd(strData: string);
begin
  setfieldwritemode(CARD_PWD);
  setCardData(CARD_PWD,strData);
end;
 
//DptCardCnt--get函数(充值交易次数)
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
 
//DptCardCnt--set函数(充值交易次数)
procedure TCM.setDptCardCnt(strData: string);
begin
  setfieldwritemode(DPT_CARD_CNT);
  setCardData(DPT_CARD_CNT,strData);
end;
 
//PayCardCnt--get函数(支付交易次数)
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
 
//PayCardCnt--set函数(支付交易次数)
procedure TCM.setPayCardCnt(strData: string);
begin
  setfieldwritemode(PAY_CARD_CNT);
  setCardData(PAY_CARD_CNT,strData);
end;

//SsdCardCnt--get函数(锁卡交易次数)
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

//SsdCardCnt--set函数(锁卡交易次数)
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
