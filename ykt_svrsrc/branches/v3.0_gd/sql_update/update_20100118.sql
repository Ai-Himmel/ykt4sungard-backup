alter table YKT_CUR.T_CUSTOMER add CLASSNAME VARCHAR2(60);
-- Add comments to the columns 
comment on column T_CUSTOMER.CLASSNAME
  is '�༶����';
alter table YKT_CUR.T_CUSTOMERTMP add CLASSNAME VARCHAR2(60);
-- Add comments to the columns 
comment on column T_CUSTOMERTMP.CLASSNAME
  is '�༶����';
alter table YKT_CUR.T_CUSTOMERTMP add CUSTTYPENAME VARCHAR2(60);
-- Add comments to the columns 
comment on column YKT_CUR.T_CUSTOMERTMP.CUSTTYPENAME
  is '�ͻ���������';
alter table YKT_CUR.T_CARD modify CARDPHYID VARCHAR2(16);