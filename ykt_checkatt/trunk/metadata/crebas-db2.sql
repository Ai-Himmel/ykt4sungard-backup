--==============================================================
-- DBMS name:      IBM DB2 UDB 8.x Common Server
-- Created on:     2006-5-8 14:03:47
--==============================================================


drop table YKT_CK.ico_account_role;

drop table YKT_CK.ico_menu;

drop table YKT_CK.ico_permission;

drop table YKT_CK.ico_resource;

drop table YKT_CK.ico_role;

drop table YKT_CK.ico_role_menu;

drop table YKT_CK.usr_account;

drop table YKT_CK.usr_person;

--==============================================================
-- Table: ico_account_role
--==============================================================
create table YKT_CK.ico_account_role
(
   account_id           varchar(32)            not null,
   role_id              varchar(32)            not null,
   constraint P_Key_4 primary key (account_id, role_id)
);

--==============================================================
-- Table: ico_menu
--==============================================================
create table YKT_CK.ico_menu
(
   id                   varchar(32)            not null,
   pid                  varchar(32)            not null default '0',
   menu_name            varchar(32)            not null,
   url                  varchar(255),
   title                varchar(255),
   target               varchar(255),
   icon                 varchar(255),
   iconopen             varchar(255),
   opened               char(1),
   sort_flag            integer,
   constraint P_Key_7 primary key (id)
);

--==============================================================
-- Table: ico_permission
--==============================================================
create table YKT_CK.ico_permission
(
   role_id              varchar(32)            not null,
   resource_id          varchar(32)            not null,
   constraint P_Key_5 primary key (role_id, resource_id)
);

--==============================================================
-- Table: ico_resource
--==============================================================
create table YKT_CK.ico_resource
(
   id                   varchar(32)            not null,
   resource_code        varchar(32)            not null,
   resource_name        varchar(255)           not null,
   parent_name          varchar(255),
   url                  varchar(255),
   acl_class            varchar(255),
   constraint P_Key_3 primary key (id)
);

--==============================================================
-- Table: ico_role
--==============================================================
create table YKT_CK.ico_role
(
   id                   varchar(32)            not null,
   role_name            varchar(64)            not null,
   role_type            char(1),
   remark               varchar(255),
   constraint P_Key_2 primary key (id)
);

--==============================================================
-- Table: ico_role_menu
--==============================================================
create table YKT_CK.ico_role_menu
(
   role_id              varchar(32)            not null,
   menu_id              varchar(32)            not null,
   constraint P_Key_6 primary key (role_id, menu_id)
);

--==============================================================
-- Table: usr_account
--==============================================================
create table YKT_CK.usr_account
(
   id                   varchar(32)            not null,
   account_name         varchar(64)            not null,
   password             varchar(64),
   enabled              char(1)                default '0',
   constraint P_Key_1 primary key (id)
);


--==============================================================
-- Table: usr_person
--==============================================================
CREATE TABLE YKT_CK.USR_PERSON
 (ID           VARCHAR(32)     NOT NULL,
  PERSON_CODE  VARCHAR(32)     NOT NULL,
  PERSON_NAME  VARCHAR(32)     NOT NULL,
  PERSON_TYPE  CHARACTER(1),
  SEX          CHARACTER(1),
  EMAIL        VARCHAR(50),
  QQ           VARCHAR(32),
  PHONE        VARCHAR(32),
  CARD_ID      VARCHAR(32),
  CARD         VARCHAR(32),
  BIRTHDAY     CHARACTER(8),
  DEPT         VARCHAR(32),
  POST         VARCHAR(32),
  POST_DATE    CHARACTER(8),
  WORK_PLACE   VARCHAR(100),
  OFFICE       VARCHAR(100),
  OFFICE_PHONE VARCHAR(32),
  ADDRESS      VARCHAR(100),
  POSTALCODE   VARCHAR(10),
  MSN          VARCHAR(32),
  POLITY       VARCHAR(32),
  NATION       VARCHAR(32),
  WORK_DATE    CHARACTER(8),
  TECH_POST    VARCHAR(32),
  SEMINARY     VARCHAR(32),
  GRADUCATION  CHARACTER(8),
  EDUCATION    VARCHAR(32),
  DEGREE       VARCHAR(32),
  REMARK       VARCHAR(100),
  QUESTION     VARCHAR(100),
  ANSWER       VARCHAR(100),
  CREATEDATE   CHARACTER(8),
  LASTDATE     CHARACTER(8),
  SORT         VARCHAR(32),
  COLLEGE      VARCHAR(100),
  DEPARTMENT   VARCHAR(32),
  GRADE        VARCHAR(32),
  BRIEF        VARCHAR(200),
  STRONG_SUIT  VARCHAR(100),
  CAMPUS       VARCHAR(32),
  DORM         VARCHAR(32),
  DORM_PHONE   VARCHAR(32)
 );
ALTER TABLE YKT_CK.USR_PERSON
  ADD CONSTRAINT P_KEY_8 PRIMARY KEY
   (ID
   );
