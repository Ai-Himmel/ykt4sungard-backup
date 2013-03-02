/**
 * 
 */
package com.kingstargroup.conference.action.parameter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.util.ParameterUtil;

public class ViewDelegateNameAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response)
			throws Exception {
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		try {
			request.setAttribute("result", ParameterUtil.getAllDelegates(operId));
			return mapping.findForward("viewdelegate");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
