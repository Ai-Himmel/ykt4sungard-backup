unit UCommon;

interface
uses
  Windows, Messages, SysUtils, Classes, Controls, Dialogs, StdCtrls, ExtCtrls,
  INIFiles,NativeXml,KSClientConsts;
  
  function createCommonXML(tyId,serType,amount,UUID,oriTransId:string):string;

  function createDptXML(tyId,serType,amount,UUID,oriTransId:string):string;

  function createItemXML(serType,UUID,code,item:string):string;

  function getSerialNo():string;
  function addZero(inNum:string):string;
  function WriteLastSerial(serialType:string;serialNo:string):Integer;
  function GetSerialTypeKey(serialType:string):string;
  function GetLastSerialNo(serialType:string):string;


  const REQIP = 'http://210.21.197.66:8889/PopsServlet';     //���ֶһ�ƽ̨
  const PlatId = '10000001';    //ƽ̨���
  const normalCode = '00';      //����������

  const dpt_ID = '1000';        //����֧��
  const cancel_ID = '1001';     //���ֳ���������
  const exchange_ID = '1100';   //ʵ��һ�
  const exCancel_ID = '1101';   //�һ�����
  const userQ_ID = '1200';      //�û���Ϣ��ѯ
  const orderQ_ID = '1300';     //������ѯ

  const yhjf = '03';            //�Żݻ���
  const gmjf = '06';            //ȫ��ͨ�����еش�����(�Żݻ���)֧��

  const ghwjf = '21';           //ݸ��������
  const sjjf = '22';            //�̼һ���

  const swdh = '04';            //ʵ��һ�
  const yhqdh = '05';           //�Ż�ȯ�һ�

  const hydj = '01';            //��Ա�ȼ���ѯ
  const yhjfcx = '02';          //ȫ��ͨ�����еش�����(�Żݻ���)��ѯ
  
implementation

function createCommonXML(tyId,serType,amount,UUID,oriTransId:string):string;
var
  tmpStr : string;
  sDate,sTime,posSeq,transId:string;
begin
  sDate := FormatDateTime('yyyyMMdd',Date);
  sTime := FormatDateTime('hhMMss',Now);
  posSeq := getSerialNo;
  transId := posId+sDate+sTime+posSeq;
  tmpStr := tmpStr + '<?xml version="1.0" encoding="utf-8"?>';
  tmpStr := tmpStr + '<req>';
  tmpStr := tmpStr + '<platId>'+PlatId+'</platId>';             //ƽ̨ID
  tmpStr := tmpStr + '<tyid>'+tyId+'</tyid>';                   //���ѽӿ�ID
  tmpStr := tmpStr + '<serverType>'+serType+'</serverType>';    //��������
  tmpStr := tmpStr + '<posId>'+POSID+'</posId>';                //POSID,POS��ţ������ÿ�����ɣ�����sam���ź󵽺�̨��ѯ�������������
  if ifDebug=1 then
    tmpStr := tmpStr + '<posNum>'+'123456789'+'</posNum>'       //psamTermId,POS�ն����к�,��������sam����
  else
    tmpStr := tmpStr + '<posNum>'+psamTermId+'</posNum>';       //psamTermId,POS�ն����к�,��������sam����
  tmpStr := tmpStr + '<merId>'+BusiID+'</merId>';               //BusiID,�̻��ţ������ÿ�����ɣ�����sam���ź󵽺�̨��ѯ�����̻���
  tmpStr := tmpStr + '<reqDate>'+sDate+'</reqDate>';            //��������
  tmpStr := tmpStr + '<reqTime>'+sTime+'</reqTime>';            //����ʱ��
  tmpStr := tmpStr + '<posSeq>'+posSeq+'</posSeq>';             //POS��ˮ
  tmpStr := tmpStr + '<transId>'+transId+'</transId>';          //������ˮ
  tmpStr := tmpStr + '<amount>'+amount+'</amount>';             //���׽��
  tmpStr := tmpStr + '<mobile>'+''+'</mobile>';                 //�ֻ�����
  tmpStr := tmpStr + '<password>'+''+'</password>';             //��������
  tmpStr := tmpStr + '<oriTransId>'+oriTransId+'</oriTransId>'; //ԭ������ˮ��,��������ʱʹ�ã�Ĭ��Ϊ��  
  tmpStr := tmpStr + '<rfsim>';
  tmpStr := tmpStr + '<uuid>'+UUID+'</uuid>';                   //RF-SIM����Ӧ�����к�
  tmpStr := tmpStr + '<desc>'+''+'</desc>';                     //�����Ľ���BASE64�������ַ���
  tmpStr := tmpStr + '<value>'+''+'</value>';                   //ǩ��ֵ
  tmpStr := tmpStr + '</rfsim>';
  Result := tmpStr;
end;

//�������ѻ���,��Աʶ��,���׳���xml
function createDptXML(tyId,serType,amount,UUID,oriTransId:string):string;
var
  dptStr:string;
begin
  dptStr := createCommonXML(tyId,serType,amount,UUID,oriTransId);
  dptStr := dptStr + '</req>';
  Result := 'xmldata='+sdAnsiToUtf8(dptStr);
end;

//��Ʒ�һ�xml,
function createItemXML(serType,UUID,code,item:string):string;
var
  itemStr:string;
begin
  itemStr := createCommonXML(exchange_ID,serType,'',UUID,'');
  itemStr := itemStr + '<additional_code>'+code+'</additional_code>';   //������
  itemStr := itemStr + '<itemProperties>'+item+'</itemProperties>';     //��Ʒ����
  itemStr := itemStr + '</req>';
  Result := 'xmldata='+sdAnsiToUtf8(itemStr);
end;

//ȡ�ñ�����ˮ��
function getSerialNo():string;
var
  myfile:TIniFile;
  sDate,serialNo,tmpDate,tmpSerial:string;
begin
  myfile := nil;
  try
    try
      myfile := TIniFile.Create(appPath+'../configs/SetPara.ini');
    except
      on e:Exception do
      begin
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;
    sDate := myfile.ReadString('tradeserial','sdate','20101010');
    tmpDate := FormatDateTime('yyyyMMdd',Date);
    if tmpDate<>sDate then
    begin
      try
        myfile.WriteString('tradeserial','sdate',tmpDate);
        myfile.WriteString('tradeserial','serialno','000009');
      except
        on e:Exception do
        begin
          ShowMessage(e.Message+'--������ִ�иò�����');
          Exit;
        end;
      end;
    end;
    serialNo := myfile.ReadString('tradeserial','serialno','000009');
    tmpSerial := addZero(IntToStr(StrToInt(serialNo)+1));
    try
      myfile.WriteString('tradeserial','serialno',tmpSerial);
    except
      on e:Exception do
      begin
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;

    Result := tmpSerial;
  finally
    myfile.Destroy;
  end;

end;

//��¼���һ�ʽ��׳ɹ�����ˮ��
function WriteLastSerial(serialType:string;serialNo:string):Integer;
var
  myfile:TIniFile;
  sKey:string;
begin
  myfile := nil;
  try
    try
      myfile := TIniFile.Create(appPath+'../configs/SetPara.ini');
    except
      on e:Exception do
      begin
        Result := -1;
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;
    sKey := GetSerialTypeKey(serialType);
    try
      myfile.WriteString('lastserial',sKey,serialNo);
    except
      on e:Exception do
      begin
        Result := -2;
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;
    Result := 0;
  finally
    myfile.Destroy;
  end;
end;

//ȡ�����һ�ʽ��׵Ľ�����ˮ
function GetLastSerialNo(serialType:string):string;
var
  myfile:TIniFile;
  sKey:string;
begin
  myfile := nil;
  try
    try
      myfile := TIniFile.Create(appPath+'../configs/SetPara.ini');
    except
      on e:Exception do
      begin
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;
    sKey := GetSerialTypeKey(serialType);
    try
      Result := myfile.ReadString('lastserial',sKey,'');
    except
      on e:Exception do
      begin
        ShowMessage(e.Message+'--������ִ�иò�����');
        Exit;
      end;
    end;
  finally
    myfile.Destroy;
  end;

end;

function GetSerialTypeKey(serialType:string):string;
var
  sKey:string;
begin
  if serialType=yhjf then
    sKey := 'yhjf'
  else
  if serialType=gmjf then
    sKey := 'gmjf'
  else
  if serialType=ghwjf then
    sKey := 'ghwjf'
  else
  if serialType=sjjf then
    sKey := 'sjjf'
  else
    sKey := serialType;
  Result := sKey;
end;

function addZero(inNum:string):string;
var
  i:Integer;
  tmpStr:string;
begin
  for i := 6 downto Length(inNum)+1 do
  begin
    tmpStr := tmpStr + '0';
  end;
  Result := tmpStr+inNum;
end;
end.
