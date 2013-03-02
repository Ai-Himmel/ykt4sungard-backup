package org.king.dormitorymanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.dormitorymanage.dao.FeemodelDAO;
import org.king.dormitorymanage.domain.Feemodel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Feemodel.
 * @see org.king.dormitorymanage.dao.hibernate.Feemodel
 * @author MyEclipse - Hibernate Tools
 */
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: FeemodelDAOHibernate.java
 * Description: TODO
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2006-4-25     ������             
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class FeemodelDAOHibernate implements FeemodelDAO{

    private static final Log log = LogFactory.getLog(FeemodelDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Feemodel instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Feemodel instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Feemodel get(Serializable id) {
				log.debug("getting Feemodel instance by id");
				return (Feemodel)baseDAO.getEntity(Feemodel.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Feemodel all");
	      String allHql = "from Feemodel";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Feemodel transientInstance) {
        log.debug("saving Feemodel instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Feemodel transientInstance){
	    	log.debug("updating Feemodel instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Feemodel persistentInstance) {
		    log.debug("deleting Feemodel instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}