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
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.ParameterUtil;

public class ModifyDelegateNameAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");		
		String dlgtName = ParamUtil.getString(request, "dlgtName");
		String comment = ParamUtil.getString(request, "comment");
		String dlgtId = ParamUtil.getString(request, "dlgtId");
		if("".equals(dlgtId)) {
			return mapping.findForward("error");
		}	
		
		try {

			if ( ParameterUtil.modifyDelegate(dlgtId, dlgtName, "1", "", operId, comment)) {
				return mapping.findForward("viewdelegate");
			}
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
		return null;
	}
}
