package org.king.hostservice.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.hostservice.dao.MonitorServiceDAO;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceAll;
import org.king.utils.PaginationUtil;
import org.springframework.orm.ObjectRetrievalFailureException;

/**
 * Data access object (DAO) for domain model class MonitorService.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.hostservice.dao.hibernate.MonitorService
 */
public class MonitorServiceDAOHibernate implements MonitorServiceDAO {

    private static final Log log = LogFactory.getLog(MonitorServiceDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorService instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorService instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorService get(Serializable id) {
        log.debug("getting MonitorService instance by id");
        Object temp = null;
        try {
        	temp = baseDAO.getEntity(MonitorService.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if(temp!=null){
			return (MonitorService)temp ;
		}		
		return null;
    }
    
    public MonitorServiceAll getServiceAll(Serializable id) {
        log.debug("getting MonitorServiceAll instance by id");
        Object temp = null;
        try {
        	temp = baseDAO.getEntity(MonitorServiceAll.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if(temp!=null){
			return (MonitorServiceAll)temp ;
		}		
		return null;
    }

    public List getAll() {
        log.debug("getting MonitorService all");
        String allHql = "from MonitorService";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorService transientInstance) {
        log.debug("saving MonitorService instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorService transientInstance) {
        log.debug("updating MonitorService instance");
        baseDAO.updateEntity(transientInstance);
    }
    
    public void updateServiceAll(MonitorServiceAll transientInstance) {
        log.debug("updating MonitorServiceAll instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorService persistentInstance) {
        log.debug("deleting MonitorService instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorServiceByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据主机服务名称判断该主机服务是否已存在
     *
     * @param serviceName .
     * @return .
     */
    public boolean isExistMonitorService(String serviceName) {
        StringBuffer hql = new StringBuffer("from MonitorService t where t.serviceName='");
        hql.append(serviceName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}