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
import com.kingstargroup.advquery.util.ParamUtil;
import com.kingstargroup.advquery.util.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AddResultAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-11  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AddResultAction extends Action {

	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String cmd = ParamUtil.getString(req, "cmd");
		String password = ParamUtil.getString(req, "password");
		String confirmPwd = ParamUtil.getString(req, "confirmpassword");
		String isShopOwner = ParamUtil.getString(req, "isshopowner").equals("") ? "0" : "1";;
		if (!password.equals(confirmPwd)) {
			SessionErrors.add(req, "eadvquery.editpassword.unpairedpassword");
			return mapping.findForward("eadvquery.adduser_stage1");
		}
		if (cmd.equals("create")) {
			String userid = ParamUtil.getString(req, "userid");
			String username = ParamUtil.getString(req, "username");			
			String storeLimitString = ParamUtil.getString(req, "storeLimitString");
			String userLimitString = ParamUtil.getString(req, "userLimitString");
			if (UserUtil.createUser(userid, username, password, storeLimitString, userLimitString, isShopOwner)) {
				SessionErrors.add(req, "eadvquery.error.createusersuccess");
				return mapping.findForward("eadvquery.adminusers");
			} else {
				SessionErrors.add(req, "eadvquery.error.createuserfailure");
				return mapping.findForward("eadvquery.adduser_stage1");
			}
		} else if (cmd.equals("stage2") ) {
			return mapping.findForward("eadvquery.adduser_stage2");
		} else if (cmd.equals("stage3")) {
			return mapping.findForward("eadvquery.adduser_stage3");
		} else if (cmd.equals("stage1")) {
			return mapping.findForward("eadvquery.adduser_stage1");
		}
		return null;
		
	}

}
