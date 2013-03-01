unit UnBatchExport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Buttons, Db, ADODB, Grids, DBGrids, ComCtrls, Jpeg, FileCtrl,
  DBGridEh, DBGridEhImpExp, GridsEh;

type
  TBatchExpot = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    Edit1: TEdit;
    DataSource1: TDataSource;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    ProgressBar1: TProgressBar;
    Label4: TLabel;
    cbtype: TComboBox;
    ADOQuery1: TADOQuery;
    Memo1: TMemo;
    ADOQuery2: TADOQuery;
    Label5: TLabel;
    Label6: TLabel;
    ListBox1: TListBox;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    DBGridEh1: TDBGridEh;
    Button1: TButton;
    SaveDialog1: TSaveDialog;
    dtpStartDate: TDateTimePicker;
    dtpEndDate: TDateTimePicker;
    cbDate: TCheckBox;
    lblName: TLabel;
    edtName: TEdit;
    chk1: TCheckBox;
    qry1: TADOQuery;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    TempStringList: TStrings;
    TempKindStringList: TStrings;

    procedure setExport(empNo:string);
    procedure ExportData;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  BatchExpot: TBatchExpot;

implementation


uses UAPhoto1, UDb, UtConfigs;
{$R *.DFM}

procedure TBatchExpot.BitBtn1Click(Sender: TObject);
var
  CurrSql: string;
  i: integer;
begin
  CurrSql:='SELECT CUT_TYPE, STUEMP_NO,STUEMP_NAME, FILENAME FROM YKT_CUR.T_CIF_PHOTO WHERE PHOTO_DATE IS NOT NULL AND PHOTO_DATE<>'+#39+''+#39;
  if chk1.Checked then
    CurrSql:=CurrSql+' and FROZEN_STATUS<>9';
  if trim(cbtype.Text)<>'' then
    currsql:=currsql+' and CUT_TYPE='+#39+trim(cbtype.Text)+#39;
  if trim(edit1.Text)<>'' then
    currsql:=currsql+' and STUEMP_NO='+#39+trim(edit1.Text)+#39;
  if trim(edtName.Text)<>'' then
    currsql:=currsql+' and STUEMP_NAME='+#39+trim(edtName.Text)+#39;
  if trim(memo1.Text)<>'' then
    currsql:=currsql+' and '+memo1.Text;

  if cbdate.Checked then
  begin
    if dtpstartdate.Date>dtpenddate.Date then
    begin
      showmessage('你选择的开始日期大于结束日期，请从新选择！');
      exit;
    end;
    currsql:=currsql+' and photo_date>='+#39+formatdatetime('yyyy-mm-dd',dtpstartdate.datetime)+#39;
    currsql:=currsql+' and photo_date<='+#39+formatdatetime('yyyy-mm-dd',dtpenddate.datetime)+#39;
  end;
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add(CurrSql);
  ADOQuery1.SQL.SaveToFile('123.txt');
  try
    ADOQuery1.Open;
    TempStringList.Clear;
    TempKindStringList.Clear;
    Label6.Caption := Inttostr(ADOQuery1.recordcount);
    for i := 0 to ADOQuery1.RecordCount - 1 do
    begin
      TempStringList.Add(Trim(ADOQuery1.fieldbyname('STUEMP_NO').Asstring));
      TempKindStringList.Add(Trim(ADOQuery1.fieldbyname('CUT_TYPE').Asstring));
      ADOQuery1.Next;
    end;
  except
  end;
end;

procedure TBatchExpot.FormCreate(Sender: TObject);
begin
  dtpstartdate.Date:=date();
  dtpenddate.Date:=date();
  TempKindStringList := TStringList.Create;
  self.TempStringList := TStringList.Create;
end;

procedure TBatchExpot.FormDestroy(Sender: TObject);
begin
  ADOQuery1.Close;
  ADOQuery2.Close;
  TempStringList.Free;
  TempKindStringList.Free;
end;

procedure TBatchExpot.BitBtn2Click(Sender: TObject);
var i: integer;
  M1: TMemoryStream;
  Fjpg: TJpegImage;
  picPath:string;
  DirPath1: string;
  Dir3: string;
begin
  if not ADOQuery1.Active then
    ShowMessage('请先查询数据！');

  if TempStringList.Count <= 0 then
    ShowMessage('请先查询数据！');
  ExportData;

  //根据日期建立建立根文件夹,
  //picpath:=NewDirPath;
  //2005-10-22日修改
  picPath:=SaveDialog1.FileName;
  picpath:=picpath+formatdatetime('yyyymmdd',Date());
  if not directoryExists(picpath) then
    if not CreateDir(picpath) then
      raise Exception.Create('不能创建文件夹：'+picpath);

  ADOQuery1.First;
  ProgressBar1.Min := 0;
  ProgressBar1.Max := TempStringList.Count;
  for i := 0 to TempStringList.Count - 1 do
  begin

    DirPath1 := picpath + '\' + TempKindStringList.Strings[i];
    Dir3 := TempStringList.Strings[i];
    //保存到本地，
    if not DirectoryExists(DirPath1) then
      if not CreateDir(DirPath1) then
        raise Exception.Create('不能创建文件夹：' + DirPath1);

    ADOQuery1.Close;
    ADOQuery1.SQL.Clear;
    ADOQuery1.SQL.Add('select STUEMP_NO,photo,filename from ' + PhotoTableName + ' where STUEMP_NO='
      + QuotedStr(TempStringList.Strings[i]));
    ADOQuery1.Open;

    if ADOQuery1.IsEmpty=true then
    begin
      ADOQuery1.Recordset.Close;
      ADOQuery1.Close;
      exit;
    end;

    Fjpg := TJpegImage.Create;
    M1 := TMemoryStream.Create;
    try
      M1.Clear;
      if TBlobField(AdoQuery1.FieldByName(PhotoRecord)).AsString <> null then
        TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(M1);
      M1.Position := 0;
      if M1.Size > 1 then
      begin
        FJpg.LoadFromStream(M1);
        FJpg.SaveToFile(DirPath1 + '\' + Dir3 + '.jpg');
        setExport(ADOQuery1.fieldbyname('STUEMP_NO').AsString);
      end
      else
      begin
        ListBox1.items.add('员工号：' + TempStringList.Strings[i] + '信息导出失败！');
        Continue;
      end;
    finally
      M1.Free;
      FJpg.Free;
    end;
    AdoQuery1.Next;
    ProgressBar1.Position := i + 1;
  end;
  ProgressBar1.Position := 0;
end;

procedure TBatchExpot.Button1Click(Sender: TObject);
begin
  close;
end;

procedure TBatchExpot.ExportData;
var
  ExpClass:TDBGridEhExportClass;
  Ext:String;
begin
  try
  begin
    SaveDialog1.FileName := '导出数据'+formatdatetime('yyyymmdd',date());
    DBGridEh1.Selection.SelectAll ;
    if SaveDialog1.Execute then
    begin
     case SaveDialog1.FilterIndex of
        1: begin ExpClass := TDBGridEhExportAsText; Ext := 'txt'; end;
        5: begin ExpClass := TDBGridEhExportAsCSV; Ext := 'csv'; end;
        2: begin ExpClass := TDBGridEhExportAsHTML; Ext := 'htm'; end;
        3: begin ExpClass := TDBGridEhExportAsRTF; Ext := 'rtf'; end;
        4: begin ExpClass := TDBGridEhExportAsXLS; Ext := 'xls'; end;
      else
        ExpClass := nil; Ext := '';
      end;
        if ExpClass <> nil then
      begin
        if UpperCase(Copy(SaveDialog1.FileName,Length(SaveDialog1.FileName)-2,3)) <>  UpperCase(Ext) then
          SaveDialog1.FileName := SaveDialog1.FileName + '.' + Ext;
        SaveDBGridEhToExportFile(ExpClass,DBGridEh1, SaveDialog1.FileName,False);
      end;
    end;
   end ;
   except
     showmessage('导出失败！请检查...');
   end;
end;

procedure TBatchExpot.setExport(empNo: string);
begin
  qry1.Close;
  qry1.SQL.Clear;
  qry1.SQL.Add('update ykt_cur.t_cif_photo set FROZEN_STATUS=9 where stuemp_no='+#39+empno+#39);
  qry1.ExecSQL;
end;

end.
