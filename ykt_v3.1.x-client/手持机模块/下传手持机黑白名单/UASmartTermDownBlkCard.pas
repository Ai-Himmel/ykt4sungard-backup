unit UASmartTermDownBlkCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVDBBinders, Db, 
  RzDBGrid,smartterminterface, ComCtrls, Buttons;

type
  TfaqhSmartTermDownBlkCard = class(TfaqhSimpleQueryTemp)
    Panel2: TPanel;
    sbInfo: TStatusBar;
    wvUpdateVersion: TWorkView;
    wvrVersion: TWVRequest;
    imgQueryBlack: TBitBtn;
    procedure WorkViewFieldsMonitors0ValueChanged(Sender: TWVFieldMonitor;
      Valid: Boolean);
    procedure btnQueryClick(Sender: TObject);
    procedure imgQueryBlackClick(Sender: TObject);
  private
    tmpDevice : string;
    function ConnectToTerm(Term:PSMART_TERMINAL_T):Integer;
    function QueryBlackCard(Term:PSMART_TERMINAL_T):Integer;
    function DownLoadBlackCard(var maxver:string):Integer;
    function UpdateTermBlackVersion(Term:PSMART_TERMINAL_T;maxver:string):Integer;
    function DoDownBlackCard:Integer;
    procedure TipMessage(msg:string);
    procedure ShowTermError;
    { Private declarations }
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhSmartTermDownBlkCard: TfaqhSmartTermDownBlkCard;

implementation

uses KsFrameworks;
     
{$R *.DFM}
function BytesToStr(mBytes: array of Byte):   string;
var
  I:Integer;
begin
  Result := '';
  for I := Low(mBytes)to High(mBytes)do
    Result := Result + Chr(mBytes[I])
end;

function TfaqhSmartTermDownBlkCard.ConnectToTerm(
  Term: PSMART_TERMINAL_T): Integer;
begin
  //
  Result := MBLReadTermInfo(Term);
end;

procedure TfaqhSmartTermDownBlkCard.Init;
begin
  inherited;
  WorkView.FieldByName('设备物理ID').DefaultValue := '';
  WorkView.Reset;
end;

procedure TfaqhSmartTermDownBlkCard.WorkViewFieldsMonitors0ValueChanged(
  Sender: TWVFieldMonitor; Valid: Boolean);
begin
  inherited;
  btnQuery.Enabled:=Valid;
end;

procedure TfaqhSmartTermDownBlkCard.btnQueryClick(Sender: TObject);
begin
  if DoDownBlackCard = 0 then
    Context.GetDialogSystem.ShowMessage('下传名单成功')
  else
    ShowTermError;
end;

function TfaqhSmartTermDownBlkCard.DoDownBlackCard: Integer;
var
  term : SMART_TERMINAL_T;
  maxver : string;
begin
  Result := -1;
  //ZeroMemory(@term,SizeOf(@term));
  // 连接手持机
  //Result := ConnectToTerm(@term);
  //if Result <> 0 then
    //Exit;
  // 查询黑白名单
  //Result := QueryBlackCard(@term);
  //if Result <> 0 then
    //Exit;
  // 下载名单到手持机
  maxver := '';
  Result := DownLoadBlackCard(maxver);
  if Result <> 0 then
    Exit;
  Result := -1;
  // 更新手持机名单版本
  //ShowMessage(maxver);
  if Length(maxver) <> 12 then
    Exit;
  Result := UpdateTermBlackVersion(@term,maxver);
  if Result <> 0 then
    Exit;
end;

function TfaqhSmartTermDownBlkCard.QueryBlackCard(
  Term: PSMART_TERMINAL_T): Integer;
var
  phyid :string;
  TermInfo : SMART_TERMINAL_T;
  tmpDevice : string;
begin
  ZeroMemory(@TermInfo,SizeOf(TermInfo));
  if MBLReadTermInfo(@TermInfo) <> 0 then
  begin
    showmessage('请先连接收费机读取编号，然后再分配！');
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmpDevice);
  Hex2Str(term^.phyid,SizeOf(term^.phyid),phyid);
  WorkView.FieldByName('设备物理ID').Data.SetString(phyid);
  try
    TipMessage('查询黑白名单');
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger <> 0 then
      ShowMessage('没有数据');
  except
    on ex : Exception do
    begin
      Context.GetDialogSystem.ShowError(ex.Message);
    end;
  end;
end;

function TfaqhSmartTermDownBlkCard.DownLoadBlackCard(
  var maxver:string): Integer;
var
  cardid,flag : Integer;
  ds : TDataSet;
  ver : string;
begin
  Result := -1;
  ds := TDataSet(WorkView.FieldByName('查询结果集').Data.AsObject);
  try
    ds.First;
    while not ds.Eof do
    begin
      cardid := ds.FieldByName('lvol0').AsInteger;
      flag := ds.FieldByName('lvol4').AsInteger;
      ver := ds.FieldByName('sserial0').AsString;
      if (cardid <= 0) or (Length(ver) <> 12) then
      begin
        Context.GetDialogSystem.ShowError('名单数据错误');
        Exit;
      end;
      // 挂失
      TipMessage(Format('下传名单卡号[%d]',[cardid]));
      if flag = 0 then
      begin
        if MBLDownBlackCard(cardid) <> 0 then
        begin
          Context.GetDialogSystem.ShowError('下传名单失败');
          Exit;
        end
      end
      else if flag = 1 then // 解挂
      begin
        if MBLDownDelBlack(cardid) <> 0 then
        begin
          Context.GetDialogSystem.ShowError('下传名单失败');
          Exit;
        end;
      end
      else
        Exit;
      if maxver < ver then
        maxver := ver;
      ds.Next;
    end;
    Result := 0;
  except
    on e : Exception do
      Context.GetDialogSystem.ShowError('没有名单下传');
  end;
end;

function TfaqhSmartTermDownBlkCard.UpdateTermBlackVersion(
  Term:PSMART_TERMINAL_T;maxver: string): Integer;
var
  phyid : string;
begin
  Result := MBLDownBlackVersion(PChar(maxver));
  if Result = 0 then
  begin
    try
      //Hex2Str(Term.phyid,SizeOf(Term.phyid),phyid);
      wvUpdateVersion.FieldByName('设备物理ID').Data.SetString(tmpDevice);
      wvUpdateVersion.FieldByName('版本号').Data.SetString(maxver);
      wvrVersion.SendCommand;
      TipMessage(Format('下传黑白名单版本[%s]成功',[maxver]));
    except
      on e : Exception do
      begin
        Context.GetDialogSystem.ShowError(e.Message);
        Result := -1;
      end;
    end;
  end;
end;

procedure TfaqhSmartTermDownBlkCard.TipMessage(msg: string);
begin
  //
  sbInfo.Panels[0].Text := msg;
  sbInfo.Update;
end;

procedure TfaqhSmartTermDownBlkCard.ShowTermError;
var
  msgbuf : array[0..512] of char;
begin
  if MBLGetErrno <> 0 then
  begin
    ZeroMemory(@msgbuf,SizeOf(msgbuf));
    MBLGetErrMsg(msgbuf);
    Context.GetDialogSystem.ShowError(msgbuf+'--');
  end;
end;

procedure TfaqhSmartTermDownBlkCard.imgQueryBlackClick(Sender: TObject);
var
  phyid :string;
  TermInfo : SMART_TERMINAL_T;
  ss:string;
begin
  ZeroMemory(@TermInfo,SizeOf(TermInfo));
  if MBLReadTermInfo(@TermInfo) <> 0 then
  begin
    showmessage('请先连接收费机读取编号，然后再查询！');
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmpDevice);
  Hex2Str(TermInfo.termtype,SizeOf(TermInfo.termtype),ss);
  if ss='0115' then
  begin
    ShowMessage('该功能只能用在收费机上面！');
    exit;
  end;
  WorkView.FieldByName('设备物理ID').Data.SetString(tmpDevice);
  try
    TipMessage('查询黑白名单');
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger <> 0 then
      ShowMessage('没有数据');
  except
    on ex : Exception do
    begin
      Context.GetDialogSystem.ShowError(ex.Message);
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('下传黑白名单',TfaqhSmartTermDownBlkCard);

end.