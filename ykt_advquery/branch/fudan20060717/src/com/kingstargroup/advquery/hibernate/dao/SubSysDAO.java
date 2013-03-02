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

import com.kingstargroup.advquery.dictionary.TPifDictionary;

public class SubSysDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static SubSysDAO getInstance() {
		if (_instance == null) {
			_instance = new SubSysDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SubSysDAO取得子系统名称<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-17  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getSubSysName()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=82");
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.error(he);
			return null;
		}
	}
	
	public TPifDictionary getSubSysName(String subsysId)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=82 and id.dictValue='"+subsysId+"'");
			return (TPifDictionary)q.list().get(0);
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.error(he);
			return null;
		}
	}
	
	
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SubSysDAO根据系统编号和日期范围取得每天的访问次数<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-17  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getSubSysVisitList(int sysid ,String beginDate,String endDate,String statType)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if ("bydate".equals(statType)){
			sqlStr.append("select log_date,count(*) as numb")
			.append(" from YKT_CUR.T_SUBSYS_LOG")
			.append(" where log_date>='"+beginDate+"' and log_date<='"+endDate+"' and sussys_id="+sysid)
			.append(" group by log_date");
		}else if ("bymonth".equals(statType)) {
			sqlStr.append("select substr(log_date,1,6) as log_date,count(*) as numb")
			.append(" from YKT_CUR.T_SUBSYS_LOG")
			.append(" where substr(log_date,1,6)>='"+beginDate+"' and substr(log_date,1,6)<='"+endDate+"' and sussys_id="+sysid)
			.append(" group by substr(log_date,1,6)");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("log_date",Hibernate.STRING);
			q.addScalar("numb",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.error(he);
			return null;
		}
	}
	private static SubSysDAO _instance;
	private Log _log = LogFactory.getLog(SubSysDAO.class.getClass());
}
