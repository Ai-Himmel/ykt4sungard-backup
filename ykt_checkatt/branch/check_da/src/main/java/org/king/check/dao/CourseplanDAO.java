package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TCourseplan;
import org.king.check.domain.TCourseplanclass;
import org.king.check.domain.TRoomElec;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


public interface CourseplanDAO extends DAO{
	
	public void save(TCourseplan courseplan);
	
	public void update(TCourseplan courseplan);
	
    public   TCourseplan   getTCourseplan(Serializable  id);

    public TCourseplanclass getTCourseplanclass(Serializable id);
    
    public  List find(String query);

    public List find(MyQuery myQuery);
     
    public void  save(TCourseplanclass  courseplanclass);
    
    public void delete(TCourseplan  courseplan);
    
    public void delete(TCourseplanclass planclass);
    
    public List findplanclass(String query);
    
    public void save(TRoomElec roomElec);
    
    public void findCourseplanByPage(DBPageLimit page,MyQuery myQuery);
}
