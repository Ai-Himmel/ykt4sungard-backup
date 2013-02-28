CREATE OR REPLACE VIEW V_AUTOTRANSCFG AS
SELECT  t.transname,c."TRANSCODE",c."TRANSTYPE",c."DRSUBJNO",d.subjname,c."CRSUBJNO",e.subjname crsubjname,c."DRFLAG",c."CRFLAG",c."DRDESC",c."CRDESC"
     FROM t_transcode t,t_cfgsplit c,t_subject d,t_subject e
    WHERE t.transcode=c.transcode and c.drsubjno=d.subjno and c.crsubjno=e.subjno;

CREATE OR REPLACE VIEW V_DAYACCMERCH AS
SELECT accdate,merchid,transcode,transdate,sum(transcnt) totalcnt,sum(transamt) totalamt
     FROM t_daystatmerch  where validtype=1 and  transamt!=0
     and accdate=(select settledate from t_settlectl where booksetno=1)
     group by accdate,merchid,transcode,transdate;
CREATE OR REPLACE VIEW V_DAYACCOPER AS
SELECT accdate,operid,branchid,transcode,transdate,count(*) transcnt,sum(inamt-outamt) transamt
     FROM t_operaccdtl  where accdate=(select settledate from t_settlectl where booksetno=1)
     group by accdate,operid,branchid,transcode,transdate;
CREATE OR REPLACE VIEW V_DAYACCSUBJ AS
SELECT accdate,transcode,transdate,sum(transcnt) totalcnt,sum(transamt) totalamt
from
(SELECT accdate,transcode,transdate,transcnt,transamt
     FROM t_dayaccoper  where transamt!=0
     and accdate=(select settledate from t_settlectl where booksetno=1)
     union all
SELECT accdate,transcode,transdate,transcnt,transamt
     FROM t_daystatbankterm  where validtype=1 and  transamt!=0
     and accdate=(select settledate from t_settlectl where booksetno=1)) t
    group by accdate,transcode,transdate;


CREATE OR REPLACE VIEW V_DAYSTATBANKTERM AS
SELECT accdate, 1 validtype,samno,cardtype,transcode,hostdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_banktransdtl  where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status=3
group by accdate,samno,cardtype,transcode,hostdate
union all
SELECT accdate,2 validtype,samno,cardtype,transcode,hostdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_banktransdtl  where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status<>3
group by accdate,samno,cardtype,transcode,hostdate;

CREATE OR REPLACE VIEW V_DAYSTATDPSTERM AS
SELECT accdate, 1 validtype,samno,operid,cardtype,transcode,hostdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_dpsdtl  where  accdate=(select settledate from t_settlectl where booksetno=1)
     and ( status=3 or status=4 )
group by accdate,samno,operid,cardtype,transcode,hostdate
union all
SELECT accdate,2 validtype,samno,operid,cardtype,transcode,hostdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_dpsdtl  where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status<>3 and status<>4
group by accdate,samno,operid,cardtype,transcode,hostdate;

CREATE OR REPLACE VIEW V_DAYSTATMERCH AS
SELECT accdate,1 validtype,merchid,cardtype,transcode,termdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status='S'
     group by accdate,merchid,cardtype,transcode,termdate
union all
SELECT accdate,2 validtype,merchid,cardtype,transcode,termdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status<>'S'
     group by accdate,merchid,cardtype,transcode,termdate;
CREATE OR REPLACE VIEW V_DAYSTATOPER AS
SELECT accdate,operid,branchid,transcode,hostdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_operdtl  where accdate=(select settledate from t_settlectl where booksetno=1)
     group by accdate,operid,branchid,transcode,hostdate;
	 
CREATE OR REPLACE VIEW V_DAYSTATPOS AS
SELECT accdate,1 validtype,samno,merchid,cardtype,transcode,termdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status='S'
     group by accdate,samno,merchid,cardtype,transcode,termdate
union all
SELECT accdate,2 validtype,samno,merchid,cardtype,transcode,termdate transdate,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status<>'S'
     group by accdate,samno,merchid,cardtype,transcode,termdate;
	 
CREATE OR REPLACE VIEW V_DAYSTATPKGFILE AS
SELECT accdate,1 validtype,fileid,merchid,samno,cardtype,transcode,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status='S'
     group by accdate,fileid,merchid,samno,cardtype,transcode
union all
SELECT accdate,2 validtype,fileid,merchid,samno,cardtype,transcode,count(*) transcnt,sum(amount) transamt
     FROM t_posdtl where  accdate=(select settledate from t_settlectl where booksetno=1)
     and status<>'S'
     group by accdate,fileid,merchid,samno,cardtype,transcode;
	 
create or replace view v_allsubject as
select subjno,subjfullname from t_subject
union all
select merchid,'应付账款/商户营业款/'||merchname from t_merch;

CREATE OR REPLACE VIEW V_DICTIONARY AS
	SELECT dicttype, dictval, dictcaption
	  FROM ykt_cur.t_dictionary
	UNION ALL
	SELECT -1 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
	  FROM ykt_cur.t_cardtype
	UNION ALL
	SELECT -2 dicttype, TO_CHAR (branchid) dictval,
		   branchname dictcaption
	  FROM ykt_cur.t_branch
	 WHERE status = 1
	UNION ALL
	SELECT -3 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
	  FROM ykt_cur.t_site
	UNION ALL
	SELECT -4 dicttype, TO_CHAR (cardphytype) dictval, cardphytypename dictcaption
	  FROM ykt_cur.t_cardphytype
	 WHERE useflag=1
	UNION ALL
	SELECT -5 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
	  FROM ykt_cur.t_cardtype
	 WHERE anonymflag = 0
	UNION ALL
	SELECT -6 dicttype, TO_CHAR (transcode) dicttype, transname dictcaption
	  FROM ykt_cur.t_transcode
	 WHERE feeflag = 1 OR transcode IN (3000, 3020, 3100, 3170)
	UNION ALL
	SELECT -7 dicttype, TO_CHAR (transcode) dicttype, transname dictcaption
	  FROM ykt_cur.t_transcode
	UNION ALL
	SELECT -8 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
	  FROM ykt_cur.t_transcode
	UNION ALL
	SELECT -9 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
	  FROM ykt_cur.t_site
    UNION ALL
	SELECT -15 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
	 FROM ykt_cur.t_transcode
	WHERE feeflag = 1
	   OR transflag = 1
	   OR (transcode > 3000 AND transcode < 4000)
	UNION ALL
	SELECT -16 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
	 FROM ykt_cur.t_transcode
	WHERE feeflag = 1 OR transflag = 1 OR transcode IN (3220)
	UNION ALL
	SELECT -17 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
	  FROM ykt_cur.t_cardtype
	 WHERE anonymflag = 1
	UNION ALL
	SELECT -18 dicttype, TO_CHAR (bankid) dictval, bankname dictcaption
	  FROM ykt_cur.t_bank
	UNION ALL
	SELECT -20 dicttype, opercode dictval, opername dictcaption
	  FROM ykt_cur.t_operator
	 WHERE opertype = 1 AND status <> 2
	UNION ALL
	SELECT -21 dicttype, to_char(operid) dictval, opername dictcaption
	  FROM ykt_cur.t_operator
	UNION ALL
	SELECT -24 dicttype, TO_CHAR (errcode) dictval, errmsg dictcaption
	  FROM ykt_cur.t_errcode
	UNION ALL
	SELECT -25 dicttype, to_char(subjno) dictval, subjname dictcaption
	  FROM ykt_cur.t_subject
	UNION ALL
	SELECT -27 dicttype, areacode dictval, areaname dictcaption
	  FROM ykt_cur.t_area   WHERE arealevel = 2
	UNION ALL
	SELECT -28 dicttype, areacode dictval, areaname dictcaption
	  FROM ykt_cur.t_area
	UNION ALL
	SELECT -29 dicttype, TO_CHAR (modulecode) dictval, modulename dictcaption
	  FROM ykt_cur.t_moduleauth
	UNION ALL
	SELECT -30 dicttype, opercode dictval, opername dictcaption
	  FROM ykt_cur.t_operator
	 WHERE opertype <> 0 AND status <> 2
	UNION ALL
	SELECT -32 dicttype, TO_CHAR (sysid) dictval, sysname dictcaption
	  FROM ykt_cur.t_subsystem
	 WHERE status = 1
	UNION ALL
	SELECT -33 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
	  FROM ykt_cur.t_site
	UNION ALL
	SELECT -35 dicttype, TO_CHAR (phytype) dictval, dname dictcaption
	  FROM ykt_cur.t_phydevice
	UNION ALL
	SELECT -36 dicttype, deptcode dictval, deptfullname dictcaption
	  FROM ykt_cur.t_dept
	UNION ALL
	SELECT -38 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
	  FROM ykt_cur.t_transcode
	UNION ALL
	SELECT -47 dicttype, TO_CHAR (sysid) dictval, sysname dictcaption
	  FROM ykt_cur.t_subsystem
	 WHERE status = 1
	UNION ALL
	SELECT -55 dicttype, TO_CHAR (transtype) dictval, transname dictcaption
	  FROM ykt_cur.t_transtype
	UNION ALL
	SELECT -56 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
	  FROM ykt_cur.t_cardtype
	UNION ALL
	select -60 dicttype,dictval,dictcaption from ykt_cur.t_dictionary where dicttype=128
	UNION ALL
	SELECT distinct -61 dicttype, to_char(vouchertype) dictval, vouchertypename dictcaption FROM ykt_cur.t_vouchertype
	UNION ALL
	SELECT distinct -62 dicttype, to_char(authtype) dictval, authtypename dictcaption FROM ykt_cur.t_authtype
	UNION ALL
	SELECT distinct -70 dicttype, to_char(subjlevel) dictval, to_char(subjlevel)||'级' dictcaption FROM ykt_cur.t_subject
	UNION ALL
	SELECT distinct -71 dicttype, to_char(subjno) dictval, subjname dictcaption FROM ykt_cur.t_subject where endflag=1 and subjclass=2
	union all 
	select -80 dicttype,to_char(factoryid) dictval,factoryname dictcaption from ykt_cur.t_cardfactory
	union all 
	select -90 dicttype,to_char(merchid) dictval,merchname dictcaption from ykt_cur.t_merch;
