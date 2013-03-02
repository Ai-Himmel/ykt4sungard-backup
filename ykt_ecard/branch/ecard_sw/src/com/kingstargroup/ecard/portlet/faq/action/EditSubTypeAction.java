/**
 * 
 */
package com.kingstargroup.ecard.portlet.faq.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: EditSubTypeAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-23  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditSubTypeAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		String id = req.getParameter("id");
		String typeName = req.getParameter("typeName");		
		try {
			if (isTokenValid(req)) {
				
				InfoTypeUtil.updateType(id, typeName);
				resetToken(req);
			}
			if (mapping.getAttribute() != null) {
				if ("request".equals(mapping.getScope())) {					
					req.removeAttribute(mapping.getAttribute());					
				} else {
					req.getSession().removeAttribute(mapping.getAttribute());
				}
			}						
			SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
			return mapping.findForward("portlet.ecardfaq.admin_type");			
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
