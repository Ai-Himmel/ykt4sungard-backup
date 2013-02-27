package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorTimedeventqueueDAO;
import org.king.support.domain.MonitorTimedeventqueue;

/**
 * Data access object (DAO) for domain model class MonitorTimedeventqueue.
 * @see org.king.support.dao.MonitorTimedeventqueue
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTimedeventqueueDAOHibernate implements MonitorTimedeventqueueDAO{

    private static final Log log = LogFactory.getLog(MonitorTimedeventqueueDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTimedeventqueue instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTimedeventqueue instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTimedeventqueue get(Serializable id) {
				log.debug("getting MonitorTimedeventqueue instance by id");
				return (MonitorTimedeventqueue)baseDAO.getEntity(MonitorTimedeventqueue.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTimedeventqueue all");
	      String allHql = "from MonitorTimedeventqueue";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTimedeventqueue transientInstance) {
        log.debug("saving MonitorTimedeventqueue instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTimedeventqueue transientInstance){
    	log.debug("updating MonitorTimedeventqueue instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTimedeventqueue persistentInstance) {
		    log.debug("deleting MonitorTimedeventqueue instance");
        baseDAO.removeEntity(persistentInstance);
    }

	public MonitorTimedeventqueue findMonitorTimedeventqueueByObjectAndType(
			Integer objectId, Integer eventType) {
		// TODO Auto-generated method stub
		List list = find("from MonitorTimedeventqueue where objectId="+objectId+" and eventType="+eventType);
		if(list!=null&&list.size()>0){
			return (MonitorTimedeventqueue)list.get(0);
		}
		return null;
	}
    
	

    

    


}