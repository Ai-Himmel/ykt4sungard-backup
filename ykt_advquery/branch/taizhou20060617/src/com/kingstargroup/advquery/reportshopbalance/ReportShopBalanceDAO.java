/**
 * 
 */
package com.kingstargroup.advquery.reportshopbalance;
import java.util.HashMap;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
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
		StringBuffer execSQL = new StringBuffer(2000);
		HashMap map = new HashMap();
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			execSQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,")
			.append("sum(rsb.mngAmt)as mngamt,sum(rsb.totalAmt)as totalamt) from TTifReportShopBalance rsb ")
			.append(" where rsb.id.balanceDate>='").append(beginDate).append("' and rsb.id.balanceDate<='").append(endDate)
			.append(" '").append(" and rsb.id.shopId in ").append(shopId)
			.append(" group by rsb.id.shopId,rsb.shopName");
		}else if ("bymonth".equals(statType)){
			execSQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,")
			.append("sum(rsb.mngAmt)as mngamt,sum(rsb.totalAmt)as totalamt)from TTifReportShopBalance as rsb ")
			.append("where substr(rsb.id.balanceDate,1,6)>='").append(beginDate)
			.append("' and substr(rsb.id.balanceDate,1,6)<='").append(endDate)
			.append("'").append(" and rsb.id.shopId in ").append(shopId)
			.append(" group by rsb.id.shopId,rsb.shopName");
		}

		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.createQuery(execSQL.toString());
			List list = query.list();
			return list;
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
