unit SetSmlPacket;

interface
uses
  Windows, Messages, SysUtils, Classes, Dialogs,KSFrameWorks,WorkViews,WVCmdReq,
  KSClientConsts,carddll,waterdll;
const
  //****************************************************************************
  //��̬�ⶨ��
  KS_SZROAD_WATER = 1;  // ��·ˮ��
  KS_YNCS_XT_WATER = 2; // �ƽ�ְˮ��
  KS_HD_WATER = 3;      // ����ѻ�ˮ��

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
  //��СǮ�����͵���̨����̨������ˮ
  wv.FieldByName('������־').data.SetString('A');
  wv.FieldByName('�ͻ���').data.setinteger(custId);
  wv.FieldByName('СǮ����').data.setinteger(packettype);
  wv.FieldByName('ת������').data.setinteger(outCardId);
  wv.FieldByName('ת�뿨��').data.setinteger(inCardId);
  wv.FieldByName('СǮ�����').data.setfloat(smlMoney);
  try
    wvRequest.SendCommand;
  except
    result := -1;
    exit;
  end;
  result := 0;
end;
   

end.
