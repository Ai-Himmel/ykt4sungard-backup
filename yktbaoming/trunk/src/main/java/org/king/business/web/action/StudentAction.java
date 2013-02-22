package org.king.business.web.action;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.StringReader;
import java.sql.Blob;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletOutputStream;
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
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.business.domain.BmStuBm;
import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTest;
import org.king.business.service.StudentService;
import org.king.business.service.TestService;
import org.king.framework.web.action.BaseAction;
import org.king.security.util.LdapFromSunDS;
import org.king.upload.web.form.UpLoadForm;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;
import org.king.business.domain.StuTestUpdate;
public class StudentAction extends BaseAction {

	private StudentService studentService;
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	private TestService testService;
	public void setTestService(TestService testService) {
		this.testService = testService;
	}
	
	
	
	
	public ActionForward search4List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception { 
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
				
		List li=new ArrayList();
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();	
		m.put("operator", session.getAttribute("userName"));						    
//		if(request.getAttribute("listNum")!=null&&((String)request.getAttribute("listNum")).equals("1")){
//			Map mm=new HashMap();
//			    
//			//新增返回首页，且第一条记录为新增记录
//			mm.put("newidstring",request.getAttribute("newid"));
//			li=studentService.getnewaddList(mm);			   
//		}
//		else
		    li=studentService.getList(m,offset);
		    Integer studentCount = studentService.getStudentCount(m);
		    
	    if(li!=null&&li.size()>0){
//	    	 List resultList=new ArrayList();
//             //起始页设置
//			 if(offset.equals("0"))
//			     resultList=li;
//			 else if((Integer.parseInt(offset))<li.size()||(Integer.parseInt(offset))==li.size())
//				 resultList=li.subList((Integer.parseInt(offset)),li.size());
//			 
//			 if(resultList!=null&&resultList.size()>0){
//				 request.setAttribute("stutestlist",resultList);
//				 request.setAttribute("listcount",new Integer(li.size()));		    
//			 }
	    	request.setAttribute("stutestlist",li);
	    	request.setAttribute("listcount",studentCount);	
	    }
	    
	    Map tm=new HashMap();
	    tm.put("operator", session.getAttribute("userName"));	
		List testList=testService.getList(tm);
		if(testList!=null&&testList.size()>0){
			for(int i=0;i<testList.size();i++){
				Map testm=(Map)testList.get(i);
				String testInfo=(String)testm.get("testCatName");
				if(testm.get("testDate")!=null)
					testInfo=testInfo+" "+(String)testm.get("testDate");
				if(testm.get("testBeginTime")!=null)
					testInfo=testInfo+" "+(String)testm.get("testBeginTime");
				if(testm.get("testEndTime")!=null)
					testInfo=testInfo+"---"+(String)testm.get("testEndTime");
				testm.put("testInfo",testInfo);
			}
			//按考试排序
			Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String curName1 = (String)m1.get("testInfo"); 
				 String curName2 = (String)m2.get("testInfo");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
	            //注意,返回值是比较的结果>0,=0,或者<0
			     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
				 } 
			} ;
			Collections.sort(testList, comp1);
			
			request.setAttribute("testlist",testList);
		}
		       		
		return (mapping.findForward("success"));		
		
	} 
	
	public ActionForward load4add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		//System.out.println("studentAction: load4add");
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		try {
			 saveToken(request);
			 Map m=new HashMap();
				m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
				m.put("operator", (String)session.getAttribute("userName"));
				List testList=testService.getList(m);
				if(testList!=null&&testList.size()>0){
					for(int i=0;i<testList.size();i++){
						Map testm=(Map)testList.get(i);
						String testInfo=(String)testm.get("testCatName");
						if(testm.get("testDate")!=null)
							testInfo=testInfo+" "+(String)testm.get("testDate");
						if(testm.get("testBeginTime")!=null)
							testInfo=testInfo+" "+(String)testm.get("testBeginTime");
						if(testm.get("testEndTime")!=null)
							testInfo=testInfo+"---"+(String)testm.get("testEndTime");
						testm.put("testInfo",testInfo);
					}
					//按考试排序
					Comparator comp1 = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 String curName1 = (String)m1.get("testInfo"); 
						 String curName2 = (String)m2.get("testInfo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
			            //注意,返回值是比较的结果>0,=0,或者<0
					     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
						 } 
					} ;
					Collections.sort(testList, comp1);
					
					request.setAttribute("testlist",testList);
				}
			 return mapping.findForward("stutest");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
	//	System.out.println("StudentAction:add ");
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
	//	System.out.println("Create form : bmstudent ");
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmStudent bmStudent = (BmStudent)aform.get("bmStudent");
				
		String testid=request.getParameter("testId");
		BmTest bmTest=testService.getDetail(testid);
				
		String msg="";
		try {			
			boolean flag=studentService.check4Save(bmStudent);//检查是否存在相同的考生
			if(flag){					
				
				bmStudent.setUpdator(userId);
				bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
					 				 
				if (isTokenValid(request, true)) {
					msg="0";
					String stubmIds=studentService.saveStuBm(bmStudent,bmTest,userId);	
					request.setAttribute("listNum","1");
					request.setAttribute("newid",stubmIds);
				}
				else{
					msg="9";
					saveToken(request);
				}	
								
				request.setAttribute("msg",msg);
				return mapping.findForward("stutestlist");
			}
			else{
				msg="2";
				request.setAttribute("msg",msg);
				return load4add(mapping, form, request, response);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return load4add(mapping, form, request, response);
		}

	}
			
	public ActionForward load4addtest(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		//System.out.println("StudentAction:load4addtest !");
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		try {
			 saveToken(request);
			 String uid=request.getParameter("updateid");
			 BmStuBm bmStuBm=studentService.getStuBmDetail(uid);
			 DynaActionForm curForm = (DynaActionForm) form;
			 curForm.set("bmStudent",bmStuBm.getBmStudent());
			 
			 Map m=new HashMap();
				m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
				m.put("operator", (String)session.getAttribute("userName"));
				List testList=testService.getList(m);
				if(testList!=null&&testList.size()>0){
					for(int i=0;i<testList.size();i++){
						Map testm=(Map)testList.get(i);
						String testInfo=(String)testm.get("testCatName");
						if(testm.get("testDate")!=null)
							testInfo=testInfo+" "+(String)testm.get("testDate");
						if(testm.get("testBeginTime")!=null)
							testInfo=testInfo+" "+(String)testm.get("testBeginTime");
						if(testm.get("testEndTime")!=null)
							testInfo=testInfo+"---"+(String)testm.get("testEndTime");
						testm.put("testInfo",testInfo);
					}
					//按考试排序
					Comparator comp1 = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 String curName1 = (String)m1.get("testInfo"); 
						 String curName2 = (String)m2.get("testInfo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
			            //注意,返回值是比较的结果>0,=0,或者<0
					     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
						 } 
					} ;
					Collections.sort(testList, comp1);
					
					request.setAttribute("testlist",testList);
				}
				request.setAttribute("uid", uid);
			 return mapping.findForward("stutestadd");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward addtest(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaActionForm curForm = (DynaActionForm) form;
		String stuNo=request.getParameter("studentNo");
		BmStudent bmStudent=studentService.getDetail(stuNo);
				
		String testid=request.getParameter("testId");
									
		String msg="";
		try {			
			boolean flag=studentService.check4SaveBm(stuNo,testid,null);//检查是否存在相同的考生报名
			if(flag){	
				String 	uid = (String)request.getParameter("uid");
				BmStuBm bmStuBm=new BmStuBm();
				BmStuBm bmStuBmDetail = studentService.getStuBmDetail(uid);
				bmStuBm.setDeptName(bmStuBmDetail.getDeptName());
				bmStuBm.setMajorName(bmStuBmDetail.getMajorName());
				bmStuBm.setCurClass(bmStuBmDetail.getCurClass());
				bmStuBm.setCurGrade(bmStuBmDetail.getCurGrade());
				  
				bmStuBm.setBmStudent(bmStudent);
				BmTest bmTest=testService.getDetail(testid);
				bmStuBm.setBmTest(bmTest);
				bmStuBm.setUpdator(userId);
				bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				
				if (isTokenValid(request, true)) {
					msg="0";					
					String stubmIds=studentService.saveBm(bmStuBm);	
					request.setAttribute("listNum","1");
					request.setAttribute("newid",stubmIds);
				}
				else{
					msg="9";
					saveToken(request);
				}	
								
				request.setAttribute("msg",msg);
				return mapping.findForward("stutestlist");
			}
			else{
				msg="2";
				request.setAttribute("msg",msg);
				curForm.set("bmStudent",bmStudent);
				 
				 Map m=new HashMap();
					m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
					List testList=testService.getList(m);
					if(testList!=null&&testList.size()>0){
						for(int i=0;i<testList.size();i++){
							Map testm=(Map)testList.get(i);
							String testInfo=(String)testm.get("testCatName");
							if(testm.get("testDate")!=null)
								testInfo=testInfo+" "+(String)testm.get("testDate");
							if(testm.get("testBeginTime")!=null)
								testInfo=testInfo+" "+(String)testm.get("testBeginTime");
							if(testm.get("testEndTime")!=null)
								testInfo=testInfo+"---"+(String)testm.get("testEndTime");
							testm.put("testInfo",testInfo);
						}
						//按考试排序
						Comparator comp1 = new Comparator() { 
							 public int compare(Object o1, Object o2){ 
							 Map m1 = (Map)o1; 
							 Map m2 = (Map)o2; 
							 String curName1 = (String)m1.get("testInfo"); 
							 String curName2 = (String)m2.get("testInfo");      				

							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
				            //注意,返回值是比较的结果>0,=0,或者<0
						     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
							 } 
						} ;
						Collections.sort(testList, comp1);
						
						request.setAttribute("testlist",testList);
					}
				 return mapping.findForward("stutestadd");
			}
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}
	
	
	
	
	
	public ActionForward load4update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		try {			 
			 String uid=request.getParameter("updateid");
			 List stubmList=studentService.getStuBm4Update(uid);
			 if(stubmList!=null&&stubmList.size()>0)
				 request.setAttribute("stubmlist",stubmList);
			
				 Map m=new HashMap();
					m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
					m.put("operator", (String)session.getAttribute("userName"));
					List testList=testService.getList(m);
					if(testList!=null&&testList.size()>0){
						for(int i=0;i<testList.size();i++){
							Map testm=(Map)testList.get(i);
							String testInfo=(String)testm.get("testCatName");
							if(testm.get("testDate")!=null)
								testInfo=testInfo+" "+(String)testm.get("testDate");
							if(testm.get("testBeginTime")!=null)
								testInfo=testInfo+" "+(String)testm.get("testBeginTime");
							if(testm.get("testEndTime")!=null)
								testInfo=testInfo+"---"+(String)testm.get("testEndTime");
							testm.put("testInfo",testInfo);
						}
						//按考试排序
						Comparator comp1 = new Comparator() { 
							 public int compare(Object o1, Object o2){ 
							 Map m1 = (Map)o1; 
							 Map m2 = (Map)o2; 
							 String curName1 = (String)m1.get("testInfo"); 
							 String curName2 = (String)m2.get("testInfo");      				

							com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
							com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
							com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
				            //注意,返回值是比较的结果>0,=0,或者<0
						     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
							 } 
						} ;
						Collections.sort(testList, comp1);
						
						request.setAttribute("testlist",testList);
					}
					
					return mapping.findForward("stutestedit");
			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("faile");
		}

	}
	
	public  ActionForward studentEdit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	       throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmStudent bmStudent = (BmStudent)aform.get("bmStudent");
				
		String msg="0";	
		String stubmid=request.getParameter("stubmId");
		try {				
		    boolean flag=studentService.check4Update(bmStudent);
			if(flag){
				//bmStudent.setUpdator(userId);
				//bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				studentService.update(bmStudent);
			}
			else{
				    msg="21";
			}
		    if(!msg.equals("0")){	
		    	List stubmList=studentService.getStuBm4Update(stubmid);
				if(stubmList!=null&&stubmList.size()>0){
					request.setAttribute("stubmlist",stubmList);
				}
				request.setAttribute("msg",msg);
				return mapping.findForward("studentedit");
		    }
		    request.setAttribute("msg",msg);
			return mapping.findForward("stutestlist");
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}
	}
	
	/*public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmStudent bmStudent = (BmStudent)aform.get("bmStudent");
				
		String testid=request.getParameter("testId");		
		String stubmid=request.getParameter("stubmId");
						
		String msg="0";
		try {
			boolean bmflag=studentService.check4SaveBm(bmStudent.getStudentNo(),testid,stubmid);
			if(bmflag){	
				BmStuBm bmStuBm=studentService.getStuBmDetail(stubmid);
				BmTest bmTest=testService.getDetail(testid);
				bmStuBm.setBmTest(bmTest);
				
				bmStuBm.setUpdator(userId);
				bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				studentService.updateBm(bmStuBm);				
			}
			else{
				msg="22";				
			}
			
			boolean flag=studentService.check4Update(bmStudent);
			if(flag){
				bmStudent.setUpdator(userId);
				bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				studentService.update(bmStudent);
			}
			else{
				if(msg.equals("22"))
				    msg="2";
			    else if(msg.equals("0"))
				    msg="21";
			}
			
			if(!msg.equals("0")){
				List stubmList=studentService.getStuBm4Update(stubmid);
				if(stubmList!=null&&stubmList.size()>0)
					request.setAttribute("stubmlist",stubmList);
				Map m=new HashMap();
				m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
				List testList=testService.getList(m);
				if(testList!=null&&testList.size()>0){
					for(int i=0;i<testList.size();i++){
						Map testm=(Map)testList.get(i);
						String testInfo=(String)testm.get("testCatName");
						if(testm.get("testDate")!=null)
							testInfo=testInfo+" "+(String)testm.get("testDate");
						if(testm.get("testBeginTime")!=null)
							testInfo=testInfo+" "+(String)testm.get("testBeginTime");
						if(testm.get("testEndTime")!=null)
							testInfo=testInfo+"---"+(String)testm.get("testEndTime");
						testm.put("testInfo",testInfo);
					}
					//按考试排序
					Comparator comp1 = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 String curName1 = (String)m1.get("testInfo"); 
						 String curName2 = (String)m2.get("testInfo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
			            //注意,返回值是比较的结果>0,=0,或者<0
					     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
						 } 
					} ;
					Collections.sort(testList, comp1);
					
				    request.setAttribute("testlist",testList);
				}
				request.setAttribute("msg",msg);
				return mapping.findForward("stutestedit");
			}
			
			request.setAttribute("msg",msg);
			return mapping.findForward("stutestlist");
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}*/
	
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		BmStudent bmStudent = (BmStudent)aform.get("bmStudent");
		
				
		String testid=request.getParameter("testId");//准备修改的考试科目		
		String stubmid=request.getParameter("stubmId");
		String ifBm= request.getParameter("ifBm");
		String ifPay = request.getParameter("ifPay");
		
		String msg="0";
		
		
		
		try {
			boolean flag=studentService.check4Update(bmStudent);//是否有其他信息相同的学生
			if(flag){//无其他信息相同的学生信息，可以更改个人信息。
				bmStudent.setUpdator(userId);
				bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				//更新学生明细。
				studentService.update(bmStudent);
			}
			
			BmStuBm bmStuBm=studentService.getStuBmDetail(stubmid);
			//此考生是否已有此考试
			boolean bmflag=studentService.check4SaveBm(bmStudent.getStudentNo(),testid,stubmid);
			
			if(bmflag){//考生无此考试。修改考生可以报考此考试。
				
				if("1".equals(ifPay)){//如果已经付费，只能修改金额相同的考试。
					
					double oldfee = bmStuBm.getBmTest().getBmTestCat().getFee();//原考试费用
					BmTest bmTest=testService.getDetail(testid);
					double newfee = bmTest.getBmTestCat().getFee();//新考试费用
					if(oldfee==newfee){
						
						//保存历史纪录
						StuTestUpdate  stuTestup = new StuTestUpdate();
						stuTestup.setBmStudent(bmStuBm.getBmStudent());
						stuTestup.setOldBmTest(bmStuBm.getBmTest());
						stuTestup.setNewBmTest(bmTest);
						stuTestup.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
						stuTestup.setUpdator(userId);
						studentService.save(stuTestup);
						//更新考试。
						bmStuBm.setBmTest(bmTest);
					}else{
						msg="feenoequals";
					}			
				}
				
				
				
			}else{//考生有此考试不能再修改考试，请先删除此考生的考试。
				msg="23";			
				
			}
			//同步更改更改考试报名中的学生信息。
			bmStuBm.setDeptName(bmStudent.getDeptName());
			bmStuBm.setMajorName(bmStudent.getMajorName());
			bmStuBm.setCurClass(bmStudent.getCurClass()); 
			bmStuBm.setCurGrade(bmStudent.getCurGrade());  
			studentService.updateBmStuBm(bmStuBm);	
			
		
			
			if(!msg.equals("0")){
				List stubmList=studentService.getStuBm4Update(stubmid);
				if(stubmList!=null&&stubmList.size()>0)
					request.setAttribute("stubmlist",stubmList);
				Map m=new HashMap();
				m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
				m.put("operator", session.getAttribute("userName"));	
				List testList=testService.getList(m);
				if(testList!=null&&testList.size()>0){
					for(int i=0;i<testList.size();i++){
						Map testm=(Map)testList.get(i);
						String testInfo=(String)testm.get("testCatName");
						if(testm.get("testDate")!=null)
							testInfo=testInfo+" "+(String)testm.get("testDate");
						if(testm.get("testBeginTime")!=null)
							testInfo=testInfo+" "+(String)testm.get("testBeginTime");
						if(testm.get("testEndTime")!=null)
							testInfo=testInfo+"---"+(String)testm.get("testEndTime");
						testm.put("testInfo",testInfo);
					}
					//按考试排序
					Comparator comp1 = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 String curName1 = (String)m1.get("testInfo"); 
						 String curName2 = (String)m2.get("testInfo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
			            //注意,返回值是比较的结果>0,=0,或者<0
					     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
						 } 
					} ;
					Collections.sort(testList, comp1);
					
				    request.setAttribute("testlist",testList);
				}
				request.setAttribute("msg",msg);
				return mapping.findForward("stutestedit");
			}
			
			request.setAttribute("msg",msg);
			return mapping.findForward("stutestlist");
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward updateBm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
						
		String testid=request.getParameter("testId");
		String stuNo=request.getParameter("studentNo");		
		String stubmid=request.getParameter("stubmId");
				
		String msg="0";
		try {
			boolean flag=studentService.check4SaveBm(stuNo,testid,stubmid);
			if(flag){		
				BmStuBm bmStuBm=studentService.getStuBmDetail(stubmid);
				BmTest bmTest=testService.getDetail(testid);
				bmStuBm.setBmTest(bmTest);
				
				bmStuBm.setUpdator(userId);
				bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				studentService.updateBm(bmStuBm);				
			}
			else
				msg="22";
									
			if(!msg.equals("0")){
				List stubmList=studentService.getStuBm4Update(stubmid);
				if(stubmList!=null&&stubmList.size()>0)
					request.setAttribute("stubmlist",stubmList);
				Map m=new HashMap();
				m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
				List testList=testService.getList(m);
				if(testList!=null&&testList.size()>0){
					for(int i=0;i<testList.size();i++){
						Map testm=(Map)testList.get(i);
						String testInfo=(String)testm.get("testCatName");
						if(testm.get("testDate")!=null)
							testInfo=testInfo+" "+(String)testm.get("testDate");
						if(testm.get("testBeginTime")!=null)
							testInfo=testInfo+" "+(String)testm.get("testBeginTime");
						if(testm.get("testEndTime")!=null)
							testInfo=testInfo+"---"+(String)testm.get("testEndTime");
						testm.put("testInfo",testInfo);
					}
					//按考试排序
					Comparator comp1 = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 String curName1 = (String)m1.get("testInfo"); 
						 String curName2 = (String)m2.get("testInfo");      				

						com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
						com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
						com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
			            //注意,返回值是比较的结果>0,=0,或者<0
					     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
						 } 
					} ;
					Collections.sort(testList, comp1);
					
				    request.setAttribute("testlist",testList);
				}
				request.setAttribute("msg",msg);
				return mapping.findForward("stutesteditbm");
			}
			
			request.setAttribute("msg",msg);
			return mapping.findForward("stutestlist");
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       	String nottoDelete="";	
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 String nottoDelName=studentService.check4DeleteBm(ids[i]);
				 if(nottoDelName!=null)
					 nottoDelete=nottoDelete+nottoDelName+",";
				 else{
					 BmStuBm bmStuBm = findbyId(ids[i]);
					 if(bmStuBm!=null)
				         studentService.deleteBm(bmStuBm);
				     msg="d0";
				 }
				 
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
		}
		if(nottoDelete.length()>1){
			nottoDelete=nottoDelete.substring(0,nottoDelete.length()-1);
			request.setAttribute("notdel",nottoDelete);
		}
		request.setAttribute("msg",msg);
		return mapping.findForward("stutestlist");
	}
	
	public  BmStuBm findbyId(String id) throws Exception {
		
	       try {	
	    	   
	    	  BmStuBm bmStuBm=studentService.getStuBmDetail(id);	 		
		      return bmStuBm;
		      
	      } catch (Exception e) {
		    e.printStackTrace();
	      }
	      return null;

	      }
	
	public ActionForward exportBm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception{
			
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();
		
		//m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
		
		List stubmList=studentService.getList(m);
		
		if(stubmList!=null&&stubmList.size()>0){
			changeRelatedValues(stubmList);
		}
				
		String	fileName="stuBmList.xls";
		
		// Create the Sheet with the name of the Table
		HSSFWorkbook wb = new HSSFWorkbook();
		
        //设置显示的字体以及相关的样式
 		HSSFFont font = wb.createFont();
 		    font.setFontHeightInPoints((short)8);
 		    font.setItalic(false);
 		    font.setStrikeout(false);
 		   
 		//设置标题栏单元格的样式
 		HSSFCellStyle cellHeadStyle=wb.createCellStyle();
 		    cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
 		cellHeadStyle.setBorderBottom(HSSFCellStyle.BORDER_DOUBLE);
 		    cellHeadStyle.setBorderLeft((short)1);
 		    cellHeadStyle.setBorderRight((short)1);
 		    cellHeadStyle.setBorderTop(HSSFCellStyle.BORDER_DOUBLE);
 		cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_YELLOW.index);
 		    cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

 		//设置数据行的字体以及以及相关的对齐方式
 		HSSFCellStyle cellDataStyle=wb.createCellStyle();
 		    cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
 		cellDataStyle.setFont(font);
		
		HSSFSheet sheet1 = wb.createSheet("Sheet1");
		    
		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short)0);
		
       //Populate the first row of the spreadsheet with the column names
		List columnNames =new ArrayList();
		columnNames.add(0,"学号");
		columnNames.add(1,"姓名");
		columnNames.add(2,"性别");
		columnNames.add(3,"入学年份");
		columnNames.add(4,"学院名称");
		columnNames.add(5,"专业名称");
		columnNames.add(6,"学院代码");
		columnNames.add(7,"专业代码");
		columnNames.add(8,"年级");
		columnNames.add(9,"班级");
		columnNames.add(10,"证件类型");
		columnNames.add(11,"证件号码");
		columnNames.add(12,"电子邮件");
		columnNames.add(13,"报名考试");
		columnNames.add(14,"是否收费");
		columnNames.add(15,"收费标准");
		columnNames.add(16,"是否已报名");
		columnNames.add(17,"报名时间");
		columnNames.add(18,"是否已缴费");
		columnNames.add(19,"缴费金额");
		columnNames.add(20,"考试成绩");
		
		// System.out.println(columnNames.size());
		for (int i=0; i<columnNames.size(); i++)
		{
			 HSSFCell cname=row.createCell((short)i);
			 cname.setCellStyle(cellHeadStyle);
			 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
			 cname.setCellValue((String)columnNames.get(i));
		}
		
		// Populate the Row Data to the SpreadSheet
		int rowCount =stubmList.size();
		// goal houses the number of cells in the target spreadsheet
		int goal = rowCount*columnNames.size();			
		
		//actual population of target spreadsheet
		int currentCell = 0;
		
		for (int i=0; i<rowCount; i++)
		{
			Map tableData = (Map)stubmList.get(i);
			// create row in spreadsheet
			row = sheet1.createRow((short)(i+1));
			
				// populate the spreadsheet with the cell						
				HSSFCell ctitle=row.createCell((short)0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("studentNo"));
				
				ctitle=row.createCell((short)1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("stuName"));
				
				ctitle=row.createCell((short)2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("gender"));
				
				ctitle=row.createCell((short)3);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("enrollYear"));
				
				ctitle=row.createCell((short)4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("deptName"));
				
				ctitle=row.createCell((short)5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("majorName"));
				
				ctitle=row.createCell((short)6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("deptCode"));
				
				ctitle=row.createCell((short)7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("majorCode"));
				
				ctitle=row.createCell((short)8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curGrade"));
												
				ctitle=row.createCell((short)9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("curClass"));
				
				ctitle=row.createCell((short)10);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("idType"));
				
				ctitle=row.createCell((short)11);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("idCard"));
				
				ctitle=row.createCell((short)12);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("email"));
				
				ctitle=row.createCell((short)13);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("testInfo"));
				
				ctitle=row.createCell((short)14);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("ifFeeName"));
				
				ctitle=row.createCell((short)15);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue(((Double)tableData.get("fee")).doubleValue());
				
				ctitle=row.createCell((short)16);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("ifBmName"));
				
				ctitle=row.createCell((short)17);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("bmTime"));
				
				ctitle=row.createCell((short)18);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("ifPayName"));
				
				ctitle=row.createCell((short)19);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if(tableData.get("feePayed")!=null)
				    ctitle.setCellValue(((Double)tableData.get("feePayed")).doubleValue());
				else
					ctitle.setCellValue(0.0);
				
				ctitle=row.createCell((short)20);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				if(tableData.get("grades")!=null)
				    ctitle.setCellValue(((Double)tableData.get("grades")).doubleValue());
				else
					ctitle.setCellValue(0);
											
				//System.out.println(columnData);
				currentCell++;

		}						
		
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition", "attachment;"
				+ " filename="
				+ new String(fileName.getBytes(), "ISO-8859-1"));

        OutputStream os = response.getOutputStream();
        wb.write(os);
        os.close();
    /*-----------------------------------------------------------------------*/ 
	 return null;	

	}	
	
	public ActionForward exportPhoto(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception{
			
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();
		m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
						
        String[] fileName=null;
		
		try {
						
			LdapFromSunDS ldap = new LdapFromSunDS();
	 		ldap.init("");
	 	    
	 		String path=ldap.getPreference("constant.stuphoto.path");
			
			Blob stuPhoto = null;
			List list=studentService.getPhotoList(m);
						
			if(list!=null&&list.size()>0){					
				res.setContentType("application/x-msdownload");
				res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
				
				fileName=new String[list.size()];
				for(int i=0;i<list.size();i++){	
					Map stuphoto=(Map)list.get(i);
					String studentNo=(String)stuphoto.get("studentNo");
				    stuPhoto =(Blob)stuphoto.get("photo");
				    BufferedOutputStream bufferout=null;
				    if (stuPhoto != null) {
				    	String fName=path+studentNo+".jpg";
				    	bufferout= new BufferedOutputStream(new FileOutputStream(fName)); 
                        Blob temp = stuPhoto;
						InputStream is = temp.getBinaryStream();
						byte buffer[] = new byte[512];
						while (is.read(buffer, 0, 512) != -1) {						
							bufferout.write(buffer);
						}		
						bufferout.flush();	
						bufferout.close();
						is.close();
						fileName[i]=fName;
					}
				}
								
				//生成含有照片地址的txt
				if(path!=null){
					ServletOutputStream out=res.getOutputStream();
					String str="照片已从数据库导出，保存在服务器路径："+path+"，本批照片导出时间为 "+DateUtil.getNow("yyyy-MM-dd HH:mm")+"。";
					str=str+"本批导出考生照片文件名为：";
					String hasfile="";
					int filenum=0;
					for(int k=0;k<fileName.length;k++){//过滤重复照片
	                	if(fileName[k]!=null&&hasfile.indexOf(fileName[k])==-1){
	                		str=str+fileName[k]+"，";
	                		hasfile=hasfile+fileName[k]+",";
	                		filenum++;
	                	}
	                 }
					str=str.substring(0,str.length()-1);
					str=str+"。 共"+filenum+"张。";
					StringReader rd=new StringReader(str);
		               
					BufferedReader sr=new BufferedReader(rd);   
					
				    String ostring=sr.readLine();
				    while (ostring!=null){
				    	out.write(ostring.getBytes());
				    	ostring=sr.readLine();
				    }
				}
				else{
					ServletOutputStream out=res.getOutputStream();
					BufferedReader sr=new BufferedReader(new StringReader("服务器上文件夹stuphoto不存在，无法保存照片。"));   
					
				    String ostring=sr.readLine();
				    while (ostring!=null){
				    	out.write(ostring.getBytes());
				    	ostring=sr.readLine();
				    }
				}
			    
			}
			else{
				res.setContentType("application/x-msdownload");
				res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
				
				ServletOutputStream out=res.getOutputStream();
				BufferedReader sr=new BufferedReader(new StringReader("没有新照片。"));   
				
			    String ostring=sr.readLine();
			    while (ostring!=null){
			    	out.write(ostring.getBytes());
			    	ostring=sr.readLine();
			    }

			}
			return null;							
	} catch(Exception pe) {		
			pe.printStackTrace();	
			res.setContentType("application/x-msdownload");
			res.setHeader("Content-Disposition","attachment;filename=stuphoto.txt");
			
			ServletOutputStream out=res.getOutputStream();
			BufferedReader sr=new BufferedReader(new StringReader("照片生成过程中有错误。"));   
			
		    String ostring=sr.readLine();
		    while (ostring!=null){
		    	out.write(ostring.getBytes());
		    	ostring=sr.readLine();
		    }
			return null;
		}

	}	
	
	public ActionForward tongji4BM(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";
		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		
		List li=studentService.getBMTongji();
		
		if(li!=null&&li.size()>0)
		    request.setAttribute("tongjilist", li);
		
		List totalli=studentService.getBMTongjiTotal();
		
		if(totalli!=null&&totalli.size()>0)
			request.setAttribute("tongjitotal",totalli);
		
		 return mapping.findForward("stutesttongji"); 

	}
	
	public ActionForward load4upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);
		Map m=new HashMap();
		m.put("operator", session.getAttribute("userName"));
		m.put("search_afterdate",DateUtil.getNow("yyyy-MM-dd"));
		List testList=testService.getList(m);
		if(testList!=null&&testList.size()>0){
			for(int i=0;i<testList.size();i++){
				Map testm=(Map)testList.get(i);
				String testInfo=(String)testm.get("testCatName");
				if(testm.get("testDate")!=null)
					testInfo=testInfo+" "+(String)testm.get("testDate");
				if(testm.get("testBeginTime")!=null)
					testInfo=testInfo+" "+(String)testm.get("testBeginTime");
				if(testm.get("testEndTime")!=null)
					testInfo=testInfo+"---"+(String)testm.get("testEndTime");
				testm.put("testInfo",testInfo);
			}
			//按考试排序
			Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String curName1 = (String)m1.get("testInfo"); 
				 String curName2 = (String)m2.get("testInfo");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
	            //注意,返回值是比较的结果>0,=0,或者<0
			     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
				 } 
			} ;
			Collections.sort(testList, comp1);
			
			request.setAttribute("testlist",testList);
		}
		return mapping.findForward("selfile");
	}		
	
	public ActionForward importExcel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception{
	   	
   		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";
				
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
	        	
	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	 	           
	        String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//取得上传的文件
	 	     if(file==null){	 	    	
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();
	      	 String size = (file.getFileSize() + " bytes");//文件大小
	      	 
	 	     String fileName= file.getFileName();//文件名
	 	     fileName=request.getParameter("filepath");
	 	     InputStream checkis = file.getInputStream();//把文件读入,用于检查格式
	 	     InputStream is=file.getInputStream();//把文件读入,用于导入数据
	 	     	 	     
	 	     String resultstring="";
	 	     String testId=request.getParameter("testId");
	 	     String importMode=request.getParameter("importmode");
	 	    try{
	 	     resultstring=checkSbModel(checkis);
	 	     HSSFWorkbook wb =null;
	 	     HSSFSheet sheet=null;
	 	     int rowCount =0;
	 	     if(resultstring.equals("")){
	 	    	 wb=new HSSFWorkbook(is);
   	             String tableName =  wb.getSheetName(0);   			
   			     sheet = wb.getSheet(tableName);
   			     rowCount = sheet.getPhysicalNumberOfRows();
   			     rowCount--;//减去标题行
   	             resultstring=resultstring+"读入excel记录数："+rowCount+"\n";
	 	     }
	 	     else{
	 	    	request.setAttribute("importresult",resultstring); 
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	    
   	         if(rowCount>0){
   	        	 if(importMode!=null&&importMode.equals("add")){
   	        		 if(testId!=null&&testId.length()>0)
   	        	         resultstring=resultstring+studentService.saveStuBmbyImport(sheet,testId,userId);
   	        	 }
   	        	 else if(importMode!=null&&importMode.equals("update")){   	        		 
   	        		 resultstring=resultstring+studentService.updateStuBmbyImport(sheet,testId,userId);
   	        	 }
   	        	else if(importMode!=null&&importMode.equals("delete")){
  	        		 if(testId!=null&&testId.length()>0)
  	        	         resultstring=resultstring+studentService.deleteStuBmbyImport(sheet,testId,userId);
  	        	 }
   	         }
   	         else if(rowCount==0){
   	        	if(importMode!=null&&importMode.equals("delete")){
 	        		 if(testId!=null&&testId.length()>0)
 	        	         resultstring=resultstring+studentService.deleteStuBmbyImport(sheet,testId,userId);
 	        	 }
   	         }
   	         else{
   	        	resultstring=resultstring+"请检查excel格式！\n";
   	         }
   	         
   	         request.setAttribute("importresult",resultstring);   	         
   	      
	    }catch(Exception e){
   		      e.printStackTrace();
   		      return mapping.findForward("importfail");
   	    }
	    finally{
	    	checkis.close();
	    	is.close();
	    }
	 }
	    return mapping.findForward("importsuccess");
    }

	public String checkSbModel(InputStream is) throws IOException {
		String resultstring="";		
		HSSFWorkbook wb = new HSSFWorkbook(is);		
		String tableName =  wb.getSheetName(0);		
		HSSFSheet sheet = wb.getSheet(tableName); 		    
		try {			
			int rowCount = sheet.getPhysicalNumberOfRows();
			if(rowCount==0){
				resultstring=resultstring+"Excel格式不正确，请检查！"+"\n";
				return resultstring;
			}
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();
			//检查Excel格式			
			if(colCount!=11){
				resultstring=resultstring+"Excel格式不正确，请检查！"+"\n";
				resultstring=resultstring+"总列数不对，请检查！"+"\n";
				return resultstring;
			}
						
			for(int i = 1; i < rowCount; i++) {
				HSSFRow row = sheet.getRow(i); 
				if(row.getCell((short)0)==null||row.getCell((short)0).getCellType()==HSSFCell.CELL_TYPE_BLANK){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 为必填！\n";
				}
				else if(row.getCell((short)0)!=null&&row.getCell((short)0).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)0).getCellType()!=HSSFCell.CELL_TYPE_STRING){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)0)!=null&&row.getCell((short)0).getStringCellValue().trim().length()>20){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 不能超过20位字符！"+"\n";
				}
				else{
					String curstring=row.getCell((short)0).getStringCellValue().trim();
					for(int j=0;j<curstring.length();j++){
						char curc=curstring.charAt(j);   
						if(!((curc>='0'&&curc<='9')||(curc>='a'&&curc<='z')||(curc>='A'&&curc<='Z'))){
							resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 必须为字母或数字！"+"\n";
							break;
						}
					}
				}
				
				if(row.getCell((short)1)==null||row.getCell((short)1).getCellType()==HSSFCell.CELL_TYPE_BLANK){//姓名
					resultstring=resultstring+"第 "+(i+1)+" 行，第 B 列 为必填！\n";
				}
				else if(row.getCell((short)1)!=null&&row.getCell((short)1).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)1).getCellType()!=HSSFCell.CELL_TYPE_STRING){//姓名
					resultstring=resultstring+"第 "+(i+1)+" 行，第 B 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)1)!=null&&row.getCell((short)1).getStringCellValue().trim().length()>20){//姓名
					resultstring=resultstring+"第 "+(i+1)+" 行，第 B 列 不能超过20个汉字！"+"\n";
				}
				
				if(row.getCell((short)2)!=null&&row.getCell((short)2).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)2).getCellType()!=HSSFCell.CELL_TYPE_STRING){//性别
					resultstring=resultstring+"第 "+(i+1)+" 行，第 C 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)2)!=null&&row.getCell((short)2).getStringCellValue().trim().length()>1){//性别
					resultstring=resultstring+"第 "+(i+1)+" 行，第 C 列 不能超过1个汉字！"+"\n";
				}
				
				if(row.getCell((short)3)!=null&&row.getCell((short)3).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)3).getCellType()!=HSSFCell.CELL_TYPE_STRING){//入学年份
					resultstring=resultstring+"第 "+(i+1)+" 行，第 D 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)3)!=null&&row.getCell((short)3).getStringCellValue().trim().length()>4){//入学年份
					resultstring=resultstring+"第 "+(i+1)+" 行，第 D 列 不能超过4位字符！"+"\n";
				}
				else{
					String curstring=row.getCell((short)3).getStringCellValue().trim();
					int totallen=0;
					for(int j=0;j<curstring.length();j++){
						char curc=curstring.charAt(j);
						if((curc>='0'&& curc<='9')||(curc>='a'&&curc<='z')||(curc>='A'&&curc<='Z')){//字母,数字   
							totallen++;   
						}
						else{   
							if(Character.isLetter(curc)){//中文   
							    totallen+=3;
							}
							else{
								String cstr=String.valueOf(curc);
								if(cstr.getBytes().length!=cstr.length()){//全角符号或控制字符
									totallen+=3;
							    }
								else{//半角符号或控制字符
									totallen++;
								}								
							}
							  
						} 
					}
					
					if(totallen>4)
					    resultstring=resultstring+"第 "+(i+1)+" 行，第 D 列 超长！"+"\n";					
				}
				
				if(row.getCell((short)4)!=null&&row.getCell((short)4).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)4).getCellType()!=HSSFCell.CELL_TYPE_STRING){//学院名称
					resultstring=resultstring+"第 "+(i+1)+" 行，第 E 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)4)!=null&&row.getCell((short)4).getStringCellValue().trim().length()>30){//学院名称
					resultstring=resultstring+"第 "+(i+1)+" 行，第 E 列 不能超过30个汉字！"+"\n";
				}
				
				if(row.getCell((short)5)!=null&&row.getCell((short)5).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)5).getCellType()!=HSSFCell.CELL_TYPE_STRING){//专业名称
					resultstring=resultstring+"第 "+(i+1)+" 行，第 F 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)5)!=null&&row.getCell((short)5).getStringCellValue().trim().length()>40){//专业名称
					resultstring=resultstring+"第 "+(i+1)+" 行，第 F 列 不能超过30个汉字！"+"\n";
				}
				
				if(row.getCell((short)6)!=null&&row.getCell((short)6).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)6).getCellType()!=HSSFCell.CELL_TYPE_STRING){//年级
					resultstring=resultstring+"第 "+(i+1)+" 行，第 G 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)6)!=null&&row.getCell((short)6).getStringCellValue().trim().length()>6){//年级
					resultstring=resultstring+"第 "+(i+1)+" 行，第 G 列 不能超过6位字符！"+"\n";
				}
				
				if(row.getCell((short)7)!=null&&row.getCell((short)7).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)7).getCellType()!=HSSFCell.CELL_TYPE_STRING){//班级
					resultstring=resultstring+"第 "+(i+1)+" 行，第 H 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)7)!=null&&row.getCell((short)7).getStringCellValue().trim().length()>20){//班级
					resultstring=resultstring+"第 "+(i+1)+" 行，第 H 列 不能超过20个汉字！"+"\n";
				}
				
				if(row.getCell((short)8)!=null&&row.getCell((short)8).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)8).getCellType()!=HSSFCell.CELL_TYPE_STRING){//证件类型
					resultstring=resultstring+"第 "+(i+1)+" 行，第 I 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)8)!=null&&row.getCell((short)8).getStringCellValue().trim().length()>6){//证件类型
					resultstring=resultstring+"第 "+(i+1)+" 行，第 I 列 不能超过6个汉字！"+"\n";
				}
				
				if(row.getCell((short)9)!=null&&row.getCell((short)9).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)9).getCellType()!=HSSFCell.CELL_TYPE_STRING){//证件号码
					resultstring=resultstring+"第 "+(i+1)+" 行，第 J 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)9)!=null&&row.getCell((short)9).getStringCellValue().trim().length()>18){//证件号码
					resultstring=resultstring+"第 "+(i+1)+" 行，第 J 列 不能超过18位字符！"+"\n";
				}
				else{
					String curstring=row.getCell((short)9).getStringCellValue().trim();
					int totallen=0;
					for(int j=0;j<curstring.length();j++){
						char curc=curstring.charAt(j);
						if((curc>='0'&& curc<='9')||(curc>='a'&&curc<='z')||(curc>='A'&&curc<='Z')){//字母,数字   
							totallen++;   
						}
						else{   
							if(Character.isLetter(curc)){//中文   
							    totallen+=3;
							}
							else{
								String cstr=String.valueOf(curc);
								if(cstr.getBytes().length!=cstr.length()){//全角符号或控制字符
									totallen+=3;
							    }
								else{//半角符号或控制字符
									totallen++;
								}								
							}
							  
						} 
					}
					
					if(totallen>18)
					    resultstring=resultstring+"第 "+(i+1)+" 行，第 J 列 超长！"+"\n";					
				}
				
				if(row.getCell((short)10)!=null&&row.getCell((short)10).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)10).getCellType()!=HSSFCell.CELL_TYPE_STRING){//电子邮件
					resultstring=resultstring+"第 "+(i+1)+" 行，第 K 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)10)!=null&&row.getCell((short)10).getStringCellValue().trim().length()>50){//电子邮件
					resultstring=resultstring+"第 "+(i+1)+" 行，第 K 列 不能超过50位字符！"+"\n";
				}
				else{
					String curstring=row.getCell((short)10).getStringCellValue().trim();
					int totallen=0;
					for(int j=0;j<curstring.length();j++){
						char curc=curstring.charAt(j);
						if((curc>='0'&& curc<='9')||(curc>='a'&&curc<='z')||(curc>='A'&&curc<='Z')){//字母,数字   
							totallen++;   
						}
						else{   
							if(Character.isLetter(curc)){//中文   
							    totallen+=3;
							}
							else{
								String cstr=String.valueOf(curc);
								if(cstr.getBytes().length!=cstr.length()){//全角符号或控制字符
									totallen+=3;
							    }
								else{//半角符号或控制字符
									totallen++;
								}								
							}
							  
						} 
					}
					
					if(totallen>50)
					    resultstring=resultstring+"第 "+(i+1)+" 行，第 K 列 超长！"+"\n";					
				}
			}
			
			return resultstring;

		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return "error";
		}		
    }
	
	public ActionForward getModel(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
    	
    	String fileName = "studentmodel.xls";

		// Create the Sheet with the name of the Table
		HSSFWorkbook wb = new HSSFWorkbook();

		// 设置显示的字体以及相关的样式
		HSSFFont font = wb.createFont();
		font.setFontHeightInPoints((short) 8);
		font.setItalic(false);
		font.setStrikeout(false);

		// 设置标题栏单元格的样式
		HSSFCellStyle cellHeadStyle = wb.createCellStyle();
		cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellHeadStyle.setBorderBottom((short) 1);
		cellHeadStyle.setBorderLeft((short) 1);
		cellHeadStyle.setBorderRight((short) 1);
		cellHeadStyle.setBorderTop((short) 1);
		cellHeadStyle
				.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
		cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

		// 设置数据行的字体以及以及相关的对齐方式
		HSSFCellStyle cellDataStyle = wb.createCellStyle();
		cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellDataStyle.setFont(font);

		HSSFSheet sheet1 = wb.createSheet("Sheet1");

		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short) 0);

		// Populate the first row of the spreadsheet with the column names
		List columnNames = new ArrayList();
		columnNames.add(0, "学号");
		columnNames.add(1, "姓名");
		columnNames.add(2, "性别");
		columnNames.add(3, "入学年份");
		columnNames.add(4, "学院名称");
		columnNames.add(5, "专业名称");
		columnNames.add(6, "年级");
		columnNames.add(7, "班级");
		columnNames.add(8, "证件类型");
		columnNames.add(9, "证件号码");
		columnNames.add(10, "电子邮件");
						
		HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
		keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		keycellHeadStyle.setBorderBottom((short) 1);
		keycellHeadStyle.setBorderLeft((short) 1);
		keycellHeadStyle.setBorderRight((short) 1);
		keycellHeadStyle.setBorderTop((short) 1);		
		keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);   
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND); 
		
		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cname = row.createCell((short) i);	
			if(i==0||i==1)
				cname.setCellStyle(keycellHeadStyle);
			else
				cname.setCellStyle(cellHeadStyle);
			cname.setEncoding(HSSFCell.ENCODING_UTF_16);			
			cname.setCellValue((String) columnNames.get(i));
		}

		// Populate the Row Data to the SpreadSheet
		int rowCount = 3;
		// goal houses the number of cells in the target spreadsheet
		int goal = rowCount * columnNames.size();
	
		
			// create row in spreadsheet
			row = sheet1.createRow((short)1);

			// populate the spreadsheet with the cell
			HSSFCell ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("993201");
			
			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("陈其");
			
			ctitle = row.createCell((short) 2);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("男");
			
			ctitle = row.createCell((short) 3);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("2005");
			
			ctitle = row.createCell((short) 4);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("新闻学院");
			
			ctitle = row.createCell((short) 5);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("新闻学");
			
			ctitle = row.createCell((short) 6);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("2008");
			
			ctitle = row.createCell((short) 7);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("新闻1班");
						
			ctitle = row.createCell((short) 8);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("身份证");
			
			ctitle = row.createCell((short) 9);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("310105198311042037");
			
			ctitle = row.createCell((short) 10);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("abc@sina.com");
												
            //create row in spreadsheet
			row = sheet1.createRow((short)2);

			//populate the spreadsheet with the cell
			ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("993202");
			
			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("罗家青");
			
			ctitle = row.createCell((short) 2);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("女");
			
			ctitle = row.createCell((short) 3);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("2005");
			
			ctitle = row.createCell((short) 4);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("外国语学院");
			
			ctitle = row.createCell((short) 5);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("英语");
			
			ctitle = row.createCell((short) 6);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("2008");
			
			ctitle = row.createCell((short) 7);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("英语1班");
						
			ctitle = row.createCell((short) 8);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("身份证");
			
			ctitle = row.createCell((short) 9);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("310105198311042046");
			
			ctitle = row.createCell((short) 10);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("jiaqing@163.com");								
		
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition", "attachment;"
				+ " filename="
				+ new String(fileName.getBytes(), "ISO-8859-1"));

		OutputStream os = response.getOutputStream();
		wb.write(os);
		/*-----------------------------------------------------------------------*/
		return null;
    	
    }
	
	public ActionForward load4uploadgrades(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		Map m=new HashMap();
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		m.put("search_beforedate",DateUtil.getNow("yyyy-MM-dd"));
		m.put("operator", (String)session.getAttribute("userName"));
		List testList=testService.getList(m);
		if(testList!=null&&testList.size()>0){
			for(int i=0;i<testList.size();i++){
				Map testm=(Map)testList.get(i);
				String testInfo=(String)testm.get("testCatName");
				if(testm.get("testDate")!=null)
					testInfo=testInfo+" "+(String)testm.get("testDate");
				if(testm.get("testBeginTime")!=null)
					testInfo=testInfo+" "+(String)testm.get("testBeginTime");
				if(testm.get("testEndTime")!=null)
					testInfo=testInfo+"---"+(String)testm.get("testEndTime");
				testm.put("testInfo",testInfo);
			}
			//按考试排序
			Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String curName1 = (String)m1.get("testInfo"); 
				 String curName2 = (String)m2.get("testInfo");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
	            //注意,返回值是比较的结果>0,=0,或者<0
			     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
				 } 
			} ;
			Collections.sort(testList, comp1);
			
			request.setAttribute("testlist",testList);
		}
		return mapping.findForward("gradesselfile");
	}
	
	public ActionForward importGrades(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception{
	   	
   		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";
				
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		if(userId.equals("")){
			return mapping.findForward("faile");
		}
	        	
	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	 	           
	        String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//取得上传的文件
	 	     if(file==null){	 	    	
	 	    	return mapping.findForward("gradesimportfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();
	      	 String size = (file.getFileSize() + " bytes");//文件大小
	      	 
	 	     String fileName= file.getFileName();//文件名
	 	     fileName=request.getParameter("filepath");
	 	     InputStream checkis = file.getInputStream();//把文件读入,用于检查格式
	 	     InputStream is=file.getInputStream();//把文件读入,用于导入数据
	 	     	 	     
	 	     String resultstring="";
	 	     String testId=request.getParameter("testId");
	 	    try{
	 	     resultstring=checkGradesModel(checkis);
	 	     HSSFWorkbook wb =null;
	 	     HSSFSheet sheet=null;
	 	     int rowCount =0;
	 	     if(resultstring.equals("")){
	 	    	 wb=new HSSFWorkbook(is);
   	             String tableName =  wb.getSheetName(0);   			
   			     sheet = wb.getSheet(tableName);
   			     rowCount = sheet.getPhysicalNumberOfRows();
   			     rowCount--;//减去标题行
   	             resultstring=resultstring+"读入excel记录数："+rowCount+"\n";
	 	     }
	 	     else{
	 	    	request.setAttribute("importresult",resultstring); 
	 	    	return mapping.findForward("gradesimportfail");
	 	     }
	 	     
	 	    
   	         if(rowCount>0){
   	        	 resultstring=resultstring+studentService.updateStuGrades(sheet,testId,userId);
   	        	 
   	         }
   	         else if(rowCount<0){
   	        	resultstring=resultstring+"请检查excel格式！\n";
   	         }
   	         
   	         request.setAttribute("importresult",resultstring);   	         
   	      
	    }catch(Exception e){
   		      e.printStackTrace();
   		      return mapping.findForward("gradesimportfail");
   	    }
	    finally{
	    	checkis.close();
	    	is.close();
	    }
	 }
	    return mapping.findForward("gradesimportsuccess");
    }

	public String checkGradesModel(InputStream is) throws IOException {
		String resultstring="";		
		HSSFWorkbook wb = new HSSFWorkbook(is);		
		String tableName =  wb.getSheetName(0);		
		HSSFSheet sheet = wb.getSheet(tableName); 		    
		try {			
			int rowCount = sheet.getPhysicalNumberOfRows();
			if(rowCount==0){
				resultstring=resultstring+"Excel格式不正确，请检查！"+"\n";
				return resultstring;
			}
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();
			//检查Excel格式			
			if(colCount!=2){
				resultstring=resultstring+"Excel格式不正确，请检查！"+"\n";
				resultstring=resultstring+"总列数不对，请检查！"+"\n";
				return resultstring;
			}
						
			for(int i = 1; i < rowCount; i++) {
				HSSFRow row = sheet.getRow(i); 
				if(row.getCell((short)0)==null||row.getCell((short)0).getCellType()==HSSFCell.CELL_TYPE_BLANK){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 为必填！\n";
				}
				else if(row.getCell((short)0)!=null&&row.getCell((short)0).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)0).getCellType()!=HSSFCell.CELL_TYPE_STRING){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 格式须为文本型！"+"\n";
				}
				else if(row.getCell((short)0)!=null&&row.getCell((short)0).getStringCellValue().trim().length()>20){//学号
					resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 不能超过20位字符！"+"\n";
				}
				else{
					String curstring=row.getCell((short)0).getStringCellValue().trim();
					for(int j=0;j<curstring.length();j++){
						char curc=curstring.charAt(j);   
						if(!((curc>='0'&&curc<='9')||(curc>='a'&&curc<='z')||(curc>='A'&&curc<='Z'))){
							resultstring=resultstring+"第 "+(i+1)+" 行，第 A 列 必须为字母或数字！"+"\n";
							break;
						}
					}
				}
				
				if(row.getCell((short)1)!=null&&row.getCell((short)1).getCellType()!=HSSFCell.CELL_TYPE_BLANK&&row.getCell((short)1).getCellType()!=HSSFCell.CELL_TYPE_NUMERIC){//成绩
					resultstring=resultstring+"第 "+(i+1)+" 行，第 B 列 格式须为数字！"+"\n";
				}
				else if(row.getCell((short)1)!=null&&row.getCell((short)1).getNumericCellValue()<0){//成绩
					resultstring=resultstring+"第 "+(i+1)+" 行，第 B 列 考试成绩不能为负数！"+"\n";
				}
				
			}
			
			return resultstring;

		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return "error";
		}		
    }
	
	public ActionForward getGradesModel(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
    	
    	String fileName = "gradesmodel.xls";

		// Create the Sheet with the name of the Table
		HSSFWorkbook wb = new HSSFWorkbook();

		// 设置显示的字体以及相关的样式
		HSSFFont font = wb.createFont();
		font.setFontHeightInPoints((short) 8);
		font.setItalic(false);
		font.setStrikeout(false);

		// 设置标题栏单元格的样式
		HSSFCellStyle cellHeadStyle = wb.createCellStyle();
		cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellHeadStyle.setBorderBottom((short) 1);
		cellHeadStyle.setBorderLeft((short) 1);
		cellHeadStyle.setBorderRight((short) 1);
		cellHeadStyle.setBorderTop((short) 1);
		cellHeadStyle
				.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
		cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

		// 设置数据行的字体以及以及相关的对齐方式
		HSSFCellStyle cellDataStyle = wb.createCellStyle();
		cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellDataStyle.setFont(font);

		HSSFSheet sheet1 = wb.createSheet("Sheet1");

		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short) 0);

		// Populate the first row of the spreadsheet with the column names
		List columnNames = new ArrayList();
		columnNames.add(0, "学号");
		columnNames.add(1, "成绩");
						
		HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
		keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		keycellHeadStyle.setBorderBottom((short) 1);
		keycellHeadStyle.setBorderLeft((short) 1);
		keycellHeadStyle.setBorderRight((short) 1);
		keycellHeadStyle.setBorderTop((short) 1);		
		keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);   
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND); 
		
		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cname = row.createCell((short) i);	
			if(i==0)
				cname.setCellStyle(keycellHeadStyle);
			else
				cname.setCellStyle(cellHeadStyle);
			cname.setEncoding(HSSFCell.ENCODING_UTF_16);			
			cname.setCellValue((String) columnNames.get(i));
		}

		// Populate the Row Data to the SpreadSheet
		int rowCount = 3;
		// goal houses the number of cells in the target spreadsheet
		int goal = rowCount * columnNames.size();
	
		
			// create row in spreadsheet
			row = sheet1.createRow((short)1);

			// populate the spreadsheet with the cell
			HSSFCell ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("993201");
			
			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding((short)HSSFCell.CELL_TYPE_NUMERIC);
			ctitle.setCellValue(90);
															
            //create row in spreadsheet
			row = sheet1.createRow((short)2);

			//populate the spreadsheet with the cell
			ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("993202");
			
			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding((short)HSSFCell.CELL_TYPE_NUMERIC);
			ctitle.setCellValue(85.5);									
		
		response.setContentType("application/x-msdownload");
		response.setHeader("Content-Disposition", "attachment;"
				+ " filename="
				+ new String(fileName.getBytes(), "ISO-8859-1"));

		OutputStream os = response.getOutputStream();
		wb.write(os);
		/*-----------------------------------------------------------------------*/
		return null;
    	
    }
	
	public ActionForward search4historyList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
				
		List li=new ArrayList();
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();	
		m.put("operator", (String)session.getAttribute("userName"));		    
		li=studentService.gethistoryList(m,offset);
		Integer studentCount = studentService.gethistoryCount(m);
		
	    if(li!=null&&li.size()>0){
//	    	 List resultList=new ArrayList();
//             //起始页设置
//			 if(offset.equals("0"))
//			     resultList=li;
//			 else if((Integer.parseInt(offset))<li.size()||(Integer.parseInt(offset))==li.size())
//				 resultList=li.subList((Integer.parseInt(offset)),li.size());
//			 
//			 if(resultList!=null&&resultList.size()>0){
//				 request.setAttribute("stutestlist",resultList);
//				 request.setAttribute("listcount",new Integer(li.size()));		    
//			 }
	    	request.setAttribute("stutestlist",li);
	    	request.setAttribute("listcount",studentCount);		  
	    }
	    
	    Map tm=new HashMap();
	    tm.put("search_beforedate",DateUtil.getNow("yyyy-MM-dd"));
	    tm.put("operator", (String)session.getAttribute("userName"));
		List testList=testService.getList(tm);
		if(testList!=null&&testList.size()>0){
			for(int i=0;i<testList.size();i++){
				Map testm=(Map)testList.get(i);
				String testInfo=(String)testm.get("testCatName");
				if(testm.get("testDate")!=null)
					testInfo=testInfo+" "+(String)testm.get("testDate");
				if(testm.get("testBeginTime")!=null)
					testInfo=testInfo+" "+(String)testm.get("testBeginTime");
				if(testm.get("testEndTime")!=null)
					testInfo=testInfo+"---"+(String)testm.get("testEndTime");
				testm.put("testInfo",testInfo);
			}
			//按考试排序
			Comparator comp1 = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 String curName1 = (String)m1.get("testInfo"); 
				 String curName2 = (String)m2.get("testInfo");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(curName1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(curName2);
	            //注意,返回值是比较的结果>0,=0,或者<0
			     return collator.compare(c1.getSourceString(),c2.getSourceString());			 
				 } 
			} ;
			Collections.sort(testList, comp1);
			
			request.setAttribute("testlist",testList);
		}
		  
		String msg=request.getParameter("msg");
		if(msg!=null&&!msg.equals("")&&!msg.equals("null")&&!msg.equals("undefined"))
		    request.setAttribute("msg",msg);
		
		return (mapping.findForward("historysuccess"));		
		
	} 
			
	public ActionForward deletefoundHistory(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       			
		DynaActionForm curForm = (DynaActionForm) form;
		Map m=new HashMap();
		m=curForm.getMap();	
							    
		List li=studentService.gethistoryList(m);
		
		if(li!=null&&li.size()>0){
			for(int i=0;i<li.size();i++){
				Map lim=(Map)li.get(i);
				BmStuBm bmStuBm = findbyId((String)lim.get("id"));	
				if(bmStuBm!=null)
				    studentService.deleteHistory(bmStuBm);				
			}
		}
		
		return mapping.findForward("historylistredirect");
	}
	
	public ActionForward deleteselectedHistory(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       	
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		    BmStuBm bmStuBm = findbyId(ids[i]);		    
		    if(bmStuBm!=null)
			    studentService.deleteHistory(bmStuBm);
			msg="d0";
		}
		
		request.setAttribute("msg",msg);
		return mapping.findForward("historylist");
	}

	public List reloadSbModel(InputStream is) throws IOException {
		
		HSSFWorkbook wb = new HSSFWorkbook(is);
		
		String tableName =  wb.getSheetName(0);
		
		HSSFSheet sheet = wb.getSheet(tableName); 	
		List result=new ArrayList();
		try {
			//clearAll();
			int rowCount = sheet.getPhysicalNumberOfRows();
			int colCount = sheet.getRow(0).getPhysicalNumberOfCells();				
			
			for(int i = 1; i < rowCount; i++) {
				
				HSSFRow row = sheet.getRow(i); 				
				ArrayList list = new ArrayList();
				
				list.add(row.getCell((short)0).getStringCellValue().trim());//学号	
				
				if(row.getCell((short)1)!=null)
					list.add(row.getCell((short)1).getStringCellValue().trim());//姓名
				else
					list.add("");

				if(row.getCell((short)2)!=null)
					list.add(row.getCell((short)2).getStringCellValue().trim());//性别
				else
					list.add("");
				
				if(row.getCell((short)3)!=null)
					list.add(row.getCell((short)3).getStringCellValue().trim());//入学年份
				else
					list.add("");
				
				if(row.getCell((short)4)!=null)
					list.add(row.getCell((short)4).getStringCellValue().trim());//学院名称
				else
					list.add("");
				
				if(row.getCell((short)5)!=null)
					list.add(row.getCell((short)5).getStringCellValue().trim());//专业名称
				else
					list.add("");
				
				if(row.getCell((short)6)!=null)
					list.add(row.getCell((short)6).getStringCellValue().trim());//年级
				else
					list.add("");
				
				if(row.getCell((short)7)!=null)
					list.add(row.getCell((short)7).getStringCellValue().trim());//班级
				else
					list.add("");
				
				if(row.getCell((short)8)!=null)
					list.add(row.getCell((short)8).getStringCellValue().trim());//证件类型
				else
					list.add("");
				
				if(row.getCell((short)9)!=null)
					list.add(row.getCell((short)9).getStringCellValue().trim());//证件号码
				else
					list.add("");
				
				if(row.getCell((short)10)!=null)
					list.add(row.getCell((short)10).getStringCellValue().trim());//电子邮件
				else
					list.add("");
				
				result.add(list);
			}	
			
			rowCount--;
			return result;
			
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
    }


	public void changeRelatedValues(List list){
		String[][] onoff= Constants.onoff_flag;
		List deptli=studentService.find("select new Map(a.deptCode as deptCode,a.deptName as deptName) from BmDepartment a ");
		List majorli=studentService.find("select new Map(a.majorCode as majorCode,a.majorName as majorName) from BmMajor a ");
		
		HashMap deptMap=new HashMap();
		if(deptli!=null&&deptli.size()>0){
			 for (int i = 0; i < deptli.size(); i++) {
					HashMap temp = (HashMap) deptli.get(i);
					deptMap.put(temp.get("deptName"), temp
							.get("deptCode"));
			 }
		 }
		HashMap majorMap=new HashMap();
		if(majorli!=null&&majorli.size()>0){
			 for (int i = 0; i < majorli.size(); i++) {
					HashMap temp = (HashMap) majorli.get(i);
					majorMap.put(temp.get("majorName"), temp
							.get("majorCode"));
			 }
		 }
		
		for(int i=0;i<list.size();i++){
			Map m=(Map)list.get(i);			
			String stateValue=(String)m.get("ifFee");
			for(int j=0;j<onoff.length;j++){
				if(onoff[j][0].equals(stateValue)){
					m.put("ifFeeName",onoff[j][1]);
				}
			}
			
			String ifBmName="否";
			if(m.get("ifBm")!=null){
				String ifbm=(String)m.get("ifBm");
				for(int j=0;j<onoff.length;j++){
					if(onoff[j][0].equals(ifbm)){
						ifBmName=onoff[j][1];
					}
				}				
			}
			m.put("ifBmName",ifBmName);
			
			String ifPayName="否";
			if(m.get("ifPay")!=null){
				String ifpay=(String)m.get("ifPay");
				for(int j=0;j<onoff.length;j++){
					if(onoff[j][0].equals(ifpay)){
						ifPayName=onoff[j][1];
					}
				}				
			}
			m.put("ifPayName",ifPayName);
			
			String deptCode="";
			String majorCode="";
			if(m.get("deptName")!=null){
				String deptstr=(String)m.get("deptName");
				if(deptMap.get(deptstr)!=null)
					deptCode=(String)deptMap.get(deptstr);
			}
			if(m.get("majorName")!=null){
				String majorstr=(String)m.get("majorName");
				if(majorMap.get(majorstr)!=null)
					majorCode=(String)majorMap.get(majorstr);
			}
			m.put("deptCode",deptCode);
			m.put("majorCode",majorCode);			
		}//for
		
	}

}
