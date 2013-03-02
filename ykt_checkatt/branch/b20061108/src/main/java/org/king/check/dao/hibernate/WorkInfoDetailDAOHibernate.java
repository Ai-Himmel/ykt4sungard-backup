package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkInfoDetailDAO;
import org.king.check.domain.Workinfodetail;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class WorkInfoDetail.
 * @see org.king.check.dao.hibernate.WorkInfoDetail
 * @author MyEclipse - Hibernate Tools
 */
public class WorkInfoDetailDAOHibernate implements WorkInfoDetailDAO{

    private static final Log log = LogFactory.getLog(WorkInfoDetailDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding WorkInfoDetail instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding WorkInfoDetail instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Workinfodetail get(Serializable id) {
				log.debug("getting WorkInfoDetail instance by id");
				return (Workinfodetail)baseDAO.getEntity(Workinfodetail.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting WorkInfoDetail all");
	      String allHql = "from WorkInfoDetail";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Workinfodetail transientInstance) {
        log.debug("saving WorkInfoDetail instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Workinfodetail transientInstance){
    	log.debug("updating WorkInfoDetail instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Workinfodetail persistentInstance) {
		    log.debug("deleting WorkInfoDetail instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}