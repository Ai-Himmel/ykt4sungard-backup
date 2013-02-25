-- 20110911  phy
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (86, '�¼�����', '153', '�ֳֻ�ǩ��');

commit;

-- 20110927  xu sheng
update ykt_cur.T_DICTIONARY set DICTCAPTION='���-���' where DICTTYPE = '81' and DICTVAL = '1005';
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION) values (81, '�豸��;', '1006', '���-�յ�');
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
		  
-- 20111020 yym ���ecard ������һ��ͨ�̻�pos��ˮ��ѯ�����޷���ѯ�����ݵ����⡣
grant select on ykt_cur.v_transdtl to ykt_portal;
grant select on ykt_cur.t_shoppos to ykt_portal;


-- 20111103 phy ���ˮ��������Ǯ�����õ���ˮ�Զ��յ�t_purseposdtl��bug
insert into t_dictionary (dicttype,dicttypename,dictval,dictcaption) values (47,'������','0251','��ʱˮ��-��Ǯ��');
insert into t_dictionary (dicttype,dicttypename,dictval,dictcaption) values (47,'������','0252','����ˮ��-��Ǯ��');


-- 20111225 yym ���ӵ���Ǯ�����������
INSERT INTO YKT_CUR.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) VALUES(14,'�̻�����','3','����֧���̻�');
INSERT INTO YKT_CUR.T_DICTIONARY(DICTTYPE,DICTTYPENAME,DICTVAL,DICTCAPTION) VALUES(24,'�����̻�����','3','����֧���̻�');

insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600031,'�������Ϸ�');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600032,'��֤ʧ��');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600033,'�˻�����');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600034,'�˻�ֹ��');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600035,'�˻�δ����');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600036,'�˻���ע��');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600037,'�˻��쳣');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600038,'�˻�����');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600039,'��̨����ʧ��');
insert into YKT_CUR.T_ERRCODE(ERRCODE,ERRMSG) values(600041,'�ظ��ύ');

insert into YKT_CUR.T_CFGTRANS(FEETYPE, TRANSCODE, TRANSTYPE, RATETYPE, RATEAMT, REMARK) values (999, 6230, 253, 0, null, '');
insert into YKT_CUR.T_CFGSPLIT(TRANSTYPE, FUNDTYPE, OFFLINEFLAG, USECARDFLAG, CALCCARDBAL, DRACCFLAG, DRSUBJNO, DRACCNO, CRACCFLAG, CRSUBJNO, CRACCNO, SUMMARY) values (253, 0, 0, 0, 0, 'I', '2003', '', 'I', '2004', '', '����Ǯ��֧��');
commit;

--alter table ykt_cur.t_netacc
ALTER TABLE YKT_CUR.T_NETACC ADD PAYPWD VARCHAR(64);
ALTER TABLE YKT_CUR.T_NETACC ADD FAILEDCNT INTEGER;
ALTER TABLE YKT_CUR.T_NETACC ADD LASTLOGINTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTBLOCKTIME VARCHAR(14);
ALTER TABLE YKT_CUR.T_NETACC ADD LASTUNBLOCKTIME VARCHAR(14); 

comment on column YKT_CUR.T_NETACC.ACCPWD is
'�ʻ�����';

comment on column YKT_CUR.T_NETACC.PAYPWD is
'֧������';

comment on column YKT_CUR.T_NETACC.STOPPAYFLAG is
'ֹ����־ 0-���� 1-ֹ��';

comment on column YKT_CUR.T_NETACC.STATUS is
'״̬ 0-δ���� 1-���� 2- ���� 3-����';

comment on column YKT_CUR.T_NETACC.YDAYBAL is
'�����������ֶΣ�';

comment on column YKT_CUR.T_NETACC.AVAILBAL is
'�����������ֶΣ�';

comment on column YKT_CUR.T_NETACC.FROZEBAL is
'�����������ֶΣ�';

comment on column YKT_CUR.T_NETACC.LASTACCDATE is
'�ϴ��������ڣ������ֶΣ�';

comment on column YKT_CUR.T_NETACC.FAILEDCNT is
'��½ʧ�ܴ���';

comment on column YKT_CUR.T_NETACC.LASTLOGINTIME is
'����½�ɹ�ʱ��';

comment on column YKT_CUR.T_NETACC.LASTBLOCKTIME is
'�������ʱ��';

comment on column YKT_CUR.T_NETACC.LASTUNBLOCKTIME is
'������ʱ��';

--alter table ykt_cur.t_shop
comment on column YKT_CUR.T_SHOP.SHOPTYPE is
'�̻�����1-�շ��̻�2-��ֵ�̻�3-����֧���̻�';


-- 2011-12-02 phy �������Ǯ�����޷���ȡ������BUG
grant select on ykt_cur.t_card to ykt_epay;