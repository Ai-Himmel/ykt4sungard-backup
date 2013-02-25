--客户及卡信息视图
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
          c.classcode classname, c.country countrycode, i.dictcaption countryname, c.email,
          c.nation nationcode, j.dictcaption nationname, c.tel, c.mobile,
          c.zipcode, t.lastsaved cardupdtime, c.lastsaved custupdtime
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
--部门临时表
create table ykt_cur.T_DEPTTMP
(
  DEPTCODE     VARCHAR2(30) not null,
  AREACODE     VARCHAR2(3),
  DEPTNAME     VARCHAR2(240),
  DEPTENAME    VARCHAR2(240),
  DEPTFULLNAME VARCHAR2(1000),
  FDEPTCODE    VARCHAR2(30),
  DEPTLEVEL    INTEGER,
  LASTSAVED    VARCHAR2(30),
  primary key(DEPTCODE)
)
tablespace TS_YKT_CUR;
