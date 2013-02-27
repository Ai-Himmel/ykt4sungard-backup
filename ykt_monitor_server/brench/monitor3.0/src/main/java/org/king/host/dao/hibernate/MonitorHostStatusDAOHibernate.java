package org.king.host.dao.hibernate;

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
import org.king.host.dao.MonitorHostStatusDAO;
import org.king.host.domain.MonitorHostStatus;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.utils.PaginationUtil;
import org.springframework.orm.ObjectRetrievalFailureException;
import org.springframework.orm.hibernate3.HibernateCallback;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 * 
 * @see org.king.host.dao.MonitorHost
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorHostStatusDAOHibernate implements MonitorHostStatusDAO {

	private static final Log log = LogFactory
			.getLog(MonitorHostStatusDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding MonitorHostStatus instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding MonitorHostStatus instance by query");
		return baseDAO.findEntity(query);
	}

	public MonitorHostStatus get(Serializable id) {
		log.debug("getting MonitorHostStatus instance by id");
		Object temp = null;
		try {
			temp = baseDAO.getEntity(MonitorHostStatus.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if (temp != null) {
			return (MonitorHostStatus) temp;
		}
		return null;
	}

	public List getAll() {
		log.debug("getting MonitorHostStatus all");
		String allHql = "from MonitorHostStatus";
		return baseDAO.findEntity(allHql);
	}

	public void save(MonitorHostStatus transientInstance) {
		log.debug("saving MonitorHostStatus instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(MonitorHostStatus transientInstance) {
		log.debug("updating MonitorHostStatus instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(MonitorHostStatus persistentInstance) {
		log.debug("deleting MonitorHostStatus instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public void findMonitorHostStatusByPage(DBPaginatedList page,
			MyQuery myQuery) {
		PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO,
				myQuery);
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