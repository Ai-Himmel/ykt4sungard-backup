unit ULiquidateStatusList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls,Checklst, KCDataAccess, Db, WVCmdTypeInfo, WVCmdProc,
  KCWVProcBinds, Menus;

type

  TfaLiquidateList = class;

  TGetLiquidateStatusThread = class(TThread)
  private
    { private declarations }
    FScrollBarWidth: Integer;
    FMarket: string;
    FSeatNo: string;
    FFunctionNo: Integer;
    FCurrencyType: string;
    FSysDate: string;
    FSerialNo: Integer;
    FOtherParam: string;
    FfaLiquidateList: TfaLiquidateList;
    FMarketSeatNoItems: TStringList;
    FProcessCount:Integer;

    FMessage: string;
    FPause: Boolean;
    procedure UpdateListBox;
    procedure StartLiquidate(OperationType,
        FunctionNo: Integer; const Market, SeatNo, CurrentDate,CurrencyType,
        OtherParams: string; var Status: string; var count:Integer);
    procedure GetLiquidateStatus;
    procedure ThreadDone(Sender: TObject);
  protected
    { protected declarations }
    procedure Execute;override;
  public
    { Public declarations }
    constructor Create(FunctionNo: Integer;SysDate,CurrencyType,OtherParam: string;SerialNo: Integer;
                       faLiquidateList: TfaLiquidateList;
                       MarketSeatNoItems: TStringList=nil);
    destructor Destroy; override;
    procedure GetSerialNo(FunctionNo: Integer; const Market, SeatNo, CurrentDate: string;
                            var SerialNo: Integer);
    procedure SendCommand(FunctionNo: Integer; const Market, SeatNo, CurrentDate: string;
                            var Status: string; var SerialNo,RecordNo: Integer);
    procedure GetInfoFromDataset(Dataset: TDataset; var Status: string; var SerialNo,RecordNo: Integer);
    procedure Pause;
  published
    property Market: string read FMarket write FMarket;
    property SeatNo: string read FSeatNo write FSeatNo;
    property ScrollBarWidth: Integer read FScrollBarWidth write FScrollBarWidth;
  end;


  TfaLiquidateList = class(TFrame)
    GroupBox: TGroupBox;
    ListBox: TListBox;
    PopupMenu: TPopupMenu;
    nClear: TMenuItem;
    procedure ListBoxMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure nClearClick(Sender: TObject);
  private
    { Private declarations }
    FDisableStop: TNotifyEvent;
    FEnableStop: TNotifyEvent;
    FSerialNo: Integer;
    FSysDate: string;
    FFunctionNo: Integer;
    FCurrencyType: string;
    FStoped: Boolean;
  protected
    { protected declarations }
  public
    { Public declarations }
    GetLiquidateStatusThread: TGetLiquidateStatusThread;
    constructor Create(AOwner: TComponent);override;
    destructor Destroy;override;
    procedure Start(FunctionNo: Integer;SysDate,CurrencyType: string;
                       MarketSeatNoItems: TStringList=nil;OtherParam: string = '');
    procedure GetMarketSeatNo(var Market,SeatNo: string);
    procedure DoDisableStop;
    procedure DoEnableStop;
    procedure Kill;
    procedure Stop;
    procedure Pause;
  published
    property EnableStop: TNotifyEvent read FEnableStop write FEnableStop;
    property DisableStop: TNotifyEvent read FDisableStop write FDisableStop;
    property SerialNo: Integer read FSerialNo write FSerialNo;
    property SysDate: string read FSysDate write FSysDate;
    property CurrencyType: string read FCurrencyType write FCurrencyType;
    property Stoped: Boolean read FStoped write FStoped;
    property FunctionNo: Integer read FFunctionNo write FFunctionNo;
  end;

implementation
uses KSFrameWorks,KSDataDictionary,KSClientConsts, KSFrameWorkUtils,
     SafeCode, WVCommands, BDAImpEx, DBAIntf, LogFile;
{$R *.DFM}

{ TGetLiquidateStatusThread }
constructor TGetLiquidateStatusThread.Create(FunctionNo: Integer;SysDate,CurrencyType,OtherParam: string;SerialNo: Integer;
                       faLiquidateList: TfaLiquidateList;
                       MarketSeatNoItems: TStringList=nil);
begin
  inherited Create(True);
  FScrollBarWidth := 0;
  FOtherParam := OtherParam;
  OnTerminate := ThreadDone;
  FreeOnTerminate := True;
  FMarket := '';
  FSeatNo := '';
  FFunctionNo := FunctionNo;
  FSysDate := SysDate;
  FCurrencyType := CurrencyType;
  FSerialNo := SerialNo;
  FPause := False;
  FProcessCount:=0;
  FfaLiquidateList := faLiquidateList;
  if MarketSeatNoItems <> nil then
  begin
    FMarketSeatNoItems := TStringList.Create;
    FMarketSeatNoItems.Assign(MarketSeatNoItems);
  end;
  Suspended := False;
end;

destructor TGetLiquidateStatusThread.Destroy;
begin
  FfaLiquidateList := nil;
  if FMarketSeatNoItems <> nil then
    FMarketSeatNoItems.Free;
  inherited;
end;

procedure TGetLiquidateStatusThread.Execute;
begin
  GetLiquidateStatus;
end;

procedure TGetLiquidateStatusThread.GetInfoFromDataset(Dataset: TDataset;
  var Status: string; var SerialNo,RecordNo: Integer);
begin
  Assert(DataSet<>nil);
  Dataset.First;
  while not Dataset.Eof do
  begin
    RecordNo:=RecordNo+1;
    Status := Dataset.fieldByName('sstatus0').AsString;
    FMessage := Dataset.fieldByName('vsmess').AsString;
    SerialNo := Dataset.fieldByName('lserial0').AsInteger;
    SynChronize(UpdateListBox);
    if Status <> '4' then
      break;
    Dataset.Next;
  end;
end;

procedure TGetLiquidateStatusThread.GetLiquidateStatus;
var
  i,recordno: Integer;
  Status: string;
begin
  if FMarketSeatNoItems = nil then
  begin
    //查询清算信息
    FMessage := '正在启动...';
    SynChronize(UpdateListBox);

    //启动清算程序
    try
      FfaLiquidateList.DoDisableStop;
      StartLiquidate(StartUp,FFunctionNo,'','',FSysDate,FCurrencyType,FOtherParam,Status,FProcessCount);
    except
      on E: Exception do
      Begin
        FMessage := E.Message;
        SynChronize(UpdateListBox);
        Exit;                             
      end;
    end;

//    FMessage := Inttostr(FProcessCount);
//    SynChronize(UpdateListBox);
    if FProcessCount<1 then FProcessCount:=1;
//    FMessage := Inttostr(FProcessCount);
//    SynChronize(UpdateListBox);

    FfaLiquidateList.DoEnableStop;
    //查询清算信息

    FSerialNo := FSerialNo + 1;
    recordno:=0;

    while not Terminated do
    begin

      try
        Status := '4';
        if recordno>0 then FSerialNo := FSerialNo + 1;
        recordno:=0;
        SendCommand(FFunctionNo, '', '', FSysDate, Status, FSerialNo,recordno);

        if Status <> '4' then
        begin
//          showmessage(Status);
//          FMessage := Status+inttostr(FSerialNo);
//          SynChronize(UpdateListBox);
//          Break;
          FProcessCount:=FProcessCount-1;
        end;
        if FProcessCount=0 then Break;
      except
        on E: Exception do
        Begin
          FMessage := E.Message;
          SynChronize(UpdateListBox);
          Break;
        end;
      end;

      Sleep(1000);
    end;

  end
  else
    for i := 0 to FMarketSeatNoItems.Count - 1 do
    begin

      if FPause then
        Exit;

      FMarket := Copy(FMarketSeatNoItems[i],1,Pos('-',FMarketSeatNoItems[i]) - 1);
      FSeatNo := Copy(FMarketSeatNoItems[i],Pos('-',FMarketSeatNoItems[i]) + 1, Length(FMarketSeatNoItems[i]));

      //查询清算信息
      FMessage := GetIdObjectName(deMarket,Market) + '-' + SeatNo + '  正在启动...';
      SynChronize(UpdateListBox);
      //启动清算程序
      try
        FfaLiquidateList.DoDisableStop;
        StartLiquidate(StartUp,FFunctionNo,Market,SeatNo,FSysDate,FCurrencyType,FOtherParam,Status,FProcessCount);
      except
        on E: Exception do
        Begin
          FMessage := E.Message;
          SynChronize(UpdateListBox);
          Exit;
        end;
      end;

      if FProcessCount<1 then FProcessCount:=1;

      FfaLiquidateList.DoEnableStop;

      FSerialNo := FSerialNo + 1;
      recordno:=0;

      while not Terminated do
      begin

        try
          FMessage := '';
          Status := '4';
          if recordno>0 then FSerialNo := FSerialNo + 1;
          recordno:=0;
          SendCommand(FFunctionNo, Market,SeatNo, FSysDate, Status, FSerialNo,recordno);
          
          if Status <> '4' then
          begin
  //          showmessage(Status);
  //          FMessage := Status+inttostr(FSerialNo);
  //          SynChronize(UpdateListBox);
  //          Break;
            FProcessCount:=FProcessCount-1;
          end;
          if FProcessCount=0 then Break;
        except
          on E: Exception do
          Begin
            FMessage := E.Message;
            SynChronize(UpdateListBox);
            Break;
          end;
        end;

        Sleep(1000);
      end;
      
      if Terminated then
        Exit;
    end;
end;

procedure TGetLiquidateStatusThread.GetSerialNo(FunctionNo: Integer;
  const Market, SeatNo, CurrentDate: string; var SerialNo: Integer);
var
  Dataset: TKCDataset;
  Param: THRPCParam;
begin
  CheckObject(Context,'Invalid Context');

  Dataset := TKCDataset.Create(nil);
  Dataset.DataBase := TKCDataBase(Context.GetSystemObject(SODatabase));
  Dataset.RequestType := 403002;

  //职工所属营业部代码
  Param := Dataset.Params.Add;
  Param.Name := 'sbranch_code0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDepartment.ID;

  //命令种类
  Param := Dataset.Params.Add;
  Param.Name := 'lcert_code';
  Param.DataType := ftInteger;
  Param.AsInteger := FunctionNo;

  //市场代码
  Param := Dataset.Params.Add;
  Param.Name := 'smarket_code';
  Param.DataType := ftChar;
  Param.AsString := Market;

  //席位代码
  Param := Dataset.Params.Add;
  Param.Name := 'sstock_code2';
  Param.DataType := ftChar;
  Param.AsString := SeatNo;

  //进程号
  Param := Dataset.Params.Add;
  Param.Name := 'lvol0';
  Param.DataType := ftInteger;
  Param.AsInteger := 0;

  //日期
  Param := Dataset.Params.Add;
  Param.Name := 'sdate0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDate;

  //流水号
  Param := Dataset.Params.Add;
  Param.Name := 'lserial0';
  Param.DataType := ftInteger;
  Param.AsInteger := -1;

  //柜员代码
  Param := Dataset.Params.Add;
  Param.Name := 'semp';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svOperatorNoName).AsString;

  //网卡号
  Param := Dataset.Params.Add;
  Param.Name := 'sstation0';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svMACAddressName).AsString;
  try
    WriteLog('Before Command Process,ID=获取流水号',lcKSClient);
    Dataset.Open;
    
    if Dataset.ReturnCode <> 0 then
      raise EDBNoDataset.CreateFmt(Dataset.Fields[1].AsString,[]);

    if not Dataset.Eof then
       SerialNo := Dataset.fieldByName('lserial0').AsInteger
    else
       SerialNo := 0;
    Dataset.Close;
    WriteLog('After Command Process,ID=获取流水号',lcKSClient);
    FreeAndNil(Dataset);
  except
    on E: EDBNoDataset do
      raise EDBNoDataset.CreateFmt(E.Message,[]);
  end;
end;

procedure TGetLiquidateStatusThread.Pause;
begin
  FPause := True;
end;

procedure TGetLiquidateStatusThread.SendCommand(FunctionNo: Integer;
  const Market, SeatNo, CurrentDate: string; var Status: string; var SerialNo,RecordNo: Integer);
var
  Dataset: TKCDataset;
  Param: THRPCParam;
begin
  CheckObject(Context,'Invalid Context');

  Dataset := TKCDataset.Create(nil);
  Dataset.DataBase := TKCDataBase(Context.GetSystemObject(SODatabase));
  Dataset.RequestType := 403002;

  //职工所属营业部代码
  Param := Dataset.Params.Add;
  Param.Name := 'sbranch_code0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDepartment.ID;

  //命令种类
  Param := Dataset.Params.Add;
  Param.Name := 'lcert_code';
  Param.DataType := ftInteger;
  Param.AsInteger := FunctionNo;

  //市场代码
  Param := Dataset.Params.Add;
  Param.Name := 'smarket_code';
  Param.DataType := ftChar;
  Param.AsString := Market;

  //席位代码
  Param := Dataset.Params.Add;
  Param.Name := 'sstock_code2';
  Param.DataType := ftChar;
  Param.AsString := SeatNo;

  //进程号
  Param := Dataset.Params.Add;
  Param.Name := 'lvol0';
  Param.DataType := ftInteger;
  Param.AsInteger := 0;

  //日期
  Param := Dataset.Params.Add;
  Param.Name := 'sdate0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDate;

  //流水号
  Param := Dataset.Params.Add;
  Param.Name := 'lserial0';
  Param.DataType := ftInteger;
  Param.AsInteger := SerialNo;

  //柜员代码
  Param := Dataset.Params.Add;
  Param.Name := 'semp';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svOperatorNoName).AsString;

  //网卡号
  Param := Dataset.Params.Add;
  Param.Name := 'sstation0';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svMACAddressName).AsString;
  try
    WriteLog('Before Command Process,ID=获取清算状态',lcKSClient);
    Dataset.Open;
    if Dataset.ReturnCode <> 0 then
      raise EDBNoDataset.CreateFmt(Dataset.Fields[1].AsString,[]);

//    if DataSet.RecordCount
    GetInfoFromDataset(Dataset, Status, SerialNo,RecordNo);
    Dataset.Close;
    WriteLog('After Command Process,ID=获取清算状态',lcKSClient);
    FreeAndNil(Dataset);
  except
    on E: EDBNoDataset do
      raise EDBNoDataset.CreateFmt(E.Message,[]);
  end;
end;

procedure TGetLiquidateStatusThread.StartLiquidate(OperationType,
  FunctionNo: Integer; const Market, SeatNo, CurrentDate, CurrencyType,
  OtherParams: string; var Status: string; var count:Integer);
var
  Dataset: TKCDataset;
  Param: THRPCParam;
begin
  CheckObject(Context,'Invalid Context');
  Dataset := TKCDataset.Create(nil);
  Dataset.DataBase := TKCDataBase(Context.GetSystemObject(SODatabase));
  Dataset.RequestType := 403001;

  //职工所属营业部代码
  Param := Dataset.Params.Add;
  Param.Name := 'sbranch_code0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDepartment.ID;

  //操作类别
  Param := Dataset.Params.Add;
  Param.Name := 'lvol0';
  Param.DataType := ftInteger;
  Param.AsInteger := OperationType;

  //命令种类
  Param := Dataset.Params.Add;
  Param.Name := 'lcert_code';
  Param.DataType := ftInteger;
  Param.AsInteger := FunctionNo;

  //市场代码
  Param := Dataset.Params.Add;
  Param.Name := 'smarket_code';
  Param.DataType := ftChar;
  Param.AsString := Market;

  //席位代码
  Param := Dataset.Params.Add;
  Param.Name := 'sstock_code2';
  Param.DataType := ftChar;
  Param.AsString := SeatNo;

  //币种
  Param := Dataset.Params.Add;
  Param.Name := 'scurrency_type';
  Param.DataType := ftChar;
  Param.AsString := CurrencyType;

  //其它参数
  Param := Dataset.Params.Add;
  Param.Name := 'scust_auth';
  Param.DataType := ftChar;
  Param.AsString := OtherParams;

  //日期
  Param := Dataset.Params.Add;
  Param.Name := 'sdate0';
  Param.DataType := ftChar;
  Param.AsString := CurrentDate;

  //柜员代码
  Param := Dataset.Params.Add;
  Param.Name := 'semp';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svOperatorNoName).AsString;

  //网卡号
  Param := Dataset.Params.Add;
  Param.Name := 'sstation0';
  Param.DataType := ftChar;
  Param.AsString := Context.ParamData(svMACAddressName).AsString;

  try
    WriteLog('Before Command Process,ID=启动清算程序',lcKSClient);
    Dataset.Open;
{    if Dataset.ReturnCode <> 0 then
    begin
      raise EDBNoDataset.CreateFmt(Dataset.Fields[1].AsString,[]);
    end;}
    if (not Dataset.Eof) and (Dataset.ReturnCode=0) then
    begin
      Status := Dataset.FieldByName('sstatus0').AsString;
      count:= Dataset.FieldByName('lvol0').AsInteger;
    end
    else
    begin
      Status := '4';
//      count:= Dataset.FieldByName('lvol0').AsInteger;
    end;
    Dataset.Close;
    WriteLog('After Command Process,ID=启动清算程序', lcKSClient);
    FreeAndNil(Dataset);
  except
    on E: EDBNoDataset do
    begin
//      FMessage:='11';
//      SynChronize(UpdateListBox);
      raise EDBNoDataset.CreateFmt(E.Message,[]);
    end;
  end;
end;

procedure TGetLiquidateStatusThread.ThreadDone(Sender: TObject);
begin
  FfaLiquidateList.GetLiquidateStatusThread := nil;
  FfaLiquidateList.SerialNo := FSerialNo;
  FfaLiquidateList.DoEnableStop;   //现在Enable再Disable这样保证能出发界面的事件
  FfaLiquidateList.Stoped := True;
  FfaLiquidateList.DoDisableStop;
end;

procedure TGetLiquidateStatusThread.UpdateListBox;
var
  w: Integer;
begin
  with FfaLiquidateList do
  begin
    w := ListBox.Canvas.TextWidth(FMessage);
    if FScrollBarWidth < w then
    begin
      FScrollBarWidth := w + 80;
      SendMessage(ListBox.Handle, LB_SETHORIZONTALEXTENT, FScrollBarWidth, 0);
    end;
    ListBox.Items.Add(FMessage);
    if ListBox.Items.Count>0 then
    ListBox.ItemIndex := ListBox.Items.Count - 1;
  end;
end;

{ TfaLiquidateList }

procedure TfaLiquidateList.Kill;
begin
  if GetLiquidateStatusThread <> nil then
  begin
    if not GetLiquidateStatusThread.Terminated then
    begin
      GetLiquidateStatusThread.Terminate;
      GetLiquidateStatusThread.WaitFor;
    end;
    GetLiquidateStatusThread := nil;
  end;
end;

procedure TfaLiquidateList.Start(FunctionNo: Integer;SysDate,CurrencyType: string;
                       MarketSeatNoItems: TStringList=nil;OtherParam: string = '');
begin
  if GetLiquidateStatusThread = nil then
  begin
    Stoped := False;
//    if FSerialNo = -1 then
      try
          GetLiquidateStatusThread.GetSerialNo(FunctionNo, '', '', SysDate, FSerialNo);
      except
        on E: Exception do
        begin
          Context.GetDialogSystem.ShowError(E.Message);
          Exit;
        end;
      end;
    GetLiquidateStatusThread := TGetLiquidateStatusThread.Create(FunctionNo,SysDate,CurrencyType,OtherParam,SerialNo,Self,MarketSeatNoItems);
  end;
  FSysDate := SysDate;
  FCurrencyType := CurrencyType;
  FFunctionNo := FunctionNo;
end;

procedure TfaLiquidateList.Pause;
begin
  if GetLiquidateStatusThread <> nil then
    GetLiquidateStatusThread.Pause;
end;

destructor TfaLiquidateList.Destroy;
begin
  if GetLiquidateStatusThread <> nil then
    Kill;
  inherited;
end;

constructor TfaLiquidateList.Create(AOwner: TComponent);
begin
  inherited;
  GetLiquidateStatusThread := nil;
  Stoped := True;
  FSerialNo := -1;
end;

procedure TfaLiquidateList.DoDisableStop;
begin
  if Assigned(FDisableStop) then
    FDisableStop(nil);
end;

procedure TfaLiquidateList.DoEnableStop;
begin
  if Assigned(FEnableStop) then
    FEnableStop(nil);
end;


procedure TfaLiquidateList.GetMarketSeatNo(var Market, SeatNo: string);
begin
  if GetLiquidateStatusThread <> nil then
  begin
    Market := GetLiquidateStatusThread.Market;
    SeatNo := GetLiquidateStatusThread.SeatNo;
  end;
end;

procedure TfaLiquidateList.Stop;
var
  Market,SeatNo,Status: string;
  count:Integer;
begin
  GetMarketSeatNo(Market, SeatNo);
  GetLiquidateStatusThread.StartLiquidate(2,FFunctionNo,Market,SeatNo,FSysDate,FCurrencyType,'',Status,count);
  Pause;
end;

procedure TfaLiquidateList.ListBoxMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
begin
  if Button = mbRight then
    PopupMenu.Items[0].Enabled := Stoped;
end;

procedure TfaLiquidateList.nClearClick(Sender: TObject);
begin
  ListBox.Clear;
  SendMessage(ListBox.Handle, LB_SETHORIZONTALEXTENT, 0, 0);
end;

end.
