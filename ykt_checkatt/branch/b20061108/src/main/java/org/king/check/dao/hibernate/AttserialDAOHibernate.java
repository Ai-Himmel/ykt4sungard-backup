package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.AttserialDAO;
import org.king.check.domain.Attserial;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
/**
 * Data access object (DAO) for domain model class Clerk.
 * @see org.king.check.dao.hibernate.Clerk
 * @author MyEclipse - Hibernate Tools
 */
public class AttserialDAOHibernate implements AttserialDAO{

    private static final Log log = LogFactory.getLog(AttserialDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        //log.debug("finding Clerk instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				//log.debug("finding Clerk instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Attserial get(Serializable id) {
				//log.debug("getting Clerk instance by id");
				return (Attserial)baseDAO.getEntity(Attserial.class,id);
	  }
	
	  public List getAll() {
	      //log.debug("getting Clerk all");
	      String allHql = "from Clerk";
	      return baseDAO.findEntity(allHql);
	  }
	  
}