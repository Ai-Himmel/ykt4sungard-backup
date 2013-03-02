package com.kingstargroup.conference.action.sign;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

/**
 * 请假
 * @author hjw
 *
 */
public class LeaveAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm from, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String cmd = ParamUtil.getString(request,"cmd");
		int confid = ParamUtil.getInteger(request,"confid");
		if ("query".equals(cmd)){
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String deptcode = ParamUtil.getString(request,"deptcode");
			String duty = ParamUtil.getString(request,"duty");
			
			request.setAttribute("confid",new Integer(confid));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("duty",duty);
			request.setAttribute("deptcode",deptcode);
			request.setAttribute("result",AttendeeUtil.getCustListLeaveMap(confid,custno,custname,duty,deptcode));
			return mapping.findForward("leave");
			
		}else if ("sign".equals(cmd)){
			int custid = ParamUtil.getInteger(request,"custid");
			if (custid==0){
				request.setAttribute("tipinfo","请假失败:请选择要请假的员工！");
				return mapping.findForward("error");
			}
			if (SignUtil.getSignedOrNot(confid,custid)){
				
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"已经签到！");
				return mapping.findForward("error");
			}
			String reason = ParamUtil.getString(request,"reason");
			if (SignUtil.attendeeLeave(confid,custid,reason)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"请假成功！");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","请假失败，请检查原因！");
				return mapping.findForward("error");
			}
		}else if ("cleave".equals(cmd)){
			int custid = ParamUtil.getInteger(request,"custid");
			if (custid==0){
				request.setAttribute("tipinfo","消假失败:请选择要请假的员工！");
				return mapping.findForward("error");
			}
			if (SignUtil.getSignedOrNot(confid,custid)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"已经签到！");
				return mapping.findForward("error");
			}
			if (SignUtil.attendeeCancleLeave(confid,custid)){
				request.setAttribute("tipinfo",GetDictionary.getCustNameById(custid)+"消假成功！");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo","消假失败，请检查原因！");
				return mapping.findForward("error");
			}
		}
		return null;
	}

}
