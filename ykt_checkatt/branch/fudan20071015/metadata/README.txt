使用oracle,自动增长字段要建立sequence
-- Create sequence 
create sequence YKT_CK.S_T_ATTSERIAL_RECORD
minvalue 1
maxvalue 999999999999999999999999999
start with 1
increment by 1
cache 20;


使用不同的数据库要修改Tattserialrecord

修改org.king.check.Constants中的数据库类型