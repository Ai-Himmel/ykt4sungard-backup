package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ExtraWorkDAO;
import org.king.check.domain.Extraworkinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Extraworkinfo.
 * @see org.king.check.dao.Extraworkinfo
 * @author MyEclipse - Hibernate Tools
 */
public class ExtraworkinfoDAOHibernate implements ExtraWorkDAO{

    private static final Log log = LogFactory.getLog(ExtraworkinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Extraworkinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Extraworkinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Extraworkinfo get(Serializable id) {
				log.debug("getting Extraworkinfo instance by id");
				return (Extraworkinfo)baseDAO.getEntity(Extraworkinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Extraworkinfo all");
	      String allHql = "from Extraworkinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Extraworkinfo transientInstance) {
        log.debug("saving Extraworkinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Extraworkinfo transientInstance){
    	log.debug("updating Extraworkinfo instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Extraworkinfo persistentInstance) {
		    log.debug("deleting Extraworkinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}