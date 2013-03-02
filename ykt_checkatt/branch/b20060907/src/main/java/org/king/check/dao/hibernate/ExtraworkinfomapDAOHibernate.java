package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ExtraworkinfomapDAO;
import org.king.check.domain.Extraworkinfomap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Extraworkinfomap.
 * @see org.king.check.dao.Extraworkinfomap
 * @author MyEclipse - Hibernate Tools
 */
public class ExtraworkinfomapDAOHibernate implements ExtraworkinfomapDAO{

    private static final Log log = LogFactory.getLog(ExtraworkinfomapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Extraworkinfomap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Extraworkinfomap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Extraworkinfomap get(Serializable id) {
				log.debug("getting Extraworkinfomap instance by id");
				return (Extraworkinfomap)baseDAO.getEntity(Extraworkinfomap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Extraworkinfomap all");
	      String allHql = "from Extraworkinfomap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Extraworkinfomap transientInstance) {
        log.debug("saving Extraworkinfomap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Extraworkinfomap transientInstance){
    	log.debug("updating Extraworkinfomap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Extraworkinfomap persistentInstance) {
		    log.debug("deleting Extraworkinfomap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}