-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分15秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_CUR "."ACT_TMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."ACT_TMP"  (
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "CUR_BALA" DECIMAL(20,6) , 
		  "CUR_BALA_NEW" DECIMAL(20,6) , 
		  "CUR_FREEBALA" DECIMAL(20,6) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) , 
		  "CUR_BALA_ODD" DECIMAL(20,6) , 
		  "CUR_FREEBALA_ODD" DECIMAL(20,6) , 
		  "CUR_FROZEBALA_ODD" DECIMAL(20,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."ACT_TMP"

ALTER TABLE "YKT_CUR "."ACT_TMP" 
	ADD CONSTRAINT "P_KEY_1" PRIMARY KEY
		("ACCOUNT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."COLSINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."COLSINFO"  (
		  "TNAME" VARCHAR(50) NOT NULL , 
		  "TID" INTEGER , 
		  "TREMARK" VARCHAR(100) , 
		  "OWNR" VARCHAR(30) , 
		  "CNAME" VARCHAR(50) NOT NULL , 
		  "CID" INTEGER , 
		  "ISKEY" CHAR(1) , 
		  "ISNULL" INTEGER , 
		  "LABL" VARCHAR(254) , 
		  "HDR" VARCHAR(254) , 
		  "MASK" VARCHAR(31) , 
		  "BMAP" CHAR(1) , 
		  "INIT" VARCHAR(254) , 
		  "CMNT" VARCHAR(254) , 
		  "EDIT" VARCHAR(31) , 
		  "TAG" VARCHAR(254) , 
		  "CTYPECODE" INTEGER , 
		  "CTYPENAME" VARCHAR(20) , 
		  "CLENGTH" INTEGER )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."INPUTINIT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."INPUTINIT"  (
		  "DBNAME" VARCHAR(20) NOT NULL , 
		  "TNAME" VARCHAR(20) NOT NULL , 
		  "TYPE" VARCHAR(4) NOT NULL , 
		  "CNAME" VARCHAR(20) NOT NULL , 
		  "CVALUE" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."INPUTINIT"

ALTER TABLE "YKT_CUR "."INPUTINIT" 
	ADD PRIMARY KEY
		("DBNAME",
		 "TNAME",
		 "TYPE",
		 "CNAME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_ALERT_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_ALERT_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "PARAMETER" VARCHAR(50) , 
		  "PHONEALERT" SMALLINT , 
		  "MAILALERT" SMALLINT , 
		  "NOTE" SMALLINT )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_ALERT_TABLE"

ALTER TABLE "YKT_CUR "."MAP_ALERT_TABLE" 
	ADD CONSTRAINT "SQL051008175051780" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_ANALYSIS_POINT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_ANALYSIS_POINT"  (
		  "ANALYSISNAME" VARCHAR(50) NOT NULL , 
		  "ANALYSISPOINT" VARCHAR(14) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_ANALYSIS_POINT"

ALTER TABLE "YKT_CUR "."MAP_ANALYSIS_POINT" 
	ADD CONSTRAINT "SQL051025111427820" PRIMARY KEY
		("ANALYSISNAME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_CAUNBALANCE_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_CAUNBALANCE_TABLE"  (
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "ANALYSIS_TIME" CHAR(14) NOT NULL , 
		  "ACT_TYPE" INTEGER , 
		  "CUSTOMER_ID" INTEGER , 
		  "CUT_NAME" VARCHAR(60) , 
		  "CUT_TYPE" INTEGER , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CARD_TYPE" INTEGER , 
		  "SUBNO" VARCHAR(20) , 
		  "PASSWORD" VARCHAR(32) , 
		  "CURRENT_STATE" INTEGER , 
		  "ISAUTOTRA" CHAR(1) , 
		  "LAST_BALA" DECIMAL(20,6) , 
		  "LAST_FREEBALA" DECIMAL(20,6) , 
		  "LAST_FROZEBALA" DECIMAL(20,6) , 
		  "CUR_BALA" DECIMAL(20,6) , 
		  "CUR_FREEBALA" DECIMAL(20,6) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) , 
		  "OUT_BALA" DECIMAL(20,6) , 
		  "IN_BALA" DECIMAL(20,6) , 
		  "OUT_COUNT" INTEGER , 
		  "IN_COUNT" INTEGER , 
		  "CARD_BALANCE" DECIMAL(15,6) , 
		  "NOBALA_NUM" INTEGER , 
		  "CONSUME_COUNT" INTEGER , 
		  "OPEN_DATE" VARCHAR(10) , 
		  "OPEN_TIME" VARCHAR(8) , 
		  "CLOSE_DATE" VARCHAR(10) , 
		  "CLOSE_TIME" VARCHAR(8) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) , 
		  "DEPOSIT_BALA" DECIMAL(9,2) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_CAUNBALANCE_TABLE"

ALTER TABLE "YKT_CUR "."MAP_CAUNBALANCE_TABLE" 
	ADD CONSTRAINT "SQL051027153227430" PRIMARY KEY
		("ACCOUNT_ID",
		 "ANALYSIS_TIME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_CONTACT_MONITOR_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_CONTACT_MONITOR_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "CONTACTNAME" VARCHAR(50) , 
		  "MONITORNO" VARCHAR(50) , 
		  "MONITORNAME" VARCHAR(50) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_CONTACT_MONITOR_TABLE"

ALTER TABLE "YKT_CUR "."MAP_CONTACT_MONITOR_TABLE" 
	ADD CONSTRAINT "SQL051010163457480" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_CONTACT_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_CONTACT_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "CONTACTNAME" VARCHAR(50) , 
		  "CONTACTGENDER" VARCHAR(3) , 
		  "CONTACTCOMPANY" VARCHAR(30) , 
		  "WEEKDAYS" VARCHAR(7) , 
		  "STARTTIME" VARCHAR(26) , 
		  "ENDTIME" VARCHAR(26) , 
		  "EMAIL" VARCHAR(30) , 
		  "CELLPHONE" VARCHAR(13) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_CONTACT_TABLE"

ALTER TABLE "YKT_CUR "."MAP_CONTACT_TABLE" 
	ADD CONSTRAINT "SQL051008175638700" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_DEVICE_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_DEVICE_TABLE"  (
		  "ANALYSIS_TIME" CHAR(14) NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "DEVICE_NAME" VARCHAR(50) , 
		  "DEVICE_TYPE" VARCHAR(4) , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "FDEVPHY_ID" VARCHAR(8) , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "AREA" INTEGER , 
		  "BSHEETVER" VARCHAR(12) , 
		  "DEVICETIME" VARCHAR(14) , 
		  "SERVERTIME" VARCHAR(14) , 
		  "CONTACT_NAME" VARCHAR(50) , 
		  "CPU" DECIMAL(5,2) , 
		  "MEMORY" DECIMAL(5,2) , 
		  "HARDDISK" DECIMAL(5,2) , 
		  "ERROR_REASON" SMALLINT )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_DEVICE_TABLE"

ALTER TABLE "YKT_CUR "."MAP_DEVICE_TABLE" 
	ADD CONSTRAINT "SQL051027192155870" PRIMARY KEY
		("ANALYSIS_TIME",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_FATHERSETS_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_FATHERSETS_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "SYSTEMID" VARCHAR(10) , 
		  "SYSTEMNAME" VARCHAR(50) , 
		  "STATUS" SMALLINT , 
		  "IP" VARCHAR(15) , 
		  "MACADDRESS" VARCHAR(25) , 
		  "COORDX" DOUBLE , 
		  "COORDY" DOUBLE , 
		  "FEATURE" VARCHAR(8) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_FATHERSETS_TABLE"

ALTER TABLE "YKT_CUR "."MAP_FATHERSETS_TABLE" 
	ADD CONSTRAINT "SQL050902093131720" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_FATHER_LINE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_FATHER_LINE"  (
		  "ID" INTEGER NOT NULL , 
		  "SPOINT" VARCHAR(16) , 
		  "EPOINT" VARCHAR(16) , 
		  "SPLAYER" INTEGER , 
		  "EPLAYER" INTEGER , 
		  "LINETYPE" SMALLINT , 
		  "LINECOLOR" BIGINT , 
		  "LINESTYLE" INTEGER , 
		  "LINESTATUS" SMALLINT )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_FATHER_LINE"

ALTER TABLE "YKT_CUR "."MAP_FATHER_LINE" 
	ADD CONSTRAINT "SQL050901133508540" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_LINES_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_LINES_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "POINT1" VARCHAR(16) , 
		  "POINT2" VARCHAR(16) , 
		  "LINETYPE" SMALLINT , 
		  "LINECOLOR" BIGINT , 
		  "LINESTYLE" INTEGER , 
		  "LINESTATUS" SMALLINT )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_LINES_TABLE"

ALTER TABLE "YKT_CUR "."MAP_LINES_TABLE" 
	ADD CONSTRAINT "SQL050901134042020" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_PARAM_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_PARAM_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "PARAMETER" VARCHAR(50) , 
		  "VALUE" DECIMAL(9,2) , 
		  "OTHER" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_PARAM_TABLE"

ALTER TABLE "YKT_CUR "."MAP_PARAM_TABLE" 
	ADD CONSTRAINT "SQL051008170326530" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_ROUTE_TEST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_ROUTE_TEST"  (
		  "ID" INTEGER NOT NULL , 
		  "SERIALNO" INTEGER , 
		  "SETID" VARCHAR(16) , 
		  "COORDX" DOUBLE , 
		  "COORDY" DOUBLE , 
		  "CUT_DATE" VARCHAR(20) , 
		  "CUT_TIME" VARCHAR(20) , 
		  "STUDNO" VARCHAR(10) , 
		  "STU_NAME" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_ROUTE_TEST"

ALTER TABLE "YKT_CUR "."MAP_ROUTE_TEST" 
	ADD CONSTRAINT "SQL051012151621200" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_SERIALEXCEPT_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_SERIALEXCEPT_TABLE"  (
		  "ANALYSIS_TIME" CHAR(14) NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) NOT NULL , 
		  "CARD_NO" INTEGER NOT NULL , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "PURSE_NO" INTEGER , 
		  "IN_BALA" INTEGER , 
		  "OUT_BALA" INTEGER , 
		  "AMOUNT" INTEGER , 
		  "TOTAL_CNT" INTEGER , 
		  "TX_CODE" INTEGER NOT NULL , 
		  "TX_MARK" INTEGER , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "SYS_ID" INTEGER , 
		  "STATUS" CHAR(1) , 
		  "COL_TIMESTAMP" CHAR(20) , 
		  "DEAL_DATE" CHAR(8) , 
		  "DEAL_TIME" CHAR(6) , 
		  "CONTACTNAME" VARCHAR(30) , 
		  "ABNORMALTYPE" SMALLINT )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_SERIALEXCEPT_TABLE"

ALTER TABLE "YKT_CUR "."MAP_SERIALEXCEPT_TABLE" 
	ADD PRIMARY KEY
		("SERIAL_NO",
		 "TX_DATE",
		 "TX_TIME",
		 "DEVICE_ID",
		 "CARD_NO",
		 "TX_CODE",
		 "ANALYSIS_TIME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_SERIALOST_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_SERIALOST_TABLE"  (
		  "ANALYSISTIME" VARCHAR(14) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "TX_DATE" VARCHAR(8) NOT NULL , 
		  "TX_TIME" VARCHAR(6) NOT NULL , 
		  "CONTACTNAME" VARCHAR(50) , 
		  "SERIAL_REASON" SMALLINT NOT NULL , 
		  "SERIAL_STATUS" SMALLINT NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_SERIALOST_TABLE"

ALTER TABLE "YKT_CUR "."MAP_SERIALOST_TABLE" 
	ADD CONSTRAINT "SQL051024171346340" PRIMARY KEY
		("ANALYSISTIME",
		 "SERIAL_NO",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_SERIAL_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_SERIAL_TABLE"  (
		  "SERINO" INTEGER NOT NULL , 
		  "SERI_TYPE" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "DEVICE_ID" INTEGER , 
		  "FDEVPHY_ID" VARCHAR(8) , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "CARD_ID" INTEGER , 
		  "TRADE_FEE" DECIMAL(15,6) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "REVISESERIAL_NO" INTEGER , 
		  "ABNORMALTYPE" INTEGER , 
		  "MAINDEVICE_ID" INTEGER , 
		  "CONTACTNAME" VARCHAR(50) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_SERIAL_TABLE"

ALTER TABLE "YKT_CUR "."MAP_SERIAL_TABLE" 
	ADD CONSTRAINT "SQL051008172330280" PRIMARY KEY
		("SERINO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_SETS_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_SETS_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "SETSID" VARCHAR(16) , 
		  "SETNAME" VARCHAR(50) , 
		  "FATHERID" VARCHAR(16) , 
		  "SETTYPE" VARCHAR(8) , 
		  "SETSTATUS" SMALLINT , 
		  "XCOOR" DOUBLE , 
		  "YCOOR" DOUBLE , 
		  "FEATURE" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_SETS_TABLE"

ALTER TABLE "YKT_CUR "."MAP_SETS_TABLE" 
	ADD CONSTRAINT "SQL050901134249040" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MAP_USER_TABLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MAP_USER_TABLE"  (
		  "ID" INTEGER NOT NULL , 
		  "USERNAME" VARCHAR(30) , 
		  "NAME" VARCHAR(30) , 
		  "PASSWORD" VARCHAR(32) , 
		  "GENDER" VARCHAR(4) , 
		  "COMPANY" VARCHAR(100) , 
		  "EMAIL" VARCHAR(40) , 
		  "PHONE" VARCHAR(30) , 
		  "USERROLE" VARCHAR(4) , 
		  "LOGINTIME" VARCHAR(14) , 
		  "USERSTATUS" INTEGER , 
		  "ADDUSER" VARCHAR(30) , 
		  "CREATETIME" VARCHAR(14) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MAP_USER_TABLE"

ALTER TABLE "YKT_CUR "."MAP_USER_TABLE" 
	ADD CONSTRAINT "SQL050928154043690" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."MESSAGES"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."MESSAGES"  (
		  "MESSAGE_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "TEXT" VARCHAR(100) NOT NULL , 
		  "NEXT_MESSAGE_ID" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."MESSAGES"

ALTER TABLE "YKT_CUR "."MESSAGES" 
	ADD CONSTRAINT "SQL050428172758570" PRIMARY KEY
		("MESSAGE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."SPLITTMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."SPLITTMP"  (
		  "TXTYPE" INTEGER NOT NULL , 
		  "TXNAME" VARCHAR(60) , 
		  "DBFLAG" INTEGER NOT NULL , 
		  "CRFLAG" INTEGER NOT NULL , 
		  "DBSUBNO" VARCHAR(20) NOT NULL , 
		  "CRSUBNO" VARCHAR(20) NOT NULL , 
		  "DBACTNO" VARCHAR(30) , 
		  "CRACTNO" VARCHAR(30) , 
		  "IDXDBACTNO" INTEGER , 
		  "IDXCRACTNO" INTEGER , 
		  "IDXAMT" INTEGER NOT NULL , 
		  "FUNDTYPE" INTEGER , 
		  "SUMMARY" VARCHAR(60) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."SPLITTMP"

ALTER TABLE "YKT_CUR "."SPLITTMP" 
	ADD PRIMARY KEY
		("TXTYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."TABLE_160"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."TABLE_160"  (
		  "BEATTIMES" VARCHAR(20) , 
		  "SUMTIMES" VARCHAR(20) , 
		  "OPERTIMES" VARCHAR(20) , 
		  "CONBEGINTIME" VARCHAR(26) , 
		  "CONENDTIME" VARCHAR(26) , 
		  "CONTIMES" VARCHAR(20) , 
		  "CONCOUNT" VARCHAR(20) , 
		  "CONMAXFEE" VARCHAR(20) , 
		  "TRANBEGINTIME" VARCHAR(26) , 
		  "TRANENDTIME" VARCHAR(26) , 
		  "TRANTIMES" VARCHAR(20) , 
		  "TRANCOUNT" VARCHAR(20) , 
		  "TRANMAXFEE" VARCHAR(20) , 
		  "CARDBEGINTIME" VARCHAR(26) , 
		  "CARDENDTIME" VARCHAR(26) , 
		  "CARDTIMES" VARCHAR(20) , 
		  "CARDCOUNT" VARCHAR(20) , 
		  "CARDMAXFEE" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."TABLE_160" IS 'Table_160';




------------------------------------------------
-- DDL Statements for table "YKT_CUR "."TAB_YKT_NODE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."TAB_YKT_NODE"  (
		  "PAPERNO" INTEGER , 
		  "SHAPEID" INTEGER , 
		  "SIGN" INTEGER , 
		  "SONPAPERNO" INTEGER , 
		  "ID" INTEGER , 
		  "PHYID" VARCHAR(20) , 
		  "MEMO" VARCHAR(20) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_AIF_ACCOUNT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_AIF_ACCOUNT"  (
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "ACT_TYPE" INTEGER , 
		  "CUSTOMER_ID" INTEGER , 
		  "CUT_NAME" VARCHAR(60) , 
		  "CUT_TYPE" INTEGER , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CARD_TYPE" INTEGER , 
		  "SUBNO" VARCHAR(20) , 
		  "PASSWORD" VARCHAR(32) , 
		  "CURRENT_STATE" INTEGER , 
		  "ISAUTOTRA" CHAR(1) , 
		  "LAST_BALA" DECIMAL(20,6) , 
		  "LAST_FREEBALA" DECIMAL(20,6) , 
		  "LAST_FROZEBALA" DECIMAL(20,6) , 
		  "CUR_BALA" DECIMAL(20,6) , 
		  "CUR_FREEBALA" DECIMAL(20,6) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) , 
		  "OUT_BALA" DECIMAL(20,6) , 
		  "IN_BALA" DECIMAL(20,6) , 
		  "OUT_COUNT" INTEGER , 
		  "IN_COUNT" INTEGER , 
		  "CARD_BALANCE" DECIMAL(15,6) , 
		  "NOBALA_NUM" INTEGER , 
		  "CONSUME_COUNT" INTEGER , 
		  "OPEN_DATE" VARCHAR(10) , 
		  "OPEN_TIME" VARCHAR(8) , 
		  "CLOSE_DATE" VARCHAR(10) , 
		  "CLOSE_TIME" VARCHAR(8) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) , 
		  "DEPOSIT_BALA" DECIMAL(9,2) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_AIF_ACCOUNT" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_AIF_ACCOUNT"

ALTER TABLE "YKT_CUR "."T_AIF_ACCOUNT" 
	ADD CONSTRAINT "P_IDENTIFIER_1" PRIMARY KEY
		("ACCOUNT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_AIF_OUTSYS_ACT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_AIF_OUTSYS_ACT"  (
		  "S_ACT_ID" CHAR(16) NOT NULL , 
		  "B_ACT_ID" VARCHAR(40) NOT NULL , 
		  "B_ACT_NAME" VARCHAR(50) , 
		  "SYS_ID" INTEGER NOT NULL , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_AIF_OUTSYS_ACT"

ALTER TABLE "YKT_CUR "."T_AIF_OUTSYS_ACT" 
	ADD PRIMARY KEY
		("S_ACT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_AIF_TRADEACT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_AIF_TRADEACT"  (
		  "TRADE_NO" INTEGER NOT NULL , 
		  "DBFLAG_1" INTEGER , 
		  "DBFLAG_2" INTEGER , 
		  "DBFLAG_3" INTEGER , 
		  "DBFLAG_4" INTEGER , 
		  "CRFLAG_1" INTEGER , 
		  "CRFLAG_2" INTEGER , 
		  "CRFLAG_3" INTEGER , 
		  "CRFLAG_4" INTEGER , 
		  "IDXDBACT1" INTEGER , 
		  "IDXDBACT2" INTEGER , 
		  "IDXDBACT3" INTEGER , 
		  "IDXDBACT4" INTEGER , 
		  "IDXCRACT1" INTEGER , 
		  "IDXCRACT2" INTEGER , 
		  "IDXCRACT3" INTEGER , 
		  "IDXCRACT4" INTEGER , 
		  "IDXAMT1" INTEGER , 
		  "IDXAMT2" INTEGER , 
		  "IDXAMT3" INTEGER , 
		  "IDXAMT4" INTEGER , 
		  "FEE_TYPE1" INTEGER , 
		  "FEE_TYPE2" INTEGER , 
		  "FEE_TYPE3" INTEGER , 
		  "FEE_TYPE4" INTEGER , 
		  "DBACTNO_1" CHAR(16) , 
		  "DBACTNO_2" CHAR(16) , 
		  "DBACTNO_3" CHAR(16) , 
		  "DBACTNO_4" CHAR(16) , 
		  "CRACTNO_1" CHAR(16) , 
		  "CRACTNO_2" CHAR(16) , 
		  "CRACTNO_3" CHAR(16) , 
		  "CRACTNO_4" CHAR(16) , 
		  "COMMENTS1" VARCHAR(60) , 
		  "COMMENTS2" VARCHAR(60) , 
		  "COMMENTS3" VARCHAR(60) , 
		  "COMMENTS4" VARCHAR(60) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."COMMENTS1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."COMMENTS2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."COMMENTS3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."COMMENTS4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRACTNO_1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRACTNO_2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRACTNO_3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRACTNO_4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRFLAG_1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRFLAG_2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRFLAG_3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."CRFLAG_4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBACTNO_1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBACTNO_2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBACTNO_3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBACTNO_4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBFLAG_1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBFLAG_2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBFLAG_3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."DBFLAG_4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."FEE_TYPE1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."FEE_TYPE2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."FEE_TYPE3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."FEE_TYPE4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXAMT1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXAMT2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXAMT3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXAMT4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXCRACT1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXCRACT2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXCRACT3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXCRACT4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXDBACT1" IS '1';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXDBACT2" IS '2';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXDBACT3" IS '3';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."IDXDBACT4" IS '4';

COMMENT ON COLUMN "YKT_CUR "."T_AIF_TRADEACT"."TRADE_NO" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_AIF_TRADEACT"

ALTER TABLE "YKT_CUR "."T_AIF_TRADEACT" 
	ADD PRIMARY KEY
		("TRADE_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUSTOMER"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUSTOMER"  (
		  "CUT_ID" INTEGER NOT NULL , 
		  "CUT_TYPE" INTEGER , 
		  "CUT_STATE" INTEGER NOT NULL , 
		  "CUT_NAME" VARCHAR(60) , 
		  "PASSWORD" VARCHAR(32) , 
		  "AREA" INTEGER , 
		  "LIB_CARDID" VARCHAR(50) , 
		  "IS_HAVECARD" CHAR(1) , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CLASSDEPT_NO" VARCHAR(10) , 
		  "CLASSDEPT_NAME" VARCHAR(50) , 
		  "S_CODE" VARCHAR(100) , 
		  "MAN" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(150) , 
		  "REG_TIME" VARCHAR(26) NOT NULL , 
		  "CAN_TIME" VARCHAR(26) , 
		  "FEE_TYPE" INTEGER , 
		  "BATCH_NO" VARCHAR(14) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "MED_FEETYPE" VARCHAR(5) , 
		  "IN_DATE" CHAR(10) , 
		  "BUILDING_NO" VARCHAR(5) , 
		  "FLOOR_NO" VARCHAR(5) , 
		  "ROOM_NO" VARCHAR(5) , 
		  "UPD_DATE" CHAR(10) , 
		  "UPD_TIME" CHAR(8) , 
		  "SYN_TIME" CHAR(14) , 
		  "COMMENTS" VARCHAR(150) , 
		  "HAS_POSTPONE_ROLE" CHAR(2) , 
		  "FROZEN_STATUS" INTEGER , 
		  "DUTY_NAME" VARCHAR(120) , 
		  "TEL2" VARCHAR(20) , 
		  "TEL3" VARCHAR(20) , 
		  "OA_ACCOUNT" VARCHAR(50) , 
		  "E_MAIL" VARCHAR(50) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_CUSTOMER" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUSTOMER"

ALTER TABLE "YKT_CUR "."T_CIF_CUSTOMER" 
	ADD PRIMARY KEY
		("CUT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUSTOMER_TEST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUSTOMER_TEST"  (
		  "CUT_ID" INTEGER NOT NULL , 
		  "CUT_TYPE" INTEGER , 
		  "CUT_STATE" INTEGER NOT NULL , 
		  "CUT_NAME" VARCHAR(60) , 
		  "PASSWORD" VARCHAR(32) , 
		  "AREA" INTEGER , 
		  "LIB_CARDID" VARCHAR(50) , 
		  "IS_HAVECARD" CHAR(1) , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CLASSDEPT_NO" VARCHAR(10) , 
		  "CLASSDEPT_NAME" VARCHAR(50) , 
		  "MAN" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(150) , 
		  "REG_TIME" VARCHAR(26) NOT NULL , 
		  "CAN_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(150) , 
		  "S_CODE" VARCHAR(100) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "BATCH_NO" VARCHAR(14) , 
		  "IN_DATE" CHAR(10) , 
		  "BUILDING_NO" VARCHAR(10) , 
		  "FLOOR_NO" VARCHAR(10) , 
		  "ROOM_NO" VARCHAR(10) , 
		  "MED_FEETYPE" VARCHAR(5) , 
		  "FEE_TYPE" VARCHAR(5) , 
		  "UPD_DATE" CHAR(10) , 
		  "UPD_TIME" CHAR(8) , 
		  "SYN_TIME" CHAR(14) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_CUSTOMER_TEST" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUSTOMER_TEST"

ALTER TABLE "YKT_CUR "."T_CIF_CUSTOMER_TEST" 
	ADD PRIMARY KEY
		("CUT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUSTOMER_TMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUSTOMER_TMP"  (
		  "BATCH_NO" CHAR(14) NOT NULL , 
		  "SEQNO" INTEGER NOT NULL , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CUT_NAME" VARCHAR(60) , 
		  "CUT_TYPE" INTEGER , 
		  "FEE_TYPE" INTEGER , 
		  "SEX" CHAR(1) , 
		  "MAN_ID" VARCHAR(20) , 
		  "PHONE" VARCHAR(20) , 
		  "AREA" INTEGER , 
		  "DEPT_NO" VARCHAR(10) , 
		  "S_CODE" VARCHAR(10) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "IN_SCHOOL_DATE" CHAR(8) , 
		  "OUT_SCHOOL_DATE" CHAR(8) , 
		  "CARD_TYPE" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUSTOMER_TMP"

ALTER TABLE "YKT_CUR "."T_CIF_CUSTOMER_TMP" 
	ADD PRIMARY KEY
		("BATCH_NO",
		 "SEQNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUST_CARD_ACCOUNT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUST_CARD_ACCOUNT"  (
		  "CUSTOMER_ID" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "B_ACT_ID" VARCHAR(40) NOT NULL , 
		  "B_ACT_NAME" VARCHAR(50) , 
		  "SYS_ID" INTEGER NOT NULL , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "BEGIN_TIME" VARCHAR(8) , 
		  "END_TIME" VARCHAR(8) , 
		  "END_DATE" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUTTYPECARDTYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUTTYPECARDTYPE"  (
		  "CUT_TYPE" INTEGER NOT NULL , 
		  "CARD_TYPE" INTEGER , 
		  "VALIDDATE" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUTTYPECARDTYPE"

ALTER TABLE "YKT_CUR "."T_CIF_CUTTYPECARDTYPE" 
	ADD PRIMARY KEY
		("CUT_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUTTYPEFEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUTTYPEFEE"  (
		  "CUT_TYPE" INTEGER NOT NULL , 
		  "TYPE_NAME" VARCHAR(50) , 
		  "IS_OUTFEE" CHAR(1) , 
		  "RATIO" DOUBLE , 
		  "VALIDDATE" INTEGER , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "IS_FIRSTCOSTFEE" INTEGER , 
		  "IS_RETURNCOSTFEE" INTEGER , 
		  "MAX_BALA" DECIMAL(15,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUTTYPEFEE"

ALTER TABLE "YKT_CUR "."T_CIF_CUTTYPEFEE" 
	ADD PRIMARY KEY
		("CUT_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUTTYPEFEE1"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUTTYPEFEE1"  (
		  "CUT_TYPE" INTEGER NOT NULL , 
		  "TYPE_NAME" VARCHAR(50) , 
		  "IS_OUTFEE" CHAR(1) , 
		  "RATIO" DOUBLE , 
		  "VALIDDATE" INTEGER , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "IS_FIRSTCOSTFEE" INTEGER , 
		  "IS_RETURNCOSTFEE" INTEGER , 
		  "MAX_BALA" DECIMAL(15,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUTTYPEFEE1"

ALTER TABLE "YKT_CUR "."T_CIF_CUTTYPEFEE1" 
	ADD PRIMARY KEY
		("CUT_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_CUTTYPETRADEFEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_CUTTYPETRADEFEE"  (
		  "CUT_TYPE" INTEGER NOT NULL , 
		  "TRADECODE" INTEGER NOT NULL , 
		  "IS_DEPOSITFEE" INTEGER , 
		  "DEPOSITFEE_FLAG" INTEGER , 
		  "DEPOSITFEE_RATIO" DOUBLE , 
		  "DEPOSITFEE" DECIMAL(9,2) , 
		  "IS_COSTFEE" INTEGER , 
		  "COSTFEE_FLAG" INTEGER , 
		  "COSTFEE_RATIO" DOUBLE , 
		  "COSTFEE" DECIMAL(9,2) , 
		  "IS_BOARDFEE" INTEGER , 
		  "BOARDFEE_FLAG" INTEGER , 
		  "BOARDFEE_RATIO" DOUBLE , 
		  "BOARDFEE" DECIMAL(9,2) , 
		  "IS_INFEE" INTEGER , 
		  "INFEE_FLAG" INTEGER , 
		  "INFEE_RATIO" DOUBLE , 
		  "INFEE" DECIMAL(9,2) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_CUTTYPETRADEFEE"

ALTER TABLE "YKT_CUR "."T_CIF_CUTTYPETRADEFEE" 
	ADD PRIMARY KEY
		("CUT_TYPE",
		 "TRADECODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_DEPT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_DEPT"  (
		  "DEPT_CODE" VARCHAR(10) NOT NULL , 
		  "IS_ACADEMY" CHAR(1) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "E_NAME" VARCHAR(100) , 
		  "PARENTDEPT_CODE" VARCHAR(10) , 
		  "DEPT_LEVEL" INTEGER , 
		  "IS_AVAILABILITY" CHAR(1) , 
		  "COMMENTS" VARCHAR(100) , 
		  "DWGLM" VARCHAR(6) , 
		  "RESERVE1" VARCHAR(100) , 
		  "RESERVE2" VARCHAR(100) , 
		  "RESERVE3" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_CIF_DEPT"."DWGLM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_DEPT"

ALTER TABLE "YKT_CUR "."T_CIF_DEPT" 
	ADD CONSTRAINT "SQL051009101333550" PRIMARY KEY
		("DEPT_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_DEPTFULL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_DEPTFULL"  (
		  "DEPT_CODE" VARCHAR(10) NOT NULL , 
		  "IS_ACADEMY" CHAR(1) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "E_NAME" VARCHAR(100) , 
		  "PARENTDEPT_CODE" VARCHAR(10) , 
		  "DEPT_LEVEL" INTEGER , 
		  "IS_AVAILABILITY" CHAR(1) , 
		  "COMMENTS" VARCHAR(100) , 
		  "DWGLM" VARCHAR(6) , 
		  "RESERVE1" VARCHAR(100) , 
		  "RESERVE2" VARCHAR(100) , 
		  "RESERVE3" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_CIF_DEPTFULL"."DWGLM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_DEPTFULL"

ALTER TABLE "YKT_CUR "."T_CIF_DEPTFULL" 
	ADD PRIMARY KEY
		("DEPT_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_EMPLOYEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_EMPLOYEE"  (
		  "EMPLOYEE_ID" VARCHAR(20) NOT NULL , 
		  "EMP_STATE" INTEGER NOT NULL , 
		  "TYPE_ID" INTEGER , 
		  "EMP_NAME" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "POLITY" INTEGER , 
		  "NATION2" INTEGER , 
		  "IDCARD" VARCHAR(20) , 
		  "LEVEL_NO" INTEGER , 
		  "DEPARTMENT_NO" VARCHAR(10) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(100) , 
		  "REG_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_EMPLOYEE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_EMPLOYEE"

ALTER TABLE "YKT_CUR "."T_CIF_EMPLOYEE" 
	ADD CONSTRAINT "P_KEY_2" PRIMARY KEY
		("EMPLOYEE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_PHOTO"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_PHOTO"  (
		  "CUT_TYPE" VARCHAR(50) , 
		  "STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "STUEMP_NAME" VARCHAR(60) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "S_CODE" VARCHAR(100) , 
		  "PHOTO_NO" INTEGER , 
		  "FILENAME" VARCHAR(100) , 
		  "PHOTO" BLOB(524288) NOT LOGGED COMPACT , 
		  "IS_CREATECARD" INTEGER , 
		  "PHOTO_DATE" VARCHAR(10) , 
		  "PHOTO_TIME" VARCHAR(8) , 
		  "IS_INSCHOOL" INTEGER , 
		  "LIB_CARDID" VARCHAR(50) , 
		  "CUR_GRADE" VARCHAR(20) , 
		  "STATUS" INTEGER , 
		  "AREA" INTEGER , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(60) , 
		  "ADDRESS" VARCHAR(150) , 
		  "CAN_TIME" VARCHAR(26) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" INTEGER , 
		  "RESERVE_4" INTEGER , 
		  "TYPE_NAME" VARCHAR(60) , 
		  "DEPT_CODE" VARCHAR(10) , 
		  "S_NAME" VARCHAR(90) , 
		  "GRADE" VARCHAR(10) , 
		  "IN_DATE" CHAR(10) , 
		  "OUT_DATE" CHAR(10) , 
		  "ID" VARCHAR(90) , 
		  "AREA_NAME" VARCHAR(60) , 
		  "BUILDING_NO" VARCHAR(10) , 
		  "FLOOR_NO" VARCHAR(10) , 
		  "ROOM_NO" VARCHAR(10) , 
		  "MED_FEETYPE" VARCHAR(5) , 
		  "FEE_TYPE" VARCHAR(5) , 
		  "UPD_DATE" CHAR(10) , 
		  "UPD_TIME" CHAR(10) , 
		  "SYN_TIME" CHAR(14) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "UPD_STATUS" CHAR(1) , 
		  "IFCARD" INTEGER WITH DEFAULT 0 , 
		  "MAKECARDDATE" VARCHAR(10) , 
		  "BATCH_NO" VARCHAR(14) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_PHOTO"

ALTER TABLE "YKT_CUR "."T_CIF_PHOTO" 
	ADD PRIMARY KEY
		("STUEMP_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_PHOTO1"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_PHOTO1"  (
		  "CUT_TYPE" VARCHAR(50) , 
		  "STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "STUEMP_NAME" VARCHAR(60) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "S_CODE" VARCHAR(100) , 
		  "PHOTO_NO" INTEGER , 
		  "FILENAME" VARCHAR(100) , 
		  "PHOTO" BLOB(524288) NOT LOGGED COMPACT , 
		  "IS_CREATECARD" INTEGER , 
		  "PHOTO_DATE" VARCHAR(10) , 
		  "PHOTO_TIME" VARCHAR(8) , 
		  "IS_INSCHOOL" INTEGER , 
		  "LIB_CARDID" VARCHAR(50) , 
		  "CUR_GRADE" VARCHAR(20) , 
		  "STATUS" INTEGER , 
		  "AREA" INTEGER , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(60) , 
		  "ADDRESS" VARCHAR(150) , 
		  "CAN_TIME" VARCHAR(26) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" INTEGER , 
		  "RESERVE_4" INTEGER , 
		  "TYPE_NAME" VARCHAR(60) , 
		  "DEPT_CODE" VARCHAR(10) , 
		  "S_NAME" VARCHAR(90) , 
		  "GRADE" VARCHAR(10) , 
		  "IN_DATE" CHAR(10) , 
		  "OUT_DATE" CHAR(10) , 
		  "ID" VARCHAR(90) , 
		  "AREA_NAME" VARCHAR(60) , 
		  "BUILDING_NO" VARCHAR(10) , 
		  "FLOOR_NO" VARCHAR(10) , 
		  "ROOM_NO" VARCHAR(10) , 
		  "MED_FEETYPE" VARCHAR(5) , 
		  "FEE_TYPE" VARCHAR(5) , 
		  "UPD_DATE" CHAR(10) , 
		  "UPD_TIME" CHAR(10) , 
		  "SYN_TIME" CHAR(14) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "UPD_STATUS" CHAR(1) , 
		  "IFCARD" INTEGER WITH DEFAULT 0 , 
		  "MAKECARDDATE" VARCHAR(10) , 
		  "BATCH_NO" VARCHAR(14) , 
		  "FROZEN_STATUS" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_PHOTO1" IS '(1-,2-,3-)(1-2-)Area2-3-4-5-status []11-12-13-[]21-22-23-24- ';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_PHOTO1"

ALTER TABLE "YKT_CUR "."T_CIF_PHOTO1" 
	ADD PRIMARY KEY
		("STUEMP_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_PHOTOTMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_PHOTOTMP"  (
		  "BATCH_NO" CHAR(14) NOT NULL , 
		  "SEQNO" INTEGER NOT NULL , 
		  "STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "STUEMP_NAME" VARCHAR(60) , 
		  "CUT_TYPE" VARCHAR(50) , 
		  "DEPT_CODE" VARCHAR(10) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "S_CODE" VARCHAR(10) , 
		  "S_NAME" VARCHAR(90) , 
		  "CUR_GRADE" VARCHAR(20) , 
		  "SEX" CHAR(1) , 
		  "MAN_ID" VARCHAR(20) , 
		  "IS_INSCHOOL" INTEGER , 
		  "STATUS" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_PHOTOTMP"

ALTER TABLE "YKT_CUR "."T_CIF_PHOTOTMP" 
	ADD CONSTRAINT "SQL051116152659140" PRIMARY KEY
		("BATCH_NO",
		 "SEQNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_PHOTO_TMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_PHOTO_TMP"  (
		  "CUT_TYPE" VARCHAR(50) , 
		  "STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "STUEMP_NAME" VARCHAR(60) , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "S_CODE" VARCHAR(100) , 
		  "PHOTO_NO" INTEGER , 
		  "FILENAME" VARCHAR(100) , 
		  "PHOTO" BLOB(524288) NOT LOGGED COMPACT , 
		  "IS_CREATECARD" INTEGER , 
		  "PHOTO_DATE" VARCHAR(10) , 
		  "PHOTO_TIME" VARCHAR(8) , 
		  "IS_INSCHOOL" INTEGER , 
		  "LIB_CARDID" VARCHAR(50) , 
		  "CUR_GRADE" VARCHAR(20) , 
		  "STATUS" INTEGER , 
		  "AREA" INTEGER , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(60) , 
		  "ADDRESS" VARCHAR(150) , 
		  "CAN_TIME" VARCHAR(26) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" INTEGER , 
		  "RESERVE_4" INTEGER , 
		  "TYPE_NAME" VARCHAR(60) , 
		  "DEPT_CODE" VARCHAR(10) , 
		  "S_NAME" VARCHAR(90) , 
		  "GRADE" VARCHAR(10) , 
		  "IN_DATE" CHAR(10) , 
		  "OUT_DATE" CHAR(10) , 
		  "ID" VARCHAR(90) , 
		  "AREA_NAME" VARCHAR(60) , 
		  "BUILDING_NO" VARCHAR(10) , 
		  "FLOOR_NO" VARCHAR(10) , 
		  "ROOM_NO" VARCHAR(10) , 
		  "MED_FEETYPE" VARCHAR(5) , 
		  "FEE_TYPE" VARCHAR(5) , 
		  "UPD_DATE" CHAR(10) , 
		  "UPD_TIME" CHAR(10) , 
		  "SYN_TIME" CHAR(14) , 
		  "CLASS_NO" VARCHAR(10) , 
		  "UPD_STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_PHOTO_TMP" IS '(1-,2-,3-)(1-2-)Area2-3-4-5-status []11-12-13-[]21-22-23-24- ';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_PHOTO_TMP"

ALTER TABLE "YKT_CUR "."T_CIF_PHOTO_TMP" 
	ADD PRIMARY KEY
		("STUEMP_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SHOP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SHOP"  (
		  "SHOP_ID" INTEGER NOT NULL , 
		  "CUT_ID" INTEGER , 
		  "DEPT_ID" INTEGER , 
		  "SHOP_NAME" VARCHAR(50) , 
		  "SHOP_TYPE" INTEGER , 
		  "IS_INDEP" CHAR(1) , 
		  "IS_LEAF" CHAR(1) , 
		  "SHOP_STATE" INTEGER , 
		  "SHOP_MANAGER" VARCHAR(20) , 
		  "MAN" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(100) , 
		  "IS_GETFEE" CHAR(1) , 
		  "RATIO" DOUBLE , 
		  "MANAGER_TYPE" INTEGER , 
		  "DUTY_TYPE" INTEGER , 
		  "REG_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) , 
		  "CAN_TIME" VARCHAR(26) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "B_ACT_NAME" VARCHAR(60) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_SHOP" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_SHOP"

ALTER TABLE "YKT_CUR "."T_CIF_SHOP" 
	ADD PRIMARY KEY
		("SHOP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SHOP2"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SHOP2"  (
		  "SHOP_ID" INTEGER NOT NULL , 
		  "CUT_ID" INTEGER , 
		  "DEPT_ID" INTEGER , 
		  "SHOP_NAME" VARCHAR(50) , 
		  "SHOP_TYPE" INTEGER , 
		  "IS_INDEP" CHAR(1) , 
		  "IS_LEAF" CHAR(1) , 
		  "SHOP_STATE" INTEGER , 
		  "SHOP_MANAGER" VARCHAR(20) , 
		  "MAN" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(100) , 
		  "IS_GETFEE" CHAR(1) , 
		  "RATIO" DOUBLE , 
		  "MANAGER_TYPE" INTEGER , 
		  "DUTY_TYPE" INTEGER , 
		  "REG_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) , 
		  "CAN_TIME" VARCHAR(26) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "B_ACT_NAME" VARCHAR(60) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SHOP_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SHOP_LOG"  (
		  "UPDATE_DATE" VARCHAR(10) NOT NULL , 
		  "SHOP_ID" INTEGER NOT NULL , 
		  "CUT_ID" INTEGER , 
		  "DEPT_ID" INTEGER , 
		  "SHOP_NAME" VARCHAR(50) , 
		  "SHOP_TYPE" INTEGER , 
		  "IS_INDEP" CHAR(1) , 
		  "IS_LEAF" CHAR(1) , 
		  "SHOP_STATE" INTEGER , 
		  "SHOP_MANAGER" VARCHAR(20) , 
		  "MAN" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "NATION" INTEGER , 
		  "MAN_ID" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(150) , 
		  "IS_GETFEE" CHAR(1) , 
		  "RATIO" DOUBLE , 
		  "MANAGER_TYPE" INTEGER , 
		  "DUTY_TYPE" INTEGER , 
		  "REG_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(150) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_SHOP_LOG"

ALTER TABLE "YKT_CUR "."T_CIF_SHOP_LOG" 
	ADD CONSTRAINT "SQL050428173110520" PRIMARY KEY
		("UPDATE_DATE",
		 "SHOP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SHOP_POS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SHOP_POS"  (
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "SHOP_ID" INTEGER , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "BEGIN_TIME" VARCHAR(8) , 
		  "END_TIME" VARCHAR(8) , 
		  "END_DATE" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) , 
		  "FEE_CODE" INTEGER NOT NULL WITH DEFAULT 0 )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_SHOP_POS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_SHOP_POS"

ALTER TABLE "YKT_CUR "."T_CIF_SHOP_POS" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SHOP_POS_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SHOP_POS_LOG"  (
		  "UPDATE_DATE" VARCHAR(10) NOT NULL , 
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "SHOP_ID" INTEGER , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "BEGIN_TIME" VARCHAR(8) , 
		  "END_TIME" VARCHAR(8) , 
		  "END_DATE" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) , 
		  "FEE_CODE" INTEGER NOT NULL WITH DEFAULT 0 )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_SHOP_POS_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_SHOP_POS_LOG"

ALTER TABLE "YKT_CUR "."T_CIF_SHOP_POS_LOG" 
	ADD PRIMARY KEY
		("UPDATE_DATE",
		 "ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIF_SPECIALITY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIF_SPECIALITY"  (
		  "S_CODE" VARCHAR(10) NOT NULL , 
		  "S_NAME" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIF_SPECIALITY" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIF_SPECIALITY"

ALTER TABLE "YKT_CUR "."T_CIF_SPECIALITY" 
	ADD PRIMARY KEY
		("S_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_CIT_STUDENT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_CIT_STUDENT"  (
		  "STUDENT_NO" VARCHAR(20) NOT NULL , 
		  "STUDY_STATE" INTEGER NOT NULL , 
		  "STUDY_TYPE" INTEGER , 
		  "STUDENT_NAME" VARCHAR(60) , 
		  "SEX" CHAR(1) , 
		  "POLITY" INTEGER , 
		  "NATION" INTEGER , 
		  "IDCARD" VARCHAR(20) , 
		  "DEPT_NO" VARCHAR(10) , 
		  "DEPT_CODE" VARCHAR(10) , 
		  "REGISTER_DATE" VARCHAR(10) , 
		  "GRADE" VARCHAR(8) , 
		  "STUDY_TIME" INTEGER , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(100) , 
		  "REG_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_CIT_STUDENT" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_CIT_STUDENT"

ALTER TABLE "YKT_CUR "."T_CIT_STUDENT" 
	ADD PRIMARY KEY
		("STUDENT_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_DEVICE_CARDLIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_DEVICE_CARDLIST"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "CARD_NO" INTEGER NOT NULL , 
		  "CARD_SERIAL_NO" CHAR(8) , 
		  "STATUS" CHAR(1) NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) NOT NULL , 
		  "VERSION" CHAR(12) NOT NULL , 
		  "SEND_FLAG" CHAR(1) NOT NULL , 
		  "STUEMP_NO" CHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_DEVICE_CARDLIST"

ALTER TABLE "YKT_CUR "."T_DOOR_DEVICE_CARDLIST" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "CARD_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_DEVICE_HOLIDAY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_DEVICE_HOLIDAY"  (
		  "DOOR_HOLIDAY_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "HOLIDAY_NAME" VARCHAR(60) , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "START_DATE" CHAR(8) NOT NULL , 
		  "END_DATE" CHAR(8) NOT NULL , 
		  "START_TIME" CHAR(6) NOT NULL , 
		  "END_TIME" CHAR(6) NOT NULL , 
		  "VERSION" CHAR(12) NOT NULL , 
		  "SEND_FLAG" CHAR(1) NOT NULL , 
		  "DAY_COUNT" INTEGER NOT NULL WITH DEFAULT 0 )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_DEVICE_HOLIDAY"

ALTER TABLE "YKT_CUR "."T_DOOR_DEVICE_HOLIDAY" 
	ADD PRIMARY KEY
		("DOOR_HOLIDAY_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_DEVICE_WORKTIME"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_DEVICE_WORKTIME"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "WEEK" INTEGER NOT NULL , 
		  "SEQNO" INTEGER NOT NULL , 
		  "CARD_TYPE" CHAR(64) NOT NULL , 
		  "START_TIME" CHAR(6) NOT NULL , 
		  "END_TIME" CHAR(6) NOT NULL , 
		  "VERSION" CHAR(12) , 
		  "SEND_FLAG" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_DOOR_DEVICE_WORKTIME" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_DEVICE_WORKTIME"

ALTER TABLE "YKT_CUR "."T_DOOR_DEVICE_WORKTIME" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "WEEK",
		 "SEQNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_GROUP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_GROUP"  (
		  "GROUP_ID" INTEGER NOT NULL GENERATED BY DEFAULT AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "GROUP_NAME" VARCHAR(80) , 
		  "REF_CNT" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_DOOR_GROUP" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_GROUP"

ALTER TABLE "YKT_CUR "."T_DOOR_GROUP" 
	ADD PRIMARY KEY
		("GROUP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_GROUP_MEMBER"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_GROUP_MEMBER"  (
		  "GROUP_ID" INTEGER NOT NULL , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "COMMENTS" VARCHAR(150) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_DOOR_GROUP_MEMBER"."COMMENTS" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_DOOR_GROUP_MEMBER"."DEVICE_ID" IS 'ID';

COMMENT ON COLUMN "YKT_CUR "."T_DOOR_GROUP_MEMBER"."GROUP_ID" IS 'ID';


-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_GROUP_MEMBER"

ALTER TABLE "YKT_CUR "."T_DOOR_GROUP_MEMBER" 
	ADD PRIMARY KEY
		("GROUP_ID",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_HOLIDAY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_HOLIDAY"  (
		  "HOLIDAY_ID" INTEGER NOT NULL , 
		  "HOLIDAY_NAME" VARCHAR(60) NOT NULL , 
		  "START_DATE" CHAR(8) NOT NULL , 
		  "END_DATE" CHAR(8) NOT NULL , 
		  "START_TIME" CHAR(6) , 
		  "END_TIME" CHAR(6) , 
		  "REF_CNT" INTEGER NOT NULL , 
		  "DAY_COUNT" INTEGER NOT NULL WITH DEFAULT 0 )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_HOLIDAY"

ALTER TABLE "YKT_CUR "."T_DOOR_HOLIDAY" 
	ADD PRIMARY KEY
		("HOLIDAY_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_OPER_RIGHT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_OPER_RIGHT"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "OPER_NO" CHAR(10) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_OPER_RIGHT"

ALTER TABLE "YKT_CUR "."T_DOOR_OPER_RIGHT" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "OPER_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_RPT_DAY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_RPT_DAY"  (
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "TOTAL_CNT" INTEGER , 
		  "VALID_CNT" INTEGER , 
		  "INVALID_CNT" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_RPT_DAY"

ALTER TABLE "YKT_CUR "."T_DOOR_RPT_DAY" 
	ADD PRIMARY KEY
		("TX_DATE",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_DOOR_TXDTL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_DOOR_TXDTL"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_DOOR_TXDTL"

ALTER TABLE "YKT_CUR "."T_DOOR_TXDTL" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "SERIAL_NO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_ALARM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_ALARM"  (
		  "ALARMNO" INTEGER NOT NULL , 
		  "MONITYPE" INTEGER , 
		  "ALARMLEVEL" INTEGER , 
		  "ALARMTYPE" INTEGER , 
		  "ALDEFINE" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_ALARM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_ALARM"

ALTER TABLE "YKT_CUR "."T_MIF_ALARM" 
	ADD PRIMARY KEY
		("ALARMNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_ALARMLEVEL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_ALARMLEVEL"  (
		  "ALARMLEVEL" INTEGER NOT NULL , 
		  "ALNAME" VARCHAR(50) , 
		  "COLORNO" INTEGER , 
		  "IS_OP" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_ALARMLEVEL" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_ALARMLEVEL"

ALTER TABLE "YKT_CUR "."T_MIF_ALARMLEVEL" 
	ADD PRIMARY KEY
		("ALARMLEVEL");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_ALARMOP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_ALARMOP"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_STATE" INTEGER , 
		  "ALARMTYPE" INTEGER , 
		  "ALARM_TIME" VARCHAR(26) , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_NO2" INTEGER , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OPER_NAME" VARCHAR(32) , 
		  "PHONE" VARCHAR(40) , 
		  "MOBILE" VARCHAR(40) , 
		  "ADDR" VARCHAR(80) , 
		  "ZIP" CHAR(6) , 
		  "EMAIL" VARCHAR(60) , 
		  "FINISH_TIME" VARCHAR(26) , 
		  "OPRESULT" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_ALARMOP" IS '¼';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_ALARMOP"

ALTER TABLE "YKT_CUR "."T_MIF_ALARMOP" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_CARDDBINCON"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_CARDDBINCON"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OP_TIME" VARCHAR(26) NOT NULL , 
		  "ALARMNO" INTEGER NOT NULL , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CUR_FREEBALA" DECIMAL(15,2) , 
		  "CARD_BALANCE" DECIMAL(15,2) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_CARDDBINCON"

ALTER TABLE "YKT_CUR "."T_MIF_CARDDBINCON" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_CARDOPERATE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_CARDOPERATE"  (
		  "SERIAL_NO2" INTEGER NOT NULL , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "CONCOUNT" INTEGER , 
		  "SERIAL_NO" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "SUBSIDY_FEE" DECIMAL(9,2) , 
		  "TOPUP_FEE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "OPER_CODE" VARCHAR(10) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_CARDOPERATE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_CARDOPERATE"

ALTER TABLE "YKT_CUR "."T_MIF_CARDOPERATE" 
	ADD PRIMARY KEY
		("SERIAL_NO2");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_CONSUME"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_CONSUME"  (
		  "SERIAL_NO2" INTEGER NOT NULL , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "CONCOUNT" INTEGER , 
		  "SERIAL_NO" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "CONSUME_COUNT" INTEGER , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CONSUME_FEE" DECIMAL(9,2) , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_CONSUME"

ALTER TABLE "YKT_CUR "."T_MIF_CONSUME" 
	ADD PRIMARY KEY
		("SERIAL_NO2");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_DEVMONERR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_DEVMONERR"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "OP_TIME" VARCHAR(26) NOT NULL , 
		  "COLLECT_TIME" VARCHAR(26) , 
		  "IS_WS" CHAR(1) , 
		  "ALARMNO" INTEGER NOT NULL , 
		  "BEATSTATE" INTEGER NOT NULL , 
		  "BSVERSION" VARCHAR(12) , 
		  "HDPER" DOUBLE , 
		  "EMSPER" DOUBLE , 
		  "CPUPER" DOUBLE , 
		  "DEVTIME" VARCHAR(26) , 
		  "NOUPLOADNUM" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_DEVMONERR"

ALTER TABLE "YKT_CUR "."T_MIF_DEVMONERR" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_DEVMONITOR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_DEVMONITOR"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "OP_TIME" VARCHAR(26) , 
		  "COLLECT_TIME" VARCHAR(26) , 
		  "IS_WS" CHAR(1) , 
		  "ALARMNO" INTEGER , 
		  "BEATSTATE" INTEGER , 
		  "BSVERSION" VARCHAR(12) , 
		  "HDPER" DOUBLE , 
		  "EMSPER" DOUBLE , 
		  "CPUPER" DOUBLE , 
		  "DEVTIME" VARCHAR(26) , 
		  "NOUPLOADNUM" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_DEVMONITOR"

ALTER TABLE "YKT_CUR "."T_MIF_DEVMONITOR" 
	ADD PRIMARY KEY
		("DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_LINKMAN"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_LINKMAN"  (
		  "ALARMNO" INTEGER NOT NULL , 
		  "OPER_CODE" VARCHAR(10) NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_LINKMAN" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_MIF_LINKMAN"."ALARMNO" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_MIF_LINKMAN"."OPER_CODE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_LINKMAN"

ALTER TABLE "YKT_CUR "."T_MIF_LINKMAN" 
	ADD PRIMARY KEY
		("ALARMNO",
		 "OPER_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_OPERATOR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_OPERATOR"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "EMPLOYEE_ID" VARCHAR(20) , 
		  "CARD_ID" INTEGER , 
		  "OPER_NAME" VARCHAR(32) NOT NULL , 
		  "PHONE" VARCHAR(40) , 
		  "MOBILE" VARCHAR(40) , 
		  "ADDR" VARCHAR(80) , 
		  "ZIP" CHAR(6) , 
		  "EMAIL" VARCHAR(60) , 
		  "STATUS" CHAR(1) , 
		  "LOGIN_TIME" VARCHAR(26) , 
		  "LOGOUT_TIME" VARCHAR(26) , 
		  "LOGIN_IP" VARCHAR(20) , 
		  "MAC_ADDR" VARCHAR(20) , 
		  "LOGIN_FLAG" CHAR(1) , 
		  "LOGIN_APP" CHAR(1) , 
		  "REG_DATE" CHAR(8) , 
		  "REG_TIME" CHAR(8) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_OPERATOR" IS '';




------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_SYSSTATE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_SYSSTATE"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OP_TIME" VARCHAR(26) NOT NULL , 
		  "ALARMNO" INTEGER NOT NULL , 
		  "SYSSTATE" INTEGER NOT NULL , 
		  "BEGINTIME" VARCHAR(26) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_SYSSTATE"

ALTER TABLE "YKT_CUR "."T_MIF_SYSSTATE" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_TRADESERIALERROR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_TRADESERIALERROR"  (
		  "SERIAL_NO2" INTEGER NOT NULL , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "CONCOUNT" INTEGER , 
		  "SERIAL_NO" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "TRADE_COUNT" INTEGER , 
		  "TRADE_FEE" DECIMAL(15,6) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "CONDITION_ID" INTEGER , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "REVISESERIAL_NO" INTEGER NOT NULL , 
		  "RESERVE_1" VARCHAR(40) , 
		  "RESERVE_2" VARCHAR(40) , 
		  "RESERVE_3" VARCHAR(40) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_TRADESERIALERROR"

ALTER TABLE "YKT_CUR "."T_MIF_TRADESERIALERROR" 
	ADD PRIMARY KEY
		("SERIAL_NO2");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_MIF_TRAN"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_MIF_TRAN"  (
		  "SERIAL_NO2" INTEGER NOT NULL , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "CONCOUNT" INTEGER , 
		  "SERIAL_NO" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "TRANSFER_FEE" DECIMAL(9,2) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "CONDITION_ID" INTEGER , 
		  "OPERATOR_ID" VARCHAR(10) , 
		  "ECODE" INTEGER , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_MIF_TRAN" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_MIF_TRAN"

ALTER TABLE "YKT_CUR "."T_MIF_TRAN" 
	ADD PRIMARY KEY
		("SERIAL_NO2");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_AA"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_AA"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "DEVICE_NAME" VARCHAR(60) , 
		  "DEV_STATE" INTEGER , 
		  "DEVTYPE" VARCHAR(4) , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "ASSET_NO" CHAR(11) , 
		  "ASSET_TYPE" INTEGER , 
		  "AREA" INTEGER , 
		  "PHYTYPE" INTEGER , 
		  "MANAGER" VARCHAR(20) , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "END_DATE" VARCHAR(10) , 
		  "DEV999_ID" VARCHAR(8) , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "DEV999_NO" INTEGER , 
		  "DEVVERSION" VARCHAR(8) , 
		  "CARDSTR" VARCHAR(2) , 
		  "CARDTYPE" VARCHAR(64) , 
		  "PORTCOUNT" INTEGER , 
		  "FDEVPHY_ID" VARCHAR(8) , 
		  "PORTNO" INTEGER , 
		  "STATE_ID" INTEGER , 
		  "JOINMODE" INTEGER , 
		  "COMADD" VARCHAR(16) , 
		  "PORT" VARCHAR(6) , 
		  "BAUDRATE" INTEGER , 
		  "COMTYPE" INTEGER , 
		  "BSHEETVDATE" VARCHAR(12) , 
		  "BSHEETVER" VARCHAR(12) , 
		  "LASTTRASERNO" INTEGER , 
		  "LASTTRADATE" VARCHAR(20) , 
		  "LASTSHUTSERNO" INTEGER , 
		  "LASTSHUTDATE" VARCHAR(20) , 
		  "SYSPWD" VARCHAR(6) , 
		  "ADMPWD" VARCHAR(6) , 
		  "PWDONOFF" INTEGER , 
		  "PUSERNO" VARCHAR(3) , 
		  "CARDSET" VARCHAR(64) , 
		  "FUNONOFF" VARCHAR(2) , 
		  "CARDUSENUM" INTEGER , 
		  "MAXDEPOSIT" INTEGER , 
		  "MINDEPOSIT" INTEGER , 
		  "RATION" INTEGER , 
		  "MAXTRADE" INTEGER , 
		  "SHUTTIMES" VARCHAR(64) , 
		  "CARD65PWD" VARCHAR(64) , 
		  "AUTHPWD" VARCHAR(64) , 
		  "FTFLAG" INTEGER , 
		  "WEB_LEVEL" INTEGER , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_AA" IS '11';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_AA"

ALTER TABLE "YKT_CUR "."T_PIF_AA" 
	ADD PRIMARY KEY
		("DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_APP_FUNC_LIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_APP_FUNC_LIST"  (
		  "OPER_STYLE" CHAR(1) NOT NULL , 
		  "APP_FUNC_NO" INTEGER NOT NULL , 
		  "APP_NO" CHAR(1) NOT NULL , 
		  "APP_FUNC_NAME" VARCHAR(32) NOT NULL , 
		  "APP_FUNC_FULL_NAME" VARCHAR(32) NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_APP_FUNC_LIST" IS '   1 2';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_APP_FUNC_LIST"

ALTER TABLE "YKT_CUR "."T_PIF_APP_FUNC_LIST" 
	ADD PRIMARY KEY
		("OPER_STYLE",
		 "APP_FUNC_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_AREA"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_AREA"  (
		  "AREA_NO" INTEGER NOT NULL , 
		  "FATHER_AREA_NO" INTEGER , 
		  "AREA_NAME" VARCHAR(50) , 
		  "AREALEVEL" INTEGER , 
		  "ADDRESS" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_AREA"

ALTER TABLE "YKT_CUR "."T_PIF_AREA" 
	ADD PRIMARY KEY
		("AREA_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_AUTHCARD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_AUTHCARD"  (
		  "PHYSICAL_NO" VARCHAR(40) NOT NULL , 
		  "STATE_ID" INTEGER NOT NULL , 
		  "TYPE_ID" INTEGER , 
		  "PASSWORD1" VARCHAR(32) , 
		  "PASSWORD2" VARCHAR(32) , 
		  "BEGIN_TIME" VARCHAR(26) , 
		  "END_TIME" VARCHAR(26) , 
		  "PHYTYPE" INTEGER , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_AUTHCARD" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_AUTHCARD"

ALTER TABLE "YKT_CUR "."T_PIF_AUTHCARD" 
	ADD PRIMARY KEY
		("PHYSICAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARD"  (
		  "CARD_ID" INTEGER NOT NULL , 
		  "SHOWID" CHAR(10) , 
		  "IS_MAIN" CHAR(1) , 
		  "STATE_ID" CHAR(4) , 
		  "TYPE_ID" INTEGER , 
		  "PASSWORD" VARCHAR(32) , 
		  "COSUMER_ID" INTEGER , 
		  "ACCOUNT_COUNT" INTEGER , 
		  "IS_MANAGEFEE" CHAR(1) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "BEGIN_TIME" VARCHAR(26) , 
		  "END_TIME" VARCHAR(26) , 
		  "PHYSICAL_NO" VARCHAR(40) , 
		  "PHYTYPE" INTEGER , 
		  "COMMENTS" VARCHAR(100) , 
		  "BAD_STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARD" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARD"

ALTER TABLE "YKT_CUR "."T_PIF_CARD" 
	ADD PRIMARY KEY
		("CARD_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARDLEVEL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARDLEVEL"  (
		  "LEVEL_ID" INTEGER NOT NULL , 
		  "LEVEL_NAME" VARCHAR(60) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARDLEVEL"

ALTER TABLE "YKT_CUR "."T_PIF_CARDLEVEL" 
	ADD PRIMARY KEY
		("LEVEL_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"  (
		  "LEVEL_ID" INTEGER NOT NULL , 
		  "GROUP_ID" INTEGER NOT NULL , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARDLEVEL_GROUP" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"."COMMENTS" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"."GROUP_ID" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"."LEVEL_ID" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARDLEVEL_GROUP"

ALTER TABLE "YKT_CUR "."T_PIF_CARDLEVEL_GROUP" 
	ADD PRIMARY KEY
		("LEVEL_ID",
		 "GROUP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARDLOSSINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARDLOSSINFO"  (
		  "OPERATE_DATE" VARCHAR(10) NOT NULL , 
		  "OPERATE_TIME" VARCHAR(8) NOT NULL , 
		  "CARD_ID" INTEGER NOT NULL , 
		  "STATE_ID" INTEGER NOT NULL , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "END_DATE" VARCHAR(10) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARDLOSSINFO" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARDLOSSINFO"

ALTER TABLE "YKT_CUR "."T_PIF_CARDLOSSINFO" 
	ADD PRIMARY KEY
		("OPERATE_DATE",
		 "OPERATE_TIME",
		 "CARD_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARDPURSE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARDPURSE"  (
		  "PURSE_ID" INTEGER NOT NULL , 
		  "PURSE_NAME" VARCHAR(60) , 
		  "ACCESSRIGHT" INTEGER , 
		  "DESCIBE" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARDPURSE"

ALTER TABLE "YKT_CUR "."T_PIF_CARDPURSE" 
	ADD PRIMARY KEY
		("PURSE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARDSTRUT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARDSTRUT"  (
		  "ID" INTEGER NOT NULL , 
		  "PHYTYPE" INTEGER , 
		  "SECTORNO" INTEGER , 
		  "BLOCKNO" INTEGER , 
		  "BEGIN_ADDR" INTEGER , 
		  "END_ADDR" INTEGER , 
		  "BYTENUM" INTEGER , 
		  "DEFINE" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARDSTRUT" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARDSTRUT"

ALTER TABLE "YKT_CUR "."T_PIF_CARDSTRUT" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARD_AND_LEVELG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARD_AND_LEVELG"  (
		  "LEVELGROUP_ID" INTEGER NOT NULL , 
		  "CARD_ID" DECIMAL(9,0) NOT NULL , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARD_AND_LEVELG" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARD_AND_LEVELG"."CARD_ID" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARD_AND_LEVELG"."COMMENTS" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_CARD_AND_LEVELG"."LEVELGROUP_ID" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARD_AND_LEVELG"

ALTER TABLE "YKT_CUR "."T_PIF_CARD_AND_LEVELG" 
	ADD PRIMARY KEY
		("LEVELGROUP_ID",
		 "CARD_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARD_LEVELG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARD_LEVELG"  (
		  "LEVELGROUP_ID" INTEGER NOT NULL , 
		  "LGNAME" VARCHAR(60) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARD_LEVELG"

ALTER TABLE "YKT_CUR "."T_PIF_CARD_LEVELG" 
	ADD PRIMARY KEY
		("LEVELGROUP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CARD_MANAGE_FEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CARD_MANAGE_FEE"  (
		  "ID" INTEGER NOT NULL , 
		  "TNAME" VARCHAR(60) , 
		  "RATIO" DOUBLE , 
		  "ID_FEE" DOUBLE , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CARD_MANAGE_FEE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CARD_MANAGE_FEE"

ALTER TABLE "YKT_CUR "."T_PIF_CARD_MANAGE_FEE" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CUR_SYSPARA"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CUR_SYSPARA"  (
		  "ID" INTEGER NOT NULL , 
		  "VALUE" VARCHAR(50) NOT NULL , 
		  "PARA_NAME" VARCHAR(100) , 
		  "USETIME" VARCHAR(26) , 
		  "OPTIME" VARCHAR(26) , 
		  "UNIT" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CUR_SYSPARA"

ALTER TABLE "YKT_CUR "."T_PIF_CUR_SYSPARA" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_CUT_AND_LEVELG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_CUT_AND_LEVELG"  (
		  "LEVELGROUP_ID" INTEGER NOT NULL , 
		  "CUT_ID" DECIMAL(9,0) NOT NULL , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_CUT_AND_LEVELG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_CUT_AND_LEVELG"

ALTER TABLE "YKT_CUR "."T_PIF_CUT_AND_LEVELG" 
	ADD PRIMARY KEY
		("LEVELGROUP_ID",
		 "CUT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVASSET"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVASSET"  (
		  "ASSET_NO" CHAR(11) , 
		  "ASSET_TYPE" INTEGER , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "BEGIN_DATE" VARCHAR(10) , 
		  "END_DATE" VARCHAR(10) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVCARDTYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVCARDTYPE"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "CUT_TYPE" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_DEVCARDTYPE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_DEVCARDTYPE"

ALTER TABLE "YKT_CUR "."T_PIF_DEVCARDTYPE" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "CUT_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVFEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVFEE"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "TYPE_ID" INTEGER , 
		  "FEE" INTEGER )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVICE_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVICE_LOG"  (
		  "LOG_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "SERIAL_TYPE" INTEGER , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "OPERATE_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_DEVICE_LOG" IS '/';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_DEVICE_LOG"

ALTER TABLE "YKT_CUR "."T_PIF_DEVICE_LOG" 
	ADD PRIMARY KEY
		("LOG_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVTIME"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVTIME"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "BEGIN_TIME" VARCHAR(8) NOT NULL , 
		  "END_TIME" VARCHAR(8) NOT NULL , 
		  "FEE" INTEGER , 
		  "MAXCOUNT" INTEGER , 
		  "CARDTYPE" VARCHAR(64) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_DEVTIME" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_DEVTIME"

ALTER TABLE "YKT_CUR "."T_PIF_DEVTIME" 
	ADD PRIMARY KEY
		("DEVICE_ID",
		 "BEGIN_TIME",
		 "END_TIME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DICTIONARY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DICTIONARY"  (
		  "DICT_NO" INTEGER NOT NULL , 
		  "DICT_VALUE" VARCHAR(30) NOT NULL , 
		  "DICT_NAME" VARCHAR(40) , 
		  "DICT_CAPTION" VARCHAR(40) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_DICTIONARY"

ALTER TABLE "YKT_CUR "."T_PIF_DICTIONARY" 
	ADD PRIMARY KEY
		("DICT_NO",
		 "DICT_VALUE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_ERRCODE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_ERRCODE"  (
		  "ECODE" INTEGER NOT NULL , 
		  "EMSG" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_ERRCODE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_ERRCODE"

ALTER TABLE "YKT_CUR "."T_PIF_ERRCODE" 
	ADD PRIMARY KEY
		("ECODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_FEETYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_FEETYPE"  (
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "FEE_NAME" VARCHAR(120) , 
		  "COMMENTS" VARCHAR(150) , 
		  "IS_OUTFEE" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_FEETYPE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_FEETYPE"

ALTER TABLE "YKT_CUR "."T_PIF_FEETYPE" 
	ADD PRIMARY KEY
		("FEE_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_MEAL_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_MEAL_TYPE"  (
		  "TYPE_ID" INTEGER NOT NULL , 
		  "CNAME" VARCHAR(60) , 
		  "BEGIN_TIME" VARCHAR(8) , 
		  "END_TIME" VARCHAR(8) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_MEAL_TYPE" IS 'ñ';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_MEAL_TYPE"

ALTER TABLE "YKT_CUR "."T_PIF_MEAL_TYPE" 
	ADD PRIMARY KEY
		("TYPE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_MODULE_AUTH"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_MODULE_AUTH"  (
		  "MODULE_CODE" VARCHAR(6) NOT NULL , 
		  "MODULE_NAME" VARCHAR(60) NOT NULL , 
		  "MENU_SET" VARCHAR(800) , 
		  "FUNC_SET" VARCHAR(600) , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OPER_DATE" CHAR(8) , 
		  "OPER_TIME" CHAR(8) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_MODULE_AUTH" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_MODULE_AUTH"

ALTER TABLE "YKT_CUR "."T_PIF_MODULE_AUTH" 
	ADD PRIMARY KEY
		("MODULE_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OLD_SYSPARA"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OLD_SYSPARA"  (
		  "ID" INTEGER NOT NULL , 
		  "VALUE" VARCHAR(50) NOT NULL , 
		  "PARA_NAME" VARCHAR(60) , 
		  "USETIME" VARCHAR(26) , 
		  "OPTIME" VARCHAR(26) , 
		  "UNIT" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_OLD_SYSPARA" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OLD_SYSPARA"

ALTER TABLE "YKT_CUR "."T_PIF_OLD_SYSPARA" 
	ADD PRIMARY KEY
		("ID",
		 "VALUE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OPERATOR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OPERATOR"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "EMPLOYEE_ID" VARCHAR(20) , 
		  "CARD_ID" INTEGER , 
		  "OPER_NAME" VARCHAR(32) NOT NULL , 
		  "PHONE" VARCHAR(40) , 
		  "MOBILE" VARCHAR(40) , 
		  "ADDR" VARCHAR(80) , 
		  "ZIP" CHAR(6) , 
		  "EMAIL" VARCHAR(60) , 
		  "IF_STATION" CHAR(1) , 
		  "IF_ACCESS" CHAR(1) , 
		  "PWD" VARCHAR(32) , 
		  "STATUS" CHAR(1) , 
		  "MENU_SET" VARCHAR(800) , 
		  "FUNC_SET" VARCHAR(600) , 
		  "LOGIN_TIME" VARCHAR(26) , 
		  "LOGOUT_TIME" VARCHAR(26) , 
		  "MODULE_QTY" INTEGER , 
		  "FAIL_NUMBER" INTEGER , 
		  "LOGIN_IP" VARCHAR(20) , 
		  "MAC_ADDR" VARCHAR(20) , 
		  "LOGIN_FLAG" CHAR(1) , 
		  "LOGIN_APP" CHAR(1) , 
		  "REG_DATE" CHAR(8) , 
		  "REG_TIME" CHAR(8) , 
		  "ORDER_STATUS" CHAR(1) , 
		  "SEAT_NO" VARCHAR(10) , 
		  "MAIN_FUNC" INTEGER , 
		  "RECV_RSP_FLAG" CHAR(1) , 
		  "RECV_INFO_FLAG" CHAR(1) , 
		  "LOGIN_BATCH" INTEGER , 
		  "SOURCE_NO" INTEGER , 
		  "NODE_ID" INTEGER , 
		  "SPECIFY_FUNC_FLAG" CHAR(1) , 
		  "FORCE_LOGOUT_REASON" VARCHAR(70) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OPERATOR"

ALTER TABLE "YKT_CUR "."T_PIF_OPERATOR" 
	ADD PRIMARY KEY
		("OPER_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OPERATOR_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OPERATOR_LOG"  (
		  "LOG_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "CARD_ID" INTEGER , 
		  "LOGIN_IP" VARCHAR(20) , 
		  "MAC_ADDR" VARCHAR(20) , 
		  "OPERATE_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_OPERATOR_LOG" IS '½/';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OPERATOR_LOG"

ALTER TABLE "YKT_CUR "."T_PIF_OPERATOR_LOG" 
	ADD PRIMARY KEY
		("LOG_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OPER_MAIN_FUNC"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OPER_MAIN_FUNC"  (
		  "MAIN_FUNC" INTEGER NOT NULL , 
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "REG_TIME" CHAR(8) NOT NULL , 
		  "REG_DATE" CHAR(8) NOT NULL , 
		  "USE_FLAG" CHAR(1) NOT NULL , 
		  "NODE_ID" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OPER_MAIN_FUNC"

ALTER TABLE "YKT_CUR "."T_PIF_OPER_MAIN_FUNC" 
	ADD PRIMARY KEY
		("MAIN_FUNC");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OPER_SITE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OPER_SITE"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "SITE_NO" VARCHAR(10) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OPER_SITE"

ALTER TABLE "YKT_CUR "."T_PIF_OPER_SITE" 
	ADD PRIMARY KEY
		("OPER_CODE",
		 "SITE_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OPER_STATUS_REC"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OPER_STATUS_REC"  (
		  "STATUS_ID" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_OPER_STATUS_REC" IS '¼ ¼¼id';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_OPER_STATUS_REC"."STATUS_ID" IS 'status_id';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OPER_STATUS_REC"

ALTER TABLE "YKT_CUR "."T_PIF_OPER_STATUS_REC" 
	ADD PRIMARY KEY
		("STATUS_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_OUTER_SYSTEM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_OUTER_SYSTEM"  (
		  "ID" INTEGER NOT NULL , 
		  "SNAME" VARCHAR(20) , 
		  "PERSON_NAME" VARCHAR(10) , 
		  "TEL" DECIMAL(20,0) , 
		  "ADDRESS" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_OUTER_SYSTEM"

ALTER TABLE "YKT_CUR "."T_PIF_OUTER_SYSTEM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_PHYDEVICE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_PHYDEVICE"  (
		  "PHYTYPE" INTEGER NOT NULL , 
		  "DNAME" VARCHAR(30) , 
		  "DTYPE" VARCHAR(30) , 
		  "FACTORY" VARCHAR(50) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_PHYDEVICE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_PHYDEVICE"

ALTER TABLE "YKT_CUR "."T_PIF_PHYDEVICE" 
	ADD PRIMARY KEY
		("PHYTYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SHOP_DUTY_FEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SHOP_DUTY_FEE"  (
		  "ID" INTEGER NOT NULL , 
		  "CNAME" VARCHAR(60) , 
		  "RATIO" DOUBLE , 
		  "CYCLE" INTEGER , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SHOP_DUTY_FEE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SHOP_DUTY_FEE"

ALTER TABLE "YKT_CUR "."T_PIF_SHOP_DUTY_FEE" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SHOP_MANAGE_FEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SHOP_MANAGE_FEE"  (
		  "ID" INTEGER NOT NULL , 
		  "CNAME" VARCHAR(60) , 
		  "RATIO" DOUBLE , 
		  "CYCLE" INTEGER , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SHOP_MANAGE_FEE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SHOP_MANAGE_FEE"

ALTER TABLE "YKT_CUR "."T_PIF_SHOP_MANAGE_FEE" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SITE_INFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SITE_INFO"  (
		  "SITE_NO" VARCHAR(10) NOT NULL , 
		  "MACHINE_NAME" VARCHAR(32) NOT NULL , 
		  "IP_ADDR" VARCHAR(20) , 
		  "MAC_ADDR" VARCHAR(20) , 
		  "NOTES" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SITE_INFO" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SITE_INFO"."IP_ADDR" IS 'IP';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SITE_INFO"."MACHINE_NAME" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SITE_INFO"."MAC_ADDR" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SITE_INFO"."NOTES" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SITE_INFO"."SITE_NO" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SITE_INFO"

ALTER TABLE "YKT_CUR "."T_PIF_SITE_INFO" 
	ADD PRIMARY KEY
		("SITE_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SPEFEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SPEFEE"  (
		  "DEPT_CODE" VARCHAR(10) NOT NULL , 
		  "CUT_TYPE" INTEGER NOT NULL , 
		  "FEE_TYPE" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SPEFEE"

ALTER TABLE "YKT_CUR "."T_PIF_SPEFEE" 
	ADD PRIMARY KEY
		("DEPT_CODE",
		 "CUT_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SUBSYSTEM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SUBSYSTEM"  (
		  "SYSTEM_ID" INTEGER NOT NULL , 
		  "SYSTEM_NAME" VARCHAR(60) , 
		  "SYSTEM_TYPE" INTEGER , 
		  "STATE" INTEGER , 
		  "AREA" INTEGER , 
		  "SERVER_ID" INTEGER , 
		  "IP" VARCHAR(20) , 
		  "MAC_ADDR" VARCHAR(20) , 
		  "INIT_KEY" VARCHAR(32) , 
		  "DYNA_KEY" VARCHAR(32) , 
		  "SYNCH_TIME" VARCHAR(26) , 
		  "VERSION" INTEGER , 
		  "MANAGER" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) , 
		  "PORT" INTEGER , 
		  "FUNC_LIST" VARCHAR(255) , 
		  "ENC_TYPE" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SUBSYSTEM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SUBSYSTEM"

ALTER TABLE "YKT_CUR "."T_PIF_SUBSYSTEM" 
	ADD PRIMARY KEY
		("SYSTEM_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SUBSYS_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SUBSYS_LOG"  (
		  "LOG_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "SERVER_ID" INTEGER , 
		  "IP" VARCHAR(20) , 
		  "INIT_KEY" VARCHAR(32) , 
		  "DYNA_KEY" VARCHAR(32) , 
		  "OPERATE_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SUBSYS_LOG" IS '/';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SUBSYS_LOG"

ALTER TABLE "YKT_CUR "."T_PIF_SUBSYS_LOG" 
	ADD PRIMARY KEY
		("LOG_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SUB_UPDATE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SUB_UPDATE"  (
		  "SU_ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "SUB_ID" INTEGER NOT NULL , 
		  "SUB_VOLUME" VARCHAR(12) NOT NULL , 
		  "SUB_FLAG" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_PIF_SUB_UPDATE"."SUB_FLAG" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SUB_UPDATE"."SUB_ID" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SUB_UPDATE"."SUB_VOLUME" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_SUB_UPDATE"."SU_ID" IS '';




------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SYSKEY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SYSKEY"  (
		  "KEY_CODE" VARCHAR(60) NOT NULL , 
		  "KEY_NAME" VARCHAR(60) NOT NULL , 
		  "KEY_VALUE" DECIMAL(15,0) NOT NULL , 
		  "MAX_VALUE" DECIMAL(15,0) NOT NULL , 
		  "KEY_TYPE" CHAR(1) NOT NULL WITH DEFAULT '0' )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_SYSKEY" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_SYSKEY"

ALTER TABLE "YKT_CUR "."T_PIF_SYSKEY" 
	ADD CONSTRAINT "P_PK_SERINO_NO" PRIMARY KEY
		("KEY_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_SYSTIME"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_SYSTIME"  (
		  "LOGIC_DATE" VARCHAR(10) , 
		  "SHUTACT_DATE" VARCHAR(10) , 
		  "NEXTTRADE_DATE" VARCHAR(10) , 
		  "NATURE_DATE" VARCHAR(10) , 
		  "SHUTACT_TIME" VARCHAR(8) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_TRADECODE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_TRADECODE"  (
		  "TRADECODE" INTEGER NOT NULL , 
		  "TRADEMSG" VARCHAR(100) , 
		  "SPLITCFG" VARCHAR(255) , 
		  "FLAG" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_PIF_TRADECODE"."SPLITCFG" IS '¼';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_TRADECODE"."TRADECODE" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_PIF_TRADECODE"."TRADEMSG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_TRADECODE"

ALTER TABLE "YKT_CUR "."T_PIF_TRADECODE" 
	ADD PRIMARY KEY
		("TRADECODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_WATCH_ADDRESS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_WATCH_ADDRESS"  (
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "ADDRESS_ID" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_WATCH_ADDRESS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_WATCH_ADDRESS"

ALTER TABLE "YKT_CUR "."T_PIF_WATCH_ADDRESS" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_SERIAL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_SERIAL"  (
		  "SERIAL_NO" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_SUBSYSPARAMS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_SUBSYSPARAMS"  (
		  "SYSID" INTEGER NOT NULL , 
		  "HEARTBEAT_INTVAL" INTEGER , 
		  "HEARTBEAT_LIMIT" INTEGER , 
		  "HEARTBEAT_FUNCNO" INTEGER , 
		  "DRPT_NO" INTEGER , 
		  "QRYTASK_INTVAL" INTEGER , 
		  "EXEC_TIMEOUT" INTEGER , 
		  "DEVTYPE" VARCHAR(20) , 
		  "WORK_MODE" CHAR(1) , 
		  "COLLECT_INTVAL" INTEGER , 
		  "DEVPROFILE_FUNCNO" INTEGER , 
		  "TASK_LIMIT" INTEGER , 
		  "RESP_FUNC" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_SUBSYSPARAMS"

ALTER TABLE "YKT_CUR "."T_SUBSYSPARAMS" 
	ADD CONSTRAINT "SQL060621110302390" PRIMARY KEY
		("SYSID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_SUBSYS_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_SUBSYS_LOG"  (
		  "ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "CUST_ID" INTEGER , 
		  "LOGIN_NAME" VARCHAR(50) , 
		  "LOG_DATE" VARCHAR(8) , 
		  "LOG_TIME" VARCHAR(6) , 
		  "FLAG" INTEGER , 
		  "SUSSYS_ID" INTEGER , 
		  "COMMENTS" VARCHAR(255) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_SUBSYS_LOG"

ALTER TABLE "YKT_CUR "."T_SUBSYS_LOG" 
	ADD CONSTRAINT "SQL060510161904980" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TEST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TEST"  (
		  "TX_DATE" CHAR(8) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TEST_SERIAL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TEST_SERIAL"  (
		  "SERIAL_NO" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TEST_SERIAL"

ALTER TABLE "YKT_CUR "."T_TEST_SERIAL" 
	ADD CONSTRAINT "SQL051028184325580" PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_AA"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_AA"  (
		  "BEGIN_DATE" VARCHAR(10) NOT NULL , 
		  "BEGIN_TIME" VARCHAR(8) , 
		  "END_DATE" VARCHAR(10) , 
		  "END_TIME" VARCHAR(8) , 
		  "BAK_DATE" VARCHAR(10) , 
		  "BAK_TIME" VARCHAR(8) , 
		  "SERIAL_NO" INTEGER , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "TRADE_COUNT" INTEGER , 
		  "TRADE_FEE" DECIMAL(15,6) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "BOARDFEE" DECIMAL(9,2) , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "CONDITION_ID" INTEGER , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "REVISESERIAL_NO" INTEGER , 
		  "RESERVE_1" VARCHAR(40) , 
		  "RESERVE_2" VARCHAR(40) , 
		  "RESERVE_3" VARCHAR(40) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_AA" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_AA"

ALTER TABLE "YKT_CUR "."T_TIF_AA" 
	ADD PRIMARY KEY
		("BEGIN_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_ACT_DAYSUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_ACT_DAYSUM"  (
		  "OPERATE_DATE" VARCHAR(10) NOT NULL , 
		  "OPERATE_TIME" VARCHAR(8) NOT NULL , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "ACT_TYPE" INTEGER , 
		  "CUSTOMER_ID" INTEGER , 
		  "CUT_NAME" VARCHAR(60) , 
		  "CUT_TYPE" INTEGER , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CARD_STATE" INTEGER , 
		  "CARD_TYPE" INTEGER , 
		  "SUBNO" VARCHAR(20) , 
		  "PASSWORD" VARCHAR(32) , 
		  "CURRENT_STATE" INTEGER , 
		  "ISAUTOTRA" CHAR(1) , 
		  "LAST_BALA" DECIMAL(20,6) , 
		  "LAST_FREEBALA" DECIMAL(20,6) , 
		  "LAST_FROZEBALA" DECIMAL(20,6) , 
		  "CUR_BALA" DECIMAL(20,6) , 
		  "CUR_FREEBALA" DECIMAL(20,6) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) , 
		  "OUT_BALA" DECIMAL(20,6) , 
		  "IN_BALA" DECIMAL(20,6) , 
		  "OUT_COUNT" INTEGER , 
		  "IN_COUNT" INTEGER , 
		  "CARD_BALANCE" DECIMAL(15,6) , 
		  "CONSUME_COUNT" INTEGER , 
		  "OPEN_DATE" VARCHAR(26) , 
		  "TODAY_OUT_BALA" DECIMAL(20,6) , 
		  "TODAY_IN_BALA" DECIMAL(20,6) , 
		  "TODAY_OUT_COUNT" INTEGER , 
		  "TODAY_IN_COUNT" INTEGER , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) , 
		  "NOBALA_NUM" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_ACT_DAYSUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_ACT_DAYSUM"

ALTER TABLE "YKT_CUR "."T_TIF_ACT_DAYSUM" 
	ADD PRIMARY KEY
		("OPERATE_DATE",
		 "OPERATE_TIME",
		 "ACCOUNT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_APPEAR_AUTHEN_RECORD2"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_APPEAR_AUTHEN_RECORD2"  (
		  "AUTHEN_ID" INTEGER NOT NULL , 
		  "BENGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_APPEAR_AUTHEN_RECORD2" IS '()';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_APPEAR_AUTHEN_RECORD2"

ALTER TABLE "YKT_CUR "."T_TIF_APPEAR_AUTHEN_RECORD2" 
	ADD PRIMARY KEY
		("AUTHEN_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_AUTHEN_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_AUTHEN_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "IS_VALID" CHAR(1) , 
		  "IS_ONLINE" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_AUTHEN_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_AUTHEN_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_AUTHEN_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_AUTO_TRANS_CONDITION"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_AUTO_TRANS_CONDITION"  (
		  "ID" INTEGER NOT NULL , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "TYPE_ID" INTEGER , 
		  "BALANCE_LOW_LIMIT" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "OPERATOR_ID" VARCHAR(10) , 
		  "CONDITION_1" VARCHAR(20) , 
		  "CONDITION_2" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_AUTO_TRANS_CONDITION"

ALTER TABLE "YKT_CUR "."T_TIF_AUTO_TRANS_CONDITION" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_AUTO_TRAN_LOSS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_AUTO_TRAN_LOSS"  (
		  "ID" BIGINT NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "TRANSFER_NO" BIGINT NOT NULL , 
		  "CONDITION_ID" INTEGER , 
		  "TRANSFER_FEE" DOUBLE , 
		  "OUT_ACCOUNT_ID" INTEGER , 
		  "IN_ACCOUNT_ID" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "IS_UPDATE" CHAR(1) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_AUTO_TRAN_LOSS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_AUTO_TRAN_LOSS"

ALTER TABLE "YKT_CUR "."T_TIF_AUTO_TRAN_LOSS" 
	ADD PRIMARY KEY
		("TRANSFER_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_BANKBILL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_BANKBILL"  (
		  "OPERATE_DATE" VARCHAR(10) , 
		  "LOCALSN" INTEGER , 
		  "BANKSN" CHAR(20) , 
		  "TRADECODE" CHAR(2) , 
		  "GDCACCOUNT" CHAR(16) , 
		  "BANKCARD" CHAR(20) , 
		  "TRANSMONEY" CHAR(9) , 
		  "CHECK_FLAG" INTEGER , 
		  "CHECK_DATE" VARCHAR(10) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "RESERVE_4" VARCHAR(20) , 
		  "RESERVE_5" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_BANKBILL" IS '';




------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_BANK_COMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_BANK_COMP"  (
		  "OP_DATE" CHAR(8) NOT NULL , 
		  "TX_CODE" CHAR(6) NOT NULL , 
		  "CARD_ID" INTEGER NOT NULL , 
		  "BANKCARD" VARCHAR(40) NOT NULL , 
		  "LOCAL_SN" INTEGER NOT NULL , 
		  "BANK_SN" VARCHAR(20) NOT NULL , 
		  "TRANS_MONEY" CHAR(9) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_BANK_COMP"

ALTER TABLE "YKT_CUR "."T_TIF_BANK_COMP" 
	ADD CONSTRAINT "SQL050526205540940" PRIMARY KEY
		("OP_DATE",
		 "LOCAL_SN");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_BANK_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_BANK_RECORD"  (
		  "TRADECODE" VARCHAR(2) , 
		  "GDCACCOUNT" VARCHAR(10) , 
		  "BANKCARD" VARCHAR(20) , 
		  "LOCALSN" VARCHAR(8) , 
		  "BANKSN" VARCHAR(20) , 
		  "TRANSMONEY" VARCHAR(9) , 
		  "LINECHANGE" VARCHAR(2) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_BLACK_SHEET"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_BLACK_SHEET"  (
		  "CARD_ID" INTEGER NOT NULL , 
		  "VOLUME" VARCHAR(12) NOT NULL , 
		  "VALIDDATE" VARCHAR(12) , 
		  "STATE_ID" INTEGER , 
		  "IS_AD" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "END_DATE" VARCHAR(10) , 
		  "END_TIME" VARCHAR(8) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_BLACK_SHEET" IS '¼';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_BLACK_SHEET"

ALTER TABLE "YKT_CUR "."T_TIF_BLACK_SHEET" 
	ADD PRIMARY KEY
		("VOLUME");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_BTOS_TRAN_LOSS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_BTOS_TRAN_LOSS"  (
		  "ID" BIGINT NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "TRANSFER_NO" BIGINT NOT NULL , 
		  "TRANSFER_FEE" DOUBLE , 
		  "OUT_ACCOUNT_ID" INTEGER , 
		  "IN_ACCOUNT_ID" INTEGER , 
		  "OPERATOR_ID" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "IS_UPDATE" CHAR(1) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_BTOS_TRAN_LOSS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_BTOS_TRAN_LOSS"

ALTER TABLE "YKT_CUR "."T_TIF_BTOS_TRAN_LOSS" 
	ADD PRIMARY KEY
		("TRANSFER_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CARDMESS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CARDMESS"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "SUBSIDY_FEE" DECIMAL(9,2) , 
		  "TOPUP_FEE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "OPER_CODE" VARCHAR(10) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER NOT NULL , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CARDMESS"

ALTER TABLE "YKT_CUR "."T_TIF_CARDMESS" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CFGSPLIT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CFGSPLIT"  (
		  "TXTYPE" INTEGER NOT NULL , 
		  "TXNAME" VARCHAR(60) , 
		  "DBFLAG" INTEGER NOT NULL , 
		  "CRFLAG" INTEGER NOT NULL , 
		  "DBSUBNO" VARCHAR(20) , 
		  "CRSUBNO" VARCHAR(20) , 
		  "DBACTNO" VARCHAR(30) , 
		  "CRACTNO" VARCHAR(30) , 
		  "FUNDTYPE" INTEGER , 
		  "SUMMARY" VARCHAR(60) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CFGSPLIT"

ALTER TABLE "YKT_CUR "."T_TIF_CFGSPLIT" 
	ADD PRIMARY KEY
		("TXTYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CFGTXFEE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CFGTXFEE"  (
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "TX_CODE" INTEGER NOT NULL , 
		  "FEE_LIST" VARCHAR(40) , 
		  "IDXDBACTNO_LIST" VARCHAR(40) , 
		  "IDXCRACTNO_LIST" VARCHAR(40) , 
		  "FORMULA_LIST" VARCHAR(255) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CFGTXFEE"

ALTER TABLE "YKT_CUR "."T_TIF_CFGTXFEE" 
	ADD PRIMARY KEY
		("TX_CODE",
		 "FEE_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CHECKOUT_CUR"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CHECKOUT_CUR"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" VARCHAR(8) , 
		  "CHECKOUT_NO" INTEGER , 
		  "CHECKOUT_ENDTIME" VARCHAR(12) , 
		  "START_NO" INTEGER , 
		  "END_NO" INTEGER , 
		  "UPTOSNUFF_COUNT" INTEGER , 
		  "UPTOSNUFF_SUM" INTEGER , 
		  "CANCEL_COUNT" INTEGER , 
		  "CANCEL_SUM" INTEGER , 
		  "ABNORMITY_COUNT" INTEGER , 
		  "ABNORMITY_SUM" INTEGER , 
		  "ELSE_COUNT" INTEGER , 
		  "SIGN" INTEGER , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_CHECKOUT_CUR" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CHECKOUT_CUR"

ALTER TABLE "YKT_CUR "."T_TIF_CHECKOUT_CUR" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CHECKOUT_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CHECKOUT_HIS"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" VARCHAR(8) , 
		  "CHECKOUT_NO" INTEGER , 
		  "CHECKOUT_ENDTIME" VARCHAR(12) , 
		  "START_NO" INTEGER , 
		  "END_NO" INTEGER , 
		  "UPTOSNUFF_COUNT" INTEGER , 
		  "UPTOSNUFF_SUM" INTEGER , 
		  "CANCEL_COUNT" INTEGER , 
		  "CANCEL_SUM" INTEGER , 
		  "ABNORMITY_COUNT" INTEGER , 
		  "ABNORMITY_SUM" INTEGER , 
		  "ELSE_COUNT" INTEGER , 
		  "SIGN" INTEGER , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_CHECKOUT_HIS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CHECKOUT_HIS"

ALTER TABLE "YKT_CUR "."T_TIF_CHECKOUT_HIS" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CHECK_BACK"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CHECK_BACK"  (
		  "ID" BIGINT NOT NULL , 
		  "BTOS_TRAN_COUNT" CHAR(1) , 
		  "BTOS_TRAN_FEE" CHAR(1) , 
		  "STOB_TRAN_COUNT" CHAR(1) , 
		  "STOB_TRAN_FEE" CHAR(1) , 
		  "QUANCUN_COUNT" CHAR(1) , 
		  "QUANCUN_FEE" CHAR(1) , 
		  "AUTO_TRAN_COUNT" CHAR(1) , 
		  "AUTO_TRAN_FEE" CHAR(1) , 
		  "OTHER_TRAN_COUNT" CHAR(1) , 
		  "OTHER_TRAN_FEE" CHAR(1) , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_CHECK_BACK" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CHECK_BACK"

ALTER TABLE "YKT_CUR "."T_TIF_CHECK_BACK" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CHECK_SUBSYSTEM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CHECK_SUBSYSTEM"  (
		  "ID" INTEGER NOT NULL , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "IS_CONSISTENT1" CHAR(1) , 
		  "IS_CONSISTENT2" CHAR(1) , 
		  "FEE_CONSISTENT" CHAR(1) , 
		  "IS_CONSISTENT3" CHAR(1) , 
		  "IS_CONSISTENT4" CHAR(1) , 
		  "IS_CONSISTENT5" CHAR(1) , 
		  "IS_CONSISTENT6" CHAR(1) , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_CHECK_SUBSYSTEM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CHECK_SUBSYSTEM"

ALTER TABLE "YKT_CUR "."T_TIF_CHECK_SUBSYSTEM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_COMPUTER_COSUME_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_COMPUTER_COSUME_RECORD"  (
		  "CONSUME_ID" INTEGER NOT NULL , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_COMPUTER_COSUME_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_COMPUTER_COSUME_RECORD" 
	ADD PRIMARY KEY
		("CONSUME_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_COSUME_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_COSUME_HIS"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "TMARK" INTEGER , 
		  "SYSTEM_ID" INTEGER , 
		  "DEVICE_ID" VARCHAR(8) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "OPERATE_DATE" VARCHAR(6) , 
		  "OPERATE_TIME" VARCHAR(6) , 
		  "CONSUME_COUNT" INTEGER , 
		  "CONSUME_FEE" INTEGER , 
		  "IN_BALANCE" INTEGER , 
		  "OUT_BALANCE" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_COSUME_HIS"

ALTER TABLE "YKT_CUR "."T_TIF_COSUME_HIS" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_COSUME_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_COSUME_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "CONSUME_COUNT" INTEGER , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "CONSUME_FEE" DECIMAL(9,2) , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER NOT NULL , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_COSUME_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_COSUME_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_CUT_INFO_UPDATE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_CUT_INFO_UPDATE"  (
		  "ID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "CARD_ID" INTEGER NOT NULL , 
		  "VOLUME" VARCHAR(12) NOT NULL , 
		  "FLAG" INTEGER NOT NULL WITH DEFAULT 0 , 
		  "OPERATE_DATE" CHAR(8) , 
		  "OPERATE_TIME" CHAR(6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_CUT_INFO_UPDATE"

ALTER TABLE "YKT_CUR "."T_TIF_CUT_INFO_UPDATE" 
	ADD CONSTRAINT "SQL050830162420000" PRIMARY KEY
		("ID");


-- DDL Statements for unique constraints on Table "YKT_CUR "."T_TIF_CUT_INFO_UPDATE"

ALTER TABLE "YKT_CUR "."T_TIF_CUT_INFO_UPDATE" 
	ADD CONSTRAINT "SQL050830162420170" UNIQUE
		("VOLUME");


------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DAY_BACK_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DAY_BACK_SUM"  (
		  "ID" BIGINT NOT NULL , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_FEE" DOUBLE , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_FEE" DOUBLE , 
		  "QUANCUN_COUNT" BIGINT , 
		  "QUANCUN_FEE" DOUBLE , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "AUTO_TRAN_FEE" DOUBLE , 
		  "OTHER_TRAN_COUNT" BIGINT , 
		  "OTHER_TRAN_FEE" DOUBLE , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_DAY_BACK_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DAY_BACK_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_DAY_BACK_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DAY_MONITOR_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DAY_MONITOR_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "ERROR_ID" INTEGER , 
		  "ERROR_COUNT" BIGINT , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_DAY_MONITOR_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DAY_MONITOR_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_DAY_MONITOR_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DAY_OPERATE_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DAY_OPERATE_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "CUSTOMER_LOGIN" BIGINT , 
		  "CUSTOMER_LOGOFF" BIGINT , 
		  "CARD_LOGIN" BIGINT , 
		  "CARD_LOGOFF" BIGINT , 
		  "CARD_LOSS" BIGINT , 
		  "CARD_RESUME" BIGINT , 
		  "CARD_CHANGE" BIGINT , 
		  "ACCOUNT_LOGIN" BIGINT , 
		  "ACCOUNT_LOGOFF" BIGINT , 
		  "ACCOUNT_UNFREEZE" BIGINT , 
		  "ACCOUNT_FREEZE" BIGINT , 
		  "CASH_DEPOSIT" BIGINT , 
		  "SUMDATE" DATE , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DAY_OPERATE_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_DAY_OPERATE_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DAY_SUBSYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DAY_SUBSYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "SUM_RECORD_COUNT" INTEGER , 
		  "CONSUME_COUNT" INTEGER , 
		  "SUM_FEE" DECIMAL(15,2) , 
		  "AUTHEN_COUNT" INTEGER , 
		  "OTHER_COUNT" INTEGER , 
		  "DEPOSIT_COUNT" INTEGER , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_DAY_SUBSYSTEM_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DAY_SUBSYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_DAY_SUBSYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DAY_SYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DAY_SYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "ACCOUNT_COUNT" BIGINT , 
		  "NEW_ACCOUNT_COUNT" BIGINT , 
		  "LOGOFF_ACCOUNT_COUNT" BIGINT , 
		  "SUM_CUSTOMER" BIGINT , 
		  "NEW_CUSTOMER_COUNT" BIGINT , 
		  "LOGOFF_CUSTOMER_COUNT" BIGINT , 
		  "SUM_CARD" BIGINT , 
		  "NEW_CARD__COUNT" BIGINT , 
		  "LOGOFF_CARD_COUNT" BIGINT , 
		  "SUM_BALANCE" DECIMAL(15,2) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "SUM_TAKING_FEE" DECIMAL(15,2) , 
		  "SUM_DEPOSITCASH_FEE" DECIMAL(15,2) , 
		  "SUMFEE_FROM_BACK" DECIMAL(15,2) , 
		  "SUMFEE_TO_BACK" DECIMAL(15,2) , 
		  "SUM_MANAGE_FEE" DECIMAL(15,2) , 
		  "SUM_DUTY_FEE" DECIMAL(15,2) , 
		  "QUANCUN_COUNT" BIGINT , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "INSIDE_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "SUBSIDY_COUNT" BIGINT , 
		  "SELFH_DEPOSIT_COUNT" BIGINT , 
		  "CASH_DEPOSIT_COUNT" BIGINT , 
		  "COSUME_LOG_COUNT" BIGINT , 
		  "AUTHEN_LOG_COUNT" BIGINT , 
		  "OTHER_LOG_COUNT" BIGINT , 
		  "SUMDATE" DATE , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DAY_SYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_DAY_SYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DEPOSIT_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DEPOSIT_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_BALANCE" DECIMAL(9,2) NOT NULL , 
		  "CONSUME_COUNT" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "OPERATOR_ID" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_DEPOSIT_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DEPOSIT_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_DEPOSIT_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DIFF_TRANSFER"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DIFF_TRANSFER"  (
		  "OP_DATE" CHAR(8) NOT NULL , 
		  "OP_TIME" CHAR(6) , 
		  "LOCAL_SN" INTEGER NOT NULL , 
		  "BANK_SN" VARCHAR(40) , 
		  "LOCAL_AMT" DECIMAL(15,2) , 
		  "BANK_AMT" DECIMAL(15,2) , 
		  "CARD_ID" INTEGER NOT NULL , 
		  "BANKCARD" VARCHAR(40) , 
		  "DIFF_AMT" DECIMAL(15,2) , 
		  "STATUS" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_TIF_DIFF_TRANSFER"."STATUS" IS '';




------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_DOOR_AUTHEN_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_DOOR_AUTHEN_RECORD"  (
		  "AUTHEN_ID" INTEGER NOT NULL , 
		  "BENGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_DOOR_AUTHEN_RECORD" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_DOOR_AUTHEN_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_DOOR_AUTHEN_RECORD" 
	ADD PRIMARY KEY
		("AUTHEN_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_ELECT_COSUME_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_ELECT_COSUME_RECORD"  (
		  "CONSUME_ID" INTEGER NOT NULL , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "ELECT_QUANTITY" DOUBLE , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_ELECT_COSUME_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_ELECT_COSUME_RECORD" 
	ADD PRIMARY KEY
		("CONSUME_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_HOSPITALLOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_HOSPITALLOG"  (
		  "CONSUME_ID" INTEGER NOT NULL , 
		  "FEE_TYPE_ID" INTEGER , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_HOSPITALLOG"

ALTER TABLE "YKT_CUR "."T_TIF_HOSPITALLOG" 
	ADD PRIMARY KEY
		("CONSUME_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_HOSPITAL_CONSUME_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_HOSPITAL_CONSUME_TYPE"  (
		  "TYPE_ID" INTEGER NOT NULL , 
		  "CNAME" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_HOSPITAL_CONSUME_TYPE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_HOSPITAL_CONSUME_TYPE"

ALTER TABLE "YKT_CUR "."T_TIF_HOSPITAL_CONSUME_TYPE" 
	ADD PRIMARY KEY
		("TYPE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LIBRARY_AUTHEN_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LIBRARY_AUTHEN_RECORD"  (
		  "AUTHEN_ID" INTEGER NOT NULL , 
		  "BENGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LIBRARY_AUTHEN_RECORD" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LIBRARY_AUTHEN_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_LIBRARY_AUTHEN_RECORD" 
	ADD PRIMARY KEY
		("AUTHEN_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LIBRARY_CONSUME_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LIBRARY_CONSUME_TYPE"  (
		  "TYPE_ID" INTEGER NOT NULL , 
		  "CNAME" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LIBRARY_CONSUME_TYPE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LIBRARY_CONSUME_TYPE"

ALTER TABLE "YKT_CUR "."T_TIF_LIBRARY_CONSUME_TYPE" 
	ADD PRIMARY KEY
		("TYPE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LIBRARY_COSUME_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LIBRARY_COSUME_RECORD"  (
		  "CONSUME_ID" INTEGER NOT NULL , 
		  "FEE_TYPE_ID" INTEGER , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LIBRARY_COSUME_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_LIBRARY_COSUME_RECORD" 
	ADD PRIMARY KEY
		("CONSUME_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LOSEAUTHEN_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LOSEAUTHEN_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "SERIAL_NO" BIGINT NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "COLLECT_TIME" TIMESTAMP , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "IS_VALID" CHAR(1) , 
		  "IS_ONLINE" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LOSEAUTHEN_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LOSEAUTHEN_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_LOSEAUTHEN_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LOSECONSUME_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LOSECONSUME_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "SERIAL_NO" BIGINT NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "COLLECT_TIME" TIMESTAMP , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_BALANCE" DECIMAL(9,2) NOT NULL , 
		  "CONSUME_COUNT" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "ACCOUNT_ID" DECIMAL(11,0) , 
		  "CONSUME_FEE" DECIMAL(9,2) , 
		  "IS_ONLINE" CHAR(1) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LOSECONSUME_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LOSECONSUME_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_LOSECONSUME_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LOSEDEPOIST_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LOSEDEPOIST_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "SERIAL_NO" BIGINT NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "MAINDEVICE_ID" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "COLLECT_TIME" TIMESTAMP , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_BALANCE" DECIMAL(9,2) NOT NULL , 
		  "CONSUME_COUNT" INTEGER , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_ACCOUNT_ID" DECIMAL(11,0) , 
		  "OUT_ACCOUNT_ID" DECIMAL(11,0) , 
		  "OPERATOR_ID" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LOSEDEPOIST_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LOSEDEPOIST_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_LOSEDEPOIST_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_LOSEWATCH_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_LOSEWATCH_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "SERIAL_NO" BIGINT NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "COLLECT_TIME" TIMESTAMP , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "BENGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "IS_FULL" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_LOSEWATCH_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_LOSEWATCH_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_LOSEWATCH_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MONTH_BACK_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MONTH_BACK_SUM"  (
		  "ID" BIGINT NOT NULL , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_FEE" DOUBLE , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_FEE" DOUBLE , 
		  "QUANCUN_COUNT" BIGINT , 
		  "QUANCUN_FEE" DOUBLE , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "AUTO_TRAN_FEE" DOUBLE , 
		  "OTHER_TRAN_COUNT" BIGINT , 
		  "OTHER_TRAN_FEE" DOUBLE , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_MONTH_BACK_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MONTH_BACK_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_MONTH_BACK_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MONTH_MONITOR_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MONTH_MONITOR_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "ERROR_ID" INTEGER , 
		  "ERROR_COUNT" BIGINT , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_MONTH_MONITOR_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MONTH_MONITOR_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_MONTH_MONITOR_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MONTH_OPERATE_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MONTH_OPERATE_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "CUSTOMER_LOGIN" BIGINT , 
		  "CUSTOMER_LOGOFF" BIGINT , 
		  "CARD_LOGIN" BIGINT , 
		  "CARD_LOGOFF" BIGINT , 
		  "CARD_LOSS" BIGINT , 
		  "CARD_RESUME" BIGINT , 
		  "CARD_CHANGE" BIGINT , 
		  "ACCOUNT_LOGIN" BIGINT , 
		  "ACCOUNT_LOGOFF" BIGINT , 
		  "ACCOUNT_UNFREEZE" BIGINT , 
		  "ACCOUNT_FREEZE" BIGINT , 
		  "CASH_DEPOSIT" BIGINT , 
		  "SUMDATE" DATE , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MONTH_OPERATE_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_MONTH_OPERATE_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MONTH_SUBSYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MONTH_SUBSYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "SUM_RECORD_COUNT" INTEGER , 
		  "CONSUME_COUNT" INTEGER , 
		  "SUM_FEE" DECIMAL(15,2) , 
		  "AUTHEN_COUNT" INTEGER , 
		  "OTHER_COUNT" INTEGER , 
		  "DEPOSIT_COUNT" INTEGER , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_MONTH_SUBSYSTEM_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MONTH_SUBSYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_MONTH_SUBSYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MONTH_SYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MONTH_SYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "ACCOUNT_COUNT" BIGINT , 
		  "NEW_ACCOUNT_COUNT" BIGINT , 
		  "LOGOFF_ACCOUNT_COUNT" BIGINT , 
		  "SUM_CUSTOMER" BIGINT , 
		  "NEW_CUSTOMER_COUNT" BIGINT , 
		  "LOGOFF_CUSTOMER_COUNT" BIGINT , 
		  "SUM_CARD" BIGINT , 
		  "NEW_CARD__COUNT" BIGINT , 
		  "LOGOFF_CARD_COUNT" BIGINT , 
		  "SUM_BALANCE" DECIMAL(15,2) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "SUM_TAKING_FEE" DECIMAL(15,2) , 
		  "SUM_DEPOSITCASH_FEE" DECIMAL(15,2) , 
		  "SUMFEE_FROM_BACK" DECIMAL(15,2) , 
		  "SUMFEE_TO_BACK" DECIMAL(15,2) , 
		  "SUM_MANAGE_FEE" DECIMAL(15,2) , 
		  "SUM_DUTY_FEE" DECIMAL(15,2) , 
		  "QUANCUN_COUNT" BIGINT , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "INSIDE_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "SUBSIDY_COUNT" BIGINT , 
		  "SELFH_DEPOSIT_COUNT" BIGINT , 
		  "CASH_DEPOSIT_COUNT" BIGINT , 
		  "COSUME_LOG_COUNT" BIGINT , 
		  "AUTHEN_LOG_COUNT" BIGINT , 
		  "OTHER_LOG_COUNT" BIGINT , 
		  "SUMDATE" DATE , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MONTH_SYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_MONTH_SYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_OUTSYS_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_OUTSYS_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" DATE , 
		  "OPERATE_TIME" TIME , 
		  "COLLECT_DATE" DATE , 
		  "COLLECT_TIME" TIME , 
		  "ENTERACT_DATE" DATE , 
		  "ENTERACT_TIME" TIME , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "OPERATE_NO" BIGINT , 
		  "EMPLOYEE_ID" BIGINT , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_OUTSYS_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_OUTSYS_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_OUTSYS_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_RCVDTL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_RCVDTL"  (
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) NOT NULL , 
		  "CARD_NO" INTEGER NOT NULL , 
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "PURSE_NO" INTEGER , 
		  "IN_BALA" INTEGER , 
		  "OUT_BALA" INTEGER , 
		  "AMOUNT" INTEGER , 
		  "TOTAL_CNT" INTEGER , 
		  "TX_CODE" INTEGER NOT NULL , 
		  "TX_MARK" INTEGER , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(4) , 
		  "INPOWER_NO" CHAR(8) , 
		  "SYS_ID" INTEGER , 
		  "OPER_NO" CHAR(8) , 
		  "STATUS" CHAR(1) , 
		  "COL_TIMESTAMP" CHAR(20) , 
		  "DEAL_DATE" CHAR(8) , 
		  "DEAL_TIME" CHAR(6) , 
		  "FEE_CODE" INTEGER , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_RCVDTL"

ALTER TABLE "YKT_CUR "."T_TIF_RCVDTL" 
	ADD PRIMARY KEY
		("SERIAL_NO",
		 "TX_DATE",
		 "TX_TIME",
		 "DEVICE_ID",
		 "CARD_NO",
		 "TX_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_ACTIVE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_ACTIVE"  (
		  "BALANCE_DATE" VARCHAR(10) NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "TRADE_NUMBER" INTEGER , 
		  "TRADE_AMT" DECIMAL(15,6) , 
		  "ACC_ADDNUM" INTEGER , 
		  "ACC_AMT" DECIMAL(15,6) , 
		  "SHOP_ADDNUM" INTEGER , 
		  "SHOP_AMT" DECIMAL(15,6) , 
		  "DEP_AMT" DECIMAL(15,6) , 
		  "EARN_AMT" DECIMAL(15,6) , 
		  "MNG_AMT" DECIMAL(15,6) , 
		  "COST_AMT" DECIMAL(15,6) , 
		  "ENSURE_AMT" DECIMAL(15,6) , 
		  "BANK_AMT" DECIMAL(15,6) , 
		  "CASH_AMT" DECIMAL(15,6) , 
		  "OPERATOR_CODE" VARCHAR(10) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) , 
		  "CHECK_ADD_AMT" DECIMAL(15,6) , 
		  "OUTLAY_ADD_AMT" DECIMAL(15,6) , 
		  "DOWN_SUBSIDY_AMT" DECIMAL(15,6) , 
		  "UP_SUBSIDY_AMT" DECIMAL(15,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_ACTIVE"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_ACTIVE" 
	ADD PRIMARY KEY
		("BALANCE_DATE",
		 "SERI_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_BANK_TRANSFER"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_BANK_TRANSFER"  (
		  "RMB_BATCH_NO1" VARCHAR(14) , 
		  "RMB_SEQ_NO" VARCHAR(6) , 
		  "RMB_ACC_STATUS1" CHAR(1) , 
		  "RMB_TRAN_KIND" CHAR(1) , 
		  "RMB_CUST_NAME" VARCHAR(50) , 
		  "RMB_ACC_NO" VARCHAR(20) , 
		  "RMB_CB_CR" CHAR(1) , 
		  "RMB_TRAN_AMT" DECIMAL(15,2) , 
		  "RMB_CUR_CODE" VARCHAR(3) , 
		  "RMB_HOST_NO" VARCHAR(8) , 
		  "RMB_RET_CODE" VARCHAR(4) , 
		  "RMB_ACC_DATE" DATE , 
		  "RMB_TRAN_NO" VARCHAR(9) , 
		  "RMB_OPEN_BRANCH" VARCHAR(7) , 
		  "RMB_VCHO_KIND" VARCHAR(2) , 
		  "RMB_VCHO_BAT_NO" VARCHAR(2) , 
		  "RMB_VCHO_NO" VARCHAR(9) , 
		  "RMB_MEMO" VARCHAR(22) , 
		  "RMB_TRAN_INFO" VARCHAR(200) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_CARDDB_NOBALANCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_CARDDB_NOBALANCE"  (
		  "BALANCE_DATE" VARCHAR(10) , 
		  "ACCOUNT_ID" CHAR(16) , 
		  "CARD_ID" INTEGER , 
		  "CUT_NAME" VARCHAR(60) , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "TYPE_ID" INTEGER , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "DB_BALA" DECIMAL(15,2) , 
		  "CARD_BALA" DECIMAL(15,2) , 
		  "NOBALA_NUM" INTEGER , 
		  "DIFF_BALA" DECIMAL(15,2) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_DEPTTRADE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_DEPTTRADE"  (
		  "BALANCE_DATE" CHAR(8) NOT NULL , 
		  "DEPT_CODE" CHAR(10) NOT NULL , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "OUTORIN" INTEGER NOT NULL , 
		  "OPCOUNT" INTEGER , 
		  "OPFEE" INTEGER , 
		  "RESERVE_1" VARCHAR(50) , 
		  "RESERVE_2" VARCHAR(50) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_DEPTTRADE"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_DEPTTRADE" 
	ADD CONSTRAINT "SQL051202170231490" PRIMARY KEY
		("BALANCE_DATE",
		 "DEPT_CODE",
		 "SERI_TYPE",
		 "FEE_TYPE",
		 "OUTORIN");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_ERRACC"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_ERRACC"  (
		  "BALANCE_DATE" VARCHAR(10) NOT NULL , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "CUT_NAME" VARCHAR(60) , 
		  "STUEMP_NO" VARCHAR(20) , 
		  "TYPE_ID" INTEGER , 
		  "DEPT_NAME" VARCHAR(100) , 
		  "LAST_BALA" DECIMAL(15,2) , 
		  "CUR_BALA" DECIMAL(15,2) , 
		  "TRADE_AMT" DECIMAL(15,2) , 
		  "DIFF_BALA" DECIMAL(15,2) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_ERRACC"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_ERRACC" 
	ADD PRIMARY KEY
		("BALANCE_DATE",
		 "ACCOUNT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_OPER"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_OPER"  (
		  "BALANCE_DATE" VARCHAR(10) NOT NULL , 
		  "OPERATOR_CODE" VARCHAR(10) NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "MAINDEVICE_ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "HAPPEN_NUM" INTEGER , 
		  "HAPPEN_AMT" DECIMAL(15,6) , 
		  "MNG_AMT" DECIMAL(15,6) , 
		  "ENSURE_AMT" DECIMAL(15,6) , 
		  "COST_AMT" DECIMAL(15,6) , 
		  "DEP_AMT" DECIMAL(15,6) , 
		  "EARN_AMT" DECIMAL(15,6) , 
		  "BANK_AMT" DECIMAL(15,6) , 
		  "CASH_AMT" DECIMAL(15,6) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) , 
		  "ACC_ADD_AMT" DECIMAL(15,6) , 
		  "SHP_ADD_AMT" DECIMAL(15,6) , 
		  "CHECK_AMT" DECIMAL(15,6) , 
		  "OUTLAY_AMT" DECIMAL(15,6) , 
		  "DOWN_SUBSIDY_AMT" DECIMAL(15,6) , 
		  "UP_SUBSIDY_AMT" DECIMAL(15,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_OPER"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_OPER" 
	ADD PRIMARY KEY
		("BALANCE_DATE",
		 "OPERATOR_CODE",
		 "SERI_TYPE",
		 "MAINDEVICE_ID",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_OPER_CARD_AMT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_OPER_CARD_AMT"  (
		  "BALANCE_DATE" VARCHAR(10) NOT NULL , 
		  "OPERATOR_CODE" VARCHAR(10) NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "MAINDEVICE_ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "BADCARD_STATUS" INTEGER NOT NULL , 
		  "HAPPEN_NUM" INTEGER , 
		  "HAPPEN_AMT" DECIMAL(15,6) , 
		  "MNG_AMT" DECIMAL(15,6) , 
		  "ENSURE_AMT" DECIMAL(15,6) , 
		  "COST_AMT" DECIMAL(15,6) , 
		  "DEP_AMT" DECIMAL(15,6) , 
		  "EARN_AMT" DECIMAL(15,6) , 
		  "BANK_AMT" DECIMAL(15,6) , 
		  "CASH_AMT" DECIMAL(15,6) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) , 
		  "ACC_ADD_AMT" DECIMAL(15,6) , 
		  "SHP_ADD_AMT" DECIMAL(15,6) , 
		  "CHECK_AMT" DECIMAL(15,6) , 
		  "OUTLAY_AMT" DECIMAL(15,6) , 
		  "DOWN_SUBSIDY_AMT" DECIMAL(15,6) , 
		  "UP_SUBSIDY_AMT" DECIMAL(15,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_OPER_CARD_AMT"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_OPER_CARD_AMT" 
	ADD PRIMARY KEY
		("BALANCE_DATE",
		 "OPERATOR_CODE",
		 "SERI_TYPE",
		 "MAINDEVICE_ID",
		 "DEVICE_ID",
		 "BADCARD_STATUS");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_RICH_DEBT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_RICH_DEBT"  (
		  "BALANCE_DATE" VARCHAR(10) , 
		  "SUB_CODE" INTEGER , 
		  "SUB_NAME" VARCHAR(50) , 
		  "SUB_TYPE" INTEGER , 
		  "LAST_BALA" DECIMAL(15,2) , 
		  "CUR_BALA" DECIMAL(15,2) , 
		  "CHANGE_AMT" DECIMAL(15,2) , 
		  "DATE_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_SHOP_BALANCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_SHOP_BALANCE"  (
		  "BALANCE_DATE" VARCHAR(10) NOT NULL , 
		  "SHOP_ID" INTEGER NOT NULL , 
		  "SHOP_NAME" VARCHAR(50) , 
		  "DEPT_ID" INTEGER , 
		  "TRADE_NUM" INTEGER , 
		  "TRADE_AMT" DECIMAL(15,6) , 
		  "MNG_AMT" DECIMAL(15,6) , 
		  "TOTAL_AMT" DECIMAL(15,6) , 
		  "DATA_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_SHOP_BALANCE"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_SHOP_BALANCE" 
	ADD CONSTRAINT "SQL051207172636260" PRIMARY KEY
		("BALANCE_DATE",
		 "SHOP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REPORT_TRANS_COMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REPORT_TRANS_COMP"  (
		  "CMP_DATE" VARCHAR(10) NOT NULL , 
		  "CMP_FLAG" INTEGER , 
		  "ADJUST_FLAG" INTEGER , 
		  "LOCALSELF_NUM" INTEGER , 
		  "LOCALSELF_AMT" DECIMAL(15,2) , 
		  "LOCALAUTO_NUM" INTEGER , 
		  "LOCALAUTO_AMT" DECIMAL(15,2) , 
		  "LOCALFEE_NUM" INTEGER , 
		  "LOCALFEE_AMT" DECIMAL(15,2) , 
		  "BANKSELF_NUM" INTEGER , 
		  "BANKSELF_AMT" DECIMAL(15,2) , 
		  "BANKAUTO_NUM" INTEGER , 
		  "BANKAUTO_AMT" DECIMAL(15,2) , 
		  "BANKFEE_NUM" INTEGER , 
		  "BANKFEE_AMT" DECIMAL(15,2) , 
		  "DATE_SIGN" VARCHAR(8) , 
		  "RESERVE1" VARCHAR(20) , 
		  "RESERVE2" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REPORT_TRANS_COMP"

ALTER TABLE "YKT_CUR "."T_TIF_REPORT_TRANS_COMP" 
	ADD CONSTRAINT "SQL050702152723160" PRIMARY KEY
		("CMP_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_REVISE_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_REVISE_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "DEVICE_ID" INTEGER , 
		  "SPONSOR_TYPE" INTEGER , 
		  "SPONSOR_ID" INTEGER , 
		  "REASON_NO" INTEGER , 
		  "TRANSFER_ID" INTEGER , 
		  "TRANSFER_TYPE_ID" INTEGER , 
		  "UPDATE_FEE" DECIMAL(9,2) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_REVISE_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_REVISE_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_REVISE_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SAVDTL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SAVDTL"  (
		  "SEQNO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "CARD_NO" INTEGER , 
		  "BILL_TYPE" INTEGER , 
		  "BILL_NO" VARCHAR(20) , 
		  "CNT" INTEGER , 
		  "AMOUNT" DECIMAL(9,2) , 
		  "TX_CODE" INTEGER , 
		  "OPER_NO" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(150) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SAVDTL"

ALTER TABLE "YKT_CUR "."T_TIF_SAVDTL" 
	ADD PRIMARY KEY
		("SEQNO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SCHBILL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SCHBILL"  (
		  "ID" INTEGER NOT NULL , 
		  "SERINO" INTEGER NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "ACT_ID" CHAR(16) NOT NULL , 
		  "OUTORIN" INTEGER , 
		  "SUBNO" VARCHAR(20) , 
		  "WARRANT_TYPE" INTEGER , 
		  "WARRANT_NO" VARCHAR(20) , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "OP_FEE" DECIMAL(9,2) , 
		  "CHECK_FLAG" INTEGER , 
		  "CHECK_DATE" VARCHAR(10) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "RESERVE_4" VARCHAR(20) , 
		  "RESERVE_5" VARCHAR(20) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SCHBILL" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SCHBILL"

ALTER TABLE "YKT_CUR "."T_TIF_SCHBILL" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SELFHELP_TRAN_LOSS"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SELFHELP_TRAN_LOSS"  (
		  "ID" BIGINT NOT NULL , 
		  "IS_REPAIR" CHAR(1) , 
		  "TRANSFER_NO" BIGINT NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "TRANSFER_FEE" DOUBLE , 
		  "OUT_ACCOUNT_ID" INTEGER , 
		  "IN_ACCOUNT_ID" INTEGER , 
		  "OPERATE_TIME" TIMESTAMP , 
		  "IS_UPDATE" CHAR(1) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SELFHELP_TRAN_LOSS" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SELFHELP_TRAN_LOSS"

ALTER TABLE "YKT_CUR "."T_TIF_SELFHELP_TRAN_LOSS" 
	ADD PRIMARY KEY
		("TRANSFER_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SHOP_DAYSUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SHOP_DAYSUM"  (
		  "SUM_ID" INTEGER NOT NULL , 
		  "SHOP_ID" INTEGER , 
		  "ACCOUNT_ID" DECIMAL(11,0) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "TODAY_BALANCE" DECIMAL(15,2) , 
		  "IN_FEE" DECIMAL(15,2) , 
		  "OUT_FEE" DECIMAL(15,2) , 
		  "TAKING_FEE" DECIMAL(15,2) , 
		  "MANAGE_FEE" DECIMAL(15,2) , 
		  "DUTY_FEE" DECIMAL(15,2) , 
		  "OPTIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SHOP_DAYSUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SHOP_DAYSUM"

ALTER TABLE "YKT_CUR "."T_TIF_SHOP_DAYSUM" 
	ADD PRIMARY KEY
		("SUM_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SHOP_MONTHSUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SHOP_MONTHSUM"  (
		  "SUM_ID" INTEGER NOT NULL , 
		  "SHOP_ID" INTEGER , 
		  "ACCOUNT_ID" DECIMAL(11,0) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "TODAY_BALANCE" DECIMAL(15,2) , 
		  "IN_FEE" DECIMAL(15,2) , 
		  "OUT_FEE" DECIMAL(15,2) , 
		  "TAKING_FEE" DECIMAL(15,2) , 
		  "MANAGE_FEE" DECIMAL(15,2) , 
		  "DUTY_FEE" DECIMAL(15,2) , 
		  "OPTIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SHOP_MONTHSUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SHOP_MONTHSUM"

ALTER TABLE "YKT_CUR "."T_TIF_SHOP_MONTHSUM" 
	ADD PRIMARY KEY
		("SUM_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SHOP_YEARSUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SHOP_YEARSUM"  (
		  "SUM_ID" INTEGER NOT NULL , 
		  "SHOP_ID" INTEGER , 
		  "ACCOUNT_ID" DECIMAL(11,0) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "TODAY_BALANCE" DECIMAL(15,2) , 
		  "IN_FEE" DECIMAL(15,2) , 
		  "OUT_FEE" DECIMAL(15,2) , 
		  "TAKING_FEE" DECIMAL(15,2) , 
		  "MANAGE_FEE" DECIMAL(15,2) , 
		  "DUTY_FEE" DECIMAL(15,2) , 
		  "OPTIME" TIMESTAMP , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SHOP_YEARSUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SHOP_YEARSUM"

ALTER TABLE "YKT_CUR "."T_TIF_SHOP_YEARSUM" 
	ADD PRIMARY KEY
		("SUM_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SPLITCFG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SPLITCFG"  (
		  "TXTYPE" INTEGER NOT NULL , 
		  "TXNAME" VARCHAR(60) , 
		  "DBFLAG" INTEGER NOT NULL , 
		  "CRFLAG" INTEGER NOT NULL , 
		  "DBSUBNO" VARCHAR(20) NOT NULL , 
		  "CRSUBNO" VARCHAR(20) NOT NULL , 
		  "DBACTNO" VARCHAR(30) , 
		  "CRACTNO" VARCHAR(30) , 
		  "IDXDBACTNO" INTEGER , 
		  "IDXCRACTNO" INTEGER , 
		  "IDXAMT" INTEGER NOT NULL , 
		  "FUNDTYPE" INTEGER , 
		  "SUMMARY" VARCHAR(60) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SPLITCFG"

ALTER TABLE "YKT_CUR "."T_TIF_SPLITCFG" 
	ADD PRIMARY KEY
		("TXTYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SUBJECT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SUBJECT"  (
		  "SUBNO" VARCHAR(20) NOT NULL , 
		  "SUBNAME" VARCHAR(50) , 
		  "SUBTYPE" INTEGER , 
		  "DIRECT" INTEGER , 
		  "KIND" INTEGER , 
		  "FATHER" VARCHAR(20) , 
		  "LEVEL" INTEGER , 
		  "ENDFLAG" INTEGER , 
		  "SPARE1" VARCHAR(25) , 
		  "SPARE2" VARCHAR(25) , 
		  "SPARE3" VARCHAR(25) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SUBJECT"

ALTER TABLE "YKT_CUR "."T_TIF_SUBJECT" 
	ADD PRIMARY KEY
		("SUBNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SUBJECT_BALANCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SUBJECT_BALANCE"  (
		  "TXDATE" VARCHAR(10) NOT NULL , 
		  "SUBNO" VARCHAR(9) NOT NULL , 
		  "SUBNAME" VARCHAR(50) , 
		  "BBALA" DECIMAL(20,6) , 
		  "BBALA_FLAG" INTEGER , 
		  "DRAMNT" DECIMAL(20,6) , 
		  "CRAMT" DECIMAL(20,6) , 
		  "ENDBALA" DECIMAL(20,6) , 
		  "ENDBALA_FLAG" INTEGER , 
		  "SPARE1" VARCHAR(25) , 
		  "SPARE2" VARCHAR(25) , 
		  "SPARE3" VARCHAR(25) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_SUBJECT_BALANCE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SUBJECT_BALANCE"

ALTER TABLE "YKT_CUR "."T_TIF_SUBJECT_BALANCE" 
	ADD PRIMARY KEY
		("TXDATE",
		 "SUBNO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SUBSIDY"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SUBSIDY"  (
		  "SUBSIDY_NO" VARCHAR(20) NOT NULL , 
		  "CUST_NO" INTEGER NOT NULL , 
		  "BATCH_NO" VARCHAR(14) , 
		  "SEQNO" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "CARD_NO" INTEGER , 
		  "SUMMARY" VARCHAR(60) , 
		  "EXPIRE_DATE" VARCHAR(8) , 
		  "BILL_TYPE" INTEGER , 
		  "BILL_NO" VARCHAR(20) , 
		  "AMOUNT" DOUBLE , 
		  "SUBSIDYTYPE" CHAR(1) , 
		  "TX_DATE" CHAR(8) , 
		  "TX_TIME" CHAR(6) , 
		  "GET_DATE" CHAR(8) , 
		  "GET_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "BROKER_ID" VARCHAR(18) , 
		  "BROKER_NAME" VARCHAR(60) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SUBSIDY"

ALTER TABLE "YKT_CUR "."T_TIF_SUBSIDY" 
	ADD CONSTRAINT "SQL060405130724200" PRIMARY KEY
		("SUBSIDY_NO",
		 "CUST_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SUBSIDYTMP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SUBSIDYTMP"  (
		  "SUBSIDY_NO" VARCHAR(20) NOT NULL , 
		  "CUST_NO" INTEGER NOT NULL , 
		  "BATCH_NO" VARCHAR(14) , 
		  "SEQNO" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "CARD_NO" INTEGER , 
		  "SUMMARY" VARCHAR(60) , 
		  "EXPIRE_DATE" VARCHAR(8) , 
		  "BILL_TYPE" INTEGER , 
		  "BILL_NO" VARCHAR(20) , 
		  "AMOUNT" DOUBLE , 
		  "SUBSIDYTYPE" CHAR(1) , 
		  "TX_DATE" CHAR(8) , 
		  "TX_TIME" CHAR(6) , 
		  "GET_DATE" CHAR(8) , 
		  "GET_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "BROKER_ID" VARCHAR(18) , 
		  "BROKER_NAME" VARCHAR(60) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_TIF_SUBSIDYTMP"."CUST_NO" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SUBSIDYTMP"

ALTER TABLE "YKT_CUR "."T_TIF_SUBSIDYTMP" 
	ADD CONSTRAINT "SQL051207161123610" PRIMARY KEY
		("SUBSIDY_NO",
		 "CUST_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_SUBSIDY_WAITING"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_SUBSIDY_WAITING"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "STATE" INTEGER NOT NULL , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "OUTORIN" INTEGER , 
		  "FEE" DECIMAL(9,2) , 
		  "REG_DATE" VARCHAR(10) , 
		  "REG_TIME" VARCHAR(8) , 
		  "OPER_CODE" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_SUBSIDY_WAITING"

ALTER TABLE "YKT_CUR "."T_TIF_SUBSIDY_WAITING" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_TRADELOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_TRADELOG"  (
		  "SERINO" INTEGER NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "ACT_ID" CHAR(16) NOT NULL , 
		  "SUBNO" VARCHAR(20) , 
		  "OTHER_ACTID" CHAR(16) , 
		  "OTHER_SUBNO" VARCHAR(20) , 
		  "OUTORIN" INTEGER , 
		  "OP_FEE" DECIMAL(15,6) , 
		  "NEW_FEE" DECIMAL(15,6) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) , 
		  "WARRANT_TYPE" INTEGER , 
		  "WARRANT_NO" VARCHAR(20) , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "ANNEX" INTEGER , 
		  "RECORD_OPER" VARCHAR(10) , 
		  "CHECK_OPER" VARCHAR(10) , 
		  "WRITE_OPER" VARCHAR(10) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_TRADELOG"

ALTER TABLE "YKT_CUR "."T_TIF_TRADELOG" 
	ADD PRIMARY KEY
		("SERINO",
		 "ACT_ID",
		 "FEE_TYPE",
		 "SERI_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_TRADESERIAL"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_TRADESERIAL"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "TRADE_COUNT" INTEGER , 
		  "TRADE_FEE" DECIMAL(15,6) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "BOARDFEE" DECIMAL(9,2) , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "CONDITION_ID" INTEGER , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "REVISESERIAL_NO" INTEGER , 
		  "RESERVE_1" VARCHAR(40) , 
		  "RESERVE_2" VARCHAR(40) , 
		  "RESERVE_3" VARCHAR(40) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_TRADESERIAL"

ALTER TABLE "YKT_CUR "."T_TIF_TRADESERIAL" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_TRANSFER_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_TRANSFER_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "TRANSFER_FEE" DECIMAL(9,2) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "B_ACT_ID" VARCHAR(40) NOT NULL , 
		  "SYS_ID" INTEGER NOT NULL , 
		  "CONDITION_ID" INTEGER , 
		  "OPERATOR_ID" VARCHAR(10) , 
		  "ECODE" INTEGER NOT NULL , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_TRANSFER_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_TRANSFER_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_TRANSFER_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_TRANUPDATER_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_TRANUPDATER_TYPE"  (
		  "ID" INTEGER NOT NULL , 
		  "TNAME" VARCHAR(60) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_TRANUPDATER_TYPE"

ALTER TABLE "YKT_CUR "."T_TIF_TRANUPDATER_TYPE" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_TRANUPDATE_REASON"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_TRANUPDATE_REASON"  (
		  "SPONSOR_ID" INTEGER NOT NULL , 
		  "SNAME" VARCHAR(100) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_TRANUPDATE_REASON" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_TIF_TRANUPDATE_REASON"."COMMENTS" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_TIF_TRANUPDATE_REASON"."SNAME" IS '';

COMMENT ON COLUMN "YKT_CUR "."T_TIF_TRANUPDATE_REASON"."SPONSOR_ID" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_TRANUPDATE_REASON"

ALTER TABLE "YKT_CUR "."T_TIF_TRANUPDATE_REASON" 
	ADD PRIMARY KEY
		("SPONSOR_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_WARRANT"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_WARRANT"  (
		  "WARRANT_NO" VARCHAR(20) NOT NULL , 
		  "WTYPE" INTEGER , 
		  "WNAME" VARCHAR(60) , 
		  "CUR_NO" VARCHAR(20) , 
		  "BEGIN_NO" VARCHAR(20) , 
		  "END_NO" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_WARRANT"

ALTER TABLE "YKT_CUR "."T_TIF_WARRANT" 
	ADD PRIMARY KEY
		("WARRANT_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_WATCH_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_WATCH_LOG"  (
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "BENGIN_TIME" VARCHAR(26) , 
		  "END_TIME" VARCHAR(26) , 
		  "IS_FULL" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_WATCH_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_WATCH_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_WATCH_LOG" 
	ADD PRIMARY KEY
		("SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_WATER_COSUME_RECORD"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_WATER_COSUME_RECORD"  (
		  "CONSUME_ID" INTEGER NOT NULL , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "WATER_QUANTITY" DOUBLE , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_WATER_COSUME_RECORD"

ALTER TABLE "YKT_CUR "."T_TIF_WATER_COSUME_RECORD" 
	ADD PRIMARY KEY
		("CONSUME_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_WHITE_SHEET"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_WHITE_SHEET"  (
		  "ID" INTEGER NOT NULL , 
		  "CARD_ID" INTEGER , 
		  "ACCOUNT_ID" INTEGER NOT NULL , 
		  "CUSTOMER_ID" INTEGER NOT NULL , 
		  "CURRENT_STATE" INTEGER NOT NULL , 
		  "SUBSIDY_COUNT" INTEGER , 
		  "SUBSIDY_FEE" DOUBLE , 
		  "IS_SUBSIDY" CHAR(1) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_WHITE_SHEET" IS '¼';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_WHITE_SHEET"

ALTER TABLE "YKT_CUR "."T_TIF_WHITE_SHEET" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_WHITE_SHEET_LOG"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_WHITE_SHEET_LOG"  (
		  "LOG_ID" INTEGER NOT NULL , 
		  "RECORD_ID" INTEGER , 
		  "VERSION" INTEGER , 
		  "CARD_ID" INTEGER , 
		  "ACCOUNT_ID" CHAR(16) NOT NULL , 
		  "CUSTOMER_ID" INTEGER NOT NULL , 
		  "CURRENT_STATE" INTEGER NOT NULL , 
		  "SUBSIDY_COUNT" INTEGER , 
		  "IS_SUBSIDY" CHAR(1) , 
		  "UPDATE_TIME" VARCHAR(26) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_WHITE_SHEET_LOG" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_WHITE_SHEET_LOG"

ALTER TABLE "YKT_CUR "."T_TIF_WHITE_SHEET_LOG" 
	ADD PRIMARY KEY
		("LOG_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_YEAR_BACK_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_YEAR_BACK_SUM"  (
		  "ID" BIGINT NOT NULL , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_FEE" DOUBLE , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_FEE" DOUBLE , 
		  "QUANCUN_COUNT" BIGINT , 
		  "QUANCUN_FEE" DOUBLE , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "AUTO_TRAN_FEE" DOUBLE , 
		  "OTHER_TRAN_COUNT" BIGINT , 
		  "OTHER_TRAN_FEE" DOUBLE , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_YEAR_BACK_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_YEAR_BACK_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_YEAR_BACK_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_YEAR_MONITOR_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_YEAR_MONITOR_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER , 
		  "ERROR_ID" INTEGER , 
		  "ERROR_COUNT" BIGINT , 
		  "BEGIN_TIME" TIMESTAMP , 
		  "END_TIME" TIMESTAMP , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_YEAR_MONITOR_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_YEAR_MONITOR_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_YEAR_MONITOR_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_YEAR_OPERATE_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_YEAR_OPERATE_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "CUSTOMER_LOGIN" BIGINT , 
		  "CUSTOMER_LOGOFF" BIGINT , 
		  "CARD_LOGIN" BIGINT , 
		  "CARD_LOGOFF" BIGINT , 
		  "CARD_LOSS" BIGINT , 
		  "CARD_RESUME" BIGINT , 
		  "CARD_CHANGE" BIGINT , 
		  "ACCOUNT_LOGIN" BIGINT , 
		  "ACCOUNT_LOGOFF" BIGINT , 
		  "ACCOUNT_UNFREEZE" BIGINT , 
		  "ACCOUNT_FREEZE" BIGINT , 
		  "CASH_DEPOSIT" BIGINT , 
		  "SUMDATE" DATE , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_YEAR_OPERATE_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_YEAR_OPERATE_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_YEAR_SUBSYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_YEAR_SUBSYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "SUM_RECORD_COUNT" INTEGER , 
		  "CONSUME_COUNT" INTEGER , 
		  "SUM_FEE" DECIMAL(15,2) , 
		  "AUTHEN_COUNT" INTEGER , 
		  "OTHER_COUNT" INTEGER , 
		  "DEPOSIT_COUNT" INTEGER , 
		  "NOW_TIME" TIMESTAMP , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_TIF_YEAR_SUBSYSTEM_SUM" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_YEAR_SUBSYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_YEAR_SUBSYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_YEAR_SYSTEM_SUM"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_YEAR_SYSTEM_SUM"  (
		  "ID" INTEGER NOT NULL , 
		  "ACCOUNT_COUNT" BIGINT , 
		  "NEW_ACCOUNT_COUNT" BIGINT , 
		  "LOGOFF_ACCOUNT_COUNT" BIGINT , 
		  "SUM_CUSTOMER" BIGINT , 
		  "NEW_CUSTOMER_COUNT" BIGINT , 
		  "LOGOFF_CUSTOMER_COUNT" BIGINT , 
		  "SUM_CARD" BIGINT , 
		  "NEW_CARD__COUNT" BIGINT , 
		  "LOGOFF_CARD_COUNT" BIGINT , 
		  "SUM_BALANCE" DECIMAL(15,2) , 
		  "SUM_IN_FEE" DECIMAL(15,2) , 
		  "SUM_OUT_FEE" DECIMAL(15,2) , 
		  "SUM_TAKING_FEE" DECIMAL(15,2) , 
		  "SUM_DEPOSITCASH_FEE" DECIMAL(15,2) , 
		  "SUMFEE_FROM_BACK" DECIMAL(15,2) , 
		  "SUMFEE_TO_BACK" DECIMAL(15,2) , 
		  "SUM_MANAGE_FEE" DECIMAL(15,2) , 
		  "SUM_DUTY_FEE" DECIMAL(15,2) , 
		  "QUANCUN_COUNT" BIGINT , 
		  "AUTO_TRAN_COUNT" BIGINT , 
		  "INSIDE_TRAN_COUNT" BIGINT , 
		  "BTOS_TRAN_COUNT" BIGINT , 
		  "STOB_TRAN_COUNT" BIGINT , 
		  "SUBSIDY_COUNT" BIGINT , 
		  "SELFH_DEPOSIT_COUNT" BIGINT , 
		  "CASH_DEPOSIT_COUNT" BIGINT , 
		  "COSUME_LOG_COUNT" BIGINT , 
		  "AUTHEN_LOG_COUNT" BIGINT , 
		  "OTHER_LOG_COUNT" BIGINT , 
		  "SUMDATE" DATE , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_YEAR_SYSTEM_SUM"

ALTER TABLE "YKT_CUR "."T_TIF_YEAR_SYSTEM_SUM" 
	ADD PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_PIF_DEVICE"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_PIF_DEVICE"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "DEVICE_NAME" VARCHAR(150) , 
		  "DEV999_ID" VARCHAR(8) , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "DEV999_NO" INTEGER , 
		  "DEVTYPE" VARCHAR(4) , 
		  "DEVVERSION" VARCHAR(8) , 
		  "CARDSTR" VARCHAR(2) , 
		  "CARDTYPE" VARCHAR(64) , 
		  "PORTCOUNT" INTEGER , 
		  "FDEV_ID" INTEGER , 
		  "PORTNO" INTEGER , 
		  "STATE_ID" INTEGER , 
		  "JOINMODE" INTEGER , 
		  "COMADD" VARCHAR(16) , 
		  "PORT" VARCHAR(6) , 
		  "BAUDRATE" INTEGER , 
		  "COMTYPE" INTEGER , 
		  "BSHEETVDATE" VARCHAR(12) , 
		  "BSHEETVER" VARCHAR(12) , 
		  "LASTTRASERNO" INTEGER , 
		  "LASTTRADATE" VARCHAR(20) , 
		  "LASTSHUTSERNO" INTEGER , 
		  "LASTSHUTDATE" VARCHAR(20) , 
		  "SYSPWD" VARCHAR(6) , 
		  "ADMPWD" VARCHAR(6) , 
		  "PWDONOFF" INTEGER , 
		  "PUSERNO" VARCHAR(3) , 
		  "CARDSET" VARCHAR(64) , 
		  "FUNONOFF" VARCHAR(2) , 
		  "CARDUSENUM" INTEGER , 
		  "MAXDEPOSIT" INTEGER , 
		  "MINDEPOSIT" INTEGER , 
		  "RATION" INTEGER , 
		  "MAXTRADE" INTEGER , 
		  "SHUTTIMES" VARCHAR(64) , 
		  "CARD65PWD" VARCHAR(64) , 
		  "AUTHPWD" VARCHAR(64) , 
		  "FTFLAG" INTEGER , 
		  "FEETYPE" INTEGER , 
		  "PHYTYPE" INTEGER , 
		  "WEB_LEVEL" INTEGER , 
		  "SUBSYSTEM_ID" INTEGER , 
		  "AREA" INTEGER , 
		  "INIT_KEY" VARCHAR(32) , 
		  "MANAGER" VARCHAR(20) , 
		  "TEL" VARCHAR(20) , 
		  "ADDRESS" VARCHAR(150) , 
		  "OPERATE_TIME" VARCHAR(26) , 
		  "COMMENTS" VARCHAR(150) , 
		  "IS_FEE_CODE" INTEGER NOT NULL WITH DEFAULT 0 , 
		  "MODE_CODE" INTEGER , 
		  "OPEN_TIME1" INTEGER , 
		  "OPEN_TIME2" INTEGER , 
		  "IS_ALLEYWAY" CHAR(1) , 
		  "IS_SAVE_DATA" CHAR(1) , 
		  "IS_LCD_DISPLAY" CHAR(1) , 
		  "DOOR_LST_VER" CHAR(12) , 
		  "DEV_USAGE" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CUR "."T_PIF_DEVICE" IS '';


-- DDL Statements for primary key on Table "YKT_CUR "."T_PIF_DEVICE"

ALTER TABLE "YKT_CUR "."T_PIF_DEVICE" 
	ADD PRIMARY KEY
		("DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TIF_MESLIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TIF_MESLIST"  (
		  "MESID" INTEGER NOT NULL GENERATED ALWAYS AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +1000000000  
		    CYCLE  
		    CACHE 50  
		    NO ORDER ) , 
		  "FUNID" INTEGER NOT NULL , 
		  "STATEID" INTEGER NOT NULL , 
		  "SENDCOUNT" INTEGER , 
		  "LEVEL" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVID" INTEGER , 
		  "INDT" VARCHAR(26) , 
		  "STARTDT" VARCHAR(26) , 
		  "ENDDT" VARCHAR(26) , 
		  "ECODE" INTEGER , 
		  "EMSG" VARCHAR(100) , 
		  "INCONTENT" VARCHAR(800) , 
		  "OUTCONTENT" VARCHAR(800) , 
		  "PFUNID" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "MAX_SEND_CNT" INTEGER , 
		  "DEL_FLAG" CHAR(1) )   
		 IN "USERSPACE1" ; 
-- DDL Statements for indexes on Table "YKT_CUR "."T_TIF_MESLIST"

CREATE INDEX "YKT_CUR "."MESLIST_ECODE" ON "YKT_CUR "."T_TIF_MESLIST" 
		("ECODE" ASC)
		PCTFREE 10 ;


-- DDL Statements for primary key on Table "YKT_CUR "."T_TIF_MESLIST"

ALTER TABLE "YKT_CUR "."T_TIF_MESLIST" 
	ADD CONSTRAINT "SQL051027184405430" PRIMARY KEY
		("MESID");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_WATER_INFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_WATER_INFO"  (
		  "CUST_NO" INTEGER NOT NULL , 
		  "WATER_METER_NO" INTEGER , 
		  "BIND_DATE" CHAR(8) , 
		  "BIND_TIME" CHAR(6) , 
		  "CARD_PHYID" CHAR(8) )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_WATER_INFO"."BIND_DATE" IS '绑定日期';

COMMENT ON COLUMN "YKT_CUR "."T_WATER_INFO"."BIND_TIME" IS '绑定时间';

COMMENT ON COLUMN "YKT_CUR "."T_WATER_INFO"."CUST_NO" IS '客户号';

COMMENT ON COLUMN "YKT_CUR "."T_WATER_INFO"."WATER_METER_NO" IS '水表号';


-- DDL Statements for primary key on Table "YKT_CUR "."T_WATER_INFO"

ALTER TABLE "YKT_CUR "."T_WATER_INFO" 
	ADD PRIMARY KEY
		("CUST_NO");



------------------------------------------------
-- DDL Statements for table "YKT_CUR "."T_TRADECODE_SHOP"
------------------------------------------------
 
 CREATE TABLE "YKT_CUR "."T_TRADECODE_SHOP"  (
		  "TRADE_CODE" INTEGER NOT NULL , 
		  "SHOP_ID" INTEGER )   
		 IN "USERSPACE1" ; 
COMMENT ON COLUMN "YKT_CUR "."T_TRADECODE_SHOP"."SHOP_ID" IS '商户ID';

COMMENT ON COLUMN "YKT_CUR "."T_TRADECODE_SHOP"."TRADE_CODE" IS '交易代码';


-- DDL Statements for primary key on Table "YKT_CUR "."T_TRADECODE_SHOP"

ALTER TABLE "YKT_CUR "."T_TRADECODE_SHOP" 
	ADD PRIMARY KEY
		("TRADE_CODE");







----------------------------

-- DDL Statements for Views

----------------------------
CREATE VIEW YKT_CUR.V_BLKLST
(CARD_ID,
IS_AD,
VOLUME,
PHYSICAL_NO,
STUEMP_NO
)
AS  Select a.card_id,a.is_ad,a.volume,c.PHYSICAL_NO,d.stuemp_no
from YKT_CUR.T_TIF_BLACK_SHEET a,(
select card_id,max(volume) as max_volume
from ykt_cur.T_TIF_BLACK_SHEET
where (is_ad = 0
or is_ad = 1)
group by card_id) b,ykt_cur.t_pif_card c,ykt_cur.t_cif_customer d
where a.card_id=b.card_id
and a.volume=b.max_volume
and a.card_id=c.card_id
and c.COSUMER_ID=d.cut_id;

COMMENT ON TABLE "YKT_CUR "."V_BLKLST" IS '';

CREATE VIEW YKT_CUR.V_CARDLST
(CARD_ID,
IS_AD,
VOLUME,
PHYSICAL_NO,
STUEMP_NO
)
AS  Select a.card_id,a.is_ad,a.volume,c.PHYSICAL_NO,d.stuemp_no
from YKT_CUR.T_TIF_BLACK_SHEET a,(
select card_id,max(volume) as max_volume ,(
case is_ad
when 9
then 1
else 2
end) as ftype
from ykt_cur.T_TIF_BLACK_SHEET
group by card_id,(
case is_ad
when 9
then 1
else 2
end) ) b,ykt_cur.t_pif_card c,ykt_cur.t_cif_customer d
where a.card_id=b.card_id
and a.volume=b.max_volume
and a.card_id=c.card_id
and c.COSUMER_ID=d.cut_id;

COMMENT ON TABLE "YKT_CUR "."V_CARDLST" IS '';

CREATE VIEW YKT_CUR.V_CIF_SHOP_TMP
(SHOP_ID,
CUT_ID,
DEPT_ID,
SHOP_NAME,
SHOP_TYPE,
IS_INDEP,
IS_LEAF,
SHOP_STATE,
SHOP_MANAGER,
MAN,
SEX,
NATION,
MAN_ID,
TEL,
ADDRESS,
IS_GETFEE,
RATIO,
MANAGER_TYPE,
DUTY_TYPE,
REG_TIME,
COMMENTS,
FAT_SHOP_NAME,
AREA,
CLASSDEPT_NO
)
AS  select a.shop_id, a.cut_id, a.dept_id, a.shop_name, a.shop_type,a.is_indep, 
a.is_leaf, a.shop_state, a.shop_manager, a.man, a.sex,a.nation, a.man_id, 
a.tel, a.address, a.is_getfee, a.ratio, a.manager_type,a.duty_type, 
a.reg_time,a.comments,a.fat_shop_name,b.area,b.classdept_no
from (
select c.shop_id, c.cut_id, c.dept_id, c.shop_name, c.shop_type,c.is_indep
, c.is_leaf, c.shop_state, c.shop_manager, c.man, c.sex,c.nation, 
c.man_id, c.tel, c.address, c.is_getfee, c.ratio, c.manager_type, 
c.duty_type, c.reg_time,c.comments,d.shop_name as fat_shop_name
from ykt_cur.t_cif_shop c
left outer join ykt_cur.t_cif_shop d
on c.dept_id=d.shop_id ) a, (
select e.shop_id,f.area,f.classdept_no
from ykt_cur.t_cif_shop e
left outer join ykt_cur.t_cif_customer f
on e.cut_id=f.cut_id ) b
where a.shop_id=b.shop_id;

COMMENT ON TABLE "YKT_CUR "."V_CIF_SHOP_TMP" IS 'V_cif_shop_tmp';

CREATE VIEW YKT_CUR.V_CUT_CARD_INFO
(CARD_ID,
PHYSICAL_NO,
STUEMP_NO,
CLASSDEPT_NO,
S_CODE,
SEX,
CUT_TYPE,
FEE_TYPE,
END_TIME,
CUT_STATE,
VOLUME,
FLAG,
CUT_NAME
)
AS  select cd.card_id,cd.physical_no,cut.stuemp_no,cut.classdept_no ,cut.s_code, 
cut.sex,cut.cut_type,cut.fee_type,cd.end_time,cut.cut_state,ci.volume, 
ci.flag,cut.cut_name
from YKT_CUR.T_PIF_CARD as cd,YKT_CUR.T_CIF_CUSTOMER as cut , 
ykt_cur.t_tif_cut_info_update as ci
where cd.cosumer_id=cut.cut_id
and cd.card_id=ci.card_id;

CREATE VIEW YKT_CUR.V_TIF_ACTTYPE_TRADE
AS  select S.subno,S.subname,S.subtype,S.direct,S.kind,S.father,S.level,S.endflag,
T.Seri_type,T.Fee_type,T.OutOrIn,T.OpCount,T.Fee_Change
from YKT_CUR.T_TIF_subject S
left outer join (
select T.subno,T.Seri_type,T.Fee_type,T.OutOrIn,count(T.Op_Fee) as 
OpCount,SUM(T.Op_Fee) as Fee_Change
from YKT_CUR.T_TIF_TradeLog T
group by T.subno,T.Seri_type,T.Fee_type,T.OutOrIn ) T
on S.subno = T.subno;

COMMENT ON TABLE "YKT_CUR "."V_TIF_ACTTYPE_TRADE" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_CARDDB_NOBALANCE
(ACCOUNT_ID,
CUSTOMER_ID,
CARD_ID,
CUT_NAME,
STUEMP_NO,
CARD_TYPE,
CLASSDEPT_NO,
DB_BALA,
CARD_BALA,
NOBALA_NUM,
DIFF_BALA
)
AS  select a.account_id, a.customer_id, a.card_id, a.cut_name, a.stuemp_no, 
a.card_type, b.classdept_no, a.cur_freebala db_bala, a.card_balance 
card_bala, a.nobala_num, (a.cur_freebala-a.card_balance) diff_bala
from ykt_cur.T_AIF_Account a,ykt_cur.T_CIF_Customer b
where a.customer_id=b.cut_id
and a.cur_freebala<>a.card_balance
and a.card_id<>0;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_CARDDB_NOBALANCE" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_ERRACC
AS  select a.account_id, a.cut_name, a.stuemp_no, a.card_type, a.last_bala, 
a.cur_bala, b.sum_trade
from ykt_cur.T_AIF_Account a
left outer join (
select act_id,SUM(sum_trade) sum_trade
from (
select t1.act_id,((
case
when t2.direct=1
then 1
else -1
end)*((
case
when t1.outorin=1
then 1
else -1
end)*t1.op_fee)) sum_trade
from ykt_cur.T_TIF_TradeLog t1,ykt_cur.T_TIF_subject t2
where t1.subno=t2.subno) t
group by act_id) b
on a.account_id=b.act_id
where a.card_type=1
and (a.cur_bala-a.last_bala)<>b.sum_trade;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_ERRACC" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_OPER
(SERIAL_TYPE,
TRADE_COUNT,
MAINDEVICE_ID,
DEVICE_ID,
OPER_CODE,
TRADE_AMT,
ACC_ADD_AMT,
SHP_ADD_AMT,
DEP_ADD_AMT,
EARN_ADD_AMT,
BANK_ADD_AMT,
DEPOSIT_AMT,
IN_AMT,
COST_AMT,
CASH_AMT,
CHECK_AMT,
OUTLAY_AMT,
DOWN_SUBSIDY_AMT,
UP_SUBSIDY_AMT
)
AS  select a.serial_type as serial_type,a.trade_count as trade_count, 
a.maindevice_id as maindevice_id,a.device_id as device_id, a.oper_code as 
oper_code,b.trade_amt as trade_amt, b.acc_add_amt as acc_add_amt, 
b.shp_add_amt as shp_add_amt,b.dep_add_amt as dep_add_amt, b.earn_add_amt 
as earn_add_amt,b.bank_add_amt as bank_add_amt, b.deposit_amt as 
deposit_amt,b.in_amt as in_amt,b.cost_amt as cost_amt, b.cash_amt as 
cash_amt,b.check_amt as check_amt,b.outlay_amt as outlay_amt, 
b.down_subsidy_amt as down_subsidy_amt,b.up_subsidy_amt as up_subsidy_amt
from (
select a.serial_type,count(a.serial_no) trade_count,a.maindevice_id, 
a.device_id,a.oper_code
from ykt_cur.T_TIF_tradeserial a
group by a.serial_type,a.maindevice_id,a.device_id,a.oper_code ) a
full outer join (
select t.seri_type,t.maindevice_id,t.device_id,t.record_oper, sum( 
t.op_count) op_count,sum(t.trade_amt) trade_amt, sum(acc_add_amt) 
acc_add_amt,sum(shp_add_amt) shp_add_amt,sum(dep_add_amt) 
dep_add_amt, sum(earn_add_amt) earn_add_amt,sum(bank_add_amt) 
bank_add_amt, sum(t.deposit_amt) deposit_amt,sum(t.in_amt) in_amt, 
sum(t.cost_amt) cost_amt,sum(t.cash_amt) cash_amt,sum(t.check_amt) 
check_amt,sum(t.outlay_amt) outlay_amt,sum(t.down_subsidy_amt) 
down_subsidy_amt,sum(t.up_subsidy_amt) up_subsidy_amt
from (
select a.seri_type,a.fee_type,a.maindevice_id,a.device_id, 
a.record_oper, count(a.seri_type) op_count,sum(a.op_fee) op_fee,
sum((
case
when (a.fee_type=1
or a.fee_type=7)
and a.outorin=1
then 1
else 0
end)*a.op_fee) trade_amt, sum((
case
when a.subno='201'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) acc_add_amt, sum((
case
when a.subno='202'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) shp_add_amt, sum((
case
when a.subno='503'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) dep_add_amt, sum((
case
when a.subno='504'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) earn_add_amt, sum((
case
when a.subno='102'
then 1
else 0
end)* (
case
when a.outorin=1
then 1
else -1
end)*a.op_fee) bank_add_amt, sum((
case
when a.act_id='2051'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) deposit_amt, sum((
case
when a.act_id='5011'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) in_amt, sum((
case
when a.act_id='5021'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) cost_amt, sum((
case
when a.act_id='1011'
then 1
else 0
end)* (
case
when a.outorin=1
then 1
else -1
end)*a.op_fee) cash_amt, sum((
case
when a.act_id='1041'
then 1
else 0
end)* (
case
when a.outorin=1
then 1
else -1
end)*a.op_fee) check_amt, sum((
case
when a.act_id='1031'
then 1
else 0
end)* (
case
when a.outorin=1
then 1
else -1
end)*a.op_fee) outlay_amt, sum((
case
when a.act_id='1071'
then 1
else 0
end)* (
case
when a.outorin=1
then 1
else -1
end)*a.op_fee) down_subsidy_amt, sum((
case
when a.act_id='2071'
then 1
else 0
end)* (
case
when a.outorin=2
then 1
else -1
end)*a.op_fee) up_subsidy_amt
from ykt_cur.t_tif_tradelog a
group by a.seri_type,a.fee_type,a.maindevice_id,a.device_id,
a.record_oper ) t
group by t.seri_type,t.maindevice_id,t.device_id,t.record_oper ) b
on a.serial_type=b.seri_type
and a.maindevice_id=b.maindevice_id
and a.device_id=b.device_id
and a.oper_code=b.record_oper;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_OPER" IS '';

CREATE VIEW YKT_CUR.V_PIF_DEVICE (NU, DEVICE_ID, DEVICE_NAME, DEV999_ID,
DEVPHY999_ID, DEV999_NO, DEVTYPE, DEVVERSION, CARDSTR, CARDTYPE, PORTCOUNT,
FDEVPHY_ID, PORTNO, STATE_ID, JOINMODE, COMADD, PORT, BAUDRATE, COMTYPE,
BSHEETVDATE, BSHEETVER, LASTTRASERNO, LASTTRADATE, LASTSHUTSERNO, LASTSHUTDATE,
SYSPWD, ADMPWD, PWDONOFF, PUSERNO, CARDSET, FUNONOFF, CARDUSENUM, MAXDEPOSIT,
MINDEPOSIT, RATION, MAXTRADE, SHUTTIMES, CARD65PWD, AUTHPWD, FTFLAG, FEETYPE,
PHYTYPE, WEB_LEVEL, SUBSYSTEM_ID, AREA, INIT_KEY, MANAGER, TEL, ADDRESS,
OPERATE_TIME, COMMENTS ) AS with L(depth,nu,device_id,device_name,dev999_id,devphy999_id,dev999_no,devtype
,devversion,cardstr,cardtype,portcount,fdevphy_id,portno,state_id,joinmode,
comadd,port,baudrate,comtype,bsheetvdate,bsheetver,lasttraserno,lasttradate,
lastshutserno,lastshutdate,syspwd,admpwd,pwdonoff,puserno,cardset,funonoff,
cardusenum,maxdeposit,mindeposit,ration,maxtrade,shuttimes,card65pwd,authpwd
,ftflag,feetype,phytype,web_level,subsystem_id,area,init_key,manager,tel,
address,operate_time,comments) As ( select 1, F.Devphy999_id concat F.comments
concat F.comments concat F.comments ,F.device_id,F.device_name,F.dev999_id,
F.devphy999_id,F.dev999_no,F.devtype,F.devversion,F.cardstr,F.cardtype,
F.portcount,F.FDEV_ID,F.portno,F.state_id,F.joinmode,F.comadd,F.port, F.baudrate,F.comtype,F.bsheetvdate,F.bsheetver,F.lasttraserno,
F.lasttradate,F.lastshutserno,F.lastshutdate,F.syspwd,F.admpwd, F.pwdonoff,F.puserno,F.cardset,F.funonoff,F.cardusenum,F.maxdeposit,
F.mindeposit,F.ration,F.maxtrade,F.shuttimes,F.card65pwd,F.authpwd, F.Ftflag,F.feetype,F.phytype,F.web_level,F.subsystem_id,F.area,
F.init_key,F.manager,F.tel,F.address,F.operate_time,F.comments from YKT_CUR.T_PIF_Device
F where device_id=1 union all select L.depth+1,L.nu concat T.Devphy999_id,T.device_id,T.device_name,
T.dev999_id,T.devphy999_id,T.dev999_no,T.devtype,T.devversion,T.cardstr,
T.cardtype,T.portcount,T.FDEV_ID,T.portno,T.state_id,T.joinmode, T.comadd,T.port,T.baudrate,T.comtype,T.bsheetvdate,T.bsheetver,
T.lasttraserno,T.lasttradate,T.lastshutserno,T.lastshutdate,T.syspwd, T.admpwd,T.pwdonoff,T.puserno,T.cardset,T.funonoff,T.cardusenum,
T.maxdeposit,T.mindeposit,T.ration,T.maxtrade,T.shuttimes,T.card65pwd,
T.authpwd,T.ftflag,T.feetype,T.phytype,T.web_level,T.subsystem_id,T.area
,T.init_key,T.manager,T.tel,T.address,T.operate_time,T.comments from YKT_CUR.T_PIF_Device
T,L where L.device_id = T.FDev_id and L.depth < 32 ) select nu,device_id,device_name,dev999_id,devphy999_id,dev999_no,devtype,
devversion,cardstr,cardtype,portcount,fdevphy_id,portno,state_id, joinmode
,comadd,port,baudrate,comtype,bsheetvdate,bsheetver, lasttraserno , lasttradate,lastshutserno,lastshutdate,syspwd,admpwd,
pwdonoff,puserno, cardset,funonoff,cardusenum,maxdeposit,mindeposit, ration,maxtrade,
shuttimes,card65pwd,authpwd,ftflag,feetype,phytype, web_level, subsystem_id
,area,init_key,manager,tel,address,operate_time, comments from L;

COMMENT ON TABLE "YKT_CUR "."V_PIF_DEVICE" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_OPER_CARD_AMT (SERIAL_TYPE, TRADE_COUNT,
MAINDEVICE_ID, DEVICE_ID, OPER_CODE, BADCARD_STATUS, TRADE_AMT, ACC_ADD_AMT,
SHP_ADD_AMT, DEP_ADD_AMT, EARN_ADD_AMT, BANK_ADD_AMT, DEPOSIT_AMT, IN_AMT,
COST_AMT, CASH_AMT, CHECK_AMT, OUTLAY_AMT, DOWN_SUBSIDY_AMT, UP_SUBSIDY_AMT
) AS  select a.serial_type as serial_type,a.trade_count as trade_count,
 a.maindevice_id as maindevice_id,a.device_id as device_id, a.oper_code
as  oper_code,a.reserve_3,b.trade_amt as trade_amt, b.acc_add_amt as  acc_add_amt,
b.shp_add_amt as shp_add_amt,b.dep_add_amt as dep_add_amt,  b.earn_add_amt
as earn_add_amt,b.bank_add_amt as bank_add_amt,  b.deposit_amt as deposit_amt,b.in_amt
as in_amt,b.cost_amt as cost_amt,  b.cash_amt as cash_amt,b.check_amt as
check_amt,b.outlay_amt as outlay_amt , b.down_subsidy_amt as down_subsidy_amt,b.up_subsidy_amt
as  up_subsidy_amt from ( select a.serial_type,count(a.serial_no) trade_count,a.maindevice_id,
 a.device_id,a.oper_code,a.reserve_3 from ykt_cur.T_TIF_tradeserial a group
by a.serial_type,a.maindevice_id,a.device_id,a.oper_code, a.reserve_3 )
a full outer join ( select t.seri_type,t.maindevice_id,t.device_id,t.record_oper,
sum(  t.op_count) op_count,sum(t.trade_amt) trade_amt, sum(acc_add_amt)
 acc_add_amt,sum(shp_add_amt) shp_add_amt,sum(dep_add_amt)  dep_add_amt,
sum(earn_add_amt) earn_add_amt,sum(bank_add_amt)  bank_add_amt, sum(t.deposit_amt)
deposit_amt,sum(t.in_amt) in_amt,  sum(t.cost_amt) cost_amt,sum(t.cash_amt)
cash_amt,sum(t.check_amt)  check_amt,sum(t.outlay_amt) outlay_amt,sum(t.down_subsidy_amt)
 down_subsidy_amt,sum(t.up_subsidy_amt) up_subsidy_amt from ( select a.seri_type,a.fee_type,a.maindevice_id,a.device_id,
 a.record_oper, a.reserve_3,count(a.seri_type) op_count,sum( a.op_fee)
op_fee, sum(( case when (a.fee_type=1 or a.fee_type=7) and a.outorin=1
then 1 else 0 end)*a.op_fee) trade_amt, sum(( case when a.subno='201' then
1 else 0 end)* ( case when a.outorin=2 then 1 else -1 end)*a.op_fee) acc_add_amt,
sum(( case when a.subno='202' then 1 else 0 end)* ( case when a.outorin=2
then 1 else -1 end)*a.op_fee) shp_add_amt, sum(( case when a.subno='503'
then 1 else 0 end)* ( case when a.outorin=2 then 1 else -1 end)*a.op_fee)
dep_add_amt, sum(( case when a.subno='504' then 1 else 0 end)* ( case when
a.outorin=2 then 1 else -1 end)*a.op_fee) earn_add_amt, sum(( case when
a.subno='102' then 1 else 0 end)* ( case when a.outorin=1 then 1 else -1
end)*a.op_fee) bank_add_amt, sum(( case when a.act_id='2051' then 1 else
0 end)* ( case when a.outorin=2 then 1 else -1 end)*a.op_fee) deposit_amt,
sum(( case when a.act_id='5011' then 1 else 0 end)* ( case when a.outorin=2
then 1 else -1 end)*a.op_fee) in_amt, sum(( case when a.act_id='5021' then
1 else 0 end)* ( case when a.outorin=2 then 1 else -1 end)*a.op_fee) cost_amt,
sum(( case when a.act_id='1011' then 1 else 0 end)* ( case when a.outorin=1
then 1 else -1 end)*a.op_fee) cash_amt, sum(( case when a.act_id='1041'
then 1 else 0 end)* ( case when a.outorin=1 then 1 else -1 end)*a.op_fee)
check_amt, sum(( case when a.act_id='1031' then 1 else 0 end)* ( case when
a.outorin=1 then 1 else -1 end)*a.op_fee) outlay_amt, sum(( case when a.act_id='1071'
then 1 else 0 end)* ( case when a.outorin=1 then 1 else -1 end)*a.op_fee)
down_subsidy_amt, sum(( case when a.act_id='2071' then 1 else 0 end)* (
case when a.outorin=2 then 1 else -1 end)*a.op_fee) up_subsidy_amt from
ykt_cur.t_tif_tradelog a group by a.seri_type,a.fee_type,a.maindevice_id,a.device_id,
 a.record_oper,a.reserve_3 ) t group by t.seri_type,t.maindevice_id,t.device_id,t.record_oper,
t.reserve_3 ) b on a.serial_type=b.seri_type and a.maindevice_id=b.maindevice_id
and a.device_id=b.device_id and a.oper_code=b.record_oper;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_OPER_CARD_AMT" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_TOTALACC AS  select sum(( case when direct=1
then 1 else -1 end)*cur_bala) as total from ( select a.cur_bala,b.direct
from ykt_cur.T_AIF_account a,ykt_cur.T_TIF_subject b where a.subno=b.subno)
c;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_TOTALACC" IS '';

CREATE VIEW YKT_CUR.V_TIF_SERTYPE_TRADE AS  select T.Seri_type,T.Fee_type,T.OutOrIn,count(T.Op_Fee)
as OpCount,SUM(  T.Op_Fee) as Fee_Change from YKT_CUR.T_TIF_TradeLog T
group by T.Seri_type,T.Fee_type,T.OutOrIn;

COMMENT ON TABLE "YKT_CUR "."V_TIF_SERTYPE_TRADE" IS '';

CREATE VIEW YKT_CUR.V_TIF_SHOP_ACT AS  select S.Shop_ID,S.Shop_Name,S.Shop_type,S.Shop_state,S.Dept_ID,S.IS_Indep,
T.Act_id,T.subno,T.Seri_type,T.Fee_type,T.OutOrIn,T.OpCount,T.Fee_Change
from YKT_CUR.T_AIF_Account A,YKT_CUR.T_CIF_Shop S,( select T.Act_id,max(T.subno)
subno,T.Seri_type,T.Fee_type,T.OutOrIn,count( T.Op_Fee) as OpCount,SUM(T.Op_Fee)
as Fee_Change from YKT_CUR.T_TIF_TradeLog T group by T.Act_id,T.Seri_type,T.Fee_type,T.OutOrIn
) T where S.cut_id >0 and S.Cut_id = A.Customer_id and A.Account_id = T.Act_id;

COMMENT ON TABLE "YKT_CUR "."V_TIF_SHOP_ACT" IS '';

CREATE VIEW YKT_CUR.V_CIF_SHOP (NU, SHOP_ID, CUT_ID, DEPT_ID, SHOP_NAME,
SHOP_TYPE, IS_INDEP, IS_LEAF, SHOP_STATE, SHOP_MANAGER, MAN, SEX, NATION,
MAN_ID, TEL, ADDRESS, IS_GETFEE, RATIO, MANAGER_TYPE, DUTY_TYPE, REG_TIME,
COMMENTS, FAT_SHOP_NAME, AREA, CLASSDEPT_NO ) AS with L(depth,nu,shop_id,cut_id,dept_id,shop_name,shop_type,is_indep,is_leaf,
 shop_state,shop_manager,man,sex,nation,man_id,tel,address,is_getfee,ratio,
 manager_type,duty_type,reg_time,comments,fat_shop_name,area,classdept_no)
As ( select 1,rtrim(char(F.dept_id)) concat rtrim(char(F.shop_id)) concat
 F.comments concat F.comments concat F.comments ,F.shop_id,F.cut_id,  F.dept_id,F.shop_name,F.shop_type,F.is_indep,F.is_leaf,F.shop_state,
 F.shop_manager,F.man,F.sex,F.nation,F.man_id,F.tel,F.address,F.is_getfee
,F.ratio,F.manager_type,F.duty_type,F.reg_time,F.comments,  F.fat_shop_name,F.area,F.classdept_no
from YKT_CUR.V_cif_shop_tmp F where shop_id=1 union all select L.depth+1,L.nu
concat rtrim(char(T.shop_id)),T.shop_id,T.cut_id,  T.dept_id,T.shop_name,T.shop_type,T.is_indep,T.is_leaf,T.shop_state,
 T.shop_manager,T.man,T.sex,T.nation,T.man_id,T.tel,T.address,T.is_getfee
,T.ratio,T.manager_type,T.duty_type,T.reg_time,T.comments,  T.fat_shop_name,T.area,T.classdept_no
from YKT_CUR.V_cif_shop_tmp T,L where L.shop_id = T.dept_id and L.depth
< 100 ) select nu,shop_id,cut_id,dept_id,shop_name,shop_type,is_indep,is_leaf,
 shop_state,shop_manager,man,sex,nation,man_id,tel,address,is_getfee, ratio
,manager_type,duty_type,reg_time,comments,fat_shop_name,area, classdept_no
from L;

COMMENT ON TABLE "YKT_CUR "."V_CIF_SHOP" IS '';

CREATE VIEW YKT_CUR.V_TIF_DEPTSHOP AS with M(depth,Dept_ID,Shop_ID,Seri_type,Fee_type,OutOrIn,OpCount,Fee_Change)
As ( select 1,F.Shop_ID,F.Shop_ID,F.Seri_type,F.Fee_type,F.OutOrIn,F.OpCount,
F.Fee_Change from YKT_CUR.V_TIF_Shop_Act F union all select M.depth+1,T.Dept_ID,M.Shop_ID,M.Seri_type,M.Fee_type,M.OutOrIn,
M.OpCount,M.Fee_Change from YKT_CUR.T_CIF_Shop T,M where M.Dept_ID = T.Shop_ID
and M.depth < 100 ) select Dept_ID,Shop_ID,Seri_type,Fee_type,OutOrIn,OpCount,Fee_Change
from M;

COMMENT ON TABLE "YKT_CUR "."V_TIF_DEPTSHOP" IS '';

CREATE VIEW YKT_CUR.V_TIF_REPORT_ACTIVE (SERIAL_TYPE, TRADE_COUNT, ACC_ADD_NUM,
ACC_ADD_AMT, SHP_ADD_NUM, SHP_ADD_AMT, DEP_ADD_AMT, EARN_ADD_AMT, IN_AMT,
DEPOSIT_AMT, COST_AMT, BANK_ADD_AMT, CASH_ADD_AMT, CHECK_ADD_AMT, OUTLAY_ADD_AMT,
DOWN_SUBSIDY_AMT, UP_SUBSIDY_AMT ) AS  select serial_type,sum(trade_count)
trade_count, sum(( case when serial_type=847101 or serial_type=8471012
or serial_type=8471013 or serial_type=8471014 or serial_type=847116 or
serial_type=847125 or serial_type=847126 or serial_type=8471262 or serial_type=8471263
or serial_type=8471264 then 1 when serial_type=847105 or serial_type=8471042
or serial_type=8471043 then -1 else 0 end)*trade_count) acc_add_num, sum(acc_add_amt)
acc_add_amt, sum(( case when serial_type=843335 then 1 when serial_type=843336
then -1 else 0 end)*trade_count) shp_add_num, sum(shp_add_amt) shp_add_amt,sum(
dep_add_amt) dep_add_amt, sum(earn_add_amt) earn_add_amt,sum(in_amt)  in_amt,
sum( deposit_amt) deposit_amt, sum(cost_amt) cost_amt, sum( bank_add_amt)
bank_add_amt, sum(cash_amt) cash_add_amt,sum(check_amt)  check_add_amt,
sum( outlay_amt) outlay_add_amt,sum(down_subsidy_amt)  down_subsidy_amt,
sum( up_subsidy_amt) up_subsidy_amt from ykt_cur.V_TIF_Report_Oper group
by serial_type;

COMMENT ON TABLE "YKT_CUR "."V_TIF_REPORT_ACTIVE" IS '';

CREATE VIEW YKT_CUR.V_TIF_SHOPDEPTFEE AS  select S.Shop_ID,S.Shop_Name,S.Shop_type,S.Shop_state,S.Dept_ID,S.IS_Indep,
H.Seri_type,H.Fee_type,H.OutOrIn,H.OpCount,H.Fee_Change from YKT_CUR.T_CIF_Shop
S left outer join ( select G.Dept_ID,G.Seri_type,G.Fee_type,G.OutOrIn,sum(G.OpCount)
as  OpCount,sum(G.Fee_Change) AS Fee_Change from YKT_CUR.V_TIF_DeptShop
G group by G.Dept_ID,G.Seri_type,G.Fee_type,G.OutOrIn ) H on H.Dept_ID
= S.Shop_ID where S.Dept_ID is not null;

COMMENT ON TABLE "YKT_CUR "."V_TIF_SHOPDEPTFEE" IS '';



-------------------------------
-- DDL Statements for Triggers
-------------------------------

CREATE TRIGGER YKT_CUR.BLACKLIST NO CASCADE BEFORE INSERT ON YKT_CUR.T_TIF_BLACK_SHEET
REFERENCING NEW AS new_row FOR EACH ROW MODE DB2SQL SET new_row.volume
= ( select substr(d,3,2)||substr(d,6,2)||substr(d,9,2)||substr(t,1,2)||substr(t,
4,2)||substr(t,7,2) from ( SELECT char(CURRENT date,ISO) d ,char(current
time,ISO) t FROM SYSIBM.SYSDUMMY1) a);



COMMIT WORK;



TERMINATE;
-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分23秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_DOOR_TXDTL_Q1"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_DOOR_TXDTL_Q1"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 
-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q1"

CREATE INDEX "YKT_HIS "."INX_DT_Q1_CARD" ON "YKT_HIS "."T_DOOR_TXDTL_Q1" 
		("CARD_NO" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;

-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q1"

CREATE INDEX "YKT_HIS "."INX_DT_Q1_DATE" ON "YKT_HIS "."T_DOOR_TXDTL_Q1" 
		("TX_DATE" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;


-- DDL Statements for primary key on Table "YKT_HIS "."T_DOOR_TXDTL_Q1"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q1" 
	ADD CONSTRAINT "P_KEYDOOR_TXDTL_Q1" PRIMARY KEY
		("DEVICE_ID",
		 "SERIAL_NO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_DOOR_TXDTL_Q2"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_DOOR_TXDTL_Q2"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 
-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q2"

CREATE INDEX "YKT_HIS "."INX_DT_Q2_CARD" ON "YKT_HIS "."T_DOOR_TXDTL_Q2" 
		("CARD_NO" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;

-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q2"

CREATE INDEX "YKT_HIS "."INX_DT_Q2_DATE" ON "YKT_HIS "."T_DOOR_TXDTL_Q2" 
		("TX_DATE" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;


-- DDL Statements for primary key on Table "YKT_HIS "."T_DOOR_TXDTL_Q2"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q2" 
	ADD CONSTRAINT "P_KEY_DT_Q2" PRIMARY KEY
		("DEVICE_ID",
		 "SERIAL_NO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_DOOR_TXDTL_Q3"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_DOOR_TXDTL_Q3"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 
-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q3"

CREATE INDEX "YKT_HIS "."INX_DT_Q3_CARD" ON "YKT_HIS "."T_DOOR_TXDTL_Q3" 
		("CARD_NO" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;

-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q3"

CREATE INDEX "YKT_HIS "."INX_DT_Q3_DATE" ON "YKT_HIS "."T_DOOR_TXDTL_Q3" 
		("TX_DATE" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;


-- DDL Statements for primary key on Table "YKT_HIS "."T_DOOR_TXDTL_Q3"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q3" 
	ADD CONSTRAINT "P_KEY_DT_Q3" PRIMARY KEY
		("DEVICE_ID",
		 "SERIAL_NO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_DOOR_TXDTL_Q4"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_DOOR_TXDTL_Q4"  (
		  "DEVICE_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 
-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q4"

CREATE INDEX "YKT_HIS "."INX_DT_Q4_CARD" ON "YKT_HIS "."T_DOOR_TXDTL_Q4" 
		("CARD_NO" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;

-- DDL Statements for indexes on Table "YKT_HIS "."T_DOOR_TXDTL_Q4"

CREATE INDEX "YKT_HIS "."INX_DT_Q4_DATE" ON "YKT_HIS "."T_DOOR_TXDTL_Q4" 
		("TX_DATE" ASC)
		PCTFREE 10 ALLOW REVERSE SCANS;


-- DDL Statements for primary key on Table "YKT_HIS "."T_DOOR_TXDTL_Q4"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q4" 
	ADD CONSTRAINT "P_KEY_DT_Q4" PRIMARY KEY
		("DEVICE_ID",
		 "SERIAL_NO",
		 "TX_DATE");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_MIF_ALARMOPHIS"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_MIF_ALARMOPHIS"  (
		  "BAK_TIME" VARCHAR(26) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_STATE" INTEGER , 
		  "ALARMTYPE" INTEGER , 
		  "ALARM_TIME" VARCHAR(26) , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_NO2" INTEGER , 
		  "SERIAL_STATE2" INTEGER , 
		  "OP_TIME" VARCHAR(26) , 
		  "ALARMNO" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OPER_NAME" VARCHAR(32) , 
		  "PHONE" VARCHAR(40) , 
		  "MOBILE" VARCHAR(40) , 
		  "ADDR" VARCHAR(80) , 
		  "ZIP" CHAR(6) , 
		  "EMAIL" VARCHAR(60) , 
		  "FINISH_TIME" VARCHAR(26) , 
		  "OPRESULT" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_HIS "."T_MIF_ALARMOPHIS" IS '¼';


-- DDL Statements for primary key on Table "YKT_HIS "."T_MIF_ALARMOPHIS"

ALTER TABLE "YKT_HIS "."T_MIF_ALARMOPHIS" 
	ADD CONSTRAINT "P_KEY_1" PRIMARY KEY
		("BAK_TIME",
		 "SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_TIF_OUTSYS_LOG_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_TIF_OUTSYS_LOG_HIS"  (
		  "BAK_TIME" TIMESTAMP NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" DATE , 
		  "OPERATE_TIME" TIME , 
		  "COLLECT_DATE" DATE , 
		  "COLLECT_TIME" TIME , 
		  "ENTERACT_DATE" DATE , 
		  "ENTERACT_TIME" TIME , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "OPERATE_NO" BIGINT , 
		  "EMPLOYEE_ID" BIGINT , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_HIS "."T_TIF_OUTSYS_LOG_HIS" IS '';


-- DDL Statements for primary key on Table "YKT_HIS "."T_TIF_OUTSYS_LOG_HIS"

ALTER TABLE "YKT_HIS "."T_TIF_OUTSYS_LOG_HIS" 
	ADD PRIMARY KEY
		("BAK_TIME",
		 "SERIAL_NO");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_TIF_SUBSIDY_WAITING_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_TIF_SUBSIDY_WAITING_HIS"  (
		  "BAK_DATE" VARCHAR(10) NOT NULL , 
		  "BAK_TIME" VARCHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER NOT NULL , 
		  "STATE" INTEGER NOT NULL , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "OUTORIN" INTEGER , 
		  "FEE" DECIMAL(9,2) , 
		  "REG_DATE" VARCHAR(10) , 
		  "REG_TIME" VARCHAR(8) , 
		  "OPER_CODE" VARCHAR(10) , 
		  "COMMENTS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_HIS "."T_TIF_SUBSIDY_WAITING_HIS"

ALTER TABLE "YKT_HIS "."T_TIF_SUBSIDY_WAITING_HIS" 
	ADD PRIMARY KEY
		("BAK_DATE",
		 "BAK_TIME");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_TIF_TRADELOG_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_TIF_TRADELOG_HIS"  (
		  "BAK_DATE" VARCHAR(10) NOT NULL , 
		  "BAK_TIME" VARCHAR(8) NOT NULL , 
		  "SERINO" INTEGER NOT NULL , 
		  "SERI_TYPE" INTEGER NOT NULL , 
		  "FEE_TYPE" INTEGER NOT NULL , 
		  "ACT_ID" CHAR(16) NOT NULL , 
		  "SUBNO" VARCHAR(20) , 
		  "OTHER_ACTID" CHAR(16) , 
		  "OTHER_SUBNO" VARCHAR(20) , 
		  "OUTORIN" INTEGER , 
		  "OP_FEE" DECIMAL(15,6) , 
		  "NEW_FEE" DECIMAL(15,6) , 
		  "WARRANT_TYPE" INTEGER , 
		  "WARRANT_NO" VARCHAR(20) , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "ANNEX" INTEGER , 
		  "RECORD_OPER" VARCHAR(10) , 
		  "CHECK_OPER" VARCHAR(10) , 
		  "WRITE_OPER" VARCHAR(10) , 
		  "RESERVE_1" VARCHAR(20) , 
		  "RESERVE_2" VARCHAR(20) , 
		  "RESERVE_3" VARCHAR(20) , 
		  "COMMENTS" VARCHAR(100) , 
		  "CUR_FROZEBALA" DECIMAL(20,6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_HIS "."T_TIF_TRADELOG_HIS"

ALTER TABLE "YKT_HIS "."T_TIF_TRADELOG_HIS" 
	ADD PRIMARY KEY
		("BAK_DATE",
		 "BAK_TIME",
		 "SERINO",
		 "SERI_TYPE",
		 "FEE_TYPE",
		 "ACT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_HIS "."T_TIF_TRADESERIAL_HIS"
------------------------------------------------
 
 CREATE TABLE "YKT_HIS "."T_TIF_TRADESERIAL_HIS"  (
		  "BAK_DATE" VARCHAR(10) NOT NULL , 
		  "BAK_TIME" VARCHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "OTHER_SERI_NO" INTEGER , 
		  "SERIAL_TYPE" INTEGER , 
		  "SERIAL_STATE" INTEGER , 
		  "OPERATE_DATE" VARCHAR(10) , 
		  "OPERATE_TIME" VARCHAR(8) , 
		  "COLLECT_DATE" VARCHAR(10) , 
		  "COLLECT_TIME" VARCHAR(8) , 
		  "ENTERACT_DATE" VARCHAR(10) , 
		  "ENTERACT_TIME" VARCHAR(8) , 
		  "MAINDEVICE_ID" INTEGER , 
		  "DEVICE_ID" INTEGER , 
		  "DEVPHY999_ID" VARCHAR(8) , 
		  "SHOWID" CHAR(10) , 
		  "CARD_ID" INTEGER , 
		  "PURSE_ID" INTEGER , 
		  "TRADE_COUNT" INTEGER , 
		  "TRADE_FEE" DECIMAL(15,6) , 
		  "IN_BALANCE" DECIMAL(9,2) , 
		  "OUT_BALANCE" DECIMAL(9,2) , 
		  "DEPOSIT_FEE" DECIMAL(9,2) , 
		  "IN_FEE" DECIMAL(9,2) , 
		  "COST_FEE" DECIMAL(9,2) , 
		  "BOARDFEE" DECIMAL(9,2) , 
		  "OLDPWD" VARCHAR(32) , 
		  "NEWPWD" VARCHAR(32) , 
		  "CUSTOMER_ID" INTEGER , 
		  "OPER_CODE" VARCHAR(10) , 
		  "OUT_ACCOUNT_ID" CHAR(16) , 
		  "IN_ACCOUNT_ID" CHAR(16) , 
		  "B_ACT_ID" VARCHAR(40) , 
		  "SYS_ID" INTEGER , 
		  "CONDITION_ID" INTEGER , 
		  "IS_ONLINE" CHAR(1) , 
		  "TMARK" INTEGER , 
		  "DEV_AUTH" CHAR(8) , 
		  "COMU_VER" INTEGER , 
		  "RUN_REASON" INTEGER , 
		  "CRC" CHAR(5) , 
		  "ECODE" INTEGER , 
		  "REVISESERIAL_NO" INTEGER , 
		  "RESERVE_1" VARCHAR(40) , 
		  "RESERVE_2" VARCHAR(40) , 
		  "RESERVE_3" VARCHAR(40) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_HIS "."T_TIF_TRADESERIAL_HIS"

ALTER TABLE "YKT_HIS "."T_TIF_TRADESERIAL_HIS" 
	ADD PRIMARY KEY
		("BAK_DATE",
		 "BAK_TIME",
		 "SERIAL_NO");







----------------------------

-- DDL Statements for Views

----------------------------
CREATE VIEW YKT_HIS.V_DOOR_TXDTL_HIS (DEVICE_ID, SERIAL_NO, TX_DATE, TX_TIME,
MODE_CODE, CARD_NO, SHOW_CARD_NO, USE_TYPE, INDUCTOR_NO, WORK_MARK, TX_MARK,
CRC, SYS_ID, COL_DATE, COL_TIME, STATUS, ERR_CODE ) AS  SELECT DEVICE_ID,
SERIAL_NO, TX_DATE , TX_TIME , MODE_CODE , CARD_NO ,  SHOW_CARD_NO , USE_TYPE
, INDUCTOR_NO , WORK_MARK , TX_MARK , CRC , SYS_ID , COL_DATE , COL_TIME
, STATUS , ERR_CODE FROM YKT_HIS.T_DOOR_TXDTL_Q1 UNION ALL SELECT DEVICE_ID,
SERIAL_NO, TX_DATE , TX_TIME , MODE_CODE , CARD_NO ,  SHOW_CARD_NO , USE_TYPE
, INDUCTOR_NO , WORK_MARK , TX_MARK , CRC , SYS_ID , COL_DATE , COL_TIME
, STATUS , ERR_CODE FROM YKT_HIS.T_DOOR_TXDTL_Q2 UNION ALL SELECT DEVICE_ID,
SERIAL_NO, TX_DATE , TX_TIME , MODE_CODE , CARD_NO ,  SHOW_CARD_NO , USE_TYPE
, INDUCTOR_NO , WORK_MARK , TX_MARK , CRC , SYS_ID , COL_DATE , COL_TIME
, STATUS , ERR_CODE FROM YKT_HIS.T_DOOR_TXDTL_Q3 UNION ALL SELECT DEVICE_ID,
SERIAL_NO, TX_DATE , TX_TIME , MODE_CODE , CARD_NO ,  SHOW_CARD_NO , USE_TYPE
, INDUCTOR_NO , WORK_MARK , TX_MARK , CRC , SYS_ID , COL_DATE , COL_TIME
, STATUS , ERR_CODE FROM YKT_HIS.T_DOOR_TXDTL_Q4;



-- DDL Statements for check constraints on Table "YKT_HIS "."T_DOOR_TXDTL_Q1"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q1" 
	ADD CONSTRAINT "CHK_DOOR_TXDTL_Q1" CHECK 
		(SUBSTR(TX_DATE,5,2) >= '01' and SUBSTR(TX_DATE,5,2) <= '03' )
	ENFORCED
	ENABLE QUERY OPTIMIZATION;

-- DDL Statements for check constraints on Table "YKT_HIS "."T_DOOR_TXDTL_Q2"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q2" 
	ADD CONSTRAINT "CHK_DOOR_TXDTL_Q2" CHECK 
		(SUBSTR(TX_DATE,5,2) >= '04' and SUBSTR(TX_DATE,5,2) <= '06' )
	ENFORCED
	ENABLE QUERY OPTIMIZATION;

-- DDL Statements for check constraints on Table "YKT_HIS "."T_DOOR_TXDTL_Q3"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q3" 
	ADD CONSTRAINT "CHK_DOOR_TXDTL_Q3" CHECK 
		(SUBSTR(TX_DATE,5,2) >= '07' and SUBSTR(TX_DATE,5,2) <= '09' )
	ENFORCED
	ENABLE QUERY OPTIMIZATION;

-- DDL Statements for check constraints on Table "YKT_HIS "."T_DOOR_TXDTL_Q4"

ALTER TABLE "YKT_HIS "."T_DOOR_TXDTL_Q4" 
	ADD CONSTRAINT "CHK_DOOR_TXDTL_Q4" CHECK 
		(SUBSTR(TX_DATE,5,2) >= '10' and SUBSTR(TX_DATE,5,2) <= '12' )
	ENFORCED
	ENABLE QUERY OPTIMIZATION;


COMMIT WORK;



TERMINATE;
-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分23秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_CK  "."CARDINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."CARDINFO"  (
		  "CARDINFOID" BIGINT NOT NULL , 
		  "RECORDTIME" DATE , 
		  "CARDNUMBER" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."CARDINFO"

ALTER TABLE "YKT_CK  "."CARDINFO" 
	ADD CONSTRAINT "P_C_KEY" PRIMARY KEY
		("CARDINFOID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."CARDINFO_TEST"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."CARDINFO_TEST"  (
		  "CARDINFOID" BIGINT NOT NULL , 
		  "RECORDTIME" TIMESTAMP , 
		  "CARDNUMBER" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."CARDINFO_TEST"

ALTER TABLE "YKT_CK  "."CARDINFO_TEST" 
	ADD PRIMARY KEY
		("CARDINFOID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."CLERK"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."CLERK"  (
		  "CLERKID" INTEGER NOT NULL , 
		  "DEPARTMENTID" VARCHAR(32) , 
		  "ISSEAT" CHAR(1) , 
		  "ISIRREGULARREST" CHAR(1) , 
		  "PASSWORD" VARCHAR(100) , 
		  "STUNUMBER" VARCHAR(32) , 
		  "CARDNUMBER" VARCHAR(32) , 
		  "CLERKNAME" VARCHAR(100) , 
		  "ISEXTRAWORK" CHAR(1) , 
		  "WORKTIMECONFID" VARCHAR(32) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."CLERK"

ALTER TABLE "YKT_CK  "."CLERK" 
	ADD CONSTRAINT "P_CK_KEY" PRIMARY KEY
		("CLERKID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."COM_DICTIONARY"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."COM_DICTIONARY"  (
		  "DICT_NO" INTEGER NOT NULL , 
		  "DICT_VALUE" VARCHAR(32) NOT NULL , 
		  "DICT_NAME" VARCHAR(100) , 
		  "DICT_CAPTION" VARCHAR(100) , 
		  "DICT_PARENT" VARCHAR(32) , 
		  "DICT_ORDER" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."COM_DICTIONARY"

ALTER TABLE "YKT_CK  "."COM_DICTIONARY" 
	ADD CONSTRAINT "P_KEY_DICT" PRIMARY KEY
		("DICT_NO",
		 "DICT_VALUE");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."DEPARTMENT"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."DEPARTMENT"  (
		  "DEPT_ID" VARCHAR(32) NOT NULL , 
		  "DEPT_NAME" VARCHAR(255) , 
		  "DEPT_PARENTID" VARCHAR(32) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."DEPARTMENT"

ALTER TABLE "YKT_CK  "."DEPARTMENT" 
	ADD CONSTRAINT "SQL060616162834310" PRIMARY KEY
		("DEPT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."DUTYTIME"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."DUTYTIME"  (
		  "TIMEID" VARCHAR(32) NOT NULL , 
		  "ONDUTYTIME" TIMESTAMP , 
		  "OFFDUTYTIME" TIMESTAMP , 
		  "CLERKID" INTEGER , 
		  "DEPARTMENTID" VARCHAR(32) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."DUTYTIME"

ALTER TABLE "YKT_CK  "."DUTYTIME" 
	ADD CONSTRAINT "P_TIME_KEY" PRIMARY KEY
		("TIMEID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."EXTRAWORKINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."EXTRAWORKINFO"  (
		  "EXTRAINFOID" VARCHAR(30) NOT NULL , 
		  "STARTDATE" DATE , 
		  "ENDDATE" DATE )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."EXTRAWORKINFO"

ALTER TABLE "YKT_CK  "."EXTRAWORKINFO" 
	ADD CONSTRAINT "P_EX_KEY" PRIMARY KEY
		("EXTRAINFOID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."EXTRAWORKINFOMAP"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."EXTRAWORKINFOMAP"  (
		  "MAPID" VARCHAR(30) NOT NULL , 
		  "CLERKID" VARCHAR(30) , 
		  "EXTRAINFOID" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."EXTRAWORKINFOMAP"

ALTER TABLE "YKT_CK  "."EXTRAWORKINFOMAP" 
	ADD CONSTRAINT "P_EM_KEY" PRIMARY KEY
		("MAPID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_ACCOUNT_ROLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_ACCOUNT_ROLE"  (
		  "ACCOUNT_ID" VARCHAR(32) NOT NULL , 
		  "ROLE_ID" VARCHAR(32) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_ACCOUNT_ROLE"

ALTER TABLE "YKT_CK  "."ICO_ACCOUNT_ROLE" 
	ADD CONSTRAINT "P_KEY_4" PRIMARY KEY
		("ACCOUNT_ID",
		 "ROLE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_MENU"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_MENU"  (
		  "ID" VARCHAR(32) NOT NULL , 
		  "PID" VARCHAR(32) NOT NULL WITH DEFAULT '0' , 
		  "MENU_NAME" VARCHAR(32) NOT NULL , 
		  "URL" VARCHAR(255) , 
		  "TITLE" VARCHAR(255) , 
		  "TARGET" VARCHAR(255) , 
		  "ICON" VARCHAR(255) , 
		  "ICONOPEN" VARCHAR(255) , 
		  "OPENED" CHAR(1) , 
		  "SORT_FLAG" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_MENU"

ALTER TABLE "YKT_CK  "."ICO_MENU" 
	ADD CONSTRAINT "P_KEY_7" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_PERMISSION"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_PERMISSION"  (
		  "ROLE_ID" VARCHAR(32) NOT NULL , 
		  "RESOURCE_ID" VARCHAR(32) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_PERMISSION"

ALTER TABLE "YKT_CK  "."ICO_PERMISSION" 
	ADD CONSTRAINT "P_KEY_5" PRIMARY KEY
		("ROLE_ID",
		 "RESOURCE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_RESOURCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_RESOURCE"  (
		  "ID" VARCHAR(32) NOT NULL , 
		  "RESOURCE_CODE" VARCHAR(32) NOT NULL , 
		  "RESOURCE_NAME" VARCHAR(255) NOT NULL , 
		  "PARENT_NAME" VARCHAR(255) , 
		  "URL" VARCHAR(255) , 
		  "ACL_CLASS" VARCHAR(255) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_RESOURCE"

ALTER TABLE "YKT_CK  "."ICO_RESOURCE" 
	ADD CONSTRAINT "P_KEY_3" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_ROLE"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_ROLE"  (
		  "ID" VARCHAR(32) NOT NULL , 
		  "ROLE_NAME" VARCHAR(64) NOT NULL , 
		  "ROLE_TYPE" CHAR(1) , 
		  "REMARK" VARCHAR(255) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_ROLE"

ALTER TABLE "YKT_CK  "."ICO_ROLE" 
	ADD CONSTRAINT "P_KEY_2" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."ICO_ROLE_MENU"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."ICO_ROLE_MENU"  (
		  "ROLE_ID" VARCHAR(32) NOT NULL , 
		  "MENU_ID" VARCHAR(32) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."ICO_ROLE_MENU"

ALTER TABLE "YKT_CK  "."ICO_ROLE_MENU" 
	ADD CONSTRAINT "P_KEY_6" PRIMARY KEY
		("ROLE_ID",
		 "MENU_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."IRREGULARREST"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."IRREGULARREST"  (
		  "IRREGULARRESTID" VARCHAR(30) NOT NULL , 
		  "STARTDATE" DATE , 
		  "ENDDATE" DATE )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."IRREGULARREST"

ALTER TABLE "YKT_CK  "."IRREGULARREST" 
	ADD CONSTRAINT "P_IR_KEY" PRIMARY KEY
		("IRREGULARRESTID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."IRREGULARRESTMAP"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."IRREGULARRESTMAP"  (
		  "MAPID" VARCHAR(30) NOT NULL , 
		  "IRREGULARRESTID" VARCHAR(30) , 
		  "CLERKID" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."IRREGULARRESTMAP"

ALTER TABLE "YKT_CK  "."IRREGULARRESTMAP" 
	ADD CONSTRAINT "P_IRM_KEY" PRIMARY KEY
		("MAPID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."LEAVEINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."LEAVEINFO"  (
		  "LEAVEINFOID" VARCHAR(32) NOT NULL , 
		  "DESCRIPTION" VARCHAR(400) , 
		  "STARTDATE" TIMESTAMP , 
		  "ENDDATE" TIMESTAMP , 
		  "RECORDDATE" TIMESTAMP , 
		  "OPERATORID" INTEGER , 
		  "CLERKID" INTEGER , 
		  "DEPARTID" VARCHAR(32) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."LEAVEINFO"

ALTER TABLE "YKT_CK  "."LEAVEINFO" 
	ADD CONSTRAINT "P_LE_KEY" PRIMARY KEY
		("LEAVEINFOID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."MANAGER"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."MANAGER"  (
		  "USERNAME" VARCHAR(20) , 
		  "TRUENAME" VARCHAR(20) , 
		  "PASSWORD" VARCHAR(20) , 
		  "DEPARTMENTID" VARCHAR(30) , 
		  "ROLE" INTEGER , 
		  "MANAGERID" VARCHAR(30) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."MANAGER"

ALTER TABLE "YKT_CK  "."MANAGER" 
	ADD CONSTRAINT "P_M_KEY" PRIMARY KEY
		("MANAGERID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."T_KQ_TXDTL"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."T_KQ_TXDTL"  (
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "DEVPHY_ID" CHAR(8) NOT NULL , 
		  "SERIAL_NO" INTEGER NOT NULL , 
		  "TX_DATE" CHAR(8) NOT NULL , 
		  "TX_TIME" CHAR(6) , 
		  "MODE_CODE" INTEGER , 
		  "CARD_NO" INTEGER , 
		  "SHOW_CARD_NO" CHAR(10) , 
		  "USE_TYPE" INTEGER , 
		  "INDUCTOR_NO" INTEGER , 
		  "WORK_MARK" INTEGER , 
		  "TX_MARK" INTEGER , 
		  "CRC" CHAR(5) , 
		  "SYS_ID" INTEGER , 
		  "COL_DATE" CHAR(8) , 
		  "COL_TIME" CHAR(6) , 
		  "STATUS" CHAR(1) , 
		  "ERR_CODE" INTEGER )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."USR_ACCOUNT"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."USR_ACCOUNT"  (
		  "ID" VARCHAR(32) NOT NULL , 
		  "ACCOUNT_NAME" VARCHAR(64) NOT NULL , 
		  "PASSWORD" VARCHAR(64) , 
		  "ENABLED" CHAR(1) WITH DEFAULT '0' )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."USR_ACCOUNT"

ALTER TABLE "YKT_CK  "."USR_ACCOUNT" 
	ADD CONSTRAINT "P_KEY_1" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."USR_PERSON"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."USR_PERSON"  (
		  "ID" VARCHAR(32) NOT NULL , 
		  "PERSON_CODE" VARCHAR(32) NOT NULL , 
		  "PERSON_NAME" VARCHAR(32) NOT NULL , 
		  "PERSON_TYPE" CHAR(1) , 
		  "SEX" CHAR(1) , 
		  "EMAIL" VARCHAR(50) , 
		  "QQ" VARCHAR(32) , 
		  "PHONE" VARCHAR(32) , 
		  "CARD_ID" VARCHAR(32) , 
		  "CARD" VARCHAR(32) , 
		  "BIRTHDAY" CHAR(8) , 
		  "DEPT" VARCHAR(32) , 
		  "POST" VARCHAR(32) , 
		  "POST_DATE" CHAR(8) , 
		  "WORK_PLACE" VARCHAR(100) , 
		  "OFFICE" VARCHAR(100) , 
		  "OFFICE_PHONE" VARCHAR(32) , 
		  "ADDRESS" VARCHAR(100) , 
		  "POSTALCODE" VARCHAR(10) , 
		  "MSN" VARCHAR(32) , 
		  "POLITY" VARCHAR(32) , 
		  "NATION" VARCHAR(32) , 
		  "WORK_DATE" CHAR(8) , 
		  "TECH_POST" VARCHAR(32) , 
		  "SEMINARY" VARCHAR(32) , 
		  "GRADUCATION" CHAR(8) , 
		  "EDUCATION" VARCHAR(32) , 
		  "DEGREE" VARCHAR(32) , 
		  "REMARK" VARCHAR(100) , 
		  "QUESTION" VARCHAR(100) , 
		  "ANSWER" VARCHAR(100) , 
		  "CREATEDATE" CHAR(8) , 
		  "LASTDATE" CHAR(8) , 
		  "SORT" VARCHAR(32) , 
		  "COLLEGE" VARCHAR(100) , 
		  "DEPARTMENT" VARCHAR(32) , 
		  "GRADE" VARCHAR(32) , 
		  "BRIEF" VARCHAR(200) , 
		  "STRONG_SUIT" VARCHAR(100) , 
		  "CAMPUS" VARCHAR(32) , 
		  "DORM" VARCHAR(32) , 
		  "DORM_PHONE" VARCHAR(32) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."USR_PERSON"

ALTER TABLE "YKT_CK  "."USR_PERSON" 
	ADD CONSTRAINT "P_KEY_8" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."VACATION"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."VACATION"  (
		  "ID" VARCHAR(30) NOT NULL , 
		  "DEPARID" VARCHAR(30) , 
		  "STARTDATE" INTEGER , 
		  "VACTIONALNAME" VARCHAR(30) , 
		  "ENDDATE" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."VACATION"

ALTER TABLE "YKT_CK  "."VACATION" 
	ADD CONSTRAINT "P_VA_ID" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKCONF"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKCONF"  (
		  "WORKCONFID" VARCHAR(32) NOT NULL , 
		  "CONFNAME" VARCHAR(20) , 
		  "PERMITLATETIME" INTEGER , 
		  "PREEARLY" INTEGER , 
		  "ONDUTYADVANCEDTIME" INTEGER , 
		  "OFFDUTYLASTTIME" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKCONF"

ALTER TABLE "YKT_CK  "."WORKCONF" 
	ADD PRIMARY KEY
		("WORKCONFID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKCONFMAP"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKCONFMAP"  (
		  "MAPID" VARCHAR(32) NOT NULL , 
		  "WORKCONFID" VARCHAR(32) , 
		  "CLERKID" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKCONFMAP"

ALTER TABLE "YKT_CK  "."WORKCONFMAP" 
	ADD PRIMARY KEY
		("MAPID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKINFO"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKINFO"  (
		  "WORKINFOID" VARCHAR(32) NOT NULL , 
		  "SERIALID" BIGINT NOT NULL , 
		  "CARDNUMBER" VARCHAR(32) NOT NULL , 
		  "CLERKID" VARCHAR(32) NOT NULL , 
		  "DEPTID" VARCHAR(32) NOT NULL , 
		  "RECORDTIME" TIMESTAMP NOT NULL , 
		  "WORKCONFID" VARCHAR(32) , 
		  "ISSEAT" CHAR(1) , 
		  "DESCRIPTION" VARCHAR(255) , 
		  "LEAVEINFODESC" VARCHAR(255) , 
		  "EXCEPTIONMINS" INTEGER , 
		  "WORKINFOTYPE" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKINFO"

ALTER TABLE "YKT_CK  "."WORKINFO" 
	ADD CONSTRAINT "P_W_KEY" PRIMARY KEY
		("WORKINFOID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKTIMECONF"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKTIMECONF"  (
		  "WORKTIMECONFID" VARCHAR(30) NOT NULL , 
		  "CONSTRAIN" INTEGER , 
		  "T_CONFNAME" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKTIMECONF"

ALTER TABLE "YKT_CK  "."WORKTIMECONF" 
	ADD CONSTRAINT "P_T_KEY" PRIMARY KEY
		("WORKTIMECONFID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKTIMEPARA"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKTIMEPARA"  (
		  "PARAID" VARCHAR(30) NOT NULL , 
		  "ONDUTYTIME" VARCHAR(20) , 
		  "OFFDUTYTIME" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKTIMEPARA"

ALTER TABLE "YKT_CK  "."WORKTIMEPARA" 
	ADD CONSTRAINT "P_PA_KEY" PRIMARY KEY
		("PARAID");



------------------------------------------------
-- DDL Statements for table "YKT_CK  "."WORKTIMEPARAMAP"
------------------------------------------------
 
 CREATE TABLE "YKT_CK  "."WORKTIMEPARAMAP"  (
		  "MAPID" VARCHAR(30) NOT NULL , 
		  "PARAID" VARCHAR(20) , 
		  "WORKTIMECONFID" VARCHAR(30) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CK  "."WORKTIMEPARAMAP"

ALTER TABLE "YKT_CK  "."WORKTIMEPARAMAP" 
	ADD CONSTRAINT "P_MAP_KEY" PRIMARY KEY
		("MAPID");









COMMIT WORK;



TERMINATE;
-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分24秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ABCONTACT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ABCONTACT"  (
		  "CONTACTID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "FIRSTNAME" VARCHAR(100) , 
		  "MIDDLENAME" VARCHAR(100) , 
		  "LASTNAME" VARCHAR(100) , 
		  "NICKNAME" VARCHAR(100) , 
		  "EMAILADDRESS" VARCHAR(100) , 
		  "HOMESTREET" VARCHAR(100) , 
		  "HOMECITY" VARCHAR(100) , 
		  "HOMESTATE" VARCHAR(100) , 
		  "HOMEZIP" VARCHAR(100) , 
		  "HOMECOUNTRY" VARCHAR(100) , 
		  "HOMEPHONE" VARCHAR(100) , 
		  "HOMEFAX" VARCHAR(100) , 
		  "HOMECELL" VARCHAR(100) , 
		  "HOMEPAGER" VARCHAR(100) , 
		  "HOMETOLLFREE" VARCHAR(100) , 
		  "HOMEEMAILADDRESS" VARCHAR(100) , 
		  "BUSINESSCOMPANY" VARCHAR(100) , 
		  "BUSINESSSTREET" VARCHAR(100) , 
		  "BUSINESSCITY" VARCHAR(100) , 
		  "BUSINESSSTATE" VARCHAR(100) , 
		  "BUSINESSZIP" VARCHAR(100) , 
		  "BUSINESSCOUNTRY" VARCHAR(100) , 
		  "BUSINESSPHONE" VARCHAR(100) , 
		  "BUSINESSFAX" VARCHAR(100) , 
		  "BUSINESSCELL" VARCHAR(100) , 
		  "BUSINESSPAGER" VARCHAR(100) , 
		  "BUSINESSTOLLFREE" VARCHAR(100) , 
		  "BUSINESSEMAILADDRESS" VARCHAR(100) , 
		  "EMPLOYEENUMBER" VARCHAR(100) , 
		  "JOBTITLE" VARCHAR(100) , 
		  "JOBCLASS" VARCHAR(100) , 
		  "HOURSOFOPERATION" LONG VARCHAR , 
		  "BIRTHDAY" TIMESTAMP , 
		  "TIMEZONEID" VARCHAR(100) , 
		  "INSTANTMESSENGER" VARCHAR(100) , 
		  "WEBSITE" VARCHAR(100) , 
		  "COMMENTS" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ABCONTACT"

ALTER TABLE "YKT_WEB "."ABCONTACT" 
	ADD CONSTRAINT "SQL051109150931260" PRIMARY KEY
		("CONTACTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ABCONTACTS_ABLISTS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ABCONTACTS_ABLISTS"  (
		  "CONTACTID" VARCHAR(100) NOT NULL , 
		  "LISTID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ABLIST"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ABLIST"  (
		  "LISTID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ABLIST"

ALTER TABLE "YKT_WEB "."ABLIST" 
	ADD CONSTRAINT "SQL051109150931380" PRIMARY KEY
		("LISTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ACCOUNT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ACCOUNT"  (
		  "ACCOUNTID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PARENTACCOUNTID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "LEGALNAME" VARCHAR(100) , 
		  "LEGALID" VARCHAR(100) , 
		  "LEGALTYPE" VARCHAR(100) , 
		  "SICCODE" VARCHAR(100) , 
		  "TICKERSYMBOL" VARCHAR(100) , 
		  "INDUSTRY" VARCHAR(100) , 
		  "TYPE_" VARCHAR(100) , 
		  "SIZE_" VARCHAR(100) , 
		  "WEBSITE" VARCHAR(100) , 
		  "EMAILADDRESS1" VARCHAR(100) , 
		  "EMAILADDRESS2" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ACCOUNT"

ALTER TABLE "YKT_WEB "."ACCOUNT" 
	ADD CONSTRAINT "SQL051109150931500" PRIMARY KEY
		("ACCOUNTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ADDRESS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ADDRESS"  (
		  "ADDRESSID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "CLASSNAME" VARCHAR(100) , 
		  "CLASSPK" VARCHAR(100) , 
		  "DESCRIPTION" VARCHAR(100) , 
		  "STREET1" VARCHAR(100) , 
		  "STREET2" VARCHAR(100) , 
		  "CITY" VARCHAR(100) , 
		  "STATE" VARCHAR(100) , 
		  "ZIP" VARCHAR(100) , 
		  "COUNTRY" VARCHAR(100) , 
		  "PHONE" VARCHAR(100) , 
		  "FAX" VARCHAR(100) , 
		  "CELL" VARCHAR(100) , 
		  "PAGER" VARCHAR(100) , 
		  "TOLLFREE" VARCHAR(100) , 
		  "PRIORITY" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ADDRESS"

ALTER TABLE "YKT_WEB "."ADDRESS" 
	ADD CONSTRAINT "SQL051109150931640" PRIMARY KEY
		("ADDRESSID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ADMINCONFIG"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ADMINCONFIG"  (
		  "CONFIGID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "TYPE_" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "CONFIG" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ADMINCONFIG"

ALTER TABLE "YKT_WEB "."ADMINCONFIG" 
	ADD CONSTRAINT "SQL051109150931790" PRIMARY KEY
		("CONFIGID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BJENTRIES_BJTOPICS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BJENTRIES_BJTOPICS"  (
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "TOPICID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BJENTRIES_BJVERSES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BJENTRIES_BJVERSES"  (
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "VERSEID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BJENTRY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BJENTRY"  (
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "CONTENT" LONG VARCHAR , 
		  "VERSESINPUT" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BJENTRY"

ALTER TABLE "YKT_WEB "."BJENTRY" 
	ADD CONSTRAINT "SQL051109150931980" PRIMARY KEY
		("ENTRYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BJTOPIC"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BJTOPIC"  (
		  "TOPICID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BJTOPIC"

ALTER TABLE "YKT_WEB "."BJTOPIC" 
	ADD CONSTRAINT "SQL051109150932140" PRIMARY KEY
		("TOPICID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BJVERSE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BJVERSE"  (
		  "VERSEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BJVERSE"

ALTER TABLE "YKT_WEB "."BJVERSE" 
	ADD CONSTRAINT "SQL051109150932190" PRIMARY KEY
		("VERSEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSCATEGORY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSCATEGORY"  (
		  "CATEGORYID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSCATEGORY"

ALTER TABLE "YKT_WEB "."BLOGSCATEGORY" 
	ADD CONSTRAINT "SQL051109150932290" PRIMARY KEY
		("CATEGORYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSCOMMENTS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSCOMMENTS"  (
		  "COMMENTSID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "ENTRYID" VARCHAR(100) , 
		  "CONTENT" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSCOMMENTS"

ALTER TABLE "YKT_WEB "."BLOGSCOMMENTS" 
	ADD CONSTRAINT "SQL051109150932450" PRIMARY KEY
		("COMMENTSID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSENTRY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSENTRY"  (
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "CATEGORYID" VARCHAR(100) , 
		  "TITLE" VARCHAR(100) , 
		  "CONTENT" LONG VARCHAR , 
		  "DISPLAYDATE" TIMESTAMP , 
		  "SHARING" CHAR(1) , 
		  "COMMENTABLE" CHAR(1) , 
		  "PROPSCOUNT" INTEGER , 
		  "COMMENTSCOUNT" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSENTRY"

ALTER TABLE "YKT_WEB "."BLOGSENTRY" 
	ADD CONSTRAINT "SQL051109150932580" PRIMARY KEY
		("ENTRYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSLINK"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSLINK"  (
		  "LINKID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "URL" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSLINK"

ALTER TABLE "YKT_WEB "."BLOGSLINK" 
	ADD CONSTRAINT "SQL051109150932750" PRIMARY KEY
		("LINKID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSPROPS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSPROPS"  (
		  "PROPSID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "ENTRYID" VARCHAR(100) , 
		  "QUANTITY" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSPROPS"

ALTER TABLE "YKT_WEB "."BLOGSPROPS" 
	ADD CONSTRAINT "SQL051109150932850" PRIMARY KEY
		("PROPSID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSREFERER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSREFERER"  (
		  "REFERERID" VARCHAR(100) NOT NULL , 
		  "ENTRYID" VARCHAR(100) , 
		  "URL" LONG VARCHAR , 
		  "TYPE_" VARCHAR(100) , 
		  "QUANTITY" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSREFERER"

ALTER TABLE "YKT_WEB "."BLOGSREFERER" 
	ADD CONSTRAINT "SQL051109150932990" PRIMARY KEY
		("REFERERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BLOGSUSER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BLOGSUSER"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "LASTPOSTDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BLOGSUSER"

ALTER TABLE "YKT_WEB "."BLOGSUSER" 
	ADD CONSTRAINT "SQL051109150933050" PRIMARY KEY
		("USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BOOKMARKSENTRY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BOOKMARKSENTRY"  (
		  "ENTRYID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "FOLDERID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "URL" LONG VARCHAR , 
		  "COMMENTS" LONG VARCHAR , 
		  "VISITS" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BOOKMARKSENTRY"

ALTER TABLE "YKT_WEB "."BOOKMARKSENTRY" 
	ADD CONSTRAINT "SQL051109150933140" PRIMARY KEY
		("ENTRYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."BOOKMARKSFOLDER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."BOOKMARKSFOLDER"  (
		  "FOLDERID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PARENTFOLDERID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."BOOKMARKSFOLDER"

ALTER TABLE "YKT_WEB "."BOOKMARKSFOLDER" 
	ADD CONSTRAINT "SQL051109150933280" PRIMARY KEY
		("FOLDERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."CALEVENT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."CALEVENT"  (
		  "EVENTID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TITLE" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "STARTDATE" TIMESTAMP , 
		  "ENDDATE" TIMESTAMP , 
		  "DURATIONHOUR" INTEGER , 
		  "DURATIONMINUTE" INTEGER , 
		  "ALLDAY" CHAR(1) , 
		  "TIMEZONESENSITIVE" CHAR(1) , 
		  "TYPE_" VARCHAR(100) , 
		  "LOCATION" VARCHAR(100) , 
		  "STREET" VARCHAR(100) , 
		  "CITY" VARCHAR(100) , 
		  "STATE" VARCHAR(100) , 
		  "ZIP" VARCHAR(100) , 
		  "PHONE" VARCHAR(100) , 
		  "REPEATING" CHAR(1) , 
		  "RECURRENCE" LONG VARCHAR , 
		  "REMINDBY" VARCHAR(100) , 
		  "FIRSTREMINDER" INTEGER , 
		  "SECONDREMINDER" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."CALEVENT"

ALTER TABLE "YKT_WEB "."CALEVENT" 
	ADD CONSTRAINT "SQL051109150933700" PRIMARY KEY
		("EVENTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."CALTASK"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."CALTASK"  (
		  "TASKID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TITLE" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "NODUEDATE" CHAR(1) , 
		  "DUEDATE" TIMESTAMP , 
		  "PRIORITY" INTEGER , 
		  "STATUS" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."CALTASK"

ALTER TABLE "YKT_WEB "."CALTASK" 
	ADD CONSTRAINT "SQL051109150933980" PRIMARY KEY
		("TASKID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."COLORSCHEME"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."COLORSCHEME"  (
		  "COLORSCHEMEID" VARCHAR(100) NOT NULL , 
		  "SETTINGS_" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."COLORSCHEME"

ALTER TABLE "YKT_WEB "."COLORSCHEME" 
	ADD CONSTRAINT "SQL051109150934160" PRIMARY KEY
		("COLORSCHEMEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."COMPANY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."COMPANY"  (
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "KEY_" LONG VARCHAR , 
		  "PORTALURL" VARCHAR(100) NOT NULL , 
		  "HOMEURL" VARCHAR(100) NOT NULL , 
		  "MX" VARCHAR(100) NOT NULL , 
		  "NAME" VARCHAR(100) NOT NULL , 
		  "SHORTNAME" VARCHAR(100) NOT NULL , 
		  "TYPE_" VARCHAR(100) , 
		  "SIZE_" VARCHAR(100) , 
		  "STREET" VARCHAR(100) , 
		  "CITY" VARCHAR(100) , 
		  "STATE" VARCHAR(100) , 
		  "ZIP" VARCHAR(100) , 
		  "PHONE" VARCHAR(100) , 
		  "FAX" VARCHAR(100) , 
		  "EMAILADDRESS" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."COMPANY"

ALTER TABLE "YKT_WEB "."COMPANY" 
	ADD CONSTRAINT "SQL051109150934340" PRIMARY KEY
		("COMPANYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."CONTACT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."CONTACT"  (
		  "CONTACTID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PARENTCONTACTID" VARCHAR(100) , 
		  "FIRSTNAME" VARCHAR(100) , 
		  "MIDDLENAME" VARCHAR(100) , 
		  "LASTNAME" VARCHAR(100) , 
		  "NICKNAME" VARCHAR(100) , 
		  "EMAILADDRESS1" VARCHAR(100) , 
		  "EMAILADDRESS2" VARCHAR(100) , 
		  "SMSID" VARCHAR(100) , 
		  "AIMID" VARCHAR(100) , 
		  "ICQID" VARCHAR(100) , 
		  "MSNID" VARCHAR(100) , 
		  "SKYPEID" VARCHAR(100) , 
		  "YMID" VARCHAR(100) , 
		  "WEBSITE" VARCHAR(100) , 
		  "MALE" CHAR(1) , 
		  "BIRTHDAY" TIMESTAMP , 
		  "TIMEZONEID" VARCHAR(100) , 
		  "EMPLOYEENUMBER" VARCHAR(100) , 
		  "JOBTITLE" VARCHAR(100) , 
		  "JOBCLASS" VARCHAR(100) , 
		  "HOURSOFOPERATION" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."CONTACT"

ALTER TABLE "YKT_WEB "."CONTACT" 
	ADD CONSTRAINT "SQL051109150934530" PRIMARY KEY
		("CONTACTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."COUNTER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."COUNTER"  (
		  "NAME" VARCHAR(100) NOT NULL , 
		  "CURRENTID" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."COUNTER"

ALTER TABLE "YKT_WEB "."COUNTER" 
	ADD CONSTRAINT "SQL051109150934630" PRIMARY KEY
		("NAME");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."CYRUSUSER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."CYRUSUSER"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "PASSWORD_" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."CYRUSUSER"

ALTER TABLE "YKT_WEB "."CYRUSUSER" 
	ADD CONSTRAINT "SQL051109150934740" PRIMARY KEY
		("USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."CYRUSVIRTUAL"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."CYRUSVIRTUAL"  (
		  "EMAILADDRESS" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."CYRUSVIRTUAL"

ALTER TABLE "YKT_WEB "."CYRUSVIRTUAL" 
	ADD CONSTRAINT "SQL051109150934820" PRIMARY KEY
		("EMAILADDRESS");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."DLFILEPROFILE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."DLFILEPROFILE"  (
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "REPOSITORYID" VARCHAR(100) NOT NULL , 
		  "FILENAME" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "VERSIONUSERID" VARCHAR(100) NOT NULL , 
		  "VERSIONUSERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "READROLES" VARCHAR(100) , 
		  "WRITEROLES" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "VERSION" DOUBLE , 
		  "SIZE_" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."DLFILEPROFILE"

ALTER TABLE "YKT_WEB "."DLFILEPROFILE" 
	ADD CONSTRAINT "SQL051109150934940" PRIMARY KEY
		("COMPANYID",
		 "REPOSITORYID",
		 "FILENAME");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."DLFILERANK"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."DLFILERANK"  (
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "REPOSITORYID" VARCHAR(100) NOT NULL , 
		  "FILENAME" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."DLFILERANK"

ALTER TABLE "YKT_WEB "."DLFILERANK" 
	ADD CONSTRAINT "SQL051109150934990" PRIMARY KEY
		("COMPANYID",
		 "USERID",
		 "REPOSITORYID",
		 "FILENAME");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."DLFILEVERSION"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."DLFILEVERSION"  (
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "REPOSITORYID" VARCHAR(100) NOT NULL , 
		  "FILENAME" VARCHAR(100) NOT NULL , 
		  "VERSION" DOUBLE NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "SIZE_" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."DLFILEVERSION"

ALTER TABLE "YKT_WEB "."DLFILEVERSION" 
	ADD CONSTRAINT "SQL051109150935080" PRIMARY KEY
		("COMPANYID",
		 "REPOSITORYID",
		 "FILENAME",
		 "VERSION");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."DLREPOSITORY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."DLREPOSITORY"  (
		  "REPOSITORYID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "READROLES" VARCHAR(100) , 
		  "WRITEROLES" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "LASTPOSTDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."DLREPOSITORY"

ALTER TABLE "YKT_WEB "."DLREPOSITORY" 
	ADD CONSTRAINT "SQL051109150935170" PRIMARY KEY
		("REPOSITORYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ECARD_HIT_INFO"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ECARD_HIT_INFO"  (
		  "ID" INTEGER NOT NULL , 
		  "TITLE" VARCHAR(500) , 
		  "INFO_ID" INTEGER NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ECARD_HIT_INFO"

ALTER TABLE "YKT_WEB "."ECARD_HIT_INFO" 
	ADD CONSTRAINT "SQL051117123523240" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ECARD_INFORMATION"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ECARD_INFORMATION"  (
		  "ID" INTEGER NOT NULL , 
		  "INFO_TYPE" VARCHAR(20) , 
		  "INFO_TITLE" VARCHAR(500) , 
		  "INFO_CONTENT" LONG VARCHAR , 
		  "ATTACHMENTS" VARCHAR(90) , 
		  "CREATE_DATE" TIMESTAMP , 
		  "CREATER" VARCHAR(20) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ECARD_INFORMATION"

ALTER TABLE "YKT_WEB "."ECARD_INFORMATION" 
	ADD CONSTRAINT "SQL051109150941110" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ECARD_MSGBOARD"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ECARD_MSGBOARD"  (
		  "ID" INTEGER NOT NULL , 
		  "MSG_TITLE" VARCHAR(200) , 
		  "POST_TIME" TIMESTAMP , 
		  "POSTER" VARCHAR(40) , 
		  "POST_CONTENT" LONG VARCHAR , 
		  "REPLY_TIME" TIMESTAMP , 
		  "REPLYER" VARCHAR(40) , 
		  "REPLY_CONTENT" LONG VARCHAR , 
		  "STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ECARD_MSGBOARD"

ALTER TABLE "YKT_WEB "."ECARD_MSGBOARD" 
	ADD CONSTRAINT "SQL051109151127180" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ECARD_PIC_DELAY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ECARD_PIC_DELAY"  (
		  "CUR_STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "OLD_STUEMP_NO" VARCHAR(20) , 
		  "STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ECARD_PIC_DELAY"

ALTER TABLE "YKT_WEB "."ECARD_PIC_DELAY" 
	ADD CONSTRAINT "SQL051109151126950" PRIMARY KEY
		("CUR_STUEMP_NO");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ECARD_POSTPONE_APPLY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ECARD_POSTPONE_APPLY"  (
		  "ID" INTEGER NOT NULL , 
		  "STUEMPNO" VARCHAR(20) , 
		  "REASON" VARCHAR(900) , 
		  "POSTPONE_TIME" VARCHAR(8) , 
		  "APPLY_TIME" TIMESTAMP , 
		  "CHECK_RESULT" VARCHAR(240) , 
		  "STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ECARD_POSTPONE_APPLY"

ALTER TABLE "YKT_WEB "."ECARD_POSTPONE_APPLY" 
	ADD CONSTRAINT "SQL051109151126700" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."GROUPS_ROLES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."GROUPS_ROLES"  (
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "ROLEID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."GROUP_"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."GROUP_"  (
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "PARENTGROUPID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "FRIENDLYURL" VARCHAR(100) , 
		  "THEMEID" VARCHAR(100) , 
		  "COLORSCHEMEID" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."GROUP_"

ALTER TABLE "YKT_WEB "."GROUP_" 
	ADD CONSTRAINT "SQL051109150935430" PRIMARY KEY
		("GROUPID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."IGFOLDER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."IGFOLDER"  (
		  "FOLDERID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PARENTFOLDERID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."IGFOLDER"

ALTER TABLE "YKT_WEB "."IGFOLDER" 
	ADD CONSTRAINT "SQL051109150935660" PRIMARY KEY
		("FOLDERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."IGIMAGE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."IGIMAGE"  (
		  "IMAGEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "FOLDERID" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "HEIGHT" INTEGER , 
		  "WIDTH" INTEGER , 
		  "SIZE_" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."IGIMAGE"

ALTER TABLE "YKT_WEB "."IGIMAGE" 
	ADD CONSTRAINT "SQL051109150935810" PRIMARY KEY
		("IMAGEID",
		 "COMPANYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."IMAGE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."IMAGE"  (
		  "IMAGEID" VARCHAR(200) NOT NULL , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TEXT_" LONG VARCHAR NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."IMAGE"

ALTER TABLE "YKT_WEB "."IMAGE" 
	ADD CONSTRAINT "SQL051109150935920" PRIMARY KEY
		("IMAGEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."INFO_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."INFO_TYPE"  (
		  "INFO_TYPE" VARCHAR(20) NOT NULL , 
		  "INFO_NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."INFO_TYPE"

ALTER TABLE "YKT_WEB "."INFO_TYPE" 
	ADD CONSTRAINT "SQL051109151126840" PRIMARY KEY
		("INFO_TYPE");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."JOURNALARTICLE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."JOURNALARTICLE"  (
		  "ARTICLEID" VARCHAR(100) NOT NULL , 
		  "VERSION" DOUBLE NOT NULL , 
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TITLE" VARCHAR(100) , 
		  "CONTENT" LONG VARCHAR , 
		  "TYPE_" VARCHAR(100) , 
		  "STRUCTUREID" VARCHAR(100) , 
		  "TEMPLATEID" VARCHAR(100) , 
		  "DISPLAYDATE" TIMESTAMP , 
		  "EXPIRATIONDATE" TIMESTAMP , 
		  "APPROVED" CHAR(1) , 
		  "APPROVEDBYUSERID" VARCHAR(100) , 
		  "APPROVEDBYUSERNAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."JOURNALARTICLE"

ALTER TABLE "YKT_WEB "."JOURNALARTICLE" 
	ADD CONSTRAINT "SQL051109150936090" PRIMARY KEY
		("ARTICLEID",
		 "VERSION");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."JOURNALSTRUCTURE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."JOURNALSTRUCTURE"  (
		  "STRUCTUREID" VARCHAR(100) NOT NULL , 
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "XSD" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."JOURNALSTRUCTURE"

ALTER TABLE "YKT_WEB "."JOURNALSTRUCTURE" 
	ADD CONSTRAINT "SQL051109150936240" PRIMARY KEY
		("STRUCTUREID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."JOURNALTEMPLATE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."JOURNALTEMPLATE"  (
		  "TEMPLATEID" VARCHAR(100) NOT NULL , 
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "STRUCTUREID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "XSL" LONG VARCHAR , 
		  "SMALLIMAGE" CHAR(1) , 
		  "SMALLIMAGEURL" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."JOURNALTEMPLATE"

ALTER TABLE "YKT_WEB "."JOURNALTEMPLATE" 
	ADD CONSTRAINT "SQL051109150936320" PRIMARY KEY
		("TEMPLATEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."LAYOUT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."LAYOUT"  (
		  "LAYOUTID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) , 
		  "PARENTLAYOUTID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "TYPE_" LONG VARCHAR , 
		  "TYPESETTINGS" LONG VARCHAR , 
		  "FRIENDLYURL" VARCHAR(100) , 
		  "PRIORITY" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."LAYOUT"

ALTER TABLE "YKT_WEB "."LAYOUT" 
	ADD CONSTRAINT "SQL051109150936400" PRIMARY KEY
		("LAYOUTID",
		 "USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."MAILRECEIPT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."MAILRECEIPT"  (
		  "RECEIPTID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "RECIPIENTNAME" VARCHAR(100) , 
		  "RECIPIENTADDRESS" VARCHAR(100) , 
		  "SUBJECT" VARCHAR(100) , 
		  "SENTDATE" TIMESTAMP , 
		  "READCOUNT" INTEGER , 
		  "FIRSTREADDATE" TIMESTAMP , 
		  "LASTREADDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."MAILRECEIPT"

ALTER TABLE "YKT_WEB "."MAILRECEIPT" 
	ADD CONSTRAINT "SQL051109150936430" PRIMARY KEY
		("RECEIPTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."MBMESSAGE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."MBMESSAGE"  (
		  "MESSAGEID" VARCHAR(100) NOT NULL , 
		  "TOPICID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "THREADID" VARCHAR(100) , 
		  "PARENTMESSAGEID" VARCHAR(100) , 
		  "SUBJECT" VARCHAR(100) , 
		  "BODY" LONG VARCHAR , 
		  "ATTACHMENTS" CHAR(1) , 
		  "ANONYMOUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."MBMESSAGE"

ALTER TABLE "YKT_WEB "."MBMESSAGE" 
	ADD CONSTRAINT "SQL051109150936520" PRIMARY KEY
		("MESSAGEID",
		 "TOPICID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."MBMESSAGEFLAG"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."MBMESSAGEFLAG"  (
		  "TOPICID" VARCHAR(100) NOT NULL , 
		  "MESSAGEID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "FLAG" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."MBMESSAGEFLAG"

ALTER TABLE "YKT_WEB "."MBMESSAGEFLAG" 
	ADD CONSTRAINT "SQL051109150936600" PRIMARY KEY
		("TOPICID",
		 "MESSAGEID",
		 "USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."MBTHREAD"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."MBTHREAD"  (
		  "THREADID" VARCHAR(100) NOT NULL , 
		  "ROOTMESSAGEID" VARCHAR(100) , 
		  "TOPICID" VARCHAR(100) , 
		  "MESSAGECOUNT" INTEGER , 
		  "LASTPOSTDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."MBTHREAD"

ALTER TABLE "YKT_WEB "."MBTHREAD" 
	ADD CONSTRAINT "SQL051109150936730" PRIMARY KEY
		("THREADID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."MBTOPIC"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."MBTOPIC"  (
		  "TOPICID" VARCHAR(100) NOT NULL , 
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "READROLES" VARCHAR(100) , 
		  "WRITEROLES" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "LASTPOSTDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."MBTOPIC"

ALTER TABLE "YKT_WEB "."MBTOPIC" 
	ADD CONSTRAINT "SQL051109150936850" PRIMARY KEY
		("TOPICID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."NETWORKADDRESS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."NETWORKADDRESS"  (
		  "ADDRESSID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "URL" LONG VARCHAR , 
		  "COMMENTS" LONG VARCHAR , 
		  "CONTENT" LONG VARCHAR , 
		  "STATUS" INTEGER , 
		  "LASTUPDATED" TIMESTAMP , 
		  "NOTIFYBY" VARCHAR(100) , 
		  "INTERVAL_" INTEGER , 
		  "ACTIVE_" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."NETWORKADDRESS"

ALTER TABLE "YKT_WEB "."NETWORKADDRESS" 
	ADD CONSTRAINT "SQL051109150936990" PRIMARY KEY
		("ADDRESSID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."NOTE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."NOTE"  (
		  "NOTEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "CLASSNAME" VARCHAR(100) , 
		  "CLASSPK" VARCHAR(100) , 
		  "CONTENT" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."NOTE"

ALTER TABLE "YKT_WEB "."NOTE" 
	ADD CONSTRAINT "SQL051109150937090" PRIMARY KEY
		("NOTEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PASSWORDTRACKER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PASSWORDTRACKER"  (
		  "PASSWORDTRACKERID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP NOT NULL , 
		  "PASSWORD_" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PASSWORDTRACKER"

ALTER TABLE "YKT_WEB "."PASSWORDTRACKER" 
	ADD CONSTRAINT "SQL051109150937180" PRIMARY KEY
		("PASSWORDTRACKERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."POLLSCHOICE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."POLLSCHOICE"  (
		  "CHOICEID" VARCHAR(100) NOT NULL , 
		  "QUESTIONID" VARCHAR(100) NOT NULL , 
		  "DESCRIPTION" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."POLLSCHOICE"

ALTER TABLE "YKT_WEB "."POLLSCHOICE" 
	ADD CONSTRAINT "SQL051109150937310" PRIMARY KEY
		("CHOICEID",
		 "QUESTIONID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."POLLSQUESTION"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."POLLSQUESTION"  (
		  "QUESTIONID" VARCHAR(100) NOT NULL , 
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TITLE" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "EXPIRATIONDATE" TIMESTAMP , 
		  "LASTVOTEDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."POLLSQUESTION"

ALTER TABLE "YKT_WEB "."POLLSQUESTION" 
	ADD CONSTRAINT "SQL051109150937440" PRIMARY KEY
		("QUESTIONID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."POLLSVOTE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."POLLSVOTE"  (
		  "QUESTIONID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CHOICEID" VARCHAR(100) NOT NULL , 
		  "VOTEDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."POLLSVOTE"

ALTER TABLE "YKT_WEB "."POLLSVOTE" 
	ADD CONSTRAINT "SQL051109150937500" PRIMARY KEY
		("QUESTIONID",
		 "USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PORTLET"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PORTLET"  (
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "NARROW" CHAR(1) , 
		  "ROLES" LONG VARCHAR , 
		  "ACTIVE_" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PORTLET"

ALTER TABLE "YKT_WEB "."PORTLET" 
	ADD CONSTRAINT "SQL051109150937590" PRIMARY KEY
		("PORTLETID",
		 "COMPANYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PORTLETPREFERENCES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PORTLETPREFERENCES"  (
		  "PORTLETID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "LAYOUTID" VARCHAR(100) NOT NULL , 
		  "PREFERENCES" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PORTLETPREFERENCES"

ALTER TABLE "YKT_WEB "."PORTLETPREFERENCES" 
	ADD CONSTRAINT "SQL051109150937660" PRIMARY KEY
		("PORTLETID",
		 "USERID",
		 "LAYOUTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."POSTPONE_FILES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."POSTPONE_FILES"  (
		  "ID" INTEGER NOT NULL , 
		  "GENERATE_DATE" TIMESTAMP , 
		  "FILE_CONTENT" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."POSTPONE_FILES"

ALTER TABLE "YKT_WEB "."POSTPONE_FILES" 
	ADD CONSTRAINT "SQL051109151127080" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PROJFIRM"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PROJFIRM"  (
		  "FIRMID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "URL" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PROJFIRM"

ALTER TABLE "YKT_WEB "."PROJFIRM" 
	ADD CONSTRAINT "SQL051109150937830" PRIMARY KEY
		("FIRMID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PROJPROJECT"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PROJPROJECT"  (
		  "PROJECTID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "FIRMID" VARCHAR(100) , 
		  "CODE" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PROJPROJECT"

ALTER TABLE "YKT_WEB "."PROJPROJECT" 
	ADD CONSTRAINT "SQL051109150937930" PRIMARY KEY
		("PROJECTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PROJTASK"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PROJTASK"  (
		  "TASKID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PROJECTID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "COMMENTS" LONG VARCHAR , 
		  "ESTIMATEDDURATION" INTEGER , 
		  "ESTIMATEDENDDATE" TIMESTAMP , 
		  "ACTUALDURATION" INTEGER , 
		  "ACTUALENDDATE" TIMESTAMP , 
		  "STATUS" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PROJTASK"

ALTER TABLE "YKT_WEB "."PROJTASK" 
	ADD CONSTRAINT "SQL051109150938170" PRIMARY KEY
		("TASKID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PROJTIME"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PROJTIME"  (
		  "TIMEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PROJECTID" VARCHAR(100) , 
		  "TASKID" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "STARTDATE" TIMESTAMP , 
		  "ENDDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PROJTIME"

ALTER TABLE "YKT_WEB "."PROJTIME" 
	ADD CONSTRAINT "SQL051109150938290" PRIMARY KEY
		("TIMEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."PROPERTIES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."PROPERTIES"  (
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "TYPE_" VARCHAR(100) NOT NULL , 
		  "PROPERTIES" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."PROPERTIES"

ALTER TABLE "YKT_WEB "."PROPERTIES" 
	ADD CONSTRAINT "SQL051109150938450" PRIMARY KEY
		("COMPANYID",
		 "TYPE_");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."RELEASE_"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."RELEASE_"  (
		  "RELEASEID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "BUILDNUMBER" INTEGER , 
		  "BUILDDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."RELEASE_"

ALTER TABLE "YKT_WEB "."RELEASE_" 
	ADD CONSTRAINT "SQL051109150938550" PRIMARY KEY
		("RELEASEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."ROLE_"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."ROLE_"  (
		  "ROLEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "NAME" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."ROLE_"

ALTER TABLE "YKT_WEB "."ROLE_" 
	ADD CONSTRAINT "SQL051109150938680" PRIMARY KEY
		("ROLEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGCART"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGCART"  (
		  "CARTID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "ITEMIDS" LONG VARCHAR , 
		  "COUPONIDS" LONG VARCHAR , 
		  "ALTSHIPPING" INTEGER , 
		  "INSURE" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGCART"

ALTER TABLE "YKT_WEB "."SHOPPINGCART" 
	ADD CONSTRAINT "SQL051109150938790" PRIMARY KEY
		("CARTID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGCATEGORY"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGCATEGORY"  (
		  "CATEGORYID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "PARENTCATEGORYID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGCATEGORY"

ALTER TABLE "YKT_WEB "."SHOPPINGCATEGORY" 
	ADD CONSTRAINT "SQL051109150938840" PRIMARY KEY
		("CATEGORYID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGCOUPON"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGCOUPON"  (
		  "COUPONID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "STARTDATE" TIMESTAMP , 
		  "ENDDATE" TIMESTAMP , 
		  "ACTIVE_" CHAR(1) , 
		  "LIMITCATEGORIES" LONG VARCHAR , 
		  "LIMITSKUS" LONG VARCHAR , 
		  "MINORDER" DOUBLE , 
		  "DISCOUNT" DOUBLE , 
		  "DISCOUNTTYPE" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGCOUPON"

ALTER TABLE "YKT_WEB "."SHOPPINGCOUPON" 
	ADD CONSTRAINT "SQL051109150938990" PRIMARY KEY
		("COUPONID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGITEM"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGITEM"  (
		  "ITEMID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "CATEGORYID" VARCHAR(100) , 
		  "SKU" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "PROPERTIES" LONG VARCHAR , 
		  "SUPPLIERUSERID" VARCHAR(100) , 
		  "FIELDS_" CHAR(1) , 
		  "FIELDSQUANTITIES" LONG VARCHAR , 
		  "MINQUANTITY" INTEGER , 
		  "MAXQUANTITY" INTEGER , 
		  "PRICE" DOUBLE , 
		  "DISCOUNT" DOUBLE , 
		  "TAXABLE" CHAR(1) , 
		  "SHIPPING" DOUBLE , 
		  "USESHIPPINGFORMULA" CHAR(1) , 
		  "REQUIRESSHIPPING" CHAR(1) , 
		  "STOCKQUANTITY" INTEGER , 
		  "FEATURED_" CHAR(1) , 
		  "SALE_" CHAR(1) , 
		  "SMALLIMAGE" CHAR(1) , 
		  "SMALLIMAGEURL" VARCHAR(100) , 
		  "MEDIUMIMAGE" CHAR(1) , 
		  "MEDIUMIMAGEURL" VARCHAR(100) , 
		  "LARGEIMAGE" CHAR(1) , 
		  "LARGEIMAGEURL" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGITEM"

ALTER TABLE "YKT_WEB "."SHOPPINGITEM" 
	ADD CONSTRAINT "SQL051109150939080" PRIMARY KEY
		("ITEMID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGITEMFIELD"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGITEMFIELD"  (
		  "ITEMFIELDID" VARCHAR(100) NOT NULL , 
		  "ITEMID" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "VALUES_" LONG VARCHAR , 
		  "DESCRIPTION" LONG VARCHAR )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGITEMFIELD"

ALTER TABLE "YKT_WEB "."SHOPPINGITEMFIELD" 
	ADD CONSTRAINT "SQL051109150939230" PRIMARY KEY
		("ITEMFIELDID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGITEMPRICE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGITEMPRICE"  (
		  "ITEMPRICEID" VARCHAR(100) NOT NULL , 
		  "ITEMID" VARCHAR(100) , 
		  "MINQUANTITY" INTEGER , 
		  "MAXQUANTITY" INTEGER , 
		  "PRICE" DOUBLE , 
		  "DISCOUNT" DOUBLE , 
		  "TAXABLE" CHAR(1) , 
		  "SHIPPING" DOUBLE , 
		  "USESHIPPINGFORMULA" CHAR(1) , 
		  "STATUS" INTEGER )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGITEMPRICE"

ALTER TABLE "YKT_WEB "."SHOPPINGITEMPRICE" 
	ADD CONSTRAINT "SQL051109150939300" PRIMARY KEY
		("ITEMPRICEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGORDER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGORDER"  (
		  "ORDERID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "TAX" DOUBLE , 
		  "SHIPPING" DOUBLE , 
		  "ALTSHIPPING" VARCHAR(100) , 
		  "REQUIRESSHIPPING" CHAR(1) , 
		  "INSURE" CHAR(1) , 
		  "INSURANCE" DOUBLE , 
		  "COUPONIDS" LONG VARCHAR , 
		  "COUPONDISCOUNT" DOUBLE , 
		  "BILLINGFIRSTNAME" VARCHAR(100) , 
		  "BILLINGLASTNAME" VARCHAR(100) , 
		  "BILLINGEMAILADDRESS" VARCHAR(100) , 
		  "BILLINGCOMPANY" VARCHAR(100) , 
		  "BILLINGSTREET" VARCHAR(100) , 
		  "BILLINGCITY" VARCHAR(100) , 
		  "BILLINGSTATE" VARCHAR(100) , 
		  "BILLINGZIP" VARCHAR(100) , 
		  "BILLINGCOUNTRY" VARCHAR(100) , 
		  "BILLINGPHONE" VARCHAR(100) , 
		  "SHIPTOBILLING" CHAR(1) , 
		  "SHIPPINGFIRSTNAME" VARCHAR(100) , 
		  "SHIPPINGLASTNAME" VARCHAR(100) , 
		  "SHIPPINGEMAILADDRESS" VARCHAR(100) , 
		  "SHIPPINGCOMPANY" VARCHAR(100) , 
		  "SHIPPINGSTREET" VARCHAR(100) , 
		  "SHIPPINGCITY" VARCHAR(100) , 
		  "SHIPPINGSTATE" VARCHAR(100) , 
		  "SHIPPINGZIP" VARCHAR(100) , 
		  "SHIPPINGCOUNTRY" VARCHAR(100) , 
		  "SHIPPINGPHONE" VARCHAR(100) , 
		  "CCNAME" VARCHAR(100) , 
		  "CCTYPE" VARCHAR(100) , 
		  "CCNUMBER" VARCHAR(100) , 
		  "CCEXPMONTH" INTEGER , 
		  "CCEXPYEAR" INTEGER , 
		  "CCVERNUMBER" VARCHAR(100) , 
		  "COMMENTS" LONG VARCHAR , 
		  "PPTXNID" VARCHAR(100) , 
		  "PPPAYMENTSTATUS" VARCHAR(100) , 
		  "PPPAYMENTGROSS" DOUBLE , 
		  "PPRECEIVEREMAIL" VARCHAR(100) , 
		  "PPPAYEREMAIL" VARCHAR(100) , 
		  "SENDORDEREMAIL" CHAR(1) , 
		  "SENDSHIPPINGEMAIL" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGORDER"

ALTER TABLE "YKT_WEB "."SHOPPINGORDER" 
	ADD CONSTRAINT "SQL051109150939460" PRIMARY KEY
		("ORDERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."SHOPPINGORDERITEM"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."SHOPPINGORDERITEM"  (
		  "ORDERID" VARCHAR(100) NOT NULL , 
		  "ITEMID" VARCHAR(100) NOT NULL , 
		  "SKU" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "PROPERTIES" LONG VARCHAR , 
		  "SUPPLIERUSERID" VARCHAR(100) , 
		  "PRICE" DOUBLE , 
		  "QUANTITY" INTEGER , 
		  "SHIPPEDDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."SHOPPINGORDERITEM"

ALTER TABLE "YKT_WEB "."SHOPPINGORDERITEM" 
	ADD CONSTRAINT "SQL051109150939910" PRIMARY KEY
		("ORDERID",
		 "ITEMID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."UPLOAD_FILES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."UPLOAD_FILES"  (
		  "ID" INTEGER NOT NULL , 
		  "STORE_FILENAME" VARCHAR(240) , 
		  "OLD_FILENAME" VARCHAR(240) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."UPLOAD_FILES"

ALTER TABLE "YKT_WEB "."UPLOAD_FILES" 
	ADD CONSTRAINT "SQL051109150940990" PRIMARY KEY
		("ID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERS_GROUPS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERS_GROUPS"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "GROUPID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERS_PROJPROJECTS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERS_PROJPROJECTS"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "PROJECTID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERS_PROJTASKS"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERS_PROJTASKS"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "TASKID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERS_ROLES"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERS_ROLES"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "ROLEID" VARCHAR(100) NOT NULL )   
		 IN "USERSPACE1" ; 



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERTRACKER"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERTRACKER"  (
		  "USERTRACKERID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "REMOTEADDR" VARCHAR(100) , 
		  "REMOTEHOST" VARCHAR(100) , 
		  "USERAGENT" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."USERTRACKER"

ALTER TABLE "YKT_WEB "."USERTRACKER" 
	ADD CONSTRAINT "SQL051109150940250" PRIMARY KEY
		("USERTRACKERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USERTRACKERPATH"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USERTRACKERPATH"  (
		  "USERTRACKERPATHID" VARCHAR(100) NOT NULL , 
		  "USERTRACKERID" VARCHAR(100) NOT NULL , 
		  "PATH" LONG VARCHAR NOT NULL , 
		  "PATHDATE" TIMESTAMP NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."USERTRACKERPATH"

ALTER TABLE "YKT_WEB "."USERTRACKERPATH" 
	ADD CONSTRAINT "SQL051109150940530" PRIMARY KEY
		("USERTRACKERPATHID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."USER_"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."USER_"  (
		  "USERID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "CREATEDATE" TIMESTAMP , 
		  "PASSWORD_" VARCHAR(100) , 
		  "PASSWORDENCRYPTED" CHAR(1) , 
		  "PASSWORDEXPIRATIONDATE" TIMESTAMP , 
		  "PASSWORDRESET" CHAR(1) , 
		  "FIRSTNAME" VARCHAR(100) , 
		  "MIDDLENAME" VARCHAR(100) , 
		  "LASTNAME" VARCHAR(100) , 
		  "NICKNAME" VARCHAR(100) , 
		  "MALE" CHAR(1) , 
		  "BIRTHDAY" TIMESTAMP , 
		  "EMAILADDRESS" VARCHAR(100) , 
		  "SMSID" VARCHAR(100) , 
		  "AIMID" VARCHAR(100) , 
		  "ICQID" VARCHAR(100) , 
		  "MSNID" VARCHAR(100) , 
		  "YMID" VARCHAR(100) , 
		  "FAVORITEACTIVITY" VARCHAR(100) , 
		  "FAVORITEBIBLEVERSE" VARCHAR(100) , 
		  "FAVORITEFOOD" VARCHAR(100) , 
		  "FAVORITEMOVIE" VARCHAR(100) , 
		  "FAVORITEMUSIC" VARCHAR(100) , 
		  "LANGUAGEID" VARCHAR(100) , 
		  "TIMEZONEID" VARCHAR(100) , 
		  "THEMEID" VARCHAR(100) , 
		  "COLORSCHEMEID" VARCHAR(100) , 
		  "GREETING" VARCHAR(100) , 
		  "RESOLUTION" VARCHAR(100) , 
		  "COMMENTS" LONG VARCHAR , 
		  "LOGINDATE" TIMESTAMP , 
		  "LOGINIP" VARCHAR(100) , 
		  "LASTLOGINDATE" TIMESTAMP , 
		  "LASTLOGINIP" VARCHAR(100) , 
		  "FAILEDLOGINATTEMPTS" INTEGER , 
		  "AGREEDTOTERMSOFUSE" CHAR(1) , 
		  "ACTIVE_" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."USER_"

ALTER TABLE "YKT_WEB "."USER_" 
	ADD CONSTRAINT "SQL051109150940050" PRIMARY KEY
		("USERID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."WIKINODE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."WIKINODE"  (
		  "NODEID" VARCHAR(100) NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "MODIFIEDDATE" TIMESTAMP , 
		  "READROLES" VARCHAR(100) , 
		  "WRITEROLES" VARCHAR(100) , 
		  "NAME" VARCHAR(100) , 
		  "DESCRIPTION" LONG VARCHAR , 
		  "SHARING" CHAR(1) , 
		  "LASTPOSTDATE" TIMESTAMP )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."WIKINODE"

ALTER TABLE "YKT_WEB "."WIKINODE" 
	ADD CONSTRAINT "SQL051109150940810" PRIMARY KEY
		("NODEID");



------------------------------------------------
-- DDL Statements for table "YKT_WEB "."WIKIPAGE"
------------------------------------------------
 
 CREATE TABLE "YKT_WEB "."WIKIPAGE"  (
		  "NODEID" VARCHAR(100) NOT NULL , 
		  "TITLE" VARCHAR(100) NOT NULL , 
		  "VERSION" DOUBLE NOT NULL , 
		  "COMPANYID" VARCHAR(100) NOT NULL , 
		  "USERID" VARCHAR(100) NOT NULL , 
		  "USERNAME" VARCHAR(100) , 
		  "CREATEDATE" TIMESTAMP , 
		  "CONTENT" LONG VARCHAR , 
		  "FORMAT" VARCHAR(100) , 
		  "HEAD" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_WEB "."WIKIPAGE"

ALTER TABLE "YKT_WEB "."WIKIPAGE" 
	ADD CONSTRAINT "SQL051109150940900" PRIMARY KEY
		("NODEID",
		 "TITLE",
		 "VERSION");









COMMIT WORK;



TERMINATE;
-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分26秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_QUERY"."T_LEADQUERY_FUNCLIST"
------------------------------------------------
 
 CREATE TABLE "YKT_QUERY"."T_LEADQUERY_FUNCLIST"  (
		  "FUNC_CODE" VARCHAR(4) NOT NULL , 
		  "FUNC_NAME" VARCHAR(100) , 
		  "FUNC_URL" VARCHAR(100) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_QUERY"."T_LEADQUERY_FUNCLIST"

ALTER TABLE "YKT_QUERY"."T_LEADQUERY_FUNCLIST" 
	ADD CONSTRAINT "P_KEY_1" PRIMARY KEY
		("FUNC_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_QUERY"."T_LEADQUERY_OPERATOR"
------------------------------------------------
 
 CREATE TABLE "YKT_QUERY"."T_LEADQUERY_OPERATOR"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "OPER_NAME" VARCHAR(20) NOT NULL , 
		  "PHONE" VARCHAR(40) , 
		  "MOBILE" VARCHAR(40) , 
		  "ADDR" VARCHAR(100) , 
		  "ZIP" CHAR(6) , 
		  "EMAIL" VARCHAR(80) , 
		  "OPER_PWD" VARCHAR(100) , 
		  "STATUS" CHAR(1) , 
		  "LOGIN_TIME" VARCHAR(32) , 
		  "LOGOUT_TIME" VARCHAR(32) , 
		  "LOGIN_IP" VARCHAR(20) , 
		  "LOGIN_FLAG" CHAR(1) , 
		  "REG_DATA" VARCHAR(10) , 
		  "REG_TIME" VARCHAR(10) , 
		  "IS_SHOP_OWNER" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_QUERY"."T_LEADQUERY_OPERATOR"

ALTER TABLE "YKT_QUERY"."T_LEADQUERY_OPERATOR" 
	ADD CONSTRAINT "SQL051113190402670" PRIMARY KEY
		("OPER_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_QUERY"."T_LEADQUERY_OPERLIMIT"
------------------------------------------------
 
 CREATE TABLE "YKT_QUERY"."T_LEADQUERY_OPERLIMIT"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "FUNC_CODE" VARCHAR(4) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_QUERY"."T_LEADQUERY_OPERLIMIT"

ALTER TABLE "YKT_QUERY"."T_LEADQUERY_OPERLIMIT" 
	ADD CONSTRAINT "SQL051109202230980" PRIMARY KEY
		("OPER_CODE",
		 "FUNC_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_QUERY"."T_LEADQUERY_STORELIMIT"
------------------------------------------------
 
 CREATE TABLE "YKT_QUERY"."T_LEADQUERY_STORELIMIT"  (
		  "OPER_CODE" VARCHAR(10) NOT NULL , 
		  "STORE_CODE" VARCHAR(6) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_QUERY"."T_LEADQUERY_STORELIMIT"

ALTER TABLE "YKT_QUERY"."T_LEADQUERY_STORELIMIT" 
	ADD PRIMARY KEY
		("OPER_CODE",
		 "STORE_CODE");









COMMIT WORK;



TERMINATE;
-- This CLP file was created using DB2LOOK Version 8.2
-- Timestamp: 2006年08月04日 星期五 14时14分27秒
-- Database Name: YKTTZ          
-- Database Manager Version: DB2/LINUX Version 8.2.0       
-- Database Codepage: 1208
-- Database Collating Sequence is: BINARY






------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_ASSEMBLY_ROOM"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_ASSEMBLY_ROOM"  (
		  "ROOM_ID" VARCHAR(8) NOT NULL , 
		  "ROOM_NAME" VARCHAR(80) , 
		  "ADDRESS" VARCHAR(120) , 
		  "SIGN" CHAR(1) , 
		  "CONTAIN" INTEGER , 
		  "COMMENTS" VARCHAR(200) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_ASSEMBLY_ROOM"

ALTER TABLE "YKT_CONF"."T_ASSEMBLY_ROOM" 
	ADD CONSTRAINT "P_KEY_1" PRIMARY KEY
		("ROOM_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_ATTENDEE_GROUP"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_ATTENDEE_GROUP"  (
		  "CUST_ID" INTEGER NOT NULL , 
		  "GROUP_ID" INTEGER NOT NULL , 
		  "COMMENTS" VARCHAR(120) )   
		 IN "USERSPACE1" ; 
COMMENT ON TABLE "YKT_CONF"."T_ATTENDEE_GROUP" IS '';

COMMENT ON COLUMN "YKT_CONF"."T_ATTENDEE_GROUP"."COMMENTS" IS '';

COMMENT ON COLUMN "YKT_CONF"."T_ATTENDEE_GROUP"."CUST_ID" IS '';

COMMENT ON COLUMN "YKT_CONF"."T_ATTENDEE_GROUP"."GROUP_ID" IS '';


-- DDL Statements for primary key on Table "YKT_CONF"."T_ATTENDEE_GROUP"

ALTER TABLE "YKT_CONF"."T_ATTENDEE_GROUP" 
	ADD PRIMARY KEY
		("CUST_ID",
		 "GROUP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_ATTENDEE_LIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_ATTENDEE_LIST"  (
		  "CON_ID" INTEGER NOT NULL , 
		  "CUST_ID" INTEGER NOT NULL , 
		  "CARD_NO" INTEGER , 
		  "ALLOT_DATE" CHAR(8) , 
		  "ALLOT_TIME" VARCHAR(6) , 
		  "SEND_SIGN" CHAR(1) , 
		  "DEL_SIGN" CHAR(1) , 
		  "ATTENDEE_TYPE" CHAR(1) , 
		  "ATTEND_SIGN" CHAR(1) , 
		  "ATTEND_DATE" CHAR(8) , 
		  "ATTEND_TIME" VARCHAR(6) , 
		  "LEAVE_REASON" VARCHAR(300) , 
		  "REPLACER_ID" VARCHAR(10) , 
		  "REPLACER_NAME" VARCHAR(60) , 
		  "REPLACER_DEPT" VARCHAR(120) , 
		  "REPLACER_DUTY" VARCHAR(120) , 
		  "REPLACER_COMMENTS" VARCHAR(300) , 
		  "DELEGRAY" VARCHAR(150) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_ATTENDEE_LIST"

ALTER TABLE "YKT_CONF"."T_ATTENDEE_LIST" 
	ADD PRIMARY KEY
		("CON_ID",
		 "CUST_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_CONFERENCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_CONFERENCE"  (
		  "CON_ID" INTEGER NOT NULL GENERATED BY DEFAULT AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "CON_NAME" VARCHAR(120) , 
		  "ROOM_ID" VARCHAR(8) , 
		  "TYPE_NAME" VARCHAR(90) , 
		  "CON_BEGINDATE" CHAR(8) , 
		  "CON_SIGNTIME" VARCHAR(6) , 
		  "CON_BEGINTIME" VARCHAR(6) , 
		  "CON_ENDDATE" CHAR(8) , 
		  "CON_ENDTIME" VARCHAR(6) , 
		  "ORGANIGER_ID" VARCHAR(10) , 
		  "COMPERE" VARCHAR(20) , 
		  "CON_EXPLAIN" VARCHAR(300) , 
		  "IF_SERECY" CHAR(1) , 
		  "STATUS" CHAR(1) WITH DEFAULT '0' , 
		  "CONTENT" VARCHAR(3000) , 
		  "COMMENTS" VARCHAR(100) , 
		  "PREPLAN_1" VARCHAR(50) , 
		  "PREPLAN_2" VARCHAR(50) , 
		  "PREPLAN_3" VARCHAR(50) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_CONFERENCE"

ALTER TABLE "YKT_CONF"."T_CONFERENCE" 
	ADD PRIMARY KEY
		("CON_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_CONFERENCE_TYPE"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_CONFERENCE_TYPE"  (
		  "TYPE_ID" INTEGER NOT NULL GENERATED BY DEFAULT AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "TYPE_NAME" VARCHAR(90) , 
		  "COMMENTS" VARCHAR(240) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_CONFERENCE_TYPE"

ALTER TABLE "YKT_CONF"."T_CONFERENCE_TYPE" 
	ADD PRIMARY KEY
		("TYPE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_DEPT_LIMIT"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_DEPT_LIMIT"  (
		  "OPER_CODE" VARCHAR(20) NOT NULL , 
		  "DEPT_ID" VARCHAR(10) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_DEPT_LIMIT"

ALTER TABLE "YKT_CONF"."T_DEPT_LIMIT" 
	ADD PRIMARY KEY
		("OPER_CODE",
		 "DEPT_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_DEV_CONFERENCE"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_DEV_CONFERENCE"  (
		  "CON_ID" INTEGER NOT NULL , 
		  "DEVICE_ID" INTEGER NOT NULL , 
		  "CON_BEGINDATE" CHAR(8) , 
		  "CON_BEGINTIME" VARCHAR(6) , 
		  "CON_ENDTIME" VARCHAR(6) , 
		  "CON_SIGNTIME" VARCHAR(6) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_DEV_CONFERENCE"

ALTER TABLE "YKT_CONF"."T_DEV_CONFERENCE" 
	ADD PRIMARY KEY
		("CON_ID",
		 "DEVICE_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_DUTY"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_DUTY"  (
		  "STUEMP_NO" VARCHAR(20) NOT NULL , 
		  "OA_ACCOUNT" VARCHAR(50) NOT NULL , 
		  "DUTY" VARCHAR(300) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_DUTY"

ALTER TABLE "YKT_CONF"."T_DUTY" 
	ADD PRIMARY KEY
		("STUEMP_NO",
		 "OA_ACCOUNT");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_FUNC_LIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_FUNC_LIST"  (
		  "FUNC_CODE" VARCHAR(4) NOT NULL , 
		  "FUNC_NAME" VARCHAR(200) , 
		  "FUNC_URL" VARCHAR(400) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_FUNC_LIST"

ALTER TABLE "YKT_CONF"."T_FUNC_LIST" 
	ADD PRIMARY KEY
		("FUNC_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_GROUP"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_GROUP"  (
		  "GROUP_ID" INTEGER NOT NULL GENERATED BY DEFAULT AS IDENTITY (  
		    START WITH +1  
		    INCREMENT BY +1  
		    MINVALUE +1  
		    MAXVALUE +2147483647  
		    NO CYCLE  
		    CACHE 20  
		    NO ORDER ) , 
		  "OPER_ID" VARCHAR(20) NOT NULL , 
		  "GROUP_NAME" VARCHAR(120) , 
		  "COMMENTS" VARCHAR(120) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_GROUP"

ALTER TABLE "YKT_CONF"."T_GROUP" 
	ADD PRIMARY KEY
		("GROUP_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_INFORM_LIST"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_INFORM_LIST"  (
		  "CUST_ID" INTEGER NOT NULL , 
		  "CON_ID" INTEGER NOT NULL , 
		  "INFORM_DATE" CHAR(8) , 
		  "INFORM_TIME" CHAR(6) , 
		  "INFORM_SIGN" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_INFORM_LIST"

ALTER TABLE "YKT_CONF"."T_INFORM_LIST" 
	ADD PRIMARY KEY
		("CUST_ID",
		 "CON_ID");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_OPERATOR"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_OPERATOR"  (
		  "OPER_CODE" VARCHAR(20) NOT NULL , 
		  "OPER_NAME" VARCHAR(60) , 
		  "OPER_PWD" VARCHAR(100) , 
		  "DEPT_ID" VARCHAR(10) , 
		  "LOGIN_TIME" VARCHAR(20) , 
		  "LOGIN_IP" VARCHAR(15) , 
		  "STATUS" CHAR(1) )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_OPERATOR"

ALTER TABLE "YKT_CONF"."T_OPERATOR" 
	ADD PRIMARY KEY
		("OPER_CODE");



------------------------------------------------
-- DDL Statements for table "YKT_CONF"."T_OPER_LIMIT"
------------------------------------------------
 
 CREATE TABLE "YKT_CONF"."T_OPER_LIMIT"  (
		  "OPER_CODE" VARCHAR(20) NOT NULL , 
		  "FUNC_CODE" VARCHAR(4) NOT NULL )   
		 IN "USERSPACE1" ; 

-- DDL Statements for primary key on Table "YKT_CONF"."T_OPER_LIMIT"

ALTER TABLE "YKT_CONF"."T_OPER_LIMIT" 
	ADD PRIMARY KEY
		("OPER_CODE",
		 "FUNC_CODE");







----------------------------

-- DDL Statements for Views

----------------------------
CREATE VIEW YKT_CONF.V_CONFERENCE AS  select conf.CON_ID, conf.CON_NAME,
conf.ROOM_ID, room.room_name, room.address, conf.TYPE_NAME, conf.CON_BEGINDATE,
conf.CON_BEGINTIME, conf.CON_ENDDATE,  conf.CON_ENDTIME, dept.dept_name,
conf.ORGANIGER_ID, conf.COMPERE,  conf.CON_EXPLAIN, conf.IF_SERECY, conf.STATUS,
conf.CONTENT, conf.COMMENTS , conf.PREPLAN_1, conf.PREPLAN_2, conf.PREPLAN_3
from YKT_CONF.T_CONFERENCE conf,ykt_cur.t_cif_dept dept,  ykt_conf.t_assembly_room
room where conf.room_id = room.room_id and conf.organiger_id=dept.dept_code;

COMMENT ON TABLE "YKT_CONF"."V_CONFERENCE" IS '';




COMMIT WORK;



TERMINATE;
