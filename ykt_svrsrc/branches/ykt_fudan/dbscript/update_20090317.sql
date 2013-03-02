--������ű�t_pif_carddtl t_pif_cardbook,�޸�һ�ű� t_pif_card

--ȡ�����������ˮ��ʹ��
insert into YKT_CUR.T_PIF_SYSKEY values ('T_PIF_CARDDTL','��Ƭ���������',0,999999999,'0');

--��������ֵ�
insert into YKT_CUR.T_PIF_DICTIONARY values (92,'1','����п�״̬','δʹ��');
insert into YKT_CUR.T_PIF_DICTIONARY values (92,'2','����п�״̬','��ʹ��');
insert into YKT_CUR.T_PIF_DICTIONARY values (92,'3','����п�״̬','����');
insert into YKT_CUR.T_PIF_DICTIONARY values (93,'0','��Ƭ��ԭ��','��Ϊ��');
insert into YKT_CUR.T_PIF_DICTIONARY values (93,'1','��Ƭ��ԭ��','����������');

CREATE TABLE YKT_CUR.T_PIF_CARDBOOK
 (SHOWCARDNO  VARCHAR(10)     NOT NULL,
  CARDTYPE    INTEGER         NOT NULL,
  CARDPHYID   VARCHAR(8),
  OPERCODE    VARCHAR(10)     NOT NULL,
  PUTOPERCODE VARCHAR(10),
  BATCHNO     VARCHAR(30),
  GETDATE     VARCHAR(8),
  USEDATE     VARCHAR(8),
  RECLAIMDATE VARCHAR(8),
  USESTATUS   CHARACTER(1)    NOT NULL
 )
  DATA CAPTURE NONE
  IN USERSPACE1;

ALTER TABLE YKT_CUR.T_PIF_CARDBOOK
  LOCKSIZE ROW
  APPEND OFF
  NOT VOLATILE;

ALTER TABLE YKT_CUR.T_PIF_CARDBOOK
  ADD CONSTRAINT SQL081205154420400 PRIMARY KEY
   (SHOWCARDNO
   );


CREATE TABLE YKT_CUR.T_PIF_CARDDTL
 (ACCDATE    VARCHAR(8)      NOT NULL,
  ACCTIME    VARCHAR(6),
  TERMID     INTEGER         NOT NULL,
  TERMSEQNO  INTEGER         NOT NULL,
  BRANCHNO   VARCHAR(30),
  OPERCODE   VARCHAR(10)     NOT NULL,
  CARDTYPE   INTEGER,
  USETYPE    CHARACTER(1)    NOT NULL,
  SUMMARY    VARCHAR(60),
  INOUTFLAG  INTEGER,
  TRANSCNT   INTEGER,
  CARDPHYID  VARCHAR(8),
  SHOWCARDNO VARCHAR(10)
 )
  DATA CAPTURE NONE
  IN USERSPACE1;

ALTER TABLE YKT_CUR.T_PIF_CARDDTL
  LOCKSIZE ROW
  APPEND OFF
  NOT VOLATILE;

ALTER TABLE YKT_CUR.T_PIF_CARDDTL
  ADD CONSTRAINT SQL081205155151580 PRIMARY KEY
   (ACCDATE,
    TERMID,
    TERMSEQNO,
    OPERCODE,
    USETYPE
   );

t_pif_card ��������ֶΣ�
  BAD_STATUS     CHARACTER(1)
  BAD_TYPE       CHARACTER(1)

--������ʽ�������棬Ϊ�˻��տ�
insert into YKT_CUR.T_PIF_CARDBOOK 
select showid ,type_id,physical_no,'system','','','20090317','','','2' from YKT_CUR.t_pif_card where state_id != '2000' and type_id != 1;
