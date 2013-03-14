unit smartterminterface;

interface

uses Windows,SysUtils;

const
  MBLDLL = 'mobileterm.dll';
  MBLDLL_SCJ = 'mobileterm_SCJ.dll';

type
  {交易流水结构定义}
  MBL_TRADE_LOG = packed record
    phyid : array[0..3] of Byte;
	  ver,runreason,serial_no,card_id:Integer;
    tx_datetime :array[0..12] of Char;
    tx_cnt,out_card_amount,in_card_amount,tx_trade_amount : Integer;
	  tx_mark : Byte;
	  crc: array[0..1] of Byte;
  end;
  PMBL_TRADE_LOG = ^MBL_TRADE_LOG;
  ///////////////////////////////////////
  {手持机信息结构定义}
  SMART_TERMINAL_T = packed record
    port,termno: Integer;
	  commision: array[0..3] of Byte;
	  phyid: array[0..3] of Byte;
	  level_array: array[0..4] of Byte;
    level : Integer;
	  termtype: array[0..1] of Byte;
    verdate : array[0..8] of Char;
  end;
  PSMART_TERMINAL_T = ^SMART_TERMINAL_T;

  {手持机参数定义}
  SMART_TERM_PARAM_T = packed record
    commision:array[0..3] of byte;	//授权号
    termno : Integer;				//机号
    pswd_switch: Integer;		//密码开关
    consume_way: Integer;		// 收费方式
    card_max_cnt: Integer;		//卡片最大使用次数
    card_type:array[0..1] of byte;	//允许消费类别
    purse_max: Integer;			//钱包存款最高限额
    consume_max: Integer;		//每次消费最高限额
    purse_min: Integer;			//钱包余款最低限额
    fixed_count: Integer;		//存取款定值额
    comsume_type: Integer;		//
    band_rate: Integer;			//波特率
    purse_attr: Integer;			// 钱包属性
    person_key: array[0..3] of byte;		//个人密钥前四个字节
    sys_pwd:array[0..1] of byte;		//系统管理员密码
    card_set: Integer;			//机器使用卡类型
  end;
  PSMART_TERM_PARAM_T = ^SMART_TERM_PARAM_T;

  smart_jsb_param_t = packed record
	commision:array[0..3] of byte;
	termno : Integer;
	pswd_switch: Integer;
	work_mode: Integer;		// 计时宝工作模式 2
	open_lock_time1: Integer; // 开锁 1 的时间
	open_lock_time2: Integer; // 开锁 2 的时间
	card_type:array[0..1] of Byte; // 卡分类
	is_gate_mode: Integer;	// 是否工作在通道机模式 0
	is_save_record: Integer;	// 是否存储打卡记录
	num_reader: Integer;			// 感应头数目
	reversed:array[0..2] of byte;	// 保留
	sys_pwd:array[0..2] of byte;		// 系统管理员密码
	v10_pwd:array[0..1] of byte;
	v10_purse_sect: Integer;		// v10 卡号/钱包扇区
	is_led_mode: Integer;		// 是否 LED 模式
	band_rate: Integer;
	time_val_switch: Integer;	// 时间间隔开关
	time_val:array[0..1] of Byte;		// 时间间隔
	card_set: Integer;			// 卡类型
  end;
  Psmart_jsb_param_t = ^smart_jsb_param_t;

  smart_jsb_serial_t = packed record
	phyid:array[0..3] of byte;				// 设备物理ID，HEX格式
	ver: Integer;						// 通讯版本
	runreason: Integer;					// 启动原因
	serial_no: Integer;					// 流水号
	card_id: Integer;					// 交易卡号
	tx_datetime:array[0..12] of char;			// 交易日期时间，yymmddHHnnss/dow
	day_of_week: Integer;				// 星期
	work_mode: Integer;					// 工作模式
	check_type: Integer;					// 考勤类型
	card_type: Integer;					// 卡类型
	reader_no: Integer;					// 感应头编号
	work_flag: Integer;					// 上/下班标志
	tx_mark: byte;					// 交易代码
	crc:array[0..1] of byte;					// CRC校验码
  end;
  Psmart_jsb_serial_t = ^smart_jsb_serial_t;
  ////////////////////////////////////////////

  {动态库接口函数定义}
  function MBLOpenCom(port,band:Integer):Integer; stdcall;
  function MBLOpenCom_SCJ(port,band:Integer):Integer; stdcall;
  function MBLCloseCom:Integer; stdcall;
  function MBLCloseCom_SCJ:Integer; stdcall;
  function MBLIsCOMOpen_SCJ:Integer;stdcall;
  function MBLIsCOMOpen:Integer;stdcall;
  function MBLGetErrno_SCJ:Integer; stdcall;
  function MBLGetErrno:Integer; stdcall;
	procedure MBLGetErrMsg(msg:PChar);stdcall;
  procedure MBLGetErrMsg_SCJ(msg:PChar);stdcall;
  function MBLReadId:Integer;stdcall;
  procedure MBLShowErrMsg;stdcall;
  function MBLWriteJh(id : Integer):Integer;stdcall;
  function MBLReadTermInfo_SCJ(term:PSMART_TERMINAL_T):Integer;stdcall;
  function MBLReadTermInfo(term:PSMART_TERMINAL_T):Integer;stdcall;
  function MBLReadType:Integer;stdcall;
  function MBLReadDate:Integer;stdcall;
  procedure MBLGetTermInfo(term:PSMART_TERMINAL_T);stdcall;
  function MBLUpRecordOne(log :PMBL_TRADE_LOG):Integer;stdcall;
  function MBLEndUpRecordOne_SCJ(serial_no:Integer):Integer;stdcall;
  function MBLEndUpRecordOne(serial_no:Integer):Integer;stdcall;
  function MBLUpHisBySerial(serial_no:Integer;log:PMBL_TRADE_LOG):Integer;stdcall;
  function MBLSetWorkKey(key:PByte):Integer;stdcall;
  function MBLSetWorkKey2(key:PChar):Integer;stdcall;
  function MBLSetWorkKey2_SCJ(key:PChar):Integer;stdcall;
  function MBLEmptyFlash:Integer;stdcall;
  function MBLSetCommision(commision:PByte):Integer;stdcall;
  function MBLSetCommision2(commision:PChar):Integer;stdcall;
  function MBLWriteId(id:PByte):Integer;stdcall;
  function MBLWriteId2(id:PChar):Integer;stdcall;
  function MBLUserUpParam(param:PByte):Integer;stdcall;
  function MBLDownBlackCard(cardid:Integer):Integer;stdcall;
  function MBLDownDelBlack(cardid:Integer):Integer;stdcall;
  function MBLDownDelBAll:Integer;stdcall;
  function MBLDownBlackVersion(version :PChar):Integer;stdcall;
  function MBLUpBlackVersion(version :PChar):Integer;stdcall;
  function MBLUpBlackExpire(expire :PChar):Integer;stdcall;
  function MBLDownBlackExpire(expire :PChar):Integer;stdcall;
  function MBLGetTermParam(param:PSMART_TERM_PARAM_T):Integer;stdcall;
  function MBLDownParam(param:PSMART_TERM_PARAM_T):Integer;stdcall;
  function MBLSetCardKind(kind:PChar):Integer;stdcall;
  function MBLGetCardKind(kind:PChar):Integer;stdcall;
  //1add 0del
  function MBLSetCardList(cardid:Integer;version:pchar;isadd:Integer):Integer;stdcall;
  function MBLSetWhiteCardList(cardid:Integer;version:pchar;isadd:Integer):Integer;stdcall;

  /////////////////////////////////////////////////////////
  function MBLUpJSBRecord(log:Psmart_jsb_serial_t):Integer;stdcall;
  function MBLUpJSBRecord_SCJ(log:Psmart_jsb_serial_t):Integer;stdcall;
  function MBLGetJSBParam(param: Psmart_jsb_param_t):Integer;stdcall;
  function MBLSetJSBParam(param: Psmart_jsb_param_t):Integer;stdcall;
  function MBLDownWhiteCard(card_id:Integer):Integer;stdcall;
  function MBLDownDelWhite(cardid:Integer):Integer;stdcall;
  function MBLDownWhiteVersion(version:PChar):Integer;stdcall;
  function MBLUpWhiteVersion(version:Pchar):Integer;stdcall;
  function MBLDownDelWAll:Integer;stdcall;
  function MBIsWhite(card_id:Integer):Integer;stdcall;
  {功能函数定义}
  function Hex2Str(hexval:array of byte;Len : Integer;
        var strval : string):Integer;
implementation

{动态库接口函数}
  function MBLOpenCom;stdcall;
    external MBLDLL name 'MBLOpenCom';
    
  function MBLOpenCom_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLOpenCom';

  function MBLCloseCom;stdcall;
    external MBLDLL name 'MBLCloseCom';

  function MBLCloseCom_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLCloseCom';

  function MBLIsCOMOpen;stdcall;
    external MBLDLL name 'MBLIsCOMOpen';
    
  function MBLIsCOMOpen_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLIsCOMOpen';

  function MBLGetErrno_SCJ;stdcall;
	external MBLDLL_SCJ name 'MBLGetErrno';

  function MBLGetErrno;stdcall;
	external MBLDLL name 'MBLGetErrno';

  procedure MBLGetErrMsg_SCJ(msg:PChar);stdcall;
    external MBLDLL_SCJ name 'MBLGetErrMsg';
  procedure MBLGetErrMsg(msg:PChar);stdcall;
    external MBLDLL name 'MBLGetErrMsg';

  function MBLReadId;stdcall;
    external MBLDLL name 'MBLReadId';
  procedure MBLShowErrMsg;stdcall;
    external MBLDLL name 'MBLShowErrMsg';
  function MBLWriteJh;stdcall;
    external MBLDLL name 'MBLWriteJh';
  function MBLReadTermInfo_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLReadTermInfo';

  function MBLReadTermInfo;stdcall;
    external MBLDLL name 'MBLReadTermInfo';

  function MBLReadType;stdcall;
    external MBLDLL name 'MBLReadType';
  function MBLReadDate;stdcall;
    external MBLDLL name 'MBLReadDate';
  procedure MBLGetTermInfo;stdcall;
    external MBLDLL name 'MBLGetTermInfo';
  function MBLUpRecordOne;stdcall;
    external MBLDLL name 'MBLUpRecordOne';
  function MBLEndUpRecordOne_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLEndUpRecordOne';

  function MBLEndUpRecordOne;stdcall;
    external MBLDLL name 'MBLEndUpRecordOne';

  function MBLUpHisBySerial;stdcall;
    external MBLDLL name 'MBLUpHisBySerial';
  function MBLSetWorkKey;stdcall;
    external MBLDLL name 'MBLSetWorkKey';
  function MBLSetWorkKey2;stdcall;
    external MBLDLL name 'MBLSetWorkKey2';
  function MBLSetWorkKey2_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLSetWorkKey2';
  function MBLEmptyFlash;stdcall;
    external MBLDLL name 'MBLEmptyFlash';
  function MBLSetCommision;stdcall;
    external MBLDLL name 'MBLSetCommision';
  function MBLSetCommision2;stdcall;
    external MBLDLL name 'MBLSetCommision2';
  function MBLWriteId;stdcall;
    external MBLDLL name 'MBLWriteId';
  function MBLWriteId2;stdcall;
    external MBLDLL name 'MBLWriteId2';
  function MBLUserUpParam;stdcall;
    external MBLDLL name 'MBLUserUpParam';
  function MBLDownBlackCard;stdcall;
    external MBLDLL name 'MBLDownBlackCard';
  function MBLDownDelBlack;stdcall;
    external MBLDLL name 'MBLDownDelBlack';
  function MBLDownDelBAll;stdcall;
    external MBLDLL name 'MBLDownDelBAll';
  function MBLDownBlackVersion;stdcall;
    external MBLDLL name 'MBLDownBlackVersion';
  function MBLUpBlackVersion;stdcall;
    external MBLDLL name 'MBLUpBlackVersion';
  function MBLUpBlackExpire;stdcall;
    external MBLDLL name 'MBLUpBlackExpire';
  function MBLDownBlackExpire;stdcall;
    external MBLDLL name 'MBLDownBlackExpire';
  function MBLGetTermParam;stdcall;
    external MBLDLL name 'MBLGetTermParam';
  function MBLSetCardKind;stdcall;
    external MBLDLL name 'MBLSetCardKind';
  function MBLGetCardKind;stdcall;
    external MBLDLL name 'MBLGetCardKind';
  function MBLDownParam;stdcall;
    external MBLDLL name 'MBLDownParam';
  function MBLSetCardList;stdcall;
    external MBLDLL name 'MBLSetCardList';
  function MBLSetWhiteCardList;stdcall;
    external MBLDLL name 'MBLSetWhiteCardList';

  //////////////////////////////////////////////////////////////
  function MBLUpJSBRecord;stdcall;
    external MBLDLL name 'MBLUpJSBRecord';
  function MBLUpJSBRecord_SCJ;stdcall;
    external MBLDLL_SCJ name 'MBLUpJSBRecord';

  function MBLGetJSBParam;stdcall;
    external MBLDLL name 'MBLGetJSBParam';
  function MBLSetJSBParam;stdcall;
    external MBLDLL name 'MBLSetJSBParam';
  function MBLDownWhiteCard;stdcall;
    external MBLDLL name 'MBLDownWhiteCard';
  function MBLDownDelWhite;stdcall;
    external MBLDLL name 'MBLDownDelWhite';
  function MBLDownWhiteVersion;stdcall;
    external MBLDLL name 'MBLDownWhiteVersion';
  function MBLUpWhiteVersion;stdcall;
    external MBLDLL name 'MBLUpWhiteVersion';
  function MBLDownDelWAll;stdcall;
    external MBLDLL name 'MBLDownDelWAll';
  function MBIsWhite;stdcall;
    external MBLDLL name 'MBIsWhite';
  
  /////////////////////////////////////////////////////

function Hex2Str(hexval: array of byte; Len: Integer;
    var strval: string): Integer;
var
  i : Integer;
  tmp : string;
begin
  Result := 0;
  SetLength(strval,Len * 2);
  for i := 0 to Len - 1 do
  begin
    tmp := Format('%s%.02x',[tmp,Ord(hexval[i])]);
  end;
  StrCopy(PChar(strval),PChar(tmp));
end;

end.
