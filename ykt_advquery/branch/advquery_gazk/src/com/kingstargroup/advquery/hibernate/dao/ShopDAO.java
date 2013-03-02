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

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ShopDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static ShopDAO getInstance() {
		if (_instance == null) {
			_instance = new ShopDAO();
		}
		return _instance;
	}
	
	public List getChildList(String parentId) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCifShop where deptId = :parentId and shop_state!=2 order by shopId asc");
			q.setInteger("parentId", Integer.parseInt(parentId));
			q.setCacheable(true);
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public List getShopBusinessReportList(
			String shopIds,
			String beginDate,
			String endDate)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select a.shop_id,s.shop_name,a.balance_date,a.operate_date,sum(a.trade_num)trade_num,sum(a.total_amt)total_amt")
		.append(" from(select a.shop_id,a.seri_type,a.trade_num,a.BALANCE_DATE,a.operate_date,")
		.append(" case a.outorin when 1 then -a.total_amt else a.total_amt end total_amt")
		.append(" from YKT_CUR.T_TIF_REPORT_SHOP_BALANCE_01 A,YKT_CUR.T_PIF_TRADECODE C ")
		.append(" WHERE A.SERI_TYPE=C.TRADECODE AND C.ACCOUNT_FLAG<9) A,")
		.append(" ykt_cur.t_cif_shop s")
		.append(" where a.shop_id=s.shop_id and a.balance_date between '")
		.append(beginDate).append("' and '").append(endDate).append("' and a.shop_id in (")
		.append(shopIds).append(")").append(" group by a.shop_id,s.shop_name,a.balance_date,a.operate_date")
		.append(" order by a.shop_id,a.balance_date,a.operate_date");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("shop_name",Hibernate.STRING);
			q.addScalar("balance_date",Hibernate.STRING);
			q.addScalar("operate_date",Hibernate.STRING);
			q.addScalar("trade_num",Hibernate.INTEGER);
			q.addScalar("total_amt",Hibernate.FLOAT);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			_log.error(he);
			return null;
		}	
	}

	private static ShopDAO _instance;
	private Log _log = LogFactory.getLog(ShopDAO.class.getClass());

}
