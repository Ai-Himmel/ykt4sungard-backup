CREATE OR REPLACE VIEW ykt_cur.v_accdtl 
AS
   SELECT *
     FROM ykt_cur.t_accdtl;

CREATE OR REPLACE VIEW ykt_cur.v_recentaccdtl 
AS
   SELECT *
     FROM ykt_cur.t_accdtl;

CREATE OR REPLACE VIEW ykt_cur.v_transdtl 
AS
   SELECT *
     FROM ykt_cur.t_transdtl;

CREATE OR REPLACE VIEW ykt_cur.v_recenttransdtl 
AS
   SELECT *
     FROM ykt_cur.t_transdtl;

CREATE OR REPLACE VIEW ykt_cur.v_consumepostype (postype)
AS
   SELECT '0226' postype
     FROM DUAL
   UNION ALL
   SELECT '0232' postype
     FROM DUAL
   UNION ALL
   SELECT '0236' postype
     FROM DUAL
   UNION ALL
   SELECT '0244' postype
     FROM DUAL
   UNION ALL
   SELECT '0245' postype
     FROM DUAL
   UNION ALL
   SELECT '0115' postype
     FROM DUAL
   UNION ALL
   SELECT '1055' postype
     FROM DUAL
   UNION ALL
   SELECT '0228' postype
     FROM DUAL
   UNION ALL
   SELECT '5301' postype
     FROM DUAL
   UNION ALL
   SELECT '5302' postype
     FROM DUAL;

/* Formatted on 2009/06/13 21:03 (Formatter Plus v4.8.8) */
CREATE OR REPLACE VIEW ykt_cur.v_custcardinfo (stuempno,
                                                     custname,
                                                     cardno,
                                                     cardstatus,
                                                     showcardno,
                                                     cardphyid,
                                                     expiredate,
                                                     opendate,
                                                     cardverno,
                                                     cardtype,
                                                     cardtypename,
                                                     custid,
                                                     custtype,
                                                     custtypename,
                                                     deptcode,
                                                     deptname,
                                                     specialtycode,
                                                     specialtyname,
                                                     sex,
                                                     idtype,
                                                     idtypename,
                                                     idno,
                                                     areacode,
                                                     areaname,
                                                     classcode,
                                                     countrycode,
                                                     country,
                                                     email,
                                                     nationcode,
                                                     nation,
                                                     tel,
                                                     mobile,
                                                     zipcode,
                                                     cardupdtime,
                                                     custupdtime
                                                    )
AS
   SELECT /*+ FIRST_ROWS */
          c.stuempno, c.custname, t.cardno,
          (CASE
              WHEN t.status = '2'
                 THEN 2
              WHEN t.lossflag = '1'
                 THEN 3
              WHEN t.frozeflag = '1'
                 THEN 4
              WHEN t.badflag = '1'
                 THEN 4
              WHEN t.lockflag = '1'
                 THEN 4
              ELSE 1
           END
          ) cardstatus,
          t.showcardno, t.cardphyid, t.expiredate, t.opendate, t.cardverno,
          t.cardtype, d.cardtypename, t.custid, c.custtype, e.custtypename,
          c.deptcode, f.deptname, c.specialtycode, g.specialtyname, c.sex,
          c.idtype, h.dictcaption idtypename, c.idno, c.areacode, k.areaname,
          c.classcode, c.country countrycode, i.dictcaption country, c.email,
          c.nation nationcode, j.dictcaption nation, c.tel, c.mobile,
          c.zipcode, t.lastsaved cardupdtime, c.lastsaved custupdtime
     FROM t_card t
          JOIN
          (SELECT   custid, MAX (cardverno) cardverno
               FROM t_card
           GROUP BY custid,cardphytype) t2
          ON t.custid = t2.custid AND t.cardverno = t2.cardverno
          LEFT JOIN t_customer c ON t.custid = c.custid
          LEFT JOIN t_custtype e ON c.custtype = e.custtype
          LEFT JOIN t_dept f ON c.deptcode = f.deptcode
          LEFT JOIN t_specialty g ON c.specialtycode = g.specialtycode
          LEFT JOIN t_cardtype d ON t.cardtype = d.cardtype
          LEFT JOIN t_dictionary h ON c.idtype = h.dictval AND h.dicttype = 87
          LEFT JOIN t_dictionary i ON c.idtype = i.dictval AND i.dicttype = 89
          LEFT JOIN t_dictionary j ON c.idtype = j.dictval
                                 AND j.dicttype = 2001
          LEFT JOIN t_area k ON c.areacode = k.areacode
          ;

/* Formatted on 2009/06/13 21:03 (Formatter Plus v4.8.8) */
CREATE OR REPLACE VIEW ykt_cur.v_device (nu,
                                               deviceid,
                                               devicename,
                                               devphyid,
                                               devtypecode,
                                               devverno,
                                               cardphytype,
                                               svrportcnt,
                                               fdeviceid,
                                               runstatus,
                                               status,
                                               commtype,
                                               ip,
                                               portno,
                                               svrportno,
                                               deviceno,
                                               baudrate,
                                               cardset,
                                               cardverno,
                                               lastseqno,
                                               lasttranstime,
                                               purseno,
                                               maxamt,
                                               devphytype,
                                               sysid,
                                               areacode,
                                               doorlstver,
                                               devusage
                                              )
AS
   SELECT     REPLACE (SYS_CONNECT_BY_PATH (devphyid, ':'), ':', '') AS nu,
              deviceid, devicename, devphyid, devtypecode, devverno,
              cardphytype, svrportcnt, fdeviceid, runstatus, status, commtype,
              ip, portno, svrportno, deviceno, baudrate, cardset, cardverno,
              lastseqno, lasttranstime, purseno, maxamt, devphytype, sysid,
              areacode, doorlstver, devusage
         FROM ykt_cur.t_device t
   CONNECT BY PRIOR deviceid = fdeviceid
   START WITH deviceid = 1;



CREATE or replace VIEW YKT_CUR.V_DICTIONARY ( DICTTYPE, DICTVAL, DICTCAPTION ) AS
    (
        SELECT
            dicttype,
            dictval,
            dictcaption
        FROM
            ykt_cur.t_dictionary
    )
UNION ALL
    (
        SELECT
            -2 dicttype,
            TO_CHAR (branchno) dictval,
            to_char(branchname) dictcaption
        FROM
            ykt_cur.t_branch
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -3 dicttype,
            TO_CHAR (siteno) dictval,
            sitename dictcaption
        FROM
            ykt_cur.t_site
    )
UNION ALL
    (
        SELECT
            -4 dicttype,
            TO_CHAR (cardphytype) dictval,
            cardphytypename dictcaption
        FROM
            ykt_cur.t_cardphytype
        WHERE
            useflag=1
    )
UNION ALL
    (
        SELECT
            -5 dicttype,
            TO_CHAR (cardtype) dictval,
            cardtypename dictcaption
        FROM
            ykt_cur.t_cardtype
        WHERE
            anonymflag = '0'
         OR anonymflag IS NULL
    )
UNION ALL
    (
        SELECT
            -6 dicttype,
            TO_CHAR (transcode) dicttype,
            transname dictcaption
        FROM
            ykt_cur.t_transcode
        WHERE
            feeflag = 1
         OR transcode IN (3000, 3020, 3100, 3170)
    )
UNION ALL
SELECT
    -7 dicttype,
    TO_CHAR (transtype) dictval,
    transname dictcaption
FROM
    ykt_cur.t_transtype
WHERE
    displayflag = '1'
UNION ALL
    (
        SELECT
            -8 dicttype,
            TO_CHAR (transcode) dictval,
            transname dictcaption
        FROM
            ykt_cur.t_transcode
    )
UNION ALL
    (
        SELECT
            -9 dicttype,
            TO_CHAR (siteno) dictval,
            sitename dictcaption
        FROM
            ykt_cur.t_site
        UNION ALL
        SELECT
            -9 dicttype,
            TO_CHAR (deviceid) dictval,
            devicename dictcaption
        FROM
            ykt_cur.t_device
    )
UNION ALL
    (
        SELECT
            -10 dicttype,
            TO_CHAR (purseno) dictval,
            pursename dictcaption
        FROM
            ykt_cur.t_purse
    )
UNION ALL
    (
        SELECT
            -11 dicttype,
            TO_CHAR (groupid) dictval,
            groupname dictcaption
        FROM
            ykt_cur.t_doorgroup
    )
UNION ALL
    (
        SELECT
            -12 dicttype,
            TO_CHAR (weekid) dictval,
            weekname dictcaption
        FROM
            ykt_cur.t_doorweektime
    )
UNION ALL
    (
        SELECT
            -13 dicttype,
            TO_CHAR (holidayid) dictval,
            holidayname dictcaption
        FROM
            ykt_cur.t_doorholiday
    )
UNION ALL
    (
        SELECT
            -14 dicttype,
            TO_CHAR(TIMEGRPID) dictval,
            TIMEGRPNAME dictcaption
        FROM
            ykt_cur.t_doortimegrp
    )
UNION ALL
SELECT
    -15 dicttype,
    TO_CHAR (transcode) dictval,
    transname dictcaption
FROM
    ykt_cur.t_transcode
WHERE
    feeflag = '1'
 OR transflag = '1'
 OR
    (
        transcode > 3000
    AND transcode < 4000
    )
UNION ALL
SELECT
    -16 dicttype,
    TO_CHAR (transcode) dictval,
    transname dictcaption
FROM
    ykt_cur.t_transcode
WHERE
    feeflag = 1
 OR transflag = 1
 OR transcode IN (3220)
UNION ALL
SELECT
    -17 dicttype,
    TO_CHAR (cardtype) dictval,
    cardtypename dictcaption
FROM
    ykt_cur.t_cardtype
WHERE
    anonymflag = '1'
UNION ALL
SELECT
    -18 dicttype,
    TO_CHAR (bankid) dictval,
    bankname dictcaption
FROM
    ykt_cur.t_bank
UNION ALL
    (
        SELECT
            -20 dicttype,
            opercode dictval,
            opername dictcaption
        FROM
            ykt_cur.t_operator
        WHERE
            opertype = '1'
        AND status <> '2'
    )
UNION ALL
    (
        SELECT
            -21 dicttype,
            TO_CHAR (mealtype) dictval,
            TO_CHAR (mealname) dictcaption
        FROM
            ykt_cur.t_mealtype
    )
UNION ALL
    (
        SELECT
            -22 dicttype,
            deptcode dictval,
            to_char(deptname) dictcaption
        FROM
            ykt_cur.t_dept
    )
UNION ALL
    (
        SELECT
            -23 dicttype,
            specialtycode dictval,
            specialtyname dictcaption
        FROM
            ykt_cur.t_specialty
    )
UNION ALL
    (
        SELECT
            -24 dicttype,
            TO_CHAR (errcode) dictval,
            errmsg dictcaption
        FROM
            ykt_cur.t_errcode
    )
UNION ALL
    (
        SELECT
            -25 dicttype,
            subjno dictval,
            subjname dictcaption
        FROM
            ykt_cur.t_subject
    )
UNION ALL
    (
        SELECT
            -26 dicttype,
            TO_CHAR(pursetype) dictval,
            PURSETYPENAME dictcaption
        FROM
            ykt_cur.t_pursetype
        WHERE
            ENABLEFLAG=1
    )
UNION ALL
    (
        SELECT
            -27 dicttype,
            areacode dictval,
            areaname dictcaption
        FROM
            ykt_cur.t_area
        WHERE
            arealevel = 2
    )
UNION ALL
    (
        SELECT
            -28 dicttype,
            areacode dictval,
            areaname dictcaption
        FROM
            ykt_cur.t_area
    )
UNION ALL
    (
        SELECT
            -29 dicttype,
            TO_CHAR (modulecode) dictval,
            modulename dictcaption
        FROM
            ykt_cur.t_moduleauth
    )
UNION ALL
    (
        SELECT
            -30 dicttype,
            opercode dictval,
            opername dictcaption
        FROM
            ykt_cur.t_operator
        WHERE
            opertype <> '0'
        AND status <> '2'
    )
UNION ALL
    (
        SELECT
            -31 dicttype,
            TO_CHAR (deviceid) dictval,
            devicename dictcaption
        FROM
            ykt_cur.t_device
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -32 dicttype,
            TO_CHAR (sysid) dictval,
            sysname dictcaption
        FROM
            ykt_cur.t_subsystem
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -33 dicttype,
            TO_CHAR (siteno) dictval,
            sitename dictcaption
        FROM
            ykt_cur.t_site
    )
UNION ALL
    (
        SELECT
            -34 dicttype,
            TO_CHAR (custtype) dictval,
            custtypename dictcaption
        FROM
            ykt_cur.t_custtype
    )
UNION ALL
    (
        SELECT
            -35 dicttype,
            TO_CHAR (phytype) dictval,
            dname dictcaption
        FROM
            ykt_cur.t_phydevice
    )
UNION ALL
    (
        SELECT
            -36 dicttype,
            deptcode dictval,
            deptfullname dictcaption
        FROM
            ykt_cur.t_dept
    )
UNION ALL
    (
        SELECT
            -38 dicttype,
            TO_CHAR (transcode) dictval,
            transname dictcaption
        FROM
            ykt_cur.t_transcode
    )
UNION ALL
    (
        SELECT
            -40 dicttype,
            TO_CHAR (shopid) dictval,
            TO_CHAR (shopname) dictcaption
        FROM
            ykt_cur.t_shop
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -42 dicttype,
            TO_CHAR (deviceid) dictval,
            devicename dictcaption
        FROM
            ykt_cur.t_device
        WHERE
            status = '1'
        AND devtypecode IN ('5301', '0226')
    )
UNION ALL
    (
        SELECT
            -43 dicttype,
            TO_CHAR (feetype) dictval,
            feename dictcaption
        FROM
            ykt_cur.t_feetype
        WHERE
            feetype > 0
    )
UNION ALL
    (
        SELECT
            -44 dicttype,
            TO_CHAR (feetype) dictval,
            feename dictcaption
        FROM
            ykt_cur.t_feetype
        UNION ALL
        SELECT
            -44 dicttype,
            '999' dictval,
            '通用类别' dictcaption
        FROM
            DUAL
    )
UNION ALL
SELECT
    -46 dicttype,
    TO_CHAR (groupid) dictval,
    groupname dictcaption
FROM
    ykt_cur.t_doorgroup
UNION ALL
    (
        SELECT
            -47 dicttype,
            TO_CHAR (sysid) dictval,
            sysname dictcaption
        FROM
            ykt_cur.t_subsystem
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -49 dicttype,
            TO_CHAR (shopid) dictval,
            to_char(shopname) dictcaption
        FROM
            ykt_cur.t_shop
        WHERE
            status = '1'
    )
UNION ALL
    (
        SELECT
            -50 dicttype,
            TO_CHAR (shopid) dictval,
            to_char(shopname) dictcaption
        FROM
            ykt_cur.t_shop t
        WHERE
            status = '1'
        AND shoptype = '2'
    )
UNION ALL
    (
        SELECT
            -51 dicttype,
            a.opercode dictval,
            b.opername dictcaption
        FROM
            ykt_cur.t_dpsoper a,
            ykt_cur.t_operator b
        WHERE
            a.opercode = b.opercode
        AND b.status = '1'
    )
UNION ALL
    (
        SELECT
            -55 dicttype,
            TO_CHAR (transtype) dictval,
            transname dictcaption
        FROM
            ykt_cur.t_transtype
    )
UNION ALL
    (
        SELECT
            -56 dicttype,
            TO_CHAR (cardtype) dictval,
            cardtypename dictcaption
        FROM
            ykt_cur.t_cardtype
    )
UNION ALL
    (
        SELECT
            -60 dicttype,
            TO_CHAR(paycode) dictval,
            summary dictcaption
        FROM
            ykt_cur.t_cfgpayment
        UNION ALL
        SELECT
            -60 dicttype,
            dictval,
            dictcaption
        FROM
            ykt_cur.t_dictionary
        WHERE
            dicttype=128
    )
UNION ALL
SELECT
    -61 dicttype,
    TO_CHAR(accchktype) dictval,
    accchktypename dictcaption
FROM
    ykt_cur.t_cfgaccchk
UNION ALL
    (
        SELECT
            -63 dicttype,
            TO_CHAR(feeid) dictval,
            feename dictcaption
        FROM
            ykt_cur.t_waterfeecfg
    )
UNION ALL
(
        select -64 dicttype,TO_CHAR(shoplevel) dictval,'第'||shoplevel||'级' dictcaption from (
			select distinct level shoplevel from t_shop t connect by prior t.shopid=t.fshopid start with t.fshopid=0 order by level)
) 	
UNION ALL
SELECT
    3002 dicttype,
    TO_CHAR (shopid) dictval,
    to_char(shopname) dictcaption
FROM
    ykt_cur.t_shop
WHERE
    shoptype=2
UNION ALL
    (
        SELECT
            3001 dicttype,
            t.areacode||t.olddeptcode dictval,
            to_char(t.deptname) dictcaption
        FROM
            ykt_cur.t_dept t
    )
UNION ALL
    (
        SELECT
            3000 dicttype,
            t.areacode||t.oldcusttype dictval,
            custtypename dictcaption
        FROM
            ykt_cur.t_custtype t
    );  
    

	  
/* Formatted on 2009/06/13 21:03 (Formatter Plus v4.8.8) */
CREATE OR REPLACE VIEW ykt_cur.v_doortimegrpdetail (timegrpid,
                                                          timegrpname,
                                                          timeid,
                                                          adddelflag,
                                                          downstatus,
                                                          updatetime,
                                                          idx
                                                         )
AS
   SELECT   timegrpid, timegrpname, timeid, adddelflag, downstatus,
            updatetime, idx
       FROM (SELECT timegrpid, timegrpname, timeid1 timeid, adddelflag,
                    downstatus, updatetime, 1 idx
               FROM ykt_cur.t_doortimegrp t1
             UNION ALL
             SELECT timegrpid, timegrpname, timeid2 timeid, adddelflag,
                    downstatus, updatetime, 2 idx
               FROM ykt_cur.t_doortimegrp t2
             UNION ALL
             SELECT timegrpid, timegrpname, timeid3 timeid, adddelflag,
                    downstatus, updatetime, 3 idx
               FROM ykt_cur.t_doortimegrp t3
             UNION ALL
             SELECT timegrpid, timegrpname, timeid4 timeid, adddelflag,
                    downstatus, updatetime, 4 idx
               FROM ykt_cur.t_doortimegrp t4
             UNION ALL
             SELECT timegrpid, timegrpname, timeid5 timeid, adddelflag,
                    downstatus, updatetime, 5 idx
               FROM ykt_cur.t_doortimegrp t5
             UNION ALL
             SELECT timegrpid, timegrpname, timeid6 timeid, adddelflag,
                    downstatus, updatetime, 6 idx
               FROM ykt_cur.t_doortimegrp t6
             UNION ALL
             SELECT timegrpid, timegrpname, timeid7 timeid, adddelflag,
                    downstatus, updatetime, 7 idx
               FROM ykt_cur.t_doortimegrp t7
             UNION ALL
             SELECT timegrpid, timegrpname, timeid8 timeid, adddelflag,
                    downstatus, updatetime, 8 idx
               FROM ykt_cur.t_doortimegrp t8) t
      WHERE timeid > 0
   ORDER BY timegrpid, idx;

/* Formatted on 2009/06/13 21:03 (Formatter Plus v4.8.8) */
CREATE OR REPLACE VIEW ykt_cur.v_sysstat (itemid, itemname, itemval)
AS
   SELECT 1 itemid, '客户总数' itemname, COUNT (1) itemval
     FROM ykt_cur.t_customer
    WHERE status = '1'
   UNION ALL
   SELECT 2, '商户账户总数', COUNT (1)
     FROM ykt_cur.t_shopacc
    WHERE status = '1'
   UNION ALL
   SELECT 3, '网络账户总数', COUNT (1)
     FROM ykt_cur.t_netacc
    WHERE status = '1'
   UNION ALL
   SELECT 4, '卡户总数', COUNT (1)
     FROM ykt_cur.t_account
    WHERE status = '1'
   UNION ALL
   SELECT 5, '日卡开户数', COUNT (1)
     FROM ykt_cur.t_account
    WHERE status = '1' AND opendate = (SELECT paraval
                                         FROM ykt_cur.t_syspara
                                        WHERE paraid = 2)
   UNION ALL
   SELECT 6, '日卡销户数', COUNT (1)
     FROM ykt_cur.t_account
    WHERE status = '2' AND closedate = (SELECT paraval
                                          FROM ykt_cur.t_syspara
                                         WHERE paraid = 2)
   UNION ALL
   SELECT 7, '挂失卡总数', COUNT (1)
     FROM ykt_cur.t_card
    WHERE status = '1' AND lossflag = '1'
   UNION ALL
   SELECT 8, '日卡挂失数', COUNT (1)
     FROM ykt_cur.t_card
    WHERE lossflag = '1' AND lossdate = (SELECT paraval
                                           FROM ykt_cur.t_syspara
                                          WHERE paraid = 2)
   UNION ALL
   SELECT 9, '冻结卡总数', COUNT (1)
     FROM ykt_cur.t_card
    WHERE status = '1' AND frozeflag = '1'
   UNION ALL
   SELECT 10, '日冻结卡数', COUNT (1)
     FROM ykt_cur.t_card t
    WHERE frozeflag = '1' AND frozedate = (SELECT paraval
                                             FROM ykt_cur.t_syspara
                                            WHERE paraid = 2)
   UNION ALL
   SELECT 11, '坏卡登记总数', COUNT (1)
     FROM ykt_cur.t_card
    WHERE status = '1' AND badflag = '1'
   UNION ALL
   SELECT 12, '日坏卡登记数', COUNT (1)
     FROM ykt_cur.t_card
    WHERE status = '1' AND badflag = '1'
          AND baddate = (SELECT paraval
                           FROM ykt_cur.t_syspara
                          WHERE paraid = 2);


/* Formatted on 2009/06/13 21:03 (Formatter Plus v4.8.8) */
CREATE OR REPLACE VIEW ykt_cur.v_term (termid, termname)
AS
   SELECT siteno termid, sitename termname
     FROM ykt_cur.t_site
   UNION ALL
   SELECT deviceid termid, devicename
     FROM ykt_cur.t_device
    WHERE deviceid > 1;
	

CREATE or replace VIEW  ykt_cur.V_POSDTL
    (
        TRANSDATE,
        TRANSTIME,
        TERMID,
        DEVPHYID,
        DEVSEQNO,
        CARDNO,
        PURSENO,
        CARDCNT,
        CARDBEFBAL,
        AMOUNT,
        CARDAFTBAL,
        MANAGEFEE,
        TRANSMARK,
        DATATYPE,
        TRANSCODE,
        SHOPID,
        SUBSIDYNO,
        BATCHNO,
        SYSID,
        COLDATE,
        COLTIME,
        ACCDATE,
        ACCTIME,
        TERMSEQNO,
        STATUS,
        ERRCODE,
        ERRMSG,
        DELFLAG
    ) AS
SELECT
    "TRANSDATE",
    "TRANSTIME",
    "TERMID",
    "DEVPHYID",
    "DEVSEQNO",
    "CARDNO",
    "PURSENO",
    "CARDCNT",
    "CARDBEFBAL",
    "AMOUNT",
    "CARDAFTBAL",
    "MANAGEFEE",
    "TRANSMARK",
    "DATATYPE",
    "TRANSCODE",
    "SHOPID",
    "SUBSIDYNO",
    "BATCHNO",
    "SYSID",
    "COLDATE",
    "COLTIME",
    "ACCDATE",
    "ACCTIME",
    "TERMSEQNO",
    "STATUS",
    "ERRCODE",
    "ERRMSG",
    "DELFLAG"
FROM
    ykt_cur.t_posdtl;

CREATE OR REPLACE VIEW ykt_cur.V_CUSTCARDINFO AS
SELECT /*+ FIRST_ROWS */
          c.stuempno, c.custname, t.cardno,
          (CASE
              WHEN t.status = '2'
                 THEN 2
              WHEN t.lossflag = '1'
                 THEN 3
              WHEN t.frozeflag = '1'
                 THEN 4
              WHEN t.badflag = '1'
                 THEN 4
              WHEN t.lockflag = '1'
                 THEN 4
              ELSE 1
           END
          ) cardstatus,
          t.showcardno, t.cardphyid, t.expiredate, t.opendate, t.cardverno,
          t.cardtype, d.cardtypename, t.custid, c.custtype, e.custtypename,
          c.deptcode, f.deptname, c.specialtycode, g.specialtyname, c.sex,
          c.idtype, h.dictcaption idtypename, c.idno, c.areacode, k.areaname,
          c.classcode classcode,c.classname classname, c.country countrycode, 
		  i.dictcaption countryname, c.email, c.nation nationcode, j.dictcaption nationname, 
		  c.tel, c.mobile, c.zipcode, t.lastsaved cardupdtime, c.lastsaved custupdtime,
		  to_number(substr(cardphyid,7,2)||substr(cardphyid,5,2)||substr(cardphyid,3,2)||substr(cardphyid,1,2),'XXXXXXXX') CARDPHYID_DEC
     FROM t_card t
          JOIN
          (SELECT   custid,cardphytype, MAX (cardverno) cardverno
               FROM t_card
           GROUP BY custid,cardphytype) t2
          ON t.custid = t2.custid AND t.cardverno = t2.cardverno and t.cardphytype=t2.cardphytype
          LEFT JOIN t_customer c ON t.custid = c.custid
          LEFT JOIN t_custtype e ON c.custtype = e.custtype
          LEFT JOIN t_dept f ON c.deptcode = f.deptcode
          LEFT JOIN t_specialty g ON c.specialtycode = g.specialtycode
          LEFT JOIN t_cardtype d ON t.cardtype = d.cardtype
          LEFT JOIN t_dictionary h ON c.idtype = h.dictval AND h.dicttype = 87
          LEFT JOIN t_dictionary i ON c.idtype = i.dictval AND i.dicttype = 89
          LEFT JOIN t_dictionary j ON c.idtype = j.dictval
                                 AND j.dicttype = 2001
          LEFT JOIN t_area k ON c.areacode = k.areacode;
--照片视图
create or replace view  ykt_cur.v_minphoto as 
select a.custid,b.stuempno,b.custname,a.minphoto,a.photoexacttime photoacttime,a.ifcard 
from ykt_cur.t_photo a,ykt_cur.t_customer b where a.custid=b.custid;
--卡状态视图
create or replace view  ykt_cur.v_cardver as 
select a.cardverno,a.cardno,a.cardphyid,a.stuempno,b.custid,a.cardvertype,a.status 
from ykt_cur.t_cardver a,ykt_cur.t_card b where a.cardno=b.cardno;
--卡余额视图
create or replace view ykt_cur.v_cardbal as 
select t.cardno,t.cardbal 
from ykt_cur.t_account t;
	