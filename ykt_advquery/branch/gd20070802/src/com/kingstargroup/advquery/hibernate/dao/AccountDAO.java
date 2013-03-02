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

import com.kingstargroup.advquery.device.TPifDevice;
public class AccountDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static AccountDAO getInstance() {
		if (_instance == null) {
			_instance = new AccountDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: TradeSerialDAO取得某个账号消费明细<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-10  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getOneAccountDetail(String custNo,String beginDate,String endDate)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select log.OPERATE_DATE, log.OPERATE_TIME, log.DEVICE_ID, log.RECORD_OPER,log.COMMENTS,log.OP_FEE")
		.append(" from YKT_CUR.T_TIF_TRADELOG log,YKT_CUR.T_AIF_ACCOUNT acc ,YKT_CUR.T_CIF_CUSTOMER cust")
		.append(" where log.ACT_ID=acc.ACCOUNT_ID and acc.CUSTOMER_ID=cust.CUT_ID and")
		.append(" OPERATE_DATE>=:begindate and OPERATE_DATE <=:enddate and cust.CUT_ID=:custno ")
		.append(" union all")
		.append(" select log.OPERATE_DATE, log.OPERATE_TIME, log.DEVICE_ID, log.RECORD_OPER,log.COMMENTS,log.OP_FEE")
		.append(" from YKT_HIS.T_TIF_TRADELOG_HIS log,YKT_CUR.T_AIF_ACCOUNT acc ,YKT_CUR.T_CIF_CUSTOMER cust")
		.append(" where log.ACT_ID=acc.ACCOUNT_ID and acc.CUSTOMER_ID=cust.CUT_ID and ")
		.append(" log.BAK_DATE>=:begindate and log.BAK_DATE <=:enddate and cust.CUT_ID=:custno ");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("OPERATE_DATE",Hibernate.STRING);
			q.addScalar("OPERATE_TIME",Hibernate.STRING);
			q.addScalar("DEVICE_ID",Hibernate.INTEGER);
			q.addScalar("RECORD_OPER",Hibernate.STRING);
			q.addScalar("COMMENTS",Hibernate.STRING);
			q.addScalar("OP_FEE",Hibernate.FLOAT);
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			q.setString("custno",custNo);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
	public String getDevNameByDevId(int devid)throws HibernateException{
		Session s = getSession();
		try {
			if (0!=devid){
				Query q = s.createQuery(" from TPifDevice where deviceId="+devid);
				return ((TPifDevice)q.list().get(0)).getDeviceName();
			}else{
				return "";
			}
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}
	}
	private static AccountDAO _instance;
	private Log _log = LogFactory.getLog(AccountDAO.class.getClass());
}
