package org.king.hostservice.dao.hibernate;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.hostservice.dao.MonitorServiceCheckDAO;
import org.king.hostservice.domain.MonitorServiceCheck;
import org.king.utils.PaginationUtil;
import org.springframework.orm.ObjectRetrievalFailureException;
import org.springframework.orm.hibernate3.HibernateCallback;

/**
 * Data access object (DAO) for domain model class MonitorServiceCheck.
 * 
 * @see org.king.hostservice.dao.hibernate.MonitorServiceCheck
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorServiceCheckDAOHibernate implements MonitorServiceCheckDAO {

	private static final Log log = LogFactory
			.getLog(MonitorServiceCheckDAOHibernate.class);

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding MonitorServiceCheck instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding MonitorServiceCheck instance by query");
		return baseDAO.findEntity(query);
	}

	public MonitorServiceCheck get(Serializable id) {
		log.debug("getting MonitorServiceCheck instance by id");
		Object temp = null;
		try {
			temp = baseDAO.getEntity(MonitorServiceCheck.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if (temp != null) {
			return (MonitorServiceCheck) temp;
		}
		return null;
	}

	public List getAll() {
		log.debug("getting MonitorServiceCheck all");
		String allHql = "from MonitorServiceCheck";
		return baseDAO.findEntity(allHql);
	}

	public void save(MonitorServiceCheck transientInstance) {
		log.debug("saving MonitorServiceCheck instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(MonitorServiceCheck transientInstance) {
		log.debug("updating MonitorServiceCheck instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(MonitorServiceCheck persistentInstance) {
		log.debug("deleting MonitorServiceCheck instance");
		baseDAO.removeEntity(persistentInstance);
	}

    public void findMonitorServiceCheckByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public void execute(final String hql) {
        ((BaseDAOHibernate)baseDAO).getHibernateTemplate().execute(new HibernateCallback() {
            public Object doInHibernate(Session session) throws HibernateException, SQLException {
                Query query = session.createQuery(hql);
                return query.executeUpdate();
            }
        });
    }
}