/**
 * 
 */
package com.kingstargroup.conference.action.parameter;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.dao.DelegateDAO;
import com.kingstargroup.conference.util.ParameterUtil;


public class AddDelegateNameAction extends Action {
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response) 
			throws Exception {
		String dlgtName = ParamUtil.getString(request, "dlgtName");
		String comment = ParamUtil.getString(request, "comment");
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");;
		DelegateDAO dao = DelegateDAO.getInstance();
		
		try{
			List list = dao.getDelegates(operId,dlgtName);
			if (!list.isEmpty()) {
				SessionErrors.add(request, "delegate.failed.delegate");
				return mapping.getInputForward();
			}
			if (ParameterUtil.createDelegate(dlgtName, "1", "", operId, comment)){
				return mapping.findForward("viewdelegate");
			}
			return mapping.findForward("error");
		}
		catch (Exception e) {
			return mapping.findForward("error");
		}
	}
}
