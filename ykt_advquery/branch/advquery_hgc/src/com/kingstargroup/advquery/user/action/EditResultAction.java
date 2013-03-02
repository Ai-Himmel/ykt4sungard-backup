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
 * File name: EditResultAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditResultAction extends Action {

	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String cmd = ParamUtil.getString(req, "cmd");
		String isShopOwner = ParamUtil.getString(req, "isshopowner").equals("") ? "0" : "1";		
		if (cmd.equals("update")) {
			String userid = ParamUtil.getString(req, "userid");
			String username = ParamUtil.getString(req, "username");			
			String storeLimitString = ParamUtil.getString(req, "storeLimitString");
			String userLimitString = ParamUtil.getString(req, "userLimitString");
			if (!UserUtil.updateUser(userid, username, storeLimitString, userLimitString, isShopOwner)) {
				SessionErrors.add(req, "eadvquery.error.edituserfailure");
				return mapping.findForward("eadvquery.edituser_stage1");
			} else {
				SessionErrors.add(req, "eadvquery.error.editusersuccess");
				return mapping.findForward("eadvquery.adminusers");
			}
		} else if (cmd.equals("stage2") ) {
			return mapping.findForward("eadvquery.edituser_stage2");
		} else if (cmd.equals("stage3")) {
			return mapping.findForward("eadvquery.edituser_stage3");
		} else if (cmd.equals("stage1")) {
			return mapping.findForward("eadvquery.edituser_stage1");
		}
		return null;
		
	}

}
