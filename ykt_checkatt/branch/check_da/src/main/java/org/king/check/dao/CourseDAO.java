package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCourse;
import org.king.framework.dao.DAO;

public interface CourseDAO extends DAO{
	
	public void save(TCourse tCourse);
	
	public void delte(TCourse tCourse);
	
	public void update(TCourse tCourse);
	
	public TCourse  get(Serializable id);
	
	public List  find(String query);
	

}
