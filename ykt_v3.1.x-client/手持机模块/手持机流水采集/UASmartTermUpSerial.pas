unit UASmartTermUpSerial;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid, smartterminterface,
  ComCtrls, RzListVw, Buttons;

const
  E_NO_SERIAL_EXISTS = 10;
  E_CRC_ERROR = 107;
  
type
  TfaqhSmartTermUpSerial = class(TfaqhSimpleQueryTemp)
    Panel2: TPanel;
    ibnUpLoadSerial: TBitBtn;
    lvSerial: TRzListView;
    sbInfo: TStatusBar;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure ibnUpLoadSerialClick(Sender: TObject);
  private
    FTermInfo : SMART_TERMINAL_T;
    FSerialCnt: Integer;
    function ConnectToSmartTerm:Integer;
    function UploadOneRecord(Log:PMBL_TRADE_LOG):Integer;
    function ConfirmOneRecord(serialno:Integer):Integer;
    function SendRecordToSvr(Log:PMBL_TRADE_LOG):Integer;
    procedure AddSerial2List(Log:PMBL_TRADE_LOG);
    procedure TipMessage(msg:string);
    procedure GetTermError;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmartTermUpSerial: TfaqhSmartTermUpSerial;

implementation

uses KsFrameworks;
     
{$R *.DFM}

function TfaqhSmartTermUpSerial.ConfirmOneRecord(
  serialno: Integer): Integer;
begin
  Result := -1;
  if MBLEndUpRecordOne(serialno) = 0 then
    Result := 0;
end;

function TfaqhSmartTermUpSerial.ConnectToSmartTerm: Integer;
begin
  Result := -1;
  if MBLIsCOMOpen = 0 then
    Result := MBLReadTermInfo(@FTermInfo);
end;

procedure TfaqhSmartTermUpSerial.Init;
begin
  inherited;
  WorkView.FieldByName('终端设备ＩＤ').DefaultValue := '';
  WorkView.FieldByName('交易流水号').DefaultValue := 0;
  WorkView.FieldByName('交易卡号').DefaultValue := 0;
  WorkView.FieldByName('钱包号').DefaultValue := 0;
  WorkView.FieldByName('交易日期').DefaultValue := '';
  WorkView.FieldByName('交易时间').DefaultValue := '';
  WorkView.FieldByName('累计使用次数').DefaultValue := 0;
  WorkView.FieldByName('本次消费金额').DefaultValue := 0;
  WorkView.FieldByName('入卡金额').DefaultValue := 0;
  WorkView.FieldByName('出卡金额').DefaultValue := 0;
  WorkView.FieldByName('交易标记').DefaultValue := 0;
  WorkView.FieldByName('通信版本号').DefaultValue := 0;
  WorkView.FieldByName('数据通信启动原因').DefaultValue := 0;
  //WorkView.FieldByName('').DefaultValue := ;
  WorkView.Reset;
end;

function TfaqhSmartTermUpSerial.SendRecordToSvr(
  Log: PMBL_TRADE_LOG): Integer;
var
  tmp : string;
begin
  Result := -1;
  Hex2Str(FTermInfo.phyid,SizeOf(FTermInfo.phyid),tmp);
  WorkView.FieldByName('终端设备ＩＤ').Data.SetString(tmp);
  WorkView.FieldByName('交易流水号').Data.SetInteger(Log^.serial_no);
  WorkView.FieldByName('交易卡号').Data.SetInteger(Log^.card_id);
  WorkView.FieldByName('钱包号').Data.SetInteger(0);
  tmp := Copy(Log^.tx_datetime,1,6);
  WorkView.FieldByName('交易日期').Data.SetString(tmp);
  tmp := Copy(Log^.tx_datetime,7,6);
  WorkView.FieldByName('交易时间').Data.SetString(tmp);
  WorkView.FieldByName('累计使用次数').Data.SetInteger(Log^.tx_cnt);
  WorkView.FieldByName('本次消费金额').Data.SetInteger(Log^.tx_trade_amount);
  WorkView.FieldByName('入卡金额').Data.SetInteger(Log^.in_card_amount);
  WorkView.FieldByName('出卡金额').Data.SetInteger(Log^.out_card_amount);
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

function TfaqhSmartTermUpSerial.UploadOneRecord(
  Log: PMBL_TRADE_LOG): Integer;
begin
  Result := -1;
  if MBLUpRecordOne(Log) = 0 then
    Result := 0;
end;

procedure TfaqhSmartTermUpSerial.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSmartTermUpSerial.ibnUpLoadSerialClick(Sender: TObject);
var
  TradeLog : MBL_TRADE_LOG;
  retval : Integer;
  serial_cnt,retries : Integer;
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
    retval := UploadOneRecord(@TradeLog);
    if retval <> 0 then
    begin
      if MBLGetErrno =  E_NO_SERIAL_EXISTS then
      begin
        Context.GetDialogSystem.ShowMessage(
          Format('上传流水完成，共[%d]条',[serial_cnt]));
        TipMessage('上传流水完成');
        Exit;
      end
      else if MBLGetErrno = E_CRC_ERROR then
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

procedure TfaqhSmartTermUpSerial.TipMessage(msg: string);
begin
  //
  sbInfo.Panels[0].Text := msg;
  sbInfo.Update;
end;

procedure TfaqhSmartTermUpSerial.GetTermError;
var
  msg : array[0..512] of char;
begin
  ZeroMemory(@msg ,SizeOf(msg));
  MBLGetErrMsg(PChar(@msg));
  Context.GetDialogSystem.ShowError(msg); 
end;

procedure TfaqhSmartTermUpSerial.AddSerial2List(Log: PMBL_TRADE_LOG);
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
  tmp := IntToStr(Log^.runreason);
  item.SubItems.Add(tmp);
  item.SubItems.Add(Log^.tx_datetime);
  tmp := IntToStr(Log^.card_id);
  item.SubItems.Add(tmp);

  tmp := IntToStr(Log^.tx_cnt);
  item.SubItems.Add(tmp);
  tmp := Format('%.2f',[Log^.in_card_amount/100]);
  item.SubItems.Add(tmp);
  tmp := Format('%.2f',[Log^.out_card_amount/100]);
  item.SubItems.Add(tmp);
  tmp := Format('%.2f',[Log^.tx_trade_amount/100]);
  item.SubItems.Add(tmp);
  tmp := IntToStr(Log^.tx_mark);
  item.SubItems.Add(tmp);
  Hex2Str(Log^.crc,SizeOf(Log^.crc),tmp);
  item.SubItems.Add(tmp);
end;

initialization
  TUIStdClassFactory.Create('采集消费流水',TfaqhSmartTermUpSerial);

end.