package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoGroupInfoDAO;
import org.king.topo.domain.MonitorTopoGroupInfo;

/**
 * Data access object (DAO) for domain model class MonitorTopoGroupInfo.
 * @see org.king.topo.dao.MonitorTopoGroupInfo
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTopoGroupInfoDAOHibernate implements MonitorTopoGroupInfoDAO{

    private static final Log log = LogFactory.getLog(MonitorTopoGroupInfoDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTopoGroupInfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTopoGroupInfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTopoGroupInfo get(Serializable id) {
				log.debug("getting MonitorTopoGroupInfo instance by id");
				return (MonitorTopoGroupInfo)baseDAO.getEntity(MonitorTopoGroupInfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTopoGroupInfo all");
	      String allHql = "from MonitorTopoGroupInfo order by devicegroupid";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTopoGroupInfo transientInstance) {
        log.debug("saving MonitorTopoGroupInfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTopoGroupInfo transientInstance){
    	log.debug("updating MonitorTopoGroupInfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTopoGroupInfo persistentInstance) {
		    log.debug("deleting MonitorTopoGroupInfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}