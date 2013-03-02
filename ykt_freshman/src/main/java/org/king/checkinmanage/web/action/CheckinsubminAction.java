package org.king.checkinmanage.web.action;

import java.io.OutputStream;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
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
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.CheckinSubmin;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.utils.DateUtil;

public class CheckinsubminAction extends BaseAction{

    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward tongjisubmit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		CheckinSubmin checkinsubmin = (CheckinSubmin)aform.get("checkinsubmin");
        
		try {
			checkinsubmin.setClassId(request.getParameter("updateclassNo"));
			checkinsubmin.setClassNo(request.getParameter("updateclassNo"));
			checkinsubmin.setIfSubmitted("1");
			checkinsubmin.setId(request.getParameter("updateid"));
 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if(checkinsubmin.getId()!=null&&checkinsubmin.getId().length()!=0&&!checkinsubmin.getId().equals("null"))
			     checkinmanageservice.update(checkinsubmin);
			 else
				 checkinmanageservice.save(checkinsubmin);
				 
				 
			 System.out.println("update success");
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward tongjibackto(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	        
		CheckinSubmin checkinsubmin = (CheckinSubmin)aform.get("checkinsubmin");
        
		try {
			checkinsubmin.setClassId(request.getParameter("updateclassNo"));
			checkinsubmin.setClassNo(request.getParameter("updateclassNo"));
			checkinsubmin.setIfSubmitted("0");
 		    checkinsubmin.setId(request.getParameter("updateid"));
			
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if(checkinsubmin.getId()!=null&&checkinsubmin.getId().length()!=0&&!checkinsubmin.getId().equals("null"))
			     checkinmanageservice.update(checkinsubmin);
			 System.out.println("update success");
			 return mapping.findForward("success");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward notcheckinstu(ActionMapping mapping, ActionForm form,
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
			 
			 String viewclassNo=request.getParameter("viewclassNo");
          	 //指定班级的新生报到信息列表
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' ";
			 
			 if(viewclassNo!=null&&!viewclassNo.equals("")&&!viewclassNo.equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+viewclassNo+"' ";			 
			 if(request.getParameter("gender")!=null&&!request.getParameter("gender").equals("")&&!request.getParameter("gender").equals("null"))
				 sqlstring=sqlstring+" and s.gender='"+request.getParameter("gender")+"' ";
			 if(request.getParameter("nationality")!=null&&request.getParameter("nationality").equals("1"))
				 sqlstring=sqlstring+" and s.nationality='CHN' ";
			 else if(request.getParameter("nationality")!=null&&request.getParameter("nationality").equals("2"))
				 sqlstring=sqlstring+" and s.nationality<>'CHN' ";
			 if(request.getParameter("hcollegeId")!=null&&!request.getParameter("hcollegeId").equals("")&&!request.getParameter("hcollegeId").equals("null"))
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"' ";
			 if(request.getParameter("hclassNo")!=null&&!request.getParameter("hclassNo").equals("")&&!request.getParameter("hclassNo").equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"' ";
			 
			 sqlstring=sqlstring+" order by ci.studentNo";
			 
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","1");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","notcheckinstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward askforlatestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
			 String viewclassNo=request.getParameter("viewclassNo");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' ";
          	 
			 if(viewclassNo!=null&&!viewclassNo.equals("")&&!viewclassNo.equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+viewclassNo+"' ";
			 if(request.getParameter("hcollegeId")!=null&&!request.getParameter("hcollegeId").equals("")&&!request.getParameter("hcollegeId").equals("null"))
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"' ";
			 if(request.getParameter("hclassNo")!=null&&!request.getParameter("hclassNo").equals("")&&!request.getParameter("hclassNo").equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"' ";
			 
			 sqlstring=sqlstring+" order by ci.studentNo";
			 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
				 
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","2");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","askforlatestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward askreservestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewclassNo=request.getParameter("viewclassNo");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' ";
			 
			 if(viewclassNo!=null&&!viewclassNo.equals("")&&!viewclassNo.equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+viewclassNo+"' ";
			 if(request.getParameter("hcollegeId")!=null&&!request.getParameter("hcollegeId").equals("")&&!request.getParameter("hcollegeId").equals("null"))
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"' ";
			 if(request.getParameter("hclassNo")!=null&&!request.getParameter("hclassNo").equals("")&&!request.getParameter("hclassNo").equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"' ";
			 
			 sqlstring=sqlstring+" order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				// System.out.println("list success");
				 request.setAttribute("htitle","3");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","askreservestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward noreasonstu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewclassNo=request.getParameter("viewclassNo");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' ";
			 
			 if(viewclassNo!=null&&!viewclassNo.equals("")&&!viewclassNo.equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+viewclassNo+"' ";
			 if(request.getParameter("hcollegeId")!=null&&!request.getParameter("hcollegeId").equals("")&&!request.getParameter("hcollegeId").equals("null"))
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"' ";
			 if(request.getParameter("hclassNo")!=null&&!request.getParameter("hclassNo").equals("")&&!request.getParameter("hclassNo").equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"' ";
			 
			 sqlstring=sqlstring+" order by ci.studentNo";
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","4");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","noreasonstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward donotcomestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
				
			 String viewclassNo=request.getParameter("viewclassNo");
			 String sqlstring="";
			 
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' ";
			 
			 if(viewclassNo!=null&&!viewclassNo.equals("")&&!viewclassNo.equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+viewclassNo+"' ";
			 if(request.getParameter("hcollegeId")!=null&&!request.getParameter("hcollegeId").equals("")&&!request.getParameter("hcollegeId").equals("null"))
				 sqlstring=sqlstring+" and c.yxCollege.collegeId='"+request.getParameter("hcollegeId")+"' ";
			 if(request.getParameter("hclassNo")!=null&&!request.getParameter("hclassNo").equals("")&&!request.getParameter("hclassNo").equals("null"))
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"' ";
			 
			 sqlstring=sqlstring+" order by ci.studentNo";			 
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","5");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","donotcomestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward notcomestu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		List stucheckininfoList=new ArrayList();
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 String order=request.getParameter("horder");
			 String odr="asc";
			 if(order!=null&&order.length()>0&&order.equals("d"))
			    odr="desc";
			 String orderby=request.getParameter("orderby");
			 
			 String sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,ci.reason as reason,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,s.fromProvince as fromProvince,c.classNo as classNo) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and (ci.reason='00' or ci.reason='02')";
			
			 if(orderby==null||orderby.length()==0)
            	 sqlstring=sqlstring+" order by ci.studentNo";
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
                 sqlstring=sqlstring+" order by ci.studentNo"+" "+odr;             
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("gender"))
                 sqlstring=sqlstring+" order by s.gender"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("department"))
                 sqlstring=sqlstring+" order by s.department"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("majorin"))
                 sqlstring=sqlstring+" order by s.majorin"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("fromProvince"))
                 sqlstring=sqlstring+" order by s.fromProvince"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("classNo"))
                 sqlstring=sqlstring+" order by c.classNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("reason"))
                 sqlstring=sqlstring+" order by ci.reason"+" "+odr;
			 
          	 //明确不来的新生列表
			 List stuinfoList=checkinmanageservice.find(sqlstring);
			 
				request.setAttribute("listcount", new Integer(stuinfoList.size()));
			 
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
    		         Collections.sort(stuinfoList, comp1);
    			 else
    				 Collections.sort(stuinfoList, comp2);
    		     
             }
			
			 sqlstring="select new Map(s.id as id,s.studentNo as studentNo,d.location as location,d.dormitory as dorm,d.roomNumber as room) from Studentmodel s,Dormitorymodel d where s.dormId=d.dormitoryId";
	            
	         List dorminfoList=checkinmanageservice.find(sqlstring);
	         
             if(stuinfoList!=null&&stuinfoList.size()!=0){  
				 
                for(int i=0;i<stuinfoList.size();i++){
					 
					 Map m=(Map)stuinfoList.get(i);
					 String sno=(String)m.get("studentNo");
				
				     if(dorminfoList!=null&&dorminfoList.size()>0){
					     int j=0;
					     for(j=0;j<dorminfoList.size();j++){
						     Map uhm=(Map)dorminfoList.get(j);
						     if(((String)uhm.get("studentNo")).equals(sno)){
							     m.put("location",uhm.get("location"));		
							     m.put("dorm",uhm.get("dorm"));
							     m.put("room",uhm.get("room"));
							     break;
						     }
					     }
                         if(j==dorminfoList.size()||j>dorminfoList.size()){
                        	 m.put("location",null);		
						     m.put("dorm",null);
						     m.put("room","");

					    }
				    }
				    else{//无新生有宿舍
				    	m.put("location",null);		
					    m.put("dorm",null);
					    m.put("room","");
				    }
				 			 
				  stucheckininfoList.add(m);
				 }
             }
             
			 if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 ChangeDormValue(stucheckininfoList);
				 
				 if(orderby!=null&&orderby.length()>0&&orderby.equals("locationName")){
		             	Comparator comp1 = new Comparator() { 
		    				 public int compare(Object o1, Object o2){ 
		    				 Map m1 = (Map)o1; 
		    				 Map m2 = (Map)o2; 
		    				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		    				 String collegeName1 = (String)m1.get("locationName"); 
		   				     String collegeName2 = (String)m2.get("locationName");      				

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
		       				String collegeName1 = (String)m1.get("locationName"); 
		       				String collegeName2 = (String)m2.get("locationName");
		       				
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
		    		         Collections.sort(stucheckininfoList, comp1);
		    			 else
		    				 Collections.sort(stucheckininfoList, comp2);
		    		     
		             }
				 
				 if(orderby!=null&&orderby.length()>0&&orderby.equals("dormitoryName")){
		             	Comparator comp1 = new Comparator() { 
		    				 public int compare(Object o1, Object o2){ 
		    				 Map m1 = (Map)o1; 
		    				 Map m2 = (Map)o2; 
		    				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		    				 String collegeName1 = (String)m1.get("dormitoryName"); 
		   				     String collegeName2 = (String)m2.get("dormitoryName");      				

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
		       				String collegeName1 = (String)m1.get("dormitoryName"); 
		       				String collegeName2 = (String)m2.get("dormitoryName");
		       				
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
		    		         Collections.sort(stucheckininfoList, comp1);
		    			 else
		    				 Collections.sort(stucheckininfoList, comp2);
		    		     
		             }
				 
				 if(orderby!=null&&orderby.length()>0&&orderby.equals("room")){
		             	Comparator comp1 = new Comparator() { 
		    				 public int compare(Object o1, Object o2){ 
		    				 Map m1 = (Map)o1; 
		    				 Map m2 = (Map)o2; 
		    				 //System.out.println("m1.collegeName="+m1.get("collegeName")+",m2.collegeName="+m2.get("collegeName")); 
		    				 String collegeName1 = (String)m1.get("room"); 
		   				     String collegeName2 = (String)m2.get("room");      				

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
		       				String collegeName1 = (String)m1.get("room"); 
		       				String collegeName2 = (String)m2.get("room");
		       				
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
		    		         Collections.sort(stucheckininfoList, comp1);
		    			 else
		    				 Collections.sort(stucheckininfoList, comp2);
		    		     
		             }
				 
				 request.setAttribute("checkinlist",stucheckininfoList);
				 request.setAttribute("order",order);
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);				 
                   //生源地
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangefromProvinceValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 
					 try{
							/*-----------------------------------------------------------------------*/
					        // Create the Excel File
					 		//FileOutputStream fileOut = new FileOutputStream("c:/新生入学信息一览.xls");
							String	fileName="notcomestulist.xls";
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
							columnNames.add(3,"生源地");
							columnNames.add(4,"录取院系");
							columnNames.add(5,"录取专业");
							columnNames.add(6,"班级");						
							columnNames.add(7,"校区");
							columnNames.add(8,"楼号");						
							columnNames.add(9,"宿舍号");
							columnNames.add(10,"未报到原因");
							
							// System.out.println(columnNames.size());
							for (int i=0; i<columnNames.size(); i++)
							{
								 HSSFCell cname=row.createCell((short)i);
								 cname.setCellStyle(cellHeadStyle);
								 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
								 cname.setCellValue((String)columnNames.get(i));
							}
							
							// Populate the Row Data to the SpreadSheet
							int rowCount = stucheckininfoList.size();
							// goal houses the number of cells in the target spreadsheet
							int goal = rowCount*columnNames.size();			
							
							//actual population of target spreadsheet
							int currentCell = 0;
							
							for (int i=0; i<rowCount; i++)
							{
								Map tableData = (Map)stucheckininfoList.get(i);
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
									ctitle.setCellValue((String)tableData.get("fromProvinceName"));
									
									ctitle=row.createCell((short)4);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("departmentName"));
									
									ctitle=row.createCell((short)5);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("majorinName"));
									
									ctitle=row.createCell((short)6);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("classNo"));				
									
									ctitle=row.createCell((short)7);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("locationName"));
									
									ctitle=row.createCell((short)8);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("dormitoryName"));
									
									ctitle=row.createCell((short)9);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("room"));
									
									ctitle=row.createCell((short)10);
									ctitle.setCellStyle(cellDataStyle);
									ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
									ctitle.setCellValue((String)tableData.get("reasonName"));
													
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
				 
					 return null;
				 }
				 else
				 return mapping.findForward("notcomestulist");
			 }
			 else
				 return mapping.findForward("notcomestulist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward reservestu(ActionMapping mapping, ActionForm form,
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
			 String viewclassNo=request.getParameter("viewclassNo");
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifReserve='1' and c.classNo='"+request.getParameter("viewclassNo")+"' order by ci.studentNo");
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 request.setAttribute("checkinlist",stucheckininfoList);
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				 //System.out.println("list success");
			     request.setAttribute("htitle","5");
			     request.setAttribute("viewclassNo",viewclassNo);
			     request.setAttribute("viewmajor","");
			     request.setAttribute("md","reservestu");
			     
			     if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward leaveschoolstu(ActionMapping mapping, ActionForm form,
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
			 String viewclassNo=request.getParameter("viewclassNo");
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and ci.ifLeaveSchool='1' and c.classNo='"+request.getParameter("viewclassNo")+"' order by ci.studentNo");
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 request.setAttribute("checkinlist",stucheckininfoList);
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","6");
				 request.setAttribute("viewclassNo",viewclassNo);
				 request.setAttribute("viewmajor","");
				 request.setAttribute("md","leaveschoolstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	
	//按专业查看报到统计
	
	public ActionForward mjnotcheckinstu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' ";
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
			 				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","1");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnotcheckinstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				    return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjaskforlatestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='01' ";
				 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","2");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjaskforlatestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjaskreservestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='02' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","3");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjaskreservestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjnoreasonstu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='03' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","4");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnoreasonstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjnotcomestu(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifCheckedin='0' and ci.reason='00' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","5");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnotcomestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjreservestu(ActionMapping mapping, ActionForm form,
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
			 
			 String viewmajor=request.getParameter("viewmajor");
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifReserve='1' and s.majorin='"+request.getParameter("viewmajor")+"' order by ci.studentNo");
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 request.setAttribute("checkinlist",stucheckininfoList);
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","5");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjreservestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjleaveschoolstu(ActionMapping mapping, ActionForm form,
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
			 String viewmajor=request.getParameter("viewmajor");
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find("select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.curYear='"+DateUtil.getNow("yyyy")+"' and ci.ifLeaveSchool='1' and s.majorin='"+request.getParameter("viewmajor")+"' order by ci.studentNo");
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 request.setAttribute("checkinlist",stucheckininfoList);
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","6");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjleaveschoolstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
//按专业查看留学生报到统计
	
	public ActionForward mjnotcheckinstuabroad(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' ";
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
			 				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","1");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnotcheckinstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				    return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjaskforlatestuabroad(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='01' ";
				 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","2");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjaskforlatestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjaskreservestuabroad(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='02' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                    //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","3");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjaskreservestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjnoreasonstuabroad(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='03' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","4");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnoreasonstu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward mjnotcomestuabroad(ActionMapping mapping, ActionForm form,
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
			 
//			起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 String viewmajor=request.getParameter("viewmajor");
			 String sqlstring="";
			 sqlstring="select new Map(ci.id as id,ci.studentNo as studentNo,ci.enrollNo as enrollNo,ci.enrollYear as enrollYear,s.stuName as stuName,s.gender as gender,s.nationality as nationality,s.department as department,s.majorin as majorin,c.classNo as classNo,ci.ifCheckedin as ifCheckedin,ci.reason as reason,ci.ifChecked as ifChecked,ci.ifReserve as ifReserve,ci.ifLeaveSchool as ifLeaveSchool,ci.ifGotMaterial as ifGotMaterial,ci.ifGotEcard as ifGotEcard,ci.ifGotStucard as ifGotStucard,ci.memo as memo,ci.ifSubmitted as ifSubmitted,ci.updatorId as updatorId,ci.updateTime as updateTime) from Stucheckininfo ci,Studentmodel s,Classmodel c where ci.studentNo=s.studentNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and s.nationality<>'CHN' and ci.ifCheckedin='0' and ci.reason='00' ";
			 
			 if(viewmajor!=null&&!viewmajor.equals("")&&!viewmajor.equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+viewmajor+"' ";
			 if(request.getParameter("hmajorin")!=null&&!request.getParameter("hmajorin").equals("")&&!request.getParameter("hmajorin").equals("null"))
				 sqlstring=sqlstring+" and s.majorin='"+request.getParameter("hmajorin")+"' ";
			 sqlstring=sqlstring+"  order by ci.studentNo";
			 
          	 //指定班级的新生报到信息列表
			 List stucheckininfoList=checkinmanageservice.find(sqlstring);
				 
			if(stucheckininfoList!=null&&stucheckininfoList.size()!=0){
				 ChangeDepartmentValue(stucheckininfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stucheckininfoList;
				 else if((Integer.parseInt(offset))<stucheckininfoList.size()||(Integer.parseInt(offset))==stucheckininfoList.size())
					 resultList=stucheckininfoList.subList((Integer.parseInt(offset)),stucheckininfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
				     request.setAttribute("checkinlist",resultList);
				     request.setAttribute("listcount",new Integer(stucheckininfoList.size()));
				 }
                   //专业
					List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
					if(majorList!=null&&majorList.size()>0)
						request.setAttribute("majorinlist",majorList);
//					国籍
					List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
					if(areaList!=null&&areaList.size()>0)
						request.setAttribute("arealist",areaList);
				 //System.out.println("list success");
				 request.setAttribute("htitle","5");
				 request.setAttribute("viewmajor",viewmajor);
				 request.setAttribute("viewclassNo","");
				 request.setAttribute("md","mjnotcomestu");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 ChangeGenderValue(stucheckininfoList);
					 ChangeMajorValue(stucheckininfoList);
					 ChangeCheckinValue(stucheckininfoList);
					 ChangeReasonValue(stucheckininfoList);
					 ChangeReserveValue(stucheckininfoList);
					 ChangeLeaveschoolValue(stucheckininfoList);
					 
					 ExportList(stucheckininfoList,response);
					 return null;
				 }
				 else
				 return mapping.findForward("studentlist");
			 }
			 else
				 return mapping.findForward("studentlist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
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
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=11 order by di.id.dictValue");
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
	
	public void ChangeNationalityValue(List list){
		List areaList=getNationalityList();
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 if(n.get("nationality")!=null){
			   String mj=((String)n.get("nationality")).trim();
			   for(int k=0;k<areaList.size();k++){
				 Map n1=(Map)areaList.get(k);
				 String mj1=((String)n1.get("dictValue")).trim();
				 if(mj.equals(mj1)){
					 n.put("nationalityName",((String)n1.get("dictCaption")).trim());
				 }
			   }
			 }
			 else
				 n.put("nationalityName","");
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
	
	public void ChangeReasonValue(List list){
		String[][] ar={{"01","请假"},{"02","申请保留入学资格"},{"03","不明原因"},{"00","不来"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("reason")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("reasonName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeReserveValue(List list){
		String[][] ar={{"0",""},{"1","保留入学资格"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifReserve")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifReserveName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeLeaveschoolValue(List list){
		String[][] ar={{"0",""},{"1","放弃入学资格"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifLeaveSchool")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifLeaveSchoolName",ar[k][1]);
				 }
			 }
			 
		 }
		
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
		return majorList;
	}
	
	public List getfromProvinceList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=10 order by di.id.dictValue");
		return majorList;
	}
	
	public List getNationalityList(){
		List areaList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=12 order by di.id.dictValue");
		return areaList;
	}
				
	public List getlocationList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=6 order by di.id.dictValue");
		return majorList;
	}
	
	public List getdormitoryList(){
		List majorList=checkinmanageservice.find("select new Map(di.id.dictNo as dictNo,di.id.dictValue as dictValue,di.dictCaption as dictCaption) from Dictionary di where di.id.dictNo=7 order by di.id.dictValue");
		return majorList;
	}
	
	public void ExportList(List list,HttpServletResponse response){
		try{
			ChangeNationalityValue(list);
		/*-----------------------------------------------------------------------*/
        // Create the Excel File
 		//FileOutputStream fileOut = new FileOutputStream("c:/新生入学信息一览.xls");
		String	fileName="stunamelist.xls";
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
		columnNames.add(3,"国籍");
		columnNames.add(4,"录取院系");
		columnNames.add(5,"录取专业");
		columnNames.add(6,"班级");						
		columnNames.add(7,"报到状态");
		columnNames.add(8,"未报到原因");						
		columnNames.add(9,"特殊情况");
		
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
				ctitle.setCellValue((String)tableData.get("nationalityName"));
				
				ctitle=row.createCell((short)4);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("departmentName"));
				
				ctitle=row.createCell((short)5);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("majorinName"));
				
				ctitle=row.createCell((short)6);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("classNo"));				
				
				ctitle=row.createCell((short)7);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("ifCheckedinName"));
				
				ctitle=row.createCell((short)8);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("reasonName"));
				
				ctitle=row.createCell((short)9);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue((String)tableData.get("ifReserveName")+(String)tableData.get("ifLeaveSchoolName"));
								
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
