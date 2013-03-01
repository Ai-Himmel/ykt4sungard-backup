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
	
	
	
	public List  getShopTrade(String stuempNo,String name,String begindate,String endDate,String posid,String posids)throws HibernateException {
		Session s = getSession();
		try{
			 
			StringBuffer sql = 
		          new StringBuffer("select  t.OPERATE_DATE opeDate ,t.operate_time as opeTime,d.device_name devname, ")
			      	.append(" cust.CUT_NAME cutName,cust.stuemp_no stuempNo,")
			      	.append(" TRADE_COUNT, decimal(-trade_fee,5,2) opFee ")
			      	.append(" from YKT_HIS.T_TIF_TRADESERIAL_HIS t ")
			      	.append(" left join ykt_cur.t_pif_device  d on t.device_id=d.device_id ,")
			      	.append(" ykt_cur.T_CIF_CUSTOMER cust where d.state_id<5  ");
		        	if(!"".equals(begindate)){
	      		       sql.append(" and  OPERATE_DATE >='"+begindate+"'");
	            	}
	                if(!"".equals(endDate)){
	                	sql.append("and  OPERATE_DATE <='"+endDate+"'");
	                }
			        if(!"".equals(posid)){
			        	sql.append(" and  d.dev999_id ='"+posid+"'");
			        }else if(!"".equals(posids)){
			        	sql.append(" and  d.dev999_id in ("+posids+")");
			        }
			        sql.append(" and cust.cut_id = t.customer_id  ");
			      	if(!"".equals(stuempNo)){
			      		sql.append(" and cust.stuemp_no='"+stuempNo+"'");
			      	 }
			        if(!"".equals(name)){
			        	 sql.append(" and cust.CUT_NAME like '%"+name+"%'");
			         }
			         sql.append(" order by OPERATE_DATE  desc ,t.operate_time desc with ur");

			         SQLQuery q=s.createSQLQuery(sql.toString());
	                 q.addScalar("opeDate",Hibernate.STRING);
	                 q.addScalar("opeTime",Hibernate.STRING);
	                 q.addScalar("devname",Hibernate.STRING);
	                 q.addScalar("cutName",Hibernate.STRING);
	                 q.addScalar("stuempNo",Hibernate.STRING);
	                 q.addScalar("TRADE_COUNT",Hibernate.INTEGER);
	                 q.addScalar("opFee",Hibernate.FLOAT);
	               
	                
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
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
	
	private static ShopDAO _instance;
	private Log _log = LogFactory.getLog(ShopDAO.class.getClass());

}
