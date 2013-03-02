package com.kingstargroup.ecard.portlet.maintain.action;

import java.util.Calendar;
import java.util.Timer;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.ecard.hibernate.util.SendEmailReportUtil;
import com.kingstargroup.ecard.hibernate.util.WebDictionaryUtil;
import com.kingstargroup.ecard.util.EcardConstants;

import com.liferay.portal.struts.PortletAction;

public class EditEmailAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		   String cmd =req.getParameter("cmd")==null?"":req.getParameter("cmd");
		   if(cmd.equals("save")){
			   String  service=req.getParameter("service")==null?"":req.getParameter("service");
			   String  title = req.getParameter("title")==null?"":req.getParameter("title");
			   String[]  receiveemail=req.getParameterValues("receiveemail");
			   String  sendemail = req.getParameter("sendemail");
			   String  username = req.getParameter("username");
			   String  password= req.getParameter("password");
			   String  emailReport = req.getParameter("emailReport");
			   String  beginDate = req.getParameter("beginDate"); 
			   String  secondtimes = req.getParameter("secondtimes");
				   
			  if(WebDictionaryUtil.saveorupdate(title,service,receiveemail,sendemail,username,password,emailReport, beginDate, secondtimes)){
				  
				  
				  Timer timer = new Timer();
				  Calendar c =Calendar.getInstance();
				  int	year =Integer.parseInt(beginDate.substring(0,4));
				  int	mm= Integer.parseInt(beginDate.substring(5,7))-1;
				  int	dd = Integer.parseInt(beginDate.substring(8,10));
				  c.set(year,mm,dd);
				  timer.schedule(new SendEmailReportUtil(),c.getTime(),Integer.parseInt(secondtimes)*24*60*60*1000);
				
				  
				  ActionMessages messages = new ActionMessages();
				  messages.add("",new ActionMessage(EcardConstants.UPDATE_INFO_SUCCESS,false));
				  req.setAttribute("show", messages);
			  }else{
				  ActionMessages messages = new ActionMessages();
				  messages.add("",new ActionMessage(EcardConstants.UPDATE_INFO_FAIL,false));
				  req.setAttribute("show", messages);
			  }
			  
			  
		   }else{
			   
		   }
		  
		   
		   return  mapping.findForward("portlet.maintain.editemail");
	}

}
