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
  WorkView.FieldByName('�豸����ID').DefaultValue := '';
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
    Context.GetDialogSystem.ShowMessage('�´������ɹ�')
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
  // �����ֳֻ�
  //Result := ConnectToTerm(@term);
  //if Result <> 0 then
    //Exit;
  // ��ѯ�ڰ�����
  //Result := QueryBlackCard(@term);
  //if Result <> 0 then
    //Exit;
  // �����������ֳֻ�
  maxver := '';
  Result := DownLoadBlackCard(maxver);
  if Result <> 0 then
    Exit;
  Result := -1;
  // �����ֳֻ������汾
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
    showmessage('���������շѻ���ȡ��ţ�Ȼ���ٷ��䣡');
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmpDevice);
  Hex2Str(term^.phyid,SizeOf(term^.phyid),phyid);
  WorkView.FieldByName('�豸����ID').Data.SetString(phyid);
  try
    TipMessage('��ѯ�ڰ�����');
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger <> 0 then
      ShowMessage('û������');
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
  ds := TDataSet(WorkView.FieldByName('��ѯ�����').Data.AsObject);
  try
    ds.First;
    while not ds.Eof do
    begin
      cardid := ds.FieldByName('lvol0').AsInteger;
      flag := ds.FieldByName('lvol4').AsInteger;
      ver := ds.FieldByName('sserial0').AsString;
      if (cardid <= 0) or (Length(ver) <> 12) then
      begin
        Context.GetDialogSystem.ShowError('�������ݴ���');
        Exit;
      end;
      // ��ʧ
      TipMessage(Format('�´���������[%d]',[cardid]));
      if flag = 0 then
      begin
        if MBLDownBlackCard(cardid) <> 0 then
        begin
          Context.GetDialogSystem.ShowError('�´�����ʧ��');
          Exit;
        end
      end
      else if flag = 1 then // ���
      begin
        if MBLDownDelBlack(cardid) <> 0 then
        begin
          Context.GetDialogSystem.ShowError('�´�����ʧ��');
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
      Context.GetDialogSystem.ShowError('û�������´�');
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
      wvUpdateVersion.FieldByName('�豸����ID').Data.SetString(tmpDevice);
      wvUpdateVersion.FieldByName('�汾��').Data.SetString(maxver);
      wvrVersion.SendCommand;
      TipMessage(Format('�´��ڰ������汾[%s]�ɹ�',[maxver]));
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
    showmessage('���������շѻ���ȡ��ţ�Ȼ���ٲ�ѯ��');
    Exit;
  end;
  Hex2Str(TermInfo.phyid,SizeOf(TermInfo.phyid),tmpDevice);
  Hex2Str(TermInfo.termtype,SizeOf(TermInfo.termtype),ss);
  if ss='0115' then
  begin
    ShowMessage('�ù���ֻ�������շѻ����棡');
    exit;
  end;
  WorkView.FieldByName('�豸����ID').Data.SetString(tmpDevice);
  try
    TipMessage('��ѯ�ڰ�����');
    MainRequest.SendCommand;
    if WorkView.FieldByName('������').Data.AsInteger <> 0 then
      ShowMessage('û������');
  except
    on ex : Exception do
    begin
      Context.GetDialogSystem.ShowError(ex.Message);
    end;
  end;
end;

initialization
  TUIStdClassFactory.Create('�´��ڰ�����',TfaqhSmartTermDownBlkCard);

end.