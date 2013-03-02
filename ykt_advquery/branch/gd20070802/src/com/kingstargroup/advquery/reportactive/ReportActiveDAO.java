/**
 * 
 */
package com.kingstargroup.advquery.reportactive;

import org.apache.log4j.Logger;

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
public class ReportActiveDAO {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ReportActiveDAO.class);
	
	/**
	 * 返回一段时间内开卡，挂失，收回，补办数量(按月份和日期范围统计)
	 * 根据传回的参数判断是按月份还是日期统计
	 * @param balanceDate
	 * @return
	 */
	public List getCardOpenLoseBackStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "CardOpenLoseBackSQl";
			}else if ("bymonth".equals(statType)){
				execSQL ="CardOpenLoseBackMonthSQl";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 存款总体情况统计报表（笔数统计）
	 * @param beginDate
	 * @param endDate
	 * @return每天各存款类别的存款笔数
	 */
	public List getTotleSavingNumStat(String beginDate,String endDate,String statType){
		if (logger.isDebugEnabled()) {
			logger
					.debug("getTotleSavingNumStat(String, String, String) - start"); //$NON-NLS-1$
		}

		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "TotleSavingNumStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "TotleSavingNumStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			//SQLQuery sqlQuery = session.createSQLQuery("");
			//sqlQuery.addScalar("aa1", Hibernate.STRING);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();

			if (logger.isDebugEnabled()) {
				logger
						.debug("getTotleSavingNumStat(String, String, String) - end"); //$NON-NLS-1$
			}
			return list;
		} catch (HibernateException e) {
			logger.error("getTotleSavingNumStat(String, String, String)", e); //$NON-NLS-1$

			_log.error(e);

			if (logger.isDebugEnabled()) {
				logger
						.debug("getTotleSavingNumStat(String, String, String) - end"); //$NON-NLS-1$
			}
			return null;
		}
		finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 存款总体情况统计（存款金额统计）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getTotleSavingMoneyStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "TotleMoneySavingStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "TotleMoneySavingStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 某段时间内的开户和销户情况统计
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getCardOpenDestroyStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||(("byweek".equals(statType)))){
				execSQL = "CardOpenDestroyStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "CardOpenDestroyStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 整体帐务情况变化：存款，消费，押金(按日期范围统计)
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllAccountChangeStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||(("byweek".equals(statType)))){
				execSQL = "AllAccountChangeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllAccountChangeMonthSQL";
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


	private Log _log = LogFactory.getLog(ReportActiveDAO.class);
}
