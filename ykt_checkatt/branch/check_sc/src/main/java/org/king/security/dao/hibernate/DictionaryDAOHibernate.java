package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.security.dao.DictionaryDAO;
import org.king.security.domain.Dictionary;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Dictionary.
 * @see org.king.classmanage.dao.hibernate.Dictionary
 * @author MyEclipse - Hibernate Tools
 */
public class DictionaryDAOHibernate implements DictionaryDAO{

    private static final Log log = LogFactory.getLog(DictionaryDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Dictionary instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Dictionary instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Dictionary get(Serializable id) {
				log.debug("getting Dictionary instance by id");
				return (Dictionary)baseDAO.getEntity(Dictionary.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Dictionary all");
	      String allHql = "from Dictionary";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Dictionary transientInstance) {
        log.debug("saving Dictionary instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Dictionary transientInstance){
    	log.debug("updating Dictionary instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Dictionary persistentInstance) {
		    log.debug("deleting Dictionary instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}