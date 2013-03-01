unit UAPhoto1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Db, ADODB, Mask, DBCtrls, ExtCtrls, FileCtrl, inifiles, Jpeg,
  ComCtrls, DBTables, Grids, DBGrids, Menus;

type
  TPhotoSystem = class(TForm)
    ADOQuery1: TADOQuery; //��ѯ��ѧ����������¼��
    DataSource1: TDataSource; //�����������ݿ⣬
    Panel1: TPanel;
    Label1: TLabel;
    Panel2: TPanel;
    Label2: TLabel;
    Edit1: TEdit;
    Button1: TButton; //����ѯ����ť��
    Panel3: TPanel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Panel4: TPanel;
    Button2: TButton; //��ȡ��Ƭ����ť��
    Label8: TLabel;
    Edit2: TEdit;
    Label9: TLabel;
    Edit3: TEdit;
    Button3: TButton;
    Button4: TButton;
    Label7: TLabel;
    Edit4: TEdit;
    Button5: TButton;
    Panel5: TPanel;
    Image1: TImage; //������ʾ������Ƭ��
    Button6: TButton;
    Button7: TButton;
    Label10: TLabel;
    Label11: TLabel;
    Panel6: TPanel;
    Image2: TImage; //��ԭʼ��Ƭ��
    ADOQuery2: TADOQuery; //��������ѧ�Ų�ѯ��
    MainMenu1: TMainMenu; //�˵���
    file1: TMenuItem; //�������ѡ��˵���
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    DBEdit1: TDBEdit;
    DBEdit2: TDBEdit;
    Edit5: TEdit;
    DBEdit4: TDBEdit;
    Label16: TLabel;
    Label17: TLabel;
    Edit6: TEdit;
    ADOQuery3: TADOQuery; //��ȡרҵ���ƣ�
    ADOQuery4: TADOQuery; //ͳ��������Ƭ������
    Label18: TLabel;
    Label19: TLabel;
    count1: TMenuItem;
    Label20: TLabel;
    Label21: TLabel;
    N1: TMenuItem;
    N2: TMenuItem;
    ADOTable1: TADOTable;
    N3: TMenuItem;
    N4: TMenuItem;
    N5: TMenuItem;
    Label22: TLabel;
    L_Tnum: TLabel;
    lbl1: TLabel;
    lblstat: TLabel;
    {��ѯ}
    procedure Button1Click(Sender: TObject);
    {ȡ��Ƭ��}
    procedure Button2Click(Sender: TObject);
    {ȷ�ϣ�}
    procedure Button3Click(Sender: TObject);
    {ȡ����}
    procedure Button4Click(Sender: TObject);
    {��ʼ��ʱ����ȡ�����ļ���}
    procedure FormCreate(Sender: TObject);
    {�޸����˳��ţ�}
    procedure Button5Click(Sender: TObject);
    {ȷ���޸ģ�}
    procedure Button6Click(Sender: TObject);
    {ȡ���޸ģ�}
    procedure Button7Click(Sender: TObject);
    procedure Edit1KeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormClick(Sender: TObject);
    {��ʾǰ����һ��ͳ�ƣ�}
    procedure FormShow(Sender: TObject);
    {�����ύ����}
    procedure ADOQuery1PostError(DataSet: TDataSet; E: EDatabaseError;
      var Action: TDataAction);
    procedure ADOQuery1EditError(DataSet: TDataSet; E: EDatabaseError;
      var Action: TDataAction);
    procedure N2Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure N4Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
  private
    fn: string;
    NewNumberString2: string;
    mask1: string; //���˳��ţ�
    user1: string; //�������ݿ���û�����
    pwd1: string; //�������ݿ�����룬
    database1: string; //���ݿ�����

    FDeptName: string;
    FSpecName: string;
    FKindName: string;
    FPersonNo: string;

    {��ʼ��������Ϣ}
    procedure InitPrefaceInfo;

    procedure DeleteJPG;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  PhotoSystem: TPhotoSystem;

implementation

uses UASetCanon, UACount1, UDb, UtConfigs, UBatchImport, UnBatchExport;

{$R *.DFM}


procedure TPhotoSystem.InitPrefaceInfo;
begin
  Label1.width := 300;
  Label8.Width := 100;
  Label10.width := 200;
  PhotoSystem.Height := 740;
  Panel5.Width := 330;
  Panel5.Height := 440;
  Button6.Visible := False;
  Button7.Visible := False;
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  Button3.Visible := False;
  Button4.Visible := False;
  Edit5.Text := '';
  Edit6.Text := '';
  Edit4.Enabled := False;
  Button5.Enabled := False;
  Button2.Enabled := False;
  Label12.Caption := '';
  Label13.Caption := '';
  Label14.Caption := '';
  Label15.Caption := '';
  Label17.Caption := '';
  Label18.Caption := '';

  DBEdit1.DataField := PersonName;
  DBEdit2.DataField := PersonNo;
end;



{���в�ѯ��}

procedure TPhotoSystem.Button1Click(Sender: TObject);
var
  content: string;
  StuEmpNumber: string;
  F3: TADOBlobStream;
  M1: TMemoryStream; //�ڴ�����
  Fjpg: TJpegImage; //��Image ��� Jpeg ���м���ʽ��
  SpeCode: string; //רҵ���룬��Ժϵ���룬
  DeptCode: string; //���Ŵ���
  stat:Integer;
begin
  if Edit1.Text = '' then
  begin
    ShowMessage('�������ѧ����Ϊ�գ�');
    exit;
  end;
  Image1.Picture.Assign(nil);
  StuEmpNumber := Trim(Edit1.text);
  ADOQuery2.Close; //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  ADOQuery2.SQL.Clear;

  ADOQuery2.SQL.Add('SELECT * from ' + PersonTableName + '  where ' +
    PersonNo + '=' + QuotedStr(StuEmpNumber));
  ADOQuery2.Open;
  if ADOQuery2.RecordCount = 0 then
  begin
    ShowMessage('��ѧ���ż�¼�����ڣ�'); //����©����
    Edit1.Text := '';
    exit;
  end;

  DeptCode := ADOQuery2.FieldByName(PersonKindNo2).AsString;
  Label12.Caption := ADOQuery2.FieldByName(PersonName).AsString;
  Label13.Caption := ADOQuery2.FieldByName(PersonNo).AsString;
  Edit5.text := ADOQuery2.FieldByName(PersonKindNo2).AsString;
  SpeCode := ADOQuery2.FieldByName(PersonKindNo1).AsString;
  Label15.Caption := ADOQuery2.FieldByName(PersinKindNo3).AsString;
  FKindName := ADOQuery2.FieldByName(PersinKindNo3).AsString;
  stat:=ADOQuery2.FieldByName(status).asinteger;
  case stat of
    11: begin
          lblstat.Caption:='�ڶ�';
          lblstat.Font.Color:=clBlack;
        end;
    12: begin
          lblstat.Caption:='��У';
          lblstat.Font.Color:=clRed;
        end;
    13: begin
          lblstat.Caption:='��ҵ';
          lblstat.Font.Color:=clRed;
        end;
    21: begin
          lblstat.Caption:='��ְ';
          lblstat.Font.Color:=clBlack;
        end;
    22: begin
          lblstat.Caption:='����';
          lblstat.Font.Color:=clBlack;
        end;
    23: begin
          lblstat.Caption:='��ְ';
          lblstat.Font.Color:=clRed;
        end;
    24: begin
          lblstat.Caption:='����';
          lblstat.Font.Color:=clRed;
        end;
    25: begin
          lblstat.Caption:='����';
          lblstat.Font.Color:=clBlack;
        end;
    else lblstat.Caption:=' ';
  end;
  FPersonNo := StuEmpNumber;

  //----ȡ��רҵ��Ϣ------
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('select * from ' + SpecialTableName + ' where ' +
    PersonKindNo1 + '=' + QuotedStr(SpeCode));
  ADOQuery2.Open;
  Label17.Caption := ADOQuery2.FieldByName(PersonKindName1).AsString;
  Edit6.Text := Label17.Caption;
  FSpecName := ADOQuery2.FieldByName(PersonKindName1).AsString;
  //----ȡ��רҵ��Ϣ------

  //----ȡ�ò�����Ϣ------
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('select * from ' + DepartmentTableName + ' where ' +
    PersonKindNo2 + '=' + QuotedStr(DeptCode));
  ADOQuery2.Open;
  Label14.Caption := ADOQuery2.FieldByName(PersonKindName2).AsString;
  Edit5.Text := Label14.Caption;
  FDeptName := ADOQuery2.FieldByName(PersonKindNo2).AsString;
  //----ȡ�ò�����Ϣ------

  //��������ط��ж�ADOQuery1�����ã�ֻ���ȹر��������ܽ����޸ģ�
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select * from ' + PhotoTableName + ' where ' +
    PersonNo + '=' + QuotedStr(StuEmpNumber));
  ADOQuery1.Open;
  ADOQuery1.Edit;
  Label20.Caption := ADOQuery1.FieldByName(PhotoDateRecord).AsString;
  Label21.Caption:=ADOQuery1.fieldbyname('photo_time').asstring;
  Button5.Enabled := True;
  Button2.Enabled := True;
  Label12.Width := 180;

  F3 := TADOBlobStream.Create(TBlobField(ADOQuery1.fieldbyname(PhotoRecord)), bmread);
  try
    //F3.Clear;
    if TBlobField(AdoQuery1.FieldByName(PhotoRecord)).AsString <> null then
      TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(F3);

    Fjpg := TJpegImage.Create;
    try
      F3.Position := 0;
      image2.Picture.Graphic := nil;
      if F3.Size > 100 then
      begin
        FJpg.LoadFromStream(F3);
        image2.Picture.Graphic := FJpg;
      end
      else
      begin
        Panel6.Caption := 'û��ԭʼ��Ƭ';
      end;
    finally
      Fjpg.Free;
    end;
  finally
    F3.Destroy; ;
  end;

end;

procedure TPhotoSystem.Button2Click(Sender: TObject);
var
  currentNum1: string;
  NewNumber2: string;
  fileNamePath2: string;
begin
  //2005-04-27�޸�
  {OldNumber2 := '';
  currentNum1 := Trim(Edit4.Text); //����ͻ��ڽ������޸ģ������ش������ļ��޸ģ�
  NewNumberString2 := currentNum1;
  while FileExists(OldDirPath + '\' + Pre + NewNumberString2 + '.jpg') do
  begin
    //if FileExists(OldDirPath + '\' + Pre + OldNumber2 + '.jpg') then
      //DeleteFile(OldDirPath + '\' + Pre + OldNumber2 + '.jpg');
    OldNumber2 := NewNumberString2;
    NewNumber2 := IntToStr(StrToInt(OldNumber2) + 1);
    NewNumber2 := '0000000000' + NewNumber2;
    NewNumberString2 := Copy(NewNumber2, (Length(NewNumber2) - NumberLen + 1), NumberLen);
  end;
  if FileExists(OldDirPath + '\' + Pre + OldNumber2 + '.jpg') then
  begin
    Image1.Picture.LoadFromFile(OldDirPath + '\' + Pre + OldNumber2 + '.jpg'); //���ж��ļ��Ƿ���ڣ�
    Edit2.Text := Pre + OldNumber2 + '.jpg';
    Edit3.Text := DBEdit2.Text + '.jpg';
    Button3.Visible := True;
    Button4.Visible := True;
  end
  else
    ShowMessage('����Ƭ�����ڣ����鲢"�޸����˳���",��Ҫʱ���ֶ��޸������ļ�..\file.ini ��ֵ��'); }
  if FileExists(OldDirPath + '\' + Pre + Trim(Edit4.text) + '.jpg') then
  begin
    Image1.Picture.LoadFromFile(OldDirPath + '\' + Pre + Trim(Edit4.text) + '.jpg'); //���ж��ļ��Ƿ���ڣ�
    Edit2.Text := Pre + Trim(Edit4.text) + '.jpg';
    Edit3.Text := DBEdit2.Text + '.jpg';
    Button3.Visible := True;
    Button4.Visible := True;
  end
  else
    ShowMessage('����Ƭ�����ڣ����鲢"�޸����˳���",��Ҫʱ���ֶ��޸������ļ�..\file.ini ��ֵ��');
end;

{������Ƭ��}

procedure TPhotoSystem.Button3Click(Sender: TObject);
var
  F: TFileStream;
  F2: TFileStream;
  OldNumber: string;
  NewNumber: string;
  NewNumberString: string;
  fileNamePath: string;
  DirPath1: string;
  DirPath2: string;
  DirPath3: string;
  j: integer; //������������Ŀ
  my: TIniFile;
  FJpeg: TJpegImage;
  M1: TMemoryStream; //�ڴ�����
  Saved1: bool;
  ShowSaved2: bool;
begin
  //���浽���ݿ⣬
  try
    //F := TFileStream.Create(OldDirPath + '\' + Pre + OldNumber2 + '.jpg', fmOpenRead);
    //2005-04-27�޸�
    F := TFileStream.Create(OldDirPath + '\' + Pre + Trim(Edit4.text) + '.jpg', fmOpenRead);
    FJpeg := TJpegImage.Create;
    //�㡰��ѯ���� ��ADOQuery1 �Ѿ������ݣ��Ҵ���
    FJpeg.Assign(Image1.Picture.Graphic);
    image1.Picture.Graphic.SaveToStream(F);
    F.Position := 0;
    ADOQuery1.Edit;
    try
      TBlobField(ADOQuery1.FieldByName(PhotoRecord)).loadfromStream(F);
    finally
      M1 := TMemoryStream.Create;
      TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(M1);
      //�����Ƭ��С�������ݿ�Blob�ֶδ�С 500k,����ʧ�ܣ�
      if M1.Size > 600000 then
      begin
        ShowMessage(' ͼƬ���� ');
        Saved1 := False;
      end;
    end;
    ADOQuery1.FieldByName(PhotoDateRecord).Value := FormatDateTime('YYYY-MM-DD',Date);
    ADOQuery1.FieldByName(PhotoTimeRecord).Value := FormatDateTime('HH:MM:SS',Time);
    if Trim(Edit5.Text) <> '' then
      ADOQuery1.FieldByName(SaveFileName).value := Edit5.Text + '\'+Label15.Caption+'\' + Label13.Caption + '.jpg'
    else
      ADOQuery1.FieldByName(SaveFileName).value := Label15.Caption+'\' +Label13.Caption + '.jpg';

    if Trim(Edit5.Text) <> '' then
      DirPath1 := NewDirPath + '\' + Edit5.Text
    else DirPath1 := NewDirPath;
    if Trim(FKindName) <> '' then
      DirPath3 := DirPath1 + '\' + FKindName
    else DirPath3 := DirPath1;
    ADOQuery1.Post;
    ShowMessage(' �ڱ�����Ƭλ���ǣ�' + NewDirPath + '\' + ADOQuery1.FieldByName('FILENAME').AsString);
    //���浽���أ�
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
    TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(F2);
  finally
    ADOQuery1.Close;
    F.Free;
    F2.Free;
  end;
  //DeleteFile(OldDirPath + '\' + Pre + OldNumber2 + '.jpg');
  if FileExists(OldDirPath + '\' + Pre +Trim(Edit4.Text) + '.jpg') then
    DeleteFile(OldDirPath + '\' + Pre +Trim(Edit4.Text)+'.jpg');
  Edit4.Text := OldNumber1;
  Edit2.Text := '';
  Edit3.Text := '';
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  Button3.Visible := False;
  Button4.Visible := False;

  //�ӽ����ϣ������һ����¼�Ĺ��̣�
  Label12.Caption := '';
  Label13.Caption := '';
  Label14.Caption := '';
  Label17.Caption := '';
  Label15.Caption := '';
  Edit5.Text := '';
  Image1.Picture.Assign(nil);
  Button5.Enabled := False;
  Button2.Enabled := False;

  //ͳ��������Ƭ����
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  ADOQuery4.SQL.Add('select Count(' + PersonNo + ') from ' + PhotoTableName +
    ' where ' + SaveFileName + '<>' + QuotedStr(''));
  ADOQuery4.Open;
  ADOQuery4.first;
  Label18.Caption := IntToStr(ADOQuery4.Fields[0].AsInteger);
  //ͳ�Ƶ�������Ƭ����
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  ADOQuery4.SQL.Add('select Count(' + PersonNo + ') from ' + PhotoTableName +
    ' where ' + SaveFileName + '<>' + QuotedStr('') + ' and photo_date=' + QuotedStr(FormatDateTime('yyyy-mm-dd', Date)));
  ADOQuery4.Open;
  ADOQuery4.first;
  L_Tnum.Caption := IntToStr(ADOQuery4.Fields[0].AsInteger);
  ADOQuery4.Close;
  ADOQuery1.Close;

  //DeleteJPG;
end;

{���¡�ȡ������ťʱ}

procedure TPhotoSystem.Button4Click(Sender: TObject);
var
  content: string;
  F: file;
  my: TInifile;
begin
  {try
    AssignFile(F, OldDirPath + '\' + Pre + OldNumber2 + '.jpg'); //�ӹ������� ɾ����Ƭ�ļ�����ɾ����Ƭ���ļ�����
    Reset(F);
    CloseFile(F);
    Erase(F);
  except
    ShowMessage('ɾ����Ƭ����');
  end;}
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  Label8.Visible := False;
  Label9.Visible := False;
  Edit2.Visible := False;
  Edit3.Visible := False;
  Button3.Visible := False;
  Button4.Visible := False;
  //�ӽ����ϣ������һ����¼�Ĺ��̣�
  Label12.Caption := '';
  Label13.Caption := '';
  Label14.Caption := '';
  Label17.Caption := '';
  Label15.Caption := '';
  Edit5.Text := '';
  Image1.Picture.Assign(nil);
  Button5.Enabled := False;
  Button2.Enabled := False;
  //my.WriteString('CANON', 'CURRENTNUM', OldNumber1);
  Edit4.Text := OldNumber1;
end;

procedure TPhotoSystem.FormCreate(Sender: TObject);
var
  i: integer;
  temp1: string;
  count1: integer;
  j: integer; //������������Ŀ
  my: TInifile;
begin
  GetConfigs;
  ConfigConnectDB;

  InitPrefaceInfo;
  Edit4.Text := OldNumber1;
end;

procedure TPhotoSystem.Button5Click(Sender: TObject);
begin
  Button5.Visible := False;
  Edit4.Enabled := True;
  Button2.Enabled := False;
  Button6.Visible := True;
  Button7.Visible := True;
  mask1 := Edit4.Text;
end;

procedure TPhotoSystem.Button6Click(Sender: TObject);
begin
  Button2.Enabled := True;
  Button6.Visible := False;
  Button7.Visible := False;
  Button5.Visible := True;
  Edit4.Enabled := False;
end;

procedure TPhotoSystem.Button7Click(Sender: TObject);
begin
  Button2.Enabled := True;
  Button6.Visible := False;
  Button7.Visible := False;
  Button5.Visible := True;
  Edit4.Enabled := False;
  Edit4.Text := mask1;
end;


procedure TPhotoSystem.Edit1KeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 13) and (Edit1.Text <> '') then
    Button1Click(nil);
end;

procedure TPhotoSystem.FormMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  PhotoSystem.Align := alNone;
end;

procedure TPhotoSystem.FormClick(Sender: TObject);
begin
  PhotoSystem.Align := alNone;
end;

procedure TPhotoSystem.FormShow(Sender: TObject);
var
  j: integer; //������������Ŀ
begin
  //ͳ��������Ƭ����
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  ADOQuery4.SQL.Add('select Count(' + PersonNo + ') from ' + PhotoTableName +
    ' where ' + SaveFileName + '<>' + QuotedStr(''));
  ADOQuery4.Open;
  ADOQuery4.first;
  j := 0;
  j := ADOQuery4.Fields[0].AsInteger;
  Label18.Caption := IntToStr(j);

  //ͳ�ƽ���������Ƭ����
  ADOQuery4.Close;
  ADOQuery4.SQL.Clear;
  ADOQuery4.SQL.Add('select Count(' + PersonNo + ') from ' + PhotoTableName +
    ' where ' + SaveFileName + '<>' + QuotedStr('')+' and photo_date='+#39+FormatDateTime('yyyy-mm-dd',Date())+#39);
  ADOQuery4.Open;
  ADOQuery4.first;
  L_Tnum.Caption := IntToStr(ADOQuery4.Fields[0].AsInteger);
end;


{ͳ�Ʊ���}

procedure TPhotoSystem.ADOQuery1PostError(DataSet: TDataSet;
  E: EDatabaseError; var Action: TDataAction);
var iDBIError: Integer;
begin
  if (E is EDBEngineError) then
  begin
    iDBIError := (E as EDBEngineError).Errors[0].Errorcode;
    showmessage('post err' + inttostr(iDBIError));
  end;
end;

procedure TPhotoSystem.ADOQuery1EditError(DataSet: TDataSet;
  E: EDatabaseError; var Action: TDataAction);
begin
  ShowMessage(' �޸ļ�¼ʧ�ܣ� ');
end;

procedure TPhotoSystem.N2Click(Sender: TObject);
var
  i: integer;
  startNumber2: string;
  temp2: string;
  my: TInifile;
begin
  SetOption := TSetOption.Create(nil);
  SetOption.ShowModal;
  if SetOption.ModalResult = mrOk then
  begin
    if (SetOption.Edit8.Text = '') or (SetOption.Edit3.Text = '') or (SetOption.Edit4.Text = '') or (SetOption.Edit2.Text = '') or (SetOption.Edit5.Text = '') then
    begin
      ShowMessage('����д����');
      exit;
    end;
    my := TIniFile.Create(ChangeFileExt('file', '.ini'));
    try
      if SetOption.Edit8.Text <> '' then
        my.WriteString('FILEDIR', 'PRENAME', Trim(SetOption.Edit8.Text) + '_');
      if SetOption.Edit3.Text <> '' then
        my.WriteString('FILEDIR', 'NUMBER', Trim(SetOption.Edit3.Text));
      if SetOption.Edit4.Text <> '' then
        my.WriteString('FILEDIR', 'STARTNUM', Trim(SetOption.Edit4.Text));
      if SetOption.Edit2.Text <> '' then
        my.WriteString('FILEDIR', 'OLDDIR', Trim(SetOption.Edit2.Text));
      if SetOption.Edit5.Text <> '' then
        my.WriteString('FILEDIR', 'NEWDIR', Trim(SetOption.Edit5.Text));

      //�����ļ��޸��ˣ�Ҫ����Ӧ���޸�
      OldDirPath := my.ReadString('FILEDIR', 'OLDDIR', '');
      NewDirPath := my.ReadString('FILEDIR', 'NEWDIR', '');
      Pre := my.ReadString('FILEDIR', 'PRENAME', '');
      NumberLen := my.ReadInteger('FILEDIR', 'NUMBER', 0);
      StartNum := my.ReadString('FILEDIR', 'STARTNUM', '');
      temp2 := '0000000000' + StartNum;
      startNumber2 := Copy(temp2, (Length(temp2) - NumberLen + 1), NumberLen);
      my.WriteString('CANON', 'INITNUM', startNumber2);
      initNumber := my.ReadString('CANON', 'INITNUM', '');
      my.WriteString('CANON', 'CURRENTNUM', startNumber2);
      addLength := my.ReadInteger('CANON', 'LENGTH', 0);
      OldNumber1 := my.ReadString('CANON', 'INITNUM', '');
      Edit4.Text := my.ReadString('CANON', 'INITNUM', '');
    finally
      my.Free;
    end;
  end;
  SetOption.free;
end;

procedure TPhotoSystem.N1Click(Sender: TObject);
var
  departName1: string;
  departCode1: string;
  deptPeopleAll: integer;
  photoedCount: integer; //���Ĺ���������
  unPhoCount: integer; //δ�Ĺ���������
begin
  ReportCount1 := TReportCount1.Create(nil);
  try
    ReportCount1.ShowModal;
  finally
    ReportCount1.free;
  end;
end;

procedure TPhotoSystem.N4Click(Sender: TObject);
begin
  BatchExpot := TBatchExpot.Create(Application);
  try
    BatchExpot.ShowModal;
  finally
    BatchExpot.Free;
  end;
end;

procedure TPhotoSystem.N5Click(Sender: TObject);
begin
  BatchImport := TBatchImport.Create(Application);
  try
    BatchImport.ShowModal;
  finally
    BatchImport.Free;
  end;
end;

procedure TPhotoSystem.DeleteJPG;
var
  s: string;
  SearchRec: TSearchRec;
begin
  FindFirst(OldDirPath + '\*.JPG', faAnyFile, SearchRec);
  repeat
    s := SearchRec.Name;
    if SearchRec.Attr <> faDirectory then
    begin
      FileSetAttr(SearchRec.Name, 0); //�޸��ļ�����Ϊ��ͨ����ֵ
      DeleteFile(OldDirPath + '\' + SearchRec.Name); //ɾ���ļ�
    end;
  until (FindNext(SearchRec) <> 0);
  FindClose(SearchRec);
end;

end.

