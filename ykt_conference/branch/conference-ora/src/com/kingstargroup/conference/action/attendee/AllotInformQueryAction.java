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

public class AllotInformQueryAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		int confid = ParamUtil.getInteger(request,"confid");
		String custno = ParamUtil.getString(request,"custno");
		String custname = ParamUtil.getString(request,"custname");
		String dept = ParamUtil.getString(request,"dept");
		String duty = ParamUtil.getString(request,"duty");
		//HttpSession session = request.getSession();
		if (confid==0){
			request.setAttribute("tipinfo","当前没有已经分配人员的会议！");
			return mapping.findForward("error");
		}
		try {
			List list = AttendeeUtil.getAttendeeListBy(confid,custno,custname,dept,duty);
			if (null==list){
				request.setAttribute("tipinfo","没有你要的查询");
				return mapping.findForward("error");
			}
			if (AttendeeUtil.getMesListIfSucceed(confid)){
				request.setAttribute("tip","有未下发到的人员名单或时间段，请重新下发该会议！");
			}else{
				request.setAttribute("tip","该会议人员名单和时间段都已下发成功！");
			}
			if (AttendeeUtil.ifSendBySucceed(confid)){
				request.setAttribute("tip","该会议还没有下发人员名单！");
			}else{
				request.setAttribute("tip","该会议人员名单和时间段都已下发成功！");
			}
			request.setAttribute("result",list);
			request.setAttribute("confid",new Integer(confid));
			request.setAttribute("custno",custno);
			request.setAttribute("custname",custname);
			request.setAttribute("dept",dept);
			request.setAttribute("duty",duty);
			return mapping.findForward("queryresult");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}

}
