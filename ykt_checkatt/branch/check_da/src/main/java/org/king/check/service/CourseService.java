package org.king.check.service;

import java.util.List;

import org.king.check.domain.TCourse;

public interface CourseService {
	
	public void  saveCourse(TCourse course);
	
	public TCourse findOneCourse(String courseName);
	
	public List findAllCourse();
	
	public List getCourseAndClass();
	
	
}
