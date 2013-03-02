package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

public class UserMaintainAddResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {

		String applyTitle = req.getParameter("applyTitle");
		String applyInfo = req.getParameter("applyInfo");
		String contact = req.getParameter("contact");
		String school = req.getParameter("school");
		String accidentDate = req.getParameter("accidentDate");
		String accidentTime = req.getParameter("accidentTime");
		String cmd = req.getParameter("cmd");
		String applyPeopleAnswer =  req.getParameter("applyPeopleAnswer");
		String id = req.getParameter("id");
		String userId = (String) req.getSession().getAttribute(WebKeys.USER_ID);
		String applyPeople = req.getParameter("applyPeople");
		String applyEmail = req.getParameter("applyEmail");
		String inputPeople = userId;
		try {

			/*
			 * if(MaintainType == null){ SessionErrors.add(req,
			 * EcardConstants.CHOOSE_MAINTAIN_TYPE); return
			 * mapping.getInputForward(); }
			 */
			if (isTokenValid(req)) {
				
				if(cmd!=null && "save".equals(cmd)){
					MaintainUtil.addMaintain(applyTitle, applyInfo, inputPeople,contact,school,accidentDate,accidentTime,applyPeople,applyEmail);
					MaintainUtil.sendEmail(applyInfo);
				}
				
				resetToken(req);
			}
           
			SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
			return mapping.findForward("portlet.maintain.view");

		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
	  
    
	
	 
}
