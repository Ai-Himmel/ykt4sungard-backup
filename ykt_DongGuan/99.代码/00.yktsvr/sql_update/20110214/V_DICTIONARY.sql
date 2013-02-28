CREATE OR REPLACE VIEW V_DICTIONARY AS
(SELECT dicttype, dictval, dictcaption
      FROM ykt_cur.t_dictionary)
   UNION ALL
   (SELECT -1 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
      FROM ykt_cur.t_cardtype)
   UNION ALL
   (SELECT -2 dicttype, TO_CHAR (branchid) dictval,
           branchname dictcaption
      FROM ykt_cur.t_branch
     WHERE status = '1')
   UNION ALL
   (SELECT -3 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
      FROM ykt_cur.t_site)
   UNION ALL
   (SELECT -4 dicttype, TO_CHAR (cardphytype) dictval, cardphytypename dictcaption
      FROM ykt_cur.t_cardphytype
     WHERE useflag=1)
   UNION ALL
   (SELECT -5 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
      FROM ykt_cur.t_cardtype
     WHERE anonymflag = 0)
   UNION ALL
   (SELECT -6 dicttype, TO_CHAR (transcode) dicttype, transname dictcaption
      FROM ykt_cur.t_transcode
     WHERE feeflag = 1 OR transcode IN (3000, 3020, 3100, 3170))
   UNION ALL
   SELECT -7 dicttype, TO_CHAR (transtype) dictval, transname dictcaption
     FROM ykt_cur.t_transtype
    WHERE displayflag = '1'
   UNION ALL
   (SELECT -8 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
      FROM ykt_cur.t_transcode)
   UNION ALL
   (SELECT -9 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
      FROM ykt_cur.t_site
    UNION ALL
    SELECT -9 dicttype, TO_CHAR (deviceid) dictval, devicename dictcaption
      FROM ykt_cur.t_device)
   UNION ALL
   SELECT -15 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
     FROM ykt_cur.t_transcode
    WHERE feeflag = '1'
       OR transflag = '1'
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
   (SELECT -20 dicttype, opercode dictval, opername dictcaption
      FROM ykt_cur.t_operator
     WHERE opertype = '1' AND status <> '2')
   UNION ALL
   (SELECT -21 dicttype, TO_CHAR (mealtype) dictval,
           TO_CHAR (mealname) dictcaption
      FROM ykt_cur.t_mealtype)
   UNION ALL
   (SELECT -22 dicttype, deptcode dictval, deptname dictcaption
      FROM ykt_cur.t_dept)
   UNION ALL
   (SELECT -24 dicttype, TO_CHAR (errcode) dictval, errmsg dictcaption
      FROM ykt_cur.t_errcode)
   UNION ALL
   (SELECT -25 dicttype, to_char(subjno) dictval, subjname dictcaption
      FROM ykt_cur.t_subject)
   UNION ALL
   (SELECT -27 dicttype, areacode dictval, areaname dictcaption
      FROM ykt_cur.t_area
     WHERE arealevel = 2)
   UNION ALL
   (SELECT -28 dicttype, areacode dictval, areaname dictcaption
      FROM ykt_cur.t_area where arealevel = 2)
   UNION ALL
   (SELECT -29 dicttype, TO_CHAR (modulecode) dictval, modulename dictcaption
      FROM ykt_cur.t_moduleauth)
   UNION ALL
   (SELECT -30 dicttype, to_char(operid) dictval, opername dictcaption
      FROM ykt_cur.t_operator
     WHERE opertype <> '0' AND status <> '2')
   UNION ALL
   (SELECT -31 dicttype, TO_CHAR (deviceid) dictval, devicename dictcaption
      FROM ykt_cur.t_device
     WHERE status = '1')
   UNION ALL
   (SELECT -32 dicttype, TO_CHAR (sysid) dictval, sysname dictcaption
      FROM ykt_cur.t_subsystem
     WHERE status = '1')
   UNION ALL
   (SELECT -33 dicttype, TO_CHAR (siteno) dictval, sitename dictcaption
      FROM ykt_cur.t_site)
   UNION ALL
   (SELECT -34 dicttype, TO_CHAR (custtype) dictval, custtypename dictcaption
      FROM ykt_cur.t_custtype)
   UNION ALL
   (SELECT -35 dicttype, TO_CHAR (phytype) dictval, dname dictcaption
      FROM ykt_cur.t_phydevice)
   UNION ALL
   (SELECT -36 dicttype, deptcode dictval, deptfullname dictcaption
      FROM ykt_cur.t_dept)
   UNION ALL
   (SELECT -38 dicttype, TO_CHAR (transcode) dictval, transname dictcaption
      FROM ykt_cur.t_transcode)
   UNION ALL
   (SELECT -47 dicttype, TO_CHAR (sysid) dictval, sysname dictcaption
      FROM ykt_cur.t_subsystem
     WHERE status = '1')
   UNION ALL
   (SELECT -51 dicttype, a.opercode dictval, b.opername dictcaption
      FROM ykt_cur.t_dpsoper a, ykt_cur.t_operator b
     WHERE a.opercode = b.opercode AND b.status = '1')
   UNION ALL
   (SELECT -55 dicttype, TO_CHAR (transtype) dictval, transname dictcaption
      FROM ykt_cur.t_transtype)
   UNION ALL
   (SELECT -56 dicttype, TO_CHAR (cardtype) dictval, cardtypename dictcaption
      FROM ykt_cur.t_cardtype)
   UNION ALL
    select -60 dicttype,dictval,dictcaption from ykt_cur.t_dictionary where dicttype=128
   UNION ALL
    SELECT distinct -61 dicttype, to_char(vouchertype) dictval, vouchertypename dictcaption FROM ykt_cur.t_vouchertype
  UNION ALL
    SELECT distinct -62 dicttype, to_char(authtype) dictval, authtypename dictcaption FROM ykt_cur.t_authtype
  UNION ALL
    SELECT distinct -70 dicttype, to_char(subjlevel) dictval, to_char(subjlevel)||'¼¶' dictcaption FROM ykt_cur.t_subject
   UNION ALL
    SELECT distinct -71 dicttype, to_char(subjno) dictval, subjname dictcaption FROM ykt_cur.t_subject where endflag=1 and subjclass=2;
