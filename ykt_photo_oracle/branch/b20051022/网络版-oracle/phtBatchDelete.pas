unit phtBatchDelete;
     
{ ***********************************************************************
  Copyright (c) 2005 �Ϻ��������˴��������޹�˾
  ��    ��: ����ɾ��������Ϣ
  ��    ��: Haifeng Zhu
  ��������: '2005-05-30'
  �޸�����:
  ��    ��: Ver 1.0
  ��    ��:
  ************************************************************************ }

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, Grids, DBGridEh, Db, ADODB, DBGridEhImpExp, DBTables;

type
  TfrmBatchDelete = class(TForm)
    lblTotlal: TLabel;
    GroupBox1: TGroupBox;
    Label6: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    edtNum: TEdit;
    cbDept: TComboBox;
    edtName: TEdit;
    cbSubDept: TComboBox;
    cbGrade: TComboBox;
    cbType: TComboBox;
    btnQuery: TButton;
    btnDelete: TButton;
    btnCancel: TButton;
    qryInit: TADOQuery;
    qrySelect: TADOQuery;
    qrySelectCUT_TYPE: TStringField;
    qrySelectSTUEMP_NO: TStringField;
    qrySelectSTUEMP_NAME: TStringField;
    qrySelectDEPT_NAME: TStringField;
    qrySelectS_CODE: TStringField;
    qrySelectSEX_NAME: TStringField;
    qrySelectID2: TStringField;
    qrySelectIN_DATE: TStringField;
    DataSource: TDataSource;
    DBGridEh1: TDBGridEh;
    dtpFromDate: TDateTimePicker;
    dtpToDate: TDateTimePicker;
    cbPhotoDate: TCheckBox;
    qrySelectPHOTO_DATE: TStringField;
    Label1: TLabel;
    Label2: TLabel;
    SaveDialog: TSaveDialog;
    qryPhoto: TADOQuery;
    qryDelete: TADOQuery;
    procedure FormShow(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnDeleteClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
    FwhrSQL: string;

    procedure InitComboBox(FieldName: string; ComboBox: TComboBox);
    procedure ExportData;
    procedure deleteData;
  public
    { Public declarations }
  end;
       
  procedure BatchDelete(Conn: TADOConnection);

implementation

{$R *.DFM}

uses
  Jpeg, FileCtrl, ksgProgress;

procedure BatchDelete(Conn: TADOConnection);
var
  frmBatchDelete: TfrmBatchDelete;
begin
  frmBatchDelete := TfrmBatchDelete.Create(Application);
  frmBatchDelete.qryInit.Connection := Conn;
  frmBatchDelete.qrySelect.Connection := Conn;
  frmBatchDelete.qryPhoto.Connection := Conn;
  frmBatchDelete.qryDelete.Connection := Conn;
  frmBatchDelete.ShowModal;
  frmBatchDelete.Free;
end;
   
{ TfrmBatchDelete }

procedure TfrmBatchDelete.InitComboBox(FieldName: string; ComboBox: TComboBox);
var
  strSQL: string;
begin
  // ��ʼ�� ComboBox �е�����
  strSQL := 'select distinct ' + FieldName +
      ' from PHOTO.T_CIF_PHOTO order by ' + FieldName;
  qryInit.SQL.Text := strSQL;
  qryInit.Open;
  ComboBox.Items.Clear;
  while not qryInit.Eof do
  begin
    ComboBox.Items.Add(qryInit.FieldByName(FieldName).AsString);
    qryInit.Next;
  end;
  qryInit.Recordset.Close;
  qryInit.Close;
end;

procedure TfrmBatchDelete.FormShow(Sender: TObject);
begin
  dtpFromDate.DateTime := Date();
  dtpToDate.DateTime := Date();
  // ��ʼ�����
  InitComboBox('CUT_TYPE',cbType);
  // ��ʼ��һ����λ  
  InitComboBox('DEPT_NAME',cbDept);
  // ��ʼ��������λ
  InitComboBox('S_CODE',cbSubDept);
  // ��ʼ���꼶
  InitComboBox('IN_DATE',cbGrade);
end;

procedure TfrmBatchDelete.btnQueryClick(Sender: TObject);
var
  strSQL: string;
begin
  FwhrSQL := '';
  if Trim(cbType.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and CUT_TYPE = ''' + Trim(cbType.Text) + ''' ';
  if Trim(edtNum.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and STUEMP_NO like ''%' + Trim(edtNum.Text) + '%'' ';
  if Trim(edtName.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and STUEMP_NAME like ''%' + Trim(edtName.Text) + '%'' ';

  if Trim(cbDept.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and DEPT_NAME = ''' + Trim(cbDept.Text) + ''' ';
  if Trim(cbSubDept.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and S_CODE = ''' + Trim(cbSubDept.Text) + ''' ';
  if Trim(cbGrade.Text) <> '' then
    FwhrSQL := FwhrSQL + ' and IN_DATE = ''' + Trim(cbGrade.Text) + ''' ';

  if cbPhotoDate.Checked then
  begin
    FwhrSQL := FwhrSQL + ' and PHOTO_DATE >= ''' +
        FormatDateTime('yyyy-mm-dd',dtpFromDate.DateTime) + ''' ';
    FwhrSQL := FwhrSQL + ' and PHOTO_DATE <= ''' +
        FormatDateTime('yyyy-mm-dd',dtpToDate.DateTime) + ''' ';
  end;
  
  if FwhrSQL = '' then
  begin
    MessageDlg('�������ѯ����!', mtWarning, [mbOk], 0);
    Exit;
  end;
  FwhrSQL := Copy(FwhrSQL, 6, Length(FwhrSQL) - 6);
  strSQL:='select CUT_TYPE, STUEMP_NO, STUEMP_NAME, DEPT_NAME, S_CODE, ' +
      'SEX_NAME, ID2, IN_DATE, PHOTO_DATE from PHOTO.T_CIF_PHOTO where ' +
      FwhrSQL;

  //qrySelect.Recordset.Close;
  if qrySelect.Active then
    qrySelect.Recordset.Close;
    
  qrySelect.Close;
  qrySelect.SQL.Text := strSQL;
  qrySelect.Open;
  lblTotlal.Caption := '�� ' + IntToStr(qrySelect.RecordCount) + ' ����¼';
end;

procedure TfrmBatchDelete.ExportData;
// from UnBatchExport
var
  ExpClass:TDBGridEhExportClass;
  Ext:String;
begin
  try
  begin
    SaveDialog.FileName := 'ɾ������'+formatdatetime('yyyymmdd',date());
    DBGridEh1.Selection.SelectAll ;
    if SaveDialog.Execute then
    begin
     case SaveDialog.FilterIndex of
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
        if UpperCase(Copy(SaveDialog.FileName,Length(SaveDialog.FileName)-2,3)) <>  UpperCase(Ext) then
          SaveDialog.FileName := SaveDialog.FileName + '.' + Ext;
        SaveDBGridEhToExportFile(ExpClass,DBGridEh1, SaveDialog.FileName,False);
      end;
    end;
  end ;
  except
    MessageDlg('����ʧ��! ����...', mtInformation, [mbOk], 0);
  end;
end;

procedure TfrmBatchDelete.btnDeleteClick(Sender: TObject);
// from UnBatchExport
var
  M1: TMemoryStream;
  Fjpg: TJpegImage;

  PicPath: string;
  FN: string;
  Num: string;
begin
  if not qrySelect.Active then
    MessageDlg('���Ȳ�ѯ����!', mtInformation, [mbOk], 0);

  ExportData;

  FN := SaveDialog.FileName;
  // PicPath := DirPath;  
  PicPath := Copy(FN, 1, Length(FN)-Length(ExtractFileExt(FN))) + '��Ƭ';

  if not DirectoryExists(PicPath) then
    if not CreateDir(PicPath) then
    begin
      MessageDlg('���ܴ����ļ���! ', mtInformation, [mbOk], 0);
      Exit;
    end;

  qrySelect.First;
  //frmProgress.BeginHandle('����ɾ������! ', 0, qrySelect.RecordCount);
  while not qrySelect.Eof do
  begin
    Num :=  qrySelect.FieldByName('STUEMP_NO').AsString;

    qryPhoto.Close;
    qryPhoto.SQL.Text := 'select STUEMP_NO, PHOTO, FILENAME from PHOTO.T_CIF_PHOTO '
        + 'where STUEMP_NO = ' + QuotedStr(Num);
    qryPhoto.Open;

    if qryPhoto.IsEmpty = True then
    begin
      qryPhoto.Recordset.Close;
      qryPhoto.Close;
      Exit;
    end;

    Fjpg := TJpegImage.Create;
    M1 := TMemoryStream.Create;
    try
      M1.Clear;

      if not qryPhoto.FieldByName('PHOTO').IsNull then
        TBlobField(qryPhoto.FieldByName('PHOTO')).SaveToStream(M1);
      M1.Position := 0;
      if M1.Size > 10 then
      begin
        FJpg.LoadFromStream(M1);
        FJpg.SaveToFile(PicPath + '\' + Num + '.jpg');
      end;
    finally
      M1.Free;
      FJpg.Free;
    end;
    deleteData;
    qrySelect.Next;
    //frmProgress.Progress;

    if (frmProgress.Escape) then
      if MessageDlg('ȷ��Ҫ�˳���?', mtConfirmation, [mbYes, mbNo], 0)
          = mrYes then
        Exit;
  end;
  ShowMessage('�Ѿ��ɹ�ɾ����ѡ������ݣ�');
  btnQuery.Click;
  {qryPhoto.Close;
  qryPhoto.SQL.Clear;
  qryPhoto.SQL.Add('delete PHOTO.T_CIF_PHOTO where stuemp_no='+dbgr);
  qryPhoto.ExecSQL; }
  qrySelect.Refresh;
  
  //frmProgress.EndHandle;
end;

procedure TfrmBatchDelete.deleteData;
begin
  qryDelete.Close;
  qryDelete.SQL.Clear;
  qryDelete.SQL.Add('delete PHOTO.T_CIF_PHOTO where stuemp_no='+#39+DBGridEh1.DataSource.DataSet.fieldbyname('stuemp_no').AsString+#39);
  qryDelete.ExecSQL;
end;

procedure TfrmBatchDelete.btnCancelClick(Sender: TObject);
begin
  if (qrySelect.IsEmpty) and (qrySelect.Active) then
  begin
    qrySelect.Recordset.Close;
    qrySelect.Close;
  end;
  if (qryDelete.IsEmpty) and(qryDelete.Active) then
  begin
    qryDelete.Recordset.Close;
    qryDelete.Close;
  end;
  if (qryInit.IsEmpty) and (qryInit.Active) then
  begin
    qryInit.Recordset.Close;
    qryInit.Close;
  end;
  close;
end;

end.
