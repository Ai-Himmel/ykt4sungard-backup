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

public class PosSwipereportAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String thisMonth = DateUtil.getNow("yyyyMM");
		((DynaActionForm) form).set("swipereportBeginMonth", thisMonth);
		((DynaActionForm) form).set("swipereportEndMonth", thisMonth);
		List departments = PosServiceUtil.getDepartments();
		request.setAttribute("departments", departments);
		return mapping.findForward("portlet.pos.swipereport.view");
	}
}
