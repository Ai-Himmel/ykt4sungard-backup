unit smartterminterface;

interface

uses Windows,SysUtils;

const
  MBLDLL = 'mobileterm.dll';

type
  {交易流水结构定义}
  MBL_TRADE_LOG = record
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
  SMART_TERMINAL_T = record
    port,termno: Integer;
	  commision: array[0..3] of Byte;
	  phyid: array[0..3] of Byte;
	  level_array: array[0..4] of Byte;
    level : Integer;
	  termtype: array[0..1] of Byte;
    verdate : array[0..8] of Char;
  end;
  PSMART_TERMINAL_T = ^SMART_TERMINAL_T;
  ////////////////////////////////////////////

  {动态库接口函数定义}
  function MBLOpenCom(port,band:Integer):Integer; stdcall;
  function MBLCloseCom:Integer; stdcall;
  function MBLReadId:Integer;stdcall;
  procedure MBLShowErrMsg;stdcall;
  function MBLWriteJh(id : Integer):Integer;stdcall;
  function MBLReadTermInfo(term:PSMART_TERMINAL_T):Integer;stdcall;
  function MBLReadType:Integer;stdcall;
  function MBLReadDate:Integer;stdcall;
  procedure MBLGetTermInfo(term:PSMART_TERMINAL_T);stdcall;
  function MBLUpRecordOne(log :PMBL_TRADE_LOG):Integer;stdcall;
  function MBLEndUpRecordOne(serial_no:Integer):Integer;stdcall;
  function MBLUpHisBySerial(serial_no:Integer;log:PMBL_TRADE_LOG):Integer;stdcall;
  function MBLSetWorkKey(key:PByte):Integer;stdcall;
  function MBLSetWorkKey2(key:PChar):Integer;stdcall;
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

  {功能函数定义}
  function Hex2Str(hexval:array of byte;Len : Integer;
        var strval : string):Integer;
implementation

{动态库接口函数}
  function MBLOpenCom;stdcall;
    external MBLDLL name 'MBLOpenCom';
  function MBLCloseCom;stdcall;
    external MBLDLL name 'MBLCloseCom';
  function MBLReadId;stdcall;
    external MBLDLL name 'MBLReadId';
  procedure MBLShowErrMsg;stdcall;
    external MBLDLL name 'MBLShowErrMsg';
  function MBLWriteJh;stdcall;
    external MBLDLL name 'MBLWriteJh';
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
  function MBLEndUpRecordOne;stdcall;
    external MBLDLL name 'MBLEndUpRecordOne';
  function MBLUpHisBySerial;stdcall;
    external MBLDLL name 'MBLUpHisBySerial';
  function MBLSetWorkKey;stdcall;
    external MBLDLL name 'MBLSetWorkKey';
  function MBLSetWorkKey2;stdcall;
    external MBLDLL name 'MBLSetWorkKey2';
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
