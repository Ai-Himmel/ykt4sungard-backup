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
import com.kingstargroup.advquery.util.GetterUtil;
import com.kingstargroup.advquery.util.ParamUtil;
import com.kingstargroup.advquery.util.SessionErrors;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: EditPwdAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-20  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditPwdAction extends Action {

	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest req, HttpServletResponse res) throws Exception {	
		String username = GetterUtil.get((String)req.getSession().getAttribute("username"), "");
		String oldPwd = ParamUtil.getString(req, "oldpassword");
		String newPwd = ParamUtil.getString(req, "newpassword");
		String confirmPwd = ParamUtil.getString(req, "confirmpassword");
		SessionErrors.clear(req);
		if (!newPwd.equals(confirmPwd)) {//密码不匹配
			SessionErrors.add(req, "eadvquery.editpassword.unpairpassword");
			return mapping.findForward("eadvquery.changepassword");
		}
		if (UserUtil.changePwd(username, oldPwd, newPwd)) {
			SessionErrors.add(req, "eadvquery.editpassword.success");
		} else {
			SessionErrors.add(req, "eadvquery.editpassword.failure");
		}		
		return mapping.findForward("eadvquery.changepassword");
	}

	

}
