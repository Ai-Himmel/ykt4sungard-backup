unit UAImpDevCustInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImpDevCustInfo = class(TfaqhSimpleQueryTemp)
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
    pbstat: TProgressBar;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    //procedure iniGridSize;
    procedure closeDataSet;//关闭记录集
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpDevCustInfo: TfaqhImpDevCustInfo;

implementation

uses KsFrameworks, KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImpDevCustInfo.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImpDevCustInfo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImpDevCustInfo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 设备编号<>'+#39+''+#39;
    sqlstr:=sqlstr+' and 商户编号<>'+#39+''+#39;
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
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确！');
  end;
end;

procedure TfaqhImpDevCustInfo.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  devId,busiId:Integer;
  stopDate,startDate,stopTime:string;
  pNo:string;
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
    ShowMessage('要导入的数据小于2条，请直接到设备商户绑定里面设置！');
    Exit;
  end;
  xH:=1;//序号
  qrySource.First;
  try
  devId := qrySource.fieldbyname('设备编号').AsInteger;
  busiId := qrySource.fieldbyname('商户编号').AsInteger;
  except
    ShowMessage('请输入有效的设备编号和商户编号！');
    Exit;
  end;
  stopDate := qrySource.fieldbyname('停用日期').AsString;
  startDate := qrySource.fieldbyname('启用日期').AsString;
  stopTime := qrySource.fieldbyname('停用时间').asstring;

  pNo := ' ';

  WorkView.FieldByName('序号').Data.SetInteger(xh);
  WorkView.FieldByName('批次号').Data.SetString(pNo);
  WorkView.FieldByName('操作标志').Data.SetString('A');
  WorkView.FieldByName('设备编号').Data.SetInteger(devId);
  WorkView.FieldByName('商户编号').Data.SetInteger(busiId);
  WorkView.FieldByName('停用日期').Data.SetString(stopDate);
  WorkView.FieldByName('启用日期').Data.SetString(startDate);
  WorkView.FieldByName('停用时间').Data.SetString(stopTime);
  //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
  //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
  WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  
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
    //ShowMessage(pNo);
  end;
  qrySource.Next;
  f:=1;
  pbstat.Max := qrySource.RecordCount;
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

    try
    devId := qrySource.fieldbyname('设备编号').AsInteger;
    busiId := qrySource.fieldbyname('商户编号').AsInteger;
    except
      ShowMessage('请输入有效的设备编号和商户编号！');
      Exit;
    end;
    stopDate := qrySource.fieldbyname('停用日期').AsString;
    startDate := qrySource.fieldbyname('启用日期').AsString;
    stopTime := qrySource.fieldbyname('停用时间').asstring;

    WorkView.FieldByName('序号').Data.SetInteger(xh);
    WorkView.FieldByName('批次号').Data.SetString(pNo);
    WorkView.FieldByName('操作标志').Data.SetString('A');
    WorkView.FieldByName('设备编号').Data.SetInteger(devId);
    WorkView.FieldByName('商户编号').Data.SetInteger(busiId);
    WorkView.FieldByName('停用日期').Data.SetString(stopDate);
    WorkView.FieldByName('启用日期').Data.SetString(startDate);
    WorkView.FieldByName('停用时间').Data.SetString(stopTime);
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
    pbstat.Position := pbstat.Position+1;
    qrySource.Next;
  end;
  pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImpDevCustInfo.btnPrintClick(Sender: TObject);
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
procedure TfaqhImpDevCustInfo.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImpDevCustInfo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('设备商户信息导入',TfaqhImpDevCustInfo);

end.