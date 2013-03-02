package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.equipment.Maintain;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.servlet.SessionErrors;

public class UpdateMaintainAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		try {
			
			String id = req.getParameter("id");
			Maintain maintain =MaintainUtil.getMaintainById(id);
			if(maintain.getAnswerInfo()==null){
				ActionMessages msg= new ActionMessages();
				msg.add("",new  ActionMessage(EcardConstants.ADMIN_NO_ANSWER,false));
				this.saveMessages(req, msg);
				return mapping.findForward("portlet.maintain.userdetail");
			}
			
			String applyPeopleAnswer = req
					.getParameter("applyPeopleAnswer");
			MaintainUtil.updateMaintain(id, applyPeopleAnswer);
			ActionMessages msg= new ActionMessages();
			msg.add("",new  ActionMessage(EcardConstants.UPDATE_INFO_SUCCESS,false));
			this.saveMessages(req, msg);
			//req.getSession().setAttribute("maintain",null);
			req.getSession().setAttribute("Maintain", MaintainUtil.getMaintainById(id));
			return mapping.findForward("portlet.maintain.userdetail");

		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
