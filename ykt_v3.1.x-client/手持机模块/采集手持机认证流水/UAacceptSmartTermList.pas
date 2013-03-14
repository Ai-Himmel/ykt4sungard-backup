unit UAacceptSmartTermList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, WVCmdProc,
  KCWVProcBinds, WVCmdTypeInfo, RzDBGrid, ComCtrls, RzListVw,smartterminterface,
  Buttons;
const
  E_NO_SERIAL_EXISTS = 10;
  E_CRC_ERROR = 107;

type
  TfaqhacceptSmartTermList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    lvSerial: TRzListView;
    ibnUpLoadSerial: TBitBtn;
    sbInfo: TStatusBar;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure ibnUpLoadSerialClick(Sender: TObject);
  private

    { Private declarations }
    FTermInfo : SMART_TERMINAL_T;
    FSerialCnt: Integer;
    function ConnectToSmartTerm:Integer;
    function UploadOneRecord(Log:Psmart_jsb_serial_t):Integer;
    function ConfirmOneRecord(serialno:Integer):Integer;
    function SendRecordToSvr(Log:Psmart_jsb_serial_t):Integer;
    procedure AddSerial2List(Log:Psmart_jsb_serial_t);
    procedure TipMessage(msg:string);
    procedure GetTermError;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhacceptSmartTermList: TfaqhacceptSmartTermList;

implementation

uses KsFrameworks, KSFrameWorkUtils, KSComCmdDefs, KSCustomers, Contnrs,
     KSClientConsts,KSDataDictionary,DataUsageUtils,SmartCardCommon,LogFile;
     
{$R *.DFM}

procedure TfaqhacceptSmartTermList.AddSerial2List(Log: Psmart_jsb_serial_t);
var
  item :TListItem;
  tmp : string;
begin
  //

  item := lvSerial.Items.Add;
  Inc(FSerialCnt);

  tmp := Format('%.04d',[FSerialCnt]);
  item.Caption := tmp;
  Hex2Str(FTermInfo.phyid,SizeOf(FTermInfo.phyid),tmp);
  item.SubItems.Add(tmp);

  tmp := IntToStr(Log^.serial_no);
  item.SubItems.Add(tmp);

  tmp := IntToStr(Log^.ver);
  item.SubItems.Add(tmp);

  item.SubItems.Add(Log^.tx_datetime);
  tmp := IntToStr(Log^.card_id);
  item.SubItems.Add(tmp);
  
  tmp := IntToStr(Log^.tx_mark);
  item.SubItems.Add(tmp);


  tmp := IntToStr(Log^.runreason);
  item.SubItems.Add(tmp);


  Hex2Str(Log^.crc,SizeOf(Log^.crc),tmp);
  item.SubItems.Add(tmp);
end;

function TfaqhacceptSmartTermList.ConfirmOneRecord(
  serialno: Integer): Integer;
begin
  Result := -1;
  if MBLEndUpRecordOne_SCJ(serialno) = 0 then
    Result := 0;
end;

function TfaqhacceptSmartTermList.ConnectToSmartTerm: Integer;
begin
  Result := -1;
  if MBLIsCOMOpen_SCJ = 0 then
    Result := MBLReadTermInfo_SCJ(@FTermInfo);
end;

procedure TfaqhacceptSmartTermList.GetTermError;
var
  msg : array[0..512] of char;
begin
  ZeroMemory(@msg ,SizeOf(msg));
  MBLGetErrMsg_SCJ(PChar(@msg));
  Context.GetDialogSystem.ShowError(msg);
end;

procedure TfaqhacceptSmartTermList.Init;
begin
  inherited;
  WorkView.FieldByName('终端设备ID').DefaultValue := '';
  WorkView.FieldByName('交易流水号').DefaultValue := 0;
  WorkView.FieldByName('交易卡号').DefaultValue := '';
  WorkView.FieldByName('交易日期').DefaultValue := 0;
  WorkView.FieldByName('交易时间').DefaultValue := 0;
  WorkView.FieldByName('交易标记').DefaultValue := 0;
  WorkView.FieldByName('通信版本号').DefaultValue := 0;
  WorkView.FieldByName('数据通信启动原因').DefaultValue := 0;
  WorkView.FieldByName('CRC').DefaultValue := '';
  WorkView.Reset;
end;

function TfaqhacceptSmartTermList.SendRecordToSvr(
  Log: Psmart_jsb_serial_t): Integer;
var
  tmp : string;
begin
  Result := -1;
  Hex2Str(FTermInfo.phyid,SizeOf(FTermInfo.phyid),tmp);
  WorkView.FieldByName('终端设备ID').Data.SetString(tmp);
  WorkView.FieldByName('交易流水号').Data.SetInteger(Log^.serial_no);
  WorkView.FieldByName('交易卡号').Data.SetInteger(Log^.card_id);
  tmp := Copy(Log^.tx_datetime,1,6);
  WorkView.FieldByName('交易日期').Data.SetString(tmp);
  tmp := Copy(Log^.tx_datetime,7,6);
  WorkView.FieldByName('交易时间').Data.SetString(tmp);
  WorkView.FieldByName('交易标记').Data.SetInteger(Log^.tx_mark);
  WorkView.FieldByName('通信版本号').Data.SetInteger(Log^.ver);
  WorkView.FieldByName('数据通信启动原因').Data.SetInteger(Log^.runreason);
  Hex2Str(Log^.crc,SizeOf(Log^.crc),tmp);

  WorkView.FieldByName('CRC').Data.SetString(tmp);
  try
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回值').Data.AsInteger = 0 then
      Result := 0;
  except
    on Ex :Exception do
    begin
      Context.GetDialogSystem.ShowError(Ex.Message);
    end;
  end;
end;

procedure TfaqhacceptSmartTermList.TipMessage(msg: string);
begin
  sbInfo.Panels[0].Text := msg;
  sbInfo.Update;
end;

function TfaqhacceptSmartTermList.UploadOneRecord(
  Log: Psmart_jsb_serial_t): Integer;
begin
  Result := -1;
  if MBLUpJSBRecord_SCJ(Log) = 0 then
    Result := 0;
end;

procedure TfaqhacceptSmartTermList.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;



procedure TfaqhacceptSmartTermList.ibnUpLoadSerialClick(Sender: TObject);
var
  TradeLog : smart_jsb_serial_t;
  retval : Integer;
  serial_cnt,retries : Integer;
  I:Integer;
begin
  //inherited;
  ZeroMemory(@TradeLog,SizeOf(TradeLog));
  if ConnectToSmartTerm <> 0 then
  begin
    GetTermError;
    Exit;
  end;
  serial_cnt := 0;
  TipMessage('开始上传流水...');
  FSerialCnt := 0;
  retries := 0;
  while True do
  begin

    TipMessage('上传流水中，请不要断开手持机...');

    retval := MBLUpJSBRecord_SCJ(@TradeLog);
    if retval <> 0 then
    begin
      if MBLGetErrno_SCJ =  E_NO_SERIAL_EXISTS then
      begin
        Context.GetDialogSystem.ShowMessage(
          Format('上传流水完成，共[%d]条',[serial_cnt]));
        TipMessage('上传流水完成');
        Exit;
      end
      else if MBLGetErrno_SCJ = E_CRC_ERROR then
      begin
        // CRC 失败重试
        Inc(retries);
        if retries >= 3 then
        begin
          // 流水CRC失败
          GetTermError;
          Exit;
        end;
        Continue;
      end;
      GetTermError;
      TipMessage('上传流水完成');
      Exit;
    end;
    TipMessage(Format('保存流水...流水号[%d]',[TradeLog.serial_no]));
    retval := SendRecordToSvr(@TradeLog);
    if retval <> 0 then
    begin
      Context.GetDialogSystem.ShowError('保存流水失败！');
      TipMessage('上传流水完成');
      Exit;
    end;
    AddSerial2List(@TradeLog);
    LabRecordCount.Caption := Format('保存 %d 条流水',[serial_cnt+1]);
    TipMessage('确认流水...');
    retval := ConfirmOneRecord(TradeLog.serial_no);
    if retval<> 0 then
    begin
      Context.GetDialogSystem.ShowError('确认当前流水失败');
      TipMessage('上传流水完成');
      Exit;
    end;
    Inc(serial_cnt);
    retries := 0;
    Application.ProcessMessages;
    Sleep(500);
  end;
end;

initialization
  TUIStdClassFactory.Create('采集认证流水',TfaqhacceptSmartTermList);

end.