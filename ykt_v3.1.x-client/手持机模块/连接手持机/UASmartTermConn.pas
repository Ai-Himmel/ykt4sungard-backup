unit UASmartTermConn;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid, RzLabel,smartterminterface,
  RzPanel, Buttons;

const
  E_NO_SERIAL_EXISTS = 10;
  
type
  TfaqhSmartTermConn = class(TfaqhSimpleQueryTemp)
    grp1: TGroupBox;
    lbl1: TLabel;
    lbl2: TLabel;
    cbbComPort: TComboBox;
    cbbComBand: TComboBox;
    RzGroupBox1: TRzGroupBox;
    RzLabel1: TRzLabel;
    RzLabel2: TRzLabel;
    RzLabel3: TRzLabel;
    RzLabel4: TRzLabel;
    RzLabel5: TRzLabel;
    lblPhyId: TRzLabel;
    lblProVer: TRzLabel;
    lblNo: TRzLabel;
    lblBlkVer: TRzLabel;
    RzLabel6: TRzLabel;
    lblBlkExpire: TRzLabel;
    btnCtrlCOM: TBitBtn;
    btnReadInfo: TBitBtn;
    btnSetWorkKey: TBitBtn;
    wvrGetSysParam: TWVRequest;
    wvGetSysParam: TWorkView;
    rgType: TRadioGroup;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnCtrlCOMClick(Sender: TObject);
    procedure btnReadInfoClick(Sender: TObject);
    procedure btnSetWorkKeyClick(Sender: TObject);
  private
    { Private declarations }
    FTermInfo : SMART_TERMINAL_T;
    function ConnectToTerm:Integer;
    function ValidateTermInfo:Integer;
    function GetWorkKey(var key:string):Integer;
    function SetTermWorkKey(key:string):Integer;
    function DoSetTermWorkKey:Integer;
    procedure ShowTermError;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmartTermConn: TfaqhSmartTermConn;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhSmartTermConn.Init;
begin
  inherited;
  ZeroMemory(@FTermInfo,SizeOf(FTermInfo));
  if MBLIsCOMOpen = -1 then
    btnCtrlCOM.Caption := '打开串口'
  else
    btnCtrlCOM.Caption := '关闭串口';
  cbbcomport.ItemIndex:=0;
  cbbcomband.ItemIndex:=1;
end;

procedure TfaqhSmartTermConn.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSmartTermConn.btnCtrlCOMClick(Sender: TObject);
var
  port,band : Integer;
begin
  if (rgtype.ItemIndex=0)then
  begin
    if MBLIsCOMOpen = -1 then
    begin
      port := cbbComPort.ItemIndex + 1;
      band := StrToInt(cbbComBand.Text);
      if MBLOpenCom(port,band) = 0 then
      begin
        Context.GetDialogSystem.ShowMessage('打开串口成功');
        btnCtrlCOM.Caption := '关闭串口';
      end
      else
      begin
        Context.GetDialogSystem.ShowMessage('打开串口失败');
      end;
    end
    else
    begin
      MBLCloseCom;
      btnCtrlCOM.Caption := '打开串口';
    end;
  end
  else
  begin
    if MBLIsCOMOpen_SCJ = -1 then
    begin
      port := cbbComPort.ItemIndex + 1;
      band := StrToInt(cbbComBand.Text);
      if MBLOpenCom_SCJ(port,band) = 0 then
      begin
        Context.GetDialogSystem.ShowMessage('打开串口成功');
        btnCtrlCOM.Caption := '关闭串口';
      end
      else
      begin
        Context.GetDialogSystem.ShowMessage('打开串口失败');
      end;
    end
    else
    begin
      MBLCloseCom_SCJ;
      btnCtrlCOM.Caption := '打开串口';
    end;
  end;
end;

procedure TfaqhSmartTermConn.ShowTermError;
var
  msgbuf : array[0..512] of char;
begin
  //
  ZeroMemory(@msgbuf,SizeOf(msgbuf));
  if (rgType.ItemIndex=0) then
    MBLGetErrMsg(PChar(@msgbuf))
  else
    MBLGetErrMsg_SCJ(PChar(@msgbuf));
  Context.GetDialogSystem.ShowError(msgbuf);
end;

procedure TfaqhSmartTermConn.btnReadInfoClick(Sender: TObject);
var
  tmp : string;
  TermInfo : SMART_TERMINAL_T;
  st:Integer;
begin
  ZeroMemory(@TermInfo,SizeOf(TermInfo));
  if (rgType.ItemIndex=0) then
  begin
    st:= MBLReadTermInfo(@TermInfo);
  end
  else
  begin
    st:=MBLReadTermInfo_SCJ(@TermInfo);
  end;
  if st <> 0 then
  begin
    ShowTermError;
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmp);
  lblPhyId.Caption := tmp;
  lblProVer.Caption := TermInfo.verDate;
  lblNo.Caption := IntToStr(TermInfo.termno);
  SetLength(tmp,12);
  {
  if MBLUpBlackVersion(PChar(tmp)) <> 0 then
  begin
    ShowTermError;
    Exit;
  end;
  lblBlkVer.Caption := tmp;
  if MBLUpBlackExpire(PChar(tmp)) <> 0 then
  begin
    ShowTermError;
    Exit;
  end;
  lblBlkExpire.Caption := tmp;
  }
end;

function TfaqhSmartTermConn.ConnectToTerm: Integer;
begin
  Result := -1;
  if (rgType.ItemIndex=0)then
  begin
    if MBLIsCOMOpen = 0 then
      Result := MBLReadTermInfo(@FTermInfo);
  end
  else
  begin
    if MBLIsCOMOpen_SCJ = 0 then
      Result := MBLReadTermInfo_SCJ(@FTermInfo);
  end;
end;

function TfaqhSmartTermConn.DoSetTermWorkKey: Integer;
var
  key : string;
begin
  // 读取设备信息
  Result := ConnectToTerm;
  if Result = -1 then
    Exit;
  // 检查设备
  Result := ValidateTermInfo;
  if Result = -1 then
  begin
    Context.GetDialogSystem.ShowMessage('该手持机没有注册，请现在设备里面注册然后使用!');
    Exit;

  end;
  // 读取工作密钥
  //ShowMessage(key);
  Result := GetWorkKey(key);
  if Result = -1 then
    Exit;
  if Length(key) <> 16 then
  begin
    Context.GetDialogSystem.ShowError('密钥长度错误!');
    Exit;
  end;
  // 设置工作密钥
  Result := SetTermWorkKey(key);
  if Result = -1 then
    Exit;
end;

function TfaqhSmartTermConn.GetWorkKey(var key: string): Integer;
var
  ds : TDataSet;
begin
  Result := -1;
  wvGetSysParam.FieldByName('参数标识').Data.SetInteger(2006);
  try
    wvrGetSysParam.SendCommand;
    if wvGetSysParam.FieldByName('返回码').Data.AsInteger <> 0 then
      Exit;
    ds := TDataSet(wvGetSysParam.FieldByName('查询结果集').Data.AsObject);
    if not ds.Eof then
    begin
      key := ds.FieldByName('scard0').AsString;
      //ShowMessage(key);
      Result := 0;
    end;
  except
    on  ex : Exception do
    begin
      Context.GetDialogSystem.ShowError(ex.Message);
    end;
  end;
end;

function TfaqhSmartTermConn.SetTermWorkKey(key: string): Integer;
begin
  if (rgType.ItemIndex=0)then
    Result := MBLSetWorkKey2(PChar(key))
  else
    Result := MBLSetWorkKey2_SCJ(PChar(key));
end;

function TfaqhSmartTermConn.ValidateTermInfo: Integer;
var
  phyid : string;
  ds : TDataSet;
begin
  Result := -1;
  Hex2Str(FTermInfo.phyid,SizeOf(FTermInfo.phyid),phyid);
  WorkView.FieldByName('设备物理ID').Data.SetString(phyid);
  //WorkView.FieldByName('设备状态').Data.SetInteger();
  try
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger <> 0 then
      Exit;
    ds := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
    while not ds.Eof do
    begin
      if ds.FieldByName('lvol4').AsInteger = 5 then
      begin
        ds.Next;
        Continue;
      end;
      if ds.FieldByName('sphone3').AsString = phyid then
      begin
        Result := 0;
        Exit;
      end;
      ds.Next;
    end;
  except
    on  ex : Exception do
    begin
      Context.GetDialogSystem.ShowError(ex.Message);
    end;
  end;
end;

procedure TfaqhSmartTermConn.btnSetWorkKeyClick(Sender: TObject);
begin
  inherited;
  if DoSetTermWorkKey = 0 then
    Context.GetDialogSystem.ShowMessage('设置设备工作密钥成功')
  else
    Context.GetDialogSystem.ShowError('设置设备工作密钥失败');
end;

initialization
  TUIStdClassFactory.Create('连接手持机',TfaqhSmartTermConn);

end.