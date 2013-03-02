package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.StuCardfeeSubmitDAO;
import org.king.checkinmanage.domain.StuCardfeeSubmit;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class StuCardfeeSubmit.
 * @see org.king.checkinmanage.dao.hibernate.StuCardfeeSubmit
 * @author MyEclipse - Hibernate Tools
 */
public class StuCardfeeSubmitDAOHibernate implements StuCardfeeSubmitDAO{

    private static final Log log = LogFactory.getLog(StuCardfeeSubmitDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding StuCardfeeSubmit instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding StuCardfeeSubmit instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public StuCardfeeSubmit get(Serializable id) {
				log.debug("getting StuCardfeeSubmit instance by id");
				return (StuCardfeeSubmit)baseDAO.getEntity(StuCardfeeSubmit.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting StuCardfeeSubmit all");
	      String allHql = "from StuCardfeeSubmit";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(StuCardfeeSubmit transientInstance) {
        log.debug("saving StuCardfeeSubmit instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(StuCardfeeSubmit transientInstance){
    	log.debug("updating StuCardfeeSubmit instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(StuCardfeeSubmit persistentInstance) {
		    log.debug("deleting StuCardfeeSubmit instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}