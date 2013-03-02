package com.kingstargroup.ecard.portlet.friendslink.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.FriendsLinkUtil;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.ParamUtil;

public class ViewFriendsLinkAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {
		String id = req.getParameter("id");
		int page = ParamUtil.get(req, "page", 0);
		try {
			if (!req.getWindowState().equals(WindowState.MAXIMIZED)) {
				req.setAttribute("result", FriendsLinkUtil.list(0,  EcardConstants.DEFAULT_RESULT_SIZE));
				return mapping.findForward("portlet.ecardlink.view");
			} else {
				if (id == null) {
					req.setAttribute("result", FriendsLinkUtil.list(page,  EcardConstants.LIST_MORE_SIZE));
					return mapping.findForward("portlet.ecardlink.viewMore");
				}
				else {
					req.setAttribute("result", FriendsLinkUtil.getLink(id));
					return mapping.findForward("portlet.ecardlink.viewlinks");
				}
			}
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
