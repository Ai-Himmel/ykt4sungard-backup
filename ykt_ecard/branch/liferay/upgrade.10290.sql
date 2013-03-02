-- 登录到ykt_portal，如果密码非默认，请修改
connect ykt_portal/ykt4portal@yktdb;
grant update,delete on ykt_portal.user_ to ykt_cur;
-- 登录到ykt_cur，如果密码非默认，请修改
connect ykt_cur/kingstar@yktdb;
-- 创建trigger 
create or replace trigger ykt_cur.tg_customer
  after update on ykt_cur.t_customer  
  for each row when (new.stuempno!=old.stuempno)
declare
  userid number;
begin
  delete from ykt_portal.user_ where screenname = :old.stuempno;
end tg_customer;
/