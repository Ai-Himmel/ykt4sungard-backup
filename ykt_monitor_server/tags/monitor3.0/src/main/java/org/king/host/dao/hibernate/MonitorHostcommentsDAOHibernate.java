package org.king.host.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.host.dao.MonitorHostcommentsDAO;
import org.king.host.domain.MonitorHostcomments;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 * @see org.king.host.dao.MonitorHost
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorHostcommentsDAOHibernate implements MonitorHostcommentsDAO{

    private static final Log log = LogFactory.getLog(MonitorHostcommentsDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostcomments instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorHostcomments instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorHostcomments get(Serializable id) {
				log.debug("getting MonitorHostcomments instance by id");
				return (MonitorHostcomments)baseDAO.getEntity(MonitorHostcomments.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorHostcomments all");
	      String allHql = "from MonitorHostcomments";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorHostcomments transientInstance) {
        log.debug("saving MonitorHostcomments instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorHostcomments transientInstance){
    	log.debug("updating MonitorHostcomments instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorHostcomments persistentInstance) {
		    log.debug("deleting MonitorHostcomments instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}