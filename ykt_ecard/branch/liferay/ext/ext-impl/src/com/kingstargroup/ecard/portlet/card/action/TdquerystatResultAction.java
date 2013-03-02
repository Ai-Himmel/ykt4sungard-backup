package com.kingstargroup.ecard.portlet.card.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

public class TdquerystatResultAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response) throws Exception {
		String begindate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(request, "tdcheckserial_begindate", ""), '/', "");
		String enddate = com.liferay.portal.kernel.util.StringUtil.replace(com.liferay.portal.kernel.util.ParamUtil.get(request, "tdcheckserial_enddate", ""), '/', "");
		String classno = ParamUtil.getString(request, "tdcheckserial_classno");
		String stuempno = ParamUtil.getString(request, "tdcheckserial_stuempno");
		String custname = ParamUtil.getString(request, "tdcheckserial_custname");
		
		if("".equals(begindate)||"".equals(enddate)){
			SessionErrors.add(request, EcardConstants.DATE_NOT_SELECTED);
			return mapping.findForward("portlet.card.tdquerystat.view");
		}
		
		List result = null;
		try {
			result = CardServiceUtil.getTdquerystat(begindate, enddate, classno, stuempno, custname);
		} catch (Exception e) {
			SessionErrors.add(request,e.getClass().getName(),e);
			//e.printStackTrace();
		}
		request.setAttribute("tdquerystatList", result);
		
		return mapping.findForward("portlet.card.tdquerystat.view");
	}
}
