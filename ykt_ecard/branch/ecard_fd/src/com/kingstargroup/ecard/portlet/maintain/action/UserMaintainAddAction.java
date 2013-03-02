package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.struts.PortletAction;

public class UserMaintainAddAction extends PortletAction {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		 saveToken(req);
		 req.getSession().setAttribute("Maintain",null);
		return mapping.findForward("portlet.maintain.useradd");
	}
}
