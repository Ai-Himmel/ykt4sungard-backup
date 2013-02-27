package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.MenuDAO;
import org.king.security.domain.Menu;
import org.king.security.domain.Role;

/**
 * Data access object (DAO) for domain model class Menu.
 * @see org.king.security.dao.hibernate.Menu
 * @author MyEclipse - Hibernate Tools
 */
public class MenuDAOHibernate implements MenuDAO{

    private static final Log log = LogFactory.getLog(MenuDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Menu instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Menu instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Menu get(Serializable id) {
				log.debug("getting Menu instance by id");
				return (Menu)baseDAO.getEntity(Menu.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Menu all");
	      String allHql = "from Menu";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Menu transientInstance) {
        log.debug("saving Menu instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Menu transientInstance){
	    	log.debug("updating Menu instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Menu persistentInstance) {
		    log.debug("deleting Menu instance");
		    
			//´¦Àí½ÇÉ«
			 Role role;   
			 Set roles  = persistentInstance.getRoles();
			 if ((roles != null) && (roles.size() > 0)) {
				 for (Iterator i = roles.iterator(); i.hasNext();) {
					 role = (Role) i.next();
					 role.getMenus().remove(persistentInstance);
					 baseDAO.updateEntity(role);
				 }
				 
			 }   
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}