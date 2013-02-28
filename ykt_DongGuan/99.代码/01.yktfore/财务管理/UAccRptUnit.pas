unit UAccRptUnit;

interface
uses
  Windows, Messages, SysUtils, Classes, Controls, Dialogs, StdCtrls, ExtCtrls,
  INIFiles, Db,ZAbstractRODataset, ZAbstractDataset, ZDataset,UAccountMgrImp;

  procedure execSQL(sqlStr:string);
  function insertStr(tmpData:TDataSet):string;

  function insertSubjTot(tmpData:TDataSet):string;
  function insertBusiDtlRpt(tmpData:TDataSet):string;
  function insertBusiStatRpt(tmpData:TDataSet):string;
  function calcSubTot:string;

  const delaccquery = 'delete from accountquery';
  const delsubjtot = 'delete from subjtot';
  const delrpttemp = 'delete from rpttemp';
  const beginTrans = 'BEGIN TRANSACTION';
  const commitTrans = 'COMMIT';
  const rollBackTrans = 'ROLLBACK';
  //const calcSubTot = '';


implementation

procedure  execSQL(sqlStr:string);
var
  qry:TZQuery;
begin
  qry := nil;
  try
    try
      qry := TZQuery.Create(nil);
      qry.Connection := cmAccountMgrImp.conFB;
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(sqlStr);
      qry.ExecSQL;
    except
      on e:Exception do
        ShowMessage('本地数据库执行错误--'+e.Message);
    end;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;

function insertStr(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlstr := 'insert into accountquery(lineno,accdate,voucherno,';
  sqlStr := sqlStr+'summary,debit,credit,direction,balance)values(';
  sqlstr:=sqlstr+tmpData.fieldbyname('lserial1').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sorder0').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('snote').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt1').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt2').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_type').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt3').AsString+')';
  Result := sqlStr;
end;

function insertSubjTot(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlstr := 'insert into subjtot(lineno,subjno,subjname,';
  sqlStr := sqlStr+'damt1,damt2,damt3,damt4,damt5,damt6)values(';
  sqlstr:=sqlstr+tmpData.fieldbyname('lserial1').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scusttypes').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt1').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt2').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt3').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt4').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt5').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt6').AsString+')';
  Result := sqlStr;
end;

function insertBusiDtlRpt(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlstr := 'insert into rpttemp(lineno,cid,cname,accdate,';
  sqlStr := sqlStr+'tmp1,tmp2,tmp3,tmp4,tmp5,tmp6)values(';
  sqlstr:=sqlstr+tmpData.fieldbyname('lserial1').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sorder1').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('snote').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sorder0').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sholder_ac_no').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sname').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone2').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_type').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone3').AsString+#39+')';
  Result := sqlStr;
end;

function insertBusiStatRpt(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlstr := 'insert into rpttemp(lineno,cid,cname,accdate,';
  sqlStr := sqlStr+'tmp1,tmp2,tmp3,tmp4,tmp5,tmp6)values(';
  sqlstr:=sqlstr+tmpData.fieldbyname('lserial1').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scusttypes').AsString+#39+',';
  sqlstr:=sqlstr+#39+''+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sphone2').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('Semail').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('Semail2').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scert_no').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scert_no2').AsString+#39+')';
  Result := sqlStr;
end;


function calcSubTot:string;
var
  str:string;
begin
  str := 'select sum(damt1)damt1,sum(damt2)damt2,sum(damt3)damt3,';
  str := str+' sum(damt4)damt4,sum(damt5)damt5,sum(damt6)damt6';
  str := str+' from subjtot where length(subjno)=4';
  Result := str;
end;

end.
 