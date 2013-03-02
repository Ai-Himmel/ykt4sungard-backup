package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.common.ec.DBPageLimit;
import org.king.check.dao.CourseplanDAO;
import org.king.check.domain.TCourseplan;
import org.king.check.domain.TCourseplanclass;
import org.king.check.domain.TRoomElec;
import org.king.check.util.PageLimitUtil;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.hibernate.BaseDAOHibernate;

public  class CourseplanDAOHibernate implements CourseplanDAO{

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public void delete(TCourseplan courseplan) {
		baseDAO.removeEntity(courseplan);
	}
	
	public void delete(TCourseplanclass planclass) {
		baseDAO.removeEntity(planclass);
	}

	public List find(String query) {
		return baseDAO.findEntity(query);
	}

    public List find(MyQuery myQuery) {
		return baseDAO.findEntity(myQuery);
	}

	public TCourseplan getRoomCourseTime(Serializable id) {
		return (TCourseplan)baseDAO.getEntity(TCourseplan.class, id);
	}

	
	public void save(TCourseplan roomCourseTime) {
		baseDAO.saveEntity(roomCourseTime);
		
	}

	public void update(TCourseplan courseplan) {
		baseDAO.updateEntity(courseplan);
	}

	public TCourseplan getTCourseplan(Serializable id) {
	    return 	(TCourseplan)baseDAO.getEntity(TCourseplan.class, id);
	}

    public TCourseplanclass getTCourseplanclass(Serializable id) {
	    return 	(TCourseplanclass)baseDAO.getEntity(TCourseplanclass.class, id);
	}

	public void save(TCourseplanclass courseplanclass) {
		baseDAO.saveEntity(courseplanclass);
		
	}

	public List findplanclass(String query) {
		return baseDAO.findEntity(query);
	}

	public void save(TRoomElec roomElec) {
		baseDAO.saveEntity(roomElec);
	}
	
	public void findCourseplanByPage(DBPageLimit page,MyQuery myQuery){
		PageLimitUtil.executeHibernatePage(page, (BaseDAOHibernate) baseDAO, myQuery);
	}
}
