package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.termdev.dao.MonitorTermdevserviceStatusDAO;
import org.king.termdev.domain.MonitorTermdevserviceStatus;
import org.king.utils.PaginationUtil;

/**
 * Data access object (DAO) for domain model class MonitorTermdevserviceStatus.
 * @see org.king.termdev.dao.hibernate.MonitorTermdevserviceStatus
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTermdevserviceStatusDAOHibernate implements MonitorTermdevserviceStatusDAO{

    private static final Log log = LogFactory.getLog(MonitorTermdevserviceStatusDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdevserviceStatus instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTermdevserviceStatus instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTermdevserviceStatus get(Serializable id) {
				log.debug("getting MonitorTermdevserviceStatus instance by id");
				return (MonitorTermdevserviceStatus)baseDAO.getEntity(MonitorTermdevserviceStatus.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTermdevserviceStatus all");
	      String allHql = "from MonitorTermdevserviceStatus";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTermdevserviceStatus transientInstance) {
        log.debug("saving MonitorTermdevserviceStatus instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTermdevserviceStatus transientInstance){
    	log.debug("updating MonitorTermdevserviceStatus instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTermdevserviceStatus persistentInstance) {
		    log.debug("deleting MonitorTermdevserviceStatus instance");
        baseDAO.removeEntity(persistentInstance);
    }

    public void findMonitorTermdevserviceStatusByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }
}