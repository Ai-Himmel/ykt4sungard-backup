package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.equipment.Maintain;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

public class AdminAnswerResultAction extends PortletAction{

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		req.getSession().setAttribute("Maintain",null);
		String id = req.getParameter("id");
		String answerInfo = req.getParameter("answerInfo");
		String userId = (String)req.getSession().getAttribute(WebKeys.USER_ID);
		String operator = req.getParameter("operator");
		String accidentExplain = req.getParameter("accidentExplain");
		String operatorDepend = req.getParameter("operatorDepend");
		String operatorStep = req.getParameter("operatorStep");
		String applyPeople = req.getParameter("applyPeople");
		String applyEmail = req.getParameter("applyEmail");
		String[] MaintainType = req.getParameterValues("maintainType");
	 try {
		 if(MaintainType == null){
		 SessionErrors.add(req, EcardConstants.CHOOSE_MAINTAIN_TYPE);			
	     return mapping.getInputForward();
	     }
		 if(MaintainUtil.answerMaintainInfo(id,userId,answerInfo,MaintainType,operator,accidentExplain,operatorDepend,operatorStep,applyPeople,applyEmail)==true){
			 SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
			 req.getSession().setAttribute("Maintain",null);
			 Maintain maintain =MaintainUtil.getMaintainById(id);
			 req.setAttribute("status", maintain.getStatus());
			 return mapping.findForward("portlet.maintain.admin");	
		 }else{
			 return mapping.getInputForward();
		 }
		/*if (isTokenValid(req)) {
			MaintainUtil.addMaintain(applyTitle,applyInfo, MaintainType,userId);
			resetToken(req);
		}*/
			
	} catch (PortalException pe) {
		req.setAttribute(PageContext.EXCEPTION, pe);
		return mapping.findForward(Constants.COMMON_ERROR);
	}
  }
}
