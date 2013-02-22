package org.king.business.web.action;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.business.service.StudentService;
import org.king.business.service.TestService;
import org.king.framework.web.action.BaseAction;

public class FeeTestAction extends BaseAction {
	
	private StudentService studentService;
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	private TestService testService;
	public void setTestService(TestService testService) {
		this.testService = testService;
	}
	public ActionForward searchInit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		   HttpSession session = request.getSession(false);

		   if (session == null) {
			session = request.getSession(true);
		   }
		   Map m=new HashMap();
		   m.put("operator", (String)session.getAttribute("userName"));
		   try{
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
			return mapping.findForward("feeTestUpdateQuery");
			}catch(Exception e) {
				e.printStackTrace();
				return mapping.findForward("faile");
			}
	}
	
	public  ActionForward feeTestUpdateResult(ActionMapping mapping, ActionForm form,
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
			
		    DynaActionForm curForm = (DynaActionForm) form;
		    Map m=new HashMap();
			m=curForm.getMap();	
			m.put("operator", session.getAttribute("userName"));
			List li = new ArrayList();
			li=studentService.getfeeTestList(m,offset); 
			Integer feeListCount = studentService.getfeeTestCount(m);
			if(li!=null && li.size()>0){
				request.setAttribute("feeTestList", li);
				request.setAttribute("listcount", feeListCount);
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
    }
