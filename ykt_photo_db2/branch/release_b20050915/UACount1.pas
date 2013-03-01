unit UACount1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, Db, ADODB, StdCtrls;

type
  TReportCount1 = class(TForm)
    StringGrid1: TStringGrid;
    ADOQuery5: TADOQuery;
    ADOQuery6: TADOQuery;
    ADOQuery7: TADOQuery;
    Button1: TButton;
    Button2: TButton;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  ReportCount1: TReportCount1;

implementation


uses UDb, UtConfigs;
{$R *.DFM}


procedure TReportCount1.Button2Click(Sender: TObject);
begin
  Close;
end;

procedure TReportCount1.Button1Click(Sender: TObject);
var
  departName1: string;
  departCode1: string; //院系代码，
  deptPeopleAll: integer;
  photoedCount: integer; //已拍过的人数，
  unPhoCount: integer; //未拍过的人数，
  i: integer; //用于强行跳出循环，
  j: integer;
  num1: integer;
begin

  i := 0;
  ADOQuery5.Close;
  ADOQuery5.SQL.Clear;
  ADOQuery5.SQL.Add('select count(' + PersonNo + ') as totle ,count(' +
    SaveFileName + ')as num1,count(' + PersonKindName2 + ')-count(' +
    SaveFileName + ') as num2 ,' + PersonKindName2 + ' from ' +
    PhotoTableName + ' group by ' + PersonKindName2);
  //ADOQuery5.SQL.SaveToFile('123.txt');
  ADOQuery5.Open;
   //ShowMessage('查询到的学院总数是 '+IntToStr(ADOQuery5.RecordCount));
   //以下对学院进行逐记录统计，
  ReportCount1.StringGrid1.cells[0, 0] := '学院';
  ReportCount1.StringGrid1.cells[1, 0] := '总人数';
  ReportCount1.StringGrid1.cells[2, 0] := '已拍照人数';
  ReportCount1.StringGrid1.cells[3, 0] := '未拍照人数';
  i := i + 1;

  ADOQuery5.First;
  while not ADOQuery5.Eof do
  begin
     //ShowMessage(' 现在处理的记录号是 '+IntToStr(i));
    departCode1 := ADOQuery5.FieldByName(PersonKindName2).AsString;
     //ShowMessage(' 已获取院系代码 ');
    deptPeopleAll := ADOQuery5.FieldByName('totle').AsInteger;
     //ShowMessage(' 已得到该院总人数 ');
    photoedCount := ADOQuery5.FieldByName('num1').AsInteger;
     //ShowMessage(' 已得到已拍照总人数 ');
    unPhoCount := ADOQuery5.FieldByName('num2').AsInteger;
     //ShowMessage(' 院系代码是 '+ADOQuery5.FieldByName('DEPT_NAME').AsString);
     //查找院系名称，
    ADOQuery7.Close;
    ADOQuery7.SQL.Clear;
    ADOQuery7.SQL.Add('select ' + PersonKindName2 + ' from ' +
      DepartmentTableName + ' where ' + PersonKindNo2 + '=' + QuotedStr(departCode1));
    ADOQuery7.Open;
    departName1 := ADOQuery7.FieldByName(PersonKindName2).AsString;
    //ShowMessage(' 院系名称是 ' + ADOQuery7.FieldByName('DEPT_NAME').AsString);

       //输出到报表，
    ReportCount1.StringGrid1.cells[0, i] := departName1;
    ReportCount1.StringGrid1.cells[1, i] := IntToStr(deptPeopleAll);
    ReportCount1.StringGrid1.cells[2, i] := IntToStr(photoedCount);
    ReportCount1.StringGrid1.cells[3, i] := IntToStr(unPhoCount);

    ADOQuery5.Next;
    i := i + 1;
    ReportCount1.StringGrid1.RowCount := ReportCount1.StringGrid1.RowCount + 1;
    if i > 751 then
      exit;
  end;
  ADOQuery5.close;
  ADOQuery7.close;

end;

end.

