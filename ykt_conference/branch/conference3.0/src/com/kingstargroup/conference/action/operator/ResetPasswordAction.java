/**
 * 
 */
package com.kingstargroup.conference.action.operator;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.OperatorUtil;


/**
 * @author hjw
 *
 */
public class ResetPasswordAction extends Action {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String opercode = req.getParameter("opercode");
		String password = req.getParameter("operpwd");
		String repassword = req.getParameter("pwdagain");
		if (!OperatorUtil.ifUserExist(opercode)){
			req.setAttribute("tipinfo","该操作员不存在，请重新输入！");
			return mapping.findForward("error");
		}
		if (!password.equals(repassword)){
			req.setAttribute("tipinfo","两次密码输入不一样！");
			return mapping.findForward("error");
		}
		if (OperatorUtil.editPassword(opercode,password)) {
			req.setAttribute("tipinfo","密码修改成功！");
		} else {
			req.setAttribute("opercode",opercode);
			req.setAttribute("password",password);
			req.setAttribute("tipinfo","密码修改失败，请检查原因！");
			return mapping.findForward("error");
		}
		return mapping.findForward("succeed");
	}

}
