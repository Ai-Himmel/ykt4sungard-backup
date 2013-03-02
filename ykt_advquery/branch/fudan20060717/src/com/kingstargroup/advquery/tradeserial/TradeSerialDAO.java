/**
 * 
 */
package com.kingstargroup.advquery.tradeserial;

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
public class TradeSerialDAO {

	/**
	 * 得到某一台Pos机在一段时间内的消费情况
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "ConsumeStatByPosSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "ConsumeStatByPosMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("posid",posId);
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
	 * 个人帐务情况变动：存款，消费，押金
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllAccountChangeStatByCustId(String custId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "AllAccountChangeStatByNoSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllAccountChangeStatByNoMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("custid",custId);
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
	 * 特殊人员查找
	 * @param dateRange
	 * @param beginDate
	 * @param endDate
	 * @param bNum
	 * @param eNum
	 * @param bFee
	 * @param eFee
	 * @return
	 */
	public List getSpecialList(int dateRange,String beginDate,String endDate,int bNum,int eNum,float bFee,float eFee){
		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.getNamedQuery("SpecialListSQL");
			query.setInteger("daterange",dateRange);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			query.setInteger("bnum",bNum);
			query.setInteger("enum",eNum);
			query.setFloat("bfee",bFee);
			query.setFloat("efee",eFee);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	private Log _log = LogFactory.getLog(TradeSerialDAO.class);
}
