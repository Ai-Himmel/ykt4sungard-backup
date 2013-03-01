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
 * File name: DeleteUserAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-11  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class DeleteUserAction extends Action {
	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String ids[] = req.getParameterValues("ids");
		if (ids == null) {
			SessionErrors.add(req, "eadvquery.error.choosedeleteusers");
			return mapping.findForward("eadvquery.adminusers");
		}
		if (UserUtil.deleteUsers(ids)) {
			SessionErrors.add(req, "eadvquery.error.deleteusersucceed");
		} else {
			SessionErrors.add(req, "eadvquery.error.deleteuserfailed");
		}
		return mapping.findForward("eadvquery.adminusers");
	}
}
