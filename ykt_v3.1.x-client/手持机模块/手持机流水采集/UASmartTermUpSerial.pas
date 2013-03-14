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
  WorkView.FieldByName('�ն��豸�ɣ�').DefaultValue := '';
  WorkView.FieldByName('������ˮ��').DefaultValue := 0;
  WorkView.FieldByName('���׿���').DefaultValue := 0;
  WorkView.FieldByName('Ǯ����').DefaultValue := 0;
  WorkView.FieldByName('��������').DefaultValue := '';
  WorkView.FieldByName('����ʱ��').DefaultValue := '';
  WorkView.FieldByName('�ۼ�ʹ�ô���').DefaultValue := 0;
  WorkView.FieldByName('�������ѽ��').DefaultValue := 0;
  WorkView.FieldByName('�뿨���').DefaultValue := 0;
  WorkView.FieldByName('�������').DefaultValue := 0;
  WorkView.FieldByName('���ױ��').DefaultValue := 0;
  WorkView.FieldByName('ͨ�Ű汾��').DefaultValue := 0;
  WorkView.FieldByName('����ͨ������ԭ��').DefaultValue := 0;
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
  WorkView.FieldByName('�ն��豸�ɣ�').Data.SetString(tmp);
  WorkView.FieldByName('������ˮ��').Data.SetInteger(Log^.serial_no);
  WorkView.FieldByName('���׿���').Data.SetInteger(Log^.card_id);
  WorkView.FieldByName('Ǯ����').Data.SetInteger(0);
  tmp := Copy(Log^.tx_datetime,1,6);
  WorkView.FieldByName('��������').Data.SetString(tmp);
  tmp := Copy(Log^.tx_datetime,7,6);
  WorkView.FieldByName('����ʱ��').Data.SetString(tmp);
  WorkView.FieldByName('�ۼ�ʹ�ô���').Data.SetInteger(Log^.tx_cnt);
  WorkView.FieldByName('�������ѽ��').Data.SetInteger(Log^.tx_trade_amount);
  WorkView.FieldByName('�뿨���').Data.SetInteger(Log^.in_card_amount);
  WorkView.FieldByName('�������').Data.SetInteger(Log^.out_card_amount);
  WorkView.FieldByName('���ױ��').Data.SetInteger(Log^.tx_mark);
  WorkView.FieldByName('ͨ�Ű汾��').Data.SetInteger(Log^.ver);
  WorkView.FieldByName('����ͨ������ԭ��').Data.SetInteger(Log^.runreason);
  Hex2Str(Log^.crc,SizeOf(Log^.crc),tmp);

  WorkView.FieldByName('CRC').Data.SetString(tmp);
  try
    MainRequest.SendCommand;
    if WorkView.FieldByName('����ֵ').Data.AsInteger = 0 then
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
  TipMessage('��ʼ�ϴ���ˮ...');
  FSerialCnt := 0;
  retries := 0;
  while True do
  begin

    TipMessage('�ϴ���ˮ�У��벻Ҫ�Ͽ��ֳֻ�...');
    retval := UploadOneRecord(@TradeLog);
    if retval <> 0 then
    begin
      if MBLGetErrno =  E_NO_SERIAL_EXISTS then
      begin
        Context.GetDialogSystem.ShowMessage(
          Format('�ϴ���ˮ��ɣ���[%d]��',[serial_cnt]));
        TipMessage('�ϴ���ˮ���');
        Exit;
      end
      else if MBLGetErrno = E_CRC_ERROR then
      begin
        // CRC ʧ������
        Inc(retries);
        if retries >= 3 then
        begin
          // ��ˮCRCʧ��
          GetTermError;
          Exit;
        end;
        Continue;
      end;
      GetTermError;
      TipMessage('�ϴ���ˮ���');
      Exit;
    end;
    TipMessage(Format('������ˮ...��ˮ��[%d]',[TradeLog.serial_no]));
    retval := SendRecordToSvr(@TradeLog);
    if retval <> 0 then
    begin
      Context.GetDialogSystem.ShowError('������ˮʧ�ܣ�');
      TipMessage('�ϴ���ˮ���');
      Exit;
    end;
    AddSerial2List(@TradeLog);
    LabRecordCount.Caption := Format('���� %d ����ˮ',[serial_cnt+1]);
    TipMessage('ȷ����ˮ...');
    retval := ConfirmOneRecord(TradeLog.serial_no);
    if retval<> 0 then
    begin
      Context.GetDialogSystem.ShowError('ȷ�ϵ�ǰ��ˮʧ��');
      TipMessage('�ϴ���ˮ���');
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
  TUIStdClassFactory.Create('�ɼ�������ˮ',TfaqhSmartTermUpSerial);

end.