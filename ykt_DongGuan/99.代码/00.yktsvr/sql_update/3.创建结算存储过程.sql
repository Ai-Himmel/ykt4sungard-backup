create or replace procedure p_daystat is
  today       number(8);
  accday      number(8);
  settday     number(8);
  statday     number(8);
  batchday    number(8);
  prdmon      number(2);
  prdyear     number(4);
begin
  select to_number(to_char(sysdate, 'YYYYMMDD')) into today from dual;
  select settledate, accdate, statdate, batchdate, periodyear, periodmonth
    into settday, accday, statday, batchday, prdyear, prdmon
    from t_settlectl
   where booksetno = 1;
  if statday > settday then
    raise_application_error(-20000, '日终统计已完成');
  end if;
  begin
    begin
      insert into t_daystatoper
        (accdate,
         operid,
         branchid,
         transcode,
         transdate,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
               operid,
               branchid,
               transcode,
               transdate,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatoper;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20009, '操作员数据重复');
    end;
   begin
      insert into t_dayaccoper
        (accdate,
         operid,
         branchid,
         transcode,
         transdate,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
               operid,
               branchid,
               transcode,
               transdate,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_dayaccoper;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20010, '操作员账务数据重复');
    end;
    begin
      insert into t_daystatbankterm
        (accdate,
         samno,
         cardtype,
         transcode,
         transdate,
         validtype,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
               samno,
               cardtype,
               transcode,
               transdate,
               validtype,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatbankterm;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20011, '圈存终端数据重复');
    end;
    begin
      insert into t_daystatdpsterm
        (accdate,
         samno,
         operid,
         cardtype,
         transcode,
         transdate,
         validtype,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
               samno,
               operid,
               cardtype,
               transcode,
               transdate,
               validtype,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatdpsterm;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20012, '充值终端数据重复');
    end;
    begin
      insert into t_daystatpos
        (accdate,
     samno,
         merchid,
         cardtype,
         transcode,
         transdate,
         validtype,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
         samno,
               merchid,
               cardtype,
               transcode,
               transdate,
               validtype,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatpos;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20013, '消费终端数据重复');
    end;
    begin
      insert into t_daystatpos
        (accdate,
     samno,
         merchid,
         cardtype,
         transcode,
         transdate,
         validtype,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
         samno,
               merchid,
               cardtype,
               transcode,
               transdate,
               validtype,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatpay;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20014, '支付终端数据重复');
    end;
    begin
      insert into t_daystatmerch
        (accdate,
         merchid,
         cardtype,
         transcode,
         transdate,
         validtype,
         transcnt,
         transamt,
         periodyear,
         periodmonth,
         statdate)
        select accdate,
               merchid,
               cardtype,
               transcode,
               transdate,
               validtype,
               transcnt,
               transamt,
               prdyear,
               prdmon,
               today
          from v_daystatmerch;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20015, '商户数据重复');
    end;
    begin
      INSERT INTO T_DAYSTATPKGFILE
        (accdate,
         VALIDTYPE,
     PKGID,
         FILEID,
         SAMNO,
         CARDTYPE,
         MERCHID,
         TRANSCODE,
         TRANSCNT,
         TRANSAMT,
         STATDATE)
        select accdate,
               a.VALIDTYPE,
         b.PKGID,
               a.FILEID,
               a.SAMNO,
               a.CARDTYPE,
               a.MERCHID,
               a.TRANSCODE,
               a.TRANSCNT,
               a.TRANSAMT,
               today
          from v_daystatpkgfile a ,t_pkgfile b where a.fileid=b.fileid;
    exception
      when DUP_VAL_ON_INDEX then
        raise_application_error(-20016, '包裹文件数据重复');
    end;
  end;
end p_daystat;
