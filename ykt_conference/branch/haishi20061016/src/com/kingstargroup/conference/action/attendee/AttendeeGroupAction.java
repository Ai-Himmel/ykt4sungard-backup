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
				request.setAttribute("tipinfo","�������ѯ�����������ٶȻ����!");
				return mapping.findForward("error");
			}else{
				List result = AttendeeUtil.getCustList(custno,custname,duty,dept);
				if (null==result){
					request.setAttribute("tipinfo","û�м�¼��������ָ����ѯ������");
					return mapping.findForward("error");
				}
				request.setAttribute("result", result);
				return mapping.findForward("attendeegrouplist");
			}
		}else if ("group".equals(cmd)){
			if ("".equals(groupname)){
				request.setAttribute("tipinfo","��ѡ��Ҫ����������ƣ�");
				return mapping.findForward("error");
			}
			if (AttendeeUtil.attendeeGroup(groupname,custIds)){
				request.setAttribute("tipinfo","����ɹ�!");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","����ʧ�ܣ�����ԭ��!");
				return mapping.findForward("error");
			}
		}
		return null;
	}
}
