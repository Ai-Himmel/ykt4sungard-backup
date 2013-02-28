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


  const REQIP = 'http://210.21.197.66:8889/PopsServlet';     //积分兑换平台
  const PlatId = '10000001';    //平台编号
  const normalCode = '00';      //正常返回码

  const dpt_ID = '1000';        //积分支付
  const cancel_ID = '1001';     //积分冲正，撤销
  const exchange_ID = '1100';   //实物兑换
  const exCancel_ID = '1101';   //兑换冲正
  const userQ_ID = '1200';      //用户信息查询
  const orderQ_ID = '1300';     //订单查询

  const yhjf = '03';            //优惠积分
  const gmjf = '06';            //全球通，动感地带积分(优惠积分)支付

  const ghwjf = '21';           //莞惠网积分
  const sjjf = '22';            //商家积分

  const swdh = '04';            //实物兑换
  const yhqdh = '05';           //优惠券兑换

  const hydj = '01';            //会员等级查询
  const yhjfcx = '02';          //全球通，动感地带积分(优惠积分)查询
  
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
  tmpStr := tmpStr + '<platId>'+PlatId+'</platId>';             //平台ID
  tmpStr := tmpStr + '<tyid>'+tyId+'</tyid>';                   //消费接口ID
  tmpStr := tmpStr + '<serverType>'+serType+'</serverType>';    //交易类型
  tmpStr := tmpStr + '<posId>'+POSID+'</posId>';                //POSID,POS编号，在设置卡座完成，读到sam卡号后到后台查询所属读卡器编号
  if ifDebug=1 then
    tmpStr := tmpStr + '<posNum>'+'123456789'+'</posNum>'       //psamTermId,POS终端序列号,读卡器的sam卡号
  else
    tmpStr := tmpStr + '<posNum>'+psamTermId+'</posNum>';       //psamTermId,POS终端序列号,读卡器的sam卡号
  tmpStr := tmpStr + '<merId>'+BusiID+'</merId>';               //BusiID,商户号，在设置卡座完成，读到sam卡号后到后台查询所属商户号
  tmpStr := tmpStr + '<reqDate>'+sDate+'</reqDate>';            //请求日期
  tmpStr := tmpStr + '<reqTime>'+sTime+'</reqTime>';            //请求时间
  tmpStr := tmpStr + '<posSeq>'+posSeq+'</posSeq>';             //POS流水
  tmpStr := tmpStr + '<transId>'+transId+'</transId>';          //交易流水
  tmpStr := tmpStr + '<amount>'+amount+'</amount>';             //交易金额
  tmpStr := tmpStr + '<mobile>'+''+'</mobile>';                 //手机号码
  tmpStr := tmpStr + '<password>'+''+'</password>';             //交易密码
  tmpStr := tmpStr + '<oriTransId>'+oriTransId+'</oriTransId>'; //原交易流水号,撤销交易时使用，默认为空  
  tmpStr := tmpStr + '<rfsim>';
  tmpStr := tmpStr + '<uuid>'+UUID+'</uuid>';                   //RF-SIM卡的应用序列号
  tmpStr := tmpStr + '<desc>'+''+'</desc>';                     //对明文进行BASE64编码后的字符串
  tmpStr := tmpStr + '<value>'+''+'</value>';                   //签名值
  tmpStr := tmpStr + '</rfsim>';
  Result := tmpStr;
end;

//创建消费积分,会员识别,交易撤销xml
function createDptXML(tyId,serType,amount,UUID,oriTransId:string):string;
var
  dptStr:string;
begin
  dptStr := createCommonXML(tyId,serType,amount,UUID,oriTransId);
  dptStr := dptStr + '</req>';
  Result := 'xmldata='+sdAnsiToUtf8(dptStr);
end;

//商品兑换xml,
function createItemXML(serType,UUID,code,item:string):string;
var
  itemStr:string;
begin
  itemStr := createCommonXML(exchange_ID,serType,'',UUID,'');
  itemStr := itemStr + '<additional_code>'+code+'</additional_code>';   //辅助码
  itemStr := itemStr + '<itemProperties>'+item+'</itemProperties>';     //商品属性
  itemStr := itemStr + '</req>';
  Result := 'xmldata='+sdAnsiToUtf8(itemStr);
end;

//取得本机流水号
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
        ShowMessage(e.Message+'--请重新执行该操作！');
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
          ShowMessage(e.Message+'--请重新执行该操作！');
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
        ShowMessage(e.Message+'--请重新执行该操作！');
        Exit;
      end;
    end;

    Result := tmpSerial;
  finally
    myfile.Destroy;
  end;

end;

//记录最后一笔交易成功的流水号
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
        ShowMessage(e.Message+'--请重新执行该操作！');
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
        ShowMessage(e.Message+'--请重新执行该操作！');
        Exit;
      end;
    end;
    Result := 0;
  finally
    myfile.Destroy;
  end;
end;

//取得最后一笔交易的交易流水
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
        ShowMessage(e.Message+'--请重新执行该操作！');
        Exit;
      end;
    end;
    sKey := GetSerialTypeKey(serialType);
    try
      Result := myfile.ReadString('lastserial',sKey,'');
    except
      on e:Exception do
      begin
        ShowMessage(e.Message+'--请重新执行该操作！');
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
