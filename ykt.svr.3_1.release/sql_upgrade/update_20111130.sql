-- 20110911  phy
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '事件代码', '153', '手持机签到');

commit;

-- 20110927  xu sheng
update ykt_cur.T_DICTIONARY set DICTCAPTION='体锻-起点' where DICTTYPE = '81' and DICTVAL = '1005';
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION) values (81, '设备用途', '1006', '体锻-终点');
commit;

--20111018  phy 
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
		  
-- 20111020 yym 解决ecard 新增的一卡通商户pos流水查询功能无法查询到数据的问题。
grant select on ykt_cur.v_transdtl to ykt_portal;
grant select on ykt_cur.t_shoppos to ykt_portal;


-- 20111103 phy 解决水控器扣主钱包费用的流水自动收到t_purseposdtl的bug
insert into t_dictionary (dicttype,dicttypename,dictval,dictcaption) values (47,'汇多机型','0251','计时水控-主钱包');
insert into t_dictionary (dicttype,dicttypename,dictval,dictcaption) values (47,'汇多机型','0252','计量水控-主钱包');


-- 20111225 yym 增加电子钱包的相关数据
INSERT INTO YKT_CUR.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) VALUES(14,'商户类型','3','电子支付商户');
INSERT INTO YKT_CUR.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) VALUES(24,'结算商户类型','3','电子支付商户');

insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600031,'参数不合法');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600032,'认证失败');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600033,'账户锁定');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600034,'账户止付');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600035,'账户未激活');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600036,'账户已注销');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600037,'账户异常');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600038,'账户余额不足');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600039,'后台处理失败');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600041,'重复提交');

insert into YKT_CUR.T_CFGTRANS(FEETYPE, TRANSCODE, TRANSTYPE, RATETYPE, RATEAMT, REMARK) values (999, 6230, 253, 0, null, '');
insert into YKT_CUR.T_CFGSPLIT(TRANSTYPE, FUNDTYPE, OFFLINEFLAG, USECARDFLAG, CALCCARDBAL, DRACCFLAG, DRSUBJNO, DRACCNO, CRACCFLAG, CRSUBJNO, CRACCNO, SUMMARY) values (253, 0, 0, 0, 0, 'I', '2003', '', 'I', '2004', '', '电子钱包支付');
commit;

--alter table ykt_cur.t_netacc
ALTER TABLE YKT_CUR.T_NETACC ADD PAYPWD VARCHAR(64);
ALTER TABLE YKT_CUR.T_NETACC ADD FAILEDCNT INTEGER;
ALTER TABLE YKT_CUR.T_NETACC ADD LASTLOGINTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTBLOCKTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTUNBLOCKTIME VARCHAR(14); 

comment on column YKT_CUR.T_NETACC.ACCPWD is
'帐户密码';

comment on column YKT_CUR.T_NETACC.PAYPWD is
'支付密码';

comment on column YKT_CUR.T_NETACC.STOPPAYFLAG is
'止付标志 0-正常 1-止付';

comment on column YKT_CUR.T_NETACC.STATUS is
'状态 0-未激活 1-正常 2- 锁定 3-销户';

comment on column YKT_CUR.T_NETACC.YDAYBAL is
'昨日余额（保留字段）';

comment on column YKT_CUR.T_NETACC.AVAILBAL is
'可用余额（保留字段）';

comment on column YKT_CUR.T_NETACC.FROZEBAL is
'冻结余额（保留字段）';

comment on column YKT_CUR.T_NETACC.LASTACCDATE is
'上次清算日期（保留字段）';

comment on column YKT_CUR.T_NETACC.FAILEDCNT is
'登陆失败次数';

comment on column YKT_CUR.T_NETACC.LASTLOGINTIME is
'最后登陆成功时间';

comment on column YKT_CUR.T_NETACC.LASTBLOCKTIME is
'最后锁定时间';

comment on column YKT_CUR.T_NETACC.LASTUNBLOCKTIME is
'最后解锁时间';

--alter table ykt_cur.t_shop
comment on column YKT_CUR.T_SHOP.SHOPTYPE is
'商户类型1-收费商户2-充值商户3-电子支付商户';


-- 2011-12-02 phy 解决电子钱包的无法读取卡余额的BUG
grant select on ykt_cur.t_card to ykt_epay;