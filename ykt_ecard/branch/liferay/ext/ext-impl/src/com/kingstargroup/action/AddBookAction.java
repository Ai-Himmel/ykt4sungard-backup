package com.kingstargroup.action;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.struts.PortletAction;

public class AddBookAction extends PortletAction {
	public void processAction(ActionMapping mapping, ActionForm form,
			PortletConfig config, ActionRequest req, ActionResponse res)
			throws Exception {
		String bookTitle = req.getParameter("book_title");
		if (null == bookTitle || "".equals(bookTitle)) {
			setForward(req, "portlet.ext.myaction.error");
		} else {
			setForward(req, "portlet.ext.myaction.success");
		}
	}

	public ActionForward render(ActionMapping mapping, ActionForm form,
			PortletConfig config, RenderRequest req, RenderResponse res)
			throws Exception {
		if (getForward(req) != null && !getForward(req).equals("")) {
			return mapping.findForward(getForward(req));
		} else {
			return mapping.findForward("portlet.ext.myaction.view");
		}
	}
}