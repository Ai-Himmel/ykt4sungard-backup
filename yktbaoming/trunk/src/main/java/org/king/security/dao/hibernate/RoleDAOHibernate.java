package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.RoleDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Menu;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;

/**
 * Data access object (DAO) for domain model class Role.
 * @see org.king.security.dao.hibernate.Role
 * @author MyEclipse - Hibernate Tools
 */
public class RoleDAOHibernate implements RoleDAO{

    private static final Log log = LogFactory.getLog(RoleDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Role instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Role instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Role get(Serializable id) {
				log.debug("getting Role instance by id");
				return (Role)baseDAO.getEntity(Role.class,id);
	  }
	
	  public List getAll() {
		  String allHql = "from Role";
		  return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Role transientInstance) {
        log.debug("saving Role instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Role transientInstance){
	    	log.debug("updating Role instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Role persistentInstance) {
		    log.debug("deleting Role instance");
		 //处理帐户   
		 Account account;   
		 Set accounts  = persistentInstance.getAccounts();
		 if ((accounts != null) && (accounts.size() > 0)) {
			 for (Iterator i = accounts.iterator(); i.hasNext();) {
				 account = (Account) i.next();
				 account.getRoles().remove(persistentInstance);
				 baseDAO.updateEntity(account);
			 }
			 
		 }
		 
		 //处理资源
		 Resource resource;   
		 Set resources  = persistentInstance.getResources();
		 if ((resources != null) && (resources.size() > 0)) {
			 for (Iterator i = resources.iterator(); i.hasNext();) {
				 resource = (Resource) i.next();
				 resource.getRoles().remove(persistentInstance);
				 baseDAO.updateEntity(resource);
			 }
			 
		 }
		 
		 
		 //处理菜单
		 Menu menu;   
		 Set menus  = persistentInstance.getMenus();
		 if ((menus != null) && (menus.size() > 0)) {
			 for (Iterator i = menus.iterator(); i.hasNext();) {
				 menu = (Menu) i.next();
				 menu.getRoles().remove(persistentInstance);
				 baseDAO.updateEntity(menu);
			 }
			 
		 }
		 
		    
        baseDAO.removeEntity(persistentInstance);
        
    }


	
    
	

    

    


}