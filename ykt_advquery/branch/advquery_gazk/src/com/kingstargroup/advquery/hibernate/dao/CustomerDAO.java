package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.customer.TCifCustomer;

public class CustomerDAO extends BasicDAO {
	
	public static CustomerDAO getInstance() {
		if (_instance == null) {
			_instance = new CustomerDAO();
		}
		return _instance;
	}
	
	public TCifCustomer getCustomerByStuempno(String stuempno){
		Session s = getSession();
		TCifCustomer cust = null;
		try {
			Query q = s.createQuery(" from TCifCustomer t where  t.stuempNo='"+stuempno+"'");
			List list = q.list();
			if(list != null && list.size()>0){
				cust = (TCifCustomer)list.get(0);
			}
			return cust;
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}
	}
	
	public    List     getCustomerBymanId(String manId){
		Session s = getSession();
		try{
			StringBuffer  sql =new StringBuffer(" select cust.cut_id cutId , card.showid  showId,cust.cut_name  cutName from t_cif_customer cust ")
			              .append(" inner join  t_pif_card card ")
                          .append(" on cust.cut_id = card.cosumer_id ")
                          .append(" where  card.state_id<>2000")
                          .append(" and  cust.man_id = '"+manId+"'")
                          .append(" order by  cutId desc ");

			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("showId",Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			return q.list();
		}catch(HibernateException e){
			_log.error(e);
			return null;
		}
	}
	
	public  String  getStateByCustId(String custId){
		Session s = getSession();
		try{
			StringBuffer sql = new StringBuffer(1024);
			sql.append(" select state_id from  ykt_cur.t_pif_card where cosumer_id="+custId);
			SQLQuery q = s.createSQLQuery(sql.toString());
			q.addScalar("state_id", Hibernate.STRING);
			return q.list().get(0).toString();
		}catch(HibernateException e){
			_log.error(e);
			return null;
		}
		
	}
	
	
	private static  CustomerDAO _instance;
	
	private Log _log = LogFactory.getLog(CustomerDAO.class.getClass());

}
