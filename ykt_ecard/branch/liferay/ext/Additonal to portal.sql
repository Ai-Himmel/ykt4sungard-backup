CREATE TABLE YKT_CUR.T_RPTTERMLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   TERMID               INTEGER                         NOT NULL,
   SUBJNO               VARCHAR(6)                      NOT NULL,
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTTERMLEDGER PRIMARY KEY (ACCDATE, TERMID, ACCNO, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON TABLE YKT_CUR.T_RPTTERMLEDGER IS
'T_RPTTERMLEDGER-�ն˷����˱�';

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


CREATE TABLE YKT_CUR.T_RPTDEPTLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   DEPTCODE             VARCHAR(30)                     NOT NULL,
   SUBJNO               VARCHAR(6)                      NOT NULL,
   TRANSTYPE            INTEGER                         NOT NULL,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTDEPTLEDGER PRIMARY KEY (ACCDATE, DEPTCODE, SUBJNO, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON TABLE YKT_CUR.T_RPTDEPTLEDGER IS
'T_RPTDEPTLEDGER-���ŷ����˱�';

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


-- Create table
create table ykt_cur.T_RCSTATDATA
(
  CARD_NO INTEGER not null,
  MEAL    CHAR(20) not null,
  TX_DATE CHAR(8) not null,
  AMOUNT  NUMBER(15,2),
  CONSTRAINT PK_T_RCSTATDATA PRIMARY KEY (CARD_NO, MEAL, TX_DATE)
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
-- Create/Recreate indexes 
create index IDX_RCSTATDATA on ykt_cur.T_RCSTATDATA (CARD_NO, MEAL, TX_DATE)
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
  
  
  