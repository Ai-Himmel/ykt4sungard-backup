package org.king.termdev.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.termdev.dao.MonitorTermdevServiceDAO;
import org.king.termdev.domain.MonitorTermdevService;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorTermdevService.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.termdev.dao.hibernate.MonitorTermdevService
 */
public class MonitorTermdevServiceDAOHibernate implements MonitorTermdevServiceDAO {

    private static final Log log = LogFactory.getLog(MonitorTermdevServiceDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdevService instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorTermdevService instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorTermdevService get(Serializable id) {
        log.debug("getting MonitorTermdevService instance by id");
        return (MonitorTermdevService) baseDAO.getEntity(MonitorTermdevService.class, id);
    }

    public List getAll() {
        log.debug("getting MonitorTermdevService all");
        String allHql = "from MonitorTermdevService";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorTermdevService transientInstance) {
        log.debug("saving MonitorTermdevService instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorTermdevService transientInstance) {
        log.debug("updating MonitorTermdevService instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorTermdevService persistentInstance) {
        log.debug("deleting MonitorTermdevService instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorTermdevServiceByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据设备服务名称判断该设备服务是否已存在
     *
     * @param devserviceName .
     * @return .
     */
    public boolean isExistMonitorTermdevService(String devserviceName) {
        StringBuffer hql = new StringBuffer("from MonitorTermdevService t where t.devserviceName='");
        hql.append(devserviceName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}