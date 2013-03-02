package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;



public class DoorDAO extends BasicDAO {
	
	public static DoorDAO getInstance() {
		if (_instance == null) {
			_instance = new DoorDAO();
		}
		return _instance;
	}
	
	public List  getDoorDetailByCust(String custno,String begingdate,String enddate)throws Exception{
		try{
		Session s = HibernateSessionFactory.currentSession();
		String execSQL = "oneDoorDetail";
		Query sqlquery = s.getNamedQuery(execSQL);
		
		sqlquery.setString("custId",custno);
		sqlquery.setString("startDate",begingdate);
		sqlquery.setString("endDate",enddate);
		sqlquery.getQueryString();
		List list = sqlquery.list();
		return list;
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
		
	}

	
	private static DoorDAO _instance;
}
