package org.king.template.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;
import org.king.template.dao.MonitorTimePeriodsDAO;
import org.king.template.domain.MonitorTimePeriods;
import org.king.utils.PaginationUtil;

/**
 * Data access object (DAO) for domain model class MonitorTimePeriods.
 * @see org.king.template.dao.hibernate.MonitorTimePeriods
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTimePeriodsDAOHibernate implements MonitorTimePeriodsDAO{

    private static final Log log = LogFactory.getLog(MonitorTimePeriodsDAOHibernate.class);

    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTimePeriods instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTimePeriods instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTimePeriods get(Serializable id) {
				log.debug("getting MonitorTimePeriods instance by id");
				return (MonitorTimePeriods)baseDAO.getEntity(MonitorTimePeriods.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTimePeriods all");
	      String allHql = "from MonitorTimePeriods";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTimePeriods transientInstance) {
        log.debug("saving MonitorTimePeriods instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTimePeriods transientInstance){
    	log.debug("updating MonitorTimePeriods instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTimePeriods persistentInstance) {
		    log.debug("deleting MonitorTimePeriods instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	public void findMonitorTimePeriodsByPage(DBPaginatedList page, MyQuery myQuery) {
        PaginationUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
    }

    /**
     * 根据模板名字判断该模板是否已存在
     *
     * @param alias
     * @return
     */
    public boolean isExistMonitorTimePeriods(String alias) {
        StringBuffer hql = new StringBuffer("from MonitorTimePeriods t where t.alias='");
        hql.append(alias);
        hql.append("'");

        List result = baseDAO.findEntity(hql.toString());
        if (result != null && result.size() > 0) {
            return true;
        }
        return false;
    }
}