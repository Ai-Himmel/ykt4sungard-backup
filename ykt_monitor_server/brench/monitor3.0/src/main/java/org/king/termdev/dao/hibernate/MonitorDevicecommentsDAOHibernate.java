package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.dao.MonitorDevicecommentsDAO;
import org.king.termdev.domain.MonitorDevicecomments;

/**
 * Data access object (DAO) for domain model class MonitorDevicecomments.
 * @see org.king.termdev.dao.hibernate.MonitorDevicecomments
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorDevicecommentsDAOHibernate implements MonitorDevicecommentsDAO{

    private static final Log log = LogFactory.getLog(MonitorDevicecommentsDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorDevicecomments instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorDevicecomments instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorDevicecomments get(Serializable id) {
				log.debug("getting MonitorDevicecomments instance by id");
				return (MonitorDevicecomments)baseDAO.getEntity(MonitorDevicecomments.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorDevicecomments all");
	      String allHql = "from MonitorDevicecomments";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorDevicecomments transientInstance) {
        log.debug("saving MonitorDevicecomments instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorDevicecomments transientInstance){
    	log.debug("updating MonitorDevicecomments instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorDevicecomments persistentInstance) {
		    log.debug("deleting MonitorDevicecomments instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}