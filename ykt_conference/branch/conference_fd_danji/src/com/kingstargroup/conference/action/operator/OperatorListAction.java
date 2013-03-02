/**
 * 
 */
package com.kingstargroup.conference.action.operator;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.OperatorUtil;



/**
 * @author º«¼ÍÎ°
 *
 */
public class OperatorListAction extends Action {

	public  ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response)
			throws Exception {
		List result = OperatorUtil.getAllOperatorList();
		request.setAttribute("result",result);
		return mapping.findForward("operatorlist");
	}
}
