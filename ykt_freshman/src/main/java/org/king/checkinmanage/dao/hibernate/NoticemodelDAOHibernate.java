package org.king.checkinmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.checkinmanage.dao.NoticemodelDAO;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.rcvmanage.domain.Stuarriveinfo;

/**
 * Data access object (DAO) for domain model class Noticemodel.
 * 
 * @see org.king.checkinmanage.dao.hibernate.Noticemodel
 * @author MyEclipse - Hibernate Tools
 */

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: NoticemodelDAOHibernate.java
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
public class NoticemodelDAOHibernate implements NoticemodelDAO {

	private static final Log log = LogFactory
			.getLog(NoticemodelDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding Noticemodel instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding Noticemodel instance by query");
		return baseDAO.findEntity(query);
	}

	public Noticemodel get(Serializable id) {
		log.debug("getting Noticemodel instance by id");
		return (Noticemodel) baseDAO.getEntity(Noticemodel.class, id);
	}

	public List getAll() {
		log.debug("getting Noticemodel all");
		String allHql = "from Noticemodel";
		return baseDAO.findEntity(allHql);
	}

	public void save(Noticemodel transientInstance) {
		log.debug("saving Noticemodel instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Noticemodel transientInstance) {
		log.debug("updating Noticemodel instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Noticemodel persistentInstance) {
		log.debug("deleting Noticemodel instance");
		baseDAO.removeEntity(persistentInstance);
	}
	
	//自定义方法
	public Noticemodel findbyId(String id) {
		
		  try{
		       List notice = find("from Noticemodel m where m.id='"+id+"'");
		       return (Noticemodel)notice.get(0);
		  }catch(Exception e){
			  e.printStackTrace();
			  System.out.println("find by id error");
		  }
        return null;
			
		}

}