/**
 * 
 */
package com.kingstargroup.advquery.reportoper;

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
public class ReportOperDAO {
	
	/**
	 * 存款情况分类统计
	 * @param seriType存款类型
	 * @param beginDate统计开始日期
	 * @param endDate统计结束日期
	 * @return
	 */
	public List getSavingSortStat(String seriType,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "savingSortStatSQL";				
			}else if ("bymonth".equals(statType)){
				execSQL = "savingSortStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setInteger("seritype",Integer.parseInt(seriType));
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
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
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ReportOperDAO各校区pos充值对比<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-18  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List posSavingCompareStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "posSavingStatSQL";				
			}else if ("bymonth".equals(statType)){
				execSQL = "posSavingStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
			
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.equals(he);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	private Log _log = LogFactory.getLog(ReportOperDAO.class);

}
