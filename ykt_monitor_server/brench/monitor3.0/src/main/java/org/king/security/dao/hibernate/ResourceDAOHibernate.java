package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.ResourceDAO;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;

/**
 * Data access object (DAO) for domain model class Resource.
 * @see org.king.security.dao.hibernate.Resource
 * @author MyEclipse - Hibernate Tools
 */
public class ResourceDAOHibernate implements ResourceDAO{

    private static final Log log = LogFactory.getLog(ResourceDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Resource instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Resource instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Resource get(Serializable id) {
				log.debug("getting Resource instance by id");
				return (Resource)baseDAO.getEntity(Resource.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Resource all");
	      String allHql = "from Resource r order by r.id";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Resource transientInstance) {
        log.debug("saving Resource instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Resource transientInstance){
	    	log.debug("updating Resource instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Resource persistentInstance) {
		    log.debug("deleting Resource instance");
		    
		//´¦Àí½ÇÉ«
			 Role role;   
			 Set roles  = persistentInstance.getRoles();
			 if ((roles != null) && (roles.size() > 0)) {
				 for (Iterator i = roles.iterator(); i.hasNext();) {
					 role = (Role) i.next();
					 role.getResources().remove(persistentInstance);
					 baseDAO.updateEntity(role);
				 }
				 
			 }
			 
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}