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
import com.kingstargroup.conference.util.ParameterUtil;


public class QueryDelegateNameAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		String dlgtName = ParamUtil.getString(request, "dlgtName");
		try {
			List result = ParameterUtil.getDelegates(operId,dlgtName);
			request.setAttribute("result",result);
			return mapping.findForward("viewdelegate");			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
