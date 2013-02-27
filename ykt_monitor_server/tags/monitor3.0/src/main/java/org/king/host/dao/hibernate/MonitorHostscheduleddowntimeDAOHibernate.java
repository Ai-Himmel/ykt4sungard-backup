package org.king.host.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.host.dao.MonitorHostscheduleddowntimeDAO;
import org.king.host.domain.MonitorHostscheduleddowntime;

/**
 * Data access object (DAO) for domain model class MonitorHost.
 * @see org.king.host.dao.MonitorHost
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorHostscheduleddowntimeDAOHibernate implements MonitorHostscheduleddowntimeDAO{

    private static final Log log = LogFactory.getLog(MonitorHostscheduleddowntimeDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorHostscheduleddowntime instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorHostscheduleddowntime instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorHostscheduleddowntime get(Serializable id) {
				log.debug("getting MonitorHostscheduleddowntime instance by id");
				return (MonitorHostscheduleddowntime)baseDAO.getEntity(MonitorHostscheduleddowntime.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorHostscheduleddowntime all");
	      String allHql = "from MonitorHostscheduleddowntime";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorHostscheduleddowntime transientInstance) {
        log.debug("saving MonitorHostscheduleddowntime instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorHostscheduleddowntime transientInstance){
    	log.debug("updating MonitorHostscheduleddowntime instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorHostscheduleddowntime persistentInstance) {
		    log.debug("deleting MonitorHostscheduleddowntime instance");
        baseDAO.removeEntity(persistentInstance);
    }

	public boolean checkHostDowntime(Integer objectid, String nowtime) {
		List list = find("from MonitorHostscheduleddowntime a where a.hostId="+objectid+" and a.scheduledStartTime<='"+nowtime+"' and a.scheduledEndTime>='"+nowtime+"'");
		if(list!=null&&list.size()>0){
			return true;
		}
		return false;
	}
    
	

    

    


}