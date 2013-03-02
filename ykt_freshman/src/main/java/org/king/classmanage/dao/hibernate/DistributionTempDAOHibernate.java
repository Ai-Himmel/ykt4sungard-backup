package org.king.classmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.DistributionTempDAO;
import org.king.classmanage.domain.DistributionTemp;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class DistributionTemp.
 * @see org.king.classmanage.dao.hibernate.DistributionTemp
 * @author MyEclipse - Hibernate Tools
 */
public class DistributionTempDAOHibernate implements DistributionTempDAO{

    private static final Log log = LogFactory.getLog(DistributionTempDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding DistributionTemp instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding DistributionTemp instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public DistributionTemp get(Serializable id) {
				log.debug("getting DistributionTemp instance by id");
				return (DistributionTemp)baseDAO.getEntity(DistributionTemp.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting DistributionTemp all");
	      String allHql = "from DistributionTemp";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(DistributionTemp transientInstance) {
        log.debug("saving DistributionTemp instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(DistributionTemp transientInstance){
    	log.debug("updating DistributionTemp instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(DistributionTemp persistentInstance) {
		    log.debug("deleting DistributionTemp instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}