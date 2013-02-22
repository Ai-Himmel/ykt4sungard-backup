package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;
import org.king.security.domain.Role;

/**
 * Data access object (DAO) for domain model class Account.
 * @see org.king.security.dao.hibernate.Account
 * @author MyEclipse - Hibernate Tools
 */
public class AccountDAOHibernate  implements AccountDAO{

    private static final Log log = LogFactory.getLog(AccountDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Account instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Account instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Account get(Serializable id) {
				log.debug("getting Account instance by id");
				return (Account)baseDAO.getEntity(Account.class,id);
	  }
	
	  public List getAll(){
		  String allHql = "from Account";
		  return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Account transientInstance) {
        log.debug("saving Account instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Account transientInstance){
	    	log.debug("updating Account instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	public void delete(Account persistentInstance) {
		log.debug("deleting Account instance");
		
		//´¦Àí½ÇÉ«
		 Role role;   
		 Set roles  = persistentInstance.getRoles();
		 if ((roles != null) && (roles.size() > 0)) {
			 for (Iterator i = roles.iterator(); i.hasNext();) {
				 role = (Role) i.next();
				 role.getAccounts().remove(persistentInstance);
				 baseDAO.updateEntity(role);
			 }
		 }
		 
        baseDAO.removeEntity(persistentInstance);
    }

	
	public Account findAccountByName(String name) {
		if (MyUtils.isBlank(name)) {
			return null;
		}

		List accounts = find("from Account a where a.name='" + name
				+ "' order by a.name");

		if (MyUtils.isBlank(accounts)) {
			return null;
		}

		return (Account)accounts.get(0);
	}
    
	

    

    


}