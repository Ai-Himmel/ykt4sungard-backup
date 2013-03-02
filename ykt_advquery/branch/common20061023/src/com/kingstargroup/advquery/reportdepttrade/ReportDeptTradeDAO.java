/**
 * 
 */
package com.kingstargroup.advquery.reportdepttrade;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;

/**
 * 整个单位卡户帐务变动情况
 * @author Administrator
 *
 */
public class ReportDeptTradeDAO {

	public List getDepAccountStat(String deptCode,String beginDate,String endDate,String statType){
		String execSQL="";
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			execSQL = "deptAccountStatSQL";
		}else if ("bymonth".equals(statType)){
			execSQL = "deptAccountStatMonthSQL";
		}
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query sqlquery = s.getNamedQuery(execSQL);
			sqlquery.setString("deptcode",deptCode);
			sqlquery.setString("begindate",beginDate);
			sqlquery.setString("enddate",endDate);
			List list = sqlquery.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 单位所有持卡人消费情况总体统计
	 * @return
	 */
	public List getDeptConsumeStat(String deptCode,String beginDate,String endDate,String statType){
		String execSQL="";
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			execSQL = "deptConsumeStatSQL";
		}else if ("bymonth".equals(statType)){
			execSQL = "deptConsumeStatMonthSQL";
		}
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query sqlquery = s.getNamedQuery(execSQL);
			sqlquery.setString("deptcode",deptCode);
			sqlquery.setString("begindate",beginDate);
			sqlquery.setString("enddate",endDate);
			List list = sqlquery.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	private Log _log = LogFactory.getLog(ReportDeptTradeDAO.class);
}
