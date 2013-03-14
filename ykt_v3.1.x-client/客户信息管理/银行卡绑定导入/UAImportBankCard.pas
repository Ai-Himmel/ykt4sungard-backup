unit UAImportBankCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImportBankCard = class(TfaqhSimpleQueryTemp)
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
    dlgSave1: TSaveDialog;
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
  faqhImportBankCard: TfaqhImportBankCard;

implementation

uses KsFrameworks, KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhImportBankCard.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhImportBankCard.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImportBankCard.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 银行卡号<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    //ShowMessage(sqlstr);
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

procedure TfaqhImportBankCard.iniGridSize;
begin

end;

procedure TfaqhImportBankCard.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  stuempNo:string;
  custId:string;
  bankCode:string;
  bankCardNo:string;
  area:string;
  custName:string;
  pNo,ssign:string;
  errList:TStringList;
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
    ShowMessage('要导入的数据小于2条，请直接到客户信息设置里面添加客户信息！');
    Exit;
  end;
  errList := nil;
  try
    errList := TStringList.Create;
    xH:=1;//序号
    qrySource.First;
    stuempNo := Trim(qrySource.fieldbyname('学工号').AsString);
    custId := qrySource.fieldbyname('客户号').AsString;
    bankCode := qrySource.fieldbyname('银行代码').AsString;
    bankCardNo := Trim(qrySource.fieldbyname('银行卡号').AsString);
    area := Trim(qrySource.fieldbyname('校区').AsString);
    custName := Trim(qrySource.fieldbyname('姓名').AsString);

    WorkView.FieldByName('序号').Data.SetInteger(xh);
    WorkView.FieldByName('批次号').Data.SetString(pNo);
    WorkView.FieldByName('是否传送完毕').Data.SetString('0');
    WorkView.FieldByName('操作标志').Data.SetString('I');
    WorkView.FieldByName('学工号').Data.SetString(stuempNo);
    WorkView.FieldByName('校区').Data.SetString(area);
    WorkView.FieldByName('姓名').Data.SetString(custName);

    if custId = '' then
      WorkView.FieldByName('客户号').Data.SetInteger(0)
    else
      WorkView.FieldByName('客户号').Data.SetInteger(StrToInt(custId));
    WorkView.FieldByName('银行代码').Data.SetString(bankCode);
    WorkView.FieldByName('银行卡号').Data.SetString(bankCardNo);
    //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
    //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息

    try
      MainRequest.SendCommand;
    except
      on e:Exception do
      begin
        Context.GetDialogSystem.ShowMessage('导入失败，请保证第一条记录先导入成功-'+e.Message);
        Exit;
      end;
    end;
    if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
    begin
      //errList.Add('学工号['+stuempNo+']导入失败，原因--'+WorkView.fieldbyname('返回信息').Data.AsString);
      Context.GetDialogSystem.ShowMessage('导入失败，请保证第一条记录先导入成功！');
      Exit;
    end
    else
    begin
      //RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
      pNo:=WorkView.fieldbyname('批次号').Data.AsString;
    end;
    qrySource.Next;
    f:=1;
    //while not qrySource.Eof do
    pbstat.Max := qrySource.RecordCount;
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

      stuempNo := Trim(qrySource.fieldbyname('学工号').AsString);
      custId := qrySource.fieldbyname('客户号').AsString;
      bankCode := qrySource.fieldbyname('银行代码').AsString;
      bankCardNo := Trim(qrySource.fieldbyname('银行卡号').AsString);
      area := Trim(qrySource.fieldbyname('校区').AsString);
      custName := Trim(qrySource.fieldbyname('姓名').AsString);

      WorkView.FieldByName('序号').Data.SetInteger(xh);
      WorkView.FieldByName('批次号').Data.SetString(pNo);
      //WorkView.FieldByName('是否传送完毕').Data.SetString('0');
      WorkView.FieldByName('操作标志').Data.SetString('I');
      WorkView.FieldByName('学工号').Data.SetString(stuempNo);
      WorkView.FieldByName('校区').Data.SetString(area);
      WorkView.FieldByName('姓名').Data.SetString(custName);
      if custId = '' then
        WorkView.FieldByName('客户号').Data.SetInteger(0)
      else
        WorkView.FieldByName('客户号').Data.SetInteger(StrToInt(custId));
      WorkView.FieldByName('银行代码').Data.SetString(bankCode);
      WorkView.FieldByName('银行卡号').Data.SetString(bankCardNo);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('学工号['+stuempNo+']导入失败，原因--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      if WorkView.FieldByName('返回码').Data.AsString<>'0' then
      begin
        errList.Add('学工号['+stuempNo+']导入失败，原因--'+WorkView.fieldbyname('返回信息').Data.AsString);
        qrySource.Next;
        Continue;
      end;
      pbstat.Position := pbstat.Position+1;
      Sleep(500);
      qrySource.Next;
    end;
  finally
    if errList.Count>0 then
      if dlgSave1.Execute then
      begin
        errList.SaveToFile(dlgSave1.FileName+'.txt');
      end;      
    errList.Destroy;
  end;
  //pbstat.Position := pbstat.Max;
  Context.GetDialogSystem.ShowMessage('导入完成！');
  //RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  closeDataSet;
end;

procedure TfaqhImportBankCard.btnPrintClick(Sender: TObject);
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
procedure TfaqhImportBankCard.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImportBankCard.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('银行卡绑定导入',TfaqhImportBankCard);

end.