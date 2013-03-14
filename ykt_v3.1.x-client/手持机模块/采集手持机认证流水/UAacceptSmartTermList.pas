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
  WorkView.FieldByName('�ն��豸ID').DefaultValue := '';
  WorkView.FieldByName('������ˮ��').DefaultValue := 0;
  WorkView.FieldByName('���׿���').DefaultValue := '';
  WorkView.FieldByName('��������').DefaultValue := 0;
  WorkView.FieldByName('����ʱ��').DefaultValue := 0;
  WorkView.FieldByName('���ױ��').DefaultValue := 0;
  WorkView.FieldByName('ͨ�Ű汾��').DefaultValue := 0;
  WorkView.FieldByName('����ͨ������ԭ��').DefaultValue := 0;
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
  WorkView.FieldByName('�ն��豸ID').Data.SetString(tmp);
  WorkView.FieldByName('������ˮ��').Data.SetInteger(Log^.serial_no);
  WorkView.FieldByName('���׿���').Data.SetInteger(Log^.card_id);
  tmp := Copy(Log^.tx_datetime,1,6);
  WorkView.FieldByName('��������').Data.SetString(tmp);
  tmp := Copy(Log^.tx_datetime,7,6);
  WorkView.FieldByName('����ʱ��').Data.SetString(tmp);
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
  TipMessage('��ʼ�ϴ���ˮ...');
  FSerialCnt := 0;
  retries := 0;
  while True do
  begin

    TipMessage('�ϴ���ˮ�У��벻Ҫ�Ͽ��ֳֻ�...');

    retval := MBLUpJSBRecord_SCJ(@TradeLog);
    if retval <> 0 then
    begin
      if MBLGetErrno_SCJ =  E_NO_SERIAL_EXISTS then
      begin
        Context.GetDialogSystem.ShowMessage(
          Format('�ϴ���ˮ��ɣ���[%d]��',[serial_cnt]));
        TipMessage('�ϴ���ˮ���');
        Exit;
      end
      else if MBLGetErrno_SCJ = E_CRC_ERROR then
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

initialization
  TUIStdClassFactory.Create('�ɼ���֤��ˮ',TfaqhacceptSmartTermList);

end.