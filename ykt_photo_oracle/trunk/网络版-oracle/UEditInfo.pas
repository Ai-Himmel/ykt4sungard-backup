unit UEditInfo;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Spin, Db, ADODB, DBCtrls, Mask;

type
  TFrmEditInfo = class(TForm)
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label16: TLabel;
    Label6: TLabel;
    Label23: TLabel;
    Edit1: TDBEdit;
    Edit2: TDBEdit;
    Edit6: TDBEdit;
    Button1: TButton;
    Button2: TButton;
    ComboBox1: TDBComboBox;
    ComboBox2: TDBComboBox;
    Label1: TLabel;
    Label2: TLabel;
    ComboBox4: TDBComboBox;
    ComboBox5: TDBComboBox;
    Edit4: TDBEdit;
    ADOQuery1: TADOQuery;
    ADOQuery2: TADOQuery;
    ADOQueryEdit: TADOQuery;
    DataSource1: TDataSource;
    DBEdit1: TDBEdit;
    dbcbbtype: TDBComboBox;
    procedure Button2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure ComboBox2Change(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    function CanInsert: Boolean;
    { Private declarations }
  public
    CurrentEditEmpNo: string;

    { Public declarations }
  end;

var
  FrmEditInfo: TFrmEditInfo;

implementation

uses Udb, UtConfigs, UAPhoto1;

{$R *.DFM}

function TFrmEditInfo.CanInsert: Boolean;
begin
  Result := True;
  Adoquery1.Close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select ' + StuempName + ' from ' + PhotoTableName +
    ' where ' + StuEmpNo + '=' + QuotedStr(Trim(Edit1.Text)));
  ADOQuery1.Open;
  if ADOQuery1.RecordCount > 0 then Result := True
  else Result := False;
end;


procedure TFrmEditInfo.Button2Click(Sender: TObject);
begin
  if application.messagebox('你确定要修改该学生信息吗？', pchar(application.title), mb_yesno + mb_iconquestion) = idyes then
  begin
    if ADOQueryEdit.State in [dsedit] then
    try
      ADOQueryEdit.fieldbyname('edit_flag').asstring := '1';
      ADOQueryEdit.Post;
      application.messagebox('修改基本信息成功！', pchar(application.title), mb_ok + mb_iconinformation);
      PhotoSystem.Button1Click(nil);
      self.close;
    except
      showmessage('修改基本信息失败！');
    end;
  end;
end;


procedure TFrmEditInfo.FormCreate(Sender: TObject);
begin
  ADOQuery1.close;
  ADOQuery1.SQL.Clear;
  ADOQuery1.SQL.Add('select distinct ' + DeptCode + ',' +
    DeptName + ' from ' + PhotoTableName +
    ' where ' + DeptCode + ' is not null order by ' + DeptCode);
  ADOQuery1.Open;
  Combobox1.Items.clear;
  Combobox4.Items.Clear;
  ADOQuery1.First;
  while not ADOQuery1.Eof do
  begin
    Combobox1.Items.Add(ADOQuery1.fieldbyname(DeptName).asstring);
    ComboBox4.Items.add(ADOQuery1.fieldbyname(DeptCode).asstring);
    ADOQuery1.Next;
  end;
  if Combobox1.Items.Count > 0 then Combobox1.ItemIndex := 0;
  ComboBox4.ItemIndex := combobox1.ItemIndex;


  ADOQuery2.close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('select distinct ' + BanchCode + ',' +
    SCode + ' from ' + PhotoTableName +
    ' where ' + BanchCode + ' is not null order by ' + BanchCode);
  ADOQuery2.Open;
  Combobox2.Items.clear;
  Combobox5.Items.Clear;
  ADOQuery2.First;
  while not ADOQuery2.Eof do
  begin
    Combobox2.Items.Add(ADOQuery2.fieldbyname(SCode).asstring);
    ComboBox5.Items.add(ADOQuery2.fieldbyname(BanchCode).asstring);
    ADOQuery2.Next;
  end;

  ADOQuery2.close;
  ADOQuery2.SQL.Clear;
  ADOQuery2.SQL.Add('select distinct ' + CutType + ' from ' + PhotoTableName );
  ADOQuery2.Open;
  dbcbbtype.Items.Clear;
  ADOQuery2.First;
  while not ADOQuery2.Eof do
  begin
    dbcbbtype.Items.Add(ADOQuery2.fieldbyname(CutType).asstring);
    ADOQuery2.Next;
  end;
  if Combobox2.Items.Count > 0 then Combobox2.ItemIndex := 0;
  ComboBox5.ItemIndex := combobox2.ItemIndex;

end;

procedure TFrmEditInfo.ComboBox1Change(Sender: TObject);
begin
  Combobox4.ItemIndex := Combobox1.ItemIndex;
end;

procedure TFrmEditInfo.ComboBox2Change(Sender: TObject);
begin
  Combobox5.ItemIndex := Combobox2.ItemIndex;
end;

procedure TFrmEditInfo.FormShow(Sender: TObject);
var
  sqlstr: string;
begin
  if PhotoSystem.Label13.caption = '' then
    exit;
  sqlstr := 'select '+STUEMPNO+','+STUEMPNAME+','+DEPTNAME+','+SCODE+','+ID2+','+CGRADE+','+
    CUTTYPE+','+Editflag+' from '+PhotoTableName+' where '+STUEMPNO+'=' + #39 + PhotoSystem.Label13.caption + #39;
  ADOQueryEdit.close;
  ADOQueryEdit.sql.clear;
  ADOQueryEdit.sql.add(sqlstr);
  ADOQueryEdit.Open;
end;

procedure TFrmEditInfo.Button1Click(Sender: TObject);
begin
  if (ADOQuery2.IsEmpty) and (ADOQuery2.Active) then
  begin
    ADOQuery2.Recordset.Close;
    ADOQuery2.Close;
  end;
  if (ADOQuery1.IsEmpty) and (ADOQuery1.Active) then
  begin
    ADOQuery1.Recordset.Close;
    ADOQuery1.Close;
  end;
  if (ADOQueryEdit.IsEmpty) and (ADOQueryEdit.Active) then
  begin
    ADOQueryEdit.Recordset.Close;
    ADOQueryEdit.Close;
  end;
  close;
end;

end.
