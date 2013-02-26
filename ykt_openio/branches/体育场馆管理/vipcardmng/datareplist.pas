unit datareplist;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DBGrids, StdCtrls, ADODB, DB, MemDS, data2Excel, DBAccess, ComObj, ExtCtrls, commu, ComCtrls;
  //Excel97, Excel2000,   inppat,
type
  TMgrid = class(TDbgrid);
  Tdatemngfrm = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    Panel3: TPanel;
    Panel4: TPanel;
    datemod: TButton;
    deldate: TButton;
    Label14: TLabel;
    datestr: TEdit;
    dateadd: TButton;
    DataSource1: TDataSource;
    SaveDialog1: TSaveDialog;
    Panel5: TPanel;
    DBGrid1: TDBGrid;
    Label2: TLabel;
    money: TEdit;
    procedure dateaddClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure deldateClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure DBGrid1CellClick(Column: TColumn);
    procedure datemodClick(Sender: TObject);
  private
    { Private declarations }

    procedure stageview;

  public
    { Public declarations }
    begindate: string;
    enddate: string;
    doctcode: string;
    stdcode: string;
    beglin, maxlin: integer;
  end;

var

  stuemp_no: string;

  datemngfrm: Tdatemngfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}

procedure Tdatemngfrm.stageview;
var
  sSql: string;
begin
  sSql := 'select *  from ykt_cur.T_STATIUM_VIPMNG order by stuemp_no';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    if debug = 'true' then
      writelog(sSql);
    DBQuery.Close;
    funcSelectSql(sSql, DBQuery);
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;

procedure Tdatemngfrm.dateaddClick(Sender: TObject);
var
  mon: integer;
  sSql: string;
begin
  stuemp_no := trim(datestr.Text);
  if trim(money.Text) <> '' then
  begin
    mon := strtoint(trim(money.Text));
  end;
  if funcConnectDB() then
  begin
    sSql := 'select *  from ykt_cur.T_STATIUM_VIPMNG where  stuemp_no=''' + (stuemp_no) + '''';
    if debug = 'true' then
      writelog(sSql);
    DBQueryBaK.Close;
    funcSelectSql(sSql, DBQueryBaK);
    if DBQueryBaK.RecordCount > 0 then
    begin
      FuncShowMessage(Application.Handle, '此学工号记录已经存在！', 2);
      exit;
    end;
    sSql := 'insert into  ykt_cur.T_STATIUM_VIPMNG(stuemp_no,TIMS,OPERATOR,RESERVE)' +
      ' values(''' + stuemp_no + ''',' + inttostr(mon) + ',''' + PtUser.GetUserName + ''','''')';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '增加VIP用户数据失败！', 2);
      exit;
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;

  stageview;
  FuncShowMessage(Application.Handle, '增加VIP用户数据成功！', 1);
  datestr.Text := '';
  money.Text := '';
end;




procedure Tdatemngfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 30;
  datestr.Text := '';
  DBQueryBaK := TADOQuery.Create(nil);
  DBQueryBaK.Connection := DBConn;
  DBQuery := TADOQuery.Create(nil);
  DBQuery.Connection := DBConn;
  DataSource1.DataSet := DBQuery;
  DBQueryTmp := TADOQuery.Create(nil);
  DBQueryTmp.Connection := DBConn;

end;


procedure Tdatemngfrm.deldateClick(Sender: TObject);
var
  ret: integer;
  sSql: string;
begin

  ret := FuncShowMessage(Application.Handle, '是否删除VIP用户数据？', 3);
  if ret = 6 then
  begin
    if funcConnectDB() then
    begin
      sSql := 'delete from  ykt_cur.T_STATIUM_VIPMNG  where stuemp_no=''' + (stuemp_no) + '''';
      DBQueryBaK.Close;
      if not funcExcuteSql(sSql, DBQueryBaK) then
      begin
        if debug = 'true' then
        begin
          writelog(sSql);
        end;
        FuncShowMessage(Application.Handle, '删除VIP用户数据失败！', 2);
        exit;
      end
      else
      begin
        stageview;
        FuncShowMessage(Application.Handle, '删除VIP用户数据成功！', 1);
      end;
    end
    else
    begin
      FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
    end;
  end;
end;
 {
procedure Tdatreplistfrm.DBGrid1DblClick(Sender: TObject);
begin
  procview;
end;
 }



procedure Tdatemngfrm.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  DBQueryTmp.Free;
  DBQuery.Free;
  DBQueryBaK.Free;
end;

procedure Tdatemngfrm.FormShow(Sender: TObject);
begin
  stageview;
end;
procedure Tdatemngfrm.DBGrid1CellClick(Column: TColumn);
begin
  datestr.Text := DBQuery.FieldByName('stuemp_no').AsString;
  money.Text := DBQuery.FieldByName('TIMS').AsString;
  stuemp_no := DBQuery.FieldByName('stuemp_no').AsString;
end;



procedure Tdatemngfrm.datemodClick(Sender: TObject);
var
  mon: integer;
  sSql: string;
begin
  if trim(datestr.Text) = '' then
  begin
    FuncShowMessage(Application.Handle, 'VIP学工号不能为空！', 2);
  end;
  if trim(money.Text) = '' then
  begin
    FuncShowMessage(Application.Handle, '可用次数不能为空！', 2);
  end;
  mon := strtoint(trim(money.Text));
  stuemp_no := trim(datestr.Text);
  if funcConnectDB() then
  begin
  {   sSql := 'select *  from ykt_cur.T_STATIUM_VIPMNG where  STUEMP_NO=' + inttostr(stuemp_no) + '';
    if debug = 'true' then
      writelog(sSql);
    DBQueryBaK.Close;
    funcSelectSql(sSql, DBQueryBaK);
    if DBQueryBaK.RecordCount > 0 then
    begin
      FuncShowMessage(Application.Handle, '此学工号记录已经存在！', 2);
      exit;
    end; }
    sSql := 'update ykt_cur.T_STATIUM_VIPMNG set STUEMP_NO=''' + datestr.Text + ''',TIMS=' + inttostr(mon) + ',OPERATOR=''' + PtUser.GetUserName + ''' where stuemp_no=''' + (stuemp_no) + '''';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, 'VIP用户数据失败！', 2);
      exit;
    end
    else
    begin
      stageview;
      FuncShowMessage(Application.Handle, 'VIP用户数据成功！', 1);
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
  stageview;
  datestr.Text := '';
  money.Text := '';
end;

end.

