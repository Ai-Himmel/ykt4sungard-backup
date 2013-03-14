unit UrptTbl;

interface

uses
  Windows, Messages, SysUtils, Classes, Controls, Dialogs, StdCtrls, ExtCtrls,
  INIFiles, Db,ZAbstractRODataset, ZAbstractDataset, ZDataset,UCMqhReportImp;

  //procedure execSQL(sqlStr:string);
  function execSQL_SLite(sqlStr:string):Integer;
  function  irptOperCashSql(tmpData:TDataSet): string ;
  function  irptOperCardSql(tmpData:TDataSet): string ;
  function  irptsysstatSql(tmpData:TDataSet): string ;
  function  irptsubjledgerSql(tmpData:TDataSet): string ;
  function  irptsubjbalSql(tmpData:TDataSet): string ;
  function  irptDailyAccSql(tmpData:TDataSet):string ;
  function  irptAccLeager(tmpData:TDataSet): string;
  function  irptRptShopMeal(tmpData:TDataSet): string;
  function  irptPosLeager(tmpData:TDataSet): string;
  function  irptPosMeal(tmpData:TDataSet): string;
  function  irptBusiRunStat(tmpData:TDataSet): string;
  function  irptOperRptSql(tmpData:TDataSet): string ;
  function  irptBusiFee(tmpData:TDataSet): string;
  function  irptDestoryCardSql(tmpData:TDataSet;i:Integer):string ;
  function  irptOperCashTotRptSql(tmpData:TDataSet):string;
  function  irptBalanceSql(tmpData:TDataSet): string ;

  const delrptsysstat = 'delete from t_rptsysstat';
  const delrptsubjledger = 'delete from T_RPTSUBJLEDGER';
  const delrptsubjbal = 'delete from t_rptsubjbal';
  const delrptopercash = 'delete from T_RPTOPERCASH';
  const delrptOperCard = 'delete from T_RPTOPERCARD';
  const delrptdailyacc = 'delete from T_RPTDAILYACC';
  const delrptAccLeager = 'delete from T_RPTACCLEDGER';
  const delrptShopMeal = 'delete from T_RPTSHOPMEAL';
  const delrptPosLeager = 'delete from T_RPTPOSLEDGER';
  const delPosMeal = 'delete from t_rptposmeal';
  const delShopAcc='delete from T_RPTSHOPACC';

  const beginTrans = 'BEGIN TRANSACTION';      
  const commitTrans = 'COMMIT';
  const rollBackTrans = 'ROLLBACK';

implementation
{
procedure  execSQL(sqlStr:string);
var
  qry:TZQuery;
begin
  qry := nil;
  try
    try
      qry := TZQuery.Create(nil);
      qry.Connection := dmReportImp.conFB;
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
}
function  execSQL_SLite(sqlStr:string):Integer;
var
  qry:TZQuery;
begin
  qry := nil;
  try
    try
      qry := TZQuery.Create(nil);
      qry.Connection := dmReportImp.conSLite;
      qry.Close;
      qry.SQL.Clear;
      qry.SQL.Add(sqlStr);
      qry.ExecSQL;
    except
      on e:Exception do
      begin
        ShowMessage('SQLite执行错误,安装目录不能是中文--'+e.Message);
        Result := -1;
        Exit;
      end;
    end;
    Result := 0;
  finally
    qry.Close;
    qry.Destroy;
  end;
end;
//系统运行情况表
function  irptsysstatSql(tmpData:TDataSet): string ;
var
  sqlStr :string;
begin
  sqlstr := 'insert into t_rptsysstat(accdate,itemid,itemname,itemval)values(';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sdate3').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('lvol1').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('vsvarstr0').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('damt0').AsString+#39+')';
  Result := sqlStr;
end;

//科目余额表
function  irptsubjbalSql(tmpData:TDataSet): string ;
var
  sqlStr :string;
begin
  sqlstr := 'insert into T_RPTSUBJBAL(ACCDATE,SUBJNO,SUBJNAME,DRBEGINBAL,';
  sqlStr := sqlStr+'CRBEGINBAL,DRAMT,CRAMT,DRENDBAL,CRENDBAL)values(';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sdate3').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt1').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt2').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt3').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt4').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt5').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt6').AsString+')';
  Result := sqlStr;
end;

//收支平衡表
function  irptBalanceSql(tmpData:TDataSet): string ;
var
  sqlStr :string;
begin
  sqlstr := 'insert into T_RPTSUBJBAL(ACCDATE,SUBJNO,SUBJNAME,DRBEGINBAL,';
  sqlStr := sqlStr+'CRBEGINBAL,DRAMT,CRAMT,DRENDBAL,CRENDBAL)values(';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sdate0').AsString+#39+',';
  sqlstr:=sqlstr+#39+''+#39+',';
  sqlstr:=sqlstr+#39+''+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt0').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt1').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt2').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt3').AsString+',';
  sqlstr:=sqlstr+'0'+',';
  sqlstr:=sqlstr+'0'+')';
  Result := sqlStr;
end;

//科目分类汇总表
function  iRptsubjledgerSql(tmpData:TDataSet): string ;
var
  sqlStr :string;
begin
  sqlstr := 'insert into T_RPTSUBJLEDGER(ACCDATE,SUBJNO,SUBJNAME,TRANSTYPE,';
  sqlStr := sqlStr+'SUMMARY,TRANSCNT,DRAMT,CRAMT,DRBAL,CRBAL)values(';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sdate3').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('lbank_acc_type2').AsString+',';
  sqlstr:=sqlstr+#39+tmpData.fieldbyname('snote').AsString+#39+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('lvol0').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt1').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt2').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt3').AsString+',';
  sqlstr:=sqlstr+tmpData.fieldbyname('damt4').AsString+')';
  Result := sqlStr;
end;

//操作员现金报表
function irptOperCashSql(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTOPERCASH(ACCDATE,BRANCHNO,BRANCHNAME,OPERCODE,';
  sqlStr := sqlStr +'OPERNAME,SUBJNO,TRANSTYPE,BEGINTIME,ENDTIME,SUMMARY,TRANSCNT,INAMT,OUTAMT) values(';
  if Trim(tmpData.fieldbyname('sdate3').AsString)='' then
    sqlStr := sqlStr +#39+ '99991231'+#39+','
  else
    sqlStr := sqlStr +#39+ tmpData.fieldbyname('sdate3').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lbank_acc_type2').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr2').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('semp_no').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlStr := sqlStr + '0' +',';
  try
    sqlStr := sqlStr +#39+ tmpData.fieldbyname('sorder1').AsString+#39+',';
    sqlStr := sqlStr +#39+ tmpData.fieldbyname('sorder2').AsString+#39+',';
  except
    sqlStr := sqlStr +#39+ '000001'+#39+',';
    sqlStr := sqlStr +#39+ '235959'+#39+',';
  end;
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString+')';
  Result := sqlStr;
end;


{-------------------------------------------------------------------------------
  过程名:    irptOperRptSql操作员现金汇总报表
  作者:      hanjiwei
  日期:      2009.07.09
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function irptOperCashTotRptSql(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTOPERCASH(ACCDATE,BRANCHNO,BRANCHNAME,OPERCODE,';
  sqlStr := sqlStr +'OPERNAME,SUBJNO,TRANSTYPE,BEGINTIME,ENDTIME,SUMMARY,TRANSCNT,INAMT,OUTAMT) values(';
  sqlStr := sqlStr +#39+ '99991231'+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lbank_acc_type2').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr2').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('semp_no').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('scust_auth').AsString+#39+',';
  sqlStr := sqlStr + '0' +',';
  sqlStr := sqlStr +#39+ '0'+#39+',';
  sqlStr := sqlStr +#39+ '0'+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptOperRptSql操作员业务报表
  作者:      hanjiwei
  日期:      2009.07.09
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function irptOperRptSql(tmpData:TDataSet):string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTOPERCASH(ACCDATE,BRANCHNO,BRANCHNAME,OPERCODE,';
  sqlStr := sqlStr +'OPERNAME,SUBJNO,TRANSTYPE,BEGINTIME,ENDTIME,SUMMARY,TRANSCNT,INAMT,OUTAMT) values(';
  sqlStr := sqlStr +#39+ '99991231'+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('sstock_code').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr2').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('semp_no').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr +#39+ '0'+#39+',';
  sqlStr := sqlStr + '0' +',';
  sqlStr := sqlStr +#39+ '0'+#39+',';
  sqlStr := sqlStr +#39+ '0'+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt0').AsString+',';
  sqlStr := sqlStr + '0'+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptOperCardSql操作员卡片使用情况
  作者:      hanjiwei
  日期:      2008.12.29
  参数:      tmpData:TDataSet;statType:string数据集
  返回值:    string
-------------------------------------------------------------------------------}
function  irptOperCardSql(tmpData:TDataSet): string ;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTOPERCARD(ACCDATE,BRANCHNO,BRANCHNAME,OPERCODE,OPERNAME,CARDTYPE,';
  sqlStr := sqlStr + 'CARDTYPENAME,USETYPE,SUMMARY,TRANSCNT,INCNT,OUTCNT,REMAINCNT) values(';
  if Trim(tmpData.fieldbyname('sdate3').AsString)='' then
    sqlStr := sqlStr +#39+ '99991231'+#39+','
  else
    sqlStr := sqlStr +#39+ tmpData.fieldbyname('sdate3').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lbank_acc_type2').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr2').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('semp_no').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lsafe_level').AsString +',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('semail').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lbank_acc_type').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol2').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol3').AsString+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptDailyAcc商户日统计表
  作者:      hanjiwei
  日期:      2008.12.29
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptDailyAccSql(tmpData:TDataSet):string ;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTDAILYACC(SHOPID,FSHOPID,SHOPNAME,';
  sqlStr := sqlStr +'TRANSCNT,DRAMT,CRAMT,TRANSAMT,RATE,SORTID) values(';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString +',';
  sqlStr := sqlStr +tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt3').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('drate0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptAccLeager商户当日结算表
  作者:      hanjiwei
  日期:      2008.12.29
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptAccLeager(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTACCLEDGER(shopid,FSHOPID,SHOPNAME,';
  sqlStr := sqlStr +'TRANSTYPE,SUMMARY,TRANSCNT,DRAMT,CRAMT,balance,SORTID,ACCDATE) values(';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt3').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+',';
  sqlStr := sqlStr + #39+tmpData.fieldbyname('sdate3').AsString+#39+')';
  Result := sqlStr;
end;
                                                     
{-------------------------------------------------------------------------------
  过程名:    irptRptShopMeal商户汇总结算-分餐
  作者:      hanjiwei
  日期:      2008.12.30
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptRptShopMeal(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into t_rptshopmeal(SHOPID,FSHOPID,SHOPNAME,';
  sqlStr := sqlStr +'TRANSCNT1,TRANSAMT1,TRANSCNT2,TRANSAMT2,';
  sqlStr := sqlStr +'TRANSCNT3,TRANSAMT3,TRANSCNT4,TRANSAMT4,TOTCNT,TOTAMT,SORTID) values(';
  sqlStr := sqlStr +tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr +'0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol6').AsString +',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt6').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol7').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt7').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol8').AsString +',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt8').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol9').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt9').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol10').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt10').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptPosLeagerPos分类结算表
  作者:      hanjiwei
  日期:      2009.01.01
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptPosLeager(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTPOSLEDGER(ACCDATE,SHOPID,FSHOPID,';
  sqlStr := sqlStr +'DEVICEID,DEVICENAME,SHOPNAME,TRANSTYPE,';
  sqlStr := sqlStr +'SUMMARY,TRANSCNT,DRAMT,CRAMT,AMOUNT,TRANSDATE,SORTID) values(';
  sqlStr := sqlStr +tmpData.fieldbyname('sdate0').AsString+',';
  sqlStr := sqlStr +tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr +'0'+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lwithdraw_flag').AsString +',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sbankname').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial0').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString +',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt3').AsString+',';
  sqlStr := sqlStr +#39+ '99991231' +#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+')';
  Result := sqlStr;
end;

{-------------------------------------------------------------------------------
  过程名:    irptPosMealPos分类结算表
  作者:      hanjiwei
  日期:      2009.01.01
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptPosMeal(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into t_rptposmeal(SHOPID,FSHOPID,SHOPNAME,DEVICENAME,';
  sqlStr := sqlStr +'DEVICEID,TRANSTYPE,SUMMARY,MEALNAME,';
  sqlStr := sqlStr +'TRANSCNT,DRAMT,CRAMT,AMOUNT,MEALTYPE,SORTID) values(';
  sqlStr := sqlStr +tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr +'0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sbankname').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lwithdraw_flag').AsString +',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial0').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('snote').AsString+#39+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt2').AsString +',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt3').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+')';
  Result := sqlStr;
end;


{-------------------------------------------------------------------------------
  过程名:    irptAccLeager商户营业情况表
  作者:      hanjiwei
  日期:      2008.12.29
  参数:      tmpData:TDataSet
  返回值:    string
-------------------------------------------------------------------------------}
function  irptBusiRunStat(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTSHOPACC(ACCDATE, LINENO, SHOPID, SHOPNAME,';
  sqlStr := sqlStr +'FSHOPID, SHOPTYPE, SHOPCODE, DEVICEID, DEVICENAME, TRANSCNT, DRAMT, CRAMT, AMOUNT, BALANCE) values(';
  sqlStr := sqlStr +#39+ FormatDateTime('yyyymmdd',Now)+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+'0'+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lwithdraw_flag').AsString+',';
  sqlStr := sqlStr +#39+tmpData.fieldbyname('sbankname').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt3').AsString+',';
  sqlStr := sqlStr + '0'+')';
  Result := sqlStr;
end;

function  irptBusiFee(tmpData:TDataSet): string;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTACCLEDGER(shopid,FSHOPID,SHOPNAME,';
  sqlStr := sqlStr +'TRANSTYPE,SUMMARY,TRANSCNT,DRAMT,CRAMT,balance,SORTID) values(';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol3').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('vsvarstr1').AsString+#39+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+'0'+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('Lvol0').AsString+',';
  sqlStr := sqlStr + tmpData.fieldbyname('damt0').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lserial1').AsString+')';
  Result := sqlStr;
end;

function  irptDestoryCardSql(tmpData:TDataSet;i:Integer):string ;
var
  sqlStr :string;
begin
  sqlStr := 'insert into T_RPTDAILYACC(SHOPID,FSHOPID,SHOPNAME,';
  sqlStr := sqlStr +'TRANSCNT,DRAMT,CRAMT,TRANSAMT,SORTID) values(';
  sqlStr := sqlStr + IntToStr(i)+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr +#39+ tmpData.fieldbyname('sall_name').AsString+#39+',';
  sqlStr := sqlStr + tmpData.fieldbyname('lvol0').AsString +',';
  sqlStr := sqlStr +tmpData.fieldbyname('damt0').AsString+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + '0'+',';
  sqlStr := sqlStr + '0'+')';
  Result := sqlStr;
end;


end.
