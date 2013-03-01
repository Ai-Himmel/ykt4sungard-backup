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
	 * @return
	 * Modify History:
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
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-10  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAllConsumeStat(String beginDate,String endDate,String statType)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			sqlStr.append("select balance_date,sum(trade_num)tradenum,sum(total_amt)tradeamt,")
			.append("sum(mng_amt)mngamt from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE")
			.append(" where balance_date>='"+beginDate+"' and balance_date<='"+endDate+"' and shop_id=1")
			.append(" group by balance_date");
		}else if ("bymonth".equals(statType)){
			sqlStr.append("select substr(balance_date,1,6) balance_date,sum(trade_num)tradenum,")
			.append("sum(total_amt)tradeamt,sum(mng_amt)mngamt from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE")
			.append(" where substr(balance_date,1,6)>='"+beginDate)
			.append("' and substr(balance_date,1,6)<='"+endDate+"' and shop_id=1")
			.append(" group by substr(balance_date,1,6)");
		}

		try {
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
		 * 各校区消费笔数对比
		 * 2006-5-31
		 * hjw
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
	 * 各校区消费金额对比
	 * 2006-5-31
	 * hjw
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
		 * 各校区消费金额和笔数对比
		 * 2006-6-2
		 * hjw
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
	
	private static ReportShopBalanceDAO _instance;
	private Log _log = LogFactory.getLog(ReportShopBalanceDAO.class.getClass());
}
