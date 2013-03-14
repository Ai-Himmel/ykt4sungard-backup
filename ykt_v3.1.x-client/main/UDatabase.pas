unit UDatabase;

{**********************************************
        Kingstar Delphi Library
   Copyright (C) Kingstar Corporation

   <Unit>UDatabase
   <What>提供服务器连接的基本信息
   <Written By> Huang YanLai (黄燕来)
   <History>
**********************************************}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  DBAIntf, KCDataAccess, KSFrameWorks, BDAImpEx;

type
  TdmDatabase = class(TDataModule, IKSDatabaseModule)
    Database: TKCDatabase;
    procedure DataModuleCreate(Sender: TObject);
    procedure DataModuleDestroy(Sender: TObject);
    procedure DatabaseBeforeReceive(Sender: TObject);
    procedure DatabaseAfterReceive(Sender: TObject);
    procedure DatabaseWait(Sender: TObject; var ContinueWait: Boolean);
  private
    { Private declarations }
    FProgressTitle: string;
    FReady: Boolean;
    //FProgressShowing: Boolean;
    FDelaySeconds: Integer;
    FDelayShowMessage: Boolean;
    procedure SetProgressTitle(const Value: string);
    procedure ShowTheProgress(Delayed: Boolean);
    procedure CloseTheProgress;
  public
    { Public declarations }
    procedure Start;
    procedure ShutDown;
    procedure ReadyForUse;
    procedure ShowWaiting(const Msg: string);
    procedure CloseWaiting;
    function GetDatabase: TObject;
    property ProgressTitle: string read FProgressTitle write SetProgressTitle;
    //property  ProgressShowing : Boolean read FProgressShowing ;
  end;

var
  dmDatabase: TdmDatabase;

implementation

uses KSClientConsts, LogFile, KCDataPack, ProgressShowing,
  UStartFlash;

{$R *.DFM}

{ TdmDatabase }

procedure TdmDatabase.ShutDown;
begin
  //  Database.close;
end;

procedure TdmDatabase.Start;
var
  ConfigSystem: IConfigSystem;
begin
  ProgressTitle := '';
  FReady := False;
  WriteLog('SizeOf(Cookie)=' + IntToStr(SizeOf(TSTCookie)), lcKSClient);
  WriteLog('Starting Server Connection...', lcKSClientStart);
  ConfigSystem := Context.GetConfigSystem;
  Database.GatewayIP := ConfigSystem.ReadString(ccServer, ckIP, cdIP);
  Database.GatewayPort := ConfigSystem.ReadInteger(ccServer, ckPort, cdPort);
  Database.GatewayIP2 := ConfigSystem.ReadString(ccServer, ckIP2, cdIP);
  Database.GatewayPort2 := ConfigSystem.ReadInteger(ccServer, ckPort2, cdPort);
  Database.GatewayEncode := ConfigSystem.ReadInteger(ccServer, ckEncode,
    cdEncode);
  Database.DestNo := ConfigSystem.ReadInteger(ccServer, ckDestNo, cdDestNo);
  Database.FuncNo := ConfigSystem.ReadInteger(ccServer, ckFuncNo, cdFuncNo);
  Database.TimeOut := ConfigSystem.ReadInteger(ccServer, ckTimeOut, cdTimeOut);
  Database.Priority := ConfigSystem.ReadInteger(ccServer, ckPrior, cdPrior);
  FDelayShowMessage := ConfigSystem.ReadBoolean(ccServer, ckDelayShowMessage,
    cdDelayShowMessage);
  FDelaySeconds := ConfigSystem.ReadInteger(ccServer, ckDelaySeconds,
    cdDelaySeconds);
  if FDelaySeconds < MinDelaySeconds then
    FDelaySeconds := MinDelaySeconds;
  InstallDefaultProgressShower;
  SetWaitCursor(crSQLWait);
  WriteLog(Format('Connecting To Server(%s:%d,Priority=%d,FuncNo=%d) ...',
    [Database.GatewayIP, Database.GatewayPort, Database.Priority,
      Database.FuncNo]),
    lcKSClientStart);
  try
    Database.Connected := True;
  except
    WriteException;
    WriteLog('Cannot Connect To Server!', lcKSClientStart);
    raise;
  end;
  WriteLog('Started Server Connection.', lcKSClientStart);
  //FProgressShowing := False;
end;

procedure TdmDatabase.DataModuleCreate(Sender: TObject);
begin
  WriteLog('dmDatabase Created.', lcConstruct_Destroy);
  DatabaseModule := Self;
end;

procedure TdmDatabase.DataModuleDestroy(Sender: TObject);
begin
  WriteLog('dmDatabase Destroying...', lcConstruct_Destroy);
  DatabaseModule := nil;
  dmDatabase := nil;
  WriteLog('dmDatabase Destroyed', lcConstruct_Destroy);
end;

procedure TdmDatabase.DatabaseBeforeReceive(Sender: TObject);
begin
  if MainThreadID <> GetCurrentThreadId then
    Exit;

  if FReady then
    ShowTheProgress(True);
end;

procedure TdmDatabase.DatabaseAfterReceive(Sender: TObject);
begin
  if MainThreadID <> GetCurrentThreadId then
    Exit;

  if FReady then
    CloseTheProgress;
end;

procedure TdmDatabase.DatabaseWait(Sender: TObject;
  var ContinueWait: Boolean);
begin
  if MainThreadID <> GetCurrentThreadId then
    Exit;

  if FReady then
  begin
    UpdateProgress;
    if IsProgressCanceled then
      ContinueWait := False;
  end
  else
    UpdateFlash;
end;

procedure TdmDatabase.SetProgressTitle(const Value: string);
begin
  FProgressTitle := Value;
  if FProgressTitle = '' then
    FProgressTitle := SWaitingOperation;
end;

procedure TdmDatabase.ReadyForUse;
begin
  Database.IsCallback := True;
  FReady := True;
end;

procedure TdmDatabase.CloseWaiting;
begin
  ProgressTitle := '';
  CloseTheProgress;
end;

procedure TdmDatabase.ShowWaiting(const Msg: string);
begin
  ProgressTitle := Msg;
  //ShowTheProgress(False);
  ShowTheProgress(FDelayShowMessage);
end;

function TdmDatabase.GetDatabase: TObject;
begin
  Result := Database;
end;

procedure TdmDatabase.ShowTheProgress(Delayed: Boolean);
var
  Title: string;
begin
  if GetNestProgressCount = 0 then
    Title := FProgressTitle
  else
    Title := '';
  if Delayed then
    ShowProgress(Title, True, SCancelPrompt, '', FDelaySeconds)
  else
    ShowProgress(Title, True, SCancelPrompt, '', 0);
end;

procedure TdmDatabase.CloseTheProgress;
begin
  CloseProgress;
end;

end.
