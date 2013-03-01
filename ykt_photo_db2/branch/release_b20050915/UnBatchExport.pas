unit UnBatchExport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Buttons, Db, ADODB, Grids, DBGrids, ComCtrls, Jpeg, FileCtrl;

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
    ComboBox1: TComboBox;
    DBGrid1: TDBGrid;
    ADOQuery1: TADOQuery;
    Memo1: TMemo;
    ADOQuery2: TADOQuery;
    Label5: TLabel;
    Label6: TLabel;
    ListBox1: TListBox;
    cb_ZDY: TCheckBox;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure Combo_academyChange(Sender: TObject);
    procedure Combo_SpecChange(Sender: TObject);
  private
    TempStringList: TStrings;
    TempDeptStringList: TStrings;
    TempKindStringList: TStrings;

    function GetCurrentSql: string;

    procedure RefreshKindList;
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
  ADOQuery2.SQL.Add('SELECT S_NAME,S_CODE FROM YKT_CUR.T_CIF_SPECIALITY');
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
      ComboBox3.Items.Add(ADOQuery2.fieldbyname('S_CODE').AsString);
      Combo_Spec.Items.Add(ADOQuery2.fieldbyname('S_NAME').AsString);
      ProgressBar1.Position := i + 1;
      ADOQuery2.Next;
    end;
  end;
  ProgressBar1.Position := 0;
  ADOQuery2.Close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('SELECT Dept_name,Dept_code FROM YKT_CUR.T_CIF_Dept');
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
      ComboBox2.Items.Add(ADOQuery2.fieldbyname('Dept_code').AsString);
      Combo_academy.Items.Add(ADOQuery2.fieldbyname('Dept_name').AsString);
      ProgressBar1.Position := i + 1;
      ADOQuery2.Next;
    end;
  end;
  ProgressBar1.Position := 0;
  ADOQuery2.Close;
end;


function TBatchExpot.GetCurrentSql: string;
begin
  Result := '';
  if Trim(Combo_academy.Text) <> '' then
  begin
    if Result = '' then Result := Result + ' M.DEPT_CODE=' + QuotedStr(Trim(ComboBox2.Items.Strings[Combo_academy.ItemIndex]))
    else Result := Result + ' and M.DEPT_CODE=' + QuotedStr(Trim(ComboBox2.Items.Strings[Combo_academy.ItemIndex]))
  end;
  if Trim(Combo_Spec.Text) <> '' then
  begin
    if Result = '' then Result := Result + ' S_code=' + QuotedStr(Trim(ComboBox3.Items.Strings[Combo_Spec.ItemIndex]))
    else Result := Result + ' and S_code=' + QuotedStr(Trim(ComboBox3.Items.Strings[Combo_Spec.ItemIndex]))
  end;
  if Trim(Edit1.Text) <> '' then
  begin
    if Result = '' then Result := Result + ' STUEMP_NO=' + QuotedStr(Trim(Edit1.Text))
    else Result := Result + ' and STUEMP_NO=' + QuotedStr(Trim(Edit1.Text));
  end;
  if Trim(ComboBox1.Text) <> '' then
  begin
    if Result = '' then Result := Result + ' Cut_type=' + QuotedStr(Trim(ComboBox1.Items.Strings[Combo_Spec.ItemIndex]))
    else Result := Result + ' and Cut_type=' + QuotedStr(Trim(ComboBox1.Items.Strings[Combo_Spec.ItemIndex]))
  end;
end;


procedure TBatchExpot.BitBtn1Click(Sender: TObject);
var TmpStr: string;
  CurrSql: string;
  i: integer;
begin
  ADOQuery1.Close;
  ADOQuery1.SQL.Clear;
  if cb_ZDY.Checked = false then
  begin
    TmpStr := GetCurrentSql;
    CurrSql := 'SELECT YKT_CUR.T_CIF_PHOTO.CUT_TYPE, YKT_CUR.T_CIF_PHOTO.STUEMP_NO, ' +
      'YKT_CUR.T_CIF_PHOTO.STUEMP_NAME, YKT_CUR.T_CIF_DEPT.DEPT_NAME,YKT_CUR.T_CIF_PHOTO.S_CODE,' +
      ' YKT_CUR.T_CIF_PHOTO.PHOTO_NO, YKT_CUR.T_CIF_PHOTO.FILENAME FROM YKT_CUR.T_CIF_PHOTO , YKT_CUR.T_CIF_DEPT ' +
      ' where YKT_CUR.T_CIF_DEPT.DEPT_CODE=YKT_CUR.T_CIF_PHOTO.DEPT_NAME';
    if Memo1.Text <> '' then
      if TmpStr <> '' then
        TmpStr := TmpStr + ' and ' + Memo1.Text
      else
        TmpStr := Memo1.Text;
    if Trim(TmpStr) = '' then
      ADOQuery1.SQL.Add(CurrSql)
    else
      ADOQuery1.SQL.Add(CurrSql + ' and ' + TmpStr);
  end;
  if cb_ZDY.Checked = true then
  begin
    ADOQuery1.SQL.Add(Memo1.Text);
  end;
  try
    ADOQuery1.Open;
    TempStringList.Clear;
    TempDeptStringList.Clear;
    TempKindStringList.Clear;
    Label6.Caption := Inttostr(ADOQuery1.recordcount);
    for i := 0 to ADOQuery1.RecordCount - 1 do
    begin
      TempStringList.Add(Trim(ADOQuery1.fieldbyname(PersonNo).Asstring));
      TempDeptStringList.Add(Trim(ADOQuery1.fieldbyname(PersonKindName2).Asstring));
      TempKindStringList.Add(Trim(ADOQuery1.fieldbyname(PersinKindNo3).Asstring));
      ADOQuery1.Next;
    end;
  except
    //ShowMessage('��ѯ���������ѯ����Ƿ���ȷ��');
  end;
end;

procedure TBatchExpot.FormCreate(Sender: TObject);
begin
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
  CurrDir: string;
  Dir1: string;
  Dir2: string;
  F3: TStringStream;
  M1: TMemoryStream;
  Fjpg: TJpegImage;
  DirPath1: string;
  DirPath3: string;
  Dir3: string;
begin
  if not ADOQuery1.Active then
    ShowMessage('���Ȳ�ѯ���ݣ�');

  if TempStringList.Count <= 0 then
    ShowMessage('���Ȳ�ѯ���ݣ�');
  if not DirectoryExists(NewDirPath) then
    if not createdir(NewDirPath) then
      raise exception.Create('���ܴ����ļ��У�' + NewDirPath);
  ADOQuery1.First;
  ProgressBar1.Min := 0;
  ProgressBar1.Max := TempStringList.Count;
  for i := 0 to TempStringList.Count - 1 do
  begin
    DirPath1 := NewDirPath + '\' + TempDeptStringList.Strings[i];
    DirPath3 := DirPath1 + '\' + TempKindStringList.Strings[i];
    Dir3 := TempStringList.Strings[i];

      //���浽���أ�
    if not DirectoryExists(DirPath1) then
      if not CreateDir(DirPath1) then
        raise Exception.Create('Cannot create ' + DirPath1);
      {
      //������רҵĿ¼��
      if not DirectoryExists(DirPath2) then
      if not CreateDir(DirPath2) then
      raise Exception.Create('Cannot create '+DirPath2);
      }
    if not DirectoryExists(DirPath3) then
      if not CreateDir(DirPath3) then
        raise Exception.Create('Cannot create ' + DirPath3);

    ADOQuery1.Close;
    ADOQuery1.SQL.Clear;
    ADOQuery1.SQL.Add('select * from ' + PhotoTableName + ' where ' +
      PersonNo + '=' + QuotedStr(TempStringList.Strings[i]));
    ADOQuery1.Open;

    Fjpg := TJpegImage.Create;
    M1 := TMemoryStream.Create;
    try
      M1.Clear;
      if TBlobField(AdoQuery1.FieldByName(PhotoRecord)).AsString <> null then
        TBlobField(AdoQuery1.FieldByName(PhotoRecord)).SaveToStream(M1);
      M1.Position := 0;
      if M1.Size > 100 then
      begin
        FJpg.LoadFromStream(M1);
        FJpg.SaveToFile(DirPath3 + '\' + Dir3 + '.jpg');
        //ShowMessage('��Ƭ�ڱ���λ���ǣ�'+DirPath3+'\'+Dir3+'.jpg');
      end
      else
      begin
        ListBox1.items.add('Ա���ţ�' + TempStringList.Strings[i] + '��Ϣ����ʧ�ܣ�');
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

end.

