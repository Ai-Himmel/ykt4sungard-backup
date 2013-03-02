package org.king.classmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.StudentmodelDAO;
import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.GzStuTemp;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.springframework.orm.ObjectRetrievalFailureException;

/**
 * Data access object (DAO) for domain model class Studentmodel.
 * @see org.king.classmanage.dao.hibernate.Studentmodel
 * @author MyEclipse - Hibernate Tools
 */
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name:
 * StudentmodelDAOHibernate.java Description: TODO Modify History（或Change Log）:
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述 创建 2006-4-25 何林青
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

public class StudentmodelDAOHibernate implements StudentmodelDAO {

	private static final Log log = LogFactory
			.getLog(StudentmodelDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding Studentmodel instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding Studentmodel instance by query");
		return baseDAO.findEntity(query);
	}

	public Studentmodel get(Serializable id) {
		log.debug("getting Studentmodel instance by id");
		try {
			return (Studentmodel) baseDAO.getEntity(Studentmodel.class, id);
		} catch (ObjectRetrievalFailureException e) {
			return null;
		}
	}

	public List getAll() {
		log.debug("getting Studentmodel all");
		String allHql = "from Studentmodel";
		return baseDAO.findEntity(allHql);
	}

	public void save(Studentmodel transientInstance) {
		log.debug("saving Studentmodel instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Studentmodel transientInstance) {
		log.debug("updating Studentmodel instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Studentmodel persistentInstance) {
		log.debug("deleting Studentmodel instance");
		baseDAO.removeEntity(persistentInstance);
	}
	
	public void saveGzStuTemp(GzStuTemp transientInstance) {
		log.debug("saving GzStuTemp instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void updateGzStuTemp(GzStuTemp transientInstance) {
		log.debug("updating GzStuTemp instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void deleteGzStuTemp(GzStuTemp persistentInstance) {
		log.debug("deleting GzStuTemp instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public void saveAlertHis(ClassAlertHis transientInstance) {
		log.debug("saveing ClassAlertHis instance");
		baseDAO.saveEntity(transientInstance);
	}
	
	//自己的方法
	public Studentmodel findbyStuId(String id) {
		
		  try{
		       List studentmodel = find("from Studentmodel s where s.studentId='"+id+"'");
		       return (Studentmodel)studentmodel.get(0);
		  }catch(Exception e){
			  e.printStackTrace();
			  System.out.println("find by id error");
		  }
        return null;
			
		}

}