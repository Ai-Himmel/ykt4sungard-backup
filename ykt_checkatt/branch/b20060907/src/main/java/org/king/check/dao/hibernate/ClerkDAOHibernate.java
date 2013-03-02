package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ClerkDAO;
import org.king.check.domain.Clerk;
import org.king.check.domain.Clerkinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;
/**
 * Data access object (DAO) for domain model class Clerk.
 * @see org.king.check.dao.hibernate.Clerk
 * @author MyEclipse - Hibernate Tools
 */
public class ClerkDAOHibernate implements ClerkDAO{

    private static final Log log = LogFactory.getLog(ClerkDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Clerk instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Clerk instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Clerk get(Serializable id) {
				log.debug("getting Clerk instance by id");
				return (Clerk)baseDAO.getEntity(Clerk.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Clerk all");
	      String allHql = "from Clerk";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Clerkinfo transientInstance) {
        log.debug("saving Clerk instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Clerkinfo transientInstance){
    	log.debug("updating Clerk instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Clerk persistentInstance) {
		    log.debug("deleting Clerk instance");
        baseDAO.removeEntity(persistentInstance);
    }

	public boolean isExist(Integer clerkId) {
		boolean flage = false;
		if (MyUtils.isBlank(clerkId)) {
			return flage;
		}
		List ret =  baseDAO.findEntity("select a.custId from Clerkinfo a where a.custId=" + clerkId );
		flage = ret.size()>0 ? true:false;
		return flage;
	}

}