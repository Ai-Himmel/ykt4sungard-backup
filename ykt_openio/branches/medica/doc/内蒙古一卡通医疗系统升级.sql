
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

COMMENT ON TABLE YKT_CUR.T_MEDICALDTL IS
'T_MEDICALDTL-ҽ���շ���ˮ��';

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

insert into T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (108, '����Ա����', '3', 'ҽ��ϵͳ����Ա');
insert into T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (107, '��������', '3', 'ҽ��ϵͳ');