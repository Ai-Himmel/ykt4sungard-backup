package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.FirstpageAccessDAO;
import org.king.security.domain.FirstpageAccess;

/**
 * Data access object (DAO) for domain model class FirstpageAccess.
 * @see org.king.security.dao.hibernate.FirstpageAccess
 * @author MyEclipse - Hibernate Tools
 */
public class FirstpageAccessDAOHibernate implements FirstpageAccessDAO{

    private static final Log log = LogFactory.getLog(FirstpageAccessDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding FirstpageAccess instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding FirstpageAccess instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public FirstpageAccess get(Serializable id) {
				log.debug("getting FirstpageAccess instance by id");
				return (FirstpageAccess)baseDAO.getEntity(FirstpageAccess.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting FirstpageAccess all");
	      String allHql = "from FirstpageAccess";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(FirstpageAccess transientInstance) {
        log.debug("saving FirstpageAccess instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(FirstpageAccess transientInstance){
    	log.debug("updating FirstpageAccess instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(FirstpageAccess persistentInstance) {
		    log.debug("deleting FirstpageAccess instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}