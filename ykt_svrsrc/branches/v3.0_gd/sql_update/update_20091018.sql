/*==============================================================*/
/* Table: T_RPTOPERLEDGER                                       */
/*==============================================================*/
CREATE TABLE YKT_CUR.T_RPTOPERLEDGER  (
   ACCDATE              VARCHAR(8)                      NOT NULL,
   OPERCODE             VARCHAR(8)                      NOT NULL,
   SUBJNO               VARCHAR(6),
   ACCNO                VARCHAR(10)                     NOT NULL,
   TRANSTYPE            INTEGER,
   SUMMARY              VARCHAR(60)                     NOT NULL,
   TRANSCNT             INTEGER,
   DRAMT                NUMBER(15,2),
   CRAMT                NUMBER(15,2),
   CONSTRAINT PK_T_RPTOPERLEDGER PRIMARY KEY (ACCDATE, OPERCODE, ACCNO, SUMMARY)
)
TABLESPACE TS_YKT_CUR;

COMMENT ON TABLE YKT_CUR.T_RPTOPERLEDGER IS
'T_RPTOPERLEDGER-����Ա�����˱�';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.ACCDATE IS
'ҵ������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.OPERCODE IS
'����Ա��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUBJNO IS
'��Ŀ��';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.ACCNO IS
'�˺�';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSTYPE IS
'��������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUMMARY IS
'ժҪ';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSCNT IS
'���״���';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.DRAMT IS
'�跽������';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.CRAMT IS
'����������';

insert into ykt_cur.T_CFGSPLIT (TRANSTYPE, FUNDTYPE, OFFLINEFLAG, USECARDFLAG, CALCCARDBAL, DRACCFLAG, DRSUBJNO, DRACCNO, CRACCFLAG, CRSUBJNO, CRACCNO, SUMMARY)
values (234, 3, 0, 1, 1, 'C', '2001', null, 'N', '112102','112102', '�������ѱ��˿�');
commit;