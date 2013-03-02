package org.king.check.service.impl;

import java.util.Calendar;
import java.util.Date;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.king.check.dao.CourseDAO;
import org.king.check.domain.TCourse;
import org.king.check.service.CourseService;
import org.springframework.jdbc.core.JdbcTemplate;

public class CourseServiceImpl implements CourseService{
   
	private CourseDAO courseDAO;
	
	private JdbcTemplate jdbcTemplate;
	
	public void setCourseDAO(CourseDAO courseDAO) {
		this.courseDAO = courseDAO;
	}
	public void saveCourse(TCourse course) {
		courseDAO.save(course);
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
	public TCourse findOneCourse(String courseName) {
		
		StringBuffer query = new StringBuffer(" from TCourse c where 1=1 ");
		if(StringUtils.isNotEmpty(courseName)){
			query = query.append(" and c.coursename = '").append(courseName).append("'");
		}
	    List list = courseDAO.find(query.toString());
	    if(list!=null && list.size()>0){
	    	TCourse course = (TCourse) list.get(0);
	    	return course;
	    }
		return null;
	}

	

	
	public List findAllCourse() {
		StringBuffer query = new StringBuffer(" select distinct new Map(c.course.courseid as courseid , c.course.coursename as coursename ) from  TCourseplan c order by c.course.coursename");
		return courseDAO.find(query.toString());
	}
	
	public List getCourseAndClass(){
		StringBuffer query = new StringBuffer(" ");
		   query.append(" select t2.classno classno  ,t1.courseid,t4.coursename ")
		   .append(" from ykt_ck.t_courseplan t1 ")
           .append(" left join ykt_ck.t_courseplanclass t2 on t1.id = t2.planid  ")
           .append(" left join ykt_ck.department t3 on t3.dept_id = t2.classno ")
           .append(" left join ykt_ck.t_course t4 on t4.courseid = t1.courseid ")
           .append(" group by t2.classno    ,t1.courseid,t4.coursename ");
        query.append(" order by t2.classno,t4.coursename");
		   List  list = jdbcTemplate.queryForList(query.toString());
		  
		   return list;
        		
	}
	
	public   static  void main(String[] arg){
		try{
	    java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat("yyyymmdd");
		Calendar c =  Calendar.getInstance();
		Date d= sdf.parse("20100301");
		c.setTime(d);
	    
		System.out.println(c.DAY_OF_MONTH);
		c.set(2010, 3, 01);
		//c.DAY_OF_WEEK;
		}catch(Exception e){
			
		}
	    
	}



	
	
	

}
