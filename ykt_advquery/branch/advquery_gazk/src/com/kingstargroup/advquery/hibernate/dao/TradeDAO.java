package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

public class TradeDAO extends BasicDAO {
	
	private static TradeDAO _instance;
	
	public static TradeDAO getInstance() {
		if (_instance == null) {
			_instance = new TradeDAO();
		}
		return _instance;
	}
	
	public   String  getCustIdsByStuempNo(String  manIds){
		Session s = getSession();
		String cutids ="";
		try{
			
		StringBuffer sqlStr = new StringBuffer("");
		sqlStr.append(" select cut_id from ykt_cur.t_cif_customer where stuemp_no in ("+manIds+")");
	    SQLQuery q = s.createSQLQuery(sqlStr.toString());
	    q.addScalar("cut_id",Hibernate.INTEGER);
	    List list  = q.list();
	    
	    for(int i=0;i<list.size();i++){
	    	   Object obj =   list.get(i);
	    	   cutids = obj.toString()+","+cutids;
	    }
		  return cutids;
		}catch (HibernateException he) {
			
			return null;
		}	

	}
	
	public  List  getTradeTotal(String  manIds,String beginDate,String endDate){
		Session s = getSession();
		beginDate = beginDate.substring(0,4)+beginDate.substring(5,7)+beginDate.substring(8,10);
		endDate =endDate.substring(0,4)+endDate.substring(5,7)+endDate.substring(8,10);;
		StringBuffer sqlstr = new StringBuffer("");
		sqlstr.append(" select  sum(trade_fee) tradeFee,count(trade_fee) total ,c.cut_id cutId ,c.man_id  manId,c.cut_name cutName ")
		      .append(" from (select customer_id, operate_date ,trade_fee from   ykt_his.t_tif_tradeserial_his " )
		      .append(" where serial_type=930031 ")
		      .append("	and operate_date>='"+beginDate+"'")
		      .append(" and operate_date<='"+endDate+ "'")
		      .append(" union  ")
		      .append(" select customer_id,operate_date,trade_fee ")
		      .append(" from ykt_cur.t_tif_tradeserial log  where serial_type=930031 ")
		      .append("	and operate_date>='"+beginDate+"'")
		      .append(" and operate_date<='"+endDate+ "'")
		      .append(" )t ,ykt_cur.t_cif_customer c ")
		      .append(" where t.customer_id = c.cut_id  ")
		      .append(" and man_id in ( "+manIds+")")
		      .append(" group by  c.cut_id , c.man_id ,c.cut_name ")
		      .append(" order by  c.cut_id ");
		SQLQuery q  = s.createSQLQuery(sqlstr.toString());
		try{
			//q.addScalar("opeDate",Hibernate.STRING);
			q.addScalar("tradeFee",Hibernate.DOUBLE);
			q.addScalar("total", Hibernate.INTEGER);
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("manId", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			return q.list();
		 }catch (HibernateException he) {
			_log.error(he);
			return null;
		}		
	}
	
	//查询卡余额
	public List getCardBalance(String manids){
		Session s = getSession();
		StringBuffer sqlstr = new StringBuffer(" select c.cut_id cutId ,c.cut_name cutName ,c.man_id manId,a.card_balance cardBalance from  ")
		             .append(" ykt_cur.t_aif_account a ,ykt_cur.t_cif_customer c,ykt_cur.t_pif_card p  ")
		             .append(" where a.customer_id = c.cut_id ")
		             .append(" and p.card_id=a.card_id and p.cosumer_id = c.cut_id and p.state_id <>2000 ")
		             .append(" and c.man_id in ("+manids+")");
		SQLQuery q = s.createSQLQuery(sqlstr.toString());
		try{
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("manId", Hibernate.STRING);
			q.addScalar("cardBalance",Hibernate.DOUBLE);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}		
		
	}
	
	 
	//查询个人消费余额
	public List  getOutBalance(String   manids){
		Session s = getSession();
		StringBuffer   sqlStr = new  StringBuffer("");
		sqlStr.append(" select rankid,customer_id,c.cut_name cut_name,c.stuemp_no stuemp_no,Operate_Date,Operate_time,card_balance,c.man_id man_id from ( " )
		      .append(" select  row_number() over(partition by customer_id order by operate_date desc,operate_time desc ) rankid, ")
			  .append(" customer_id,Operate_Date,Operate_time,out_balance from ( " )
			  .append(" select customer_id,Operate_Date,Operate_time, out_balance ")
			  .append(" from ykt_his.t_tif_tradeserial_his his ")
			  .append(" where   his.serial_state = 2 and not (his.serial_type='930036' ) ")
			  .append(" union all  ")
			  .append(" select customer_id,Operate_Date,Operate_time, out_balance ")
			  .append("  from ykt_cur.t_tif_tradeserial log  ")
			  .append(" where ") 
			  .append(" log.serial_state = 2 and not (log.serial_type='930036')")
			  .append(" ) t )p  ,ykt_cur.t_cif_customer  c")
			  .append("  where p.customer_id=c.cut_id and  p.rankid=1 and man_id in("+manids+")");
		   SQLQuery q = s.createSQLQuery(sqlStr.toString());
		   try{
			   q.addScalar("rankid",Hibernate.INTEGER);
			   q.addScalar("customer_id",Hibernate.INTEGER);
			   q.addScalar("cut_name",Hibernate.STRING);
			   q.addScalar("stuemp_no",Hibernate.STRING);
			   q.addScalar("Operate_Date",Hibernate.STRING);
			   q.addScalar("Operate_time",Hibernate.STRING);
			   q.addScalar("card_balance",Hibernate.DOUBLE);
			   q.addScalar("man_id", Hibernate.STRING);
			   return q.list();
		
	} catch (HibernateException he) {
		_log.error(he);
		return null;
	}			         
  }
	
	//统计消费情况
	public List getMoreAccountDetail(String manids,String beginDate,String endDate)throws HibernateException{
		
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select log.OPERATE_DATE, log.OPERATE_TIME, dev.DEVICE_name, log.RECORD_OPER,log.COMMENTS,log.OP_FEE,log.new_fee,cust.cut_name ,cust.man_id ")
		.append(" from YKT_CUR.T_TIF_TRADELOG log,YKT_CUR.T_AIF_ACCOUNT acc ,YKT_CUR.T_CIF_CUSTOMER cust ,ykt_cur.t_pif_device dev")
		.append(" where log.ACT_ID=acc.ACCOUNT_ID and acc.CUSTOMER_ID=cust.CUT_ID and log.device_id=dev.device_Id and ")
		.append(" OPERATE_DATE>=:begindate and OPERATE_DATE <=:enddate and cust.man_id in("+manids+")")
		.append(" union all")
		.append(" select log.OPERATE_DATE, log.OPERATE_TIME, dev.DEVICE_name , log.RECORD_OPER,log.COMMENTS,log.OP_FEE ,log.new_fee,cust.cut_name ,cust.man_id ")
		.append(" from YKT_HIS.T_TIF_TRADELOG_HIS log,YKT_CUR.T_AIF_ACCOUNT acc ,YKT_CUR.T_CIF_CUSTOMER cust , ykt_cur.t_pif_device dev ")
		.append(" where log.ACT_ID=acc.ACCOUNT_ID and acc.CUSTOMER_ID=cust.CUT_ID and  log.device_id=dev.device_Id and ")
		.append(" log.BAK_DATE>=:begindate and log.BAK_DATE <=:enddate and cust.man_id in("+manids+")")
		.append(" order by operate_date desc ,operate_time desc ");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("OPERATE_DATE",Hibernate.STRING);
			q.addScalar("OPERATE_TIME",Hibernate.STRING);
			q.addScalar("DEVICE_name",Hibernate.STRING);
			q.addScalar("RECORD_OPER",Hibernate.STRING);
			q.addScalar("COMMENTS",Hibernate.STRING);
			q.addScalar("OP_FEE",Hibernate.DOUBLE);
			q.addScalar("new_fee", Hibernate.DOUBLE);
			q.addScalar("cut_name", Hibernate.STRING);
			q.addScalar("man_id", Hibernate.STRING);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
	
}
