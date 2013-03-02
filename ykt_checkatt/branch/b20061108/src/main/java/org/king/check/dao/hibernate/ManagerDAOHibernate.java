package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ManagerDao;
import org.king.check.domain.Manager;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Manager.
 * @see org.king.check.dao.hibernate.Manager
 * @author MyEclipse - Hibernate Tools
 */
public class ManagerDAOHibernate implements ManagerDao{

    private static final Log log = LogFactory.getLog(ManagerDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Manager instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Manager instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Manager get(Serializable id) {
				log.debug("getting Manager instance by id");
				return (Manager)baseDAO.getEntity(Manager.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Manager all");
	      String allHql = "from Manager";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Manager transientInstance) {
        log.debug("saving Manager instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Manager transientInstance){
    	log.debug("updating Manager instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Manager persistentInstance) {
		    log.debug("deleting Manager instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}