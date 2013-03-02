package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.IrregularrestmapDao;
import org.king.check.domain.Irregularrestmap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Irregularrestmap.
 * @see org.king.check.dao.Irregularrestmap
 * @author MyEclipse - Hibernate Tools
 */
public class IrregularrestmapDAOHibernate implements IrregularrestmapDao{

    private static final Log log = LogFactory.getLog(IrregularrestmapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Irregularrestmap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Irregularrestmap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Irregularrestmap get(Serializable id) {
				log.debug("getting Irregularrestmap instance by id");
				return (Irregularrestmap)baseDAO.getEntity(Irregularrestmap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Irregularrestmap all");
	      String allHql = "from Irregularrestmap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Irregularrestmap transientInstance) {
        log.debug("saving Irregularrestmap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Irregularrestmap transientInstance){
    	log.debug("updating Irregularrestmap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Irregularrestmap persistentInstance) {
		    log.debug("deleting Irregularrestmap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}