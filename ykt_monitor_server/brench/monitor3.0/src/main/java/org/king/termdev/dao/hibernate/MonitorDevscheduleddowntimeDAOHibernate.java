package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.dao.MonitorDevscheduleddowntimeDAO;
import org.king.termdev.domain.MonitorDevscheduleddowntime;

/**
 * Data access object (DAO) for domain model class MonitorDevscheduleddowntime.
 * @see org.king.termdev.dao.hibernate.MonitorDevscheduleddowntime
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorDevscheduleddowntimeDAOHibernate implements MonitorDevscheduleddowntimeDAO{

    private static final Log log = LogFactory.getLog(MonitorDevscheduleddowntimeDAOHibernate.class);

    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorDevscheduleddowntime instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorDevscheduleddowntime instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorDevscheduleddowntime get(Serializable id) {
				log.debug("getting MonitorDevscheduleddowntime instance by id");
				return (MonitorDevscheduleddowntime)baseDAO.getEntity(MonitorDevscheduleddowntime.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorDevscheduleddowntime all");
	      String allHql = "from MonitorDevscheduleddowntime";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorDevscheduleddowntime transientInstance) {
        log.debug("saving MonitorDevscheduleddowntime instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorDevscheduleddowntime transientInstance){
    	log.debug("updating MonitorDevscheduleddowntime instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorDevscheduleddowntime persistentInstance) {
		    log.debug("deleting MonitorDevscheduleddowntime instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	
	  public boolean checkDevDowntime(Integer objectid,String nowtime){
			List list = find("from MonitorDevscheduleddowntime a where a.deviceId="+objectid+" and a.scheduledStartTime<='"+nowtime+"' and a.scheduledEndTime>='"+nowtime+"'");
			if(list!=null&&list.size()>0){
				return true;
			}
			return false;
		}
    

    


}