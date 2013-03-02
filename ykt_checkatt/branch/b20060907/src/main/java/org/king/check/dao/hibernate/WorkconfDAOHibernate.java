package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkConfDao;
import org.king.check.domain.Workconf;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Workconf.
 * @see org.king.check.dao.hibernate.Workconf
 * @author MyEclipse - Hibernate Tools
 */
public class WorkconfDAOHibernate implements WorkConfDao{

    private static final Log log = LogFactory.getLog(WorkconfDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Workconf instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Workconf instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Workconf get(Serializable id) {
				log.debug("getting Workconf instance by id");
				return (Workconf)baseDAO.getEntity(Workconf.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Workconf all");
	      String allHql = "from Workconf";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Workconf transientInstance) {
        log.debug("saving Workconf instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Workconf transientInstance){
    	log.debug("updating Workconf instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Workconf persistentInstance) {
		    log.debug("deleting Workconf instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}