-- 20110427 �޸������֧�����п�����ѯ
update t_area set remark='����д��ȷ�����з��ṩ��ѧУ���룬�����ͬУ���в�ͬ����Ҳ�ڴ˴���д';

-- СǮ��δ������ת�ˣ�����޷��˿��򲹰쿨���޸�������ж��СǮ������ֶ��ִ��
insert into  t_cardbalance (accno,pursetype,cardno,oldcardno,transdate,transtime,dpscnt,paycnt,balance,cardbal,accumdpsamt)
select accno,СǮ������,cardno,0,'20110101','000000',0,0,0,0,0 from t_account where accno not in (select accno from t_cardbalance where pursetype=СǮ������) and status=1;


-- ������֧�������ô����뼰���Ӧ��Ϣ
insert into t_errcode(errcode,errmsg) values(1000,'����ʱ');
insert into t_errcode(errcode,errmsg) values(1001,'�������');
insert into t_errcode(errcode,errmsg) values(1002,'�������ݴ���');
insert into t_errcode(errcode,errmsg) values(1003,'���ӳ�ʱ');


/*==============================================================*/
/* Table: T_BANKCHKDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKDTL  (
   BANKID               INTEGER                         NOT NULL,
   BANKDATE             NUMBER(8)                       NOT NULL,
   RECORDNO             NUMBER(8)                       NOT NULL,
   AMOUNT               NUMBER(15,2)                    NOT NULL,
   TRANSDATE            NUMBER(8),
   CHKRESULT            CHAR(1)                        DEFAULT 'I',
   RESOLVED             CHAR(1)                      DEFAULT '0' NOT NULL,
   REMARK               VARCHAR(240),
   BANKCARDNO           VARCHAR(20),
   LOCALSNO             VARCHAR(20),
   BANKSNO              VARCHAR(20),
   CUSTID               INTEGER,
   STUEMPNO             VARCHAR(20),
   CARDNO               INTEGER,
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_BANKCHKDTL PRIMARY KEY (BANKID, BANKDATE, RECORDNO)
);
CREATE INDEX YKT_CUR.IDX_BANKCHKDTL_BANKCARDNO ON YKT_CUR.T_BANKCHKDTL (
   BANKCARDNO ASC
);

CREATE TABLE YKT_CUR.T_BANKCHKFILE  (
   BANKID               INTEGER                         NOT NULL,
   BANKDATE             NUMBER(8)                       NOT NULL,
   BANKCHKFILE          VARCHAR(240),
   LOCALCHKFILE         VARCHAR(240),
   LOCALCVTFILE         VARCHAR(240),
   FILESOURCE           CHAR(1),
   STATUS               CHAR(1),
   RESOLVED             CHAR(1),
   REMARK               VARCHAR(240),
   BANKCNT              INTEGER,
   BANKAMT              NUMBER(15,2),
   LOCALCNT             INTEGER,
   LOCALAMT             NUMBER(15,2),
   CRTTIME              CHAR(14),
   UPDTIME              CHAR(14),
   CONSTRAINT PK_T_BANKCHKFILE PRIMARY KEY (BANKID, BANKDATE)
);



-- ���ж������� ���ֵ�����
insert into T_FRONT (FRONTID, FRONTNAME, IP, DRTPPORT, DRTPNODE, BCCMAINFUNCNO)
values (����ǰ��ID, 'ǰ������', 'ǰ��IP', ǰ��DRTP�˿ں�, ǰ��DRTP�ڵ���, ǰ��ksmbcc�����ܺ�);    
insert into T_BANK (BANKID, BANKCODE, BANKNAME, USEFLAG, CHKACCLAG, SVRBEGINTIME, SVRENDTIME, BANKIP, BANKPORT, BANKTIMEOUT, FRONTID, CHKTYPE, CHKBEGINDATE, LASTCHKDATE, CHKBEGINTIME, CVTEXECFILE, CHKEXECFILE, AUTORESOLVE)
values (����ID, '00', '��������', 1, 1, '050000', '230000', '����IP', ���ж˿ں�, ��ʱʱ�䣨�룩, ����ǰ��ID, '�������ݣ�L��ʾ������ˮ�ţ�B��ʾ�����˺�', '��ʼ��������', '', '���˿�ʼʱ��', '���˳�������', null, 0);

insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '�����ļ�����״̬', 'I', '����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '�����ļ�����״̬', 'P', '�ݲ�����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '�����ļ�����״̬', 'C', '�ر�');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (171, '�����ļ�����״̬','E', '�쳣');

insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '����״̬', 'I', 'δ����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '����״̬', 'F', '���ض����ļ���');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '����״̬', 'V', 'ת��������');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '����״̬', 'C', '���˴�����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (170, '����״̬', 'S', '�������');

insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', '=', 'һ��');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', '/', '��һ��');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', 'X', '����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', 'U', 'һ��ͨδ����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', 'N', 'һ��ͨ�޼�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', 'B', '�����޼�¼');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (172, '������ϸ״̬', 'I', '�ȴ�����');

insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '������ϸ����״̬', '0', 'δ����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '������ϸ����״̬', 'I', '����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '������ϸ����', 'P', '�ݲ�����');
insert into ykt_cur.T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (173, '������ϸ����','A', '���˴���');

-- ����ˮ�۲������ɽ��ǰ̨�Ҳ���������bug
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK, LASTSAVED)
values (157, '0', 'ˮ�ط���1', 'Ԫ/��', '1', '�����ѻ�ˮ�صĵ�λˮ�ۣ�������λ�ɼ��������ã�1��ˮ�ۣ�', null);
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK, LASTSAVED)
values (158, '0', 'ˮ�ط���2', 'Ԫ/��', '1', '�����ѻ�ˮ�صĵ�λˮ�ۣ�������λ�ɼ��������ã�2��ˮ�ۣ�', null);
insert into ykt_cur.T_SYSPARA (PARAID, PARAVAL, PARANAME, PARAUNIT, DISPLAYFLAG, REMARK, LASTSAVED)
values (159, '0', 'ˮ�ط���3', 'Ԫ/��', '1', '�����ѻ�ˮ�صĵ�λˮ�ۣ�������λ�ɼ��������ã�3��ˮ�ۣ�', null);

commit;


grant select,update,insert,delete on ykt_cur.t_cardbalance to ykt_portal;
grant select,update,insert,delete on ykt_cur.t_account to ykt_portal;
grant select on ykt_cur.t_doordtl  to ykt_portal;
grant select on YKT_CUR.T_RPTSYSSTAT   to ykt_portal;


--ÿ��ִ��һ�εĶ�ʱ���񣬽��°쿨�û���СǮ����Ϣ����������
CREATE OR REPLACE PROCEDURE YKT_PORTAL.ANALYSIZE_SPECIALSTU_his (d1 in varchar2,
                                                     d2 in varchar2) is
   currDay  varchar2(8);
   v_error_code NUMBER;
   v_error_message VARCHAR2(255);
 begin
   select to_char(sysdate, 'yyyymmdd') into currDay from dual;
   delete from ykt_portal.T_RCSTATDATA where tx_date >= d1 and tx_date<=d2;
   commit;
     insert into ykt_portal.T_RCSTATDATA
            select cardno,meal,transdate,sum(amount) amount
            from
      (   select t.transdate,
              trim(to_char(to_date(SUBSTR(t.transdate,1,4)||'-'||SUBSTR(t.transdate,5,2)||'-'||SUBSTR(t.transdate,7,2),'yyyy-mm-dd'),'day','nls_date_language=American')) as week,
              (case when transtime <'093000' then 'bk'
                    when (transtime >='093000' and transtime<'150000') then 'lun'
                    else 'sup' end) as meal,
              t.cardno,t.devphyid,t.AMOUNT,t.transcode
          from ykt_cur.t_posdtl t
          where status='3' and t.amount>0 and transdate >= d1 and transdate <= d2
      )
      where week in ('monday','tuesday','wednesday','thursday','friday')
      group by cardno,meal,transdate;
  commit;

  delete from ykt_portal.t_rpttermledger where accdate >= d1 and accdate <= d2;
  commit;

  insert into ykt_portal.t_rpttermledger(accdate,termid,subjno,accno,transtype,summary,transcnt,dramt,cramt)
    select accdate,termid,subjno,accno,transtype,summary,count(summary),sum((2-dcflag)*amount) dramt,
    sum((dcflag-1)*amount) cramt from ykt_cur.v_accdtl  where accdate>= d1 and accdate <= d2 and subjno='2004'
    group by accdate,termid,subjno,accno,transtype,summary;
  commit;

  delete from ykt_portal.t_rptdeptledger where accdate>= d1 and accdate <= d2;
  commit;

  insert into ykt_portal.t_rptdeptledger(accdate,deptcode,subjno,transtype,summary,transcnt,dramt,cramt)
    select accdate,deptcode,subjno,transtype,summary,count(summary),sum(dramt) dramt,sum(cramt) cramt
    from (select a.accdate,a.subjno,(2-dcflag)*a.amount dramt,(dcflag-1)*amount cramt,a.transtype,a.summary,c.deptcode
    from ykt_cur.v_accdtl a,ykt_cur.t_card b,ykt_cur.t_customer c
    where a.accdate>= d1 and a.accdate <= d2 and a.accno=b.accno and b.custid=c.custid and c.deptcode is not null )
    group by accdate,deptcode,subjno,transtype,summary;

  commit;
  -- ���ж��СǮ�����ͣ��븴�ƶ��������
  insert into  ykt_cur.t_cardbalance (accno,pursetype,cardno,oldcardno,transdate,transtime,dpscnt,paycnt,balance,cardbal,accumdpsamt)
     select accno,СǮ������,cardno,0,'20110101','000000',0,0,0,0,0 from ykt_cur.t_account where accno not in (select accno from ykt_cur.t_cardbalance where pursetype=СǮ������) and status=1;
  commit;
  
EXCEPTION
  when OTHERS THEN
     null;
   v_error_code := SQLCODE;
   v_error_message := SQLERRM;
   INSERT INTO YKT_PORTAL.t_joblog( errcode,errcontent,errdate) VALUES ( v_error_code, v_error_message,to_char(sysdate, 'yyyymmdd hh24miss'));
   commit;
end;
/



-- ������֧��-�Ͼ��ѽ����ѵĶ������ݱ�
CREATE
    TABLE YKT_CUR.T_THIRDPAY_JJLINK
    (
        ECARD_ID NUMBER(14) NOT NULL,
        REQUEST_TIME VARCHAR2(20),
        ECARD_NUM VARCHAR2(20),
        USERNAME VARCHAR2(50),
        FULLNAME VARCHAR2(50),
        AMOUNT NUMBER(15,2),
        ECARD_MACHINE_ID INTEGER,
        ECARD_IP VARCHAR2(20),
        INPAYAMOUNT_ID VARCHAR2(30),
        REPLY_TIME VARCHAR2(20),
        ACK_TIME VARCHAR2(20),
        STATUS CHAR(1),
        UPDATE_TIME VARCHAR2(20),
        CHECK_NUM INTEGER DEFAULT 0 ,
        PRIMARY KEY (ECARD_ID)
    );
COMMENT ON COLUMN T_THIRDPAY_JJLINK.ECARD_ID
IS
    'һ��ͨ��ֵ��ˮ��';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.REQUEST_TIME
IS
    '��ֵ�������ʱ�� YYYY-MM-DD HH:mm:ss';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.ECARD_NUM
IS
    'һ��ͨ����';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.USERNAME
IS
    '����ֵ�û�id';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.FULLNAME
IS
    '����ֵ�û���ʵ����';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.AMOUNT
IS
    '��ֵ����λ��Ԫ';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.ECARD_MACHINE_ID
IS
    '��ֵ�豸�ն˱��';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.ECARD_IP
IS
    'һ��ͨ������IP��ַ';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.INPAYAMOUNT_ID
IS
    '��ֵ��¼��';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.REPLY_TIME
IS
    '����ʱ�� YYYY-MM-DD HH:mm:ss';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.ACK_TIME
IS
    'ȷ��ʱ�� YYYY-MM-DD HH:mm:ss';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.STATUS
IS
    '״̬��1 �����ֵ,2 ��ֵ�ɹ�,3��ֵʧ��  4 �������ݲ����� 5 ���˲���ֵ�ɹ� 6 ���˲���ֵʧ�� 7 ���˳ɹ���';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.UPDATE_TIME
IS
    '������ʱ��';
COMMENT ON COLUMN T_THIRDPAY_JJLINK.CHECK_NUM
IS
    '���˴���';


/*==============================================================*/
/* Table: T_WATERRATE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_WATERRATE  (
   FEETYPE              INTEGER                         NOT NULL,
   RATE1                INTEGER,
   RATE2                INTEGER,
   RATE3                INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_WATERRATE PRIMARY KEY (FEETYPE)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_WATERRATE.FEETYPE IS
'�շ����';

COMMENT ON COLUMN YKT_CUR.T_WATERRATE.RATE1 IS
'ˮ��1';

COMMENT ON COLUMN YKT_CUR.T_WATERRATE.RATE2 IS
'ˮ��2';

COMMENT ON COLUMN YKT_CUR.T_WATERRATE.RATE3 IS
'ˮ��3';

COMMENT ON COLUMN YKT_CUR.T_WATERRATE.LASTSAVED IS
'����ʱ��';

-- Create table
create table T_BANK
(
  BANKID       INTEGER not null,
  BANKCODE     VARCHAR2(2) not null,
  BANKNAME     VARCHAR2(60) not null,
  USEFLAG      NUMBER(1) default 0 not null,
  CHKACCLAG    NUMBER(1) default 1,
  SVRBEGINTIME VARCHAR2(6),
  SVRENDTIME   VARCHAR2(6),
  BANKIP       VARCHAR2(15),
  BANKPORT     INTEGER,
  BANKTIMEOUT  NUMBER(2),
  FRONTID      INTEGER,
  CHKTYPE      CHAR(1),
  CHKBEGINDATE NUMBER(8),
  LASTCHKDATE  NUMBER(8),
  CHKBEGINTIME VARCHAR2(6),
  CVTEXECFILE  VARCHAR2(240),
  CHKEXECFILE  VARCHAR2(240),
  AUTORESOLVE  NUMBER(1)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column T_BANK.BANKID
  is '����ID';
comment on column T_BANK.BANKCODE
  is '���д���';
comment on column T_BANK.BANKNAME
  is '��������';
comment on column T_BANK.USEFLAG
  is '�Ƿ�����';
comment on column T_BANK.CHKACCLAG
  is '�Ƿ����';
comment on column T_BANK.SVRBEGINTIME
  is '����ʼʱ��';
comment on column T_BANK.SVRENDTIME
  is '�����ֹʱ��';
comment on column T_BANK.BANKIP
  is '����IP';
comment on column T_BANK.BANKPORT
  is '���ж˿�';
comment on column T_BANK.BANKTIMEOUT
  is '���ж˳�ʱʱ��';
comment on column T_BANK.FRONTID
  is 'һ��ͨǰ�û�ID';
comment on column T_BANK.CHKTYPE
  is 'һ��ͨ�˶���';
comment on column T_BANK.CHKBEGINDATE
  is '���˿�ʼ����';
comment on column T_BANK.LASTCHKDATE
  is '�ϴζ�������';
comment on column T_BANK.CHKBEGINTIME
  is '���˿�ʼʱ��';
comment on column T_BANK.CVTEXECFILE
  is 'ת��ִ���ļ�';
comment on column T_BANK.CHKEXECFILE
  is '����ִ���ļ�';
comment on column T_BANK.AUTORESOLVE
  is '���˲����Զ�����';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANK
  add constraint PK_T_BANK primary key (BANKID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Create/Recreate indexes 
create unique index UNIQ_BANKCODE_BANKCODE on T_BANK (BANKCODE)
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

-- Create table
create table T_BANKCHKFILE
(
  BANKID       INTEGER not null,
  BANKDATE     NUMBER(8) not null,
  BANKCHKFILE  VARCHAR2(240),
  LOCALCHKFILE VARCHAR2(240),
  LOCALCVTFILE VARCHAR2(240),
  FILESOURCE   CHAR(1),
  STATUS       CHAR(1),
  RESOLVED     CHAR(1),
  REMARK       VARCHAR2(240),
  BANKCNT      INTEGER,
  BANKAMT      NUMBER(15,2),
  LOCALCNT     INTEGER,
  LOCALAMT     NUMBER(15,2),
  CRTTIME      CHAR(14),
  UPDTIME      CHAR(14)
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column T_BANKCHKFILE.BANKID
  is '���б�ʶ';
comment on column T_BANKCHKFILE.BANKDATE
  is '��������';
comment on column T_BANKCHKFILE.BANKCHKFILE
  is '���ж����ļ���';
comment on column T_BANKCHKFILE.LOCALCHKFILE
  is '���ض����ļ���';
comment on column T_BANKCHKFILE.LOCALCVTFILE
  is '����ת���ļ���';
comment on column T_BANKCHKFILE.FILESOURCE
  is '''L�� ���� ��B''����';
comment on column T_BANKCHKFILE.STATUS
  is '�˶�״̬:I����''C''�������''R''�������';
comment on column T_BANKCHKFILE.RESOLVED
  is '�����־';
comment on column T_BANKCHKFILE.REMARK
  is '��ע';
comment on column T_BANKCHKFILE.BANKCNT
  is '���м�¼����';
comment on column T_BANKCHKFILE.BANKAMT
  is '�����ܽ��';
comment on column T_BANKCHKFILE.LOCALCNT
  is '��������';
comment on column T_BANKCHKFILE.LOCALAMT
  is '�����ܽ��';
comment on column T_BANKCHKFILE.CRTTIME
  is '��¼����ʱ��';
comment on column T_BANKCHKFILE.UPDTIME
  is '��󱣴�ʱ��';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_BANKCHKFILE
  add constraint PK_T_BANKCHKFILE primary key (BANKID, BANKDATE)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );

-- Create table
create table T_FRONT
(
  FRONTID       INTEGER not null,
  FRONTNAME     VARCHAR2(60),
  IP            VARCHAR2(15),
  DRTPPORT      INTEGER default 4000,
  DRTPNODE      NUMBER,
  BCCMAINFUNCNO INTEGER
)
tablespace TS_YKT_CUR
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column T_FRONT.FRONTID
  is 'FRONTID';
comment on column T_FRONT.FRONTNAME
  is 'ǰ�û�����';
comment on column T_FRONT.IP
  is 'IP��ַ';
comment on column T_FRONT.DRTPPORT
  is 'DRTP�˿�';
comment on column T_FRONT.DRTPNODE
  is 'DRTP�ڵ��';
comment on column T_FRONT.BCCMAINFUNCNO
  is 'BCC�����ܺ�';
-- Create/Recreate primary, unique and foreign key constraints 
alter table T_FRONT
  add constraint PK_T_FRONT primary key (FRONTID)
  using index 
  tablespace TS_YKT_CUR
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


  
  
CREATE or replace VIEW
    V_DICTIONARY ( DICTTYPE, DICTVAL, DICTCAPTION ) AS
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
            branchname dictcaption
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
            deptname dictcaption
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
            'ͨ�����' dictcaption
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
            shopname dictcaption
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
            shopname dictcaption
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
SELECT
    3002 dicttype,
    TO_CHAR (shopid) dictval,
    shopname dictcaption
FROM
    ykt_cur.t_shop
WHERE
    shoptype=2
UNION ALL
    (
        SELECT
            3001 dicttype,
            t.areacode||t.olddeptcode dictval,
            t.deptname dictcaption
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
    
update t_cfgsplit set summary='Ȧ��ת��' where transtype=204;
commit;

-- 20110520 �¿��յĿ�������ȱ�ٵ��ֶδ��ڴ˱�ģ�⿨�����ݣ���֧������ҵ������
CREATE TABLE T_NEWCAPEC_CARD
(
  CARDPHYNO  VARCHAR2(16) NOT NULL,
  APPTYPE    INTEGER,
  FEETYPE    INTEGER,
  CUSTTYPE   INTEGER,
  CUSTID     INTEGER,
  IDTYPE     INTEGER,
  DPSCNT     INTEGER,
  TRANSDATE  INTEGER,
  DAYMAXAMT  INTEGER,
  PUBLISHID  INTEGER,
  SHOWCARDNO INTEGER,
  SUBSIDYNO  INTEGER,
  CARDSTRUCT INTEGER,
  SCHOOLCODE INTEGER
)
TABLESPACE TS_YKT_CUR
  PCTFREE 10
  INITRANS 1
  MAXTRANS 255
  STORAGE
  (
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
  );
-- CREATE/RECREATE PRIMARY, UNIQUE AND FOREIGN KEY CONSTRAINTS 
ALTER TABLE T_NEWCAPEC_CARD
  ADD CONSTRAINT PK_T_NEWCAPEC_CARD PRIMARY KEY (CARDPHYNO)
  USING INDEX 
  TABLESPACE TS_YKT_CUR
  PCTFREE 10
  INITRANS 2
  MAXTRANS 255
  STORAGE
  (
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
  );
