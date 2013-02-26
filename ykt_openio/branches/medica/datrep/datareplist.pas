unit datareplist;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DBGrids, StdCtrls,  db, Ora, MemDS, data2Excel,DBAccess,ComObj, ExtCtrls, inppat, commu, ComCtrls;
  //Excel97, Excel2000,
type
  TMgrid = class(TDbgrid);
  Tdatreplistfrm = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Panel3: TPanel;
    Panel4: TPanel;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    DBGrid1: TDBGrid;
    Label14: TLabel;
    doctor: TEdit;
    stuno: TLabel;
    studentno: TEdit;
    oldbegdate: TDateTimePicker;
    Label12: TLabel;
    Label13: TLabel;
    oldenddate: TDateTimePicker;
    Button4: TButton;
    DataSource1: TDataSource;
    SaveDialog1: TSaveDialog;
    outexcel: TButton;

    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure procListmedc;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure DBGrid1DblClick(Sender: TObject);
    procedure procview;
    procedure outexcelClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  //  function funtoexcel(excelFile: string): boolean;
  public
    { Public declarations }
    begindate: string;
    enddate: string;
    doctcode: string;
    stdcode: string;
    beglin, maxlin: integer;
  end;

var
  datreplistfrm: Tdatreplistfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}
{
function Tdatreplistfrm.funtoexcel(excelFile: string): boolean;
var
   y, Number: integer;
  ssql, srcstr: string;
  v: Variant;
  FWorkBook: Variant;
begin
  result := false;
  try
    v := CreateOleObject('Excel.Application');
  except
    showmessage('您还未安装OFFICE EXCEL软件！');
    exit;
  end;
  v.Visible := false;
  FWorkBook := v.WorkBooks.Add;
  v.WorkSheets[1].Activate;
  v.WorkSheets[1].Columns[1].NumberFormatLocal := '@';
  v.WorkSheets[1].Columns[2].NumberFormatLocal := '@';
  v.WorkSheets[1].Columns[3].NumberFormatLocal := '@';
  v.WorkSheets[1].Columns[4].NumberFormatLocal := '@';
  try
    y := 2;
    v.Cells[1, 1] := '医生代码';
    v.Cells[1, 2] := '医生姓名';
    v.Cells[1, 3] := '学工号';
    v.Cells[1, 4] := '姓名';
    v.Cells[1, 5] := '客户类别';
    v.Cells[1, 6] := '性别';
    v.Cells[1, 7] := '缴费金额';
    v.Cells[1, 8] := '缴费日期';
    v.Cells[1, 9] := '处方编号';
    DBQueryTmp.First;
    Number := DBQueryTmp.RecordCount;
    while not (Number = 0) do
    begin
      v.Cells[y, 1] := DBQueryTmp.FieldByName('OPERCODE').AsString;
      v.Cells[y, 2] := DBQueryTmp.FieldByName('OPERNAME').AsString;
      v.Cells[y, 3] := DBQueryTmp.FieldByName('STUEMPNO').AsString;
      v.Cells[y, 4] := DBQueryTmp.FieldByName('CUSTNAME').AsString;
      v.Cells[y, 5] := DBQueryTmp.FieldByName('CUSTTYPENAME').AsString;
      v.Cells[y, 6] := DBQueryTmp.FieldByName('sexname').AsString;
      v.Cells[y, 7] := DBQueryTmp.FieldByName('TRANSAMT').AsVariant;
      v.Cells[y, 8] := DBQueryTmp.FieldByName('TRANSDATE').AsString;
      v.Cells[y, 9] := DBQueryTmp.FieldByName('VOUCHERNO').AsString;
      inc(y);
      DBQueryTmp.Next;
      dec(Number);
    end;
    showmessage('数据导出完毕！');

  finally
    v.Columns.AutoFit;
    FWorkBook.SaveAs(excelFile);
    v.WorkBooks.Close;
    v.Quit;
  end;
  result := true;
end;
 }
procedure Tdatreplistfrm.Button3Click(Sender: TObject);
begin
  close;
end;

procedure Tdatreplistfrm.procview;
var
  VOUCHERNO, stdno: string;
  frm: Tinppatfrm;
begin
  frm := Tinppatfrm.Create(self);
  try
    VOUCHERNO := trim(DBQueryTmp.FieldByName('VOUCHERNO').AsString);
    frm.VOUCHERNO := VOUCHERNO;
    frm.studno := trim(DBQueryTmp.FieldByName('stuempno').AsString);
    frm.ShowModal;
  finally
    frm.Free;
  end;
  Screen.Cursor := crDefault;
end;

procedure Tdatreplistfrm.Button4Click(Sender: TObject);
begin
  doctcode := trim(doctor.Text);
  stdcode := trim(studentno.Text);
  procListmedc;
end;

procedure Tdatreplistfrm.procListmedc;
var
  sSql: string;
  sqstr: string;
begin
  if trim(doctor.Text) <> '' then
    sqstr := ' and a.OPERCODE=' + trim(doctor.Text);
  if trim(studentno.Text) <> '' then
    sqstr := sqstr + ' and a.STUEMPNO=' + trim(studentno.Text);
  sSql := 'SELECT * FROM (select rownum AS ROWNO ,a.VOUCHERNO,a.OPERCODE,a.STUEMPNO,a.TRANSAMT/100 as TRANSAMT ,a.TRANSDATE,b.CUSTNAME,' +
    'trim((case b.sex  when ''1'' then :f1 else :f2 end)) as sexname,c.OPERNAME,trim(d.CUSTTYPENAME) as CUSTTYPENAME from ' +
    'T_MEDICALDTL a ,T_CUSTOMER B,T_OPERATOR c,T_CUSTTYPE d ' +
    ' where a.transdate >=' + FormatDateTime('yyyymmdd', oldbegdate.DateTime) + ' and a.transdate <=' + FormatDateTime('yyyymmdd', oldenddate.DateTime) + '' +
    '  and a.CUSTID=B.CUSTID and a.OPERCODE=c.OPERCODE and b.custtype=d.CUSTTYPE' + sqstr + ') TABLE_ALIAS WHERE TABLE_ALIAS.ROWNO <= ' + inttostr(beglin + maxlin) + ' AND TABLE_ALIAS.ROWNO >= ' + inttostr(beglin);
  procGetIniInfo;
  if funcConnectDB() then
  begin
    DBQueryTmp.SQL.Text := sSql;
    if debug = 'true' then
      writelog(sSql);
    DBQueryTmp.Params[0].AsWideString := '男';
    DBQueryTmp.Params[1].AsWideString := '女';
    DBQueryTmp.Open;
  end;

end;


procedure Tdatreplistfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 30;
  doctor.Text := '';
  studentno.Text := '';
  oldbegdate.Date := date();
  oldenddate.Date := date();
  DBQueryTmp := TOraQuery.Create(nil);
  DBQueryTmp.Connection := DBConn;
  DataSource1.DataSet := DBQueryTmp;
end;

procedure Tdatreplistfrm.Button1Click(Sender: TObject);
begin
  if (beglin - maxlin >= 0) then
    beglin := beglin - maxlin;
  procListmedc;
end;

procedure Tdatreplistfrm.Button2Click(Sender: TObject);
begin
  if DBQueryTmp.RecordCount <> 0 then
  begin
    beglin := beglin + maxlin;
    procListmedc;
  end;
end;

procedure Tdatreplistfrm.DBGrid1DblClick(Sender: TObject);
begin
  procview;
end;

procedure Tdatreplistfrm.outexcelClick(Sender: TObject);
var
  excel: string;
begin
  if FuncShowMessage(Handle, '是否确定导出到excel?', 3) = IDYES then
  begin
    if DBQueryTmp.RecordCount > 0 then
    begin
      try
        if saveDialog1.Execute then
        begin
          excel := saveDialog1.FileName+'.xls';
          DataGridToXLS(DBGrid1,excel);
   //       funtoexcel(excel);
        end;
      finally
      end;
    end
    else
    begin
      showmessage('没有需要导出的信息！');
    end;
  end;
end;

procedure Tdatreplistfrm.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
DBQueryTmp.Free;
end;

end.

