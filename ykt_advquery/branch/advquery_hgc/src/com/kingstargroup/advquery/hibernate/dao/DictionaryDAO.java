package com.kingstargroup.advquery.hibernate.dao;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

public class DictionaryDAO extends BasicDAO {
	
	private static  DictionaryDAO _instance;
	
	public static DictionaryDAO getInstance(){
		if(_instance == null){
			_instance = new DictionaryDAO();
		}
		return _instance;
	}
	
    
	
	public List getFeeState()throws HibernateException{
		
		Session s = getSession();
		SQLQuery q = s.createSQLQuery( "select  register_flag ,register_info from  ykt_cur.t_tif_register_info ");
		q.addScalar("register_flag",Hibernate.STRING);
		q.addScalar("register_info",Hibernate.STRING);
		return q.list();
	}
	
	public List getTermList()throws HibernateException{
		Session s = getSession();
		SQLQuery q = s.createSQLQuery(" select  distinct(schoolterm_name) termName from ykt_cur.t_tif_register_schoolterm " +
				                        " where reg_flag in (1,2) and cuttype is not null"+
				                        " order by schoolterm_name desc ");
		q.addScalar("termName",Hibernate.STRING);
		List termList = q.list();
		Iterator it  = termList.iterator();
		List result = new ArrayList();
		while(it.hasNext()){
			   Object obj =  (Object)it.next();
			   String termName =  obj.toString();
			   SQLQuery sq= s.createSQLQuery(" select reg_id regId from ykt_cur.t_tif_register_schoolterm "+
					                         " where reg_flag in (1,2) and cuttype is not null and schoolterm_name='"+termName+"'"+
					                         " order by  schoolterm_name desc ");
			   sq.addScalar("regId",Hibernate.STRING);
			   List regList =   sq.list();
			   Iterator regIt = regList.iterator();
			   Map  strMap =  new  HashMap();
			   String pam ="";
			   while(regIt.hasNext()){
				   pam = pam + regIt.next().toString()+",";
			   }
			   pam = pam.substring(0,pam.lastIndexOf(","));
			   strMap.put("code",pam);
			   strMap.put("name",termName);
			   result.add(strMap);
		}
		return  result;
	}
	
	public  List getDeptList() throws HibernateException{
		Session s = getSession();
		Query q = s.createQuery(" select  new Map(deptCode  as id ,deptName as name) from  TCifDept");
		return q.list();
	}
	
	public List getSpeciality() throws  HibernateException{
		Session s = getSession();
		SQLQuery q = s.createSQLQuery(" select s_code ,s_name from  ykt_cur.t_cif_speciality ");
		q.addScalar("s_code",Hibernate.STRING);
		q.addScalar("s_name",Hibernate.STRING);
		return q.list();
	}
	
	public List getCuttype() throws HibernateException{
		Session s = getSession();
		SQLQuery q = s.createSQLQuery(" select cut_type, type_name from ykt_cur.t_cif_cuttypefee" );
		q.addScalar("cut_type",Hibernate.STRING);
		q.addScalar("type_name",Hibernate.STRING);
		return q.list();
	}
	
	public List getFeetype() throws HibernateException{
		Session s = getSession();
		SQLQuery q = s.createSQLQuery(" select fee_type , fee_name from ykt_cur.t_pif_feetype ");
		q.addScalar("fee_type",Hibernate.STRING);
		q.addScalar("fee_name",Hibernate.STRING);
		return q.list();
	}
	
}
