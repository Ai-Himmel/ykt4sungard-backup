package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.LeaveinfomapDao;
import org.king.check.domain.Leaveinfomap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Leaveinfomap.
 * @see org.king.check.dao.hibernate.Leaveinfomap
 * @author MyEclipse - Hibernate Tools
 */
public class LeaveinfomapDAOHibernate implements LeaveinfomapDao{

    private static final Log log = LogFactory.getLog(LeaveinfomapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Leaveinfomap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Leaveinfomap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Leaveinfomap get(Serializable id) {
				log.debug("getting Leaveinfomap instance by id");
				return (Leaveinfomap)baseDAO.getEntity(Leaveinfomap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Leaveinfomap all");
	      String allHql = "from Leaveinfomap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Leaveinfomap transientInstance) {
        log.debug("saving Leaveinfomap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Leaveinfomap transientInstance){
    	log.debug("updating Leaveinfomap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Leaveinfomap persistentInstance) {
		    log.debug("deleting Leaveinfomap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}