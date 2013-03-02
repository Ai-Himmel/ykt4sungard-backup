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
			request.setAttribute("tipinfo", "������ֻ��Ϊ���ֻ���ĸ");
			return mapping.findForward("error");
		}
		if (!newPwd.equals(confirmPwd)) {// ���벻ƥ��
			request.setAttribute("tipinfo", "�����������벻һ�£����������룡");
			return mapping.findForward("error");
		}
		if (OperatorUtil.changePwd(username, oldPwd, newPwd)) {
			request.setAttribute("tipinfo", "�޸�����ɹ���");
		} else {
			request.setAttribute("tipinfo", "�����޸�ʧ�ܣ�����ԭ��");
			return mapping.findForward("error");
		}
		return mapping.findForward("succeed");
	}

}
