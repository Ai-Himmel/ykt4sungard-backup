package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkconfmapDao;
import org.king.check.domain.Workconfmap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Workconfmap.
 * @see org.king.check.dao.hibernate.Workconfmap
 * @author MyEclipse - Hibernate Tools
 */
public class WorkconfmapDAOHibernate implements WorkconfmapDao{

    private static final Log log = LogFactory.getLog(WorkconfmapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Workconfmap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Workconfmap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Workconfmap get(Serializable id) {
				log.debug("getting Workconfmap instance by id");
				return (Workconfmap)baseDAO.getEntity(Workconfmap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Workconfmap all");
	      String allHql = "from Workconfmap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Workconfmap transientInstance) {
        log.debug("saving Workconfmap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Workconfmap transientInstance){
    	log.debug("updating Workconfmap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Workconfmap persistentInstance) {
		    log.debug("deleting Workconfmap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}