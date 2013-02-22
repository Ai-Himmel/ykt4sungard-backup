--==============================================================
-- DBMS name:      IBM DB2 UDB 8.x Common Server
-- Created on:     2006-12-1 15:23:09
--==============================================================


alter table schoolrep.wl_arrival
   drop foreign key F_Ref_arl;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_21;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_34;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_35;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_36;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_81;

alter table schoolrep.wl_arrival_detail
   drop foreign key F_Ref_88;

alter table schoolrep.wl_arrivalplace_info
   drop foreign key F_Ref_38;

alter table schoolrep.wl_arrivalplace_info
   drop foreign key F_Ref_39;

alter table schoolrep.wl_arrivalplace_info
   drop foreign key F_Ref_40;

alter table schoolrep.wl_arrivalplace_info
   drop foreign key F_Ref_41;

alter table schoolrep.wl_arrivalplace_info
   drop foreign key F_Ref_83;

alter table schoolrep.wl_building_info
   drop foreign key F_Ref_28;

alter table schoolrep.wl_building_info
   drop foreign key F_Ref_86;

alter table schoolrep.wl_cabinet_info
   drop foreign key F_Ref_27;

alter table schoolrep.wl_cabinet_info
   drop foreign key F_Ref_87;

alter table schoolrep.wl_check_process
   drop foreign key F_Ref_82;

alter table schoolrep.wl_dept_dl
   drop foreign key F_Ref_45;

alter table schoolrep.wl_dept_otherperson_info
   drop foreign key F_Ref_80;

alter table schoolrep.wl_dept_otherperson_info
   drop foreign key F_Ref_81;

alter table schoolrep.wl_dept_wlmc
   drop foreign key F_Ref_20;

alter table schoolrep.wl_dept_wlmc
   drop foreign key F_Ref_43;

alter table schoolrep.wl_dept_xl
   drop foreign key F_Ref_23;

alter table schoolrep.wl_dept_xl
   drop foreign key F_Ref_44;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_11;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_68;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_69;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_70;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_71;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_72;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_73;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_74;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_75;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_76;

alter table schoolrep.wl_dispatch_rcd
   drop foreign key F_Ref_9;

alter table schoolrep.wl_eqp_abandon_rcd
   drop foreign key F_Ref_16;

alter table schoolrep.wl_eqp_colcheck_config
   drop foreign key F_Ref_46;

alter table schoolrep.wl_eqp_detailinfo
   drop foreign key F_Ref_3;

alter table schoolrep.wl_eqp_dispatch_apply
   drop foreign key F_Ref_12;

alter table schoolrep.wl_eqp_dispatch_apply
   drop foreign key F_Ref_22;

alter table schoolrep.wl_eqp_dispatch_apply
   drop foreign key F_Ref_24;

alter table schoolrep.wl_eqp_dispatch_apply
   drop foreign key F_Ref_77;

alter table schoolrep.wl_eqp_dispatch_apply
   drop foreign key F_Ref_78;

alter table schoolrep.wl_eqp_maintain_rcd
   drop foreign key F_Ref_13;

alter table schoolrep.wl_eqp_maintain_rcd
   drop foreign key F_Ref_79;

alter table schoolrep.wl_eqp_netcard_info
   drop foreign key F_Ref_5;

alter table schoolrep.wl_eqp_tginfo
   drop foreign key F_Ref_15;

alter table schoolrep.wl_eqp_tginfo
   drop foreign key F_Ref_67;

alter table schoolrep.wl_eqpinfo_change_rcd
   drop foreign key F_Ref_18;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_17;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_48;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_49;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_50;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_51;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_52;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_53;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_54;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_55;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_56;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_57;

alter table schoolrep.wl_equipment_info
   drop foreign key F_Ref_58;

alter table schoolrep.wl_history_rcd
   drop foreign key F_Ref_66;

alter table schoolrep.wl_history_rcd
   drop foreign key F_Ref_88;

alter table schoolrep.wl_history_rcd
   drop foreign key F_Ref_89;

alter table schoolrep.wl_process_config
   drop foreign key F_Ref_83;

alter table schoolrep.wl_process_config
   drop foreign key F_Ref_84;

alter table schoolrep.wl_purchase
   drop foreign key F_Ref_pur;

alter table schoolrep.wl_purchaseApp
   drop foreign key F_Ref_apy;

alter table schoolrep.wl_purchaseApp_goods
   drop foreign key F_Ref_30;

alter table schoolrep.wl_purchaseApp_goods
   drop foreign key F_Ref_31;

alter table schoolrep.wl_purchaseApp_goods
   drop foreign key F_Ref_82;

alter table schoolrep.wl_purchaseApp_goods
   drop foreign key F_wl_appl;

alter table schoolrep.wl_purchase_good
   drop foreign key F_Ref_84;

alter table schoolrep.wl_purchase_good
   drop foreign key F_Ref_86;

alter table schoolrep.wl_purchase_good
   drop foreign key F_Ref_87;

alter table schoolrep.wl_purchase_good
   drop foreign key F_Ref_88;

alter table schoolrep.wl_purchase_good
   drop foreign key F_Ref_89;

alter table schoolrep.wl_return_info
   drop foreign key F_Ref_25;

alter table schoolrep.wl_return_info
   drop foreign key F_Ref_4;

alter table schoolrep.wl_room_info
   drop foreign key F_Ref_26;

alter table schoolrep.wl_room_info
   drop foreign key F_Ref_85;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref83;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_19;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_59;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_60;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_61;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_62;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_63;

alter table schoolrep.wl_yhp_kucuninfo
   drop foreign key F_Ref_64;

drop table schoolrep.com_dictionary;

drop table schoolrep.wl_arrival;

drop table schoolrep.wl_arrival_detail;

drop table schoolrep.wl_arrivalplace_info;

drop table schoolrep.wl_building_info;

drop table schoolrep.wl_cabinet_info;

drop table schoolrep.wl_check_process;

drop table schoolrep.wl_dept_companyinfo;

drop table schoolrep.wl_dept_dl;

drop table schoolrep.wl_dept_info;

drop table schoolrep.wl_dept_otherperson_info;

drop table schoolrep.wl_dept_role;

drop table schoolrep.wl_dept_wlmc;

drop table schoolrep.wl_dept_xl;

drop table schoolrep.wl_dictionary;

drop table schoolrep.wl_dispatch_rcd;

drop table schoolrep.wl_eqp_abandon_rcd;

drop table schoolrep.wl_eqp_colcheck_config;

drop table schoolrep.wl_eqp_detailinfo;

drop table schoolrep.wl_eqp_dispatch_apply;

drop table schoolrep.wl_eqp_maintain_rcd;

drop table schoolrep.wl_eqp_netcard_info;

drop table schoolrep.wl_eqp_tginfo;

drop table schoolrep.wl_eqpinfo_change_rcd;

drop table schoolrep.wl_equipment_info;

drop table schoolrep.wl_history_rcd;

drop table schoolrep.wl_process_config;

drop table schoolrep.wl_purchase;

drop table schoolrep.wl_purchaseApp;

drop table schoolrep.wl_purchaseApp_goods;

drop table schoolrep.wl_purchase_good;

drop table schoolrep.wl_return_info;

drop table schoolrep.wl_room_info;

drop table schoolrep.wl_yhp_kucuninfo;

--==============================================================
-- Table: com_dictionary
--==============================================================
create table schoolrep.com_dictionary
(
   dict_no            INTEGER                not null,
   dict_name          VARCHAR(30)            not null,
   dict_value         VARCHAR(40),
   dict_caption       VARCHAR(40),
   dict_parent        VARCHAR(30),
   dict_sort          VARCHAR(30),
   dict_parent1       VARCHAR(30),
   dict_avail         INTEGER,
   constraint P_Key_1 primary key (dict_no, dict_name)
);

comment on table schoolrep.com_dictionary is
'Êý¾Ý×Öµä±í';

--==============================================================
-- Table: wl_arrival
--==============================================================
create table schoolrep.wl_arrival
(
   id                 VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   memo               VARCHAR(500),
   dept_id            VARCHAR(32)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_arrival_detail
--==============================================================
create table schoolrep.wl_arrival_detail
(
   id                 VARCHAR(32)            not null,
   arrival_id         VARCHAR(32)            not null,
   mtl_name_id        VARCHAR(32)            not null,
   mtl_model          VARCHAR(200),
   mtl_spn            VARCHAR(200),
   if_appendix        CHARACTER(1)           not null default '0',
   usage_category     VARCHAR(32),
   mtl_usage          VARCHAR(200),
   procure_date       VARCHAR(8),
   pro_person_id      VARCHAR(32),
   procure_price      DECIMAL(18,2),
   warranty_period    FLOAT,
   arrival_num        INTEGER                not null,
   mtl_company_id     VARCHAR(32),
   mtl_merchant_id    VARCHAR(32),
   mtl_maintainer     VARCHAR(32),
   pur_dtl_id         VARCHAR(32),
   fund_source        VARCHAR(200),
   receipt_no         VARCHAR(200),
   contract_no        VARCHAR(200),
   account_date       VARCHAR(8),
   receipt_date       VARCHAR(8),
   arrival_date       VARCHAR(8)             not null,
   arr_person_id      VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   tk_person_id       VARCHAR(32),
   memo               VARCHAR(500),
   mtl_source         VARCHAR(32)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_arrivalplace_info
--==============================================================
create table schoolrep.wl_arrivalplace_info
(
   id                 INTEGER                not null,
   avl_dtl_id         VARCHAR(32)            not null,
   place_num          INTEGER                not null,
   pf_category_id     VARCHAR(32)            not null,
   college_area_id    VARCHAR(32),
   building_id        VARCHAR(32),
   room_name          VARCHAR(32),
   place              VARCHAR(200),
   manager_id         VARCHAR(32)            not null,
   memo               VARCHAR(500),
   rcd_person_id      VARCHAR(32)            not null,
   record_date        VARCHAR(8)             not null,
   manager_check      CHARACTER(1)           not null,
   apply_state        CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_building_info
--==============================================================
create table schoolrep.wl_building_info
(
   id                 VARCHAR(32)            not null,
   lymc               VARCHAR(200)           not null,
   college_area_id    VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   state              CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_cabinet_info
--==============================================================
create table schoolrep.wl_cabinet_info
(
   id                 VARCHAR(32)            not null,
   cabinetmc          VARCHAR(200)           not null,
   room_id            VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   state              CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_check_process
--==============================================================
create table schoolrep.wl_check_process
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   record_id          VARCHAR(32)            not null,
   serial             INTEGER                not null,
   check_person_id    VARCHAR(32)            not null,
   check_group_id     VARCHAR(32)            not null,
   check_state        CHARACTER(2)           not null,
   check_memo         VARCHAR(500),
   check_time         TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_companyinfo
--==============================================================
create table schoolrep.wl_dept_companyinfo
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   company_type       CHARACTER(1)           not null,
   company_name       VARCHAR(200)           not null,
   cmy_brief_name     VARCHAR(100)           not null,
   address            VARCHAR(300),
   post_code          CHARACTER(6),
   website            VARCHAR(200),
   bank_no            VARCHAR(100),
   representative     VARCHAR(32),
   customer_no        VARCHAR(32),
   contact_person     VARCHAR(32),
   telephone          VARCHAR(100),
   mobile_phone       VARCHAR(100),
   email_address      VARCHAR(200),
   fax_address        VARCHAR(200),
   memo               VARCHAR(500),
   state              CHARACTER(2)           not null,
   updator_id         VARCHAR(32)            not null,
   update_time        TIMESTAMP              not null,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_dl
--==============================================================
create table schoolrep.wl_dept_dl
(
   id                 VARCHAR(32)            not null,
   depti_id           VARCHAR(32)            not null,
   dlbh               VARCHAR(20)            not null,
   dlmc               VARCHAR(100)           not null,
   wzsx               VARCHAR(50)            not null default '1',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_info
--==============================================================
create table schoolrep.wl_dept_info
(
   dept_code          VARCHAR(10)            not null,
   is_academy         CHARACTER(1),
   dept_name          VARCHAR(100),
   e_name             VARCHAR(100),
   parentdept_code    VARCHAR(10),
   dept_level         INTEGER,
   is_availability    CHARACTER(1),
   comments           VARCHAR(100),
   dwglm              VARCHAR(6),
   reserve1           VARCHAR(100),
   reserve2           VARCHAR(100),
   reserve3           VARCHAR(100),
   constraint P_Key_1 primary key (dept_code)
);

--==============================================================
-- Table: wl_dept_otherperson_info
--==============================================================
create table schoolrep.wl_dept_otherperson_info
(
   id                 VARCHAR(32)            not null,
   employee_no        VARCHAR(32),
   person_name        VARCHAR(100),
   gender             CHARACTER(1),
   dept_id            VARCHAR(32)            not null,
   telephone          VARCHAR(100),
   mobile_phone       VARCHAR(100),
   email_address      VARCHAR(100),
   indept_id          VARCHAR(32),
   memo               VARCHAR(500),
   state              CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_role
--==============================================================
create table schoolrep.wl_dept_role
(
   id                 VARCHAR(32)            not null,
   role_id            VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   isLimit            CHARACTER(1)           not null default '0',
   updateperson       VARCHAR(32),
   updatedate         TIMESTAMP,
   account_id         VARCHAR(32),
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_wlmc
--==============================================================
create table schoolrep.wl_dept_wlmc
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   wlmc               VARCHAR(200)           not null,
   wldw               VARCHAR(10),
   memo               VARCHAR(200),
   xlbh               VARCHAR(20)            not null,
   state              VARCHAR(50)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dept_xl
--==============================================================
create table schoolrep.wl_dept_xl
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   lbbh               VARCHAR(20)            not null,
   lbmc               VARCHAR(100)           not null,
   jldw               VARCHAR(50),
   wzsx               VARCHAR(50)            not null default '1',
   dlbh               VARCHAR(20)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_dictionary
--==============================================================
create table schoolrep.wl_dictionary
(
   dict_value         VARCHAR(32)            not null,
   dict_name          VARCHAR(100),
   dict_caption       VARCHAR(100)           not null,
   dict_parent_no     INTEGER,
   dict_prt_value     VARCHAR(32),
   is_valid           CHARACTER(1)           not null default '1',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (dict_value)
);

--==============================================================
-- Table: wl_dispatch_rcd
--==============================================================
create table schoolrep.wl_dispatch_rcd
(
   id                 VARCHAR(32)            not null,
   material_id        VARCHAR(32)            not null,
   o_pfcategory_id    VARCHAR(32)            not null,
   o_cll_id           VARCHAR(32),
   o_bd_id            VARCHAR(32),
   o_roomname_id      VARCHAR(32),
   o_place            VARCHAR(200),
   o_manager_id       VARCHAR(32)            not null,
   pf_num             INTEGER                not null,
   begin_no           VARCHAR(100),
   end_no             VARCHAR(100),
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   pf_reason_code     CHARACTER(4)           not null,
   apply_person_id    VARCHAR(32)            not null,
   usage_category     VARCHAR(32),
   pf_usage           VARCHAR(200),
   n_pfcategory_id    VARCHAR(32)            not null,
   n_clg_id           VARCHAR(32),
   n_bd_id            VARCHAR(32),
   n_roomname_id      VARCHAR(32),
   n_place            VARCHAR(200),
   n_manager_id       VARCHAR(32)            not null,
   manager_check      CHARACTER(1)           not null,
   memo               VARCHAR(500),
   act_person_id      VARCHAR(32),
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_eqp_abandon_rcd
--==============================================================
create table schoolrep.wl_eqp_abandon_rcd
(
   equipment_no       VARCHAR(32)            not null,
   abandon_reason     VARCHAR(200),
   if_complete        CHARACTER(1),
   memo               VARCHAR(500),
   apply_person_id    VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   apply_state        CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (equipment_no)
);

--==============================================================
-- Table: wl_eqp_colcheck_config
--==============================================================
create table schoolrep.wl_eqp_colcheck_config
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   table_name         VARCHAR(256)           not null,
   column_name        VARCHAR(256)           not null,
   serial             INTEGER                not null,
   check_person_id    VARCHAR(32),
   check_group_id     VARCHAR(32)            not null,
   memo               VARCHAR(500),
   updator_id         VARCHAR(32)            not null,
   update_time        TIMESTAMP              not null,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_eqp_detailinfo
--==============================================================
create table schoolrep.wl_eqp_detailinfo
(
   equipment_no       VARCHAR(32)            not null,
   cpu_info           VARCHAR(200),
   memory_info        VARCHAR(200),
   harddisk_info      VARCHAR(200),
   net_info           VARCHAR(200),
   powe_info          VARCHAR(200),
   op_system          VARCHAR(200),
   height             INTEGER,
   memo               VARCHAR(500),
   power_info         VARCHAR(200),
   length             VARCHAR(10),
   width              VARCHAR(10),
   kvm_use            VARCHAR(200),
   kvm_port           VARCHAR(200),
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (equipment_no)
);

--==============================================================
-- Table: wl_eqp_dispatch_apply
--==============================================================
create table schoolrep.wl_eqp_dispatch_apply
(
   id                 VARCHAR(32)            not null,
   equipment_no       VARCHAR(32)            not null,
   cabinet_no         VARCHAR(32),
   b_location         VARCHAR(10),
   e_location         VARCHAR(10),
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   apply_person_id    VARCHAR(32)            not null,
   memo               VARCHAR(500),
   act_person_id      VARCHAR(32),
   apply_state        CHARACTER(2)           not null,
   dispatch_id        VARCHAR(32)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   pre_apply_id       VARCHAR(32),
   next_apply_id      VARCHAR(32),
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_eqp_maintain_rcd
--==============================================================
create table schoolrep.wl_eqp_maintain_rcd
(
   id                 VARCHAR(32)            not null,
   equipment_no       VARCHAR(32)            not null,
   maintain_reason    VARCHAR(200),
   maintain_task      VARCHAR(300),
   down_date          VARCHAR(8)             not null,
   mtn_period         INTEGER,
   mtn_price          DECIMAL(18,2),
   apply_person_id    VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   begin_date         VARCHAR(8),
   end_date           VARCHAR(8),
   act_person_id      VARCHAR(32),
   maintainer_id      VARCHAR(32),
   maintain_price     DECIMAL(18,2),
   fund_source        VARCHAR(200),
   done               CHARACTER(1)           default '0',
   memo               VARCHAR(500),
   apply_state        CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_eqp_netcard_info
--==============================================================
create table schoolrep.wl_eqp_netcard_info
(
   id                 VARCHAR(32)            not null,
   equipment_no       VARCHAR(32)            not null,
   nc_usage           VARCHAR(200),
   ipv4_address       VARCHAR(200),
   ipv6_address       VARCHAR(200),
   mac_address        VARCHAR(200),
   transfer_ip        VARCHAR(32),
   transfer_port      VARCHAR(20),
   server_name1       VARCHAR(200),
   server_name2       VARCHAR(200),
   jumpline           VARCHAR(20),
   rate               VARCHAR(20),
   memo               VARCHAR(500),
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_eqp_tginfo
--==============================================================
create table schoolrep.wl_eqp_tginfo
(
   equipment_no       VARCHAR(32)            not null,
   tg_dept_id         VARCHAR(32)            not null,
   service_name       VARCHAR(200),
   service_port       VARCHAR(200),
   check_method       VARCHAR(200),
   if_start_auto      CHARACTER(1),
   if_mn_auto         CHARACTER(1),
   tg_date            VARCHAR(8)             not null,
   tg_grade           CHARACTER(1)           not null,
   memo               VARCHAR(500),
   rcd_person_id      VARCHAR(32),
   record_date        TIMESTAMP,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (equipment_no)
);

--==============================================================
-- Table: wl_eqpinfo_change_rcd
--==============================================================
create table schoolrep.wl_eqpinfo_change_rcd
(
   id                 VARCHAR(32)            not null,
   equipment_no       VARCHAR(32)            not null,
   change_table       VARCHAR(256)           not null,
   change_column      VARCHAR(256)           not null,
   original_value     VARCHAR(500),
   new_value          VARCHAR(500),
   check_state        CHARACTER(2)           not null,
   updator_id         VARCHAR(32)            not null,
   update_time        TIMESTAMP              not null,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_equipment_info
--==============================================================
create table schoolrep.wl_equipment_info
(
   equipment_no       VARCHAR(32)            not null,
   asset_no           VARCHAR(32),
   serial_no          VARCHAR(200),
   eqp_name_id        VARCHAR(32)            not null,
   eqp_model          VARCHAR(200),
   eqp_sption         VARCHAR(200),
   if_appendix        CHARACTER(1)           not null default '0',
   parent_eqp_no      VARCHAR(32),
   usage_category     VARCHAR(32),
   eqp_usage          VARCHAR(200),
   eqp_source_id      VARCHAR(32)            not null,
   maintainer_id      VARCHAR(32),
   dept_id            VARCHAR(32)            not null,
   pf_category_id     VARCHAR(32)            not null,
   college_area_id    VARCHAR(32),
   bd_name_id         VARCHAR(32),
   room_name_id       VARCHAR(32),
   place              VARCHAR(200),
   manager_id         VARCHAR(32)            not null,
   cabinet_no         VARCHAR(32),
   b_location         VARCHAR(10),
   e_location         VARCHAR(10),
   state              CHARACTER(4)           not null,
   memo               VARCHAR(500),
   arv_dtl_id         VARCHAR(32)            not null,
   is_valid           CHARACTER(1)           not null default '1',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (equipment_no)
);

--==============================================================
-- Table: wl_history_rcd
--==============================================================
create table schoolrep.wl_history_rcd
(
   id                 VARCHAR(32)            not null,
   material_no        VARCHAR(32)            not null,
   apply_type         VARCHAR(32)            not null,
   apply_id           VARCHAR(32)            not null,
   operator_id        VARCHAR(32)            not null,
   operate_time       TIMESTAMP              not null,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_process_config
--==============================================================
create table schoolrep.wl_process_config
(
   id                 VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   apply_name         VARCHAR(200)           not null,
   pf_category_id     VARCHAR(32)            not null,
   inorout            CHARACTER(1)           not null,
   serial             INTEGER                not null,
   check_person_id    VARCHAR(32),
   check_group_id     VARCHAR(32)            not null,
   memo               VARCHAR(500),
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_purchase
--==============================================================
create table schoolrep.wl_purchase
(
   procure_id         VARCHAR(32)            not null,
   pur_startdate      VARCHAR(8),
   memo               VARCHAR(500),
   rcd_person_id      VARCHAR(32)            not null,
   state              CHARACTER(2)           not null,
   dept_id            VARCHAR(32)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   pur_enddate        VARCHAR(8),
   constraint P_Key_1 primary key (procure_id)
);

--==============================================================
-- Table: wl_purchaseApp
--==============================================================
create table schoolrep.wl_purchaseApp
(
   procure_id         VARCHAR(32)            not null,
   apply_pur_date     VARCHAR(8),
   memo               VARCHAR(500),
   apply_person_id    VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   apply_state        CHARACTER(2)           not null,
   if_finished        CHARACTER(1)           not null default '0',
   dept_id            VARCHAR(32)            not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (procure_id)
);

--==============================================================
-- Table: wl_purchaseApp_goods
--==============================================================
create table schoolrep.wl_purchaseApp_goods
(
   proc_dtl_id        VARCHAR(32)            not null,
   procure_id         VARCHAR(32)            not null,
   mtl_name_id        VARCHAR(32)            not null,
   mtl_model          VARCHAR(200),
   mtl_sption         VARCHAR(200),
   if_appendix        CHARACTER(1)           not null default '0',
   apply_num          INTEGER                not null,
   mtl_price          DECIMAL(18,2),
   mtl_company_id     VARCHAR(32),
   mtl_merchant_id    VARCHAR(32),
   usage_category     VARCHAR(32),
   mtl_usage          VARCHAR(200),
   apply_reason       VARCHAR(500),
   memo               VARCHAR(500),
   if_finished        CHARACTER(1)           not null default '0',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   state              CHARACTER(2),
   constraint P_Key_1 primary key (proc_dtl_id)
);

--==============================================================
-- Table: wl_purchase_good
--==============================================================
create table schoolrep.wl_purchase_good
(
   pur_dtl_id         VARCHAR(32)            not null,
   pur_id             VARCHAR(32)            not null,
   proc_dtl_id        VARCHAR(32),
   mtl_name_id        VARCHAR(32)            not null,
   mtl_model          VARCHAR(200),
   mtl_sption         VARCHAR(200),
   if_appendix        CHARACTER(1)           not null default '0',
   pur_num            INTEGER                not null,
   mtl_price          DECIMAL(18,2),
   mtl_company_id     VARCHAR(32),
   mtl_merchant_id    VARCHAR(32),
   usage_category     VARCHAR(32),
   mtl_usage          VARCHAR(200),
   apply_reason       VARCHAR(500),
   memo               VARCHAR(500),
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   state              CHARACTER(2),
   exp_arrTime        TIMESTAMP,
   ifreceiptavl       CHARACTER(1),
   ifaccount          CHARACTER(1),
   constraint P_Key_1 primary key (pur_dtl_id)
);

--==============================================================
-- Table: wl_return_info
--==============================================================
create table schoolrep.wl_return_info
(
   material_id        VARCHAR(32)            not null,
   return_reason      VARCHAR(200),
   memo               VARCHAR(500),
   rtn_person_id      VARCHAR(32)            not null,
   rcd_person_id      VARCHAR(32)            not null,
   record_date        TIMESTAMP              not null,
   return_date        VARCHAR(8),
   done               CHARACTER(1)           not null default '0',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (material_id)
);

--==============================================================
-- Table: wl_room_info
--==============================================================
create table schoolrep.wl_room_info
(
   id                 VARCHAR(32)            not null,
   roommc             VARCHAR(200)           not null,
   roomflag           CHARACTER(1)           not null,
   building_id        VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   state              CHARACTER(2)           not null,
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

--==============================================================
-- Table: wl_yhp_kucuninfo
--==============================================================
create table schoolrep.wl_yhp_kucuninfo
(
   id                 VARCHAR(32)            not null,
   yhp_id             VARCHAR(32)            not null,
   begin_no           VARCHAR(100),
   end_no             VARCHAR(100),
   usage_category     VARCHAR(32),
   yhp_usage          VARCHAR(200),
   yhp_source_id      VARCHAR(32)            not null,
   dept_id            VARCHAR(32)            not null,
   yhp_num            INTEGER                not null,
   cur_num            INTEGER                not null,
   pf_category_id     VARCHAR(32)            not null,
   college_area_id    VARCHAR(32),
   bd_name_id         VARCHAR(32),
   room_name_id       VARCHAR(32),
   place              VARCHAR(200),
   arv_dtl_id         VARCHAR(32)            not null,
   memo               VARCHAR(500),
   is_valid           CHARACTER(1)           not null default '1',
   updator_id         VARCHAR(32),
   update_time        TIMESTAMP,
   constraint P_Key_1 primary key (id)
);

alter table schoolrep.wl_arrival
   add constraint F_Ref_arl foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_21 foreign key (mtl_name_id)
      references schoolrep.wl_dept_wlmc (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_34 foreign key (mtl_company_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_35 foreign key (mtl_merchant_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_36 foreign key (mtl_maintainer)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_81 foreign key (arrival_id)
      references schoolrep.wl_arrival (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrival_detail
   add constraint F_Ref_88 foreign key (pur_dtl_id)
      references schoolrep.wl_purchase_good (pur_dtl_id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrivalplace_info
   add constraint F_Ref_38 foreign key (pf_category_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrivalplace_info
   add constraint F_Ref_39 foreign key (college_area_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrivalplace_info
   add constraint F_Ref_40 foreign key (building_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrivalplace_info
   add constraint F_Ref_41 foreign key (room_name)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_arrivalplace_info
   add constraint F_Ref_83 foreign key (avl_dtl_id)
      references schoolrep.wl_arrival_detail (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_building_info
   add constraint F_Ref_28 foreign key (college_area_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_building_info
   add constraint F_Ref_86 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_cabinet_info
   add constraint F_Ref_27 foreign key (room_id)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_cabinet_info
   add constraint F_Ref_87 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_check_process
   add constraint F_Ref_82 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_dl
   add constraint F_Ref_45 foreign key (depti_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_otherperson_info
   add constraint F_Ref_80 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_otherperson_info
   add constraint F_Ref_81 foreign key (indept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_wlmc
   add constraint F_Ref_20 foreign key (xlbh)
      references schoolrep.wl_dept_xl (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_wlmc
   add constraint F_Ref_43 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_xl
   add constraint F_Ref_23 foreign key (dlbh)
      references schoolrep.wl_dept_dl (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dept_xl
   add constraint F_Ref_44 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_11 foreign key (material_id)
      references schoolrep.wl_yhp_kucuninfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_68 foreign key (o_pfcategory_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_69 foreign key (o_cll_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_70 foreign key (o_bd_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_71 foreign key (o_roomname_id)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_72 foreign key (pf_reason_code)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_73 foreign key (n_pfcategory_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_74 foreign key (n_clg_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_75 foreign key (n_bd_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_76 foreign key (n_roomname_id)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_dispatch_rcd
   add constraint F_Ref_9 foreign key (material_id)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_abandon_rcd
   add constraint F_Ref_16 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_colcheck_config
   add constraint F_Ref_46 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_detailinfo
   add constraint F_Ref_3 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_dispatch_apply
   add constraint F_Ref_12 foreign key (dispatch_id)
      references schoolrep.wl_dispatch_rcd (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_dispatch_apply
   add constraint F_Ref_22 foreign key (pre_apply_id)
      references schoolrep.wl_eqp_dispatch_apply (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_dispatch_apply
   add constraint F_Ref_24 foreign key (next_apply_id)
      references schoolrep.wl_eqp_dispatch_apply (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_dispatch_apply
   add constraint F_Ref_77 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_dispatch_apply
   add constraint F_Ref_78 foreign key (cabinet_no)
      references schoolrep.wl_cabinet_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_maintain_rcd
   add constraint F_Ref_13 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_maintain_rcd
   add constraint F_Ref_79 foreign key (maintainer_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_netcard_info
   add constraint F_Ref_5 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_tginfo
   add constraint F_Ref_15 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqp_tginfo
   add constraint F_Ref_67 foreign key (tg_dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_eqpinfo_change_rcd
   add constraint F_Ref_18 foreign key (equipment_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_17 foreign key (arv_dtl_id)
      references schoolrep.wl_arrival_detail (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_48 foreign key (eqp_name_id)
      references schoolrep.wl_dept_wlmc (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_49 foreign key (parent_eqp_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_50 foreign key (maintainer_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_51 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_52 foreign key (pf_category_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_53 foreign key (college_area_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_54 foreign key (bd_name_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_55 foreign key (room_name_id)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_56 foreign key (cabinet_no)
      references schoolrep.wl_cabinet_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_57 foreign key (eqp_source_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_equipment_info
   add constraint F_Ref_58 foreign key (state)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_history_rcd
   add constraint F_Ref_66 foreign key (apply_type)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_history_rcd
   add constraint F_Ref_88 foreign key (material_no)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_history_rcd
   add constraint F_Ref_89 foreign key (material_no)
      references schoolrep.wl_yhp_kucuninfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_process_config
   add constraint F_Ref_83 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_process_config
   add constraint F_Ref_84 foreign key (pf_category_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase
   add constraint F_Ref_pur foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchaseApp
   add constraint F_Ref_apy foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchaseApp_goods
   add constraint F_Ref_30 foreign key (mtl_company_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchaseApp_goods
   add constraint F_Ref_31 foreign key (mtl_merchant_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchaseApp_goods
   add constraint F_Ref_82 foreign key (procure_id)
      references schoolrep.wl_purchaseApp (procure_id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchaseApp_goods
   add constraint F_wl_appl foreign key (mtl_name_id)
      references schoolrep.wl_dept_wlmc (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase_good
   add constraint F_Ref_84 foreign key (pur_id)
      references schoolrep.wl_purchase (procure_id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase_good
   add constraint F_Ref_86 foreign key (mtl_name_id)
      references schoolrep.wl_dept_wlmc (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase_good
   add constraint F_Ref_87 foreign key (mtl_company_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase_good
   add constraint F_Ref_88 foreign key (mtl_merchant_id)
      references schoolrep.wl_dept_companyinfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_purchase_good
   add constraint F_Ref_89 foreign key (proc_dtl_id)
      references schoolrep.wl_purchaseApp_goods (proc_dtl_id)
      on delete restrict on update restrict;

alter table schoolrep.wl_return_info
   add constraint F_Ref_25 foreign key (material_id)
      references schoolrep.wl_yhp_kucuninfo (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_return_info
   add constraint F_Ref_4 foreign key (material_id)
      references schoolrep.wl_equipment_info (equipment_no)
      on delete restrict on update restrict;

alter table schoolrep.wl_room_info
   add constraint F_Ref_26 foreign key (building_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_room_info
   add constraint F_Ref_85 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref83 foreign key (arv_dtl_id)
      references schoolrep.wl_arrival_detail (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_19 foreign key (yhp_id)
      references schoolrep.wl_dept_wlmc (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_59 foreign key (yhp_source_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_60 foreign key (dept_id)
      references schoolrep.wl_dept_info (dept_code)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_61 foreign key (pf_category_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_62 foreign key (college_area_id)
      references schoolrep.wl_dictionary (dict_value)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_63 foreign key (bd_name_id)
      references schoolrep.wl_building_info (id)
      on delete restrict on update restrict;

alter table schoolrep.wl_yhp_kucuninfo
   add constraint F_Ref_64 foreign key (room_name_id)
      references schoolrep.wl_room_info (id)
      on delete restrict on update restrict;

