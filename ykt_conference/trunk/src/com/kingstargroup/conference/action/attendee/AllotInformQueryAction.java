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
			request.setAttribute("tipinfo","��ǰû���Ѿ�������Ա�Ļ��飡");
			return mapping.findForward("error");
		}
		try {
			List list = AttendeeUtil.getAttendeeListBy(confid,custno,custname,dept,duty);
			if (null==list){
				request.setAttribute("tipinfo","û����Ҫ�Ĳ�ѯ");
				return mapping.findForward("error");
			}
			if (AttendeeUtil.getMesListIfSucceed(confid)){
				request.setAttribute("tip","��δ�·�������Ա������ʱ��Σ��������·��û��飡");
			}else{
				request.setAttribute("tip","�û�����Ա������ʱ��ζ����·��ɹ���");
			}
			if (AttendeeUtil.ifSendBySucceed(confid)){
				request.setAttribute("tip","�û��黹û���·���Ա������");
			}else{
				request.setAttribute("tip","�û�����Ա������ʱ��ζ����·��ɹ���");
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
