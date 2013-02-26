unit datareplist;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, DBGrids, StdCtrls, ADODB, DB, data2Excel,  ComObj, ExtCtrls, commu, ComCtrls;
  //Excel97, Excel2000,   inppat,   MemDS, DBAccess,
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
    stuno: TLabel;
    bgtime: TEdit;
    oldbegdate: TDateTimePicker;
    Label12: TLabel;
    Label13: TLabel;
    oldenddate: TDateTimePicker;
    dateadd: TButton;
    DataSource1: TDataSource;
    modtime: TButton;
    Panel5: TPanel;
    DBGrid1: TDBGrid;
    Panel6: TPanel;
    DBGrid2: TDBGrid;
    DataSource2: TDataSource;
    STAGETIMEADD: TButton;
    deltime: TButton;
    Label2: TLabel;
    edtime: TEdit;
    procedure dateaddClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure deldateClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure STAGETIMEADDClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure modtimeClick(Sender: TObject);
    procedure DBGrid2CellClick(Column: TColumn);
    procedure deltimeClick(Sender: TObject);
    procedure DBGrid1CellClick(Column: TColumn);
    procedure DBGrid2DblClick(Sender: TObject);
    procedure datemodClick(Sender: TObject);
  private
    { Private declarations }
    function getrightdate(datestr: string): boolean;
    procedure stageview;
    procedure dateview;
  public
    { Public declarations }
    begindate: string;
    enddate: string;
    doctcode: string;
    stdcode: string;
    beglin, maxlin: integer;
  end;

var
  STAGE_ID: integer;
  DATA_ID: integer;
  dateval: string;
  FEE_DATA: string;
  STAGE_VALUE: string;
  datemngfrm: Tdatemngfrm;
  DataSource1: TDataSource;
implementation

{$R *.dfm}

function Tdatemngfrm.getrightdate(datestr: string): boolean;
var
  datestr2, datestr3, bstr, estr, bstr2, estr2, getstr, getstr2, sSql: string;
  i: integer;
begin
  result := false;
  datestr2 := datestr;
  datestr3 := datestr;
  getstr := GetNextStr(datestr);
  while getstr <> '' do
  begin
    sSql := 'select *  from ykt_cur.T_STATIUM_STAGE where STAGE_ID=' + getstr + ' order by STAGE_ID';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      if debug = 'true' then
        writelog(sSql);
      DBQueryBak.Close;
      if funcSelectSql(sSql, DBQueryBak) then
      begin
        if DBQueryBak.RecordCount > 0 then
        begin
          bstr := DBQueryBaK.FieldByName('BEGIN_TIME').AsString;
          estr := DBQueryBaK.FieldByName('END_TIME').AsString;
          datestr2 := datestr3;
          getstr2 := GetNextStr(datestr2);
         if  getstr=getstr2 then
          begin
          getstr2 := GetNextStr(datestr2); //不和自己比
          end;
           writelog(getstr+'='+getstr2);
          while getstr2 <> '' do
          begin
          if  getstr=getstr2 then
          begin
          //break; //不和自己比
           getstr2 := GetNextStr(datestr2);
            continue;
          end;
            sSql := 'select *  from ykt_cur.T_STATIUM_STAGE where STAGE_ID=' + getstr2 + ' order by STAGE_ID';
            getstr2 := GetNextStr(datestr2);
            procGetIniInfo;
            if funcConnectDB() then
            begin
              if debug = 'true' then
                writelog(sSql);
              DBQueryBak.Close;
              if funcSelectSql(sSql, DBQueryBak) then
              begin
                bstr2 := DBQueryBaK.FieldByName('BEGIN_TIME').AsString;
                estr2 := DBQueryBaK.FieldByName('END_TIME').AsString;
                 writelog(datestr3+'开始时间'+bstr+'结束时间'+estr+'开始时间'+bstr2+'结束时间'+estr2);
                if (((bstr >=bstr2 ) and (estr <=estr2)) or ((estr >=bstr2 ) and (estr <estr2))) then
                begin
                  result := true;
                end;
              end;
            end;
          end;
        end;
      end;
       getstr := GetNextStr(datestr);
    end
    else
    begin
      FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
    end;
  end;
end;

procedure Tdatemngfrm.stageview;
var
  sSql: string;
begin
  sSql := 'select *  from ykt_cur.T_STATIUM_STAGE order by STAGE_ID';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    if debug = 'true' then
      writelog(sSql);
    DBQueryTmp.Close;
    funcSelectSql(sSql, DBQueryTmp);
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;

procedure Tdatemngfrm.dateview;
var
  sSql: string;
begin
  sSql := 'select *  from ykt_cur.T_STATIUM_FEEDATE order by DATA_ID';
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
  i, bgdt, eddt: integer;
  sSql: string;
begin
  dateval := trim(datestr.Text);
  if dateval = '' then
  begin
    FuncShowMessage(Application.Handle, '日期数据不能为空！', 2);
    exit;
  end;
  if  getrightdate(dateval) then
  begin
    FuncShowMessage(Application.Handle, '你选择的时间段存在重复时间！', 2);
    exit;
  end;
  bgdt := strtoint(FormatDateTime('yyyymmdd', oldbegdate.DateTime));
  eddt := strtoint(FormatDateTime('yyyymmdd', oldenddate.DateTime));
  for i := bgdt to eddt do
  begin
    sSql := 'select max(DATA_ID) as DATA_ID from ykt_cur.T_STATIUM_FEEDATE';
    procGetIniInfo;
    if funcConnectDB() then
    begin
      if debug = 'true' then
        writelog(sSql);
      DBQueryBaK.Close;
      if funcSelectSql(sSql, DBQueryBaK) then
      begin
        if DBQueryBaK.RecordCount > 0 then
        begin
          DATA_ID := DBQueryBaK.FieldByName('DATA_ID').AsInteger + 1;
        end
        else
        begin
          DATA_ID := 1;
        end;
      end;
      sSql := 'insert into  ykt_cur.T_STATIUM_FEEDATE(DATA_ID,FEE_DATA,STAGE_VALUE,OPERATOR,RESERVE)' +
        ' values(' + inttostr(DATA_ID) + ',''' + inttostr(i) + ''',''' + dateval + ''',''' + PtUser.GetUserName + ''','''')';
      DBQueryBaK.Close;
      if not funcExcuteSql(sSql, DBQueryBaK) then
      begin
        if debug = 'true' then
        begin
          writelog(sSql);
        end;
        FuncShowMessage(Application.Handle, '增加收费日期数据失败！', 2);
        exit;
      end;
    end
    else
    begin
      FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
    end;
  end;
  dateview;
  FuncShowMessage(Application.Handle, '增加收费日期数据成功！', 1);
  datestr.Text := '';
end;




procedure Tdatemngfrm.FormCreate(Sender: TObject);
begin
  beglin := 0;
  maxlin := 30;
  datestr.Text := '';
  bgtime.Text := '';
  edtime.Text := '';
  oldbegdate.Date := date();
  oldenddate.Date := date();
  DBQueryBaK := TADOQuery.Create(nil);
  DBQueryBaK.Connection := DBConn;
  DBQuery := TADOQuery.Create(nil);
  DBQuery.Connection := DBConn;
  DataSource1.DataSet := DBQuery;
  DBQueryTmp := TADOQuery.Create(nil);
  DBQueryTmp.Connection := DBConn;
  DataSource2.DataSet := DBQueryTmp;
end;


procedure Tdatemngfrm.deldateClick(Sender: TObject);
var
  ret: integer;
  sSql: string;
begin
  if DATA_ID <= 7 then
  begin
    FuncShowMessage(Application.Handle, '小于7的收费日期为通用收费日期，不能删除！', 2);
    exit;
  end;
  ret := FuncShowMessage(Application.Handle, '是否删除收费日期数据？', 3);
  if ret = 6 then
  begin
    if funcConnectDB() then
    begin
      sSql := 'delete from  ykt_cur.T_STATIUM_FEEDATE  where DATA_ID=' + inttostr(DATA_ID) + '';
      DBQueryBaK.Close;
      if not funcExcuteSql(sSql, DBQueryBaK) then
      begin
        if debug = 'true' then
        begin
          writelog(sSql);
        end;
        FuncShowMessage(Application.Handle, '删除收费日期数据失败！', 2);
        exit;
      end
      else
      begin
        dateview;
        FuncShowMessage(Application.Handle, '删除收费日期数据成功！', 1);
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

procedure Tdatemngfrm.STAGETIMEADDClick(Sender: TObject);
var
  sSql, bgtm, edtm: string;
begin
  bgtm := trim(bgtime.Text);
  edtm := trim(edtime.Text);
  if ((bgtm = '') or (edtm = '')) then
  begin
    FuncShowMessage(Application.Handle, '结束时间和开始时间为空！', 2);
    exit;
  end
  else
  begin
    if length(bgtm) <> 4 then
    begin
      FuncShowMessage(Application.Handle, '开始时间格式不正确:hhmm', 2);
      exit;
    end;
    if length(edtm) <> 4 then
    begin
      FuncShowMessage(Application.Handle, '结束时间格式不正确:hhmm', 2);
      exit;
    end;
  end;
  sSql := 'select max(STAGE_ID) as STAGE_ID from ykt_cur.T_STATIUM_STAGE';
  procGetIniInfo;
  if funcConnectDB() then
  begin
    if debug = 'true' then
      writelog(sSql);
    DBQueryBaK.Close;
    if funcSelectSql(sSql, DBQueryBaK) then
    begin
      if DBQueryBaK.RecordCount > 0 then
      begin
        STAGE_ID := DBQueryBaK.FieldByName('STAGE_ID').AsInteger + 1;
      end
      else
      begin
        STAGE_ID := 1;
      end;
    end;

    sSql := 'insert into  ykt_cur.T_STATIUM_STAGE(STAGE_ID,BEGIN_TIME,END_TIME,OPERATOR,RESERVE)' +
      ' values(' + inttostr(STAGE_ID) + ',''' + bgtm + ''',''' + edtm + ''',''' + PtUser.GetUserName + ''','''')';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '增加时间段数据失败！', 2);
      exit;
    end
    else
    begin
      stageview;
      FuncShowMessage(Application.Handle, '增加时间段数据成功！', 1);
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;

procedure Tdatemngfrm.FormShow(Sender: TObject);
begin
  dateview;
  stageview;
end;

procedure Tdatemngfrm.modtimeClick(Sender: TObject);
var
  sSql, bgtm, edtm: string;
begin
  bgtm := trim(bgtime.Text);
  edtm := trim(edtime.Text);
  if ((bgtm = '') or (edtm = '')) then
  begin
    FuncShowMessage(Application.Handle, '结束时间和开始时间为空！', 2);
    exit;
  end
  else
  begin
    if length(bgtm) <> 4 then
    begin
      FuncShowMessage(Application.Handle, '开始时间格式不正确:hhmm', 2);
      exit;
    end;
    if length(edtm) <> 4 then
    begin
      FuncShowMessage(Application.Handle, '结束时间格式不正确:hhmm', 2);
      exit;
    end;
  end;
  if funcConnectDB() then
  begin
    sSql := 'update  ykt_cur.T_STATIUM_STAGE set BEGIN_TIME=''' + bgtm + ''',END_TIME=''' + edtm + ''',OPERATOR=''' + PtUser.GetUserName + ''' where STAGE_ID=' + inttostr(STAGE_ID) + '';
    DBQueryBaK.Close;
    if not funcExcuteSql(sSql, DBQueryBaK) then
    begin
      if debug = 'true' then
      begin
        writelog(sSql);
      end;
      FuncShowMessage(Application.Handle, '修改时间段数据失败！', 2);
      exit;
    end
    else
    begin
      stageview;
      FuncShowMessage(Application.Handle, '修改时间段数据成功！', 1);
    end;
  end
  else
  begin
    FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
  end;
end;

procedure Tdatemngfrm.DBGrid2CellClick(Column: TColumn);
begin
  STAGE_ID := DBQueryTmp.FieldByName('STAGE_ID').AsInteger;
  bgtime.Text := DBQueryTmp.FieldByName('BEGIN_TIME').AsString;
  edtime.Text := DBQueryTmp.FieldByName('END_TIME').AsString;
end;

procedure Tdatemngfrm.deltimeClick(Sender: TObject);
var
  sSql: string;
  ret: integer;
begin
  ret := FuncShowMessage(Application.Handle, '是否删除时间段数据？', 3);
  if ret = 6 then
  begin
    if funcConnectDB() then
    begin
      sSql := 'delete from  ykt_cur.T_STATIUM_STAGE  where STAGE_ID=' + inttostr(STAGE_ID) + '';
      DBQueryBaK.Close;
      if not funcExcuteSql(sSql, DBQueryBaK) then
      begin
        if debug = 'true' then
        begin
          writelog(sSql);
        end;
        FuncShowMessage(Application.Handle, '删除时间段数据失败！', 2);
        exit;
      end
      else
      begin
        stageview;
        FuncShowMessage(Application.Handle, '删除时间段数据成功！', 1);
      end;
    end
    else
    begin
      FuncShowMessage(Application.Handle, '连接数据库失败！', 2);
    end;
  end;
end;

procedure Tdatemngfrm.DBGrid1CellClick(Column: TColumn);
begin
  DATA_ID := DBQuery.FieldByName('DATA_ID').AsInteger;
  datestr.Text := DBQuery.FieldByName('STAGE_VALUE').AsString;
end;

procedure Tdatemngfrm.DBGrid2DblClick(Sender: TObject);
begin
  STAGE_ID := DBQueryTmp.FieldByName('STAGE_ID').AsInteger;
  if length(trim(datestr.Text)) > 0 then
  begin
    datestr.Text := trim(datestr.Text) + ',' + inttostr(STAGE_ID);
  end
  else
  begin
    datestr.Text := inttostr(STAGE_ID);
  end;
end;

procedure Tdatemngfrm.datemodClick(Sender: TObject);
var
  sSql: string;
begin
  dateval := trim(datestr.Text);
  if dateval = '' then
  begin
    FuncShowMessage(Application.Handle, '日期数据不能为空！', 2);
    exit;
  end;
  if  getrightdate(dateval) then
  begin
    FuncShowMessage(Application.Handle, '你选择的时间段存在重复时间！', 2);
    exit;
  end;
  if funcConnectDB() then
  begin
    sSql := 'update ykt_cur.T_STATIUM_FEEDATE set STAGE_VALUE=''' + datestr.Text + ''',OPERATOR=''' + PtUser.GetUserName + ''' where DATA_ID=' + inttostr(DATA_ID) + '';
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
  dateview;
  datestr.Text := '';
end;

end.

