unit UAImportDevInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImportDevInfo = class(TfaqhSimpleQueryTemp)
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
    procedure closeDataSet;//关闭记录集
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImportDevInfo: TfaqhImportDevInfo;

implementation

uses KsFrameworks, 
     KSClientConsts;
     
{$R *.DFM}

procedure TfaqhImportDevInfo.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImportDevInfo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImportDevInfo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 设备名称<>'+#39+''+#39;
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
    pbstat.Position := 0;
  except
    ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确！');
  end;
end;

procedure TfaqhImportDevInfo.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  devName:string;
  devType:Integer;
  devMaType:string;
  devUse:Integer;
  devphyId:string;
  area:string;
  parentDev:Integer;
  subSystem:Integer;
  subFee:Integer;
  cardCon:string;
  portNo:Integer;
  devMaNo:Integer;
  IpAddr:string;
  linkType:Integer;
  portNum:Integer;
  linkNo:Integer;
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
    ShowMessage('要导入的数据小于2条，请直接到设备信息设置中添加设备！');
    Exit;
  end;
  xH:=1;//序号
  qrySource.First;
  devName := Trim(qrySource.fieldbyname('设备名称').AsString);
  devType := qrySource.fieldbyname('设备类型').AsInteger;
  devMaType := qrySource.fieldbyname('设备机型').AsString;
  devUse := qrySource.fieldbyname('设备用途').AsInteger;
  devphyId := qrySource.fieldbyname('设备物理编号').AsString;
  area := qrySource.fieldbyname('所在区域').AsString;

  parentDev := qrySource.fieldbyname('上级设备').AsInteger;
  subSystem := qrySource.fieldbyname('所属子系统').AsInteger;
  subFee := 0;//qrySource.fieldbyname('支持科目收费').AsInteger;
  cardCon := Trim(qrySource.fieldbyname('卡片结构').AsString);
  portNo := qrySource.fieldbyname('服务器端口号').AsInteger;
  devMaNo := qrySource.fieldbyname('设备机号').AsInteger;
  IpAddr := qrySource.fieldbyname('IP地址').AsString;
  linkType := qrySource.fieldbyname('通讯类别').AsInteger;
  portNum := qrySource.fieldbyname('服务器端口数').AsInteger;
  linkNo := qrySource.fieldbyname('通讯端口').AsInteger;
  pNo := ' ';

  WorkView.FieldByName('序号').Data.SetInteger(xh);
  WorkView.FieldByName('批次号').Data.SetString(pNo);
  WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  
  WorkView.FieldByName('设备名称').Data.SetString(devName);
  WorkView.FieldByName('设备类型').Data.SetInteger(devType);
  WorkView.FieldByName('设备机型').Data.SetString(devMaType);
  WorkView.FieldByName('设备用途').Data.SetInteger(devUse);
  WorkView.FieldByName('设备物理编号').Data.SetString(devphyId);
  WorkView.FieldByName('所在区域').Data.SetString(area);
  WorkView.FieldByName('上级设备').Data.SetInteger(parentDev);
  WorkView.FieldByName('所属子系统').Data.SetInteger(subSystem);
  WorkView.FieldByName('支持科目收费').Data.SetInteger(subFee);
  WorkView.FieldByName('卡片结构').Data.SetString(cardCon);
  WorkView.FieldByName('服务器端口号').Data.SetInteger(portNo);
  WorkView.FieldByName('设备机号').Data.SetInteger(devMaNo);
  WorkView.FieldByName('IP地址').Data.SetString(IpAddr);
  WorkView.FieldByName('通讯类别').Data.SetInteger(linkType);
  WorkView.FieldByName('服务器端口数').Data.SetInteger(portNum);
  WorkView.FieldByName('通讯端口').Data.SetInteger(linkNo);
  WorkView.FieldByName('操作标志').Data.SetString('A');
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
    
    devName := Trim(qrySource.fieldbyname('设备名称').AsString);
    devType := qrySource.fieldbyname('设备类型').AsInteger;
    devMaType := qrySource.fieldbyname('设备机型').AsString;
    devUse := qrySource.fieldbyname('设备用途').AsInteger;
    devphyId := qrySource.fieldbyname('设备物理编号').AsString;
    area := qrySource.fieldbyname('所在区域').AsString;

    parentDev := qrySource.fieldbyname('上级设备').AsInteger;
    subSystem := qrySource.fieldbyname('所属子系统').AsInteger;
    subFee := 0;//qrySource.fieldbyname('支持科目收费').AsInteger;
    cardCon := Trim(qrySource.fieldbyname('卡片结构').AsString);
    portNo := qrySource.fieldbyname('服务器端口号').AsInteger;
    devMaNo := qrySource.fieldbyname('设备机号').AsInteger;
    IpAddr := qrySource.fieldbyname('IP地址').AsString;
    linkType := qrySource.fieldbyname('通讯类别').AsInteger;
    portNum := qrySource.fieldbyname('服务器端口数').AsInteger;
    linkNo := qrySource.fieldbyname('通讯端口').AsInteger;
    //pNo := ' ';

    WorkView.FieldByName('序号').Data.SetInteger(xh);
    WorkView.FieldByName('批次号').Data.SetString(pNo);
    //WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  
    WorkView.FieldByName('设备名称').Data.SetString(devName);
    WorkView.FieldByName('设备类型').Data.SetInteger(devType);
    WorkView.FieldByName('设备机型').Data.SetString(devMaType);
    WorkView.FieldByName('设备用途').Data.SetInteger(devUse);
    WorkView.FieldByName('设备物理编号').Data.SetString(devphyId);
    WorkView.FieldByName('所在区域').Data.SetString(area);
    WorkView.FieldByName('上级设备').Data.SetInteger(parentDev);
    WorkView.FieldByName('所属子系统').Data.SetInteger(subSystem);
    WorkView.FieldByName('支持科目收费').Data.SetInteger(subFee);
    WorkView.FieldByName('卡片结构').Data.SetString(cardCon);
    WorkView.FieldByName('服务器端口号').Data.SetInteger(portNo);
    WorkView.FieldByName('设备机号').Data.SetInteger(devMaNo);
    WorkView.FieldByName('IP地址').Data.SetString(IpAddr);
    WorkView.FieldByName('通讯类别').Data.SetInteger(linkType);
    WorkView.FieldByName('服务器端口数').Data.SetInteger(portNum);
    WorkView.FieldByName('通讯端口').Data.SetInteger(linkNo);
    WorkView.FieldByName('操作标志').Data.SetString('A');
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
    pbstat.Position := pbstat.Position + 1;
    qrySource.Next;
  end;
  pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage(WorkView.fieldbyname('返回信息').Data.AsString);
  RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImportDevInfo.btnPrintClick(Sender: TObject);
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
procedure TfaqhImportDevInfo.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImportDevInfo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('设备信息导入',TfaqhImportDevInfo);

end.