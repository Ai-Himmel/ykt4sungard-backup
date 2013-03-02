/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.util.WebKeys;

public class ReportActiveDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static ReportActiveDAO getInstance() {
		if (_instance == null) {
			_instance = new ReportActiveDAO();
		}
		return _instance;
	}
	
		/**
		 * 存款总体情况笔数统计
		 * 2006-5-31
		 * hjw
		 * @param
		 * @return
		 */
	public List getTotleSavingNumStat(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "TotleSavingNumStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "TotleSavingNumStatMonthSQL";
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
	 * 存款总体情况统计（存款金额统计）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getTotleSavingMoneyStat(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "TotleMoneySavingStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "TotleMoneySavingStatMonthSQL";
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
		 * 各类存款对比（金额和笔数）
		 * 2006-6-2
		 * hjw
		 * @param
		 * @return
		 */
	public List getTotleSavingStat(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "TotleSavingStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "TotleSavingStatMonthSQL";
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
	 * 经费本和支票充值情况对比
	 * 2006-6-5
	 * hjw
	 * @param
	 * @return
	 */
	public List getBillTotleSavingStat(String beginDate,String endDate,String statType)throws HibernateException{
		String execSQL = "";
		Session session = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "BillTotleSavingStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "BillTotleSavingStatMonthSQL";
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
	}
	/**
	 * 圈存成功率统计
	 * 2006-6-6
	 * hjw
	 * @param
	 * @return
	 */
	public List getTransferSuccessRate(String beginDate,String endDate, String statType)throws HibernateException{
		String execSQL = "";
		Session session = getSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				if ("DB2".equals(WebKeys.DATABASE)){
					execSQL = "TransferSuccessRateSQL_DB2";
				}else if ("ORACLE".equals(WebKeys.DATABASE)){
					execSQL = "TransferSuccessRateSQL_ORACLE";
				}
				
			}else if ("bymonth".equals(statType)){
				if ("DB2".equals(WebKeys.DATABASE)){
					execSQL = "TransferSuccessRateMonthSQL_DB2";
				}else if ("ORACLE".equals(WebKeys.DATABASE)){
					execSQL = "TransferSuccessRateMonthSQL_ORACLE";
				}
				
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
	}
	
	
	private static ReportActiveDAO _instance;
	private Log _log = LogFactory.getLog(ReportActiveDAO.class.getClass());
}
