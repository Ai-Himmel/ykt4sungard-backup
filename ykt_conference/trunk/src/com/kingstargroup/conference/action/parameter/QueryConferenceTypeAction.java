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

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.ParameterUtil;


/**
 * @author Õı”®
 *
 */
public class QueryConferenceTypeAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String typename = ParamUtil.getString(request, "contypename");

		try {
			List result = ParameterUtil.getConfTypeForQue(typename);
			request.setAttribute("result",result);
			return mapping.findForward("viewconftype");			
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
