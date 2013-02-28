/*==============================================================*/
/* DBMS name:      ORACLE Version 10g                           */
/* Created on:     2011-02-26 16:18:27                          */
/*==============================================================*/


CREATE SEQUENCE YKT_CUR.S_REFNO
INCREMENT BY 1
START WITH 1
 MAXVALUE 999999
 MINVALUE 1
CYCLE
 CACHE 100
ORDER;

/*==============================================================*/
/* Table: T_ACTPARA                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ACTPARA  (
   PARAID               NUMBER(9)                       NOT NULL,
   BOOKSETNO            NUMBER(2)                       NOT NULL,
   CONSTRAINT PK_T_ACTPARA PRIMARY KEY (PARAID)
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

COMMENT ON COLUMN YKT_CUR.T_ACTPARA.PARAID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_ACTPARA.BOOKSETNO IS
'���׺�';

/*==============================================================*/
/* Table: T_APPLY                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_APPLY  (
   APPLYID              NUMBER(9)                       NOT NULL,
   CARDNO               NUMBER(9),
   OLDCARDID            NUMBER(9),
   NEWCARDID            NUMBER(9),
   CARDSTATUS           NUMBER(2),
   APPLYDATE            NUMBER(8),
   APPLYTYPE            NUMBER(2),
   APPLYREASON          VARCHAR(60),
   STATUS               NUMBER(1),
   HANDLEDATE           NUMBER(8),
   UPDTIME              VARCHAR(14),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_APPLY PRIMARY KEY (APPLYID)
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

COMMENT ON COLUMN YKT_CUR.T_APPLY.APPLYID IS
'���뵥��';

COMMENT ON COLUMN YKT_CUR.T_APPLY.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_APPLY.OLDCARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_APPLY.NEWCARDID IS
'�¿�ID';

COMMENT ON COLUMN YKT_CUR.T_APPLY.CARDSTATUS IS
'��״̬';

COMMENT ON COLUMN YKT_CUR.T_APPLY.APPLYDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_APPLY.APPLYTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_APPLY.APPLYREASON IS
'����ԭ��';

COMMENT ON COLUMN YKT_CUR.T_APPLY.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_APPLY.HANDLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_APPLY.UPDTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_APPLY.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_APPLY_CARDNO_STATUS                               */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_APPLY_CARDNO_STATUS ON YKT_CUR.T_APPLY (
   CARDNO ASC,
   STATUS ASC
);

/*==============================================================*/
/* Table: T_AREA                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_AREA  (
   AREACODE             VARCHAR(3)                      NOT NULL,
   AREANAME             VARCHAR(60),
   FAREACODE            VARCHAR(3),
   OLDAREACODE          VARCHAR(3),
   AREALEVEL            NUMBER(9),
   ADDR                 VARCHAR(240),
   REMARK               VARCHAR(60),
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
/* Table: T_AUTHCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_AUTHCARD  (
   CARDNO               NUMBER(9)                       NOT NULL,
   OPERCODE             VARCHAR(8),
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   PRIVILEGE            NUMBER(9),
   EXPIREDATE           NUMBER(8),
   STATUS               VARCHAR(1000),
   LOSSFLAG             NUMBER(1),
   LOSSDATE             NUMBER(8),
   OPENDATE             NUMBER(8),
   CLOSEDATE            NUMBER(8),
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
/* Table: T_AUTHTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_AUTHTYPE  (
   AUTHTYPE             NUMBER(9)                       NOT NULL,
   AUTHTYPENAME         VARCHAR(60),
   AUTHCLASS            NUMBER(9),
   CONSTRAINT PK_T_AUTHTYPE PRIMARY KEY (AUTHTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_AUTHTYPE.AUTHTYPE IS
'Ȩ��С��';

COMMENT ON COLUMN YKT_CUR.T_AUTHTYPE.AUTHTYPENAME IS
'Ȩ������';

COMMENT ON COLUMN YKT_CUR.T_AUTHTYPE.AUTHCLASS IS
'Ȩ�޴���';

/*==============================================================*/
/* Table: T_BANK                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANK  (
   BANKID               NUMBER(9)                       NOT NULL,
   BANKCODE             VARCHAR(12)                     NOT NULL,
   BANKNAME             VARCHAR(60)                     NOT NULL,
   ENABLED              NUMBER(1)                      DEFAULT 0 NOT NULL,
   SVRBEGINTIME         NUMBER(6),
   SVRENDTIME           NUMBER(6),
   FRONTID              NUMBER(9),
   BANKIP               VARCHAR(15),
   BANKPORT             NUMBER(9),
   BANKTIMEOUT          NUMBER(2),
   CONSTRAINT PK_T_BANK PRIMARY KEY (BANKID)
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

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANK.ENABLED IS
'�Ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_BANK.SVRBEGINTIME IS
'����ʼʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANK.SVRENDTIME IS
'�����ֹʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANK.FRONTID IS
'ǰ�û�ID';

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKIP IS
'����IP';

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKPORT IS
'���ж˿�';

COMMENT ON COLUMN YKT_CUR.T_BANK.BANKTIMEOUT IS
'���ж˳�ʱʱ��(��)';

/*==============================================================*/
/* Index: UNIQ_BANKCODE_BANKCODE                                */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_BANKCODE_BANKCODE ON YKT_CUR.T_BANK (
   BANKCODE ASC
);

/*==============================================================*/
/* Table: T_BANKCARD                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCARD  (
   CUSTID               INTEGER                         NOT NULL,
   BANKCARDNO           VARCHAR(20)                     NOT NULL,
   BANKCODE             VARCHAR(12),
   BATCHNO              VARCHAR(14),
   CREATEDDATE          NUMBER(8),
   RELATEDATE           NUMBER(8),
   LASTSAVED            VARCHAR(14),
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
/* Index: UNIQ_BANKCARD_CUSTID                                  */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_BANKCARD_CUSTID ON YKT_CUR.T_BANKCARD (
   CUSTID ASC
);

/*==============================================================*/
/* Table: T_BANKCHKDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKDTL  (
   BANKID               NUMBER(9)                       NOT NULL,
   BANKDATE             NUMBER(8)                       NOT NULL,
   RECORDNO             NUMBER(9)                       NOT NULL,
   AMOUNT               NUMBER(9)                       NOT NULL,
   TRANSDATE            NUMBER(8),
   CHKRESULT            CHAR(1)                        DEFAULT 'I',
   RESOLVED             CHAR(1),
   REMARK               VARCHAR(60),
   LOCALSNO             VARCHAR(20),
   BANKSNO              VARCHAR(20),
   BANKCARDNO           VARCHAR(20),
   CARDNO               NUMBER(9),
   CUSTID               INTEGER,
   STUEMPNO             VARCHAR(20),
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_BANKCHKDTL PRIMARY KEY (BANKID, BANKDATE, RECORDNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKID IS
'���б�ʶ';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKDATE IS
'�˵�����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.RECORDNO IS
'��¼��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.AMOUNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKRESULT IS
'���˽��:I-δ���� = һ��,���� ,Nһ��ͨ������Uһ��ͨδ����,X����B���в�����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.RESOLVED IS
'��S''-����''I''����''A''-����''R''�Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.LOCALSNO IS
'������ˮ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKSNO IS
'������ˮ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.STUEMPNO IS
'ѧ����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.OPERCODE IS
'����Ա';

/*==============================================================*/
/* Index: IDX_BANKCHKDTL_BANKCARDNO                             */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_BANKCHKDTL_BANKCARDNO ON YKT_CUR.T_BANKCHKDTL (
   BANKCARDNO ASC
);

/*==============================================================*/
/* Table: T_BANKCHKFILE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKCHKFILE  (
   BANKDATE             NUMBER(8)                       NOT NULL,
   BANKID               NUMBER(9)                       NOT NULL,
   BANKCHKFILE          VARCHAR(240),
   LOCALCHKFILE         VARCHAR(240),
   LOCALCVTFILE         VARCHAR(240),
   FILESOURCE           CHAR(1),
   STATUS               CHAR(1),
   RESOLVED             CHAR(1),
   REMARK               VARCHAR(60),
   BANKCNT              NUMBER(9),
   BANKAMT              NUMBER(9),
   LOCALCNT             NUMBER(9),
   LOCALAMT             NUMBER(9),
   CRTTIME              VARCHAR(14),
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_BANKCHKFILE PRIMARY KEY (BANKID, BANKDATE)
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

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.BANKDATE IS
'�˵�����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.BANKID IS
'���б�ʶ';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.BANKCHKFILE IS
'���ж����ļ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.LOCALCHKFILE IS
'���ض����ļ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.LOCALCVTFILE IS
'����ת���ļ���';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.FILESOURCE IS
'''L�� ���� ��B''����';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.STATUS IS
'�˶�״̬:F�����ļ���Vת����C������S�������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.RESOLVED IS
'��N������''I''���ԡ�,��E''����,S-''���� C-''�ر�''';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.BANKCNT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.BANKAMT IS
'�����ܽ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.LOCALCNT IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.LOCALAMT IS
'�����ܽ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.CRTTIME IS
'��¼����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKFILE.UPDTIME IS
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_BANKERRCODE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKERRCODE  (
   ERRCODE              NUMBER(9)                       NOT NULL,
   ERRMSG               VARCHAR(240),
   CONSTRAINT PK_T_BANKERRCODE PRIMARY KEY (ERRCODE)
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

COMMENT ON COLUMN YKT_CUR.T_BANKERRCODE.ERRCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKERRCODE.ERRMSG IS
'������Ϣ';

/*==============================================================*/
/* Table: T_BANKTRANSDTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BANKTRANSDTL  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   REFNO                VARCHAR(14)                     NOT NULL,
   BATCHNO              NUMBER(9)                       NOT NULL,
   SAMNO                VARCHAR(12)                     NOT NULL,
   SAMSEQNO             NUMBER(9)                       NOT NULL,
   TERMDATE             NUMBER(8)                       NOT NULL,
   TERMTIME             NUMBER(6),
   CARDNO               NUMBER(9),
   CARDID               NUMBER(9),
   CARDASNO             VARCHAR(20),
   CARDTYPE             NUMBER(2),
   DPSCNT               NUMBER(6),
   AMOUNT               NUMBER(9),
   BEFCARDBAL           NUMBER(9),
   AFTCARDBAL           NUMBER(9),
   BALANCE              NUMBER(9),
   EXPDATE              NUMBER(8),
   TRANSCODE            NUMBER(4),
   BRANCHID             NUMBER(6),
   MERCHID              NUMBER(9),
   HOSTDATE             NUMBER(8),
   HOSTTIME             NUMBER(6),
   BANKCODE             VARCHAR(12),
   BANKCARDNO           VARCHAR(20),
   BANKREFNO            VARCHAR(12),
   STATUS               NUMBER(2),
   WCTATUS              NUMBER(2),
   TAC                  VARCHAR(8),
   ERRCODE              NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_BANKTRANSDTL PRIMARY KEY (ACCDATE, REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BATCHNO IS
'��ֵ���κ�';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.SAMNO IS
'SAM���ն˱��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.SAMSEQNO IS
'SAM�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.TERMDATE IS
'�ն�����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.TERMTIME IS
'�ն�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.CARDTYPE IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.DPSCNT IS
'����ֵǰ����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.AMOUNT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BEFCARDBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.AFTCARDBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BALANCE IS
'�˻����(���׺�)';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.EXPDATE IS
'����Ч��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BRANCHID IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.MERCHID IS
'Ӫ���̻���';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.HOSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.HOSTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BANKCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BANKCARDNO IS
'���п���';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.BANKREFNO IS
'���вο���';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.WCTATUS IS
'д��״̬';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.TAC IS
'TAC��';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.ERRCODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_BANKTRANSDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_BANKTRANSDTL_TERM                                 */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.IDX_BANKTRANSDTL_TERM ON YKT_CUR.T_BANKTRANSDTL (
   BATCHNO ASC,
   SAMNO ASC,
   SAMSEQNO ASC,
   TERMDATE ASC
);

/*==============================================================*/
/* Table: T_BLACKLIST                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BLACKLIST  (
   CARDID               NUMBER(9)                       NOT NULL,
   CARDSN               VARCHAR(20)                     NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   LISTTYPE             CHAR(1),
   LISTVERNO            VARCHAR(14),
   LISTLEVEL            NUMBER(9),
   INTOLISTCAUSE        NUMBER(2),
   INTOLISTCNT          NUMBER(9),
   INTOLISTDATE         NUMBER(8),
   RMFLAG               NUMBER(1),
   RMDATE               NUMBER(8),
   CONSTRAINT PK_T_BLACKLIST PRIMARY KEY (CARDID)
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

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.CARDSN IS
'��Ƭ���к�';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.LISTTYPE IS
'��������''B''-������''G''-������';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.LISTVERNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.LISTLEVEL IS
'��������0-��ʾ����������Խ�󼶱�Խ��';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.INTOLISTCAUSE IS
'1�����ѿ�����
2�� ��ֵ������
3�� �û���ʧ
4�� ����̨¼��
5�� �˿�
������ԭ��:1���ѿ�����2��ֵ������3�û���ʧ4����¼��5��ʧ';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.INTOLISTCNT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.INTOLISTDATE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.RMFLAG IS
'�����־:0-δ���1�ѽ��';

COMMENT ON COLUMN YKT_CUR.T_BLACKLIST.RMDATE IS
'�������';

/*==============================================================*/
/* Table: T_BOOKSET                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BOOKSET  (
   BOOKSETNO            NUMBER(2)                       NOT NULL,
   BOOKSETNAME          VARCHAR(60)                     NOT NULL,
   DEPTNAME             VARCHAR(60),
   DEPTSHORTNAME        VARCHAR(60),
   SUPERVISOR           NUMBER(9),
   PERIODYEAR           NUMBER(4),
   PERIODMONTH          NUMBER(2),
   VOUCHERCLASS         NUMBER(1),
   ENABLEDATE           NUMBER(8),
   CONSTRAINT PK_T_BOOKSET PRIMARY KEY (BOOKSETNO)
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

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.BOOKSETNO IS
'���׺�';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.BOOKSETNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.DEPTNAME IS
'��λ����';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.DEPTSHORTNAME IS
'��λ���';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.SUPERVISOR IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.PERIODYEAR IS
'���������ڼ�';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.PERIODMONTH IS
'�����»�����';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.VOUCHERCLASS IS
'����ƾ֤���';

COMMENT ON COLUMN YKT_CUR.T_BOOKSET.ENABLEDATE IS
'��������';

/*==============================================================*/
/* Table: T_BOOKTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BOOKTYPE  (
   BOOKTYPE             NUMBER(2)                       NOT NULL,
   BOOKNAME             VARCHAR(240)                    NOT NULL,
   CONSTRAINT PK_T_BOOKTYPE PRIMARY KEY (BOOKTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_BOOKTYPE.BOOKTYPE IS
'�˲�����';

COMMENT ON COLUMN YKT_CUR.T_BOOKTYPE.BOOKNAME IS
'�˲�����';

/*==============================================================*/
/* Table: T_BRANCH                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_BRANCH  (
   BRANCHID             NUMBER(6)                       NOT NULL,
   AREACODE             VARCHAR(3),
   TOWNCODE             VARCHAR(20),
   BRANCHNO             VARCHAR(20),
   BRANCHNAME           VARCHAR(60),
   BRANCHTYPE           CHAR(1),
   CONTACTMAN           VARCHAR(90),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   FAX                  VARCHAR(30),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   STATUS               NUMBER(1),
   OPENDATE             NUMBER(8),
   CLOSEDATE            NUMBER(8),
   CONSTRAINT PK_T_BRANCH PRIMARY KEY (BRANCHID)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.AREACODE IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.TOWNCODE IS
'����';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHNO IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHTYPE IS
'�������ͣ�1-��������2-��ֵ��3-����';

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

/*==============================================================*/
/* Index: UNIQ_BRANCH_BRANCHNO                                  */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_BRANCH_BRANCHNO ON YKT_CUR.T_BRANCH (
   BRANCHNO ASC
);

/*==============================================================*/
/* Table: T_CARD                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARD  (
   CARDID               NUMBER(9)                       NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDASNO             VARCHAR(20),
   CARDMNGRNO           VARCHAR(20),
   CARDUCID             VARCHAR(20),
   CARDPHYID            VARCHAR(16),
   CARDTYPE             NUMBER(2),
   CARDPHYTYPE          NUMBER(4),
   ISSUEUNIT            NUMBER(2),
   CARDVERSION          NUMBER(2),
   LISTVERSION          VARCHAR(14),
   CUSTID               INTEGER,
   PASSWD               VARCHAR(32),
   STATUS               NUMBER(2),
   MADEDATE             NUMBER(8),
   ISSUEBATCHNO         VARCHAR(14),
   ISSUEDATE            NUMBER(8),
   ENABLEDATE           NUMBER(8),
   EXPDATE              NUMBER(8),
   DEPOSIT              NUMBER(9)                      DEFAULT 0 NOT NULL,
   BALANCE              NUMBER(9)                      DEFAULT 0 NOT NULL,
   CARDBAL              NUMBER(9)                      DEFAULT 0 NOT NULL,
   DPSAMT               NUMBER(6)                      DEFAULT 0 NOT NULL,
   PAYAMT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   DPSCNT               NUMBER(6),
   PAYCNT               NUMBER(6),
   DPSNUM               NUMBER(6),
   PAYNUM               NUMBER(6),
   TERMID               NUMBER(9),
   TRANSDATE            NUMBER(8),
   TRANSTIME            NUMBER(6),
   DPSWFAILFLAG         NUMBER(1),
   LOSSFLAG             NUMBER(1),
   LOSSDATE             NUMBER(8),
   LOSSEFTDATE          NUMBER(8),
   DELDATE              NUMBER(8),
   DELFLAG              NUMBER(1)                      DEFAULT 0 NOT NULL,
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_CARD PRIMARY KEY (CARDID)
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

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDNO IS
'���ڷ��񿨺š�';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDMNGRNO IS
'��Դ�����';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDUCID IS
'�ֻ�UCID';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYTYPE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_CARD.ISSUEUNIT IS
'���е�λ';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDVERSION IS
'��Ƭ�汾';

COMMENT ON COLUMN YKT_CUR.T_CARD.LISTVERSION IS
'�������汾��';

COMMENT ON COLUMN YKT_CUR.T_CARD.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.PASSWD IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARD.STATUS IS
'��״̬';

COMMENT ON COLUMN YKT_CUR.T_CARD.MADEDATE IS
'�ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_CARD.ISSUEBATCHNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_CARD.ISSUEDATE IS
'��(��)������';

COMMENT ON COLUMN YKT_CUR.T_CARD.ENABLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.EXPDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARD.DEPOSIT IS
'��Ѻ��';

COMMENT ON COLUMN YKT_CUR.T_CARD.BALANCE IS
'���˻����';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDBAL IS
'��ʵ�����';

COMMENT ON COLUMN YKT_CUR.T_CARD.DPSAMT IS
'��ֵ�ܽ��';

COMMENT ON COLUMN YKT_CUR.T_CARD.PAYAMT IS
'�����ܽ��';

COMMENT ON COLUMN YKT_CUR.T_CARD.DPSCNT IS
'��ֵ����';

COMMENT ON COLUMN YKT_CUR.T_CARD.PAYCNT IS
'���Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.DPSNUM IS
'��ֵ�ܱ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.PAYNUM IS
'�����ܱ���';

COMMENT ON COLUMN YKT_CUR.T_CARD.TERMID IS
'������ն˺�';

COMMENT ON COLUMN YKT_CUR.T_CARD.TRANSDATE IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_CARD.TRANSTIME IS
'�����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARD.DPSWFAILFLAG IS
'��ֵд��ʧ�ܱ�־';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSFLAG IS
'��ʧ��־:1-��ʧ0-δ��ʧ';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSDATE IS
'��ʧ����';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSEFTDATE IS
'��ʧ��Ч����';

COMMENT ON COLUMN YKT_CUR.T_CARD.DELDATE IS
'ɾ������';

COMMENT ON COLUMN YKT_CUR.T_CARD.DELFLAG IS
'ɾ����־';

COMMENT ON COLUMN YKT_CUR.T_CARD.UPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Index: IDX_CARD_CARDASNO                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARD_CARDASNO ON YKT_CUR.T_CARD (
   CARDASNO ASC
);

/*==============================================================*/
/* Table: T_CARDBALUPDLIST                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDBALUPDLIST  (
   BATCHNO              VARCHAR(14)                     NOT NULL,
   SEQNO                NUMBER(9)                       NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   TRANSDATE            NUMBER(8),
   STATUS               CHAR(1)                         NOT NULL,
   AMOUNT               NUMBER(9)                       NOT NULL,
   SUMMARY              VARCHAR(60),
   TRANSCODE            NUMBER(4),
   LASTUPDTIME          VARCHAR(14),
   CONSTRAINT PK_T_CARDBALUPDLIST PRIMARY KEY (BATCHNO, SEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.BATCHNO IS
'���κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.SEQNO IS
'�·����';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.STATUS IS
'N-δ����P���·�S����ȡFд��ʧ��Iд���ж�C����';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.AMOUNT IS
'��д�����Ϊ��Ǯ��Ϊ��Ǯ';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.TRANSCODE IS
'ԭ���״���';

COMMENT ON COLUMN YKT_CUR.T_CARDBALUPDLIST.LASTUPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Index: IDX_CARDBALUPDLIST_CARDNO                             */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDBALUPDLIST_CARDNO ON YKT_CUR.T_CARDBALUPDLIST (
   CARDNO ASC,
   STATUS ASC
);

/*==============================================================*/
/* Table: T_CARDBATCH                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDBATCH  (
   BATCHNO              VARCHAR(14)                     NOT NULL,
   CARDNUM              NUMBER(9),
   CRTTIME              VARCHAR(14),
   SYNDATE              NUMBER(8),
   STARTDATE            NUMBER(8),
   ENDDATE              NUMBER(8),
   STATUS               NUMBER(2),
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_CARDBATCH PRIMARY KEY (BATCHNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.BATCHNO IS
'���κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.CARDNUM IS
'�ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.CRTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.SYNDATE IS
'ͬ������';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.STARTDATE IS
'�ƿ���ʼ����';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.ENDDATE IS
'�ƿ���������';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.STATUS IS
'�ƿ�״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDBATCH.UPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_CARDBITMAP                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDBITMAP  (
   CARDID               NUMBER(9)                       NOT NULL,
   BASENO               NUMBER(9),
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
   CONSTRAINT PK_T_CARDBITMAP PRIMARY KEY (CARDID)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.CARDID IS
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

/*==============================================================*/
/* Table: T_CARDDTL                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDDTL  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   REFNO                VARCHAR(14)                     NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   SAMNO                VARCHAR(12),
   SAMSEQNO             NUMBER(9),
   TERMDATE             NUMBER(8),
   TERMTIME             NUMBER(6),
   CARDID               NUMBER(9)                       NOT NULL,
   CARDASNO             VARCHAR(20),
   CARDTYPE             NUMBER(2),
   DPSCNT               NUMBER(6)                      DEFAULT 0 NOT NULL,
   PAYCNT               NUMBER(6)                      DEFAULT 0 NOT NULL,
   BEFCARDBAL           NUMBER(9)                      DEFAULT 0 NOT NULL,
   AFTCARDBAL           NUMBER(9)                      DEFAULT 0 NOT NULL,
   AMOUNT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   OTHERAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   BALANCE              NUMBER(9)                      DEFAULT 0,
   TRANSCODE            NUMBER(4),
   TRANSTYPE            NUMBER(9),
   TRANSDESC            VARCHAR(60),
   CITYCODE             NUMBER(2),
   MERCHID              NUMBER(9),
   POSNO                NUMBER(9),
   POSSEQNO             NUMBER(9),
   BRANCHID             NUMBER(6),
   OPERID               NUMBER(9),
   HOSTDATE             NUMBER(8),
   HOSTTIME             NUMBER(6),
   STATUS               NUMBER(2),
   WCSTATUS             NUMBER(2),
   ERRCODE              NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_CARDDTL PRIMARY KEY (ACCDATE, REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SAMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.DPSCNT IS
'����ֵ����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.PAYCNT IS
'�����Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.BEFCARDBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.AFTCARDBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.AMOUNT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.OTHERAMT IS
'��/�ۿ��ɱ���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.BALANCE IS
'�˻����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TRANSDESC IS
'����˵��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CITYCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.MERCHID IS
'Ӫ���̻���';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.POSNO IS
'POS�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.POSSEQNO IS
'POS��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.BRANCHID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.OPERID IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.HOSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.HOSTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.WCSTATUS IS
'д��״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.ERRCODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_CARDDTL_CARDNO                                    */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDDTL_CARDNO ON YKT_CUR.T_CARDDTL (
   CARDNO ASC
);

/*==============================================================*/
/* Table: T_CARDFACTORY                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDFACTORY  (
   FACTORYID            NUMBER(2)                       NOT NULL,
   FACTORYCODE          VARCHAR(2)                      NOT NULL,
   FACTORYNAME          VARCHAR(60)                     NOT NULL,
   CARDVERNO            NUMBER(2)                      DEFAULT 1 NOT NULL,
   CONSTRAINT PK_T_CARDFACTORY PRIMARY KEY (FACTORYID)
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

COMMENT ON COLUMN YKT_CUR.T_CARDFACTORY.FACTORYID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_CARDFACTORY.FACTORYCODE IS
'���Ҵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDFACTORY.FACTORYNAME IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDFACTORY.CARDVERNO IS
'���汾��';

/*==============================================================*/
/* Table: T_CARDLEDGER                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDLEDGER  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDSEQNO            NUMBER(6)                       NOT NULL,
   SUBSEQNO             NUMBER                          NOT NULL,
   TRANSTYPE            NUMBER(4)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   DRAMT                NUMBER(9)                      DEFAULT 0 NOT NULL,
   CRAMT                NUMBER(9)                      DEFAULT 0 NOT NULL,
   BALANCE              NUMBER(9)                      DEFAULT 0 NOT NULL,
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_CARDLEDGER PRIMARY KEY (ACCDATE, CARDNO, CARDSEQNO, SUBSEQNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.CARDSEQNO IS
'����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.SUBSEQNO IS
'����ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.BALANCE IS
'���';

COMMENT ON COLUMN YKT_CUR.T_CARDLEDGER.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_CARDLIST                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDLIST  (
   CARDASNO             VARCHAR(20)                     NOT NULL,
   BATCHNO              VARCHAR(14)                     NOT NULL,
   CARDNO               NUMBER(9),
   CARDUID              VARCHAR(16),
   ISSUEUNIT            NUMBER(2),
   CUSTNAME             VARCHAR(90),
   IDTYPE               VARCHAR(2),
   IDNO                 VARCHAR(60),
   BIRTHDAY             NUMBER(8),
   HEIGHT               NUMBER(3),
   SEX                  CHAR(1),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   UNITNAME             VARCHAR(240),
   MARRIED              VARCHAR(2),
   EDUCATION            VARCHAR(2),
   POLITICS             VARCHAR(2),
   INCOMESRC            VARCHAR(2),
   COUNTRY              VARCHAR(3),
   NATION               VARCHAR(2),
   NATIVE               VARCHAR(60),
   DOMICILETYPE         VARCHAR(2),
   DOMICILE             VARCHAR(240),
   LIVEREASON           VARCHAR(2),
   ADDR                 VARCHAR(240),
   LIVEDATE             NUMBER(8),
   ARRIVALDATE          NUMBER(8),
   PHOTO                BLOB,
   SYNFLAG              NUMBER(1),
   STATUS               NUMBER(2),
   REMARK               VARCHAR(60),
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_CARDLIST PRIMARY KEY (CARDASNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.BATCHNO IS
'�ƿ����κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.CARDUID IS
'��UID';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.ISSUEUNIT IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.BIRTHDAY IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.HEIGHT IS
'���(CM)';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.SEX IS
'�Ա�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.UNITNAME IS
'��λ����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.MARRIED IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.EDUCATION IS
'�Ļ��̶�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.POLITICS IS
'������ò';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.INCOMESRC IS
'������Դ';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.COUNTRY IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.NATION IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.NATIVE IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.DOMICILETYPE IS
'�������ڵ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.DOMICILE IS
'�������ڵ�';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.LIVEREASON IS
'��ס����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.ADDR IS
'��ס��ַ';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.LIVEDATE IS
'��ס����';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.ARRIVALDATE IS
'�״ε��ﱾ������';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.PHOTO IS
'��Ƭ';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.SYNFLAG IS
'ͬ����־:0-δͬ��1��ͬ��';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.STATUS IS
'�ƿ�״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_CARDLIST.UPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Index: IDX_CARDLIST_BATCHNO                                  */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDLIST_BATCHNO ON YKT_CUR.T_CARDLIST (
   BATCHNO ASC
);

/*==============================================================*/
/* Table: T_CARDMADEINFO                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDMADEINFO  (
   CARDID               NUMBER(9)                       NOT NULL,
   APPLYID              NUMBER(9),
   CRTBATNO             VARCHAR(14),
   MADEBATNO            VARCHAR(14),
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDASNO             VARCHAR(20),
   CARDMNGRNO           VARCHAR(20),
   CARDPHYID            VARCHAR(16),
   CARDPHYTYPE          NUMBER(4),
   CARDTYPE             NUMBER(2),
   ISSUEUNIT            NUMBER(2),
   CUSTID               INTEGER,
   APPLYSTATUS          NUMBER(2),
   MADESTATUS           NUMBER(2),
   APPLYTYPE            NUMBER(2),
   APPLYDATE            NUMBER(8),
   MADEDATE             NUMBER(8),
   DEPOSIT              NUMBER(9)                      DEFAULT 0 NOT NULL,
   DPSAMT               NUMBER(6),
   DPSFLAG              NUMBER(1),
   EXPDATE              NUMBER(8),
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_CARDMADEINFO PRIMARY KEY (CARDID)
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

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.APPLYID IS
'���뵥��';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CRTBATNO IS
'�������κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.MADEBATNO IS
'�ƿ����κ�';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDNO IS
'���ڷ��񿨺š�';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDMNGRNO IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDPHYID IS
'������ID';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDPHYTYPE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.ISSUEUNIT IS
'������λ';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.APPLYSTATUS IS
'������״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.MADESTATUS IS
'�ƿ�״̬';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.APPLYTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.APPLYDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.MADEDATE IS
'�ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.DEPOSIT IS
'��Ѻ��/�ɱ���';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.DPSAMT IS
'Ԥ���ֵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.DPSFLAG IS
'�Ƿ��ֵ';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.EXPDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDMADEINFO.UPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Index: IDX_CARDMADEINFO_APPLYID                              */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_CARDMADEINFO_APPLYID ON YKT_CUR.T_CARDMADEINFO (
   APPLYID ASC
);

/*==============================================================*/
/* Table: T_CARDNOCHANGE                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDNOCHANGE  (
   OLDCARDNO            NUMBER(9)                       NOT NULL,
   NEWCARDNO            NUMBER(9)                       NOT NULL,
   CHANGEDATE           NUMBER(8),
   CONSTRAINT PK_T_CARDNOCHANGE PRIMARY KEY (OLDCARDNO)
);

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.OLDCARDNO IS
'�ɿ���';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.NEWCARDNO IS
'�¿���';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.CHANGEDATE IS
'�������';

/*==============================================================*/
/* Table: T_CARDNOCTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDNOCTL  (
   ISSUEUNIT            NUMBER(2)                       NOT NULL,
   CARDNO               NUMBER(9),
   CONSTRAINT PK_T_CARDNOCTL PRIMARY KEY (ISSUEUNIT)
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

COMMENT ON COLUMN YKT_CUR.T_CARDNOCTL.ISSUEUNIT IS
'ISSUEUNIT';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCTL.CARDNO IS
'CARDNO';

ALTER TABLE YKT_CUR.T_CARDNOCTL
   ADD CONSTRAINT CKT_T_CARDNOCTL CHECK (ISSUEUNIT =SUBSTR(CARDNO,1,2)  AND CARDNO>=100000000);

/*==============================================================*/
/* Table: T_CARDPHYTYPE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDPHYTYPE  (
   CARDPHYTYPE          NUMBER(4)                       NOT NULL,
   CARDPHYTYPENAME      VARCHAR(60)                     NOT NULL,
   CARDPHYTYPECODE      NUMBER(9)                       NOT NULL,
   USEFLAG              NUMBER(1)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_CARDPHYTYPE PRIMARY KEY (CARDPHYTYPE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPENAME IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPECODE IS
'���������ͱ���';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.USEFLAG IS
'�Ƿ�����';

/*==============================================================*/
/* Table: T_CARDSEQNOCTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDSEQNOCTL  (
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDSEQNO            NUMBER(9)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_CARDSEQNOCTL PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDSEQNOCTL.CARDNO IS
'CARDNO';

COMMENT ON COLUMN YKT_CUR.T_CARDSEQNOCTL.CARDSEQNO IS
'CARDSEQNO';

/*==============================================================*/
/* Table: T_CARDSNCTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDSNCTL  (
   YEAR                 NUMBER(2)                       NOT NULL,
   FACTORYID            NUMBER(1)                       NOT NULL,
   APPTYPE              NUMBER(1)                       NOT NULL,
   CITYCODE             NUMBER(2)                       NOT NULL,
   SEQNO                NUMBER(9)                       NOT NULL,
   CONSTRAINT PK_T_CARDSNCTL PRIMARY KEY (YEAR, FACTORYID, APPTYPE, CITYCODE)
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

COMMENT ON COLUMN YKT_CUR.T_CARDSNCTL.YEAR IS
'���';

COMMENT ON COLUMN YKT_CUR.T_CARDSNCTL.FACTORYID IS
'���Ҵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDSNCTL.APPTYPE IS
'Ӧ������';

COMMENT ON COLUMN YKT_CUR.T_CARDSNCTL.CITYCODE IS
'���б���';

COMMENT ON COLUMN YKT_CUR.T_CARDSNCTL.SEQNO IS
'˳���';

/*==============================================================*/
/* Table: T_CARDTRANS                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDTRANS  (
   CARDNO               NUMBER(9)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   TRANSTIME            NUMBER(6)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   TERMID               NUMBER(9)                      DEFAULT 0 NOT NULL,
   TERMSEQNO            NUMBER(9)                      DEFAULT 0 NOT NULL,
   DPSCNT               NUMBER(6)                       NOT NULL,
   PAYCNT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   AMOUNT               NUMBER(9)                       NOT NULL,
   CARDBEFBAL           NUMBER(9)                       NOT NULL,
   CARDAFTBAL           NUMBER(9)                      DEFAULT 0 NOT NULL,
   UPDCNT               NUMBER(9)                      DEFAULT 0,
   UPDTIME              CHAR(14)                       DEFAULT 'to_char(sysdate,''YYYYMMDDHH24MISS'')',
   CONSTRAINT PK_T_CARDTRANS PRIMARY KEY (CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.TRANSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.TERMID IS
'�����ն�';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.DPSCNT IS
'��ֵ����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.PAYCNT IS
'���Ѵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.AMOUNT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.CARDBEFBAL IS
'����ǰ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.CARDAFTBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.UPDCNT IS
'���´���';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANS.UPDTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_CARDTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CARDTYPE  (
   CARDTYPE             NUMBER(2)                       NOT NULL,
   CARDTYPENAME         VARCHAR(60),
   CARDPHYTYPE          NUMBER(4),
   ANONYMFLAG           NUMBER(1),
   PRESTOREAMT          NUMBER(9),
   CARDCOSTFEE          NUMBER(9),
   REUSEABLE            NUMBER(1),
   RENEWABLE            NUMBER(1),
   RECYCLEABLE          NUMBER(1),
   FIXDAYFLAG           NUMBER(1),
   FIXDAYCNT            NUMBER(9),
   ENABLED              NUMBER(1),
   MAXDPSAMT            NUMBER(9),
   MAXCARDBAL           NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_CARDTYPE PRIMARY KEY (CARDTYPE)
);

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDTYPENAME IS
'���������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDPHYTYPE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.ANONYMFLAG IS
'1-����0-����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.PRESTOREAMT IS
'Ԥ��ֵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDCOSTFEE IS
'���ɱ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.REUSEABLE IS
'�ܷ�����:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RENEWABLE IS
'�ܷ񲹰�:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RECYCLEABLE IS
'�ܷ����:0-����1-��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYFLAG IS
'��Ч���Ƿ�̶�����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYCNT IS
'��Ч����';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.ENABLED IS
'ʹ�ñ�־:0-δʹ��1��ʹ��';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.MAXDPSAMT IS
'��������ֵ���';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.MAXCARDBAL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.REMARK IS
'��;';

/*==============================================================*/
/* Table: T_CFGPAYMENT                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGPAYMENT  (
   PAYCODE              NUMBER(9)                       NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   ENABLED              NUMBER(1)                       NOT NULL,
   ONLINEPAY            NUMBER(1)                       NOT NULL,
   PAYCHKFLAG           NUMBER(1)                       NOT NULL,
   PAYEEACCTYPE         NUMBER(1)                       NOT NULL,
   SHOPID               NUMBER(9)                       NOT NULL,
   BCCFUNCNO            NUMBER(9),
   BCCDRTPNO            NUMBER(9),
   IP                   VARCHAR(15),
   PORT                 NUMBER(9),
   TIMEOUT              NUMBER(9),
   LASTSAVED            VARCHAR(14),
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
/* Table: T_CFGSPLIT                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGSPLIT  (
   TRANSCODE            NUMBER(4)                       NOT NULL,
   TRANSTYPE            NUMBER(4)                      DEFAULT 0,
   DRSUBJNO             NUMBER(10)                     DEFAULT 0 NOT NULL,
   CRSUBJNO             NUMBER(10)                     DEFAULT 0 NOT NULL,
   DRFLAG               NUMBER(1)                      DEFAULT 0 NOT NULL,
   CRFLAG               NUMBER(1)                      DEFAULT 0 NOT NULL,
   DRDESC               VARCHAR(60)                     NOT NULL,
   CRDESC               VARCHAR(60),
   CONSTRAINT PK_T_CFGSPLIT PRIMARY KEY (TRANSCODE)
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

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRSUBJNO IS
'�跽��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRSUBJNO IS
'������Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRFLAG IS
'�Ƿ�˶Խ跽��ϸ��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRFLAG IS
'�Ƿ�˶Դ�����ϸ��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRDESC IS
'�跽ժҪ';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRDESC IS
'����ժҪ';

/*==============================================================*/
/* Table: T_CFGVER                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CFGVER  (
   CFGTYPE              NUMBER(9)                       NOT NULL,
   CFGVERNO             NUMBER(9)                       NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(14),
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
/* Table: T_CUSTOMER                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTOMER  (
   CUSTID               INTEGER                         NOT NULL,
   CARDNO               NUMBER(9),
   CARDID               NUMBER(9),
   CARDTYPE             NUMBER(2),
   ISSUEUNIT            NUMBER(9),
   EXPMONTHS            NUMBER(9),
   APPLYDATE            NUMBER(8),
   APPLYSTATUS          NUMBER(2),
   PREPAIDAMT           NUMBER(9),
   CUSTNAME             VARCHAR(90),
   IDTYPE               VARCHAR(2),
   IDNO                 VARCHAR(60),
   BIRTHDAY             NUMBER(8),
   HEIGHT               NUMBER(3),
   SEX                  VARCHAR(2000),
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   UNITNAME             VARCHAR(240),
   MARRIED              VARCHAR(2),
   EDUCATION            VARCHAR(2),
   POLITICS             VARCHAR(2),
   INCOMESRC            VARCHAR(2),
   COUNTRY              VARCHAR(3),
   NATION               VARCHAR(2),
   NATIVE               VARCHAR(60),
   DOMICILETYPE         VARCHAR(2),
   DOMICILE             VARCHAR(240),
   LIVEREASON           VARCHAR(2),
   ADDR                 VARCHAR(240),
   LIVEDATE             NUMBER(8),
   ARRIVALDATE          NUMBER(8),
   UPDTIME              VARCHAR(14),
   DELFLAG              NUMBER(1),
   DELDATE              NUMBER(8),
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

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CARDNO IS
'���ڷ��񿨺š�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ISSUEUNIT IS
'������λ';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EXPMONTHS IS
'��Ч�·�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.APPLYDATE IS
'�������汾��';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.APPLYSTATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.PREPAIDAMT IS
'Ԥ���';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDNO IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.BIRTHDAY IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.HEIGHT IS
'���';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.SEX IS
'�Ա�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EMAIL IS
'EMAIL';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.UNITNAME IS
'��λ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.MARRIED IS
'MARRIED';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EDUCATION IS
'EDUCATION';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.POLITICS IS
'POLITICS';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.INCOMESRC IS
'INCOMESRC';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.COUNTRY IS
'COUNTRY';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.NATION IS
'NATION';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.NATIVE IS
'NATIVE';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DOMICILETYPE IS
'DOMICILETYPE';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DOMICILE IS
'DOMICILE';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.LIVEREASON IS
'LIVEREASON';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ADDR IS
'ADDR';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.LIVEDATE IS
'LIVEDATE';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ARRIVALDATE IS
'ARRIVALDATE';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.UPDTIME IS
'UPDTIME';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DELFLAG IS
'DELFLAG';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DELDATE IS
'DELDATE';

/*==============================================================*/
/* Table: T_CUSTTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_CUSTTYPE  (
   CUSTTYPE             INTEGER                         NOT NULL,
   CUSTTYPENAME         VARCHAR(60),
   FEETYPE              INTEGER,
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

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.OLDCUSTTYPE IS
'ԭ�ͻ����';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.USEFLAG IS
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_DAYSTATBANKTERM                                     */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATBANKTERM  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   SAMNO                VARCHAR(12)                     NOT NULL,
   VALIDTYPE            NUMBER(1)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   CARDTYPE             NUMBER(2)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   TRANSCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TRANSAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   STATDATE             NUMBER(8)                       NOT NULL,
   CONSTRAINT PK_T_DAYSTATBANKTERM PRIMARY KEY (ACCDATE, SAMNO, TRANSCODE, CARDTYPE, VALIDTYPE, TRANSDATE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.VALIDTYPE IS
'1��Ч2��Ч';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.TRANSAMT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATBANKTERM.STATDATE IS
'ͳ������';

/*==============================================================*/
/* Table: T_DAYSTATDPSTERM                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATDPSTERM  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   SAMNO                VARCHAR(12)                     NOT NULL,
   OPERID               NUMBER(9)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   CARDTYPE             NUMBER(2)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   VALIDTYPE            NUMBER(1)                       NOT NULL,
   TRANSCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TRANSAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   STATDATE             NUMBER(8)                       NOT NULL,
   CONSTRAINT PK_T_DAYSTATDPSTERM PRIMARY KEY (ACCDATE, SAMNO, OPERID, TRANSCODE, CARDTYPE, TRANSDATE, VALIDTYPE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.OPERID IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.VALIDTYPE IS
'1��Ч2��Ч';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.TRANSAMT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATDPSTERM.STATDATE IS
'ͳ������';

/*==============================================================*/
/* Table: T_DAYSTATMERCH                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATMERCH  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   MERCHID              NUMBER(9)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   CARDTYPE             NUMBER(2)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   VALIDTYPE            NUMBER(1)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   STATDATE             NUMBER(8)                       NOT NULL,
   TRANSCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TRANSAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   FEEAMT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_DAYSTATMERCH PRIMARY KEY (ACCDATE, MERCHID, TRANSCODE, CARDTYPE, TRANSDATE, VALIDTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.VALIDTYPE IS
'�Ϸ�״̬:1��Ч2��Ч';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.STATDATE IS
'ͳ������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.TRANSCNT IS
'���ױ���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.TRANSAMT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATMERCH.FEEAMT IS
'������';

/*==============================================================*/
/* Table: T_DAYSTATOPER                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATOPER  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   OPERID               NUMBER(9)                       NOT NULL,
   BRANCHID             NUMBER(6)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   TRANSCNT             NUMBER(9)                       NOT NULL,
   TRANSAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   PERIODYEAR           NUMBER(4),
   PERIODMONTH          NUMBER(2),
   STATDATE             NUMBER(8),
   CONSTRAINT PK_T_DAYSTATOPER PRIMARY KEY (ACCDATE, OPERID, BRANCHID, TRANSCODE, TRANSDATE)
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

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.OPERID IS
'����ԱID';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.BRANCHID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.TRANSAMT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.PERIODYEAR IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.PERIODMONTH IS
'����·�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATOPER.STATDATE IS
'ͳ������';

/*==============================================================*/
/* Table: T_DAYSTATPKGFILE                                      */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATPKGFILE  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   PKGID                NUMBER(9)                       NOT NULL,
   FILEID               NUMBER(9)                       NOT NULL,
   MERCHID              NUMBER(9)                       NOT NULL,
   SAMNO                VARCHAR(12)                     NOT NULL,
   CARDTYPE             NUMBER(2)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   VALIDTYPE            NUMBER(1)                       NOT NULL,
   TRANSCNT             NUMBER(9)                       NOT NULL,
   TRANSAMT             NUMBER(9)                       NOT NULL,
   STATDATE             NUMBER(8)                       NOT NULL,
   CONSTRAINT PK_T_DAYSTATPKGFILE PRIMARY KEY (ACCDATE, PKGID, FILEID, MERCHID, SAMNO, CARDTYPE, TRANSCODE, VALIDTYPE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.PKGID IS
'PKGID';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.FILEID IS
'�����ļ�ID';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.VALIDTYPE IS
'1��Ч2��Ч';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.TRANSAMT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPKGFILE.STATDATE IS
'ͳ������';

/*==============================================================*/
/* Table: T_DAYSTATPOS                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DAYSTATPOS  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   SAMNO                VARCHAR(12)                     NOT NULL,
   MERCHID              NUMBER(9)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   CARDTYPE             NUMBER(2)                       NOT NULL,
   VALIDTYPE            NUMBER(1)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   STATDATE             NUMBER(8)                       NOT NULL,
   TRANSCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TRANSAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_DAYSTATPOS PRIMARY KEY (ACCDATE, SAMNO, MERCHID, TRANSCODE, CARDTYPE, VALIDTYPE, TRANSDATE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.TRANSCODE IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.VALIDTYPE IS
'1��Ч2��Ч';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.STATDATE IS
'ͳ������';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_DAYSTATPOS.TRANSAMT IS
'������';

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
   DEPTLEVEL            NUMBER(9),
   DEPTTYPE             NUMBER(1)                      DEFAULT 0,
   OLDDEPTCODE          VARCHAR(30),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(14),
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
/* Table: T_DEVNOCTL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DEVNOCTL  (
   DEVKEYID             VARCHAR(4)                      NOT NULL,
   SEQNO                NUMBER(6),
   CONSTRAINT PK_T_DEVNOCTL PRIMARY KEY (DEVKEYID)
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

COMMENT ON COLUMN YKT_CUR.T_DEVNOCTL.DEVKEYID IS
'DEVKEYID';

COMMENT ON COLUMN YKT_CUR.T_DEVNOCTL.SEQNO IS
'SEQNO';

ALTER TABLE YKT_CUR.T_DEVNOCTL
   ADD CONSTRAINT CKT_T_DEVNOCTL CHECK (LENGTH(DEVKEYID)=4);

/*==============================================================*/
/* Table: T_DICTIONARY                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DICTIONARY  (
   DICTTYPE             NUMBER(9)                       NOT NULL,
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
/* Table: T_DPSDTL                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_DPSDTL  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   REFNO                VARCHAR(14)                     NOT NULL,
   HOSTDATE             NUMBER(8)                       NOT NULL,
   HOSTTIME             NUMBER(6)                       NOT NULL,
   CARDID               NUMBER(9)                       NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDASNO             VARCHAR(20),
   CARDTYPE             NUMBER(2),
   DPSCNT               NUMBER(6)                      DEFAULT 0,
   PAYCNT               NUMBER(6)                      DEFAULT 0,
   TERMDATE             NUMBER(8)                       NOT NULL,
   TERMTIME             NUMBER(6),
   TERMID               NUMBER(9),
   SAMNO                VARCHAR(12)                     NOT NULL,
   TERMSEQNO            NUMBER(9)                       NOT NULL,
   TRANSTYPE            NUMBER(4),
   AMOUNT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   OTHERAMT             NUMBER(9)                      DEFAULT 0,
   BEFCARDBAL           NUMBER(9)                      DEFAULT 0,
   AFTCARDBAL           NUMBER(9)                      DEFAULT 0,
   LASTSAMNO            VARCHAR(12),
   LASTTYPE             NUMBER(4),
   LASTAMT              NUMBER(9)                      DEFAULT 0 NOT NULL,
   LASTDATE             NUMBER(8),
   LASTTIME             NUMBER(6),
   BALANCE              NUMBER(9),
   OPERID               NUMBER(9),
   BRANCHID             NUMBER(6),
   MERCHID              NUMBER(9),
   TRANSCODE            NUMBER(4)                       NOT NULL,
   STATUS               NUMBER(2),
   WCSTATUS             NUMBER(2),
   ERRCODE              NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_DPSDTL PRIMARY KEY (ACCDATE, REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.HOSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.HOSTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.CARDID IS
'��ID';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.DPSCNT IS
'����ֵǰ����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.PAYCNT IS
'������ǰ����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TERMDATE IS
'�ն�����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TERMTIME IS
'�ն�ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TERMID IS
'�ն��豸ID��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.SAMNO IS
'�ն˱��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TERMSEQNO IS
'�ն��豸��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.AMOUNT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.OTHERAMT IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.BEFCARDBAL IS
'����ǰ�����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.AFTCARDBAL IS
'���׺����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.LASTSAMNO IS
'�ϴ��ն˺�';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.LASTTYPE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.LASTAMT IS
'�ϴν��׽��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.LASTDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.LASTTIME IS
'�ϴν���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.BALANCE IS
'�˻����(���׺�)';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.OPERID IS
'����ԱID';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.BRANCHID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.WCSTATUS IS
'д��״̬';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.ERRCODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_DPSDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_DPSDTL_CARDNO                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DPSDTL_CARDNO ON YKT_CUR.T_DPSDTL (
   CARDNO ASC
);

/*==============================================================*/
/* Index: IDX_DPSDTL_STATUS                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_DPSDTL_STATUS ON YKT_CUR.T_DPSDTL (
   STATUS ASC
);

/*==============================================================*/
/* Index: UNIQ_DPSDTL_POS                                       */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_DPSDTL_POS ON YKT_CUR.T_DPSDTL (
   TERMDATE ASC,
   SAMNO ASC,
   TERMSEQNO ASC
);

/*==============================================================*/
/* Table: T_ERRCODE                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_ERRCODE  (
   ERRCODE              NUMBER(9)                       NOT NULL,
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
/* Table: T_FRONT                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_FRONT  (
   FRONTID              NUMBER(9)                       NOT NULL,
   FRONTNAME            VARCHAR(60),
   IP                   VARCHAR(15),
   DRTPPORT             NUMBER(9)                      DEFAULT 4000,
   DRTPNODE             NUMBER,
   BCCMAINFUNCNO        NUMBER(9),
   CONSTRAINT PK_T_FRONT PRIMARY KEY (FRONTID)
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

COMMENT ON COLUMN YKT_CUR.T_FRONT.FRONTID IS
'FRONTID';

COMMENT ON COLUMN YKT_CUR.T_FRONT.FRONTNAME IS
'ǰ�û�����';

COMMENT ON COLUMN YKT_CUR.T_FRONT.IP IS
'IP��ַ';

COMMENT ON COLUMN YKT_CUR.T_FRONT.DRTPPORT IS
'DRTP�˿�';

COMMENT ON COLUMN YKT_CUR.T_FRONT.DRTPNODE IS
'DRTP�ڵ��';

COMMENT ON COLUMN YKT_CUR.T_FRONT.BCCMAINFUNCNO IS
'BCC�����ܺ�';

/*==============================================================*/
/* Table: T_FRONTCFG                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_FRONTCFG  (
   PARANAME             VARCHAR(60)                     NOT NULL,
   PARAVAL              VARCHAR(240)                    NOT NULL,
   CONSTRAINT PK_T_FRONTCFG PRIMARY KEY (PARANAME)
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

COMMENT ON COLUMN YKT_CUR.T_FRONTCFG.PARANAME IS
'PARANAME';

COMMENT ON COLUMN YKT_CUR.T_FRONTCFG.PARAVAL IS
'PARAVAL';

ALTER TABLE YKT_CUR.T_FRONTCFG
   ADD CONSTRAINT CKT_T_FRONTCFG CHECK (PARANAME = LOWER(PARANAME));

/*==============================================================*/
/* Table: T_MACHINECODE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MACHINECODE  (
   MACHINECODE          VARCHAR(60)                     NOT NULL,
   IP                   VARCHAR(15),
   LASTSAVED            VARCHAR(14),
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
/* Table: T_MAKECARDLIST                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MAKECARDLIST  (
   BATCHNO              VARCHAR(14)                     NOT NULL,
   CARDNO               NUMBER(9)                       NOT NULL,
   CARDASNO             VARCHAR(20)                     NOT NULL,
   EXPDATE              NUMBER(8),
   ISSUEUNIT            NUMBER(2),
   CUSTNAME             VARCHAR(90),
   IDTYPE               VARCHAR(2),
   IDNO                 VARCHAR(60),
   CONSTRAINT PK_T_MAKECARDLIST PRIMARY KEY (BATCHNO, CARDNO)
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

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.BATCHNO IS
'���κ�';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.CARDASNO IS
'Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.EXPDATE IS
'��Ч��';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.ISSUEUNIT IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.CUSTNAME IS
'����';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.IDTYPE IS
'֤������';

COMMENT ON COLUMN YKT_CUR.T_MAKECARDLIST.IDNO IS
'֤������';

/*==============================================================*/
/* Index: IDX_MAKECARDLIST_CARDSN                               */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.IDX_MAKECARDLIST_CARDSN ON YKT_CUR.T_MAKECARDLIST (
   CARDASNO ASC
);

/*==============================================================*/
/* Table: T_MEALTYPE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MEALTYPE  (
   MEALTYPE             NUMBER(9)                       NOT NULL,
   MEALNAME             VARCHAR(30)                     NOT NULL,
   ENDTIME              NUMBER(6)                       NOT NULL,
   LASTSAVED            VARCHAR(14),
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
/* Table: T_MERCH                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCH  (
   MERCHID              NUMBER(9)                       NOT NULL,
   SUBJNO               NUMBER(10),
   BALACE               NUMBER(9)                       NOT NULL,
   MERCHNO              VARCHAR(20),
   PRVMERCHNO           VARCHAR(20),
   MERCHNAME            VARCHAR(90),
   ENGLISHNAME          VARCHAR(60),
   SHORTNAME            VARCHAR(60),
   MERCHTYPE            CHAR(1),
   INDUSTRYTYPE         VARCHAR(10),
   STATUS               NUMBER(1),
   CONTACTS             VARCHAR(90),
   MOBILE               VARCHAR(30),
   TEL                  VARCHAR(30),
   FAX                  VARCHAR(30),
   EMAIL                VARCHAR(60),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   FEERATE              NUMBER(5,4),
   BANKNAME             VARCHAR(120),
   BANKACCNO            VARCHAR(20),
   BANKACCNAME          VARCHAR(90),
   UNIONBANKNO          VARCHAR(20),
   OPENDATE             NUMBER(8),
   CLOSEDATE            NUMBER(8),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_MERCH PRIMARY KEY (MERCHID)
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

COMMENT ON COLUMN YKT_CUR.T_MERCH.MERCHID IS
'�̻�ID';

COMMENT ON COLUMN YKT_CUR.T_MERCH.SUBJNO IS
'�̻���Ŀ';

COMMENT ON COLUMN YKT_CUR.T_MERCH.BALACE IS
'�˻����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.MERCHNO IS
'�����̻���';

COMMENT ON COLUMN YKT_CUR.T_MERCH.PRVMERCHNO IS
'ʡ�̻����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.MERCHNAME IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_MERCH.ENGLISHNAME IS
'�̻�Ӣ������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.SHORTNAME IS
'�̻����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.MERCHTYPE IS
'�̻����� ''P''-�շ��̻�''D''-��ֵ�̻�';

COMMENT ON COLUMN YKT_CUR.T_MERCH.INDUSTRYTYPE IS
'��ҵ����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.STATUS IS
'1����2����3����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.CONTACTS IS
'��ϵ��';

COMMENT ON COLUMN YKT_CUR.T_MERCH.MOBILE IS
'�ֻ�';

COMMENT ON COLUMN YKT_CUR.T_MERCH.TEL IS
'�绰';

COMMENT ON COLUMN YKT_CUR.T_MERCH.FAX IS
'����';

COMMENT ON COLUMN YKT_CUR.T_MERCH.EMAIL IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.ADDR IS
'Ӫҵ��ַ';

COMMENT ON COLUMN YKT_CUR.T_MERCH.ZIPCODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.FEERATE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.BANKNAME IS
'������������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.BANKACCNO IS
'�����˺�';

COMMENT ON COLUMN YKT_CUR.T_MERCH.BANKACCNAME IS
'�����ʻ���';

COMMENT ON COLUMN YKT_CUR.T_MERCH.UNIONBANKNO IS
'���к�';

COMMENT ON COLUMN YKT_CUR.T_MERCH.OPENDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.CLOSEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCH.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_MERCHBAL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHBAL  (
   MERCHID              NUMBER(9)                       NOT NULL,
   SUBJNO               NUMBER(10)                      NOT NULL,
   DRACCUMAMT           NUMBER(15)                     DEFAULT 0 NOT NULL,
   CRACCUMAMT           NUMBER(15)                     DEFAULT 0 NOT NULL,
   BALFLAG              NUMBER(1)                      DEFAULT 0 NOT NULL,
   BEGINBAL             NUMBER(9)                      DEFAULT 0 NOT NULL,
   YEARDRAMT            NUMBER(9)                      DEFAULT 0 NOT NULL,
   YEARCRAMT            NUMBER(9)                      DEFAULT 0 NOT NULL,
   MONTHDRAMT           NUMBER(9)                      DEFAULT 0 NOT NULL,
   MONTHCRAMT           NUMBER(9)                      DEFAULT 0 NOT NULL,
   DRBAL                NUMBER(9)                      DEFAULT 0 NOT NULL,
   CRBAL                NUMBER(9)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_MERCHBAL PRIMARY KEY (MERCHID)
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

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.MERCHID IS
'�̻�ID';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.DRACCUMAMT IS
'�跽�ۼƷ�����';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.CRACCUMAMT IS
'�����ۼƷ�����';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.BEGINBAL IS
'�ڳ����';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.YEARDRAMT IS
'����跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.YEARCRAMT IS
'�������������';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.MONTHDRAMT IS
'���½跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.MONTHCRAMT IS
'���´���������';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.DRBAL IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_MERCHBAL.CRBAL IS
'�������';

/*==============================================================*/
/* Table: T_MERCHDAY                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHDAY  (
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   MERCHID              NUMBER(9)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   PERIODDAY            NUMBER(2)                       NOT NULL,
   YEARDRAMT            NUMBER(9)                       NOT NULL,
   YEARCRAMT            NUMBER(9)                       NOT NULL,
   MONTHDRAMT           NUMBER(9)                       NOT NULL,
   MONTHCRAMT           NUMBER(9)                       NOT NULL,
   LASTDAYDRBAL         NUMBER(9)                       NOT NULL,
   LASTDAYCRBAL         NUMBER(9)                       NOT NULL,
   DRAMT                NUMBER(9)                       NOT NULL,
   CRAMT                NUMBER(9)                       NOT NULL,
   DRBAL                NUMBER(9)                       NOT NULL,
   CRBAL                NUMBER(9)                       NOT NULL,
   TOTALACCCNT          NUMBER(9)                       NOT NULL,
   NEWACCCNT            NUMBER(9)                       NOT NULL,
   CLOSEACCCNT          NUMBER(9)                       NOT NULL,
   CONSTRAINT PK_T_MERCHDAY PRIMARY KEY (SETTLEDATE, MERCHID)
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

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.SETTLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.PERIODDAY IS
'������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.YEARDRAMT IS
'�����ۼƽ跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.YEARCRAMT IS
'�����ۼƴ���������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.MONTHDRAMT IS
'�����ۼƽ跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.MONTHCRAMT IS
'�����ۼƴ���������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.LASTDAYDRBAL IS
'���ս跽���';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.LASTDAYCRBAL IS
'���մ������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.DRBAL IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.CRBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.TOTALACCCNT IS
'�ܻ���';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.NEWACCCNT IS
'�¿�����';

COMMENT ON COLUMN YKT_CUR.T_MERCHDAY.CLOSEACCCNT IS
'������';

/*==============================================================*/
/* Table: T_MERCHDEV                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHDEV  (
   TERMSN               VARCHAR(20)                     NOT NULL,
   PRVTERMSN            VARCHAR(20),
   MERCHID              NUMBER(9)                       NOT NULL,
   STATUS               NUMBER(2)                       NOT NULL,
   DEVTYPE              VARCHAR(8),
   POSID                NUMBER(9),
   REGDATE              NUMBER(8),
   ENABLEDATE           NUMBER(8),
   DISABLEDATE          NUMBER(1),
   UPDTIME              VARCHAR(14),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_MERCHDEV PRIMARY KEY (TERMSN)
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

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.TERMSN IS
'�ն����к�';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.PRVTERMSN IS
'ʡPOS�ն����к�';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.MERCHID IS
'�����̻���';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.STATUS IS
'1δ�����豸2����3����4ͣ��';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.DEVTYPE IS
'�豸����';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.POSID IS
'POS�豸ID';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.REGDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.ENABLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.DISABLEDATE IS
'ͣ������';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.UPDTIME IS
'������ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MERCHDEV.REMARK IS
'��ע';

/*==============================================================*/
/* Table: T_MERCHMONTH                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHMONTH  (
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   MERCHID              NUMBER(9)                       NOT NULL,
   LASTMONTHDRBAL       NUMBER(15)                      NOT NULL,
   LASTMONTHCRBAL       NUMBER(15)                      NOT NULL,
   YEARDRAMT            NUMBER(15)                      NOT NULL,
   YEARCRAMT            NUMBER(15)                      NOT NULL,
   DRAMT                NUMBER(15)                      NOT NULL,
   CRAMT                NUMBER(15)                      NOT NULL,
   DRBAL                NUMBER(15)                      NOT NULL,
   CRBAL                NUMBER(15)                      NOT NULL,
   TOTALACCCNT          NUMBER(9),
   NEWACCCNT            NUMBER(9),
   CLOSEACCCNT          NUMBER(9),
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   CONSTRAINT PK_T_MERCHMONTH PRIMARY KEY (PERIODYEAR, PERIODMONTH, MERCHID)
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

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.MERCHID IS
'�̻���';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.LASTMONTHDRBAL IS
'����ĩ�跽���';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.LASTMONTHCRBAL IS
'����ĩ�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.YEARDRAMT IS
'����跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.YEARCRAMT IS
'�������������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.DRBAL IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.CRBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.TOTALACCCNT IS
'�ܻ���';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.NEWACCCNT IS
'�¿�����';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.CLOSEACCCNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_MERCHMONTH.SETTLEDATE IS
'��������';

/*==============================================================*/
/* Table: T_MODULEAUTH                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MODULEAUTH  (
   MODULECODE           VARCHAR(30)                     NOT NULL,
   MODULENAME           VARCHAR(60),
   MENUSET              VARCHAR2(800),
   FUNCSET              VARCHAR2(600),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(14),
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
/* Table: T_OPERACCDTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERACCDTL  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   REFNO                VARCHAR(14)                     NOT NULL,
   BRANCHID             NUMBER(6)                       NOT NULL,
   OPERID               NUMBER(9)                       NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   TRANSCODE            NUMBER(4)                       NOT NULL,
   INAMT                NUMBER(9)                       NOT NULL,
   OUTAMT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_OPERACCDTL PRIMARY KEY (ACCDATE, REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.BRANCHID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.OPERID IS
'����ԱID';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.INAMT IS
'����';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.OUTAMT IS
'֧��';

COMMENT ON COLUMN YKT_CUR.T_OPERACCDTL.REMARK IS
'��ע';

/*==============================================================*/
/* Index: IDX_OPERACCDTL_OPERID                                 */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_OPERACCDTL_OPERID ON YKT_CUR.T_OPERACCDTL (
   OPERID ASC
);

/*==============================================================*/
/* Table: T_OPERATOR                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERATOR  (
   OPERID               NUMBER(9)                       NOT NULL,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   OPERSEQNO            NUMBER(9)                       NOT NULL,
   OPERTYPE             NUMBER(1)                       NOT NULL,
   BRANCHID             NUMBER(6)                       NOT NULL,
   CARDNO               NUMBER(9),
   OPERNAME             VARCHAR(90)                     NOT NULL,
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   OPERPWD              VARCHAR(32),
   STATUS               NUMBER(2)                       NOT NULL,
   MENUSET              VARCHAR2(800),
   FUNCSET              VARCHAR2(600),
   RIGHTFLAG            NUMBER(1),
   SITELIMIT            NUMBER(1),
   LOGINFLAG            NUMBER(1),
   LOGINSITENO          NUMBER(9),
   LASTTRANSDATE        NUMBER(8),
   LOGINTIME            VARCHAR(14),
   LOGOUTTIME           VARCHAR(14),
   FAILNUMBER           NUMBER(9),
   OPENDATE             NUMBER(8),
   CLOSEDATE            NUMBER(8),
   CONSTRAINT PK_T_OPERATOR PRIMARY KEY (OPERID)
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

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERID IS
'����ԱID';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERCODE IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERSEQNO IS
'����Ա��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERTYPE IS
'����Ա����';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.BRANCHID IS
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

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LASTTRANSDATE IS
'���������';

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
/* Index: UNIQ_OPERATOR_OPERCODE                                */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_OPERATOR_OPERCODE ON YKT_CUR.T_OPERATOR (
   OPERCODE ASC
);

/*==============================================================*/
/* Table: T_OPERAUTH                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERAUTH  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   AUTHTYPE             NUMBER(9)                       NOT NULL,
   AUTHORIZER           VARCHAR(8),
   AUTHDATE             NUMBER(8),
   CONSTRAINT PK_T_OPERAUTH PRIMARY KEY (OPERCODE, AUTHTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_OPERAUTH.OPERCODE IS
'����Ա';

COMMENT ON COLUMN YKT_CUR.T_OPERAUTH.AUTHTYPE IS
'Ȩ�޴���';

COMMENT ON COLUMN YKT_CUR.T_OPERAUTH.AUTHORIZER IS
'��Ȩ��';

COMMENT ON COLUMN YKT_CUR.T_OPERAUTH.AUTHDATE IS
'��Ȩ����';

/*==============================================================*/
/* Table: T_OPERDTL                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERDTL  (
   ACCDATE              NUMBER(8)                       NOT NULL,
   REFNO                VARCHAR(14)                     NOT NULL,
   OPERID               NUMBER(9)                       NOT NULL,
   OPERSEQNO            NUMBER(9),
   HOSTDATE             NUMBER(8),
   HOSTTIME             NUMBER(6),
   CARDNO               NUMBER(9)                       NOT NULL,
   AMOUNT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   OTHERAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TRANSCODE            NUMBER(4),
   TRANSDESC            VARCHAR(480),
   TERMID               NUMBER(9),
   SAMNO                VARCHAR(12),
   TERMSEQNO            NUMBER(9),
   BRANCHID             NUMBER(6),
   CHKOPERID            NUMBER(9),
   STATUS               NUMBER(2)                       NOT NULL,
   REQDATA              VARCHAR(1000),
   CONSTRAINT PK_T_OPERDTL PRIMARY KEY (ACCDATE, REFNO)
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

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.OPERID IS
'����ԱID';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.OPERSEQNO IS
'����Ա��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.HOSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.HOSTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.CARDNO IS
'����';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.AMOUNT IS
'���׽��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.OTHERAMT IS
'���ɱ���';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSDESC IS
'������Ϣ';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMID IS
'�ն�ID';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.SAMNO IS
'�ն�SAM��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMSEQNO IS
'�ն���ˮ��';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.BRANCHID IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.CHKOPERID IS
'��˲���Ա';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.STATUS IS
'��ˮ״̬1-δ����2-ʧ��3-�ɹ�4-����';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.REQDATA IS
'��������';

/*==============================================================*/
/* Index: IDX_OPERDTL_OPERID                                    */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_OPERDTL_OPERID ON YKT_CUR.T_OPERDTL (
   OPERID ASC
);

/*==============================================================*/
/* Table: T_OPERSITE                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_OPERSITE  (
   OPERCODE             VARCHAR(8)                      NOT NULL,
   SITENO               NUMBER(9)                       NOT NULL,
   LASTSAVED            VARCHAR(14),
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
/* Table: T_PERIOD                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PERIOD  (
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   STARTDATE            NUMBER(8)                       NOT NULL,
   ENDDATE              NUMBER(8)                       NOT NULL,
   SETTLEFLAG           NUMBER(1)                       NOT NULL,
   CONSTRAINT PK_T_PERIOD PRIMARY KEY (PERIODYEAR, PERIODMONTH)
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

COMMENT ON COLUMN YKT_CUR.T_PERIOD.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_PERIOD.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_PERIOD.STARTDATE IS
'��ʼ����';

COMMENT ON COLUMN YKT_CUR.T_PERIOD.ENDDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PERIOD.SETTLEFLAG IS
'���˱�־';

/*==============================================================*/
/* Table: T_PHOTO                                               */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PHOTO  (
   CUSTID               INTEGER                         NOT NULL,
   PHOTO                BLOB,
   PHOTODATE            NUMBER(8),
   PHOTOTIME            NUMBER(6),
   CONSTRAINT PK_T_PHOTO PRIMARY KEY (CUSTID)
)
TABLESPACE TS_YKT_PHOTO;

COMMENT ON COLUMN YKT_CUR.T_PHOTO.CUSTID IS
'�ͻ���';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTO IS
'��Ƭ';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTODATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTOTIME IS
'����ʱ��';

/*==============================================================*/
/* Table: T_PHYDEVICE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PHYDEVICE  (
   PHYTYPE              NUMBER(9)                       NOT NULL,
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
/* Table: T_PKG                                                 */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PKG  (
   PKGID                NUMBER(9)                       NOT NULL,
   UNITNO               NUMBER(9),
   PKGFILENAME          VARCHAR(240),
   PKGNO                VARCHAR(30),
   CITYCODE             NUMBER(2),
   RECVDATE             NUMBER(8),
   RECVTIME             NUMBER(6),
   FILENUM              NUMBER(9),
   PROCESSDATE          NUMBER(8),
   PROCESSTIME          NUMBER(6),
   STATUS               CHAR(1),
   FEEDBACK             NUMBER(1),
   ERRCODE              NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_PKG PRIMARY KEY (PKGID)
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

COMMENT ON COLUMN YKT_CUR.T_PKG.PKGID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_PKG.UNITNO IS
'���͵�λ���';

COMMENT ON COLUMN YKT_CUR.T_PKG.PKGFILENAME IS
'�����ļ���';

COMMENT ON COLUMN YKT_CUR.T_PKG.PKGNO IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_PKG.CITYCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_PKG.RECVDATE IS
'���ݰ���������';

COMMENT ON COLUMN YKT_CUR.T_PKG.RECVTIME IS
'���ݰ�����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PKG.FILENUM IS
'���ݰ����ļ�����';

COMMENT ON COLUMN YKT_CUR.T_PKG.PROCESSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_PKG.PROCESSTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PKG.STATUS IS
'���ݰ�����״̬';

COMMENT ON COLUMN YKT_CUR.T_PKG.FEEDBACK IS
'FEEDBACK';

COMMENT ON COLUMN YKT_CUR.T_PKG.ERRCODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_PKG.REMARK IS
'��ע';

/*==============================================================*/
/* Index: UNIQ_PKG_PKGFILENAME                                  */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_PKG_PKGFILENAME ON YKT_CUR.T_PKG (
   UNITNO ASC,
   PKGFILENAME ASC
);

/*==============================================================*/
/* Table: T_PKGFILE                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_PKGFILE  (
   FILEID               NUMBER(9)                       NOT NULL,
   FILENAME             VARCHAR(240),
   PKGID                NUMBER(9)                       NOT NULL,
   SEQNO                NUMBER(9)                       NOT NULL,
   MERCHID              NUMBER(9),
   TOTALNUM             NUMBER(9),
   TOTALAMT             NUMBER(9),
   PROCESSDATE          NUMBER(8),
   PROCESSTIME          NUMBER(6),
   STATUS               CHAR(1),
   ERRCODE              NUMBER(9),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_PKGFILE PRIMARY KEY (FILEID)
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

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.FILEID IS
'�ļ�ID';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.FILENAME IS
'�ļ���';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.PKGID IS
'����ID';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.SEQNO IS
'�����������';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.MERCHID IS
'�̻����';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.TOTALNUM IS
'��¼������';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.TOTALAMT IS
'�ܽ��';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.PROCESSDATE IS
'���ݴ�������';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.PROCESSTIME IS
'���ݴ���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.ERRCODE IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_PKGFILE.REMARK IS
'��ע';

/*==============================================================*/
/* Index: UNIQ_PKGFILE_PKGIDSEQNO                               */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_PKGFILE_PKGIDSEQNO ON YKT_CUR.T_PKGFILE (
   PKGID ASC,
   SEQNO ASC
);

/*==============================================================*/
/* Table: T_POS                                                 */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_POS  (
   POSID                INTEGER                         NOT NULL,
   POSNO                VARCHAR(20),
   MERCHID              NUMBER(9),
   AREACODE             VARCHAR(2),
   SAMNO                VARCHAR(12),
   DEVPHYID             VARCHAR(20),
   TERMSN               VARCHAR(20),
   TERMMODEL            NUMBER(9),
   TERMTYPE             VARCHAR(2),
   TERMNAME             VARCHAR(60),
   USAGE                INTEGER,
   STATUS               CHAR(1),
   ENABLEDATE           NUMBER(8),
   REGDATE              NUMBER(8),
   DELDATE              NUMBER(8),
   UPDTIME              VARCHAR(14),
   REMARK               VARCHAR(60),
   CONSTRAINT PK_T_POS PRIMARY KEY (POSID)
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

COMMENT ON COLUMN YKT_CUR.T_POS.POSID IS
'POS��ID';

COMMENT ON COLUMN YKT_CUR.T_POS.POSNO IS
'POS�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_POS.MERCHID IS
'�����̻���';

COMMENT ON COLUMN YKT_CUR.T_POS.AREACODE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POS.SAMNO IS
'SAM���ն˱��';

COMMENT ON COLUMN YKT_CUR.T_POS.DEVPHYID IS
'�豸�������';

COMMENT ON COLUMN YKT_CUR.T_POS.TERMSN IS
'�ն����к�';

COMMENT ON COLUMN YKT_CUR.T_POS.TERMMODEL IS
'POS�ͺ�';

COMMENT ON COLUMN YKT_CUR.T_POS.TERMTYPE IS
'POS����';

COMMENT ON COLUMN YKT_CUR.T_POS.TERMNAME IS
'POS����';

COMMENT ON COLUMN YKT_CUR.T_POS.USAGE IS
'��;';

COMMENT ON COLUMN YKT_CUR.T_POS.STATUS IS
'POS״̬:''A"���� ''U''-����''F��-����''X''-����';

COMMENT ON COLUMN YKT_CUR.T_POS.ENABLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POS.REGDATE IS
'ע������';

COMMENT ON COLUMN YKT_CUR.T_POS.DELDATE IS
'ɾ������';

COMMENT ON COLUMN YKT_CUR.T_POS.UPDTIME IS
'������ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POS.REMARK IS
'��ע';

ALTER TABLE YKT_CUR.T_POS
   ADD CONSTRAINT CKT_T_POS CHECK (LENGTH(POSNO)=10);

/*==============================================================*/
/* Index: UNIQ_POS_POSNO                                        */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_POS_POSNO ON YKT_CUR.T_POS (
   POSNO ASC
);

/*==============================================================*/
/* Table: T_POSDTL                                              */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_POSDTL  (
   FILEID               NUMBER(9)                       NOT NULL,
   ROWNO                NUMBER(9)                       NOT NULL,
   HOSTDATE             NUMBER(8),
   HOSTTIME             NUMBER(6),
   CITYCODE             NUMBER(2),
   MERCHID              NUMBER(9),
   POSNO                VARCHAR(20),
   POSSEQNO             NUMBER(9),
   SAMNO                VARCHAR(12),
   SAMSEQNO             NUMBER(9),
   CARDASNO             VARCHAR(20),
   CARDNO               NUMBER(9),
   CARDTYPE             NUMBER(2)                      DEFAULT 0 NOT NULL,
   TRANSCODE            NUMBER(4),
   TERMDATE             NUMBER(8),
   TERMTIME             NUMBER(6),
   LOCKFLAG             NUMBER(1),
   LINENO               NUMBER(9),
   INTEGRAL             NUMBER(9),
   TRANSTYPE            NUMBER(9),
   CARDCNT              NUMBER(6)                       NOT NULL,
   AMOUNT               NUMBER(9)                      DEFAULT 0 NOT NULL,
   BEFCARDBAL           NUMBER(9)                      DEFAULT 0 NOT NULL,
   AFTCARDBAL           NUMBER(9)                      DEFAULT 0 NOT NULL,
   LASTTERMSNO          VARCHAR(12),
   LASTTERMDATE         NUMBER(8),
   LASTTRANSTIME        NUMBER(6),
   LASTTRANSTYPE        NUMBER(9),
   LASTAMOUNT           NUMBER(9)                      DEFAULT 0 NOT NULL,
   TAC                  VARCHAR(8),
   ACCDATE              NUMBER(8)                      DEFAULT 0 NOT NULL,
   REFNO                VARCHAR(14),
   STATUS               CHAR(1)                         NOT NULL,
   REMARK               VARCHAR(60),
   ERRCODE              NUMBER(9),
   CONSTRAINT PK_T_POSDTL PRIMARY KEY (FILEID, ROWNO)
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

COMMENT ON COLUMN YKT_CUR.T_POSDTL.FILEID IS
'���ݰ��ļ�ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ROWNO IS
'�ļ��ڼ�¼���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.HOSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.HOSTTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CITYCODE IS
'���д���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.MERCHID IS
'�̻����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.POSNO IS
'POS�ն˺�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.POSSEQNO IS
'POS��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SAMNO IS
'�ն�SAM���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SAMSEQNO IS
'SAM��ˮ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDASNO IS
'��Ӧ�����к�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDNO IS
'���ڷ��񿨺�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDTYPE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMTIME IS
'����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LOCKFLAG IS
'0-����1����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LINENO IS
'��·��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.INTEGRAL IS
'���λ���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSTYPE IS
'��������:���ѡ��ۿ�����ֵ';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDCNT IS
'������ǰ����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.AMOUNT IS
'������/����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.BEFCARDBAL IS
'����ǰ�����/����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.AFTCARDBAL IS
'���׺����/����';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LASTTERMSNO IS
'�ϴ��ն����к�';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LASTTERMDATE IS
'�ϴν�������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LASTTRANSTIME IS
'�ϴν���ʱ��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LASTTRANSTYPE IS
'��������:���ѡ��ۿ�����ֵ';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.LASTAMOUNT IS
'�ϴν��׽��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TAC IS
'TAC��';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ACCDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.REFNO IS
'���ײο���';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.STATUS IS
'����״̬';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.REMARK IS
'��ע';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ERRCODE IS
'������';

ALTER TABLE YKT_CUR.T_POSDTL
   ADD CONSTRAINT CKT_T_POSDTL CHECK (STATUS>='A');

/*==============================================================*/
/* Index: IDX_POSDTL_STATUS                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_POSDTL_STATUS ON YKT_CUR.T_POSDTL (
   STATUS ASC
);

/*==============================================================*/
/* Table: T_RPTTERMMEAL                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTTERMMEAL  (
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TERMID               NUMBER(9)                       NOT NULL,
   TRANSTYPE            NUMBER(9)                       NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSDATE            NUMBER(8)                       NOT NULL,
   MEALTYPE             NUMBER(9)                       NOT NULL,
   TRANSCNT             NUMBER(9)                       NOT NULL,
   DRAMT                NUMBER(9)                       NOT NULL,
   CRAMT                NUMBER(9)                       NOT NULL,
   AMOUNT               NUMBER(9),
   CONSTRAINT PK_T_RPTTERMMEAL PRIMARY KEY (SETTLEDATE, ACCNO, TERMID, TRANSTYPE, SUMMARY, TRANSDATE, MEALTYPE)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.SETTLEDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.ACCNO IS
'�̻��˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.TERMID IS
'�豸���';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.MEALTYPE IS
'�ʹ�����';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMMEAL.AMOUNT IS
'�����';

/*==============================================================*/
/* Table: T_SEQNOCTL                                            */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SEQNOCTL  (
   TERMID               NUMBER(9)                       NOT NULL,
   TERMSEQNO            NUMBER(9),
   ACCDATE              NUMBER(8),
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
/* Table: T_SETTLECTL                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SETTLECTL  (
   BOOKSETNO            NUMBER(9)                       NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   ACCDATE              NUMBER(8)                       NOT NULL,
   BATCHDATE            NUMBER(8),
   STATDATE             NUMBER(8),
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   AUTOSTATTIME         NUMBER(2),
   AUTOSETTLTIME        NUMBER(2),
   SETTLEFLAG           NUMBER(1)                       NOT NULL,
   VOUCHERGENFLAG       NUMBER(1)                       NOT NULL,
   VOUCHERPOSTTYPE      NUMBER(1)                       NOT NULL,
   STATUS               NUMBER(1)                       NOT NULL,
   UPDTIME              VARCHAR(14),
   CONSTRAINT PK_T_SETTLECTL PRIMARY KEY (BOOKSETNO)
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

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.BOOKSETNO IS
'���׺�';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.PERIODYEAR IS
'��ǰ������';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.PERIODMONTH IS
'��ǰ����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.ACCDATE IS
'��ǰ��������';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.BATCHDATE IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.STATDATE IS
'��ǰͳ������';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.SETTLEDATE IS
'��ǰ��������';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.AUTOSTATTIME IS
'�Զ�ͳ��ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.AUTOSETTLTIME IS
'�Զ�����ʱ��';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.SETTLEFLAG IS
'�ս������ɱ�־';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.VOUCHERGENFLAG IS
'���ɻ���ƾ֤';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.VOUCHERPOSTTYPE IS
'��������1-�Զ�0�ֶ�';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.STATUS IS
'״̬';

COMMENT ON COLUMN YKT_CUR.T_SETTLECTL.UPDTIME IS
'�ϴν���ʱ��';

/*==============================================================*/
/* Table: T_SITE                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SITE  (
   SITENO               NUMBER(9)                       NOT NULL,
   SITENAME             VARCHAR(60),
   IP                   VARCHAR(15),
   MACHINECODE          VARCHAR(60),
   LASTSAVED            VARCHAR(14),
   REMARK               VARCHAR(60),
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
/* Table: T_SUBJECT                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBJECT  (
   SUBJID               NUMBER(9)                       NOT NULL,
   SUBJNO               NUMBER(10)                      NOT NULL,
   SUBJNAME             VARCHAR(60)                     NOT NULL,
   SUBJFULLNAME         VARCHAR(240),
   SUBJLEVEL            NUMBER(1),
   ENDFLAG              NUMBER(1),
   SUBJCLASS            INTEGER,
   PROPERTY             NUMBER(9),
   BOOKTYPE             NUMBER(1),
   HELPCODE             VARCHAR(10),
   PERSONFLAG           NUMBER(1),
   COMPANYFLAG          NUMBER(1),
   DEPTLAG              NUMBER(1),
   ITEMFLAG             NUMBER(1),
   SYSFLAG              NUMBER(1),
   CASHFLAG             NUMBER(1),
   BANKFLAG             NUMBER(1),
   CLOSEFLAG            NUMBER(1),
   DRACCUMAMT           NUMBER(15),
   CRACCUMAMT           NUMBER(15),
   BALFLAG              NUMBER(1),
   BEGINBAL             NUMBER(15),
   YEARDRAMT            NUMBER(15),
   YEARCRAMT            NUMBER(15),
   MONTHDRAMT           NUMBER(15),
   MONTHCRAMT           NUMBER(15),
   DRBAL                NUMBER(15),
   CRBAL                NUMBER(15),
   CONSTRAINT PK_T_SUBJECT PRIMARY KEY (SUBJID)
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

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJID IS
'��ĿID';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJNAME IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJFULLNAME IS
'��Ŀȫ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJLEVEL IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.ENDFLAG IS
'ĩ����־';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJCLASS IS
'��Ŀ���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.PROPERTY IS
'��Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BOOKTYPE IS
'��ҳ��ʽ';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.HELPCODE IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.PERSONFLAG IS
'�Ƿ������������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.COMPANYFLAG IS
'�Ƿ�λ��������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.DEPTLAG IS
'�Ƿ��ź���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.ITEMFLAG IS
'�Ƿ���Ŀ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SYSFLAG IS
'�Ƿ�ϵͳ��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.CASHFLAG IS
'�Ƿ��ֽ��Ŀ';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BANKFLAG IS
'�Ƿ����п�Ŀ';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.CLOSEFLAG IS
'��Ŀ����־';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.DRACCUMAMT IS
'�跽�ۼƷ�����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.CRACCUMAMT IS
'�����ۼƷ�����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BEGINBAL IS
'�ڳ����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.YEARDRAMT IS
'����跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.YEARCRAMT IS
'�������������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.MONTHDRAMT IS
'���½跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.MONTHCRAMT IS
'���´���������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.DRBAL IS
'��Ŀ�跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.CRBAL IS
'��Ŀ�������';

/*==============================================================*/
/* Index: UNIQ_SUBJECT_SUBJNO                                   */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_SUBJECT_SUBJNO ON YKT_CUR.T_SUBJECT (
   SUBJNO ASC
);

/*==============================================================*/
/* Table: T_SUBJECTBAL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBJECTBAL  (
   SUBJNO               NUMBER(10)                      NOT NULL,
   BEGINDRBAL           NUMBER(15),
   BEGINCRBAL           NUMBER(15),
   MONTHDRAMT           NUMBER(15),
   MONTHCRAMT           NUMBER(15),
   YEARDRAMT            NUMBER(15),
   YEARCRAMT            NUMBER(15),
   DRBAL                NUMBER(15),
   CRBAL                NUMBER(15),
   CONSTRAINT PK_T_SUBJECTBAL PRIMARY KEY (SUBJNO)
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

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.BEGINDRBAL IS
'�ڳ��跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.BEGINCRBAL IS
'�ڳ��������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.MONTHDRAMT IS
'���½跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.MONTHCRAMT IS
'���´���������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.YEARDRAMT IS
'����跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.YEARCRAMT IS
'�������������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.DRBAL IS
'��Ŀ�跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTBAL.CRBAL IS
'��Ŀ�������';

/*==============================================================*/
/* Table: T_SUBJECTDAY                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBJECTDAY  (
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   SUBJNO               NUMBER(10)                      NOT NULL,
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   PERIODDAY            NUMBER(2)                       NOT NULL,
   YEARDRAMT            NUMBER(15)                      NOT NULL,
   YEARCRAMT            NUMBER(15)                      NOT NULL,
   MONTHDRAMT           NUMBER(15)                      NOT NULL,
   MONTHCRAMT           NUMBER(15)                      NOT NULL,
   LASTDAYDRBAL         NUMBER(15)                      NOT NULL,
   LASTDAYCRBAL         NUMBER(15)                      NOT NULL,
   DRAMT                NUMBER(15)                      NOT NULL,
   CRAMT                NUMBER(15)                      NOT NULL,
   DRBAL                NUMBER(15)                      NOT NULL,
   CRBAL                NUMBER(15)                      NOT NULL,
   TOTALACCCNT          NUMBER(9)                       NOT NULL,
   NEWACCCNT            NUMBER(9)                       NOT NULL,
   CLOSEACCCNT          NUMBER(9)                       NOT NULL,
   CONSTRAINT PK_T_SUBJECTDAY PRIMARY KEY (SETTLEDATE, SUBJNO)
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

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.SETTLEDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.PERIODDAY IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.YEARDRAMT IS
'�����ۼƽ跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.YEARCRAMT IS
'�����ۼƴ���������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.MONTHDRAMT IS
'�����ۼƽ跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.MONTHCRAMT IS
'�����ۼƴ���������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.LASTDAYDRBAL IS
'���ս跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.LASTDAYCRBAL IS
'���մ������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.DRBAL IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.CRBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.TOTALACCCNT IS
'�ܻ���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.NEWACCCNT IS
'�¿�����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTDAY.CLOSEACCCNT IS
'������';

/*==============================================================*/
/* Table: T_SUBJECTMONTH                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBJECTMONTH  (
   PERIODYEAR           NUMBER(4)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   SUBJNO               NUMBER(10)                      NOT NULL,
   LASTMONTHDRBAL       NUMBER(15)                      NOT NULL,
   LASTMONTHCRBAL       NUMBER(15)                      NOT NULL,
   YEARDRAMT            NUMBER(15)                      NOT NULL,
   YEARCRAMT            NUMBER(15)                      NOT NULL,
   DRAMT                NUMBER(15)                      NOT NULL,
   CRAMT                NUMBER(15)                      NOT NULL,
   DRBAL                NUMBER(15)                      NOT NULL,
   CRBAL                NUMBER(15)                      NOT NULL,
   TOTALACCCNT          NUMBER(9),
   NEWACCCNT            NUMBER(9),
   CLOSEACCCNT          NUMBER(9),
   SETTLEDATE           NUMBER(8)                       NOT NULL,
   CONSTRAINT PK_T_SUBJECTMONTH PRIMARY KEY (PERIODYEAR, PERIODMONTH, SUBJNO)
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

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.PERIODYEAR IS
'�����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.PERIODMONTH IS
'�»���ڼ�';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.LASTMONTHDRBAL IS
'����ĩ�跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.LASTMONTHCRBAL IS
'����ĩ�������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.YEARDRAMT IS
'����跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.YEARCRAMT IS
'�������������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.CRAMT IS
'����������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.DRBAL IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.CRBAL IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.TOTALACCCNT IS
'�ܻ���';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.NEWACCCNT IS
'�¿�����';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.CLOSEACCCNT IS
'������';

COMMENT ON COLUMN YKT_CUR.T_SUBJECTMONTH.SETTLEDATE IS
'��������';

/*==============================================================*/
/* Table: T_SUBSYSPARA                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_SUBSYSPARA  (
   SYSID                NUMBER(9)                       NOT NULL,
   WORKMODE             NUMBER(1),
   BEATINTERVAL         NUMBER(9),
   BEATCNTLIMIT         NUMBER(9),
   REQBEATFUNCNO        NUMBER(9),
   REQDEVFUNCNO         NUMBER(9),
   REQTASKFUNCNO        NUMBER(9),
   RESPFUNCNO           NUMBER(9),
   EXECTIMEOUT          NUMBER(9),
   COLINTERVAL          NUMBER(9),
   QRYINTERVAL          NUMBER(9),
   TASKMAXLIMIT         NUMBER(9),
   BCCDRTPNO            NUMBER(9),
   BCCDRTPIP            VARCHAR(15),
   BCCDRTPPORT          NUMBER(9),
   BCCMAINFUNCNO        NUMBER(9),
   BCCINTERVAL          NUMBER(9),
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
   SYSID                NUMBER(9)                       NOT NULL,
   SYSNAME              VARCHAR(60),
   SYSTYPE              NUMBER(9),
   AREACODE             VARCHAR(3),
   SERVERID             NUMBER(9),
   MACADDR              VARCHAR(17),
   IP                   VARCHAR(15),
   PORT                 NUMBER(9),
   CARDVERNO            VARCHAR(14)                    DEFAULT '000000000000',
   INITKEY              VARCHAR(32),
   DYNAKEY              VARCHAR(32),
   SYNCTIME             VARCHAR(14),
   RUNSTATUS            NUMBER(9),
   STATUS               NUMBER(1),
   OPENDATE             NUMBER(8),
   CLOSEDATE            NUMBER(8),
   REMARK               VARCHAR(60),
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
   MAXVAL               NUMBER(9),
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
   PARAID               NUMBER(9)                       NOT NULL,
   PARAVAL              VARCHAR(60),
   PARANAME             VARCHAR(60),
   PARAUNIT             VARCHAR(30),
   DISPLAYFLAG          NUMBER(1),
   REMARK               VARCHAR(60),
   LASTSAVED            VARCHAR(14),
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
   TRANSCODE            NUMBER(4)                       NOT NULL,
   TRANSNAME            VARCHAR(60),
   LOGFLAG              NUMBER(9),
   LIMITFLAG            NUMBER(9),
   FEEFLAG              NUMBER(9),
   TRANSFLAG            NUMBER(9),
   DISABLEFLAG          NUMBER(1),
   CASHFLAG             NUMBER(1),
   BANKFLAG             NUMBER(1),
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

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.CASHFLAG IS
'�Ƿ��ֽ�';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.BANKFLAG IS
'�Ƿ�����';

/*==============================================================*/
/* Table: T_TRANSTYPE                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_TRANSTYPE  (
   TRANSTYPE            INTEGER                         NOT NULL,
   TRANSNAME            VARCHAR(60),
   DISPLAYFLAG          NUMBER(1),
   USEFLAG              NUMBER(1),
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
/* Table: T_UNIT                                                */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_UNIT  (
   UNITNO               NUMBER(9)                       NOT NULL,
   UNITNAME             VARCHAR(60),
   ENABLED              NUMBER(1)                      DEFAULT 0,
   BEGINDATE            NUMBER(8),
   LASTDATE             NUMBER(8),
   CONSTRAINT PK_T_UNIT PRIMARY KEY (UNITNO)
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

COMMENT ON COLUMN YKT_CUR.T_UNIT.UNITNO IS
'���뵥λ��';

COMMENT ON COLUMN YKT_CUR.T_UNIT.UNITNAME IS
'���뵥λ����';

COMMENT ON COLUMN YKT_CUR.T_UNIT.ENABLED IS
'���ñ�־:1����0ͣ��';

COMMENT ON COLUMN YKT_CUR.T_UNIT.BEGINDATE IS
'��ʼ����';

COMMENT ON COLUMN YKT_CUR.T_UNIT.LASTDATE IS
'�ϴ�����';

/*==============================================================*/
/* Table: T_UNITCFG                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_UNITCFG  (
   PARANAME             VARCHAR(60)                     NOT NULL,
   PARAVAL              VARCHAR(240),
   PARADESC             VARCHAR(240),
   CONSTRAINT PK_T_UNITCFG PRIMARY KEY (PARANAME)
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

COMMENT ON COLUMN YKT_CUR.T_UNITCFG.PARANAME IS
'������';

COMMENT ON COLUMN YKT_CUR.T_UNITCFG.PARAVAL IS
'����ֵ';

COMMENT ON COLUMN YKT_CUR.T_UNITCFG.PARADESC IS
'����˵��';

/*==============================================================*/
/* Table: T_VOUCHER                                             */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_VOUCHER  (
   VOUCHERID            NUMBER(9)                       NOT NULL,
   PERIODYEAR           NUMBER(4),
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   VOUCHERTYPE          NUMBER(2)                       NOT NULL,
   VOUCHERNO            NUMBER(6)                       NOT NULL,
   VOUCHERDATE          NUMBER(8),
   TRANSDATE            NUMBER(8),
   TOTALCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   TOTALAMT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   ATTACHMENTS          NUMBER(2),
   SUMMARY              VARCHAR(60),
   ENTRYCNT             NUMBER(2),
   DATASOURCE           NUMBER(1),
   SIGNFLAG             NUMBER(1),
   CHECKFLAG            NUMBER(1)                       NOT NULL,
   POSTFLAG             NUMBER(1),
   INVALIDFLAG          NUMBER(1),
   EDITFLAG             NUMBER(1),
   PREPARER             VARCHAR(8),
   CASHIER              VARCHAR(8),
   CHECKER              VARCHAR(8),
   POSTER               VARCHAR(8),
   POSTDATE             NUMBER(8),
   BRANCHID             NUMBER(6),
   CONSTRAINT PK_T_VOUCHER PRIMARY KEY (VOUCHERID)
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

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.VOUCHERID IS
'ƾ֤ID';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.PERIODYEAR IS
'������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.PERIODMONTH IS
'����ڼ�';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.VOUCHERTYPE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.VOUCHERNO IS
'ƾ֤���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.VOUCHERDATE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.TRANSDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.TOTALCNT IS
'�����ܱ���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.TOTALAMT IS
'�����ܽ��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.ATTACHMENTS IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.ENTRYCNT IS
'��¼��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.DATASOURCE IS
'ƾ֤��Դ';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.SIGNFLAG IS
'�Ƿ�ǩ��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.CHECKFLAG IS
'�Ƿ񸴺�';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.POSTFLAG IS
'�Ƿ�����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.INVALIDFLAG IS
'0-��Ч1����2�д�ƾ֤';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.EDITFLAG IS
'�ܷ��޸�';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.PREPARER IS
'�Ƶ���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.CASHIER IS
'����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.CHECKER IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.POSTER IS
'������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.POSTDATE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHER.BRANCHID IS
'�Ƶ��������';

/*==============================================================*/
/* Index: UNIQ_VOUCHER                                          */
/*==============================================================*/
CREATE UNIQUE INDEX YKT_CUR.UNIQ_VOUCHER ON YKT_CUR.T_VOUCHER (
   PERIODYEAR ASC,
   PERIODMONTH ASC,
   VOUCHERTYPE ASC,
   VOUCHERNO ASC
);

/*==============================================================*/
/* Index: IDX_VOUCHER_POSTED                                    */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_VOUCHER_POSTED ON YKT_CUR.T_VOUCHER (
   POSTFLAG ASC
);

/*==============================================================*/
/* Index: IDX_VOUCHER_VOUCHERDATE                               */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_VOUCHER_VOUCHERDATE ON YKT_CUR.T_VOUCHER (
   VOUCHERDATE ASC
);

/*==============================================================*/
/* Index: IDX_VOUCHER_INVALIDFLAG                               */
/*==============================================================*/
CREATE INDEX YKT_CUR.IDX_VOUCHER_INVALIDFLAG ON YKT_CUR.T_VOUCHER (
   INVALIDFLAG ASC
);

/*==============================================================*/
/* Table: T_VOUCHERCTL                                          */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_VOUCHERCTL  (
   VOUCHERTYPE          NUMBER(2)                       NOT NULL,
   VOUCHERNO            NUMBER(6)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   CONSTRAINT PK_T_VOUCHERCTL PRIMARY KEY (VOUCHERTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_VOUCHERCTL.VOUCHERTYPE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERCTL.VOUCHERNO IS
'ƾ֤��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERCTL.PERIODMONTH IS
'����ڼ�';

/*==============================================================*/
/* Table: T_VOUCHERENTRY                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_VOUCHERENTRY  (
   VOUCHERID            NUMBER(9)                       NOT NULL,
   ENTRYID              NUMBER(2)                       NOT NULL,
   SETTLETYPE           NUMBER(2),
   SETTLENO             VARCHAR(20),
   SUMMARY              VARCHAR(60)                     NOT NULL,
   SUBJNO               NUMBER(10)                      NOT NULL,
   OPPSUBJNO            NUMBER(10),
   TRANSCNT             NUMBER(9)                      DEFAULT 0 NOT NULL,
   DRAMT                NUMBER(9)                       NOT NULL,
   CRAMT                NUMBER(9)                       NOT NULL,
   BALFLAG              NUMBER(1)                       NOT NULL,
   BALANCE              NUMBER(9)                      DEFAULT 0 NOT NULL,
   CONSTRAINT PK_T_VOUCHERENTRY PRIMARY KEY (VOUCHERID, ENTRYID)
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

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.VOUCHERID IS
'ƾ֤ID';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.ENTRYID IS
'��¼���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.SETTLETYPE IS
'���㷽ʽ';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.SETTLENO IS
'�����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.OPPSUBJNO IS
'�Է���Ŀ';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.TRANSCNT IS
'����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.DRAMT IS
'�跽���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.CRAMT IS
'�������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.BALFLAG IS
'����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERENTRY.BALANCE IS
'���';

/*==============================================================*/
/* Index: UNIQ_VOUCHERENTRY                                     */
/*==============================================================*/
CREATE INDEX YKT_CUR.UNIQ_VOUCHERENTRY ON YKT_CUR.T_VOUCHERENTRY (
   SUBJNO ASC,
   ENTRYID ASC
);

/*==============================================================*/
/* Table: T_VOUCHERNOCTL                                        */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_VOUCHERNOCTL  (
   VOUCHERTYPE          NUMBER(2)                       NOT NULL,
   VOUCHERNO            NUMBER(6)                       NOT NULL,
   PERIODMONTH          NUMBER(2)                       NOT NULL,
   CONSTRAINT PK_T_VOUCHERNOCTL PRIMARY KEY (VOUCHERTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_VOUCHERNOCTL.VOUCHERTYPE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERNOCTL.VOUCHERNO IS
'ƾ֤��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERNOCTL.PERIODMONTH IS
'����ڼ�';

/*==============================================================*/
/* Table: T_VOUCHERTYPE                                         */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_VOUCHERTYPE  (
   VOUCHERTYPE          NUMBER(2)                       NOT NULL,
   VOUCHERTYPENAME      VARCHAR(6)                      NOT NULL,
   VOUCHERTYPEFULLNAME  VARCHAR(30),
   VOUCHERCLASS         NUMBER(1)                       NOT NULL,
   ENABLEFLAG           NUMBER(1)                       NOT NULL,
   CONSTRAINT PK_T_VOUCHERTYPE PRIMARY KEY (VOUCHERTYPE)
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

COMMENT ON COLUMN YKT_CUR.T_VOUCHERTYPE.VOUCHERTYPE IS
'ƾ֤����';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERTYPE.VOUCHERTYPENAME IS
'ƾ֤���ͼ��';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERTYPE.VOUCHERTYPEFULLNAME IS
'ƾ֤��������';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERTYPE.VOUCHERCLASS IS
'ƾ֤���';

COMMENT ON COLUMN YKT_CUR.T_VOUCHERTYPE.ENABLEFLAG IS
'�Ƿ�����';

/*==============================================================*/
/* Table: T_MERCHPARA                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHPARA  (

   	MERCHID             NUMBER(9)				DEFAULT 0 NOT NULL,
	CZAMTMAX            NUMBER(9)	            DEFAULT 0 NOT NULL,
	CZRATE				NUMBER(2)				DEFAULT 0 NOT NULL,
	STATUS              NUMBER(1)				DEFAULT 0 NOT NULL,
	OPENTIME            NUMBER(6)				DEFAULT 0 NOT NULL,
	CLOSETIME           NUMBER(6)				DEFAULT 0 NOT NULL,
	PAYDATE				NUMBER(2)				DEFAULT 0 NOT NULL,
	BILLDATE			NUMBER(2)				DEFAULT 0 NOT NULL,
   CONSTRAINT T_MERCHPARA PRIMARY KEY (MERCHID)
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

COMMENT ON TABLE YKT_CUR.T_MERCHPARA IS
'��ֵ�̻�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.MERCHID IS
'��ֵ�̻����';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.CZAMTMAX IS
'�̻���ֵ�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.CZRATE IS
'�̻��ĳ�ֵ��ɱ��� 0-100';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.STATUS IS
'��ֵ�̻�״̬ 1��������ֵ 2����ֹ��ֵ';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.OPENTIME IS
'�̻���ֵ�ķ���ʼʱ��';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.CLOSETIME IS
'�̻���ֵ�ķ������ʱ��';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.PAYDATE IS
'�̻�ÿ�����ɿ������';

COMMENT ON COLUMN YKT_CUR.T_MERCHPARA.BILLDATE IS
'�̻��˵���';

/*==============================================================*/
/* Table: T_MERCHWORK                                           */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_MERCHWORK  (

	MERCHID             NUMBER(9)				DEFAULT 0 NOT NULL,
	CZAMT               NUMBER(9)             	DEFAULT 0 NOT NULL,
	CZCNT	            NUMBER(9)               DEFAULT 0 NOT NULL,
	CZTOTALAMT          NUMBER(9)	            DEFAULT 0 NOT NULL,
   CONSTRAINT T_MERCHWORK PRIMARY KEY (MERCHID)
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

COMMENT ON TABLE YKT_CUR.T_MERCHWORK IS
'��ֵ�̻�������';

COMMENT ON COLUMN YKT_CUR.T_MERCHWORK.MERCHID IS
'��ֵ�̻����';

COMMENT ON COLUMN YKT_CUR.T_MERCHWORK.CZAMT IS
'�̻���ֵ�˻����';

COMMENT ON COLUMN YKT_CUR.T_MERCHWORK.CZCNT IS
'�̻���ֵ����';

COMMENT ON COLUMN YKT_CUR.T_MERCHWORK.CZTOTALAMT IS
'�̻��ѳ�ֵ�ܽ��';
