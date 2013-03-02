package org.king.check.service;

import java.util.List;
import java.util.Map;

import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TCourseplan;
import org.king.check.domain.TCourseplanclass;

public interface CourseplanService {
	
	public   Map  getTCourseplanMap(String id )throws Exception;
	
	public   TCourseplan  getTCourseplan(String id )throws Exception;
	
	public String ifCourseCanImp(HSSFSheet  Sheet ,String termId,String areaCode );
	
	public String  saveCourseplanImp(HSSFSheet Sheet,String termId,String userId);
	
	//public List  findCourseplan(ActionForm form)throws Exception;
	
	public void  findCourseplan(DynaActionForm form,DBPageLimit page)throws Exception;
	
	public String  updateCourseplan(ActionForm form,String planId,String[] classes)throws Exception;
	
	public void updateCourseplan(TCourseplan courseplan)throws Exception;
	
	public void deleteCourseplan(TCourseplan courseplan)throws Exception;
	
	public void deleteCourseplanClass(TCourseplanclass planclass)throws Exception;
	
	public List  findCourseplanclass(String planId)throws Exception;
	
}
