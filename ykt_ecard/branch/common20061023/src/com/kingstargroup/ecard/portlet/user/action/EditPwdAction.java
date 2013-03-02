/**
 * 
 */
package com.kingstargroup.ecard.portlet.user.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.OldPwdErrorException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.UnpairedPwdException;
import com.kingstargroup.ecard.hibernate.util.SystemManagementUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: EditPwdAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-10-20  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditPwdAction extends PortletAction {

	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest req, HttpServletResponse res) throws Exception {
		try {
			String userId = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
			String oldPwd = ParamUtil.getString(req, "oldpassword");
			String newPwd = ParamUtil.getString(req, "newpassword");
			String confirmPwd = ParamUtil.getString(req, "confirmpassword");
			SystemManagementUtil.changePassword(userId, oldPwd, newPwd, confirmPwd);
			if (mapping.getAttribute() != null) {
				if ("request".equals(mapping.getScope())) {					
					req.removeAttribute(mapping.getAttribute());					
				} else {
					req.getSession().removeAttribute(mapping.getAttribute());
				}
			}
			SessionErrors.add(req, EcardConstants.EDIT_PASSWORD_SUCCEED);
		}  catch (PortalException pe) {
			if (pe instanceof OldPwdErrorException 
					|| pe instanceof UnpairedPwdException) {
				SessionErrors.add(req, pe.getClass().getName());
			} else {
				req.setAttribute(PageContext.EXCEPTION, pe);
				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		return mapping.findForward("portlet.ecarduser.edit_password");
	}

	

}
