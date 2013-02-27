unit mobiletermdemo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls,IniFiles, ComCtrls, ExtCtrls,smartterminterface;
type
  {���嶨��}
  TfrmMain = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    cbbComPort: TComboBox;
    cbbComBand: TComboBox;
    btnCtrlCOM: TButton;
    btnExit: TButton;
    Panel1: TPanel;
    Label3: TLabel;
    lblPhyId: TLabel;
    lblVerDate: TLabel;
    btnReadTerm: TButton;
    edtTermNo: TEdit;
    btnSetTermNo: TButton;
    btnEmptyFlash: TButton;
    edtUserParam: TEdit;
    btnUpUserParam: TButton;
    lblTermType: TLabel;
    Panel2: TPanel;
    cbbWorkKeys: TComboBox;
    btnSetWorkKey: TButton;
    edtCommision: TEdit;
    btnSetComm: TButton;
    btnDelAllBlack: TButton;
    btnSetCommision: TButton;
    Panel3: TPanel;
    edtBlkCardId: TEdit;
    btnDownBlk: TButton;
    btnDelBlk: TButton;
    edtBlkVersion: TEdit;
    btnUpBlkVer: TButton;
    btnDownBlkVer: TButton;
    edtBlkExpire: TEdit;
    btnDownBlkExpire: TButton;
    btnUpBlkExpire: TButton;
    pnl1: TPanel;
    btnUpRecord: TButton;
    edtSerial: TEdit;
    btnEndUpSerial: TButton;
    btnViewLogDetail: TButton;
    btnUpHisSerial: TButton;
    edtSerialNo: TEdit;
    procedure btnCtrlCOMClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure btnReadTermClick(Sender: TObject);
    procedure btnSetTermNoClick(Sender: TObject);
    procedure btnSetWorkKeyClick(Sender: TObject);
    procedure btnEmptyFlashClick(Sender: TObject);
    procedure btnSetCommClick(Sender: TObject);
    procedure btnUpRecordClick(Sender: TObject);
    procedure btnUpUserParamClick(Sender: TObject);
    procedure btnDelAllBlackClick(Sender: TObject);
    procedure btnUpBlkVerClick(Sender: TObject);
    procedure btnDownBlkVerClick(Sender: TObject);
    procedure btnDownBlkClick(Sender: TObject);
    procedure btnDelBlkClick(Sender: TObject);
    procedure btnEndUpSerialClick(Sender: TObject);
    procedure btnViewLogDetailClick(Sender: TObject);
    procedure btnUpHisSerialClick(Sender: TObject);
    procedure btnUpBlkExpireClick(Sender: TObject);
    procedure btnDownBlkExpireClick(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    { Private declarations }
    FBasePath : string;
    FConfigFile : string;
    FCOMOpen : Boolean;
    FWorkKeys : TStrings;
    FSmartTerm :SMART_TERMINAL_T;
    FTradeLog : MBL_TRADE_LOG;
    procedure LoadConfig;
    procedure SaveConfig;
  public
    { Public declarations }
    constructor Create(AOwner:TComponent);override;
    destructor Destroy;override;
    function GetBasePath:string;
  end;
  
var
  frmMain: TfrmMain;

implementation

uses serialdetail;
  
{$R *.DFM}

procedure TfrmMain.btnCtrlCOMClick(Sender: TObject);
var
  port,band : Integer;
begin
  if not FCOMOpen then
  begin
    port := cbbComPort.ItemIndex + 1;
    band := StrToInt(cbbComBand.Text);
    if MBLOpenCom(port,band) = 0 then
    begin
      ShowMessage('�򿪴��ڳɹ�');
      FCOMOpen := True;
      btnCtrlCOM.Caption := '�رմ���';
    end
    else
    begin
      ShowMessage('�򿪴���ʧ��');
    end;
  end
  else
  begin
    MBLCloseCom;
    FCOMOpen := False;
    btnCtrlCOM.Caption := '�򿪴���';
  end;
end;

constructor TfrmMain.Create(AOwner: TComponent);
begin
  inherited;
  FWorkKeys := TStringList.Create;
  FBasePath := ExtractFilePath(Application.ExeName);
  FConfigFile := Format('%s\config.ini',[FBasePath]);
  LoadConfig;
  ZeroMemory(@FSmartTerm,SizeOf(FSmartTerm));
end;

destructor TfrmMain.Destroy;
begin
  SaveConfig;
  FreeAndNil(FWorkKeys);
  inherited;
end;

procedure TfrmMain.LoadConfig;
var
  config : TIniFile;
  tmpInt ,i,j: Integer;
  tmpkey : string;
begin
  config := TIniFile.Create(FConfigFile);
  try
    tmpInt := config.ReadInteger('COM','PORT',0);
    cbbComPort.ItemIndex := tmpInt;
    tmpInt := config.ReadInteger('COM','BAND',0);
    cbbComBand.ItemIndex := tmpInt;
    tmpkey := config.ReadString('KEY','WORKKEY','');
    j := 1;
    i := 1;
    while i <= Length(tmpkey) do
    begin
      if tmpkey[i] = ',' then
      begin
        FWorkKeys.Add(Trim(Copy(tmpkey,j,i-j)));
        Inc(i);
        j := i;
      end;
      Inc(i);
    end;
    if j < i then
    begin
      FWorkKeys.Add(Trim(Copy(tmpkey,j,i - j)));
    end;
    cbbWorkKeys.Items.BeginUpdate;
    cbbWorkKeys.Items.Clear;
    try
      cbbWorkKeys.Items.Assign(FWorkKeys);
    finally
      cbbWorkKeys.Items.EndUpdate;
    end;
  except
    // ignore all
  end;
  FreeAndNil(config);
end;

procedure TfrmMain.SaveConfig;
var
  config : TIniFile;
begin
  config := TIniFile.Create(FConfigFile);
  try
    config.WriteInteger('COM','PORT',cbbComPort.ItemIndex);
    config.WriteInteger('COM','BAND',cbbComBand.ItemIndex);
  except
    // ignore all
  end;
  FreeAndNil(config);
end;

procedure TfrmMain.btnExitClick(Sender: TObject);
begin
  if FCOMOpen then
  begin
    MBLCloseCom;
  end;
  Close;
end;

procedure TfrmMain.btnReadTermClick(Sender: TObject);
var
  phystr:string;
begin
  if MBLReadTermInfo(@FSmartTerm) = 0 then
  begin
    edtTermNo.Text := IntToStr(FSmartTerm.termno);
    SetLength(phystr,10);
    Hex2Str(FSmartTerm.phyid,4,phystr);
    lblPhyId.Caption := '����ID��' + phystr;
    lblVerDate.Caption := '����汾��' + FSmartTerm.verdate;
    Hex2Str(FSmartTerm.termtype,2,phystr);
    lblTermType.Caption := '���ͣ�' + phystr;
  end
  else
  begin
    MBLShowErrMsg;
  end;
end;

procedure TfrmMain.btnSetTermNoClick(Sender: TObject);
begin
  if Trim(edtTermNo.Text) = '' then
    Exit;
  if MBLWriteJh(StrToInt(edtTermNo.Text)) = 0 then
  begin
    ShowMessage('���û��ųɹ���');
  end
  else
  begin
    MBLShowErrMsg;
  end;
end;

procedure TfrmMain.btnSetWorkKeyClick(Sender: TObject);
var
  Key : string;
begin
  if MessageDlg('�Ƿ�Ҫʹ�øù�����Կ?',mtConfirmation,mbOKCancel,0) = mrCancel	 then
  begin
    Exit;
  end;
  key := cbbWorkKeys.Text;
  if Length(Key) <> 16 then
  begin
    ShowMessage('������Կ���Ȳ���ȷ��');
    Exit;
  end;
  if MBLSetWorkKey2(PChar(key)) = 0 then
  begin
    ShowMessage('������Կ�ɹ���');
  end
  else
    MBLShowErrMsg;
end;

procedure TfrmMain.btnEmptyFlashClick(Sender: TObject);
begin
  if MessageDlg('�Ƿ�Ҫ���ֳֻ���ʼ��Ϊ����״̬?'
    ,mtConfirmation,mbOKCancel,0) = mrCancel	 then
  begin
    Exit;
  end;
  if MBLEmptyFlash = 0 then
  begin
    ShowMessage('��ʼ���ɹ�');
    if MBLReadTermInfo(@FSmartTerm) = 0 then
      Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnSetCommClick(Sender: TObject);
var
  comm : string;
begin
  comm := Trim(edtCommision.Text);
  if Length(comm) <> 8 then
  begin
    ShowMessage('����ID�ų��Ȳ���ȷ��');
    Exit;
  end;

  if MessageDlg('�Ƿ�����Ϊ����ID��?'
    ,mtConfirmation,mbOKCancel,0) = mrCancel	 then
  begin
    Exit;
  end;

  if MBLWriteId2(PChar(comm)) = 0 then
  begin
    ShowMessage('��������ID�ųɹ�');
    if MBLSetCommision2(PChar(comm)) = 0 then
    begin
      ShowMessage('������Ȩ�ųɹ�');
      if MBLReadTermInfo(@FSmartTerm) = 0 then
        Exit;
    end;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnUpRecordClick(Sender: TObject);
begin
  ZeroMemory(@FTradeLog,SizeOf(MBL_TRADE_LOG));
  if MBLUpRecordOne(@FTradeLog) = 0 then
  begin
    edtSerial.Text := Format('��ˮ��:[%d]���׿���[%d]���[%d]��������[%s]',
      [FTradeLog.serial_no,FTradeLog.card_id,FTradeLog.tx_trade_amount
      ,FTradeLog.tx_datetime]);
    //lblSerialNo.Caption := Format('%d',[record_log.serial_no]);
    Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnEndUpSerialClick(Sender: TObject);
begin
  if MessageDlg('�Ƿ�Ҫ�����ϴ���ˮ?'
    ,mtConfirmation,mbOKCancel,0) = mrCancel	 then
  begin
    Exit;
  end;
  if MBLEndUpRecordOne(FTradeLog.serial_no) = 0 then
  begin
    ShowMessage('�����ϴ���ˮ�ɹ���');
    //lblSerialNo.Caption := Format('%d',[record_log.serial_no]);
    Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnUpUserParamClick(Sender: TObject);
var
  paramstr: string;
  param : array[0..32] of Byte;
begin

  ZeroMemory(@param,SizeOf(param));
  if MBLUserUpParam(@param) = 0 then
  begin
    SetLength(paramstr,33 * 2 + 1);
    Hex2Str(param,SizeOf(param),paramstr);
    edtUserParam.Text := paramstr;
    ShowMessage(Copy(paramstr,9 * 2,4));
  end;
end;

procedure TfrmMain.btnDelAllBlackClick(Sender: TObject);
begin
  if MessageDlg('�Ƿ�Ҫɾ�����к�����?'
    ,mtConfirmation,mbOKCancel,0) = mrCancel	 then
  begin
    Exit;
  end;
  if MBLDownDelBAll = 0 then
    ShowMessage('ɾ���ɹ�')
  else
    MBLShowErrMsg;
end;

procedure TfrmMain.btnUpBlkVerClick(Sender: TObject);
var
  version : array[0..11] of Char;
begin
  ZeroMemory(@version,SizeOf(version));
  if MBLUpBlackVersion(version) = 0 then
    edtBlkVersion.Text := version
  else
    MBLShowErrMsg;
end;

procedure TfrmMain.btnDownBlkVerClick(Sender: TObject);
var
  version : string;
begin
  version := Trim(edtBlkVersion.Text);
  if Length(version) <> 12 then
  begin
    ShowMessage('�������汾���Ȳ���12���ֽڣ�');
    Exit;
  end;
  if MBLDownBlackVersion(PChar(version)) = 0 then
    ShowMessage('�´��������汾�ɹ���')
  else
    MBLShowErrMsg;

end;

procedure TfrmMain.btnDownBlkClick(Sender: TObject);
var
  cardid : Integer;
begin
  if Length(Trim(edtBlkCardId.Text)) = 0 then
  begin
    ShowMessage('���Ŵ���');
  end;
  try
    cardid := StrToInt(Trim(edtBlkCardId.Text));
  except
    ShowMessage('���Ŵ���');
    Exit;
  end;
  if MBLDownBlackCard(cardid) = 0 then
    ShowMessage('�´��������ɹ���')
  else
    MBLShowErrMsg;
end;

procedure TfrmMain.btnDelBlkClick(Sender: TObject);
var
  cardid : Integer;
begin
  if Length(Trim(edtBlkCardId.Text)) = 0 then
  begin
    ShowMessage('���Ŵ���');
  end;
  try
    cardid := StrToInt(Trim(edtBlkCardId.Text));
  except
    ShowMessage('���Ŵ���');
    Exit;
  end;
  if MBLDownDelBlack(cardid) = 0 then
    ShowMessage('ɾ���������ɹ���')
  else
    MBLShowErrMsg;

end;

procedure TfrmMain.btnViewLogDetailClick(Sender: TObject);
begin
  if FTradeLog.card_id = 0 then
  begin
    ShowMessage('�����ϴ�һ����ˮ');
    Exit;
  end;
  if frmDetail.ShowDetail(@FTradeLog) = mrYes then
  begin
    btnEndUpSerialClick(btnViewLogDetail);
  end;
end;

procedure TfrmMain.btnUpHisSerialClick(Sender: TObject);
var
  serial_no : integer;
begin
  try
    serial_no := StrToInt(edtSerialNo.Text);
  except
    ShowMessage('��������ȷ����ˮ��');
    Exit;
  end;
  ZeroMemory(@FTradeLog,SizeOf(FTradeLog));
  if MBLUpHisBySerial(serial_no,@FTradeLog) = 0 then
  begin
    edtSerial.Text := Format('��ˮ��:[%d]���׿���[%d]���[%d]',
      [FTradeLog.serial_no,FTradeLog.card_id,FTradeLog.tx_trade_amount]);
    //lblSerialNo.Caption := Format('%d',[record_log.serial_no]);
    Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnUpBlkExpireClick(Sender: TObject);
var
  expire : array[0..12] of Char;
begin
  edtBlkExpire.Text := '';
  ZeroMemory(@expire,SizeOf(expire));
  if MBLUpBlackExpire(PChar(@expire)) = 0 then
  begin
    edtBlkExpire.Text := expire;
    Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.btnDownBlkExpireClick(Sender: TObject);
var
  datestr : string;
begin
  datestr := Trim(edtBlkExpire.Text);
  if Length(datestr) <> 12 then
  begin
    ShowMessage('�´������ڸ�ʽ����ȷ��');
    Exit;
  end;
  if MBLDownBlackExpire(PChar(datestr)) = 0 then
  begin
    ShowMessage('�´���Ч�ڳɹ���');
    Exit;
  end;
  MBLShowErrMsg;
end;

procedure TfrmMain.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Shift <> [] then
  begin
    Exit;
  end;
  if Key = VK_ESCAPE then
  begin
    Close;
  end;
end;

function TfrmMain.GetBasePath: string;
begin
  Result := FBasePath;
end;

end.

