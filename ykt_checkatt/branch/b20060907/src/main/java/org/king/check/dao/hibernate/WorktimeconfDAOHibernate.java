package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkTimeConfDao;
import org.king.check.domain.Worktimeconf;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Worktimeconf.
 * @see org.king.check.dao.hibernate.Worktimeconf
 * @author MyEclipse - Hibernate Tools
 */
public class WorktimeconfDAOHibernate implements WorkTimeConfDao{

    private static final Log log = LogFactory.getLog(WorktimeconfDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Worktimeconf instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Worktimeconf instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Worktimeconf get(Serializable id) {
				log.debug("getting Worktimeconf instance by id");
				return (Worktimeconf)baseDAO.getEntity(Worktimeconf.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Worktimeconf all");
	      String allHql = "from Worktimeconf";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Worktimeconf transientInstance) {
        log.debug("saving Worktimeconf instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Worktimeconf transientInstance){
    	log.debug("updating Worktimeconf instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Worktimeconf persistentInstance) {
		    log.debug("deleting Worktimeconf instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}