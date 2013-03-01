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
	 * ����������ͳ��
	 * @param seriType�������
	 * @param beginDateͳ�ƿ�ʼ����
	 * @param endDateͳ�ƽ�������
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
	 * Description: ReportOperDAO��У��pos��ֵ�Ա�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-5-18  <br>
	 * @author   ����ΰ
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
