package org.king.template.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.template.dao.MonitorTimerangerDAO;
import org.king.template.domain.MonitorTimeranger;

/**
 * Data access object (DAO) for domain model class MonitorTimeranger.
 * @see org.king.template.dao.hibernate.MonitorTimeranger
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTimerangerDAOHibernate implements MonitorTimerangerDAO{

    private static final Log log = LogFactory.getLog(MonitorTimerangerDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTimeranger instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTimeranger instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTimeranger get(Serializable id) {
				log.debug("getting MonitorTimeranger instance by id");
				return (MonitorTimeranger)baseDAO.getEntity(MonitorTimeranger.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTimeranger all");
	      String allHql = "from MonitorTimeranger";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTimeranger transientInstance) {
        log.debug("saving MonitorTimeranger instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTimeranger transientInstance){
    	log.debug("updating MonitorTimeranger instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTimeranger persistentInstance) {
		    log.debug("deleting MonitorTimeranger instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}