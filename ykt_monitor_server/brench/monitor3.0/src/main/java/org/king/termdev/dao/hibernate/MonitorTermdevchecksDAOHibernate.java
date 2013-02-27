package org.king.termdev.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.termdev.dao.MonitorTermdevchecksDAO;
import org.king.termdev.domain.MonitorTermdevchecks;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorTermdevchecks.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.termdev.dao.hibernate.MonitorTermdevchecks
 */
public class MonitorTermdevchecksDAOHibernate implements MonitorTermdevchecksDAO {

    private static final Log log = LogFactory.getLog(MonitorTermdevchecksDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdevchecks instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorTermdevchecks instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorTermdevchecks get(Serializable id) {
        log.debug("getting MonitorTermdevchecks instance by id");
        return (MonitorTermdevchecks) baseDAO.getEntity(MonitorTermdevchecks.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorTermdevchecks all");
        String allHql = "from MonitorTermdevchecks";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorTermdevchecks transientInstance) {
        log.debug("saving MonitorTermdevchecks instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorTermdevchecks transientInstance) {
        log.debug("updating MonitorTermdevchecks instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorTermdevchecks persistentInstance) {
        log.debug("deleting MonitorTermdevchecks instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorTermdevchecksByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }
}