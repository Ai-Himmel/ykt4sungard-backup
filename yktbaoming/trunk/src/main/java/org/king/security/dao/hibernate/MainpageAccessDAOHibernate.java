package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.business.domain.BmAccessInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.MainpageAccessDAO;
import org.king.security.domain.MainpageAccess;

/**
 * Data access object (DAO) for domain model class MainpageAccess.
 * @see org.king.security.dao.hibernate.MainpageAccess
 * @author MyEclipse - Hibernate Tools
 */
public class MainpageAccessDAOHibernate implements MainpageAccessDAO{

    private static final Log log = LogFactory.getLog(MainpageAccessDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MainpageAccess instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MainpageAccess instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MainpageAccess get(Serializable id) {
				log.debug("getting MainpageAccess instance by id");
				return (MainpageAccess)baseDAO.getEntity(MainpageAccess.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MainpageAccess all");
	      String allHql = "from MainpageAccess";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MainpageAccess transientInstance) {
        log.debug("saving MainpageAccess instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MainpageAccess transientInstance){
    	log.debug("updating MainpageAccess instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MainpageAccess persistentInstance) {
		    log.debug("deleting MainpageAccess instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	  public void save(BmAccessInfo transientInstance) {
	        log.debug("saving MainpageAccess instance");
	        baseDAO.saveEntity(transientInstance);
	    }

    

    


}