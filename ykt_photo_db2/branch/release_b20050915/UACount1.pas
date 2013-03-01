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
  departCode1: string; //Ժϵ���룬
  deptPeopleAll: integer;
  photoedCount: integer; //���Ĺ���������
  unPhoCount: integer; //δ�Ĺ���������
  i: integer; //����ǿ������ѭ����
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
   //ShowMessage('��ѯ����ѧԺ������ '+IntToStr(ADOQuery5.RecordCount));
   //���¶�ѧԺ�������¼ͳ�ƣ�
  ReportCount1.StringGrid1.cells[0, 0] := 'ѧԺ';
  ReportCount1.StringGrid1.cells[1, 0] := '������';
  ReportCount1.StringGrid1.cells[2, 0] := '����������';
  ReportCount1.StringGrid1.cells[3, 0] := 'δ��������';
  i := i + 1;

  ADOQuery5.First;
  while not ADOQuery5.Eof do
  begin
     //ShowMessage(' ���ڴ���ļ�¼���� '+IntToStr(i));
    departCode1 := ADOQuery5.FieldByName(PersonKindName2).AsString;
     //ShowMessage(' �ѻ�ȡԺϵ���� ');
    deptPeopleAll := ADOQuery5.FieldByName('totle').AsInteger;
     //ShowMessage(' �ѵõ���Ժ������ ');
    photoedCount := ADOQuery5.FieldByName('num1').AsInteger;
     //ShowMessage(' �ѵõ������������� ');
    unPhoCount := ADOQuery5.FieldByName('num2').AsInteger;
     //ShowMessage(' Ժϵ������ '+ADOQuery5.FieldByName('DEPT_NAME').AsString);
     //����Ժϵ���ƣ�
    ADOQuery7.Close;
    ADOQuery7.SQL.Clear;
    ADOQuery7.SQL.Add('select ' + PersonKindName2 + ' from ' +
      DepartmentTableName + ' where ' + PersonKindNo2 + '=' + QuotedStr(departCode1));
    ADOQuery7.Open;
    departName1 := ADOQuery7.FieldByName(PersonKindName2).AsString;
    //ShowMessage(' Ժϵ������ ' + ADOQuery7.FieldByName('DEPT_NAME').AsString);

       //���������
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

