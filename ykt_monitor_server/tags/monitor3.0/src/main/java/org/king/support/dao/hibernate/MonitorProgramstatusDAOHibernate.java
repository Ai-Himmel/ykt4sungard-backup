package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorProgramstatusDAO;
import org.king.support.domain.MonitorProgramstatus;

/**
 * Data access object (DAO) for domain model class MonitorProgramstatus.
 * @see org.king.support.dao.hibernate.MonitorProgramstatus
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorProgramstatusDAOHibernate implements MonitorProgramstatusDAO{
	
	private static final Log log = LogFactory.getLog(MonitorProgramstatusDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorProgramstatus instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorProgramstatus instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorProgramstatus get(Serializable id) {
				log.debug("getting MonitorProgramstatus instance by id");
				return (MonitorProgramstatus)baseDAO.getEntity(MonitorProgramstatus.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorProgramstatus all");
	      String allHql = "from MonitorProgramstatus";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorProgramstatus transientInstance) {
        log.debug("saving MonitorProgramstatus instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorProgramstatus transientInstance){
    	log.debug("updating MonitorProgramstatus instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorProgramstatus persistentInstance) {
		    log.debug("deleting MonitorProgramstatus instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}