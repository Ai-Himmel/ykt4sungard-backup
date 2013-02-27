package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.dao.MonitorDsrvscheduleddowntimeDAO;
import org.king.termdev.domain.MonitorDsrvscheduleddowntime;

/**
 * Data access object (DAO) for domain model class MonitorDsrvscheduleddowntime.
 * @see org.king.termdev.dao.hibernate.MonitorDsrvscheduleddowntime
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorDsrvscheduleddowntimeDAOHibernate implements MonitorDsrvscheduleddowntimeDAO{

    private static final Log log = LogFactory.getLog(MonitorDsrvscheduleddowntimeDAOHibernate.class);
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorDsrvscheduleddowntime instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorDsrvscheduleddowntime instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorDsrvscheduleddowntime get(Serializable id) {
				log.debug("getting MonitorDsrvscheduleddowntime instance by id");
				return (MonitorDsrvscheduleddowntime)baseDAO.getEntity(MonitorDsrvscheduleddowntime.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorDsrvscheduleddowntime all");
	      String allHql = "from MonitorDsrvscheduleddowntime";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorDsrvscheduleddowntime transientInstance) {
        log.debug("saving MonitorDsrvscheduleddowntime instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorDsrvscheduleddowntime transientInstance){
    	log.debug("updating MonitorDsrvscheduleddowntime instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorDsrvscheduleddowntime persistentInstance) {
		    log.debug("deleting MonitorDsrvscheduleddowntime instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	
	  public boolean checkDsrvDowntime(Integer objectid,String nowtime){
			List list = find("from MonitorSrvScheduleddowntime a where a.serviceId="+objectid+" and a.scheduledStartTime<='"+nowtime+"' and a.scheduledEndTime>='"+nowtime+"'");
			if(list!=null&&list.size()>0){
				return true;
			}
			return false;
		}
    

    


}