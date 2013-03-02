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

import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.util.ParameterUtil;

/**
 * @author Õı”®
 *
 */
public class AddConferenceTypeAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response)
			throws Exception {		
		String typename = request.getParameter("contypename");
		String comments = request.getParameter("comments");	

		try {
			List list = ParameterUtil.getConferenceType(typename);			
			if (!list.isEmpty()){
				 SessionErrors.add(request, "conftype.failed.typename");
				return mapping.getInputForward();
			}
			if ( ParameterUtil.createConferenceType(typename, comments) ) {		
				List result = ParameterUtil.getConfTypeForQue("");
				request.setAttribute("result",result);
				return mapping.findForward("viewconftype");
			} 
			return mapping.findForward("error");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}
}
