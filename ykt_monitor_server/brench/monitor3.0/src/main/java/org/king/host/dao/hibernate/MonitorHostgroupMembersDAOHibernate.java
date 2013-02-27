package org.king.host.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.host.dao.MonitorHostgroupMembersDAO;
import org.king.host.domain.MonitorHostgroupMembers;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 * @see org.king.host.dao.MonitorHost
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorHostgroupMembersDAOHibernate implements MonitorHostgroupMembersDAO{

    private static final Log log = LogFactory.getLog(MonitorHostgroupMembersDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostgroupMembers instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorHostgroupMembers instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorHostgroupMembers get(Serializable id) {
				log.debug("getting MonitorHostgroupMembers instance by id");
				return (MonitorHostgroupMembers)baseDAO.getEntity(MonitorHostgroupMembers.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorHostgroupMembers all");
	      String allHql = "from MonitorHostgroupMembers";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorHostgroupMembers transientInstance) {
        log.debug("saving MonitorHostgroupMembers instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorHostgroupMembers transientInstance){
    	log.debug("updating MonitorHostgroupMembers instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorHostgroupMembers persistentInstance) {
		    log.debug("deleting MonitorHostgroupMembers instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}