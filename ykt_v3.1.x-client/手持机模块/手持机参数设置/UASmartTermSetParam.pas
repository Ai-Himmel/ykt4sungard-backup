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
  WorkView.FieldByName('�豸����').DefaultValue := '';
  WorkView.FieldByName('�����豸ע���').DefaultValue := '';
  WorkView.FieldByName('�豸����ID').DefaultValue := '';
  WorkView.FieldByName('����').DefaultValue := 0;
  WorkView.FieldByName('���ʹ���').DefaultValue := '';
  WorkView.FieldByName('�ϼ��豸����ID').DefaultValue := '';
  WorkView.FieldByName('�豸״̬').DefaultValue := 0;
  WorkView.FieldByName('�豸�����ͺ�').DefaultValue := 0;
  WorkView.FieldByName('������ϵͳ').DefaultValue := 0;
  WorkView.FieldByName('�豸��������').DefaultValue := 0;
  WorkView.FieldByName('������Ա����').DefaultValue := '';
  WorkView.Reset;

  wvGetSysParam.FieldByName('������ʶ').DefaultValue := 0;
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
  wvGetSysParam.FieldByName('������ʶ').Data.SetInteger(2006);
  try
    wvrGetSysParam.SendCommand;
    if wvGetSysParam.FieldByName('������').Data.AsInteger <> 0 then
      Exit;
    ds := TDataSet(wvGetSysParam.FieldByName('��ѯ�����').Data.AsObject);
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
  WorkView.FieldByName('�豸����ID').Data.SetString(phyid);
  //WorkView.FieldByName('�豸״̬').Data.SetInteger();
  try
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger <> 0 then
      Exit;
    ds := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
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
  // ��ȡ�豸��Ϣ
  Result := ConnectToTerm;
  if Result = -1 then
    Exit;
  // ����豸
  Result := ValidateTermInfo;
  if Result = -1 then
    Exit;
  // ��ȡ������Կ
  Result := GetWorkKey(key);
  if Result = -1 then
    Exit;
  if Length(key) <> 16 then
  begin
    Context.GetDialogSystem.ShowError('��Կ���ȴ���');
    Exit;
  end;
  // ���ù�����Կ
  Result := SetTermWorkKey(key);
  if Result = -1 then
    Exit;
end;

procedure TfaqhSmartTermSetParam.ibnSetWorkKeyClick(Sender: TObject);
begin
  inherited;
  if DoSetTermWorkKey = 0 then
    Context.GetDialogSystem.ShowMessage('�����豸������Կ�ɹ�')
  else
    Context.GetDialogSystem.ShowError('�����豸������Կʧ��');
end;

initialization
  TUIStdClassFactory.Create('�ֳֻ���������',TfaqhSmartTermSetParam);

end.