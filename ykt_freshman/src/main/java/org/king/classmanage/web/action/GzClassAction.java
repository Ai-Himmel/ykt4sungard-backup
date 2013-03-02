/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassAction.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-29     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.action;

import java.io.IOException;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.sql.Date;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.classmanage.domain.ClassAlertHis;
import org.king.classmanage.domain.Classmanager;
import org.king.classmanage.domain.ClassmanagerId;
import org.king.classmanage.domain.Classmodel;
import org.king.classmanage.domain.Collegemodel;
import org.king.classmanage.domain.Managermodel;
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.Studentmodel;
import org.king.classmanage.service.ClassService;
import org.king.classmanage.service.CollegeService;
import org.king.classmanage.service.ManagerService;
import org.king.classmanage.service.StudentService;
import org.king.classmanage.web.help.ClassAlertHistory;
import org.king.classmanage.web.help.ClassWithDormitory;
import org.king.classmanage.web.help.ClassWithManager;
import org.king.classmanage.web.help.StudentWithAllInfo;
import org.king.dormitorymanage.exception.DormitoryHasStuException;
import org.king.dormitorymanage.service.DormitoryService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.utils.StringUtil;

public class GzClassAction extends BaseAction {

	private CollegeService collegeService;

	private ManagerService managerService;

	private ClassService classService;

	private StudentService studentService;

	private DormitoryService dormitoryService;

	/**
	 * @param dormitoryService
	 *            The dormitoryService to set.
	 */
	public void setdormitoryService(DormitoryService dormitoryService) {
		this.dormitoryService = dormitoryService;
	}

	/**
	 * @param collegeService
	 *            The collegeService to set.
	 */
	public void setCollegeService(CollegeService collegeService) {
		this.collegeService = collegeService;
	}

	/**
	 * @param managerService
	 *            The managerService to set.
	 */
	public void setManagerService(ManagerService managerService) {
		this.managerService = managerService;
	}

	/**
	 * @param classService
	 *            The classService to set.
	 */
	public void setClassService(ClassService classService) {
		this.classService = classService;
	}

	/**
	 * @param studentService
	 *            The studentService to set.
	 */
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	public ActionForward binding4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
//		// 书院列表
//		List collegeList = collegeService.getAllCollegeByfdxy();
//		request.setAttribute("collegeList", collegeList);
//		// 所有班级列表
//		List classListset = classService.getClassmodelbyschoolId(new String("0002"));
//		request.setAttribute("classList", classListset);
		
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}		
		
		Account manager=(Account)session.getAttribute("accountPerson");	            
        String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
        
        if(dormitoryService==null)
        	System.out.println("service is null");
        List managerdeptList=dormitoryService.find("select a.tabSsDept.id from TabSsManager a where a.stuNo='"+managerNo+"' and a.inOffice=1 ");
		
        String curDept="";
        
        if(managerdeptList!=null&&managerdeptList.size()>0)
        	curDept=(String)managerdeptList.get(0);
        
        if(curDept.equals(""))
        	return mapping.findForward("faile");
        
		//护理学院的所有班级及其人数
		List classnumList=getClassNumList();
		request.setAttribute("classlist", classnumList);
		
		// 所有已绑定的宿舍列表
		List bindeddormList = dormitoryService.getBindedDorm(curDept);
		request.setAttribute("bindeddormList", bindeddormList);
//		// 楼区域列表
//		List locationList = studentService.getDiction("6");
//		request.setAttribute("locationList", locationList);
//		// 所有楼列表
//		List buildingList = studentService.getDiction("7");
//		// List buildingList = dormitoryService.getDormmitoryList();
//		request.setAttribute("buildingList", buildingList);
		
//		classService.initForm(request);
		
		//初始化楼区域列表,所有楼列表
		List areaList=dormitoryService.getAreaList(curDept);
		if(areaList!=null&&areaList.size()>0)
			request.setAttribute("arealist",areaList);
		else
			request.setAttribute("arealist",new ArrayList());
		
		String[][] alList=dormitoryService.getALList(curDept);//校区区域对应表
		if(alList!=null&&alList.length>0)
			request.setAttribute("allist",alList);
		
		String[][] ldList=dormitoryService.getLDList(curDept);//区域楼号对应表
		if(ldList!=null&&ldList.length>0)
			request.setAttribute("ldlist",ldList);
		
		// 所有还可以分配的宿舍列表
		List unbindeddormList = dormitoryService.getUnBindedDorm(curDept);
		request.setAttribute("roomList", unbindeddormList);
		return mapping.findForward("bindinglist");
	}

	public ActionForward classList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}

	public ActionForward bindingDormList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		return null;
	}

	public ActionForward DormList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		return null;
	}
	
	//班级自动分配学生表
	public ActionForward stuinfofind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(classService==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 			 
			 String stuName=request.getParameter("hstuName");
			 String enrollNo=request.getParameter("henrollNo");
			 String gender=request.getParameter("hgender");
			 String examType=request.getParameter("hexamType");
		     
			 String sqlstring="";
//			 List hasclass=classService.find(" select s from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' and s.classId is not null and s.classId!=''");
//			 if(hasclass!=null&&hasclass.size()>0)
//				 sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,c.classNo as classNo) from GzStuTemp s,Classmodel c where s.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
//			 else
				 sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,s.classId as classId) from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
			
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			 if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				 sqlstring=sqlstring+" and s.enterenceNo like '%"+request.getParameter("henrollNo")+"%'";
						 
			 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			 if(request.getParameter("hexamType")!=null&&request.getParameter("hexamType").length()!=0)
				 sqlstring=sqlstring+" and s.examType='"+request.getParameter("hexamType")+"'";
			 			 			 			 
			 sqlstring=sqlstring+" order by s.enterenceNo";
			 			 
			 List stucheckininfoList=classService.find(sqlstring);
			
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeclassIdValue(stucheckininfoList);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("enrollNo",enrollNo);
					 request.setAttribute("stuName",stuName);
					 request.setAttribute("gender",gender);
					 request.setAttribute("examType",examType);
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }                
				 System.out.println("list success");
				 return mapping.findForward("stuinfolist");
			 }
			 else
				 return mapping.findForward("stuinfolist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stuinfoview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        			
	          try {
		            if(classService==null)
		            	 System.out.println("service is null");
		                                					 		 
		            String sqlstring=null;
		            	            
		            //sqlstring="select new Map(ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit) from Stucheckininfo ci,Stuarchivesinfo ai,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=s.studentNo and s.yxClass.classId=c.classId and s.studentNo='"+request.getParameter("updateid")+"'";
		            //新生个人信息
		            sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.birthday as birthday,s.idCard as idCard,s.polityBg as polityBg,s.examType as examType,s.totalScore as totalScore,s.district as district,s.familyAddress as familyAddress,s.postCode as postCode,s.telephone as telephone) from GzStuTemp s where s.enterenceNo='"+request.getParameter("updateid")+"'";
		            	            
		            List stuinfoList=classService.find(sqlstring);
		            
		          if(stuinfoList!=null&&stuinfoList.size()!=0){
		        	  ChangepolityBgValue(stuinfoList);
		        	  ChangedistrictValue(stuinfoList);
		        	  ChangeexamTypeValue(stuinfoList);
		            request.setAttribute("stuinfolist",stuinfoList);
		 	        System.out.println("find student info success");
		            return mapping.findForward("stuinfoview");
		          }
		          else
			        return mapping.findForward("stuinfoview");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }

	   }
	
	//班级自动分配
	public ActionForward classdistribute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(classService==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 boolean flag=false;
			 
			 List hasclass=classService.find(" select s from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' and s.classId is not null and s.classId!=''");
			 if(hasclass!=null&&hasclass.size()>0){
				 if(request.getParameter("needmsg")!=null&&request.getParameter("needmsg").length()>0)
				     request.setAttribute("msg","2");
				 flag=true;
			 }
			 else{
			     flag=classService.updateGzClass();	
			     if(flag)
			         request.setAttribute("msg","0");
			     else
			    	 request.setAttribute("msg","1");
			 }
				
			 String stuName=request.getParameter("hstuName");
			 String enrollNo=request.getParameter("henrollNo");
			 String gender=request.getParameter("hgender");
			 String examType=request.getParameter("hexamType");
		     
			 //String sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,c.classNo as classNo) from GzStuTemp s,Classmodel c where s.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 String sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,s.classId as classId) from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			 if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				 sqlstring=sqlstring+" and s.enterenceNo like '%"+request.getParameter("henrollNo")+"%'";
						 
			 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			 if(request.getParameter("hexamType")!=null&&request.getParameter("hexamType").length()!=0)
				 sqlstring=sqlstring+" and s.examType='"+request.getParameter("hexamType")+"'";
			 			 			 			 
			 sqlstring=sqlstring+" order by s.enterenceNo";
			 			 
			 List stucheckininfoList=new ArrayList();
			 if(flag)
			     stucheckininfoList=classService.find(sqlstring);
			
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeclassIdValue(stucheckininfoList);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("enrollNo",enrollNo);
					 request.setAttribute("stuName",stuName);
					 request.setAttribute("gender",gender);
					 request.setAttribute("examType",examType);
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }                
				 
				 return mapping.findForward("stuinfolist");
			 }
			 else{				 
				 return mapping.findForward("stuinfolist");
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	//班级手工调整查询
	public ActionForward classalertfind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(classService==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
				List classList=getClassList();
				if(classList!=null&&classList.size()>0)
					 request.setAttribute("classlist",classList);
			 			 
			 String stuName=request.getParameter("hstuName");
			 String enrollNo=request.getParameter("henrollNo");
			 String gender=request.getParameter("hgender");
			 String examType=request.getParameter("hexamType");
			 String classId=request.getParameter("hclassId");
		     
			 String sqlstring="";
			 //sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,c.classNo as classNo) from GzStuTemp s,Classmodel c where s.classId=c.classId and c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 sqlstring="select new Map(s.id as id,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.examType as examType,s.totalScore as totalScore,s.classId as classId) from GzStuTemp s where s.enrollYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			 if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				 sqlstring=sqlstring+" and s.enterenceNo like '%"+request.getParameter("henrollNo")+"%'";
						 
			 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			 if(request.getParameter("hexamType")!=null&&request.getParameter("hexamType").length()!=0)
				 sqlstring=sqlstring+" and s.examType='"+request.getParameter("hexamType")+"'";
			 
			 if(request.getParameter("hclassId")!=null&&request.getParameter("hclassId").length()!=0)
				 sqlstring=sqlstring+" and s.classId='"+request.getParameter("hclassId")+"'";
			 			 			 			 
			 sqlstring=sqlstring+" order by s.classId,s.totalScore desc";
			 			 
			 List stucheckininfoList=classService.find(sqlstring);
			
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeclassIdValue(stucheckininfoList);
				 
				 //班级排序
				 Comparator comp1 = new Comparator() { 
						public int compare(Object o1, Object o2){ 
						Map m1 = (Map)o1; 
						Map m2 = (Map)o2; 
						String dictCaption1 = (String)m1.get("classNo"); 
						String dictCaption2 = (String)m2.get("classNo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
		                //注意,返回值是比较的结果>0,=0,或者<0
					    return collator.compare(c1.getSourceString(),c2.getSourceString());				
						 } 
				} ;				
					 
				Collections.sort(stucheckininfoList, comp1);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("enrollNo",enrollNo);
					 request.setAttribute("stuName",stuName);
					 request.setAttribute("gender",gender);
					 request.setAttribute("examType",examType);
					 request.setAttribute("classId",classId);
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }                
				 System.out.println("list success");
				 return mapping.findForward("classalertlist");
			 }
			 else
				 return mapping.findForward("classalertlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	//班级手工调整
	public ActionForward classalert(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		List classList=getClassList();
		 if(classList!=null&&classList.size()>0)
			 request.setAttribute("classlist",classList);
		 
		Account manager=(Account)session.getAttribute("accountPerson");	            
        String managerName=manager.getPerson().getPersonName();	//获取登录者的姓名
		ActionMessages errors = new ActionMessages();
		
		 String stuName=request.getParameter("hstuName");
		 String enrollNo=request.getParameter("henrollNo");
		 String gender=request.getParameter("hgender");
		 String examType=request.getParameter("hexamType");
		 String classId=request.getParameter("hclassId");
		 String toclassId=request.getParameter("toclassId");
		
		boolean flag=false;
		
		String[] ids=request.getParameterValues("cbgroup");
		flag=classService.updateGzClassAlert(ids,toclassId,managerName);
		if(flag){
			request.setAttribute("msg","0");
			return mapping.findForward("classalert");
		}
		else{
			request.setAttribute("msg","1");
			return mapping.findForward("classalert");
		}

	}
//	班级分配结果重置页面
	public ActionForward classResetPage(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		Integer classDistributionResult = classService.getClassDistributionResult();
        request.setAttribute("classDistributionResult",classDistributionResult);

		return mapping.findForward("classResetPage");
	}
	//班级分配结果重置
	public ActionForward classReset(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			classService.deleteClassDistribution();
			// 学生分班
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classDistribution.resetsuccess"));
			saveErrors(request, messages);
		} catch (Exception e) {
			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classDistribution.resetnotsuccess"));
			saveErrors(request, messages);
		}
		Integer classDistributionResult = classService
				.getClassDistributionResult();
		request.setAttribute("classDistributionResult",
				classDistributionResult);
		
		return mapping.findForward("classResetPage");
	}
	
//	宿舍分配结果重置页面
	public ActionForward dormResetPage(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		Integer dormDistributionResult = classService.getDormDistributionResult();
        request.setAttribute("dormDistributionResult",dormDistributionResult);

		return mapping.findForward("dormResetPage");
	}
	//宿舍分配结果重置
	public ActionForward dormReset(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			classService.deleteDormDistribution();
			// 学生分宿舍
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classDistribution.dormresetsuccess"));
			saveErrors(request, messages);
		} catch (Exception e) {
			e.printStackTrace();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classDistribution.dormresetnotsuccess"));
			saveErrors(request, messages);
		}
		Integer dormDistributionResult = classService
				.getDormDistributionResult();
		request.setAttribute("dormDistributionResult",
				dormDistributionResult);
		
		return mapping.findForward("dormResetPage");
	}

	public ActionForward saveBinding(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		String myarea = request.getParameter("dormitorymodel.area");
		String mylocation = request.getParameter("dormitorymodel.location");
		String mydormitory = request.getParameter("dormitorymodel.dormitory");
		String myclass = request.getParameter("classes");
		request.setAttribute("myarea", myarea);
		request.setAttribute("mylocation", mylocation);
		request.setAttribute("mydormitory", mydormitory);
		request.setAttribute("myclass", myclass);
		String binddormitorys = request.getParameter("binddormitorys");
		String unbinddormitorys = request.getParameter("unbinddormitorys");
		String[] temp = StringUtil.split(binddormitorys, ",");
		String[] untemp = StringUtil.split(unbinddormitorys, ",");
		String operator = "";
		if (request.getSession().getAttribute("accountPerson") != null) {
			operator = ((Account) request.getSession().getAttribute(
					"accountPerson")).getPerson().getPersonCode();
		}
		
        List managerdeptList=classService.find("select a.tabSsDept.id from TabSsManager a where a.stuNo='"+operator+"' and a.inOffice=1 ");
		
        String curDept="";
        
        if(managerdeptList!=null&&managerdeptList.size()>0)
        	curDept=(String)managerdeptList.get(0);
        
        if(curDept.equals(""))
        	return mapping.findForward("faile");
        
		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();
		try {
			
			classService.updateDormitory(temp, untemp,curDept);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.success"));
			saveErrors(request, messages);
		} catch (DormitoryHasStuException e) {
			String dormerrmesg = e.getMessage();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.studenthasindorm", dormerrmesg));
			saveErrors(request, messages);
		} catch (Exception e) {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"classBinding.error"));
			saveErrors(request, messages);
			return binding4List(mapping, form, request, response);
		}
		return binding4List(mapping, form, request, response);
	}
	
//	菜单开放时间设置
	public ActionForward menutimelist(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		String sqlstring=" select new Map(a.id as id,b.name as menuName,a.beginDate as beginDate,a.beginTime as beginTime,a.endDate as endDate,a.endTime as endTime,a.updateTime as updateTime) from MenuTime a,Menu b where b.id=a.menuId and a.schoolId='0002' ";
		
		if(request.getParameter("hmenuName")!=null&&request.getParameter("hmenuName").length()!=0){
			 sqlstring=sqlstring+" and b.name like '%"+request.getParameter("hmenuName")+"%'";
			 request.setAttribute("menuName",request.getParameter("hmenuName"));
		}
		
		List menutimeList=classService.find(sqlstring);
		
		if(menutimeList!=null&&menutimeList.size()>0){
		    request.setAttribute("checkinlist",menutimeList);
		    request.setAttribute("listcount",new Integer(menutimeList.size()));
		}
		return mapping.findForward("menutimelist");	
	}
	
	public ActionForward updatemenutime(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		Account manager=(Account)session.getAttribute("accountPerson");	            
        String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
        String msg="";
		try {
			List menutimeList=classService.find(" select a from MenuTime a where a.id='"+request.getParameter("updateid")+"'");
	        
			if(menutimeList!=null&&menutimeList.size()>0){
				MenuTime menuTime=(MenuTime)menutimeList.get(0);
				String mtid=menuTime.getId();
				if(request.getParameter("beginDate"+mtid)!=null&&request.getParameter("beginDate"+mtid).length()>8)
				    menuTime.setBeginDate(new Date(Integer.parseInt(request.getParameter("beginDate"+mtid).substring(0,4))-1900,Integer.parseInt(request.getParameter("beginDate"+mtid).substring(5,7))-1,Integer.parseInt(request.getParameter("beginDate"+mtid).substring(8))));
				menuTime.setBeginTime(new Time(Integer.parseInt(request.getParameter("beginTime"+mtid).substring(0,2)),Integer.parseInt(request.getParameter("beginTime"+mtid).substring(3,5)),0));
				if(request.getParameter("endDate"+mtid)!=null&&request.getParameter("endDate"+mtid).length()>8)
				    menuTime.setEndDate(new Date(Integer.parseInt(request.getParameter("endDate"+mtid).substring(0,4))-1900,Integer.parseInt(request.getParameter("endDate"+mtid).substring(5,7))-1,Integer.parseInt(request.getParameter("endDate"+mtid).substring(8))));
				menuTime.setEndTime(new Time(Integer.parseInt(request.getParameter("endTime"+mtid).substring(0,2)),Integer.parseInt(request.getParameter("endTime"+mtid).substring(3,5)),0));
	       	    menuTime.setUpdator(managerNo);
				menuTime.setUpdateTime(new Timestamp(System.currentTimeMillis()));		     
						     
 		     // 数据库验证
		
			 if(classService==null)
				 System.out.println("service is null");
			 classService.updateMenuTime(menuTime);			 
			 msg="0";
			 request.setAttribute("msg",msg);
			 
			}
			return mapping.findForward("mtsuccess");
		} catch (Exception e) {
			e.printStackTrace();			
			return mapping.findForward("faile");
		}

	}
		
	public List getClassNumList(){
		try {
			List classList=new ArrayList();
			 if(studentService==null)
				 System.out.println("service is null");
			 
			 String sqlstring=" select new Map(c.classId as classId,c.classNo as classNo,c.className as className) from Classmodel c where c.yxCollege.yxSchool.schoolId='0002' and c.curYear='"+DateUtil.getNow("yyyy")+"' order by c.classNo ";
			 
			 classList=studentService.find(sqlstring);
			 
			 sqlstring="select new Map(count(app.studentNo) as stuNum,s.yxClass.classId as classId) from Studentmodel s,GzDormApply app where app.studentNo=s.studentNo and app.ifGiveDorm='1' and s.yxClass.yxCollege.yxSchool.schoolId='0002' and s.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by s.yxClass.classId order by s.yxClass.classId ";
			 List maleList=studentService.find(sqlstring);
			 
			 sqlstring="select new Map(count(app.studentNo) as stuNum,s.yxClass.classId as classId) from Studentmodel s,GzDormApply app where app.studentNo=s.studentNo and app.ifGiveDorm='1' and s.yxClass.yxCollege.yxSchool.schoolId='0002' and s.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by s.yxClass.classId order by s.yxClass.classId ";
			 List femaleList=studentService.find(sqlstring);
			 
			 if(classList!=null&&classList.size()>0){
				 for(int i=0;i<classList.size();i++){
					 Map classm=(Map)classList.get(i);
					 if(maleList!=null&&maleList.size()>0){
						 int j=0;
						 for(j=0;j<maleList.size();j++){
							 Map malem=(Map)maleList.get(j);
							 if(classm.get("classId").equals(malem.get("classId"))){
								 classm.put("maleNum",malem.get("stuNum"));
								 break;
							 }
						 }
						 if(j>maleList.size()-1)
							 classm.put("maleNum",new Integer(0));
					 }
					 else
						 classm.put("maleNum",new Integer(0));
					 if(femaleList!=null&&femaleList.size()>0){
						 int j=0;
						 for(j=0;j<femaleList.size();j++){
							 Map femalem=(Map)femaleList.get(j);
							 if(classm.get("classId").equals(femalem.get("classId"))){
								 classm.put("femaleNum",femalem.get("stuNum"));
								 break;
							 }
						 }
						 if(j>femaleList.size()-1)
							 classm.put("femaleNum",new Integer(0));
					 }
					 else
						 classm.put("femaleNum",new Integer(0));
						 
				 }
				 
				 
				 return classList;
			 }
				 
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
	
	
//	取护理学院的所有班级
	public List getClassList(){
		try {
			 if(classService==null)
				 System.out.println("service is null");
			 String sqlstring="select new Map(col.classId as classId,col.classNo as classNo,col.className as className) from Classmodel col where col.yxCollege.yxSchool.schoolId='0002' and col.curYear='"+DateUtil.getNow("yyyy")+"' order by col.classNo";
			 List classList=classService.find(sqlstring);
			 
			 if(classList!=null&&classList.size()>0)
				 return classList;
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
	
	public void ChangeclassIdValue(List list){
		List classList=getClassList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("classId")!=null){
			   String mj=((String)n.get("classId")).trim();
			   int k=0;
			   for(k=0;k<classList.size();k++){
				 Map n1=(Map)classList.get(k);
				 String mj1=((String)n1.get("classId")).trim();
				 if(mj.equals(mj1)){
					 n.put("classNo",((String)n1.get("classNo")).trim());
					 break;
				 }
			   }
			   if(k>classList.size()-1)
				   n.put("classNo","");
			 }
			 else
				 n.put("classNo","");
		 }
	}
	
	public void ChangepolityBgValue(List list){
		List majorList=getpolityBgList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("polityBg")!=null){
			   String mj=((String)n.get("polityBg")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("polityBgName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("polityBgName","");
		 }
		
	}
	
	public void ChangedistrictValue(List list){
		List majorList=getdistrictList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("district")!=null){
			   String mj=((String)n.get("district")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("districtName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("districtName","");
		 }
		
	}
	
	public void ChangeexamTypeValue(List list){
		List majorList=getexamTypeList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("examType")!=null){
			   String mj=((String)n.get("examType")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("examTypeName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("examTypeName","");
		 }
		
	}
	
	public List getpolityBgList(){
		List objList=classService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=4 order by di.id.dictValue");
		return objList;
	}
	public List getdistrictList(){
		List objList=classService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=23 order by di.id.dictValue");
		return objList;
	}
	public List getexamTypeList(){
		List objList=classService.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=25 order by di.id.dictValue");
		return objList;
	}
}
