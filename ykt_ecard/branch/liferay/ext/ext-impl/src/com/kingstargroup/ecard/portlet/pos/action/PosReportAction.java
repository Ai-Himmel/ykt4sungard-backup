package com.kingstargroup.ecard.portlet.pos.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.struts.PortletAction;

public class PosReportAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String now = DateUtil.getNow("yyyy-MM-dd");
		((DynaActionForm) form).set("reportBeginDate", now);
		((DynaActionForm) form).set("reportEndDate", now);
		return mapping.findForward("portlet.pos.report.view");
	}
}
