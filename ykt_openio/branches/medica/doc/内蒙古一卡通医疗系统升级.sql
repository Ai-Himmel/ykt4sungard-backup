
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
'T_MEDICALDTL-医疗收费流水表';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CUSTNAME IS
'客户名';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.STUEMPNO IS
'学/工号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.VOUCHERNO IS
'处方单号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.MEDICINES IS
'所需药品';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.MEDICALINFO IS
'病情信息';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.CARDNO IS
'缴费卡号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSDATE IS
'缴费日期';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSTIME IS
'缴费时间';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSTYPE IS
'缴费类型';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.TRANSAMT IS
'缴费金额';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.STATUS IS
'记录状态 (1录入2-扣卡失败3-扣卡成功)';

COMMENT ON COLUMN YKT_CUR.T_MEDICALDTL.REMARK IS
'备注';

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
values (108, '操作员类型', '3', '医疗系统操作员');
insert into T_DICTIONARY (DICTTYPE, DICTTYPENAME, DICTVAL, DICTCAPTION)
values (107, '网点类型', '3', '医疗系统');