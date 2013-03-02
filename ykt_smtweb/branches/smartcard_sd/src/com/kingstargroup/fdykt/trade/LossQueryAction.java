package com.kingstargroup.fdykt.trade;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class LossQueryAction extends Action {


	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.findForward("failure");

		forward = doLossQuery(mapping, request);

		return forward;
	}

	private ActionForward doLossQuery(ActionMapping mapping,
			HttpServletRequest request) {
			return mapping.findForward("logon");
	}
}
