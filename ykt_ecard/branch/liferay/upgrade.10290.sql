-- ��¼��ykt_portal����������Ĭ�ϣ����޸�
connect ykt_portal/ykt4portal@yktdb;
grant update,delete on ykt_portal.user_ to ykt_cur;
-- ��¼��ykt_cur����������Ĭ�ϣ����޸�
connect ykt_cur/kingstar@yktdb;
-- ����trigger 
create or replace trigger ykt_cur.tg_customer
  after update on ykt_cur.t_customer  
  for each row when (new.stuempno!=old.stuempno)
declare
  userid number;
begin
  delete from ykt_portal.user_ where screenname = :old.stuempno;
end tg_customer;
/