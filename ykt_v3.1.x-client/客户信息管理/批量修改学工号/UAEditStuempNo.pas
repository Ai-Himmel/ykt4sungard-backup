unit UAEditStuempNo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  UqhSimpleQueryTemp, WVCmdReq, WorkViews, Grids, DBGrids, StdCtrls,
  ImageCtrls, ExtCtrls, UICtrls, WVCtrls, Mask, WVDBBinders, Db, 
  RzDBGrid, ADODB, RzStatus, RzPanel, Buttons;

type
  TfaqhEditStuempNo = class(TfaqhSimpleQueryTemp)
    Panel1: TPanel;
    btnImport: TImageButton;
    conSource: TADOConnection;
    qrySource: TADOQuery;
    btnOpen: TImageButton;
    dlgOpen: TOpenDialog;
    Label5: TLabel;
    edtTable: TWVEdit;
    lbl1: TLabel;
    lblFile: TLabel;
    StatusBar: TRzStatusBar;
    RzStatusPane1: TRzStatusPane;
    dlgSave1: TSaveDialog;
    RzDBGrid1: TRzDBGrid;
    procedure btnOpenClick(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnPrintClick(Sender: TObject);
    procedure GridDrawColumnCell(Sender: TObject; const Rect: TRect;
      DataCol: Integer; Column: TColumn; State: TGridDrawState);
  private
    { Private declarations }
    procedure clsDataSet;//关闭记录集
  public
    procedure Init; override;
    { Public declarations }
  end;

var
  faqhEditStuempNo: TfaqhEditStuempNo;

implementation

uses KsFrameworks, KSClientConsts,UCMqhCustomerImp;
     
{$R *.DFM}

procedure TfaqhEditStuempNo.Init;
begin
  inherited;

end;

procedure TfaqhEditStuempNo.btnOpenClick(Sender: TObject);
begin
  //inherited;
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFile.Caption := dlgOpen.FileName;
end;

procedure TfaqhEditStuempNo.btnQueryClick(Sender: TObject);
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

    sqlstr:='select * from ['+Trim(edtTable.Text)+'$] where 原学工号<>'+#39+''+#39;
    sqlstr := sqlstr+ ' and 新学工号<>'+#39+''+#39;
    qrySource.Close;
    qrySource.SQL.Clear;
    qrySource.SQL.Add(sqlstr);
    try
      qrySource.Open;

    except
      Context.GetDialogSystem.ShowMessage('查询错误，请检查excel文件及表单名称是否正确！');
      Exit;
    end;

    for  i:= 0 to RzDBGrid1.Columns.Count-1 do
    begin
      RzDBGrid1.Columns[i].Width:=120;
      RzDBGrid1.Columns[i].Title.Alignment:=taCenter;
    end;

  except
    Context.GetDialogSystem.ShowMessage('打开数据表失败，检查打开的Excel文件或表单名称是否正确！');
  end;
  
end;

procedure TfaqhEditStuempNo.btnImportClick(Sender: TObject);
var
  sOldNo,sNewNo:string;
  errList:TStrings;
begin
  //inherited;
  if qrySource.RecordCount=0 then
  begin
    Context.GetDialogSystem.ShowMessage('没有你要导入的数据！');
    Exit;
  end;
  if Application.MessageBox('你确定要批量修改学工号吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
    Exit;
  errList := nil;
  qrySource.First;
  try
    errList := TStringList.Create;
    while not qrySource.Eof do
    begin
      sOldNo := Trim(qrySource.fieldbyname('原学工号').AsString);
      sNewNo := Trim(qrySource.fieldbyname('新学工号').AsString);

      WorkView.FieldByName('原学工号').Data.SetString(sOldNo);
      WorkView.FieldByName('新学工号').Data.SetString(sNewNo);
      WorkView.FieldByName('操作标志').Data.SetString('U');
      WorkView.FieldByName('批量标志').Data.SetString('1');
      try
        MainRequest.SendCommand;
      except
        on e:Exception do
        begin
          errList.Add('原学/工号:'+sOldNo+' 修改失败，失败原因--'+e.Message);
        end;
      end;
      qrySource.Next;
    end;
  finally
    if errList.Count>0 then
    begin
      if dlgSave1.Execute then
      begin
        errList.SaveToFile(dlgSave1.FileName+'.txt');
        Context.GetDialogSystem.ShowMessage('批量修改学/工号完成,失败信息保存在'+dlgSave1.FileName+'.txt中');
      end
    end
    else
      Context.GetDialogSystem.ShowMessage('批量修改学/工号完成!');
    errList.Destroy;
  end;

  RzStatusPane1.Caption:=WorkView.fieldbyname('返回信息').Data.AsString;
  clsDataSet;
end;

procedure TfaqhEditStuempNo.btnPrintClick(Sender: TObject);
begin
  //inherited;
  clsDataSet;
end;

{-------------------------------------------------------------------------------
  过程名:    TfaqhImportCustomerInfo.closeDataSet关闭Excel记录集
  作者:      Administrator
  日期:      2005.08.01
  参数:      无
  返回值:    无
-------------------------------------------------------------------------------}
procedure TfaqhEditStuempNo.clsDataSet;
begin
  qrySource.Recordset.Close;
  qrySource.Close;
  conSource.Connected:=false;
end;

procedure TfaqhEditStuempNo.GridDrawColumnCell(Sender: TObject;
  const Rect: TRect; DataCol: Integer; Column: TColumn;
  State: TGridDrawState);
begin
  //inherited;

end;

initialization
  TUIStdClassFactory.Create('批量修改学工号',TfaqhEditStuempNo);

end.