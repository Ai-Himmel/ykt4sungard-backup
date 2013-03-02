package com.kingstargroup.ecard.hibernate.friendslink;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Criteria;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.criterion.Expression;
import org.hibernate.criterion.Property;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class FriendsLinkPersistence extends BasicPersistence {

	public void add(FriendsLink link) throws DBSystemException {
		Session s = getSession();
		try {			
			s.saveOrUpdate(link);			
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public  FriendsLink  getLinkById(String id) throws DBSystemException{
		Session s = getSession();
		try{
		FriendsLink link = (FriendsLink) s.get(FriendsLink.class,new Integer(id));
		return link;
		}catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public boolean update(FriendsLink link) throws DBSystemException {
		Session s = getSession();
		try {			
			s.update(link);			
			return true;
		} catch (HibernateException ex) {
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public boolean deleteLinkByIds(String[] ids) throws DBSystemException {
		Session s = getSession();
		try {			
			for (int i = 0; i < ids.length; i++) {
				s.delete(getLinkById(ids[i]));
			}			
			return true;
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	public List search(String title) throws DBSystemException {
		Session s = getSession();
		try {
			Criteria criteria = s.createCriteria(FriendsLink.class);
			if (title != null && !title.equals("")) {
				criteria.add(Expression.like("infoTitle", "%" + title + "%"));				
			}
			criteria.addOrder(Property.forName("createDate").desc());
			return criteria.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex);
		}
	}
	
	public ResultPage search(String linkName, String linkurl,  int page, int size) throws DBSystemException {
		Session s = getSession();
		List list = new  ArrayList();
		  
		try {			
			StringBuffer Hql = new StringBuffer( " from  FriendsLink  f where 1=1 " );
			if(linkName != null && !("").equals(linkName)){
				Hql.append(" and  f.linkName  like ?");
			}
			Hql.append(" order by  f.id");
			Query query  = s.createQuery(Hql.toString());
			if(linkName != null && !("").equals(linkName)){
			  query.setString(0, "%" + linkName + "%");
			}
			list =query.list();
			int  totalRecords =0 ;
			if(list != null ){
			  totalRecords= list.size();
			}
		/*	Criteria criteria = s.createCriteria(FriendsLink.class);
			criteria.add(Expression.in("infoType", infoType));
			
			if (title != null && !title.equals("")) {
				criteria.add(Expression.like("infoTitle", "%" + title + "%"));
			}
			if (content != null && !content.equals("")) {
				criteria.add(Expression.like("infoContent", "%" + content + "%"));
			}
			criteria.setProjection(Projections.alias(Projections.rowCount(), "countRecords"));	*/		
		/*	int totalRecords = ((Integer) criteria.uniqueResult()).intValue();
			criteria.setProjection(null);
			criteria.addOrder(Property.forName("id").desc());*/
			ResultPage result = new ResultPage(query, page, size);
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
	
	private static final Log _log = LogFactory.getLog(FriendsLinkPersistence.class);
}
