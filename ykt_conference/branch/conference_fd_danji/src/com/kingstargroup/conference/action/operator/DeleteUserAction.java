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
public class DeleteUserAction extends Action {
	/* (non-Javadoc)
	 * @see com.liferay.portal.struts.PortletAction#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(ActionMapping mapping, 
								ActionForm form, 
								HttpServletRequest req, 
								HttpServletResponse res) throws Exception {
		String cmd = req.getParameter("cmd");
		String opercode = req.getParameter("operCode");
		if ("delete".equals(cmd)){
			if (opercode == null) {
				req.setAttribute("tipinfo","请先选择要删除的会议管理员，然后删除！");
				return mapping.findForward("error");
			}
			if (OperatorUtil.deleteUsers(opercode)) {
				req.setAttribute("tipinfo","删除操作员成功，请刷新操作员列表！");
				return mapping.findForward("succeed");
			}else{
				req.setAttribute("tipinfo","删除操作员失败，请检查原因！");
				return mapping.findForward("error");
			}
			
		}else if ("query".equals(cmd)){
			req.setAttribute("result",OperatorUtil.getAllOperatorList());
			return mapping.findForward("operatorlist");
		}else{
			return mapping.findForward("operatorlist");
		}
	}
}
