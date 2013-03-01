/**
 * 
 */
package com.kingstargroup.advquery.user.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.UserUtil;
import com.kingstargroup.advquery.util.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ResetPasswordAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-14  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ResetPasswordAction extends Action {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String userids[] = req.getParameterValues("ids");
		if (userids == null) {
			SessionErrors.add(req, "eadvquery.error.chooserestusers");
			return mapping.findForward("eadvquery.adminusers");
		}
		if (UserUtil.resetPassword(userids)) {
			SessionErrors.add(req, "eadvquery.error.restusersucceed");
		} else {
			SessionErrors.add(req, "eadvquery.error.restuserfailed");
		}
		return mapping.findForward("eadvquery.adminusers");
	}

}
