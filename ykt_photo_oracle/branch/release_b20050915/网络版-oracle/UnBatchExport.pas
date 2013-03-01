unit UnBatchExport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Buttons, Db, ADODB, Grids, DBGrids, ComCtrls, Jpeg, FileCtrl,
  DBGridEh, DBGridEhImpExp;

type
  TBatchExpot = class(TForm)
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Combo_academy: TComboBox;
    Combo_Spec: TComboBox;
    Edit1: TEdit;
    DataSource1: TDataSource;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    ComboBox2: TComboBox;
    ComboBox3: TComboBox;
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
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure Combo_academyChange(Sender: TObject);
    procedure Combo_SpecChange(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    TempStringList: TStrings;
    TempDeptStringList: TStrings;
    TempKindStringList: TStrings;


    procedure RefreshKindList;
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

procedure TBatchExpot.RefreshKindList;
var i: integer;
begin
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('SELECT distinct ' + SCode + ',' + BanchCode +
    ' FROM ' + PhotoTableName);
  ADOQuery2.Open;
  if ADOQuery2.RecordCount > 0 then
  begin
    ProgressBar1.Min := 0;
    ProgressBar1.Max := ADOQuery2.RecordCount;
    Combo_Spec.Items.Clear;
    ComboBox3.Items.Clear;
    ADOQuery2.First;
    for i := 0 to ADOQuery2.RecordCount - 1 do
    begin
      ComboBox3.Items.Add(ADOQuery2.fieldbyname(BanchCode).AsString);
      Combo_Spec.Items.Add(ADOQuery2.fieldbyname(SCode).AsString);
      ProgressBar1.Position := i + 1;
      ADOQuery2.Next;
    end;
  end;
  ProgressBar1.Position := 0;
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('SELECT distinct ' + DeptName + ',' + DeptCode +
    ' FROM ' + PhotoTableName);
  ADOQuery2.Open;
  ADOQuery2.First;
  if ADOQuery2.RecordCount > 0 then
  begin
    ProgressBar1.Min := 0;
    ProgressBar1.Max := ADOQuery2.RecordCount;
    Combo_academy.Items.Clear;
    ComboBox2.Items.Clear;
    for i := 0 to ADOQuery2.RecordCount - 1 do
    begin
      ComboBox2.Items.Add(ADOQuery2.fieldbyname(DeptCode).AsString);
      Combo_academy.Items.Add(ADOQuery2.fieldbyname(DeptName).AsString);
      ProgressBar1.Position := i + 1;
      ADOQuery2.Next;
    end;
  end;
  ProgressBar1.Position := 0;
  ADOQuery2.Close;
end;

procedure TBatchExpot.BitBtn1Click(Sender: TObject);
var
  TmpStr: string;
  CurrSql: string;
  i: integer;
begin
  CurrSql := 'SELECT ' + DeptName + ', ' + StuEmpNo + ',' +CutType+','+
    StuempName + ',' + SCode +',' + DeptCode + ',' + opername+','+
    FileName + ' FROM ' + PhotoTableName+' where '+filename+' is not null ';

  if trim(Combo_academy.Text)<>'' then
    currsql:=currsql+' and '+deptname+'='+#39+trim(Combo_academy.Text)+#39;
  if trim(Combo_Spec.text)<>'' then
    currsql:=currsql+' and '+scode+'='+#39+trim(Combo_Spec.text)+#39;
  if trim(cbtype.Text)<>'' then
    currsql:=currsql+' and '+cuttype+'='+#39+trim(cbtype.Text)+#39;
  if trim(edit1.Text)<>'' then
    currsql:=currsql+' and '+stuempno+'='+#39+trim(edit1.Text)+#39;
  if trim(memo1.Text)<>'' then
    currsql:=currsql+' and '+#39+memo1.Text+#39;
  if cbdate.Checked then
  begin
    if dtpstartdate.Date>dtpenddate.Date then
    begin
      showmessage('你选择的开始日期大于结束日期，请从新选择！');
      exit;
    end;
    currsql:=currsql+' and '+photodate+'>='+#39+formatdatetime('yyyy-mm-dd',dtpstartdate.datetime)+#39;
    currsql:=currsql+' and '+photodate+'<='+#39+formatdatetime('yyyy-mm-dd',dtpenddate.datetime)+#39;
  end;
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  if Trim(TmpStr) = '' then
    ADOQuery1.SQL.Add(CurrSql)
  else
    ADOQuery1.SQL.Add(CurrSql + ' and ' + TmpStr);
  try
    ADOQuery1.Open;
    TempStringList.Clear;
    TempDeptStringList.Clear;
    TempKindStringList.Clear;
    Label6.Caption := Inttostr(ADOQuery1.recordcount);
    for i := 0 to ADOQuery1.RecordCount - 1 do
    begin
      TempStringList.Add(Trim(ADOQuery1.fieldbyname(StuEmpNo).Asstring));
      TempDeptStringList.Add(Trim(ADOQuery1.fieldbyname(SCode).Asstring));
      TempKindStringList.Add(Trim(ADOQuery1.fieldbyname(CutType).Asstring));
      ADOQuery1.Next;
    end;
  except
  end;
end;

procedure TBatchExpot.FormCreate(Sender: TObject);
begin
  dtpstartdate.Date:=date();
  dtpenddate.Date:=date();
  RefreshKindList;
  TempKindStringList := TStringList.Create;
  self.TempStringList := TStringList.Create;
  self.TempDeptStringList := TStringList.Create;
end;

procedure TBatchExpot.FormDestroy(Sender: TObject);
begin
  ADOQuery1.Close;
  ADOQuery2.Close;
  TempStringList.Free;
  TempKindStringList.Free;
  TempDeptStringList.Free;
end;

procedure TBatchExpot.BitBtn2Click(Sender: TObject);
var i: integer;
  M1: TMemoryStream;
  Fjpg: TJpegImage;
  picPath:string;
  DirPath1: string;
  DirPath3: string;
  Dir3: string;
begin
  if not ADOQuery1.Active then
    ShowMessage('请先查询数据！');

  if TempStringList.Count <= 0 then
    ShowMessage('请先查询数据！');
  ExportData;

  //根据日期建立建立根文件夹,
  picpath:=NewDirPath;
  picpath:=picpath+formatdatetime('yyyymmdd',Date());
  if not directoryExists(picpath) then
    if not CreateDir(picpath) then
      raise Exception.Create('不能创建文件夹：'+picpath);

  ADOQuery1.First;
  ProgressBar1.Min := 0;
  ProgressBar1.Max := TempStringList.Count;
  for i := 0 to TempStringList.Count - 1 do
  begin

    //按学生院系建立文件夹，修改过后按类别建立文件夹,修改日期：2005-04-14
    //DirPath1 := NewDirPath + '\' + TempDeptStringList.Strings[i];
    //DirPath3 := DirPath1 + '\' + TempKindStringList.Strings[i];
    DirPath1 := picpath + '\' + TempKindStringList.Strings[i];
    //DirPath3 := DirPath1 + '\' + TempDeptStringList.Strings[i];
    Dir3 := TempStringList.Strings[i];
    //保存到本地，
    if not DirectoryExists(DirPath1) then
      if not CreateDir(DirPath1) then
        raise Exception.Create('不能创建文件夹：' + DirPath1);
    {if not DirectoryExists(DirPath3) then
      if not CreateDir(DirPath3) then
        raise Exception.Create('不能创建文件夹：' + DirPath3);}

    ADOQuery1.Close;
    ADOQuery1.SQL.Clear;
    ADOQuery1.SQL.Add('select STUEMP_NO,photo,filename from ' + PhotoTableName + ' where ' +
      StuEmpNo + '=' + QuotedStr(TempStringList.Strings[i]));
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
      if TBlobField(AdoQuery1.FieldByName(Photo)).AsString <> null then
        TBlobField(AdoQuery1.FieldByName(Photo)).SaveToStream(M1);
      M1.Position := 0;
      if M1.Size > 10 then
      begin
        FJpg.LoadFromStream(M1);
        FJpg.SaveToFile(DirPath1 + '\' + Dir3 + '.jpg');
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

procedure TBatchExpot.Combo_academyChange(Sender: TObject);
begin
  ComboBox2.ItemIndex := Combo_academy.ItemIndex;
end;

procedure TBatchExpot.Combo_SpecChange(Sender: TObject);
begin
  ComboBox3.ItemIndex := Combo_Spec.ItemIndex;
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

end.
