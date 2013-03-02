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
import com.kingstargroup.conference.util.OperatorUtil;

/**
 * @author hjw
 *
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
		if (cmd.equals("update")) {
			String userid = ParamUtil.getString(req, "opercode");
			String username = ParamUtil.getString(req, "opername");	
			String deptcode = ParamUtil.getString(req,"deptcode");
			String deptLimitString = ParamUtil.getString(req, "deptLimitString");
			String userLimitString = ParamUtil.getString(req, "userLimitString");
			if ("".equals(userLimitString)){
				req.setAttribute("tipinfo","请选择该人员所具有的权限");
				return mapping.findForward("error");
			}
			if (!OperatorUtil.updateUser(userid,username,deptcode,deptLimitString,userLimitString)) {
				return mapping.findForward("conference.edituser_stage1");
			} else {
				return mapping.findForward("conference.operlist");
			}
		} else if (cmd.equals("stage2") ) {
			return mapping.findForward("conference.edituser_stage2");
		} else if (cmd.equals("stage3")) {
			return mapping.findForward("conference.edituser_stage3");
		} else if (cmd.equals("stage1")) {
			return mapping.findForward("conference.edituser_stage1");
		}
		return null;
		
	}

}
