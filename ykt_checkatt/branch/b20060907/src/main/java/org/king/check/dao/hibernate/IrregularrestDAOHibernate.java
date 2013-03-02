package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.IrregularrestDao;
import org.king.check.domain.Irregularrest;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Irregularrest.
 * @see org.king.check.dao.Irregularrest
 * @author MyEclipse - Hibernate Tools
 */
public class IrregularrestDAOHibernate implements IrregularrestDao{

    private static final Log log = LogFactory.getLog(IrregularrestDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Irregularrest instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Irregularrest instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Irregularrest get(Serializable id) {
				log.debug("getting Irregularrest instance by id");
				return (Irregularrest)baseDAO.getEntity(Irregularrest.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Irregularrest all");
	      String allHql = "from Irregularrest";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Irregularrest transientInstance) {
        log.debug("saving Irregularrest instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Irregularrest transientInstance){
    	log.debug("updating Irregularrest instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Irregularrest persistentInstance) {
		    log.debug("deleting Irregularrest instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}