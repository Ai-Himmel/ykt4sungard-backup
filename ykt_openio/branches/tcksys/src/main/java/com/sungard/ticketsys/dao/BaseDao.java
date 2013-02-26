package com.sungard.ticketsys.dao;


import hibernate.HibernateSessionFactory;

import java.io.Serializable;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.hibernate.Criteria;
import org.hibernate.Query;
import org.hibernate.criterion.Order;
import org.hibernate.criterion.Restrictions;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Page;

public class BaseDao  {
	
	public void save(Object o) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();		
		session.save(0);
		tx.commit();
	}

	public void update(Object o) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();		
		session.update(0);
		tx.commit();
	}

	public void remove(Object o) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();		
		session.delete(o);
		tx.commit();
	}

	@SuppressWarnings("unchecked")
	public void removeById(Class entityClass, Serializable id) {
		this.remove(this.get(entityClass, id));
	}

	public void flush() {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();		
		session.flush();
		tx.commit();
	}

	public void clear() {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();		
		session.clear();
		tx.commit();
	}

	public Query createQuery(String hql, Object... values) {
		Session session = HibernateSessionFactory.getSession();
		Query query = session.createQuery(hql);
		for (int i = 0; i < values.length; i++) {
			query.setParameter(i, values[i]);
		}
		return query;
	}

	@SuppressWarnings("unchecked")
	public <T> List<T> getAll(Class<T> entityClass) {
		Session session = HibernateSessionFactory.getSession();
		Criteria criteria = session.createCriteria(entityClass);
		criteria.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY);
		return criteria.list();
	}

	@SuppressWarnings("unchecked")
	public <T> T get(Class<T> entityClass, Serializable id) {
		Session session = HibernateSessionFactory.getSession();
		return (T) session.get(entityClass, id);
	}

	@SuppressWarnings("unchecked")
	public List find(String hql, Object... values) {
		Session session = HibernateSessionFactory.getSession();
		Query queryObject = session.createQuery(hql);
		if (values != null) {
			for (int i = 0; i < values.length; i++) {
				queryObject.setParameter(i, values[i]);
			}
		}
		return queryObject.list();
		
	}

	@SuppressWarnings("unchecked")
	public <T> List<T> findBy(Class<T> entity, String propertyName, Object value) {
		Session session = HibernateSessionFactory.getSession();
		Criteria c =session.createCriteria(entity);
		c.add(Restrictions.eq(propertyName, value));
		return c.list();
	}

	@SuppressWarnings("unchecked")
	public <T> List<T> findBy(Class<T> entity, String propertyName,
			Object value, String orderBy, boolean isAsc) {
		Session session = HibernateSessionFactory.getSession();
		Criteria c = session.createCriteria(entity);
		c.add(Restrictions.eq(propertyName, value));
		if (isAsc) {
			c.addOrder(Order.asc(orderBy));
		}
		else {
			c.addOrder(Order.desc(orderBy));
		}
		return c.list();
	}

	private static String removeSelect(String hql) {
		int begin = hql.indexOf("from");
		return hql.substring(begin);
	}

	/**
	 * 去除hql的orderby 子句，用于pageQuery.
	 *
	 * @see #pagedQuery(String,int,int,Object[])
	 */
	private static String removeOrders(String hql) {
		Pattern p = Pattern.compile("order\\s*by[\\w|\\W|\\s|\\S]*",
				Pattern.CASE_INSENSITIVE);
		Matcher m = p.matcher(hql);
		StringBuffer sb = new StringBuffer();
		while (m.find()) {
			m.appendReplacement(sb, "");
		}
		m.appendTail(sb);
		return sb.toString();
	}

	@SuppressWarnings({ "static-access", "unchecked" })
	public Page pageQuery(String hql, int pageNo, int pageSize,
			Object... values) {
		Session session = HibernateSessionFactory.getSession();
		String countQueryString = " select count(*) "
				+ removeSelect(removeOrders(hql));
		List countList = find(countQueryString,values);
		long totalCount = (Long) countList.get(0);

		if (totalCount < 1) {
			return new Page();
		}
		int startIndex = Page.getStartOfPage(pageNo, pageSize);
		Transaction transaction = session.beginTransaction();
		Query query = session.createQuery(hql);
		for (int i = 0; i < values.length; i++) {
			query.setParameter(i, values[i]);
		}
		List list = query.setFirstResult(startIndex).setMaxResults(pageSize)
				.list();
		transaction.commit();
		return new Page(startIndex, totalCount, pageSize, list);
	}
	
	
}
