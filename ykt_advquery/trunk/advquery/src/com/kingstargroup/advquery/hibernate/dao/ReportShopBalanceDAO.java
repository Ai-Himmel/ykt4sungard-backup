/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

public class ReportShopBalanceDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * 
	 * @return Modify History:
	 */
	public static ReportShopBalanceDAO getInstance() {
		if (_instance == null) {
			_instance = new ReportShopBalanceDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: TradeSerialDAO总体消费情况统计<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-5-10 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0 20081119加入and seri_type <>'847222'，去掉商户划拨款
	 */
	public List getAllConsumeStat(String beginDate,String endDate,String statType)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			sqlStr.append("select balance_date,sum(trade_num)tradenum,sum(total_amt)tradeamt,")
			.append("sum(mng_amt)mngamt from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE")
			.append(" where balance_date>='"+beginDate+"' and balance_date<='"+endDate+"' and shop_id=1")
			.append(" and seri_type <>'847222' group by balance_date");
		}else if ("bymonth".equals(statType)){
			sqlStr.append("select substr(balance_date,1,6) balance_date,sum(trade_num)tradenum,")
			.append("sum(total_amt)tradeamt,sum(mng_amt)mngamt from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE")
			.append(" where substr(balance_date,1,6)>='"+beginDate)
			.append("' and substr(balance_date,1,6)<='"+endDate+"' and shop_id=1")
			.append(" and seri_type <>'847222' group by substr(balance_date,1,6)");
		}

		try {
			System.out.println(sqlStr.toString());
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("balance_date",Hibernate.STRING);
			q.addScalar("tradeamt",Hibernate.FLOAT);
			q.addScalar("mngamt",Hibernate.FLOAT);
			q.addScalar("tradenum",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
		/**
		 * 各校区消费笔数对比 2006-5-31 hjw
		 * 
		 * @param
		 * @return
		 */
	public List getAreaSalesNumCompare(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesNumCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesNumCompareMonthSQL";
			}
			Query q = s.getNamedQuery(execSQL);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	/**
	 * 各校区消费金额对比 2006-5-31 hjw
	 * 
	 * @param
	 * @return
	 */
	public List getAreaSalesMoneyCompare(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesMoneyCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesMoneyCompareMonthSQL";
			}
			Query q = s.getNamedQuery(execSQL);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}
	
		/**
		 * 各校区消费金额和笔数对比 2006-6-2 hjw
		 * 
		 * @param
		 * @return
		 */
	public List getAreaSalesCompare(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesCompareMonthSQL";
			}
			Query q = s.getNamedQuery(execSQL);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}
	
    // pos营业情况分天汇总表 gejinfeng 2009-09-16
	public List  getPosQueryResult(String begindate,String enddate,String shopid,String isdevice,String ismeal){
		Session s = getSession();
		StringBuffer execSQL = new StringBuffer(1024);
		try{
			if("1".equals(isdevice)&& ("1".equals(ismeal))){
				 execSQL.append(" select * from (   ")
				   .append(" select shop_id,shop_name,dept_id,device_id,device_name,  ")
				   .append(" meal_id,meal_name,sum(trade_count) trade_count ,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt ,sum(total_amt) total_amt, ")
				   .append(" case device_id when 0 then 1 else 2 end dflag from (  ")
				   .append(" select operate_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id  ")
				   .append(" ,'' as meal_name,sum(trade_num) as trade_count,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt, ")
				   .append(" 	sum(total_amt) as total_amt  ")
				   .append(" from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE_01 B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T ON (T.TRADECODE=B.SERI_TYPE)  ")
				   .append(" where operate_date>='").append(begindate).append("' and operate_date <='").append(enddate).append("'") 
				   .append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL) ") 
				   .append(" group by operate_date,shop_id,shop_name,dept_id  ")
				   .append(" union all ")
				   .append(" select operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,  ")
				   .append(" sum(trade_count),sum(trade_fee) as trade_amt,sum(mng_fee) as mng_amt,sum(total_fee) as total_amt  ")
				   .append(" from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL_01 a  ")
				   .append(" left join ykt_cur.t_cif_shop b  ")
				   .append(" on a.shop_id=b.shop_id ")
				   .append(" where a.operate_date>='").append(begindate).append("' and a.operate_date <='").append(enddate).append("'")
				   .append(" group by operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name ) t  ")
				   .append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")
				   .append(" group by t.shop_id,t.shop_name,t.device_id,t.device_name,t.meal_id,t.meal_name,t.dept_id ) t  ")
				   .append(" order by shop_id,dflag,device_name,meal_id ");
				 
			}else if("0".equals(isdevice)&& ("0".equals(ismeal))){
				 
				execSQL.append("SELECT shop_id,shop_name,dept_id,0 as device_id,'' as  device_name ,-1 as  meal_id ,'' as  meal_name ,sum(Trade_num) as trade_count, ")
						.append("sum(Trade_amt) as  trade_amt,sum(Mng_amt) as   mng_amt,sum(Total_amt) as  total_amt , ")
						.append(" 3 as  dflag ")
						.append(" from   ")
						.append("(   ")
						.append(" SELECT a.Shop_id,b.Shop_name,a.Dept_id,  ")
						.append(" sum(trade_num) trade_num,sum(Trade_amt) Trade_amt,  ")
						.append(" sum(Mng_amt) Mng_amt, sum(Total_amt) Total_amt,  ")
						.append(" operate_date,''  FROM YKT_CUR.T_TIF_Report_shop_balance_01 a   ")
						.append(" left join YKT_CUR.T_PIF_TRADECODE T on (T.TRADECODE=a.SERI_TYPE )   ")
						.append(" ,ykt_cur.t_cif_shop b  ")
						 .append(" where operate_date>='").append(begindate).append("' and operate_date <='").append(enddate).append("'") 
						.append(" and a.shop_id=b.shop_id ")  
						.append(" AND (T.ACCOUNT_FLAG=1 or T.ACCOUNT_FLAG IS NULL)  ")
						.append("  and  (a.Dept_id in (").append(shopid).append(") or a.Shop_id in (").append(shopid).append("))")
						.append(" group by a.operate_date,a.shop_id,b.shop_name,a.dept_id  ")
						.append(") T group by shop_id,shop_name,dept_id order by dept_id,shop_name  ");
				
			}else if("1".equals(isdevice)&& ("0".equals(ismeal))){
				   
				execSQL.append("select * from ( ")
				.append(" select shop_id,shop_name,dept_id,device_id,device_name, ")
				.append(" -1 meal_id ,'' meal_name,sum(trade_count) trade_count,sum(trade_amt) trade_amt,sum(mng_amt)mng_amt,sum(total_amt) total_amt, ")
				.append(" case device_id when 0 then 1 else 2 end dflag from ")
				.append(" ( ")
				.append(" select operate_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id ")
				.append(" ,'' as meal_name,sum(trade_num) as trade_count,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt, ")			 
				.append(" sum(total_amt) total_amt from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE_01 B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T  ")
				.append(" ON (T.TRADECODE=B.SERI_TYPE )  ")			 
				.append(" where operate_date>='").append(begindate).append("' and operate_date <='").append(enddate).append("'") 
				.append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL) ")
				.append(" group by operate_date,shop_id,shop_name,dept_id ")	
				.append(" union all  ")
				.append(" select operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,   ")
				.append("  sum(trade_count) trade_count,sum(trade_fee) as trade_amt,sum(mng_fee) as mng_amt, ")			 
				.append("  sum(total_fee) as total_amt from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL_01 a  ")			 
				.append(" left join ykt_cur.t_cif_shop b on a.shop_id=b.shop_id  ")			 
				.append(" where a.operate_date>='").append(begindate).append("' and a.operate_date <='").append(enddate).append("'")		
				.append(" group by operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name  ")			
				.append(" ) t ")		
				.append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")
				.append(" group by t.shop_id,t.shop_name,t.device_id,t.device_name,t.dept_id ) t  ")			 
				.append(" order by shop_id,dflag,device_name ");		 
			}else if("0".equals(isdevice)&& ("1".equals(ismeal))){
				execSQL.append("select shop_id,shop_name,dept_id,0 device_id ,'' device_name  ")
				.append(" ,meal_id,meal_name,sum(trade_count) trade_count,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt,sum(total_amt)total_amt , " )
				.append(" 3 as  dflag ")
				.append(" from ")
				.append(" ( ")
				.append(" select operate_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id  ")
				.append(" ,'' as meal_name,sum(trade_num) as trade_count,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt, ")
				.append("  sum(total_amt) total_amt  ")
				.append(" from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE_01 B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T ")
				.append(" ON (T.TRADECODE=B.SERI_TYPE)  ")
				.append(" where operate_date>='").append(begindate).append("' and operate_date <='").append(enddate).append("'") 
				.append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL)  ")
				.append(" group by operate_date,shop_id,shop_name,dept_id  ")
				.append(" union all  ")
				.append(" select operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,  ") 
				.append(" sum(trade_count) trade_count,sum(trade_fee) as trade_amt,sum(mng_fee) as mng_amt, ") 
				.append(" sum(total_fee) as total_amt from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL_01 a  ") 
				.append(" left join ykt_cur.t_cif_shop b on a.shop_id=b.shop_id  ")
				 .append(" where a.operate_date>='").append(begindate).append("' and a.operate_date <='").append(enddate).append("'")
				.append(" group by operate_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name ")
				.append(" ) t  ")
				.append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")
				.append(" group by t.shop_id,t.shop_name,t.meal_id,t.meal_name,t.dept_id  ")
				.append(" order by shop_id,meal_id ");
						 	
			}
			SQLQuery query = s.createSQLQuery(execSQL.toString());
			query.addScalar("shop_id",Hibernate.INTEGER);
			query.addScalar("shop_name",Hibernate.STRING);
			query.addScalar("dept_id",Hibernate.STRING);
			query.addScalar("device_id",Hibernate.STRING);
			query.addScalar("device_name",Hibernate.STRING);
			query.addScalar("meal_id",Hibernate.STRING);
			query.addScalar("meal_name",Hibernate.STRING);
			query.addScalar("trade_count",Hibernate.INTEGER);
			query.addScalar("trade_amt",Hibernate.FLOAT);
			query.addScalar("mng_amt",Hibernate.FLOAT);
			query.addScalar("total_amt",Hibernate.FLOAT);
			query.addScalar("dflag",Hibernate.INTEGER);
			return query.list();
		}catch(HibernateException e){
			e.getMessage();
			e.printStackTrace();
			return null;
		}
	}
	
	
	// 商户营业结算报表 gejinfeng 2009-09-16
	public List  getShopAccountQueryResult(String begindate,String enddate,String shopid,String isdevice,String ismeal){
		Session s = getSession();
		StringBuffer execSQL = new StringBuffer(1024);
		try{
			if("1".equals(isdevice)&& ("1".equals(ismeal))){
				execSQL.append(" select * from ( ")
				.append(" select shop_id,shop_name,dept_id,device_id,device_name,  ")	
				.append(" meal_id,meal_name,sum(trade_count) trade_count,sum(trade_amt) trade_amt ,sum(mng_amt) mng_amt ,sum(total_amt) total_amt, ")
				.append(" case device_id when 0 then 1 else 2 end dflag from  ")		
				.append(" (  ")
				.append("  select balance_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id   ")		
				.append(" ,'' as meal_name,trade_num as trade_count,trade_amt,mng_amt,total_amt  ")		
				.append("  from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T ON (T.TRADECODE=B.SERI_TYPE)   ")		  
				.append(" where balance_date>='").append(begindate).append("' and balance_date <='").append(enddate).append("'")
				.append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL)")   
				.append(" union all  ")
				.append(" select balance_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,  ")		
				.append(" trade_count,trade_fee as trade_amt,mng_fee as mng_amt,total_fee as total_amt  ")		  
				.append(" from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL a   ")		  
				.append(" left join ykt_cur.t_cif_shop b   ")		
				.append(" on a.shop_id=b.shop_id   ")		 
			    .append(" where a.balance_date>='").append(begindate).append("' and a.balance_date <='").append(enddate).append("'")			 
				.append(" ) t ")		 
				.append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")	 
				.append(" group by t.shop_id,t.shop_name,t.device_id,t.device_name,t.meal_id,t.meal_name,t.dept_id ) t  ")		
				.append(" order by shop_id,dflag,device_name,meal_id ");		 
						
			}else if("1".equals(isdevice)&& ("0".equals(ismeal))){
				
				execSQL.append(" select * from (  ")
				.append(" select shop_id,shop_name,dept_id,device_id,device_name,   ")
				.append(" -1 meal_id ,'' meal_name,sum(trade_count) trade_count,sum(trade_amt) trade_amt ,sum(mng_amt) mng_amt,sum(total_amt) total_amt,  ")	
				.append(" case device_id when 0 then 1 else 2 end dflag from   ")
				.append(" ( ")
				.append(" select balance_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id   ")
				.append(" ,'' as meal_name,trade_num as trade_count,trade_amt,mng_amt,total_amt  ")
				.append(" from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T ON (T.TRADECODE=B.SERI_TYPE )  ")
				.append(" where balance_date>='").append(begindate).append("' and balance_date <='").append(enddate).append("'")
				.append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL)  ")
				.append("  union all  ")
				.append(" select balance_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,    ")
				.append(" trade_count,trade_fee as trade_amt,mng_fee as mng_amt,total_fee as total_amt    ")
				.append(" from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL a   ")
				.append(" left join ykt_cur.t_cif_shop b  on a.shop_id=b.shop_id  ")
				.append(" where a.balance_date>='").append(begindate).append("' and a.balance_date <='").append(enddate).append("'")	
				.append(" ) t   ")
				.append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")	 
				.append(" group by t.shop_id,t.shop_name,t.device_id,t.device_name,t.dept_id ) t  ")
				.append(" order by shop_id,dflag,device_name ");
							
			}else if("0".equals(isdevice)&& ("1".equals(ismeal))){
				
				execSQL.append(" select shop_id,shop_name,dept_id,0 device_id ,'' device_name ")
				.append(" ,meal_id,meal_name,sum(trade_count) trade_count,sum(trade_amt) trade_amt,sum(mng_amt) mng_amt,sum(total_amt) total_amt  , ")
				.append(" 3 as  dflag")
				.append(" from (")
				.append(" select balance_date,shop_id,shop_name,dept_id,0 as device_id,'' as device_name,-1 as meal_id   ")
				.append(" ,'' as meal_name,trade_num as trade_count,trade_amt,mng_amt,total_amt   ") 
				.append("  from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE B LEFT JOIN YKT_CUR.T_PIF_TRADECODE T ON (T.TRADECODE=B.SERI_TYPE)  ") 
				.append(" where balance_date>='").append(begindate).append("' and balance_date <='").append(enddate).append("'")
				.append(" AND (T.ACCOUNT_FLAG=1 OR T.ACCOUNT_FLAG IS NULL) ")
				.append("  union all  ")   
				.append("  select balance_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,a.device_name,a.meal_id,a.meal_name,   ")
				.append(" trade_count,trade_fee as trade_amt,mng_fee as mng_amt,total_fee as total_amt   ")
			    .append("  from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL a   ")
			    .append("  left join ykt_cur.t_cif_shop b  ")
				.append(" on a.shop_id=b.shop_id  ")
				.append(" where a.balance_date>='").append(begindate).append("' and a.balance_date <='").append(enddate).append("'")
				.append(" ) t  ")
				.append(" where (t.Dept_id in (").append(shopid).append(") or t.Shop_id in (").append(shopid).append("))")	 
				.append(" group by t.shop_id,t.shop_name,t.meal_id,t.meal_name,t.dept_id  ")
				.append(" order by shop_id,meal_id ");
				
			}else if("0".equals(isdevice)&& ("0".equals(ismeal))){
				execSQL.append(" SELECT shop_id,shop_name,dept_id,0 device_id ,'' device_name ,-1 meal_id ,'' meal_name,sum(Trade_num) trade_count,  ")
				.append(" sum(Trade_amt) trade_amt,sum(Mng_amt) mng_amt,sum(Total_amt) total_amt , ")
				.append(" 3 as  dflag ")
				.append(" from (")
				.append(" SELECT a.Shop_id,b.Shop_name,a.Dept_id,  ")
				.append(" case when t.account_flag=1 then Trade_num else 0 end trade_num,  ")   
				.append(" case when t.account_flag=1 then Trade_amt else 0 end Trade_amt,  ") 
				.append(" case when t.account_flag=1 then Mng_amt else 0 end Mng_amt,  ")
				.append(" case when t.account_flag=1 then Total_amt else 0 end Total_amt,")
				.append("  Balance_date,Data_sign  FROM YKT_CUR.T_TIF_Report_shop_balance a ")  
				.append("  left join YKT_CUR.T_PIF_TRADECODE T on (T.TRADECODE=a.SERI_TYPE )  ,ykt_cur.t_cif_shop b  ")   
				.append(" where balance_date>='").append(begindate).append("' and balance_date <='").append(enddate).append("'")  
				.append(" and a.shop_id=b.shop_id AND (T.ACCOUNT_FLAG=1 or T.ACCOUNT_FLAG IS NULL)  and  ")
				.append(" (a.Dept_id in (").append(shopid).append(") or a.Shop_id in (").append(shopid).append("))")  
				.append(" ) T   ")  
			    .append(" group by shop_id,shop_name,dept_id order by dept_id,shop_name ");
			}
			
		
			SQLQuery query = s.createSQLQuery(execSQL.toString());
			query.addScalar("shop_id",Hibernate.INTEGER);
			query.addScalar("shop_name",Hibernate.STRING);
			query.addScalar("dept_id",Hibernate.STRING);
			query.addScalar("device_id",Hibernate.STRING);
			query.addScalar("device_name",Hibernate.STRING);
			query.addScalar("meal_id",Hibernate.STRING);
			query.addScalar("meal_name",Hibernate.STRING);
			query.addScalar("trade_count",Hibernate.INTEGER);
			query.addScalar("trade_amt",Hibernate.FLOAT);
			query.addScalar("mng_amt",Hibernate.FLOAT);
			query.addScalar("total_amt",Hibernate.FLOAT);
			query.addScalar("dflag",Hibernate.INTEGER);
			return query.list();
		}catch(HibernateException e){
			return null;
		}
	}
	
	
	// 商户营业结算报表 gejinfeng 2008-09-23
	
	/*
	 * public List getShopAccountQueryResult(String beginDate,String
	 * endDate,String shopid) throws HibernateException{
	 * 
	 * Session s = getSession(); StringBuffer sqlStr = new StringBuffer();
	 * sqlStr.append(" select shop_id,shop_name,dept_id,device_id,device_name, " )
	 * .append(" sum(trade_count) sum_count ,sum(trade_amt) sum_trade
	 * ,sum(mng_amt) sum_mng ,sum(total_amt) sum_total from " ) .append(" (
	 * select balance_date,shop_id,shop_name,dept_id,0 as device_id,'' as
	 * device_name,-1 as meal_id " ) .append(" ,'' as meal_name,trade_num as
	 * trade_count,trade_amt,mng_amt,total_amt " ) .append(" from
	 * YKT_CUR.T_TIF_REPORT_SHOP_BALANCE ,YKT_CUR.T_PIF_TRADECODE C ") .append("
	 * where balance_date>='"+beginDate+"' and balance_date<='"+endDate+"'" )
	 * .append(" and seri_type=c.tradecode and c.account_flag=1 ") .append("
	 * union all ") .append(" select
	 * balance_date,a.shop_id,b.shop_name,b.dept_id,a.device_id,c.device_name,a.meal_id,d.meal_name, " )
	 * .append(" trade_count,trade_fee as trade_amt,mng_fee as mng_amt,total_fee
	 * as total_amt " ) .append(" from YKT_CUR.T_TIF_REPORT_DEVICE_MEAL a ")
	 * .append(" left join ykt_cur.t_cif_shop b ") .append(" on
	 * a.shop_id=b.shop_id ") .append(" left join ykt_cur.t_pif_device c ")
	 * .append(" on a.device_id=c.device_id" ) .append(" left join
	 * ykt_cur.t_pif_meal_type d ") .append(" on a.meal_id=d.meal_id ")
	 * .append(" where a.balance_date>='"+beginDate+"' and a.balance_date<='"+endDate+"' ")
	 * .append(" ) t ") .append(" where (t.Dept_id in ("+shopid+") or t.Shop_id
	 * in ( "+shopid+") ) ") .append(" group by
	 * t.shop_id,t.shop_name,t.device_id,t.device_name,t.dept_id ")
	 * .append("order by shop_name,device_name"); try { SQLQuery q =
	 * s.createSQLQuery(sqlStr.toString()); q.addScalar("shop_id",
	 * Hibernate.INTEGER); q.addScalar("shop_name", Hibernate.STRING);
	 * q.addScalar("dept_id",Hibernate.INTEGER);
	 * q.addScalar("device_id",Hibernate.INTEGER);
	 * q.addScalar("device_name",Hibernate.STRING);
	 * q.addScalar("sum_count",Hibernate.INTEGER);
	 * q.addScalar("sum_trade",Hibernate.FLOAT);
	 * q.addScalar("sum_mng",Hibernate.FLOAT);
	 * q.addScalar("sum_total",Hibernate.FLOAT); return q.list(); } catch
	 * (HibernateException he) { _log.error(he); return null; } }
	 */
	
	private static ReportShopBalanceDAO _instance;
	private Log _log = LogFactory.getLog(ReportShopBalanceDAO.class.getClass());
}
