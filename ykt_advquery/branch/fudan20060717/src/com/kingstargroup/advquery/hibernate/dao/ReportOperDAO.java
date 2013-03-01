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

public class ReportOperDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static ReportOperDAO getInstance() {
		if (_instance == null) {
			_instance = new ReportOperDAO();
		}
		return _instance;
	}
	
	public List posSavingCompareStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session s = getSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "posSavingStatSQL";				
			}else if ("bymonth".equals(statType)){
				execSQL = "posSavingStatMonthSQL";
			}
			Query q = s.getNamedQuery(execSQL);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
			
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.equals(he);
			return null;
		}
	}
	private static ReportOperDAO _instance;
	private Log _log = LogFactory.getLog(ReportOperDAO.class.getClass());
}
