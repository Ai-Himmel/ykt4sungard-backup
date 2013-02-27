package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.monitor.domain.TDevice;
import org.king.topo.dao.MonitorTopoGroupStatisticDAO;
import org.king.topo.domain.MonitorTopoGroupStatistic;

/**
 * Data access object (DAO) for domain model class MonitorTopoGroupStatistic.
 * @see org.king.topo.domain.MonitorTopoGroupStatistic
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTopoGroupStatisticDAOHibernate implements MonitorTopoGroupStatisticDAO{

    private static final Log log = LogFactory.getLog(MonitorTopoGroupStatisticDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTopoGroupStatistic instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTopoGroupStatistic instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTopoGroupStatistic get(Serializable id) {
				log.debug("getting MonitorTopoGroupStatistic instance by id");
				return (MonitorTopoGroupStatistic)baseDAO.getEntity(MonitorTopoGroupStatistic.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTopoGroupStatistic all");
	      String allHql = "from MonitorTopoGroupStatistic order by id";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTopoGroupStatistic transientInstance) {
        log.debug("saving MonitorTopoGroupStatistic instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTopoGroupStatistic transientInstance){
    	log.debug("updating MonitorTopoGroupStatistic instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTopoGroupStatistic persistentInstance) {
		    log.debug("deleting MonitorTopoGroupStatistic instance");
        baseDAO.removeEntity(persistentInstance);
    }

	public TDevice getDevice(Serializable deviceid) {
		// TODO Auto-generated method stub
		return (TDevice)baseDAO.getEntity(TDevice.class, deviceid);
	}
    
	

    

    


}