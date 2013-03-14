unit UASmartTermSetParam;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid,smartterminterface, Buttons;

type
  TfaqhSmartTermSetParam = class(TfaqhSimpleQueryTemp)
    ibnSetWorkKey: TBitBtn;
    wvGetSysParam: TWorkView;
    wvrGetSysParam: TWVRequest;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure ibnSetWorkKeyClick(Sender: TObject);
  private
    FTermInfo : SMART_TERMINAL_T;
    function ConnectToTerm:Integer;
    function ValidateTermInfo:Integer;
    function GetWorkKey(var key:string):Integer;
    function SetTermWorkKey(key:string):Integer;
    function DoSetTermWorkKey:Integer;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmartTermSetParam: TfaqhSmartTermSetParam;

implementation

uses KsFrameworks;
     
{$R *.DFM}

procedure TfaqhSmartTermSetParam.Init;
begin
  inherited;
  ZeroMemory(@FTermInfo,SizeOf(FTermInfo));
  WorkView.FieldByName('设备名称').DefaultValue := '';
  WorkView.FieldByName('三九设备注册号').DefaultValue := '';
  WorkView.FieldByName('设备物理ID').DefaultValue := '';
  WorkView.FieldByName('机号').DefaultValue := 0;
  WorkView.FieldByName('机型代码').DefaultValue := '';
  WorkView.FieldByName('上级设备物理ID').DefaultValue := '';
  WorkView.FieldByName('设备状态').DefaultValue := 0;
  WorkView.FieldByName('设备物理型号').DefaultValue := 0;
  WorkView.FieldByName('所属子系统').DefaultValue := 0;
  WorkView.FieldByName('设备所在区域').DefaultValue := 0;
  WorkView.FieldByName('负责人员工号').DefaultValue := '';
  WorkView.Reset;

  wvGetSysParam.FieldByName('参数标识').DefaultValue := 0;
  wvGetSysParam.Reset;
end;

procedure TfaqhSmartTermSetParam.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

function TfaqhSmartTermSetParam.ConnectToTerm: Integer;
begin
  Result := -1;
  if MBLIsCOMOpen = 0 then
    Result := MBLReadTermInfo(@FTermInfo);
end;

function TfaqhSmartTermSetParam.GetWorkKey(var key: string): Integer;
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

function TfaqhSmartTermSetParam.SetTermWorkKey(key:string): Integer;
begin
  Result := MBLSetWorkKey2(PChar(key));
end;

function TfaqhSmartTermSetParam.ValidateTermInfo: Integer;
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
      if ds.FieldByName('sbank_pwd2').AsString = phyid then
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

function TfaqhSmartTermSetParam.DoSetTermWorkKey: Integer;
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
    Exit;
  // 读取工作密钥
  Result := GetWorkKey(key);
  if Result = -1 then
    Exit;
  if Length(key) <> 16 then
  begin
    Context.GetDialogSystem.ShowError('密钥长度错误');
    Exit;
  end;
  // 设置工作密钥
  Result := SetTermWorkKey(key);
  if Result = -1 then
    Exit;
end;

procedure TfaqhSmartTermSetParam.ibnSetWorkKeyClick(Sender: TObject);
begin
  inherited;
  if DoSetTermWorkKey = 0 then
    Context.GetDialogSystem.ShowMessage('设置设备工作密钥成功')
  else
    Context.GetDialogSystem.ShowError('设置设备工作密钥失败');
end;

initialization
  TUIStdClassFactory.Create('手持机参数设置',TfaqhSmartTermSetParam);

end.