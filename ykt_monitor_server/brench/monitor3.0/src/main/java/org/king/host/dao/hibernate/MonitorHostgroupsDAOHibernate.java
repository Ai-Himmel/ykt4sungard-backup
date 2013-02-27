package org.king.host.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.host.dao.MonitorHostgroupsDAO;
import org.king.host.domain.MonitorHostgroups;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.host.dao.MonitorHost
 */
public class MonitorHostgroupsDAOHibernate implements MonitorHostgroupsDAO {

    private static final Log log = LogFactory.getLog(MonitorHostgroupsDAOHibernate.class);

    protected void initDao() {
        //do nothing
    }

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostgroups instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorHostgroups instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorHostgroups get(Serializable id) {
        log.debug("getting MonitorHostgroups instance by id");
        return (MonitorHostgroups) baseDAO.getEntity(MonitorHostgroups.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorHostgroups all");
        String allHql = "from MonitorHostgroups";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorHostgroups transientInstance) {
        log.debug("saving MonitorHostgroups instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorHostgroups transientInstance) {
        log.debug("updating MonitorHostgroups instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorHostgroups persistentInstance) {
        log.debug("deleting MonitorHostgroups instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorHostgroupsByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    public boolean isExistMonitorHostgroups(String groupName) {
        StringBuffer hql = new StringBuffer("from MonitorHostgroups t where t.groupName='");
        hql.append(groupName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }


}