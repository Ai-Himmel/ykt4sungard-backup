/**
 * 
 */
package com.kingstargroup.advquery.photo;

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
public class PhotoDAO {
	
	/**
	 * �������ͳ�ư���Ա���ͳ��
	 * @param cutType
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getphotoNumByType(String cutType,String beginDate,String endDate,String statType){
		String sqlQuery = "";
		Session session = HibernateSessionFactory.currentSession();
		if ("bymonth".equals(statType)){
			sqlQuery = "photoNumByTypeMonthSQL";
		}else if ("bydate".equals(statType)){
			sqlQuery = "photoNumByTypeSQL";
		}
		try {
			Query query = session.getNamedQuery(sqlQuery);
			query.setString("cuttype",cutType);
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
	 * �������ͳ�ƣ������ˣ�
	 * @param cutType
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getphotoNumAll(String beginDate,String endDate,String statType){
		String sqlQuery = "";
		Session session = HibernateSessionFactory.currentSession();
		if ("bymonth".equals(statType)){
			sqlQuery = "photoNumByTypeMonthAllSQL";
		}else if ("bydate".equals(statType)){
			sqlQuery = "photoNumByTypeAllSQL";
		}
		try {
			Query query = session.getNamedQuery(sqlQuery);
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
	private Log _log = LogFactory.getLog(PhotoDAO.class);
}
