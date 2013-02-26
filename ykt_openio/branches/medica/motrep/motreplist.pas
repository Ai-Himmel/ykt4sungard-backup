unit motreplist;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DBGrids, db, Ora, MemDS, DBAccess, commu,data2Excel,StdCtrls,ComObj,
   ExtCtrls;
//  Excel97, Excel2000,
type
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
    Label2: TLabel;
    doctor: TEdit;
    Label4: TLabel;
    year: TEdit;
    Button4: TButton;
    outexcel: TButton;
    SaveDialog1: TSaveDialog;
    procedure FormCreate(Sender: TObject);
    procedure procListmedc;
    procedure Button4Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure outexcelClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
   //   function funtoexcel(excelFile: string): boolean;
  public
    { Public declarations }
    beglin, maxlin: integer;
  end;

var
  datreplistfrm: Tdatreplistfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}

{function Tdatreplistfrm.funtoexcel(excelFile: string): boolean;
var
   y,  Number : integer;
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
    v.Cells[1, 1] := '月度';
    v.Cells[1, 2] := '医生代码';
    v.Cells[1, 3] := '看病人数';
    v.Cells[1, 4] := '医生姓名';
    v.Cells[1, 5] := '收费金额';
      DBQueryTmp.First;
      Number := DBQueryTmp.RecordCount;

      while not (Number = 0) do
      begin
        v.Cells[y, 1] := DBQueryTmp.FieldByName('trmonth').AsString;
        v.Cells[y, 2] := DBQueryTmp.FieldByName('OPERCODE').AsString;
        v.Cells[y, 3] := DBQueryTmp.FieldByName('stnumber').AsString;
        v.Cells[y, 4] := DBQueryTmp.FieldByName('OPERname').AsString;
        v.Cells[y, 5] := DBQueryTmp.FieldByName('totalmoney').AsVariant;
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
procedure Tdatreplistfrm.procListmedc;
var
  sSql: string;
  sqstr, sqstr2: string;
begin
  if year.Text = '' then
  begin
    FuncShowMessage(Application.Handle, '请先填写年份！', 2);
    exit;
  end;
  if trim(doctor.Text) <> '' then
  begin
    sqstr := ' where OPERCODE like ''%' + trim(doctor.Text) + '%''';
  end;
  if trim(year.Text) <> '' then
  begin
    if trim(doctor.Text) <> '' then
    begin
      sqstr := sqstr + ' and TRANSDATE like ''%' + trim(year.Text) + '%''';
    end
    else
    begin
      sqstr := 'where TRANSDATE like ''%' + trim(year.Text) + '%''';
    end;
  end;

  ssql := 'select a.trmonth,a.opercode,a.stnumber,a.totalmoney,b.opername from ' +
    '(select substr(transdate,1,6) trmonth,opercode,count(*) stnumber,sum(transamt)/100 totalmoney from t_medicaldtl  t ' + sqstr + ' ' +
    'group by opercode,substr(transdate,1,6)) a,t_operator b  where a.opercode=b.opercode ' +
    'and  rownum<= ' + inttostr(beglin + 15) + '  and rownum >= ' + inttostr(beglin) + '  order by a.trmonth';

  procGetIniInfo;
  if funcConnectDB() then
  begin

    if debug = 'true' then
      writelog(sSql);
    DBQueryTmp.SQL.Text := sSql;
 //  DBQueryTmp.Params[0].AsWideString := '月';
//    DBQueryTmp.Params[1].AsWideString := '月';
    DBQueryTmp.Open;
    DataSource1.DataSet := DBQueryTmp;
  end;
  DBGrid1.DataSource := DataSource1;
end;


procedure Tdatreplistfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 15;
  doctor.Text := '';
  year.Text := '';
  DataSource1 := TDataSource.Create(nil);
      DBQueryTmp := TOraQuery.Create(nil);
    DBQueryTmp.Connection := DBConn;
end;

procedure Tdatreplistfrm.Button4Click(Sender: TObject);
begin
  procListmedc;
end;

procedure Tdatreplistfrm.Button1Click(Sender: TObject);
begin
  if (beglin - maxlin > 0) then
    beglin := beglin - maxlin;
    procListmedc;
end;

procedure Tdatreplistfrm.Button2Click(Sender: TObject);
begin
  if DBQuery <> nil then
    if 0 < DBQuery.RecordCount then
      beglin := beglin + maxlin;
      procListmedc
end;

procedure Tdatreplistfrm.Button3Click(Sender: TObject);
begin
  close;
end;

procedure Tdatreplistfrm.outexcelClick(Sender: TObject);
var
excel:string;
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
       // funtoexcel(excel);
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

