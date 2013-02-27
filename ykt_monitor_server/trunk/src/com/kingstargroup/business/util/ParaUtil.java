package com.kingstargroup.business.util;

import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapParamTable;

public class ParaUtil {
	
	 public static  MapParamTable getPara(String para){
		 
		 Session session = HibernateSessionFactory.currentSession();
		 MapParamTable parameter = new MapParamTable();
		 try{
			 StringBuffer  str = new StringBuffer("");
			 str.append(" select  t   from   MapParamTable  t where t.parameter =:para");
			 Query query = session.createQuery(str.toString());
			 query.setString("para", para);
			 List result = query.list();
			 if(result!=null && result.size()>0){
				 parameter = (MapParamTable)result.get(0);
			 }
		 }catch(HibernateException e){
				e.printStackTrace();
			} finally {
			  HibernateSessionFactory.closeSession();
		   }		
			 return parameter;
		}		 
 }

