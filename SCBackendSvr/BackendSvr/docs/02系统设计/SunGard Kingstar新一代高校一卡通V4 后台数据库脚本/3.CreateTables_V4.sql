/*==============================================================*/
/* Table: T_ACCDTL                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ACCDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
   SUBSEQNO             INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   PAYTYPE              INTEGER,
   VOUCHERNO            VARCHAR(20),
   TRANSCODE            INTEGER,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   ACCNO                VARCHAR(10)                    NOT NULL,
   ACCNAME              VARCHAR(60),
   DCFLAG               NUMBER(1),
   AMOUNT               NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   OPPSUBJNO            VARCHAR(20),
   OPPACCNO             VARCHAR(10),
   OPPACCNAME           VARCHAR(60),
   OPERCODE             VARCHAR(8),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_ACCDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO, SUBSEQNO, ACCNO)
);

COMMENT ON TABLE SG_CUR.T_ACCDTL IS 
'�ʻ�������ϸ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TERMID IS 
'�ն˱��(վ��š��豸ID)';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.SUBSEQNO IS 
'����ˮ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TRANSDATE IS 
'��������,ȡϵͳ����';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TRANSTIME IS 
'����ʱ��,ȡϵͳʱ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.PAYTYPE IS 
'ƾ֤����';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.VOUCHERNO IS 
'ƾ֤��(֧Ʊ�����ѱ�����)';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.TRANSTYPE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.ACCNAME IS 
'�ʻ���';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.DCFLAG IS 
'���';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.BALANCE IS 
'�ʻ����';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.OPPSUBJNO IS 
'�Է���Ŀ';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.OPPACCNO IS 
'�Է��˺�';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.OPPACCNAME IS 
'�Է��ʻ���';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_ACCDTL.REMARK IS 
'��ע';

/*==============================================================*/
/* Index: IDX_ACCDTLACCNO                                       */
/*==============================================================*/
CREATE INDEX IDX_ACCDTLACCNO ON SG_CUR.T_ACCDTL (
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
TABLESPACE TS_SG_CUR;

/*==============================================================*/
/* Table: T_AREA                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_AREA 
(
   AREACODE             VARCHAR(3)                     NOT NULL,
   AREANAME             VARCHAR(60),
   FAREACODE            VARCHAR(3),
   OLDAREACODE          VARCHAR(3),
   AREALEVEL            INTEGER,
   ADDR                 VARCHAR(240),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_AREA PRIMARY KEY (AREACODE),
   CONSTRAINT FK_AREA_AREA FOREIGN KEY (FAREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_AREA IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_AREA.AREACODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_AREA.AREANAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_AREA.FAREACODE IS 
'�ϼ��������';

COMMENT ON COLUMN SG_CUR.T_AREA.OLDAREACODE IS 
'ԭ�������';

COMMENT ON COLUMN SG_CUR.T_AREA.AREALEVEL IS 
'���򼶱�';

COMMENT ON COLUMN SG_CUR.T_AREA.ADDR IS 
'��ַ';

COMMENT ON COLUMN SG_CUR.T_AREA.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_FEETYPE                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_FEETYPE 
(
   FEETYPE              INTEGER                        NOT NULL,
   FEENAME              VARCHAR(60),
   BOARDFEEFLAG         CHAR(1),
   USEFLAG              CHAR(1),
   REMARK               VARCHAR(240),
   BOARDFEERATE         NUMBER(8,2)                    DEFAULT '0',
   CONSTRAINT PK_T_FEETYPE PRIMARY KEY (FEETYPE)
);

COMMENT ON TABLE SG_CUR.T_FEETYPE IS 
'�շ�����';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.FEENAME IS 
'�շ�����';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.BOARDFEEFLAG IS 
'�Ƿ��մ���:1-��0-����';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.USEFLAG IS 
'ʹ�ñ�־';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_FEETYPE.BOARDFEERATE IS 
'Ԥ�մ��ѷ��ʣ������10%������д0.1';

/*==============================================================*/
/* Table: T_CUSTTYPE                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CUSTTYPE 
(
   CUSTTYPE             INTEGER                        NOT NULL,
   CUSTTYPENAME         VARCHAR(60),
   FEETYPE              INTEGER,
   AREACODE             VARCHAR(3),
   OLDCUSTTYPE          VARCHAR(10),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_CUSTTYPE PRIMARY KEY (CUSTTYPE),
   CONSTRAINT FK_CUSTTYPE_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE)
);

COMMENT ON TABLE SG_CUR.T_CUSTTYPE IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.CUSTTYPE IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.CUSTTYPENAME IS 
'�ͻ���������';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.FEETYPE IS 
'Ĭ���շ����';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.AREACODE IS 
'ѧУ����';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.OLDCUSTTYPE IS 
'ԭ�ͻ����';

COMMENT ON COLUMN SG_CUR.T_CUSTTYPE.USEFLAG IS 
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_CUSTOMER                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CUSTOMER 
(
   CUSTID               INTEGER                        NOT NULL,
   STUEMPNO             VARCHAR(20),
   CUSTTYPE             INTEGER,
   FEETYPE              INTEGER,
   STATUS               CHAR(1),
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
   CONSTRAINT PK_T_CUSTOMER PRIMARY KEY (CUSTID),
   CONSTRAINT FK_CUSTOMER_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE),
   CONSTRAINT FK_CUSTOMER_CUSTTYPE FOREIGN KEY (CUSTTYPE)
      REFERENCES SG_CUR.T_CUSTTYPE (CUSTTYPE),
   CONSTRAINT FK_CUSTOMER_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE)
);

COMMENT ON TABLE SG_CUR.T_CUSTOMER IS 
'�ͻ���Ϣ��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CUSTTYPE IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.STATUS IS 
'״̬1-����2-ע��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CUSTNAME IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.DEPTFULLNAME IS 
'����ȫ��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.SPECIALTYCODE IS 
'רҵ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CLASSCODE IS 
'�༶����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CLASSNAME IS 
'�༶����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.IDTYPE IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.IDNO IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.SEX IS 
'�Ա�';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.COUNTRY IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.NATION IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.EMAIL IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.TEL IS 
'�绰';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.MOBILE IS 
'�ֻ�';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.ADDR IS 
'��ַ';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.ZIPCODE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CUSTATTR IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.INDATE IS 
'��У����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.OUTDATE IS 
'Ԥ����У����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.OPENDATE IS 
'ע������,ָ���ǿͻ���Ϣ��ӽ���������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.OPENFLAG IS 
'��ʽ����ͨ��־';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.HOLDCARDCNT IS 
'ӵ�п�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.USEFLAG IS 
'ʹ�ñ�־';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.EACCFLAG IS 
'����Ǯ����ͨ��־';

COMMENT ON COLUMN SG_CUR.T_CUSTOMER.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CARDPHYTYPE                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDPHYTYPE 
(
   CARDPHYTYPE          INTEGER                        NOT NULL,
   CARDPHYTYPENAME      VARCHAR(60),
   USEFLAG              CHAR(1),
   CARDPHYTYPECODE      INTEGER,
   CONSTRAINT PK_T_CARDPHYTYPE PRIMARY KEY (CARDPHYTYPE)
);

COMMENT ON TABLE SG_CUR.T_CARDPHYTYPE IS 
'���������ͱ�';

COMMENT ON COLUMN SG_CUR.T_CARDPHYTYPE.CARDPHYTYPE IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_CARDPHYTYPE.CARDPHYTYPENAME IS 
'���������';

COMMENT ON COLUMN SG_CUR.T_CARDPHYTYPE.USEFLAG IS 
'�Ƿ�����';

COMMENT ON COLUMN SG_CUR.T_CARDPHYTYPE.CARDPHYTYPECODE IS 
'���������ͱ���';

/*==============================================================*/
/* Table: T_CARDTYPE                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDTYPE 
(
   CARDTYPE             INTEGER                        NOT NULL,
   CARDTYPENAME         VARCHAR(60),
   CARDPHYTYPE          INTEGER,
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
   CONSTRAINT PK_T_CARDTYPE PRIMARY KEY (CARDTYPE),
   CONSTRAINT FK_CARDTYPE_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE),
   CONSTRAINT FK_CARDTYPE_CARDPHYTYPE FOREIGN KEY (CARDPHYTYPE)
      REFERENCES SG_CUR.T_CARDPHYTYPE (CARDPHYTYPE)
);

COMMENT ON TABLE SG_CUR.T_CARDTYPE IS 
'�����ͱ�';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.CARDTYPENAME IS 
'���������';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.CARDPHYTYPE IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.ANONYMFLAG IS 
'1-����0-����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.FEETYPE IS 
'Ĭ���շ����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.CARDCOSTFEE IS 
'���ɱ���';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.REUSEABLE IS 
'�ܷ�����:0-����1-��';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.RENEWABLE IS 
'�ܷ񲹰�:0-����1-��';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.RECYCLEABLE IS 
'�ܷ����:0-����1-��';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.MULTIPURSE IS 
'��Ǯ����־';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.FIXDAYFLAG IS 
'��Ч���Ƿ�̶�����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.FIXDAYCNT IS 
'��Ч����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.USEFLAG IS 
'ʹ�ñ�־:0-δʹ��1��ʹ��';

COMMENT ON COLUMN SG_CUR.T_CARDTYPE.PURPOSE IS 
'��;';

/*==============================================================*/
/* Table: T_CARD                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARD 
(
   CARDNO               INTEGER                        NOT NULL,
   ACCNO                VARCHAR(10),
   CARDTYPE             INTEGER,
   CARDPHYTYPE          INTEGER,
   FEETYPE              INTEGER,
   CUSTID               INTEGER,
   SHOWCARDNO           VARCHAR(10),
   CARDPHYID            VARCHAR(16),
   CARDPWD              VARCHAR(32),
   EXPIREDATE           VARCHAR(8),
   STATUS               CHAR(1)                        NOT NULL,
   LOSSFLAG             CHAR(1)                        NOT NULL,
   LOSSDATE             VARCHAR(8),
   LOSSEFTTIME          VARCHAR(30),
   FROZEFLAG            CHAR(1)                        NOT NULL,
   FROZEDATE            VARCHAR(8),
   BADFLAG              CHAR(1)                        NOT NULL,
   BADTYPE              CHAR(1),
   BADDATE              VARCHAR(8),
   LOCKFLAG             CHAR(1),
   LOCKDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CARDVERNO            VARCHAR(12),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CARD PRIMARY KEY (CARDNO),
   CONSTRAINT FK_CARD_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID),
   CONSTRAINT FK_CARD_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE),
   CONSTRAINT FK_CARD_CARDTYPE FOREIGN KEY (CARDTYPE)
      REFERENCES SG_CUR.T_CARDTYPE (CARDTYPE),
   CONSTRAINT FK_CARD_CARDPHYTYPE FOREIGN KEY (CARDPHYTYPE)
      REFERENCES SG_CUR.T_CARDPHYTYPE (CARDPHYTYPE)
);

COMMENT ON TABLE SG_CUR.T_CARD IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARD.ACCNO IS 
'���˺�';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDPHYTYPE IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_CARD.FEETYPE IS 
'�շ�����';

COMMENT ON COLUMN SG_CUR.T_CARD.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_CARD.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDPWD IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARD.EXPIREDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARD.STATUS IS 
'��¼״̬1-����2-ע��';

COMMENT ON COLUMN SG_CUR.T_CARD.LOSSFLAG IS 
'1-��ʧ0-δ��ʧ';

COMMENT ON COLUMN SG_CUR.T_CARD.LOSSDATE IS 
'��ʧ����';

COMMENT ON COLUMN SG_CUR.T_CARD.LOSSEFTTIME IS 
'��ʧ��Чʱ��';

COMMENT ON COLUMN SG_CUR.T_CARD.FROZEFLAG IS 
'1-����0-δ����';

COMMENT ON COLUMN SG_CUR.T_CARD.FROZEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARD.BADFLAG IS 
'1-����0-���ǻ���';

COMMENT ON COLUMN SG_CUR.T_CARD.BADTYPE IS 
'0-���ṹ����1-��Ϊ��2-��������';

COMMENT ON COLUMN SG_CUR.T_CARD.BADDATE IS 
'�����Ǽ�����';

COMMENT ON COLUMN SG_CUR.T_CARD.LOCKFLAG IS 
'������־';

COMMENT ON COLUMN SG_CUR.T_CARD.LOCKDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARD.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARD.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_CARD.CARDVERNO IS 
'���汾��';

COMMENT ON COLUMN SG_CUR.T_CARD.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SUBJECT                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SUBJECT 
(
   SUBJNO               VARCHAR(20)                    NOT NULL,
   SUBJNAME             VARCHAR(60),
   SUBJTYPE             INTEGER,
   BALFLAG              NUMBER(1),
   FSUBJNO              VARCHAR(20),
   SUBJLEVEL            INTEGER,
   ENDFLAG              CHAR(1),
   CONSTRAINT PK_T_SUBJECT PRIMARY KEY (SUBJNO),
   CONSTRAINT FK_SUBJECT_SUBJECT FOREIGN KEY (FSUBJNO)
      REFERENCES SG_CUR.T_SUBJECT (SUBJNO)
);

COMMENT ON TABLE SG_CUR.T_SUBJECT IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.SUBJNAME IS 
'��Ŀ����';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.SUBJTYPE IS 
'��Ŀ����';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.BALFLAG IS 
'��Ŀ����';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.FSUBJNO IS 
'�ϼ���Ŀ��';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.SUBJLEVEL IS 
'��Ŀ����';

COMMENT ON COLUMN SG_CUR.T_SUBJECT.ENDFLAG IS 
'ĩ����־';

/*==============================================================*/
/* Table: T_ACCOUNT                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ACCOUNT 
(
   ACCNO                VARCHAR(10)                    NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   ACCPWD               VARCHAR(64),
   CUSTID               INTEGER,
   CARDNO               INTEGER,
   PURSENO              INTEGER,
   SINGLEMAXAMT         NUMBER(15,2),
   DAYCOSTMAXAMT        NUMBER(15,2),
   DAYCOSTAMT           NUMBER(15,2),
   CARDMAXBAL           NUMBER(15,2),
   STATUS               CHAR(1),
   FOREGIFT             NUMBER(15,2),
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   AVAILBAL             NUMBER(15,2),
   FROZEBAL             NUMBER(15,2),
   SUBSIDYBAL           NUMBER(15,2),
   SUBSIDYNO            INTEGER,
   CARDBAL              NUMBER(15,2),
   CARDCNT              INTEGER,
   DPSCNT               INTEGER,
   PAYCNT               INTEGER,
   TERMID               INTEGER,
   TRANSTIME            VARCHAR(30),
   LASTSUBSIDYAMT       NUMBER(15,2),
   LASTSUBSIDYNO        INTEGER,
   LASTCARDBAL          NUMBER(15,2),
   LASTCARDCNT          INTEGER,
   LASTDPSCNT           INTEGER,
   LASTPAYCNT           INTEGER,
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_ACCOUNT PRIMARY KEY (ACCNO),
   CONSTRAINT FK_ACCOUN_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO),
   CONSTRAINT FK_ACCOUNT_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID),
   CONSTRAINT FK_ACCOUNT_SUBJECT FOREIGN KEY (SUBJNO)
      REFERENCES SG_CUR.T_SUBJECT (SUBJNO)
);

COMMENT ON TABLE SG_CUR.T_ACCOUNT IS 
'�ʻ���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.ACCNAME IS 
'�ʻ�����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.ACCPWD IS 
'�ʻ�����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.SINGLEMAXAMT IS 
'���������޶�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.DAYCOSTMAXAMT IS 
'�������޶�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.DAYCOSTAMT IS 
'���ۼ����ѽ��';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CARDMAXBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.FOREGIFT IS 
'Ѻ��';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.YDAYBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.BALANCE IS 
'�ʻ����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.AVAILBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.FROZEBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.SUBSIDYBAL IS 
'���첹�����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.SUBSIDYNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CARDBAL IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.DPSCNT IS 
'����ֵ����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.PAYCNT IS 
'�����Ѵ���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.TERMID IS 
'�����ն˺�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTSUBSIDYAMT IS 
'�ϴβ������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTSUBSIDYNO IS 
'�ϴβ������κ�';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTCARDBAL IS 
'�ϴο����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTCARDCNT IS 
'�ϴν��״���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTDPSCNT IS 
'�ϴο���ֵ����';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTPAYCNT IS 
'�ϴ����Ѵ���';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTTRANSDATE IS 
'�ϴν�������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.LASTACCDATE IS 
'�ϴ���������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_ACCOUNT.CLOSEDATE IS 
'��������';

/*==============================================================*/
/* Index: IDX_CARDNOPURSENO                                     */
/*==============================================================*/
CREATE INDEX IDX_CARDNOPURSENO ON SG_CUR.T_ACCOUNT (
CARDNO ASC,
PURSENO ASC
);

/*==============================================================*/
/* Index: IDX_ACCOUNT_CUSTID                                    */
/*==============================================================*/
CREATE INDEX IDX_ACCOUNT_CUSTID ON SG_CUR.T_ACCOUNT (
CUSTID ASC
);

/*==============================================================*/
/* Table: T_ACTION                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ACTION 
(
   NAME                 VARCHAR(60),
   ACTION_VALUE         INTEGER,
   REMARK               VARCHAR(240)
);

COMMENT ON TABLE SG_CUR.T_ACTION IS 
'Ȩ�޲�����';

COMMENT ON COLUMN SG_CUR.T_ACTION.NAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_ACTION.ACTION_VALUE IS 
'Ȩ��ֵ';

COMMENT ON COLUMN SG_CUR.T_ACTION.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_ATTDEVCARDLIST                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ATTDEVCARDLIST 
(
   DEVICEID             INTEGER                        NOT NULL,
   CUSTID               INTEGER                        NOT NULL,
   WEEKID               INTEGER                        NOT NULL,
   HOLIDAYID            INTEGER,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER                        NOT NULL,
   DOWNTIME             VARCHAR(30),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_ATTDEVCARDLIST PRIMARY KEY (DEVICEID, CUSTID, WEEKID)
);

COMMENT ON TABLE SG_CUR.T_ATTDEVCARDLIST IS 
'�����豸������';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.WEEKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.HOLIDAYID IS 
'�ڼ���ID';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.CARDVERNO IS 
'�����汾��';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.ADDDELFLAG IS 
'��ɾ��־:1-��-2ɾ';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.DOWNTIME IS 
'�´�ʱ��';

COMMENT ON COLUMN SG_CUR.T_ATTDEVCARDLIST.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_ATTENDDTL                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ATTENDDTL 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20)                    NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_ATTENDDTL IS 
'������ˮ��';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.DEVSEQNO IS 
'��ˮ��';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.CUSTNAME IS 
'����';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.TRANSMARK IS 
'���ױ��';

COMMENT ON COLUMN SG_CUR.T_ATTENDDTL.STATUS IS 
'״̬';

/*==============================================================*/
/* Table: T_AUTHCARD                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_AUTHCARD 
(
   CARDNO               INTEGER                        NOT NULL,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   PRIVILEGE            INTEGER,
   EXPIREDATE           VARCHAR(8),
   STATUS               CHAR(1),
   LOSSFLAG             CHAR(1),
   LOSSDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_AUTHCARD PRIMARY KEY (CARDNO),
   CONSTRAINT FK_AUTHCARD_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_AUTHCARD IS 
'����Ա��Ȩ����';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.PRIVILEGE IS 
'��Ȩ��Ȩ��';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.EXPIREDATE IS 
'��Ч��';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.STATUS IS 
'��¼״̬';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.LOSSFLAG IS 
'��ʧ״̬';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.LOSSDATE IS 
'��ʧ����';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_AUTHCARD.CLOSEDATE IS 
'ע������';

/*==============================================================*/
/* Table: T_BANK                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANK 
(
   BANKID               INTEGER                        NOT NULL,
   BANKCODE             VARCHAR(2)                     NOT NULL,
   BANKNAME             VARCHAR(60)                    NOT NULL,
   USEFLAG              NUMBER(1)                      DEFAULT '0' NOT NULL,
   CHKACCLAG            NUMBER(1)                      DEFAULT '1',
   SVRBEGINTIME         VARCHAR(6),
   SVRENDTIME           VARCHAR(6),
   BANKIP               VARCHAR(15),
   BANKPORT             INTEGER,
   BANKTIMEOUT          NUMBER(2),
   FRONTID              INTEGER,
   CHKTYPE              CHAR(1),
   CHKBEGINDATE         NUMBER(8),
   LASTCHKDATE          NUMBER(8),
   CHKBEGINTIME         VARCHAR(6),
   CVTEXECFILE          VARCHAR(240),
   CHKEXECFILE          VARCHAR(240),
   AUTORESOLVE          NUMBER(1),
   GETBANKFILE          CHAR(1)                        DEFAULT '0',
   CONSTRAINT PK_T_BANK PRIMARY KEY (BANKID)
);

COMMENT ON TABLE SG_CUR.T_BANK IS 
'������Ϣ��';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKCODE IS 
'���д���';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANK.USEFLAG IS 
'�Ƿ�����';

COMMENT ON COLUMN SG_CUR.T_BANK.CHKACCLAG IS 
'�Ƿ����';

COMMENT ON COLUMN SG_CUR.T_BANK.SVRBEGINTIME IS 
'����ʼʱ��';

COMMENT ON COLUMN SG_CUR.T_BANK.SVRENDTIME IS 
'�����ֹʱ��';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKIP IS 
'����IP';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKPORT IS 
'���ж˿�';

COMMENT ON COLUMN SG_CUR.T_BANK.BANKTIMEOUT IS 
'���ж˳�ʱʱ��';

COMMENT ON COLUMN SG_CUR.T_BANK.FRONTID IS 
'һ��ͨǰ�û�ID';

COMMENT ON COLUMN SG_CUR.T_BANK.CHKTYPE IS 
'һ��ͨ�˶���';

COMMENT ON COLUMN SG_CUR.T_BANK.CHKBEGINDATE IS 
'���˿�ʼ����';

COMMENT ON COLUMN SG_CUR.T_BANK.LASTCHKDATE IS 
'�ϴζ�������';

COMMENT ON COLUMN SG_CUR.T_BANK.CHKBEGINTIME IS 
'���˿�ʼʱ��';

COMMENT ON COLUMN SG_CUR.T_BANK.CVTEXECFILE IS 
'ת��ִ���ļ�';

COMMENT ON COLUMN SG_CUR.T_BANK.CHKEXECFILE IS 
'����ִ���ļ�';

COMMENT ON COLUMN SG_CUR.T_BANK.AUTORESOLVE IS 
'���˲����Զ�����';

COMMENT ON COLUMN SG_CUR.T_BANK.GETBANKFILE IS 
'1:������ȡ���ж����ļ�';

/*==============================================================*/
/* Index: UNIQ_BANKCODE_BANKCODE                                */
/*==============================================================*/
CREATE UNIQUE INDEX UNIQ_BANKCODE_BANKCODE ON SG_CUR.T_BANK (
BANKCODE ASC
);

/*==============================================================*/
/* Table: T_BANKCARD                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCARD 
(
   CUSTID               INTEGER                        NOT NULL,
   BANKCARDNO           VARCHAR(30)                    NOT NULL,
   BANKCODE             VARCHAR(2),
   BATCHNO              VARCHAR(30),
   CREATEDDATE          VARCHAR(8),
   RELATEDATE           VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_BANKCARD PRIMARY KEY (CUSTID, BANKCARDNO),
   CONSTRAINT FK_BANKCARD_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID)
);

COMMENT ON TABLE SG_CUR.T_BANKCARD IS 
'�ͻ����п���';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.BANKCARDNO IS 
'���п���';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.BANKCODE IS 
'���б��';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.CREATEDDATE IS 
'¼������';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.RELATEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCARD.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_BANKCARDDTL                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCARDDTL 
(
   REFNO                NUMBER(14)                     NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_BANKCARDDTL IS 
'���п�����ˮ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.CUSTNAME IS 
'����';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.BANKCARDNO IS 
'���п���';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.OPTYPE IS 
'1- ǩԼ2-��Լ3- ͬ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.ADDDELFLAG IS 
'1-����2-ɾ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_BANKCARDDTL.REMARK IS 
'��ע';

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_CUSTID                                */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDDTL_CUSTID ON SG_CUR.T_BANKCARDDTL (
CUSTID ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_SNO                                   */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDDTL_SNO ON SG_CUR.T_BANKCARDDTL (
STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_OPTYPE                                */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDDTL_OPTYPE ON SG_CUR.T_BANKCARDDTL (
OPTYPE ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDDTL_TRANSDATE                             */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDDTL_TRANSDATE ON SG_CUR.T_BANKCARDDTL (
TRANSDATE ASC
);

/*==============================================================*/
/* Table: T_BANKCARDTMP                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCARDTMP 
(
   RECORDNO             NUMBER(14)                     NOT NULL,
   TERMID               INTEGER,
   BATCHNO              VARCHAR(30),
   OPERCODE             VARCHAR(8),
   CUSTID               INTEGER,
   STUEMPNO             VARCHAR(20),
   BANKCARDNO           VARCHAR(30),
   OPTYPE               NUMBER(1),
   TRANSDATE            VARCHAR(8),
   STATUS               NUMBER(1)                      NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_BANKCARDTMP PRIMARY KEY (RECORDNO)
);

COMMENT ON TABLE SG_CUR.T_BANKCARDTMP IS 
'���п�������ʱ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.RECORDNO IS 
'��¼��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.BANKCARDNO IS 
'���п���';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.OPTYPE IS 
'1- ǩԼ2-��Լ3- ͬ��';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.STATUS IS 
'1��Ч��¼2�������¼3����ʧ��4����ɹ�';

COMMENT ON COLUMN SG_CUR.T_BANKCARDTMP.REMARK IS 
'��ע';

/*==============================================================*/
/* Index: IDX_BANKCARDTMP_STATUS                                */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDTMP_STATUS ON SG_CUR.T_BANKCARDTMP (
STATUS ASC
);

/*==============================================================*/
/* Index: IDX_BANKCARDTMP_BATCHNO                               */
/*==============================================================*/
CREATE INDEX IDX_BANKCARDTMP_BATCHNO ON SG_CUR.T_BANKCARDTMP (
BATCHNO ASC
);

/*==============================================================*/
/* Table: T_BANKCHKBILL                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCHKBILL 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   BANKCARDNO           VARCHAR(30)                    NOT NULL,
   BANKSN               VARCHAR(30)                    NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   LOCALSN              VARCHAR(30),
   TRANSCODE            INTEGER,
   SUMMARY              VARCHAR(60),
   BANKAMT              NUMBER(15,2)                   NOT NULL,
   LOCALAMT             NUMBER(15,2),
   DIFFAMT              NUMBER(15,2),
   CHKFLAG              CHAR(1),
   CONSTRAINT PK_T_BANKCHKBILL PRIMARY KEY (TRANSDATE, BANKCARDNO, BANKSN, CARDNO)
);

COMMENT ON TABLE SG_CUR.T_BANKCHKBILL IS 
'���ж��˵���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.BANKCARDNO IS 
'���п���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.BANKSN IS 
'���ж���ˮ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.LOCALSN IS 
'������ˮ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.BANKAMT IS 
'���ж˽��׽��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.LOCALAMT IS 
'���ؽ��׽��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.DIFFAMT IS 
'���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKBILL.CHKFLAG IS 
'0-δ����1-�Ѳ���';

/*==============================================================*/
/* Table: T_BANKCHKDATE                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCHKDATE 
(
   CHKDATE              VARCHAR(8)                     NOT NULL,
   CHKFLAG              NUMBER(1),
   CONSTRAINT PK_T_BANKCHKDATE PRIMARY KEY (CHKDATE)
);

COMMENT ON TABLE SG_CUR.T_BANKCHKDATE IS 
'���ж����ļ����ڿ��Ʊ�';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDATE.CHKDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDATE.CHKFLAG IS 
'�˶Ա�־';

/*==============================================================*/
/* Table: T_BANKCHKDTL                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCHKDTL 
(
   BANKID               INTEGER                        NOT NULL,
   BANKDATE             NUMBER(8)                      NOT NULL,
   RECORDNO             NUMBER(8)                      NOT NULL,
   AMOUNT               NUMBER(15,2)                   NOT NULL,
   TRANSDATE            NUMBER(8),
   CHKRESULT            CHAR(1)                        DEFAULT 'I',
   RESOLVED             CHAR(1)                        DEFAULT '0' NOT NULL,
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

COMMENT ON TABLE SG_CUR.T_BANKCHKDTL IS 
'���ж�����ϸ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.BANKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.BANKDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.RECORDNO IS 
'��¼��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.CHKRESULT IS 
'���˽��:I-δ����E��ͬ,���� ,N������,D,����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.RESOLVED IS 
'����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.BANKCARDNO IS 
'���п���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.LOCALSNO IS 
'������ˮ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.BANKSNO IS 
'������ˮ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKDTL.OPERCODE IS 
'����Ա';

/*==============================================================*/
/* Index: IDX_BANKCHKDTL_BANKCARDNO                             */
/*==============================================================*/
CREATE INDEX IDX_BANKCHKDTL_BANKCARDNO ON SG_CUR.T_BANKCHKDTL (
BANKCARDNO ASC
);

/*==============================================================*/
/* Table: T_BANKCHKFILE                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BANKCHKFILE 
(
   BANKID               INTEGER                        NOT NULL,
   BANKDATE             NUMBER(8)                      NOT NULL,
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

COMMENT ON TABLE SG_CUR.T_BANKCHKFILE IS 
'���ж����ļ���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.BANKID IS 
'���б�ʶ';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.BANKDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.BANKCHKFILE IS 
'���ж����ļ���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.LOCALCHKFILE IS 
'���ض����ļ���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.LOCALCVTFILE IS 
'����ת���ļ���';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.FILESOURCE IS 
'''L�� ���� ��B''����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.STATUS IS 
'�˶�״̬:I����''C''�������''R''�������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.RESOLVED IS 
'�����־';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.BANKCNT IS 
'���м�¼����';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.BANKAMT IS 
'�����ܽ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.LOCALCNT IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.LOCALAMT IS 
'�����ܽ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.CRTTIME IS 
'��¼����ʱ��';

COMMENT ON COLUMN SG_CUR.T_BANKCHKFILE.UPDTIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_BRANCH                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_BRANCH 
(
   BRANCHNO             INTEGER                        NOT NULL,
   AREACODE             VARCHAR(3),
   BRANCHNAME           VARCHAR(60),
   BRANCHTYPE           CHAR(1),
   BANKCODE             VARCHAR(2),
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
   CONSTRAINT PK_T_BRANCH PRIMARY KEY (BRANCHNO),
   CONSTRAINT FK_BRANCH_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_BRANCH IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BRANCHNO IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_BRANCH.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BRANCHNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BRANCHTYPE IS 
'�������ͣ�1-��������2-��ֵ��3-����';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BANKCODE IS 
'���д���';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BANKACCNO IS 
'�����ʻ�';

COMMENT ON COLUMN SG_CUR.T_BRANCH.BANKACCNAME IS 
'�����ʻ���';

COMMENT ON COLUMN SG_CUR.T_BRANCH.CONTACTMAN IS 
'��ϵ��';

COMMENT ON COLUMN SG_CUR.T_BRANCH.TEL IS 
'�绰';

COMMENT ON COLUMN SG_CUR.T_BRANCH.MOBILE IS 
'�ֻ�';

COMMENT ON COLUMN SG_CUR.T_BRANCH.FAX IS 
'����';

COMMENT ON COLUMN SG_CUR.T_BRANCH.ADDR IS 
'��ַ';

COMMENT ON COLUMN SG_CUR.T_BRANCH.ZIPCODE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_BRANCH.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_BRANCH.OPENDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_BRANCH.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_BRANCH.USEFLAG IS 
'ʹ��״̬ 0-δʹ��1-��ʹ��';

COMMENT ON COLUMN SG_CUR.T_BRANCH.LASTSAVED IS 
'����ʱ��';

/*==============================================================*/
/* Index: INDEX_CARD_CARDTYPE                                   */
/*==============================================================*/
CREATE INDEX INDEX_CARD_CARDTYPE ON SG_CUR.T_CARD (
CARDTYPE ASC
);

/*==============================================================*/
/* Table: T_CARDACCDIFF                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDACCDIFF 
(
   CARDNO               INTEGER                        NOT NULL,
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
   STARTDATE            VARCHAR(8)                     NOT NULL,
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
   CONSTRAINT PK_T_CARDACCDIFF PRIMARY KEY (CARDNO, STARTDATE),
   CONSTRAINT FK_CARDACCDIFF_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO),
   CONSTRAINT FK_CARDACCDIFF_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID)
);

COMMENT ON TABLE SG_CUR.T_CARDACCDIFF IS 
'���ⲻƽ��';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.CUSTNAME IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.AREACODE IS 
'У��';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.DIFFAMT IS 
'��ƽ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.DIFFDAYCNT IS 
'��ƽ����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.AVAILBAL IS 
'�˻���ǰ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.LASTCARDBAL IS 
'����ǰ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.LASTCARDCNT IS 
'�˻������״���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.STATDATE IS 
'ͳ������';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.STATTIME IS 
'ͳ��ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.STARTDATE IS 
'��ƽ��ʼ����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.ENDDATE IS 
'ͳ�ƽ�ֹ����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.MAXCARDCNT IS 
'�ڼ俨����״���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.CARDAFTBAL IS 
'�ڼ俨������';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.PAYLOSSAMT IS 
'�ڼ�����ȱʧ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.DPSLOSSAMT IS 
'�ڼ��ֵȱʧ���';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.TOTALLOSSAMT IS 
'�ڼ�ȱʧ�ܽ��';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.TOTALLOSSCNT IS 
'�ڼ�ȱʧ����';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.DEALDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.OPERCODE IS 
'�������Ա';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.STATUS IS 
'ƽ��״̬';

COMMENT ON COLUMN SG_CUR.T_CARDACCDIFF.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_CARDBALANCE                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDBALANCE 
(
   ACCNO                VARCHAR(10)                    NOT NULL,
   PURSETYPE            NUMBER(1)                      NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   OLDCARDNO            INTEGER,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   DPSCNT               INTEGER                        NOT NULL,
   PAYCNT               INTEGER,
   BALANCE              NUMBER(15,2),
   CARDBAL              NUMBER(15,2)                   NOT NULL,
   ACCUMDPSAMT          NUMBER(15,2),
   CONSTRAINT PK_T_CARDBALANCE PRIMARY KEY (ACCNO, PURSETYPE)
);

COMMENT ON TABLE SG_CUR.T_CARDBALANCE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.PURSETYPE IS 
'Ǯ������';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.OLDCARDNO IS 
'ԭ����';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.TRANSDATE IS 
'���������';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.TRANSTIME IS 
'�����ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.DPSCNT IS 
'��ֵ����';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.PAYCNT IS 
'���Ѵ���';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.BALANCE IS 
'�˻����';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.CARDBAL IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_CARDBALANCE.ACCUMDPSAMT IS 
'�ۼƳ�ֵ���';

/*==============================================================*/
/* Index: IDX_CARDBALANCE_CARDNO                                */
/*==============================================================*/
CREATE INDEX IDX_CARDBALANCE_CARDNO ON SG_CUR.T_CARDBALANCE (
PURSETYPE ASC,
CARDNO ASC
);

/*==============================================================*/
/* Table: T_CARDBALUPDLIST                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDBALUPDLIST 
(
   BATCHNO              VARCHAR(30)                    NOT NULL,
   SEQNO                INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   TRANSDATE            NUMBER(8),
   STATUS               CHAR(1)                        NOT NULL,
   AMOUNT               NUMBER(15,2)                   NOT NULL,
   SUMMARY              VARCHAR(60),
   TRANSCODE            INTEGER,
   LASTUPDTIME          VARCHAR(30),
   CONSTRAINT PK_T_CARDBALUPDLIST PRIMARY KEY (BATCHNO, SEQNO)
);

COMMENT ON TABLE SG_CUR.T_CARDBALUPDLIST IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.BATCHNO IS 
'���κ�';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.SEQNO IS 
'�·����';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.STATUS IS 
'N-δ����P���·�S����ȡFд��ʧ��Iд���ж�C����';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.AMOUNT IS 
'��д�����Ϊ��Ǯ��Ϊ��Ǯ';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.TRANSCODE IS 
'ԭ���״���';

COMMENT ON COLUMN SG_CUR.T_CARDBALUPDLIST.LASTUPDTIME IS 
'����ʱ��';

/*==============================================================*/
/* Index: IDX_CARDBALUPDLIST_CARDNO                             */
/*==============================================================*/
CREATE INDEX IDX_CARDBALUPDLIST_CARDNO ON SG_CUR.T_CARDBALUPDLIST (
CARDNO ASC,
STATUS ASC
);

/*==============================================================*/
/* Table: T_CARDBITMAP                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDBITMAP 
(
   CARDNO               INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_CARDBITMAP PRIMARY KEY (CARDNO),
   CONSTRAINT FK_CARDBITMAP_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_CARDBITMAP IS 
'�������״���>����׼��ˮ��+1000���ƶ���500λͼ��ǰ500λͼ��λ�ã���պ�500�ֽ�λͼ���޸Ŀ���׼��ˮ��Ϊ����׼��ˮ��+500';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BASENO IS 
'��׼����ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP0 IS 
'λͼ0';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP1 IS 
'λͼ1';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP2 IS 
'λͼ2';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP3 IS 
'λͼ3';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP4 IS 
'λͼ4';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP5 IS 
'λͼ5';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP6 IS 
'λͼ6';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP7 IS 
'λͼ7';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP8 IS 
'λͼ8';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.BITMAP9 IS 
'λͼ9';

COMMENT ON COLUMN SG_CUR.T_CARDBITMAP.DELFLAG IS 
'ɾ����־';

/*==============================================================*/
/* Table: T_CARDBOOK                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDBOOK 
(
   SHOWCARDNO           NUMBER(10)                     NOT NULL,
   CARDTYPE             INTEGER                        NOT NULL,
   CARDPHYID            VARCHAR(16),
   OPERCODE             VARCHAR(8)                     NOT NULL,
   PUTOPERCODE          VARCHAR(8),
   BATCHNO              VARCHAR(30),
   GETDATE              VARCHAR(8),
   USEDATE              VARCHAR(8),
   RECLAIMDATE          VARCHAR(8),
   USESTATUS            NUMBER(1)                      NOT NULL,
   CONSTRAINT PK_T_CARDBOOK PRIMARY KEY (SHOWCARDNO)
);

COMMENT ON TABLE SG_CUR.T_CARDBOOK IS 
'��Ƭ�ǼǱ�';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.SHOWCARDNO IS 
'��¼��';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.PUTOPERCODE IS 
'ת������Ա';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.GETDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.USEDATE IS 
'ʹ������';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.RECLAIMDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDBOOK.USESTATUS IS 
'ʹ��״̬';

/*==============================================================*/
/* Table: T_CARDDTL                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   CARDTYPE             INTEGER,
   USETYPE              INTEGER                        NOT NULL,
   SUMMARY              VARCHAR(60),
   INOUTFLAG            INTEGER,
   TRANSCNT             INTEGER,
   CARDPHYID            VARCHAR(16),
   SHOWCARDNO           VARCHAR(10),
   CONSTRAINT PK_T_CARDDTL PRIMARY KEY (ACCDATE, TERMSEQNO, TERMID, OPERCODE, USETYPE)
);

COMMENT ON TABLE SG_CUR.T_CARDDTL IS 
'��Ƭʹ����ϸ��';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.TERMID IS 
'�յ���';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.BRANCHNO IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.USETYPE IS 
'��ʹ������';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.INOUTFLAG IS 
'1-����2-֧��';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.TRANSCNT IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.CARDPHYID IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDDTL.SHOWCARDNO IS 
'��ʾ����';

/*==============================================================*/
/* Table: T_PHYDEVICE                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PHYDEVICE 
(
   PHYTYPE              INTEGER                        NOT NULL,
   DNAME                VARCHAR(60),
   DTYPE                VARCHAR(60),
   FACTORY              VARCHAR(60),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PHYDEVICE PRIMARY KEY (PHYTYPE)
);

COMMENT ON TABLE SG_CUR.T_PHYDEVICE IS 
'�豸�������ͱ�';

/*==============================================================*/
/* Table: T_SUBSYSTEM                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SUBSYSTEM 
(
   SYSID                INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_SUBSYSTEM PRIMARY KEY (SYSID),
   CONSTRAINT FK_SUBSYSTEM_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_SUBSYSTEM IS 
'��ϵͳ��';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.SYSNAME IS 
'��ϵͳ����';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.SYSTYPE IS 
'��ϵͳ���';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.CARDVERNO IS 
'���汾��';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.RUNSTATUS IS 
'����״̬';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.OPENDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSTEM.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_DEVICE                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DEVICE 
(
   DEVICEID             INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_DEVICE PRIMARY KEY (DEVICEID),
   CONSTRAINT FK_DEVICE_PHYDEVICE FOREIGN KEY (DEVPHYTYPE)
      REFERENCES SG_CUR.T_PHYDEVICE (PHYTYPE),
   CONSTRAINT FK_DEVICE_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE),
   CONSTRAINT FK_DEVICE_SUBSYS FOREIGN KEY (SYSID)
      REFERENCES SG_CUR.T_SUBSYSTEM (SYSID)
);

COMMENT ON TABLE SG_CUR.T_DEVICE IS 
'�豸��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVICEID IS 
'�ն˱��Ҳ���豸���';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVICENAME IS 
'�豸����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVPHYID IS 
'�豸����ID��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVICENO IS 
'�豸����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVPHYTYPE IS 
'�豸���̴���';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVTYPECODE IS 
'�豸���͡�';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVVERNO IS 
'�豸�汾�š�';

COMMENT ON COLUMN SG_CUR.T_DEVICE.CARDPHYTYPE IS 
'�������ͺ�';

COMMENT ON COLUMN SG_CUR.T_DEVICE.FDEVICEID IS 
'�ϼ��豸ID';

COMMENT ON COLUMN SG_CUR.T_DEVICE.RUNSTATUS IS 
'����״̬';

COMMENT ON COLUMN SG_CUR.T_DEVICE.STATUS IS 
'״̬:1-����2-ע��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.SVRPORTCNT IS 
'�˿�����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.SVRPORTNO IS 
'�������ӿڱ��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.COMMTYPE IS 
'ͨѶ��ʽ:1-����2-MODEM3-TCPIP 9-����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.IP IS 
'IP��ַ';

COMMENT ON COLUMN SG_CUR.T_DEVICE.PORTNO IS 
'������SOCKET�˿ں�';

COMMENT ON COLUMN SG_CUR.T_DEVICE.BAUDRATE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_DEVICE.CARDSET IS 
'�ն�����ʹ�õĿ��շ����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.CARDVERNO IS 
'���������汾��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.LASTSEQNO IS 
'�ϴ��豸������ˮ��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.LASTTRANSTIME IS 
'�ϴν���ʱ��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.PURSENO IS 
'�豸������Ǯ����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.MAXAMT IS 
'����ֵ�޶��λ��';

COMMENT ON COLUMN SG_CUR.T_DEVICE.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_DEVICE.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DOORLSTVER IS 
'���ڼ�¼�Ѿ���¼��Ϣ���е������汾';

COMMENT ON COLUMN SG_CUR.T_DEVICE.DEVUSAGE IS 
'�豸��;';

COMMENT ON COLUMN SG_CUR.T_DEVICE.OPENDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_DEVICE.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_DEVICE.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_DEVICE.LASTSAVED IS 
'�ϴ��޸�����';

COMMENT ON COLUMN SG_CUR.T_DEVICE.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_CARDINSTEADDTL                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDINSTEADDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_CARDINSTEADDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO),
   CONSTRAINT FK_CARDINSTEADDTL_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO),
   CONSTRAINT FK_CARDINSTEADDTL_DEVICE FOREIGN KEY (TERMID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_CARDINSTEADDTL IS 
'-�����ǼǱ�';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.CARDNO IS 
'ԭ����';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDCARDTYPE IS 
'ԭ������';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDCARDPHYID IS 
'ԭ������ID';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDSHOWCARDNO IS 
'ԭ��ʾ����';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDCARDCNT IS 
'ԭ�����״���';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDCARDBAL IS 
'ԭ�����';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.OLDSUBSIDYNO IS 
'ԭ���������κ�';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.CARDPHYID IS 
'�¿�����ID';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.SHOWCARDNO IS 
'�¿���ʾ����';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.REVFLAG IS 
'������־';

COMMENT ON COLUMN SG_CUR.T_CARDINSTEADDTL.STATUS IS 
'״̬';

/*==============================================================*/
/* Index: IDX_OLDCARDNOCARDNO                                   */
/*==============================================================*/
CREATE INDEX IDX_OLDCARDNOCARDNO ON SG_CUR.T_CARDINSTEADDTL (
CARDNO ASC
);

/*==============================================================*/
/* Table: T_CARDNOCHANGE                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDNOCHANGE 
(
   OLDCARDNO            INTEGER                        NOT NULL,
   NEWCARDNO            INTEGER                        NOT NULL,
   CHANGEDATE           VARCHAR(8),
   CONSTRAINT PK_T_CARDNOCHANGE PRIMARY KEY (OLDCARDNO),
   CONSTRAINT FK_CARDNOCHANGE_CARD FOREIGN KEY (NEWCARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_CARDNOCHANGE IS 
'�¾ɿ��Ŷ��ձ�';

COMMENT ON COLUMN SG_CUR.T_CARDNOCHANGE.OLDCARDNO IS 
'�ɿ���';

COMMENT ON COLUMN SG_CUR.T_CARDNOCHANGE.NEWCARDNO IS 
'�¿���';

COMMENT ON COLUMN SG_CUR.T_CARDNOCHANGE.CHANGEDATE IS 
'�������';

/*==============================================================*/
/* Table: T_CARDTRANS                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDTRANS 
(
   CARDNO               INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8)                     DEFAULT TO_CHAR(SYSDATE,'YYYYMMDD') NOT NULL,
   TRANSTIME            VARCHAR(6)                     DEFAULT TO_CHAR(SYSDATE,'HH24MISS') NOT NULL,
   TRANSCODE            INTEGER                        DEFAULT 0 NOT NULL,
   TERMID               INTEGER                        DEFAULT 0 NOT NULL,
   TERMSEQNO            INTEGER                        DEFAULT 0 NOT NULL,
   DPSCNT               INTEGER                        DEFAULT 0 NOT NULL,
   PAYCNT               INTEGER                        DEFAULT 0 NOT NULL,
   AMOUNT               NUMBER(15,2)                   DEFAULT '0' NOT NULL,
   CARDBEFBAL           NUMBER(15,2)                   DEFAULT '0' NOT NULL,
   CARDAFTBAL           NUMBER(15,2)                   DEFAULT '0' NOT NULL,
   UPDCNT               INTEGER                        DEFAULT 0,
   UPDTIME              CHAR(14)                       DEFAULT TO_CHAR(SYSDATE,'YYYYMMDDHH24MISS'),
   CONSTRAINT PK_T_CARDTRANS PRIMARY KEY (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_CARDTRANS IS 
'��������ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.TRANSCODE IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.TERMID IS 
'�����ն�';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.DPSCNT IS 
'��ֵ����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.PAYCNT IS 
'���Ѵ���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.AMOUNT IS 
'���׽��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.CARDBEFBAL IS 
'����ǰ���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.UPDCNT IS 
'���´���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANS.UPDTIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_CARDTRANSDTL                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDTRANSDTL 
(
   CARDNO               INTEGER                        NOT NULL,
   TRANSFLAG            NUMBER(1)                      NOT NULL,
   CARDCNT              INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6)                     NOT NULL,
   TERMNO               VARCHAR(12)                    NOT NULL,
   TERMSNO              INTEGER                        NOT NULL,
   CARDBEFBAL           NUMBER(15,2)                   NOT NULL,
   AMOUNT               NUMBER(15,2)                   NOT NULL,
   ADDAMT               NUMBER(15,2),
   MANAGEFEE            NUMBER(15,2),
   SHOPID               INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   STATUS               NUMBER(1)                      NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CARDTRANSDTL PRIMARY KEY (TRANSFLAG, CARDCNT, CARDNO)
);

COMMENT ON TABLE SG_CUR.T_CARDTRANSDTL IS 
'CARD������ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.TRANSFLAG IS 
'���ױ�־';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.TERMNO IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.TERMSNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.AMOUNT IS 
'������-���������';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.ADDAMT IS 
'��д���';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.MANAGEFEE IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.SHOPID IS 
'�̻�����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.STATUS IS 
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN SG_CUR.T_CARDTRANSDTL.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_OPERATOR                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_OPERATOR 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   OPERTYPE             CHAR(1),
   BRANCHNO             INTEGER,
   CARDNO               INTEGER,
   OPERNAME             VARCHAR(60)                    NOT NULL,
   TEL                  VARCHAR(30),
   MOBILE               VARCHAR(30),
   EMAIL                VARCHAR(60),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   OPERPWD              VARCHAR(32),
   STATUS               CHAR(1),
   LASTTRANSDATE        VARCHAR(8),
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
   CONSTRAINT PK_T_OPERATOR PRIMARY KEY (OPERCODE),
   CONSTRAINT FK_OPERATOR_BRANCH FOREIGN KEY (BRANCHNO)
      REFERENCES SG_CUR.T_BRANCH (BRANCHNO)
);

COMMENT ON TABLE SG_CUR.T_OPERATOR IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.OPERCODE IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.OPERTYPE IS 
'����Ա����:0-ϵͳ����Ա 1-��˲���Ա 2-ҵ�����Ա 3-ҽ��ϵͳ����Ա';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.BRANCHNO IS 
'���������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.CARDNO IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.OPERNAME IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.TEL IS 
'�绰';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.MOBILE IS 
'�ֻ�';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.EMAIL IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.ADDR IS 
'��ַ';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.ZIPCODE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.OPERPWD IS 
'����';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.STATUS IS 
'״̬:0-����1-����2-ע��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.LASTTRANSDATE IS 
'���������:��ֵ����Աʹ��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.FUNCSET IS 
'����Ȩ�޼�';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.RIGHTFLAG IS 
'Ȩ�ޱ�־';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.SITELIMIT IS 
'�Ƿ���վ������:0-������1-������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.LOGINFLAG IS 
'��¼��־:0-δ��¼1-�ѵ�¼';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.LOGINSITENO IS 
'��¼վ���';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.LOGINTIME IS 
'��¼ʱ��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.LOGOUTTIME IS 
'�ǳ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.FAILNUMBER IS 
'��¼ʧ�ܴ���';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.OPENDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR.CLOSEDATE IS 
'ע������';

/*==============================================================*/
/* Table: T_CARDTYPERIGHT                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDTYPERIGHT 
(
   CARDTYPE             INTEGER                        NOT NULL,
   FEETYPE              INTEGER                        NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CARDTYPERIGHT PRIMARY KEY (CARDTYPE, FEETYPE),
   CONSTRAINT FK_CARDTYPERIGHT_CARDTYPE FOREIGN KEY (CARDTYPE)
      REFERENCES SG_CUR.T_CARDTYPE (CARDTYPE),
   CONSTRAINT FK_CARDTYPERIGHT_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE),
   CONSTRAINT FK_CARDTYPERIGHT_OPERATOR FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_OPERATOR (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_CARDTYPERIGHT IS 
'������Ȩ�ޱ�';

COMMENT ON COLUMN SG_CUR.T_CARDTYPERIGHT.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CARDTYPERIGHT.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPERIGHT.OPERCODE IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_CARDTYPERIGHT.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CARDVER                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CARDVER 
(
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   CARDVERNO            VARCHAR(12)                    NOT NULL,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   STUEMPNO             VARCHAR(20),
   CARDVERTYPE          INTEGER,
   ADDDELFLAG           NUMBER(1),
   STATUS               CHAR(1),
   CONSTRAINT PK_T_CARDVER PRIMARY KEY (CARDVERNO),
   CONSTRAINT FK_CARDVE_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO),
   CONSTRAINT FK_CARDVE_DEVICE FOREIGN KEY (TERMID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_CARDVER IS 
'���汾������';

COMMENT ON COLUMN SG_CUR.T_CARDVER.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CARDVER.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_CARDVER.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_CARDVER.CARDVERNO IS 
'���汾��';

COMMENT ON COLUMN SG_CUR.T_CARDVER.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_CARDVER.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_CARDVER.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_CARDVER.CARDVERTYPE IS 
'��־:1-��ʧ2���3-����4-�ⶳ5-�·���6-�˿� 7-�����ɿ�8�����¿�';

COMMENT ON COLUMN SG_CUR.T_CARDVER.ADDDELFLAG IS 
'��ɾ��־1-���-2ɾ��';

COMMENT ON COLUMN SG_CUR.T_CARDVER.STATUS IS 
'��¼״̬1-����-2-ע��';

/*==============================================================*/
/* Index: INDEX_CARDNO                                          */
/*==============================================================*/
CREATE INDEX INDEX_CARDNO ON SG_CUR.T_CARDVER (
CARDNO ASC
);

/*==============================================================*/
/* Table: T_CFGACCCHK                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGACCCHK 
(
   ACCCHKTYPE           INTEGER                        NOT NULL,
   ACCCHKTYPENAME       VARCHAR(30),
   ACCCHKFILEPATH       VARCHAR(240),
   ACCCHKEXCNAME        VARCHAR(30),
   BCCDRTPNO            INTEGER,
   BCCFUNCNO            INTEGER,
   BCCTIMEOUT           INTEGER,
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_CFGACCCHK PRIMARY KEY (ACCCHKTYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGACCCHK IS 
'�������ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.ACCCHKTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.ACCCHKTYPENAME IS 
'�����������';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.ACCCHKFILEPATH IS 
'�����ļ���ǰ�û��ϵ�·��';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.ACCCHKEXCNAME IS 
'���˳��������';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.BCCDRTPNO IS 
'ǰ�û��ڵ�';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.BCCFUNCNO IS 
'ǰ�û����ܺ�';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.BCCTIMEOUT IS 
'ǰ�û���ʱʱ�䣨�룩';

COMMENT ON COLUMN SG_CUR.T_CFGACCCHK.DELFLAG IS 
'�Ƿ�ɾ��ǰ���϶����ļ�';

/*==============================================================*/
/* Table: T_CFGBANK                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGBANK 
(
   BANKCODE             VARCHAR(2)                     NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_CFGBANK IS 
'���д������ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKCODE IS 
'���д���';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKSTARTTIME IS 
'���з���ʼʱ��';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKENDTIME IS 
'���з����ֹʱ��';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKIP IS 
'����IP';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKPORT IS 
'���ж˿�';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BANKTIMEOUT IS 
'���ж˳�ʱʱ��';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BCCDRTPNO IS 
'ǰ�û��ڵ�';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BCCFUNCNO IS 
'ǰ�û����ܺ�';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.BCCTIMEOUT IS 
'ǰ�û���ʱ';

COMMENT ON COLUMN SG_CUR.T_CFGBANK.QRYCARDFLAG IS 
'QRYCARDFLAG';

/*==============================================================*/
/* Table: T_TRANSTYPE                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_TRANSTYPE 
(
   TRANSTYPE            INTEGER                        NOT NULL,
   TRANSNAME            VARCHAR(60),
   DISPLAYFLAG          CHAR(1),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_TRANSTYPE PRIMARY KEY (TRANSTYPE)
);

COMMENT ON TABLE SG_CUR.T_TRANSTYPE IS 
'�������ͱ�';

COMMENT ON COLUMN SG_CUR.T_TRANSTYPE.TRANSTYPE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_TRANSTYPE.TRANSNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_TRANSTYPE.DISPLAYFLAG IS 
'��ʾ��־1-��ʾ0-����ʾ';

COMMENT ON COLUMN SG_CUR.T_TRANSTYPE.USEFLAG IS 
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_CFGFEE                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGFEE 
(
   FEETYPE              INTEGER                        NOT NULL,
   TRANSCODE            INTEGER                        NOT NULL,
   CARDTYPE             INTEGER                        NOT NULL,
   TRANSTYPE            INTEGER                        NOT NULL,
   RATETYPE             INTEGER,
   RATEAMT              NUMBER(15,2),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGFEE PRIMARY KEY (FEETYPE, TRANSCODE, CARDTYPE, TRANSTYPE),
   CONSTRAINT FK_CFGFEE_CARDTYPE FOREIGN KEY (CARDTYPE)
      REFERENCES SG_CUR.T_CARDTYPE (CARDTYPE),
   CONSTRAINT FK_CFGFEE_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE),
   CONSTRAINT FK_CFGFEE_TRANSTYPE FOREIGN KEY (TRANSTYPE)
      REFERENCES SG_CUR.T_TRANSTYPE (TRANSTYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGFEE IS 
'�����շ����ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.FEETYPE IS 
'�ͻ����շ����';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.RATETYPE IS 
'��������:1�̶�ֵ- 2-�ٷֱ�3-������ֵ��Ϊ�շѽ��';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.RATEAMT IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CFGFEE.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_CFGPAYMENT                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGPAYMENT 
(
   PAYCODE              INTEGER                        NOT NULL,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   ENABLED              NUMBER(1)                      NOT NULL,
   ONLINEPAY            NUMBER(1)                      NOT NULL,
   PAYCHKFLAG           NUMBER(1)                      NOT NULL,
   PAYEEACCTYPE         NUMBER(1)                      NOT NULL,
   SHOPID               INTEGER                        NOT NULL,
   BCCFUNCNO            INTEGER,
   BCCDRTPNO            INTEGER,
   IP                   VARCHAR(15),
   PORT                 INTEGER,
   TIMEOUT              INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGPAYMENT PRIMARY KEY (PAYCODE)
);

COMMENT ON TABLE SG_CUR.T_CFGPAYMENT IS 
'֧���������ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.PAYCODE IS 
'�ͻ����շ����';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.SUMMARY IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.ENABLED IS 
'�Ƿ�����';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.ONLINEPAY IS 
'0-������1����';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.PAYCHKFLAG IS 
'1��Ҫ0����Ҫ';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.PAYEEACCTYPE IS 
'0-����1����2�ͻ���3ѧ��';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.BCCFUNCNO IS 
'BCC�����ܺ�';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.BCCDRTPNO IS 
'BCCDRTP�ڵ��';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.IP IS 
'�̻�����IP';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.PORT IS 
'�̻�����˿�';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.TIMEOUT IS 
'�̻���ʱʱ��(��)';

COMMENT ON COLUMN SG_CUR.T_CFGPAYMENT.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SHOP                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOP 
(
   SHOPID               INTEGER                        NOT NULL,
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
   BUSINESSADDR         VARCHAR(240),
   ADDR                 VARCHAR(240),
   ZIPCODE              VARCHAR(6),
   BOARDFEEFLAG         CHAR(1),
   RAKEOFFTYPE          CHAR(1),
   RAKEOFFRATE          NUMBER(5,4),
   DEPOSITAGIO          NUMBER(5,4),
   DEPOSITCNT           INTEGER,
   DEPOSITAMT           NUMBER(15,2),
   DISCOUNTAMT          NUMBER(15,2),
   BANKCODE             VARCHAR(2),
   BANKACCNO            VARCHAR(20),
   BANKACCNAME          VARCHAR(60),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_SHOP PRIMARY KEY (SHOPID),
   CONSTRAINT FK_SHOP_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_SHOP IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOP.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOP.FSHOPID IS 
'�ϼ��̻���';

COMMENT ON COLUMN SG_CUR.T_SHOP.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SHOP.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_SHOP.SHOPNAME IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOP.SHOPTYPE IS 
'�̻�����1-�շ��̻�2-��ֵ�̻�';

COMMENT ON COLUMN SG_CUR.T_SHOP.ACCFLAG IS 
'�Ƿ�������㣺1-��������0-��';

COMMENT ON COLUMN SG_CUR.T_SHOP.STATUS IS 
'�̻�״̬ 1-����2-����';

COMMENT ON COLUMN SG_CUR.T_SHOP.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_SHOP.CONTACTMAN IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SHOP.IDTYPE IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_SHOP.IDNO IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_SHOP.TEL IS 
'�绰';

COMMENT ON COLUMN SG_CUR.T_SHOP.MOBILE IS 
'�ֻ�';

COMMENT ON COLUMN SG_CUR.T_SHOP.EMAIL IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOP.BUSINESSADDR IS 
'��Ӫ��ַ';

COMMENT ON COLUMN SG_CUR.T_SHOP.ADDR IS 
'��ϵ��ַ';

COMMENT ON COLUMN SG_CUR.T_SHOP.ZIPCODE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOP.BOARDFEEFLAG IS 
'�Ƿ��մ���';

COMMENT ON COLUMN SG_CUR.T_SHOP.RAKEOFFTYPE IS 
'Ӷ������';

COMMENT ON COLUMN SG_CUR.T_SHOP.RAKEOFFRATE IS 
'Ӷ�����';

COMMENT ON COLUMN SG_CUR.T_SHOP.DEPOSITAGIO IS 
'����ۿ���';

COMMENT ON COLUMN SG_CUR.T_SHOP.DEPOSITCNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SHOP.DEPOSITAMT IS 
'����ܽ��';

COMMENT ON COLUMN SG_CUR.T_SHOP.DISCOUNTAMT IS 
'�ۿ��ܽ��';

COMMENT ON COLUMN SG_CUR.T_SHOP.BANKCODE IS 
'���д���';

COMMENT ON COLUMN SG_CUR.T_SHOP.BANKACCNO IS 
'�����ʺ�';

COMMENT ON COLUMN SG_CUR.T_SHOP.BANKACCNAME IS 
'�����ʻ���';

COMMENT ON COLUMN SG_CUR.T_SHOP.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOP.CLOSEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOP.USEFLAG IS 
'ʹ�ñ�־';

/*==============================================================*/
/* Table: T_CFGRAKEOFF                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGRAKEOFF 
(
   SHOPID               INTEGER                        NOT NULL,
   AMOUNT               NUMBER(15,2)                   NOT NULL,
   AGIO                 NUMBER(5,4),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGRAKEOFF PRIMARY KEY (SHOPID, AMOUNT),
   CONSTRAINT FK_CFGRAKEOFF_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID)
);

COMMENT ON TABLE SG_CUR.T_CFGRAKEOFF IS 
'�̻��ۿ������ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGRAKEOFF.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_CFGRAKEOFF.AMOUNT IS 
'�̻����';

COMMENT ON COLUMN SG_CUR.T_CFGRAKEOFF.AGIO IS 
'�ۿ۷�����';

COMMENT ON COLUMN SG_CUR.T_CFGRAKEOFF.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_CFGSHOPFEE                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGSHOPFEE 
(
   SHOPID               INTEGER                        NOT NULL,
   FEETYPE              INTEGER                        NOT NULL,
   FEERATE              NUMBER(5,4),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGSHOPFEE PRIMARY KEY (SHOPID, FEETYPE),
   CONSTRAINT FK_CFGSHOPFEE_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID),
   CONSTRAINT FK_CFGSHOPFEE_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGSHOPFEE IS 
'�̻�����ѷ��ʱ�';

COMMENT ON COLUMN SG_CUR.T_CFGSHOPFEE.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_CFGSHOPFEE.FEETYPE IS 
'���շ����';

COMMENT ON COLUMN SG_CUR.T_CFGSHOPFEE.FEERATE IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CFGSHOPFEE.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_CFGSHOPFEE.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CFGSPLIT                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGSPLIT 
(
   TRANSTYPE            INTEGER                        NOT NULL,
   FUNDTYPE             INTEGER                        NOT NULL,
   OFFLINEFLAG          INTEGER,
   USECARDFLAG          INTEGER,
   CALCCARDBAL          INTEGER,
   DRACCFLAG            CHAR(1)                        NOT NULL,
   DRSUBJNO             VARCHAR(20),
   DRACCNO              VARCHAR(10),
   CRACCFLAG            CHAR(1)                        NOT NULL,
   CRSUBJNO             VARCHAR(20),
   CRACCNO              VARCHAR(10),
   SUMMARY              VARCHAR(60),
   CONSTRAINT PK_T_CFGSPLIT PRIMARY KEY (TRANSTYPE, FUNDTYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGSPLIT IS 
'���׷�¼���ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.FUNDTYPE IS 
'�ʽ�����';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.OFFLINEFLAG IS 
'�ѻ���־1-�ѻ�0-����';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.USECARDFLAG IS 
'�����ױ�־';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.CALCCARDBAL IS 
'���㿨����־';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.DRACCFLAG IS 
'�跽��־';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.DRSUBJNO IS 
'�跽��Ŀ';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.DRACCNO IS 
'�跽�˺�';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.CRACCFLAG IS 
'������־';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.CRSUBJNO IS 
'������Ŀ';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.CRACCNO IS 
'�����˺�';

COMMENT ON COLUMN SG_CUR.T_CFGSPLIT.SUMMARY IS 
'ժҪ';

/*==============================================================*/
/* Table: T_CFGTRANS                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGTRANS 
(
   FEETYPE              INTEGER                        NOT NULL,
   TRANSCODE            INTEGER                        NOT NULL,
   TRANSTYPE            INTEGER                        NOT NULL,
   RATETYPE             INTEGER,
   RATEAMT              NUMBER(15,2),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_CFGTRANS PRIMARY KEY (FEETYPE, TRANSCODE, TRANSTYPE),
   CONSTRAINT FK_CFGTRANS_FEETYPE FOREIGN KEY (FEETYPE)
      REFERENCES SG_CUR.T_FEETYPE (FEETYPE),
   CONSTRAINT FK_CFGTRANS_TRANSTYPE FOREIGN KEY (TRANSTYPE)
      REFERENCES SG_CUR.T_TRANSTYPE (TRANSTYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGTRANS IS 
'�������ñ�';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.FEETYPE IS 
'�ͻ����շ����';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.RATETYPE IS 
'��������:1����- 2-�ٷֱ�3-��������Ϊ׼';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.RATEAMT IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CFGTRANS.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_CFGVER                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CFGVER 
(
   CFGTYPE              INTEGER                        NOT NULL,
   CFGVERNO             INTEGER                        NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CFGVER PRIMARY KEY (CFGTYPE)
);

COMMENT ON TABLE SG_CUR.T_CFGVER IS 
'���ð汾��';

COMMENT ON COLUMN SG_CUR.T_CFGVER.CFGTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CFGVER.CFGVERNO IS 
'���ð汾';

COMMENT ON COLUMN SG_CUR.T_CFGVER.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_CFGVER.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_CUSTIDCTL                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CUSTIDCTL 
(
   AREACODE             VARCHAR(3)                     NOT NULL,
   STARTNO              INTEGER                        NOT NULL,
   NEXTNO               INTEGER,
   ENDNO                INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_CUSTIDCTL PRIMARY KEY (AREACODE, STARTNO),
   CONSTRAINT FK_CUSTIDCTL_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_CUSTIDCTL IS 
'�ͻ��ſ��Ʊ�';

COMMENT ON COLUMN SG_CUR.T_CUSTIDCTL.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_CUSTIDCTL.STARTNO IS 
'�ͻ���ʼ��';

COMMENT ON COLUMN SG_CUR.T_CUSTIDCTL.NEXTNO IS 
'�ͻ���ǰ��';

COMMENT ON COLUMN SG_CUR.T_CUSTIDCTL.ENDNO IS 
'�ͻ�������';

COMMENT ON COLUMN SG_CUR.T_CUSTIDCTL.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Index: IDX_CUSTOMER_STUEMPNO                                 */
/*==============================================================*/
CREATE INDEX IDX_CUSTOMER_STUEMPNO ON SG_CUR.T_CUSTOMER (
STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_FEETYPE                                  */
/*==============================================================*/
CREATE INDEX IDX_CUSTOMER_FEETYPE ON SG_CUR.T_CUSTOMER (
FEETYPE ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_HOLDCARDCNT                              */
/*==============================================================*/
CREATE INDEX IDX_CUSTOMER_HOLDCARDCNT ON SG_CUR.T_CUSTOMER (
HOLDCARDCNT ASC
);

/*==============================================================*/
/* Index: IDX_CUSTOMER_DEPTCODE                                 */
/*==============================================================*/
CREATE INDEX IDX_CUSTOMER_DEPTCODE ON SG_CUR.T_CUSTOMER (
DEPTCODE ASC
);

/*==============================================================*/
/* Table: T_CUSTOMERTMP                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_CUSTOMERTMP 
(
   BATCHNO              VARCHAR(30)                    NOT NULL,
   SEQNO                INTEGER                        NOT NULL,
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
   UPDFLAG              NUMBER(1),
   SYNCFLAG             NUMBER(1)                      DEFAULT '0' NOT NULL,
   CHKFLAG              NUMBER(1)                      DEFAULT '0' NOT NULL,
   ERRMSG               VARCHAR(240)
);

COMMENT ON TABLE SG_CUR.T_CUSTOMERTMP IS 
'�ͻ���Ϣ��ʱ��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.BATCHNO IS 
'�������κŻ�ͬ��ʱ��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.SEQNO IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.OPERCODE IS 
'�������Ա';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.CUSTTYPE IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.CUSTTYPENAME IS 
'�ͻ��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.CUSTNAME IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.DEPTNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.SPECIALTYCODE IS 
'רҵ����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.CLASSNAME IS 
'�༶����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.IDTYPE IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.IDNO IS 
'֤������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.SEX IS 
'�Ա�';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.COUNTRY IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.NATION IS 
'����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.EMAIL IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.TEL IS 
'�绰';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.MOBILE IS 
'�ֻ�';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.ADDR IS 
'��ַ';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.ZIPCODE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.INDATE IS 
'��У����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.OUTDATE IS 
'��У����';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.UPDFLAG IS 
'���±�־';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.SYNCFLAG IS 
'1-ͬ������0-��ͬ������';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.CHKFLAG IS 
'0-δ���1-���ʧ��2���ͨ��';

COMMENT ON COLUMN SG_CUR.T_CUSTOMERTMP.ERRMSG IS 
'������Ϣ';

/*==============================================================*/
/* Index: IDX_CUSTTMP_SYNCFLAG                                  */
/*==============================================================*/
CREATE INDEX IDX_CUSTTMP_SYNCFLAG ON SG_CUR.T_CUSTOMERTMP (
SYNCFLAG ASC,
STUEMPNO ASC
);

/*==============================================================*/
/* Index: IDX_CUSTTMP_BATCHNO                                   */
/*==============================================================*/
CREATE INDEX IDX_CUSTTMP_BATCHNO ON SG_CUR.T_CUSTOMERTMP (
BATCHNO ASC,
SEQNO ASC
);

/*==============================================================*/
/* Table: T_DEPT                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DEPT 
(
   DEPTCODE             VARCHAR(30)                    NOT NULL,
   AREACODE             VARCHAR(3),
   DEPTNAME             VARCHAR(240),
   DEPTENAME            VARCHAR(240),
   DEPTFULLNAME         VARCHAR(1000),
   FDEPTCODE            VARCHAR(30),
   DEPTLEVEL            INTEGER,
   DEPTTYPE             NUMBER(1)                      DEFAULT '0',
   OLDDEPTCODE          VARCHAR(30),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DEPT PRIMARY KEY (DEPTCODE),
   CONSTRAINT FK_DEPT_DEPT FOREIGN KEY (FDEPTCODE)
      REFERENCES SG_CUR.T_DEPT (DEPTCODE),
   CONSTRAINT FK_DEPT_AREA FOREIGN KEY (AREACODE)
      REFERENCES SG_CUR.T_AREA (AREACODE)
);

COMMENT ON TABLE SG_CUR.T_DEPT IS 
'������Ϣ��';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_DEPT.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTENAME IS 
'����Ӣ����';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTFULLNAME IS 
'����ȫ��';

COMMENT ON COLUMN SG_CUR.T_DEPT.FDEPTCODE IS 
'�ϼ����Ŵ���';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTLEVEL IS 
'���ż���';

COMMENT ON COLUMN SG_CUR.T_DEPT.DEPTTYPE IS 
'0����1�༶';

COMMENT ON COLUMN SG_CUR.T_DEPT.OLDDEPTCODE IS 
'ԭ���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_DEPT.USEFLAG IS 
'ʹ�ñ�־:0-δʹ��1-��ʹ��';

COMMENT ON COLUMN SG_CUR.T_DEPT.LASTSAVED IS 
'��󱣴�����';

/*==============================================================*/
/* Table: T_DEPTTMP                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DEPTTMP 
(
   DEPTCODE             VARCHAR2(30)                   NOT NULL,
   AREACODE             VARCHAR2(3),
   DEPTNAME             VARCHAR2(240),
   DEPTENAME            VARCHAR2(240),
   DEPTFULLNAME         VARCHAR2(1000),
   FDEPTCODE            VARCHAR2(30),
   DEPTLEVEL            INTEGER,
   LASTSAVED            VARCHAR2(30),
   CONSTRAINT PK_T_DEPTTMP PRIMARY KEY (DEPTCODE)
);

COMMENT ON TABLE SG_CUR.T_DEPTTMP IS 
'������ʱ��';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.DEPTNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.DEPTENAME IS 
'����Ӣ����';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.DEPTFULLNAME IS 
'����ȫ��';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.FDEPTCODE IS 
'�ϼ����Ŵ���';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.DEPTLEVEL IS 
'���ż���';

COMMENT ON COLUMN SG_CUR.T_DEPTTMP.LASTSAVED IS 
'��󱣴�����';

/*==============================================================*/
/* Index: IDX_DEVPHYID                                          */
/*==============================================================*/
CREATE INDEX IDX_DEVPHYID ON SG_CUR.T_DEVICE (
DEVPHYID ASC
);

/*==============================================================*/
/* Table: T_DEVICETMP                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DEVICETMP 
(
   BATCHNO              VARCHAR(30)                    NOT NULL,
   SEQNO                INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_DEVICETMP IS 
'�豸��ʱ��';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.SEQNO IS 
'�������к�';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.OPERCODE IS 
'�������Ա';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.AREACODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVICENAME IS 
'�豸����';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVPHYID IS 
'�豸����ID��';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVPHYTYPE IS 
'�豸���̴���';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVTYPECODE IS 
'�豸���͡�';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVICENO IS 
'�豸����';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.FDEVICEID IS 
'�ϼ��豸ID';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.CARDPHYTYPE IS 
'�������ͺ�';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.COMMTYPE IS 
'ͨѶ��ʽ:1-����2-MODEM3-TCPIP 9-����';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.IP IS 
'IP��ַ';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.PORTNO IS 
'ͨѶ�˿ں�';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.SVRPORTNO IS 
'�������ӿڱ��';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.SVRPORTCNT IS 
'�˿�����';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.SYSID IS 
'ǰ�û�ϵͳID';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.DEVUSAGE IS 
'�豸��;';

COMMENT ON COLUMN SG_CUR.T_DEVICETMP.ERRMSG IS 
'������Ϣ';

/*==============================================================*/
/* Table: T_DEVMONITOR                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DEVMONITOR 
(
   DEVICEID             INTEGER                        NOT NULL,
   OPTIME               VARCHAR(30),
   COLTIME              VARCHAR(30),
   DEVTIME              VARCHAR(30),
   BEATSTATUS           INTEGER,
   CARDVERNO            VARCHAR(12),
   HARDISKPER           NUMBER,
   MEMORYPER            NUMBER,
   CPUPER               NUMBER,
   CONSTRAINT PK_T_DEVMONITOR PRIMARY KEY (DEVICEID),
   CONSTRAINT FK_DEVMONITOR_DEVICE FOREIGN KEY (DEVICEID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_DEVMONITOR IS 
'�豸��ر�';

COMMENT ON COLUMN SG_CUR.T_DEVMONITOR.DEVICEID IS 
'�ն˱��Ҳ���豸���';

COMMENT ON COLUMN SG_CUR.T_DEVMONITOR.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_DEVMONITOR.BEATSTATUS IS 
'����';

COMMENT ON COLUMN SG_CUR.T_DEVMONITOR.CARDVERNO IS 
'���汾��';

/*==============================================================*/
/* Table: T_DICTIONARY                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DICTIONARY 
(
   DICTTYPE             INTEGER                        NOT NULL,
   DICTTYPENAME         VARCHAR(60),
   DICTVAL              VARCHAR(30)                    NOT NULL,
   DICTCAPTION          VARCHAR(60),
   CONSTRAINT PK_T_DICTIONARY PRIMARY KEY (DICTTYPE, DICTVAL)
);

COMMENT ON TABLE SG_CUR.T_DICTIONARY IS 
'�����ֵ��';

COMMENT ON COLUMN SG_CUR.T_DICTIONARY.DICTTYPE IS 
'�ֵ�����';

COMMENT ON COLUMN SG_CUR.T_DICTIONARY.DICTTYPENAME IS 
'�ֵ���������';

COMMENT ON COLUMN SG_CUR.T_DICTIONARY.DICTVAL IS 
'�ֵ�ֵ';

COMMENT ON COLUMN SG_CUR.T_DICTIONARY.DICTCAPTION IS 
'�ֵ�����';

/*==============================================================*/
/* Table: T_DOORCARD                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORCARD 
(
   DEVICEID             INTEGER                        NOT NULL,
   CUSTID               INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   STATUS               NUMBER(1)                      NOT NULL,
   INSERTDATE           VARCHAR(14),
   CONSTRAINT PK_T_DOORCARD PRIMARY KEY (DEVICEID, CUSTID, CARDNO)
);

COMMENT ON TABLE SG_CUR.T_DOORCARD IS 
'�Ž���';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.CARDVERNO IS 
'�����汾��';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_DOORCARD.INSERTDATE IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORCARDADDR                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORCARDADDR 
(
   CARDADDR             INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   USEFLAG              CHAR(1),
   LISTID               INTEGER,
   CTRLID               INTEGER                        NOT NULL,
   ADDDELFLAG           NUMBER(1)                      NOT NULL,
   CONSTRAINT PK_T_DOORCARDADDR PRIMARY KEY (CARDADDR, CTRLID)
);

COMMENT ON TABLE SG_CUR.T_DOORCARDADDR IS 
'�Ž�����ַ';

COMMENT ON COLUMN SG_CUR.T_DOORCARDADDR.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_DOORCARDADDR.ADDDELFLAG IS 
'��ɾ��־';

/*==============================================================*/
/* Index: IDX_DCA_CARDNOCTRLID                                  */
/*==============================================================*/
CREATE INDEX IDX_DCA_CARDNOCTRLID ON SG_CUR.T_DOORCARDADDR (
CARDNO ASC,
CTRLID ASC
);

/*==============================================================*/
/* Index: IDX_DCA_LCA                                           */
/*==============================================================*/
CREATE INDEX IDX_DCA_LCA ON SG_CUR.T_DOORCARDADDR (
LISTID ASC,
CTRLID ASC,
ADDDELFLAG ASC
);

/*==============================================================*/
/* Index: IDX_DCA_USEFLAGCTRLID                                 */
/*==============================================================*/
CREATE INDEX IDX_DCA_USEFLAGCTRLID ON SG_CUR.T_DOORCARDADDR (
USEFLAG ASC,
CTRLID ASC
);

/*==============================================================*/
/* Table: T_DOORDEVCARDLIST                                     */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDEVCARDLIST 
(
   DEVICEID             INTEGER                        NOT NULL,
   CUSTID               INTEGER                        NOT NULL,
   WEEKID               INTEGER                        NOT NULL,
   HOLIDAYID            INTEGER,
   CARDNO               INTEGER,
   CARDPHYID            VARCHAR(16),
   CARDVERNO            VARCHAR(12),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER                        NOT NULL,
   DOWNTIME             VARCHAR(30),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVCARDLIST PRIMARY KEY (DEVICEID, CUSTID, WEEKID)
);

COMMENT ON TABLE SG_CUR.T_DOORDEVCARDLIST IS 
'�Ž��豸������';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.WEEKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.HOLIDAYID IS 
'�ڼ���ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.CARDVERNO IS 
'�����汾��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.ADDDELFLAG IS 
'��ɾ��־:1-��-2ɾ';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.DOWNTIME IS 
'�´�ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVCARDLIST.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVHOLIDAY                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDEVHOLIDAY 
(
   MAJORDEVID           NUMBER                         NOT NULL,
   MINORDEVID           INTEGER                        NOT NULL,
   HOLIDAYID            NUMBER                         NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVHOLIDAY PRIMARY KEY (MAJORDEVID, MINORDEVID, HOLIDAYID)
);

COMMENT ON TABLE SG_CUR.T_DOORDEVHOLIDAY IS 
'�Ž��豸�ڼ��ձ�';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.MAJORDEVID IS 
'���豸ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.MINORDEVID IS 
'���豸ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.HOLIDAYID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.SEQNO IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.DOWNTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVHOLIDAY.UPDATETIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVTIME                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDEVTIME 
(
   MAJORDEVID           INTEGER                        NOT NULL,
   MINORDEVID           INTEGER                        NOT NULL,
   TIMEID               INTEGER                        NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVTIME PRIMARY KEY (MAJORDEVID, MINORDEVID, TIMEID)
);

COMMENT ON TABLE SG_CUR.T_DOORDEVTIME IS 
'�Ž��豸ʱ��α�';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIME.TIMEID IS 
'ʱ���ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIME.SEQNO IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIME.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIME.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIME.DOWNTIME IS 
'�´�ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVTIMEGRP                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDEVTIMEGRP 
(
   MAJORDEVID           INTEGER                        NOT NULL,
   MINORDEVID           INTEGER                        NOT NULL,
   TIMEGRPID            INTEGER                        NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVTIMEGRP PRIMARY KEY (MAJORDEVID, MINORDEVID, TIMEGRPID)
);

COMMENT ON TABLE SG_CUR.T_DOORDEVTIMEGRP IS 
'�Ž��豸ʱ�����';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.TIMEGRPID IS 
'ʱ�����ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.SEQNO IS 
'��ˮ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.DOWNTIME IS 
'�´�ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.REFCNT IS 
'���ô���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVTIMEGRP.UPDATETIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDEVWEEK                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDEVWEEK 
(
   MAJORDEVID           INTEGER                        NOT NULL,
   MINORDEVID           INTEGER                        NOT NULL,
   WEEKID               INTEGER                        NOT NULL,
   SEQNO                INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   DOWNTIME             VARCHAR(30),
   REFCNT               INTEGER,
   LINKCNT              INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORDEVWEEK PRIMARY KEY (MAJORDEVID, MINORDEVID, WEEKID)
);

COMMENT ON TABLE SG_CUR.T_DOORDEVWEEK IS 
'�Ž��豸��ʱ���';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.WEEKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.SEQNO IS 
'��ˮ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.DOWNTIME IS 
'�´�ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDEVWEEK.UPDATETIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORDOWNLOAD                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDOWNLOAD 
(
   ID                   INTEGER                        NOT NULL,
   CARDVERNO            VARCHAR(12),
   CUSTID               INTEGER                        NOT NULL,
   CTRLID               INTEGER                        NOT NULL,
   SYSID                INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   CARDPHYID            VARCHAR(16)                    NOT NULL,
   RIGHTBIT             VARCHAR(240),
   CARDSEQNO            INTEGER                        NOT NULL,
   WEEKID               INTEGER                        NOT NULL,
   WEEKSEQNO            INTEGER                        NOT NULL,
   HOLIDAYID            INTEGER                        NOT NULL,
   HOLIDAYSEQNO         INTEGER                        NOT NULL,
   CREATETIME           VARCHAR(30)                    NOT NULL,
   SUCCTIME             VARCHAR(30),
   STATUS               NUMBER(1)                      NOT NULL,
   ADDDELFLAG           NUMBER(1)                      NOT NULL,
   DOORCOUNT            INTEGER,
   CONSTRAINT PK_T_DOORDOWNLOAD PRIMARY KEY (ID)
);

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.ID IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.CARDVERNO IS 
'�����汾��';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.RIGHTBIT IS 
'Ȩ��';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_DOORDOWNLOAD.ADDDELFLAG IS 
'��ɾ��־';

/*==============================================================*/
/* Index: IDX_DOORDL                                            */
/*==============================================================*/
CREATE INDEX IDX_DOORDL ON SG_CUR.T_DOORDOWNLOAD (
CARDVERNO ASC,
CTRLID ASC
);

/*==============================================================*/
/* Table: T_DOORDTL                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORDTL 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20)                    NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_DOORDTL IS 
'�Ž���ˮ��';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.DEVSEQNO IS 
'��ˮ��';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.CUSTNAME IS 
'�ͻ�����';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.TRANSMARK IS 
'���ױ��';

COMMENT ON COLUMN SG_CUR.T_DOORDTL.SYSID IS 
'��ϵͳID';

/*==============================================================*/
/* Table: T_DOOREVENTDTL                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOOREVENTDTL 
(
   DEVICEID             INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6)                     NOT NULL,
   EVENTCODE            INTEGER                        NOT NULL,
   EVENTMSG             VARCHAR(240),
   SYSID                INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   CONSTRAINT PK_T_DOOREVENTDTL PRIMARY KEY (DEVICEID, TRANSDATE, TRANSTIME, EVENTCODE)
);

COMMENT ON TABLE SG_CUR.T_DOOREVENTDTL IS 
'�Ž��¼���ˮ��';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.EVENTCODE IS 
'�¼�����';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.EVENTMSG IS 
'�¼���Ϣ';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_DOOREVENTDTL.COLTIME IS 
'�ɼ�ʱ��';

/*==============================================================*/
/* Table: T_DOORGROUP                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORGROUP 
(
   GROUPID              INTEGER                        NOT NULL,
   GROUPNAME            VARCHAR(60),
   STATUS               CHAR(1),
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGROUP PRIMARY KEY (GROUPID)
);

COMMENT ON TABLE SG_CUR.T_DOORGROUP IS 
'�Ž����';

COMMENT ON COLUMN SG_CUR.T_DOORGROUP.GROUPID IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORGROUP.GROUPNAME IS 
'������';

COMMENT ON COLUMN SG_CUR.T_DOORGROUP.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_DOORGROUP.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORGRPMEMBER                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORGRPMEMBER 
(
   GROUPID              INTEGER                        NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGRPMEMBER PRIMARY KEY (GROUPID, DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_DOORGRPMEMBER IS 
'�Ž����Ա';

COMMENT ON COLUMN SG_CUR.T_DOORGRPMEMBER.GROUPID IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORGRPMEMBER.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOORGRPMEMBER.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORGRPOPERRIGHT                                    */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORGRPOPERRIGHT 
(
   GROUPID              INTEGER                        NOT NULL,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORGRPOPERRIGHT PRIMARY KEY (GROUPID, OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_DOORGRPOPERRIGHT IS 
'�Ž������ԱȨ��';

COMMENT ON COLUMN SG_CUR.T_DOORGRPOPERRIGHT.GROUPID IS 
'���';

COMMENT ON COLUMN SG_CUR.T_DOORGRPOPERRIGHT.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DOORGRPOPERRIGHT.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORHOLIDAY                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORHOLIDAY 
(
   HOLIDAYID            INTEGER                        NOT NULL,
   HOLIDAYNAME          VARCHAR(60),
   DAYCNT               INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORHOLIDAY PRIMARY KEY (HOLIDAYID)
);

COMMENT ON TABLE SG_CUR.T_DOORHOLIDAY IS 
'�Ž��ڼ��ձ�';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.HOLIDAYID IS 
'�ڼ���ID';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.HOLIDAYNAME IS 
'�ڼ�����';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.DAYCNT IS 
'�ڼ�������';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAY.UPDATETIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOORHOLIDAYTIME                                     */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORHOLIDAYTIME 
(
   HOLIDAYID            INTEGER                        NOT NULL,
   HOLIDAYDATE          VARCHAR(8)                     NOT NULL,
   TIMEGRPID            INTEGER,
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORHOLIDAYTIME PRIMARY KEY (HOLIDAYID, HOLIDAYDATE)
);

COMMENT ON TABLE SG_CUR.T_DOORHOLIDAYTIME IS 
'�Ž��ڼ���ʱ��α�';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAYTIME.TIMEGRPID IS 
'ʱ����ID';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAYTIME.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAYTIME.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORHOLIDAYTIME.UPDATETIME IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DOOROPERRIGHT                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOOROPERRIGHT 
(
   DEVICEID             INTEGER                        NOT NULL,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOOROPERRIGHT PRIMARY KEY (DEVICEID, OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_DOOROPERRIGHT IS 
'�Ž�����ԱȨ��';

COMMENT ON COLUMN SG_CUR.T_DOOROPERRIGHT.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOOROPERRIGHT.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DOOROPERRIGHT.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORRPTDAY                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORRPTDAY 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   TOTALCNT             INTEGER,
   VALIDCNT             NUMBER,
   INVALIDCNT           INTEGER,
   CONSTRAINT PK_T_DOORRPTDAY PRIMARY KEY (TRANSDATE, DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_DOORRPTDAY IS 
'�Ž�����';

COMMENT ON COLUMN SG_CUR.T_DOORRPTDAY.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DOORRPTDAY.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DOORRPTDAY.TOTALCNT IS 
'�ܴ���';

/*==============================================================*/
/* Table: T_DOORTIME                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORTIME 
(
   TIMEID               INTEGER                        NOT NULL,
   TIMENAME             VARCHAR(60),
   STARTTIME            VARCHAR(6),
   ENDTIME              VARCHAR(6),
   ADDDELFLAG           NUMBER(1),
   DOWNSTATUS           INTEGER,
   UPDATETIME           VARCHAR(30),
   CONSTRAINT PK_T_DOORTIME PRIMARY KEY (TIMEID)
);

COMMENT ON TABLE SG_CUR.T_DOORTIME IS 
'�Ž�ʱ��β�����';

COMMENT ON COLUMN SG_CUR.T_DOORTIME.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORTIME.DOWNSTATUS IS 
'�´�״̬';

/*==============================================================*/
/* Table: T_DOORTIMEGRP                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORTIMEGRP 
(
   TIMEGRPID            INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_DOORTIMEGRP IS 
'�Ž�ʱ����鶨���';

COMMENT ON COLUMN SG_CUR.T_DOORTIMEGRP.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORTIMEGRP.DOWNSTATUS IS 
'�´�״̬';

COMMENT ON COLUMN SG_CUR.T_DOORTIMEGRP.UPDATETIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_DOORWEEKTIME                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DOORWEEKTIME 
(
   WEEKID               INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_DOORWEEKTIME IS 
'�Ž���ʱ���';

COMMENT ON COLUMN SG_CUR.T_DOORWEEKTIME.WEEKID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_DOORWEEKTIME.ADDDELFLAG IS 
'��ɾ��־';

COMMENT ON COLUMN SG_CUR.T_DOORWEEKTIME.DOWNSTATUS IS 
'�´�״̬';

/*==============================================================*/
/* Table: T_DPSOPER                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DPSOPER 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
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
   BATCHNO              INTEGER,
   AUTHCODE             INTEGER,
   DEVPHYID             VARCHAR(20),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSOPER PRIMARY KEY (OPERCODE),
   CONSTRAINT FK_DPSOPER_OPERATOR FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_OPERATOR (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_DPSOPER IS 
'��ֵ����Ա��';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.DEVLIMITFLAG IS 
'ʹ�����Ʊ�־';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.SHOPOPERFLAG IS 
'��ֵ�̻�����Ա��־';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.MAXDEPOSITAMT IS 
'����ֵ���';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.DEPOSITCNT IS 
'�ܳ�ֵ����';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.DEPOSITAMT IS 
'�ܳ�ֵ���';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.LASTTRANSDATE IS 
'����ֵ����';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.LASTDEVPHYID IS 
'����ֵ�豸����ID';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.LASTDEVSEQNO IS 
'�ϴ��豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.BATCHNO IS 
'��ֵ���κ�';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.AUTHCODE IS 
'��Ȩ��';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_DPSOPER.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DPSOPERCARD                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DPSOPERCARD 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   DISABLEFLAG          NUMBER(1)                      NOT NULL,
   OPENOPER             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSOPERCARD PRIMARY KEY (OPERCODE),
   CONSTRAINT FK_DPSOPERCARD_OPERATOR FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_OPERATOR (OPERCODE)
);

COMMENT ON COLUMN SG_CUR.T_DPSOPERCARD.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DPSOPERCARD.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_DPSOPERCARD.DISABLEFLAG IS 
'0-����1-����';

COMMENT ON COLUMN SG_CUR.T_DPSOPERCARD.OPENOPER IS 
'�󶨲���Ա';

COMMENT ON COLUMN SG_CUR.T_DPSOPERCARD.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DPSOPERPOS                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DPSOPERPOS 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   OPENOPER             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSOPERPOS PRIMARY KEY (OPERCODE, DEVICEID),
   CONSTRAINT FK_DPSOPERPOS_DEVICE FOREIGN KEY (DEVICEID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID),
   CONSTRAINT FK_DPSOPERPOS_DPSOPER FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_DPSOPER (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_DPSOPERPOS IS 
'��ֵ����Ա�豸��';

COMMENT ON COLUMN SG_CUR.T_DPSOPERPOS.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DPSOPERPOS.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_DPSOPERPOS.OPENOPER IS 
'ע�����Ա';

COMMENT ON COLUMN SG_CUR.T_DPSOPERPOS.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_DPSSHOPPOS                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_DPSSHOPPOS 
(
   DEVICEID             INTEGER                        NOT NULL,
   SHOPID               INTEGER                        NOT NULL,
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_DPSSHOPPOS PRIMARY KEY (DEVICEID),
   CONSTRAINT FK_DPSSHOPPOS_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID),
   CONSTRAINT FK_DPSSHOPPOS_DEVICE FOREIGN KEY (DEVICEID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_DPSSHOPPOS IS 
'��ֵ�̻�POS��';

COMMENT ON COLUMN SG_CUR.T_DPSSHOPPOS.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_DPSSHOPPOS.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_DPSSHOPPOS.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_DPSSHOPPOS.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_ERR_ACCOUNT                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ERR_ACCOUNT 
(
   CARDNO               INTEGER,
   TOTALNUM             INTEGER,
   LOSTCNTDETAIL        VARCHAR2(1000)
);

COMMENT ON TABLE SG_CUR.T_ERR_ACCOUNT IS 
'ȱʧ��ˮ���ܱ�';

/*==============================================================*/
/* Table: T_ERR_ACCOUNT_TMP                                     */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ERR_ACCOUNT_TMP 
(
   CARDNO               INTEGER
);

COMMENT ON TABLE SG_CUR.T_ERR_ACCOUNT_TMP IS 
'ȱʧ��ˮ�����м��';

/*==============================================================*/
/* Table: T_ERR_WRITECARD                                       */
/*==============================================================*/
CREATE TABLE T_ERR_WRITECARD 
(
   ACCDATE              VARCHAR2(8),
   ACCTIME              VARCHAR2(6),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   TRANSDATE            VARCHAR2(8),
   TRANSDATE1           VARCHAR2(8),
   TRANSTIME            VARCHAR2(6),
   TRANSTIME1           VARCHAR2(6),
   TRANSCODE            INTEGER,
   TRANSCODE1           INTEGER,
   CARDNO               INTEGER,
   CARDCNT              INTEGER,
   CARDCNT1             INTEGER,
   CARDBEFBAL           NUMERIC(38,2),
   CARDAFTBAL           NUMERIC(38,2),
   CARDBEFBAL1          NUMERIC(38,2),
   CARDAFTBAL1          NUMERIC(38,2),
   AMOUNT               NUMERIC(38,2),
   DEVPHYID             VARCHAR2(20),
   DEVSEQNO             INTEGER,
   STATUS               CHAR(1),
   ERRCODE              INTEGER,
   CARDBAL              NUMERIC(38,2),
   AVAILBAL             NUMERIC(38,2)
);

COMMENT ON TABLE T_ERR_WRITECARD IS 
'Ȧ��д��ʧ�ܷ��������';

/*==============================================================*/
/* Table: T_EXCEPTDTL                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_EXCEPTDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
   REFNO                NUMBER(14)                     NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   PURSENO              INTEGER                        NOT NULL,
   DPSCNT               INTEGER                        NOT NULL,
   PAYCNT               INTEGER                        NOT NULL,
   CARDBEFBAL           NUMBER(15,2)                   NOT NULL,
   CARDAFTBAL           NUMBER(15,2)                   NOT NULL,
   FAILTYPE             NUMBER(1),
   STATUS               NUMBER(1)                      NOT NULL,
   REMARK               VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_EXCEPTDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
);

COMMENT ON TABLE SG_CUR.T_EXCEPTDTL IS 
'�쳣����ˮ';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.DPSCNT IS 
'����ֵ����';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.PAYCNT IS 
'�����Ѵ���';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.CARDBEFBAL IS 
'������ǰ���';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.CARDAFTBAL IS 
'�����׺����';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.FAILTYPE IS 
'0-��;�ο�1д��ʧ��';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.STATUS IS 
'0-δ����2ʧ��3�ɹ�';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_EXCEPTDTL.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_EXTCARDDTL                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_EXTCARDDTL 
(
   REFNO                NUMBER(14)                     NOT NULL,
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   CARDNO               INTEGER                        NOT NULL,
   AMOUNT               INTEGER,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   STATUS               NUMBER(1)                      NOT NULL,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_EXTCARDDTL PRIMARY KEY (REFNO)
);

COMMENT ON TABLE SG_CUR.T_EXTCARDDTL IS 
'��д����ˮ��';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.CARDNO IS 
'��Ϊ��Ǯ��Ϊ��Ǯ';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.AMOUNT IS 
'��д���';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.STATUS IS 
'1δ��д2�Ѳ�д3���²���';

COMMENT ON COLUMN SG_CUR.T_EXTCARDDTL.REMARK IS 
'��дԭ��';

/*==============================================================*/
/* Table: T_FRONT                                               */
/*==============================================================*/
CREATE TABLE SG_CUR.T_FRONT 
(
   FRONTID              INTEGER                        NOT NULL,
   FRONTNAME            VARCHAR(60),
   IP                   VARCHAR(15),
   DRTPPORT             INTEGER                        DEFAULT 4000,
   DRTPNODE             NUMBER,
   BCCMAINFUNCNO        INTEGER,
   CONSTRAINT PK_T_FRONT PRIMARY KEY (FRONTID)
);

COMMENT ON TABLE SG_CUR.T_FRONT IS 
'ǰ�û���Ϣ��';

COMMENT ON COLUMN SG_CUR.T_FRONT.FRONTID IS 
'ǰ�û����';

COMMENT ON COLUMN SG_CUR.T_FRONT.FRONTNAME IS 
'ǰ�û�����';

COMMENT ON COLUMN SG_CUR.T_FRONT.IP IS 
'IP��ַ';

COMMENT ON COLUMN SG_CUR.T_FRONT.DRTPPORT IS 
'DRTP�˿�';

COMMENT ON COLUMN SG_CUR.T_FRONT.DRTPNODE IS 
'DRTP�ڵ��';

COMMENT ON COLUMN SG_CUR.T_FRONT.BCCMAINFUNCNO IS 
'BCC�����ܺ�';

/*==============================================================*/
/* Table: T_FUNCTIONALITY                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_FUNCTIONALITY 
(
   ID                   INTEGER                        NOT NULL,
   PID                  INTEGER,
   NAME                 VARCHAR(60),
   SUPPORTED_ACTION     INTEGER,
   TARGET_PLUGIN        VARCHAR(60),
   FUNC_LEVEL           INTEGER,
   APP                  VARCHAR(30),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_FUNCTIONALITY PRIMARY KEY (ID),
   CONSTRAINT FK_FUNCTIONALITY_FUNCTIONALITY FOREIGN KEY (PID)
      REFERENCES SG_CUR.T_FUNCTIONALITY (ID)
);

COMMENT ON TABLE SG_CUR.T_FUNCTIONALITY IS 
'ϵͳ����';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.ID IS 
'ID';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.PID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.NAME IS 
'����';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.SUPPORTED_ACTION IS 
'֧�ֵ���Ȩ����ֵ';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.TARGET_PLUGIN IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.FUNC_LEVEL IS 
'����';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.APP IS 
'����ϵͳ';

COMMENT ON COLUMN SG_CUR.T_FUNCTIONALITY.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_GETELECCARD                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_GETELECCARD 
(
   CARDNO               INTEGER                        NOT NULL,
   CARDPHYID            VARCHAR(16)                    NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   USETYPE              NUMBER(1)                      NOT NULL,
   ADDDELFLAG           NUMBER(1)                      NOT NULL,
   DOWNTIME             VARCHAR(30),
   CONSTRAINT PK_T_GETELECCARD PRIMARY KEY (CARDNO, DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_GETELECCARD IS 
'ȡ�翨��';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.USETYPE IS 
'0-����-1-������';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.ADDDELFLAG IS 
'1-����2-ɾ��';

COMMENT ON COLUMN SG_CUR.T_GETELECCARD.DOWNTIME IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_INNERACC                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_INNERACC 
(
   ACCNO                VARCHAR(10)                    NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   BALFLAG              NUMBER(1),
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   CONSTRAINT PK_T_INNERACC PRIMARY KEY (ACCNO)
);

COMMENT ON TABLE SG_CUR.T_INNERACC IS 
'�ڲ��ʻ���';

COMMENT ON COLUMN SG_CUR.T_INNERACC.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_INNERACC.ACCNAME IS 
'�ʻ���';

COMMENT ON COLUMN SG_CUR.T_INNERACC.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_INNERACC.YDAYBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_INNERACC.BALANCE IS 
'�ʻ����';

COMMENT ON COLUMN SG_CUR.T_INNERACC.BALFLAG IS 
'����';

COMMENT ON COLUMN SG_CUR.T_INNERACC.LASTTRANSDATE IS 
'�ϴν�������';

COMMENT ON COLUMN SG_CUR.T_INNERACC.LASTACCDATE IS 
'�ϴ���������';

/*==============================================================*/
/* Table: T_KEYS                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_KEYS 
(
   KEYID                INTEGER                        NOT NULL,
   KEYVAL               VARCHAR(64),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_KEYS PRIMARY KEY (KEYID)
);

COMMENT ON TABLE SG_CUR.T_KEYS IS 
'CPU����Կ��';

COMMENT ON COLUMN SG_CUR.T_KEYS.KEYID IS 
'��ԿID';

COMMENT ON COLUMN SG_CUR.T_KEYS.KEYVAL IS 
'��Կֵ';

COMMENT ON COLUMN SG_CUR.T_KEYS.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_MACHINECODE                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_MACHINECODE 
(
   MACHINECODE          VARCHAR(60)                    NOT NULL,
   IP                   VARCHAR(15),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_MACHINECODE PRIMARY KEY (MACHINECODE)
);

COMMENT ON TABLE SG_CUR.T_MACHINECODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_MACHINECODE.MACHINECODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_MACHINECODE.IP IS 
'IP��ַ';

COMMENT ON COLUMN SG_CUR.T_MACHINECODE.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_MEALTYPE                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_MEALTYPE 
(
   MEALTYPE             INTEGER                        NOT NULL,
   MEALNAME             VARCHAR(30)                    NOT NULL,
   ENDTIME              VARCHAR(6)                     NOT NULL,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_MEALTYPE PRIMARY KEY (MEALTYPE)
);

COMMENT ON TABLE SG_CUR.T_MEALTYPE IS 
'�ʹ�����';

COMMENT ON COLUMN SG_CUR.T_MEALTYPE.MEALTYPE IS 
'�ʹ�ID';

COMMENT ON COLUMN SG_CUR.T_MEALTYPE.MEALNAME IS 
'�ʹ�����';

COMMENT ON COLUMN SG_CUR.T_MEALTYPE.ENDTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_MEALTYPE.LASTSAVED IS 
'����ʱ��';

/*==============================================================*/
/* Table: T_MESSAGE_CODE                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_MESSAGE_CODE 
(
   RET_CODE             INTEGER                        NOT NULL,
   RET_MSG              VARCHAR(240),
   CONSTRAINT PK_T_MESSAGE_CODE PRIMARY KEY (RET_CODE)
);

COMMENT ON TABLE SG_CUR.T_MESSAGE_CODE IS 
'������Ϣ���';

COMMENT ON COLUMN SG_CUR.T_MESSAGE_CODE.RET_CODE IS 
'��Ϣ��';

COMMENT ON COLUMN SG_CUR.T_MESSAGE_CODE.RET_MSG IS 
'��Ϣ';

/*==============================================================*/
/* Table: T_MODIFYINFO                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_MODIFYINFO 
(
   CUSTID               INTEGER                        NOT NULL,
   STUEMPNO             VARCHAR(20)                    NOT NULL,
   ENROLLNO             VARCHAR(30)                    NOT NULL,
   MODIFYDATE           VARCHAR(8),
   MODIFYTIME           VARCHAR(6),
   CONSTRAINT PK_T_MODIFYINFO PRIMARY KEY (CUSTID, ENROLLNO),
   CONSTRAINT FK_MODIFYINFO_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID)
);

COMMENT ON TABLE SG_CUR.T_MODIFYINFO IS 
'ѧ���޸���Ϣ��';

COMMENT ON COLUMN SG_CUR.T_MODIFYINFO.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_MODIFYINFO.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_MODIFYINFO.ENROLLNO IS 
'¼ȡ֪ͨ��';

COMMENT ON COLUMN SG_CUR.T_MODIFYINFO.MODIFYDATE IS 
'�޸�����';

COMMENT ON COLUMN SG_CUR.T_MODIFYINFO.MODIFYTIME IS 
'�޸�ʱ��';

/*==============================================================*/
/* Table: T_MSGLIST                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_MSGLIST 
(
   MSGID                INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_MSGLIST PRIMARY KEY (MSGID),
   CONSTRAINT FK_MSGLIST_DEVICE FOREIGN KEY (DEVICEID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID),
   CONSTRAINT FK_MSGLIST_SUBSYS FOREIGN KEY (SYSID)
      REFERENCES SG_CUR.T_SUBSYSTEM (SYSID)
);

COMMENT ON TABLE SG_CUR.T_MSGLIST IS 
'��Ϣ���б�';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.MSGID IS 
'��ϢID';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.MSGTYPE IS 
'��Ϣ����';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.MSGLEVEL IS 
'��Ϣ����';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.SYSID IS 
'��ϵͳ���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.CREATEDTIME IS 
'��Ϣ����ʱ��';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.STARTTIME IS 
'��Ϣ��ʼ����ʱ��';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.ENDTIME IS 
'��Ϣ�������ʱ��';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.REQDATA IS 
'��Ϣ��������';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.RESPDATA IS 
'��ϢӦ������';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.FUNCNO IS 
'���ܺ�';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.PFUNCNO IS 
'�����ܺ�';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.MAXSENDCNT IS 
'����ʹ���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.SENDCNT IS 
'���ʹ���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.RECVCNT IS 
'���մ���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.STATUS IS 
'��Ϣ״̬';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.SEQNO IS 
'���';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.ERRMSG IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_MSGLIST.DELFLAG IS 
'ɾ����־';

/*==============================================================*/
/* Index: IDX_MSGLIST_DEVICEID                                  */
/*==============================================================*/
CREATE INDEX IDX_MSGLIST_DEVICEID ON SG_CUR.T_MSGLIST (
DEVICEID ASC
);

/*==============================================================*/
/* Table: T_NETACC                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_NETACC 
(
   ACCNO                VARCHAR(10)                    NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   ACCPWD               VARCHAR(64),
   CUSTID               INTEGER,
   STOPPAYFLAG          INTEGER,
   STATUS               CHAR(1),
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   AVAILBAL             NUMBER(15,2),
   FROZEBAL             NUMBER(15,2),
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   PAYPWD               VARCHAR(64),
   FAILEDCNT            INTEGER,
   LASTLOGINTIME        VARCHAR(14),
   LASTBLOCKTIME        VARCHAR(14),
   LASTUNBLOCKTIME      VARCHAR(14),
   CONSTRAINT PK_T_NETACC PRIMARY KEY (ACCNO)
);

COMMENT ON TABLE SG_CUR.T_NETACC IS 
'�����ʻ���';

COMMENT ON COLUMN SG_CUR.T_NETACC.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_NETACC.ACCNAME IS 
'�ʻ���';

COMMENT ON COLUMN SG_CUR.T_NETACC.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_NETACC.ACCPWD IS 
'�ʻ�����';

COMMENT ON COLUMN SG_CUR.T_NETACC.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_NETACC.STOPPAYFLAG IS 
'ֹ����־';

COMMENT ON COLUMN SG_CUR.T_NETACC.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_NETACC.YDAYBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_NETACC.BALANCE IS 
'�ʻ����';

COMMENT ON COLUMN SG_CUR.T_NETACC.AVAILBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_NETACC.FROZEBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_NETACC.LASTTRANSDATE IS 
'�ϴν�������';

COMMENT ON COLUMN SG_CUR.T_NETACC.LASTACCDATE IS 
'�ϴ���������';

COMMENT ON COLUMN SG_CUR.T_NETACC.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_NETACC.CLOSEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_NETACC.PAYPWD IS 
'֧������';

COMMENT ON COLUMN SG_CUR.T_NETACC.FAILEDCNT IS 
'��½ʧ�ܴ���';

COMMENT ON COLUMN SG_CUR.T_NETACC.LASTLOGINTIME IS 
'����½�ɹ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_NETACC.LASTBLOCKTIME IS 
'�������ʱ��';

COMMENT ON COLUMN SG_CUR.T_NETACC.LASTUNBLOCKTIME IS 
'������ʱ��';

/*==============================================================*/
/* Table: T_NEWCAPEC_CARD                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_NEWCAPEC_CARD 
(
   CARDPHYNO            VARCHAR2(16)                   NOT NULL,
   APPTYPE              INTEGER,
   FEETYPE              INTEGER,
   CUSTTYPE             INTEGER,
   CUSTID               INTEGER,
   IDTYPE               INTEGER,
   DPSCNT               INTEGER,
   TRANSDATE            INTEGER,
   DAYMAXAMT            INTEGER,
   PUBLISHID            INTEGER,
   SHOWCARDNO           INTEGER,
   SUBSIDYNO            INTEGER,
   CARDSTRUCT           INTEGER,
   SCHOOLCODE           INTEGER,
   CONSTRAINT PK_T_NEWCAPEC_CARD PRIMARY KEY (CARDPHYNO)
);

COMMENT ON TABLE SG_CUR.T_NEWCAPEC_CARD IS 
'�¿����û�����';

/*==============================================================*/
/* Table: T_NEWCARDCHANGE                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_NEWCARDCHANGE 
(
   SHOWCARDNO           VARCHAR(10)                    NOT NULL,
   STUEMPNO             VARCHAR(20)                    NOT NULL,
   EXPIREDATE           VARCHAR(8)                     NOT NULL,
   STATUS               NUMBER(1)                      NOT NULL,
   BATCHNO              VARCHAR(30),
   SEQNO                INTEGER,
   CARDPHYID            VARCHAR(16),
   OLDCARDPHYID         VARCHAR(16),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_NEWCARDCHANGE PRIMARY KEY (SHOWCARDNO)
);

COMMENT ON TABLE SG_CUR.T_NEWCARDCHANGE IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.STUEMPNO IS 
'ѧ��';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.EXPIREDATE IS 
'����Ч��';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.BATCHNO IS 
'���κ�';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.SEQNO IS 
'˳���';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.OLDCARDPHYID IS 
'�ɿ�����ID';

COMMENT ON COLUMN SG_CUR.T_NEWCARDCHANGE.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Index: INDEX_NEWCARDCHG_BATCHNO                              */
/*==============================================================*/
CREATE INDEX INDEX_NEWCARDCHG_BATCHNO ON SG_CUR.T_NEWCARDCHANGE (
BATCHNO ASC,
SEQNO ASC
);

/*==============================================================*/
/* Table: T_ROLE                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_ROLE 
(
   ID                   INTEGER                        NOT NULL,
   NAME                 VARCHAR(240),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_ROLE PRIMARY KEY (ID)
);

COMMENT ON TABLE SG_CUR.T_ROLE IS 
'��ɫ';

COMMENT ON COLUMN SG_CUR.T_ROLE.ID IS 
'��ɫID';

COMMENT ON COLUMN SG_CUR.T_ROLE.NAME IS 
'��ɫ����';

COMMENT ON COLUMN SG_CUR.T_ROLE.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_OPERATOR_ROLE                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_OPERATOR_ROLE 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   ROLE_ID              INTEGER                        NOT NULL,
   CONSTRAINT PK_T_OPERATOR_ROLE PRIMARY KEY (OPERCODE, ROLE_ID),
   CONSTRAINT FK_OPERATOR_ROLE_ROLE FOREIGN KEY (ROLE_ID)
      REFERENCES SG_CUR.T_ROLE (ID),
   CONSTRAINT FK_OPERATOR_ROLE_OPERATOR FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_OPERATOR (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_OPERATOR_ROLE IS 
'����Ա��ɫ������';

COMMENT ON COLUMN SG_CUR.T_OPERATOR_ROLE.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_OPERATOR_ROLE.ROLE_ID IS 
'��ɫ���';

/*==============================================================*/
/* Table: T_OPERAUTH                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_OPERAUTH 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   AUTHTYPE             INTEGER                        NOT NULL,
   AUTHORIZER           VARCHAR(8),
   AUTHDATE             VARCHAR(8),
   CONSTRAINT PK_T_OPERAUTH PRIMARY KEY (OPERCODE, AUTHTYPE)
);

COMMENT ON TABLE SG_CUR.T_OPERAUTH IS 
'����Ա��Ȩ��';

COMMENT ON COLUMN SG_CUR.T_OPERAUTH.OPERCODE IS 
'����Ա';

COMMENT ON COLUMN SG_CUR.T_OPERAUTH.AUTHTYPE IS 
'Ȩ�޴���';

COMMENT ON COLUMN SG_CUR.T_OPERAUTH.AUTHORIZER IS 
'��Ȩ��';

COMMENT ON COLUMN SG_CUR.T_OPERAUTH.AUTHDATE IS 
'��Ȩ����';

/*==============================================================*/
/* Table: T_OPERDTL                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_OPERDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   TRANSCODE            INTEGER,
   CHKOPER              VARCHAR(8),
   STATUS               CHAR(1),
   TRANSINFO            VARCHAR(480),
   REQDATA              VARCHAR(1000),
   CONSTRAINT PK_T_OPERDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO)
);

COMMENT ON TABLE SG_CUR.T_OPERDTL IS 
'����Ա������ˮ��';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TERMID IS 
'վ���';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TERMSEQNO IS 
'վ����ˮ��';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.CHKOPER IS 
'��˲���Ա';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.STATUS IS 
'��ˮ״̬1-δ����2-ʧ��3-�ɹ�4-����';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.TRANSINFO IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_OPERDTL.REQDATA IS 
'��������';

/*==============================================================*/
/* Table: T_SITE                                                */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SITE 
(
   SITENO               INTEGER                        NOT NULL,
   SITENAME             VARCHAR(60),
   IP                   VARCHAR(15),
   MACHINECODE          VARCHAR(60),
   LASTSAVED            VARCHAR(30),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_SITE PRIMARY KEY (SITENO)
);

COMMENT ON TABLE SG_CUR.T_SITE IS 
'վ���';

COMMENT ON COLUMN SG_CUR.T_SITE.SITENO IS 
'վ���';

COMMENT ON COLUMN SG_CUR.T_SITE.SITENAME IS 
'վ������';

COMMENT ON COLUMN SG_CUR.T_SITE.IP IS 
'IP��ַ';

COMMENT ON COLUMN SG_CUR.T_SITE.MACHINECODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SITE.LASTSAVED IS 
'��󱣴�ʱ��';

COMMENT ON COLUMN SG_CUR.T_SITE.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_OPERSITE                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_OPERSITE 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   SITENO               INTEGER                        NOT NULL,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_OPERSITE PRIMARY KEY (OPERCODE, SITENO),
   CONSTRAINT FK_OPERSITE_SITE FOREIGN KEY (SITENO)
      REFERENCES SG_CUR.T_SITE (SITENO),
   CONSTRAINT FK_OPERSITE_OPERATOR FOREIGN KEY (OPERCODE)
      REFERENCES SG_CUR.T_OPERATOR (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_OPERSITE IS 
'����Ավ���ϵ��';

COMMENT ON COLUMN SG_CUR.T_OPERSITE.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_OPERSITE.SITENO IS 
'վ���';

COMMENT ON COLUMN SG_CUR.T_OPERSITE.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_PAYMENTDTL                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PAYMENTDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_PAYMENTDTL IS 
'�����ϸ��';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.ACCNAME IS 
'�˻���';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.AMOUNT IS 
'���';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.PAYBANKACCNO IS 
'��������˺�';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.PAYBANKACCNAME IS 
'��������˻���';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.PAYEEBANKACCNO IS 
'�տ�����˺�';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.PAYEEBANKACCNAME IS 
'�տ�����˻���';

COMMENT ON COLUMN SG_CUR.T_PAYMENTDTL.OPERCODE IS 
'����Ա��';

/*==============================================================*/
/* Table: T_PAYPARA                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PAYPARA 
(
   PARANAME             VARCHAR(60)                    NOT NULL,
   PAYCODE              INTEGER                        NOT NULL,
   PARAVAL              VARCHAR(60),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PAYPARA PRIMARY KEY (PARANAME, PAYCODE)
);

COMMENT ON TABLE SG_CUR.T_PAYPARA IS 
'֧��������';

COMMENT ON COLUMN SG_CUR.T_PAYPARA.PARANAME IS 
'֧����������';

COMMENT ON COLUMN SG_CUR.T_PAYPARA.PAYCODE IS 
'֧������';

COMMENT ON COLUMN SG_CUR.T_PAYPARA.PARAVAL IS 
'֧������ֵ';

COMMENT ON COLUMN SG_CUR.T_PAYPARA.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_PERMISSION                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PERMISSION 
(
   FUNC_ID              INTEGER                        NOT NULL,
   ROLE_ID              INTEGER                        NOT NULL,
   AUTH_ACTION          INTEGER,
   CONSTRAINT PK_T_PERMISSION PRIMARY KEY (FUNC_ID, ROLE_ID),
   CONSTRAINT FK_PERMISSION_FUNCTIONALITY FOREIGN KEY (FUNC_ID)
      REFERENCES SG_CUR.T_FUNCTIONALITY (ID),
   CONSTRAINT FK_PERMISISSION_ROLE FOREIGN KEY (ROLE_ID)
      REFERENCES SG_CUR.T_ROLE (ID)
);

COMMENT ON TABLE SG_CUR.T_PERMISSION IS 
'���ܽ�ɫ������';

COMMENT ON COLUMN SG_CUR.T_PERMISSION.FUNC_ID IS 
'ϵͳ����ID';

COMMENT ON COLUMN SG_CUR.T_PERMISSION.ROLE_ID IS 
'��ɫID';

COMMENT ON COLUMN SG_CUR.T_PERMISSION.AUTH_ACTION IS 
'������Ȩ����ֵ';

/*==============================================================*/
/* Table: T_PHOTO                                               */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PHOTO 
(
   CUSTID               INTEGER                        NOT NULL,
   STUEMPNO             VARCHAR(20),
   PHOTO                BLOB,
   MINPHOTO             BLOB,
   PHOTODATE            VARCHAR(8),
   PHOTOTIME            VARCHAR(6),
   IFCARD               CHAR(1),
   MAKECARDDATE         VARCHAR(8),
   MAKECARDTIME         VARCHAR(6),
   PHOTOEXACTTIME       VARCHAR(30),
   CONSTRAINT PK_T_PHOTO PRIMARY KEY (CUSTID),
   CONSTRAINT FK_PHOTO_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID)
);

COMMENT ON TABLE SG_CUR.T_PHOTO IS 
'��Ƭ��';

COMMENT ON COLUMN SG_CUR.T_PHOTO.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_PHOTO.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_PHOTO.PHOTO IS 
'��Ƭ';

COMMENT ON COLUMN SG_CUR.T_PHOTO.MINPHOTO IS 
'С��Ƭ';

COMMENT ON COLUMN SG_CUR.T_PHOTO.PHOTODATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PHOTO.PHOTOTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PHOTO.IFCARD IS 
'�Ƿ��п�';

COMMENT ON COLUMN SG_CUR.T_PHOTO.MAKECARDDATE IS 
'�ƿ�����';

COMMENT ON COLUMN SG_CUR.T_PHOTO.MAKECARDTIME IS 
'�ƿ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_PHOTO.PHOTOEXACTTIME IS 
'����ʱ��';

/*==============================================================*/
/* Index: IDX_STUEMPNO                                          */
/*==============================================================*/
CREATE INDEX IDX_STUEMPNO ON SG_CUR.T_PHOTO (
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
TABLESPACE TS_SG_CUR;

/*==============================================================*/
/* Table: T_PHOTOLIMIT                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PHOTOLIMIT 
(
   OPERCODE             VARCHAR(8)                     NOT NULL,
   OPERNAME             VARCHAR(60),
   OPERPWD              VARCHAR(64),
   OPERLIMIT            VARCHAR(60),
   ENABLED              CHAR(1),
   BEGINDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PHOTOLIMIT PRIMARY KEY (OPERCODE)
);

COMMENT ON TABLE SG_CUR.T_PHOTOLIMIT IS 
'��ƬȨ�ޱ�';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.OPERNAME IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.OPERPWD IS 
'����Ա����';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.OPERLIMIT IS 
'Ȩ��';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.ENABLED IS 
'�Ƿ����';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.BEGINDATE IS 
'��Ч����';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.ENDDATE IS 
'ʧЧ����';

COMMENT ON COLUMN SG_CUR.T_PHOTOLIMIT.REMARK IS 
'��ע';

/*==============================================================*/
/* Table: T_POSDTL                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_POSDTL 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6),
   TERMID               INTEGER,
   DEVPHYID             VARCHAR(20)                    NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
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
   STATUS               CHAR(1)                        NOT NULL,
   ERRCODE              INTEGER,
   ERRMSG               VARCHAR(240),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_POSDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO)
);

COMMENT ON TABLE SG_CUR.T_POSDTL IS 
'POS��ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_POSDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_POSDTL.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_POSDTL.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_POSDTL.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.AMOUNT IS 
'������-���������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.MANAGEFEE IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TRANSMARK IS 
'���ױ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.DATATYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.SHOPID IS 
'�̻�����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.SUBSIDYNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_POSDTL.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_POSDTL.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_POSDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_POSDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSDTL.STATUS IS 
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN SG_CUR.T_POSDTL.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_POSDTL.ERRMSG IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_POSDTL.DELFLAG IS 
'ɾ����־';

/*==============================================================*/
/* Index: IDX_CARDNOCARDCNT                                     */
/*==============================================================*/
CREATE INDEX IDX_CARDNOCARDCNT ON SG_CUR.T_POSDTL (
CARDNO ASC,
CARDCNT ASC
);

/*==============================================================*/
/* Index: IDX_POSDTL_POS                                        */
/*==============================================================*/
CREATE INDEX IDX_POSDTL_POS ON SG_CUR.T_POSDTL (
STATUS ASC
);

/*==============================================================*/
/* Table: T_POSDTLTMP                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_POSDTLTMP 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6),
   DEVPHYID             VARCHAR(20)                    NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
   SHOPID               INTEGER,
   TRANSCODE            INTEGER,
   CARDNO               INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_POSDTLTMP IS 
'POS��ˮ��ʱ��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.SHOPID IS 
'�̻�����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.AMOUNT IS 
'������-���������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.MANAGEFEE IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.TRANSMARK IS 
'���ױ��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.SEQNO IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.IMPDATE IS 
'¼������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.IMPTIME IS 
'¼������';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.IMPOPER IS 
'¼�����Ա��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.TERMSEQNO IS 
'¼����ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.STATUS IS 
'��ˮ״̬:1-¼��2-���ʧ��3-�����';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.ERRMSG IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CHKOPER IS 
'��˲���Ա��';

COMMENT ON COLUMN SG_CUR.T_POSDTLTMP.CHKDATE IS 
'�������';

/*==============================================================*/
/* Table: T_POSSEQNO                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_POSSEQNO 
(
   DEVICEID             INTEGER                        NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   CONSTRAINT PK_T_POSSEQNO PRIMARY KEY (DEVICEID, DEVSEQNO, TRANSDATE)
);

COMMENT ON TABLE SG_CUR.T_POSSEQNO IS 
'POS��ˮ�ű�';

COMMENT ON COLUMN SG_CUR.T_POSSEQNO.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_POSSEQNO.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_POSSEQNO.TRANSDATE IS 
'��������';

/*==============================================================*/
/* Table: T_PSAMCARD                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PSAMCARD 
(
   CARDNO               INTEGER                        NOT NULL,
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

COMMENT ON TABLE SG_CUR.T_PSAMCARD IS 
'PSAM����';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.CARDVER IS 
'���汾��';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.TERMNO IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.STARTDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.EXPIREDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.KEYINDEX IS 
'��Կ����';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.DEVJOINTIME IS 
'�豸������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.PUBLISHID IS 
'���з�ID';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.USERID IS 
'�û�ID';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.OPENDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.CLOSEDATE IS 
'�ر�����';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.DISABLEDATE IS 
'ͣ������';

COMMENT ON COLUMN SG_CUR.T_PSAMCARD.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_PURSE                                               */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PURSE 
(
   PURSENO              INTEGER                        NOT NULL,
   PURSENAME            VARCHAR(60),
   CARDMAXBAL           NUMBER(15,2),
   USEFLAG              CHAR(1),
   CONSTRAINT PK_T_PURSE PRIMARY KEY (PURSENO)
);

COMMENT ON TABLE SG_CUR.T_PURSE IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_PURSE.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_PURSE.PURSENAME IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_PURSE.CARDMAXBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_PURSE.USEFLAG IS 
'ʹ�ñ�־0-δʹ��1-��ʹ��';

/*==============================================================*/
/* Table: T_PURSEPOSDTL                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PURSEPOSDTL 
(
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSTIME            VARCHAR(6),
   TERMID               INTEGER,
   DEVPHYID             VARCHAR(20)                    NOT NULL,
   DEVSEQNO             INTEGER                        NOT NULL,
   CARDNO               INTEGER                        NOT NULL,
   PURSETYPE            NUMBER(1),
   CARDCNT              INTEGER,
   CARDBEFBAL           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CARDAFTBAL           NUMBER(15,2),
   TRANSMARK            INTEGER,
   DATATYPE             NUMBER(1),
   SHOPID               INTEGER,
   BATCHNO              VARCHAR(30),
   SYSID                INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   ACCDATE              VARCHAR(8),
   ACCTIME              VARCHAR(6),
   TERMSEQNO            INTEGER,
   STATUS               CHAR(1)                        NOT NULL,
   ERRCODE              INTEGER,
   ERRMSG               VARCHAR(240),
   DELFLAG              CHAR(1),
   CONSTRAINT PK_T_PURSEPOSDTL PRIMARY KEY (TRANSDATE, DEVPHYID, DEVSEQNO, CARDNO)
);

COMMENT ON TABLE SG_CUR.T_PURSEPOSDTL IS 
'СǮ����ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.TERMID IS 
'�ն˺�';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.PURSETYPE IS 
'Ǯ������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.AMOUNT IS 
'������-���������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.TRANSMARK IS 
'���ױ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.DATATYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.SHOPID IS 
'�̻�����';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.STATUS IS 
'״̬-1��ʼ״̬2-����ʧ��3-�ɹ�4-�쳣��ˮ';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.ERRMSG IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_PURSEPOSDTL.DELFLAG IS 
'ɾ����־';

/*==============================================================*/
/* Index: IDX_PURSEPOSDTL_STATUS                                */
/*==============================================================*/
CREATE INDEX IDX_PURSEPOSDTL_STATUS ON SG_CUR.T_PURSEPOSDTL (
STATUS ASC
);

/*==============================================================*/
/* Table: T_PURSETRANSDTL                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PURSETRANSDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
   PURSETYPE            NUMBER(1)                      NOT NULL,
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
   OPERCODE             VARCHAR(8),
   SYSID                INTEGER,
   DEVPHYID             VARCHAR(20),
   DEVSEQNO             INTEGER,
   COLDATE              VARCHAR(8),
   COLTIME              VARCHAR(6),
   STATUS               CHAR(1),
   ERRCODE              INTEGER,
   REMARK               VARCHAR(240),
   CONSTRAINT PK_T_PURSETRANSDTL PRIMARY KEY (ACCDATE, TERMID, TERMSEQNO, PURSETYPE)
);

COMMENT ON TABLE SG_CUR.T_PURSETRANSDTL IS 
'СǮ��������ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.PURSETYPE IS 
'Ǯ������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CUSTNAME IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.TRANSFLAG IS 
'1��ֵ��־2���Ѵ���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.SYSID IS 
'��ϵͳ���';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.STATUS IS 
'��¼״̬1:δ����2-����ʧ��3-�ɹ�';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_PURSETRANSDTL.REMARK IS 
'��ע';

/*==============================================================*/
/* Index: IDX_PURSETRANSDTL_CARDNO                              */
/*==============================================================*/
CREATE INDEX IDX_PURSETRANSDTL_CARDNO ON SG_CUR.T_PURSETRANSDTL (
CARDNO ASC
);

/*==============================================================*/
/* Index: IDX_PURSETRANSDTL_CUSTID                              */
/*==============================================================*/
CREATE INDEX IDX_PURSETRANSDTL_CUSTID ON SG_CUR.T_PURSETRANSDTL (
CUSTID ASC
);

/*==============================================================*/
/* Table: T_PURSETYPE                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PURSETYPE 
(
   PURSETYPE            NUMBER(1)                      NOT NULL,
   PURSETYPENAME        VARCHAR(60),
   PURSEMAXBAL          NUMBER(15,2),
   ONLINEFLAG           NUMBER(1),
   SHOPID               NUMBER(2),
   REFUNDFLAG           NUMBER(1),
   PRIMARYFLAG          NUMBER(1),
   ENABLEFLAG           NUMBER(1),
   REMARK               VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_PURSETYPE PRIMARY KEY (PURSETYPE)
);

COMMENT ON TABLE SG_CUR.T_PURSETYPE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.PURSETYPE IS 
'Ǯ������';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.PURSETYPENAME IS 
'Ǯ��������';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.PURSEMAXBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.ONLINEFLAG IS 
'������־';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.REFUNDFLAG IS 
'�˿�����־';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.PRIMARYFLAG IS 
'��Ǯ����־';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.ENABLEFLAG IS 
'���ñ�־';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_PURSETYPE.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_PUSHTASK                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_PUSHTASK 
(
   TASKID               INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_PUSHTASK IS 
'���������';

COMMENT ON COLUMN SG_CUR.T_PUSHTASK.TASKID IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_PUSHTASK.TASKSEQ IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_PUSHTASK.DEVICEID IS 
'�豸���';

/*==============================================================*/
/* Table: T_REFNO                                               */
/*==============================================================*/
CREATE TABLE SG_CUR.T_REFNO 
(
   REFNO                NUMBER(14)                     NOT NULL,
   MAC                  VARCHAR(8)                     NOT NULL,
   STATUS               NUMBER(1)                      NOT NULL,
   REQREFNO             VARCHAR(20),
   ACCDATE              VARCHAR(8),
   TERMID               INTEGER,
   TERMSEQNO            INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_REFNO PRIMARY KEY (REFNO)
);

COMMENT ON TABLE SG_CUR.T_REFNO IS 
'���ײο��ű�';

COMMENT ON COLUMN SG_CUR.T_REFNO.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_REFNO.MAC IS 
'MAC��';

COMMENT ON COLUMN SG_CUR.T_REFNO.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_REFNO.REQREFNO IS 
'���󷽲ο���';

COMMENT ON COLUMN SG_CUR.T_REFNO.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_REFNO.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_REFNO.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_REFNO.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_RPTACCBAL                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTACCBAL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   SUBJNO               VARCHAR(20),
   ACCNO                VARCHAR(10)                    NOT NULL,
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTACCBAL PRIMARY KEY (ACCDATE, ACCNO)
);

COMMENT ON TABLE SG_CUR.T_RPTACCBAL IS 
'�˻�����';

COMMENT ON COLUMN SG_CUR.T_RPTACCBAL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTACCBAL.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTACCBAL.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTACCBAL.BALFLAG IS 
'����';

COMMENT ON COLUMN SG_CUR.T_RPTACCBAL.BALANCE IS 
'���';

/*==============================================================*/
/* Table: T_RPTACCLEDGER                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTACCLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   PERSONCNT            INTEGER,
   CONSTRAINT PK_T_RPTACCLEDGER PRIMARY KEY (ACCDATE, ACCNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTACCLEDGER IS 
'��ϸ�����˱�(�̻�)';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.BALFLAG IS 
'����';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.BALANCE IS 
'���';

COMMENT ON COLUMN SG_CUR.T_RPTACCLEDGER.PERSONCNT IS 
'�˴�';

/*==============================================================*/
/* Table: T_RPTDAILYACC                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTDAILYACC 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTDAILYACC PRIMARY KEY (ACCDATE, ACCNO)
);

COMMENT ON TABLE SG_CUR.T_RPTDAILYACC IS 
'�˻��ռƱ�(�̻�)';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.BALFLAG IS 
'����';

COMMENT ON COLUMN SG_CUR.T_RPTDAILYACC.BALANCE IS 
'���';

/*==============================================================*/
/* Table: T_RPTDEPTLEDGER                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTDEPTLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   DEPTCODE             VARCHAR(30)                    NOT NULL,
   SUBJNO               VARCHAR(20)                    NOT NULL,
   TRANSTYPE            INTEGER                        NOT NULL,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTDEPTLEDGER PRIMARY KEY (ACCDATE, DEPTCODE, SUBJNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTDEPTLEDGER IS 
'���ŷ����˱�';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.DEPTCODE IS 
'���Ŵ���';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTDEPTLEDGER.CRAMT IS 
'����������';

/*==============================================================*/
/* Table: T_RPTOPERCARD                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTOPERCARD 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   CARDTYPE             INTEGER                        NOT NULL,
   USETYPE              INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   INCNT                INTEGER,
   OUTCNT               INTEGER,
   REMAINCNT            INTEGER,
   CONSTRAINT PK_T_RPTOPERCARD PRIMARY KEY (ACCDATE, OPERCODE, CARDTYPE, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTOPERCARD IS 
'����Ա��Ƭ����';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.BRANCHNO IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.CARDTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.USETYPE IS 
'ʹ������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.INCNT IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.OUTCNT IS 
'֧������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCARD.REMAINCNT IS 
'�������';

/*==============================================================*/
/* Table: T_RPTOPERCASH                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTOPERCASH 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   BRANCHNO             INTEGER,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   SUBJNO               VARCHAR(20)                    NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   INAMT                NUMBER(15,2),
   OUTAMT               NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTOPERCASH PRIMARY KEY (ACCDATE, OPERCODE, SUBJNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTOPERCASH IS 
'����Ա�ֽ�Ʊ�ݱ���';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.BRANCHNO IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.TRANSTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.INAMT IS 
'���뷢����';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.OUTAMT IS 
'֧��������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERCASH.AMOUNT IS 
'�����';

/*==============================================================*/
/* Table: T_RPTOPERLEDGER                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTOPERLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   OPERCODE             VARCHAR(8)                     NOT NULL,
   SUBJNO               VARCHAR(20),
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTOPERLEDGER PRIMARY KEY (ACCDATE, OPERCODE, ACCNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTOPERLEDGER IS 
'����Ա�����˱�';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.TRANSTYPE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTOPERLEDGER.CRAMT IS 
'����������';

/*==============================================================*/
/* Table: T_RPTPOSLEDGER                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTPOSLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTPOSLEDGER PRIMARY KEY (ACCDATE, ACCNO, DEVICEID, SUMMARY, TRANSDATE)
);

COMMENT ON TABLE SG_CUR.T_RPTPOSLEDGER IS 
'�̻�POS�����˱�';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSLEDGER.AMOUNT IS 
'�����';

/*==============================================================*/
/* Table: T_RPTPOSMEAL                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTPOSMEAL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   MEALTYPE             INTEGER,
   MEALNAME             VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTPOSMEAL PRIMARY KEY (ACCDATE, ACCNO, DEVICEID, SUMMARY, TRANSDATE, MEALNAME)
);

COMMENT ON TABLE SG_CUR.T_RPTPOSMEAL IS 
'�̻�POS�ֲʹα���';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.DEVICEID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.MEALTYPE IS 
'�ʹ�����';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.MEALNAME IS 
'�ʹ�����';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTPOSMEAL.AMOUNT IS 
'�����';

/*==============================================================*/
/* Table: T_RPTSHOPBOARD                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSHOPBOARD 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSCNT             INTEGER                        NOT NULL,
   TRANSAMT             NUMBER(15,2)                   NOT NULL,
   CONSTRAINT PK_T_RPTSHOPBOARD PRIMARY KEY (ACCDATE, ACCNO)
);

COMMENT ON COLUMN SG_CUR.T_RPTSHOPBOARD.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPBOARD.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPBOARD.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPBOARD.TRANSAMT IS 
'������';

/*==============================================================*/
/* Table: T_RPTSHOPMEAL                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSHOPMEAL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSCNT1            INTEGER,
   TRANSAMT1            NUMBER(15,2),
   TRANSCNT2            INTEGER,
   TRANSAMT2            NUMBER(15,2),
   TRANSCNT3            INTEGER,
   TRANSAMT3            NUMBER(15,2),
   TRANSCNT4            INTEGER,
   TRANSAMT4            NUMBER(15,2),
   CONSTRAINT PK_T_RPTSHOPMEAL PRIMARY KEY (ACCDATE, ACCNO)
);

COMMENT ON TABLE SG_CUR.T_RPTSHOPMEAL IS 
'�̻��ֲʹα���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSCNT1 IS 
'��ͽ��״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSAMT1 IS 
'��ͽ��';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSCNT2 IS 
'��ͽ��״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSAMT2 IS 
'��ͽ��';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSCNT3 IS 
'��ͽ��״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSAMT3 IS 
'��ͽ��';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSCNT4 IS 
'ҹ�ͽ��״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPMEAL.TRANSAMT4 IS 
'ҹ�ͽ��';

/*==============================================================*/
/* Table: T_RPTSHOPRAKEOFF                                      */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSHOPRAKEOFF 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   SHOPID               INTEGER,
   ACCNO                VARCHAR(10)                    NOT NULL,
   ACCNAME              VARCHAR(60),
   RAKEOFFRATE          NUMBER(5,4)                    NOT NULL,
   TRANSCNT             INTEGER                        NOT NULL,
   TRANSAMT             NUMBER(15,2)                   NOT NULL,
   RAKEOFFAMT           NUMBER(15,2),
   AMOUNT               NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   PERSONCNT            INTEGER,
   CONSTRAINT PK_T_RPTSHOPRAKEOFF PRIMARY KEY (ACCDATE, ACCNO)
);

COMMENT ON TABLE SG_CUR.T_RPTSHOPRAKEOFF IS 
'�̻�Ӷ�𱨱�';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.ACCDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.ACCNAME IS 
'�̻��˻���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.RAKEOFFRATE IS 
'Ӷ�����';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.TRANSAMT IS 
'Ӫҵ���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.RAKEOFFAMT IS 
'Ӷ����';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.BALANCE IS 
'���';

COMMENT ON COLUMN SG_CUR.T_RPTSHOPRAKEOFF.PERSONCNT IS 
'�˴�';

/*==============================================================*/
/* Table: T_RPTSUBJBAL                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSUBJBAL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   SUBJNO               VARCHAR(20)                    NOT NULL,
   BEGINBAL             NUMBER(15,2),
   BEGINBALFLAG         NUMBER(1),
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   ENDBAL               NUMBER(15,2),
   ENDBALFLAG           NUMBER(1),
   CONSTRAINT PK_T_RPTSUBJBAL PRIMARY KEY (ACCDATE, SUBJNO)
);

COMMENT ON TABLE SG_CUR.T_RPTSUBJBAL IS 
'��Ŀ����';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.BEGINBAL IS 
'�ڳ����';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.BEGINBALFLAG IS 
'�ڳ�����';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.ENDBAL IS 
'��ĩ���';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJBAL.ENDBALFLAG IS 
'��ĩ����';

/*==============================================================*/
/* Table: T_RPTSUBJLEDGER                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSUBJLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   SUBJNO               VARCHAR(20)                    NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   BALFLAG              NUMBER(1),
   BALANCE              NUMBER(15,2),
   CONSTRAINT PK_T_RPTSUBJLEDGER PRIMARY KEY (ACCDATE, SUBJNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTSUBJLEDGER IS 
'��Ŀ�����˱���';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.BALFLAG IS 
'����';

COMMENT ON COLUMN SG_CUR.T_RPTSUBJLEDGER.BALANCE IS 
'���';

/*==============================================================*/
/* Table: T_RPTSYSSTAT                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTSYSSTAT 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ITEMID               INTEGER                        NOT NULL,
   ITEMNAME             VARCHAR(60),
   ITEMVAL              VARCHAR(30),
   CONSTRAINT PK_T_RPTSYSSTAT PRIMARY KEY (ACCDATE, ITEMID)
);

COMMENT ON TABLE SG_CUR.T_RPTSYSSTAT IS 
'ϵͳͳ�Ʊ���';

COMMENT ON COLUMN SG_CUR.T_RPTSYSSTAT.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTSYSSTAT.ITEMID IS 
'ͳ����Ŀ���';

COMMENT ON COLUMN SG_CUR.T_RPTSYSSTAT.ITEMNAME IS 
'ͳ����Ŀ����';

COMMENT ON COLUMN SG_CUR.T_RPTSYSSTAT.ITEMVAL IS 
'ͳ������';

/*==============================================================*/
/* Table: T_RPTTERMLEDGER                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTTERMLEDGER 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   SUBJNO               VARCHAR(20)                    NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTTERMLEDGER PRIMARY KEY (ACCDATE, TERMID, ACCNO, SUMMARY)
);

COMMENT ON TABLE SG_CUR.T_RPTTERMLEDGER IS 
'�ն˷����˱�';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMLEDGER.CRAMT IS 
'����������';

/*==============================================================*/
/* Table: T_RPTTERMMEAL                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_RPTTERMMEAL 
(
   SETTLEDATE           NUMBER(8)                      NOT NULL,
   ACCNO                VARCHAR(10)                    NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TRANSTYPE            INTEGER                        NOT NULL,
   SUMMARY              VARCHAR(60)                    NOT NULL,
   TRANSDATE            VARCHAR(8)                     NOT NULL,
   MEALTYPE             INTEGER                        NOT NULL,
   TRANSCNT             INTEGER                        NOT NULL,
   DRAMT                NUMBER(15,2)                   NOT NULL,
   CRAMT                NUMBER(15,2)                   NOT NULL,
   AMOUNT               NUMBER(15,2),
   CONSTRAINT PK_T_RPTTERMMEAL PRIMARY KEY (SETTLEDATE, ACCNO, TERMID, TRANSTYPE, SUMMARY, TRANSDATE, MEALTYPE)
);

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.SETTLEDATE IS 
'ҵ������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.TERMID IS 
'�豸���';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.TRANSTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.MEALTYPE IS 
'�ʹ�����';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.TRANSCNT IS 
'���״���';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.DRAMT IS 
'�跽������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.CRAMT IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_RPTTERMMEAL.AMOUNT IS 
'�����';

/*==============================================================*/
/* Table: T_SEQNOCTL                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SEQNOCTL 
(
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER,
   ACCDATE              INTEGER,
   CONSTRAINT PK_T_SEQNOCTL PRIMARY KEY (TERMID),
   CONSTRAINT FK_SEQNOCTL_DEVICE FOREIGN KEY (TERMID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_SEQNOCTL IS 
'��ˮ�ſ��Ʊ�';

COMMENT ON COLUMN SG_CUR.T_SEQNOCTL.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_SEQNOCTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_SEQNOCTL.ACCDATE IS 
'��������';

/*==============================================================*/
/* Table: T_SHOPACC                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOPACC 
(
   ACCNO                VARCHAR(10)                    NOT NULL,
   SHOPID               INTEGER                        NOT NULL,
   ACCNAME              VARCHAR(60),
   SUBJNO               VARCHAR(20),
   ACCPWD               VARCHAR(64),
   STATUS               CHAR(1),
   YDAYBAL              NUMBER(15,2),
   BALANCE              NUMBER(15,2),
   AVAILBAL             NUMBER(15,2),
   FROZEBAL             NUMBER(15,2),
   LASTTRANSDATE        VARCHAR(8),
   LASTACCDATE          VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   CONSTRAINT PK_T_SHOPACC PRIMARY KEY (ACCNO),
   CONSTRAINT FK_SHOPACC_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID),
   CONSTRAINT FK_SHOPACC_SUBJECET FOREIGN KEY (SUBJNO)
      REFERENCES SG_CUR.T_SUBJECT (SUBJNO)
);

COMMENT ON TABLE SG_CUR.T_SHOPACC IS 
'�̻��ʻ���';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.ACCNO IS 
'�˺�';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.ACCNAME IS 
'�ʻ���';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.SUBJNO IS 
'��Ŀ��';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.ACCPWD IS 
'�ʻ�����';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.STATUS IS 
'״̬';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.YDAYBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.BALANCE IS 
'�ʻ����';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.AVAILBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.FROZEBAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.LASTTRANSDATE IS 
'�ϴν�������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.LASTACCDATE IS 
'�ϴ���������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPACC.CLOSEDATE IS 
'��������';

/*==============================================================*/
/* Table: T_SHOPCARD                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOPCARD 
(
   CARDNO               INTEGER                        NOT NULL,
   SHOPID               INTEGER,
   SHOWCARDNO           VARCHAR(10),
   CARDPHYID            VARCHAR(16),
   CARDPWD              VARCHAR(32),
   EXPIREDATE           VARCHAR(8),
   STATUS               CHAR(1)                        NOT NULL,
   LOSSFLAG             CHAR(1)                        NOT NULL,
   LOSSDATE             VARCHAR(8),
   OPENDATE             VARCHAR(8),
   CLOSEDATE            VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPCARD PRIMARY KEY (CARDNO),
   CONSTRAINT FK_SHOPCARD_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID),
   CONSTRAINT FK_SHOPCARD_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_SHOPCARD IS 
'�̻�����';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.CARDPHYID IS 
'������ID';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.CARDPWD IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.EXPIREDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.STATUS IS 
'��¼״̬1-����2-ע��';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.LOSSFLAG IS 
'1-��ʧ0-δ��ʧ';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.LOSSDATE IS 
'��ʧ����';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.OPENDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.CLOSEDATE IS 
'ע������';

COMMENT ON COLUMN SG_CUR.T_SHOPCARD.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SHOPMEAL                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOPMEAL 
(
   SHOPID               INTEGER                        NOT NULL,
   ACCNO                VARCHAR(10),
   ENDTIME1             VARCHAR(6),
   ENDTIME2             VARCHAR(6),
   ENDTIME3             VARCHAR(6),
   ENDTIME4             VARCHAR(6),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPMEAL PRIMARY KEY (SHOPID),
   CONSTRAINT FK_SHOPMEAL_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID)
);

COMMENT ON TABLE SG_CUR.T_SHOPMEAL IS 
'�̻��ʹα�';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.ACCNO IS 
'�̻��˺�';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.ENDTIME1 IS 
'��ͽ���ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.ENDTIME2 IS 
'��ͽ���ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.ENDTIME3 IS 
'��ͽ���ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.ENDTIME4 IS 
'ҹ�ͽ���ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_SHOPMEAL.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_SHOPPOS                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOPPOS 
(
   ID                   INTEGER                        NOT NULL,
   DEVICEID             INTEGER                        NOT NULL,
   DEVPHYID             VARCHAR(20),
   SHOPID               INTEGER                        NOT NULL,
   STARTTIME            VARCHAR(6),
   ENDTIME              VARCHAR(6),
   REMARK               VARCHAR(240),
   STARTDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   STATUS               CHAR(1),
   OPERCODE             VARCHAR(8),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SHOPPOS PRIMARY KEY (ID),
   CONSTRAINT FK_SHOPPOS_SHOP FOREIGN KEY (SHOPID)
      REFERENCES SG_CUR.T_SHOP (SHOPID),
   CONSTRAINT FK_SHOPPOS_DEVICE FOREIGN KEY (DEVICEID)
      REFERENCES SG_CUR.T_DEVICE (DEVICEID)
);

COMMENT ON TABLE SG_CUR.T_SHOPPOS IS 
'�̻��豸��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.ID IS 
'��¼���';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.STARTTIME IS 
'��ʼʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.ENDTIME IS 
'��ֹʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.REMARK IS 
'��ע';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.STARTDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.ENDDATE IS 
'ͣ������';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.STATUS IS 
'1-����2-����';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOS.LASTSAVED IS 
'��ñ���ʱ��';

/*==============================================================*/
/* Index: IDX_SHOPPOSDEVICE                                     */
/*==============================================================*/
CREATE INDEX IDX_SHOPPOSDEVICE ON SG_CUR.T_SHOPPOS (
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
TABLESPACE TS_SG_CUR;

/*==============================================================*/
/* Table: T_SHOPPOSTMP                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SHOPPOSTMP 
(
   BATCHNO              VARCHAR(30)                    NOT NULL,
   SEQNO                INTEGER                        NOT NULL,
   TRANSDATE            VARCHAR(8),
   TRANSTIME            VARCHAR(6),
   OPERCODE             VARCHAR(8),
   DEVICEID             INTEGER,
   DEVPHYID             VARCHAR(20),
   SHOPID               INTEGER                        NOT NULL,
   ENDTIME              VARCHAR(6),
   STARTDATE            VARCHAR(8),
   ENDDATE              VARCHAR(8),
   ERRMSG               VARCHAR(240),
   CONSTRAINT PK_T_SHOPPOSTMP PRIMARY KEY (BATCHNO, SEQNO)
);

COMMENT ON TABLE SG_CUR.T_SHOPPOSTMP IS 
'�̻��豸��ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.SEQNO IS 
'����˳���';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.OPERCODE IS 
'�������Ա';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.DEVICEID IS 
'�豸ID';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.SHOPID IS 
'�̻���';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.ENDTIME IS 
'��ֹʱ��';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.STARTDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.ENDDATE IS 
'ͣ������';

COMMENT ON COLUMN SG_CUR.T_SHOPPOSTMP.ERRMSG IS 
'������Ϣ';

/*==============================================================*/
/* Table: T_SPECIALTY                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SPECIALTY 
(
   SPECIALTYCODE        VARCHAR(30)                    NOT NULL,
   SPECIALTYNAME        VARCHAR(60),
   USEFLAG              CHAR(1),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SPECIALTY PRIMARY KEY (SPECIALTYCODE)
);

COMMENT ON TABLE SG_CUR.T_SPECIALTY IS 
'רҵ��';

COMMENT ON COLUMN SG_CUR.T_SPECIALTY.SPECIALTYCODE IS 
'רҵ����';

COMMENT ON COLUMN SG_CUR.T_SPECIALTY.SPECIALTYNAME IS 
'רҵ����';

COMMENT ON COLUMN SG_CUR.T_SPECIALTY.USEFLAG IS 
'ʹ�ñ�־';

COMMENT ON COLUMN SG_CUR.T_SPECIALTY.LASTSAVED IS 
'��󱣴�ʱ��';

/*==============================================================*/
/* Table: T_STATCUSTTRANS                                       */
/*==============================================================*/
CREATE TABLE SG_CUR.T_STATCUSTTRANS 
(
   SETTLEDATE           NUMBER(8)                      NOT NULL,
   CUSTID               INTEGER                        NOT NULL,
   TRANSDATE            NUMBER(8)                      NOT NULL,
   TRANSCNT             INTEGER                        NOT NULL,
   TRANSAMT             NUMBER(15,2)                   NOT NULL,
   CONSTRAINT PK_T_STATCUSTTRANS PRIMARY KEY (SETTLEDATE, CUSTID, TRANSDATE)
);

COMMENT ON COLUMN SG_CUR.T_STATCUSTTRANS.SETTLEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_STATCUSTTRANS.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_STATCUSTTRANS.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_STATCUSTTRANS.TRANSCNT IS 
'ˢ������';

COMMENT ON COLUMN SG_CUR.T_STATCUSTTRANS.TRANSAMT IS 
'ˢ�����';

/*==============================================================*/
/* Index: IDX_STATCUSTTRANS_TRANSDATE                           */
/*==============================================================*/
CREATE INDEX IDX_STATCUSTTRANS_TRANSDATE ON SG_CUR.T_STATCUSTTRANS (
TRANSDATE ASC
);

/*==============================================================*/
/* Table: T_STATTERMTIME                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_STATTERMTIME 
(
   SETTLEDATE           NUMBER(8)                      NOT NULL,
   TERMID               INTEGER                        NOT NULL,
   TRANSDATE            NUMBER(8)                      NOT NULL,
   TIMEID               NUMBER(2)                      NOT NULL,
   FEECNT               INTEGER                        NOT NULL,
   FREECNT              INTEGER                        NOT NULL,
   TOTALCNT             INTEGER                        NOT NULL,
   TOTALAMT             NUMBER(15,2)                   NOT NULL,
   CONSTRAINT PK_T_STATTERMTIME PRIMARY KEY (SETTLEDATE, TERMID, TRANSDATE, TIMEID)
);

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.SETTLEDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.TIMEID IS 
'ʱ��ID';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.FEECNT IS 
'�շѴ���';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.FREECNT IS 
'�Ǵδ���';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.TOTALCNT IS 
'�ܴ���';

COMMENT ON COLUMN SG_CUR.T_STATTERMTIME.TOTALAMT IS 
'�ܽ��';

/*==============================================================*/
/* Table: T_SUBSIDY                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SUBSIDY 
(
   BATCHNO              VARCHAR(30)                    NOT NULL,
   SEQNO                INTEGER                        NOT NULL,
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
   SUBSIDYMODE          NUMBER(1),
   IMPDATE              VARCHAR(8),
   IMPTIME              VARCHAR(6),
   PUTDATE              VARCHAR(8),
   PUTTIME              VARCHAR(6),
   GETDATE              VARCHAR(8),
   GETTIME              VARCHAR(6),
   STATUS               CHAR(1),
   CHECKFLAG            NUMBER(1),
   ERRMSG               VARCHAR(240),
   OPERCODE             VARCHAR(8),
   CONSTRAINT PK_T_SUBSIDY PRIMARY KEY (BATCHNO, SEQNO),
   CONSTRAINT FK_SUBSIDY_CUSTOMER FOREIGN KEY (CUSTID)
      REFERENCES SG_CUR.T_CUSTOMER (CUSTID),
   CONSTRAINT FK_SUBSIDY_CARD FOREIGN KEY (CARDNO)
      REFERENCES SG_CUR.T_CARD (CARDNO)
);

COMMENT ON TABLE SG_CUR.T_SUBSIDY IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.BATCHNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.SEQNO IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.SUBSIDYNO IS 
'�������κ�';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.CARDNO IS 
'���׿���';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.SUMMARY IS 
'ժҪ';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.BROKERNAME IS 
'����������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.BROKERIDNO IS 
'���������֤��';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.PAYTYPE IS 
'֧����ʽ:1-�ֽ�2-֧Ʊ3-���ѱ�';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.VOUCHERNO IS 
'ƾ֤����';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.SUBSIDYTYPE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.SUBSIDYMODE IS 
'����ģʽ';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.IMPDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.IMPTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.PUTDATE IS 
'�·�����';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.PUTTIME IS 
'�·�ʱ��';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.GETDATE IS 
'��ȡ����';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.GETTIME IS 
'��ȡʱ��';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.STATUS IS 
'״̬:1-δ�·�2-���·�3-����ȡ-4-��Ч';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.CHECKFLAG IS 
'��˱�־';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.ERRMSG IS 
'������Ϣ';

COMMENT ON COLUMN SG_CUR.T_SUBSIDY.OPERCODE IS 
'����Ա��';

/*==============================================================*/
/* Table: T_SUBSYSPARA                                          */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SUBSYSPARA 
(
   SYSID                INTEGER                        NOT NULL,
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
   CONSTRAINT PK_T_SUBSYSPARA PRIMARY KEY (SYSID),
   CONSTRAINT FK_SUBSYSTEM_SUBSYSPARA FOREIGN KEY (SYSID)
      REFERENCES SG_CUR.T_SUBSYSTEM (SYSID)
);

COMMENT ON TABLE SG_CUR.T_SUBSYSPARA IS 
'��ϵͳ������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.SYSID IS 
'��ϵͳID';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.WORKMODE IS 
'����ģʽ';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BEATINTERVAL IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BEATCNTLIMIT IS 
'������������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.REQBEATFUNCNO IS 
'�������͹��ܺ�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.REQDEVFUNCNO IS 
'�����豸��Ϣ���ܺ�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.REQTASKFUNCNO IS 
'���������ܺ�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.RESPFUNCNO IS 
'Ӧ���ܺ�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.EXECTIMEOUT IS 
'ִ�г�ʱʱ��';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.COLINTERVAL IS 
'�ɼ����';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.QRYINTERVAL IS 
'��ѯ������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.TASKMAXLIMIT IS 
'�����������';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BCCDRTPNO IS 
'ͨѶƽ̨�ڵ��';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BCCDRTPIP IS 
'ͨѶƽ̨IP';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BCCDRTPPORT IS 
'ͨѶƽ̨�˿�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BCCMAINFUNCNO IS 
'�����ܺ�';

COMMENT ON COLUMN SG_CUR.T_SUBSYSPARA.BCCINTERVAL IS 
'��ѯʱ��������λ�����룩';

/*==============================================================*/
/* Table: T_SYSKEY                                              */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SYSKEY 
(
   KEYCODE              VARCHAR(60)                    NOT NULL,
   KEYNAME              VARCHAR(60),
   KEYVAL               NUMBER(10),
   MAXVAL               INTEGER,
   KEYTYPE              CHAR(1),
   CONSTRAINT PK_T_SYSKEY PRIMARY KEY (KEYCODE)
);

COMMENT ON TABLE SG_CUR.T_SYSKEY IS 
'ϵͳ��ֵ��';

/*==============================================================*/
/* Table: T_SYSPARA                                             */
/*==============================================================*/
CREATE TABLE SG_CUR.T_SYSPARA 
(
   PARAID               INTEGER                        NOT NULL,
   PARAVAL              VARCHAR(60),
   PARANAME             VARCHAR(60),
   PARAUNIT             VARCHAR(30),
   DISPLAYFLAG          CHAR(1),
   REMARK               VARCHAR(240),
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_SYSPARA PRIMARY KEY (PARAID)
);

COMMENT ON TABLE SG_CUR.T_SYSPARA IS 
'ϵͳ������';

/*==============================================================*/
/* Table: T_THIRDPAY_JJLINK                                     */
/*==============================================================*/
CREATE TABLE SG_CUR.T_THIRDPAY_JJLINK 
(
   ECARD_ID             NUMBER(14)                     NOT NULL,
   REQUEST_TIME         VARCHAR2(20),
   ECARD_NUM            VARCHAR2(20),
   USERNAME             VARCHAR2(50),
   FULLNAME             VARCHAR2(50),
   AMOUNT               NUMBER(15,2),
   ECARD_MACHINE_ID     INTEGER,
   ECARD_IP             VARCHAR2(20),
   INPAYAMOUNT_ID       VARCHAR2(30),
   REPLY_TIME           VARCHAR2(20),
   ACK_TIME             VARCHAR2(20),
   STATUS               CHAR(1),
   UPDATE_TIME          VARCHAR2(20),
   CHECK_NUM            INTEGER                        DEFAULT 0,
   CONSTRAINT PK_T_THIRDPAY_JJLINK PRIMARY KEY (ECARD_ID)
);

COMMENT ON TABLE SG_CUR.T_THIRDPAY_JJLINK IS 
'�ѽ����Ѷ�����ˮ��';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.ECARD_ID IS 
'һ��ͨ��ֵ��ˮ��';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.REQUEST_TIME IS 
'��ֵ�������ʱ�� YYYY-MM-DD HH:mm:ss';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.ECARD_NUM IS 
'һ��ͨ����';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.USERNAME IS 
'����ֵ�û�id';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.FULLNAME IS 
'����ֵ�û���ʵ����';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.AMOUNT IS 
'��ֵ����λ��Ԫ';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.ECARD_MACHINE_ID IS 
'��ֵ�豸�ն˱��';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.ECARD_IP IS 
'һ��ͨ������IP��ַ';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.INPAYAMOUNT_ID IS 
'��ֵ��¼��';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.REPLY_TIME IS 
'����ʱ�� YYYY-MM-DD HH:mm:ss';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.ACK_TIME IS 
'ȷ��ʱ�� YYYY-MM-DD HH:mm:ss';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.STATUS IS 
'״̬��1 �����ֵ,2 ��ֵ�ɹ�,3��ֵʧ��  4 �������ݲ����� 5 ���˲���ֵ�ɹ� 6 ���˲���ֵʧ�� 7 ���˳ɹ���';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.UPDATE_TIME IS 
'������ʱ��';

COMMENT ON COLUMN SG_CUR.T_THIRDPAY_JJLINK.CHECK_NUM IS 
'���˴���';

/*==============================================================*/
/* Table: T_TRANSCODE                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_TRANSCODE 
(
   TRANSCODE            INTEGER                        NOT NULL,
   TRANSNAME            VARCHAR(60),
   LOGFLAG              INTEGER,
   LIMITFLAG            INTEGER,
   FEEFLAG              INTEGER,
   TRANSFLAG            INTEGER,
   DISABLEFLAG          INTEGER,
   CONSTRAINT PK_T_TRANSCODE PRIMARY KEY (TRANSCODE)
);

COMMENT ON TABLE SG_CUR.T_TRANSCODE IS 
'�������';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.TRANSNAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.LOGFLAG IS 
'�Ƿ��¼����Ա��־:0-����¼1-ֻ��¼�ɹ���ˮ2-ֻ��¼ʧ��3-�ɹ�ʧ�ܶ���¼';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.LIMITFLAG IS 
'�Ƿ����Ʋ���Ա:0������1-����';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.FEEFLAG IS 
'�շѱ�־';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.TRANSFLAG IS 
'���ױ�־';

COMMENT ON COLUMN SG_CUR.T_TRANSCODE.DISABLEFLAG IS 
'���ñ�־';

/*==============================================================*/
/* Table: T_TRANSDTL                                            */
/*==============================================================*/
CREATE TABLE SG_CUR.T_TRANSDTL 
(
   ACCDATE              VARCHAR(8)                     NOT NULL,
   ACCTIME              VARCHAR(6),
   TERMID               INTEGER                        NOT NULL,
   TERMSEQNO            INTEGER                        NOT NULL,
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
);

COMMENT ON TABLE SG_CUR.T_TRANSDTL IS 
'������ˮ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.ACCDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.ACCTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TERMID IS 
'�ն˱��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TERMSEQNO IS 
'�ն���ˮ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TRANSDATE IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TRANSTIME IS 
'����ʱ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.REFNO IS 
'���ײο���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TRANSCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CUSTID IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CUSTNAME IS 
'�ͻ���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.STUEMPNO IS 
'ѧ����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.SHOWCARDNO IS 
'��ʾ����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CARDNO IS 
'����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.TRANSFLAG IS 
'1��ֵ��־2���Ѵ���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CARDCNT IS 
'�����״���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CARDBEFBAL IS 
'����ǰ�����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.CARDAFTBAL IS 
'���׺����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.AMOUNT IS 
'������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.ADDAMT IS 
'��Ϊ�Ӹ�Ϊ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.MANAGEFEE IS 
'�����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.PAYTYPE IS 
'֧����ʽ';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.VOUCHERNO IS 
'ƾ֤����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.OPERCODE IS 
'����Ա��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.SYSID IS 
'��ϵͳ���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.DEVPHYID IS 
'�豸����ID';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.DEVSEQNO IS 
'�豸��ˮ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.EXTTYPE IS 
'������������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.EXTDATA IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.COLDATE IS 
'�ɼ�����';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.COLTIME IS 
'�ɼ�ʱ��';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.OFFLINEFLAG IS 
'�ѻ���־';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.REVFLAG IS 
'������־0-δ����1-�ѳ���';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.STATUS IS 
'��¼״̬1:δ����2-����ʧ��3-�ɹ�';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.ERRCODE IS 
'������';

COMMENT ON COLUMN SG_CUR.T_TRANSDTL.REMARK IS 
'��ע';

/*==============================================================*/
/* Index: IDX_TRANSDTL_CARDNO                                   */
/*==============================================================*/
CREATE INDEX IDX_TRANSDTL_CARDNO ON SG_CUR.T_TRANSDTL (
CARDNO ASC
);

/*==============================================================*/
/* Index: IDX_TRANSDTL_CUSTID                                   */
/*==============================================================*/
CREATE INDEX IDX_TRANSDTL_CUSTID ON SG_CUR.T_TRANSDTL (
CUSTID ASC
);

/*==============================================================*/
/* Table: T_WATERFEECFG                                         */
/*==============================================================*/
CREATE TABLE SG_CUR.T_WATERFEECFG 
(
   FEEID                INTEGER                        NOT NULL,
   FEENAME              VARCHAR(60),
   PURSENO              INTEGER,
   FEEMODE              INTEGER,
   FEETYPECNT           INTEGER,
   CONSTRAINT PK_T_WATERFEECFG PRIMARY KEY (FEEID),
   CONSTRAINT FK_WATERFEECFG_PURSE FOREIGN KEY (PURSENO)
      REFERENCES SG_CUR.T_PURSE (PURSENO)
);

COMMENT ON TABLE SG_CUR.T_WATERFEECFG IS 
'��ط���';

COMMENT ON COLUMN SG_CUR.T_WATERFEECFG.FEEID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_WATERFEECFG.FEENAME IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_WATERFEECFG.PURSENO IS 
'Ǯ����';

COMMENT ON COLUMN SG_CUR.T_WATERFEECFG.FEEMODE IS 
'����ģʽ';

COMMENT ON COLUMN SG_CUR.T_WATERFEECFG.FEETYPECNT IS 
'��Ȩ���������';

/*==============================================================*/
/* Table: T_WATERFEETYPE                                        */
/*==============================================================*/
CREATE TABLE SG_CUR.T_WATERFEETYPE 
(
   FEEID                INTEGER                        NOT NULL,
   FEETYPE              INTEGER                        NOT NULL,
   FEECNT               INTEGER,
   STARTTIME1           INTEGER,
   FEETIME1             INTEGER,
   FEEAMT1              INTEGER,
   STARTTIME2           INTEGER,
   FEETIME2             INTEGER,
   FEEAMT2              INTEGER,
   STARTTIME3           INTEGER,
   FEETIME3             INTEGER,
   FEEAMT3              INTEGER,
   CONSTRAINT PK_T_WATERFEETYPE PRIMARY KEY (FEEID, FEETYPE),
   CONSTRAINT FK_WATERFEETYPE_WATERFEECFG FOREIGN KEY (FEEID)
      REFERENCES SG_CUR.T_WATERFEECFG (FEEID)
);

COMMENT ON TABLE SG_CUR.T_WATERFEETYPE IS 
'����շ�����';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEEID IS 
'����ID';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEECNT IS 
'��������';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.STARTTIME1 IS 
'�Ʒѿ�ʼʱ��1';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEETIME1 IS 
'�Ʒ�ʱ��1';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEEAMT1 IS 
'�Ʒѽ��1';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.STARTTIME2 IS 
'�Ʒѿ�ʼʱ��2';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEETIME2 IS 
'�Ʒ�ʱ��2';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEEAMT2 IS 
'�Ʒѽ��2';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.STARTTIME3 IS 
'�Ʒѿ�ʼʱ��3';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEETIME3 IS 
'�Ʒ�ʱ��3';

COMMENT ON COLUMN SG_CUR.T_WATERFEETYPE.FEEAMT3 IS 
'�Ʒѽ��3';

/*==============================================================*/
/* Table: T_WATERRATE                                           */
/*==============================================================*/
CREATE TABLE SG_CUR.T_WATERRATE 
(
   FEETYPE              INTEGER                        NOT NULL,
   RATE1                INTEGER,
   RATE2                INTEGER,
   RATE3                INTEGER,
   LASTSAVED            VARCHAR(30),
   CONSTRAINT PK_T_WATERRATE PRIMARY KEY (FEETYPE)
);

COMMENT ON TABLE SG_CUR.T_WATERRATE IS 
'�ѻ�ˮ��';

COMMENT ON COLUMN SG_CUR.T_WATERRATE.FEETYPE IS 
'�շ����';

COMMENT ON COLUMN SG_CUR.T_WATERRATE.RATE1 IS 
'ˮ��1';

COMMENT ON COLUMN SG_CUR.T_WATERRATE.RATE2 IS 
'ˮ��2';

COMMENT ON COLUMN SG_CUR.T_WATERRATE.RATE3 IS 
'ˮ��3';

COMMENT ON COLUMN SG_CUR.T_WATERRATE.LASTSAVED IS 
'����ʱ��';

