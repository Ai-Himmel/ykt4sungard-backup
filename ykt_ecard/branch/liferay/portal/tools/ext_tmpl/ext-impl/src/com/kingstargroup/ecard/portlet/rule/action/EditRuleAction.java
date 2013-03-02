/**
 * 
 */
package com.kingstargroup.ecard.portlet.rule.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: EditRuleAction.java<br>
 * Description: �༭һ������ƶȵ�StrutsActionʵ��<br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditRuleAction extends PortletAction {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		String id = req.getParameter("id");
		String title = req.getParameter("title");
		String content = req.getParameter("content");
		try {
			if (isTokenValid(req)) {
				
				EcardInformationServiceUtil.updateInfoById(id, title, content, "");
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
			return mapping.findForward("portlet.ecardrule.admin");			
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

}
