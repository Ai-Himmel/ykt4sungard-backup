package org.king.check.service;

import java.util.List;

import org.apache.struts.action.DynaActionForm;
import org.king.check.common.ec.DBPageLimit;

public interface CheckReportService {
	
     public List  getStuCheckRpt(DynaActionForm dform)throws Exception ;
     
     public List  getClassCheckRpt(DynaActionForm dform)throws Exception ;

     public List  getTeaCheckRpt(DynaActionForm dform)throws Exception ;
     
     public void getStudentTermCheckRpt(DynaActionForm dform, DBPageLimit page)throws Exception ;
     
     public List getTeacherTermCheckRpt(DynaActionForm dform)throws Exception ;
     
     public List getClassTermCheckRpt(DynaActionForm dform)throws Exception ;
     
     public List getRoomState(DynaActionForm dform)throws Exception ;
     
     public boolean roomTrans(String[] serialno,String personname,String personCode)throws Exception ;
     
     public List  getTRoomTRans(DynaActionForm dform)throws Exception ;
     
     public List  getTransPerson(DynaActionForm dform)throws Exception ;
     
     public List  getTodayStuCheckList(DynaActionForm dform)throws Exception ;
     
     public List  getAllStudentByPlan(String planId,String classno)throws Exception ;
     
     public List getRealStudentByPlan(String planId,String classno)throws Exception ;
     
     public List getNotComeStudentByPlan(String planId,String classno)throws Exception ;
     
     public List getDailyStudentShould(String courseid,String classid ,String begindate,String enddate,String stuempno)throws Exception;
     
     public List getDailyStudentOther(String courseid,String classid ,String begindate,String enddate,String stuempno,String islate ,String isleave)throws Exception;
     
     public List getDailyTeacherShould(String courseid,String begindate,String enddate ,String stuempno )throws Exception;
     
     public List getDailyTeacherOther(String courseid,String begindate,String enddate,String stuempno,String islate ,String isleave )throws Exception;
 	
     public List getClassShoudStudent(String courseid,String classid ,String begindate,String enddate)throws Exception;
     
     public List getClassStudentOther(String courseid,String classid ,String begindate,String enddate,String islate ,String isleave )throws Exception;

     public List getUnplanStudent(String courseid ,String classid ,String begindate,String enddate,String isactivate,String islate ,String isleave,String stuempNo )throws Exception;

     public void  updateUnplanStudent(String student,String type)throws Exception;

    public List getClassStudentNocome(String courseid, String classid,String begindate, String enddate) throws Exception;

    public List findDeviceCheckList(DynaActionForm dform) throws Exception;

    public List findDeviceUnplanned() throws Exception;

    public void findCheckDetail(DynaActionForm dform,DBPageLimit page);

    public List getCheckDetail(String termId, String classId, String courseId, String stuempNo, Integer custType, Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum) throws Exception;

    public List getTeacherCheckDetail(String termId, String courseId, String stuempNo,Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum) throws Exception;

    public List getClassCheckDetail(String termId, String classId, String courseId, String stuempNo, Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum,String beginDate,String endDate) throws Exception;
}
