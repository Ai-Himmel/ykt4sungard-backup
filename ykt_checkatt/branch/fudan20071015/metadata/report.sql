export to 'd:\a.del' of del  
9��ǰ������Ա��������
select count(att_date),cut_name from (

select att_date,cut_name 
  from (
  	   select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	   inner join   YKT_CK.T_CLERKINFO  ck
	   on ck.cust_id = cust.cut_id    
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))
  	   and(att_time>='060000' and att_time<='090000')
		union 
  select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	   and (cust.cut_name = ('������') or cust.cut_name =('�ſ�'))
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))
  	   and(att_time>='060000' and att_time<='090000')
		 )  as w  where  DAYOFWEEK_ISO(check_date) not in (6,7)
		) w group by cut_name order by  cut_name 

  �����յĹ���ʱ��
	   select cut_name,count(att_date) �� from (
	   select att_date, cut_name from (
       select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	   inner join   YKT_CK.T_CLERKINFO  ck
	   on ck.cust_id = cust.cut_id    
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))	   
	   ) w where DAYOFWEEK_ISO(check_date) not in (6,7)
	   group by att_date,cut_name  )y
	   group by cut_name order by cut_name

  ������ˢ��2��
  select cut_name,count(att_date)  from (
	  select  att_date, cut_name,count(att_time) times from (
      select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	   inner join   YKT_CK.T_CLERKINFO  ck
	   on ck.cust_id = cust.cut_id    
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))
	   )w where DAYOFWEEK_ISO(check_date) not in (6,7)
	   group by att_date,cut_name having count(att_time) >=2) y group by cut_name order by  cut_name 


��������
select  cut_name ,sum(ldays) from (
select cust_id , cut_name, case   when  leavedays=0 then 1 else leavedays end  as ldays from (
select cust_id , cut_name,days(enddate)-days(begindate)  leavedays  from (
select  lea.cust_id ,cust.cut_name,substr(lea.leave_begindate,1,4)|| '-' ||substr(lea.leave_begindate,5,2) || '-'||substr(lea.leave_begindate,7,2)  begindate 

,substr(lea.leave_enddate,1,4)|| '-' ||substr(lea.leave_enddate,5,2) || '-'||substr(lea.leave_enddate,7,2)  enddate
    from YKT_CK.T_REPORTLEAVE lea
   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = lea.cust_id  
	
  	   and leave_id ='1' and lea.leave_begindate>='20080101' and   ifagree='1')w)y)z
	   group by cut_name order by cut_name
	   
	   
	   
select cut_name,count(att_date)  from (
	  select  att_date, cut_name,count(att_time) times from (
      select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	  and cust.cut_id=214305
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))
	   )w 
	   group by att_date,cut_name having count(att_time) >=2) y group by cut_name order by  cut_name
	   
select cut_name,count(att_date) �� from (
	   select att_date, cut_name from (
       select att.CUST_ID, att_date, cut_name,att_time, substr(att_date,1,4)|| '-' ||substr(att_date,5,2) || '-'||substr(att_date,7,2)  as check_date
  	   from YKT_CK.T_ATTSERIAL att 
	   inner join ykt_cur.t_cif_customer   cust on cust.cut_id = att.cust_id  
	
	    and cust.cut_id=214305
  	   and  ( (att_date >='20080101' and att_date <='2008127')
  	   or(att_date >='20080219' and att_date<='20080714')
  	   or(att_date>='20080820' and att_date<='20081231'))	   
	   ) w 
	   group by att_date,cut_name  )y
	   group by cut_name order by cut_name	   