package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoServerStatisticDAO;
import org.king.topo.domain.MonitorTopoServerStatistic;

/**
 * Data access object (DAO) for domain model class MonitorTopoServerStatistic.
 * @see org.king.topo.domain.MonitorTopoServerStatistic
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTopoServerStatisticDAOHibernate implements MonitorTopoServerStatisticDAO{

    private static final Log log = LogFactory.getLog(MonitorTopoServerStatisticDAOHibernate.class);

    
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
	  
	  public MonitorTopoServerStatistic get(Serializable id) {
				log.debug("getting MonitorTopoServerStatistic instance by id");
				return (MonitorTopoServerStatistic)baseDAO.getEntity(MonitorTopoServerStatistic.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTopoServerStatistic all");
	      String allHql = "from MonitorTopoServerStatistic";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTopoServerStatistic transientInstance) {
        log.debug("saving MonitorTopoServerStatistic instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTopoServerStatistic transientInstance){
    	log.debug("updating MonitorTopoServerStatistic instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTopoServerStatistic persistentInstance) {
		    log.debug("deleting MonitorTopoServerStatistic instance");
        baseDAO.removeEntity(persistentInstance);
    }



}