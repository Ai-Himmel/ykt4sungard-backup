unit datareplist;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DBGrids, StdCtrls, ADODB, DB, MemDS, data2Excel, DBAccess, ComObj, ExtCtrls, commu, ComCtrls,
  frxClass, frxDBSet;
type
  TMgrid = class(TDbgrid);
  Tdatemngfrm = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Panel3: TPanel;
    Panel4: TPanel;
    datequery: TButton;
    DataSource1: TDataSource;
    Panel5: TPanel;
    DBGrid1: TDBGrid;
    printf: TButton;
    Label2: TLabel;
    oldbegdate: TDateTimePicker;
    Label3: TLabel;
    oldenddate: TDateTimePicker;
    frxDBDataset1: TfrxDBDataset;
    frReport1: TfrxReport;
    procedure datequeryClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure printfClick(Sender: TObject);
    procedure frReport1GetValue(const VarName: string; var Value: Variant);

  private
    { Private declarations }


  public
    { Public declarations }
    begindate: string;
    enddate: string;
    doctcode: string;
    stdcode: string;
    beglin, maxlin: integer;
  end;

var

  CARD_TYPE: integer;

  datemngfrm: Tdatemngfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}

procedure Tdatemngfrm.datequeryClick(Sender: TObject);
var
  mon: integer;
  sSql: string;
begin
  procGetIniInfo;
  if funcConnectDB() then
  begin
    sSql := 'select  * from ykt_cur.T_TIF_REPORT_STADIUM where BALANCE_DATE >=''' + FormatDateTime('yyyymmdd', oldbegdate.DateTime) + ''' and BALANCE_DATE<=''' + FormatDateTime('yyyymmdd', oldenddate.DateTime) + ''' order by BALANCE_DATE';
    DBQuery.Close;
    if not funcSelectSql(sSql, DBQuery) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '查询数据失败！', 2);
      exit;
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;




procedure Tdatemngfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 30;
  oldbegdate.Date := date();
  oldenddate.Date := date();
  DBQueryBaK := TADOQuery.Create(nil);
  DBQueryBaK.Connection := DBConn;
  DBQuery := TADOQuery.Create(nil);
  DBQuery.Connection := DBConn;
  DataSource1.DataSet := DBQuery;
  DBQueryTmp := TADOQuery.Create(nil);
  DBQueryTmp.Connection := DBConn;
  frxDBDataset1.DataSet := DBQueryTmp;
 // frReport1.DataSet:= frxDBDataset1;

end;


procedure Tdatemngfrm.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  DBQueryTmp.Free;
  DBQuery.Free;
  DBQueryBaK.Free;
end;

procedure Tdatemngfrm.printfClick(Sender: TObject);
var
  sSql: string;
  i: integer;
begin
  if funcConnectDB() then
  begin
    sSql := 'select  BALANCE_DATE as BALANCE_DATE,sum(FEE_NUM) as FEE_NUM,sum(AMT) as AMT,sum(FREE_NUM) as FREE_NUM, sum(VIP_NUM) as VIP_NUM,sum(CARD_NUM) as CARD_NUM' +
      ' from ykt_cur.T_TIF_REPORT_STADIUM where BALANCE_DATE >=''' + FormatDateTime('yyyymmdd', oldbegdate.DateTime) + ''' and' +
      ' BALANCE_DATE<=''' + FormatDateTime('yyyymmdd', oldenddate.DateTime) + ''' group by BALANCE_DATE';
    DBQueryTmp.Close;
    if not funcSelectSql(sSql, DBQueryTmp) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '查询数据失败！', 2);
      exit;
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
  i := DBQueryTmp.RecordCount;

  frReport1.ShowReport;


end;

procedure Tdatemngfrm.frReport1GetValue(const VarName: string;
  var Value: Variant);
begin
 {
  if CompareText(VarName, 'totalfee') = 0 then
    Value := DBQueryTmp.FieldByName('totalfee').AsString;
  if CompareText(VarName, 'totalamt') = 0 then
    Value := DBQueryTmp.FieldByName('totalamt').AsString;
  if CompareText(VarName, 'totalfree') = 0 then
    Value := DBQueryTmp.FieldByName('totalfee').AsString;
  if CompareText(VarName, 'totalvip') = 0 then
    Value := DBQueryTmp.FieldByName('totalvip').AsString;
  if CompareText(VarName, 'totalcard') = 0 then
    Value := DBQueryTmp.FieldByName('totalcard').AsString;
   } 
end;

end.

