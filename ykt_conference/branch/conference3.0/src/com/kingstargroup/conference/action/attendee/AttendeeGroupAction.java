package com.kingstargroup.conference.action.attendee;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;

public class AttendeeGroupAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String cmd = request.getParameter("cmd");
		String custno = request.getParameter("custno");
		String custname = request.getParameter("custname");
		String duty = request.getParameter("duty");
		String dept = request.getParameter("dept");
		String custIds = request.getParameter("groupedlist");
		String groupname=ParamUtil.getString(request,"groupname");
		String custNames = request.getParameter("custNames");
		int confid = 0;
		List custList = null;
		if ("query".equals(cmd)){
			if (("".equals(custno.trim())) && ("".equals(custname)) && ("".equals(duty))
					&& ("-".equals(dept))) {
				request.setAttribute("tipinfo","请输入查询条件，否则速度会很慢!");
				return mapping.findForward("error");
			}else{
				if (AAUtils.isAjaxRequest(request)) {
					List result = AttendeeUtil.getCustList(custno,custname,duty,dept,custNames,confid,custList);
					request.setAttribute("result", result);
					AAUtils.addZonesToRefresh(request, "custlist");
					return mapping.findForward("attendeegrouplist");
				}
			}
		}else if ("group".equals(cmd)){
			if ("".equals(groupname)){
				request.setAttribute("tipinfo","请选择要分组的组名称！");
				return mapping.findForward("error");
			}
			if (AttendeeUtil.attendeeGroup(groupname,custIds)){
				request.setAttribute("tipinfo","分组成功!");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","分组失败，请检查原因!");
				return mapping.findForward("error");
			}
		}
		return null;
	}
}
