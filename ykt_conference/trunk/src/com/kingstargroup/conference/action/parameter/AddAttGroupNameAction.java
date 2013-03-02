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

import com.kingstargroup.conference.util.ParameterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.common.WebKeys;
import com.kingstargroup.conference.dao.AttGroupNameDAO;

/**
 * @author Õı”®
 *
 */
public class AddAttGroupNameAction extends Action {
	
	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form,
			HttpServletRequest request, 
			HttpServletResponse response) 
			throws Exception {
		String groupName = ParamUtil.getString(request, "groupName");
		String comments = ParamUtil.getString(request, "comments");
		String operId = WebKeys.USER_KEY;
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		
		try{
			List list = dao.getAttGroupName(groupName);
			if (!list.isEmpty()) {
				SessionErrors.add(request, "attgroupname.failed.groupname");
				return mapping.getInputForward();
			}
			if (ParameterUtil.createAttGroupName(operId, groupName, comments)){
				return mapping.findForward("viewattgroupname");
			}
			return mapping.findForward("error");
		}
		catch (Exception e) {
			return mapping.findForward("error");
		}
	}
}
