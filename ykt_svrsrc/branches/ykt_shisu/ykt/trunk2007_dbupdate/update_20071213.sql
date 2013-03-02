DROP TABLE YKT_CUR.T_TIF_SUBSIDY;

create table YKT_CUR.T_TIF_SUBSIDY  (
   SUBSIDY_NO           NUMBER                    not null,
   CUST_NO              NUMBER                          not null,
   BATCH_NO             VARCHAR2(14),
   SEQNO                NUMBER,
   OPER_CODE            VARCHAR2(10),
   CARD_NO              NUMBER,
   SUMMARY              VARCHAR2(60),
   EXPIRE_DATE          VARCHAR2(8),
   BILL_TYPE            NUMBER,
   BILL_NO              VARCHAR2(20),
   AMOUNT               NUMBER,
   SUBSIDYTYPE          CHAR,
   TX_DATE              CHAR(8),
   TX_TIME              CHAR(6),
   GET_DATE             CHAR(8),
   GET_TIME             CHAR(6),
   STATUS               CHAR,
   BROKER_ID            VARCHAR2(18),
   BROKER_NAME          VARCHAR2(60),
   constraint SYS_C007250 primary key (SUBSIDY_NO, CUST_NO)
         
   using index
       pctfree 10
       initrans 2
       maxtrans 255
       tablespace TS_YKT_CUR
       storage
       (
           initial 64K
           minextents 1
           maxextents unlimited
       )
        logging
)
  pctfree 10
initrans 1
maxtrans 255
storage
(
    initial 64K
    minextents 1
    maxextents unlimited
)
tablespace TS_YKT_CUR
logging
monitoring
  noparallel;
  
  
DROP TABLE YKT_CUR.T_TIF_SUBSIDYTMP;

CREATE TABLE YKT_CUR.T_TIF_SUBSIDYTMP
(
  SUBSIDY_NO   NUMBER,
  CUST_NO      NUMBER                           NOT NULL,
  BATCH_NO     VARCHAR2(14 BYTE),
  SEQNO        NUMBER,
  OPER_CODE    VARCHAR2(10 BYTE),
  CARD_NO      NUMBER,
  SUMMARY      VARCHAR2(60 BYTE),
  EXPIRE_DATE  VARCHAR2(8 BYTE),
  BILL_TYPE    NUMBER,
  BILL_NO      VARCHAR2(20 BYTE),
  AMOUNT       NUMBER,
  SUBSIDYTYPE  CHAR(1 BYTE),
  TX_DATE      CHAR(8 BYTE),
  TX_TIME      CHAR(6 BYTE),
  GET_DATE     CHAR(8 BYTE),
  GET_TIME     CHAR(6 BYTE),
  STATUS       CHAR(1 BYTE),
  BROKER_ID    VARCHAR2(18 BYTE),
  BROKER_NAME  VARCHAR2(60 BYTE),
  primary key (SUBSIDY_NO, CUST_NO, OPER_CODE)
)
TABLESPACE TS_YKT_CUR
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          64K
            MINEXTENTS       1
            MAXEXTENTS       2147483645
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
           )
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;