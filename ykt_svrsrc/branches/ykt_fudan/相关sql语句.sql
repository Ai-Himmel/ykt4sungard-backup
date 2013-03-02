-- 查询消费流水
select * from ykt_cur.v_urp_tradeserial v where stuemp_no='999997' and operate_date between '20100320' and '20100402' 
order by operate_date desc,operate_time desc fetch first 10 rows only with ur;

-- 查询门禁流水
select * from ykt_cur.v_urp_doortxdtl v where stuemp_no='08300270029' and tx_date between '20100329' and '20100402'
fetch first 10 rows only with ur;

-- 查询补助信息
select * from  ykt_cur.v_urp_subsidy where stuemp_no='0515090' order by tx_date desc with ur;

-- 查询门禁权限 
select *  from ykt_cur.v_urp_door_right where stuemp_no='08300130076'  with ur;

-- 查询账户金额 , 请在查询界面提示“由于数据传输到系统有延时，卡余额仅供参考”
select * from  ykt_cur.v_urp_account where stuemp_no='999999' with ur;

-- 抽取流水，抽取时按enteract_date进行抽取
-- stuemp_no  varchar(20) 学工号
-- cut_id	  integer 客户号
-- operate_date  varchar(8) 发生日期
-- operate_time  varchar(6) 发生时间
-- enteract_date varchar(8) 记账日期
-- enteract_time varchar(6) 记账时间
-- trade_fee     double     发生金额
-- device_name	 varchar(60) 设备名称
select stuemp_no,cut_id,operate_date,operate_time,enteract_date,enteract_time,trade_fee,device_Name
from ykt_cur.v_urp_serial2 where enteract_date='20100406' and stuemp_no='999997' with ur;

--- 用户名 fdurp 密码 415fduykt



---YKT_CUR.V_URP_TRADESERIAL
CREATE VIEW YKT_CUR.V_URP_TRADESERIAL
 (STUEMP_NO,
  CARD_ID,
  OPERATE_DATE,
  OPERATE_TIME,
  TRADE_FEE,
  DEVICE_NAME,
  SERIAL_TYPE
 )
  AS  select c.stuemp_no,h.card_id,h.operate_date,h.operate_time,h.trade_fee,
    d.device_name,p.trademsg as serial_type
  from ykt_cur.t_cif_customer c,ykt_cur.t_pif_device d,ykt_cur.t_pif_tradecode
    p, (
    select h1.customer_id,h1.device_id,h1.trade_fee,h1.serial_type,
        h1.operate_date,h1.operate_time,h1.card_id
      from ykt_cur.t_tif_tradeserial h1
      where serial_state=2
    union all
    select h2.customer_id,h2.device_id,h2.trade_fee,h2.serial_type,
        h2.operate_date,h2.operate_time,h2.card_id
      from ykt_his.t_tif_tradeserial_his h2
      where serial_state=2) h
  where c.cut_id=h.customer_id
    and h.device_id=d.device_id
    and h.serial_type=p.tradecode;
    
----YKT_CUR.V_URP_DOORTXDTL 
CREATE VIEW YKT_CUR.V_URP_DOORTXDTL
 (STUEMP_NO,
  CARD_ID,
  TX_DATE,
  TX_TIME,
  DEVICE_NAME,
  TX_MARK
 )
  AS  select c.stuemp_no,h.card_no,h.tx_date,h.tx_time,d.device_name,p.emsg
  from ykt_cur.t_pif_card a,ykt_cur.t_cif_customer c,ykt_cur.t_pif_device d ,
    ykt_cur.t_pif_errcode p, (
    select card_no,tx_date,tx_time,device_id,tx_mark
      from ykt_cur.t_door_txdtl
    union all
    select card_no,tx_date,tx_time,device_id,tx_mark
      from ykt_his.v_door_txdtl_his) h
  where c.cut_id=a.cosumer_id
    and a.card_id=h.card_no
    and h.device_id=d.devphy999_id
    and d.state_id<5
    and p.ecode=390000+h.tx_mark;
    
    
----YKT_CUR.V_URP_SUBSIDY
 CREATE VIEW YKT_CUR.V_URP_SUBSIDY
 (STUEMP_NO,
  CUST_ID,
  AMOUNT,
  TX_DATE,
  SUMMARY,
  STATUS
 )
  AS  select c.stuemp_no,h.cust_no,h.amount,h.tx_date,h.summary,h.status
  from ykt_cur.t_tif_subsidy h,ykt_cur.t_cif_customer c
  where h.cust_no=c.cut_id;
  
----YKT_CUR.V_URP_DOOR_RIGHT
CREATE VIEW YKT_CUR.V_URP_DOOR_RIGHT
 (STUEMP_NO,
  DEVICE_NAME,
  SEND_FLAG,
  STATUS
 )
  AS  select h.stuemp_no,p.device_name,h.send_flag,h.status
  from ykt_cur.t_door_device_cardlist h,ykt_cur.t_pif_device p
  where h.device_id=p.devphy999_id
    and p.state_id<5;
    
    
---YKT_CUR.V_URP_ACCOUNT
CREATE VIEW YKT_CUR.V_URP_ACCOUNT
 (STUEMP_NO,
  CARD_ID,
  STATE_ID,
  TYPE_ID,
  CARD_BALANCE
 )
  AS  select c.stuemp_no,p.card_id,t.state_id,t.type_id,p.card_balance
  from ykt_cur.t_cif_customer c,ykt_cur.t_aif_account p,ykt_cur.t_pif_card t
  where c.cut_id=p.customer_id
    and p.current_state=1
    and p.card_id=t.card_id;


----YKT_CUR.V_URP_SERIAL2
CREATE VIEW YKT_CUR.V_URP_SERIAL2
 (STUEMP_NO,
  CUT_ID,
  OPERATE_DATE,
  OPERATE_TIME,
  ENTERACT_DATE,
  ENTERACT_TIME,
  TRADE_FEE,
  DEVICE_NAME
 )
  AS  select c.stuemp_no,c.cut_id,h.operate_date,h.operate_time,h.enteract_date,
    h.enteract_time,h.trade_fee,p.device_name
  from ykt_his.t_tif_tradeserial_his h
    left join ykt_cur.t_pif_device p
    on ( h.device_id=p.device_id ),ykt_cur.t_cif_customer c
  where h.customer_id=c.cut_id
    and serial_state=2;