/**
 * 
 */
package org.king.checkinmanage.web.action;

import java.io.FileOutputStream;
import java.io.OutputStream;
import java.sql.Timestamp;
import java.sql.Time;
import java.text.CollationKey;
import java.text.DateFormat;
import java.text.RuleBasedCollator;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.sql.Date;
import java.util.List;

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
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.security.domain.AbstractAccount;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.utils.DateUtil;

import com.ibm.icu.text.Collator;
/**
 * @author jackey
 *
 */
public class CheckinmanageAction extends BaseAction{
	
	
	private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		Stucheckininfo stucheckininfo = (Stucheckininfo)aform.get("stucheckininfo");
        
		try {
			 
			 stucheckininfo.setIfCheckedin(request.getParameter("ifCheckedin"+request.getParameter("updateid")));
			 if(request.getParameter("ifCheckedin"+request.getParameter("updateid")).equals("0")){//未报到
				 stucheckininfo.setIfChecked("0");
	       	     stucheckininfo.setIfGotMaterial("0");
	       	     stucheckininfo.setIfGotEcard("0");
	             stucheckininfo.setIfGotStucard("0");
			 }
			 if(request.getParameter("ifCheckedin"+request.getParameter("updateid")).equals("1")){
	       	     stucheckininfo.setIfChecked(request.getParameter("ifChecked"+request.getParameter("updateid")));
	       	     stucheckininfo.setIfGotMaterial(request.getParameter("ifGotMaterial"+request.getParameter("updateid")));
	       	     stucheckininfo.setIfGotEcard(request.getParameter("ifGotEcard"+request.getParameter("updateid")));
	             stucheckininfo.setIfGotStucard(request.getParameter("ifGotStucard"+request.getParameter("updateid")));
			 }
			 
	      	 stucheckininfo.setReason(request.getParameter("reason"+request.getParameter("updateid")));
	      	 
	      	 if(request.getParameter("memo"+request.getParameter("updateid")).length()==0)
	      		stucheckininfo.setMemo("");
	      	 else
	            stucheckininfo.setMemo(request.getParameter("memo"+request.getParameter("updateid")));
	      		      	 
	      	 stucheckininfo.setStudentNo(request.getParameter("studentNo"+request.getParameter("updateid")));
	      	 stucheckininfo.setEnrollNo(request.getParameter("enrollNo"+request.getParameter("updateid")));
	      	 stucheckininfo.setEnrollYear(request.getParameter("enrollYear"+request.getParameter("updateid")));
	      	 stucheckininfo.setIfReserve(request.getParameter("ifReserve"+request.getParameter("updateid")));
	      	 stucheckininfo.setIfLeaveSchool(request.getParameter("ifLeaveSchool"+request.getParameter("updateid")));
	      	 stucheckininfo.setIfSubmitted(request.getParameter("ifSubmitted"+request.getParameter("updateid")));
	      	 stucheckininfo.setUpdatorId(request.getParameter("updatorId"+request.getParameter("updateid")));
	      	 stucheckininfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
		     stucheckininfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stucheckininfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			return list(mapping, form, request, response);
		}

	}
	
	public ActionForward updateall(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		boolean flag=false;
		
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		    DynaValidatorForm aform = (DynaValidatorForm) form;	        
		    Stucheckininfo stucheckininfo = new Stucheckininfo();
        
		    try {
			 
			 stucheckininfo.setIfCheckedin(request.getParameter("ifCheckedin"+ids[i]));
			 if(request.getParameter("ifCheckedin"+ids[i]).equals("0")){//未报到
				 stucheckininfo.setIfChecked("0");
	       	     stucheckininfo.setIfGotMaterial("0");
	       	     stucheckininfo.setIfGotEcard("0");
	             stucheckininfo.setIfGotStucard("0");
			 }
			 if(request.getParameter("ifCheckedin"+ids[i]).equals("1")){
	       	     stucheckininfo.setIfChecked(request.getParameter("ifChecked"+ids[i]));
	       	     stucheckininfo.setIfGotMaterial(request.getParameter("ifGotMaterial"+ids[i]));
	       	     stucheckininfo.setIfGotEcard(request.getParameter("ifGotEcard"+ids[i]));
	             stucheckininfo.setIfGotStucard(request.getParameter("ifGotStucard"+ids[i]));
			 }
	      	 stucheckininfo.setReason(request.getParameter("reason"+ids[i]));
	      	 stucheckininfo.setMemo(request.getParameter("memo"+ids[i]));
	      		      	 
	      	 stucheckininfo.setStudentNo(request.getParameter("studentNo"+ids[i]));
	      	 stucheckininfo.setEnrollNo(request.getParameter("enrollNo"+ids[i]));
	      	 stucheckininfo.setEnrollYear(request.getParameter("enrollYear"+ids[i]));
	      	 stucheckininfo.setIfReserve(request.getParameter("ifReserve"+ids[i]));
	      	 stucheckininfo.setIfLeaveSchool(request.getParameter("ifLeaveSchool"+ids[i]));
	      	 stucheckininfo.setIfSubmitted(request.getParameter("ifSubmitted"+ids[i]));
	      	 stucheckininfo.setUpdatorId(request.getParameter("updatorId"+ids[i]));
	      	 stucheckininfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
		     stucheckininfo.setId(ids[i]);

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stucheckininfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			flag=false;
			return list(mapping, form, request, response);
		    }
		}
		if(flag)
		    return mapping.findForward("success");
		else{
			request.setAttribute("msg","1");
		    return list(mapping, form, request, response);
		}

	}
	
	public ActionForward find(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			    Studentmodel stuinfo=new Studentmodel();
				stuinfo.setEnterenceNo(request.getParameter("henrollNo"));
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));
				stuinfo.setGender(request.getParameter("hgender"));				
				stuinfo.setMajorin(request.getParameter("hmajorin"));							
			 
                //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
			 
             //班级报到信息提交表查询,classNo要从session中取得
			 List stuarriveinfoList=null;
			 String classNo="";			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Classmodel c,Managermodel m,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
	         if(managerclassList!=null&&managerclassList.size()>0){
	        	 
				 classNo=(String)managerclassList.get(0);
			     String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs where cs.classNo='"+classNo+"'";
			 
			     List checkinsubminList=checkinmanageservice.find(sqlstring);
			 
			     if(checkinsubminList!=null&&checkinsubminList.size()>0)
				     request.setAttribute("checkinsubmin",checkinsubminList);
			 
			     sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId";
			 
			    if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				    sqlstring=sqlstring+" and ci.enrollNo like '%"+request.getParameter("henrollNo")+"%'";
			 
			    if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				    sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			    if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				    sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			    if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				    sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			 
			    if(request.getParameter("fh_ifCheckedin")!=null&&request.getParameter("fh_ifCheckedin").length()!=0)
			        sqlstring=sqlstring+" and ci.ifCheckedin='"+request.getParameter("fh_ifCheckedin")+"'";
			 
			    if(request.getParameter("fh_ifChecked")!=null&&request.getParameter("fh_ifChecked").length()!=0)
			       sqlstring=sqlstring+" and ci.ifChecked='"+request.getParameter("fh_ifChecked")+"'";
			 
			    if(request.getParameter("fh_ifGotMaterial")!=null&&request.getParameter("fh_ifGotMaterial").length()!=0)
		    	    sqlstring=sqlstring+" and ci.ifGotMaterial='"+request.getParameter("fh_ifGotMaterial")+"'";
			 
			    if(request.getParameter("fh_ifGotEcard")!=null&&request.getParameter("fh_ifGotEcard").length()!=0)
		           sqlstring=sqlstring+" and ci.ifGotEcard='"+request.getParameter("fh_ifGotEcard")+"'";
			 
			    if(request.getParameter("fh_ifGotStucard")!=null&&request.getParameter("fh_ifGotStucard").length()!=0)
			      sqlstring=sqlstring+" and ci.ifGotStucard='"+request.getParameter("fh_ifGotStucard")+"'";
			 
			    sqlstring=sqlstring+" and c.classNo='"+classNo+"'";//班级条件,要从session中获取
			    
			    sqlstring=sqlstring+" order by ci.studentNo";
			 
			    //System.out.println(sqlstring);
			 
			    stuarriveinfoList=checkinmanageservice.find(sqlstring);
	         }
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("stuinfo",stuinfo);				 			 
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));				 
				 }
				 
			 }			 
             return mapping.findForward("findlist"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}


   public ActionForward findstuinfo(ActionMapping mapping, ActionForm form,
	    HttpServletRequest request, HttpServletResponse response)
	    throws Exception {
      HttpSession session = request.getSession(false);

      if (session == null) {
	      session = request.getSession(true);
      }

        ActionMessages errors = new ActionMessages();
        

	// 数据库验证
          try {
	            if(checkinmanageservice==null)
	            	 System.out.println("service is null");
				 		 
	            String sqlstring=null;
	            	            
	            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and s.enterenceNo='"+request.getParameter("stucheckininfo.enrollNo")+"'";
	            	            
	            List stuinfoList=checkinmanageservice.find(sqlstring);
	 
	            if(stuinfoList!=null&&stuinfoList.size()!=0){
	            request.setAttribute("stuinfo",stuinfoList);
	 	        System.out.println("find student success");
	            return mapping.findForward("reservelist");
	       }
	       else
		        return mapping.findForward("reservelist");
          } catch (Exception e) {
	           e.printStackTrace();
	           System.out.println("find error");
	           return mapping.findForward("faile");
          }

   }
	
	public ActionForward list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
             //班级报到信息提交表查询,classNo要从session中取得
			 List stucheckininfoList=null;
			 String classNo="";
			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and m.managerNo='"+managerNo+"'");//查找该人是否为某班级的辅导员
			 
	         if(managerclassList!=null&&managerclassList.size()>0){
				 classNo=(String)managerclassList.get(0);
	         
	             String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs where cs.classNo='"+classNo+"'";
			 
			     List checkinsubminList=checkinmanageservice.find(sqlstring);
			 
			     if(checkinsubminList!=null&&checkinsubminList.size()>0)
				      request.setAttribute("checkinsubmin",checkinsubminList);
			 
			     //指定班级的新生报到信息列表,classNo要从session中取得
			     stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+classNo+"'");
	         } 
	         
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 request.setAttribute("checkinlist",stucheckininfoList);				 
				 request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
                 //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				 System.out.println("list success");
				 return mapping.findForward("checkinmanagelist");
			 }
			 else
				 return mapping.findForward("checkinmanagelist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}	
	
	//新生入学信息列表
	public ActionForward stuinfolist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		try{
			//生源地
			List areaList=getfromProvinceList();
			if(areaList!=null&&areaList.size()>0)
				 request.setAttribute("arealist",areaList);
			//专业
			List majorList=getmajorList();
			if(majorList!=null&&majorList.size()>0)
				request.setAttribute("majorinlist",majorList);
			return mapping.findForward("stuinfolist");
		}catch(Exception e){
			e.printStackTrace();
			return mapping.findForward("faile");
		}
		
        

	}
	
	//新生入学信息查询
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
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
                //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
                //生源地
				List areaList=getfromProvinceList();
				if(areaList!=null&&areaList.size()>0)
					request.setAttribute("arealist",areaList);
                //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);   
			 
			 Studentmodel stuinfo=new Studentmodel();
			 stuinfo.setStuName(request.getParameter("hstuName"));
			 stuinfo.setStudentNo(request.getParameter("hstudentNo"));
			 stuinfo.setGender(request.getParameter("hgender"));
			 stuinfo.setMajorin(request.getParameter("hmajorin"));
			 stuinfo.setFromProvince(request.getParameter("hfromProvince"));
			 
			 String classNo=request.getParameter("hclassNo");
			 
		     
			 String sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			 
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
			 
			 if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			     sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
			 			 
			 sqlstring=sqlstring+" order by s.studentNo";
			 			 
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
			
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
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
			            if(checkinmanageservice==null)
			            	 System.out.println("service is null");
			            
                        //生源地
						List areaList=getfromProvinceList();
						if(areaList!=null&&areaList.size()>0)
							request.setAttribute("arealist",areaList);
		                //专业
						List majorList=getmajorList();
						if(majorList!=null&&majorList.size()>0)
							request.setAttribute("majorinlist",majorList); 
						 		 
			            String sqlstring=null;
			            	            
			            //sqlstring="select new Map(ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit) from Stucheckininfo ci,Stuarchivesinfo ai,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=s.studentNo and s.yxClass.classId=c.classId and s.studentNo='"+request.getParameter("updateid")+"'";
			            //新生个人信息
			            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.studentNo='"+request.getParameter("updateid")+"'";
			            	            
			            List stuinfoList=checkinmanageservice.find(sqlstring);
			            
			            //新生报到信息
			            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit,hi.ifUnhealthy as ifUnhealthy) from Stucheckininfo ci,Stuarchivesinfo ai,Stuhealthinfo hi,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=ci.studentNo and hi.studentNo=ci.studentNo and s.yxClass.classId=c.classId and ci.studentNo='"+request.getParameter("updateid")+"'";
			            
			            List stucheckinList=checkinmanageservice.find(sqlstring);	
			            
                        //新生一卡通拍照信息
			            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollYear as enrollYear,ci.ecardPhoto as ecardPhoto) from StuCardfeeInfo ci where ci.studentNo='"+request.getParameter("updateid")+"'";
			            
			            List ecardPhotoList=checkinmanageservice.find(sqlstring);
			            
			            if(ecardPhotoList!=null&&ecardPhotoList.size()>0)
			            	request.setAttribute("ecardphotolist",ecardPhotoList);
                        
			            if(stucheckinList!=null&&stucheckinList.size()>0)
			            	request.setAttribute("checkinlist",stucheckinList);
			            
			          if(stuinfoList!=null&&stuinfoList.size()!=0){
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
	 
	 //复旦学院查看新生入学信息	 
	 public ActionForward stucheckinlist(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
			    throws Exception {
		      HttpSession session = request.getSession(false);

		      if (session == null) {
			      session = request.getSession(true);
		      }

		        ActionMessages errors = new ActionMessages();
		        List s1=new ArrayList();
		        			
		          try {
			            if(checkinmanageservice==null)
			            	 System.out.println("service is null");
			            
                        //起始页
						String offset = request.getParameter("pager.offset");
						if (offset == null) {
							offset = "0";
						}
						
						 Studentmodel stuinfo=new Studentmodel();
						 stuinfo.setStuName(request.getParameter("hstuName"));
						 stuinfo.setStudentNo(request.getParameter("hstudentNo"));
						 stuinfo.setGender(request.getParameter("hgender"));
						 stuinfo.setMajorin(request.getParameter("hmajorin"));
						 stuinfo.setFromProvince(request.getParameter("hfromProvince"));
						 
						 String classNo=request.getParameter("hclassNo");
			            
                        //生源地
						List areaList=getfromProvinceList();
						if(areaList!=null&&areaList.size()>0)
							request.setAttribute("arealist",areaList);
		                //专业
						List majorList=getmajorList();
						if(majorList!=null&&majorList.size()>0)
							request.setAttribute("majorinlist",majorList); 
						 		 
			            String sqlstring=null;
			            
			            String order=request.getParameter("horder");
					    String odr="asc";
					    if(order!=null&&order.length()>0&&order.equals("d"))
					    	 odr="desc";
						String orderby=request.getParameter("orderby");
			            
			            //新生报到信息
			            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit,hi.ifUnhealthy as ifUnhealthy,ei.ecardPhoto as ecardPhoto) from Stucheckininfo ci,Stuarchivesinfo ai,Stuhealthinfo hi,StuCardfeeInfo ei,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=ci.studentNo and hi.studentNo=ci.studentNo and ei.studentNo=ci.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			            
			            if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
							 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
						 
						 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
							 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
									 
						 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
							 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
									
						 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
							 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
						 
						 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
							 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
						 
						 if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
						     sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
						 			 
						 if(orderby==null||orderby.length()==0)
			            	 sqlstring=sqlstring+" order by ci.studentNo";
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
			                 sqlstring=sqlstring+" order by ci.studentNo"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName"))
			                 sqlstring=sqlstring+" order by s.stuName"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("gender"))
			                 sqlstring=sqlstring+" order by s.gender"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("majorin"))
			                 sqlstring=sqlstring+" order by s.majorin"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("fromProvince"))
			                 sqlstring=sqlstring+" order by s.fromProvince"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifCheckedin"))
			                 sqlstring=sqlstring+" order by ci.ifCheckedin"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifChecked"))
			                 sqlstring=sqlstring+" order by ci.ifChecked"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotMaterial"))
			                 sqlstring=sqlstring+" order by ci.ifGotMaterial"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ecardPhoto"))
			                 sqlstring=sqlstring+" order by ei.ecardPhoto"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotEcard"))
			                 sqlstring=sqlstring+" order by ci.ifGotEcard"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("hasArchives"))
			                 sqlstring=sqlstring+" order by ai.hasArchives"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("hasStuarchive"))
			                 sqlstring=sqlstring+" order by ai.hasStuarchive"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifUnhealthy"))
			                 sqlstring=sqlstring+" order by hi.ifUnhealthy"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotStucard"))
			                 sqlstring=sqlstring+" order by ci.ifGotStucard"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("classNo"))
			                 sqlstring=sqlstring+" order by c.classNo"+" "+odr;
						 
			            List stucheckinList=checkinmanageservice.find(sqlstring);		
			            
			            if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName")){
		                	Comparator comp1 = new Comparator() { 
		       				 public int compare(Object o1, Object o2){ 
		       				 Map m1 = (Map)o1; 
		       				 Map m2 = (Map)o2; 
		       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		       				 String collegeName1 = (String)m1.get("stuName"); 
		      				 String collegeName2 = (String)m2.get("stuName");      				

		      				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
		      				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
		      				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
		                     //注意,返回值是比较的结果>0,=0,或者<0
		       			     //return collator.compare(((CollationKey)c1).getSourceString(), ((CollationKey)c2).getSourceString());
		                     return collator.compare(c1.getSourceString(),c2.getSourceString());
		       				 //return collegeName1.compareTo(collegeName2); 
		       				 } 
		       				} ;
		       				Comparator comp2 = new Comparator() { 
		          				 public int compare(Object o1, Object o2){ 
		          				 Map m1 = (Map)o1; 
		          				 Map m2 = (Map)o2; 
		          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		          				String collegeName1 = (String)m1.get("stuName"); 
		          				String collegeName2 = (String)m2.get("stuName");
		          				
		          				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
		          				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
		          				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
		                        //注意,返回值是比较的结果>0,=0,或者<0
		          			     //return collator.compare(((CollationKey)c2).getSourceString(), ((CollationKey)c1).getSourceString()); 
		          				return collator.compare(c2.getSourceString(),c1.getSourceString());
		          				 //return collegeName2.compareTo(collegeName1); 
		          				 } 
		          				} ;
		       			 if(odr.equals("asc"))	
		       		         Collections.sort(stucheckinList, comp1);
		       			 else
		       				 Collections.sort(stucheckinList, comp2);
		       		     
		                }
                        
			          if(stucheckinList!=null&&stucheckinList.size()!=0){
			        	  
			        	  s1=stucheckinList;
			          }
			          
			          if(s1!=null&&s1.size()>0){
			        	  List resultList=new ArrayList();
							 //起始页设置
							 if(offset.equals("0"))
							     resultList=s1;
							 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
								 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
							 
							 if(resultList!=null&&resultList.size()>0){
								 request.setAttribute("stuinfo",stuinfo);
								 request.setAttribute("classNo",classNo);
							     request.setAttribute("checkinlist",resultList);
							     request.setAttribute("listcount",new Integer(s1.size()));	
							     request.setAttribute("order",order);
					          } 
							 
						 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
														 
							 ChangeGenderValue(s1);
							 ChangeMajorValue(s1);
							 ChangefromProvinceValue(s1);
							 
							 ChangeCheckinValue(s1);
							 ChangeCheckValue(s1);
							 ChangeGotMaterialValue(s1);
							 ChangeEcardPhotoValue(s1);
							 ChangeGotEcardValue(s1);
							 ChangeGotStucardValue(s1);
							 ChangeUnhealthyValue(s1);
							 ChangeArchivesValue(s1);							 
							 ChangeStuArchiveValue(s1);		
							 
							 ExportstucheckinList(s1,response);
							 
							 return null;
			          }
					  else							 
							return mapping.findForward("stucheckinlist");
			        }else
				           return mapping.findForward("stucheckinlist");
		          } catch (Exception e) {
			           e.printStackTrace();
			           System.out.println("find error");
			           return mapping.findForward("faile");
		          }

		   }
	 
     //辅导员查看班级入学信息	 
	 public ActionForward classcheckinlist(ActionMapping mapping, ActionForm form,
			    HttpServletRequest request, HttpServletResponse response)
			    throws Exception {
		      HttpSession session = request.getSession(false);

		      if (session == null) {
			      session = request.getSession(true);
		      }

		        ActionMessages errors = new ActionMessages();
		        List s1=new ArrayList();
		        			
		          try {
			            if(checkinmanageservice==null)
			            	 System.out.println("service is null");
			            
                        //起始页
						String offset = request.getParameter("pager.offset");
						if (offset == null) {
							offset = "0";
						}
						
						 Studentmodel stuinfo=new Studentmodel();
						 stuinfo.setStuName(request.getParameter("hstuName"));
						 stuinfo.setStudentNo(request.getParameter("hstudentNo"));
						 stuinfo.setGender(request.getParameter("hgender"));
						 stuinfo.setMajorin(request.getParameter("hmajorin"));
						 stuinfo.setFromProvince(request.getParameter("hfromProvince"));					 
						
			            
                        //生源地
						List areaList=getfromProvinceList();
						if(areaList!=null&&areaList.size()>0)
							request.setAttribute("arealist",areaList);
		                //专业
						List majorList=getmajorList();
						if(majorList!=null&&majorList.size()>0)
							request.setAttribute("majorinlist",majorList); 
						 		 
			            String sqlstring=null;
			            
			            String order=request.getParameter("horder");
					    String odr="asc";
					    if(order!=null&&order.length()>0&&order.equals("d"))
					    	 odr="desc";
						String orderby=request.getParameter("orderby");
			            
			            List stucheckinList=new ArrayList();
			            String classNo="";			 
						Account manager=(Account)session.getAttribute("accountPerson");	            
					    String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
					    List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and (mmr.id.roleId='21' or mmr.id.roleId='22') and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
					    
					if(managerclassList!=null&&managerclassList.size()>0){		        	 

			             classNo=(String)managerclassList.get(0);
			            
			            //新生报到信息
			            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit,hi.ifUnhealthy as ifUnhealthy,ei.ecardPhoto as ecardPhoto) from Stucheckininfo ci,Stuarchivesinfo ai,Stuhealthinfo hi,StuCardfeeInfo ei,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=ci.studentNo and hi.studentNo=ci.studentNo and ei.studentNo=ci.studentNo and s.yxClass.classId=c.classId and c.classNo='"+classNo+"'";
			            
			            if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
							 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
						 
						 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
							 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
									 
						 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
							 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
									
						 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
							 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";						 
						 
						 if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
						     sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
						 			 
						 if(orderby==null||orderby.length()==0)
			            	 sqlstring=sqlstring+" order by ci.studentNo";
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
			                 sqlstring=sqlstring+" order by ci.studentNo"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName"))
			                 sqlstring=sqlstring+" order by s.stuName"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("gender"))
			                 sqlstring=sqlstring+" order by s.gender"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("majorin"))
			                 sqlstring=sqlstring+" order by s.majorin"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("fromProvince"))
			                 sqlstring=sqlstring+" order by s.fromProvince"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifCheckedin"))
			                 sqlstring=sqlstring+" order by ci.ifCheckedin"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifChecked"))
			                 sqlstring=sqlstring+" order by ci.ifChecked"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotMaterial"))
			                 sqlstring=sqlstring+" order by ci.ifGotMaterial"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ecardPhoto"))
			                 sqlstring=sqlstring+" order by ei.ecardPhoto"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotEcard"))
			                 sqlstring=sqlstring+" order by ci.ifGotEcard"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("hasArchives"))
			                 sqlstring=sqlstring+" order by ai.hasArchives"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("hasStuarchive"))
			                 sqlstring=sqlstring+" order by ai.hasStuarchive"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifUnhealthy"))
			                 sqlstring=sqlstring+" order by hi.ifUnhealthy"+" "+odr;
			             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotStucard"))
			                 sqlstring=sqlstring+" order by ci.ifGotStucard"+" "+odr;
						 
			            stucheckinList=checkinmanageservice.find(sqlstring);
			            
			            if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName")){
		                	Comparator comp1 = new Comparator() { 
		       				 public int compare(Object o1, Object o2){ 
		       				 Map m1 = (Map)o1; 
		       				 Map m2 = (Map)o2; 
		       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		       				 String collegeName1 = (String)m1.get("stuName"); 
		      				 String collegeName2 = (String)m2.get("stuName");      				

		      				 com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
		      				 com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
		      				 com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
		                     //注意,返回值是比较的结果>0,=0,或者<0
		       			     //return collator.compare(((CollationKey)c1).getSourceString(), ((CollationKey)c2).getSourceString());
		                     return collator.compare(c1.getSourceString(),c2.getSourceString());
		       				 //return collegeName1.compareTo(collegeName2); 
		       				 } 
		       				} ;
		       				Comparator comp2 = new Comparator() { 
		          				 public int compare(Object o1, Object o2){ 
		          				 Map m1 = (Map)o1; 
		          				 Map m2 = (Map)o2; 
		          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		          				String collegeName1 = (String)m1.get("stuName"); 
		          				String collegeName2 = (String)m2.get("stuName");
		          				
		          				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
		          				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
		          				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
		                        //注意,返回值是比较的结果>0,=0,或者<0
		          			     //return collator.compare(((CollationKey)c2).getSourceString(), ((CollationKey)c1).getSourceString()); 
		          				return collator.compare(c2.getSourceString(),c1.getSourceString());
		          				 //return collegeName2.compareTo(collegeName1); 
		          				 } 
		          				} ;
		       			 if(odr.equals("asc"))	
		       		         Collections.sort(stucheckinList, comp1);
		       			 else
		       				 Collections.sort(stucheckinList, comp2);
		       		     
		                }
			            
					}  			            
			            
			          if(stucheckinList!=null&&stucheckinList.size()!=0){
			        	  
			        	  s1=stucheckinList;
					  }   
			          if(s1!=null&&s1.size()>0){
			        	  List resultList=new ArrayList();
							 //起始页设置
							 if(offset.equals("0"))
							     resultList=s1;
							 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
								 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
							 
							 if(resultList!=null&&resultList.size()>0){
								 request.setAttribute("stuinfo",stuinfo);								 
							     request.setAttribute("checkinlist",resultList);
							     request.setAttribute("listcount",new Integer(s1.size()));		
							     request.setAttribute("order",order);
					          }   
			            
			          
			          
			          if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
							 
							 ChangeGenderValue(s1);
							 ChangeMajorValue(s1);
							 ChangefromProvinceValue(s1);
							 
							 ChangeCheckinValue(s1);
							 ChangeCheckValue(s1);
							 ChangeGotMaterialValue(s1);
							 ChangeEcardPhotoValue(s1);
							 ChangeGotEcardValue(s1);
							 ChangeGotStucardValue(s1);
							 ChangeUnhealthyValue(s1);
							 ChangeArchivesValue(s1);							 
							 ChangeStuArchiveValue(s1);		
							 
							 ExportstucheckinList(s1,response);
							 
							 return null;
			          }
					  else
				          return mapping.findForward("classcheckinlist");
			          
			       }else
			        	  return mapping.findForward("classcheckinlist");
		          } catch (Exception e) {
			           e.printStackTrace();
			           System.out.println("find error");
			           return mapping.findForward("faile");
		          }

	}
		 
	//教务员提交或退回统计结果
	public ActionForward tongjilist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
            //班级报到信息提交表查询
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 List sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by c.classNo");
				 List sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by c.classNo");
				 List sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by c.classNo");
				 List sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by c.classNo");
				 List sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				 
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by c.classNo");
				 List sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
				 
				 
				 //保留入学资格人数
				 //List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' group by c.classNo");
				 //List sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				 //放弃入学资格人数
				// List sl8=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' group by c.classNo");
				// List sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",null);
						 }
					 }
					 else
						 m.put("exactcheckinNum",null);
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",null);
						 }
					 }
					 else
						 m.put("notcheckinNum",null);
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("classNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",null);
						 }
					 }
					 else
						 m.put("askforlateNum",null);
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("classNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",null);
						 }
					 }
					 else
						 m.put("askreserveNum",null);
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("classNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",null);
						 }
					 }
					 else
						 m.put("noreasonNum",null); 
					
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",null);
						 }
					 }
					 else
						 m.put("notcomeNum",null);					 
					 
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",null);
						 }
					 }
					 else
						 m.put("reserveNum",null); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("classNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",null);
						 }
					 }
					 else
						 m.put("leaveschoolNum",null);
				     */
					 
					 //班级报到提交状态
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//表中无该班的提交记录,则说明该班报到信息未提交
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//表为空,所有班级均未提交报到信息	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                 //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",null);
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",null);
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",null);
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",null);
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",null); 
					 
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",null); 
					
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",null); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",null);
					*/
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
		 
			 
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 request.setAttribute("tjlist",stucheckininfoList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);
				 System.out.println("tongji list success");
				 System.out.println(stucheckininfoList.size());
				 return mapping.findForward("tongjilist");
			 }
			 else
				 return mapping.findForward("tongjilist"); 

			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
    //按男女统计结果一览
	public ActionForward tongjilistallview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckinschoolList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");			 
			 
			 List collegeList=getCollegeList();
			 if(collegeList!=null&&collegeList.size()>0)
				 request.setAttribute("collegelist",collegeList);
		
			 String[][] colandclsList=getColandCls();
			 if(colandclsList!=null&&colandclsList.length>0){
				 request.setAttribute("classlist",colandclsList);				 
			 }
			 
			 
			 
			 
			String classNo=request.getParameter("hclassNo");
			String collegeId=request.getParameter("hcollegeId");
			 
           //班级报到信息提交表查询
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 
			 List sl1schooltotal=new ArrayList();
			 List sl1total=new ArrayList();			 
			 
			 sl1schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
			 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //应到男生数
				 List sl1male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by c.classNo");
				 
				 List sl1schooltotalmale=new ArrayList();
				 List sl1totalmale=new ArrayList();			 
				 
				 sl1schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by col.collegeNo");
				 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1'");
					
				 //应到女生数
                 List sl1female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by c.classNo");
				 
				 List sl1schooltotalfemale=new ArrayList();
				 List sl1totalfemale=new ArrayList();			 
				 
				 sl1schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by col.collegeNo");
				 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2'");
								 
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by c.classNo");
				 List sl2schooltotal=new ArrayList();
				 List sl2total=new ArrayList();				 
				 sl2schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //实到男生数
				 List sl2male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='1' group by c.classNo");
				 List sl2schooltotalmale=new ArrayList();
				 List sl2totalmale=new ArrayList();				 
				 sl2schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by col.collegeNo");
				 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='1'");
				 
                 //实到女生数
				 List sl2female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='2' group by c.classNo");
				 List sl2schooltotalfemale=new ArrayList();
				 List sl2totalfemale=new ArrayList();				 
				 sl2schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by col.collegeNo");
				 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='2'");
				 				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3schooltotal=new ArrayList();
				 List sl3total=new ArrayList();				 
				 sl3schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //未到男生数
				 List sl3male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.gender='1' group by c.classNo");
				 List sl3schooltotalmale=new ArrayList();
				 List sl3totalmale=new ArrayList();				 
				 sl3schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by col.collegeNo");
				 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.gender='1'");
                 
				 //未到女生数
				 List sl3female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.gender='2' group by c.classNo");
				 List sl3schooltotalfemale=new ArrayList();
				 List sl3totalfemale=new ArrayList();				 
				 sl3schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by col.collegeNo");
				 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.gender='2'");
                 				 
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by c.classNo");
				 List sl4schooltotal=new ArrayList();
				 List sl4total=new ArrayList();				 
				 sl4schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as askforlateNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by c.classNo");
				 List sl5schooltotal=new ArrayList();
				 List sl5total=new ArrayList();				 
				 sl5schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as askreserveNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by c.classNo");
				 List sl6schooltotal=new ArrayList();
				 List sl6total=new ArrayList();				 
				 sl6schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as noreasonNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by c.classNo");
				 List sl7schooltotal=new ArrayList();
				 List sl7total=new ArrayList();				 
				 sl7schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcomeNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
				
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' group by c.classNo");
				 List sl7schooltotal=new ArrayList();
				 List sl7total=new ArrayList();				 
				 sl7schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as reserveNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId group by col.collegeNo");
				 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' group by c.classNo");
				 List sl8schooltotal=new ArrayList();
				 List sl8total=new ArrayList();				 
				 sl8schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as leaveschoolNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId group by col.collegeNo");
				 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl1male!=null&&sl1male.size()>0){
						 int j=0;
						 for(j=0;j<sl1male.size();j++){
					         Map m1male=(Map)sl1male.get(j);
					         if(((String)m1male.get("classNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1male.size()||j>sl1male.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1female!=null&&sl1female.size()>0){
						 int j=0;
						 for(j=0;j<sl1female.size();j++){
					         Map m1female=(Map)sl1female.get(j);
					         if(((String)m1female.get("classNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1female.size()||j>sl1female.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2male!=null&&sl2male.size()>0){
						 int j=0;
						 for(j=0;j<sl2male.size();j++){
					         Map m2male=(Map)sl2male.get(j);
					         if(((String)m2male.get("classNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2male.size()||j>sl2male.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2female!=null&&sl2female.size()>0){
						 int j=0;
						 for(j=0;j<sl2female.size();j++){
					         Map m2female=(Map)sl2female.get(j);
					         if(((String)m2female.get("classNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2female.size()||j>sl2female.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3male!=null&&sl3male.size()>0){
						 int j=0;
						 for(j=0;j<sl3male.size();j++){
					         Map m3male=(Map)sl3male.get(j);
					         if(((String)m3male.get("classNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3male.size()||j>sl3male.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3female!=null&&sl3female.size()>0){
						 int j=0;
						 for(j=0;j<sl3female.size();j++){
					         Map m3female=(Map)sl3female.get(j);
					         if(((String)m3female.get("classNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3female.size()||j>sl3female.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("classNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("classNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("classNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
					 
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("classNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));
				    */
					 
					 //班级报到提交状态
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//表中无该班的提交记录,则说明该班报到信息未提交
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//表为空,所有班级均未提交报到信息	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                 //书院总人数
				 for(int i=0;i<sl1schooltotal.size();i++){
					 
					 Map m=(Map)sl1schooltotal.get(i);
					 String cno=(String)m.get("collegeNo");
					 
					 if(sl1schooltotalmale!=null&&sl1schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl1schooltotalmale.size();j++){
					         Map m1male=(Map)sl1schooltotalmale.get(j);
					         if(((String)m1male.get("collegeNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1schooltotalmale.size()||j>sl1schooltotalmale.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1schooltotalfemale!=null&&sl1schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl1schooltotalfemale.size();j++){
					         Map m1female=(Map)sl1schooltotalfemale.get(j);
					         if(((String)m1female.get("collegeNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1schooltotalfemale.size()||j>sl1schooltotalfemale.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2schooltotal!=null&&sl2schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotal.size();j++){
					         Map m2=(Map)sl2schooltotal.get(j);
					         if(((String)m2.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotal.size()||j>sl2schooltotal.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2schooltotalmale!=null&&sl2schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotalmale.size();j++){
					         Map m2male=(Map)sl2schooltotalmale.get(j);
					         if(((String)m2male.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotalmale.size()||j>sl2schooltotalmale.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2schooltotalfemale!=null&&sl2schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotalfemale.size();j++){
					         Map m2female=(Map)sl2schooltotalfemale.get(j);
					         if(((String)m2female.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotalfemale.size()||j>sl2schooltotalfemale.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3schooltotal!=null&&sl3schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotal.size();j++){
					         Map m3=(Map)sl3schooltotal.get(j);
					         if(((String)m3.get("collegeNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotal.size()||j>sl3schooltotal.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3schooltotalmale!=null&&sl3schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotalmale.size();j++){
					         Map m3male=(Map)sl3schooltotalmale.get(j);
					         if(((String)m3male.get("collegeNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotalmale.size()||j>sl3schooltotalmale.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3schooltotalfemale!=null&&sl3schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotalfemale.size();j++){
					         Map m3female=(Map)sl3schooltotalfemale.get(j);
					         if(((String)m3female.get("collegeNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotalfemale.size()||j>sl3schooltotalfemale.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4schooltotal!=null&&sl4schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl4schooltotal.size();j++){
					         Map m4=(Map)sl4schooltotal.get(j);
					         if(((String)m4.get("collegeNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4schooltotal.size()||j>sl4schooltotal.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5schooltotal!=null&&sl5schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl5schooltotal.size();j++){
					         Map m5=(Map)sl5schooltotal.get(j);
					         if(((String)m5.get("collegeNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5schooltotal.size()||j>sl5schooltotal.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6schooltotal!=null&&sl6schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl6schooltotal.size();j++){
					         Map m6=(Map)sl6schooltotal.get(j);
					         if(((String)m6.get("collegeNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6schooltotal.size()||j>sl6schooltotal.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					 
					 if(sl7schooltotal!=null&&sl7schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl7schooltotal.size();j++){
					         Map m7=(Map)sl7schooltotal.get(j);
					         if(((String)m7.get("collegeNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7schooltotal.size()||j>sl7schooltotal.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
						
					 /*
					 if(sl7schooltotal!=null&&sl7schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl7schooltotal.size();j++){
					         Map m7=(Map)sl7schooltotal.get(j);
					         if(((String)m7.get("collegeNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7schooltotal.size()||j>sl7schooltotal.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8schooltotal!=null&&sl8schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl8schooltotal.size();j++){
					         Map m8=(Map)sl8schooltotal.get(j);
					         if(((String)m8.get("collegeNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8schooltotal.size()||j>sl8schooltotal.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));	
				     */
					 
					 if(collegeList!=null&&collegeList.size()>0){//加入书院名称
						 for(int j=0;j<collegeList.size();j++){
							 Map n=(Map)collegeList.get(j);
							 String cno2=((String)n.get("collegeNo")).trim();
							 if(cno.equals(cno2)){
								 m.put("collegeName",n.get("collegeName"));							     
							 }
						 }
					 }					
					 			 
					 stucheckinschoolList.add(m);
			 
			     }
				 
                //复旦学院总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl1totalmale!=null&&sl1totalmale.size()>k&&sl1totalmale.get(k)!=null){
					     Map t1male=(Map)sl1totalmale.get(k);
					     t.put("shouldcheckinmaleNumtotal",t1male.get("shouldcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl1totalfemale!=null&&sl1totalfemale.size()>k&&sl1totalfemale.get(k)!=null){
					     Map t1female=(Map)sl1totalfemale.get(k);
					     t.put("shouldcheckinfemaleNumtotal",t1female.get("shouldcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",new Integer(0));
					 
					 if(sl2totalmale!=null&&sl2totalmale.size()>k&&sl2totalmale.get(k)!=null){
					     Map t2male=(Map)sl2totalmale.get(k);
					     t.put("exactcheckinmaleNumtotal",t2male.get("exactcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl2totalfemale!=null&&sl2totalfemale.size()>k&&sl2totalfemale.get(k)!=null){
					     Map t2female=(Map)sl2totalfemale.get(k);
					     t.put("exactcheckinfemaleNumtotal",t2female.get("exactcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",new Integer(0));
					 
					 if(sl3totalmale!=null&&sl3totalmale.size()>k&&sl3totalmale.get(k)!=null){
					     Map t3male=(Map)sl3totalmale.get(k);
					     t.put("notcheckinmaleNumtotal",t3male.get("notcheckinmaleNumtotal"));
					 }
					 else
						 t.put("notcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl3totalfemale!=null&&sl3totalfemale.size()>k&&sl3totalfemale.get(k)!=null){
					     Map t3female=(Map)sl3totalfemale.get(k);
					     t.put("notcheckinfemaleNumtotal",t3female.get("notcheckinfemaleNumtotal"));
					 }
					 else
						 t.put("notcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",new Integer(0));
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",new Integer(0));
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",new Integer(0)); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",new Integer(0)); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",new Integer(0)); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",new Integer(0));
					*/
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 List resultList=new ArrayList();
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){			
				
				     for(int k=0;k<stucheckininfoList.size();k++){
				    	 Map m=(Map)stucheckininfoList.get(k);
				    	 String cno=(String)m.get("classNo");
				    	 if(colandclsList!=null&&colandclsList.length>0){
				    		 int l=0;
				    		 for(l=0;l<colandclsList.length;l++){				    			 
				    			 if(cno.equals(colandclsList[l][0])){
				    				 m.put("collegeNo",colandclsList[l][3]);
				    				 m.put("collegeName",colandclsList[l][2]);
				    				 m.put("collegeId",colandclsList[l][1]);
				    				 //System.out.println(colandclsList[l][2]+colandclsList[l][1]);
				    				 break;
				    			 }
				    		 }
				    		 if(l==colandclsList.length||l>colandclsList.length){
				    			 m.put("collegeNo","nocollege");
				    			 m.put("collegeName","nocollege");
				    			 m.put("collegeId","nocollege");
				    		 }
				    	 }
				    	 else{
				    		 m.put("collegeNo","nocollege");
				    		 m.put("collegeName","nocollege"); 
				    		 m.put("collegeId","nocollege");
				    	 }
				    	 resultList.add(m);
					 
				     }
				 
			 }		 
			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){//根据书院编号对resultList排序
				 
				 Comparator comp = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
						 String collegeName1 = (String)m1.get("collegeNo"); 
						 String collegeName2 = (String)m2.get("collegeNo"); 
						 return collegeName1.compareTo(collegeName2); 
						 } 
						 } ;
				 Collections.sort(resultList, comp);
				 List rList=new ArrayList();
				 int l=0;
				 int t=0;
				 for(int k=0;k<stucheckinschoolList.size();k++){//按顺序加入书院总人数
					 Map m=(Map)stucheckinschoolList.get(k);
					 String cname=(String)m.get("collegeNo");
					 for(l=t;l<resultList.size();l++){
						 Map n=(Map)resultList.get(l);
						 String cname2=(String)n.get("collegeNo");
						 if(cname.equals(cname2)){
							 rList.add(n);
							 t++;
						 }
						 else{
							 rList.add(m);
							 rList.add(n);
							 t++;
							 break;
						 }						 
							 
					 }
					 
					 
				 }	
				 rList.add((Map)stucheckinschoolList.get(stucheckinschoolList.size()-1));
					 
				 request.setAttribute("classNo",classNo);
				 request.setAttribute("collegeId",collegeId);
				 request.setAttribute("tjlist",rList);				 
				 request.setAttribute("tjlisttotal",stucheckintotalList);
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					 
		                // Create the Excel File
					    String	fileName="tongjiclass.xls";
							
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
						columnNames.add(0,"书院");
						columnNames.add(1,"班级");
						columnNames.add(2,"应到总人数");
						columnNames.add(3,"应到男生数");
						columnNames.add(4,"应到女生数");
						columnNames.add(5,"实到总人数");
						columnNames.add(6,"实到男生数");
						columnNames.add(7,"实到女生数");
						columnNames.add(8,"未到总人数");
						columnNames.add(9,"未到男生数");
						columnNames.add(10,"未到女生数");
						columnNames.add(11,"请假人数");
						columnNames.add(12,"申请保留入学资格人数");
						columnNames.add(13,"不明原因未报到人数");
						columnNames.add(14,"明确不来人数");
						//columnNames.add(9,"放弃入学资格人数");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNum")).toString()));								
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;

						}
						//总计
						if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
						     Map tableData = (Map)stucheckintotalList.get(0);
	                         //create row in spreadsheet
							 row = sheet1.createRow((short)rowCount+1);						
							 
							    HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("复旦学院");
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("总计");
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;
							 
						}
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 return null;				 
				 
				 }
				 else					 
				     return mapping.findForward("tongjilistallview");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilistallview"); 
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
//	按中外统计结果一览
	public ActionForward tongjilistallviewabroad(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckinschoolList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");			 
			 
			 List collegeList=getCollegeList();
			 if(collegeList!=null&&collegeList.size()>0)
				 request.setAttribute("collegelist",collegeList);
		
			 String[][] colandclsList=getColandCls();
			 if(colandclsList!=null&&colandclsList.length>0){
				 request.setAttribute("classlist",colandclsList);				 
			 }
			 
			 
			 
			 
			String classNo=request.getParameter("hclassNo");
			String collegeId=request.getParameter("hcollegeId");
			 
           //班级报到信息提交表查询
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 
			 List sl1schooltotal=new ArrayList();
			 List sl1total=new ArrayList();			 
			 
			 sl1schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
			 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //应到中国学生数
				 List sl1male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' group by c.classNo");
				 
				 List sl1schooltotalmale=new ArrayList();
				 List sl1totalmale=new ArrayList();			 
				 
				 sl1schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' group by col.collegeNo");
				 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'");
					
				 //应到留学生数
                 List sl1female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by c.classNo");
				 
				 List sl1schooltotalfemale=new ArrayList();
				 List sl1totalfemale=new ArrayList();			 
				 
				 sl1schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as shouldcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by col.collegeNo");
				 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN'");
								 
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by c.classNo");
				 List sl2schooltotal=new ArrayList();
				 List sl2total=new ArrayList();				 
				 sl2schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //实到中国学生数
				 List sl2male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality='CHN' group by c.classNo");
				 List sl2schooltotalmale=new ArrayList();
				 List sl2totalmale=new ArrayList();				 
				 sl2schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' group by col.collegeNo");
				 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality='CHN'");
				 
                 //实到留学生数
				 List sl2female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality<>'CHN' group by c.classNo");
				 List sl2schooltotalfemale=new ArrayList();
				 List sl2totalfemale=new ArrayList();				 
				 sl2schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as exactcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by col.collegeNo");
				 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality<>'CHN'");
				 				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3schooltotal=new ArrayList();
				 List sl3total=new ArrayList();				 
				 sl3schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //未到中国学生数
				 List sl3male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.nationality='CHN' group by c.classNo");
				 List sl3schooltotalmale=new ArrayList();
				 List sl3totalmale=new ArrayList();				 
				 sl3schooltotalmale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinmaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' group by col.collegeNo");
				 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.nationality='CHN'");
                 
				 //未到留学生数
				 List sl3female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.nationality<>'CHN' group by c.classNo");
				 List sl3schooltotalfemale=new ArrayList();
				 List sl3totalfemale=new ArrayList();				 
				 sl3schooltotalfemale=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcheckinfemaleNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by col.collegeNo");
				 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.nationality<>'CHN'");
                 				 
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by c.classNo");
				 List sl4schooltotal=new ArrayList();
				 List sl4total=new ArrayList();				 
				 sl4schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as askforlateNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by c.classNo");
				 List sl5schooltotal=new ArrayList();
				 List sl5total=new ArrayList();				 
				 sl5schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as askreserveNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by c.classNo");
				 List sl6schooltotal=new ArrayList();
				 List sl6total=new ArrayList();				 
				 sl6schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as noreasonNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by c.classNo");
				 List sl7schooltotal=new ArrayList();
				 List sl7total=new ArrayList();				 
				 sl7schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as notcomeNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by col.collegeNo");
				 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
				
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' group by c.classNo");
				 List sl7schooltotal=new ArrayList();
				 List sl7total=new ArrayList();				 
				 sl7schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as reserveNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId group by col.collegeNo");
				 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' group by c.classNo");
				 List sl8schooltotal=new ArrayList();
				 List sl8total=new ArrayList();				 
				 sl8schooltotal=checkinmanageservice.find("select new Map(col.collegeNo as collegeNo,count(ci.studentNo) as leaveschoolNum,'书院小计' as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId group by col.collegeNo");
				 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl1male!=null&&sl1male.size()>0){
						 int j=0;
						 for(j=0;j<sl1male.size();j++){
					         Map m1male=(Map)sl1male.get(j);
					         if(((String)m1male.get("classNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1male.size()||j>sl1male.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1female!=null&&sl1female.size()>0){
						 int j=0;
						 for(j=0;j<sl1female.size();j++){
					         Map m1female=(Map)sl1female.get(j);
					         if(((String)m1female.get("classNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1female.size()||j>sl1female.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2male!=null&&sl2male.size()>0){
						 int j=0;
						 for(j=0;j<sl2male.size();j++){
					         Map m2male=(Map)sl2male.get(j);
					         if(((String)m2male.get("classNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2male.size()||j>sl2male.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2female!=null&&sl2female.size()>0){
						 int j=0;
						 for(j=0;j<sl2female.size();j++){
					         Map m2female=(Map)sl2female.get(j);
					         if(((String)m2female.get("classNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2female.size()||j>sl2female.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3male!=null&&sl3male.size()>0){
						 int j=0;
						 for(j=0;j<sl3male.size();j++){
					         Map m3male=(Map)sl3male.get(j);
					         if(((String)m3male.get("classNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3male.size()||j>sl3male.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3female!=null&&sl3female.size()>0){
						 int j=0;
						 for(j=0;j<sl3female.size();j++){
					         Map m3female=(Map)sl3female.get(j);
					         if(((String)m3female.get("classNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3female.size()||j>sl3female.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("classNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("classNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("classNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
					 
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("classNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));
				    */
					 
					 //班级报到提交状态
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//表中无该班的提交记录,则说明该班报到信息未提交
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//表为空,所有班级均未提交报到信息	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                 //书院总人数
				 for(int i=0;i<sl1schooltotal.size();i++){
					 
					 Map m=(Map)sl1schooltotal.get(i);
					 String cno=(String)m.get("collegeNo");
					 
					 if(sl1schooltotalmale!=null&&sl1schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl1schooltotalmale.size();j++){
					         Map m1male=(Map)sl1schooltotalmale.get(j);
					         if(((String)m1male.get("collegeNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1schooltotalmale.size()||j>sl1schooltotalmale.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1schooltotalfemale!=null&&sl1schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl1schooltotalfemale.size();j++){
					         Map m1female=(Map)sl1schooltotalfemale.get(j);
					         if(((String)m1female.get("collegeNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1schooltotalfemale.size()||j>sl1schooltotalfemale.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2schooltotal!=null&&sl2schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotal.size();j++){
					         Map m2=(Map)sl2schooltotal.get(j);
					         if(((String)m2.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotal.size()||j>sl2schooltotal.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2schooltotalmale!=null&&sl2schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotalmale.size();j++){
					         Map m2male=(Map)sl2schooltotalmale.get(j);
					         if(((String)m2male.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotalmale.size()||j>sl2schooltotalmale.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2schooltotalfemale!=null&&sl2schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl2schooltotalfemale.size();j++){
					         Map m2female=(Map)sl2schooltotalfemale.get(j);
					         if(((String)m2female.get("collegeNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2schooltotalfemale.size()||j>sl2schooltotalfemale.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3schooltotal!=null&&sl3schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotal.size();j++){
					         Map m3=(Map)sl3schooltotal.get(j);
					         if(((String)m3.get("collegeNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotal.size()||j>sl3schooltotal.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3schooltotalmale!=null&&sl3schooltotalmale.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotalmale.size();j++){
					         Map m3male=(Map)sl3schooltotalmale.get(j);
					         if(((String)m3male.get("collegeNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotalmale.size()||j>sl3schooltotalmale.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3schooltotalfemale!=null&&sl3schooltotalfemale.size()>0){
						 int j=0;
						 for(j=0;j<sl3schooltotalfemale.size();j++){
					         Map m3female=(Map)sl3schooltotalfemale.get(j);
					         if(((String)m3female.get("collegeNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3schooltotalfemale.size()||j>sl3schooltotalfemale.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4schooltotal!=null&&sl4schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl4schooltotal.size();j++){
					         Map m4=(Map)sl4schooltotal.get(j);
					         if(((String)m4.get("collegeNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4schooltotal.size()||j>sl4schooltotal.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5schooltotal!=null&&sl5schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl5schooltotal.size();j++){
					         Map m5=(Map)sl5schooltotal.get(j);
					         if(((String)m5.get("collegeNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5schooltotal.size()||j>sl5schooltotal.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6schooltotal!=null&&sl6schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl6schooltotal.size();j++){
					         Map m6=(Map)sl6schooltotal.get(j);
					         if(((String)m6.get("collegeNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6schooltotal.size()||j>sl6schooltotal.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					 
					 if(sl7schooltotal!=null&&sl7schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl7schooltotal.size();j++){
					         Map m7=(Map)sl7schooltotal.get(j);
					         if(((String)m7.get("collegeNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7schooltotal.size()||j>sl7schooltotal.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
						
					 /*
					 if(sl7schooltotal!=null&&sl7schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl7schooltotal.size();j++){
					         Map m7=(Map)sl7schooltotal.get(j);
					         if(((String)m7.get("collegeNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7schooltotal.size()||j>sl7schooltotal.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8schooltotal!=null&&sl8schooltotal.size()>0){
						 int j=0;
						 for(j=0;j<sl8schooltotal.size();j++){
					         Map m8=(Map)sl8schooltotal.get(j);
					         if(((String)m8.get("collegeNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8schooltotal.size()||j>sl8schooltotal.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));	
				     */
					 
					 if(collegeList!=null&&collegeList.size()>0){//加入书院名称
						 for(int j=0;j<collegeList.size();j++){
							 Map n=(Map)collegeList.get(j);
							 String cno2=((String)n.get("collegeNo")).trim();
							 if(cno.equals(cno2)){
								 m.put("collegeName",n.get("collegeName"));							     
							 }
						 }
					 }					
					 			 
					 stucheckinschoolList.add(m);
			 
			     }
				 
                //复旦学院总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl1totalmale!=null&&sl1totalmale.size()>k&&sl1totalmale.get(k)!=null){
					     Map t1male=(Map)sl1totalmale.get(k);
					     t.put("shouldcheckinmaleNumtotal",t1male.get("shouldcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl1totalfemale!=null&&sl1totalfemale.size()>k&&sl1totalfemale.get(k)!=null){
					     Map t1female=(Map)sl1totalfemale.get(k);
					     t.put("shouldcheckinfemaleNumtotal",t1female.get("shouldcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",new Integer(0));
					 
					 if(sl2totalmale!=null&&sl2totalmale.size()>k&&sl2totalmale.get(k)!=null){
					     Map t2male=(Map)sl2totalmale.get(k);
					     t.put("exactcheckinmaleNumtotal",t2male.get("exactcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl2totalfemale!=null&&sl2totalfemale.size()>k&&sl2totalfemale.get(k)!=null){
					     Map t2female=(Map)sl2totalfemale.get(k);
					     t.put("exactcheckinfemaleNumtotal",t2female.get("exactcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",new Integer(0));
					 
					 if(sl3totalmale!=null&&sl3totalmale.size()>k&&sl3totalmale.get(k)!=null){
					     Map t3male=(Map)sl3totalmale.get(k);
					     t.put("notcheckinmaleNumtotal",t3male.get("notcheckinmaleNumtotal"));
					 }
					 else
						 t.put("notcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl3totalfemale!=null&&sl3totalfemale.size()>k&&sl3totalfemale.get(k)!=null){
					     Map t3female=(Map)sl3totalfemale.get(k);
					     t.put("notcheckinfemaleNumtotal",t3female.get("notcheckinfemaleNumtotal"));
					 }
					 else
						 t.put("notcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",new Integer(0));
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",new Integer(0));
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",new Integer(0)); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",new Integer(0)); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",new Integer(0)); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",new Integer(0));
					*/
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 List resultList=new ArrayList();
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){			
				
				     for(int k=0;k<stucheckininfoList.size();k++){
				    	 Map m=(Map)stucheckininfoList.get(k);
				    	 String cno=(String)m.get("classNo");
				    	 if(colandclsList!=null&&colandclsList.length>0){
				    		 int l=0;
				    		 for(l=0;l<colandclsList.length;l++){				    			 
				    			 if(cno.equals(colandclsList[l][0])){
				    				 m.put("collegeNo",colandclsList[l][3]);
				    				 m.put("collegeName",colandclsList[l][2]);
				    				 m.put("collegeId",colandclsList[l][1]);
				    				 //System.out.println(colandclsList[l][2]+colandclsList[l][1]);
				    				 break;
				    			 }
				    		 }
				    		 if(l==colandclsList.length||l>colandclsList.length){
				    			 m.put("collegeNo","nocollege");
				    			 m.put("collegeName","nocollege");
				    			 m.put("collegeId","nocollege");
				    		 }
				    	 }
				    	 else{
				    		 m.put("collegeNo","nocollege");
				    		 m.put("collegeName","nocollege"); 
				    		 m.put("collegeId","nocollege");
				    	 }
				    	 resultList.add(m);
					 
				     }
				 
			 }		 
			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){//根据书院编号对resultList排序
				 
				 Comparator comp = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
						 String collegeName1 = (String)m1.get("collegeNo"); 
						 String collegeName2 = (String)m2.get("collegeNo"); 
						 return collegeName1.compareTo(collegeName2); 
						 } 
						 } ;
				 Collections.sort(resultList, comp);
				 List rList=new ArrayList();
				 int l=0;
				 int t=0;
				 for(int k=0;k<stucheckinschoolList.size();k++){//按顺序加入书院总人数
					 Map m=(Map)stucheckinschoolList.get(k);
					 String cname=(String)m.get("collegeNo");
					 for(l=t;l<resultList.size();l++){
						 Map n=(Map)resultList.get(l);
						 String cname2=(String)n.get("collegeNo");
						 if(cname.equals(cname2)){
							 rList.add(n);
							 t++;
						 }
						 else{
							 rList.add(m);
							 rList.add(n);
							 t++;
							 break;
						 }						 
							 
					 }
					 
					 
				 }	
				 rList.add((Map)stucheckinschoolList.get(stucheckinschoolList.size()-1));
					 
				 request.setAttribute("classNo",classNo);
				 request.setAttribute("collegeId",collegeId);
				 request.setAttribute("tjlist",rList);				 
				 request.setAttribute("tjlisttotal",stucheckintotalList);
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					 
		                // Create the Excel File
					    String	fileName="tongjiclass.xls";
							
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
						columnNames.add(0,"书院");
						columnNames.add(1,"班级");
						columnNames.add(2,"应到总人数");
						columnNames.add(3,"应到中国学生数");
						columnNames.add(4,"应到留学生数");
						columnNames.add(5,"实到总人数");
						columnNames.add(6,"实到中国学生数");
						columnNames.add(7,"实到留学生数");
						columnNames.add(8,"未到总人数");
						columnNames.add(9,"未到中国学生数");
						columnNames.add(10,"未到留学生数");
						columnNames.add(11,"请假人数");
						columnNames.add(12,"申请保留入学资格人数");
						columnNames.add(13,"不明原因未报到人数");
						columnNames.add(14,"明确不来人数");
						//columnNames.add(9,"放弃入学资格人数");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNum")).toString()));								
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;

						}
						//总计
						if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
						     Map tableData = (Map)stucheckintotalList.get(0);
	                         //create row in spreadsheet
							 row = sheet1.createRow((short)rowCount+1);						
							 
							    HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("复旦学院");
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("总计");
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;
							 
						}
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 return null;				 
				 
				 }
				 else					 
				     return mapping.findForward("tongjilistallviewabroad");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilistallviewabroad"); 
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
	//统计结果查询
	public ActionForward tongjilistview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 if(request.getParameter("hclassNo")==null&&request.getParameter("hcollegeId")==null||request.getParameter("hclassNo").length()==0&&request.getParameter("hcollegeId").length()==0)
			     return tongjilistallview(mapping,form,request,response);
				 
			 List collegeList=getCollegeList();
			 if(collegeList!=null&&collegeList.size()>0)
				 request.setAttribute("collegelist",collegeList);
			 
			 String[][] colandclsList=getColandCls();
			 if(colandclsList!=null&&colandclsList.length>0){
				 request.setAttribute("classlist",colandclsList);
				 //request.setAttribute("listlength",new Integer(colandclsList.length));
			 }
			 
			String classNo=request.getParameter("hclassNo");
			String collegeId=request.getParameter("hcollegeId");
			 
           //班级报到信息提交表查询
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 List sl1total=new ArrayList();
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
			 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
			 else
			     sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 
                 //应到男生数
				 List sl1male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' group by c.classNo");
				 List sl1totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1'");
				
                 //应到女生数
				 List sl1female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' group by c.classNo");
				 List sl1totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2'");
				
				 
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by c.classNo");
				 List sl2total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //实到男生数
				 List sl2male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='1' group by c.classNo");
				 List sl2totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and ci.ifCheckedin='1'");
				 
				 //实到女生数
				 List sl2female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.gender='2' group by c.classNo");
				 List sl2totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and ci.ifCheckedin='1'");
				 
				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //未到男生数
				 List sl3male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and s.gender='1' and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='1' and ci.ifCheckedin='0'");
                
				 //未到女生数
				 List sl3female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and s.gender='2' and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.gender='2' and ci.ifCheckedin='0'");
                
				 
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by c.classNo");
				 List sl4total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by c.classNo");
				 List sl5total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by c.classNo");
				 List sl6total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
				 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by c.classNo");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
								 
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' group by c.classNo");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' group by c.classNo");
				 List sl8total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl1male!=null&&sl1male.size()>0){
						 int j=0;
						 for(j=0;j<sl1male.size();j++){
					         Map m1male=(Map)sl1male.get(j);
					         if(((String)m1male.get("classNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1male.size()||j>sl1male.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1female!=null&&sl1female.size()>0){
						 int j=0;
						 for(j=0;j<sl1female.size();j++){
					         Map m1female=(Map)sl1female.get(j);
					         if(((String)m1female.get("classNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1female.size()||j>sl1female.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2male!=null&&sl2male.size()>0){
						 int j=0;
						 for(j=0;j<sl2male.size();j++){
					         Map m2male=(Map)sl2male.get(j);
					         if(((String)m2male.get("classNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2male.size()||j>sl2male.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2female!=null&&sl2female.size()>0){
						 int j=0;
						 for(j=0;j<sl2female.size();j++){
					         Map m2female=(Map)sl2female.get(j);
					         if(((String)m2female.get("classNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2female.size()||j>sl2female.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3male!=null&&sl3male.size()>0){
						 int j=0;
						 for(j=0;j<sl3male.size();j++){
					         Map m3male=(Map)sl3male.get(j);
					         if(((String)m3male.get("classNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3male.size()||j>sl3male.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3female!=null&&sl3female.size()>0){
						 int j=0;
						 for(j=0;j<sl3female.size();j++){
					         Map m3female=(Map)sl3female.get(j);
					         if(((String)m3female.get("classNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3female.size()||j>sl3female.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("classNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("classNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("classNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					 
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
					
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("classNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));
					*/
					 
					 //班级报到提交状态
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//表中无该班的提交记录,则说明该班报到信息未提交
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//表为空,所有班级均未提交报到信息	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl1totalmale!=null&&sl1totalmale.size()>k&&sl1totalmale.get(k)!=null){
					     Map t1male=(Map)sl1totalmale.get(k);
					     t.put("shouldcheckinmaleNumtotal",t1male.get("shouldcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl1totalfemale!=null&&sl1totalfemale.size()>k&&sl1totalfemale.get(k)!=null){
					     Map t1female=(Map)sl1totalfemale.get(k);
					     t.put("shouldcheckinfemaleNumtotal",t1female.get("shouldcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",new Integer(0));
					 
					 if(sl2totalmale!=null&&sl2totalmale.size()>k&&sl2totalmale.get(k)!=null){
					     Map t2male=(Map)sl2totalmale.get(k);
					     t.put("exactcheckinmaleNumtotal",t2male.get("exactcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl2totalfemale!=null&&sl2totalfemale.size()>k&&sl2totalfemale.get(k)!=null){
					     Map t2female=(Map)sl2totalfemale.get(k);
					     t.put("exactcheckinfemaleNumtotal",t2female.get("exactcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",new Integer(0));
					 
					 if(sl3totalmale!=null&&sl3totalmale.size()>k&&sl3totalmale.get(k)!=null){
					     Map t3male=(Map)sl3totalmale.get(k);
					     t.put("notcheckinmaleNumtotal",t3male.get("notcheckinmaleNumtotal"));
					 }
					 else
						 t.put("notcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl3totalfemale!=null&&sl3totalfemale.size()>k&&sl3totalfemale.get(k)!=null){
					     Map t3female=(Map)sl3totalfemale.get(k);
					     t.put("notcheckinfemaleNumtotal",t3female.get("notcheckinfemaleNumtotal"));
					 }
					 else
						 t.put("notcheckinfemaleNumtotal",new Integer(0));
					 					 					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",new Integer(0));
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",new Integer(0));
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",new Integer(0)); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",new Integer(0)); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",new Integer(0)); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",new Integer(0));
					*/
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 List resultList=new ArrayList();
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){			
				
				     for(int k=0;k<stucheckininfoList.size();k++){
				    	 Map m=(Map)stucheckininfoList.get(k);
				    	 String cno=(String)m.get("classNo");
				    	 if(colandclsList!=null&&colandclsList.length>0){
				    		 int l=0;
				    		 for(l=0;l<colandclsList.length;l++){				    			 
				    			 if(cno.equals(colandclsList[l][0])){
				    				 m.put("collegeName",colandclsList[l][2]);
				    				 m.put("collegeId",colandclsList[l][1]);
				    				 //System.out.println(colandclsList[l][2]+colandclsList[l][1]);
				    				 break;
				    			 }
				    		 }
				    		 if(l==colandclsList.length||l>colandclsList.length){
				    			 m.put("collegeName","nocollege");
				    			 m.put("collegeId","nocollege");
				    		 }
				    	 }
				    	 else{
				    		 m.put("collegeName","nocollege"); 
				    		 m.put("collegeId","nocollege");
				    	 }
				    	 resultList.add(m);
					 
				     }
				 
			 }		 
			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){
				 
				 Comparator comp = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
						 String collegeName1 = (String)m1.get("collegeName"); 
						 String collegeName2 = (String)m2.get("collegeName"); 
						 return collegeName1.compareTo(collegeName2); 
						 } 
						 } ;
				 Collections.sort(resultList, comp);
				 List rList=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0){
					 for(int i=0;i<resultList.size();i++){
						 Map r=(Map)resultList.get(i);
						 if(((String)r.get("classNo")).trim().equals(request.getParameter("hclassNo").trim()))
							 rList.add(r);
					 }
					 
				 }
					 
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0){
                     for(int i=0;i<resultList.size();i++){
                    	 Map r=(Map)resultList.get(i);
						 if(((String)r.get("collegeId")).trim().equals(request.getParameter("hcollegeId").trim()))
							 rList.add(r);
						 
					 }
				 }
				 else
					 rList=resultList;
				 request.setAttribute("classNo",classNo);
				 request.setAttribute("collegeId",collegeId);
				 request.setAttribute("tjlist",rList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);	
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					 
		                // Create the Excel File
					    String	fileName="tongjiclass.xls";
							
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
						columnNames.add(0,"书院");
						columnNames.add(1,"班级");
						columnNames.add(2,"应到总人数");
						columnNames.add(3,"应到男生数");
						columnNames.add(4,"应到女生数");
						columnNames.add(5,"实到总人数");
						columnNames.add(6,"实到男生数");
						columnNames.add(7,"实到女生数");
						columnNames.add(8,"未到总人数");
						columnNames.add(9,"未到男生数");
						columnNames.add(10,"未到女生数");
						columnNames.add(11,"请假人数");
						columnNames.add(12,"申请保留入学资格人数");
						columnNames.add(13,"不明原因未报到人数");
						columnNames.add(14,"明确不来人数");
						//columnNames.add(9,"放弃入学资格人数");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNum")).toString()));
																
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNum")).toString()));								
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;

						}
						//总计
						if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
						     Map tableData = (Map)stucheckintotalList.get(0);
	                         //create row in spreadsheet
							 row = sheet1.createRow((short)rowCount+1);						
							 
							    HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("总");
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("计");
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;
							 
						}
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 return null;	
				 }
				 else
				     return mapping.findForward("tongjilistview");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilistview"); 
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
//	统计结果查询
	public ActionForward tongjilistviewabroad(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 if(request.getParameter("hclassNo")==null&&request.getParameter("hcollegeId")==null||request.getParameter("hclassNo").length()==0&&request.getParameter("hcollegeId").length()==0)
			     return tongjilistallviewabroad(mapping,form,request,response);
				 
			 List collegeList=getCollegeList();
			 if(collegeList!=null&&collegeList.size()>0)
				 request.setAttribute("collegelist",collegeList);
			 
			 String[][] colandclsList=getColandCls();
			 if(colandclsList!=null&&colandclsList.length>0){
				 request.setAttribute("classlist",colandclsList);
				 //request.setAttribute("listlength",new Integer(colandclsList.length));
			 }
			 
			String classNo=request.getParameter("hclassNo");
			String collegeId=request.getParameter("hcollegeId");
			 
           //班级报到信息提交表查询
			 String sqlstring="select new Map(cs.id as id,cs.classNo as classNo,cs.ifSubmitted as ifSubmitted) from CheckinSubmin cs";
			 
			 List checkinsubminList=checkinmanageservice.find(sqlstring);	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' group by c.classNo");
			 List sl1total=new ArrayList();
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
			 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
			 else
			     sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 
                 //应到中国学生数
				 List sl1male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' group by c.classNo");
				 List sl1totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl1totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'");
				
                 //应到留学生数
				 List sl1female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as shouldcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by c.classNo");
				 List sl1totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl1totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN'");
				
				 
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by c.classNo");
				 List sl2total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //实到中国学生数
				 List sl2male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality='CHN' group by c.classNo");
				 List sl2totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl2totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and ci.ifCheckedin='1'");
				 
				 //实到留学生数
				 List sl2female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as exactcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' and s.nationality<>'CHN' group by c.classNo");
				 List sl2totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl2totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='1'");
				 
				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //未到中国学生数
				 List sl3male=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinmaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3totalmale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and s.nationality='CHN' and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl3totalmale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinmaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN' and ci.ifCheckedin='0'");
                
				 //未到留学生数
				 List sl3female=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcheckinfemaleNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' group by c.classNo");
				 List sl3totalfemale=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and s.nationality<>'CHN' and c.curYear='"+DateUtil.getNow("yyyy")+"' and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
					 sl3totalfemale=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinfemaleNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0'");
                
				 
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by c.classNo");
				 List sl4total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='01' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by c.classNo");
				 List sl5total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='02' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by c.classNo");
				 List sl6total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='03' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
				 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by c.classNo");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifCheckedin='0' and ci.reason='00' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
								 
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' group by c.classNo");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(c.classNo as classNo,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' group by c.classNo");
				 List sl8total=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+request.getParameter("hclassNo")+"'");
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c,Collegemodel col where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and col.collegeId='"+request.getParameter("hcollegeId")+"'");
				 else
				     sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("classNo");
					 
					 if(sl1male!=null&&sl1male.size()>0){
						 int j=0;
						 for(j=0;j<sl1male.size();j++){
					         Map m1male=(Map)sl1male.get(j);
					         if(((String)m1male.get("classNo")).equals(cno)){
					             m.put("shouldcheckinmaleNum",m1male.get("shouldcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1male.size()||j>sl1male.size()){
							 m.put("shouldcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinmaleNum",new Integer(0));
					 
					 if(sl1female!=null&&sl1female.size()>0){
						 int j=0;
						 for(j=0;j<sl1female.size();j++){
					         Map m1female=(Map)sl1female.get(j);
					         if(((String)m1female.get("classNo")).equals(cno)){
					             m.put("shouldcheckinfemaleNum",m1female.get("shouldcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl1female.size()||j>sl1female.size()){
							 m.put("shouldcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("shouldcheckinfemaleNum",new Integer(0));
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("classNo")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 
					 if(sl2male!=null&&sl2male.size()>0){
						 int j=0;
						 for(j=0;j<sl2male.size();j++){
					         Map m2male=(Map)sl2male.get(j);
					         if(((String)m2male.get("classNo")).equals(cno)){
					             m.put("exactcheckinmaleNum",m2male.get("exactcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2male.size()||j>sl2male.size()){
							 m.put("exactcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinmaleNum",new Integer(0));
					 
					 if(sl2female!=null&&sl2female.size()>0){
						 int j=0;
						 for(j=0;j<sl2female.size();j++){
					         Map m2female=(Map)sl2female.get(j);
					         if(((String)m2female.get("classNo")).equals(cno)){
					             m.put("exactcheckinfemaleNum",m2female.get("exactcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2female.size()||j>sl2female.size()){
							 m.put("exactcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinfemaleNum",new Integer(0));
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("classNo")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl3male!=null&&sl3male.size()>0){
						 int j=0;
						 for(j=0;j<sl3male.size();j++){
					         Map m3male=(Map)sl3male.get(j);
					         if(((String)m3male.get("classNo")).equals(cno)){
					             m.put("notcheckinmaleNum",m3male.get("notcheckinmaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3male.size()||j>sl3male.size()){
							 m.put("notcheckinmaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinmaleNum",new Integer(0));
					 
					 if(sl3female!=null&&sl3female.size()>0){
						 int j=0;
						 for(j=0;j<sl3female.size();j++){
					         Map m3female=(Map)sl3female.get(j);
					         if(((String)m3female.get("classNo")).equals(cno)){
					             m.put("notcheckinfemaleNum",m3female.get("notcheckinfemaleNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3female.size()||j>sl3female.size()){
							 m.put("notcheckinfemaleNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinfemaleNum",new Integer(0));
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("classNo")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("classNo")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("classNo")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					 
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
					
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("classNo")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("reserveNum",new Integer(0)); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("classNo")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",new Integer(0));
						 }
					 }
					 else
						 m.put("leaveschoolNum",new Integer(0));
					*/
					 
					 //班级报到提交状态
					 if(checkinsubminList!=null&&checkinsubminList.size()>0){
						 int j=0;
						 for(j=0;j<checkinsubminList.size();j++){
							 Map mcs=(Map)checkinsubminList.get(j);
							 if(((String)mcs.get("classNo")).equals(cno)){
								 m.put("ifSubmitted",(String)mcs.get("ifSubmitted"));
								 m.put("csid",(String)mcs.get("id"));
								 break;
							 }
						 }
						 if(j==checkinsubminList.size()||j>checkinsubminList.size()){
							 m.put("ifSubmitted",null);//表中无该班的提交记录,则说明该班报到信息未提交
							 m.put("csid",null);
						 }
					 }
					 else{
						 m.put("ifSubmitted",null);//表为空,所有班级均未提交报到信息	
						 m.put("csid",null);
					 }
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl1totalmale!=null&&sl1totalmale.size()>k&&sl1totalmale.get(k)!=null){
					     Map t1male=(Map)sl1totalmale.get(k);
					     t.put("shouldcheckinmaleNumtotal",t1male.get("shouldcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl1totalfemale!=null&&sl1totalfemale.size()>k&&sl1totalfemale.get(k)!=null){
					     Map t1female=(Map)sl1totalfemale.get(k);
					     t.put("shouldcheckinfemaleNumtotal",t1female.get("shouldcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("shouldcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",new Integer(0));
					 
					 if(sl2totalmale!=null&&sl2totalmale.size()>k&&sl2totalmale.get(k)!=null){
					     Map t2male=(Map)sl2totalmale.get(k);
					     t.put("exactcheckinmaleNumtotal",t2male.get("exactcheckinmaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl2totalfemale!=null&&sl2totalfemale.size()>k&&sl2totalfemale.get(k)!=null){
					     Map t2female=(Map)sl2totalfemale.get(k);
					     t.put("exactcheckinfemaleNumtotal",t2female.get("exactcheckinfemaleNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinfemaleNumtotal",new Integer(0));
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",new Integer(0));
					 
					 if(sl3totalmale!=null&&sl3totalmale.size()>k&&sl3totalmale.get(k)!=null){
					     Map t3male=(Map)sl3totalmale.get(k);
					     t.put("notcheckinmaleNumtotal",t3male.get("notcheckinmaleNumtotal"));
					 }
					 else
						 t.put("notcheckinmaleNumtotal",new Integer(0));
					 
					 if(sl3totalfemale!=null&&sl3totalfemale.size()>k&&sl3totalfemale.get(k)!=null){
					     Map t3female=(Map)sl3totalfemale.get(k);
					     t.put("notcheckinfemaleNumtotal",t3female.get("notcheckinfemaleNumtotal"));
					 }
					 else
						 t.put("notcheckinfemaleNumtotal",new Integer(0));
					 					 					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",new Integer(0));
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",new Integer(0));
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",new Integer(0)); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",new Integer(0)); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",new Integer(0)); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",new Integer(0));
					*/
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 List resultList=new ArrayList();
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){			
				
				     for(int k=0;k<stucheckininfoList.size();k++){
				    	 Map m=(Map)stucheckininfoList.get(k);
				    	 String cno=(String)m.get("classNo");
				    	 if(colandclsList!=null&&colandclsList.length>0){
				    		 int l=0;
				    		 for(l=0;l<colandclsList.length;l++){				    			 
				    			 if(cno.equals(colandclsList[l][0])){
				    				 m.put("collegeName",colandclsList[l][2]);
				    				 m.put("collegeId",colandclsList[l][1]);
				    				 //System.out.println(colandclsList[l][2]+colandclsList[l][1]);
				    				 break;
				    			 }
				    		 }
				    		 if(l==colandclsList.length||l>colandclsList.length){
				    			 m.put("collegeName","nocollege");
				    			 m.put("collegeId","nocollege");
				    		 }
				    	 }
				    	 else{
				    		 m.put("collegeName","nocollege"); 
				    		 m.put("collegeId","nocollege");
				    	 }
				    	 resultList.add(m);
					 
				     }
				 
			 }		 
			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){
				 
				 Comparator comp = new Comparator() { 
						 public int compare(Object o1, Object o2){ 
						 Map m1 = (Map)o1; 
						 Map m2 = (Map)o2; 
						 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
						 String collegeName1 = (String)m1.get("collegeName"); 
						 String collegeName2 = (String)m2.get("collegeName"); 
						 return collegeName1.compareTo(collegeName2); 
						 } 
						 } ;
				 Collections.sort(resultList, comp);
				 List rList=new ArrayList();
				 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0){
					 for(int i=0;i<resultList.size();i++){
						 Map r=(Map)resultList.get(i);
						 if(((String)r.get("classNo")).trim().equals(request.getParameter("hclassNo").trim()))
							 rList.add(r);
					 }
					 
				 }
					 
				 else if(request.getParameter("hcollegeId")!=null&&request.getParameter("hcollegeId").length()!=0){
                     for(int i=0;i<resultList.size();i++){
                    	 Map r=(Map)resultList.get(i);
						 if(((String)r.get("collegeId")).trim().equals(request.getParameter("hcollegeId").trim()))
							 rList.add(r);
						 
					 }
				 }
				 else
					 rList=resultList;
				 request.setAttribute("classNo",classNo);
				 request.setAttribute("collegeId",collegeId);
				 request.setAttribute("tjlist",rList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);	
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					 
		                // Create the Excel File
					    String	fileName="tongjiclass.xls";
							
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
						columnNames.add(0,"书院");
						columnNames.add(1,"班级");
						columnNames.add(2,"应到总人数");
						columnNames.add(3,"应到中国学生数");
						columnNames.add(4,"应到留学生数");
						columnNames.add(5,"实到总人数");
						columnNames.add(6,"实到中国学生数");
						columnNames.add(7,"实到留学生数");
						columnNames.add(8,"未到总人数");
						columnNames.add(9,"未到中国学生数");
						columnNames.add(10,"未到留学生数");
						columnNames.add(11,"请假人数");
						columnNames.add(12,"申请保留入学资格人数");
						columnNames.add(13,"不明原因未报到人数");
						columnNames.add(14,"明确不来人数");
						//columnNames.add(9,"放弃入学资格人数");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("collegeName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("classNo"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNum")).toString()));
																
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNum")).toString()));								
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNum")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNum")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;

						}
						//总计
						if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
						     Map tableData = (Map)stucheckintotalList.get(0);
	                         //create row in spreadsheet
							 row = sheet1.createRow((short)rowCount+1);						
							 
							    HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("总");
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("计");
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinmaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinfemaleNumtotal")).toString()));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
								
								ctitle=row.createCell((short)12);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
								
								ctitle=row.createCell((short)13);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
								
								ctitle=row.createCell((short)14);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
								
								//ctitle=row.createCell((short)9);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;
							 
						}
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 return null;	
				 }
				 else
				     return mapping.findForward("tongjilistviewabroad");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilistviewabroad"); 
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
	//报到统计按专业
	public ActionForward tongjilistmajor(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");	
			 
                //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
			 
			 String majorin=request.getParameter("hmajorin");           	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by s.majorin");
			 List sl1total=new ArrayList();
			 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.majorin='"+request.getParameter("hmajorin")+"'");			 
			 else
			     sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by s.majorin");
				 List sl2total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by s.majorin");
				 List sl3total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by s.majorin");
				 List sl4total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by s.majorin");
				 List sl5total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by s.majorin");
				 List sl6total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
				 
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifReserve='1' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifLeaveSchool='1' group by s.majorin");
				 List sl8total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("majorin");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("majorin")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",null);
						 }
					 }
					 else
						 m.put("exactcheckinNum",null);
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("majorin")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",null);
						 }
					 }
					 else
						 m.put("notcheckinNum",null);
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("majorin")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",null);
						 }
					 }
					 else
						 m.put("askforlateNum",null);
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("majorin")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",null);
						 }
					 }
					 else
						 m.put("askreserveNum",null);
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("majorin")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",null);
						 }
					 }
					 else
						 m.put("noreasonNum",null); 
					 
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",null);
						 }
					 }
					 else
						 m.put("notcomeNum",null); 
					
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",null);
						 }
					 }
					 else
						 m.put("reserveNum",null); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("majorin")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",null);
						 }
					 }
					 else
						 m.put("leaveschoolNum",null);					 
					 */
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",null);
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",null);
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",null);
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",null);
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",null); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",null); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",null); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",null);
					 */
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 
			 Comparator comp = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
				 String collegeName1 = (String)m1.get("majorin"); 
				 String collegeName2 = (String)m2.get("majorin"); 
				 return collegeName1.compareTo(collegeName2); 
				 } 
				 } ;
		     Collections.sort(stucheckininfoList, comp);//按专业代码排序
		     
			 List resultList=stucheckininfoList;			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){				 
				 List rList=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0){
					 for(int i=0;i<resultList.size();i++){
						 Map r=(Map)resultList.get(i);
						 if(((String)r.get("majorin")).trim().equals(request.getParameter("hmajorin").trim()))
							 rList.add(r);
					 }
					 ChangeMajorValue(rList);
					 
				 }
					 
				 else{
					 rList=resultList;
					 ChangeMajorValue(rList);
					 
				 }
				 request.setAttribute("majorin",majorin);				 
				 request.setAttribute("tjlist",rList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);				
				 return mapping.findForward("tongjilistmajor");
			 }
			 else
				 return mapping.findForward("tongjilistmajor"); 

			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
//	报到统计按专业导出excel
	public ActionForward tongjilistmajorexcel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");	
			 
                //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
			 
			 String majorin=request.getParameter("hmajorin");           	 
			 			
             //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' group by s.majorin");
			 List sl1total=new ArrayList();
			 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.majorin='"+request.getParameter("hmajorin")+"'");			 
			 else
			     sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1' group by s.majorin");
				 List sl2total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.ifCheckedin='1' and ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='1'");
				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' group by s.majorin");
				 List sl3total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0'");
                
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' group by s.majorin");
				 List sl4total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' group by s.majorin");
				 List sl5total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' group by s.majorin");
				 List sl6total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03'");
				
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00'");
				 
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifReserve='1' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifLeaveSchool='1' group by s.majorin");
				 List sl8total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("majorin");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("majorin")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("exactcheckinNum",new Integer(0));
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("majorin")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcheckinNum",new Integer(0));
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("majorin")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askforlateNum",new Integer(0));
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("majorin")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",new Integer(0));
						 }
					 }
					 else
						 m.put("askreserveNum",new Integer(0));
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("majorin")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",new Integer(0));
						 }
					 }
					 else
						 m.put("noreasonNum",new Integer(0)); 
					 
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",new Integer(0));
						 }
					 }
					 else
						 m.put("notcomeNum",new Integer(0)); 
					
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",null);
						 }
					 }
					 else
						 m.put("reserveNum",null); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("majorin")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",null);
						 }
					 }
					 else
						 m.put("leaveschoolNum",null);					 
					 */
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",new Integer(0));
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",new Integer(0));
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",new Integer(0));
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",new Integer(0));
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",new Integer(0)); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",new Integer(0)); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",null); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",null);
					 */
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 
			 Comparator comp = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
				 String collegeName1 = (String)m1.get("majorin"); 
				 String collegeName2 = (String)m2.get("majorin"); 
				 return collegeName1.compareTo(collegeName2); 
				 } 
				 } ;
		     Collections.sort(stucheckininfoList, comp);//按专业代码排序
		     
			 List resultList=stucheckininfoList;			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){				 
				 List rList=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0){
					 for(int i=0;i<resultList.size();i++){
						 Map r=(Map)resultList.get(i);
						 if(((String)r.get("majorin")).trim().equals(request.getParameter("hmajorin").trim()))
							 rList.add(r);
					 }
					 ChangeMajorValue(rList);
					 
				 }
					 
				 else{
					 rList=resultList;
					 ChangeMajorValue(rList);
					 
				 }
				 request.setAttribute("majorin",majorin);				 
				 request.setAttribute("tjlist",rList);
				 request.setAttribute("tjlisttotal",stucheckintotalList);	
				 				 
				 /*-----------------------------------------------------------------------*/
				 
	                // Create the Excel File
				    String	fileName="tongjimajor.xls";
						
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
					columnNames.add(0,"专业");
					columnNames.add(1,"应到人数");
					columnNames.add(2,"实到人数");
					columnNames.add(3,"未到人数");
					columnNames.add(4,"请假人数");
					columnNames.add(5,"申请保留入学资格人数");
					columnNames.add(6,"不明原因未报到人数");
					columnNames.add(7,"明确不来人数");
					
					// System.out.println(columnNames.size());
					for (int i=0; i<columnNames.size(); i++)
					{
						 HSSFCell cname=row.createCell((short)i);
						 cname.setCellStyle(cellHeadStyle);
						 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
						 cname.setCellValue((String)columnNames.get(i));
					}
					
					// Populate the Row Data to the SpreadSheet
					int rowCount = rList.size();
					// goal houses the number of cells in the target spreadsheet
					int goal = rowCount*columnNames.size();			
					
					//actual population of target spreadsheet
					int currentCell = 0;
					
					for (int i=0; i<rowCount; i++)
					{
						Map tableData = (Map)rList.get(i);
						// create row in spreadsheet
						row = sheet1.createRow((short)(i+1));
						
							// populate the spreadsheet with the cell						
							HSSFCell ctitle=row.createCell((short)0);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("majorinName"));
							
							ctitle=row.createCell((short)1);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
							
							
							ctitle=row.createCell((short)2);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
							
							
							ctitle=row.createCell((short)3);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
							
							ctitle=row.createCell((short)4);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
							
							ctitle=row.createCell((short)5);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
							
							ctitle=row.createCell((short)6);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
							
							ctitle=row.createCell((short)7);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
						
							//ctitle=row.createCell((short)8);
							//ctitle.setCellStyle(cellDataStyle);
							//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
														
							//System.out.println(columnData);
							currentCell++;

					}
					//总计
					if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
					     Map tableData = (Map)stucheckintotalList.get(0);
                         //create row in spreadsheet
						 row = sheet1.createRow((short)rowCount+1);						
						 
						 HSSFCell ctitle=row.createCell((short)0);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue("总计");
							
							ctitle=row.createCell((short)1);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
							
							ctitle=row.createCell((short)2);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
							
							ctitle=row.createCell((short)3);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
							
							ctitle=row.createCell((short)4);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
							
							ctitle=row.createCell((short)5);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
							
							ctitle=row.createCell((short)6);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
							
							ctitle=row.createCell((short)7);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
							
							//ctitle=row.createCell((short)8);
							//ctitle.setCellStyle(cellDataStyle);
							//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
														
							//System.out.println(columnData);
							currentCell++;
						 
					}
					
					response.setContentType("application/x-msdownload");
					response.setHeader("Content-Disposition", "attachment;"
							+ " filename="
							+ new String(fileName.getBytes(), "ISO-8859-1"));

	                OutputStream os = response.getOutputStream();
	                wb.write(os);
			    /*-----------------------------------------------------------------------*/ 
				 return null;
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilistmajor"); 
			 }
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
//	留学生报到统计按专业
	public ActionForward tongjilistmajorabroad(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stucheckininfoList=new ArrayList();
		List stucheckintotalList=new ArrayList();
		
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");	
			 
                //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList);
			 
			 String majorin=request.getParameter("hmajorin");           	 
			 			
			 //应报到人数
			 List sl1=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as shouldcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' group by s.majorin");
			 List sl1total=new ArrayList();
			 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				 sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and s.majorin='"+request.getParameter("hmajorin")+"'");			 
			 else
			     sl1total=checkinmanageservice.find("select new Map(count(ci.studentNo) as shouldcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN'");
			
			 if(sl1!=null&&sl1.size()>0){
				 //实际报到人数
				 List sl2=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as exactcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='1' group by s.majorin");
				 List sl2total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='1' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl2total=checkinmanageservice.find("select new Map(count(ci.studentNo) as exactcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='1'");
				 
				 //未报到人数
				 List sl3=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcheckinNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' group by s.majorin");
				 List sl3total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl3total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcheckinNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0'");
                
				 //请假人数
				 List sl4=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askforlateNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='01' group by s.majorin");
				 List sl4total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='01' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl4total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askforlateNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='01'");
				
				 //申请保留入学资格人数
				 List sl5=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as askreserveNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='02' group by s.majorin");
				 List sl5total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo) as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='02' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl5total=checkinmanageservice.find("select new Map(count(ci.studentNo)as askreserveNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='02'");
				
				 //未明原因人数
				 List sl6=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as noreasonNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='03' group by s.majorin");
				 List sl6total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo) as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='03' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl6total=checkinmanageservice.find("select new Map(count(ci.studentNo)as noreasonNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='03'");
				
                 //明确不来人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo)as notcomeNum) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='00' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='00' and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo)as notcomeNumtotal) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='00'");
				 
				 /*
				 //保留入学资格人数
				 List sl7=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as reserveNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifReserve='1' group by s.majorin");
				 List sl7total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifReserve='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl7total=checkinmanageservice.find("select new Map(count(ci.studentNo) as reserveNumtotal) from Stucheckininfo ci where ci.ifReserve='1'");
				
				 //放弃入学资格人数
				 List sl8=checkinmanageservice.find("select new Map(s.majorin as majorin,count(ci.studentNo) as leaveschoolNum) from Stucheckininfo ci,Studentmodel s where ci.studentNo=s.studentNo and ci.ifLeaveSchool='1' group by s.majorin");
				 List sl8total=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
					 sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci,Studentmodel s where ci.ifLeaveSchool='1' and ci.studentNo=s.studentNo and s.majorin='"+request.getParameter("hmajorin")+"'");
				 else
				     sl8total=checkinmanageservice.find("select new Map(count(ci.studentNo) as leaveschoolNumtotal) from Stucheckininfo ci where ci.ifLeaveSchool='1'");
				 */
				 
				 for(int i=0;i<sl1.size();i++){
	 
					 Map m=(Map)sl1.get(i);
					 String cno=(String)m.get("majorin");
					 
					 if(sl2!=null&&sl2.size()>0){
						 int j=0;
						 for(j=0;j<sl2.size();j++){
					         Map m2=(Map)sl2.get(j);
					         if(((String)m2.get("majorin")).equals(cno)){
					             m.put("exactcheckinNum",m2.get("exactcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl2.size()||j>sl2.size()){
							 m.put("exactcheckinNum",null);
						 }
					 }
					 else
						 m.put("exactcheckinNum",null);
					 					 
					 if(sl3!=null&&sl3.size()>0){
						 int j=0;
						 for(j=0;j<sl3.size();j++){
					         Map m3=(Map)sl3.get(j);
					         if(((String)m3.get("majorin")).equals(cno)){
					             m.put("notcheckinNum",m3.get("notcheckinNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl3.size()||j>sl3.size()){
							 m.put("notcheckinNum",null);
						 }
					 }
					 else
						 m.put("notcheckinNum",null);
					 
					 if(sl4!=null&&sl4.size()>0){
						 int j=0;
						 for(j=0;j<sl4.size();j++){
					         Map m4=(Map)sl4.get(j);
					         if(((String)m4.get("majorin")).equals(cno)){
					             m.put("askforlateNum",m4.get("askforlateNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl4.size()||j>sl4.size()){
							 m.put("askforlateNum",null);
						 }
					 }
					 else
						 m.put("askforlateNum",null);
					 
					 if(sl5!=null&&sl5.size()>0){
						 int j=0;
						 for(j=0;j<sl5.size();j++){
					         Map m5=(Map)sl5.get(j);
					         if(((String)m5.get("majorin")).equals(cno)){
					             m.put("askreserveNum",m5.get("askreserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl5.size()||j>sl5.size()){
							 m.put("askreserveNum",null);
						 }
					 }
					 else
						 m.put("askreserveNum",null);
						 
					 if(sl6!=null&&sl6.size()>0){
						 int j=0;
						 for(j=0;j<sl6.size();j++){
					         Map m6=(Map)sl6.get(j);
					         if(((String)m6.get("majorin")).equals(cno)){
					             m.put("noreasonNum",m6.get("noreasonNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl6.size()||j>sl6.size()){
							 m.put("noreasonNum",null);
						 }
					 }
					 else
						 m.put("noreasonNum",null); 
					 
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("notcomeNum",m7.get("notcomeNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("notcomeNum",null);
						 }
					 }
					 else
						 m.put("notcomeNum",null); 
					
					 /*
					 if(sl7!=null&&sl7.size()>0){
						 int j=0;
						 for(j=0;j<sl7.size();j++){
					         Map m7=(Map)sl7.get(j);
					         if(((String)m7.get("majorin")).equals(cno)){
					             m.put("reserveNum",m7.get("reserveNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl7.size()||j>sl7.size()){
							 m.put("reserveNum",null);
						 }
					 }
					 else
						 m.put("reserveNum",null); 
						 
					 if(sl8!=null&&sl8.size()>0){
						 int j=0;
						 for(j=0;j<sl8.size();j++){
					         Map m8=(Map)sl8.get(j);
					         if(((String)m8.get("majorin")).equals(cno)){
					             m.put("leaveschoolNum",m8.get("leaveschoolNum"));//合并到一个Map对象中
					             break;
					         }
						 }
						 if(j==sl8.size()||j>sl8.size()){
							 m.put("leaveschoolNum",null);
						 }
					 }
					 else
						 m.put("leaveschoolNum",null);					 
					 */
					 			 
					 stucheckininfoList.add(m);
			 
			     }
				 
                //总人数
				 for(int k=0;k<sl1total.size();k++){
					 Map t=(Map)sl1total.get(k);
					 
					 if(sl2total!=null&&sl2total.size()>k&&sl2total.get(k)!=null){
					     Map t2=(Map)sl2total.get(k);
					     t.put("exactcheckinNumtotal",t2.get("exactcheckinNumtotal"));//合并到一个Map对象中
					 }
					 else
						 t.put("exactcheckinNumtotal",null);
					 
					 if(sl3total!=null&&sl3total.size()>k&&sl3total.get(k)!=null){
					     Map t3=(Map)sl3total.get(k);
					     t.put("notcheckinNumtotal",t3.get("notcheckinNumtotal"));
					 }
					 else
						 t.put("notcheckinNumtotal",null);
					 
					 if(sl4total!=null&&sl4total.size()>k&&sl4total.get(k)!=null){
					     Map t4=(Map)sl4total.get(k);
					     t.put("askforlateNumtotal",t4.get("askforlateNumtotal"));
					 }
					 else
						 t.put("askforlateNumtotal",null);
					 
					 if(sl5total!=null&&sl5total.size()>k&&sl5total.get(k)!=null){
					     Map t5=(Map)sl5total.get(k);
					     t.put("askreserveNumtotal",t5.get("askreserveNumtotal"));
					 }
					 else
						 t.put("askreserveNumtotal",null);
						 
					 if(sl6total!=null&&sl6total.size()>k&&sl6total.get(k)!=null){
					     Map t6=(Map)sl6total.get(k);
					     t.put("noreasonNumtotal",t6.get("noreasonNumtotal"));
					 }
					 else
						 t.put("noreasonNumtotal",null); 
					
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("notcomeNumtotal",t7.get("notcomeNumtotal"));
					 }
					 else
						 t.put("notcomeNumtotal",null); 
					 
					 /*
					 if(sl7total!=null&&sl7total.size()>k&&sl7total.get(k)!=null){
					     Map t7=(Map)sl7total.get(k);
					     t.put("reserveNumtotal",t7.get("reserveNumtotal"));
					 }
					 else
						 t.put("reserveNumtotal",null); 
						 
					 if(sl8total!=null&&sl8total.size()>k&&sl8total.get(k)!=null){
					     Map t8=(Map)sl8total.get(k);
					     t.put("leaveschoolNumtotal",t8.get("leaveschoolNumtotal"));
					 }
					 else
						 t.put("leaveschoolNumtotal",null);
					 */
					 
					 stucheckintotalList.add(t);
				 }
				 
			 }
			 
			 Comparator comp = new Comparator() { 
				 public int compare(Object o1, Object o2){ 
				 Map m1 = (Map)o1; 
				 Map m2 = (Map)o2; 
				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
				 String collegeName1 = (String)m1.get("majorin"); 
				 String collegeName2 = (String)m2.get("majorin"); 
				 return collegeName1.compareTo(collegeName2); 
				 } 
				 } ;
		     Collections.sort(stucheckininfoList, comp);//按专业代码排序
		     
			 List resultList=stucheckininfoList;			 		 
			 
			 if(resultList!=null&&resultList.size()!=0){				 
				 List rList=new ArrayList();
				 if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0){
					 for(int i=0;i<resultList.size();i++){
						 Map r=(Map)resultList.get(i);
						 if(((String)r.get("majorin")).trim().equals(request.getParameter("hmajorin").trim()))
							 rList.add(r);
					 }
					 ChangeMajorValue(rList);
					 
				 }
					 
				 else{
					 rList=resultList;
					 ChangeMajorValue(rList);
					 
				 }
				 
				 request.setAttribute("majorin",majorin);				 
			     request.setAttribute("tjlist",rList);
			     request.setAttribute("tjlisttotal",stucheckintotalList);
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 /*-----------------------------------------------------------------------*/
					 
		                // Create the Excel File
					    String	fileName="tongjimajorabroad.xls";
							
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
						columnNames.add(0,"专业");
						columnNames.add(1,"应到人数");
						columnNames.add(2,"实到人数");
						columnNames.add(3,"未到人数");
						columnNames.add(4,"请假人数");
						columnNames.add(5,"申请保留入学资格人数");
						columnNames.add(6,"不明原因未报到人数");
						columnNames.add(7,"明确不来人数");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount = rList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)rList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("majorinName"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("shouldcheckinNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("exactcheckinNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("notcheckinNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("askforlateNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("askreserveNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("noreasonNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNum")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("notcomeNum")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNum")).toString()));
								else
									ctitle.setCellValue(0);
							
								//ctitle=row.createCell((short)8);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNum")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;

						}
						//总计
						if(stucheckintotalList!=null&&stucheckintotalList.size()>0){
						     Map tableData = (Map)stucheckintotalList.get(0);
	                         //create row in spreadsheet
							 row = sheet1.createRow((short)rowCount+1);						
							 
							 HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue("总计");
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("shouldcheckinNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("shouldcheckinNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("exactcheckinNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("exactcheckinNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("notcheckinNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcheckinNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("askforlateNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askforlateNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("askreserveNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("askreserveNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("noreasonNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("noreasonNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("notcomeNumtotal")!=null)
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("notcomeNumtotal")).toString()));
								else
									ctitle.setCellValue(0);
								
								//ctitle=row.createCell((short)8);
								//ctitle.setCellStyle(cellDataStyle);
								//ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("leaveschoolNumtotal")).toString()));							
															
								//System.out.println(columnData);
								currentCell++;
							 
						}
						
						response.setContentType("application/x-msdownload");
						response.setHeader("Content-Disposition", "attachment;"
								+ " filename="
								+ new String(fileName.getBytes(), "ISO-8859-1"));

		                OutputStream os = response.getOutputStream();
		                wb.write(os);
				    /*-----------------------------------------------------------------------*/ 
					 return null;
				 }
				 else{				     				
				     return mapping.findForward("abroadtongjilistmajor");
				 }
			 }
			 else
				 return mapping.findForward("abroadtongjilistmajor"); 

			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
	//入学情况一览
	public ActionForward stucheckininfolist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
//		HttpSession session = request.getSession(false);
//
//		if (session == null) {
//			session = request.getSession(true);
//		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
               //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
		     String order=request.getParameter("horder");
		     String odr="asc";
		     if(order!=null&&order.length()>0&&order.equals("d"))
		    	 odr="desc";
			 String orderby=request.getParameter("orderby");
             List s1=new ArrayList();	
             
             Studentmodel stuinfo=new Studentmodel();				
			 stuinfo.setStudentNo(request.getParameter("hstudentNo"));
			 stuinfo.setStuName(request.getParameter("hstuName"));
             //新生报到信息列表
             String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime,hi.ifUnhealthy as ifUnhealthy) from Stucheckininfo ci,Stuhealthinfo hi,Studentmodel s where ci.studentNo=s.studentNo and hi.studentNo=ci.studentNo and s.yxClass.yxCollege.yxSchool.schoolId='0001' and s.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
             if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
             if(orderby==null||orderby.length()==0)
            	 sqlstring=sqlstring+" order by ci.studentNo";
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
                 sqlstring=sqlstring+" order by ci.studentNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName"))
                 sqlstring=sqlstring+" order by s.stuName"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("gender"))
                 sqlstring=sqlstring+" order by s.gender"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("majorin"))
                 sqlstring=sqlstring+" order by s.majorin"+" "+odr;
             
             
             List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){                 
				 
                 //新生缴费信息表查询,学费已缴纳新生
				 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay)";
				 
				 List tuitionList=checkinmanageservice.find(sqlstring);
				 
                for(int i=0;i<stucheckininfoList.size();i++){
					 
					 Map m=(Map)stucheckininfoList.get(i);
					 String sno=(String)m.get("studentNo");
				
				     if(tuitionList!=null&&tuitionList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionList.size();j++){
						     Map uhm=(Map)tuitionList.get(j);
						     if(((String)uhm.get("studentNo")).equals(sno)){
							     m.put("tuitionpayed","1");							     
							     break;
						     }
					     }
                         if(j==tuitionList.size()||j>tuitionList.size()){
						 m.put("tuitionpayed","0");//表中无该生的已缴费记录,则说明该生未缴学费

					    }
				    }
				    else{
					    m.put("tuitionpayed","0");//表为空,所有新生的体检结果均是合格
				    }
				 			 
				 s1.add(m);
				 }
                
                if(orderby!=null&&orderby.length()>0&&orderby.equals("stuName")){
                	Comparator comp1 = new Comparator() { 
       				 public int compare(Object o1, Object o2){ 
       				 Map m1 = (Map)o1; 
       				 Map m2 = (Map)o2; 
       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
       				 String collegeName1 = (String)m1.get("stuName"); 
      				 String collegeName2 = (String)m2.get("stuName");      				

      				 com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(Locale.CHINA);
      				 com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
      				 com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
                     //注意,返回值是比较的结果>0,=0,或者<0
       			     //return collator.compare(((CollationKey)c1).getSourceString(), ((CollationKey)c2).getSourceString());
                     return collator.compare(c1.getSourceString(),c2.getSourceString());
       				 //return collegeName1.compareTo(collegeName2); 
       				 } 
       				} ;
       				Comparator comp2 = new Comparator() { 
          				 public int compare(Object o1, Object o2){ 
          				 Map m1 = (Map)o1; 
          				 Map m2 = (Map)o2; 
          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
          				String collegeName1 = (String)m1.get("stuName"); 
          				String collegeName2 = (String)m2.get("stuName");
          				
          				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(Locale.CHINA);
          				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(collegeName1);
          				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(collegeName2);
                        //注意,返回值是比较的结果>0,=0,或者<0
          			     //return collator.compare(((CollationKey)c2).getSourceString(), ((CollationKey)c1).getSourceString()); 
          				return collator.compare(c2.getSourceString(),c1.getSourceString());
          				 //return collegeName2.compareTo(collegeName1); 
          				 } 
          				} ;
       			 if(odr.equals("asc"))	
       		         Collections.sort(s1, comp1);
       			 else
       				 Collections.sort(s1, comp2);
       		     
                }
                
                if(orderby!=null&&orderby.length()>0&&orderby.equals("ifChecked")){
                	Comparator comp1 = new Comparator() { 
       				 public int compare(Object o1, Object o2){ 
       				 Map m1 = (Map)o1; 
       				 Map m2 = (Map)o2; 
       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
       				 String collegeName1 = (String)m1.get("ifChecked"); 
       				 String collegeName2 = (String)m2.get("ifChecked"); 
       				
       				 return collegeName1.compareTo(collegeName2); 
       				 } 
       				} ;
       				Comparator comp2 = new Comparator() { 
          				 public int compare(Object o1, Object o2){ 
          				 Map m1 = (Map)o1; 
          				 Map m2 = (Map)o2; 
          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
          				 String collegeName1 = (String)m1.get("ifChecked"); 
          				 String collegeName2 = (String)m2.get("ifChecked"); 
          				
          				 return collegeName2.compareTo(collegeName1); 
          				 } 
          				} ;
       			 if(odr.equals("asc"))	
       		         Collections.sort(s1, comp1);
       			 else
       				 Collections.sort(s1, comp2);
       		     
                }
                if(orderby!=null&&orderby.length()>0&&orderby.equals("ifUnhealthy")){
                	Comparator comp1 = new Comparator() { 
       				 public int compare(Object o1, Object o2){ 
       				 Map m1 = (Map)o1; 
       				 Map m2 = (Map)o2; 
       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
       				 String collegeName1 = (String)m1.get("ifUnhealthy"); 
       				 String collegeName2 = (String)m2.get("ifUnhealthy"); 
       				 
       				 String ckin1=(String)m1.get("ifCheckedin"); 
     				 String ckin2=(String)m2.get("ifCheckedin"); 
     				 if(ckin1.equals(ckin2))
     				 return collegeName1.compareTo(collegeName2); 
     				else
     					return ckin1.compareTo(ckin2);
       				 } 
       				} ;
       				Comparator comp2 = new Comparator() { 
          				 public int compare(Object o1, Object o2){ 
          				 Map m1 = (Map)o1; 
          				 Map m2 = (Map)o2; 
          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
          				 String collegeName1 = (String)m1.get("ifUnhealthy"); 
          				 String collegeName2 = (String)m2.get("ifUnhealthy"); 
          				 String ckin1=(String)m1.get("ifCheckedin"); 
          				 String ckin2=(String)m2.get("ifCheckedin"); 
          				 if(ckin1.equals(ckin2))
          				 return collegeName2.compareTo(collegeName1); 
          				else
          					return ckin2.compareTo(ckin1);
          				 } 
          				} ;
       			 if(odr.equals("asc"))	
       		         Collections.sort(s1, comp1);
       			 else
       				 Collections.sort(s1, comp2);
       		     
                }
                if(orderby!=null&&orderby.length()>0&&orderby.equals("tuitionpayed")){
                	Comparator comp1 = new Comparator() { 
       				 public int compare(Object o1, Object o2){ 
       				 Map m1 = (Map)o1; 
       				 Map m2 = (Map)o2; 
       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
       				 String collegeName1 = (String)m1.get("tuitionpayed"); 
       				 String collegeName2 = (String)m2.get("tuitionpayed"); 
       				
       				 String ckin1=(String)m1.get("ifCheckedin"); 
    				 String ckin2=(String)m2.get("ifCheckedin"); 
    				 if(ckin1.equals(ckin2))
    				 return collegeName1.compareTo(collegeName2); 
    				 else
    					return ckin1.compareTo(ckin2); 
       				 } 
       				} ;
       				Comparator comp2 = new Comparator() { 
          				 public int compare(Object o1, Object o2){ 
          				 Map m1 = (Map)o1; 
          				 Map m2 = (Map)o2; 
          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
          				 String collegeName1 = (String)m1.get("tuitionpayed"); 
          				 String collegeName2 = (String)m2.get("tuitionpayed"); 
          				
          				 String ckin1=(String)m1.get("ifCheckedin"); 
         				 String ckin2=(String)m2.get("ifCheckedin"); 
         				 if(ckin1.equals(ckin2))
         				 return collegeName2.compareTo(collegeName1); 
         				 else
         					return ckin2.compareTo(ckin1);
          				 } 
          				} ;
       			 if(odr.equals("asc"))	
       		         Collections.sort(s1, comp1);
       			 else
       				 Collections.sort(s1, comp2);
       		     
                }
                if(orderby!=null&&orderby.length()>0&&orderby.equals("ifGotStucard")){
                	Comparator comp1 = new Comparator() { 
       				 public int compare(Object o1, Object o2){ 
       				 Map m1 = (Map)o1; 
       				 Map m2 = (Map)o2; 
       				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
       				 String collegeName1 = (String)m1.get("ifGotStucard"); 
       				 String collegeName2 = (String)m2.get("ifGotStucard"); 
       				
       				 String ckin1=(String)m1.get("ifCheckedin"); 
    				 String ckin2=(String)m2.get("ifCheckedin"); 
    				 if(ckin1.equals(ckin2))
    				 return collegeName1.compareTo(collegeName2); 
    				 else
    					return ckin1.compareTo(ckin2);
       				 } 
       				} ;
       				Comparator comp2 = new Comparator() { 
          				 public int compare(Object o1, Object o2){ 
          				 Map m1 = (Map)o1; 
          				 Map m2 = (Map)o2; 
          				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
          				 String collegeName1 = (String)m1.get("ifGotStucard"); 
          				 String collegeName2 = (String)m2.get("ifGotStucard"); 
          				
          				 String ckin1=(String)m1.get("ifCheckedin"); 
         				 String ckin2=(String)m2.get("ifCheckedin"); 
         				 if(ckin1.equals(ckin2))
         				 return collegeName2.compareTo(collegeName1); 
         				 else
         					return ckin2.compareTo(ckin1);
          				 } 
          				} ;
       			 if(odr.equals("asc"))	
       		         Collections.sort(s1, comp1);
       			 else
       				 Collections.sort(s1, comp2);
       		     
                }
                
                Map endm1=new HashMap();
                endm1.put("id","");
                endm1.put("studentNo","");
                endm1.put("gender","");
                endm1.put("majorin","");
                endm1.put("ifChecked","9");
                endm1.put("tuitionpayed","9");
                endm1.put("ifUnhealthy","9");
                endm1.put("ifGotStucard","9");
                
                Map endm2=new HashMap();
                endm2.put("id","");
                endm2.put("studentNo","");
                endm2.put("gender","");
                endm2.put("majorin","");
                endm2.put("ifChecked","8");
                endm2.put("tuitionpayed","8");
                endm2.put("ifUnhealthy","8");
                endm2.put("ifGotStucard","8");	
                
                s1.add(endm1);s1.add(endm2);
				 
				 List resultList=new ArrayList();
				 //起始页设置
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				     request.setAttribute("stuinfo",stuinfo);
				     request.setAttribute("order",order);
                     //专业
				 	List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				    //System.out.println("list success");
				 }
				    return mapping.findForward("stucheckininfolist");
				 
			}
			else
				 return mapping.findForward("stucheckininfolist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}	
	
//	入学情况一览导出Excel
	public ActionForward stucheckininfoexcel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		String msg="";
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
               //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
             List s1=new ArrayList();		 			 
             Studentmodel stuinfo=new Studentmodel();				
			 stuinfo.setStudentNo(request.getParameter("hstudentNo"));
			 stuinfo.setStuName(request.getParameter("hstuName"));
			 
             //新生报到信息列表
             String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime,hi.ifUnhealthy as ifUnhealthy) from Stucheckininfo ci,Stuhealthinfo hi,Studentmodel s where ci.studentNo=s.studentNo and hi.studentNo=ci.studentNo and s.yxClass.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
             if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 sqlstring=sqlstring+" order by ci.studentNo";
			 
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){                 
				 
                 //新生缴费信息表查询,学费已缴纳新生
				 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo) from StuFeeInfo ci where ci.feeItem='01' and (ci.exactPay>ci.shouldPay or ci.exactPay=ci.shouldPay)";
				 
				 List tuitionList=checkinmanageservice.find(sqlstring);
				 
                for(int i=0;i<stucheckininfoList.size();i++){
					 
					 Map m=(Map)stucheckininfoList.get(i);
					 String sno=(String)m.get("studentNo");
				
				     if(tuitionList!=null&&tuitionList.size()>0){
					     int j=0;
					     for(j=0;j<tuitionList.size();j++){
						     Map uhm=(Map)tuitionList.get(j);
						     if(((String)uhm.get("studentNo")).equals(sno)){
							     m.put("tuitionpayed","1");							     
							     break;
						     }
					     }
                         if(j==tuitionList.size()||j>tuitionList.size()){
						 m.put("tuitionpayed","0");//表中无该生的已缴费记录,则说明该生未缴学费

					    }
				    }
				    else{
					    m.put("tuitionpayed","0");//表为空,所有新生的体检结果均是合格
				    }
				 			 
				 s1.add(m);
				 }
				 
				 List resultList=new ArrayList();
				 //起始页设置
				 if(offset.equals("0"))
				     resultList=s1;
				 else if((Integer.parseInt(offset))<s1.size()||(Integer.parseInt(offset))==s1.size())
					 resultList=s1.subList((Integer.parseInt(offset)),s1.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(s1.size()));
				     request.setAttribute("stuinfo",stuinfo);
                     //专业
				 	List majorList=getmajorList();
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				    System.out.println("list success");
				 }
				 
				 ChangeMajorValue(s1);
				 ChangeGenderValue(s1);
				 ChangeCheckValue(s1);
				 ChangeHealthValue(s1);
				 ChangeFeeValue(s1);
				 ChangeStucardValue(s1);
				 
				 /*-----------------------------------------------------------------------*/
	                // Create the Excel File
			 		//FileOutputStream fileOut = new FileOutputStream("c:/新生入学信息一览.xls");
					String	fileName="stucheckininfo.xls";
					// Create the Sheet with the name of the Table
					HSSFWorkbook wb = new HSSFWorkbook();
					
	                //设置显示的字体以及相关的样式
			 		HSSFFont font = wb.createFont();
			 		    font.setFontHeightInPoints((short)8);
			 		    //font.setFontName("宋体");
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
					columnNames.add(3,"录取专业");
					columnNames.add(4,"入学通知书是否已核验");
					columnNames.add(5,"健康复查是否已合格");
					columnNames.add(6,"学费是否已缴");
					columnNames.add(7,"学生证/校徽是否发放");
					
					// System.out.println(columnNames.size());
					for (int i=0; i<columnNames.size(); i++)
					{
						 HSSFCell cname=row.createCell((short)i);
						 cname.setCellStyle(cellHeadStyle);
						 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
						 cname.setCellValue((String)columnNames.get(i));
					}
					
					// Populate the Row Data to the SpreadSheet
					int rowCount = s1.size();
					// goal houses the number of cells in the target spreadsheet
					int goal = rowCount*columnNames.size();			
					
					//actual population of target spreadsheet
					int currentCell = 0;
					
					for (int i=0; i<rowCount; i++)
					{
						Map tableData = (Map)s1.get(i);
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
							ctitle.setCellValue((String)tableData.get("genderName"));
							
							ctitle=row.createCell((short)3);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("majorinName"));
							
							ctitle=row.createCell((short)4);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("ifCheckedName"));
							
							ctitle=row.createCell((short)5);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("ifUnhealthyName"));
							
							ctitle=row.createCell((short)6);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("tuitionpayedName"));
							
							ctitle=row.createCell((short)7);
							ctitle.setCellStyle(cellDataStyle);
							ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
							ctitle.setCellValue((String)tableData.get("ifGotStucardName"));
							//System.out.println(columnData);
							currentCell++;

					}			
					// clean up resources
				   	//wb.write(fileOut);
			 	 	//fileOut.close();
					
					response.setContentType("application/x-msdownload");
					response.setHeader("Content-Disposition", "attachment;"
							+ " filename="
							+ new String(fileName.getBytes(), "ISO-8859-1"));

	                OutputStream os = response.getOutputStream();
	                wb.write(os);
			    /*-----------------------------------------------------------------------*/ 
				 
				 return null;
				 
			}
			else{
				msg="0";
				request.setAttribute("msg",msg);
				return mapping.findForward("stucheckininfolist");
			}
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}	
	
	//入学信息 报到信息一览
	public ActionForward checkininfoview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        

		// 数据库验证
	          try {
		            if(checkinmanageservice==null)
		            	 System.out.println("service is null");
		            
		            Account freshmen=(Account)session.getAttribute("accountPerson");
		            		            
		            String id=freshmen.getPerson().getPersonCode();	//获取登录新生的学号	           
					 		 
		            String sqlstring=null;		            
		            
		            sqlstring="select new Map(ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ai.hasArchives as hasArchives,ai.hasStuarchive as hasStuarchive,ai.archiveSubmit as archiveSubmit,hi.ifUnhealthy as ifUnhealthy) from Stucheckininfo ci,Stuarchivesinfo ai,Stuhealthinfo hi,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and ai.studentNo=ci.studentNo and hi.studentNo=ci.studentNo and s.yxClass.classId=c.classId and ci.studentNo='"+id+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		            
                    //新生一卡通拍照信息
		            sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollYear as enrollYear,ci.ecardPhoto as ecardPhoto) from StuCardfeeInfo ci where ci.studentNo='"+id+"'";
		            
		            List ecardPhotoList=checkinmanageservice.find(sqlstring);
		            
		            if(ecardPhotoList!=null&&ecardPhotoList.size()>0)
		            	request.setAttribute("ecardphotolist",ecardPhotoList);
		            
		          if(stuinfoList!=null&&stuinfoList.size()!=0){
		            request.setAttribute("checkinlist",stuinfoList);
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
		 	        System.out.println("find student info success");
		            return mapping.findForward("checkininfoview");
		          }
		          else
			        return mapping.findForward("checkininfoview");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }

	   }
	
//	入学信息 个人信息一览
	public ActionForward personalinfoview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        

		// 数据库验证
	          try {
		            if(checkinmanageservice==null)
		            	 System.out.println("service is null");
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String id=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
		            
		            String sqlstring=null;		            
		            
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,s.enterenceNo as enrollNo,s.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,s.fromProvince as fromProvince) from Studentmodel s where s.studentNo='"+id+"'";
		            	            
		            List stuinfoList=checkinmanageservice.find(sqlstring);
		            
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,c.classNo as classNo,c.introduction as classintroduction,col.collegeName as collegeName,col.collegeId as collegeId,col.introduction as introduction) from Studentmodel s,Classmodel c,Collegemodel col where s.yxClass.classId=c.classId and c.yxCollege.collegeId=col.collegeId and s.studentNo='"+id+"'";
    	            
		            List classinfoList=checkinmanageservice.find(sqlstring);
		            
                    sqlstring="select new Map(s.id as id,s.studentNo as studentNo,m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Studentmodel s,Collegemanager cm,Managermodel m where s.yxClass.yxCollege.collegeId=cm.id.collegeId and cm.id.managerId=m.managerId and s.studentNo='"+id+"'";
    	            
		            List supermanagerinfoList=checkinmanageservice.find(sqlstring);
		            
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,c.classNo as classNo,m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Studentmodel s,Classmodel c,Classmanager cm,Managermodel m,Managermanagerrole mr where s.yxClass.classId=c.classId and cm.id.classId=s.yxClass.classId and cm.id.managerId=m.managerId and mr.id.managerId=m.managerId and mr.id.roleId='21' and s.studentNo='"+id+"'";
    	            
		            List managerinfoList=checkinmanageservice.find(sqlstring);
		            
                    sqlstring="select new Map(s.id as id,s.studentNo as studentNo,c.classNo as classNo,m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Studentmodel s,Classmodel c,Classmanager cm,Managermodel m,Managermanagerrole mr where s.yxClass.classId=c.classId and cm.id.classId=s.yxClass.classId and cm.id.managerId=m.managerId and mr.id.managerId=m.managerId and mr.id.roleId='22' and s.studentNo='"+id+"'";
    	            
		            List tutorinfoList=checkinmanageservice.find(sqlstring);
		            
                    //sqlstring="select new Map(s.id as id,s.studentNo as studentNo,c.classNo as classNo,m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Studentmodel s,Classmodel c,Classmanager cm,Managermodel m,Managermanagerrole mr where s.yxClass.classId=c.classId and cm.id.classId=s.yxClass.classId and cm.id.managerId=m.managerId and cm.tutorType='1' and mr.id.managerId=m.managerId and mr.id.roleId='22' and s.studentNo='"+id+"'";
    	            
		            //List majortutorinfoList=checkinmanageservice.find(sqlstring);
		            
		            sqlstring="select new Map(s.id as id,s.studentNo as studentNo,d.location as location,d.dormitory as dorm,d.roomNumber as room) from Studentmodel s,Dormitorymodel d where s.dormId=d.dormitoryId and s.studentNo='"+id+"'";
    	            
		            List dorminfoList=checkinmanageservice.find(sqlstring);		            
		            
		 		         		    	            
		          if(stuinfoList!=null&&stuinfoList.size()!=0){
		        	  ChangeDepartmentValue(stuinfoList);
		            request.setAttribute("checkinlist",stuinfoList);
		            
		            if(classinfoList!=null&&classinfoList.size()>0)
		            	request.setAttribute("classlist",classinfoList);
		            if(supermanagerinfoList!=null&&supermanagerinfoList.size()>0)
		            	request.setAttribute("supermanagerlist",supermanagerinfoList);
		            if(managerinfoList!=null&&managerinfoList.size()>0)
		            	request.setAttribute("managerlist",managerinfoList);
		            if(tutorinfoList!=null&&tutorinfoList.size()>0)		            	
		                request.setAttribute("tutorlist",tutorinfoList);
		            //if(majortutorinfoList!=null&&majortutorinfoList.size()>0)		            	
		            //    request.setAttribute("majortutorlist",majortutorinfoList);
		            if(dorminfoList!=null&&dorminfoList.size()>0){
		            	ChangeDormValue(dorminfoList);
		            	request.setAttribute("dormlist",dorminfoList);
		            }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
		 	        //System.out.println("find student info success");
		            return mapping.findForward("personalinfoview");
		          }
		          else
			        return mapping.findForward("personalinfoview");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }

	   }
	
//辅导员导师本班信息查询
	public ActionForward myclassinfoview(ActionMapping mapping, ActionForm form,
		    HttpServletRequest request, HttpServletResponse response)
		    throws Exception {
	      HttpSession session = request.getSession(false);

	      if (session == null) {
		      session = request.getSession(true);
	      }

	        ActionMessages errors = new ActionMessages();
	        

		// 数据库验证
	          try {
		            if(checkinmanageservice==null)
		            	 System.out.println("service is null");
					
		            Account freshmen=(Account)session.getAttribute("accountPerson");	            
		            
		            String id=freshmen.getPerson().getPersonCode();	//获取登录人的学号
		            
		            String sqlstring=null;		            
		            		           		            
		            sqlstring="select new Map(c.classId as classId,c.classNo as classNo,c.introduction as classintroduction,col.collegeName as collegeName,col.collegeId as collegeId,col.introduction as introduction) from Classmodel c,Collegemodel col,Classmanager cm,Managermodel m where cm.id.classId=c.classId and cm.id.managerId=m.managerId and c.yxCollege.collegeId=col.collegeId and m.managerNo='"+id+"'";
    	            
		            List classinfoList=checkinmanageservice.find(sqlstring);
		            
		            if(classinfoList!=null&&classinfoList.size()>0){
		            	Map classm=(Map)classinfoList.get(0);
		            	String classId=(String)classm.get("classId");
		            	String collegeId=(String)classm.get("collegeId");
		            
                    sqlstring="select new Map(m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Collegemanager cm,Managermodel m where cm.id.managerId=m.managerId and cm.id.collegeId='"+collegeId+"'";
    	            
		            List supermanagerinfoList=checkinmanageservice.find(sqlstring);
		            
		            sqlstring="select new Map(m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Classmanager cm,Managermodel m,Managermanagerrole mr where cm.id.managerId=m.managerId and mr.id.managerId=m.managerId and mr.id.roleId='21' and cm.id.classId='"+classId+"'";
    	            
		            List managerinfoList=checkinmanageservice.find(sqlstring);
		            
		            sqlstring="select new Map(m.managerName as managerName,m.contact as contact,m.introduction as introduction) from Classmanager cm,Managermodel m,Managermanagerrole mr where cm.id.managerId=m.managerId and mr.id.managerId=m.managerId and mr.id.roleId='22' and cm.id.classId='"+classId+"'";
	    	           
		            List tutorinfoList=checkinmanageservice.find(sqlstring);
		            
		            request.setAttribute("classlist",classinfoList);
		            if(supermanagerinfoList!=null&&supermanagerinfoList.size()>0)
		            	request.setAttribute("supermanagerlist",supermanagerinfoList);
		            if(managerinfoList!=null&&managerinfoList.size()>0)
		            	request.setAttribute("managerlist",managerinfoList);
		            if(tutorinfoList!=null&&tutorinfoList.size()>0)		            	
		                request.setAttribute("tutorlist",tutorinfoList);
		            
		            return mapping.findForward("myclassinfoview");
		          }
		          else
			        return mapping.findForward("myclassinfoview");
	          } catch (Exception e) {
		           e.printStackTrace();
		           System.out.println("find error");
		           return mapping.findForward("faile");
	          }

	   }
			
    //取复旦学院的所有书院
	public List getCollegeList(){
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 String sqlstring="select new Map(col.collegeId as id,col.collegeNo as collegeNo,col.collegeName as collegeName) from Collegemodel col where col.yxSchool.schoolId='0001' order by col.collegeNo";
			 List collegeList=checkinmanageservice.find(sqlstring);
			 
			 if(collegeList!=null&&collegeList.size()>0)
				 return collegeList;
			 else
				 return null;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}
	
	}
	//取书院和班级列表
	public String[][] getColandCls(){
		
		   List rList=new ArrayList();			   
		   String sqlstring = "";	
		   String[][] result;
		   
		   try {
				 if(checkinmanageservice==null)
					 System.out.println("service is null");		     
		     
		     sqlstring="select new Map(cls.classNo as classNo,col.collegeId as collegeId,col.collegeName as collegeName,col.collegeNo as collegeNo) from Collegemodel col,Classmodel cls where cls.yxCollege.collegeId=col.collegeId and cls.curYear='"+DateUtil.getNow("yyyy")+"' order by col.collegeNo";
		     
		     rList=checkinmanageservice.find(sqlstring);
		     if(rList!=null&&rList.size()>0){
		    	 result=new String[rList.size()][4];
		         for(int i=0;i<rList.size();i++){
		             result[i][0] =(String)(((Map)rList.get(i)).get("classNo"));
		             result[i][1] = (String)(((Map)rList.get(i)).get("collegeId"));
		             result[i][2] = (String)(((Map)rList.get(i)).get("collegeName"));
		             result[i][3] = (String)(((Map)rList.get(i)).get("collegeNo"));
		         } 		        
		         return result;
		     }
		     else
		    	 return null;

		   }catch (Exception e){
		     e.printStackTrace();
		     return null;
		   }

		 }
	
	public void ChangeGenderValue(List list){
		String[][] ar={{"1","男"},{"2","女"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("gender")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("genderName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeDepartmentValue(List list){
		List departList=getdepartmentList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("department")!=null){
			     String mj=((String)n.get("department")).trim();
			     for(int k=0;k<departList.size();k++){
				     Map n1=(Map)departList.get(k);
				     String mj1=((String)n1.get("deptCode")).trim();
				     if(mj.equals(mj1)){
					     n.put("departmentName",((String)n1.get("deptName")).trim());
				     }
			     }
			 }
			 else
				 n.put("departmentName","");
				 
		 }
		
	}
	
	public void ChangeMajorValue(List list){
		List majorList=getmajorList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("majorin")!=null){
			   String mj=((String)n.get("majorin")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("majorinName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("majorinName","");
		 }
		
	}
	
	public void ChangefromProvinceValue(List list){
		List majorList=getfromProvinceList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("fromProvince")!=null){
			   String mj=((String)n.get("fromProvince")).trim();
			   for(int k=0;k<majorList.size();k++){
				 Map n1=(Map)majorList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("fromProvinceName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("fromProvinceName","");
		 }
		
	}
	
	public void ChangeCheckinValue(List list){
		String[][] ar={{"0","未报到"},{"1","已报到"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifCheckedin")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifCheckedinName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeCheckValue(List list){
		String[][] ar={{"0","未核验"},{"1","已核验"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifChecked")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifCheckedName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeGotMaterialValue(List list){
		String[][] ar={{"0","未领取"},{"1","已领取"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifGotMaterial")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifGotMaterialName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeEcardPhotoValue(List list){
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("ecardPhoto")!=null&&n.get("ecardPhoto").equals("1"))
				 n.put("ecardPhotoName","已完成");
			 else
				 n.put("ecardPhotoName","未完成");
		 
		 }
		
	}
	
	public void ChangeGotEcardValue(List list){
		String[][] ar={{"0","未更换"},{"1","已更换"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifGotEcard")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifGotEcardName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeGotStucardValue(List list){
		String[][] ar={{"0","未领取"},{"1","已领取"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifGotStucard")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifGotStucardName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeUnhealthyValue(List list){
		String[][] ar={{"0","未体检"},{"1","体检合格"},{"2","需复检"},{"3","复检合格"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifUnhealthy")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifUnhealthyName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeArchivesValue(List list){
		String[][] ar={{"0","未上交"},{"1","已上交"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("hasArchives")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("hasArchivesName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeStuArchiveValue(List list){
		String[][] ar={{"0","未核对"},{"1","已核对"}};
		String[][] ar2={{"0","未入库"},{"1","已入库"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("hasStuarchive")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("hasStuarchiveName",ar[k][1]);
				 }
			 }
			 
		 }
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("archiveSubmit")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar2[k][0];
				 if(mj.equals(mj1)){
					 n.put("archiveSubmitName",ar2[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeHealthValue(List list){
		String[][] ar={{"0","未体检"},{"1","体检合格"},{"2","需复检"},{"3","复检合格"}};
		String[][] ci={{"0","未报到"},{"1","已报到"}};
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String ic=((String)n.get("ifCheckedin")).trim();
			 String mj=((String)n.get("ifUnhealthy")).trim();
			 if(ic.equals("0")){
				 n.put("ifUnhealthyName",ci[0][1]);
				 
			 }
			 else{
			    for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("ifUnhealthyName",ar[k][1]);
				   }
			    }
			 }
		 }//for
		
	}
	
	public void ChangeFeeValue(List list){
		String[][] ar={{"0","未缴纳"},{"1","已缴纳"}};
		String[][] ci={{"0","未报到"},{"1","已报到"}};
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String ic=((String)n.get("ifCheckedin")).trim();
			 String mj=((String)n.get("tuitionpayed")).trim();
			 if(ic.equals("0")){
				 n.put("tuitionpayedName",ci[0][1]);
				 
			 }
			 else{
			    for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("tuitionpayedName",ar[k][1]);
				   }
			    }
			 }
		 }//for
		
	}
	
	public void ChangeStucardValue(List list){
		String[][] ar={{"0","未发放"},{"1","已发放"}};
		String[][] ci={{"0","未报到"},{"1","已报到"}};
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String ic=((String)n.get("ifCheckedin")).trim();
			 String mj=((String)n.get("ifGotStucard")).trim();
			 if(ic.equals("0")){
				 n.put("ifGotStucardName",ci[0][1]);
				 
			 }
			 else{
			    for(int k=0;k<ar.length;k++){				 
				   String mj1=ar[k][0];				 
				   if(mj.equals(mj1)){
					   n.put("ifGotStucardName",ar[k][1]);
				   }
			    }
			 }
		 }//for
		
	}
	
	public void ChangeDormValue(List list){
		List locationList=getlocationList();
		List dormitoryList=getdormitoryList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("location")!=null){
			 String mj=((String)n.get("location")).trim();			 
			   for(int k=0;k<locationList.size();k++){
				 Map n1=(Map)locationList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("locationName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("locationName","");			 
		 }
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("dorm")!=null){
			   String mj=((String)n.get("dorm")).trim();			 
			   for(int k=0;k<dormitoryList.size();k++){
				 Map n1=(Map)dormitoryList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("dormitoryName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("dormitoryName","");
		 }
	}
	
	public List getdepartmentList(){
		List departmentList=checkinmanageservice.find("select new Map(d.deptCode as deptCode,d.deptName as deptName) from Department d");
		return departmentList;
	}
	
	public List getmajorList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
		
		Comparator comp1 = new Comparator() { 
				public int compare(Object o1, Object o2){ 
				Map m1 = (Map)o1; 
				Map m2 = (Map)o2; 
				String dictCaption1 = (String)m1.get("dictCaption"); 
				String dictCaption2 = (String)m2.get("dictCaption");      				

				com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
				com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
				com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
                //注意,返回值是比较的结果>0,=0,或者<0
			    return collator.compare(c1.getSourceString(),c2.getSourceString());				
				 } 
		} ;				
			 
		Collections.sort(majorList, comp1);		
		
		return majorList;
	}
	
	public List getfromProvinceList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
		Comparator comp1 = new Comparator() { 
			public int compare(Object o1, Object o2){ 
			Map m1 = (Map)o1; 
			Map m2 = (Map)o2; 
			String dictCaption1 = (String)m1.get("dictCaption"); 
			String dictCaption2 = (String)m2.get("dictCaption");      				

			com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
			com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
			com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
            //注意,返回值是比较的结果>0,=0,或者<0
		    return collator.compare(c1.getSourceString(),c2.getSourceString());				
			 } 
	    } ;				
		 
	    Collections.sort(majorList, comp1);
		return majorList;
	}
	
	public List getlocationList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=6 order by di.id.dictValue");
		return majorList;
	}
	
	public List getdormitoryList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=7 order by di.id.dictValue");
		return majorList;
	}
	
	public void ExportstucheckinList(List list,HttpServletResponse response){
		try{
		/*-----------------------------------------------------------------------*/
            // Create the Excel File
			String	fileName="stucheckinlist.xls";
			// Create the Sheet with the name of the Table
			HSSFWorkbook wb = new HSSFWorkbook();
			
            //设置显示的字体以及相关的样式
	 		HSSFFont font = wb.createFont();
	 		    font.setFontHeightInPoints((short)8);
	 		    //font.setFontName("宋体");
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
			columnNames.add(0,"班级");
			columnNames.add(1,"学号");
			columnNames.add(2,"姓名");
			columnNames.add(3,"性别");
			columnNames.add(4,"专业");
			columnNames.add(5,"生源地");
			columnNames.add(6,"报到");
			columnNames.add(7,"通知书");
			columnNames.add(8,"资料");
			columnNames.add(9,"一卡通拍照");
			columnNames.add(10,"正式一卡通");
			columnNames.add(11,"档案袋");
			columnNames.add(12,"档案");
			columnNames.add(13,"体检");								
			columnNames.add(14,"学生证/校徽");
			
			// System.out.println(columnNames.size());
			for (int i=0; i<columnNames.size(); i++)
			{
				 HSSFCell cname=row.createCell((short)i);
				 cname.setCellStyle(cellHeadStyle);
				 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
				 cname.setCellValue((String)columnNames.get(i));
			}
			
			// Populate the Row Data to the SpreadSheet
			int rowCount = list.size();
			// goal houses the number of cells in the target spreadsheet
			int goal = rowCount*columnNames.size();			
			
			//actual population of target spreadsheet
			int currentCell = 0;
			
			for (int i=0; i<rowCount; i++)
			{
				Map tableData = (Map)list.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short)(i+1));
				
					// populate the spreadsheet with the cell						
					HSSFCell ctitle=row.createCell((short)0);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("classNo"));
					
					ctitle=row.createCell((short)1);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("studentNo"));
					
					ctitle=row.createCell((short)2);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("stuName"));
					
					ctitle=row.createCell((short)3);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("genderName"));
					
					ctitle=row.createCell((short)4);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("majorinName"));
					
					ctitle=row.createCell((short)5);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("fromProvinceName"));
					
					ctitle=row.createCell((short)6);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifCheckedinName"));
					
					ctitle=row.createCell((short)7);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifCheckedName"));
					
					ctitle=row.createCell((short)8);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifGotMaterialName"));
					
					ctitle=row.createCell((short)9);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ecardPhotoName"));
					
					ctitle=row.createCell((short)10);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifGotEcardName"));
					
					ctitle=row.createCell((short)11);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("hasArchivesName"));
					
					ctitle=row.createCell((short)12);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("hasStuarchiveName")+" "+(String)tableData.get("archiveSubmitName"));
					
					ctitle=row.createCell((short)13);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifUnhealthyName"));
															
					ctitle=row.createCell((short)14);
					ctitle.setCellStyle(cellDataStyle);
					ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					ctitle.setCellValue((String)tableData.get("ifGotStucardName"));
					//System.out.println(columnData);
					currentCell++;

			}			
			// clean up resources
		   	//wb.write(fileOut);
	 	 	//fileOut.close();
			
			response.setContentType("application/x-msdownload");
			response.setHeader("Content-Disposition", "attachment;"
					+ " filename="
					+ new String(fileName.getBytes(), "ISO-8859-1"));

            OutputStream os = response.getOutputStream();
            wb.write(os);
	    /*-----------------------------------------------------------------------*/ 
            
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
}


