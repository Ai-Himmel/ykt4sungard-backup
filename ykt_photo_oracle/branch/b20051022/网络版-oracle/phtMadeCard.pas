unit phtMadeCard;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids, DBGrids, Db, ADODB, Grids_ts, TSGrid, TSDBGrid;

type
  TfrmMadeCard = class(TForm)
    GroupBox1: TGroupBox;
    Label6: TLabel;
    Label8: TLabel;
    edtNum: TEdit;
    cbDept: TComboBox;
    Label9: TLabel;
    Label10: TLabel;
    edtName: TEdit;
    cbSubDept: TComboBox;
    cbGrade: TComboBox;
    Label11: TLabel;
    Label12: TLabel;
    cbType: TComboBox;
    qryInit: TADOQuery;
    qrySelect: TADOQuery;
    btnQuery: TButton;
    tsDBGrid: TtsDBGrid;
    btnAntSelect: TButton;
    btnMadeCard: TButton;
    btnCancel: TButton;
    btnAllSelect: TButton;
    DataSource: TDataSource;
    qrySelectCUT_TYPE: TStringField;
    qrySelectSTUEMP_NO: TStringField;
    qrySelectSTUEMP_NAME: TStringField;
    qrySelectDEPT_NAME: TStringField;
    qrySelectS_CODE: TStringField;
    qrySelectSEX_NAME: TStringField;
    qrySelectID2: TStringField;
    qrySelectIN_DATE: TStringField;
    qrySelectIF_MAKECARD: TStringField;
    lblTotlal: TLabel;
    btnNotMade: TButton;
    procedure btnAllSelectClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnQueryClick(Sender: TObject);
    procedure btnMadeCardClick(Sender: TObject);
    procedure btnAntSelectClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure btnNotMadeClick(Sender: TObject);
  private
    { Private declarations }
     procedure InitComboBox(FieldName: string; ComboBox: TComboBox);
  public
    { Public declarations }
  end;

  procedure MadeCard(Conn: TADOConnection);

implementation

{$R *.DFM}

procedure MadeCard(Conn: TADOConnection);
var
  frmMadeCard: TfrmMadeCard;
begin
  frmMadeCard := TfrmMadeCard.Create(Application);
  frmMadeCard.qryInit.Connection := Conn;
  frmMadeCard.qrySelect.Connection := Conn;
  frmMadeCard.ShowModal;
  frmMadeCard.Free;
end;

procedure TfrmMadeCard.FormShow(Sender: TObject);
begin      
  // 初始化类别
  InitComboBox('CUT_TYPE',cbType);
  // 初始化一级单位  
  InitComboBox('DEPT_NAME',cbDept);
  // 初始化二级单位
  InitComboBox('S_CODE',cbSubDept);
  // 初始化年级
  InitComboBox('IN_DATE',cbGrade);
end;

procedure TfrmMadeCard.InitComboBox(FieldName: string; ComboBox: TComboBox);
var
  strSQL: string;
begin
  // 初始化 ComboBox 中的数据
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

procedure TfrmMadeCard.btnQueryClick(Sender: TObject);
var
  strSQL: string;
  whrSQL: string;
begin
  whrSQL := '';
  if Trim(cbType.Text) <> '' then
    whrSQL := whrSQL + ' and CUT_TYPE = ''' + Trim(cbType.Text) + ''' ';
  if Trim(edtNum.Text) <> '' then
    whrSQL := whrSQL + ' and STUEMP_NO like ''%' + Trim(edtNum.Text) + '%'' ';
  if Trim(edtName.Text) <> '' then
    whrSQL := whrSQL + ' and STUEMP_NAME like ''%' + Trim(edtName.Text) + '%'' ';

  if Trim(cbDept.Text) <> '' then
    whrSQL := whrSQL + ' and DEPT_NAME = ''' + Trim(cbDept.Text) + ''' ';
  if Trim(cbSubDept.Text) <> '' then
    whrSQL := whrSQL + ' and S_CODE = ''' + Trim(cbSubDept.Text) + ''' ';
  if Trim(cbGrade.Text) <> '' then
    whrSQL := whrSQL + ' and IN_DATE = ''' + Trim(cbGrade.Text) + ''' ';

  if whrSQL = '' then
  begin
    MessageDlg('请输入查询条件!', mtWarning, [mbOk], 0);
    Exit;
  end;
  whrSQL := Copy(whrSQL, 6, Length(whrSQL) - 6);
  strSQL:='select CUT_TYPE, STUEMP_NO, STUEMP_NAME, DEPT_NAME, S_CODE, ' +
      'SEX_NAME, ID2, IN_DATE, IF_MAKECARD from PHOTO.T_CIF_PHOTO where ' +
      whrSQL;

  //qrySelect.Recordset.Close;
  if qrySelect.Active then
    qrySelect.Recordset.Close;
    
  qrySelect.Close;
  qrySelect.SQL.Text := strSQL;
  qrySelect.Open;
  lblTotlal.Caption := '共 ' + IntToStr(qrySelect.RecordCount) + ' 条记录';
end;

procedure TfrmMadeCard.btnAllSelectClick(Sender: TObject);
begin
  tsDBGrid.SelectAll;
end;

procedure TfrmMadeCard.btnAntSelectClick(Sender: TObject);  
var
  I: Integer;
  Flag: Boolean;
begin
  qrySelect.First;
  for I := 1 to tsDBGrid.Rows do
  begin
    Flag := tsDBGrid.RowSelected[tsDBGrid.CurrentDataRow];
    tsDBGrid.RowSelected[tsDBGrid.CurrentDataRow] := not Flag;
    qrySelect.Next;
  end;
end;

procedure TfrmMadeCard.btnMadeCardClick(Sender: TObject);
var
  I: Integer;
begin
  qrySelect.First;
  for I := 1 to tsDBGrid.Rows do
  begin
    if tsDBGrid.RowSelected[tsDBGrid.CurrentDataRow] then
    begin
      qrySelect.Edit;
      qrySelect.FieldByName('IF_MAKECARD').AsString := '1';
    end;
    qrySelect.Next;
  end;
end;  

procedure TfrmMadeCard.btnNotMadeClick(Sender: TObject);
var
  I: Integer;
begin
  qrySelect.First;
  for I := 1 to tsDBGrid.Rows do
  begin
    if tsDBGrid.RowSelected[tsDBGrid.CurrentDataRow] then
    begin
      qrySelect.Edit;
      qrySelect.FieldByName('IF_MAKECARD').AsString := '0';
    end;
    qrySelect.Next;
  end;
end;

procedure TfrmMadeCard.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  qrySelect.Close;
end;

end.
