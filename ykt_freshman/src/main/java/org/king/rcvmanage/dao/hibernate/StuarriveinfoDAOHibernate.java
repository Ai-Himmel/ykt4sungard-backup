package org.king.rcvmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;
import org.king.rcvmanage.dao.StuarriveinfoDAO;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.domain.Account;


/**
 * Data access object (DAO) for domain model class Stuarriveinfo.
 * @see org.king.rcvmanage.dao.hibernate.Stuarriveinfo
 * @author MyEclipse - Hibernate Tools
 */
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StuarriveinfoDAOHibernate.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-25     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
public class StuarriveinfoDAOHibernate implements StuarriveinfoDAO{

    private static final Log log = LogFactory.getLog(StuarriveinfoDAOHibernate.class);

	protected void initDao() {
		//do nothing
	}
    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding Stuarriveinfo instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding Stuarriveinfo instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public Stuarriveinfo get(Serializable id) {
				log.debug("getting Stuarriveinfo instance by id");
				return (Stuarriveinfo)baseDAO.getEntity(Stuarriveinfo.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting Stuarriveinfo all");
	      String allHql = "from Stuarriveinfo";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(Stuarriveinfo transientInstance) {
        log.debug("saving Stuarriveinfo instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(Stuarriveinfo transientInstance){
	    	log.debug("updating Stuarriveinfo instance");
	    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(Stuarriveinfo persistentInstance) {
		    log.debug("deleting Stuarriveinfo instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	//自定义方法
	  
	  public List getAllwith() {
	      log.debug("getting Stuarriveinfo all with other attribute");
	      String allHql = "select b.stuName,a from Stuarriveinfo a,Studentmodel b where a.enrollNo=b.enterenceNo";
	      return baseDAO.findEntity(allHql);
	  }
    
	  public Stuarriveinfo findbyId(String id) {
			
		  try{
		       List stuarriveinfo = find("from Stuarriveinfo m where m.id='"+id+"'");
		       return (Stuarriveinfo)stuarriveinfo.get(0);
		  }catch(Exception e){
			  e.printStackTrace();
			  System.out.println("find by id error");
		  }
          return null;
			
		}
    


}