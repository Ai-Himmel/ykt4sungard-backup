package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkInfoDetailMapDAO;
import org.king.check.domain.Workinfodetailmap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class WorkInfoDetailMap.
 * @see org.king.check.dao.hibernate.WorkInfoDetailMapDAO
 * @author MyEclipse - Hibernate Tools
 */
public class WorkInfoDetailMapDAOHibernate implements WorkInfoDetailMapDAO{

    private static final Log log = LogFactory.getLog(WorkInfoDetailMapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding WorkInfoDetailMap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding WorkInfoDetailMap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Workinfodetailmap get(Serializable id) {
				log.debug("getting WorkInfoDetailMap instance by id");
				return (Workinfodetailmap)baseDAO.getEntity(Workinfodetailmap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting WorkInfoDetailMap all");
	      String allHql = "from WorkInfoDetailMap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Workinfodetailmap transientInstance) {
        log.debug("saving WorkInfoDetailMap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Workinfodetailmap transientInstance){
    	log.debug("updating WorkInfoDetailMap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Workinfodetailmap persistentInstance) {
		    log.debug("deleting WorkInfoDetailMap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}