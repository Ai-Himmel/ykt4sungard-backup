package com.kingstargroup.ecard.portlet.lostfound.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;

public class ViewLostFoundAction extends PortletAction {

	public ActionForward render(ActionMapping mapping, ActionForm form, PortletConfig config, RenderRequest req, RenderResponse res) throws Exception {
		String id = req.getParameter("id");
		int page = ParamUtil.get(req, "page", 0);
		try {
			if (!req.getWindowState().equals(WindowState.MAXIMIZED)) {
				req.setAttribute("result", EcardInformationServiceUtil.list(0, EcardConstants.INFORMATION_LOSTFOUND_TYPE, EcardConstants.DEFAULT_RESULT_SIZE));
				return mapping.findForward("portlet.lostfound.view");
			} else {
				if (id == null) {
					req.setAttribute("result", EcardInformationServiceUtil.list(page, EcardConstants.INFORMATION_LOSTFOUND_TYPE, EcardConstants.LIST_MORE_SIZE));
					return mapping.findForward("portlet.lostfound.viewMore");
				} else {
					req.setAttribute("result", EcardInformationServiceUtil.getInfoById(id));
					return mapping.findForward("portlet.lostfound.viewLostFound");
				}
			}
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}
}
