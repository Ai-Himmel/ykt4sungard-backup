/**
 * 
 */
package com.kingstargroup.ecard.portlet.card.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.PostponeUtil;
import com.kingstargroup.ecard.portlet.card.service.PostponeServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CancelPostponeAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作�?   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  Sep 27, 2005  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CancelPostponeAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String applyId = com.liferay.portal.kernel.util.ParamUtil.getString(req, "id");
			PostponeServiceUtil.cancelPostpone(applyId);
			return mapping.findForward("portlet.ecardtransaction.postpone_view");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}
}
