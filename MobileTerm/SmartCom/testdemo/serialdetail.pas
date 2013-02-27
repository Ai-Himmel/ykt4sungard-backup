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
    ShowMessage(Format('����[%s]��ֵ����',[cap]));
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
    AddItemValue('�豸����ID',log.phyid,SizeOf(log.phyid));
    AddItemValue('ͨ�Ű汾��',log.ver);
    AddItemValue('����ԭ��',log.runreason);
    AddItemValue('��ˮ��',log.serial_no);
    AddItemValue('���׿���',log.card_id);
    AddItemValue('����ʱ��',log.tx_datetime);
    AddItemValue('�ۼ�ʹ�ô���',log.tx_cnt);
    AddItemValue('�뿨���',log.in_card_amount);
    AddItemValue('�������',log.out_card_amount);
    AddItemValue('���׽��',log.tx_trade_amount);
    AddItemValue('���ױ��',log.tx_mark);
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
    ShowMessage('û�����Ŀ¼��');
    Exit;
  end;
  filename := Format('%s\%s',[outputpath,filename]);
  AssignFile(dataFile,filename);
  try
    Rewrite(dataFile);
    Writeln(dataFile,'<?xml version="1.0" encoding="gb2312"?>');
    Writeln(dataFile,'<serial>');
    WriteValue(dataFile,'�豸����ID',FLog.phyid,SizeOf(FLog.phyid));
    WriteValue(dataFile,'ͨ�Ű汾��',FLog.ver);
    WriteValue(dataFile,'����ԭ��',FLog.runreason);
    WriteValue(dataFile,'��ˮ��',FLog.serial_no);
    WriteValue(dataFile,'���׿���',FLog.card_id);
    WriteValue(dataFile,'����ʱ��',FLog.tx_datetime);
    WriteValue(dataFile,'�ۼ�ʹ�ô���',FLog.tx_cnt);
    WriteValue(dataFile,'�뿨���',FLog.in_card_amount);
    WriteValue(dataFile,'�������',FLog.out_card_amount);
    WriteValue(dataFile,'���׽��',FLog.tx_trade_amount);
    WriteValue(dataFile,'���ױ��',FLog.tx_mark);
    WriteValue(dataFile,'CRC',FLog.crc,SizeOf(FLog.crc));
    Writeln(dataFile,'</serial>');
  except
    ShowMessage('�����ļ�ʧ��');
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
