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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TERMID IS
'终端编号(站点号、设备ID)';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUBSEQNO IS
'子流水号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSDATE IS
'交易日期,取系统日期';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSTIME IS
'交易时间,取系统时间';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.PAYTYPE IS
'凭证类型';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.VOUCHERNO IS
'凭证号(支票、经费本号码)';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.TRANSTYPE IS
'交易类别';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.ACCNAME IS
'帐户名';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.DCFLAG IS
'借贷';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.BALANCE IS
'帐户余额';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPSUBJNO IS
'对方科目';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPACCNO IS
'对方账号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPPACCNAME IS
'对方帐户名';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_ACCDTL.REMARK IS
'备注';

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
'账号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.ACCNAME IS
'帐户名称';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.ACCPWD IS
'帐户密码';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SINGLEMAXAMT IS
'单次消费限额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DAYCOSTMAXAMT IS
'日消费限额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DAYCOSTAMT IS
'日累计消费金额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDMAXBAL IS
'卡最大金额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.FOREGIFT IS
'押金';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.YDAYBAL IS
'昨日余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.BALANCE IS
'帐户余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.AVAILBAL IS
'可用余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.FROZEBAL IS
'冻结余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBSIDYBAL IS
'代领补助金额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.SUBSIDYNO IS
'补助批次号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDBAL IS
'卡余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.DPSCNT IS
'卡充值次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.PAYCNT IS
'卡消费次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTSUBSIDYAMT IS
'上次补助金额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTSUBSIDYNO IS
'上次补助批次号';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTCARDBAL IS
'上次卡余额';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTCARDCNT IS
'上次交易次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTDPSCNT IS
'上次卡充值次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTPAYCNT IS
'上次消费次数';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTTRANSDATE IS
'上次交易日期';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.LASTACCDATE IS
'上次清算日期';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.OPENDATE IS
'开户日期';

COMMENT ON COLUMN YKT_CUR.T_ACCOUNT.CLOSEDATE IS
'销户日期';

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
'区域编号';

COMMENT ON COLUMN YKT_CUR.T_AREA.AREANAME IS
'区域名称';

COMMENT ON COLUMN YKT_CUR.T_AREA.FAREACODE IS
'上级区域代码';

COMMENT ON COLUMN YKT_CUR.T_AREA.OLDAREACODE IS
'原区域代码';

COMMENT ON COLUMN YKT_CUR.T_AREA.AREALEVEL IS
'区域级别';

COMMENT ON COLUMN YKT_CUR.T_AREA.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_AREA.REMARK IS
'备注';

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
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.WEEKID IS
'星期ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.HOLIDAYID IS
'节假日ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.CARDVERNO IS
'名单版本号';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.ADDDELFLAG IS
'增删标志:1-增-2删';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.DOWNTIME IS
'下传时间';

COMMENT ON COLUMN YKT_CUR.T_ATTDEVCARDLIST.UPDATETIME IS
'更新时间';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.DEVSEQNO IS
'流水号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.CUSTNAME IS
'姓名';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.TRANSMARK IS
'交易标记';

COMMENT ON COLUMN YKT_CUR.T_ATTENDDTL.STATUS IS
'状态';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.PRIVILEGE IS
'授权卡权限';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.EXPIREDATE IS
'有效期';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.STATUS IS
'记录状态';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.LOSSFLAG IS
'挂失状态';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.LOSSDATE IS
'挂失日期';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.OPENDATE IS
'发卡日期';

COMMENT ON COLUMN YKT_CUR.T_AUTHCARD.CLOSEDATE IS
'注销日期';

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
'客户号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BANKCARDNO IS
'银行卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BANKCODE IS
'银行编号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.CREATEDDATE IS
'录入日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.RELATEDATE IS
'关联日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCARD.LASTSAVED IS
'最后保存时间';

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
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TRANSDATE IS
'发生日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TRANSTIME IS
'发生时间';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.CUSTNAME IS
'姓名';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.BANKCARDNO IS
'银行卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.OPTYPE IS
'1- 签约2-解约3- 同步';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.ADDDELFLAG IS
'1-增加2-删除';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDDTL.REMARK IS
'备注';

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
'记录号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.BANKCARDNO IS
'银行卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.OPTYPE IS
'1- 签约2-解约3- 同步';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.TRANSDATE IS
'处理日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.STATUS IS
'1无效记录2待处理记录3处理失败4处理成功';

COMMENT ON COLUMN YKT_CUR.T_BANKCARDTMP.REMARK IS
'备注';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKCARDNO IS
'银行卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKSN IS
'银行端流水号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.LOCALSN IS
'本地流水号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.BANKAMT IS
'银行端交易金额';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.LOCALAMT IS
'本地交易金额';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.DIFFAMT IS
'差额';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKBILL.CHKFLAG IS
'0-未补帐1-已补帐';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDATE.CHKFLAG IS
'核对标志';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.BANKCARDNO IS
'银行卡号';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKSTATUS IS
'对账状态';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKFLAG IS
'对账标志';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKOPER IS
'对账操作员';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKDATE IS
'对账日期';

COMMENT ON COLUMN YKT_CUR.T_BANKCHKDTL.CHKTIME IS
'对账时间';

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
'网点号';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHNAME IS
'网点名称';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BRANCHTYPE IS
'网点类型：1-管理中心2-充值点3-超市';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKCODE IS
'银行代码';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKACCNO IS
'银行帐户';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.BANKACCNAME IS
'银行帐户名';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.CONTACTMAN IS
'联系人';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.TEL IS
'电话';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.MOBILE IS
'手机';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.FAX IS
'传真';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.ZIPCODE IS
'邮政编码';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.OPENDATE IS
'注册日期';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.USEFLAG IS
'使用状态 0-未使用1-已使用';

COMMENT ON COLUMN YKT_CUR.T_BRANCH.LASTSAVED IS
'保存时间';

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
'卡号';

COMMENT ON COLUMN YKT_CUR.T_CARD.ACCNO IS
'卡账号';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYTYPE IS
'卡物理类型';

COMMENT ON COLUMN YKT_CUR.T_CARD.FEETYPE IS
'收费类型';

COMMENT ON COLUMN YKT_CUR.T_CARD.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_CARD.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDPWD IS
'卡密码';

COMMENT ON COLUMN YKT_CUR.T_CARD.EXPIREDATE IS
'到期日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.STATUS IS
'记录状态1-正常2-注销';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSFLAG IS
'1-挂失0-未挂失';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSDATE IS
'挂失日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOSSEFTTIME IS
'挂失生效时间';

COMMENT ON COLUMN YKT_CUR.T_CARD.FROZEFLAG IS
'1-冻结0-未冻结';

COMMENT ON COLUMN YKT_CUR.T_CARD.FROZEDATE IS
'冻结日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADFLAG IS
'1-坏卡0-不是坏卡';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADTYPE IS
'0-卡结构错误1-人为损坏2-质量问题';

COMMENT ON COLUMN YKT_CUR.T_CARD.BADDATE IS
'坏卡登记日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOCKFLAG IS
'锁定标志';

COMMENT ON COLUMN YKT_CUR.T_CARD.LOCKDATE IS
'锁定日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.OPENDATE IS
'开卡日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_CARD.CARDVERNO IS
'卡版本号';

COMMENT ON COLUMN YKT_CUR.T_CARD.LASTSAVED IS
'最后保存时间';

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
'卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CUSTNAME IS
'姓名';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.AREACODE IS
'校区';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DIFFAMT IS
'不平金额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DIFFDAYCNT IS
'不平天数';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.AVAILBAL IS
'账户当前余额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.LASTCARDBAL IS
'卡当前余额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.LASTCARDCNT IS
'账户卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATDATE IS
'统计日期';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATTIME IS
'统计时间';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STARTDATE IS
'不平开始日期';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.ENDDATE IS
'统计截止日期';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.MAXCARDCNT IS
'期间卡最大交易次数';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.CARDAFTBAL IS
'期间卡最后余额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.PAYLOSSAMT IS
'期间消费缺失金额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DPSLOSSAMT IS
'期间充值缺失金额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.TOTALLOSSAMT IS
'期间缺失总金额';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.TOTALLOSSCNT IS
'期间缺失条数';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.DEALDATE IS
'处理日期';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.OPERCODE IS
'处理操作员';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.STATUS IS
'平账状态';

COMMENT ON COLUMN YKT_CUR.T_CARDACCDIFF.REMARK IS
'备注';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BASENO IS
'基准卡流水号';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP0 IS
'位图0';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP1 IS
'位图1';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP2 IS
'位图2';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP3 IS
'位图3';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP4 IS
'位图4';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP5 IS
'位图5';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP6 IS
'位图6';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP7 IS
'位图7';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP8 IS
'位图8';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.BITMAP9 IS
'位图9';

COMMENT ON COLUMN YKT_CUR.T_CARDBITMAP.DELFLAG IS
'删除标志';

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
'记录号';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.PUTOPERCODE IS
'转交操作员';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.BATCHNO IS
'领入批次号';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.GETDATE IS
'领入日期';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.USEDATE IS
'使用日期';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.RECLAIMDATE IS
'回收日期';

COMMENT ON COLUMN YKT_CUR.T_CARDBOOK.USESTATUS IS
'使用状态';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMID IS
'终点编号';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.BRANCHNO IS
'网点号';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.USETYPE IS
'卡使用类型';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.INOUTFLAG IS
'1-收入2-支出';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.TRANSCNT IS
'交易数量';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.CARDPHYID IS
'物理卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDDTL.SHOWCARDNO IS
'显示卡号';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.CARDNO IS
'原卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDTYPE IS
'原卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDPHYID IS
'原卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDSHOWCARDNO IS
'原显示卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDCNT IS
'原卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDCARDBAL IS
'原卡余额';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.OLDSUBSIDYNO IS
'原卡补助批次号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.CARDPHYID IS
'新卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.SHOWCARDNO IS
'新卡显示卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.REVFLAG IS
'冲正标志';

COMMENT ON COLUMN YKT_CUR.T_CARDINSTEADDTL.STATUS IS
'状态';

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
'旧卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.NEWCARDNO IS
'新卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDNOCHANGE.CHANGEDATE IS
'变更日期';

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
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPENAME IS
'卡类别名称';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.USEFLAG IS
'是否启用';

COMMENT ON COLUMN YKT_CUR.T_CARDPHYTYPE.CARDPHYTYPECODE IS
'卡物理类型编码';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSFLAG IS
'交易标志';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TERMNO IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.TERMSNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.AMOUNT IS
'发生额-包含管理费';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.ADDAMT IS
'补写金额';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.MANAGEFEE IS
'管理费';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.SHOPID IS
'商户卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.STATUS IS
'状态-1初始状态2-入账失败3-成功4-异常流水';

COMMENT ON COLUMN YKT_CUR.T_CARDTRANSDTL.REMARK IS
'备注';

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
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDTYPENAME IS
'卡类别名称';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.ANONYMFLAG IS
'1-匿名0-记名';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FEETYPE IS
'默认收费类别';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.CARDCOSTFEE IS
'卡成本费';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.REUSEABLE IS
'能否重用:0-不能1-能';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RENEWABLE IS
'能否补办:0-不能1-能';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.RECYCLEABLE IS
'能否回收:0-不能1-能';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.MULTIPURSE IS
'多钱包标志';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYFLAG IS
'有效期是否固定天数';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.FIXDAYCNT IS
'有效天数';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.USEFLAG IS
'使用标志:0-未使用1已使用';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPE.PURPOSE IS
'用途';

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
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.FEETYPE IS
'收费类别';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_CARDTYPERIGHT.LASTSAVED IS
'最好保存时间';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDVERNO IS
'卡版本号';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.CARDVERTYPE IS
'标志:1-挂失2解挂3-冻结4-解冻5-新发卡6-退卡 7-换卡旧卡8换卡新卡';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.ADDDELFLAG IS
'增删标志1-添加-2删除';

COMMENT ON COLUMN YKT_CUR.T_CARDVER.STATUS IS
'记录状态1-正常-2-注销';

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
'对账类型';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKTYPENAME IS
'对账类别名称';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKFILEPATH IS
'对账文件在前置机上的路径';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.ACCCHKEXCNAME IS
'对账程序的名称';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCDRTPNO IS
'前置机节点';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCFUNCNO IS
'前置机功能号';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.BCCTIMEOUT IS
'前置机超时时间（秒）';

COMMENT ON COLUMN YKT_CUR.T_CFGACCCHK.DELFLAG IS
'是否删除前置上对账文件';

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
'银行代码';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKNAME IS
'银行名称';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKSTARTTIME IS
'银行服务开始时间';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKENDTIME IS
'银行服务截止时间';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKIP IS
'银行IP';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKPORT IS
'银行端口';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BANKTIMEOUT IS
'银行端超时时间';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCDRTPNO IS
'前置机节点';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCFUNCNO IS
'前置机功能号';

COMMENT ON COLUMN YKT_CUR.T_CFGBANK.BCCTIMEOUT IS
'前置机超时';

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
'银行代码';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDHEAD IS
'卡头';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDHEADLEN IS
'卡头长度';

COMMENT ON COLUMN YKT_CUR.T_CFGBANKCODE.CARDLEN IS
'卡全长';

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
'客户的收费类别';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.RATETYPE IS
'费率类型:1固定值- 2-百分比3-以输入值作为收费金额';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.RATEAMT IS
'费率';

COMMENT ON COLUMN YKT_CUR.T_CFGFEE.REMARK IS
'备注';

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
'客户的收费类别';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.SUMMARY IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.ENABLED IS
'是否启用';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.ONLINEPAY IS
'0-不联机1联机';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PAYCHKFLAG IS
'1需要0不需要';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PAYEEACCTYPE IS
'0-输入1卡号2客户号3学号';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.BCCFUNCNO IS
'BCC主功能号';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.BCCDRTPNO IS
'BCCDRTP节点号';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.IP IS
'商户服务IP';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.PORT IS
'商户服务端口';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.TIMEOUT IS
'商户超时时间(秒)';

COMMENT ON COLUMN YKT_CUR.T_CFGPAYMENT.LASTSAVED IS
'最后保存时间';

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
'商户号';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.AMOUNT IS
'商户金额';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.AGIO IS
'折扣返回率';

COMMENT ON COLUMN YKT_CUR.T_CFGRAKEOFF.REMARK IS
'备注';

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
'商户号';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.FEETYPE IS
'卡收费类别';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.FEERATE IS
'费率';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_CFGSHOPFEE.LASTSAVED IS
'最后保存时间';

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
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.FUNDTYPE IS
'资金类型';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.OFFLINEFLAG IS
'脱机标志1-脱机0-联机';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.USECARDFLAG IS
'卡交易标志';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CALCCARDBAL IS
'计算卡余额标志';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRACCFLAG IS
'借方标志';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRSUBJNO IS
'借方科目';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.DRACCNO IS
'借方账号';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRACCFLAG IS
'贷方标志';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRSUBJNO IS
'贷方科目';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.CRACCNO IS
'贷方账号';

COMMENT ON COLUMN YKT_CUR.T_CFGSPLIT.SUMMARY IS
'摘要';

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
'客户的收费类别';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.RATETYPE IS
'费率类型:1定额- 2-百分比3-以输入金额为准';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.RATEAMT IS
'费率';

COMMENT ON COLUMN YKT_CUR.T_CFGTRANS.REMARK IS
'备注';

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
'配置类型';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.CFGVERNO IS
'配置版本';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_CFGVER.LASTSAVED IS
'最后保存时间';

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
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.STARTNO IS
'客户起始号';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.NEXTNO IS
'客户当前号';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.ENDNO IS
'客户结束号';

COMMENT ON COLUMN YKT_CUR.T_CUSTIDCTL.LASTSAVED IS
'最后保存时间';

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
'客户号';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTTYPE IS
'客户类型';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.FEETYPE IS
'收费类别';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.STATUS IS
'状态1-正常2-注销';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTNAME IS
'客户名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DEPTCODE IS
'部门代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.DEPTFULLNAME IS
'部门全称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.SPECIALTYCODE IS
'专业代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLASSCODE IS
'班级代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLASSNAME IS
'班级名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDTYPE IS
'证件类型';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.IDNO IS
'证件号码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.SEX IS
'性别';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.COUNTRY IS
'国籍';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.NATION IS
'民族';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EMAIL IS
'电子信箱';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.TEL IS
'电话';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.MOBILE IS
'手机';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.ZIPCODE IS
'邮政编码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CUSTATTR IS
'客户属性';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.INDATE IS
'入校日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OUTDATE IS
'预计离校日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OPENDATE IS
'注册日期,指的是客户信息添加进来的日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.OPENFLAG IS
'正式卡开通标志';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.HOLDCARDCNT IS
'拥有卡个数';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.USEFLAG IS
'使用标志';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.EACCFLAG IS
'电子钱包开通标志';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMER.LASTSAVED IS
'最后保存时间';

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
'导入批次号或同步时间';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SEQNO IS
'导入序号';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.TRANSDATE IS
'导入日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.OPERCODE IS
'导入操作员';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTTYPE IS
'客户类型';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTTYPENAME IS
'客户类别名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.FEETYPE IS
'收费类别';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CUSTNAME IS
'客户名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.DEPTCODE IS
'部门代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.DEPTNAME IS
'部门名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SPECIALTYCODE IS
'专业代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CLASSNAME IS
'班级名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.IDTYPE IS
'证件类型';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.IDNO IS
'证件号码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SEX IS
'性别';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.COUNTRY IS
'国籍';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.NATION IS
'民族';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.EMAIL IS
'电子信箱';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.TEL IS
'电话';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.MOBILE IS
'手机';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ZIPCODE IS
'邮政编码';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.INDATE IS
'入校日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.OUTDATE IS
'离校日期';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.SYNCFLAG IS
'1-同步数据0-非同步数据';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.CHKFLAG IS
'0-未审核1-审核失败2审核通过';

COMMENT ON COLUMN YKT_CUR.T_CUSTOMERTMP.ERRMSG IS
'错误信息';

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
'客户类型';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.CUSTTYPENAME IS
'客户类型名称';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.FEETYPE IS
'默认收费类别';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.AREACODE IS
'学校代码';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.OLDCUSTTYPE IS
'原客户类别';

COMMENT ON COLUMN YKT_CUR.T_CUSTTYPE.USEFLAG IS
'使用标志';

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
'部门代码';

COMMENT ON COLUMN YKT_CUR.T_DEPT.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTNAME IS
'部门名称';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTENAME IS
'部门英文名';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTFULLNAME IS
'部门全称';

COMMENT ON COLUMN YKT_CUR.T_DEPT.FDEPTCODE IS
'上级部门代码';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTLEVEL IS
'部门级别';

COMMENT ON COLUMN YKT_CUR.T_DEPT.DEPTTYPE IS
'0部门1班级';

COMMENT ON COLUMN YKT_CUR.T_DEPT.OLDDEPTCODE IS
'原部门代码';

COMMENT ON COLUMN YKT_CUR.T_DEPT.USEFLAG IS
'使用标志:0-未使用1-已使用';

COMMENT ON COLUMN YKT_CUR.T_DEPT.LASTSAVED IS
'最后保存日期';

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
'终端编号也是设备编号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVICENAME IS
'设备名称';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVPHYID IS
'设备物理ID★';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVICENO IS
'设备机号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVPHYTYPE IS
'设备厂商代码';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVTYPECODE IS
'设备类型★';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVVERNO IS
'设备版本号★';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDPHYTYPE IS
'卡物理型号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.FDEVICEID IS
'上级设备ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.RUNSTATUS IS
'运行状态';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.STATUS IS
'状态:1-正常2-注销';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SVRPORTCNT IS
'端口总数';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SVRPORTNO IS
'服务器接口编号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.COMMTYPE IS
'通讯方式:1-串口2-MODEM3-TCPIP 9-级联';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.IP IS
'IP地址';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.PORTNO IS
'服务器SOCKET端口号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.BAUDRATE IS
'波特率';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDSET IS
'终端允许使用的卡收费类别';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CARDVERNO IS
'卡黑名单版本号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTSEQNO IS
'上次设备交易流水号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTTRANSTIME IS
'上次交易时间';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.PURSENO IS
'设备读卡的钱包号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.MAXAMT IS
'最大充值限额，单位分';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.SYSID IS
'前置机系统ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DOORLSTVER IS
'用于记录已经记录消息队列的名单版本';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.DEVUSAGE IS
'设备用途';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.OPENDATE IS
'注册日期';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.LASTSAVED IS
'上次修改日期';

COMMENT ON COLUMN YKT_CUR.T_DEVICE.REMARK IS
'备注';

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
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SEQNO IS
'导入序列号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.TRANSDATE IS
'导入日期';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.TRANSTIME IS
'导入时间';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.OPERCODE IS
'导入操作员';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVICENAME IS
'设备名称';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVPHYID IS
'设备物理ID★';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVPHYTYPE IS
'设备厂商代码';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVTYPECODE IS
'设备类型★';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVICENO IS
'设备机号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.FDEVICEID IS
'上级设备ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.CARDPHYTYPE IS
'卡物理型号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.COMMTYPE IS
'通讯方式:1-串口2-MODEM3-TCPIP 9-级联';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.IP IS
'IP地址';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.PORTNO IS
'通讯端口号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SVRPORTNO IS
'服务器接口编号';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SVRPORTCNT IS
'端口总数';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.SYSID IS
'前置机系统ID';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.DEVUSAGE IS
'设备用途';

COMMENT ON COLUMN YKT_CUR.T_DEVICETMP.ERRMSG IS
'错误信息';

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
'终端编号也是设备编号';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.OPTIME IS
'OPTIME';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.DEVTIME IS
'DEVTIME';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.BEATSTATUS IS
'BEATSTATUS';

COMMENT ON COLUMN YKT_CUR.T_DEVMONITOR.CARDVERNO IS
'卡版本号';

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
'字典类型';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTTYPENAME IS
'字典类型名称';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTVAL IS
'字典值';

COMMENT ON COLUMN YKT_CUR.T_DICTIONARY.DICTCAPTION IS
'字典名称';

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
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.CARDVERNO IS
'名单版本号';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_DOORCARD.INSERTDATE IS
'更新时间';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.USEFLAG IS
'USEFLAG';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.LISTID IS
'LISTID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.CTRLID IS
'CTRLID';

COMMENT ON COLUMN YKT_CUR.T_DOORCARDADDR.ADDDELFLAG IS
'增删标志';

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
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.WEEKID IS
'星期ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.HOLIDAYID IS
'节假日ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.CARDVERNO IS
'名单版本号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.ADDDELFLAG IS
'增删标志:1-增-2删';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.DOWNTIME IS
'下传时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVCARDLIST.UPDATETIME IS
'更新时间';

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
'主设备ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.MINORDEVID IS
'从设备ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.HOLIDAYID IS
'假日ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.SEQNO IS
'序号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.DOWNTIME IS
'下载时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.REFCNT IS
'REFCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVHOLIDAY.UPDATETIME IS
'最后保存时间';

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
'时间段ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.SEQNO IS
'序号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIME.DOWNTIME IS
'下传时间';

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
'时间段组ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.SEQNO IS
'流水号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.DOWNTIME IS
'下传时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.REFCNT IS
'引用次数';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVTIMEGRP.UPDATETIME IS
'最后保存时间';

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
'星期ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.SEQNO IS
'流水号';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.DOWNTIME IS
'下传时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.REFCNT IS
'REFCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.LINKCNT IS
'LINKCNT';

COMMENT ON COLUMN YKT_CUR.T_DOORDEVWEEK.UPDATETIME IS
'最后保存时间';

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
'编号';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDVERNO IS
'名单版本号';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CTRLID IS
'CTRLID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.SYSID IS
'SYSID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.RIGHTBIT IS
'权限';

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
'状态';

COMMENT ON COLUMN YKT_CUR.T_DOORDOWNLOAD.ADDDELFLAG IS
'增删标志';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.DEVSEQNO IS
'流水号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.CUSTNAME IS
'客户姓名';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.TRANSMARK IS
'交易标记';

COMMENT ON COLUMN YKT_CUR.T_DOORDTL.SYSID IS
'子系统ID';

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
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.EVENTCODE IS
'事件代码';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.EVENTMSG IS
'事件消息';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.SYSID IS
'子系统ID';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_DOOREVENTDTL.COLTIME IS
'采集时间';

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
'组号';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.GROUPNAME IS
'组名称';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_DOORGROUP.UPDATETIME IS
'更新时间';

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
'组号';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPMEMBER.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPMEMBER.UPDATETIME IS
'更新时间';

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
'组号';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPOPERRIGHT.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_DOORGRPOPERRIGHT.UPDATETIME IS
'更新时间';

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
'节假日ID';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.HOLIDAYNAME IS
'节假日名';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.DAYCNT IS
'节假日天数';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAY.UPDATETIME IS
'最后保存时间';

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
'时间组ID';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.ADDDELFLAG IS
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORHOLIDAYTIME.UPDATETIME IS
'最后保存时间';

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
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOOROPERRIGHT.OPERCODE IS
'操作员号';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DOORRPTDAY.TOTALCNT IS
'总次数';

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
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORTIME.DOWNSTATUS IS
'下传状态';

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
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.DOWNSTATUS IS
'下传状态';

COMMENT ON COLUMN YKT_CUR.T_DOORTIMEGRP.UPDATETIME IS
'更新时间';

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
'星期ID';

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
'增删标志';

COMMENT ON COLUMN YKT_CUR.T_DOORWEEKTIME.DOWNSTATUS IS
'下传状态';

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
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEVLIMITFLAG IS
'使用限制标志';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.SHOPOPERFLAG IS
'充值商户操作员标志';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.OPENDATE IS
'开户日期';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.MAXDEPOSITAMT IS
'最大充值金额';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEPOSITCNT IS
'总充值次数';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.DEPOSITAMT IS
'总充值金额';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTTRANSDATE IS
'最后充值日期';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTDEVPHYID IS
'最后充值设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTDEVSEQNO IS
'上次设备流水号';

COMMENT ON COLUMN YKT_CUR.T_DPSOPER.LASTSAVED IS
'最后保存时间';

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
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.OPENOPER IS
'注册操作员';

COMMENT ON COLUMN YKT_CUR.T_DPSOPERPOS.LASTSAVED IS
'最后保存时间';

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
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_DPSSHOPPOS.LASTSAVED IS
'最后保存时间';

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
'错误码';

COMMENT ON COLUMN YKT_CUR.T_ERRCODE.ERRMSG IS
'错误消息';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDNO IS
'卡号';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.DPSCNT IS
'卡充值次数';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.PAYCNT IS
'卡消费次数';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDBEFBAL IS
'卡交易前余额';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.CARDAFTBAL IS
'卡交易后余额';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.FAILTYPE IS
'0-中途拔卡1写卡失败';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.STATUS IS
'0-未处理2失败3成功';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.REMARK IS
'备注';

COMMENT ON COLUMN YKT_CUR.T_EXCEPTDTL.LASTSAVED IS
'最后保存时间';

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
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.ACCDATE IS
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.CARDNO IS
'正为加钱负为减钱';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.AMOUNT IS
'补写金额';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TRANSDATE IS
'处理日期';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.TRANSTIME IS
'处理时间';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.STATUS IS
'1未补写2已补写3已下补助';

COMMENT ON COLUMN YKT_CUR.T_EXTCARDDTL.REMARK IS
'补写原因';

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
'收费类别';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.FEENAME IS
'收费名称';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.BOARDFEEFLAG IS
'是否收搭伙费:1-收0-不收';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.USEFLAG IS
'使用标志';

COMMENT ON COLUMN YKT_CUR.T_FEETYPE.REMARK IS
'备注';

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
'参数名称';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.PARAVAL IS
'参数值';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.REMARK IS
'备注';

COMMENT ON COLUMN YKT_CUR.T_GDCTPARA.PARAFLAG IS
'参数标志';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.DEVICEID IS
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.USETYPE IS
'0-管理卡-1-常开卡';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.ADDDELFLAG IS
'1-增加2-删除';

COMMENT ON COLUMN YKT_CUR.T_GETELECCARD.DOWNTIME IS
'下载时间';

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
'账号';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.ACCNAME IS
'帐户名';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.YDAYBAL IS
'昨日余额';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.BALANCE IS
'帐户余额';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.BALFLAG IS
'余额方向';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.LASTTRANSDATE IS
'上次交易日期';

COMMENT ON COLUMN YKT_CUR.T_INNERACC.LASTACCDATE IS
'上次清算日期';

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
'密钥ID';

COMMENT ON COLUMN YKT_CUR.T_KEYS.KEYVAL IS
'密钥值';

COMMENT ON COLUMN YKT_CUR.T_KEYS.REMARK IS
'备注';

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
'卡号';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.CARDPHYID IS
'物理卡号';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.SHOPCODE IS
'登记商户代码';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REGDATE IS
'登记日期';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REGTIME IS
'登记时间';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.STATUS IS
'遗失卡状态';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.ENDDATE IS
'保存截至日期';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETCARDPLACE IS
'卡片所在位置';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.TEL IS
'联系电话';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.ADDR IS
'商户地点';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.IDTYPE IS
'领取人证件类型';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.IDNO IS
'证件号码';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETDATE IS
'领取日期';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.GETTIME IS
'领取时间';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDINFO.REMARK IS
'备注';

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
'登陆商户号';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.SHOPNAME IS
'商户名称';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.ADDR IS
'商户地点';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.TEL IS
'联系电话';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.GETCARDPLACE IS
'领取卡片地点';

COMMENT ON COLUMN YKT_CUR.T_LOSSCARDSHOP.LASTSAVED IS
'最后修改时间';

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
'机器码';

COMMENT ON COLUMN YKT_CUR.T_MACHINECODE.IP IS
'IP地址';

COMMENT ON COLUMN YKT_CUR.T_MACHINECODE.LASTSAVED IS
'最后保存时间';

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
'餐次ID';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.MEALNAME IS
'餐次名称';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.ENDTIME IS
'结束时间';

COMMENT ON COLUMN YKT_CUR.T_MEALTYPE.LASTSAVED IS
'更新时间';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDATE.CHKFLAG IS
'核对标志';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CARDNO IS
'卡号';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.MOBILE IS
'手机号';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKSTATUS IS
'对账状态';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKFLAG IS
'对账标志';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKOPER IS
'对账操作员';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKDATE IS
'对账日期';

COMMENT ON COLUMN YKT_CUR.T_MOBILECHKDTL.CHKTIME IS
'对账时间';

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
'客户号';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.ENROLLNO IS
'录取通知号';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.MODIFYDATE IS
'修改日期';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.MODIFYTIME IS
'修改时间';

COMMENT ON COLUMN YKT_CUR.T_MODIFYINFO.OPERCODE IS
'操作员号';

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
'模块代码';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.MODULENAME IS
'模块名';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.MENUSET IS
'菜单集';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.FUNCSET IS
'功能集';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_MODULEAUTH.LASTSAVED IS
'最后保存时间';

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
'消息ID';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MSGTYPE IS
'消息类型';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MSGLEVEL IS
'消息级别';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SYSID IS
'子系统编号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.CREATEDTIME IS
'消息生成时间';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.STARTTIME IS
'消息开始处理时间';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ENDTIME IS
'消息处理完成时间';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.REQDATA IS
'消息请求内容';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.RESPDATA IS
'消息应答内容';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.FUNCNO IS
'功能号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.PFUNCNO IS
'父功能号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.MAXSENDCNT IS
'最大发送次数';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SENDCNT IS
'发送次数';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.RECVCNT IS
'接收次数';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.STATUS IS
'消息状态';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.SEQNO IS
'序号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.ERRMSG IS
'错误消息';

COMMENT ON COLUMN YKT_CUR.T_MSGLIST.DELFLAG IS
'删除标志';

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
'账号';

COMMENT ON COLUMN YKT_CUR.T_NETACC.ACCNAME IS
'帐户名';

COMMENT ON COLUMN YKT_CUR.T_NETACC.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_NETACC.ACCPWD IS
'帐户密码';

COMMENT ON COLUMN YKT_CUR.T_NETACC.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_NETACC.STOPPAYFLAG IS
'止付标志';

COMMENT ON COLUMN YKT_CUR.T_NETACC.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_NETACC.YDAYBAL IS
'昨日余额';

COMMENT ON COLUMN YKT_CUR.T_NETACC.BALANCE IS
'帐户余额';

COMMENT ON COLUMN YKT_CUR.T_NETACC.AVAILBAL IS
'可用余额';

COMMENT ON COLUMN YKT_CUR.T_NETACC.FROZEBAL IS
'冻结余额';

COMMENT ON COLUMN YKT_CUR.T_NETACC.LASTTRANSDATE IS
'上次交易日期';

COMMENT ON COLUMN YKT_CUR.T_NETACC.LASTACCDATE IS
'上次清算日期';

COMMENT ON COLUMN YKT_CUR.T_NETACC.OPENDATE IS
'开户日期';

COMMENT ON COLUMN YKT_CUR.T_NETACC.CLOSEDATE IS
'销户日期';

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
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.STUEMPNO IS
'学号';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.EXPIREDATE IS
'卡有效期';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.BATCHNO IS
'批次号';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.SEQNO IS
'顺序号';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.OLDCARDPHYID IS
'旧卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_NEWCARDCHANGE.LASTSAVED IS
'最后保存时间';

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
'操作员代码';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERTYPE IS
'操作员类型';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.BRANCHNO IS
'所属网点号';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.CARDNO IS
'操作员卡号';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERNAME IS
'操作员姓名';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.TEL IS
'电话';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.MOBILE IS
'手机';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.EMAIL IS
'电子邮箱';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.ZIPCODE IS
'邮政编码';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPERPWD IS
'密码';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.STATUS IS
'状态:0-锁定1-正常2-注销';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LASTTRANSDATE IS
'最后交易日期:充值操作员使用';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.MENUSET IS
'菜单权限集';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.FUNCSET IS
'功能权限集';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.RIGHTFLAG IS
'权限标志';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.SITELIMIT IS
'是否有站点限制:0-无限制1-有限制';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINFLAG IS
'登录标志:0-未登录1-已登录';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINSITENO IS
'登录站点号';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGINTIME IS
'登录时间';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.LOGOUTTIME IS
'签出时间';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.FAILNUMBER IS
'登录失败次数';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.OPENDATE IS
'注册日期';

COMMENT ON COLUMN YKT_CUR.T_OPERATOR.CLOSEDATE IS
'注销日期';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMID IS
'站点号';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TERMSEQNO IS
'站点流水号';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSTIME IS
'发生时间';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.CHKOPER IS
'审核操作员';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.STATUS IS
'流水状态1-未处理2-失败3-成功4-冲正';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.TRANSINFO IS
'交易信息';

COMMENT ON COLUMN YKT_CUR.T_OPERDTL.REQDATA IS
'请求数据';

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
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_OPERSITE.SITENO IS
'站点号';

COMMENT ON COLUMN YKT_CUR.T_OPERSITE.LASTSAVED IS
'最后保存时间';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.ACCNAME IS
'账户名';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.AMOUNT IS
'金额';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYBANKACCNO IS
'付款方银行账号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYBANKACCNAME IS
'付款方银行账户名';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYEEBANKACCNO IS
'收款方银行账号';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.PAYEEBANKACCNAME IS
'收款方银行账户名';

COMMENT ON COLUMN YKT_CUR.T_PAYMENTDTL.OPERCODE IS
'操作员号';

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
'客户号';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTO IS
'照片';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MINPHOTO IS
'小照片';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTODATE IS
'拍照日期';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTOTIME IS
'拍照时间';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.IFCARD IS
'是否有卡';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MAKECARDDATE IS
'制卡日期';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.MAKECARDTIME IS
'制卡时间';

COMMENT ON COLUMN YKT_CUR.T_PHOTO.PHOTOEXACTTIME IS
'更新时间';

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
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERNAME IS
'操作员名称';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERPWD IS
'操作员密码';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.OPERLIMIT IS
'权限';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.ENABLED IS
'是否可用';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.BEGINDATE IS
'生效日期';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.ENDDATE IS
'失效日期';

COMMENT ON COLUMN YKT_CUR.T_PHOTOLIMIT.REMARK IS
'备注';

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
'任务编号,取最大值加1';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.SUMMARY IS
'任务说明';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGNAME IS
'程序名';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGPATH IS
'程序路径';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.PROGARGV IS
'命令行参数';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.DIALY IS
'每天一次,取值范围0-1,0表示禁用';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.WEEKLY IS
'每星期一次,取值范围0-7,0表示禁用';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.MONTHLY IS
'每月一次,取值范围0-31,0表示禁用';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.STARTTIME IS
'运行开始时间';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.ENDTIME IS
'运行结束时间';

COMMENT ON COLUMN YKT_CUR.T_PLANTASK.USEFLAG IS
'是否启用';

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
'运行日期';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.STARTTIME IS
'运行时间';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.TASKNO IS
'任务编号';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.PROGNAME IS
'程序名';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.ENDTIME IS
'运行结束时间，格式为yyyy-mm-dd hh:mm:ss';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.RUNSTATUS IS
'运行状态:0-运行中,1-成功,2-失败';

COMMENT ON COLUMN YKT_CUR.T_PLANTASKLOG.SUMMARY IS
'运行结果说明';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.AMOUNT IS
'发生额-包含管理费';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.MANAGEFEE IS
'管理费';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSMARK IS
'交易标记';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DATATYPE IS
'数据类型';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SHOPID IS
'商户卡号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SUBSIDYNO IS
'补助批次号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.SYSID IS
'子系统ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ACCDATE IS
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.STATUS IS
'状态-1初始状态2-入账失败3-成功4-异常流水';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.ERRMSG IS
'错误信息';

COMMENT ON COLUMN YKT_CUR.T_POSDTL.DELFLAG IS
'删除标志';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.SHOPID IS
'商户卡号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.AMOUNT IS
'发生额-包含管理费';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.MANAGEFEE IS
'管理费';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TRANSMARK IS
'交易标记';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.SEQNO IS
'导入序号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPDATE IS
'录入日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPTIME IS
'录入日期';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.IMPOPER IS
'录入操作员号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.TERMSEQNO IS
'录入流水号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.STATUS IS
'流水状态:1-录入2-审核失败3-已审核';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.ERRMSG IS
'错误信息';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CHKOPER IS
'审核操作员号';

COMMENT ON COLUMN YKT_CUR.T_POSDTLTMP.CHKDATE IS
'审核日期';

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
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_POSSEQNO.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_POSSEQNO.TRANSDATE IS
'交易日期';

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
'卡号';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CARDVER IS
'卡版本号';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.TERMNO IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.STARTDATE IS
'启用日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.EXPIREDATE IS
'过期日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.KEYINDEX IS
'密钥索引';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DEVICEID IS
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DEVJOINTIME IS
'设备绑定日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.PUBLISHID IS
'发行方ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.USERID IS
'用户ID';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.OPENDATE IS
'注册日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.CLOSEDATE IS
'关闭日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.DISABLEDATE IS
'停用日期';

COMMENT ON COLUMN YKT_CUR.T_PSAMCARD.LASTSAVED IS
'最后保存时间';

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
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_PURSE.PURSENAME IS
'钱包名';

COMMENT ON COLUMN YKT_CUR.T_PURSE.CARDMAXBAL IS
'最大存款金额';

COMMENT ON COLUMN YKT_CUR.T_PURSE.USEFLAG IS
'使用标志0-未使用1-已使用';

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
'任务号';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.TASKSEQ IS
'任务序号';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.FUNCNO IS
'FUNCNO';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.FUNCGROUP IS
'FUNCGROUP';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.SYSID IS
'SYSID';

COMMENT ON COLUMN YKT_CUR.T_PUSHTASK.DEVICEID IS
'设备编号';

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
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_REFNO.MAC IS
'MAC码';

COMMENT ON COLUMN YKT_CUR.T_REFNO.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_REFNO.ACCDATE IS
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_REFNO.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_REFNO.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_REFNO.LASTSAVED IS
'最后保存时间';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.BALFLAG IS
'余额方向';

COMMENT ON COLUMN YKT_CUR.T_RPTACCBAL.BALANCE IS
'余额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.BALFLAG IS
'余额方向';

COMMENT ON COLUMN YKT_CUR.T_RPTACCLEDGER.BALANCE IS
'余额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.BALFLAG IS
'余额方向';

COMMENT ON COLUMN YKT_CUR.T_RPTDAILYACC.BALANCE IS
'余额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.DEPTCODE IS
'部门代码';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTDEPTLEDGER.CRAMT IS
'贷方发生额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.BRANCHNO IS
'网点号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.CARDTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.USETYPE IS
'使用类型';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.INCNT IS
'收入数量';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.OUTCNT IS
'支出数量';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCARD.REMAINCNT IS
'库存数量';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.BRANCHNO IS
'网点号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.TRANSTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.INAMT IS
'收入发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.OUTAMT IS
'支出发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERCASH.AMOUNT IS
'结存金额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSTYPE IS
'卡类型';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTOPERLEDGER.CRAMT IS
'贷方发生额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSLEDGER.AMOUNT IS
'结存金额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.DEVICEID IS
'设备编号';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.MEALTYPE IS
'餐次类型';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.MEALNAME IS
'餐次名称';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTPOSMEAL.AMOUNT IS
'结存金额';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPBOARD.TRANSAMT IS
'发生额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT1 IS
'早餐交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT1 IS
'早餐金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT2 IS
'午餐交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT2 IS
'午餐金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT3 IS
'晚餐交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT3 IS
'晚餐金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSCNT4 IS
'夜餐交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPMEAL.TRANSAMT4 IS
'夜餐金额';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.ACCNAME IS
'商户账户名';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.RAKEOFFRATE IS
'佣金费率';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.TRANSAMT IS
'营业金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.RAKEOFFAMT IS
'佣金金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.AMOUNT IS
'结算金额';

COMMENT ON COLUMN YKT_CUR.T_RPTSHOPRAKEOFF.BALANCE IS
'余额';

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
'结算日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.BEGINBAL IS
'期初余额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.BEGINBALFLAG IS
'期初余额方向';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.ENDBAL IS
'期末余额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJBAL.ENDBALFLAG IS
'期末余额方向';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.CRAMT IS
'贷方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.BALFLAG IS
'余额方向';

COMMENT ON COLUMN YKT_CUR.T_RPTSUBJLEDGER.BALANCE IS
'余额';

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
'结算日期';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMID IS
'统计项目编号';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMNAME IS
'统计项目名称';

COMMENT ON COLUMN YKT_CUR.T_RPTSYSSTAT.ITEMVAL IS
'统计数据';

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
'业务日期';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.ACCNO IS
'账号';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TRANSTYPE IS
'交易类型';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.TRANSCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.DRAMT IS
'借方发生额';

COMMENT ON COLUMN YKT_CUR.T_RPTTERMLEDGER.CRAMT IS
'贷方发生额';

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
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_SEQNOCTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_SEQNOCTL.ACCDATE IS
'记账日期';

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
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOP.FSHOPID IS
'上级商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOP.AREACODE IS
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPTCODE IS
'部门代码';

COMMENT ON COLUMN YKT_CUR.T_SHOP.SHOPNAME IS
'商户名';

COMMENT ON COLUMN YKT_CUR.T_SHOP.SHOPTYPE IS
'商户类型1-收费商户2-充值商户';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ACCFLAG IS
'是否独立核算：1-独立核算0-否';

COMMENT ON COLUMN YKT_CUR.T_SHOP.STATUS IS
'商户状态 1-正常2-销户';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_SHOP.CONTACTMAN IS
'负责人';

COMMENT ON COLUMN YKT_CUR.T_SHOP.IDTYPE IS
'证件类型';

COMMENT ON COLUMN YKT_CUR.T_SHOP.IDNO IS
'证件号码';

COMMENT ON COLUMN YKT_CUR.T_SHOP.TEL IS
'电话';

COMMENT ON COLUMN YKT_CUR.T_SHOP.MOBILE IS
'手机';

COMMENT ON COLUMN YKT_CUR.T_SHOP.EMAIL IS
'电子信箱';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ADDR IS
'地址';

COMMENT ON COLUMN YKT_CUR.T_SHOP.ZIPCODE IS
'邮政编码';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BOARDFEEFLAG IS
'是否收搭伙费';

COMMENT ON COLUMN YKT_CUR.T_SHOP.RAKEOFFTYPE IS
'佣金类型';

COMMENT ON COLUMN YKT_CUR.T_SHOP.RAKEOFFRATE IS
'佣金费率';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITAGIO IS
'存款折扣率';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITCNT IS
'存款次数';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DEPOSITAMT IS
'存款总金额';

COMMENT ON COLUMN YKT_CUR.T_SHOP.DISCOUNTAMT IS
'折扣总金额';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKCODE IS
'银行代码';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKACCNO IS
'银行帐号';

COMMENT ON COLUMN YKT_CUR.T_SHOP.BANKACCNAME IS
'银行帐户名';

COMMENT ON COLUMN YKT_CUR.T_SHOP.OPENDATE IS
'开户日期';

COMMENT ON COLUMN YKT_CUR.T_SHOP.CLOSEDATE IS
'销户日期';

COMMENT ON COLUMN YKT_CUR.T_SHOP.USEFLAG IS
'使用标志';

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
'账号';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.ACCNAME IS
'帐户名';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.SUBJNO IS
'科目号';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.ACCPWD IS
'帐户密码';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.STATUS IS
'状态';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.YDAYBAL IS
'昨日余额';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.BALANCE IS
'帐户余额';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.AVAILBAL IS
'可用余额';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.FROZEBAL IS
'冻结余额';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.LASTTRANSDATE IS
'上次交易日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.LASTACCDATE IS
'上次清算日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.OPENDATE IS
'开户日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPACC.CLOSEDATE IS
'销户日期';

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
'卡号';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CARDPHYID IS
'卡物理ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CARDPWD IS
'卡密码';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.EXPIREDATE IS
'到期日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.STATUS IS
'记录状态1-正常2-注销';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LOSSFLAG IS
'1-挂失0-未挂失';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LOSSDATE IS
'挂失日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.OPENDATE IS
'开卡日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.CLOSEDATE IS
'注销日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPCARD.LASTSAVED IS
'最后保存时间';

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
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ACCNO IS
'商户账号';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME1 IS
'早餐结束时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME2 IS
'午餐结束时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME3 IS
'晚餐结束时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.ENDTIME4 IS
'夜餐结束时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_SHOPMEAL.LASTSAVED IS
'最后保存时间';

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
'记录编号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.DEVICEID IS
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.ENDTIME IS
'截止时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.REMARK IS
'备注';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.STARTDATE IS
'启用日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.ENDDATE IS
'停用日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.STATUS IS
'1-正常2-过期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOS.LASTSAVED IS
'最好保存时间';

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
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.SEQNO IS
'导入顺序号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.TRANSDATE IS
'导入日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.TRANSTIME IS
'导入时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.OPERCODE IS
'导入操作员';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.DEVICEID IS
'设备ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.SHOPID IS
'商户号';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ENDTIME IS
'截止时间';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.STARTDATE IS
'启用日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ENDDATE IS
'停用日期';

COMMENT ON COLUMN YKT_CUR.T_SHOPPOSTMP.ERRMSG IS
'错误信息';

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
'站点号';

COMMENT ON COLUMN YKT_CUR.T_SITE.SITENAME IS
'站点名称';

COMMENT ON COLUMN YKT_CUR.T_SITE.IP IS
'IP地址';

COMMENT ON COLUMN YKT_CUR.T_SITE.MACHINECODE IS
'机器码';

COMMENT ON COLUMN YKT_CUR.T_SITE.LASTSAVED IS
'最后保存时间';

COMMENT ON COLUMN YKT_CUR.T_SITE.REMARK IS
'备注';

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
'专业代码';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.SPECIALTYNAME IS
'专业名称';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.USEFLAG IS
'使用标志';

COMMENT ON COLUMN YKT_CUR.T_SPECIALTY.LASTSAVED IS
'最后保存时间';

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
'科目号';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJNAME IS
'科目名称';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJTYPE IS
'科目类型';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.BALFLAG IS
'科目余额方向';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.FSUBJNO IS
'上级科目号';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.SUBJLEVEL IS
'科目级别';

COMMENT ON COLUMN YKT_CUR.T_SUBJECT.ENDFLAG IS
'末级标志';

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
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SEQNO IS
'导入序号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUBSIDYNO IS
'补助批次号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUMMARY IS
'摘要';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.BROKERNAME IS
'经办人姓名';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.BROKERIDNO IS
'经办人身份证号';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PAYTYPE IS
'支付方式:1-现金2-支票3-经费本';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.VOUCHERNO IS
'凭证号码';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.SUBSIDYTYPE IS
'补助类型';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.IMPDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.IMPTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PUTDATE IS
'下发日期';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.PUTTIME IS
'下发时间';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.GETDATE IS
'领取日期';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.GETTIME IS
'领取时间';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.STATUS IS
'状态:1-未下发2-已下发3-已领取-4-无效';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.ERRMSG IS
'错误信息';

COMMENT ON COLUMN YKT_CUR.T_SUBSIDY.OPERCODE IS
'操作员号';

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
'子系统ID';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.WORKMODE IS
'工作模式';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BEATINTERVAL IS
'心跳间隔';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.BEATCNTLIMIT IS
'心跳次数限制';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQBEATFUNCNO IS
'心跳发送功能号';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQDEVFUNCNO IS
'请求设备信息功能号';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.REQTASKFUNCNO IS
'请求任务功能号';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.RESPFUNCNO IS
'应答功能号';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.EXECTIMEOUT IS
'执行超时时间';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.COLINTERVAL IS
'采集间隔';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.QRYINTERVAL IS
'查询任务间隔';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSPARA.TASKMAXLIMIT IS
'任务最大限制';

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
'区域代码';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SERVERID IS
'SERVERID';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.MACADDR IS
'MACADDR';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.IP IS
'IP';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.PORT IS
'PORT';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.CARDVERNO IS
'卡版本号';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.INITKEY IS
'INITKEY';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.DYNAKEY IS
'DYNAKEY';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.SYNCTIME IS
'SYNCTIME';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.RUNSTATUS IS
'运行状态';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.STATUS IS
'STATUS';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.OPENDATE IS
'注册日期';

COMMENT ON COLUMN YKT_CUR.T_SUBSYSTEM.CLOSEDATE IS
'注销日期';

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
'最大值';

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
'参数ID';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARAVAL IS
'参数值';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARANAME IS
'参数名称';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.PARAUNIT IS
'单位';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.DISPLAYFLAG IS
'是否显示';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.REMARK IS
'备注';

COMMENT ON COLUMN YKT_CUR.T_SYSPARA.LASTSAVED IS
'最后保存时间';

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
'交易码';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.TRANSNAME IS
'交易名称';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.LOGFLAG IS
'是否记录操作员日志:0-不记录1-只记录成功流水2-只记录失败3-成功失败都记录';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.LIMITFLAG IS
'是否限制操作员:0不限制1-限制';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.FEEFLAG IS
'收费标志';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.TRANSFLAG IS
'交易标志';

COMMENT ON COLUMN YKT_CUR.T_TRANSCODE.DISABLEFLAG IS
'禁用标志';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CUSTNAME IS
'客户名';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDNO IS
'卡号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.TRANSFLAG IS
'1充值标志2消费次数';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ADDAMT IS
'正为加负为减';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.MANAGEFEE IS
'管理费';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.PAYTYPE IS
'支付方式';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.VOUCHERNO IS
'凭证号码';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.SYSID IS
'子系统编号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.EXTTYPE IS
'附加数据类型';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.EXTDATA IS
'附加数据';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.OFFLINEFLAG IS
'脱机标志';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REVFLAG IS
'冲正标志0-未冲正1-已冲正';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.STATUS IS
'记录状态1:未入账2-入账失败3-成功';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_TRANSDTL.REMARK IS
'备注';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.PAYTYPE IS
'支付方式';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.VOUCHERNO IS
'凭证号码';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CUSTNAME IS
'客户名';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDNO IS
'卡号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.PURSENO IS
'钱包号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.MANAGEFEE IS
'管理费';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.OPERCODE IS
'操作员号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.SYSID IS
'子系统编号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.OFFLINEFLAG IS
'脱机标志';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.EXTTYPE IS
'附加数据类型';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.EXTDATA IS
'附加数据';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.REVFLAG IS
'冲正标志0-未冲正1-已冲正';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.STATUS IS
'记录状态1:未入账2-入账失败3-成功';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_TRANSINFO.REMARK IS
'备注';

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
'交易类别';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.TRANSNAME IS
'交易名称';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.DISPLAYFLAG IS
'显示标志1-显示0-不显示';

COMMENT ON COLUMN YKT_CUR.T_TRANSTYPE.USEFLAG IS
'使用标志';

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
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.OLDCARDNO IS
'原卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.CARDCNT IS
'交易次数';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.CARDBAL IS
'卡余额';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.TOTALDPSAMT IS
'累计充值金额';

COMMENT ON COLUMN YKT_CUR.T_WATERCARDBAL.LASTSAVED IS
'最后更新日期';

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
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TERMID IS
'终端号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDNO IS
'交易卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.AMOUNT IS
'发生额-包含管理费';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TRANSMARK IS
'交易标记';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.SHOPID IS
'商户卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.BATCHNO IS
'导入批次号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.SYSID IS
'子系统ID';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ACCDATE IS
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.STATUS IS
'状态-1初始状态2-入账失败3-成功4-异常流水';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.ERRMSG IS
'错误信息';

COMMENT ON COLUMN YKT_CUR.T_WATERPOSDTL.DELFLAG IS
'删除标志';

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
'记账日期';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.ACCTIME IS
'记账时间';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TERMID IS
'终端编号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TERMSEQNO IS
'终端流水号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSDATE IS
'交易日期';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSTIME IS
'交易时间';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.REFNO IS
'交易参考号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSCODE IS
'交易码';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CUSTID IS
'客户号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CUSTNAME IS
'客户名';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.STUEMPNO IS
'学工号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.SHOWCARDNO IS
'显示卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDNO IS
'卡号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.TRANSFLAG IS
'1充值标志2消费次数';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDCNT IS
'卡交易次数';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDBEFBAL IS
'交易前卡余额';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.CARDAFTBAL IS
'交易后卡余额';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.AMOUNT IS
'发生额';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.SYSID IS
'子系统编号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.DEVPHYID IS
'设备物理ID';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.DEVSEQNO IS
'设备流水号';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.COLDATE IS
'采集日期';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.COLTIME IS
'采集时间';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.STATUS IS
'记录状态1:未入账2-入账失败3-成功';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.ERRCODE IS
'错误码';

COMMENT ON COLUMN YKT_CUR.T_WATERTRANSDTL.REMARK IS
'备注';

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

