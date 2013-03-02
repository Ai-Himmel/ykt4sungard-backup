package com.kingstargroup.ecard.portlet.shop.action;

import java.util.Locale;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.struts.PortletAction;

public class ViewShopPosReportAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String datetime = DateUtil.getCurrentDate("yyyy/MM/dd", Locale.CHINA);
		datetime = com.kingstargroup.ecard.util.DateUtil.getOtherDate(datetime,
				"yyyy/MM/dd", -1);
		req.setAttribute("shopad_begindate", datetime);
		req.setAttribute("shopad_enddate", datetime);
		return mapping.findForward("portlet.shopposreport.view");

	}
}
