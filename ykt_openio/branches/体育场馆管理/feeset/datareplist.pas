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
    dateadd: TButton;
    DataSource1: TDataSource;
    SaveDialog1: TSaveDialog;
    Panel5: TPanel;
    DBGrid1: TDBGrid;
    Label2: TLabel;
    money: TEdit;
    ComboBox1: TComboBox;
    procedure dateaddClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure deldateClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure DBGrid1CellClick(Column: TColumn);
    procedure datemodClick(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
  private
    { Private declarations }

    procedure stageview;
    procedure  stagelistfee ;
  public
    { Public declarations }
    begindate: string;
    enddate: string;
    doctcode: string;
    stdcode: string;
    beglin, maxlin: integer;
  end;

var

  FEE_TYPE: integer;

  datemngfrm: Tdatemngfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}

procedure Tdatemngfrm.stageview;
var
  sSql: string;
begin
  sSql := 'select *  from ykt_cur.T_STATIUM_FEEMNG  order by FEE_TYPE';
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
procedure Tdatemngfrm.stagelistfee;
var
  sSql: string;
  i:integer;
begin
  sSql := 'select t.fee_type,t.fee_name  from  ykt_cur.t_pif_feetype t order by  t.fee_type';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    if debug = 'true' then
      writelog(sSql);
    //DBQuerytmp.Close;
    funcSelectSql(sSql, DBQuerytmp);
    if DBQuerytmp.RecordCount>0  then
    begin
       for i:=0 to DBQuerytmp.RecordCount-1 do
          begin
          ComboBox1.Items.Add(DBQuerytmp.fieldbyname('fee_type').AsString+','+DBQuerytmp.fieldbyname('fee_name').AsString);
          DBQuerytmp.Next;
          end;
    end;

  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;


procedure Tdatemngfrm.ComboBox1Change(Sender: TObject);
var
feetp:string;
begin
    feetp:= combobox1.items[combobox1.ItemIndex] ;
    if feetp='' then
    begin
      FuncShowMessage(Application.Handle, '收费类别不能为空！', 2);
    end;
    FEE_TYPE:=strtoint(getnextstr(feetp));
end;

procedure Tdatemngfrm.dateaddClick(Sender: TObject);
var
  mon: integer;
  sSql: string;
begin
  if trim(money.Text) <> '' then
  begin
    mon := strtoint(trim(money.Text));
  end;
  if funcConnectDB() then
  begin
    sSql := 'insert into  ykt_cur.T_STATIUM_FEEMNG(FEE_TYPE,MONEY,OPERATOR,RESERVE)' +
      ' values(' + inttostr(FEE_TYPE) + ',' + inttostr(mon) + ',''' + PtUser.GetUserName + ''','''')';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '增加收费额数据失败！', 2);
      exit;
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;

  stageview;
  FuncShowMessage(Application.Handle, '增加收费额数据成功！', 1);
  money.Text:='';
end;




procedure Tdatemngfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 30;;
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

  ret := FuncShowMessage(Application.Handle, '是否删除收费额数据？', 3);
  if ret = 6 then
  begin
    if funcConnectDB() then
    begin
      sSql := 'delete from  ykt_cur.T_STATIUM_FEEMNG  where FEE_TYPE=' + inttostr(FEE_TYPE) + '';
      DBQueryBaK.Close;
      if not funcExcuteSql(sSql, DBQueryBaK) then
      begin
        if debug = 'true' then
        begin
          writelog(sSql);
        end;
        FuncShowMessage(Application.Handle, '删除收费额数据失败！', 2);
        exit;
      end
      else
      begin
        stageview;
        FuncShowMessage(Application.Handle, '删除收费额数据成功！', 1);
      end;
    end
    else
    begin
      FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
    end;
  end;
end;

procedure Tdatemngfrm.FormClose(Sender: TObject;
  var Action: TCloseAction);
begin
  DBQueryTmp.Free;
end;

procedure Tdatemngfrm.FormShow(Sender: TObject);
begin
  stageview;
  stagelistfee;
end;



procedure Tdatemngfrm.DBGrid1CellClick(Column: TColumn);
var
feetype:string;
begin
  feetype:=  DBQuery.FieldByName('FEE_TYPE').AsString ;
  combobox1.Text := getnextstr(feetype);
  money.Text:= DBQuery.FieldByName('FEE_TYPE').AsString;
  FEE_TYPE:= DBQuery.FieldByName('FEE_TYPE').AsInteger;
end;



procedure Tdatemngfrm.datemodClick(Sender: TObject);
var
  mon: integer;
  sSql: string;
begin
  if FEE_TYPE = 0 then
  begin
    FuncShowMessage(Application.Handle, '收费类型不能为空！', 2);
  end;
  if trim(money.Text) = '' then
  begin
    FuncShowMessage(Application.Handle, '金额不能为空！', 2);
  end;
  mon := strtoint(trim(money.Text));
  if funcConnectDB() then
  begin
    sSql := 'update ykt_cur.T_STATIUM_FEEMNG set FEE_TYPE=' + inttostr(FEE_TYPE) + ',FEE_TYPE='+inttostr(mon)+',OPERATOR=''' + PtUser.GetUserName + ''' where FEE_TYPE=' + inttostr(FEE_TYPE) + '';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '修改日期数据失败！', 2);
      exit;
    end
    else
    begin
      stageview;
      FuncShowMessage(Application.Handle, '修改日期段数据成功！', 1);
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
  stageview;
  money.Text:='';
end;

end.

