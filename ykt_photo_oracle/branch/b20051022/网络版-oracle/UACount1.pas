unit UACount1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Grids, Db, ADODB, ExtCtrls, StdCtrls;

type
  TReportCount1 = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    StringGrid1: TStringGrid;
    ADOQuery5: TADOQuery;
    ADOQuery6: TADOQuery;
    ADOQuery7: TADOQuery;
    RadioGroup1: TRadioGroup;
    Label1: TLabel;
    Button1: TButton;
    Button2: TButton;
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
    stype:string;
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
  close;
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
  case RadioGroup1.ItemIndex of
  0: stype:='��ְ��';
  1: stype:='��ʿ�о���';
  2: stype:='�о���';
  3: stype:='��ר����';
  end;

  i := 0;
  ADOQuery5.Close;
  ADOQuery5.SQL.Clear;
  ADOQuery5.SQL.Add('select count(' + StuEmpNo + ') as totle ,count(' +
    FileName + ')as num1,count(' + StuEmpNo + ')-count(' +
    FileName + ') as num2 ,' + BanchCode +','+DeptName+ ' from ' +
    PhotoTableName +' where cut_type='+#39+stype+#39+' group by ' + BanchCode+','+DeptName);
  //ADOQuery5.SQL.SaveToFile('123.txt');
  ADOQuery5.Open;
   //ShowMessage('��ѯ����ѧԺ������ '+IntToStr(ADOQuery5.RecordCount));
   //���¶�ѧԺ�������¼ͳ�ƣ�
  ReportCount1.StringGrid1.cells[0, 0] := 'ѧԺ';
  ReportCount1.StringGrid1.cells[1, 0] := 'רҵ';
  ReportCount1.StringGrid1.cells[2, 0] := '������';
  ReportCount1.StringGrid1.cells[3, 0] := '����������';
  ReportCount1.StringGrid1.cells[4, 0] := 'δ��������';
  i := i + 1;

  ADOQuery5.First;
  while not ADOQuery5.Eof do
  begin
     //ShowMessage(' ���ڴ���ļ�¼���� '+IntToStr(i));
    departCode1 := ADOQuery5.FieldByName(BanchCode).AsString;
     //ShowMessage(' �ѻ�ȡԺϵ���� ');
    deptPeopleAll := ADOQuery5.FieldByName('totle').AsInteger;
     //ShowMessage(' �ѵõ���Ժ������ ');
    photoedCount := ADOQuery5.FieldByName('num1').AsInteger;
     //ShowMessage(' �ѵõ������������� ');
    unPhoCount := ADOQuery5.FieldByName('num2').AsInteger;
         //����Ժϵ���ƣ�
    ADOQuery7.Close;
    ADOQuery7.SQL.Clear;
    ADOQuery7.SQL.Add('select distinct ' + SCode + ' from ' +
      PhotoTableName + ' where ' + BanchCode + '=' + QuotedStr(departCode1));
    ADOQuery7.Open;
    departName1 := ADOQuery7.FieldByName(SCode).AsString;

    //���������
    ReportCount1.StringGrid1.cells[0, i] := ADOQuery5.FieldByName(DeptName).AsString;
    ReportCount1.StringGrid1.cells[1, i] := departName1;
    ReportCount1.StringGrid1.cells[2, i] := IntToStr(deptPeopleAll);
    ReportCount1.StringGrid1.cells[3, i] := IntToStr(photoedCount);
    ReportCount1.StringGrid1.cells[4, i] := IntToStr(unPhoCount);
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
