unit UCustReport;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  FR_Class, FR_DSet, FR_DBSet;

type
  TfrmCustReport = class(TForm)
    procedure frCustReportGetValue(const ParName: String;
      var ParValue: Variant);
  private
    rTitle, rDept,rDesc,rTitDate,rDate,rOper:string;
    { Private declarations }
  public
    { Public declarations }
    procedure setCustValue(const Title, Dept,Desc,TitDate,Date,oper:string);
  end;

var
  frmCustReport: TfrmCustReport;

implementation

{$R *.DFM}

{ TfrmCustReport }

procedure TfrmCustReport.setCustValue(const Title, Dept, Desc, TitDate, Date,
  oper: string);
begin
  rTitle := Title;
  rDept := Dept;
  rDesc := Desc;
  rTitDate := TitDate;
  rDate := Date;
  rOper := oper;
end;

procedure TfrmCustReport.frCustReportGetValue(const ParName: String;
  var ParValue: Variant);
begin
  if ParName = 'RTitle' then
    ParValue := rTitle;
  if ParName = 'RDept' then
    ParValue := rDept;
  if ParName = 'RDesc' then
    ParValue := rDesc;
  if ParName = 'RTitleDate' then
    ParValue := rTitDate;
  if ParName = 'RDate' then
    ParValue := rDate;
  if ParName = 'ROper' then
    ParValue := rOper;

end;

end.
