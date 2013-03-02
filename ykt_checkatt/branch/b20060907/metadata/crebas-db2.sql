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
create table YKT_CK.usr_person
(
   id                   varchar(32)            not null,
   person_code          varchar(32)            not null,
   person_name          varchar(32)            not null,
   person_type          char(1),
   sex                  char(1),
   email                varchar(50),
   qq                   varchar(32),
   phone                varchar(32),
   card                 varchar(32),
   birthday             char(8),
   dept                 varchar(32),
   post                 varchar(32),
   post_date            CHAR(8),
   work_place           varchar(100),
   office               varchar(100),
   office_phone         varchar(32),
   address              varchar(100),
   postalcode           varchar(10),
   msn                  varchar(32),
   polity               varchar(32),
   nation               varchar(32),
   work_date            CHAR(8),
   tech_post            varchar(32),
   seminary             varchar(32),
   graducation          CHAR(8),
   education            varchar(32),
   degree               varchar(32),
   remark               varchar(100),
   question             varchar(100),
   answer               varchar(100),
   createdate           CHAR(8),
   lastdate             CHAR(8),
   sort                 varchar(32),
   college              varchar(100),
   department           varchar(32),
   grade                varchar(32),
   brief                varchar(200),
   strong_suit          varchar(100),
   campus               varchar(32),
   dorm                 varchar(32),
   dorm_phone           varchar(32),
   constraint P_Key_8 primary key (id)
);

