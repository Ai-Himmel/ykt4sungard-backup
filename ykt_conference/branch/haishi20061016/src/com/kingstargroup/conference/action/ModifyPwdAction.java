package com.kingstargroup.conference.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.util.OperatorUtil;

public class ModifyPwdAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response)
			throws Exception {
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		String oldPwd = ParamUtil.getString(request, "oldpwd");
		String newPwd = ParamUtil.getString(request, "newpwd");
		String confirmPwd = ParamUtil.getString(request, "renewpwd");
		if ((StringUtil.inputIfCharAndNum(oldPwd))
				|| (StringUtil.inputIfCharAndNum(newPwd))
				|| (StringUtil.inputIfCharAndNum(confirmPwd))) {
			request.setAttribute("tipinfo", "密码项只能为数字或字母");
			return mapping.findForward("error");
		}
		if (!newPwd.equals(confirmPwd)) {// 密码不匹配
			request.setAttribute("tipinfo", "两次输入密码不一致，请重新输入！");
			return mapping.findForward("error");
		}
		if (OperatorUtil.changePwd(username, oldPwd, newPwd)) {
			request.setAttribute("tipinfo", "修改密码成功！");
		} else {
			request.setAttribute("tipinfo", "密码修改失败，请检查原因！");
			return mapping.findForward("error");
		}
		return mapping.findForward("succeed");
	}

}
