package com.kingstargroup.fdykt.trade;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class GetOnlineCheckResultAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String lvol8 = request.getParameter("lvol8");
		String damt0 = request.getParameter("damt0");
		request.setAttribute("lvol8", lvol8);
		request.setAttribute("damt0", damt0);
		return mapping.findForward("success");
		
	}

}
