unit UBatchImport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, Db, ADODB, StdCtrls, FileCtrl, ExtCtrls, Jpeg, ComCtrls;

type
  TBatchImport = class(TForm)
    DataSource1: TDataSource;
    Panel1: TPanel;
    Label1: TLabel;
    DirectoryListBox1: TDirectoryListBox;
    FileListBox1: TFileListBox;
    DriveComboBox1: TDriveComboBox;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Button1: TButton;
    Button2: TButton;
    dtp_date: TDateTimePicker;
    Label10: TLabel;
    dtp_time: TDateTimePicker;
    ADOQuery2: TADOQuery;
    ProgressBar1: TProgressBar;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    ADOQuery1: TADOQuery;
    ListBox1: TListBox;
    Label14: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    FBootDir: string;
    FDeptName: string;
    FDeptNo: string;
    FSpecName: string;
    FSpecNo: string;
    FKindName: string;
    FPersonName: string;
    FPersonNo: string;

    ErrorPersonNo: TStrings;
    ErrorPersonName: TStrings;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  BatchImport: TBatchImport;

implementation

uses udb, UtConfigs;

{$R *.DFM}

procedure TBatchImport.Button1Click(Sender: TObject);
var i: Integer;
  FCurrentSetDir: string;
  FFileName: string;
  FJpeg: TJpegImage;
  F: TFileStream;
  M1: TMemoryStream;
  DirPath1: string;
  DirPath3: string;
  F2: TFileStream;
  FCurrentFileName: string;
begin
  if FileListBox1.Items.Count = 0 then
  begin
    ShowMessage('没有照片可以批量导入');
    Exit;
  end;
  ProgressBar1.Position := 0;
  ProgressBar1.Min := 0;
  Label13.Caption := IntToStr(FileListBox1.Items.Count);

  ProgressBar1.Max := FileListBox1.Items.Count;
  for i := 0 to FileListBox1.Items.Count - 1 do
  begin
    Label11.Caption := IntToStr(i + 1);
    ProgressBar1.Position := i + 1;

    FCurrentSetDir := DirectoryListBox1.Directory;
    FFileName := LowerCase(Trim(FileListBox1.Items.Strings[i]));
    FPersonNo := Trim(Copy(FFileName, 1, Pos('.', FFileName) - 1));
    if LowerCase(ExtractFileExt(DirectoryListBox1.Directory + '\' + FFileName)) <> '.jpg' then
    begin
      ListBox1.Items.Add('文件名：' + DirectoryListBox1.Directory + '\' + FFileName + '不是正确的图片文件！导入失败！');
      Continue;
    end;

    ADOQuery1.Close;
    ADOQuery1.SQL.Clear;
    ADOQuery1.SQL.Add('select * from ' + PhotoTableName + ' where ' +
      PersonNo + '=' + QuotedStr(FPersonNo));
    try
      ADOQuery1.Open;
    except
    end;
    if ADOQuery1.RecordCount = 0 then
    begin
      ErrorPersonNo.Add(PersonNo);
      ErrorPersonName.Add('');
      ListBox1.Items.Add('学号为：' + FPersonNo + '的图片信息不存在导入失败！');
      Continue;
    end;
    FPersonName := ADOQuery1.FieldByName(PersonName).AsString;
    FDeptNo := ADOQuery1.FieldByName(PersonKindNo2).AsString;
    FSpecNo := ADOQuery1.FieldByName(PersonKindNo1).AsString;
    FKindName := ADOQuery1.FieldByName(PersinKindNo3).AsString;
    Label3.Caption := FPersonNo;
    Label4.Caption := FPersonName;
    Label7.Caption := FDeptName;

{    //----取得专业信息------
    ADOQuery2.Close;
    ADOQuery2.SQL.Clear;
    ADOQuery2.SQL.Add('select * from '+SpecialTableName+' where '+
         PersonKindNo1+'='+QuotedStr(FSpecNo));
    ADOQuery2.Open;
    FSpecName:= ADOQuery2.FieldByName(PersonKindName1).AsString;
    //----取得专业信息------
}
    //----取得院系信息------
    FDeptName := '';
    ADOQuery2.Close;
    ADOQuery2.SQL.Clear;
    ADOQuery2.SQL.Add('select * from ' + DepartmentTableName + ' where ' +
      PersonKindNo2 + '=' + QuotedStr(FDeptNo));
    ADOQuery2.Open;
    if ADOQuery2.RecordCount > 0 then
      FDeptName := ADOQuery2.FieldByName(PersonKindName2).AsString;
    ADOQuery2.Close;
    //----取得院系信息------

    ADOQuery1.Edit;
    F := TFileStream.Create(FCurrentSetDir + '\' + FPersonNo + '.jpg', fmOpenRead);
    F.Position := 0;
    try
      TBlobField(ADOQuery1.FieldByName(PhotoRecord)).loadfromStream(F);

      M1 := TMemoryStream.Create;
      TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(M1);
      //如果照片大小超过数据库Blob字段大小 500k,保存失败，
      if M1.Size > 600000 then
      begin
        ListBox1.Items.Add('学号为：' + FPersonNo + '的图片信息过大导入失败！');
        Continue;
      end;

      if Trim(FKindName) <> '' then
        ADOQuery1.FieldByName(SaveFileName).value := FKindName + '\' + FPersonNo + '.jpg'
      else
        ADOQuery1.FieldByName(SaveFileName).value := FPersonNo + '.jpg';
      if Trim(FDeptName) <> '' then
        ADOQuery1.FieldByName(SaveFileName).value := FDeptName + '\' + ADOQuery1.FieldByName(SaveFileName).value
      else
        ADOQuery1.FieldByName(SaveFileName).value := ADOQuery1.FieldByName(SaveFileName).value;

      if Trim(FDeptName) <> '' then
        DirPath1 := NewDirPath + '\' + FDeptName
      else DirPath1 := NewDirPath;
      if Trim(FKindName) <> '' then
        DirPath3 := DirPath1 + '\' + FKindName
      else DirPath3 := DirPath1;
      
      FPersonName := ADOQuery1.FieldByName(PersonName).AsString;
      //ADOQuery1.FieldByName(PersonKindName2).AsString := FDeptNo;
      //ADOQuery1.FieldByName(PersonKindNo1).AsString := FSpecNo;
      //ADOQuery1.FieldByName(PersinKindNo3).AsString := FKindName; QuotedStr
      ADOQuery1.FieldByName(PhotoDateRecord).asstring :=(FormatDateTime('yyyy-mm-dd',dtp_date.Date));
      ADOQuery1.FieldByName(PhotoTimeRecord).asstring := (FormatDateTime('hh:mm:ss',dtp_time.time));
      Label9.Caption := ADOQuery1.FieldByName(SaveFileName).AsString;
      try
        ADOQuery1.Post;
      except
        ErrorPersonNo.Add(FPersonNo + '的图片信息导入失败！');
        ErrorPersonName.Add(FPersonName);
        ListBox1.Items.Add(FPersonNo + '的图片信息导入失败！');
        continue;
      end;

      {创建本地路径}
      if not DirectoryExists(NewDirPath) then
        if not CreateDir(NewDirPath) then
          raise Exception.Create('Cannot create ' + NewDirPath);
      if not DirectoryExists(DirPath1) then
        if not CreateDir(DirPath1) then
          raise Exception.Create('Cannot create ' + DirPath1);

      if not DirectoryExists(DirPath3) then
        if not CreateDir(DirPath3) then
          raise Exception.Create('Cannot create ' + DirPath3);

      F2 := TFileStream.Create(DirPath3 + '\' + FPersonNo + '.jpg', fmCreate);
      try
        TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(F2);
      finally
        F2.Free;
      end;
    finally
      F.Free;
      M1.Free;
    end;
  end;
  ProgressBar1.Position := 0;
end;

procedure TBatchImport.FormCreate(Sender: TObject);
begin
  ErrorPersonNo := TStringList.Create;
  ErrorPersonName := TStringList.Create;
  dtp_date.Date:=Date();
  dtp_time.Time:=Now();
end;

procedure TBatchImport.FormDestroy(Sender: TObject);
begin
  ErrorPersonNo.Free;
  ErrorPersonName.Free;
end;

procedure TBatchImport.Button2Click(Sender: TObject);
begin
  close;
end;

end.
