unit uPhotoPExp;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, GridsEh, DBGridEh, ComCtrls, Buttons, DB, ADODB,jpeg;

type
  TfrmPhotoPExp = class(TForm)
    dbgrdhDb: TDBGridEh;
    pb1: TProgressBar;
    grp2: TGroupBox;
    lbl1: TLabel;
    edtSheetName: TEdit;
    btnOpenExcel: TBitBtn;
    btnCloseExcel: TBitBtn;
    btnImport: TBitBtn;
    btnExit: TBitBtn;
    Label1: TLabel;
    lblFilePath: TLabel;
    dsOpen: TDataSource;
    qryOpen: TADOQuery;
    dlgOpen: TOpenDialog;
    btnQueryData: TBitBtn;
    grp1: TGroupBox;
    mmoError: TMemo;
    BitBtn1: TBitBtn;
    dlgSave1: TSaveDialog;
    conOpen: TADOConnection;
    GroupBox1: TGroupBox;
    Label2: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    Label12: TLabel;
    chkSetSize: TCheckBox;
    edtWidth: TEdit;
    edtHeight: TEdit;
    qryQuery: TADOQuery;
    dsQuery: TDataSource;
    procedure btnExitClick(Sender: TObject);
    procedure btnOpenExcelClick(Sender: TObject);
    procedure btnCloseExcelClick(Sender: TObject);
    procedure btnImportClick(Sender: TObject);
    procedure btnQueryDataClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }     TempStringList: TStrings;
    procedure closeDataSet;
  public
    { Public declarations }
  end;

var
  frmPhotoPExp: TfrmPhotoPExp;

implementation

uses uCommon, Udm;

{$R *.dfm}

procedure TfrmPhotoPExp.btnExitClick(Sender: TObject);
begin
  qryOpen.Close;
  conOpen.Connected:=false;
  close;
end;

procedure TfrmPhotoPExp.btnOpenExcelClick(Sender: TObject);
begin
  dlgOpen.Title := '请选择相应的Excel文件';
  dlgOpen.Filter := 'Excel(*.xls)|*.xls';
  if dlgOpen.Execute then
    lblFilePath.Caption := dlgOpen.FileName;
end;

procedure TfrmPhotoPExp.btnCloseExcelClick(Sender: TObject);
begin
  closeDataSet;
  btnImport.Enabled:=False;
  btnCloseExcel.Enabled := False;
end;

procedure TfrmPhotoPExp.btnImportClick(Sender: TObject);
var
  i: integer;
  M1: TMemoryStream;
  //Fjpg: TJpegImage;
  picPath:string;
  photoName: string;
  tmpQuery:TADOQuery;

  tmpBmp:TBitmap;
  OldGraphics : TBitmap;
  expJpg:TJPEGImage;
begin

  if TempStringList.Count <= 0 then
  begin
    ShowMessage('请先查询数据,然后再导出！');
    Exit;
  end;
  
  if chkSetSize.Checked then
  begin
    try
      if (StrToInt(edtWidth.Text)<30) or (StrToInt(edtHeight.Text)<40) then

      if StrToInt(edtWidth.Text)<300 then
        if Application.MessageBox('照片宽度像素小于300时，照片质量可能受到影响，你确定使用该像素要导出吗？',PChar(Application.Title),MB_YESNO+mb_iconquestion)=idno then
          Exit;
    except
      on ex:Exception do
      begin
        ShowMessage(ex.Message+' 宽度像素不能小于30，请输入有效的像素值！');
        Exit;
      end;
    end;
  end;
  {
  if ExportData(dlgSave1,dbgrdhDb)=False then
    Exit;
  }
  if dlgSave1.Execute then
    picPath:=dlgSave1.Title;
  picpath:=picpath+formatdatetime('yyyymmdd',Date());
  if not directoryExists(picpath) then
    if not CreateDir(picpath) then
      raise Exception.Create('不能创建文件夹：'+picpath);

  //qryQuery.First;
  pb1.Min := 0;
  pb1.Max := TempStringList.Count;
  mmoError.Lines.Clear;
  for i := 0 to TempStringList.Count - 1 do
  begin
    //**************************************************************************
    tmpQuery:=nil;
    M1:=nil;
    //Fjpg:=nil;
    try
      tmpQuery:=TADOQuery.Create(nil);
      tmpQuery.Connection:=frmdm.conn;
      tmpQuery.Close;
      tmpQuery.SQL.Clear;
      tmpQuery.SQL.Add('select p.'+custId+',c.'+stuempNo+',p.'+pPhoto+' from '+tblPhoto);
      tmpQuery.SQL.Add(' p left join '+tblCust+' c on p.'+custId+'=c.'+custId);
      tmpQuery.SQL.Add(' where p.'+stuempNo+'='+#39+TempStringList.Strings[i]+#39);
      tmpQuery.Open;
      if not tmpQuery.IsEmpty then
      begin
        photoName := tmpQuery.FieldByName(stuempNo).AsString;
        //Fjpg := TJpegImage.Create;
        M1 := TMemoryStream.Create;
        M1.Clear;
        if TBlobField(tmpQuery.FieldByName(pPhoto)).AsString <> null then
          TBlobField(tmpQuery.FieldByName(pPhoto)).SaveToStream(M1);
        M1.Position := 0;
        //M1.SaveToFile('d:\ddd.jpg');
        if M1.Size > 0 then
        begin
          //FJpg.LoadFromStream(M1);
          //自定义照片大小导出
          if chkSetSize.Checked then
          begin
            OldGraphics := nil;
            tmpBmp := nil;
            expJpg:=nil;
            try
              OldGraphics := TBitmap.Create;
              //先把jpg格式的照片转换为bmp格式
              //OldGraphics.Assign(Fjpg);
              OldGraphics.LoadFromStream(M1);

              //重新定义照片的大小
              tmpBmp := TBitmap.Create;
              tmpBmp.Width := StrToInt(edtWidth.Text);
              tmpBmp.Height := StrToInt(edtHeight.Text);
              tmpBmp.Canvas.StretchDraw(Rect(0, 0, tmpBmp.Width, tmpBmp.Height),OldGraphics);

              //重新把照片转换为jpg格式
              expJpg := TJPEGImage.Create;
              expJpg.Assign(tmpBmp);
              expJpg.SaveToFile(picpath + '\' + photoName + '.jpg');
            finally
              OldGraphics.Free;
              tmpBmp.Free;
              expJpg.Free;
            end;
          end
          else
          begin
            M1.SaveToFile(picpath + '\' + photoName + '.jpg');
            //FJpg.SaveToFile(picpath + '\' + photoName + '.jpg');
          end;
        end
        else
        begin
          mmoError.Lines.add('信息导出失败：'+photoName );
          Continue;
        end;
      end
      else
      begin
        mmoError.Lines.add('学/工号：' + TempStringList.Strings[i]);
        Continue;
      end;
    finally
      M1.Free;
      //FJpg.Free;
      tmpQuery.Destroy;
    end;
    //qryQuery.Next;
    pb1.Position := i + 1;
  end;
  TempStringList.Clear;
  if mmoError.Lines.Count>0 then
  begin
    mmoError.Lines.SaveToFile(picpath+'\导出失败列表.txt');
  end;
  ShowMessage('完成导出人员照片信息，文件存放位置--'+picpath);
  pb1.Position := 0;
end;

procedure TfrmPhotoPExp.btnQueryDataClick(Sender: TObject);
var
  sqlstr:string;
  i:Integer;
begin
  try
    if conOpen.Connected=True then
      conOpen.Connected:=False;
    conOpen.ConnectionString:='Provider=Microsoft.Jet.OLEDB.4.0;Data Source='+
    Trim(lblFilePath.Caption)+';Extended Properties=Excel 8.0;Persist Security Info=False';
    conOpen.Connected :=True;
    qryOpen.Connection := conOpen;

    sqlstr:='select * from ['+Trim(edtSheetName.Text)+'$] where 学工号<>'+#39+''+#39;
    qryOpen.Close;
    qryOpen.SQL.Clear;
    qryOpen.SQL.Add(sqlstr);
    qryOpen.Open;
    for  i:= 0 to dbgrdhDb.Columns.Count-1 do
    begin
      dbgrdhDb.Columns[i].Width:=100;
      dbgrdhDb.Columns[i].Title.Alignment:=taCenter;
    end;
  except
    ShowMessage('打开数据表失败，请检查打开的Excel文件是否正确！');
    Exit;
  end;
  if not qryOpen.IsEmpty then
  begin
    qryOpen.First;
    while not qryOpen.Eof do
    begin
      //if qryQuery.fieldbyname(custId).AsString<>'' then
      TempStringList.Add(qryOpen.fieldbyname('学工号').AsString);
      qryOpen.Next;
    end;
  end;
  btnImport.Enabled:=True;
  btnCloseExcel.Enabled := True;
end;

procedure TfrmPhotoPExp.closeDataSet;
begin
  if qryOpen.Active then
  begin
    qryOpen.Recordset.Close;
    qryOpen.Close;
  end;
  if conOpen.Connected then
    conOpen.Connected:=false;
end;

procedure TfrmPhotoPExp.FormDestroy(Sender: TObject);
begin
  TempStringList.Destroy;
  closeDataSet;
end;

procedure TfrmPhotoPExp.BitBtn1Click(Sender: TObject);
begin
  if mmoError.Lines.Count=0 then
  begin
    ShowMessage('没有要保存的文本信息！');
    Exit;
  end;
  dlgSave1.Title := '请选择要保存的文件路径';
  dlgSave1.Filter := '文本文件|*.txt';
  if dlgSave1.Execute then
    mmoError.Lines.SaveToFile(dlgSave1.FileName+'.txt');
end;

procedure TfrmPhotoPExp.FormShow(Sender: TObject);
begin
  TempStringList:=TStringList.Create;

end;

end.
