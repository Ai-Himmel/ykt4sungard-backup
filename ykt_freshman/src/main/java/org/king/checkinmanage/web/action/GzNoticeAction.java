/**
 * 
 */
package org.king.checkinmanage.web.action;

import org.king.framework.web.action.BaseAction;

/**
 * @author jackey
 *
 */

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.sql.Time;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.sql.Date;
import java.sql.Clob;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;


public class GzNoticeAction  extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		//ActionMessages msg = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		Noticemodel notice = (Noticemodel)aform.get("notice");
		String msg="";
		try {
			
			if(request.getParameter("notice.noticeNo").length()==0)
			   notice.setNoticeNo("0002");
			
			notice.setCreateTime(new Timestamp(System.currentTimeMillis()));		    
		    notice.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		
 		// 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if (isTokenValid(request, true)) {				 
			     checkinmanageservice.save(notice);
			     msg="0";
			 }
			 else{
				 msg="9";
				 saveToken(request);
			 }
			 request.setAttribute("msg",msg);
			 return mapping.findForward("noticelistall");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("add error");
			request.setAttribute("msg","1");
			return load4add(mapping, form, request, response);
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
			 
			 //指定班级的新生报到信息列表,classNo要从session中取得
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni order by ni.updateTime desc");
			
			 if(noticeList!=null&&noticeList.size()!=0){
				 
                 List resultList=new ArrayList();
                 
				 if(noticeList.size()>5)
				     resultList=noticeList.subList(0,5);//只显示前5条记录
				 else
					 resultList=noticeList;
				 
				 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("noticelist",resultList);
				 
				 request.setAttribute("listcount",new Integer(resultList.size()));
				 
				 }
				 System.out.println("list success");
				 return mapping.findForward("success");
			 }
			 else
				 return mapping.findForward("success");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward load4add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 	 
			 //System.out.println("begin add success");
			 saveToken(request);
			 return mapping.findForward("notice");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("begin add error");
			return mapping.findForward("faile");
		}

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
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+id+"'");
			    
			     request.setAttribute("noticelist",noticeList);
				 System.out.println("view success");
				 return mapping.findForward("noticeview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
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
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+updateid+"'");
			    
		     request.setAttribute("noticelist",noticeList);
			 System.out.println("find 4 update success");
			 return mapping.findForward("noticeedit");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find 4 update error");
			return load4update(mapping, form, request, response);
		}

	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages msg = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		Noticemodel notice = (Noticemodel)aform.get("notice");
        
		try {
			if(request.getParameter("notice.noticeNo").length()==0)
			   notice.setNoticeNo("0002");
			 			 						 
			notice.setCreateTime(new Timestamp(Integer.parseInt(request.getParameter("createTime").substring(0,4))-1900,Integer.parseInt(request.getParameter("createTime").substring(5,7))-1,Integer.parseInt(request.getParameter("createTime").substring(8,10)),Integer.parseInt(request.getParameter("createTime").substring(11,13)),Integer.parseInt(request.getParameter("createTime").substring(14,16)),Integer.parseInt(request.getParameter("createTime").substring(17,19)),0));		    
		    notice.setUpdateTime(new Timestamp(System.currentTimeMillis()));
				
		    notice.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(notice);
			 System.out.println("update success");
			 request.setAttribute("msg","0");
			 
			 return mapping.findForward("noticelistall");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			request.setAttribute("msg","1");
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
		
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 Noticemodel notice = findbyId(ids[i]);
		    
 		         // 数据库验证
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     checkinmanageservice.delete(notice);
			     request.setAttribute("msg","d0");
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     request.setAttribute("msg","d1");
			     return mapping.findForward("faile");
		    }
		}
		return mapping.findForward("noticelist");
	}
	
	public  Noticemodel findbyId(String id)
	throws Exception {
		
       ActionMessages errors = new ActionMessages();

	
       try {
	      if(checkinmanageservice==null)
	     	 System.out.println("service is null");
	      Noticemodel notice=checkinmanageservice.findbyId(id);
	 			 
	      System.out.println("find by id success");
	      return notice;
      } catch (Exception e) {
	    e.printStackTrace();
	    System.out.println("find by id error");
      }
      return null;

      }
	
	public ActionForward find(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
        
		Noticemodel notice = (Noticemodel)aform.get("notice");
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.noticeNo='0002' ";
			 
//			 if(request.getParameter("notice.noticeNo")!=null&&request.getParameter("notice.noticeNo").length()!=0)
//				 sqlstring=sqlstring+" and ni.noticeNo like '%"+request.getParameter("notice.noticeNo")+"%'";
//			 
			 if(request.getParameter("notice.title")!=null&&request.getParameter("notice.title").length()!=0)
				 sqlstring=sqlstring+" and ni.title like '%"+request.getParameter("notice.title")+"%'";
 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("noticeform",notice);
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("success");				 
			 }
			 
			 else
				 return mapping.findForward("success"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward findall(ActionMapping mapping, ActionForm form,
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

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.noticeNo='0002' ";
			 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){					 
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("listallsuccess");				 
			 }
			 
			 else
				 return mapping.findForward("listallsuccess"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}	
	
	//新生查看入学事项公告
	public ActionForward listview(ActionMapping mapping, ActionForm form,
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
			 			
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni order by ni.updateTime desc");
			
			 if(noticeList!=null&&noticeList.size()!=0){
				 
                 List resultList=new ArrayList();                 
				 if(noticeList.size()>5)
				     resultList=noticeList.subList(0,5);//只显示前5条记录
				 else
					 resultList=noticeList;
				 
				 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("noticelist",resultList);
				 
				 request.setAttribute("listcount",new Integer(resultList.size()));
				 
				 }
				 System.out.println("list success");
				 return mapping.findForward("success2");
			 }
			 else
				 return mapping.findForward("success2");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stufind(ActionMapping mapping, ActionForm form,
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
			 
			 DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
			 Noticemodel notice = (Noticemodel)aform.get("notice");
				
		        //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.ifDeleted<>'2' and ni.noticeNo='0002' ";
			 
//			 if(request.getParameter("notice.noticeNo")!=null&&request.getParameter("notice.noticeNo").length()!=0)
//				 sqlstring=sqlstring+" and ni.noticeNo like '%"+request.getParameter("notice.noticeNo")+"%'";
//			 
			 if(request.getParameter("notice.title")!=null&&request.getParameter("notice.title").length()!=0)
				 sqlstring=sqlstring+" and ni.title like '%"+request.getParameter("notice.title")+"%'";
 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("noticeform",notice);
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("success2");				 
			 }
			 
			 else
				 return mapping.findForward("success2"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stuview(ActionMapping mapping, ActionForm form,
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
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+id+"'");
			    
			     request.setAttribute("noticelist",noticeList);
				 System.out.println("view success");
				 return mapping.findForward("noticestuview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
			}

	}
		
}
