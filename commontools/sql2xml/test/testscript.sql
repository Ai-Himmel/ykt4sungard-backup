--常住人口……建表脚本
--作者：刘以兵
-- $Id: testscript.sql 3 2003-11-17 08:45:14Z cash $

--drop sequence b_zhuhu_seq;
create sequence b_zhuhu_seq;

--drop table b_zhuhu;
/**
 *住户管理表  b_zhuhu
 */
create table b_zhuhu(                                                  
	bzhh_id 		integer default nextval('b_zhuhu_seq'),		--@自增长系统编号
	bzhh_sect		varchar(2) default getsysparam('SectId'),	--@地区编号
	bzhh_country	varchar(30),		--@村（居）委会
	bzhh_group		varchar(3),			--@村（居）小组	
	bzhh_doorno		varchar(6),			--@户编号
	bzhh_remark		varchar(100),   	--@备注 
	primary key(bzhh_id,bzhh_sect)
);

--drop sequence b_changzhurenkou_seq;
create sequence b_changzhurenkou_seq;
--drop table b_changzhurenkou;
/**
 *常住人口登记表  b_changzhurenkou
 */
create table b_changzhurenkou(
	bczrk_id				integer default nextval('b_changzhurenkou_seq'),--@自增长系统id
	bczrk_sect				varchar(2)default getsysparam('SectId'),	--@地区编号→bzhh_sect
	bczrk_fid				integer,									--@系统编号→bzhh_id
	bczrk_relationflag		boolean default false,				--@以此判断唯一户主户主标志
	bczrk_peoplealterflag	numeric(1, 0)default 0,--@0正常,1死亡,2迁出,3迁入,4新生婴儿,(人口死亡、迁出标志)
	bczrk_relation			varchar(10),		--@与户主关系
	bczrk_name				varchar(20),		--@姓名
	bczrk_sex				varchar(2),			--@性别
	bczrk_nation			varchar(10),		--@民族
	bczrk_birthday			date,				--@出生年月
	bczrk_level				varchar(10),		--@文化程度
	bczrk_marry				varchar(6),			--@婚姻状况
	bczrk_firstmarry		date,				--@初婚时间
	bczrk_singletondate		date,				--@领独生证时间
	bczrk_alterreason		varchar(20),		--@变动情况原因
	bczrk_alterdate			date,				--@变动情况时间
	bczrk_mate				integer,			--@为已婚妇女时必填丈夫ID（操作ID，显示名称）
	bczrk_remark			varchar(100),		--@备注
    primary key(bczrk_id,bczrk_sect)
);
create index bczrk_name_ix on b_changzhurenkou(bczrk_name);
create index bczrk_sex_ix on b_changzhurenkou(bczrk_sex);

--drop sequence b_siwangrenyuan_seq;
create sequence b_siwangrenyuan_seq;
--drop table b_siwangrenyuan;
/**
 *死亡人员管理  b_siwangrenyuan
 */
create table b_siwangrenyuan(
	bswry_id			integer default nextval('b_siwangrenyuan_seq'),--@自增长系统id
	bswry_sect			varchar(2)default getsysparam('SectId'),		--@地区编号→bzhh_sect
	bswry_fid 			integer,				--@系统编号→bzhh_id
	bswry_deathreason	varchar(10),			--@死亡原因
	bswry_deathdate		date,					--@死亡年月
	bswry_remark		varchar(200),			--@备注
    primary key(bswry_id,bswry_sect)
);

--drop sequence b_qianchurenyuan_seq;
create sequence b_qianchurenyuan_seq;
--drop table b_qianchurenyuan;
/**
 *迁出人员管理 b_qianchurenyuan
 */
create table b_qianchurenyuan(
	bqcry_id			integer default nextval('b_qianchurenyuan_seq'),--@自增长系统id
	bqcry_sect			varchar(2) default getsysparam('SectId'),--@地区编号→bzhh_sect
	bqcry_fid			integer,				--@系统编号→bzhh_id
	bqcry_deathreason	date,					--@迁出年月
	bqcry_moveaddr		varchar(60),			--@迁往地点
	bqcry_movereason	varchar(10),			--@迁出原因
	bqcry_remark		varchar(50),			--@备注
    primary key(bqcry_id,bqcry_sect)
);

--drop sequence b_qianrurenyuan_seq;
create sequence b_qianrurenyuan_seq;
--drop table b_qianrurenyuan;
/**
 *迁入人员管理 b_qianrurenyuan
 */
create table b_qianrurenyuan(
	bqrry_id			integer default nextval('b_qianrurenyuan_seq'),--@自增长系统id
	bqrry_sect			varchar(2) default getsysparam('SectId'),--@地区编号→bzhh_sect
	bqrry_fid			integer,		--@系统编号→bzhh_id
	bqrry_movedate		date,			--@迁入时间
	bqrry_movereason	varchar(10),	--@迁入原因
	bqrry_remark		varchar(50),	--@备注
	primary key(bqrry_id,bqrry_sect)
);



















     
     
     
     