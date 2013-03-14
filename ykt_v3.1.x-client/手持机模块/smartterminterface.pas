unit smartterminterface;

interface

uses Windows,SysUtils;

const
  MBLDLL = 'mobileterm.dll';
  MBLDLL_SCJ = 'mobileterm_SCJ.dll';

type
  {������ˮ�ṹ����}
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
  {�ֳֻ���Ϣ�ṹ����}
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

  {�ֳֻ���������}
  SMART_TERM_PARAM_T = packed record
    commision:array[0..3] of byte;	//��Ȩ��
    termno : Integer;				//����
    pswd_switch: Integer;		//���뿪��
    consume_way: Integer;		// �շѷ�ʽ
    card_max_cnt: Integer;		//��Ƭ���ʹ�ô���
    card_type:array[0..1] of byte;	//�����������
    purse_max: Integer;			//Ǯ���������޶�
    consume_max: Integer;		//ÿ����������޶�
    purse_min: Integer;			//Ǯ���������޶�
    fixed_count: Integer;		//��ȡ�ֵ��
    comsume_type: Integer;		//
    band_rate: Integer;			//������
    purse_attr: Integer;			// Ǯ������
    person_key: array[0..3] of byte;		//������Կǰ�ĸ��ֽ�
    sys_pwd:array[0..1] of byte;		//ϵͳ����Ա����
    card_set: Integer;			//����ʹ�ÿ�����
  end;
  PSMART_TERM_PARAM_T = ^SMART_TERM_PARAM_T;

  smart_jsb_param_t = packed record
	commision:array[0..3] of byte;
	termno : Integer;
	pswd_switch: Integer;
	work_mode: Integer;		// ��ʱ������ģʽ 2
	open_lock_time1: Integer; // ���� 1 ��ʱ��
	open_lock_time2: Integer; // ���� 2 ��ʱ��
	card_type:array[0..1] of Byte; // ������
	is_gate_mode: Integer;	// �Ƿ�����ͨ����ģʽ 0
	is_save_record: Integer;	// �Ƿ�洢�򿨼�¼
	num_reader: Integer;			// ��Ӧͷ��Ŀ
	reversed:array[0..2] of byte;	// ����
	sys_pwd:array[0..2] of byte;		// ϵͳ����Ա����
	v10_pwd:array[0..1] of byte;
	v10_purse_sect: Integer;		// v10 ����/Ǯ������
	is_led_mode: Integer;		// �Ƿ� LED ģʽ
	band_rate: Integer;
	time_val_switch: Integer;	// ʱ��������
	time_val:array[0..1] of Byte;		// ʱ����
	card_set: Integer;			// ������
  end;
  Psmart_jsb_param_t = ^smart_jsb_param_t;

  smart_jsb_serial_t = packed record
	phyid:array[0..3] of byte;				// �豸����ID��HEX��ʽ
	ver: Integer;						// ͨѶ�汾
	runreason: Integer;					// ����ԭ��
	serial_no: Integer;					// ��ˮ��
	card_id: Integer;					// ���׿���
	tx_datetime:array[0..12] of char;			// ��������ʱ�䣬yymmddHHnnss/dow
	day_of_week: Integer;				// ����
	work_mode: Integer;					// ����ģʽ
	check_type: Integer;					// ��������
	card_type: Integer;					// ������
	reader_no: Integer;					// ��Ӧͷ���
	work_flag: Integer;					// ��/�°��־
	tx_mark: byte;					// ���״���
	crc:array[0..1] of byte;					// CRCУ����
  end;
  Psmart_jsb_serial_t = ^smart_jsb_serial_t;
  ////////////////////////////////////////////

  {��̬��ӿں�������}
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
  {���ܺ�������}
  function Hex2Str(hexval:array of byte;Len : Integer;
        var strval : string):Integer;
implementation

{��̬��ӿں���}
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
