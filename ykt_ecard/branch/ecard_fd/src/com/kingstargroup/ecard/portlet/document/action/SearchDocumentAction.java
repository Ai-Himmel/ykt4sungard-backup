/**
 * 
 */
package com.kingstargroup.ecard.portlet.document.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.ParamUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: SearchDocumentAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class SearchDocumentAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String title = req.getParameter("search_title");				
			int page = ParamUtil.get(req, "page", 0);
			if (mapping.getAttribute() != null) {
				if ("request".equals(mapping.getScope())) {					
					req.setAttribute(mapping.getAttribute(), form);					
				} else {
					req.getSession().setAttribute(mapping.getAttribute(), form);
				}
			}
			req.setAttribute("result", InformationUtil.search(title, null, EcardConstants.INFORMATION_DOCUMENT_TYPE, page));
			return mapping.findForward("portlet.ecarddoc.search_result");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}
}
