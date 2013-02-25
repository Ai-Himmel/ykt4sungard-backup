--��ס�˿ڡ�������ű�
--���ߣ����Ա�
-- $Id: testscript.sql 3 2003-11-17 08:45:14Z cash $

--drop sequence b_zhuhu_seq;
create sequence b_zhuhu_seq;

--drop table b_zhuhu;
/**
 *ס�������  b_zhuhu
 */
create table b_zhuhu(                                                  
	bzhh_id 		integer default nextval('b_zhuhu_seq'),		--@������ϵͳ���
	bzhh_sect		varchar(2) default getsysparam('SectId'),	--@�������
	bzhh_country	varchar(30),		--@�壨�ӣ�ί��
	bzhh_group		varchar(3),			--@�壨�ӣ�С��	
	bzhh_doorno		varchar(6),			--@�����
	bzhh_remark		varchar(100),   	--@��ע 
	primary key(bzhh_id,bzhh_sect)
);

--drop sequence b_changzhurenkou_seq;
create sequence b_changzhurenkou_seq;
--drop table b_changzhurenkou;
/**
 *��ס�˿ڵǼǱ�  b_changzhurenkou
 */
create table b_changzhurenkou(
	bczrk_id				integer default nextval('b_changzhurenkou_seq'),--@������ϵͳid
	bczrk_sect				varchar(2)default getsysparam('SectId'),	--@������š�bzhh_sect
	bczrk_fid				integer,									--@ϵͳ��š�bzhh_id
	bczrk_relationflag		boolean default false,				--@�Դ��ж�Ψһ����������־
	bczrk_peoplealterflag	numeric(1, 0)default 0,--@0����,1����,2Ǩ��,3Ǩ��,4����Ӥ��,(�˿�������Ǩ����־)
	bczrk_relation			varchar(10),		--@�뻧����ϵ
	bczrk_name				varchar(20),		--@����
	bczrk_sex				varchar(2),			--@�Ա�
	bczrk_nation			varchar(10),		--@����
	bczrk_birthday			date,				--@��������
	bczrk_level				varchar(10),		--@�Ļ��̶�
	bczrk_marry				varchar(6),			--@����״��
	bczrk_firstmarry		date,				--@����ʱ��
	bczrk_singletondate		date,				--@�����֤ʱ��
	bczrk_alterreason		varchar(20),		--@�䶯���ԭ��
	bczrk_alterdate			date,				--@�䶯���ʱ��
	bczrk_mate				integer,			--@Ϊ�ѻ鸾Ůʱ�����ɷ�ID������ID����ʾ���ƣ�
	bczrk_remark			varchar(100),		--@��ע
    primary key(bczrk_id,bczrk_sect)
);
create index bczrk_name_ix on b_changzhurenkou(bczrk_name);
create index bczrk_sex_ix on b_changzhurenkou(bczrk_sex);

--drop sequence b_siwangrenyuan_seq;
create sequence b_siwangrenyuan_seq;
--drop table b_siwangrenyuan;
/**
 *������Ա����  b_siwangrenyuan
 */
create table b_siwangrenyuan(
	bswry_id			integer default nextval('b_siwangrenyuan_seq'),--@������ϵͳid
	bswry_sect			varchar(2)default getsysparam('SectId'),		--@������š�bzhh_sect
	bswry_fid 			integer,				--@ϵͳ��š�bzhh_id
	bswry_deathreason	varchar(10),			--@����ԭ��
	bswry_deathdate		date,					--@��������
	bswry_remark		varchar(200),			--@��ע
    primary key(bswry_id,bswry_sect)
);

--drop sequence b_qianchurenyuan_seq;
create sequence b_qianchurenyuan_seq;
--drop table b_qianchurenyuan;
/**
 *Ǩ����Ա���� b_qianchurenyuan
 */
create table b_qianchurenyuan(
	bqcry_id			integer default nextval('b_qianchurenyuan_seq'),--@������ϵͳid
	bqcry_sect			varchar(2) default getsysparam('SectId'),--@������š�bzhh_sect
	bqcry_fid			integer,				--@ϵͳ��š�bzhh_id
	bqcry_deathreason	date,					--@Ǩ������
	bqcry_moveaddr		varchar(60),			--@Ǩ���ص�
	bqcry_movereason	varchar(10),			--@Ǩ��ԭ��
	bqcry_remark		varchar(50),			--@��ע
    primary key(bqcry_id,bqcry_sect)
);

--drop sequence b_qianrurenyuan_seq;
create sequence b_qianrurenyuan_seq;
--drop table b_qianrurenyuan;
/**
 *Ǩ����Ա���� b_qianrurenyuan
 */
create table b_qianrurenyuan(
	bqrry_id			integer default nextval('b_qianrurenyuan_seq'),--@������ϵͳid
	bqrry_sect			varchar(2) default getsysparam('SectId'),--@������š�bzhh_sect
	bqrry_fid			integer,		--@ϵͳ��š�bzhh_id
	bqrry_movedate		date,			--@Ǩ��ʱ��
	bqrry_movereason	varchar(10),	--@Ǩ��ԭ��
	bqrry_remark		varchar(50),	--@��ע
	primary key(bqrry_id,bqrry_sect)
);



















     
     
     
     