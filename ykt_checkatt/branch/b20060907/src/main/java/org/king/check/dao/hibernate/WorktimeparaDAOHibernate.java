package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkConfTimeParaDao;
import org.king.check.domain.Worktimepara;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Worktimepara.
 * @see org.king.check.dao.hibernate.Worktimepara
 * @author MyEclipse - Hibernate Tools
 */
public class WorktimeparaDAOHibernate implements WorkConfTimeParaDao{

    private static final Log log = LogFactory.getLog(WorktimeparaDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Worktimepara instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Worktimepara instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Worktimepara get(Serializable id) {
				log.debug("getting Worktimepara instance by id");
				return (Worktimepara)baseDAO.getEntity(Worktimepara.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Worktimepara all");
	      String allHql = "from Worktimepara";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Worktimepara transientInstance) {
        log.debug("saving Worktimepara instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Worktimepara transientInstance){
    	log.debug("updating Worktimepara instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Worktimepara persistentInstance) {
		    log.debug("deleting Worktimepara instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}