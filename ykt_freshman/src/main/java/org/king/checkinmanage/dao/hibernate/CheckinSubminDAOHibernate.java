package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.CheckinSubminDAO;
import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class CheckinSubmin.
 * @see org.king.checkinmanage.dao.hibernate.CheckinSubmin
 * @author MyEclipse - Hibernate Tools
 */
public class CheckinSubminDAOHibernate implements CheckinSubminDAO{

    private static final Log log = LogFactory.getLog(CheckinSubminDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding CheckinSubmin instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding CheckinSubmin instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public CheckinSubmin get(Serializable id) {
				log.debug("getting CheckinSubmin instance by id");
				return (CheckinSubmin)baseDAO.getEntity(CheckinSubmin.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting CheckinSubmin all");
	      String allHql = "from CheckinSubmin";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(CheckinSubmin transientInstance) {
        log.debug("saving CheckinSubmin instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(CheckinSubmin transientInstance){
    	log.debug("updating CheckinSubmin instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(CheckinSubmin persistentInstance) {
		    log.debug("deleting CheckinSubmin instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}