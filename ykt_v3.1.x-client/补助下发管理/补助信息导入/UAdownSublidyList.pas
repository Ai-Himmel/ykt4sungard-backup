unit UAdownSublidyList;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, RzStatus, ADODB, Buttons;

type
  TfaqhdownSublidyList = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    lbl1: TLabel;
    lblFile: TLabel;
    Label3: TLabel;
    edtTable: TWVEdit;
    btnOpen: TBitBtn;
    RzStatusPane1: TRzStatusPane;
    btnImport: TBitBtn;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    dlgOpen: TOpenDialog;
    grid1: TRzDBGrid;
    dlgSave1: TSaveDialog;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
  private

    { Private declarations }
    procedure closeDateSet;
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhdownSublidyList: TfaqhdownSublidyList;

implementation

uses KsFrameworks, 
     KSClientConsts,UCMqhSubsidyImp;
     
{$R *.DFM}

procedure TfaqhdownSublidyList.Init;
begin
  inherited;
  WorkView.Reset;
end;

procedure TfaqhdownSublidyList.btnOpenClick(Sender: TObject);
begin
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhdownSublidyList.btnQueryClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  //try
    if conSource.Connected=True then
      conSource.Connected:=False;
    conSource.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFile.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conSource.Connected :=True;
    qrySource.Connection := conSource;

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 学工号<>'+#39+''+#39+' or 客户号<>'+#39+''+#39;
    {
    if Trim(edtNo.Text)<>'' then
      sqlstr:=sqlstr+' and 学工号='+#39+Trim(edtNo.Text)+#39;
    if Trim(edtMoney.Text)<>'' then
      sqlstr:=sqlstr+' and 补助金额 ='+Trim(edtMoney.Text);
    if Trim(edtDate.Text)<>'' then
      sqlstr:=sqlstr+' and 截止日期 ='+Trim(edtDate.Text);
      }
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    qrySource.Open;
    for  i:= 0 to Grid1.Columns.Count-1 do
    begin
      Grid1.Columns[i].Width:=120;
      Grid1.Columns[i].Title.Alignment:=taCenter;
    end;
  //except
    //ShowMessage('打开数据表失败，请检查打开的Excel文件是否正确！');
  //end;
end;

procedure TfaqhdownSublidyList.closeDateSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;

end;

procedure TfaqhdownSublidyList.btnPrintClick(Sender: TObject);
begin
  //inherited;
  closeDateSet;
end;

procedure TfaqhdownSublidyList.btnImportClick(Sender: TObject);
var
  xH,f,i,custno:integer;
  scust_auth,sdate2,pNo,operCode:string;
  damt0:Real;
  returnInfo : String;
  errList:TStringList;
begin
  //inherited;
  operCode := Context.ParamData(svOperatorNoName).AsString;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('没有你要导入的数据！');
    Exit;
  end;
  if qrySource.RecordCount=1 then
  begin
    xH:=1;//序号
    qrySource.First;
    if Trim(qrySource.fieldbyname('客户号').asstring)='' then
      custno := 0
    else
      custno :=qrySource.fieldbyname('客户号').AsInteger;
    scust_auth := qrySource.fieldbyname('学工号').AsString;
    //sdate0 := qrySource.fieldbyname('补助批次号').asstring;
    try
      damt0 := qrySource.fieldbyname('补助金额').AsFloat;
    except
      damt0 := 0;
    end;
    sdate2 := qrySource.fieldbyname('截止日期').AsString;
    pNo := ' ';

    WorkView.FieldByName('顺序号').Data.SetInteger(xh);
    WorkView.FieldByName('客户号').Data.SetInteger(custno);
    WorkView.FieldByName('学工号').Data.SetString(scust_auth);
    WorkView.FieldByName('导入批次号').Data.SetString(pNo);
    WorkView.FieldByName('补助批次号').Data.SetString('');
    WorkView.FieldByName('补助金额').Data.SetFloat(damt0);
    WorkView.FieldByName('截止日期').Data.SetString(sdate2);
    WorkView.FieldByName('操作员').Data.SetString(operCode);
    //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
    //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
    WorkView.FieldByName('导入标志').Data.SetString('1');

    MainRequest.SendCommand;
    returnInfo:=WorkView.fieldbyname('返回信息').Data.AsString;
    Context.GetDialogSystem.ShowMessage(returnInfo);
    RzStatusPane1.Caption:=returnInfo;
    Exit;
  end;
  xH:=1;//序号
  qrySource.First;
    if Trim(qrySource.fieldbyname('客户号').asstring)='' then
      custno := 0
    else
      custno :=qrySource.fieldbyname('客户号').AsInteger;
  scust_auth := qrySource.fieldbyname('学工号').AsString;
  //sdate0 := qrySource.fieldbyname('补助批次号').AsString;
  try
    damt0 := qrySource.fieldbyname('补助金额').AsFloat;
  except
    damt0 := 0;
  end;
  sdate2 := qrySource.fieldbyname('截止日期').AsString;
  pNo := ' ';

  WorkView.FieldByName('顺序号').Data.SetInteger(xh);
  WorkView.FieldByName('客户号').Data.SetInteger(custno);
  WorkView.FieldByName('学工号').Data.SetString(scust_auth);
  WorkView.FieldByName('导入批次号').Data.SetString(pNo);
  WorkView.FieldByName('补助批次号').Data.SetString('');
  WorkView.FieldByName('补助金额').Data.SetFloat(damt0);
  WorkView.FieldByName('截止日期').Data.SetString(sdate2);
  WorkView.FieldByName('操作员').Data.SetString(operCode);
  //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
  //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
  WorkView.FieldByName('导入标志').Data.SetString('0');

  MainRequest.SendCommand;
  returnInfo := WorkView.fieldbyname('返回信息').Data.AsString;
  if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
  begin
    ShowMessage(returnInfo);
    RzStatusPane1.Caption:=returnInfo;
    Exit;
  end
  else
  begin
    RzStatusPane1.Caption:=returnInfo;
    pNo:=WorkView.fieldbyname('导入批次号').Data.AsString;
  end;
  qrySource.Next;
  f:=1;
  errList := nil;
  try
    errList := TStringList.Create;
    //while not qrySource.Eof do
    for i := 1 to qrySource.RecordCount-1 do
    begin

      //所有的信息传送完成后发送一个完成标志，然后等待后台返回是否写入数据库标志
      //成功则返回成功提示信息，失败则返回哪一条记录失败，并返回失败信息
      xh:=xh+1;
      f:=f+1;
      if f=qrySource.RecordCount then
      begin
        WorkView.FieldByName('导入标志').Data.SetString('1');
      end
      else
      begin
        WorkView.FieldByName('导入标志').Data.SetString('0');
      end;

      if Trim(qrySource.fieldbyname('客户号').asstring)='' then
        custno := 0
      else
        custno :=qrySource.fieldbyname('客户号').AsInteger;
      scust_auth := qrySource.fieldbyname('学工号').AsString;
      //sdate0 := qrySource.fieldbyname('补助批次号').asstring;
      try
      damt0 := qrySource.fieldbyname('补助金额').AsFloat;
      except
        damt0:=0;
      end;
      sdate2 := qrySource.fieldbyname('截止日期').AsString;

      WorkView.FieldByName('顺序号').Data.SetInteger(xh);
      WorkView.FieldByName('客户号').Data.SetInteger(custno);
      WorkView.FieldByName('学工号').Data.SetString(scust_auth);
      WorkView.FieldByName('导入批次号').Data.SetString(pNo);
      WorkView.FieldByName('补助批次号').Data.SetString('');
      WorkView.FieldByName('补助金额').Data.SetFloat(damt0);
      WorkView.FieldByName('截止日期').Data.SetString(sdate2);
      WorkView.FieldByName('操作员').Data.SetString(operCode);
      {
      MainRequest.SendCommand;
      returnInfo:= WorkView.fieldbyname('返回信息').Data.AsString;
      if WorkView.FieldByName('返回码').Data.AsInteger<>0 then
      begin
        RzStatusPane1.Caption:=returnInfo;

        Context.GetDialogSystem.ShowMessage(returnInfo);
        RzStatusPane1.Caption:=returnInfo;
        Exit;
      end;
      }
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('学工号['+scust_auth+']导入失败，原因--'+e.Message);
          qrySource.Next;
          Continue;
        end;
      end;
      if WorkView.FieldByName('返回码').Data.AsString<>'0' then
      begin
        errList.Add('学工号['+scust_auth+']导入失败，原因--'+WorkView.fieldbyname('返回信息').Data.AsString);
        qrySource.Next;
        Continue;
      end;

      RzStatusPane1.Caption:=returnInfo;
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

  Context.GetDialogSystem.ShowMessage(returnInfo);
  RzStatusPane1.Caption:=returnInfo;
  //closeDataSet;
end;

initialization
  TUIStdClassFactory.Create('补助信息导入',TfaqhdownSublidyList);

end.