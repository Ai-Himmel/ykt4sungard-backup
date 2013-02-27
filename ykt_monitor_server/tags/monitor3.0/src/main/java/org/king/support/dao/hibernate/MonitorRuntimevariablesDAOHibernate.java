package org.king.support.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.support.dao.MonitorRuntimevariablesDAO;
import org.king.support.domain.MonitorRuntimevariables;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorRuntimevariables.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.support.dao.hibernate.MonitorRuntimevariables
 */
public class MonitorRuntimevariablesDAOHibernate implements MonitorRuntimevariablesDAO {
    private static final Log log = LogFactory.getLog(MonitorRuntimevariablesDAOHibernate.class);
    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorRuntimevariables instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorRuntimevariables instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorRuntimevariables get(Serializable id) {
        log.debug("getting MonitorRuntimevariables instance by id");
        return (MonitorRuntimevariables) baseDAO.getEntity(
                MonitorRuntimevariables.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorRuntimevariables all");
        String allHql = "from MonitorRuntimevariables";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorRuntimevariables transientInstance) {
        log.debug("saving MonitorRuntimevariables instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorRuntimevariables transientInstance) {
        log.debug("updating MonitorRuntimevariables instance");
        baseDAO.updateEntity(transientInstance);
    }

    public void delete(MonitorRuntimevariables persistentInstance) {
        log.debug("deleting MonitorRuntimevariables instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorRuntimevariablesByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据变量名字判断该变量是否已存在
     *
     * @param varName .
     * @return .
     */
    public boolean isExistMonitorRuntimevariables(String varName) {
        StringBuffer hql = new StringBuffer("from MonitorRuntimevariables t where t.varname='");
        hql.append(varName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}