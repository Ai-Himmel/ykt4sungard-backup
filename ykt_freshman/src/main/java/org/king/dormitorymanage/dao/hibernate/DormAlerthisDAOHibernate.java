package org.king.dormitorymanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.dormitorymanage.dao.DormAlerthisDAO;
import org.king.dormitorymanage.domain.DormAlerthis;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class DormAlerthis.
 * @see org.king.dormitorymanage.dao.hibernate.DormAlerthis
 * @author MyEclipse - Hibernate Tools
 */
public class DormAlerthisDAOHibernate implements DormAlerthisDAO{

    private static final Log log = LogFactory.getLog(DormAlerthisDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding DormAlerthis instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding DormAlerthis instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public DormAlerthis get(Serializable id) {
				log.debug("getting DormAlerthis instance by id");
				return (DormAlerthis)baseDAO.getEntity(DormAlerthis.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting DormAlerthis all");
	      String allHql = "from DormAlerthis";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(DormAlerthis transientInstance) {
        log.debug("saving DormAlerthis instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(DormAlerthis transientInstance){
    	log.debug("updating DormAlerthis instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(DormAlerthis persistentInstance) {
		    log.debug("deleting DormAlerthis instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}