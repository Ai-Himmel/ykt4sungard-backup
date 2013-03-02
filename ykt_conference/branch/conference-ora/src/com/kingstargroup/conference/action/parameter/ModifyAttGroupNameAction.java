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
import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.dao.AttGroupNameDAO;
import com.kingstargroup.conference.hibernate.form.TGroup;

/**
 * @author Õı”®
 *
 */
public class ModifyAttGroupNameAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String operId = GetterUtil.get((String) request.getSession().getAttribute("username"), "");		
		String groupName = ParamUtil.getString(request, "groupName");
		String comments = ParamUtil.getString(request, "comments");
		String groupid = ParamUtil.getString(request, "groupid");
		Integer id;
		if("".equals(groupid)) {
			return mapping.findForward("error");
		}
		id = Integer.valueOf(groupid);
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		String oldname = "";		
		
		try {
			if(dao.findByPrimaryKey(TGroup.class, id) != null) {
				oldname = ((TGroup)dao.findByPrimaryKey(TGroup.class, id)).getGroupName();			
			}
			if(!oldname.equals(groupName)) {
				List list = dao.getAttGroupName(groupName);
				if (!list.isEmpty()) {
					SessionErrors.add(request, "attgroupname.failed.groupname");
					return mapping.getInputForward();
				}
			}
			
			if ( ParameterUtil.modifyAttGroupName(id, operId, groupName, comments) ) {
				return mapping.findForward("viewattgroupname");
			}
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
		return null;
	}
}
