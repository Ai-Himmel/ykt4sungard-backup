package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.util.DateFormatUtil;
import com.liferay.portal.struts.PortletAction;

public class TdquerystatAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String begindate = DateFormatUtil.getDateLaterNow("yyyy/MM/dd");
		String enddate = DateFormatUtil.getNowDate("yyyy/MM/dd");
		((DynaActionForm) form).set("tdcheckserial_begindate", begindate);
		((DynaActionForm) form).set("tdcheckserial_enddate", enddate);
		return mapping.findForward("portlet.card.tdquerystat.view");
	}
}
