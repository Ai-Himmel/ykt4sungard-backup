unit serialdetail;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, ComCtrls, StdCtrls,smartterminterface,FileCtrl;

type
  TfrmDetail = class(TForm)
    lvDetail: TListView;
    btnClose: TButton;
    btnEndSerial: TButton;
    btnSaveDetail: TButton;
    procedure btnSaveDetailClick(Sender: TObject);
  private
    { Private declarations }
    FLog : PMBL_TRADE_LOG;
    function EnsureDir(devphy:string;var path:string):Integer;
    procedure AddItemValue(cap:string;val:array of Byte;vallen:Integer); overload;
    procedure AddItemValue(cap:string;val:Integer);overload;
    procedure AddItemValue(cap,val:string); overload;
    procedure WriteValue(var F:TextFile;key:string;value:array of Byte;vallen:Integer);overload;
    procedure WriteValue(var F:TextFile;key:string;value:Integer);overload;
    procedure WriteValue(var F:TextFile;key:string;value:string);overload;
  public
    { Public declarations }
    function ShowDetail(log:PMBL_TRADE_LOG):Integer;
  end;

var
  frmDetail: TfrmDetail;

implementation

uses mobiletermdemo;

{$R *.DFM}

{ TfrmDetail }

procedure TfrmDetail.AddItemValue(cap: string; val: array of Byte;
  vallen: Integer);
var
  valstring : string;
begin
  SetLength(valstring,100);
  Hex2Str(val,vallen,valstring);
  AddItemValue(cap,valstring);
end;

procedure TfrmDetail.AddItemValue(cap: string; val: Integer);
var
  valstring : string;
begin
  try
    valstring := IntToStr(val);
    AddItemValue(cap,valstring);
  except
    ShowMessage(Format('参数[%s]的值错误',[cap]));
  end;
end;

procedure TfrmDetail.AddItemValue(cap, val: string);
var
  item : TListItem;
begin
  with lvDetail do
  begin
    item := Items.Add;
    item.Caption := cap;
    item.SubItems.Append(val);
  end;
end;

function TfrmDetail.ShowDetail(log: PMBL_TRADE_LOG): Integer;
begin
  lvDetail.Items.BeginUpdate;
  try
    FLog := log;
    lvDetail.Items.Clear;
    AddItemValue('设备物理ID',log.phyid,SizeOf(log.phyid));
    AddItemValue('通信版本号',log.ver);
    AddItemValue('启动原因',log.runreason);
    AddItemValue('流水号',log.serial_no);
    AddItemValue('交易卡号',log.card_id);
    AddItemValue('交易时间',log.tx_datetime);
    AddItemValue('累计使用次数',log.tx_cnt);
    AddItemValue('入卡金额',log.in_card_amount);
    AddItemValue('出卡金额',log.out_card_amount);
    AddItemValue('交易金额',log.tx_trade_amount);
    AddItemValue('交易标记',log.tx_mark);
    AddItemValue('CRC',log.crc,SizeOf(log.crc));
  finally
    lvDetail.Items.EndUpdate;
  end;
  Result := ShowModal;
end;

procedure TfrmDetail.btnSaveDetailClick(Sender: TObject);
var
  dataFile : TextFile;
  filename : string;
  valstring : string;
  outputpath : string;
begin
  SetLength(valstring,100);
  Hex2Str(FLog.phyid,SizeOf(FLog.phyid),valstring);
  valstring := Trim(valstring);
  filename := Format('%s_%d.xml',[valstring,FLog.serial_no]);
  if EnsureDir(valstring,outputpath) = -1 then
  begin
    ShowMessage('没有输出目录！');
    Exit;
  end;
  filename := Format('%s\%s',[outputpath,filename]);
  AssignFile(dataFile,filename);
  try
    Rewrite(dataFile);
    Writeln(dataFile,'<?xml version="1.0" encoding="gb2312"?>');
    Writeln(dataFile,'<serial>');
    WriteValue(dataFile,'设备物理ID',FLog.phyid,SizeOf(FLog.phyid));
    WriteValue(dataFile,'通信版本号',FLog.ver);
    WriteValue(dataFile,'启动原因',FLog.runreason);
    WriteValue(dataFile,'流水号',FLog.serial_no);
    WriteValue(dataFile,'交易卡号',FLog.card_id);
    WriteValue(dataFile,'交易时间',FLog.tx_datetime);
    WriteValue(dataFile,'累计使用次数',FLog.tx_cnt);
    WriteValue(dataFile,'入卡金额',FLog.in_card_amount);
    WriteValue(dataFile,'出卡金额',FLog.out_card_amount);
    WriteValue(dataFile,'交易金额',FLog.tx_trade_amount);
    WriteValue(dataFile,'交易标记',FLog.tx_mark);
    WriteValue(dataFile,'CRC',FLog.crc,SizeOf(FLog.crc));
    Writeln(dataFile,'</serial>');
  except
    ShowMessage('保存文件失败');
  end;
  CloseFile(dataFile);
end;

procedure TfrmDetail.WriteValue(var F: TextFile; key: string;
  value: array of Byte; vallen: Integer);
var
  valstring : string;
begin
  SetLength(valstring,100);
  Hex2Str(value,vallen,valstring);
  WriteValue(F,key,valstring);

end;

procedure TfrmDetail.WriteValue(var F: TextFile; key: string;
  value: Integer);
begin
  WriteValue(F,key,IntToStr(value));
end;

procedure TfrmDetail.WriteValue(var F: TextFile; key, value: string);
var
  line : string;
begin
  line := Format('<param name=%s value=%s />',
    [QuotedStr(key),QuotedStr(value)]);
  Writeln(F,line);
end;

function TfrmDetail.EnsureDir(devphy: string;var path:string): Integer;
begin
  Result := 0;
  path := Format('%s\serials\%s',[frmMain.GetBasePath,devphy]);
  if not DirectoryExists(path) then
  begin
    if not CreateDir(path) then
      Result := -1;
  end;
end;

end.
