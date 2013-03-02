package com.kingstargroup.ecard.hibernate.termregister;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;

public class TermRegPersistence extends BasicPersistence {
	
	  public List  getTermByCutId(int cutId)throws DBSystemException {	  
		  try{
		  Session s = getSession();
		   		 
		  String sql =" select r.cust_id custId,r.reg_id  regId ,r.tx_date  txDate ,t.schoolterm_name termName ,r.reg_flag regFlag"
			         +" from t_tif_registration r ,"
			         +" ykt_cur.t_tif_register_schoolterm t "
			         +" where  t.reg_id =r.reg_id "
			         +" and  r.cust_id="+cutId
			        /* +" and  t.reg_flag = 1 "*/
			         +" order by tx_date desc";
		  SQLQuery  q = s.createSQLQuery(sql);
		  q.addScalar("custId",Hibernate.STRING);
		  q.addScalar("regId",Hibernate.STRING);
		  q.addScalar("txDate",Hibernate.STRING);
		  q.addScalar("termName",Hibernate.STRING);
		  q.addScalar("regFlag",Hibernate.STRING);
		  List list  =q.list();
		  List result = new ArrayList();
		  for(int i=0;i<list.size();i++){
			  Object[] obj =(Object[])list.get(i);
			  Map temp = new HashMap();
			      temp.put("custId",obj[0]);
			      temp.put("regId",obj[1]);
			      temp.put("txDate",obj[2]);			      
			      temp.put("termName",obj[3]);
			      temp.put("regFlag",obj[4]);
			      result.add(temp);
		  }
			return result;  
		  } catch (HibernateException ex) {			
				_log.error(ex);			
				throw new DBSystemException(ex.getMessage());
		  }
		  
	  }
		private static final Log _log = LogFactory.getLog(TermRegPersistence.class);

}
