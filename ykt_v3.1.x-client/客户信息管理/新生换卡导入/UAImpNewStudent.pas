unit UAImpNewStudent;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons, ComCtrls;

type
  TfaqhImpNewStudent = class(TfaqhSimpleQueryTemp)
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
    FPath:string;
    procedure iniGridSize;
    procedure closeDataSet;//关闭记录集
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhImpNewStudent: TfaqhImpNewStudent;

implementation

uses KsFrameworks, 
     KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhImpNewStudent.Init;
begin
  inherited;
  WorkView.Reset;
  FPath := ExtractFileDir(application.ExeName) + '\' + 'PatchLog';
end;

procedure TfaqhImpNewStudent.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhImpNewStudent.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 学工号<>'+#39+''+#39+' and 新卡显示卡号<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    //ShowMessage(sqlstr);
    try
      qrySource.Open;
    except
      on e:Exception do
      begin
        ShowMessage('查询错误，请检查excel文件及表单名称是否正确--'+e.Message);
        //closeDataSet;
        Exit;
      end;
    end;
    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;
    pbstat.Position := 0;
  except
    on e:Exception do
    begin
      ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确--'+e.Message);
      //closeDataSet;
    end;
  end;
end;

procedure TfaqhImpNewStudent.iniGridSize;
begin

end;

procedure TfaqhImpNewStudent.btnImportClick(Sender: TObject);
var
  xH,f,i:integer;
  stuempNo:string;
  showCardNo:string;
  dealDate:string;
  pNo:string;
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
  xH:=1;//序号
  qrySource.First;
  stuempNo := Trim(qrySource.fieldbyname('学工号').AsString);
  showCardNo := Trim(qrySource.fieldbyname('新卡显示卡号').AsString);
  dealDate := Trim(qrySource.fieldbyname('卡有效期').AsString);
  WorkView.FieldByName('序号').Data.SetInteger(xh);
  WorkView.FieldByName('批次号').Data.SetString(pNo);
  WorkView.FieldByName('是否传送完毕').Data.SetString('0');
  WorkView.FieldByName('操作标志').Data.SetString('A');
  WorkView.FieldByName('学工号').Data.SetString(stuempNo);
  WorkView.FieldByName('新卡显示卡号').Data.SetString(showCardNo);
  WorkView.FieldByName('卡有效期').Data.SetString(dealDate);
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
    //RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
    pNo:=WorkView.fieldbyname('批次号').Data.AsString;
  end;
  
  //pNo:= '';
  qrySource.Next;
  f:=1;
  //while not qrySource.Eof do
  errList := nil;
  try
    errList := TStringList.Create;
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
      showCardNo := qrySource.fieldbyname('新卡显示卡号').AsString;
      dealDate := Trim(qrySource.fieldbyname('卡有效期').AsString);
      WorkView.FieldByName('序号').Data.SetInteger(xh);
      WorkView.FieldByName('批次号').Data.SetString(pNo);
      WorkView.FieldByName('学工号').Data.SetString(stuempNo);
      WorkView.FieldByName('操作标志').Data.SetString('A');
      WorkView.FieldByName('新卡显示卡号').Data.SetString(showCardNo);
      WorkView.FieldByName('卡有效期').Data.SetString(dealDate);
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('学工号['+stuempNO+'],新卡显示卡号['+showcardno+']导入失败，失败原因--'+e.Message);
          pbstat.Position := pbstat.Position+1;
          qrySource.Next;
          Continue;
        end;
      end;
      {       412702198112238124
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
      }
      pbstat.Position := pbstat.Position+1;
      qrySource.Next;
    end;
    pbstat.Position := pbstat.Max;
    if ErrList.Count>0 then
    begin
      ErrList.SaveToFile(FPath+'\新生换卡名单导入失败记录'+FormatDateTime('yyyymmddhhmmss',Now)+'.txt');
      Context.GetDialogSystem.ShowMessage('新生换卡名单导入完成，失败信息存在\bin\PATCHLOG下');
    end
    else
      //Context.GetDialogSystem.ShowMessage('新生换卡名单导入完成!');
      Context.GetDialogSystem.ShowMessage('导入完成，'+WorkView.fieldbyname('返回信息').Data.AsString);
    RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  finally
    errList.Destroy;
    closeDataSet;
  end;
end;

procedure TfaqhImpNewStudent.btnPrintClick(Sender: TObject);
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
procedure TfaqhImpNewStudent.closeDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhImpNewStudent.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('新生换卡名单导入',TfaqhImpNewStudent);

end.