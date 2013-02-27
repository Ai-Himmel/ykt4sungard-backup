package org.king.termdev.dao.hibernate;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.termdev.dao.MonitorTermdeviceStatusDAO;
import org.king.termdev.domain.MonitorTermdeviceStatus;
import org.king.utils.PaginationUtil;
import org.springframework.orm.ObjectRetrievalFailureException;

import java.io.Serializable;
import java.util.List;

/**
 * Data access object (DAO) for domain model class MonitorTermdeviceStatus.
 *
 * @author MyEclipse - Hibernate Tools
 * @see org.king.termdev.dao.hibernate.MonitorTermdeviceStatus
 */
public class MonitorTermdeviceStatusDAOHibernate implements MonitorTermdeviceStatusDAO {

    private static final Log log = LogFactory.getLog(MonitorTermdeviceStatusDAOHibernate.class);

    private BaseDAO baseDAO;

    public void setBaseDAO(BaseDAO baseDAO) {
        this.baseDAO = baseDAO;
    }

    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdeviceStatus instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }

    public List find(String query) {
        log.debug("finding MonitorTermdeviceStatus instance by query");
        return baseDAO.findEntity(query);
    }

    public MonitorTermdeviceStatus get(Serializable id) {
        log.debug("getting MonitorTermdeviceStatus instance by id");
        Object temp = null;
        try {
        	temp = baseDAO.getEntity(MonitorTermdeviceStatus.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if(temp!=null){
			return (MonitorTermdeviceStatus)temp ;
		}		
		return null;
    }

    public List getAll() {
        log.debug("getting MonitorTermdeviceStatus all");
        String allHql = "from MonitorTermdeviceStatus";
        return baseDAO.findEntity(allHql);
    }

    public void save(MonitorTermdeviceStatus transientInstance) {
        log.debug("saving MonitorTermdeviceStatus instance");
        baseDAO.saveEntity(transientInstance);
    }

    public void update(MonitorTermdeviceStatus transientInstance) {
        log.debug("updating MonitorTermdeviceStatus instance");
        baseDAO.updateEntity(transientInstance);
    }


    public void delete(MonitorTermdeviceStatus persistentInstance) {
        log.debug("deleting MonitorTermdeviceStatus instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorTermdeviceStatusByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }
}