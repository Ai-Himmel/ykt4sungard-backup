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
import com.kingstargroup.ecard.portlet.infotype.service.InfoTypeServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AddSubTypeAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-23  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AddSubTypeAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String parentId = req.getParameter("parentId");
			String typeName = req.getParameter("typeName");
			String cmd = req.getParameter("cmd");
			if (isTokenValid(req)) {
				
				InfoTypeServiceUtil.add(parentId, typeName);
				resetToken(req);
			}
			//如果操作类型为保存并添加下一个，就需要清除对应的Form对象
			if (cmd.equals("saveandnext")) {
				if (mapping.getAttribute() != null) {
					if ("request".equals(mapping.getScope())) {					
						req.removeAttribute(mapping.getAttribute());					
					} else {
						req.getSession().removeAttribute(mapping.getAttribute());
					}
				}
				saveToken(req);
				SessionErrors.add(req, EcardConstants.ADD_INFO_SUCCEED);
				return mapping.findForward("portlet.ecardfaq.add_type");
			}
			return mapping.findForward("portlet.ecardfaq.admin_type");
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}	
}
