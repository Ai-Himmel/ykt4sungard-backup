package com.kingstargroup.ecard.portlet.faq.action;

import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.ParamUtil;

public class ViewFAQAction extends PortletAction {

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {
		String subId = ParamUtil.get(req, "subid", "");
		try {
			ResultPage subResult = InfoTypeUtil.getChildList(EcardConstants.INFORMATION_FAQ_TYPE);
			if (!subId.equals("") || subResult.getList().size() == 0) {
				subId = subId.equals("") ? EcardConstants.INFORMATION_FAQ_TYPE : subId;
				req.setAttribute("result", InformationUtil.list(subId));
				return mapping.findForward("portlet.ecardfaq.view");
			} else {				
				req.setAttribute("result", subResult);
				return mapping.findForward("portlet.ecardfaq.viewsublist");
			}			
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
}
