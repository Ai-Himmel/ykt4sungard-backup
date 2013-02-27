package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.support.dao.MonitorContactDAO;
import org.king.support.domain.MonitorContact;
import org.king.utils.PaginationUtil;

/**
 * Data access object (DAO) for domain model class MonitorCommands.
 * @see org.king.support.dao.hibernate.MonitorCommands
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorContactDAOHibernate implements MonitorContactDAO{

    private static final Log log = LogFactory.getLog(MonitorContactDAOHibernate.class);    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorContact instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorContact instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorContact get(Serializable id) {
				log.debug("getting MonitorContact instance by id");
				return (MonitorContact)baseDAO.getEntity(MonitorContact.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorContact all");
	      String allHql = "from MonitorContact";
	      return baseDAO.findEntity(allHql);
	  }
	  
	  public List findContactBygroup(Integer groupid){
		  log.debug("getting MonitorContact by Group");
	      String allHql = "from MonitorContact where contactGroups.contactgroupId="+groupid;
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorContact transientInstance) {
        log.debug("saving MonitorContact instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorContact transientInstance){
    	log.debug("updating MonitorContact instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorContact persistentInstance) {
		    log.debug("deleting MonitorContact instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	public void findMonitorContactByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据变量名字判断该变量是否已存在
     *
     * @param contactName .
     * @return .
     */
    public boolean isExistMonitorContact(String contactName) {
        StringBuffer hql = new StringBuffer("from MonitorContact t where t.contactName='");
        hql.append(contactName);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        return result != null && result.size() > 0;
    }
}