alter table t_bank add (GETBANKFILE   CHAR(1) default 0);
comment on column t_bank.GETBANKFILE  is '1:������ȡ���ж����ļ�';