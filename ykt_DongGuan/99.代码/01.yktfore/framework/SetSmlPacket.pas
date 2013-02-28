unit SetSmlPacket;

interface
uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,WVCmdReq,
  KSClientConsts,carddll,waterdll;
const
  //****************************************************************************
  //动态库定义
  KS_SZROAD_WATER = 1;  // 凯路水控
  KS_YNCS_XT_WATER = 2; // 云交职水控
  KS_HD_WATER = 3;      // 汇多脱机水控

function appendSmlSerial(wv:TWorkView;wvRequest:TWVRequest;
    custId:integer;packettype:integer;
    outCardId:integer;inCardId:integer;
    smlMoney:real):integer;

implementation

function appendSmlSerial(wv:TWorkView;wvRequest:TWVRequest;
    custId:integer;packettype:integer;
    outCardId:integer;inCardId:integer;
    smlMoney:real):integer;
begin
  //把小钱包余额发送到后台，后台记入流水
  wv.FieldByName('操作标志').data.SetString('A');
  wv.FieldByName('客户号').data.setinteger(custId);
  wv.FieldByName('小钱包号').data.setinteger(packettype);
  wv.FieldByName('转出卡号').data.setinteger(outCardId);
  wv.FieldByName('转入卡号').data.setinteger(inCardId);
  wv.FieldByName('小钱包金额').data.setfloat(smlMoney);
  try
    wvRequest.SendCommand;
  except
    result := -1;
    exit;
  end;
  result := 0;
end;
   

end.
