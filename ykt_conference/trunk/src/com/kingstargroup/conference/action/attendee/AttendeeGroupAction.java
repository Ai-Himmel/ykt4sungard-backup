package com.kingstargroup.conference.action.attendee;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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
		if ("query".equals(cmd)){
			if (("".equals(custno)) && ("".equals(custname)) && ("".equals(duty))
					&& ("-".equals(dept))) {
				request.setAttribute("tipinfo","请输入查询条件，否则速度会很慢!");
				return mapping.findForward("error");
			}else{
				List result = AttendeeUtil.getCustList(custno,custname,duty,dept);
				if (null==result){
					request.setAttribute("tipinfo","没有记录，请重新指定查询条件！");
					return mapping.findForward("error");
				}
				request.setAttribute("result", result);
				return mapping.findForward("attendeegrouplist");
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
