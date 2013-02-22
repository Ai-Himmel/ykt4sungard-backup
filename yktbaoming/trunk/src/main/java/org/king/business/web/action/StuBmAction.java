package org.king.business.web.action;

import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.business.domain.BmStuBm;
import org.king.business.domain.BmStudent;
import org.king.business.domain.BmTest;
import org.king.business.service.StudentService;
import org.king.business.service.TestService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.web.util.Constants;

public class StuBmAction extends BaseAction {
	
	private StudentService studentService;
	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	private TestService testService;
	public void setTestService(TestService testService) {
		this.testService = testService;
	}
	
	public ActionForward stuinfoview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
		
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }
	      
	          try {		            
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String stuNo=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
		            
		            String sqlstring=null;		            
		            
		            sqlstring="select new Map(a.studentNo as studentNo,a.stuName as stuName,a.gender as gender,a.enrollYear as enrollYear," +
				"a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.idType as idType,a.idCard as idCard,a.email as email) from BmStudent a where a.studentNo='"+stuNo+"'";
		            	            
		            List stuinfoList=studentService.find(sqlstring);
		            
		            sqlstring="select new Map(b.cutId as cutId,b.stuempNo as studentNo,a.id.photo as photo) from TCifPhoto a,TCifCustomer b where b.cutId=a.id.cutId and b.stuempNo='" + stuNo+"' ";
		            
		            List stuphotoList=studentService.find(sqlstring);
		            
		            if(stuinfoList!=null&&stuinfoList.size()!=0)
		                request.setAttribute("stuinfolist",stuinfoList);	
		            
		            if(stuphotoList!=null&&stuphotoList.size()>0){
	            		Map photom=(Map)stuphotoList.get(0);
	            		request.setAttribute("cutId",photom.get("cutId"));
	            	}
		            else
		            	request.setAttribute("cutId","");
		           
			        return mapping.findForward("stuinfoview");
			        
	          } catch (Exception e) {
		           e.printStackTrace();
		           return mapping.findForward("faile");
	          }
	   }
	
	public ActionForward load4stuinfoupdate(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
		
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }
	      
	          try {		            
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String stuNo=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
		            
		            String sqlstring=null;		            
		            
		            sqlstring="select new Map(a.studentNo as studentNo,a.stuName as stuName,a.gender as gender,a.enrollYear as enrollYear,a.deptName as deptName,a.majorName as majorName,a.curGrade as curGrade,a.curClass as curClass,a.idType as idType,a.idCard as idCard,a.email as email) from BmStudent a where a.studentNo='"+stuNo+"'";
		            	            
		            List stuinfoList=studentService.find(sqlstring);
		            
		            if(stuinfoList!=null&&stuinfoList.size()!=0)		        	  
		                request.setAttribute("stuinfolist",stuinfoList);		            		            
		            
		            return mapping.findForward("stuinfoedit");
		            
	          } catch (Exception e) {
		           e.printStackTrace();
		           return mapping.findForward("faile");
	          }
	   }

	public ActionForward stuinfoupdate(ActionMapping mapping, ActionForm form,
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
		try {
			
			bmStudent.setUpdator(userId);
			bmStudent.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
			studentService.update(bmStudent);
						
			request.setAttribute("msg",msg);
			return stuinfoview(mapping,form,request,response);
			
		} catch (Exception e) {
			e.printStackTrace();
			msg="1";
			request.setAttribute("msg",msg);
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward search4stuBmList(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
		
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }
	      
	          try {		            
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String stuNo=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
		            		            		            	            
		            List stubmList=studentService.getStuBmList(stuNo,false);//显示报名时间段内该考生未报名的考试列表
		            
		            if(stubmList!=null&&stubmList.size()!=0)		        	  
		                request.setAttribute("stubmlist",stubmList);		            		            
		            
		            String todays=DateUtil.getNow("yyyy-MM-dd HH:mm");
					List stubmli=studentService.find("select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo," +
							"a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee)" +
							" from BmStuBm a where a.ifBm='"+Constants.yesCode+"' and ((a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)>'"+todays+"') and a.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay<>'"+Constants.yesCode+"') and a.bmStudent.studentNo='"+stuNo+"'" +
									" order by a.bmTest.bmEndDate ");
		    		
		    		if(stubmli!=null&&stubmli.size()>0){
		    		    session.setAttribute("giveAlert","1");
		    		}
		    		else{
		    			session.setAttribute("giveAlert","0");
		    		}
		    		
		            return mapping.findForward("stubmlist");
		            
	          } catch (Exception e) {
		           e.printStackTrace();
		           return mapping.findForward("faile");
	          }
	   }
	
	public ActionForward stubm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
		Account freshmen=(Account)session.getAttribute("accountPerson");	            
        
        String stuNo=freshmen.getPerson().getPersonCode();
                
       	String nottoBm="";	
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 String nottoBmName=studentService.check4Bm(ids[i],stuNo);
				 if(!nottoBmName.equals(""))
					 nottoBm=nottoBm+nottoBmName+",";
				 else{
					 BmStuBm bmStuBm = findbyId(ids[i]);
					 bmStuBm.setIfBm(Constants.yesCode);
					 bmStuBm.setBmTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
					  //gejinfeng20091215,不能修改创建时间，只有创建者本人用户才可以修改。
					 // bmStuBm.setUpdator(userId);
					// bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				     studentService.updateStuBm(bmStuBm);
				     msg="0";
				 }
				 
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
		}
		if(nottoBm.length()>1){
			nottoBm=nottoBm.substring(0,nottoBm.length()-1);
			request.setAttribute("nottobm",nottoBm);
		}
		request.setAttribute("msg",msg);
						
		return mapping.findForward("bmsuccess");
	}
	
	public ActionForward stunotbm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		String userId="";		
		if(session.getAttribute(Constants.LOGIN_NAME)!=null)
			userId=(String)session.getAttribute(Constants.LOGIN_NAME);
		
        Account freshmen=(Account)session.getAttribute("accountPerson");	            
        
        String stuNo=freshmen.getPerson().getPersonCode();
                
       	String nottoBm="";	
       	String nottoBmDue="";
		String[] ids=request.getParameterValues("cbgroup");
		
		String msg="";
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 String nottoBmName=studentService.check4NotBm(ids[i]);
				 String nottoBmDueName=studentService.check4NotBmDue(ids[i]);
				 if(!nottoBmName.equals(""))
					 nottoBm=nottoBm+nottoBmName;
				 else if(!nottoBmDueName.equals(""))
					 nottoBmDue=nottoBmDue+nottoBmDueName;				 
				 else{
					 BmStuBm bmStuBm = findbyId(ids[i]);
					 bmStuBm.setIfBm(Constants.noCode);
					 bmStuBm.setBmTime(null);
					// bmStuBm.setUpdator(userId);
					//bmStuBm.setUpdateTime(DateUtil.getDateTime("yyyy-MM-dd HH:mm",new Date()));
				     studentService.updateStuBm(bmStuBm);
				     msg="0";
				 }
				 
		    } catch (Exception e) {
			     e.printStackTrace();
			     return mapping.findForward("faile");
		    }
		}
		if(nottoBm.length()>1){
			nottoBm=nottoBm.substring(0,nottoBm.length()-1);
			request.setAttribute("nottobm",nottoBm);
		}
		if(nottoBmDue.length()>1){
			nottoBmDue=nottoBmDue.substring(0,nottoBmDue.length()-1);
			request.setAttribute("nottobmdue",nottoBmDue);
		}
		request.setAttribute("msg",msg);
						
		return mapping.findForward("notbmsuccess");
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
	
	public ActionForward search4stuBmListview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
		
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }
	      
	          try {		            
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String stuNo=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
		            
		            
                    List stubmList=studentService.getStuBmList(stuNo,true);//显示该考生已报名的考试列表
		            
		            if(stubmList!=null&&stubmList.size()!=0){		        	  
		                request.setAttribute("stubmlist",stubmList);
		                
		                String todays=DateUtil.getNow("yyyy-MM-dd HH:mm");
		                String bmendFirst="";
		                for(int i=0;i<stubmList.size();i++){
							Map stubm=(Map)stubmList.get(i);						
					        String bmendtime=(String)stubm.get("bmEnd");
					        
							if(bmendFirst.equals(""))
								bmendFirst=bmendtime;
							else if(bmendFirst.compareTo(bmendtime)>0&&bmendtime.compareTo(todays)>0){
								bmendFirst=bmendtime;								
							}
						}
						if(!bmendFirst.equals("")&&bmendFirst.compareTo(todays)>0)
							request.setAttribute("bmendfirst",bmendFirst);
		                
		                List feetotalli=studentService.find("select sum(a.bmTest.bmTestCat.fee) as feeTotal from BmStuBm a where a.ifBm='"+Constants.yesCode+"' and ((a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)>'"+todays+"') and a.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay<>'"+Constants.yesCode+"') and a.bmStudent.studentNo='"+stuNo+"'");
						if(feetotalli!=null&&feetotalli.size()>0){
							java.text.DecimalFormat df = new java.text.DecimalFormat("####0.##");
							
							if(feetotalli.get(0)!=null){
							    String feeTotal=df.format(((Double)feetotalli.get(0)).doubleValue());
							    request.setAttribute("feetotal",feeTotal);
							}
						}
		            }
		            
		            String todays=DateUtil.getNow("yyyy-MM-dd HH:mm");
					List stubmli=studentService.find("select new Map(a.id as id,(a.bmTest.bmTestCat.testCatName||' '||a.bmTest.testDate||' '||a.bmTest.testBeginTime||'---'||a.bmTest.testEndTime) as testInfo," +
							"a.bmTest.bmTestCat.ifFee as ifFee,a.bmTest.bmTestCat.fee as fee)" +
							" from BmStuBm a where a.ifBm='"+Constants.yesCode+"' and ((a.bmTest.bmEndDate||' '||a.bmTest.bmEndTime)>'"+todays+"') and a.bmTest.bmTestCat.ifFee='"+Constants.yesCode+"' and (a.ifPay is null or a.ifPay<>'"+Constants.yesCode+"') and a.bmStudent.studentNo='"+stuNo+"'" +
									" order by a.bmTest.bmEndDate ");
		    		
		    		if(stubmli!=null&&stubmli.size()>0){
		    		    session.setAttribute("giveAlert","1");
		    		}
		    		else{
		    			session.setAttribute("giveAlert","0");
		    		}
		    		
		            return mapping.findForward("stubmlistview");
		            
	          } catch (Exception e) {
		           e.printStackTrace();
		           return mapping.findForward("faile");
	          }
	   }

}
