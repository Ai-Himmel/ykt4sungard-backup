unit UAImportPosSerial;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons;

type
  TfaqhPosSerialImport = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnImport: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    btnOpen: TBitBtn;
    dlgOpen: TOpenDialog;
    Label5: TLabel;
    edtTable: TWVEdit;
    lbl1: TLabel;
    lblFile: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    RzDBGrid1: TRzDBGrid;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    procedure iniGridSize;
    procedure closeDataSet;//关闭记录集
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhPosSerialImport: TfaqhPosSerialImport;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhPosSerialImport.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhPosSerialImport.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhPosSerialImport.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  //inherited;
  try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFile.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 卡号<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;
    except
      ShowMessage('查询错误，请检查excel文件及表单名称是否正确！');
      Exit;
    end;
    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=100;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确！');
  end;
end;

procedure TfaqhPosSerialImport.iniGridSize;
begin

end;

procedure TfaqhPosSerialImport.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  sDate,sTime,sDevId,pNo:string;
  iSerial,iBusiId,iTradeCode,iCardNo,iPckNo,iTrdNo,iSign:Integer;
  fBMoney,fEMoney,fMoney,fMMoney:Real;
begin
  //inherited;
  if qrySource.Active=False then
  begin
    ShowMessage('请先打开要要导入的Excel！');
    Exit;
  end;
  if qrySource.RecordCount=0 then
  begin
    ShowMessage('没有你要导入的数据！');
    Exit;
  end;
  if qrySource.RecordCount<2 then
  begin
    ShowMessage('要导入的数据小于2条，请直接到POS流水设置中添加流水信息！');
    Exit;
  end;
  xH:=1;//序号
  qrySource.First;
  sDate := Trim(qrySource.fieldbyname('交易日期').AsString);
  sTime := qrySource.fieldbyname('交易时间').AsString;
  sDevId := qrySource.fieldbyname('设备物理编号').AsString;

  iSerial := qrySource.fieldbyname('设备流水号').AsInteger;
  iBusiId := qrySource.fieldbyname('商户号').AsInteger;
  iTradeCode := 0;//qrySource.fieldbyname('交易码').AsInteger;
  iCardNo := qrySource.fieldbyname('卡号').AsInteger;
  iPckNo := qrySource.fieldbyname('钱包号').AsInteger;
  iTrdNo := qrySource.fieldbyname('卡交易次数').AsInteger;
  iSign := qrySource.fieldbyname('交易标记').AsInteger;

  fBMoney := qrySource.fieldbyname('卡交易前余额').AsFloat;
  fEMoney := qrySource.fieldbyname('卡交易后余额').AsFloat;
  fMoney := qrySource.fieldbyname('发生额').AsFloat;
  fMMoney := qrySource.fieldbyname('搭伙费').AsFloat;

  pNo := ' ';

  WorkView.FieldByName('序号').Data.SetInteger(xh);
  WorkView.FieldByName('批次号').Data.SetString(pNo);
  WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  WorkView.FieldByName('交易日期').Data.SetString(sDate);
  WorkView.FieldByName('交易时间').Data.SetString(sTime);
  WorkView.FieldByName('设备物理编号').Data.SetString(sDevId);
  WorkView.FieldByName('设备流水号').Data.SetInteger(iSerial);
  WorkView.FieldByName('商户卡号').Data.SetInteger(iBusiId);
  WorkView.FieldByName('交易码').Data.SetInteger(iTradeCode);
  WorkView.FieldByName('卡号').Data.SetInteger(iCardNo);
  WorkView.FieldByName('钱包号').Data.SetInteger(iPckNo);
  WorkView.FieldByName('卡交易次数').Data.SetInteger(iTrdNo);
  WorkView.FieldByName('交易标记').Data.SetInteger(iSign);

  WorkView.FieldByName('卡交易前余额').Data.SetFloat(fBMoney);
  WorkView.FieldByName('卡交易后余额').Data.SetFloat(fEMoney);
  WorkView.FieldByName('发生额').Data.SetFloat(fMoney);
  WorkView.FieldByName('管理费').Data.SetFloat(fMMoney);
  //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
  //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息

  MainRequest.SendCommand;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    pNo:=WorkView.fieldbyname('批次号').Data.AsString;
  end;
  qrySource.Next;
  f:=1;
  //while not qrySource.Eof do
  for i := 1 to qrySource.RecordCount-1 do
  begin

    //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
    //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
    xh:=xh+1;
    f:=f+1;
    if f=qrySource.RecordCount then
    begin
      WorkView.FieldByName('是否传送完毕').Data.SetString('1');
    end
    else
    begin
      WorkView.FieldByName('是否传送完毕').Data.SetString('0');
    end;
    
    sDate := Trim(qrySource.fieldbyname('交易日期').AsString);
    sTime := qrySource.fieldbyname('交易时间').AsString;
    sDevId := qrySource.fieldbyname('设备物理编号').AsString;

    iSerial := qrySource.fieldbyname('设备流水号').AsInteger;
    iBusiId := qrySource.fieldbyname('商户号').AsInteger;
    iTradeCode := 0;//qrySource.fieldbyname('交易码').AsInteger;
    iCardNo := qrySource.fieldbyname('卡号').AsInteger;
    iPckNo := qrySource.fieldbyname('钱包号').AsInteger;
    iTrdNo := qrySource.fieldbyname('卡交易次数').AsInteger;
    iSign := qrySource.fieldbyname('交易标记').AsInteger;

    fBMoney := qrySource.fieldbyname('卡交易前余额').AsFloat;
    fEMoney := qrySource.fieldbyname('卡交易后余额').AsFloat;
    fMoney := qrySource.fieldbyname('发生额').AsFloat;
    fMMoney := qrySource.fieldbyname('搭伙费').AsFloat;

    WorkView.FieldByName('序号').Data.SetInteger(xh);
    WorkView.FieldByName('批次号').Data.SetString(pNo);
    //WorkView.FieldByName('是否传送完毕').Data.SetString('0');
    WorkView.FieldByName('交易日期').Data.SetString(sDate);
    WorkView.FieldByName('交易时间').Data.SetString(sTime);
    WorkView.FieldByName('设备物理编号').Data.SetString(sDevId);
    WorkView.FieldByName('设备流水号').Data.SetInteger(iSerial);
    WorkView.FieldByName('商户卡号').Data.SetInteger(iBusiId);
    WorkView.FieldByName('交易码').Data.SetInteger(iTradeCode);
    WorkView.FieldByName('卡号').Data.SetInteger(iCardNo);
    WorkView.FieldByName('钱包号').Data.SetInteger(iPckNo);
    WorkView.FieldByName('卡交易次数').Data.SetInteger(iTrdNo);
    WorkView.FieldByName('交易标记').Data.SetInteger(iSign);

    WorkView.FieldByName('卡交易前余额').Data.SetFloat(fBMoney);
    WorkView.FieldByName('卡交易后余额').Data.SetFloat(fEMoney);
    WorkView.FieldByName('发生额').Data.SetFloat(fMoney);
    WorkView.FieldByName('管理费').Data.SetFloat(fMMoney);
    MainRequest.SendCommand;
    if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
      RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
      Exit;
    end
    else
    begin
      RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    end;
    qrySource.Next;
  end;

  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  closeDataSet;
end;

procedure TfaqhPosSerialImport.btnPrintClick(Sender: TObject);
begin
  //inherited;
  closeDataSet;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhImportCustomerInfo.closeDataSet关闭Excel记录集
  作者:      Administrator
  日期:      2005.08.01
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaqhPosSerialImport.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhPosSerialImport.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('POS流水导入',TfaqhPosSerialImport);

end.