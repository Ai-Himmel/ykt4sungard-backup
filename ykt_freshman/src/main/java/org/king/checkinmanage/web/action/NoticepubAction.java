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


public class NoticepubAction  extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
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
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.ifDeleted='0' order by ni.updateTime desc");
			
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
				 //System.out.println("list success");
				 return mapping.findForward("pubsuccess");
			 }
			 else
				 return mapping.findForward("pubsuccess");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
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
				 //System.out.println("view success");
				 return mapping.findForward("noticepubview");
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
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}
		
		String noticeNo=request.getParameter("hnoticeNo");
		String title=request.getParameter("htitle");

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");			 
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.ifDeleted='0'";
			 
			 if(request.getParameter("hnoticeNo")!=null&&request.getParameter("hnoticeNo").length()!=0)
				 sqlstring=sqlstring+" and ni.noticeNo like '%"+request.getParameter("hnoticeNo")+"%'";
			 
			 if(request.getParameter("htitle")!=null&&request.getParameter("htitle").length()!=0)
				 sqlstring=sqlstring+" and ni.title like '%"+request.getParameter("htitle")+"%'";
 			 
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
					 request.setAttribute("noticeNo",noticeNo);
					 request.setAttribute("title",title);
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("pubsuccess");				 
			 }
			 
			 else
				 return mapping.findForward("pubsuccess"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
}