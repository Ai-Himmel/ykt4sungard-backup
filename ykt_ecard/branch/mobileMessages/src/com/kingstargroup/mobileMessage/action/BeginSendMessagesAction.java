package com.kingstargroup.mobileMessage.action;

import java.util.Timer;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.mobileMessage.util.KSConfiguration;
import com.kingstargroup.mobileMessage.util.SCMMessageUtil;
import com.kingstargroup.mobileMessage.util.SCMSendMessage;

public class BeginSendMessagesAction  extends Action  {
	
	//private Timer timer = new Timer(true);
	//private long seconds = KSConfiguration.getInstance().getPropertyAsInt("sendSeconds",10);

	public ActionForward execute(ActionMapping mapping,   
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		    String cmd = req.getParameter("cmd");
		    ServletContext  app = req.getSession().getServletContext();
		    if("begin".equals(cmd)){
		    	sendMessage();    	
				app.setAttribute("Send", "begin");
		    }
		  /*  if("stop".equals(cmd)){
		    	cancelSend();
		    	app.setAttribute("Send", "stop");
		    	
		    	
		    }*/
		    return mapping.findForward("index");
	}
	private void  sendMessage(){
	
		/* Calendar c =Calendar.getInstance();
		 timer =new  Timer(true);
		 timer.schedule(new SCMSendMessage(),c.getTime(),seconds*1000);//60 seconds
*/	     SCMSendMessage  send = new SCMSendMessage();
         send.start();
	}
	private void cancelSend(){
		SCMMessageUtil.cancelSend();
	}
	



}
