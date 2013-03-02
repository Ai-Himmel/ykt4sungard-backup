package com.kingstargroup.ecard.portlet.news.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.ParamUtil;

public class ViewNewsAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {
		String id = req.getParameter("id");
		int page = ParamUtil.get(req, "page", 0);
		try {
			if (!req.getWindowState().equals(WindowState.MAXIMIZED)) {
				req.setAttribute("result", InformationUtil.list(0, EcardConstants.INFORMATION_NEWS_TYPE, EcardConstants.DEFAULT_RESULT_SIZE));
				return mapping.findForward("portlet.ecardnews.view");
			} else {
				if (id == null) {
					req.setAttribute("result", InformationUtil.list(page, EcardConstants.INFORMATION_NEWS_TYPE, EcardConstants.LIST_MORE_SIZE));
					return mapping.findForward("portlet.ecardnews.viewMore");
				}
				else {
					req.setAttribute("result", InformationUtil.getInfoById(id));
					return mapping.findForward("portlet.ecardnews.viewNews");
				}
			}
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
}
