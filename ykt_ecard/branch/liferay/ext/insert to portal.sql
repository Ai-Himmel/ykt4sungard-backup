--这个是部门报表 需要单独运行的报表
Insert into ykt_portal.T_RCSTATDATA
select cardno,meal,transdate,sum(amount) amount
from 
(   select t.transdate,
        to_char(to_date(SUBSTR(t.transdate,1,4)||'-'||SUBSTR(t.transdate,5,2)||'-'||SUBSTR(t.transdate,7,2),'yyyy-mm-dd'),'day') week,
        (case when transtime <'093000' then 'bk' 
              when (transtime >='093000' and transtime<'150000') then 'lun' 
              else 'sup' end) as meal,
        t.cardno,t.devphyid,t.AMOUNT,t.transcode 
    from ykt_cur.t_posdtl t 
    where status='3' and t.amount>0 and transdate >='yyyymmdd' and transdate<='yyyymmdd'
)
where week in ('星期一','星期二','星期三','星期四','星期五')
group by cardno,meal,transdate

commit;


--这个应该是后台升级的报表
insert into ykt_portal.t_rpttermledger(accdate,termid,subjno,accno,transtype,summary,transcnt,dramt,cramt)
select accdate,termid,subjno,accno,transtype,summary,count(summary),sum((2-dcflag)*amount) dramt,
sum((dcflag-1)*amount) cramt from ykt_cur.v_accdtl  where accdate>='yyyymmdd' and accdate<='yyyymmdd' and subjno='2004'
group by accdate,termid,subjno,accno,transtype,summary

commit;

--这个是部门报表 需要单独运行的报表
insert into ykt_portal.t_rptdeptledger(accdate,deptcode,subjno,transtype,summary,transcnt,dramt,cramt)
select accdate,deptcode,subjno,transtype,summary,count(summary),sum(dramt) dramt,sum(cramt) cramt 
from (select a.accdate,a.subjno,(2-dcflag)*a.amount dramt,(dcflag-1)*amount cramt,a.transtype,a.summary,c.deptcode 
from ykt_cur.t_accdtl a,ykt_cur.t_card b,ykt_cur.t_customer c 
where a.accdate='yyyymmdd' and a.accno=b.accno and b.custid=c.custid and c.deptcode is not null )
group by accdate,deptcode,subjno,transtype,summary;

commit;

