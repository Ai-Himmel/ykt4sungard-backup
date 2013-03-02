package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.LeaveInfoDao;
import org.king.check.domain.Leaveinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Leaveinfo.
 * @see org.king.check.dao.hibernate.Leaveinfo
 * @author MyEclipse - Hibernate Tools
 */
public class LeaveinfoDAOHibernate implements LeaveInfoDao{

    private static final Log log = LogFactory.getLog(LeaveinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Leaveinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Leaveinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Leaveinfo get(Serializable id) {
				log.debug("getting Leaveinfo instance by id");
				return (Leaveinfo)baseDAO.getEntity(Leaveinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Leaveinfo all");
	      String allHql = "from Leaveinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Leaveinfo transientInstance) {
        log.debug("saving Leaveinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Leaveinfo transientInstance){
    	log.debug("updating Leaveinfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Leaveinfo persistentInstance) {
		    log.debug("deleting Leaveinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}