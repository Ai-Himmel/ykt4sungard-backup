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

/**
 * @author Õı”®
 *
 */
public class QueryAttGroupNameAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		String groupName = ParamUtil.getString(request, "groupName");
		try {
			List result = ParameterUtil.getAttGroupName(operId, groupName);
			request.setAttribute("result",result);
			return mapping.findForward("viewattgroupname");			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
