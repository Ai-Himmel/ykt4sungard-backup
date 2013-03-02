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
				req.setAttribute("tipinfo","����ѡ��Ҫɾ���Ļ������Ա��Ȼ��ɾ����");
				return mapping.findForward("error");
			}
			if (OperatorUtil.deleteUsers(opercode)) {
				req.setAttribute("tipinfo","ɾ������Ա�ɹ�����ˢ�²���Ա�б�");
				return mapping.findForward("succeed");
			}else{
				req.setAttribute("tipinfo","ɾ������Աʧ�ܣ�����ԭ��");
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
