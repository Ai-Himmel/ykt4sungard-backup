unit UBatchImport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, DBGrids, Db, ADODB, StdCtrls, FileCtrl, ExtCtrls, Jpeg, ComCtrls,
  phtIfRepalce;

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

    FOldJPEG, FNewJPEG: TJPEGImage; // add by zhf
    FReply: TphtReply;

    ErrorPersonNo: TStrings;
    ErrorPersonName: TStrings;
    { Private declarations }
    function getNum(s: string) : string;
  public
    { Public declarations }
  end;

var
  BatchImport: TBatchImport;

implementation

uses udb, UtConfigs;

{$R *.DFM}

function TBatchImport.getNum(s: string) : string;
var
  i: Integer;
  temps : string;
begin
  for i := 1  to Length(s)  do
  begin
    if (s[i] in ['0'..'9']) then
    begin
      temps := temps + s[i];
    end;
  end;
  result := temps;
end;

procedure TBatchImport.Button1Click(Sender: TObject);
var i: Integer;
  FCurrentSetDir: string;
  FFileName: string;
  FJpeg: TJpegImage;
  F: TFileStream;
  BS: TADOBlobStream;
  M1: TMemoryStream;
  DirPath1: string;
  DirPath3: string;
  F2: TFileStream;
  FCurrentFileName: string;

  J: Integer; // 1 to 4 add by zhf  050531
  CurDir: string;
  FailDir: string;
  SkipDir: string;
begin
  if FileListBox1.Items.Count = 0 then
  begin
    ShowMessage('没有照片可以批量导入');
    Exit;
  end;
  ProgressBar1.Position := 0;
  ProgressBar1.Min := 0;
  Label13.Caption := IntToStr(FileListBox1.Items.Count);

  FReply := rpNone;

  // add by zhf 20050531
  ListBox1.Items.Clear;
  // 导入时，失败及跳过照片存于'未导入照片'目录中
  CurDir := DirectoryListBox1.Directory;
  FailDir := CurDir + '\导入失败照片';
  SkipDir := CurDir + '\导入跳过照片';
  CreateDir(FailDir);
  CreateDir(SkipDir);
  // end of add

  ProgressBar1.Max := FileListBox1.Items.Count;
  for i := 0 to FileListBox1.Items.Count - 1 do
  begin
    Label11.Caption := IntToStr(i + 1);
    ProgressBar1.Position := i + 1;

    FCurrentSetDir := DirectoryListBox1.Directory;
    FFileName := Trim(FileListBox1.Items.Strings[i]);
    //FPersonNo := Trim(Copy(FFileName, 1, Pos('.', FFileName) - 1));
    FPersonNo:=getNum(FFileName);
    { // ni xiang gan shen me, mei jian guo zhe me bian ma de
    if LowerCase(ExtractFileExt(DirectoryListBox1.Directory + '\' + FFileName)) <> '.jpg' then
    begin
      ListBox1.Items.Add('文件名：' + DirectoryListBox1.Directory + '\' + FFileName + '不是正确的图片文件！导入失败！');
      Continue;
    end;
    }
    ADOQuery1.Close;
    ADOQuery1.SQL.Clear;
    ADOQuery1.SQL.Add('select '+cuttype+','+stuempno+','+stuempname+','+deptname+','+scode+','+sexname+','+
      id2+','+deptcode+','+indate+','+photo+','+filename+','+photodate+','+phototime+' from ' + PhotoTableName + ' where ' +
      StuEmpNo+'='+QuotedStr(FPersonNo));

    //try
      ADOQuery1.Open;
    //except
    //end;
    if ADOQuery1.IsEmpty then
    begin
      ErrorPersonNo.Add(StuEmpNo);
      ErrorPersonName.Add('');
      ListBox1.Items.Add('学号(工号)为：' + QuotedStr(FPersonNo) + '的人员基本信息不存在, 导入失败!');
      ADOQuery1.Recordset.Close;
      ADOQuery1.Close;

      CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);   // add by zhf 050531

      Continue;
    end;

    FPersonName := ADOQuery1.FieldByName(StuempName).AsString;
    FDeptNo := ADOQuery1.FieldByName(SCode).AsString;
    FSpecNo := ADOQuery1.FieldByName(DeptCode).AsString;
    FKindName := ADOQuery1.FieldByName(CutType).AsString;
    FDeptName := ADOQuery1.FieldByName(deptname).AsString;
    Label3.Caption := FPersonNo;
    Label4.Caption := FPersonName;
    Label7.Caption := FDeptName;
    //----取得院系信息------
    {FDeptName := '';
    ADOQuery2.Close;
    ADOQuery2.SQL.Clear;
    ADOQuery2.SQL.Add('select '+stuempno+','+stuempname+','+deptname+','+scode+'  from ' + DepartmentTableName + ' where ' +
      BanchCode + '=' + QuotedStr(FDeptNo));
      ADOQuery2.SQL.SaveToFile('123.txt');
    ADOQuery2.Open;
    if ADOQuery2.RecordCount > 0 then
    begin
      FDeptName := ADOQuery2.FieldByName(SCode).AsString;
    end
    else
    begin
      ADOQuery2.Recordset.close;
      ADOQuery2.Close;
    end;}

    // add by zhf 050422
    if (FReply <> rpAllReplace) and
        (not AdoQuery1.FieldByName(Photo).IsNull) then
    begin

      BS := TADOBlobStream.Create(TBlobField(AdoQuery1.FieldByName(Photo)),
          bmread);
      TBlobField(AdoQuery1.FieldByName(Photo)).SaveToStream(BS);
      BS.Position := 0;
      if BS.Size > 100 then
        FOldJPEG.LoadFromStream(BS);

      try
        FNewJPEG.LoadFromFile(FFileName);
      except
        ListBox1.Items.Add('学号为：' + FPersonNo + '的图片格式错误, 导入失败! ');
        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);   // add by zhf 050531
        Continue;
      end;

      FReply := frmIfRepalce.GetReply(FPersonNo, FOldJPEG, FNewJPEG);

      //BS.Destroy;
      //ListBox1.Items.Add('学号为：' + FPersonNo + '的图片已经存在于数据库！');
      case FReply of
        rpReplace: ;

        rpSkip:
        begin
          ///ADOQuery1.Recordset.Close;
          ///ADOQuery1.Close;
          CopyFile(PChar(CurDir+'\'+FFileName), PChar(SkipDir+'\'+FFileName), false);   // add by zhf 050531
          Continue;
        end;
        rpCancel:
        begin
          // add by zhf 050531
          for J := I to FileListBox1.Items.Count - 1 do
          begin
            FFileName := Trim(FileListBox1.Items.Strings[J]);
            CopyFile(PChar(CurDir+'\'+FFileName), PChar(SkipDir+'\'+FFileName), false);   // add by zhf 050531
          end;
          // end of add
          Break;
        end;

      end;
    end;
    // end of add

    //----取得院系信息------
    ADOQuery1.Edit;
    // F := TFileStream.Create(FCurrentSetDir + '\' + FPersonNo+FPersonName + '.jpg', fmOpenRead);
    F := TFileStream.Create(FCurrentSetDir + '\' + FFileName, fmOpenRead);
    F.Position := 0;
    try
      TBlobField(ADOQuery1.FieldByName(Photo)).loadfromStream(F);
      M1 := TMemoryStream.Create;
      TBlobField(AdoQuery1.FieldByName(Photo)).SaveToStream(M1);
      //如果照片大小超过数据库Blob字段大小 500k,保存失败，
      if M1.Size > 600000 then
      begin
        ListBox1.Items.Add('学号为：' + FPersonNo + '的图片信息过大, 导入失败! ');

        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);   // add by zhf 050531

        Continue;
      end;

      if Trim(FKindName) <> '' then
        ADOQuery1.FieldByName(FileName).value := FKindName + '\' + FPersonNo + '.jpg'
      else
        ADOQuery1.FieldByName(FileName).value := FPersonNo + '.jpg';
      if Trim(FDeptName) <> '' then
        ADOQuery1.FieldByName(FileName).value := FDeptName + '\' + ADOQuery1.FieldByName(FileName).value
      else
        ADOQuery1.FieldByName(FileName).value := ADOQuery1.FieldByName(FileName).value;

      if Trim(FDeptName) <> '' then
        DirPath1 := NewDirPath + '\' + FKindName
      else DirPath1 := NewDirPath;
      if Trim(FKindName) <> '' then
        DirPath3 := DirPath1 + '\' + FDeptName
      else DirPath3 := DirPath1;

      FPersonName := ADOQuery1.FieldByName(StuempName).AsString;
      ADOQuery1.FieldByName(SCode).AsString := FDeptNo;
      ADOQuery1.FieldByName(DeptCode).AsString := FSpecNo;
      ADOQuery1.FieldByName(CutType).AsString := FKindName;
      ADOQuery1.FieldByName(PhotoDate).Value := FormatDateTime('yyyy-mm-dd',dtp_date.date);//'2004-12-31';// cur to 2 exchange by zhf
      ADOQuery1.FieldByName(PhotoTime).Value := FormatDateTime('hh-nn-ss',dtp_date.time);// '12:12:30'
      Label9.Caption := ADOQuery1.FieldByName(FileName).AsString;
      try
        ADOQuery1.Post;
      except
        ErrorPersonNo.Add(FPersonNo + '的图片信息导入失败!');
        ErrorPersonName.Add(FPersonName);
        ListBox1.Items.Add(FPersonNo + '的图片信息导入失败!');

        CopyFile(PChar(CurDir+'\'+FFileName), PChar(FailDir+'\'+FFileName), false);   // add by zhf 050531

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
        TBlobField(AdoQuery1.FieldByName(Photo)).SaveToStream(F2);
      finally
        F2.Free;
      end;
    finally
      F.Free;
      M1.Free;
    end;
  end; // of for

  // add by zhf 050531 | if _Dir is empty, then remove
  RemoveDir(FailDir);
  RemoveDir(SkipDir);
  // end of add

  ProgressBar1.Position := 0;
end;

procedure TBatchImport.FormCreate(Sender: TObject);
begin
  ErrorPersonNo := TStringList.Create;
  ErrorPersonName := TStringList.Create;

  FOldJPEG := TJPEGImage.Create;
  FNewJPEG := TJPEGImage.Create;
end;

procedure TBatchImport.FormDestroy(Sender: TObject);
begin
  ErrorPersonNo.Free;
  ErrorPersonName.Free;

  FOldJPEG.Free;
  FNewJPEG.Free;
end;

procedure TBatchImport.Button2Click(Sender: TObject);
begin
  close;
end;

end.
