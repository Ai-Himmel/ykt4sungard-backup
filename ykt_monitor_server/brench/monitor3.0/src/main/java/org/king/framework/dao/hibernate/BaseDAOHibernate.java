package org.king.framework.dao.hibernate;

import java.io.Serializable;
import java.sql.Date;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.Para;
import org.springframework.orm.ObjectRetrievalFailureException;
import org.springframework.orm.hibernate3.HibernateCallback;
import org.springframework.orm.hibernate3.support.HibernateDaoSupport;

public class BaseDAOHibernate extends HibernateDaoSupport implements BaseDAO {
	protected final Log log = LogFactory.getLog(getClass());

	public List findEntity(MyQuery myQuery) {
		List returnList = null;
		if (myQuery.isCache()) {
			returnList = new ArrayList();

			for (Iterator it = getQuery(myQuery).iterate(); it.hasNext();)
				returnList.add(it.next());
		} else {
			returnList = getQuery(myQuery).list();
		}
		return returnList;
	}

	public List findEntity(String query) {
		MyQuery myquery = new MyQuery();
		myquery.setQueryString(query);

		return findEntity(myquery);
	}

	public Object getEntity(Class clazz, Serializable id) {
		Object obj = getHibernateTemplate().get(clazz, id);

		if (obj == null) {
			throw new ObjectRetrievalFailureException(clazz, id);
		}

		return obj;
	}

	public void saveEntity(Object obj) {
		getHibernateTemplate().save(obj);
	}

	public void updateEntity(Object obj) {
		getHibernateTemplate().update(obj);
	}

	public void removeEntity(Object obj) {
		getHibernateTemplate().delete(obj);
	}

	private Query getQuery(final MyQuery myquery) {
		return (Query) getHibernateTemplate().execute(new HibernateCallback() {

			public Object doInHibernate(Session session)
					throws HibernateException {
				StringBuffer querystr = new StringBuffer(myquery
						.getQueryString());

				if (myquery.getOrderby() != null) {
					querystr.append(myquery.getOrderby());
				}

				if (myquery.getGroupby() != null) {
					querystr.append(myquery.getGroupby());
				}
				Query query = session.createQuery(querystr.toString());
				if (myquery.getParalist() != null) {
					List list = myquery.getParalist();

					int i = 0;
					for (int n = list.size(); i < n; i++) {
						Para param = (Para) list.get(i);

						switch (param.getTypeNo()) {
						case 12:
							query.setString(i, param.getPName().toString());

							break;
						case 4:
							query.setInteger(i, ((Integer) param.getPName())
									.intValue());

							break;
						case 91:
							query.setDate(i, (Date) param.getPName());

							break;
						case 8:
							query.setDouble(i, ((Double) param.getPName())
									.doubleValue());

							break;
						case 16:
							query.setBoolean(i, ((Boolean) param.getPName())
									.booleanValue());

							break;
						case 1:
							query.setCharacter(i,
									((Character) param.getPName()).charValue());
						}

					}

				}

				if ((myquery.getPageStartNo() != 0) || (myquery.isOffset())) {
					int pageno = myquery.getPageStartNo();
					query.setFirstResult(pageno);
					query.setMaxResults(pageno + myquery.getPageSize());
				}

				query.setCacheable(true);
				query.setCacheRegion("frontpages");
				return query;
			}
		});
	}
}