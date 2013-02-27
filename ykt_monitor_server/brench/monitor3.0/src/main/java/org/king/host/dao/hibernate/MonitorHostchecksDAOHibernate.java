package org.king.host.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.host.dao.MonitorHostchecksDAO;
import org.king.host.domain.MonitorHostchecks;
import org.king.utils.PaginationUtil;
import org.springframework.orm.hibernate3.HibernateCallback;

import java.io.Serializable;
import java.sql.SQLException;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.host.dao.MonitorHost
 */
public class MonitorHostchecksDAOHibernate implements MonitorHostchecksDAO {

    private static final Log log = LogFactory.getLog(MonitorHostchecksDAOHibernate.class);

    protected void initDao() {
        //do nothing
    }

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostchecks instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorHostchecks instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorHostchecks get(Serializable id) {
        log.debug("getting MonitorHostchecks instance by id");
        return (MonitorHostchecks) baseDAO.getEntity(MonitorHostchecks.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorHostchecks all");
        String allHql = "from MonitorHostchecks";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorHostchecks transientInstance) {
        log.debug("saving MonitorHostchecks instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorHostchecks transientInstance) {
        log.debug("updating MonitorHostchecks instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorHostchecks persistentInstance) {
        log.debug("deleting MonitorHostchecks instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorHostchecksByPage(DBPaginatedList page, MyQuery myQuery) {
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