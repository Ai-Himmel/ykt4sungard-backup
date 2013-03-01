/**
 * 
 */
package com.kingstargroup.advquery.reportshopbalance;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
/**
 * @author Administrator
 *
 */
public class ReportShopBalanceDAO {
	/**
	 * 商户整体账户变动情况，营业额，管理费金额
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getShopAccountChangeStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "ShopAccountChangeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "ShopAccountChangeStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 消费总体情况统计
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllConsumeStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AllConsumeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllConsumeStatMonthSQL";
			}

			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	/**
	 * 各校区营业情况对比（笔数）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAreaSalesNumCompare(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesNumCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesNumCompareMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	/**
	 * 各校区营业情况对比（金额）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAreaSalesMoneyCompare(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesMoneyCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesMoneyCompareMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 各商户营业情况统计
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getOneAccountStat(int shopId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "OneShopAccountChangeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "OneShopAccountChangeStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setInteger("shopid",shopId);
			query.setString("begindate",beginDate);
			query.setString("endate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 各商户营业情况对比
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getShopAccountCompare(String shopId,String beginDate,String endDate,String statType){
		StringBuffer execSQL = new StringBuffer(1024);
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			execSQL.append("select rsb.shop_id shopid,rsb.shop_name shopname,sum(round(rsb.trade_Num,2))tradenum,")
			.append(" sum(round(rsb.trade_Amt,2))tradeamt,sum(round(rsb.mng_Amt,2))mngamt,sum(round(rsb.total_Amt,2))totalamt")
			.append(" from ykt_cur.T_Tif_Report_Shop_Balance rsb ")
			.append(" where rsb.balance_Date>='").append(beginDate).append("' and rsb.balance_Date<='")
			.append(endDate).append("' and rsb.shop_Id in").append(shopId)
			.append(" group by rsb.shop_Id,rsb.shop_Name");
		}else if ("bymonth".equals(statType)){
			execSQL.append("select rsb.shop_id shopid,rsb.shop_name shopname,sum(round(rsb.trade_Num,2))tradenum,")
			.append(" sum(round(rsb.trade_Amt,2))tradeamt,sum(round(rsb.mng_Amt,2))mngamt,sum(round(rsb.total_Amt,2))totalamt")
			.append(" from ykt_cur.T_Tif_Report_Shop_Balance rsb ")
			.append(" where substr(rsb.balance_date,1,6)>='").append(beginDate).append("' and substr(rsb.balance_date,1,6)<='")
			.append(endDate).append("' and rsb.shop_Id in").append(shopId)
			.append(" group by rsb.shop_Id,rsb.shop_Name");
		}

		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(execSQL.toString());
			query.addScalar("shopid",Hibernate.INTEGER);
			query.addScalar("shopname",Hibernate.STRING);
			query.addScalar("tradenum",Hibernate.INTEGER);
			query.addScalar("tradeamt",Hibernate.DOUBLE);
			query.addScalar("mngamt",Hibernate.DOUBLE);
			query.addScalar("totalamt",Hibernate.DOUBLE);
			List list = query.list();
			
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("shopid",objects[0]);
				accMap.put("shopname",objects[1]);
				accMap.put("tradenum",objects[2]);
				accMap.put("tradeamt",objects[3]);
				accMap.put("mngamt",objects[4]);
				accMap.put("totalamt",objects[5]);
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			e.printStackTrace();
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	private Log _log = LogFactory.getLog(ReportShopBalanceDAO.class);
}
