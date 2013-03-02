package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorktimeparamapDao;
import org.king.check.domain.Worktimeparamap;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Worktimeparamap.
 * @see org.king.check.dao.hibernate.Worktimeparamap
 * @author MyEclipse - Hibernate Tools
 */
public class WorktimeparamapDAOHibernate implements WorktimeparamapDao{

    private static final Log log = LogFactory.getLog(WorktimeparamapDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Worktimeparamap instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Worktimeparamap instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Worktimeparamap get(Serializable id) {
				log.debug("getting Worktimeparamap instance by id");
				return (Worktimeparamap)baseDAO.getEntity(Worktimeparamap.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Worktimeparamap all");
	      String allHql = "from Worktimeparamap";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Worktimeparamap transientInstance) {
        log.debug("saving Worktimeparamap instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Worktimeparamap transientInstance){
    	log.debug("updating Worktimeparamap instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Worktimeparamap persistentInstance) {
		    log.debug("deleting Worktimeparamap instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}