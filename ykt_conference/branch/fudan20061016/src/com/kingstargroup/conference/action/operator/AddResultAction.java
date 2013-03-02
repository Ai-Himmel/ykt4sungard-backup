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

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.util.OperatorUtil;


/**
 * @author hjw
 *
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
		String password = ParamUtil.getString(req, "operpwd");
		String confirmPwd = ParamUtil.getString(req, "pwdagain");
		String opercode = ParamUtil.getString(req, "opercode");
		if (cmd.equals("create")) {
			String opername = ParamUtil.getString(req, "opername");	
			String deptcode = ParamUtil.getString(req,"deptcode");
			String deptLimitString= ParamUtil.getString(req, "deptLimitString");
			String userLimitString = ParamUtil.getString(req, "userLimitString");
			if ("".equals(userLimitString)){
				req.setAttribute("tipinfo","请选择该人员所具有的权限");
				return mapping.findForward("error");
			}
			if (OperatorUtil.createOperator(opercode,opername,deptcode,deptLimitString,userLimitString,password)) {
				SessionErrors.add(req, "conference.error.createusersuccess");
				req.setAttribute("tipinfo","登录名为：["+opercode+"]的会议管理员创建成功！");
				return mapping.findForward("succeed");
			} else {
				SessionErrors.add(req, "conference.error.createuserfailure");
				return mapping.findForward("conference.adduser_stage1");
			}
		} else if (cmd.equals("stage2") ) {
			if (OperatorUtil.ifUserExist(opercode)) {
				SessionErrors.add(req, "conference.error.createuserfailure");
				return mapping.findForward("conference.adduser_stage1");
			}else if (!password.equals(confirmPwd)){
				SessionErrors.add(req, "conference.editpassword.unpairedpassword");
				return mapping.findForward("conference.adduser_stage1");
			}else if (StringUtil.inputIfCharAndNum(opercode)){
				SessionErrors.add(req, "conference.opercode.error");
				return mapping.findForward("conference.adduser_stage1");
			}else if (StringUtil.inputIfCharAndNum(password)){
				SessionErrors.add(req, "conference.password.error");
				return mapping.findForward("conference.adduser_stage1");
			}else{
				return mapping.findForward("conference.adduser_stage2");
			}
		} else if (cmd.equals("stage3")) {
			return mapping.findForward("conference.adduser_stage3");
		} else if (cmd.equals("stage1")) {
			return mapping.findForward("conference.adduser_stage1");
		}
		return null;
		
	}

}
