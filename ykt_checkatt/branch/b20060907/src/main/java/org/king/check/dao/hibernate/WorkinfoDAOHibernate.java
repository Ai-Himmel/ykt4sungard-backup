package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkInfoDao;
import org.king.check.domain.Workinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Workinfo.
 * @see org.king.check.dao.hibernate.Workinfo
 * @author MyEclipse - Hibernate Tools
 */
public class WorkinfoDAOHibernate implements WorkInfoDao{

    private static final Log log = LogFactory.getLog(WorkinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Workinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Workinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Workinfo get(Serializable id) {
				log.debug("getting Workinfo instance by id");
				return (Workinfo)baseDAO.getEntity(Workinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Workinfo all");
	      String allHql = "from Workinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Workinfo transientInstance) {
        log.debug("saving Workinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Workinfo transientInstance){
    	log.debug("updating Workinfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Workinfo persistentInstance) {
		    log.debug("deleting Workinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}