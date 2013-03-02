package com.kingstargroup.conference.action.nocardimp;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.AttendeeUtil;
 
public class AddNoCardNoInfo extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		try{
		   String confId = request.getParameter("confid");   
		   String name = request.getParameter("name");
		   String sex = request.getParameter("sex");
		   String duty = request.getParameter("duty");
		   String dept = request.getParameter("dept");
		   
		   boolean ifsuccess = AttendeeUtil.addNoCardNoInfo(Integer.parseInt(confId),name,sex,duty,dept);
		   if(ifsuccess){
			   request.setAttribute("tipinfo",name+"添加成功！");
			   
		   }
		   if(!ifsuccess){
			   request.setAttribute("tipinfo",name+"添加失败！");
			  
		   }
		   request.setAttribute("confid",confId);
		   return mapping.findForward("addnocardnoinfo");
		}catch(Exception e){
			 request.setAttribute("tipinfo","添加失败！");
			return mapping.findForward("addnocardnoinfo");
		}
	}
}