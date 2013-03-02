package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.customer.TCifCustomer;

public class CustomerDao extends BasicDAO {
	
	public static CustomerDao getInstance() {
		if (_instance == null) {
			_instance = new CustomerDao();
		}
		return _instance;
	}
	public TCifCustomer getCustomerByStuempNo(String stuempNo){
		try{
		   Session s = getSession();
		   Query q=s.createQuery("from  TCifCustomer where stuempNo=:stuempNo");
		   q.setString("stuempNo",stuempNo);
		   return (TCifCustomer)q.list().get(0);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public List getCustomerByName(String name){
		try{
		   Session s = getSession();
		   Query q=s.createQuery("from  TCifCustomer where cutName=:name");
		   q.setString("name",name);
		   return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	
	private static CustomerDao _instance;

}
