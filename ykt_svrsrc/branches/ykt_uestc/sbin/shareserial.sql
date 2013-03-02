insert into ykt_cur.t_tradeserial_share(stuemp_no,card_id,tx_date ,total_amount,elect_amount,show_amount)
select '' as stuemp_no, a.card_id,a.enteract_date as tx_date,a.sum_trade_fee as 
total_amount,b.sum_trade_fee as elect_amount ,'' as show_amount
from
(select card_id,enteract_date,sum(trade_fee) as sum_trade_fee
from ykt_cur.t_tif_tradeserial where serial_type=930031 and serial_state=2
group by card_id,enteract_date) a left outer join
(select card_id,enteract_date, sum(trade_fee) as sum_trade_fee 
from t_tif_tradeserial t
 where serial_type=847134
  and serial_state=2
 group by card_id,enteract_date) b
 on a.card_id=b.card_id 
 order by a.card_id;
