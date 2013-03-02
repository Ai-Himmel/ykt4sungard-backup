package com.kingstargroup.ecard.portlet.pos.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.pos.service.PosServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.struts.PortletAction;

public class PosSwipedetailAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String now = DateUtil.getNow("yyyy-MM-dd");
		((DynaActionForm) form).set("swipedetailBeginDate", now);
		((DynaActionForm) form).set("swipedetailEndDate", now);
		List departments = PosServiceUtil.getDepartments();
		request.setAttribute("departments", departments);
		return mapping.findForward("portlet.pos.swipedetail.view");
	}
}
