/**
 * 
 */
package com.kingstargroup.ecard.portlet.distribution.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: ViewDocsAction.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-13  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ViewMapsAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String id = ParamUtil.get(req, "id", "");
			int page = ParamUtil.get(req, "page", 0);
			if (id.equals("")) {
				req.setAttribute("result", EcardInformationServiceUtil.list(page, EcardConstants.INFORMATION_DISTRIBUTION_TYPE, EcardConstants.LIST_MORE_SIZE));
				return mapping.findForward("portlet.distribution.view");
			} else {
				req.setAttribute("result", EcardInformationServiceUtil.getInfoById(id));
				return mapping.findForward("portlet.distribution.viewdetail");
			}
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

}
