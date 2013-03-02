/**
 * 
 */
package org.king.rcvmanage.web.action;

import java.io.FileOutputStream;
import java.io.OutputStream;
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
import org.king.classmanage.domain.MenuTime;
import org.king.classmanage.domain.Studentmodel;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;
import org.king.rcvmanage.helper.StuarriveinfoHelper;
import org.king.rcvmanage.service.RcvmanageService;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;


/**
 * @author jackey
 *
 */
public class RcvmanageAction extends BaseAction{
	
	
	private RcvmanageService rcvmanageservice;
	
	public void setRcvmanageService(RcvmanageService rcvmanageservice) {
		this.rcvmanageservice = rcvmanageservice;
	}

	public ActionForward add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
        aform.set("stuName",request.getParameter("stuName"));
		Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
        String msg="";
		try {
			
			if(request.getParameter("companyNum")!=null&&request.getParameter("companyNum").length()!=0)
				stuarriveinfo.setCompanyNum(new Integer(Integer.parseInt(request.getParameter("companyNum"))));
			else
				stuarriveinfo.setCompanyNum(new Integer(0));
			
			if(request.getParameter("stuarriveinfo.trainNo")==null||request.getParameter("stuarriveinfo.trainNo").length()==0)
				stuarriveinfo.setTrainNo("");
			
			if(request.getParameter("stuarriveinfo.trainRoomNo")==null||request.getParameter("stuarriveinfo.trainRoomNo").length()==0)
				stuarriveinfo.setTrainRoomNo("");
			
			if(request.getParameter("stuarriveinfo.ifDeleted")==null||request.getParameter("stuarriveinfo.ifDeleted").length()==0||request.getParameter("stuarriveinfo.arrivePlace").equals("02")||request.getParameter("stuarriveinfo.arrivePlace").equals("04")||request.getParameter("stuarriveinfo.arrivePlace").equals("05")||request.getParameter("stuarriveinfo.arrivePlace").equals("06"))
				stuarriveinfo.setIfDeleted("0");//作为扩充字段，表示抵沪地点，1-上海站；2-上海南站；3-虹桥机场；4-浦东机场
			
			if(request.getParameter("stuarriveinfo.ifNeedHelp")==null||request.getParameter("stuarriveinfo.ifNeedHelp").length()==0)
				stuarriveinfo.setIfNeedHelp("0");
			
			if(request.getParameter("stuarriveinfo.ifNeedBus")==null||request.getParameter("stuarriveinfo.ifNeedBus").length()==0)
				stuarriveinfo.setIfNeedBus("0");
			
			stuarriveinfo.setArriveDate(new Date(Integer.parseInt(request.getParameter("arriveDate").substring(0,4))-1900,Integer.parseInt(request.getParameter("arriveDate").substring(5,7))-1,Integer.parseInt(request.getParameter("arriveDate").substring(8))));
			//System.out.println(stuarriveinfo.getArriveDate().toString());
			stuarriveinfo.setArriveTime(new Time(Integer.parseInt(request.getParameter("arriveTime").substring(0,2)),Integer.parseInt(request.getParameter("arriveTime").substring(3,5)),0));
			//System.out.println(stuarriveinfo.getArriveTime().toString());
			stuarriveinfo.setCreateTime(new Timestamp(System.currentTimeMillis()));
		    //System.out.println(new java.util.Date(System.currentTimeMillis()).toString());
		    stuarriveinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));		    
		
 		// 数据库验证
		
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 if (isTokenValid(request, true)) {
			     rcvmanageservice.save(stuarriveinfo);
			     //System.out.println("add success");
			     msg="0";
			 }
			 else{
				 msg="9";
				 saveToken(request);
			 }
			 	 
			 request.setAttribute("msg",msg);
			 return mapping.findForward("editsuccess");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("add error");
			return mapping.findForward("faile");
		}

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
        aform.set("stuName",request.getParameter("stuName"));
		Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
        String msg="";
		try {
			 
			if(request.getParameter("companyNum")!=null&&request.getParameter("companyNum").length()!=0)
				stuarriveinfo.setCompanyNum(new Integer(Integer.parseInt(request.getParameter("companyNum"))));
			else
				stuarriveinfo.setCompanyNum(new Integer(0));
			
			if(request.getParameter("stuarriveinfo.trainNo")==null||request.getParameter("stuarriveinfo.trainNo").length()==0)
				stuarriveinfo.setTrainNo("");
			
			if(request.getParameter("stuarriveinfo.trainRoomNo")==null||request.getParameter("stuarriveinfo.trainRoomNo").length()==0)
				stuarriveinfo.setTrainRoomNo("");
			
			if(request.getParameter("stuarriveinfo.ifDeleted")==null||request.getParameter("stuarriveinfo.ifDeleted").length()==0||request.getParameter("stuarriveinfo.arrivePlace").equals("02")||request.getParameter("stuarriveinfo.arrivePlace").equals("04")||request.getParameter("stuarriveinfo.arrivePlace").equals("05")||request.getParameter("stuarriveinfo.arrivePlace").equals("06"))
				stuarriveinfo.setIfDeleted("0");//作为扩充字段，表示抵沪地点，1-上海站；2-上海南站；3-虹桥机场；4-浦东机场
			
			if(request.getParameter("stuarriveinfo.ifNeedHelp")==null||request.getParameter("stuarriveinfo.ifNeedHelp").length()==0)
				stuarriveinfo.setIfNeedHelp("0");
			
			if(request.getParameter("stuarriveinfo.ifNeedBus")==null||request.getParameter("stuarriveinfo.ifNeedBus").length()==0)
				stuarriveinfo.setIfNeedBus("0");
			
	       	 stuarriveinfo.setArriveDate(new Date(Integer.parseInt(request.getParameter("arriveDate").substring(0,4))-1900,Integer.parseInt(request.getParameter("arriveDate").substring(5,7))-1,Integer.parseInt(request.getParameter("arriveDate").substring(8))));
	       	 System.out.println(stuarriveinfo.getArriveDate().toString());
	       	 stuarriveinfo.setArriveTime(new Time(Integer.parseInt(request.getParameter("arriveTime").substring(0,2)),Integer.parseInt(request.getParameter("arriveTime").substring(3,5)),0));
	      	 System.out.println(stuarriveinfo.getArriveTime().toString());
		     stuarriveinfo.setCreateTime(new Timestamp(Integer.parseInt(request.getParameter("createTime").substring(0,4))-1900,Integer.parseInt(request.getParameter("createTime").substring(5,7))-1,Integer.parseInt(request.getParameter("createTime").substring(8,10)),Integer.parseInt(request.getParameter("createTime").substring(11,13)),Integer.parseInt(request.getParameter("createTime").substring(14,16)),Integer.parseInt(request.getParameter("createTime").substring(17,19)),0));
		     stuarriveinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));		     
				
		     stuarriveinfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 rcvmanageservice.update(stuarriveinfo);
			 //System.out.println("update success");
			 msg="0";
			 request.setAttribute("msg",msg);
			 return mapping.findForward("editsuccess");
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("update error");
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
       
		ActionMessages errors = new ActionMessages();
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		String msg="";
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 Stuarriveinfo stuarriveinfo = findbyId(ids[i]);
		    
 		         // 数据库验证
		   
			     if(rcvmanageservice==null)
				     System.out.println("service is null");
			     if(stuarriveinfo!=null){
			          rcvmanageservice.delete(stuarriveinfo);
			          msg="d0";
			     }
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     msg="d1";
			     return mapping.findForward("faile");
		    }
		}
		request.setAttribute("msg",msg);
		return mapping.findForward("success");
	}
	
	public ActionForward view(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		
		String id=request.getParameter("updateid");
		
			 try {
				 	    
 		         // 数据库验证
		   
			     if(rcvmanageservice==null)
				     System.out.println("service is null");
			     List stuarriveinfoList=rcvmanageservice.find("select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s where si.enrollNo=s.enterenceNo and si.id='"+id+"'");
			     
			     /*
			     List sl=new ArrayList();
			     for(int i=0;i<stuarriveinfoList.size();i++){
			    	 Stuarriveinfo si=(Stuarriveinfo)stuarriveinfoList.get(i);
			    	 StuarriveinfoHelper stuarriveinfohelper=new StuarriveinfoHelper(si);
			    	 stuarriveinfohelper.setArriveDate(si.getArriveDate());
			    	 stuarriveinfohelper.setArriveTime(si.getArriveTime());
			    	 stuarriveinfohelper.setCompanyNum(si.getCompanyNum());
			    	 stuarriveinfohelper.setCreateTime(si.getCreateTime());
			    	 stuarriveinfohelper.setUpdateTime(si.getUpdateTime());
			    	 
			    	 sl.add(stuarriveinfohelper);
			     }
			     request.setAttribute("arrivelist",sl);
			     */
			     if(stuarriveinfoList!=null&&stuarriveinfoList.size()>0)
			          request.setAttribute("arrivelist",stuarriveinfoList);
				 //System.out.println("view success");
				 return mapping.findForward("stuarriveinfoview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
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
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			    DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
				//Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");				
				
				Studentmodel stuinfo=new Studentmodel();
				stuinfo.setEnterenceNo(request.getParameter("henrollNo"));
				stuinfo.setStudentNo(request.getParameter("hstudentNo"));				
				stuinfo.setStuName(request.getParameter("hstuName"));
				
				List rList=new ArrayList();
				List resultList=new ArrayList();
				
			    //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			 //String sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId";
			
			 String sqlstring="select new Map(s.enterenceNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.enterenceNo!=null and s.enterenceNo!='' and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'";
			 
			 if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
				 sqlstring=sqlstring+" and s.enterenceNo like '%"+request.getParameter("henrollNo")+"%'";
			 
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";			 
			 
			 sqlstring=sqlstring+" order by s.studentNo";
			 
			 List stuinfoList=rcvmanageservice.find(sqlstring);
			 
			 sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.ifDeleted as ifDeleted,si.trainNo as trainNo,si.tempconcact as tempconcact,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
						 
			 /*
			 if(request.getParameter("stuarriveinfo.arriveDate")!=null&&request.getParameter("stuarriveinfo.arriveDate").length()!=0&&!request.getParameter("stuarriveinfo.arriveDate").equals("1900-01-01"))
				 sqlstring=sqlstring+" and si.arriveDate='"+request.getParameter("stuarriveinfo.arriveDate")+"'";
						
			 if(request.getParameter("stuarriveinfo.arriveTime")!=null&&request.getParameter("stuarriveinfo.arriveTime").length()!=0&&!request.getParameter("stuarriveinfo.arriveTime").equals("00:00:01"))
				 sqlstring=sqlstring+" and si.arriveTime='"+request.getParameter("stuarriveinfo.arriveTime")+"'";
			 
			 if(request.getParameter("stuarriveinfo.arrivePlace")!=null&&request.getParameter("stuarriveinfo.arrivePlace").length()!=0)
				 sqlstring=sqlstring+" and si.arrivePlace='"+request.getParameter("stuarriveinfo.arrivePlace")+"'";
			 
			 if(request.getParameter("stuarriveinfo.trainNo")!=null&&request.getParameter("stuarriveinfo.trainNo").length()!=0)
				 sqlstring=sqlstring+" and si.trainNo='"+request.getParameter("stuarriveinfo.trainNo")+"'";
			 		
			 sqlstring=sqlstring+" order by si.updateTime";
			 //System.out.println(sqlstring);
			  
			  */
			 
			 List stuarriveinfoList=rcvmanageservice.find(sqlstring);	
			 
			 if(stuinfoList!=null&&stuinfoList.size()>0){
			 
			   if(stuarriveinfoList!=null&&stuarriveinfoList.size()>0){			    
				 
				  for(int i=0;i<stuinfoList.size();i++){
					 Map m=(Map)stuinfoList.get(i);
					 String eno="";
					 if(m.get("enrollNo")!=null){
					     eno=((String)m.get("enrollNo")).trim();
					 }
					 
					 int j=0;
					 for(j=0;j<stuarriveinfoList.size();j++){
						 Map m1=(Map)stuarriveinfoList.get(j);
						 String eno1=((String)m1.get("enrollNo")).trim();
						 if(eno.equals(eno1)){
							 m.put("id",m1.get("id"));
							 m.put("arriveDate",m1.get("arriveDate"));
							 m.put("arriveTime",m1.get("arriveTime"));
							 m.put("arrivePlace",m1.get("arrivePlace"));
							 m.put("ifDeleted",m1.get("ifDeleted"));
							 m.put("trainNo",m1.get("trainNo"));
							 m.put("tempconcact",m1.get("tempconcact"));
							 m.put("updateTime",m1.get("updateTime"));
							 break;
						 }
							 
					 }
					 if(j==stuarriveinfoList.size()||j>stuarriveinfoList.size()){
						 m.put("id",null);
						 m.put("arriveDate",null);
						 m.put("arriveTime",null);
						 m.put("arrivePlace",null);
						 m.put("ifDeleted",null);
						 m.put("trainNo",null);
						 m.put("tempconcact",null);
						 m.put("updateTime",null);						 
					 }	
					 rList.add(m);
				  }				 	
			   }
			   else
				   rList=stuinfoList;
			   
			   if(rList!=null&&rList.size()>0){
			   
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=rList;
				 else if((Integer.parseInt(offset))<rList.size()||(Integer.parseInt(offset))==rList.size())
					 resultList=rList.subList((Integer.parseInt(offset)),rList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 //request.setAttribute("arriveform",stuarriveinfo);
					 request.setAttribute("stuinfo",stuinfo);
					 
				     request.setAttribute("arrivelist",resultList);
				     request.setAttribute("listcount",new Integer(rList.size()));
				 }				 				 
			   
			   }
			   return mapping.findForward("findlist");
		  }
		
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}
		 return mapping.findForward("findlist"); 

	}
	
	public ActionForward findall(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			    DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
				//Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");				
				
				Studentmodel stuinfo=new Studentmodel();
				if(request.getParameter("stuarriveinfo.enrollNo")!=null&&request.getParameter("stuarriveinfo.enrollNo").length()!=0)
					stuinfo.setEnterenceNo(request.getParameter("stuarriveinfo.enrollNo"));
				else if(request.getParameter("henrollNo")!=null&&request.getParameter("henrollNo").length()!=0)
					stuinfo.setEnterenceNo(request.getParameter("henrollNo"));
				
				stuinfo.setStudentNo(request.getParameter("studentNo"));				
				stuinfo.setStuName(request.getParameter("stuName"));
				
				request.setAttribute("stuinfo",stuinfo);
				request.setAttribute("enrollNo",stuinfo.getEnterenceNo());
				
				List rList=new ArrayList();
				List resultList=new ArrayList();
				
			    //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			 //String sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId";
			
			 
			 
			 String sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.ifDeleted as ifDeleted,si.trainNo as trainNo,si.tempconcact as tempconcact,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(stuinfo.getEnterenceNo()!=null&&stuinfo.getEnterenceNo().length()!=0)
				 sqlstring=sqlstring+" and si.enrollNo='"+stuinfo.getEnterenceNo()+"'";			 
			 
//			 if(request.getParameter("stuarriveinfo.arriveDate")!=null&&request.getParameter("stuarriveinfo.arriveDate").length()!=0&&!request.getParameter("stuarriveinfo.arriveDate").equals("1900-01-01"))
//				 sqlstring=sqlstring+" and si.arriveDate='"+request.getParameter("stuarriveinfo.arriveDate")+"'";
//						
//			 if(request.getParameter("stuarriveinfo.arriveTime")!=null&&request.getParameter("stuarriveinfo.arriveTime").length()!=0&&!request.getParameter("stuarriveinfo.arriveTime").equals("00:00:01"))
//				 sqlstring=sqlstring+" and si.arriveTime='"+request.getParameter("stuarriveinfo.arriveTime")+"'";
//			 
//			 if(request.getParameter("stuarriveinfo.arrivePlace")!=null&&request.getParameter("stuarriveinfo.arrivePlace").length()!=0)
//				 sqlstring=sqlstring+" and si.arrivePlace='"+request.getParameter("stuarriveinfo.arrivePlace")+"'";
//			 
//			 if(request.getParameter("stuarriveinfo.trainNo")!=null&&request.getParameter("stuarriveinfo.trainNo").length()!=0)
//				 sqlstring=sqlstring+" and si.trainNo='"+request.getParameter("stuarriveinfo.trainNo")+"'";
//			 
//			 
//			 sqlstring=sqlstring+" order by si.updateTime";
		 
			 List curarriveinfoList=rcvmanageservice.find(sqlstring);	
			 
			 if(curarriveinfoList!=null&&curarriveinfoList.size()>0){//把当前修改的抵沪记录放在结果集的第一条	    
				  Map curm=(Map)curarriveinfoList.get(0);
				  rList.add(curm);	 	
			   }
			 
			 sqlstring="select new Map(s.enterenceNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName) from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and s.enterenceNo!=null and s.enterenceNo!='' and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(stuinfo.getEnterenceNo()!=null&&stuinfo.getEnterenceNo().length()!=0)
				 sqlstring=sqlstring+" and s.enterenceNo!='"+stuinfo.getEnterenceNo()+"'";
			 
			 sqlstring=sqlstring+" order by s.studentNo";
			 
			 List stuinfoList=rcvmanageservice.find(sqlstring);
			 
			 sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.ifDeleted as ifDeleted,si.trainNo as trainNo,si.tempconcact as tempconcact,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			
			 List stuarriveinfoList=rcvmanageservice.find(sqlstring);	
			 
			 if(stuinfoList!=null&&stuinfoList.size()>0){
			 
			   if(stuarriveinfoList!=null&&stuarriveinfoList.size()>0){			    
				 
				  for(int i=0;i<stuinfoList.size();i++){
					 Map m=(Map)stuinfoList.get(i);
					 String eno="";
					 if(m.get("enrollNo")!=null){
					     eno=((String)m.get("enrollNo")).trim();
					 }
					 
					 int j=0;
					 for(j=0;j<stuarriveinfoList.size();j++){
						 Map m1=(Map)stuarriveinfoList.get(j);
						 String eno1=((String)m1.get("enrollNo")).trim();
						 if(eno.equals(eno1)){
							 m.put("id",m1.get("id"));
							 m.put("arriveDate",m1.get("arriveDate"));
							 m.put("arriveTime",m1.get("arriveTime"));
							 m.put("arrivePlace",m1.get("arrivePlace"));
							 m.put("ifDeleted",m1.get("ifDeleted"));
							 m.put("trainNo",m1.get("trainNo"));
							 m.put("tempconcact",m1.get("tempconcact"));
							 m.put("updateTime",m1.get("updateTime"));
							 break;
						 }
							 
					 }
					 if(j==stuarriveinfoList.size()||j>stuarriveinfoList.size()){
						 m.put("id",null);
						 m.put("arriveDate",null);
						 m.put("arriveTime",null);
						 m.put("arrivePlace",null);
						 m.put("ifDeleted",null);
						 m.put("trainNo",null);
						 m.put("tempconcact",null);
						 m.put("updateTime",null);						 
					 }	
					 rList.add(m);
				  }				 	
			   }
			   else{
				   for(int k=0;k<stuinfoList.size();k++){
					   Map m=(Map)stuinfoList.get(k);
					   m.put("id",null);
					   m.put("arriveDate",null);
					   m.put("arriveTime",null);
					   m.put("arrivePlace",null);
					   m.put("ifDeleted",null);
					   m.put("trainNo",null);
					   m.put("tempconcact",null);
					   m.put("updateTime",null);
					   rList.add(m);
				   }
			   }
				   
			 }
			 			   
			   
			   if(rList!=null&&rList.size()>0){
			   
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=rList;
				 else if((Integer.parseInt(offset))<rList.size()||(Integer.parseInt(offset))==rList.size())
					 resultList=rList.subList((Integer.parseInt(offset)),rList.size());
				 
				 if(resultList!=null&&resultList.size()>0){					
				     request.setAttribute("arrivelist",resultList);
				     request.setAttribute("listcount",new Integer(rList.size()));
				 }				 				 
			   
			   }
			   return mapping.findForward("findlistall");
		 
		
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}
		
	}
	
	public Stuarriveinfo findbyId(String id)
			throws Exception {
				
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 Stuarriveinfo stuarriveinfo=rcvmanageservice.findbyId(id);
			 			 
			 System.out.println("find by id success");
			 return stuarriveinfo;
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find by id error");
		}
		return null;

	}
	
	public ActionForward findstuinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();
		
		String id=request.getParameter("updateid");
        String msg="";
 		// 数据库验证
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			 request.setAttribute("curYear",DateUtil.getNow("yyyy"));
						 		 
			 List hisList=rcvmanageservice.find("select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s where si.enrollNo=s.enterenceNo and si.id='"+id+"'");
			 
			 if(hisList!=null&&hisList.size()>0){//该新生的抵沪信息已登记过，直接进入修改页面
				 request.setAttribute("arrivelist",hisList);
				 //System.out.println("find 4 update success");
				 msg="2";
				 request.setAttribute("msg",msg);
				 return mapping.findForward("stuarriveinfoedit"); 
			 }
			 
			 List stuinfoList=rcvmanageservice.find("select new Map(s.enterenceNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName) from Studentmodel s where s.enterenceNo='"+id+"'");
			 
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 request.setAttribute("stuinfo",stuinfoList);
			 	 //System.out.println("find student success");
				 msg="1";
				 request.setAttribute("msg",msg);
				 saveToken(request);
			     return mapping.findForward("stuarriveinfo");
			 }
			 else{				 
				 msg="0";
				 request.setAttribute("msg",msg);
				 return mapping.findForward("stuarriveinfo");
			 }
		} catch (Exception e) {
			e.printStackTrace();
			//System.out.println("find error");
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
		
		ActionMessages errors = new ActionMessages();
		
		
		//String[] userid=request.getParameterValues("cb");
		String updateid=request.getParameter("updateid");

 		// 数据库验证
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 List stuarriveinfoList=rcvmanageservice.find("select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and si.id='"+updateid+"'");
			 
			 request.setAttribute("curYear",DateUtil.getNow("yyyy"));
			if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){
				 request.setAttribute("arrivelist",stuarriveinfoList);				 
				 //System.out.println(((Map)stuarriveinfoList.get(0)).get("ifDeleted"));
				 return mapping.findForward("stuarriveinfoedit"); 
			 }
			 else
				 return mapping.findForward("stuarriveinfoedit"); 
			 
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find 4 update error");
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
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
               //起始页
				String offset = "0";
				
			 List stuarriveinfoList=rcvmanageservice.find("select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and s.enrollYear='"+DateUtil.getNow("yyyy")+"' order by si.updateTime desc");
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()>0){				 
				 //request.setAttribute("arrivelist",stuarriveinfoList);				 
				 //request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));			 
				 
				 //System.out.println("list success");
				 return mapping.findForward("rcvmanagelist");
			 }
			 else
				 return mapping.findForward("rcvmanagelist");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		

	}
	
	public ActionForward jiezhanlist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		return mapping.findForward("jiezhanlist");
		
		
		
	}
	
	public ActionForward jiezhanfind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();		
		
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			    DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
				Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
				String studentNo=request.getParameter("hstudentNo");
				String classNo=request.getParameter("hclassNo");
				
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
			 
			 String sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,upper(si.trainNo) as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' ";
			 
			 if(request.getParameter("stuarriveinfo.enrollNo")!=null&&request.getParameter("stuarriveinfo.enrollNo").length()!=0)
				 sqlstring=sqlstring+" and si.enrollNo like '%"+request.getParameter("stuarriveinfo.enrollNo")+"%'";
			 
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
			 
			 if(request.getParameter("hclassNo")!=null&&request.getParameter("hclassNo").length()!=0)
				 sqlstring=sqlstring+" and c.classNo='"+request.getParameter("hclassNo")+"'";
						 
			 if(request.getParameter("stuarriveinfo.arriveDate")!=null&&request.getParameter("stuarriveinfo.arriveDate").length()!=0&&!request.getParameter("stuarriveinfo.arriveDate").equals("1900-01-01"))
				 sqlstring=sqlstring+" and si.arriveDate='"+request.getParameter("stuarriveinfo.arriveDate")+"'";
						
			 if(request.getParameter("stuarriveinfo.arriveTime")!=null&&request.getParameter("stuarriveinfo.arriveTime").length()!=0&&!request.getParameter("stuarriveinfo.arriveTime").equals("00:00:01"))
				 sqlstring=sqlstring+" and si.arriveTime='"+request.getParameter("stuarriveinfo.arriveTime")+"'";
			 
			 if(request.getParameter("stuarriveinfo.arrivePlace")!=null&&request.getParameter("stuarriveinfo.arrivePlace").length()!=0)
				 sqlstring=sqlstring+" and si.arrivePlace='"+request.getParameter("stuarriveinfo.arrivePlace")+"'";
			 
			 if(request.getParameter("stuarriveinfo.trainNo")!=null&&request.getParameter("stuarriveinfo.trainNo").length()!=0)
				 sqlstring=sqlstring+" and upper(si.trainNo) like '%"+request.getParameter("stuarriveinfo.trainNo").toUpperCase()+"%'";
			 
			 if(orderby==null||orderby.length()==0)
			     sqlstring=sqlstring+" order by si.arriveDate,si.arriveTime";
			 else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
                 sqlstring=sqlstring+" order by s.studentNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("enrollNo"))
                 sqlstring=sqlstring+" order by si.enrollNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("classNo"))
                 sqlstring=sqlstring+" order by c.classNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arriveDate"))
                 sqlstring=sqlstring+" order by si.arriveDate"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arriveTime"))
                 sqlstring=sqlstring+" order by si.arriveTime"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifDeleted"))
                 sqlstring=sqlstring+" order by si.ifDeleted"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arrivePlace"))
                 sqlstring=sqlstring+" order by si.arrivePlace"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("trainNo"))
                 sqlstring=sqlstring+" order by si.trainNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("companyNum"))
                 sqlstring=sqlstring+" order by si.companyNum"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifNeedBus"))
                 sqlstring=sqlstring+" order by si.ifNeedBus"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("tempconcact"))
                 sqlstring=sqlstring+" order by si.tempconcact"+" "+odr;
			 					 
			 List stuarriveinfoList=null;
			 
			 if(sqlstring.length()>0)
				 stuarriveinfoList=rcvmanageservice.find(sqlstring);
			 			
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
    		         Collections.sort(stuarriveinfoList, comp1);
    			 else
    				 Collections.sort(stuarriveinfoList, comp2);
    		     
             }
			 
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){
				 ChangeifDeletedValue(stuarriveinfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){					 
					 request.setAttribute("arriveform",stuarriveinfo);
					 request.setAttribute("studentNo",studentNo);
					 request.setAttribute("classNo",classNo);
				     request.setAttribute("jzlist",resultList);
				     request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				     request.setAttribute("order",order);
				 }
				 //System.out.println("jiezhan list success");
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					    ChangePlaceValue(stuarriveinfoList);
					    ChangeNeedbusValue(stuarriveinfoList);
		                // Create the Excel File
					    String	fileName="jiezhan.xls";
							
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
						columnNames.add(0,"抵沪日期");
						columnNames.add(1,"抵沪时间");
						columnNames.add(2,"抵沪方式");
						columnNames.add(3,"抵沪地点");
						columnNames.add(4,"火车车次");
						columnNames.add(5,"学号");
						columnNames.add(6,"录取通知书号");
						columnNames.add(7,"姓名");
						columnNames.add(8,"班级");						
						columnNames.add(9,"陪同人数");
						columnNames.add(10,"坐校车");
						columnNames.add(11,"联系方式");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount =stuarriveinfoList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)stuarriveinfoList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue(((Date)tableData.get("arriveDate")).toString());
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue(((Time)tableData.get("arriveTime")).toString());
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("arrivePlaceName"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("ifDeletedName"));	
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("trainNo"));								
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("enrollNo"));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("classNo"));																
								
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("arrivePlace").equals("01"))
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("companyNum")).toString()));
								else
									ctitle.setCellValue("");
								
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("ifNeedBusName"));
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("tempconcact"));	
															
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
				 else
				      return mapping.findForward("jiezhanlist");
			 }
			 else
				 return mapping.findForward("jiezhanlist");
		 			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action jiezhan list error");
			return mapping.findForward("faile");
		}

	}
	
	//辅导员查看班级接站信息
	public ActionForward classjiezhanlist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		return mapping.findForward("classjiezhanlist");
		
		
		
	}
	
	public ActionForward classjiezhanfind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();		
		
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			    DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
				Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
				String studentNo=request.getParameter("hstudentNo");
				String stuName=request.getParameter("hstuName");
				
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
				
			List stuarriveinfoList=null;
			String classNo="";			 
			Account manager=(Account)session.getAttribute("accountPerson");	            
		    String managerNo=manager.getPerson().getPersonCode();	//获取登录者的学工号
		    List managerclassList=rcvmanageservice.find("select c.classNo as classNo from Managermodel m,Classmodel c,Classmanager cm,Managermanagerrole mmr where mmr.id.managerId=m.managerId and mmr.id.roleId='21' and m.managerId=cm.id.managerId and c.classId=cm.id.classId and m.available='1' and c.curYear='"+DateUtil.getNow("yyyy")+"' and m.managerNo='"+managerNo+"'");
		    
		    if(managerclassList!=null&&managerclassList.size()>0){		        	 

             classNo=(String)managerclassList.get(0);
			 
			 String sqlstring="select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,c.classNo as classNo,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,upper(si.trainNo) as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.classNo='"+classNo+"'";
			 
			 if(request.getParameter("stuarriveinfo.enrollNo")!=null&&request.getParameter("stuarriveinfo.enrollNo").length()!=0)
				 sqlstring=sqlstring+" and si.enrollNo like '%"+request.getParameter("stuarriveinfo.enrollNo")+"%'";
			 
			 if(request.getParameter("hstudentNo")!=null&&request.getParameter("hstudentNo").length()!=0)
				 sqlstring=sqlstring+" and s.studentNo like '%"+request.getParameter("hstudentNo")+"%'";
			 
			 if(request.getParameter("hstuName")!=null&&request.getParameter("hstuName").length()!=0)
				 sqlstring=sqlstring+" and s.stuName like '%"+request.getParameter("hstuName")+"%'";
						 
			 if(request.getParameter("stuarriveinfo.arriveDate")!=null&&request.getParameter("stuarriveinfo.arriveDate").length()!=0&&!request.getParameter("stuarriveinfo.arriveDate").equals("1900-01-01"))
				 sqlstring=sqlstring+" and si.arriveDate='"+request.getParameter("stuarriveinfo.arriveDate")+"'";
						
			 if(request.getParameter("stuarriveinfo.arriveTime")!=null&&request.getParameter("stuarriveinfo.arriveTime").length()!=0&&!request.getParameter("stuarriveinfo.arriveTime").equals("00:00:01"))
				 sqlstring=sqlstring+" and si.arriveTime='"+request.getParameter("stuarriveinfo.arriveTime")+"'";
			 
			 if(request.getParameter("stuarriveinfo.arrivePlace")!=null&&request.getParameter("stuarriveinfo.arrivePlace").length()!=0)
				 sqlstring=sqlstring+" and si.arrivePlace='"+request.getParameter("stuarriveinfo.arrivePlace")+"'";
			 
			 if(request.getParameter("stuarriveinfo.trainNo")!=null&&request.getParameter("stuarriveinfo.trainNo").length()!=0)
				 sqlstring=sqlstring+" and upper(si.trainNo) like '%"+request.getParameter("stuarriveinfo.trainNo").toUpperCase()+"%'";
			 
			 if(orderby==null||orderby.length()==0)
			     sqlstring=sqlstring+" order by si.arriveDate,si.arriveTime";
			 else if(orderby!=null&&orderby.length()>0&&orderby.equals("studentNo"))
                 sqlstring=sqlstring+" order by s.studentNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("enrollNo"))
                 sqlstring=sqlstring+" order by si.enrollNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("classNo"))
                 sqlstring=sqlstring+" order by c.classNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arriveDate"))
                 sqlstring=sqlstring+" order by si.arriveDate"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arriveTime"))
                 sqlstring=sqlstring+" order by si.arriveTime"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifDeleted"))
                 sqlstring=sqlstring+" order by si.ifDeleted"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("arrivePlace"))
                 sqlstring=sqlstring+" order by si.arrivePlace"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("trainNo"))
                 sqlstring=sqlstring+" order by si.trainNo"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("companyNum"))
                 sqlstring=sqlstring+" order by si.companyNum"+" "+odr;
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("ifNeedBus"))
                 sqlstring=sqlstring+" order by si.ifNeedBus"+" "+odr;	
             else if(orderby!=null&&orderby.length()>0&&orderby.equals("tempconcact"))
                 sqlstring=sqlstring+" order by si.tempconcact"+" "+odr;
			 
			 stuarriveinfoList=rcvmanageservice.find(sqlstring);
			 
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
	    		         Collections.sort(stuarriveinfoList, comp1);
	    			 else
	    				 Collections.sort(stuarriveinfoList, comp2);
	    		     
	             }
			 
		   }
		    
			 if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0){
				 ChangeifDeletedValue(stuarriveinfoList);
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=stuarriveinfoList;
				 else if((Integer.parseInt(offset))<stuarriveinfoList.size()||(Integer.parseInt(offset))==stuarriveinfoList.size())
					 resultList=stuarriveinfoList.subList((Integer.parseInt(offset)),stuarriveinfoList.size());
				 
				 if(resultList!=null&&resultList.size()>0){					 
					 request.setAttribute("arriveform",stuarriveinfo);
					 request.setAttribute("studentNo",studentNo);
					 request.setAttribute("stuName",stuName);
				     request.setAttribute("jzlist",resultList);
				     request.setAttribute("listcount",new Integer(stuarriveinfoList.size()));
				     request.setAttribute("order",order);
				 }
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					    ChangePlaceValue(stuarriveinfoList);
					    ChangeNeedbusValue(stuarriveinfoList);
		                // Create the Excel File
					    String	fileName="classjiezhan.xls";
							
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
						columnNames.add(0,"抵沪日期");
						columnNames.add(1,"抵沪时间");
						columnNames.add(2,"抵沪方式");
						columnNames.add(3,"抵沪地点");
						columnNames.add(4,"火车车次");
						columnNames.add(5,"学号");
						columnNames.add(6,"录取通知书号");
						columnNames.add(7,"姓名");
						columnNames.add(8,"班级");						
						columnNames.add(9,"陪同人数");
						columnNames.add(10,"坐校车");
						columnNames.add(11,"联系方式");
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount =stuarriveinfoList.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)stuarriveinfoList.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue(((Date)tableData.get("arriveDate")).toString());
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue(((Time)tableData.get("arriveTime")).toString());
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("arrivePlaceName"));
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("ifDeletedName"));
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("trainNo"));								
								
								ctitle=row.createCell((short)5);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("studentNo"));
								
								
								ctitle=row.createCell((short)6);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("enrollNo"));
								
								ctitle=row.createCell((short)7);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("stuName"));
								
								ctitle=row.createCell((short)8);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue((String)tableData.get("classNo"));
																
								ctitle=row.createCell((short)9);
								ctitle.setCellStyle(cellDataStyle);
								if(tableData.get("arrivePlace").equals("01"))
								    ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("companyNum")).toString()));
								else
									ctitle.setCellValue("");
									
								ctitle=row.createCell((short)10);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("ifNeedBusName"));	
								
								ctitle=row.createCell((short)11);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
								ctitle.setCellValue((String)tableData.get("tempconcact"));
															
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
				 else
				     return mapping.findForward("classjiezhanlist");
			 }
			 else
				 return mapping.findForward("classjiezhanlist");
		 			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action jiezhan list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward tongjilist(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
				
 		// 数据库验证
		try {
		  if(rcvmanageservice==null)
				 System.out.println("service is null");
			 			 
		  if(request.getParameter("startTime")!=null&&request.getParameter("startTime")!=""&&request.getParameter("startTime").length()!=0){
			 
		      String arriveDate=request.getParameter("arriveDate");
			  String startTime=request.getParameter("startTime");
			  String endTime=request.getParameter("endTime");
			  String ostartTime=request.getParameter("startTime");
			  String oendTime=request.getParameter("endTime");
			  int otimePeriod=Integer.parseInt(request.getParameter("timePeriod"));
			  
			  String arrivePlace=request.getParameter("arrivePlace");
			  String arriveWay="";
			  String arrivePot="";
			  
			  if(arrivePlace!=null&&arrivePlace.length()>0){
				  arriveWay=arrivePlace.substring(0,2);
				  arrivePot=arrivePlace.substring(2);
			  }
			 
			 int timePeriod=Integer.parseInt(request.getParameter("timePeriod"))*60;

			 List sl=new ArrayList();
			 
			 SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			 
			 startTime=arriveDate+" "+startTime;//拼成日期时间格式
			 endTime=arriveDate+" "+endTime;//拼成日期时间格式
			 
			 java.util.Date sd=sdf.parse(startTime);
			 java.util.Date ed=sdf.parse(endTime);
			 
			 while(sd.before(ed)){
				 
				 String newTime=getNewTime(startTime, timePeriod);	//加上间隔时间后得到的新日期时间		 
	
				 //给定时段需要乘坐校车的新生人数
				 String sqlstring1="select new Map('"+arriveDate+"' as arriveDate,'"+arrivePlace+"' as arrivePlace,'"+startTime.substring(11)+"' as beginTime,'"+newTime.substring(11)+"' as finishTime"+",count(si.enrollNo) as stuNum) from Stuarriveinfo si where si.arriveDate='"+request.getParameter("arriveDate")+"' and si.arrivePlace='"+arriveWay+"' and (si.arriveTime between '"+startTime.substring(11)+"' and '"+newTime.substring(11)+"' and si.arriveTime!= '"+newTime.substring(11)+"') and si.ifNeedBus='1' ";
			     if(arrivePot.length()>0)
			    	 sqlstring1=sqlstring1+" and si.ifDeleted='"+arrivePot+"'";
			     
				 List stuarriveinfoList1=rcvmanageservice.find(sqlstring1);
			     
			     if(stuarriveinfoList1!=null&&stuarriveinfoList1.size()!=0&&stuarriveinfoList1.get(0)!=null){
			    	 
			    	 Map m=(Map)stuarriveinfoList1.get(0);
			    	 //给定时段的陪同人员总数
			         String sqlstring2="select new Map('"+arriveDate+"' as arriveDate,'"+arrivePlace+"' as arrivePlace,'"+startTime.substring(11)+"' as beginTime,'"+newTime.substring(11)+"' as finishTime"+",sum(si.companyNum) as companyNum) from Stuarriveinfo si where si.arriveDate='"+request.getParameter("arriveDate")+"' and si.arrivePlace='"+arriveWay+"' and (si.arriveTime between '"+startTime.substring(11)+"' and '"+newTime.substring(11)+"' and si.arriveTime!= '"+newTime.substring(11)+"') and si.ifNeedBus='1' ";
			         if(arrivePot.length()>0)
				    	 sqlstring2=sqlstring2+" and si.ifDeleted='"+arrivePot+"'";
			         
			         List stuarriveinfoList2=rcvmanageservice.find(sqlstring2);
			         if(stuarriveinfoList2!=null&&stuarriveinfoList2.size()!=0&&stuarriveinfoList2.get(0)!=null){
			        	 
			        	 Map m2=(Map)stuarriveinfoList2.get(0);
			        	 if(m2.get("companyNum")!=null)
			        	      m.put("companyNum",m2.get("companyNum"));//合并到一个Map对象中
			        	 else
			        		 m.put("companyNum",new Integer(0));
			        	 
			        	 int n1=((Integer)m.get("stuNum")).intValue();
			        	 int n2=((Integer)m.get("companyNum")).intValue();
			        	 n1=n1+n2;
			        	 m.put("totalNum",new Integer(n1));//总人数
			        	 
			         }
			         sl.add(m);
			     }			 
			     
			     startTime=newTime;
			     sd=sdf.parse(newTime);
			 			 
			 }
			 
			 if(sl!=null&&sl.size()!=0){
				 request.setAttribute("tjlist",sl);
				 request.setAttribute("arriveDate",arriveDate);
				 request.setAttribute("arrivePlace",arrivePlace);
				 request.setAttribute("startTime",ostartTime);
				 request.setAttribute("endTime",oendTime);
				 request.setAttribute("timePeriod",new Integer(otimePeriod));
				 
				 if(request.getParameter("doexl")!=null&&request.getParameter("doexl").length()>0&&request.getParameter("doexl").equals("1")){
					 //导出excel
					 /*-----------------------------------------------------------------------*/
					    
		                // Create the Excel File
					    String	fileName="arrivetongji.xls";
							
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
						columnNames.add(0,"开始时间");
						columnNames.add(1,"结束时间");
						columnNames.add(2,"到站新生人数");
						columnNames.add(3,"陪同人员数");
						columnNames.add(4,"总人数");
						
						// System.out.println(columnNames.size());
						for (int i=0; i<columnNames.size(); i++)
						{
							 HSSFCell cname=row.createCell((short)i);
							 cname.setCellStyle(cellHeadStyle);
							 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
							 cname.setCellValue((String)columnNames.get(i));
						}
						
						// Populate the Row Data to the SpreadSheet
						int rowCount =sl.size();
						// goal houses the number of cells in the target spreadsheet
						int goal = rowCount*columnNames.size();			
						
						//actual population of target spreadsheet
						int currentCell = 0;
						
						for (int i=0; i<rowCount; i++)
						{
							Map tableData = (Map)sl.get(i);
							// create row in spreadsheet
							row = sheet1.createRow((short)(i+1));
							
								// populate the spreadsheet with the cell						
								HSSFCell ctitle=row.createCell((short)0);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue((String)tableData.get("beginTime"));
								
								ctitle=row.createCell((short)1);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue((String)tableData.get("finishTime"));
								
								ctitle=row.createCell((short)2);
								ctitle.setCellStyle(cellDataStyle);								
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("stuNum")).toString()));								
								
								ctitle=row.createCell((short)3);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("companyNum")).toString()));
								
								
								ctitle=row.createCell((short)4);
								ctitle.setCellStyle(cellDataStyle);
								ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("totalNum")).toString()));
															
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
				     return mapping.findForward("tongjilist");
			 }
			 else{
				 request.setAttribute("msg","0");
				 return mapping.findForward("tongjilist");
			 } 
	  }	
	  else
			return mapping.findForward("tongjilist");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action tongji list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward dhfstongji(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stuNumList=new ArrayList();
		List stuarriveList=new ArrayList();
		List s1=new ArrayList();
		
		int totalNum=0;
		int arriveNum=0;
		
		String[] dhfs={"01","02","03","04","05","06"};
		String[] dhdd={"1","2","3","4"};
		
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");	
			 
			 for(int i=0;i<dhfs.length;i++){
			 
			 String sqlstring="select new Map('"+dhfs[i]+"' as arrivePlace,count(si.enrollNo) as stuNum) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and si.arrivePlace='"+dhfs[i]+"')";
		     List stuarriveinfoList=rcvmanageservice.find(sqlstring);
		      if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0&&stuarriveinfoList.get(0)!=null){
		    	 Map m=(Map)stuarriveinfoList.get(0);  
		    	 s1.add(m);
		      }
			 
			 }
			 
			 stuNumList=rcvmanageservice.find("select distinct s.studentNo from Studentmodel s,Classmodel c where s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			 stuarriveList=rcvmanageservice.find("select distinct si.enrollNo from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"'");
			 if(s1!=null&&s1.size()!=0){
				 request.setAttribute("tjlist",s1);					
			 }
			 if(stuNumList!=null)
				totalNum= stuNumList.size();
			 
			 if(stuarriveList!=null)
				arriveNum= stuarriveList.size();
			 
			 request.setAttribute("notdjNum",(new Integer(totalNum-arriveNum)));
			 			 
			 for(int i=0;i<dhdd.length;i++){
			   String sqlstring="select new Map('"+dhdd[i]+"' as ifDeleted,count(si.enrollNo) as stuNum) from Stuarriveinfo si,Studentmodel s,Classmodel c where si.enrollNo=s.enterenceNo and s.yxClass.classId=c.classId and c.yxCollege.yxSchool.schoolId='0001' and c.curYear='"+DateUtil.getNow("yyyy")+"' and si.ifDeleted='"+dhdd[i]+"')";
		       List stuarriveinfoList=rcvmanageservice.find(sqlstring);
		       
		       if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0&&stuarriveinfoList.get(0)!=null){
			    	 Map m=(Map)stuarriveinfoList.get(0);
			    	 if(m.get("ifDeleted").equals("1"))
			    		 request.setAttribute("d1",m.get("stuNum"));
			    	 else if(m.get("ifDeleted").equals("2"))
			    		 request.setAttribute("d2",m.get("stuNum"));
			    	 else if(m.get("ifDeleted").equals("3"))
			    		 request.setAttribute("d3",m.get("stuNum"));
			    	 else if(m.get("ifDeleted").equals("4"))
			    		 request.setAttribute("d4",m.get("stuNum"));
			      }
			 }
			 			 
			 return mapping.findForward("dhfstongji");
			 
		}catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
	public ActionForward dhfsexcel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
		List stuNumList=new ArrayList();
		List stuarriveList=new ArrayList();
		List s1=new ArrayList();
		
		int totalNum=0;
		int arriveNum=0;
		
		String[] dhfs={"01","02","03","04","05","06"};
		
		try {
			 if(rcvmanageservice==null)
				 System.out.println("service is null");	
			 
			 for(int i=0;i<dhfs.length;i++){
			 
			 String sqlstring="select new Map('"+dhfs[i]+"' as arrivePlace,count(si.enrollNo) as stuNum) from Stuarriveinfo si where si.arrivePlace='"+dhfs[i]+"')";
		     List stuarriveinfoList=rcvmanageservice.find(sqlstring);
		      if(stuarriveinfoList!=null&&stuarriveinfoList.size()!=0&&stuarriveinfoList.get(0)!=null){
		    	 Map m=(Map)stuarriveinfoList.get(0);  
		    	 s1.add(m);
		      }
			 
			 }
			 
			 stuNumList=rcvmanageservice.find("select distinct s.studentNo from Studentmodel s");
			 stuarriveList=rcvmanageservice.find("select distinct si.enrollNo from Stuarriveinfo si");
			 if(s1!=null&&s1.size()!=0){
				 request.setAttribute("tjlist",s1);					
			 }
			 if(stuNumList!=null)
				totalNum= stuNumList.size();
			 
			 if(stuarriveList!=null)
				arriveNum= stuarriveList.size();
			 
			 request.setAttribute("notdjNum",(new Integer(totalNum-arriveNum)));
			 
			 /*-----------------------------------------------------------------------*/
                // Create the Excel File
		 		FileOutputStream fileOut = new FileOutputStream("c:/抵沪方式统计.xls");
					
				// Create the Sheet with the name of the Table
				HSSFWorkbook wb = new HSSFWorkbook();
				
                //设置显示的字体以及相关的样式
		 		HSSFFont font = wb.createFont();
		 		    font.setFontHeightInPoints((short)8);
		 		    font.setFontName("宋体");
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
				columnNames.add(0,"抵沪方式");
				columnNames.add(1,"人数");				
				// System.out.println(columnNames.size());
				for (int i=0; i<columnNames.size(); i++)
				{
					 HSSFCell cname=row.createCell((short)i);
					 cname.setCellStyle(cellHeadStyle);
					 cname.setEncoding(HSSFCell.ENCODING_UTF_16);
					 cname.setCellValue((String)columnNames.get(i));
				}
				ChangePlaceValue(s1);
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
						ctitle.setCellValue((String)tableData.get("arrivePlaceName"));
						
						ctitle=row.createCell((short)1);
						ctitle.setCellStyle(cellDataStyle);
						ctitle.setCellValue(Double.parseDouble(((Integer)tableData.get("stuNum")).toString()));
						
						//System.out.println(columnData);
						currentCell++;

				}			
				// clean up resources
			   	wb.write(fileOut);
		 	 	fileOut.close();
		    /*-----------------------------------------------------------------------*/ 
			
			 return mapping.findForward("dhfsexcel");
		}catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}
		
	}
	
	public static String getNewTime(String st, int interval){
		try{
			
			SimpleDateFormat sdf=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			java.util.Date d=sdf.parse(st);
			Calendar calendar = Calendar.getInstance();
			calendar.setTimeInMillis(d.getTime());
			calendar.add(Calendar.SECOND, interval);
			return sdf.format(calendar.getTime());
		} catch (Exception e) {
			return st;
		}		
	  }
	
	//新生填写抵沪信息
	public ActionForward load4stuadd(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			String timespan="";
			timespan=rcvmanageservice.checkTimeUp("7005");
			if(!timespan.equals("")){
				request.setAttribute("timespan",timespan);
				return mapping.findForward("timeup");
			}
			
			Account freshmen=(Account)session.getAttribute("accountPerson");
            
            String id=freshmen.getPerson().getPersonCode();	//获取登录新生的学号
            
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 
			 request.setAttribute("curYear",DateUtil.getNow("yyyy"));
						 		 
			 List hisList=rcvmanageservice.find("select new Map(si.id as id,si.enrollNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName,si.arriveDate as arriveDate,si.arriveTime as arriveTime,si.arrivePlace as arrivePlace,si.trainNo as trainNo,si.trainRoomNo as trainRoomNo,si.companyNum as companyNum,si.ifDeleted as ifDeleted,si.ifNeedHelp as ifNeedHelp,si.ifNeedBus as ifNeedBus,si.tempconcact as tempconcact,si.memo as memo,si.creatorId as creatorId,si.createTime as createTime,si.updatorId as updatorId,si.updateTime as updateTime) from Stuarriveinfo si,Studentmodel s where si.enrollNo=s.enterenceNo and s.studentNo='"+id+"'");
			 
			 if(hisList!=null&&hisList.size()>0){//该新生的抵沪信息已登记过，直接进入修改页面
				 request.setAttribute("arrivelist",hisList);
				 System.out.println("find 4 update success");
				 return mapping.findForward("arriveinfoedit"); 
			 }
			 
			 List stuinfoList=rcvmanageservice.find("select new Map(s.enterenceNo as enrollNo,s.studentNo as studentNo,s.stuName as stuName) from Studentmodel s where s.studentNo='"+id+"'");
			 
			 if(stuinfoList!=null&&stuinfoList.size()!=0){
				 request.setAttribute("stuinfo",stuinfoList);
			 	 //System.out.println("find student success");
			 	 saveToken(request);
			 	 return mapping.findForward("arriveinfo");
			 }
			 else
				 return mapping.findForward("arriveinfo");
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("begin add error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stuadd(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
        aform.set("stuName",request.getParameter("stuName"));
		Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
        String msg="";
		try {
			
			if(request.getParameter("companyNum")!=null&&request.getParameter("companyNum").length()!=0)
				stuarriveinfo.setCompanyNum(new Integer(Integer.parseInt(request.getParameter("companyNum"))));
			else
				stuarriveinfo.setCompanyNum(new Integer(0));
			
			if(request.getParameter("stuarriveinfo.trainNo")==null||request.getParameter("stuarriveinfo.trainNo").length()==0)
				stuarriveinfo.setTrainNo("");
			
			if(request.getParameter("stuarriveinfo.trainRoomNo")==null||request.getParameter("stuarriveinfo.trainRoomNo").length()==0)
				stuarriveinfo.setTrainRoomNo("");
			
			if(request.getParameter("stuarriveinfo.ifDeleted")==null||request.getParameter("stuarriveinfo.ifDeleted").length()==0||request.getParameter("stuarriveinfo.arrivePlace").equals("02")||request.getParameter("stuarriveinfo.arrivePlace").equals("04")||request.getParameter("stuarriveinfo.arrivePlace").equals("05")||request.getParameter("stuarriveinfo.arrivePlace").equals("06"))
				stuarriveinfo.setIfDeleted("0");//作为扩充字段，表示抵沪地点，1-上海站；2-上海南站；3-虹桥机场；4-浦东机场
			
			if(request.getParameter("stuarriveinfo.ifNeedHelp")==null||request.getParameter("stuarriveinfo.ifNeedHelp").length()==0)
				stuarriveinfo.setIfNeedHelp("0");
			
			if(request.getParameter("stuarriveinfo.ifNeedBus")==null||request.getParameter("stuarriveinfo.ifNeedBus").length()==0)
				stuarriveinfo.setIfNeedBus("0");
			   
			stuarriveinfo.setArriveDate(new Date(Integer.parseInt(request.getParameter("arriveDate").substring(0,4))-1900,Integer.parseInt(request.getParameter("arriveDate").substring(5,7))-1,Integer.parseInt(request.getParameter("arriveDate").substring(8))));
			System.out.println(stuarriveinfo.getArriveDate().toString());
			stuarriveinfo.setArriveTime(new Time(Integer.parseInt(request.getParameter("arriveTime").substring(0,2)),Integer.parseInt(request.getParameter("arriveTime").substring(3,5)),0));
			System.out.println(stuarriveinfo.getArriveTime().toString());
			stuarriveinfo.setCreateTime(new Timestamp(System.currentTimeMillis()));
		    System.out.println(new java.util.Date(System.currentTimeMillis()).toString());
		    stuarriveinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));		   
		
 		// 数据库验证
		
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 if (isTokenValid(request, true)) {
			     rcvmanageservice.save(stuarriveinfo);
			     msg="1";
			 }
			 else{
				 msg="9";
				 saveToken(request);
			 }
			 request.setAttribute("msg",msg);
			 //System.out.println("add success");
			 return mapping.findForward("arriveinfogoto");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("add error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stuupdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
        aform.set("stuName",request.getParameter("stuName"));
		Stuarriveinfo stuarriveinfo = (Stuarriveinfo)aform.get("stuarriveinfo");
        String msg="";
		try {
			if(request.getParameter("companyNum")!=null&&request.getParameter("companyNum").length()!=0)
				stuarriveinfo.setCompanyNum(new Integer(Integer.parseInt(request.getParameter("companyNum"))));
			else
				stuarriveinfo.setCompanyNum(new Integer(0));
			
			if(request.getParameter("stuarriveinfo.trainNo")==null||request.getParameter("stuarriveinfo.trainNo").length()==0)
				stuarriveinfo.setTrainNo("");
			
			if(request.getParameter("stuarriveinfo.trainRoomNo")==null||request.getParameter("stuarriveinfo.trainRoomNo").length()==0)
				stuarriveinfo.setTrainRoomNo("");
			
			if(request.getParameter("stuarriveinfo.ifDeleted")==null||request.getParameter("stuarriveinfo.ifDeleted").length()==0||request.getParameter("stuarriveinfo.arrivePlace").equals("02")||request.getParameter("stuarriveinfo.arrivePlace").equals("04")||request.getParameter("stuarriveinfo.arrivePlace").equals("05")||request.getParameter("stuarriveinfo.arrivePlace").equals("06"))
				stuarriveinfo.setIfDeleted("0");//作为扩充字段，表示抵沪地点，1-上海站；2-上海南站；3-虹桥机场；4-浦东机场
			
			if(request.getParameter("stuarriveinfo.ifNeedHelp")==null||request.getParameter("stuarriveinfo.ifNeedHelp").length()==0)
				stuarriveinfo.setIfNeedHelp("0");
			
			if(request.getParameter("stuarriveinfo.ifNeedBus")==null||request.getParameter("stuarriveinfo.ifNeedBus").length()==0)
				stuarriveinfo.setIfNeedBus("0");			
			
	       	 stuarriveinfo.setArriveDate(new Date(Integer.parseInt(request.getParameter("arriveDate").substring(0,4))-1900,Integer.parseInt(request.getParameter("arriveDate").substring(5,7))-1,Integer.parseInt(request.getParameter("arriveDate").substring(8))));
	       	 System.out.println(stuarriveinfo.getArriveDate().toString());
	       	 stuarriveinfo.setArriveTime(new Time(Integer.parseInt(request.getParameter("arriveTime").substring(0,2)),Integer.parseInt(request.getParameter("arriveTime").substring(3,5)),0));
	      	 System.out.println(stuarriveinfo.getArriveTime().toString());
		     stuarriveinfo.setCreateTime(new Timestamp(Integer.parseInt(request.getParameter("createTime").substring(0,4))-1900,Integer.parseInt(request.getParameter("createTime").substring(5,7))-1,Integer.parseInt(request.getParameter("createTime").substring(8,10)),Integer.parseInt(request.getParameter("createTime").substring(11,13)),Integer.parseInt(request.getParameter("createTime").substring(14,16)),Integer.parseInt(request.getParameter("createTime").substring(17,19)),0));
		     stuarriveinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		     
				
		     stuarriveinfo.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(rcvmanageservice==null)
				 System.out.println("service is null");
			 rcvmanageservice.update(stuarriveinfo);
			 msg="2";
			 request.setAttribute("msg",msg);
			 return mapping.findForward("arriveinfogoto");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward studelete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		String msg="";
		 try {
		         String id=request.getParameter("updateid");
		
				 Stuarriveinfo stuarriveinfo = findbyId(id);
		    
 		         // 数据库验证
		   
			     if(rcvmanageservice==null)
				     System.out.println("service is null");
			     rcvmanageservice.delete(stuarriveinfo);
			     msg="3";
			     request.setAttribute("msg",msg);
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     return mapping.findForward("faile");
		    }
		
		return mapping.findForward("arriveinfogoto");
	}
	
	
	public void ChangePlaceValue(List list){
		String[][] ar={{"01","火车"},{"02","长途汽车"},{"03","飞机"},{"04","自驾车"},{"05","其他"},{"06","本市"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("arrivePlace")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("arrivePlaceName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeNeedbusValue(List list){
		String[][] ar={{"0","不需要"},{"1","需要"}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifNeedBus")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifNeedBusName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
	public void ChangeifDeletedValue(List list){
		String[][] ar={{"1","上海站"},{"2","上海南站"},{"3","虹桥机场"},{"4","浦东机场"},{"0",""}};
		
		for(int j=0;j<list.size();j++){
			 Map n=(Map)list.get(j);
			 String mj=((String)n.get("ifDeleted")).trim();
			 for(int k=0;k<ar.length;k++){				 
				 String mj1=ar[k][0];
				 if(mj.equals(mj1)){
					 n.put("ifDeletedName",ar[k][1]);
				 }
			 }
			 
		 }
		
	}
	
}

