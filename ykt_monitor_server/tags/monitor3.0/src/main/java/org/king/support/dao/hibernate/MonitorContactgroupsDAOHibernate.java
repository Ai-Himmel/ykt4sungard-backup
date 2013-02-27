package org.king.support.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.support.dao.MonitorContactgroupsDAO;
import org.king.support.domain.MonitorContactgroups;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorContactgroups.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.support.dao.hibernate.MonitorContactgroups
 */
public class MonitorContactgroupsDAOHibernate implements MonitorContactgroupsDAO {
    private static final Log log = LogFactory.getLog(MonitorContactgroupsDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorContactgroups instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorContactgroups instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorContactgroups get(Serializable id) {
        log.debug("getting MonitorContactgroups instance by id");
        return (MonitorContactgroups) baseDAO.getEntity(MonitorContactgroups.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorContactgroups all");
        String allHql = "from MonitorContactgroups";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorContactgroups transientInstance) {
        log.debug("saving MonitorContactgroups instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorContactgroups transientInstance) {
        log.debug("updating MonitorContactgroups instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorContactgroups persistentInstance) {
        log.debug("deleting MonitorContactgroups instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorContactgroupsByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public boolean isExistMonitorContactgroups(String groupName) {
        StringBuffer hql = new StringBuffer("from MonitorContactgroups t where t.contactgroupName='");
        hql.append(groupName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}