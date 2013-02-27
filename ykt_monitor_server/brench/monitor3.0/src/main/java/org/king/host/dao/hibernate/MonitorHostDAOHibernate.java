package org.king.host.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.host.dao.MonitorHostDAO;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostAll;
import org.king.utils.PaginationUtil;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.host.dao.MonitorHost
 */
public class MonitorHostDAOHibernate implements MonitorHostDAO {

    private static final Log log = LogFactory.getLog(MonitorHostDAOHibernate.class);

    protected void initDao() {
        //do nothing
    }

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHost instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorHost instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorHost get(Serializable id) {
        log.debug("getting MonitorHost instance by id");
        Object temp = null;
        try {
        	temp = baseDAO.getEntity(MonitorHost.class, id);
		} catch (Exception e) {
			// TODO: handle exception
		}
        if(temp!=null){
        	return (MonitorHost)temp ;
        }
        return null;
    }
    
    public MonitorHostAll getHostAll(Serializable id) {
        log.debug("getting MonitorHostAll instance by id");
        Object temp = null;
        try {
        	temp = baseDAO.getEntity(MonitorHostAll.class, id);
		} catch (Exception e) {
			// TODO: handle exception
		}
        if(temp!=null){
        	return (MonitorHostAll)temp ;
        }
        return null;
    }

    public List getAll() {
        log.debug("getting MonitorHost all");
        String allHql = "from MonitorHost";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorHost transientInstance) {
        log.debug("saving MonitorHost instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorHost transientInstance) {
        log.debug("updating MonitorHost instance");
        baseDAO.updateEntity(transientInstance);
    }
    
    public void updateHostAll(MonitorHostAll transientInstance) {
        log.debug("updating MonitorHost instance");
        baseDAO.updateEntity(transientInstance);
    }
    


    public void delete(MonitorHost persistentInstance) {
        log.debug("deleting MonitorHost instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorHostByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据主机地址判断该主机是否已存在
     *
     * @param hostAddress .
     * @return .
     */
    public boolean isExistMonitorHost(String hostAddress) {
        StringBuffer hql = new StringBuffer("from MonitorHost t where t.hostAddress='");
        hql.append(hostAddress);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}