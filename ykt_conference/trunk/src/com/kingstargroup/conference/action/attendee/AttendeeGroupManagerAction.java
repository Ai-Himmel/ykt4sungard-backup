package com.kingstargroup.conference.action.attendee;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;


/**
 * @author hjw人员分组维护
 *
 */
public class AttendeeGroupManagerAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String cmd = ParamUtil.getString(request,"cmd");
		String custIds = ParamUtil.getString(request,"selectvalue");
		int groupid=ParamUtil.getInteger(request,"groupname");
		if ("query".equals(cmd)){
				request.setAttribute("result", AttendeeUtil.getCustListByGroupId(groupid));
				request.setAttribute("groupid",new Integer(groupid).toString());
				return mapping.findForward("attendeemanagerlist");
		}else if ("delete".equals(cmd)){
			AttendeeUtil.deleteCustGroup(groupid,custIds);
			request.setAttribute("tipinfo","人员从组中删除成功！");
			return mapping.findForward("succeed");			
		}
		return null;
	}
}
