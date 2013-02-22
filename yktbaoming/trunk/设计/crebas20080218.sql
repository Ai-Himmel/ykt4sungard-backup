/*==============================================================*/
/* DBMS name:      ORACLE Version 10g                           */
/* Created on:     2008-2-18 15:46:45                           */
/*==============================================================*/


alter table "ykt_bm"."bm_test"
   drop constraint FK_TEST;

drop table "ykt_bm"."bm_access_info" cascade constraints;

drop table "ykt_bm"."bm_department" cascade constraints;

drop table "ykt_bm"."bm_major" cascade constraints;

drop table "ykt_bm"."bm_stu_bm" cascade constraints;

drop table "ykt_bm"."bm_student" cascade constraints;

drop table "ykt_bm"."bm_test" cascade constraints;

drop table "ykt_bm"."bm_test_cat" cascade constraints;

drop table "ykt_bm"."bm_test_publish" cascade constraints;

/*==============================================================*/
/* Table: "bm_access_info"                                      */
/*==============================================================*/
create table "ykt_bm"."bm_access_info"  (
   "id"                 VARCHAR(32)                     not null,
   "user_name"          VARCHAR(32),
   "true_name"          VARCHAR(60),
   "access_date"        VARCHAR(10),
   "access_time"        VARCHAR(8),
   "ip_address"         VARCHAR(20),
   constraint PK_BM_ACCESS primary key ("id")
);

/*==============================================================*/
/* Table: "bm_department"                                       */
/*==============================================================*/
create table "ykt_bm"."bm_department"  (
   "dept_code"          VARCHAR(20)                     not null,
   "dept_name"          VARCHAR(100),
   "soryby"             FLOAT,
   "reserve1"           VARCHAR(100),
   "reserve2"           VARCHAR(100),
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_DEPT primary key ("dept_code")
);

/*==============================================================*/
/* Table: "bm_major"                                            */
/*==============================================================*/
create table "ykt_bm"."bm_major"  (
   "major_code"         VARCHAR(20)                     not null,
   "major_name"         VARCHAR(100),
   "in_dept"            VARCHAR(20),
   "sortby"             FLOAT,
   "reserve1"           VARCHAR(100),
   "reserve2"           VARCHAR(100),
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_MAJOR primary key ("major_code")
);

/*==============================================================*/
/* Table: "bm_stu_bm"                                           */
/*==============================================================*/
create table "ykt_bm"."bm_stu_bm"  (
   "student_no"         VARCHAR(20)                     not null,
   "test_id"            VARCHAR(32),
   "if_bm"              CHARACTER(1),
   "bm_time"            TIMESTAMP,
   "if_pay"             CHARACTER(1),
   "fee_payed"          NUMBER(9,2),
   "pay_time"           TIMESTAMP,
   constraint PK_BM_STU_BM primary key ("student_no")
);

/*==============================================================*/
/* Table: "bm_student"                                          */
/*==============================================================*/
create table "ykt_bm"."bm_student"  (
   "student_no"         VARCHAR(20)                     not null,
   "stu_name"           VARCHAR(60),
   "gender"             VARCHAR(4),
   "enroll_year"        VARCHAR(4),
   "dept_name"          VARCHAR(100),
   "major_name"         VARCHAR(100),
   "cur_grade"          VARCHAR(20),
   "cur_class"          VARCHAR(60),
   "id_type"            VARCHAR(20),
   "id_card"            VARCHAR(20),
   "email"              VARCHAR(60),
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_STUDENT primary key ("student_no")
);

/*==============================================================*/
/* Table: "bm_test"                                             */
/*==============================================================*/
create table "ykt_bm"."bm_test"  (
   "id"                 VARCHAR(32)                     not null,
   "test_cat_id"        VARCHAR(32),
   "bm_begin_date"      VARCHAR(10),
   "bm_begin_time"      VARCHAR(8),
   "bm_end_date"        VARCHAR(10),
   "bm_end_time"        VARCHAR(8),
   "test_date"          VARCHAR(10),
   "test_begin_time"    VARCHAR(8),
   "test_end_time"      VARCHAR(8),
   "test_memo"          VARCHAR(500),
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_TEST primary key ("id")
);

/*==============================================================*/
/* Table: "bm_test_cat"                                         */
/*==============================================================*/
create table "ykt_bm"."bm_test_cat"  (
   "id"                 VARCHAR(32)                     not null,
   "test_cat_name"      VARCHAR(100),
   "if_fee"             CHARACTER(1),
   "fee"                NUMBER(9,2),
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_TEST_CAT primary key ("id")
);

/*==============================================================*/
/* Table: "bm_test_publish"                                     */
/*==============================================================*/
create table "ykt_bm"."bm_test_publish"  (
   "id"                 VARCHAR(32)                     not null,
   "title"              VARCHAR(200),
   "body"               CLOB,
   "creator"            VARCHAR(32),
   "create_time"        TIMESTAMP,
   "updator"            VARCHAR(32),
   "update_time"        TIMESTAMP,
   constraint PK_BM_TEST_PUB primary key ("id")
);

alter table "ykt_bm"."bm_test"
   add constraint FK_TEST foreign key ("test_cat_id")
      references "ykt_bm"."bm_test_cat" ("id");

