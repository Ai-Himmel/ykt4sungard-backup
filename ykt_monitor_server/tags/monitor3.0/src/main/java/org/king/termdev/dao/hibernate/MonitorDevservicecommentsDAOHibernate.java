package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.dao.MonitorDevservicecommentsDAO;
import org.king.termdev.domain.MonitorDevservicecomments;

/**
 * Data access object (DAO) for domain model class MonitorDevservicecomments.
 * @see org.king.termdev.dao.hibernate.MonitorDevservicecomments
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorDevservicecommentsDAOHibernate implements MonitorDevservicecommentsDAO{

    private static final Log log = LogFactory.getLog(MonitorDevservicecommentsDAOHibernate.class);

    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorDevservicecomments instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorDevservicecomments instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorDevservicecomments get(Serializable id) {
				log.debug("getting MonitorDevservicecomments instance by id");
				return (MonitorDevservicecomments)baseDAO.getEntity(MonitorDevservicecomments.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorDevservicecomments all");
	      String allHql = "from MonitorDevservicecomments";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorDevservicecomments transientInstance) {
        log.debug("saving MonitorDevservicecomments instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorDevservicecomments transientInstance){
    	log.debug("updating MonitorDevservicecomments instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorDevservicecomments persistentInstance) {
		    log.debug("deleting MonitorDevservicecomments instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}