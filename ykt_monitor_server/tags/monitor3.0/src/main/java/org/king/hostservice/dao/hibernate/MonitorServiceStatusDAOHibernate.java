package org.king.hostservice.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.hostservice.dao.MonitorServiceStatusDAO;
import org.king.hostservice.domain.MonitorServiceStatus;
import org.king.utils.PaginationUtil;
import org.springframework.orm.ObjectRetrievalFailureException;
import org.springframework.orm.hibernate3.HibernateCallback;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorServiceStatus.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.hostservice.dao.hibernate.MonitorServiceStatus
 */
public class MonitorServiceStatusDAOHibernate implements MonitorServiceStatusDAO {

    private static final Log log = LogFactory.getLog(MonitorServiceStatusDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorServiceStatus instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorServiceStatus instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorServiceStatus get(Serializable id) {
        log.debug("getting MonitorServiceStatus instance by id");
        Object temp = null;
        try {
            temp = baseDAO.getEntity(MonitorServiceStatus.class, id);
        } catch (ObjectRetrievalFailureException e) {
            // TODO: handle exception
        }
        if (temp != null) {
            return (MonitorServiceStatus) temp;
        }
        return null;
    }

    public List getAll() {
        log.debug("getting MonitorServiceStatus all");
        String allHql = "from MonitorServiceStatus";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorServiceStatus transientInstance) {
        log.debug("saving MonitorServiceStatus instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorServiceStatus transientInstance) {
        log.debug("updating MonitorServiceStatus instance");
        baseDAO.updateEntity(transientInstance);
    }

    public void delete(MonitorServiceStatus persistentInstance) {
        log.debug("deleting MonitorServiceStatus instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorServiceStatusByPage(DBPaginatedList page,
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