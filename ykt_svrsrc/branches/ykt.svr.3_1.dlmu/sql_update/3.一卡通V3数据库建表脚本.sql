/*==============================================================*/
/* DBMS name:      ORACLE Version 10g                           */
/* Created on:     2010-7-19 15:40:11                           */
/*==============================================================*/


/*==============================================================*/
/* Table: T_ACCDTL                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ACCDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   SUBSEQNO             INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   PAYTYPE              INTEGER,
   VOUCHERNO            VARCHAR(20),
   TRANSCODE            INTEGER,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   SUBJNO               VARCHAR(20),
   ACCNO                VARCHAR(10)                     NOT NULL,
   ACCNAME              VARCHAR(60),
   DCFLAG               NUMBER(1)                       NOT NULL,
   AMOUNT               NUMBER(15,2)                    NOT NULL,
   BALANCE              NUMBER(15,2)                    NOT NULL,
   OPPSUBJNO            VARCHAR(20),
   OPPACCNO             VARCHAR(10),
   OPPACCNAME           VARCHAR(60),
   OPERCODE             VARCHAR(8),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_ACCDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO, SUBSEQNO, ACCNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TERMID IS
'�ն˱��(վ��š��豸ID)';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUBSEQNO IS
'����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSDATE IS
'��������,ȡϵͳ����';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSTIME IS
'����ʱ��,ȡϵͳʱ��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.PAYTYPE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.VOUCHERNO IS
'ƾ֤��(֧Ʊ�����ѱ�����)';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSTYPE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCNAME IS
'�ʻ���';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.DCFLAG IS
'���';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.BALANCE IS
'�ʻ����';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPSUBJNO IS
'�Է���Ŀ';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPACCNO IS
'�Է��˺�';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPACCNAME IS
'�Է��ʻ���';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_ACCDTLACCNO                                       */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_ACCDTLACCNO ON YKT_CUR.T_ACCDTL (
   ACCNO ASC
)
PCTFREE 10
INITRANS 2
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR;

/*==============================================================*/
/* Table: T_ACCOUNT                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ACCOUNT  (
   ACCNO                VARCHAR(10)                     NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20)                     NOT NULL,
   ACCPWD               VARCHAR(64),
   CUSTID               INTEGER,
   CARDNO               INTEGER,
   PURSENO              INTEGER,
   SINGLEMAXAMT         NUMBER(15,2),
   DAYCOSTMAXAMT        NUMBER(15,2),
   DAYCOSTAMT           NUMBER(15,2),
   CARDMAXBAL           NUMBER(15,2),
   STATUS               CHAR(1)                         NOT NULL,
   FOREGIFT             NUMBER(15,2)                    NOT NULL,
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2)                    NOT NULL,
   AVAILBAL             NUMBER(15,2)                    NOT NULL,
   FROZEBAL             NUMBER(15,2)                    NOT NULL,
   SUBSIDYBAL           NUMBER(15,2)                    NOT NULL,
   SUBSIDYNO            INTEGER,
   CARDBAL              NUMBER(15,2)                    NOT NULL,
   CARDCNT              INTEGER,
   DPSCNT               INTEGER,
   PAYCNT               INTEGER,
   LASTSUBSIDYAMT       NUMBER(15,2),
   LASTSUBSIDYNO        INTEGER,
   LASTCARDBAL          NUMBER(15,2),
   LASTCARDCNT          INTEGER,
   LASTDPSCNT           INTEGER,
   LASTPAYCNT           INTEGER,
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8)                      NOT NULL,
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_ACCOUNT PRIMARY KEY (ACCNO)
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

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.ACCNAME IS
'�ʻ�����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.ACCPWD IS
'�ʻ�����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SINGLEMAXAMT IS
'���������޶�';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DAYCOSTMAXAMT IS
'�������޶�';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DAYCOSTAMT IS
'���ۼ����ѽ��';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDMAXBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.FOREGIFT IS
'Ѻ��';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.YDAYBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.BALANCE IS
'�ʻ����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.AVAILBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.FROZEBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBSIDYBAL IS
'���첹�����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBSIDYNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDBAL IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DPSCNT IS
'����ֵ����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.PAYCNT IS
'�����Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTSUBSIDYAMT IS
'�ϴβ������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTSUBSIDYNO IS
'�ϴβ������κ�';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTCARDBAL IS
'�ϴο����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTCARDCNT IS
'�ϴν��״���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTDPSCNT IS
'�ϴο���ֵ����';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTPAYCNT IS
'�ϴ����Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTTRANSDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTACCDATE IS
'�ϴ���������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CLOSEDATE IS
'��������';

/*==============================================================*/
/* Index: IDX_CARDNOPURSENO                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDNOPURSENO ON YKT_CUR.T_ACCOUNT (
   CARDNO ASC,
   PURSENO ASC
);

/*==============================================================*/
/* Index: IDX_ACCOUNT_CUSTID                                    */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_ACCOUNT_CUSTID ON YKT_CUR.T_ACCOUNT (
   CUSTID ASC
);

/*==============================================================*/
/* Table: T_AREA                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_AREA  (
   AREACODE             VARCHAR(3)                      NOT NULL,
   AREANAME             VARCHAR(60),
   FAREACODE            VARCHAR(3),
   OLDAREACODE          VARCHAR(3),
   AREALEVEL            INTEGER,
   ADDR                 VARCHAR(240),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_AREA PRIMARY KEY (AREACODE)
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

COMMENT ON COLUMN YKT_CUR.T_AREA.AREACODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_AREA.AREANAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_AREA.FAREACODE IS
'�ϼ��������';

COMMENT ON COLUMN YKT_CUR.T_AREA.OLDAREACODE IS
'ԭ�������';

COMMENT ON COLUMN YKT_CUR.T_AREA.AREALEVEL IS
'���򼶱�';

COMMENT ON COLUMN YKT_CUR.T_AREA.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_AREA.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_ATTDEVCARDLIST                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ATTDEVCARDLIST  (
   DEVICEID             INTEGER                         NOT NULL,
   CUSTID               INTEGER                         NOT NULL,
   WEEKID               INTEGER                         NOT NULL,
   HOLIDAYID            INTEGER,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER                         NOT NULL,
   DOWNTIME             VARCHAR(30),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_ATTDEVCARDLIST PRIMARY KEY (DEVICEID, CUSTID, WEEKID)
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

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.WEEKID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.HOLIDAYID IS
'�ڼ���ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDVERNO IS
'�����汾��';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.ADDDELFLAG IS
'��ɾ��־:1-��-2ɾ';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.DOWNTIME IS
'�´�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_ATTENDDTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ATTENDDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   STUEMPNO             VARCHAR(20),
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   TRANSMARK            INTEGER,
   STATUS               NUMBER(1),
   CONSTRAINT PK_T_ATTENDDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVSEQNO IS
'��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.TRANSMARK IS
'���ױ��';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.STATUS IS
'״̬';

/*==============================================================*/
/* Table: T_AUTHCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_AUTHCARD  (
   CARDNO               INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8),
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   PRIVILEGE            INTEGER,
   EXPIREDATE           VARCHAR(8),
   STATUS               CHAR(1),
   LOSSFLAG             CHAR(1),
   LOSSDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_AUTHCARD PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.PRIVILEGE IS
'��Ȩ��Ȩ��';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.EXPIREDATE IS
'��Ч��';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.STATUS IS
'��¼״̬';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.LOSSFLAG IS
'��ʧ״̬';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.LOSSDATE IS
'��ʧ����';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.CLOSEDATE IS
'ע������';

/*==============================================================*/
/* Table: T_BANKCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCARD  (
   CUSTID               INTEGER                         NOT NULL,
   BANKCARDNO           VARCHAR(30)                     NOT NULL,
   BANKCODE             CHAR(2),
   BATCHNO              VARCHAR(30),
   CREATEDDATE          VARCHAR(8),
   RELATEDATE           VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_BANKCARD PRIMARY KEY (CUSTID, BANKCARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BANKCODE IS
'���б��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.CREATEDDATE IS
'¼������';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.RELATEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_BANKCARDDTL                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCARDDTL  (
   REFNO                NUMBER(14)                      NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   TERMID               INTEGER,
   OPERCODE             VARCHAR(8),
   BATCHNO              VARCHAR(30),
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   STUEMPNO             VARCHAR(20),
   BANKCARDNO           VARCHAR(30),
   OPTYPE               NUMBER(1),
   ADDDELFLAG           NUMBER(1),
   ERRCODE              INTEGER,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_BANKCARDDTL PRIMARY KEY (REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.OPTYPE IS
'1- ǩԼ2-��Լ3- ͬ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.ADDDELFLAG IS
'1-����2-ɾ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_CUSTID                                */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDDTL_CUSTID ON YKT_CUR.T_BANKCARDDTL (
   CUSTID ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_SNO                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDDTL_SNO ON YKT_CUR.T_BANKCARDDTL (
   STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_OPTYPE                                */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDDTL_OPTYPE ON YKT_CUR.T_BANKCARDDTL (
   OPTYPE ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_TRANSDATE                             */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDDTL_TRANSDATE ON YKT_CUR.T_BANKCARDDTL (
   TRANSDATE ASC
);

/*==============================================================*/
/* Table: T_BANKCARDTMP                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCARDTMP  (
   RECORDNO             NUMBER(14)                      NOT NULL,
   TERMID               INTEGER,
   BATCHNO              VARCHAR(30),
   OPERCODE             VARCHAR(8),
   CUSTID               INTEGER,
   STUEMPNO             VARCHAR(20),
   BANKCARDNO           VARCHAR(30),
   OPTYPE               NUMBER(1),
   TRANSDATE            VARCHAR(8),
   STATUS               NUMBER(1)                       NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_BANKCARDTMP PRIMARY KEY (RECORDNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.RECORDNO IS
'��¼��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.OPTYPE IS
'1- ǩԼ2-��Լ3- ͬ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.STATUS IS
'1��Ч��¼2�������¼3����ʧ��4����ɹ�';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_BANKCARDTMP_STATUS                                */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDTMP_STATUS ON YKT_CUR.T_BANKCARDTMP (
   STATUS ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDTMP_BATCHNO                               */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCARDTMP_BATCHNO ON YKT_CUR.T_BANKCARDTMP (
   BATCHNO ASC
);

/*==============================================================*/
/* Table: T_BANKCHKBILL                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKBILL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   BANKCARDNO           VARCHAR(30)                     NOT NULL,
   BANKSN               VARCHAR(30)                     NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   LOCALSN              VARCHAR(30),
   TRANSCODE            INTEGER,
   SUMMARY              VARCHAR(60),
   BANKAMT              NUMBER(15,2)                    NOT NULL,
   LOCALAMT             NUMBER(15,2),
   DIFFAMT              NUMBER(15,2),
   CHKFLAG              CHAR(1),
   CONSTRAINT PK_T_BANKCHKBILL PRIMARY KEY (TRANSDATE, BANKCARDNO, BANKSN, CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKSN IS
'���ж���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.LOCALSN IS
'������ˮ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKAMT IS
'���ж˽��׽��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.LOCALAMT IS
'���ؽ��׽��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.DIFFAMT IS
'���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.CHKFLAG IS
'0-δ����1-�Ѳ���';

/*==============================================================*/
/* Table: T_BANKCHKDATE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKDATE  (
   CHKDATE              VARCHAR(8)                      NOT NULL,
   CHKFLAG              NUMBER(1),
   CONSTRAINT PK_T_BANKCHKDATE PRIMARY KEY (CHKDATE)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDATE.CHKDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDATE.CHKFLAG IS
'�˶Ա�־';

/*==============================================================*/
/* Table: T_BANKCHKDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   REFNO                NUMBER(14)                      NOT NULL,
   STUEMPNO             VARCHAR(20),
   BANKCARDNO           VARCHAR(30),
   AMOUNT               NUMBER(15,2),
   CHKSTATUS            NUMBER(1),
   CHKFLAG              NUMBER(1),
   CHKOPER              VARCHAR(8),
   CHKDATE              VARCHAR(8),
   CHKTIME              VARCHAR(6),
   CONSTRAINT PK_T_BANKCHKDTL PRIMARY KEY (REFNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKSTATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKFLAG IS
'���˱�־';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKOPER IS
'���˲���Ա';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_BRANCH                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BRANCH  (
   BRANCHNO             INTEGER                         NOT NULL,
   AREACODE             VARCHAR(3),
   BRANCHNAME           VARCHAR(60),
   BRANCHTYPE           CHAR(1),
   BANKCODE             CHAR(2),
   BANKACCNO            VARCHAR(20),
   BANKACCNAME          VARCHAR(60),
   CONTACTMAN           VARCHAR(60),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   FAX                  VARCHAR(30),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   STATUS               CHAR(1),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_BRANCH PRIMARY KEY (BRANCHNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHNO IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHTYPE IS
'�������ͣ�1-��������2-��ֵ��3-����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKACCNO IS
'�����ʻ�';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKACCNAME IS
'�����ʻ���';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.CONTACTMAN IS
'��ϵ��';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.FAX IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.OPENDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.USEFLAG IS
'ʹ��״̬ 0-δʹ��1-��ʹ��';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.LASTSAVED IS
'����ʱ��';

/*==============================================================*/
/* Table: T_CARD                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARD  (
   CARDNO               INTEGER                         NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   CARDTYPE             INTEGER,
   CARDPHYTYPE          INTEGER,
   FEETYPE              INTEGER                         NOT NULL,
   CUSTID               INTEGER,
   SHOWCARDNO           VARCHAR(10),
   CARDPHYID            VARCHAR(16),
   CARDPWD              VARCHAR(32),
   EXPIREDATE           VARCHAR(8)                      NOT NULL,
   STATUS               CHAR(1)                         NOT NULL,
   LOSSFLAG             CHAR(1)                         NOT NULL,
   LOSSDATE             VARCHAR(8),
   LOSSEFTTIME          VARCHAR(30),
   FROZEFLAG            CHAR(1)                         NOT NULL,
   FROZEDATE            VARCHAR(8),
   BADFLAG              CHAR(1)                         NOT NULL,
   BADTYPE              CHAR(1),
   BADDATE              VARCHAR(8),
   LOCKFLAG             CHAR(1)                         NOT NULL,
   LOCKDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8)                      NOT NULL,
   CLOSEDATE            VARCHAR(8),
   CARDVERNO            VARCHAR(12),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CARD PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARD.ACCNO IS
'���˺�';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYTYPE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_CARD.FEETYPE IS
'�շ�����';

COMMENT ON COLUMN YKT_CUR.T_CARD.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPWD IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARD.EXPIREDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.STATUS IS
'��¼״̬1-����2-ע��';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSFLAG IS
'1-��ʧ0-δ��ʧ';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSDATE IS
'��ʧ����';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSEFTTIME IS
'��ʧ��Чʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARD.FROZEFLAG IS
'1-����0-δ����';

COMMENT ON COLUMN YKT_CUR.T_CARD.FROZEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADFLAG IS
'1-����0-���ǻ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADTYPE IS
'0-���ṹ����1-��Ϊ��2-��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADDATE IS
'�����Ǽ�����';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOCKFLAG IS
'������־';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOCKDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDVERNO IS
'���汾��';

COMMENT ON COLUMN YKT_CUR.T_CARD.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Index: INDEX_CARD_CARDTYPE                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.INDEX_CARD_CARDTYPE ON YKT_CUR.T_CARD (
   CARDTYPE ASC
);

/*==============================================================*/
/* Table: T_CARDACCDIFF                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDACCDIFF  (
   CARDNO               INTEGER                         NOT NULL,
   CUSTID               INTEGER,
   STUEMPNO             VARCHAR(20),
   CUSTNAME             VARCHAR(60),
   AREACODE             VARCHAR(3),
   DIFFAMT              NUMBER(15,2),
   DIFFDAYCNT           INTEGER,
   AVAILBAL             NUMBER(15,2),
   LASTCARDBAL          NUMBER(15,2),
   LASTCARDCNT          INTEGER,
   STATDATE             VARCHAR(8),
   STATTIME             VARCHAR(6),
   STARTDATE            VARCHAR(8)                      NOT NULL,
   ENDDATE              VARCHAR(8),
   MAXCARDCNT           INTEGER,
   CARDAFTBAL           NUMBER(15,2),
   PAYLOSSAMT           NUMBER(15,2),
   DPSLOSSAMT           NUMBER(15,2),
   TOTALLOSSAMT         NUMBER(15,2),
   TOTALLOSSCNT         INTEGER,
   DEALDATE             VARCHAR(8),
   OPERCODE             VARCHAR(8),
   STATUS               CHAR(1),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CARDACCDIFF PRIMARY KEY (CARDNO, STARTDATE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.AREACODE IS
'У��';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DIFFAMT IS
'��ƽ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DIFFDAYCNT IS
'��ƽ����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.AVAILBAL IS
'�˻���ǰ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.LASTCARDBAL IS
'����ǰ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.LASTCARDCNT IS
'�˻������״���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATDATE IS
'ͳ������';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATTIME IS
'ͳ��ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STARTDATE IS
'��ƽ��ʼ����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.ENDDATE IS
'ͳ�ƽ�ֹ����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.MAXCARDCNT IS
'�ڼ俨����״���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CARDAFTBAL IS
'�ڼ俨������';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.PAYLOSSAMT IS
'�ڼ�����ȱʧ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DPSLOSSAMT IS
'�ڼ��ֵȱʧ���';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.TOTALLOSSAMT IS
'�ڼ�ȱʧ�ܽ��';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.TOTALLOSSCNT IS
'�ڼ�ȱʧ����';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DEALDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.OPERCODE IS
'�������Ա';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATUS IS
'ƽ��״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CARDBITMAP                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDBITMAP  (
   CARDNO               INTEGER                         NOT NULL,
   BASENO               INTEGER,
   BITMAP0              VARCHAR(100),
   BITMAP1              VARCHAR(100),
   BITMAP2              VARCHAR(100),
   BITMAP3              VARCHAR(100),
   BITMAP4              VARCHAR(100),
   BITMAP5              VARCHAR(100),
   BITMAP6              VARCHAR(100),
   BITMAP7              VARCHAR(100),
   BITMAP8              VARCHAR(100),
   BITMAP9              VARCHAR(100),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_CARDBITMAP PRIMARY KEY (CARDNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BASENO IS
'��׼����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP0 IS
'λͼ0';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP1 IS
'λͼ1';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP2 IS
'λͼ2';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP3 IS
'λͼ3';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP4 IS
'λͼ4';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP5 IS
'λͼ5';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP6 IS
'λͼ6';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP7 IS
'λͼ7';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP8 IS
'λͼ8';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP9 IS
'λͼ9';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.DELFLAG IS
'ɾ����־';

/*==============================================================*/
/* Table: T_CARDBOOK                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDBOOK  (
   SHOWCARDNO           NUMBER(10)                      NOT NULL,
   CARDTYPE             INTEGER                         NOT NULL,
   CARDPHYID            VARCHAR(16),
   OPERCODE             VARCHAR(8)                      NOT NULL,
   PUTOPERCODE          VARCHAR(8),
   BATCHNO              VARCHAR(30),
   GETDATE              VARCHAR(8),
   USEDATE              VARCHAR(8),
   RECLAIMDATE          VARCHAR(8),
   USESTATUS            NUMBER(1)                       NOT NULL,
   CONSTRAINT PK_T_CARDBOOK PRIMARY KEY (SHOWCARDNO)
);

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.SHOWCARDNO IS
'��¼��';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.PUTOPERCODE IS
'ת������Ա';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.GETDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.USEDATE IS
'ʹ������';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.RECLAIMDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.USESTATUS IS
'ʹ��״̬';

/*==============================================================*/
/* Table: T_CARDDTL                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   CARDTYPE             INTEGER,
   USETYPE              INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60),
   INOUTFLAG            INTEGER,
   TRANSCNT             INTEGER,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   CONSTRAINT PK_T_CARDDTL PRIMARY KEY (ACCDATE, TERMSEQNO, TERMID, OPERCODE, USETYPE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMID IS
'�յ���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.BRANCHNO IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.USETYPE IS
'��ʹ������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.INOUTFLAG IS
'1-����2-֧��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TRANSCNT IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDPHYID IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SHOWCARDNO IS
'��ʾ����';

/*==============================================================*/
/* Table: T_CARDINSTEADDTL                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDINSTEADDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   CARDNO               INTEGER,
   OLDCARDTYPE          INTEGER,
   OLDCARDPHYID         VARCHAR(16),
   OLDSHOWCARDNO        VARCHAR(10),
   OLDCARDCNT           INTEGER,
   OLDCARDBAL           NUMBER(15,2),
   OLDSUBSIDYNO         INTEGER,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   REVFLAG              CHAR(1),
   STATUS               CHAR(1),
   CONSTRAINT PK_T_CARDINSTEADDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
);

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.CARDNO IS
'ԭ����';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDTYPE IS
'ԭ������';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDPHYID IS
'ԭ������ID';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDSHOWCARDNO IS
'ԭ��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDCNT IS
'ԭ�����״���';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDBAL IS
'ԭ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDSUBSIDYNO IS
'ԭ���������κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.CARDPHYID IS
'�¿�����ID';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.SHOWCARDNO IS
'�¿���ʾ����';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.REVFLAG IS
'������־';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.STATUS IS
'״̬';

/*==============================================================*/
/* Index: IDX_OLDCARDNOCARDNO                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_OLDCARDNOCARDNO ON YKT_CUR.T_CARDINSTEADDTL (
   CARDNO ASC
);

/*==============================================================*/
/* Table: T_CARDNOCHANGE                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDNOCHANGE  (
   OLDCARDNO            INTEGER                         NOT NULL,
   NEWCARDNO            INTEGER                         NOT NULL,
   CHANGEDATE           VARCHAR(8),
   CONSTRAINT PK_T_CARDNOCHANGE PRIMARY KEY (OLDCARDNO)
);

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.OLDCARDNO IS
'�ɿ���';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.NEWCARDNO IS
'�¿���';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.CHANGEDATE IS
'�������';

/*==============================================================*/
/* Table: T_CARDPHYTYPE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDPHYTYPE  (
   CARDPHYTYPE          INTEGER                         NOT NULL,
   CARDPHYTYPENAME      VARCHAR(60)                     NOT NULL,
   USEFLAG              NUMBER(1)                      DEFAULT 0 NOT NULL,
   CARDPHYTYPECODE      INTEGER                        DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_CARDPHYTYPE PRIMARY KEY (CARDPHYTYPE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPENAME IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.USEFLAG IS
'�Ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPECODE IS
'���������ͱ���';

/*==============================================================*/
/* Table: T_CARDTRANSDTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDTRANSDTL  (
   CARDNO               INTEGER                         NOT NULL,
   TRANSFLAG            NUMBER(1)                       NOT NULL,
   CARDCNT              INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6)                      NOT NULL,
   TERMNO               VARCHAR(12)                     NOT NULL,
   TERMSNO              INTEGER                         NOT NULL,
   CARDBEFBAL           NUMBER(15,2)                    NOT NULL,
   AMOUNT               NUMBER(15,2)                    NOT NULL,
   ADDAMT               NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   SHOPID               INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   STATUS               NUMBER(1)                       NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CARDTRANSDTL PRIMARY KEY (TRANSFLAG, CARDCNT, CARDNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSFLAG IS
'���ױ�־';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TERMNO IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TERMSNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.AMOUNT IS
'������-���������';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.ADDAMT IS
'��д���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.MANAGEFEE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.SHOPID IS
'�̻�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.STATUS IS
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CARDTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDTYPE  (
   CARDTYPE             INTEGER                         NOT NULL,
   CARDTYPENAME         VARCHAR(60),
   ANONYMFLAG           CHAR(1),
   FEETYPE              INTEGER,
   CARDCOSTFEE          NUMBER(15,2),
   REUSEABLE            CHAR(1),
   RENEWABLE            CHAR(1),
   RECYCLEABLE          CHAR(1),
   MULTIPURSE           CHAR(1),
   FIXDAYFLAG           CHAR(1),
   FIXDAYCNT            INTEGER,
   USEFLAG              CHAR(1),
   PURPOSE              VARCHAR(240),
   CONSTRAINT PK_T_CARDTYPE PRIMARY KEY (CARDTYPE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDTYPENAME IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.ANONYMFLAG IS
'1-����0-����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FEETYPE IS
'Ĭ���շ����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDCOSTFEE IS
'���ɱ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.REUSEABLE IS
'�ܷ�����:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RENEWABLE IS
'�ܷ񲹰�:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RECYCLEABLE IS
'�ܷ����:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.MULTIPURSE IS
'��Ǯ����־';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYFLAG IS
'��Ч���Ƿ�̶�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYCNT IS
'��Ч����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.USEFLAG IS
'ʹ�ñ�־:0-δʹ��1��ʹ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.PURPOSE IS
'��;';

/*==============================================================*/
/* Table: T_CARDTYPERIGHT                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDTYPERIGHT  (
   CARDTYPE             INTEGER                         NOT NULL,
   FEETYPE              INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CARDTYPERIGHT PRIMARY KEY (CARDTYPE, FEETYPE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.FEETYPE IS
'�շ����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.LASTSAVED IS
'��ñ���ʱ��';

/*==============================================================*/
/* Table: T_CARDVER                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDVER  (
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   CARDVERNO            VARCHAR(12)                     NOT NULL,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   STUEMPNO             VARCHAR(20),
   CARDVERTYPE          INTEGER,
   ADDDELFLAG           NUMBER(1),
   STATUS               CHAR(1),
   CONSTRAINT PK_T_CARDVER PRIMARY KEY (CARDVERNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDVER.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDVERNO IS
'���汾��';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDVERTYPE IS
'��־:1-��ʧ2���3-����4-�ⶳ5-�·���6-�˿� 7-�����ɿ�8�����¿�';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.ADDDELFLAG IS
'��ɾ��־1-���-2ɾ��';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.STATUS IS
'��¼״̬1-����-2-ע��';

/*==============================================================*/
/* Index: INDEX_CARDNO                                          */
/*==============================================================*/
CREATE INDEX YKT_CUR.INDEX_CARDNO ON YKT_CUR.T_CARDVER (
   CARDNO ASC
);

/*==============================================================*/
/* Table: T_CFGACCCHK                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGACCCHK  (
   ACCCHKTYPE           INTEGER                         NOT NULL,
   ACCCHKTYPENAME       VARCHAR(30),
   ACCCHKFILEPATH       VARCHAR(240),
   ACCCHKEXCNAME        VARCHAR(30),
   BCCDRTPNO            INTEGER,
   BCCFUNCNO            INTEGER,
   BCCTIMEOUT           INTEGER,
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_CFGACCCHK PRIMARY KEY (ACCCHKTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKTYPENAME IS
'�����������';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKFILEPATH IS
'�����ļ���ǰ�û��ϵ�·��';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKEXCNAME IS
'���˳��������';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCDRTPNO IS
'ǰ�û��ڵ�';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCFUNCNO IS
'ǰ�û����ܺ�';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCTIMEOUT IS
'ǰ�û���ʱʱ�䣨�룩';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.DELFLAG IS
'�Ƿ�ɾ��ǰ���϶����ļ�';

/*==============================================================*/
/* Table: T_CFGBANK                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGBANK  (
   BANKCODE             CHAR(2)                         NOT NULL,
   BANKNAME             VARCHAR(30),
   BANKSTARTTIME        VARCHAR(6),
   BANKENDTIME          VARCHAR(6),
   BANKIP               VARCHAR(15),
   BANKPORT             INTEGER,
   BANKTIMEOUT          INTEGER,
   BCCDRTPNO            INTEGER,
   BCCFUNCNO            INTEGER,
   BCCTIMEOUT           INTEGER,
   QRYCARDFLAG          NUMBER(1),
   CONSTRAINT PK_T_CFGBANK PRIMARY KEY (BANKCODE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKSTARTTIME IS
'���з���ʼʱ��';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKENDTIME IS
'���з����ֹʱ��';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKIP IS
'����IP';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKPORT IS
'���ж˿�';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKTIMEOUT IS
'���ж˳�ʱʱ��';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCDRTPNO IS
'ǰ�û��ڵ�';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCFUNCNO IS
'ǰ�û����ܺ�';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCTIMEOUT IS
'ǰ�û���ʱ';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.QRYCARDFLAG IS
'QRYCARDFLAG';

/*==============================================================*/
/* Table: T_CFGBANKCODE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGBANKCODE  (
   BANKCODE             CHAR(2),
   CARDHEAD             VARCHAR(30)                     NOT NULL,
   CARDHEADLEN          NUMBER(1),
   CARDLEN              NUMBER(1),
   CONSTRAINT PK_T_CFGBANKCODE PRIMARY KEY (CARDHEAD)
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

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDHEAD IS
'��ͷ';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDHEADLEN IS
'��ͷ����';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDLEN IS
'��ȫ��';

/*==============================================================*/
/* Table: T_CFGFEE                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGFEE  (
   FEETYPE              INTEGER                         NOT NULL,
   TRANSCODE            INTEGER                         NOT NULL,
   CARDTYPE             INTEGER                         NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   RATETYPE             INTEGER,
   RATEAMT              NUMBER(15,2),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGFEE PRIMARY KEY (FEETYPE, TRANSCODE, CARDTYPE, TRANSTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.FEETYPE IS
'�ͻ����շ����';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.RATETYPE IS
'��������:1�̶�ֵ- 2-�ٷֱ�3-������ֵ��Ϊ�շѽ��';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.RATEAMT IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CFGPAYMENT                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGPAYMENT  (
   PAYCODE              INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   ENABLED              NUMBER(1)                       NOT NULL,
   ONLINEPAY            NUMBER(1)                       NOT NULL,
   PAYCHKFLAG           NUMBER(1)                       NOT NULL,
   PAYEEACCTYPE         NUMBER(1)                       NOT NULL,
   SHOPID               INTEGER                         NOT NULL,
   BCCFUNCNO            INTEGER,
   BCCDRTPNO            INTEGER,
   IP                   VARCHAR(15),
   PORT                 INTEGER,
   TIMEOUT              INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGPAYMENT PRIMARY KEY (PAYCODE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PAYCODE IS
'�ͻ����շ����';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.SUMMARY IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.ENABLED IS
'�Ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.ONLINEPAY IS
'0-������1����';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PAYCHKFLAG IS
'1��Ҫ0����Ҫ';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PAYEEACCTYPE IS
'0-����1����2�ͻ���3ѧ��';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.BCCFUNCNO IS
'BCC�����ܺ�';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.BCCDRTPNO IS
'BCCDRTP�ڵ��';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.IP IS
'�̻�����IP';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PORT IS
'�̻�����˿�';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.TIMEOUT IS
'�̻���ʱʱ��(��)';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CFGRAKEOFF                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGRAKEOFF  (
   SHOPID               INTEGER                         NOT NULL,
   AMOUNT               NUMBER(15,2)                    NOT NULL,
   AGIO                 NUMBER(5,4),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGRAKEOFF PRIMARY KEY (SHOPID, AMOUNT)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.AMOUNT IS
'�̻����';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.AGIO IS
'�ۿ۷�����';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CFGSHOPFEE                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGSHOPFEE  (
   SHOPID               INTEGER                         NOT NULL,
   FEETYPE              INTEGER                         NOT NULL,
   FEERATE              NUMBER(5,4),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGSHOPFEE PRIMARY KEY (SHOPID, FEETYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.FEETYPE IS
'���շ����';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.FEERATE IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CFGSPLIT                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGSPLIT  (
   TRANSTYPE            INTEGER                         NOT NULL,
   FUNDTYPE             INTEGER                         NOT NULL,
   OFFLINEFLAG          INTEGER,
   USECARDFLAG          INTEGER,
   CALCCARDBAL          INTEGER,
   DRACCFLAG            CHAR(1)                         NOT NULL,
   DRSUBJNO             VARCHAR(20),
   DRACCNO              VARCHAR(10),
   CRACCFLAG            CHAR(1)                         NOT NULL,
   CRSUBJNO             VARCHAR(20),
   CRACCNO              VARCHAR(10),
   SUMMARY              VARCHAR(60),
   CONSTRAINT PK_T_CFGSPLIT PRIMARY KEY (TRANSTYPE, FUNDTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.FUNDTYPE IS
'�ʽ�����';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.OFFLINEFLAG IS
'�ѻ���־1-�ѻ�0-����';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.USECARDFLAG IS
'�����ױ�־';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CALCCARDBAL IS
'���㿨����־';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRACCFLAG IS
'�跽��־';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRSUBJNO IS
'�跽��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRACCNO IS
'�跽�˺�';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRACCFLAG IS
'������־';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRSUBJNO IS
'������Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRACCNO IS
'�����˺�';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.SUMMARY IS
'ժҪ';

/*==============================================================*/
/* Table: T_CFGTRANS                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGTRANS  (
   FEETYPE              INTEGER                         NOT NULL,
   TRANSCODE            INTEGER                         NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   RATETYPE             INTEGER,
   RATEAMT              NUMBER(15,2),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGTRANS PRIMARY KEY (FEETYPE, TRANSCODE, TRANSTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.FEETYPE IS
'�ͻ����շ����';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.RATETYPE IS
'��������:1����- 2-�ٷֱ�3-��������Ϊ׼';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.RATEAMT IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CFGVER                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGVER  (
   CFGTYPE              INTEGER                         NOT NULL,
   CFGVERNO             INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGVER PRIMARY KEY (CFGTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGVER.CFGTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.CFGVERNO IS
'���ð汾';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CUSTIDCTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTIDCTL  (
   AREACODE             VARCHAR(3)                      NOT NULL,
   STARTNO              INTEGER                         NOT NULL,
   NEXTNO               INTEGER,
   ENDNO                INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CUSTIDCTL PRIMARY KEY (AREACODE, STARTNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.STARTNO IS
'�ͻ���ʼ��';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.NEXTNO IS
'�ͻ���ǰ��';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.ENDNO IS
'�ͻ�������';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CUSTOMER                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTOMER  (
   CUSTID               INTEGER                         NOT NULL,
   STUEMPNO             VARCHAR(20),
   CUSTTYPE             INTEGER,
   FEETYPE              INTEGER,
   STATUS               CHAR(1)                         NOT NULL,
   CUSTNAME             VARCHAR(60),
   AREACODE             VARCHAR(3),
   DEPTCODE             VARCHAR(30),
   DEPTFULLNAME         VARCHAR(1000),
   SPECIALTYCODE        VARCHAR(30),
   CLASSCODE            VARCHAR(30),
   CLASSNAME            VARCHAR(60),
   IDTYPE               CHAR(1),
   IDNO                 VARCHAR(60),
   SEX                  CHAR(1),
   COUNTRY              CHAR(3),
   NATION               CHAR(2),
   EMAIL                VARCHAR(60),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   CUSTATTR             VARCHAR(10),
   INDATE               VARCHAR(8),
   OUTDATE              VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   BATCHNO              VARCHAR(30),
   OPENFLAG             NUMBER(1),
   HOLDCARDCNT          INTEGER,
   USEFLAG              CHAR(1),
   EACCFLAG             CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CUSTOMER PRIMARY KEY (CUSTID)
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

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTTYPE IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.FEETYPE IS
'�շ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.STATUS IS
'״̬1-����2-ע��';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTNAME IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DEPTCODE IS
'���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DEPTFULLNAME IS
'����ȫ��';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.SPECIALTYCODE IS
'רҵ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLASSCODE IS
'�༶����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLASSNAME IS
'�༶����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.SEX IS
'�Ա�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.COUNTRY IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.NATION IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTATTR IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.INDATE IS
'��У����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OUTDATE IS
'Ԥ����У����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OPENDATE IS
'ע������,ָ���ǿͻ���Ϣ��ӽ���������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OPENFLAG IS
'��ʽ����ͨ��־';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.HOLDCARDCNT IS
'ӵ�п�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.USEFLAG IS
'ʹ�ñ�־';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EACCFLAG IS
'����Ǯ����ͨ��־';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Index: IDX_CUSTOMER_STUEMPNO                                 */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTOMER_STUEMPNO ON YKT_CUR.T_CUSTOMER (
   STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_FEETYPE                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTOMER_FEETYPE ON YKT_CUR.T_CUSTOMER (
   FEETYPE ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_HOLDCARDCNT                              */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTOMER_HOLDCARDCNT ON YKT_CUR.T_CUSTOMER (
   HOLDCARDCNT ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_DEPTCODE                                 */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTOMER_DEPTCODE ON YKT_CUR.T_CUSTOMER (
   DEPTCODE ASC
);

/*==============================================================*/
/* Table: T_CUSTOMERTMP                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTOMERTMP  (
   BATCHNO              VARCHAR(30)                     NOT NULL,
   SEQNO                INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   OPERCODE             VARCHAR(8),
   STUEMPNO             VARCHAR(20),
   CUSTTYPE             INTEGER,
   CUSTTYPENAME         VARCHAR(60),
   FEETYPE              INTEGER,
   CUSTNAME             VARCHAR(60),
   AREACODE             VARCHAR(3),
   DEPTCODE             VARCHAR(30),
   DEPTNAME             VARCHAR(90),
   SPECIALTYCODE        VARCHAR(30),
   CLASSNAME            VARCHAR(60),
   IDTYPE               CHAR(1),
   IDNO                 VARCHAR(60),
   SEX                  CHAR(1),
   COUNTRY              CHAR(3),
   NATION               CHAR(2),
   EMAIL                VARCHAR(60),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   INDATE               VARCHAR(8),
   OUTDATE              VARCHAR(8),
   SYNCFLAG             NUMBER(1)                      DEFAULT 0 NOT NULL,
   CHKFLAG              NUMBER(1)                      DEFAULT 0 NOT NULL,
   ERRMSG               VARCHAR(240)
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

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.BATCHNO IS
'�������κŻ�ͬ��ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SEQNO IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.OPERCODE IS
'�������Ա';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTTYPE IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTTYPENAME IS
'�ͻ��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.FEETYPE IS
'�շ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTNAME IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.DEPTCODE IS
'���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.DEPTNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SPECIALTYCODE IS
'רҵ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CLASSNAME IS
'�༶����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SEX IS
'�Ա�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.COUNTRY IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.NATION IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.INDATE IS
'��У����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.OUTDATE IS
'��У����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SYNCFLAG IS
'1-ͬ������0-��ͬ������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CHKFLAG IS
'0-δ���1-���ʧ��2���ͨ��';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ERRMSG IS
'������Ϣ';

/*==============================================================*/
/* Index: IDX_CUSTTMP_SYNCFLAG                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTTMP_SYNCFLAG ON YKT_CUR.T_CUSTOMERTMP (
   SYNCFLAG ASC,
   STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_CUSTTMP_BATCHNO                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CUSTTMP_BATCHNO ON YKT_CUR.T_CUSTOMERTMP (
   BATCHNO ASC,
   SEQNO ASC
);

/*==============================================================*/
/* Table: T_CUSTTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTTYPE  (
   CUSTTYPE             INTEGER                         NOT NULL,
   CUSTTYPENAME         VARCHAR(60),
   FEETYPE              INTEGER,
   AREACODE             VARCHAR(3),
   OLDCUSTTYPE          VARCHAR(10),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_CUSTTYPE PRIMARY KEY (CUSTTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.CUSTTYPE IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.CUSTTYPENAME IS
'�ͻ���������';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.FEETYPE IS
'Ĭ���շ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.AREACODE IS
'ѧУ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.OLDCUSTTYPE IS
'ԭ�ͻ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.USEFLAG IS
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_DEPT                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DEPT  (
   DEPTCODE             VARCHAR(30)                     NOT NULL,
   AREACODE             VARCHAR(3),
   DEPTNAME             VARCHAR(240),
   DEPTENAME            VARCHAR(240),
   DEPTFULLNAME         VARCHAR(1000),
   FDEPTCODE            VARCHAR(30),
   DEPTLEVEL            INTEGER,
   DEPTTYPE             NUMBER(1)                      DEFAULT 0,
   OLDDEPTCODE          VARCHAR(30),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DEPT PRIMARY KEY (DEPTCODE)
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

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTCODE IS
'���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_DEPT.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTENAME IS
'����Ӣ����';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTFULLNAME IS
'����ȫ��';

COMMENT ON COLUMN YKT_CUR.T_DEPT.FDEPTCODE IS
'�ϼ����Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTLEVEL IS
'���ż���';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTTYPE IS
'0����1�༶';

COMMENT ON COLUMN YKT_CUR.T_DEPT.OLDDEPTCODE IS
'ԭ���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_DEPT.USEFLAG IS
'ʹ�ñ�־:0-δʹ��1-��ʹ��';

COMMENT ON COLUMN YKT_CUR.T_DEPT.LASTSAVED IS
'��󱣴�����';

/*==============================================================*/
/* Table: T_DEVICE                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DEVICE  (
   DEVICEID             INTEGER                         NOT NULL,
   DEVICENAME           VARCHAR(60),
   DEVPHYID             VARCHAR(20),
   DEVICENO             INTEGER,
   DEVPHYTYPE           INTEGER,
   DEVTYPECODE          VARCHAR(30),
   DEVVERNO             VARCHAR(30),
   CARDPHYTYPE          CHAR(2),
   FDEVICEID            INTEGER,
   RUNSTATUS            INTEGER,
   STATUS               CHAR(1),
   SVRPORTCNT           INTEGER,
   SVRPORTNO            INTEGER,
   COMMTYPE             INTEGER,
   IP                   VARCHAR(15),
   PORTNO               INTEGER,
   BAUDRATE             INTEGER,
   CARDSET              VARCHAR(64),
   CARDVERNO            VARCHAR(12)                    DEFAULT '000000000000',
   LASTSEQNO            INTEGER,
   LASTTRANSTIME        VARCHAR(30),
   PURSENO              INTEGER,
   MAXAMT               NUMBER(15,2),
   SYSID                INTEGER,
   AREACODE             VARCHAR(3),
   DOORLSTVER           VARCHAR(12),
   DEVUSAGE             INTEGER,
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   BATCHNO              VARCHAR(30),
   LASTSAVED            VARCHAR(30),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_DEVICE PRIMARY KEY (DEVICEID)
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

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVICEID IS
'�ն˱��Ҳ���豸���';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVICENAME IS
'�豸����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVPHYID IS
'�豸����ID��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVICENO IS
'�豸����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVPHYTYPE IS
'�豸���̴���';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVTYPECODE IS
'�豸���͡�';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVVERNO IS
'�豸�汾�š�';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDPHYTYPE IS
'�������ͺ�';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.FDEVICEID IS
'�ϼ��豸ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.RUNSTATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.STATUS IS
'״̬:1-����2-ע��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SVRPORTCNT IS
'�˿�����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SVRPORTNO IS
'�������ӿڱ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.COMMTYPE IS
'ͨѶ��ʽ:1-����2-MODEM3-TCPIP 9-����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.IP IS
'IP��ַ';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.PORTNO IS
'������SOCKET�˿ں�';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.BAUDRATE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDSET IS
'�ն�����ʹ�õĿ��շ����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDVERNO IS
'���������汾��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTSEQNO IS
'�ϴ��豸������ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTTRANSTIME IS
'�ϴν���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.PURSENO IS
'�豸������Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.MAXAMT IS
'����ֵ�޶��λ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SYSID IS
'ǰ�û�ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DOORLSTVER IS
'���ڼ�¼�Ѿ���¼��Ϣ���е������汾';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVUSAGE IS
'�豸��;';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.OPENDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTSAVED IS
'�ϴ��޸�����';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_DEVPHYID                                          */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DEVPHYID ON YKT_CUR.T_DEVICE (
   DEVPHYID ASC
);

/*==============================================================*/
/* Table: T_DEVICETMP                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DEVICETMP  (
   BATCHNO              VARCHAR(30)                     NOT NULL,
   SEQNO                INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   OPERCODE             VARCHAR(8),
   AREACODE             VARCHAR(3),
   DEVICENAME           VARCHAR(60),
   DEVPHYID             VARCHAR(20),
   DEVPHYTYPE           INTEGER,
   DEVTYPECODE          VARCHAR(30),
   DEVICENO             INTEGER,
   FDEVICEID            INTEGER,
   CARDPHYTYPE          CHAR(2),
   COMMTYPE             INTEGER,
   IP                   VARCHAR(15),
   PORTNO               INTEGER,
   SVRPORTNO            INTEGER,
   SVRPORTCNT           INTEGER,
   SYSID                INTEGER,
   DEVUSAGE             INTEGER,
   ERRMSG               VARCHAR(240),
   CONSTRAINT PK_T_DEVICETMP PRIMARY KEY (BATCHNO, SEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SEQNO IS
'�������к�';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.OPERCODE IS
'�������Ա';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVICENAME IS
'�豸����';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVPHYID IS
'�豸����ID��';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVPHYTYPE IS
'�豸���̴���';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVTYPECODE IS
'�豸���͡�';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVICENO IS
'�豸����';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.FDEVICEID IS
'�ϼ��豸ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.CARDPHYTYPE IS
'�������ͺ�';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.COMMTYPE IS
'ͨѶ��ʽ:1-����2-MODEM3-TCPIP 9-����';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.IP IS
'IP��ַ';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.PORTNO IS
'ͨѶ�˿ں�';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SVRPORTNO IS
'�������ӿڱ��';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SVRPORTCNT IS
'�˿�����';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SYSID IS
'ǰ�û�ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVUSAGE IS
'�豸��;';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.ERRMSG IS
'������Ϣ';

/*==============================================================*/
/* Table: T_DEVMONITOR                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DEVMONITOR  (
   DEVICEID             INTEGER                         NOT NULL,
   OPTIME               VARCHAR(30),
   COLTIME              VARCHAR(30),
   DEVTIME              VARCHAR(30),
   BEATSTATUS           INTEGER,
   CARDVERNO            VARCHAR(12),
   HARDISKPER           NUMBER,
   MEMORYPER            NUMBER,
   CPUPER               NUMBER,
   CONSTRAINT PK_T_DEVMONITOR PRIMARY KEY (DEVICEID)
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

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.DEVICEID IS
'�ն˱��Ҳ���豸���';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.OPTIME IS
'OPTIME';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.DEVTIME IS
'DEVTIME';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.BEATSTATUS IS
'BEATSTATUS';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.CARDVERNO IS
'���汾��';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.HARDISKPER IS
'HARDISKPER';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.MEMORYPER IS
'MEMORYPER';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.CPUPER IS
'CPUPER';

/*==============================================================*/
/* Table: T_DICTIONARY                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DICTIONARY  (
   DICTTYPE             INTEGER                         NOT NULL,
   DICTTYPENAME         VARCHAR(60),
   DICTVAL              VARCHAR(30)                     NOT NULL,
   DICTCAPTION          VARCHAR(60),
   CONSTRAINT PK_T_DICTIONARY PRIMARY KEY (DICTTYPE, DICTVAL)
);

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTTYPE IS
'�ֵ�����';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTTYPENAME IS
'�ֵ���������';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTVAL IS
'�ֵ�ֵ';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTCAPTION IS
'�ֵ�����';

/*==============================================================*/
/* Table: T_DOORCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORCARD  (
   DEVICEID             INTEGER                         NOT NULL,
   CUSTID               INTEGER                         NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   STATUS               NUMBER(1)                       NOT NULL,
   INSERTDATE           VARCHAR(14),
   CONSTRAINT PK_T_DOORCARD PRIMARY KEY (DEVICEID, CUSTID, CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDVERNO IS
'�����汾��';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.INSERTDATE IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORCARDADDR                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORCARDADDR  (
   CARDADDR             INTEGER                         NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   USEFLAG              CHAR(1),
   LISTID               INTEGER,
   CTRLID               INTEGER                         NOT NULL,
   ADDDELFLAG           NUMBER(1)                       NOT NULL,
   CONSTRAINT PK_T_DOORCARDADDR PRIMARY KEY (CARDADDR, CTRLID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.CARDADDR IS
'CARDADDR';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.USEFLAG IS
'USEFLAG';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.LISTID IS
'LISTID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.CTRLID IS
'CTRLID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.ADDDELFLAG IS
'��ɾ��־';

/*==============================================================*/
/* Index: IDX_DCA_CARDNOCTRLID                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DCA_CARDNOCTRLID ON YKT_CUR.T_DOORCARDADDR (
   CARDNO ASC,
   CTRLID ASC
);

/*==============================================================*/
/* Index: IDX_DCA_LCA                                           */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DCA_LCA ON YKT_CUR.T_DOORCARDADDR (
   LISTID ASC,
   CTRLID ASC,
   ADDDELFLAG ASC
);

/*==============================================================*/
/* Index: IDX_DCA_USEFLAGCTRLID                                 */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DCA_USEFLAGCTRLID ON YKT_CUR.T_DOORCARDADDR (
   USEFLAG ASC,
   CTRLID ASC
);

/*==============================================================*/
/* Table: T_DOORDEVCARDLIST                                     */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDEVCARDLIST  (
   DEVICEID             INTEGER                         NOT NULL,
   CUSTID               INTEGER                         NOT NULL,
   WEEKID               INTEGER                         NOT NULL,
   HOLIDAYID            INTEGER,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER                         NOT NULL,
   DOWNTIME             VARCHAR(30),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVCARDLIST PRIMARY KEY (DEVICEID, CUSTID, WEEKID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.WEEKID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.HOLIDAYID IS
'�ڼ���ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDVERNO IS
'�����汾��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.ADDDELFLAG IS
'��ɾ��־:1-��-2ɾ';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.DOWNTIME IS
'�´�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVHOLIDAY                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDEVHOLIDAY  (
   MAJORDEVID           NUMBER                          NOT NULL,
   MINORDEVID           INTEGER                         NOT NULL,
   HOLIDAYID            NUMBER                          NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVHOLIDAY PRIMARY KEY (MAJORDEVID, MINORDEVID, HOLIDAYID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.MAJORDEVID IS
'���豸ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.MINORDEVID IS
'���豸ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.HOLIDAYID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.SEQNO IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.DOWNTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.REFCNT IS
'REFCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.UPDATETIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVTIME                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDEVTIME  (
   MAJORDEVID           INTEGER                         NOT NULL,
   MINORDEVID           INTEGER                         NOT NULL,
   TIMEID               INTEGER                         NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVTIME PRIMARY KEY (MAJORDEVID, MINORDEVID, TIMEID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.MAJORDEVID IS
'MAJORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.MINORDEVID IS
'MINORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.TIMEID IS
'ʱ���ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.SEQNO IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.DOWNTIME IS
'�´�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.REFCNT IS
'REFCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.UPDATETIME IS
'UPDATETIME';

/*==============================================================*/
/* Table: T_DOORDEVTIMEGRP                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDEVTIMEGRP  (
   MAJORDEVID           INTEGER                         NOT NULL,
   MINORDEVID           INTEGER                         NOT NULL,
   TIMEGRPID            INTEGER                         NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVTIMEGRP PRIMARY KEY (MAJORDEVID, MINORDEVID, TIMEGRPID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.MAJORDEVID IS
'MAJORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.MINORDEVID IS
'MINORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.TIMEGRPID IS
'ʱ�����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.SEQNO IS
'��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.DOWNTIME IS
'�´�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.REFCNT IS
'���ô���';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.UPDATETIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVWEEK                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDEVWEEK  (
   MAJORDEVID           INTEGER                         NOT NULL,
   MINORDEVID           INTEGER                         NOT NULL,
   WEEKID               INTEGER                         NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   LINKCNT              INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVWEEK PRIMARY KEY (MAJORDEVID, MINORDEVID, WEEKID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.MAJORDEVID IS
'MAJORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.MINORDEVID IS
'MINORDEVID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.WEEKID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.SEQNO IS
'��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.DOWNTIME IS
'�´�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.REFCNT IS
'REFCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.LINKCNT IS
'LINKCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.UPDATETIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDOWNLOAD                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDOWNLOAD  (
   ID                   INTEGER                         NOT NULL,
   CARDVERNO            VARCHAR(12),
   CUSTID               INTEGER                         NOT NULL,
   CTRLID               INTEGER                         NOT NULL,
   SYSID                INTEGER                         NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   CARDPHYID            VARCHAR(16)                     NOT NULL,
   RIGHTBIT             VARCHAR(240),
   CARDSEQNO            INTEGER                         NOT NULL,
   WEEKID               INTEGER                         NOT NULL,
   WEEKSEQNO            INTEGER                         NOT NULL,
   HOLIDAYID            INTEGER                         NOT NULL,
   HOLIDAYSEQNO         INTEGER                         NOT NULL,
   CREATETIME           VARCHAR(30)                     NOT NULL,
   SUCCTIME             VARCHAR(30),
   STATUS               NUMBER(1)                       NOT NULL,
   ADDDELFLAG           NUMBER(1)                       NOT NULL,
   DOORCOUNT            INTEGER,
   CONSTRAINT PK_T_DOORDOWNLOAD PRIMARY KEY (ID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.ID IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDVERNO IS
'�����汾��';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CTRLID IS
'CTRLID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.SYSID IS
'SYSID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.RIGHTBIT IS
'Ȩ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDSEQNO IS
'CARDSEQNO';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.WEEKID IS
'WEEKID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.WEEKSEQNO IS
'WEEKSEQNO';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.HOLIDAYID IS
'HOLIDAYID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.HOLIDAYSEQNO IS
'HOLIDAYSEQNO';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CREATETIME IS
'CREATETIME';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.SUCCTIME IS
'SUCCTIME';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.DOORCOUNT IS
'DOORCOUNT';

/*==============================================================*/
/* Index: IDX_DOORDL                                            */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DOORDL ON YKT_CUR.T_DOORDOWNLOAD (
   CARDVERNO ASC,
   CTRLID ASC
);

/*==============================================================*/
/* Table: T_DOORDTL                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   STUEMPNO             VARCHAR(20),
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   TRANSMARK            INTEGER,
   SYSID                INTEGER,
   CONSTRAINT PK_T_DOORDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVSEQNO IS
'��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CUSTNAME IS
'�ͻ�����';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.TRANSMARK IS
'���ױ��';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.SYSID IS
'��ϵͳID';

/*==============================================================*/
/* Table: T_DOOREVENTDTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOOREVENTDTL  (
   DEVICEID             INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6)                      NOT NULL,
   EVENTCODE            INTEGER                         NOT NULL,
   EVENTMSG             VARCHAR(240),
   SYSID                INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   CONSTRAINT PK_T_DOOREVENTDTL PRIMARY KEY (DEVICEID, TRANSDATE, TRANSTIME, EVENTCODE)
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

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.EVENTCODE IS
'�¼�����';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.EVENTMSG IS
'�¼���Ϣ';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.SYSID IS
'��ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.COLTIME IS
'�ɼ�ʱ��';

/*==============================================================*/
/* Table: T_DOORGROUP                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORGROUP  (
   GROUPID              INTEGER                         NOT NULL,
   GROUPNAME            VARCHAR(60),
   STATUS               CHAR(1),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGROUP PRIMARY KEY (GROUPID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.GROUPID IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.GROUPNAME IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORGRPMEMBER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORGRPMEMBER  (
   GROUPID              INTEGER                         NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGRPMEMBER PRIMARY KEY (GROUPID, DEVICEID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORGRPMEMBER.GROUPID IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPMEMBER.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPMEMBER.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORGRPOPERRIGHT                                    */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORGRPOPERRIGHT  (
   GROUPID              INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGRPOPERRIGHT PRIMARY KEY (GROUPID, OPERCODE)
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

COMMENT ON COLUMN YKT_CUR.T_DOORGRPOPERRIGHT.GROUPID IS
'���';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPOPERRIGHT.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPOPERRIGHT.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORHOLIDAY                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORHOLIDAY  (
   HOLIDAYID            INTEGER                         NOT NULL,
   HOLIDAYNAME          VARCHAR(60),
   DAYCNT               INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORHOLIDAY PRIMARY KEY (HOLIDAYID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.HOLIDAYID IS
'�ڼ���ID';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.HOLIDAYNAME IS
'�ڼ�����';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.DAYCNT IS
'�ڼ�������';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.UPDATETIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORHOLIDAYTIME                                     */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORHOLIDAYTIME  (
   HOLIDAYID            INTEGER                         NOT NULL,
   HOLIDAYDATE          VARCHAR(8)                      NOT NULL,
   TIMEGRPID            INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORHOLIDAYTIME PRIMARY KEY (HOLIDAYID, HOLIDAYDATE)
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

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.HOLIDAYID IS
'HOLIDAYID';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.HOLIDAYDATE IS
'HOLIDAYDATE';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.TIMEGRPID IS
'ʱ����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.UPDATETIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOOROPERRIGHT                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOOROPERRIGHT  (
   DEVICEID             INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOOROPERRIGHT PRIMARY KEY (DEVICEID, OPERCODE)
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

COMMENT ON COLUMN YKT_CUR.T_DOOROPERRIGHT.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOOROPERRIGHT.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DOOROPERRIGHT.UPDATETIME IS
'UPDATETIME';

/*==============================================================*/
/* Table: T_DOORRPTDAY                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORRPTDAY  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   TOTALCNT             INTEGER,
   VALIDCNT             NUMBER,
   INVALIDCNT           INTEGER,
   CONSTRAINT PK_T_DOORRPTDAY PRIMARY KEY (TRANSDATE, DEVICEID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.TOTALCNT IS
'�ܴ���';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.VALIDCNT IS
'VALIDCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.INVALIDCNT IS
'INVALIDCNT';

/*==============================================================*/
/* Table: T_DOORTIME                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORTIME  (
   TIMEID               INTEGER                         NOT NULL,
   TIMENAME             VARCHAR(60),
   STARTTIME            VARCHAR(6),
   ENDTIME              VARCHAR(6),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORTIME PRIMARY KEY (TIMEID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.TIMEID IS
'TIMEID';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.TIMENAME IS
'TIMENAME';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.STARTTIME IS
'STARTTIME';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.ENDTIME IS
'ENDTIME';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.UPDATETIME IS
'UPDATETIME';

/*==============================================================*/
/* Table: T_DOORTIMEGRP                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORTIMEGRP  (
   TIMEGRPID            INTEGER                         NOT NULL,
   TIMEGRPNAME          VARCHAR(60),
   TIMEID1              INTEGER,
   TIMEID2              INTEGER,
   TIMEID3              INTEGER,
   TIMEID4              INTEGER,
   TIMEID5              INTEGER,
   TIMEID6              INTEGER,
   TIMEID7              INTEGER,
   TIMEID8              INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORTIMEGRP PRIMARY KEY (TIMEGRPID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEGRPID IS
'TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEGRPNAME IS
'TIMEGRPNAME';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID1 IS
'TIMEID1';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID2 IS
'TIMEID2';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID3 IS
'TIMEID3';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID4 IS
'TIMEID4';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID5 IS
'TIMEID5';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID6 IS
'TIMEID6';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID7 IS
'TIMEID7';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.TIMEID8 IS
'TIMEID8';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.UPDATETIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORWEEKTIME                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DOORWEEKTIME  (
   WEEKID               INTEGER                         NOT NULL,
   WEEKNAME             VARCHAR(60),
   DAY1TIMEGRPID        INTEGER,
   DAY2TIMEGRPID        INTEGER,
   DAY3TIMEGRPID        INTEGER,
   DAY4TIMEGRPID        INTEGER,
   DAY5TIMEGRPID        INTEGER,
   DAY6TIMEGRPID        INTEGER,
   DAY7TIMEGRPID        INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORWEEKTIME PRIMARY KEY (WEEKID)
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

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.WEEKID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.WEEKNAME IS
'WEEKNAME';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY1TIMEGRPID IS
'DAY1TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY2TIMEGRPID IS
'DAY2TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY3TIMEGRPID IS
'DAY3TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY4TIMEGRPID IS
'DAY4TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY5TIMEGRPID IS
'DAY5TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY6TIMEGRPID IS
'DAY6TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DAY7TIMEGRPID IS
'DAY7TIMEGRPID';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.ADDDELFLAG IS
'��ɾ��־';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DOWNSTATUS IS
'�´�״̬';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.UPDATETIME IS
'UPDATETIME';

/*==============================================================*/
/* Table: T_DPSOPER                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DPSOPER  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   DEVLIMITFLAG         CHAR(1),
   SHOPOPERFLAG         CHAR(1),
   STATUS               CHAR(1),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   MAXDEPOSITAMT        NUMBER(15,2),
   DEPOSITCNT           INTEGER,
   DEPOSITAMT           NUMBER(15,2),
   LASTTRANSDATE        VARCHAR(8),
   LASTDEVPHYID         VARCHAR(20),
   LASTDEVSEQNO         INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSOPER PRIMARY KEY (OPERCODE)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEVLIMITFLAG IS
'ʹ�����Ʊ�־';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.SHOPOPERFLAG IS
'��ֵ�̻�����Ա��־';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.MAXDEPOSITAMT IS
'����ֵ���';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEPOSITCNT IS
'�ܳ�ֵ����';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEPOSITAMT IS
'�ܳ�ֵ���';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTTRANSDATE IS
'����ֵ����';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTDEVPHYID IS
'����ֵ�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTDEVSEQNO IS
'�ϴ��豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DPSOPERPOS                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DPSOPERPOS  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   OPENOPER             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSOPERPOS PRIMARY KEY (OPERCODE, DEVICEID)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.OPENOPER IS
'ע�����Ա';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DPSSHOPPOS                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DPSSHOPPOS  (
   DEVICEID             INTEGER                         NOT NULL,
   SHOPID               INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSSHOPPOS PRIMARY KEY (DEVICEID)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_ERRCODE                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ERRCODE  (
   ERRCODE              INTEGER                         NOT NULL,
   ERRMSG               VARCHAR(240),
   CONSTRAINT PK_T_ERRCODE PRIMARY KEY (ERRCODE)
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

COMMENT ON COLUMN YKT_CUR.T_ERRCODE.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_ERRCODE.ERRMSG IS
'������Ϣ';

/*==============================================================*/
/* Table: T_EXCEPTDTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_EXCEPTDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   REFNO                NUMBER(14)                      NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   PURSENO              INTEGER                         NOT NULL,
   DPSCNT               INTEGER                         NOT NULL,
   PAYCNT               INTEGER                         NOT NULL,
   CARDBEFBAL           NUMBER(15,2)                    NOT NULL,
   CARDAFTBAL           NUMBER(15,2)                    NOT NULL,
   FAILTYPE             NUMBER(1),
   STATUS               NUMBER(1)                       NOT NULL,
   REMARK               VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_EXCEPTDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.DPSCNT IS
'����ֵ����';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.PAYCNT IS
'�����Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDBEFBAL IS
'������ǰ���';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDAFTBAL IS
'�����׺����';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.FAILTYPE IS
'0-��;�ο�1д��ʧ��';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.STATUS IS
'0-δ����2ʧ��3�ɹ�';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_EXTCARDDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_EXTCARDDTL  (
   REFNO                NUMBER(14)                      NOT NULL,
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   CARDNO               INTEGER                         NOT NULL,
   AMOUNT               INTEGER,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   STATUS               NUMBER(1)                       NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_EXTCARDDTL PRIMARY KEY (REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.CARDNO IS
'��Ϊ��Ǯ��Ϊ��Ǯ';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.AMOUNT IS
'��д���';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.STATUS IS
'1δ��д2�Ѳ�д3���²���';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.REMARK IS
'��дԭ��';

/*==============================================================*/
/* Table: T_FEETYPE                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_FEETYPE  (
   FEETYPE              INTEGER                         NOT NULL,
   FEENAME              VARCHAR(60),
   BOARDFEEFLAG         CHAR(1),
   USEFLAG              CHAR(1),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_FEETYPE PRIMARY KEY (FEETYPE)
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

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.FEETYPE IS
'�շ����';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.FEENAME IS
'�շ�����';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.BOARDFEEFLAG IS
'�Ƿ��մ���:1-��0-����';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.USEFLAG IS
'ʹ�ñ�־';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_GDCTPARA                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_GDCTPARA  (
   PARANAME             VARCHAR(60)                     NOT NULL,
   PARAVAL              VARCHAR(60),
   REMARK               VARCHAR(240),
   PARAFLAG             NUMBER(1),
   CONSTRAINT PK_T_GDCTPARA PRIMARY KEY (PARANAME)
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

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.PARANAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.PARAVAL IS
'����ֵ';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.PARAFLAG IS
'������־';

/*==============================================================*/
/* Table: T_GETELECCARD                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_GETELECCARD  (
   CARDNO               INTEGER                         NOT NULL,
   CARDPHYID            VARCHAR(16)                     NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   USETYPE              NUMBER(1)                       NOT NULL,
   ADDDELFLAG           NUMBER(1)                       NOT NULL,
   DOWNTIME             VARCHAR(30),
   CONSTRAINT PK_T_GETELECCARD PRIMARY KEY (CARDNO, DEVICEID)
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

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.USETYPE IS
'0-����-1-������';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.ADDDELFLAG IS
'1-����2-ɾ��';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.DOWNTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_INNERACC                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_INNERACC  (
   ACCNO                VARCHAR(10)                     NOT NULL,
   ACCNAME              VARCHAR(60)                     NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2)                    NOT NULL,
   BALFLAG              NUMBER(1)                       NOT NULL,
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   CONSTRAINT PK_T_INNERACC PRIMARY KEY (ACCNO)
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

COMMENT ON COLUMN YKT_CUR.T_INNERACC.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.ACCNAME IS
'�ʻ���';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.YDAYBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.BALANCE IS
'�ʻ����';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.LASTTRANSDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.LASTACCDATE IS
'�ϴ���������';

/*==============================================================*/
/* Table: T_KEYS                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_KEYS  (
   KEYID                INTEGER                         NOT NULL,
   KEYVAL               VARCHAR(64),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_KEYS PRIMARY KEY (KEYID)
);

COMMENT ON COLUMN YKT_CUR.T_KEYS.KEYID IS
'��ԿID';

COMMENT ON COLUMN YKT_CUR.T_KEYS.KEYVAL IS
'��Կֵ';

COMMENT ON COLUMN YKT_CUR.T_KEYS.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_LOSSCARDINFO                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_LOSSCARDINFO  (
   CARDNO               INTEGER                         NOT NULL,
   CARDPHYID            VARCHAR(16),
   SHOPCODE             VARCHAR(60)                     NOT NULL,
   REGDATE              VARCHAR(8)                      NOT NULL,
   REGTIME              VARCHAR(6),
   STATUS               NUMBER(1),
   ENDDATE              VARCHAR(8),
   GETCARDPLACE         VARCHAR(240),
   TEL                  VARCHAR(30),
   ADDR                 VARCHAR(240),
   IDTYPE               NUMBER(1),
   IDNO                 VARCHAR(60),
   GETDATE              VARCHAR(8),
   GETTIME              VARCHAR(6),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_LOSSCARDINFO PRIMARY KEY (CARDNO, SHOPCODE, REGDATE)
);

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.CARDPHYID IS
'������';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.SHOPCODE IS
'�Ǽ��̻�����';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REGDATE IS
'�Ǽ�����';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REGTIME IS
'�Ǽ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.STATUS IS
'��ʧ��״̬';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.ENDDATE IS
'�����������';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETCARDPLACE IS
'��Ƭ����λ��';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.TEL IS
'��ϵ�绰';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.ADDR IS
'�̻��ص�';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.IDTYPE IS
'��ȡ��֤������';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETDATE IS
'��ȡ����';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETTIME IS
'��ȡʱ��';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_LOSSCARDSHOP                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_LOSSCARDSHOP  (
   SHOPCODE             VARCHAR(60)                     NOT NULL,
   SHOPNAME             VARCHAR(60),
   ADDR                 VARCHAR(240),
   TEL                  VARCHAR(30),
   GETCARDPLACE         VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_LOSSCARDSHOP PRIMARY KEY (SHOPCODE)
);

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.SHOPCODE IS
'��½�̻���';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.SHOPNAME IS
'�̻�����';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.ADDR IS
'�̻��ص�';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.TEL IS
'��ϵ�绰';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.GETCARDPLACE IS
'��ȡ��Ƭ�ص�';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.LASTSAVED IS
'����޸�ʱ��';

/*==============================================================*/
/* Table: T_MACHINECODE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MACHINECODE  (
   MACHINECODE          VARCHAR(60)                     NOT NULL,
   IP                   VARCHAR(15),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_MACHINECODE PRIMARY KEY (MACHINECODE)
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

COMMENT ON COLUMN YKT_CUR.T_MACHINECODE.MACHINECODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_MACHINECODE.IP IS
'IP��ַ';

COMMENT ON COLUMN YKT_CUR.T_MACHINECODE.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_MEALTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MEALTYPE  (
   MEALTYPE             INTEGER                         NOT NULL,
   MEALNAME             VARCHAR(30)                     NOT NULL,
   ENDTIME              VARCHAR(6)                      NOT NULL,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_MEALTYPE PRIMARY KEY (MEALTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.MEALTYPE IS
'�ʹ�ID';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.MEALNAME IS
'�ʹ�����';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.ENDTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.LASTSAVED IS
'����ʱ��';

/*==============================================================*/
/* Table: T_MEDICALDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MEDICALDTL  (
   REFNO                NUMBER(14)                      NOT NULL,
   CUSTID               INTEGER                         NOT NULL,
   CUSTNAME             VARCHAR(60)                     NOT NULL,
   STUEMPNO             VARCHAR(20),
   VOUCHERNO            VARCHAR(20),
   MEDICINES            VARCHAR(1000),
   MEDICALINFO          VARCHAR(1000),
   CARDNO               INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6)                      NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   TRANSAMT             NUMBER(15,2)                    NOT NULL,
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER,
   OPERCODE             VARCHAR(8),
   STATUS               NUMBER(1)                       NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_MEDICALDTL PRIMARY KEY (REFNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CUSTNAME IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.STUEMPNO IS
'ѧ/����';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.VOUCHERNO IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.MEDICINES IS
'����ҩƷ';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.MEDICALINFO IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CARDNO IS
'�ɷѿ���';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSDATE IS
'�ɷ�����';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSTIME IS
'�ɷ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSTYPE IS
'�ɷ�����';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSAMT IS
'�ɷѽ��';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.STATUS IS
'��¼״̬ (1¼��2-�ۿ�ʧ��3-�ۿ��ɹ�)';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_MEDICALDTL_CARDNO                                 */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_MEDICALDTL_CARDNO ON YKT_CUR.T_MEDICALDTL (
   CARDNO ASC
)
TABLESPACE TS_YKT_HIS;

/*==============================================================*/
/* Index: IDX_MEDICALDTL_STUEMPNO                               */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_MEDICALDTL_STUEMPNO ON YKT_CUR.T_MEDICALDTL (
   STUEMPNO ASC
);

/*==============================================================*/
/* Table: T_MOBILECHKDATE                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MOBILECHKDATE  (
   CHKDATE              VARCHAR(8)                      NOT NULL,
   CHKFLAG              NUMBER(1),
   CONSTRAINT PK_T_MOBILECHKDATE PRIMARY KEY (CHKDATE)
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

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDATE.CHKDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDATE.CHKFLAG IS
'�˶Ա�־';

/*==============================================================*/
/* Table: T_MOBILECHKDTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MOBILECHKDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   REFNO                NUMBER(14)                      NOT NULL,
   CARDNO               INTEGER,
   MOBILE               VARCHAR(30),
   AMOUNT               NUMBER(15,2),
   CHKSTATUS            NUMBER(1),
   CHKFLAG              NUMBER(1),
   CHKOPER              VARCHAR(8),
   CHKDATE              VARCHAR(8),
   CHKTIME              VARCHAR(6),
   CONSTRAINT PK_T_MOBILECHKDTL PRIMARY KEY (REFNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 16K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.MOBILE IS
'�ֻ���';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKSTATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKFLAG IS
'���˱�־';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKOPER IS
'���˲���Ա';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_MODIFYINFO                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MODIFYINFO  (
   CUSTID               INTEGER                         NOT NULL,
   STUEMPNO             VARCHAR(20)                     NOT NULL,
   ENROLLNO             VARCHAR(30)                     NOT NULL,
   MODIFYDATE           VARCHAR(8),
   MODIFYTIME           VARCHAR(6),
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_MODIFYINFO PRIMARY KEY (CUSTID, STUEMPNO, ENROLLNO)
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

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.ENROLLNO IS
'¼ȡ֪ͨ��';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.MODIFYDATE IS
'�޸�����';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.MODIFYTIME IS
'�޸�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.OPERCODE IS
'����Ա��';

/*==============================================================*/
/* Table: T_MODULEAUTH                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MODULEAUTH  (
   MODULECODE           VARCHAR(30)                     NOT NULL,
   MODULENAME           VARCHAR(60),
   MENUSET              VARCHAR2(800),
   FUNCSET              VARCHAR2(600),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_MODULEAUTH PRIMARY KEY (MODULECODE)
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

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.MODULECODE IS
'ģ�����';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.MODULENAME IS
'ģ����';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.MENUSET IS
'�˵���';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.FUNCSET IS
'���ܼ�';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_MSGLIST                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MSGLIST  (
   MSGID                INTEGER                         NOT NULL,
   MSGTYPE              INTEGER,
   MSGLEVEL             INTEGER,
   SYSID                INTEGER,
   DEVICEID             INTEGER,
   CARDNO               INTEGER,
   TRANSDATE            VARCHAR(8),
   CREATEDTIME          VARCHAR(30),
   STARTTIME            VARCHAR(30),
   ENDTIME              VARCHAR(30),
   REQDATA              VARCHAR(1000),
   RESPDATA             VARCHAR(1000),
   FUNCNO               INTEGER,
   PFUNCNO              INTEGER,
   MAXSENDCNT           INTEGER,
   SENDCNT              INTEGER,
   RECVCNT              INTEGER,
   STATUS               NUMBER(1),
   SEQNO                INTEGER,
   OPERCODE             VARCHAR(8),
   ERRCODE              INTEGER,
   ERRMSG               VARCHAR(240),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_MSGLIST PRIMARY KEY (MSGID)
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

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MSGID IS
'��ϢID';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MSGTYPE IS
'��Ϣ����';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MSGLEVEL IS
'��Ϣ����';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SYSID IS
'��ϵͳ���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.CREATEDTIME IS
'��Ϣ����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.STARTTIME IS
'��Ϣ��ʼ����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ENDTIME IS
'��Ϣ�������ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.REQDATA IS
'��Ϣ��������';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.RESPDATA IS
'��ϢӦ������';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.FUNCNO IS
'���ܺ�';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.PFUNCNO IS
'�����ܺ�';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MAXSENDCNT IS
'����ʹ���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SENDCNT IS
'���ʹ���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.RECVCNT IS
'���մ���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.STATUS IS
'��Ϣ״̬';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SEQNO IS
'���';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ERRMSG IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.DELFLAG IS
'ɾ����־';

/*==============================================================*/
/* Index: IDX_MSGLIST_DEVICEID                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_MSGLIST_DEVICEID ON YKT_CUR.T_MSGLIST (
   DEVICEID ASC
);

/*==============================================================*/
/* Table: T_NETACC                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_NETACC  (
   ACCNO                VARCHAR(10)                     NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   ACCPWD               VARCHAR(64),
   CUSTID               INTEGER,
   STOPPAYFLAG          INTEGER,
   STATUS               CHAR(1)                         NOT NULL,
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2)                    NOT NULL,
   AVAILBAL             NUMBER(15,2)                    NOT NULL,
   FROZEBAL             NUMBER(15,2)                    NOT NULL,
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8)                      NOT NULL,
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_NETACC PRIMARY KEY (ACCNO)
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

COMMENT ON COLUMN YKT_CUR.T_NETACC.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_NETACC.ACCNAME IS
'�ʻ���';

COMMENT ON COLUMN YKT_CUR.T_NETACC.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_NETACC.ACCPWD IS
'�ʻ�����';

COMMENT ON COLUMN YKT_CUR.T_NETACC.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_NETACC.STOPPAYFLAG IS
'ֹ����־';

COMMENT ON COLUMN YKT_CUR.T_NETACC.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_NETACC.YDAYBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.BALANCE IS
'�ʻ����';

COMMENT ON COLUMN YKT_CUR.T_NETACC.AVAILBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.FROZEBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.LASTTRANSDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.LASTACCDATE IS
'�ϴ���������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_NETACC.CLOSEDATE IS
'��������';

/*==============================================================*/
/* Table: T_NEWCARDCHANGE                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_NEWCARDCHANGE  (
   SHOWCARDNO           VARCHAR(10)                     NOT NULL,
   STUEMPNO             VARCHAR(20)                     NOT NULL,
   EXPIREDATE           VARCHAR(8)                      NOT NULL,
   STATUS               NUMBER(1)                       NOT NULL,
   BATCHNO              VARCHAR(30),
   SEQNO                INTEGER,
   CARDPHYID            VARCHAR(16),
   OLDCARDPHYID         VARCHAR(16),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_NEWCARDCHANGE PRIMARY KEY (SHOWCARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.STUEMPNO IS
'ѧ��';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.EXPIREDATE IS
'����Ч��';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.BATCHNO IS
'���κ�';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.SEQNO IS
'˳���';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.OLDCARDPHYID IS
'�ɿ�����ID';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Index: INDEX_NEWCARDCHG_BATCHNO                              */
/*==============================================================*/
CREATE INDEX YKT_CUR.INDEX_NEWCARDCHG_BATCHNO ON YKT_CUR.T_NEWCARDCHANGE (
   BATCHNO ASC,
   SEQNO ASC
);

/*==============================================================*/
/* Table: T_OPERATOR                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERATOR  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   OPERTYPE             CHAR(1)                         NOT NULL,
   BRANCHNO             INTEGER,
   CARDNO               INTEGER,
   OPERNAME             VARCHAR(60)                     NOT NULL,
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   OPERPWD              VARCHAR(32),
   STATUS               CHAR(1)                         NOT NULL,
   LASTTRANSDATE        VARCHAR(8),
   MENUSET              VARCHAR2(800),
   FUNCSET              VARCHAR2(600),
   RIGHTFLAG            NUMBER(1),
   SITELIMIT            CHAR(1),
   LOGINFLAG            CHAR(1),
   LOGINSITENO          INTEGER,
   LOGINTIME            VARCHAR(30),
   LOGOUTTIME           VARCHAR(30),
   FAILNUMBER           INTEGER,
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_OPERATOR PRIMARY KEY (OPERCODE)
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

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERCODE IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERTYPE IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.BRANCHNO IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.CARDNO IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERNAME IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERPWD IS
'����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.STATUS IS
'״̬:0-����1-����2-ע��';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LASTTRANSDATE IS
'���������:��ֵ����Աʹ��';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.MENUSET IS
'�˵�Ȩ�޼�';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.FUNCSET IS
'����Ȩ�޼�';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.RIGHTFLAG IS
'Ȩ�ޱ�־';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.SITELIMIT IS
'�Ƿ���վ������:0-������1-������';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINFLAG IS
'��¼��־:0-δ��¼1-�ѵ�¼';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINSITENO IS
'��¼վ���';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINTIME IS
'��¼ʱ��';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGOUTTIME IS
'ǩ��ʱ��';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.FAILNUMBER IS
'��¼ʧ�ܴ���';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPENDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.CLOSEDATE IS
'ע������';

/*==============================================================*/
/* Table: T_OPERDTL                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   OPERCODE             VARCHAR(8),
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   TRANSCODE            INTEGER,
   CHKOPER              VARCHAR(8),
   STATUS               CHAR(1),
   TRANSINFO            VARCHAR(480),
   REQDATA              VARCHAR(1000),
   CONSTRAINT PK_T_OPERDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMID IS
'վ���';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMSEQNO IS
'վ����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.CHKOPER IS
'��˲���Ա';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.STATUS IS
'��ˮ״̬1-δ����2-ʧ��3-�ɹ�4-����';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSINFO IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.REQDATA IS
'��������';

/*==============================================================*/
/* Table: T_OPERSITE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERSITE  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   SITENO               INTEGER                         NOT NULL,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_OPERSITE PRIMARY KEY (OPERCODE, SITENO)
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

COMMENT ON COLUMN YKT_CUR.T_OPERSITE.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_OPERSITE.SITENO IS
'վ���';

COMMENT ON COLUMN YKT_CUR.T_OPERSITE.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_PAYMENTDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PAYMENTDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   SHOPID               INTEGER,
   ACCNO                VARCHAR(10),
   ACCNAME              VARCHAR(60),
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   AMOUNT               NUMBER(15,2),
   PAYBANKACCNO         VARCHAR(20),
   PAYBANKACCNAME       VARCHAR(60),
   PAYEEBANKACCNO       VARCHAR(20),
   PAYEEBANKACCNAME     VARCHAR(60),
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_PAYMENTDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.ACCNAME IS
'�˻���';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.AMOUNT IS
'���';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYBANKACCNO IS
'��������˺�';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYBANKACCNAME IS
'��������˻���';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYEEBANKACCNO IS
'�տ�����˺�';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYEEBANKACCNAME IS
'�տ�����˻���';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.OPERCODE IS
'����Ա��';

/*==============================================================*/
/* Table: T_PAYPARA                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PAYPARA  (
   PARANAME             VARCHAR(60)                     NOT NULL,
   PAYCODE              INTEGER                         NOT NULL,
   PARAVAL              VARCHAR(60),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PAYPARA PRIMARY KEY (PARANAME, PAYCODE)
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

COMMENT ON COLUMN YKT_CUR.T_PAYPARA.PARANAME IS
'PARANAME';

COMMENT ON COLUMN YKT_CUR.T_PAYPARA.PAYCODE IS
'PAYCODE';

COMMENT ON COLUMN YKT_CUR.T_PAYPARA.PARAVAL IS
'PARAVAL';

COMMENT ON COLUMN YKT_CUR.T_PAYPARA.REMARK IS
'REMARK';

/*==============================================================*/
/* Table: T_PHOTO                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PHOTO  (
   CUSTID               INTEGER                         NOT NULL,
   STUEMPNO             VARCHAR(20),
   PHOTO                BLOB,
   MINPHOTO             BLOB,
   PHOTODATE            VARCHAR(8),
   PHOTOTIME            VARCHAR(6),
   IFCARD               CHAR(1),
   MAKECARDDATE         VARCHAR(8),
   MAKECARDTIME         VARCHAR(6),
   PHOTOEXACTTIME       VARCHAR(30),
   CONSTRAINT PK_T_PHOTO PRIMARY KEY (CUSTID)
)
TABLESPACE TS_YKT_PHOTO;

COMMENT ON COLUMN YKT_CUR.T_PHOTO.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTO IS
'��Ƭ';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MINPHOTO IS
'С��Ƭ';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTODATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTOTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.IFCARD IS
'�Ƿ��п�';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MAKECARDDATE IS
'�ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MAKECARDTIME IS
'�ƿ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTOEXACTTIME IS
'����ʱ��';

/*==============================================================*/
/* Index: IDX_STUEMPNO                                          */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_STUEMPNO ON YKT_CUR.T_PHOTO (
   STUEMPNO ASC
)
PCTFREE 10
INITRANS 2
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR;

/*==============================================================*/
/* Table: T_PHOTOLIMIT                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PHOTOLIMIT  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   OPERNAME             VARCHAR(60),
   OPERPWD              VARCHAR(64),
   OPERLIMIT            VARCHAR(60),
   ENABLED              CHAR(1),
   BEGINDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PHOTOLIMIT PRIMARY KEY (OPERCODE)
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

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERNAME IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERPWD IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERLIMIT IS
'Ȩ��';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.ENABLED IS
'�Ƿ����';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.BEGINDATE IS
'��Ч����';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.ENDDATE IS
'ʧЧ����';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_PHYDEVICE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PHYDEVICE  (
   PHYTYPE              INTEGER                         NOT NULL,
   DNAME                VARCHAR(60),
   DTYPE                VARCHAR(60),
   FACTORY              VARCHAR(60),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PHYDEVICE PRIMARY KEY (PHYTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_PHYDEVICE.PHYTYPE IS
'PHYTYPE';

COMMENT ON COLUMN YKT_CUR.T_PHYDEVICE.DNAME IS
'DNAME';

COMMENT ON COLUMN YKT_CUR.T_PHYDEVICE.DTYPE IS
'DTYPE';

COMMENT ON COLUMN YKT_CUR.T_PHYDEVICE.FACTORY IS
'FACTORY';

COMMENT ON COLUMN YKT_CUR.T_PHYDEVICE.REMARK IS
'REMARK';

/*==============================================================*/
/* Table: T_PLANTASK                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PLANTASK  (
   TASKNO               INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60),
   PROGNAME             VARCHAR(60),
   PROGPATH             VARCHAR(240),
   PROGARGV             VARCHAR(240),
   DIALY                INTEGER,
   WEEKLY               INTEGER,
   MONTHLY              INTEGER,
   STARTTIME            VARCHAR(6),
   ENDTIME              VARCHAR(6),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_PLANTASK PRIMARY KEY (TASKNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.TASKNO IS
'������,ȡ���ֵ��1';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.SUMMARY IS
'����˵��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGNAME IS
'������';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGPATH IS
'����·��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGARGV IS
'�����в���';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.DIALY IS
'ÿ��һ��,ȡֵ��Χ0-1,0��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.WEEKLY IS
'ÿ����һ��,ȡֵ��Χ0-7,0��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.MONTHLY IS
'ÿ��һ��,ȡֵ��Χ0-31,0��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.STARTTIME IS
'���п�ʼʱ��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.ENDTIME IS
'���н���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.USEFLAG IS
'�Ƿ�����';

/*==============================================================*/
/* Table: T_PLANTASKLOG                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PLANTASKLOG  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   STARTTIME            VARCHAR(6)                      NOT NULL,
   TASKNO               INTEGER                         NOT NULL,
   PROGNAME             VARCHAR(60),
   ENDTIME              VARCHAR(30),
   RUNSTATUS            INTEGER,
   SUMMARY              VARCHAR(240),
   CONSTRAINT PK_T_PLANTASKLOG PRIMARY KEY (TRANSDATE, STARTTIME, TASKNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.STARTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.TASKNO IS
'������';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.PROGNAME IS
'������';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.ENDTIME IS
'���н���ʱ�䣬��ʽΪyyyy-mm-dd hh:mm:ss';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.RUNSTATUS IS
'����״̬:0-������,1-�ɹ�,2-ʧ��';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.SUMMARY IS
'���н��˵��';

/*==============================================================*/
/* Table: T_POSDTL                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_POSDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6),
   TERMID               INTEGER,
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   PURSENO              INTEGER,
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   TRANSMARK            INTEGER,
   DATATYPE             NUMBER(1),
   TRANSCODE            INTEGER,
   SHOPID               INTEGER,
   SUBSIDYNO            INTEGER,
   BATCHNO              VARCHAR(30),
   SYSID                INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   ACCDATE              VARCHAR(8),
   ACCTIME              VARCHAR(6),
   TERMSEQNO            INTEGER,
   STATUS               CHAR(1)                         NOT NULL,
   ERRCODE              INTEGER,
   ERRMSG               VARCHAR(240),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_POSDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.AMOUNT IS
'������-���������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.MANAGEFEE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSMARK IS
'���ױ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DATATYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SHOPID IS
'�̻�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SUBSIDYNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SYSID IS
'��ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.STATUS IS
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ERRMSG IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DELFLAG IS
'ɾ����־';

/*==============================================================*/
/* Index: IDX_POSDTL_STATUS                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_POSDTL_STATUS ON YKT_CUR.T_POSDTL (
   STATUS ASC
);

/*==============================================================*/
/* Table: T_POSDTLTMP                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_POSDTLTMP  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   SHOPID               INTEGER,
   TRANSCODE            INTEGER,
   CARDNO               INTEGER                         NOT NULL,
   CARDCNT              INTEGER,
   PURSENO              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   TRANSMARK            INTEGER,
   BATCHNO              VARCHAR(30),
   SEQNO                INTEGER,
   IMPDATE              VARCHAR(8),
   IMPTIME              VARCHAR(6),
   IMPOPER              VARCHAR(8),
   TERMSEQNO            INTEGER,
   STATUS               CHAR(1),
   ERRMSG               VARCHAR(240),
   CHKOPER              VARCHAR(8),
   CHKDATE              VARCHAR(8),
   CONSTRAINT PK_T_POSDTLTMP PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.SHOPID IS
'�̻�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.AMOUNT IS
'������-���������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.MANAGEFEE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSMARK IS
'���ױ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.SEQNO IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPDATE IS
'¼������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPTIME IS
'¼������';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPOPER IS
'¼�����Ա��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TERMSEQNO IS
'¼����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.STATUS IS
'��ˮ״̬:1-¼��2-���ʧ��3-�����';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.ERRMSG IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CHKOPER IS
'��˲���Ա��';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CHKDATE IS
'�������';

/*==============================================================*/
/* Table: T_POSSEQNO                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_POSSEQNO  (
   DEVICEID             INTEGER                         NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   CONSTRAINT PK_T_POSSEQNO PRIMARY KEY (DEVICEID, DEVSEQNO, TRANSDATE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_POSSEQNO.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_POSSEQNO.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSSEQNO.TRANSDATE IS
'��������';

/*==============================================================*/
/* Table: T_PSAMCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PSAMCARD  (
   CARDNO               INTEGER                         NOT NULL,
   CARDTYPE             INTEGER,
   CARDVER              INTEGER,
   TERMNO               VARCHAR(12),
   STATUS               NUMBER(1),
   STARTDATE            VARCHAR(8),
   EXPIREDATE           VARCHAR(8),
   KEYINDEX             INTEGER,
   DEVICEID             INTEGER,
   DEVJOINTIME          VARCHAR(30),
   PUBLISHID            VARCHAR(8),
   USERID               VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   DISABLEDATE          VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_PSAMCARD PRIMARY KEY (CARDNO)
);

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CARDVER IS
'���汾��';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.TERMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.STARTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.EXPIREDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.KEYINDEX IS
'��Կ����';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DEVJOINTIME IS
'�豸������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.PUBLISHID IS
'���з�ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.USERID IS
'�û�ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.OPENDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CLOSEDATE IS
'�ر�����';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DISABLEDATE IS
'ͣ������';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_PURSE                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PURSE  (
   PURSENO              INTEGER                         NOT NULL,
   PURSENAME            VARCHAR(60),
   CARDMAXBAL           NUMBER(15,2),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_PURSE PRIMARY KEY (PURSENO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_PURSE.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_PURSE.PURSENAME IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_PURSE.CARDMAXBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_PURSE.USEFLAG IS
'ʹ�ñ�־0-δʹ��1-��ʹ��';

/*==============================================================*/
/* Table: T_PUSHTASK                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PUSHTASK  (
   TASKID               INTEGER                         NOT NULL,
   TASKSEQ              INTEGER,
   FUNCNO               INTEGER,
   FUNCGROUP            INTEGER,
   SYSID                INTEGER,
   DEVICEID             INTEGER,
   ADDTIME              VARCHAR(30),
   BEGINTIME            VARCHAR(30),
   INVALIDTIME          VARCHAR(30),
   EXECTIME             VARCHAR(30),
   EXECCNT              INTEGER,
   MAXEXEC              INTEGER,
   NEXTINTERVAL         INTEGER,
   STATUS               INTEGER,
   FLAG                 VARCHAR(10),
   SENDTYPE             INTEGER,
   ROUTEID              INTEGER,
   CONTENTSTR           VARCHAR(1000),
   RETCODE              VARCHAR(30),
   RETMSG               VARCHAR(240),
   CONSTRAINT PK_T_PUSHTASK PRIMARY KEY (TASKID)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.TASKID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.TASKSEQ IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.FUNCNO IS
'FUNCNO';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.FUNCGROUP IS
'FUNCGROUP';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.SYSID IS
'SYSID';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.ADDTIME IS
'ADDTIME';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.BEGINTIME IS
'BEGINTIME';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.INVALIDTIME IS
'INVALIDTIME';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.EXECTIME IS
'EXECTIME';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.EXECCNT IS
'EXECCNT';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.MAXEXEC IS
'MAXEXEC';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.NEXTINTERVAL IS
'NEXTINTERVAL';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.STATUS IS
'STATUS';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.FLAG IS
'FLAG';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.SENDTYPE IS
'SENDTYPE';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.ROUTEID IS
'ROUTEID';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.CONTENTSTR IS
'CONTENTSTR';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.RETCODE IS
'RETCODE';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.RETMSG IS
'RETMSG';

/*==============================================================*/
/* Table: T_REFNO                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_REFNO  (
   REFNO                NUMBER(14)                      NOT NULL,
   MAC                  VARCHAR(8)                      NOT NULL,
   STATUS               NUMBER(1)                       NOT NULL,
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_REFNO PRIMARY KEY (REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_REFNO.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_REFNO.MAC IS
'MAC��';

COMMENT ON COLUMN YKT_CUR.T_REFNO.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_REFNO.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_REFNO.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_REFNO.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_REFNO.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_RPTACCBAL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTACCBAL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   BALFLAG              NUMBER(1)                       NOT NULL,
   BALANCE              NUMBER(15,2)                    NOT NULL,
   CONSTRAINT PK_T_RPTACCBAL PRIMARY KEY (ACCDATE, ACCNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.BALANCE IS
'���';

/*==============================================================*/
/* Table: T_RPTACCLEDGER                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTACCLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTACCLEDGER PRIMARY KEY (ACCDATE, ACCNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.BALANCE IS
'���';

/*==============================================================*/
/* Table: T_RPTDAILYACC                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTDAILYACC  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTDAILYACC PRIMARY KEY (ACCDATE, ACCNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.BALANCE IS
'���';

/*==============================================================*/
/* Table: T_RPTDEPTLEDGER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTDEPTLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   DEPTCODE             VARCHAR(30)                     NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTDEPTLEDGER PRIMARY KEY (ACCDATE, DEPTCODE, SUBJNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.DEPTCODE IS
'���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.CRAMT IS
'����������';

/*==============================================================*/
/* Table: T_RPTOPERCARD                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTOPERCARD  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   CARDTYPE             INTEGER                         NOT NULL,
   USETYPE              INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   INCNT                INTEGER                         NOT NULL,
   OUTCNT               INTEGER                         NOT NULL,
   REMAINCNT            INTEGER                         NOT NULL,
   CONSTRAINT PK_T_RPTOPERCARD PRIMARY KEY (ACCDATE, OPERCODE, CARDTYPE, USETYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.BRANCHNO IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.USETYPE IS
'ʹ������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.INCNT IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.OUTCNT IS
'֧������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.REMAINCNT IS
'�������';

/*==============================================================*/
/* Table: T_RPTOPERCASH                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTOPERCASH  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   INAMT                NUMBER(15,2)                    NOT NULL,
   OUTAMT               NUMBER(15,2)                    NOT NULL,
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTOPERCASH PRIMARY KEY (ACCDATE, OPERCODE, SUBJNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.BRANCHNO IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.TRANSTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.INAMT IS
'���뷢����';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.OUTAMT IS
'֧��������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.AMOUNT IS
'�����';

/*==============================================================*/
/* Table: T_RPTOPERLEDGER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTOPERLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(20),
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   CONSTRAINT PK_T_RPTOPERLEDGER PRIMARY KEY (ACCDATE, OPERCODE, ACCNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.CRAMT IS
'����������';

/*==============================================================*/
/* Table: T_RPTPOSLEDGER                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTPOSLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTPOSLEDGER PRIMARY KEY (ACCDATE, ACCNO, DEVICEID, TRANSTYPE, SUMMARY, TRANSDATE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.AMOUNT IS
'�����';

/*==============================================================*/
/* Table: T_RPTPOSMEAL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTPOSMEAL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   MEALTYPE             INTEGER                         NOT NULL,
   MEALNAME             VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTPOSMEAL PRIMARY KEY (ACCDATE, ACCNO, DEVICEID, TRANSTYPE, SUMMARY, TRANSDATE, MEALTYPE, MEALNAME)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.DEVICEID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.MEALTYPE IS
'�ʹ�����';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.MEALNAME IS
'�ʹ�����';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.AMOUNT IS
'�����';

/*==============================================================*/
/* Table: T_RPTSHOPBOARD                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSHOPBOARD  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   TRANSAMT             NUMBER(15,2)                    NOT NULL,
   CONSTRAINT PK_T_RPTSHOPBOARD PRIMARY KEY (ACCDATE, ACCNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.TRANSAMT IS
'������';

/*==============================================================*/
/* Table: T_RPTSHOPMEAL                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSHOPMEAL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSCNT1            INTEGER                         NOT NULL,
   TRANSAMT1            NUMBER(15,2)                    NOT NULL,
   TRANSCNT2            INTEGER                         NOT NULL,
   TRANSAMT2            NUMBER(15,2)                    NOT NULL,
   TRANSCNT3            INTEGER                         NOT NULL,
   TRANSAMT3            NUMBER(15,2)                    NOT NULL,
   TRANSCNT4            INTEGER                         NOT NULL,
   TRANSAMT4            NUMBER(15,2)                    NOT NULL,
   CONSTRAINT PK_T_RPTSHOPMEAL PRIMARY KEY (ACCDATE, ACCNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT1 IS
'��ͽ��״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT1 IS
'��ͽ��';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT2 IS
'��ͽ��״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT2 IS
'��ͽ��';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT3 IS
'��ͽ��״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT3 IS
'��ͽ��';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT4 IS
'ҹ�ͽ��״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT4 IS
'ҹ�ͽ��';

/*==============================================================*/
/* Table: T_RPTSHOPRAKEOFF                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSHOPRAKEOFF  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   SHOPID               INTEGER,
   ACCNO                VARCHAR(10)                     NOT NULL,
   ACCNAME              VARCHAR(60),
   RAKEOFFRATE          NUMBER(5,4)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   TRANSAMT             NUMBER(15,2)                    NOT NULL,
   RAKEOFFAMT           NUMBER(15,2)                    NOT NULL,
   AMOUNT               NUMBER(15,2)                    NOT NULL,
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTSHOPRAKEOFF PRIMARY KEY (ACCDATE, ACCNO)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.ACCNAME IS
'�̻��˻���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.RAKEOFFRATE IS
'Ӷ�����';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.TRANSAMT IS
'Ӫҵ���';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.RAKEOFFAMT IS
'Ӷ����';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.BALANCE IS
'���';

/*==============================================================*/
/* Table: T_RPTSUBJBAL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSUBJBAL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   BEGINBAL             NUMBER(15,2)                    NOT NULL,
   BEGINBALFLAG         NUMBER(1)                       NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   ENDBAL               NUMBER(15,2)                    NOT NULL,
   ENDBALFLAG           NUMBER(1)                       NOT NULL,
   CONSTRAINT PK_T_RPTSUBJBAL PRIMARY KEY (ACCDATE, SUBJNO)
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

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.BEGINBAL IS
'�ڳ����';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.BEGINBALFLAG IS
'�ڳ�����';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.ENDBAL IS
'��ĩ���';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.ENDBALFLAG IS
'��ĩ����';

/*==============================================================*/
/* Table: T_RPTSUBJLEDGER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSUBJLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTSUBJLEDGER PRIMARY KEY (ACCDATE, SUBJNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.BALANCE IS
'���';

/*==============================================================*/
/* Table: T_RPTSYSSTAT                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTSYSSTAT  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ITEMID               INTEGER                         NOT NULL,
   ITEMNAME             VARCHAR(60),
   ITEMVAL              VARCHAR(30),
   CONSTRAINT PK_T_RPTSYSSTAT PRIMARY KEY (ACCDATE, ITEMID)
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

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMID IS
'ͳ����Ŀ���';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMNAME IS
'ͳ����Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMVAL IS
'ͳ������';

/*==============================================================*/
/* Table: T_RPTTERMLEDGER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTTERMLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   SUBJNO               VARCHAR(20)                     NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER                         NOT NULL,
   DRAMT                NUMBER(15,2)                    NOT NULL,
   CRAMT                NUMBER(15,2)                    NOT NULL,
   CONSTRAINT PK_T_RPTTERMLEDGER PRIMARY KEY (ACCDATE, TERMID, ACCNO, TRANSTYPE, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.CRAMT IS
'����������';

/*==============================================================*/
/* Table: T_SEQNOCTL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SEQNOCTL  (
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER,
   ACCDATE              INTEGER,
   CONSTRAINT PK_T_SEQNOCTL PRIMARY KEY (TERMID)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_SEQNOCTL.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_SEQNOCTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_SEQNOCTL.ACCDATE IS
'��������';

/*==============================================================*/
/* Table: T_SHOP                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOP  (
   SHOPID               INTEGER                         NOT NULL,
   FSHOPID              INTEGER,
   AREACODE             VARCHAR(3),
   DEPTCODE             VARCHAR(30),
   SHOPNAME             VARCHAR(60),
   SHOPTYPE             NUMBER(1),
   ACCFLAG              CHAR(1),
   STATUS               CHAR(1),
   ACCNO                VARCHAR(10),
   CONTACTMAN           VARCHAR(60),
   IDTYPE               CHAR(1),
   IDNO                 VARCHAR(60),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   BOARDFEEFLAG         CHAR(1),
   RAKEOFFTYPE          CHAR(1),
   RAKEOFFRATE          NUMBER(5,4),
   DEPOSITAGIO          NUMBER(5,4),
   DEPOSITCNT           INTEGER,
   DEPOSITAMT           NUMBER(15,2),
   DISCOUNTAMT          NUMBER(15,2),
   BANKCODE             CHAR(2),
   BANKACCNO            VARCHAR(20),
   BANKACCNAME          VARCHAR(60),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_SHOP PRIMARY KEY (SHOPID)
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

COMMENT ON COLUMN YKT_CUR.T_SHOP.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.FSHOPID IS
'�ϼ��̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPTCODE IS
'���Ŵ���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.SHOPNAME IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.SHOPTYPE IS
'�̻�����1-�շ��̻�2-��ֵ�̻�';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ACCFLAG IS
'�Ƿ�������㣺1-��������0-��';

COMMENT ON COLUMN YKT_CUR.T_SHOP.STATUS IS
'�̻�״̬ 1-����2-����';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_SHOP.CONTACTMAN IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_SHOP.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_SHOP.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ADDR IS
'��ַ';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BOARDFEEFLAG IS
'�Ƿ��մ���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.RAKEOFFTYPE IS
'Ӷ������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.RAKEOFFRATE IS
'Ӷ�����';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITAGIO IS
'����ۿ���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITCNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITAMT IS
'����ܽ��';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DISCOUNTAMT IS
'�ۿ��ܽ��';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKACCNO IS
'�����ʺ�';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKACCNAME IS
'�����ʻ���';

COMMENT ON COLUMN YKT_CUR.T_SHOP.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.CLOSEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOP.USEFLAG IS
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_SHOPACC                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOPACC  (
   ACCNO                VARCHAR(10)                     NOT NULL,
   SHOPID               INTEGER                         NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20)                     NOT NULL,
   ACCPWD               VARCHAR(64),
   STATUS               CHAR(1)                         NOT NULL,
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2)                    NOT NULL,
   AVAILBAL             NUMBER(15,2)                    NOT NULL,
   FROZEBAL             NUMBER(15,2)                    NOT NULL,
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8)                      NOT NULL,
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_SHOPACC PRIMARY KEY (ACCNO)
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

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.ACCNAME IS
'�ʻ���';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.ACCPWD IS
'�ʻ�����';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.YDAYBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.BALANCE IS
'�ʻ����';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.AVAILBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.FROZEBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.LASTTRANSDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.LASTACCDATE IS
'�ϴ���������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.CLOSEDATE IS
'��������';

/*==============================================================*/
/* Table: T_SHOPCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOPCARD  (
   CARDNO               INTEGER                         NOT NULL,
   SHOPID               INTEGER,
   SHOWCARDNO           VARCHAR(10),
   CARDPHYID            VARCHAR(16),
   CARDPWD              VARCHAR(32),
   EXPIREDATE           VARCHAR(8),
   STATUS               CHAR(1)                         NOT NULL,
   LOSSFLAG             CHAR(1)                         NOT NULL,
   LOSSDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPCARD PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CARDPWD IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.EXPIREDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.STATUS IS
'��¼״̬1-����2-ע��';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LOSSFLAG IS
'1-��ʧ0-δ��ʧ';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LOSSDATE IS
'��ʧ����';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SHOPMEAL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOPMEAL  (
   SHOPID               INTEGER                         NOT NULL,
   ACCNO                VARCHAR(10),
   ENDTIME1             VARCHAR(6),
   ENDTIME2             VARCHAR(6),
   ENDTIME3             VARCHAR(6),
   ENDTIME4             VARCHAR(6),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPMEAL PRIMARY KEY (SHOPID)
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

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME1 IS
'��ͽ���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME2 IS
'��ͽ���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME3 IS
'��ͽ���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME4 IS
'ҹ�ͽ���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SHOPPOS                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOPPOS  (
   ID                   INTEGER                         NOT NULL,
   DEVICEID             INTEGER                         NOT NULL,
   DEVPHYID             VARCHAR(20),
   SHOPID               INTEGER                         NOT NULL,
   ENDTIME              VARCHAR(6),
   REMARK               VARCHAR(240),
   STARTDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   STATUS               CHAR(1),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPPOS PRIMARY KEY (ID)
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

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.ID IS
'��¼���';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.ENDTIME IS
'��ֹʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.STARTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.ENDDATE IS
'ͣ������';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.STATUS IS
'1-����2-����';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.LASTSAVED IS
'��ñ���ʱ��';

/*==============================================================*/
/* Index: IDX_SHOPPOSDEVICE                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_SHOPPOSDEVICE ON YKT_CUR.T_SHOPPOS (
   DEVPHYID ASC
)
PCTFREE 10
INITRANS 2
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_CUR;

/*==============================================================*/
/* Table: T_SHOPPOSTMP                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SHOPPOSTMP  (
   BATCHNO              VARCHAR(30)                     NOT NULL,
   SEQNO                INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   OPERCODE             VARCHAR(8),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20),
   SHOPID               INTEGER                         NOT NULL,
   ENDTIME              VARCHAR(6),
   STARTDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   ERRMSG               VARCHAR(240),
   CONSTRAINT PK_T_SHOPPOSTMP PRIMARY KEY (BATCHNO, SEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.SEQNO IS
'����˳���';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.OPERCODE IS
'�������Ա';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.DEVICEID IS
'�豸ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.SHOPID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ENDTIME IS
'��ֹʱ��';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.STARTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ENDDATE IS
'ͣ������';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ERRMSG IS
'������Ϣ';

/*==============================================================*/
/* Table: T_SITE                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SITE  (
   SITENO               INTEGER                         NOT NULL,
   SITENAME             VARCHAR(60),
   IP                   VARCHAR(15),
   MACHINECODE          VARCHAR(60),
   LASTSAVED            VARCHAR(30),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_SITE PRIMARY KEY (SITENO)
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

COMMENT ON COLUMN YKT_CUR.T_SITE.SITENO IS
'վ���';

COMMENT ON COLUMN YKT_CUR.T_SITE.SITENAME IS
'վ������';

COMMENT ON COLUMN YKT_CUR.T_SITE.IP IS
'IP��ַ';

COMMENT ON COLUMN YKT_CUR.T_SITE.MACHINECODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SITE.LASTSAVED IS
'��󱣴�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SITE.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_SPECIALTY                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SPECIALTY  (
   SPECIALTYCODE        VARCHAR(30)                     NOT NULL,
   SPECIALTYNAME        VARCHAR(60),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SPECIALTY PRIMARY KEY (SPECIALTYCODE)
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

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.SPECIALTYCODE IS
'רҵ����';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.SPECIALTYNAME IS
'רҵ����';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.USEFLAG IS
'ʹ�ñ�־';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SUBJECT                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBJECT  (
   SUBJNO               VARCHAR(20)                     NOT NULL,
   SUBJNAME             VARCHAR(60),
   SUBJTYPE             INTEGER,
   BALFLAG              NUMBER(1),
   FSUBJNO              VARCHAR(20),
   SUBJLEVEL            INTEGER,
   ENDFLAG              CHAR(1),
   CONSTRAINT PK_T_SUBJECT PRIMARY KEY (SUBJNO)
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

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJNAME IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJTYPE IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BALFLAG IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.FSUBJNO IS
'�ϼ���Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJLEVEL IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.ENDFLAG IS
'ĩ����־';

/*==============================================================*/
/* Table: T_SUBSIDY                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBSIDY  (
   BATCHNO              VARCHAR(30)                     NOT NULL,
   SEQNO                INTEGER                         NOT NULL,
   STUEMPNO             VARCHAR(20),
   CUSTID               INTEGER,
   SUBSIDYNO            INTEGER,
   CARDNO               INTEGER,
   SUMMARY              VARCHAR(60),
   BROKERNAME           VARCHAR(60),
   BROKERIDNO           VARCHAR(60),
   PAYTYPE              INTEGER,
   VOUCHERNO            VARCHAR(20),
   AMOUNT               NUMBER(15,2),
   SUBSIDYTYPE          CHAR(1),
   IMPDATE              VARCHAR(8),
   IMPTIME              VARCHAR(6),
   PUTDATE              VARCHAR(8),
   PUTTIME              VARCHAR(6),
   GETDATE              VARCHAR(8),
   GETTIME              VARCHAR(6),
   STATUS               CHAR(1),
   ERRMSG               VARCHAR(240),
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_SUBSIDY PRIMARY KEY (BATCHNO, SEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SEQNO IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUBSIDYNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.BROKERNAME IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.BROKERIDNO IS
'���������֤��';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PAYTYPE IS
'֧����ʽ:1-�ֽ�2-֧Ʊ3-���ѱ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.VOUCHERNO IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUBSIDYTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.IMPDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.IMPTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PUTDATE IS
'�·�����';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PUTTIME IS
'�·�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.GETDATE IS
'��ȡ����';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.GETTIME IS
'��ȡʱ��';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.STATUS IS
'״̬:1-δ�·�2-���·�3-����ȡ-4-��Ч';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.ERRMSG IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.OPERCODE IS
'����Ա��';

/*==============================================================*/
/* Index: IDX_SUBSIDY_BATCHNO_CUSTID                            */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.IDX_SUBSIDY_BATCHNO_CUSTID ON YKT_CUR.T_SUBSIDY (
   BATCHNO ASC,
   CUSTID ASC
);

/*==============================================================*/
/* Table: T_SUBSYSPARA                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBSYSPARA  (
   SYSID                INTEGER                         NOT NULL,
   WORKMODE             CHAR(1),
   BEATINTERVAL         INTEGER,
   BEATCNTLIMIT         INTEGER,
   REQBEATFUNCNO        INTEGER,
   REQDEVFUNCNO         INTEGER,
   REQTASKFUNCNO        INTEGER,
   RESPFUNCNO           INTEGER,
   EXECTIMEOUT          INTEGER,
   COLINTERVAL          INTEGER,
   QRYINTERVAL          INTEGER,
   TASKMAXLIMIT         INTEGER,
   BCCDRTPNO            INTEGER,
   BCCDRTPIP            VARCHAR(15),
   BCCDRTPPORT          INTEGER,
   BCCMAINFUNCNO        INTEGER,
   BCCINTERVAL          INTEGER,
   CONSTRAINT PK_T_SUBSYSPARA PRIMARY KEY (SYSID)
);

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.SYSID IS
'��ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.WORKMODE IS
'����ģʽ';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BEATINTERVAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BEATCNTLIMIT IS
'������������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQBEATFUNCNO IS
'�������͹��ܺ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQDEVFUNCNO IS
'�����豸��Ϣ���ܺ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQTASKFUNCNO IS
'���������ܺ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.RESPFUNCNO IS
'Ӧ���ܺ�';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.EXECTIMEOUT IS
'ִ�г�ʱʱ��';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.COLINTERVAL IS
'�ɼ����';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.QRYINTERVAL IS
'��ѯ������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.TASKMAXLIMIT IS
'�����������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BCCDRTPNO IS
'BCCDRTPNO';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BCCDRTPIP IS
'BCCDRTPIP';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BCCDRTPPORT IS
'BCCDRTPPORT';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BCCMAINFUNCNO IS
'BCCMAINFUNCNO';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BCCINTERVAL IS
'BCCINTERVAL';

/*==============================================================*/
/* Table: T_SUBSYSTEM                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBSYSTEM  (
   SYSID                INTEGER                         NOT NULL,
   SYSNAME              VARCHAR(60),
   SYSTYPE              INTEGER,
   AREACODE             VARCHAR(3),
   SERVERID             INTEGER,
   MACADDR              VARCHAR(17),
   IP                   VARCHAR(15),
   PORT                 INTEGER,
   CARDVERNO            VARCHAR(12)                    DEFAULT '000000000000',
   INITKEY              VARCHAR(32),
   DYNAKEY              VARCHAR(32),
   SYNCTIME             VARCHAR(30),
   RUNSTATUS            INTEGER,
   STATUS               CHAR(1),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_SUBSYSTEM PRIMARY KEY (SYSID)
);

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SYSID IS
'SYSID';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SYSNAME IS
'SYSNAME';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SYSTYPE IS
'SYSTYPE';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.AREACODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SERVERID IS
'SERVERID';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.MACADDR IS
'MACADDR';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.IP IS
'IP';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.PORT IS
'PORT';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.CARDVERNO IS
'���汾��';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.INITKEY IS
'INITKEY';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.DYNAKEY IS
'DYNAKEY';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SYNCTIME IS
'SYNCTIME';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.RUNSTATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.STATUS IS
'STATUS';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.OPENDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.CLOSEDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.REMARK IS
'REMARK';

/*==============================================================*/
/* Table: T_SYSKEY                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SYSKEY  (
   KEYCODE              VARCHAR(60)                     NOT NULL,
   KEYNAME              VARCHAR(60),
   KEYVAL               NUMBER(10),
   MAXVAL               INTEGER,
   KEYTYPE              CHAR(1),
   CONSTRAINT PK_T_SYSKEY PRIMARY KEY (KEYCODE)
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

COMMENT ON COLUMN YKT_CUR.T_SYSKEY.KEYCODE IS
'KEYCODE';

COMMENT ON COLUMN YKT_CUR.T_SYSKEY.KEYNAME IS
'KEYNAME';

COMMENT ON COLUMN YKT_CUR.T_SYSKEY.KEYVAL IS
'KEYVALUE';

COMMENT ON COLUMN YKT_CUR.T_SYSKEY.MAXVAL IS
'���ֵ';

COMMENT ON COLUMN YKT_CUR.T_SYSKEY.KEYTYPE IS
'KEYTYPE';

/*==============================================================*/
/* Table: T_SYSPARA                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SYSPARA  (
   PARAID               INTEGER                         NOT NULL,
   PARAVAL              VARCHAR(60),
   PARANAME             VARCHAR(60),
   PARAUNIT             VARCHAR(30),
   DISPLAYFLAG          CHAR(1),
   REMARK               VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SYSPARA PRIMARY KEY (PARAID)
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

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARAID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARAVAL IS
'����ֵ';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARANAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARAUNIT IS
'��λ';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.DISPLAYFLAG IS
'�Ƿ���ʾ';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.LASTSAVED IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_TRANSCODE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_TRANSCODE  (
   TRANSCODE            INTEGER                         NOT NULL,
   TRANSNAME            VARCHAR(60),
   LOGFLAG              INTEGER,
   LIMITFLAG            INTEGER,
   FEEFLAG              INTEGER,
   TRANSFLAG            INTEGER,
   DISABLEFLAG          INTEGER,
   CONSTRAINT PK_T_TRANSCODE PRIMARY KEY (TRANSCODE)
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

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.TRANSNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.LOGFLAG IS
'�Ƿ��¼����Ա��־:0-����¼1-ֻ��¼�ɹ���ˮ2-ֻ��¼ʧ��3-�ɹ�ʧ�ܶ���¼';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.LIMITFLAG IS
'�Ƿ����Ʋ���Ա:0������1-����';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.FEEFLAG IS
'�շѱ�־';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.TRANSFLAG IS
'���ױ�־';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.DISABLEFLAG IS
'���ñ�־';

/*==============================================================*/
/* Table: T_TRANSDTL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_TRANSDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   REFNO                NUMBER(14),
   TRANSCODE            INTEGER,
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   STUEMPNO             VARCHAR(20),
   SHOWCARDNO           NUMBER(10),
   CARDNO               INTEGER,
   PURSENO              INTEGER,
   TRANSFLAG            NUMBER(1),
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   ADDAMT               NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   PAYTYPE              INTEGER,
   VOUCHERNO            VARCHAR(20),
   OPERCODE             VARCHAR(8),
   SYSID                INTEGER,
   DEVPHYID             VARCHAR(20),
   DEVSEQNO             INTEGER,
   EXTTYPE              INTEGER,
   EXTDATA              VARCHAR(30),
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   OFFLINEFLAG          NUMBER(1),
   REVFLAG              CHAR(1),
   STATUS               CHAR(1),
   ERRCODE              INTEGER,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_TRANSDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CUSTNAME IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSFLAG IS
'1��ֵ��־2���Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ADDAMT IS
'��Ϊ�Ӹ�Ϊ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.MANAGEFEE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.PAYTYPE IS
'֧����ʽ';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.VOUCHERNO IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.SYSID IS
'��ϵͳ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.EXTTYPE IS
'������������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.EXTDATA IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.OFFLINEFLAG IS
'�ѻ���־';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REVFLAG IS
'������־0-δ����1-�ѳ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.STATUS IS
'��¼״̬1:δ����2-����ʧ��3-�ɹ�';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_TRANSDTL_CARDNO                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_TRANSDTL_CARDNO ON YKT_CUR.T_TRANSDTL (
   CARDNO ASC
)
TABLESPACE TS_YKT_HIS;

/*==============================================================*/
/* Index: IDX_TRANSDTL_CUSTID                                   */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_TRANSDTL_CUSTID ON YKT_CUR.T_TRANSDTL (
   CUSTID ASC
)
TABLESPACE TS_YKT_HIS;

/*==============================================================*/
/* Table: T_TRANSINFO                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_TRANSINFO  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   TRANSCODE            INTEGER,
   PAYTYPE              INTEGER,
   VOUCHERNO            VARCHAR(20),
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   SHOWCARDNO           NUMBER(10),
   CARDNO               INTEGER,
   PURSENO              INTEGER,
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   OPERCODE             VARCHAR(8),
   SYSID                INTEGER,
   DEVPHYID             VARCHAR(20),
   DEVSEQNO             INTEGER,
   OFFLINEFLAG          NUMBER(1),
   EXTTYPE              INTEGER,
   EXTDATA              VARCHAR(30),
   REVFLAG              CHAR(1),
   STATUS               CHAR(1),
   ERRCODE              INTEGER,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_TRANSINFO PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.PAYTYPE IS
'֧����ʽ';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.VOUCHERNO IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CUSTNAME IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.PURSENO IS
'Ǯ����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.MANAGEFEE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.SYSID IS
'��ϵͳ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.OFFLINEFLAG IS
'�ѻ���־';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.EXTTYPE IS
'������������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.EXTDATA IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.REVFLAG IS
'������־0-δ����1-�ѳ���';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.STATUS IS
'��¼״̬1:δ����2-����ʧ��3-�ɹ�';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_TRANSDTL_CARDNO2                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_TRANSDTL_CARDNO2 ON YKT_CUR.T_TRANSINFO (
   CARDNO ASC
);

/*==============================================================*/
/* Table: T_TRANSTYPE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_TRANSTYPE  (
   TRANSTYPE            INTEGER                         NOT NULL,
   TRANSNAME            VARCHAR(60),
   DISPLAYFLAG          CHAR(1),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_TRANSTYPE PRIMARY KEY (TRANSTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.TRANSTYPE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.TRANSNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.DISPLAYFLAG IS
'��ʾ��־1-��ʾ0-����ʾ';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.USEFLAG IS
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_WATERCARDBAL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_WATERCARDBAL  (
   CARDNO               INTEGER                         NOT NULL,
   OLDCARDNO            INTEGER,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   CARDCNT              INTEGER                         NOT NULL,
   CARDBAL              NUMBER(15,2)                    NOT NULL,
   TOTALDPSAMT          NUMBER(15,2),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_WATERCARDBAL PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.OLDCARDNO IS
'ԭ����';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.CARDCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.CARDBAL IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TOTALDPSAMT IS
'�ۼƳ�ֵ���';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.LASTSAVED IS
'����������';

/*==============================================================*/
/* Table: T_WATERPOSDTL                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_WATERPOSDTL  (
   TRANSDATE            VARCHAR(8)                      NOT NULL,
   TRANSTIME            VARCHAR(6),
   TERMID               INTEGER,
   DEVPHYID             VARCHAR(20)                     NOT NULL,
   DEVSEQNO             INTEGER                         NOT NULL,
   CARDNO               INTEGER                         NOT NULL,
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   TRANSMARK            INTEGER,
   SHOPID               INTEGER,
   BATCHNO              VARCHAR(30),
   SYSID                INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   ACCDATE              VARCHAR(8),
   ACCTIME              VARCHAR(6),
   TERMSEQNO            INTEGER,
   STATUS               CHAR(1)                         NOT NULL,
   ERRCODE              INTEGER,
   ERRMSG               VARCHAR(240),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_WATERPOSDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TERMID IS
'�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDNO IS
'���׿���';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.AMOUNT IS
'������-���������';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TRANSMARK IS
'���ױ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.SHOPID IS
'�̻�����';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.BATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.SYSID IS
'��ϵͳID';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.STATUS IS
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ERRMSG IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DELFLAG IS
'ɾ����־';

/*==============================================================*/
/* Index: IDX_CARDNOCARDCNT2                                    */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDNOCARDCNT2 ON YKT_CUR.T_WATERPOSDTL (
   CARDNO ASC,
   CARDCNT ASC
);

/*==============================================================*/
/* Table: T_WATERTRANSDTL                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_WATERTRANSDTL  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                         NOT NULL,
   TERMSEQNO            INTEGER                         NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   REFNO                NUMBER(14),
   TRANSCODE            INTEGER,
   CUSTID               INTEGER,
   CUSTNAME             VARCHAR(60),
   STUEMPNO             VARCHAR(20),
   SHOWCARDNO           NUMBER(10),
   CARDNO               INTEGER,
   TRANSFLAG            NUMBER(1),
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   SYSID                INTEGER,
   DEVPHYID             VARCHAR(20),
   DEVSEQNO             INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   STATUS               CHAR(1),
   ERRCODE              INTEGER,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_WATERTRANSDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
)
PCTFREE 10
INITRANS 1
STORAGE
(
    INITIAL 64K
    MINEXTENTS 1
    MAXEXTENTS UNLIMITED
)
TABLESPACE TS_YKT_HIS
LOGGING
MONITORING
 NOPARALLEL;

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.ACCTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TERMID IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CUSTNAME IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.SHOWCARDNO IS
'��ʾ����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSFLAG IS
'1��ֵ��־2���Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDCNT IS
'�����״���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDBEFBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.SYSID IS
'��ϵͳ���';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.DEVPHYID IS
'�豸����ID';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.DEVSEQNO IS
'�豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.COLDATE IS
'�ɼ�����';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.COLTIME IS
'�ɼ�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.STATUS IS
'��¼״̬1:δ����2-����ʧ��3-�ɹ�';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_TRANSDTL_CARDNO3                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_TRANSDTL_CARDNO3 ON YKT_CUR.T_WATERTRANSDTL (
   CARDNO ASC
)
TABLESPACE TS_YKT_HIS;

/*==============================================================*/
/* Index: IDX_TRANSDTL_CUSTID2                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_TRANSDTL_CUSTID2 ON YKT_CUR.T_WATERTRANSDTL (
   CUSTID ASC
)
TABLESPACE TS_YKT_HIS;

