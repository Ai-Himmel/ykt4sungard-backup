/**
 * 
 */
package org.king.checkinmanage.web.action;

/**
 * @author jackey
 *
 */
import java.sql.Timestamp;
import java.sql.Time;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.sql.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Stuarchivesinfo;
import org.king.checkinmanage.domain.Stucheckininfo;

import org.king.checkinmanage.service.CheckinmanageService;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;



/**
 * @author jackey
 *
 */
public class ArchivesAction extends BaseAction{
	
	
	private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	//档案袋明细登记
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		Stuarchivesinfo stuarchivesinfo = (Stuarchivesinfo)aform.get("stuarchivesinfo");
        
		try {
			 
			 stuarchivesinfo.setHasArchives(request.getParameter("hasArchives"+request.getParameter("updateid")));
	         stuarchivesinfo.setHasStuarchive(request.getParameter("hasStuarchive"+request.getParameter("updateid")));
	       	 stuarchivesinfo.setHasLeagueFile(request.getParameter("hasLeagueFile"+request.getParameter("updateid")));
	       	 stuarchivesinfo.setHasRegform(request.getParameter("hasRegform"+request.getParameter("updateid")));
	       	 
	     	 stuarchivesinfo.setIfSubmitted(request.getParameter("ifSubmitted"+request.getParameter("updateid")));
	         stuarchivesinfo.setArchiveSubmit(request.getParameter("archiveSubmit"+request.getParameter("updateid")));

			 
	      	 stuarchivesinfo.setOtherFiles(request.getParameter("otherFiles"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setMemo(request.getParameter("memo"+request.getParameter("updateid")));
	      		      	 
	      	 stuarchivesinfo.setStudentNo(request.getParameter("studentNo"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setEnrollNo(request.getParameter("enrollNo"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setEnrollYear(request.getParameter("enrollYear"+request.getParameter("updateid")));
	      		     
	      	 stuarchivesinfo.setUpdatorId(request.getParameter("updatorId"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
		     stuarchivesinfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stuarchivesinfo);
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
		    Stuarchivesinfo stuarchivesinfo = new Stuarchivesinfo();
        
		    try {
			 
		    	stuarchivesinfo.setHasArchives(request.getParameter("hasArchives"+ids[i]));
		         stuarchivesinfo.setHasStuarchive(request.getParameter("hasStuarchive"+ids[i]));
		       	 stuarchivesinfo.setHasLeagueFile(request.getParameter("hasLeagueFile"+ids[i]));
		       	 stuarchivesinfo.setHasRegform(request.getParameter("hasRegform"+ids[i]));
		       	 
		     	 stuarchivesinfo.setIfSubmitted(request.getParameter("ifSubmitted"+ids[i]));
		         stuarchivesinfo.setArchiveSubmit(request.getParameter("archiveSubmit"+ids[i]));

				 
		      	 stuarchivesinfo.setOtherFiles(request.getParameter("otherFiles"+ids[i]));
		      	 stuarchivesinfo.setMemo(request.getParameter("memo"+ids[i]));
		      		      	 
		      	 stuarchivesinfo.setStudentNo(request.getParameter("studentNo"+ids[i]));
		      	 stuarchivesinfo.setEnrollNo(request.getParameter("enrollNo"+ids[i]));
		      	 stuarchivesinfo.setEnrollYear(request.getParameter("enrollYear"+ids[i]));
		      		     
		      	 stuarchivesinfo.setUpdatorId(request.getParameter("updatorId"+ids[i]));
		      	 stuarchivesinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		      		      	 
			     stuarchivesinfo.setId(ids[i]);

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stuarchivesinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			flag=false;
			request.setAttribute("msg","1");
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
				stuinfo.setStuName(request.getParameter("hstuName"));
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
			 
			 List stuarriveinfoList=null;
			 String classNo="";			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
	         if(managerclassList!=null&&managerclassList.size()>0){
	        	 
				 classNo=(String)managerclassList.get(0);
			 
			     String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.hasArchives as hasArchives,ci.otherFiles as otherFiles,ci.hasStuarchive as hasStuarchive,ci.hasLeagueFile as hasLeagueFile,ci.hasRegform as hasRegform,ci.ifSubmitted as ifSubmitted,ci.archiveSubmit as archiveSubmit,ci.memo as memo,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stuarchivesinfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId";
			 
			    if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				    sqlstring=sqlstring+" and ci.enrollNo like '%"+request.getParameter("henrollNo")+"%'";
			 
			    if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				    sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			    if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				   sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
						
			    if(request.getParameter("hmajorin")!=null&&request.getParameter("hmajorin").length()!=0)
				   sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"'";
			 
			    if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				   sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			    if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			       sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
			 			 
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
				 
				 request.setAttribute("stuinfo",stuinfo);
				 request.setAttribute("checkinlist",resultList);
				 request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				 //System.out.println("find success");
				 return mapping.findForward("findlist");				 
			 }
			 
			 else
				 return mapping.findForward("findlist"); 
			
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
			 
			 //指定班级的新生档案袋信息列表,classNo要从session中取得
			 List stucheckininfoList=null;
             String classNo="";			 
			 Account manager=(Account)session.getAttribute("accountPerson");	            
	         String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
	         List managerclassList=checkinmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and m.managerNo='"+managerNo+"'");
	         if(managerclassList!=null&&managerclassList.size()>0){
				 classNo=(String)managerclassList.get(0);
	             stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.hasArchives as hasArchives,ci.otherFiles as otherFiles,ci.hasStuarchive as hasStuarchive,ci.hasLeagueFile as hasLeagueFile,ci.hasRegform as hasRegform,ci.ifSubmitted as ifSubmitted,ci.archiveSubmit as archiveSubmit,ci.memo as memo,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stuarchivesinfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.classNo='"+classNo+"'");
	         }         
			 			 
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 //生源地
				 List areaList=getfromProvinceList();
				 if(areaList!=null&&areaList.size()>0)
					 request.setAttribute("arealist",areaList);
	             //专业
				List majorList=getmajorList();
				if(majorList!=null&&majorList.size()>0)
					request.setAttribute("majorinlist",majorList); 
				 request.setAttribute("checkinlist",stucheckininfoList);
				 request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 System.out.println("list success");
				 return mapping.findForward("archiveslist");
			 }
			 else
				 return mapping.findForward("archiveslist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	//入库登记
	
	public ActionForward allupdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		Stuarchivesinfo stuarchivesinfo = (Stuarchivesinfo)aform.get("stuarchivesinfo");
        
		try {
			 
			 stuarchivesinfo.setHasArchives(request.getParameter("hasArchives"+request.getParameter("updateid")));
	         stuarchivesinfo.setHasStuarchive(request.getParameter("hasStuarchive"+request.getParameter("updateid")));
	       	 stuarchivesinfo.setHasLeagueFile(request.getParameter("hasLeagueFile"+request.getParameter("updateid")));
	       	 stuarchivesinfo.setHasRegform(request.getParameter("hasRegform"+request.getParameter("updateid")));
	       	 
	     	 stuarchivesinfo.setIfSubmitted(request.getParameter("ifSubmitted"+request.getParameter("updateid")));
	         stuarchivesinfo.setArchiveSubmit(request.getParameter("archiveSubmit"+request.getParameter("updateid")));

			 
	      	 stuarchivesinfo.setOtherFiles(request.getParameter("otherFiles"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setMemo(request.getParameter("memo"+request.getParameter("updateid")));
	      		      	 
	      	 stuarchivesinfo.setStudentNo(request.getParameter("studentNo"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setEnrollNo(request.getParameter("enrollNo"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setEnrollYear(request.getParameter("enrollYear"+request.getParameter("updateid")));
	      		     
	      	 stuarchivesinfo.setUpdatorId(request.getParameter("updatorId"+request.getParameter("updateid")));
	      	 stuarchivesinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
	      		      	 
		     stuarchivesinfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stuarchivesinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 return mapping.findForward("success2");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			return allfind(mapping, form, request, response);
		}

	}
	
	public ActionForward allupdateall(ActionMapping mapping, ActionForm form,
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
		    Stuarchivesinfo stuarchivesinfo = new Stuarchivesinfo();
        
		    try {
			 
		    	 stuarchivesinfo.setHasArchives(request.getParameter("hasArchives"+ids[i]));
		         stuarchivesinfo.setHasStuarchive(request.getParameter("hasStuarchive"+ids[i]));
		       	 stuarchivesinfo.setHasLeagueFile(request.getParameter("hasLeagueFile"+ids[i]));
		       	 stuarchivesinfo.setHasRegform(request.getParameter("hasRegform"+ids[i]));
		       	 
		     	 stuarchivesinfo.setIfSubmitted(request.getParameter("ifSubmitted"+ids[i]));
		         stuarchivesinfo.setArchiveSubmit(request.getParameter("archiveSubmit"+ids[i]));

				 
		      	 stuarchivesinfo.setOtherFiles(request.getParameter("otherFiles"+ids[i]));
		      	 stuarchivesinfo.setMemo(request.getParameter("memo"+ids[i]));
		      		      	 
		      	 stuarchivesinfo.setStudentNo(request.getParameter("studentNo"+ids[i]));
		      	 stuarchivesinfo.setEnrollNo(request.getParameter("enrollNo"+ids[i]));
		      	 stuarchivesinfo.setEnrollYear(request.getParameter("enrollYear"+ids[i]));
		      		     
		      	 stuarchivesinfo.setUpdatorId(request.getParameter("updatorId"+ids[i]));
		      	 stuarchivesinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		      		      	 
			     stuarchivesinfo.setId(ids[i]);

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(stuarchivesinfo);
			 //System.out.println("update success");
			 request.setAttribute("msg","0");
			 flag=true;
			 
		    } catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
			request.setAttribute("msg","1");
			flag=false;
			return allfind(mapping, form, request, response);
		    }
		}
		if(flag)
		    return mapping.findForward("success2");
		else{
			request.setAttribute("msg","1");
		    return allfind(mapping, form, request, response);
		}

	}
	
	public ActionForward allfind(ActionMapping mapping, ActionForm form,
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
				stuinfo.setStuName(request.getParameter("hstuName"));
				stuinfo.setFromProvince(request.getParameter("hfromProvince"));
				 
				 String classNo=request.getParameter("hclassNo");
				
			 String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.birthday as birthday,s.fromProvince as fromProvince,c.classNo as classNo,ci.hasArchives as hasArchives,ci.otherFiles as otherFiles,ci.hasStuarchive as hasStuarchive,ci.hasLeagueFile as hasLeagueFile,ci.hasRegform as hasRegform,ci.ifSubmitted as ifSubmitted,ci.archiveSubmit as archiveSubmit,ci.memo as memo,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stuarchivesinfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality='CHN'";
			 
			 if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				 sqlstring=sqlstring+" and ci.enrollNo like '%"+request.getParameter("henrollNo")+"%'";
			 
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and ci.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
						 
			 if(request.getParameter("hgender")!=null&&request.getParameter("hgender").length()!=0)
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("hgender")+"'";
								 
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
			 
			 if(request.getParameter("hfromProvince")!=null&&request.getParameter("hfromProvince").length()!=0)
			     sqlstring=sqlstring+" and s.fromProvince='"+request.getParameter("hfromProvince")+"'";
			 			 
			 //sqlstring=sqlstring+" order by ci.studentNo";
			 
			 System.out.println(sqlstring);
			 
			 List stuarriveinfoList=checkinmanageservice.find(sqlstring);
			 
			 //生源地
			 List areaList=getfromProvinceList();
			 if(areaList!=null&&areaList.size()>0)
				 request.setAttribute("arealist",areaList);
             //专业
		     List majorList=getmajorList();
			 if(majorList!=null&&majorList.size()>0)
				 request.setAttribute("majorinlist",majorList); 
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){	
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("stuinfo",stuinfo);
					 request.setAttribute("classNo",classNo);
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				 } 				 
                 
				 System.out.println("find success");
				 return mapping.findForward("allfindlist");				 
			 }
			 
			 else
				 return mapping.findForward("allfindlist"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward alllist(ActionMapping mapping, ActionForm form,
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
			 
			 //List stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo,ci.hasArchives as hasArchives,ci.otherFiles as otherFiles,ci.hasStuarchive as hasStuarchive,ci.hasLeagueFile as hasLeagueFile,ci.hasRegform as hasRegform,ci.ifSubmitted as ifSubmitted,ci.archiveSubmit as archiveSubmit,ci.memo as memo,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stuarchivesinfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId");
             
			 //生源地
			 List areaList=getfromProvinceList();
			 if(areaList!=null&&areaList.size()>0)
				request.setAttribute("arealist",areaList);             
			 
			 //request.setAttribute("checkinlist",stucheckininfoList);
             System.out.println("list success");
			 return mapping.findForward("allarchiveslist");
			 
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

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
}