package com.liferay.portal.score.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.score.util.ConnectDatabase;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;

public class StudentScoreResultAction extends PortletAction {

	
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest req, HttpServletResponse res) throws Exception {
			//logger.info("--action--begin------"); 
			List studentScore=null;
			HttpSession session = req.getSession();
			
			String firstYear = (String) req.getParameter("studentYear");
			//logger.info("--action--firstYear------"+firstYear);
			String termNo = (String) req.getParameter("termNo");
			//logger.info("--action--termNo------"+termNo);
			String  studentno = session.getAttribute(WebKeys.USER_ID).toString();
			//logger.info("--action--studentno------"+studentno);
			studentScore = new  ConnectDatabase().getStudentScore(studentno,firstYear,termNo);
			req.setAttribute("studentScore", studentScore);
			
		 return mapping.findForward("portlet.ecardtransaction.studentscore_result");
		
		
	}
		private static final Logger logger = Logger.getLogger(StudentScoreResultAction.class);

}
