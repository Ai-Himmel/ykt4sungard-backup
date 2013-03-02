/**
 * 
 */
package com.kingstargroup.advquery.device;

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
public class DeviceDAO {

	/**
	 * 终端设备使用率情况统计
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getDevUseStat(int serialType,String devType,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if ("bydate".equals(statType)){
				execSQL = "devUesRateSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "devUesRateMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setInteger("serialtype",serialType);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			query.setString("devtype",devType);
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
	
	
	private Log _log = LogFactory.getLog(DeviceDAO.class);
}
