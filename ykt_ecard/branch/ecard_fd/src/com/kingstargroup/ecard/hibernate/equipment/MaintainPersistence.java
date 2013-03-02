package com.kingstargroup.ecard.hibernate.equipment;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class MaintainPersistence extends BasicPersistence {
	
	
   public  List adminTotal(String beginDate,String endDate)throws DBSystemException {	
		Session s = getSession();
		List  totalList = new ArrayList();
		try {		
		 	StringBuffer Hql = new StringBuffer(" select   t.dic_value as dicValue,d.dic_caption as dicCaption,count(m.id) as total ");
			Hql.append(" from YKT_WEB.MAINTAIN m  "); 
			Hql.append(" left join ykt_web.maintain_type t  ");
			Hql.append(" on  m.id= t.maintain_id  " );
			Hql.append(" left join ykt_web.dictionary   d");
			Hql.append(" on   d.dic_value = t.dic_value and d.dic_no='001'");
			if(beginDate !=null && !("").equals(beginDate)){
				Hql.append(" and m.apply_time >='"+beginDate+"'");
			}
			if(endDate !=null && !("").equals(endDate)){
				Hql.append(" and m.apply_time <='"+endDate+"'");
			}
			Hql.append("  group by t.dic_value ,d.dic_caption ");
			Hql.append(" union " );
			Hql.append(" select status as dicValue,d.dic_caption as dicCaption, count(*) as total from  YKT_WEB.MAINTAIN m " );
			Hql.append(" left join ykt_web.dictionary  d " );
			Hql.append(" on m.status =d.dic_value and d.dic_no='002' " );
			Hql.append(" group by status ,d.dic_caption" );
			
			 SQLQuery sqlquery  = s.createSQLQuery(Hql.toString());
			 sqlquery.addScalar("dicValue", Hibernate.STRING);
		     sqlquery.addScalar("dicCaption",Hibernate.STRING);
		     sqlquery.addScalar("total",Hibernate.STRING);
	
			 List list = sqlquery.list();
			 
			 
			 if(list != null){
			 for(int i=0;i<list.size();i++){
				 Map  m = new HashMap();
				    if(list.get(i)!= null){
				    Object[] obj =(Object[])list.get(i);
				    if(obj[1]!=null){
				     m.put("dicValue",obj[0]);
				     m.put("dicCaption",obj[1]);
				     m.put("total",obj[2]);
				    totalList.add(m);
				    }
				    }
			 }
			 }
            return totalList;
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
   }
	
	public Maintain getMaintainById(String id) throws DBSystemException {		
		Maintain info = null;
		Session s = getSession();
		try {			
			info = (Maintain) s.get(Maintain.class, new Integer(id));			
			return info;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public List getMainType(String dicNo)throws DBSystemException{
		Session s = getSession();
		try{
			StringBuffer Hql = new StringBuffer(" from WebDictionary  d  where d.id.dicNo= '"+dicNo+"'");
			Query query = s.createQuery(Hql.toString());
			return  query.list();
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	
	public  void  addMaintain(Maintain maintain)throws DBSystemException {
		Session s = getSession();
		try{
			s.saveOrUpdate(maintain);
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public ResultPage adminQry(String userId,String status,String  type,String appBeginDate,String appEndDate,String asrBeginDate,String asrEndDate,int page,int size)throws DBSystemException {
		Session s = getSession();
		List list = new  ArrayList();
		try {			
			StringBuffer Hql = new StringBuffer("");
			if(type !=null && !"".equals(type)){
				Hql = new StringBuffer("select t.maintainId   from MaintainType  t where t.dicValue ='"+type+"'");
				if(status != null && !("").equals(status)){
					Hql.append(" and  t.maintainId.status ='"+status+"'");
				}	
				if(appBeginDate != null && !"".equals(appBeginDate)){
					Hql.append(" and t.maintainId.applyTime >='"+appBeginDate+"'");
				}
				if(appEndDate != null && !"".equals(appEndDate)){
					Hql.append(" and t.maintainId.applyTime <='"+appEndDate+"'");
				} 
				if(asrBeginDate != null && !"".equals(asrBeginDate)){
					Hql.append(" and t.maintainId.answerTime >='"+asrBeginDate+"'");
				}
				if(asrEndDate != null && !"".equals(asrEndDate)){
					Hql.append(" and t.maintainId.answerTime <='"+asrEndDate+"'");
				}
				Hql.append( " order by  t.maintainId.id desc ");
				
			}else{
				Hql = new StringBuffer(" from  Maintain m where 1=1");
				if(status != null && !("").equals(status)){
					Hql.append(" and m.status ='"+status+"'" );
				}
				if(appBeginDate != null && !"".equals(appBeginDate)){
					Hql.append(" and m.applyTime >='"+appBeginDate+"'");
				}
				if(appEndDate != null && !"".equals(appEndDate)){
					Hql.append(" and m.applyTime <='"+appEndDate+"'");
				}
				if(asrBeginDate != null && !"".equals(asrBeginDate)){
					Hql.append(" and m.answerTime >='"+asrBeginDate+"'");
				}
				if(asrEndDate != null && !"".equals(asrEndDate)){
					Hql.append(" and m.answerTime <='"+asrEndDate+"'");
				}
				Hql.append(" order by m.id desc  ");
			}
			
			Query query  = s.createQuery(Hql.toString());
			list =query.list();
			int  totalRecords =0 ;
			if(list != null ){
			  totalRecords= list.size();
			}	ResultPage result = new ResultPage(query, page, size);
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}			
			return result;
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}

	public ResultPage search(String title,String userId,String status,int page, int size) throws DBSystemException {
		
		Session s = getSession();
		List list = new  ArrayList();
		try {			
			StringBuffer Hql = new StringBuffer(" from Maintain where 1=1 ");
			if(title != null && !"".equals(title)){
				Hql.append(" and  applyInfo like ?");
			}
			if(userId != null && !"".equals(userId) && !"admin".equals(userId)){
				Hql.append(" and  applyPeople =:userId");
			}
			if(status != null && "adminQuery".equals(status)){
				Hql.append(" and answerInfo is null ");
			}
			 Hql.append(" order by id desc ");
			 Query query  = s.createQuery(Hql.toString());
			 
			 if(title != null && !"".equals(title)){
			   query.setString(0, "%" + title + "%");
			 }
			 if(userId != null && !"".equals(userId) && !"admin".equals(userId)){//admin可以查所有人的信息
				    query.setString("userId",userId);
			 }
			 list =query.list();
				int  totalRecords =0 ;
				if(list != null ){
				  totalRecords= list.size();
				}	ResultPage result = new ResultPage(query, page, size);
				int quotient = totalRecords / size;
				int remainder = totalRecords % size;
				if (remainder == 0 && quotient != 0) {
					result.setTotalPage(quotient);
				} else {
					result.setTotalPage(quotient + 1);
				}			
				return result;
			} catch (HibernateException ex) {			
				_log.error(ex);			
				throw new DBSystemException(ex.getMessage());
			}
		}
	private static final Log _log = LogFactory.getLog(MaintainPersistence.class);
}
