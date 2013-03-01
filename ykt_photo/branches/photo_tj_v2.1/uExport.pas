unit uExport;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, GridsEh, DBGridEh, ComCtrls, DB, ADODB,
  DBCtrls, Mask, DBCtrlsEh, DBLookupEh,INIFiles,jpeg;

type
  TfrmExport = class(TForm)
    pnlTop: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    chkCust: TCheckBox;
    pnl1: TPanel;
    mmoSql: TMemo;
    Label7: TLabel;
    pnl2: TPanel;
    Label8: TLabel;
    lstError: TListBox;
    btnQuery: TButton;
    btnExport: TButton;
    btnExit: TButton;
    pnl3: TPanel;
    dbgrdhData: TDBGridEh;
    Label9: TLabel;
    edtStuEmpNo: TEdit;
    edtName: TEdit;
    dtpBegin: TDateTimePicker;
    dtpEnd: TDateTimePicker;
    cbbDept: TDBLookupComboboxEh;
    cbbType: TDBLookupComboboxEh;
    cbbSpec: TDBLookupComboboxEh;
    ProgressBar1: TProgressBar;
    cbbArea: TDBLookupComboboxEh;
    Label10: TLabel;
    qryType: TADOQuery;
    dsType: TDataSource;
    dsDept: TDataSource;
    qryDept: TADOQuery;
    qryArea: TADOQuery;
    dsArea: TDataSource;
    qrySpec: TADOQuery;
    dsSpec: TDataSource;
    dsQuery: TDataSource;
    qryQuery: TADOQuery;
    SaveDialog1: TSaveDialog;
    Label11: TLabel;
    grp1: TGroupBox;
    chkSetSize: TCheckBox;
    lbl1: TLabel;
    lbl2: TLabel;
    edtWidth: TEdit;
    edtHeight: TEdit;
    lbl3: TLabel;
    lbl4: TLabel;
    Label12: TLabel;
    procedure FormShow(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnExitClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnExportClick(Sender: TObject);
    procedure edtWidthChange(Sender: TObject);
    procedure edtWidthClick(Sender: TObject);
    procedure edtWidthKeyPress(Sender: TObject; var Key: Char);
    procedure edtHeightKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }

    TempStringList: TStrings;
    procedure fillCbbData();
    procedure queryData();
  public
    { Public declarations }
  end;

var
  frmExport: TfrmExport;

implementation

uses Udm, uCommon;

{$R *.dfm}

procedure TfrmExport.FormShow(Sender: TObject);
begin
  closeQuery;
  fillCbbData();
  dtpBegin.Date:=(Date()-365*5);
  dtpEnd.Date:=Date();
  TempStringList:=TStringList.Create;
end;

procedure TfrmExport.fillCbbData;
var
  deptSql:string;
  specSql:string;
  typeSql:string;
  areaSql:string;
begin
  //deptSql:='select '+deptcode+','+deptName+' from '+tbldept;
  //specSql:='select '+specCode+','+specName+' from '+tblspec;
  //typeSql:='select '+typeNo+','+typeName+' from '+tblCutType;
  //areaSql:='select '+areaNo+','+areaName+' from '+tblArea+' where '+areaFather+'=1';

  getFillQuerySql(deptSql,specSql,typeSql,areaSql);
  qryDept.Close;
  qryDept.SQL.Clear;
  qryDept.SQL.Add(deptSql);
  qryDept.Open;
  cbbDept.ListField:=deptName;
  cbbDept.KeyField:=deptCode;
  qryDept.Sort := deptName;

  qryType.Close;
  qryType.SQL.Clear;
  qryType.SQL.Add(typeSql);
  qryType.Open;
  cbbType.KeyField:=typeNo;
  cbbType.ListField:=typeName;

  qrySpec.Close;
  qrySpec.SQL.Clear;
  qrySpec.SQL.Add(specSql);
  qrySpec.Open;
  cbbSpec.KeyField:=specCode;
  cbbSpec.ListField:=specName;
  qrySpec.Sort := specName;

  qryArea.Close;
  qryArea.SQL.Clear;
  qryArea.SQL.Add(areaSql);
  qryArea.Open;
  cbbArea.KeyField:=areaNo;
  cbbArea.ListField:=areaName;
end;

procedure TfrmExport.queryData;
var
  queryIni:TIniFile;
  sqlStr:string;
begin
  if chkCust.Checked=True then
  begin
    sqlStr:=mmoSql.Text;
  end
  else
  begin
    queryIni := nil;
    if FileExists(apppath+'photoquery.ini') = false then
    begin
      Application.MessageBox('系统配置文件已经被破坏，请与系统管理员联系！',
        '系统错误！', mb_ok + mb_iconerror);
      Application.Terminate;
    end;
    try
      queryIni := TIniFile.Create(apppath+'photoquery.ini');
      sqlStr := queryIni.ReadString('photoquery','photoquerysql','');
    finally
      queryIni.Destroy;
    end;
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+'>='+#39+formatdatetime('yyyymmdd',dtpBegin.Date)+#39;
    sqlStr:=sqlStr+' and photo.'+pPhotoDate+'<='+#39+formatdatetime('yyyymmdd',dtpEnd.Date)+#39;
    if edtStuEmpNo.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+stuempNo+'='+#39+edtStuEmpNo.Text+#39;
    if edtName.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+custName+' like '+#39+'%'+edtname.Text+'%'+#39;
    if cbbArea.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+custArea+'='+inttostr(cbbArea.KeyValue);
    if cbbDept.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+custDeptNo+'='+#39+cbbdept.KeyValue+#39;
    if cbbType.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+custType+'='+inttostr(cbbType.KeyValue);
    if cbbSpec.Text<>'' then
      sqlStr:=sqlStr+' and cust.'+custSpecNo+'='+#39+cbbspec.KeyValue+#39;
  end;
  dbgrdhData.Columns[0].FieldName:=custId;
  dbgrdhData.Columns[1].FieldName:=stuempNo;
  dbgrdhData.Columns[2].FieldName:=custName;
  dbgrdhData.Columns[3].FieldName:=deptName;
  dbgrdhData.Columns[4].FieldName:=specName;
  dbgrdhData.Columns[5].FieldName:=typeName;
  dbgrdhData.Columns[6].FieldName:=classNo;
  qryQuery.Close;
  qryQuery.SQL.Clear;
  qryQuery.SQL.Add(sqlStr);
  qryQuery.SQL.SaveToFile('sql.txt');
  qryQuery.Open;                                     
  if not qryQuery.IsEmpty then
  begin
    qryQuery.First;
    while not qryQuery.Eof do
    begin
      //if qryQuery.fieldbyname(custId).AsString<>'' then
      TempStringList.Add(qryQuery.fieldbyname(custId).AsString);
      qryQuery.Next;
    end;
  end;
end;

procedure TfrmExport.btnQueryClick(Sender: TObject);
begin
  if dtpBegin.Date>dtpEnd.Date then
  begin
    showmessage('你选择的开始日期大于结束日期，请从新选择！');
    exit;
  end;
  TempStringList.Clear;
  queryData();
end;

procedure TfrmExport.btnExitClick(Sender: TObject);
begin
  close();
end;

procedure TfrmExport.FormDestroy(Sender: TObject);
begin
  TempStringList.Destroy;
end;

procedure TfrmExport.btnExportClick(Sender: TObject);
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
  if ExportData(SaveDialog1,dbgrdhData)=False then
    Exit;

  picPath:=SaveDialog1.Title;
  picpath:=picpath+formatdatetime('yyyymmdd',Date());
  if not directoryExists(picpath) then
    if not CreateDir(picpath) then
      raise Exception.Create('不能创建文件夹：'+picpath);

  qryQuery.First;
  ProgressBar1.Min := 0;
  ProgressBar1.Max := TempStringList.Count;
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
      tmpQuery.SQL.Add(' where p.'+custId+'='+#39+TempStringList.Strings[i]+#39);
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
          lstError.items.add('学/工号：' + photoName + '信息导出失败！');
          Continue;
        end;
      end;
    finally
      M1.Free;
      //FJpg.Free;
      tmpQuery.Destroy;
    end;
    qryQuery.Next;
    ProgressBar1.Position := i + 1;
  end;
  ShowMessage('完成导出人员照片信息，文件存放位置--'+picpath);
  ProgressBar1.Position := 0;
end;

procedure TfrmExport.edtWidthChange(Sender: TObject);
var
  w,h:Integer;
begin
  if (Sender = edtWidth) and (ActiveControl = edtWidth) then
  begin
    try
      if Trim(edtWidth.Text)='' then
        w:=0
      else
        w:=StrToInt(edtWidth.Text);
    except
      ShowMessage('请输入有效的照片宽度！');
      Exit;
    end;
    edtHeight.Text := IntToStr(Round((w * 4)/3));
  end
  else
  if (Sender = edtHeight) and (ActiveControl = edtHeight) then
  begin
    try
      if Trim(edtHeight.Text)='' then
        h:=0
      else
        h:=StrToInt(edtHeight.Text);
    except
      ShowMessage('请输入有效的照片高度！');
      Exit;
    end;
    edtWidth.Text := IntToStr(Round((h * 3)/4));
  end;
end;

procedure TfrmExport.edtWidthClick(Sender: TObject);
begin
  TEdit(Sender).SelectAll;

end;

procedure TfrmExport.edtWidthKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key = #13) then
  begin
    Key := #0;
    edtHeight.SetFocus;
  end
  else
  if not (Key in ['0'..'9', #8]) then
  begin
    Key := #0;
  end;

end;

procedure TfrmExport.edtHeightKeyPress(Sender: TObject; var Key: Char);
begin
  if (Key = #13) then
  begin
    Key := #0;
    //ModalResult := mrOk;
  end;

end;

end.
