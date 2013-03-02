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
import com.kingstargroup.conference.mail.MailSender;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;
import com.kingstargroup.conference.util.GetDictionary;

public class AttendeeInformAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//ִ�в���
		String cmd =ParamUtil.getString(request,"cmd");
		//������
		int confid = ParamUtil.getInteger(request,"confid"); 
		if (confid == 0){
			request.setAttribute("result",ConferenceUtil.getAllConference());			
			return mapping.findForward("informconflist");
		}
		if ("inform".equals(cmd)){
			//�ӷ����еõ�����Ա�б�
			String custIdsGroup = ParamUtil.getString(request,"groupliststring");
			//�Ӳ�ѯ�еõ�����Ա�б�
			String custIdsQuery = ParamUtil.getString(request,"queryliststring");
			//�豸�б�
			String informcontext = ParamUtil.getString(request,"informcontent");
			//
			if (AttendeeUtil.attendeeInform(confid,custIdsGroup,custIdsQuery,informcontext)){
				//request.setAttribute("result",ConferenceUtil.getAllConference());
				//�·�����֪ͨ
				MailSender.mailsSender(confid);
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+":�·�֪ͨ�ɹ���");
				return mapping.findForward("succeed");
			}else{
				request.setAttribute("tipinfo",GetDictionary.getConfNameById(confid)+":�·�֪ͨʧ�ܣ�֪ͨ���ݲ��ܴ���1000�����֣��������·���");
				return mapping.findForward("error");
			}
		}else if("stage2".equals(cmd)){
			if (AAUtils.isAjaxRequest(request)){
				int groupid = ParamUtil.getInteger(request,"groupsrclist");
				request.setAttribute("refreshlist",AttendeeUtil.getCustListByGroupId(groupid));
		        AAUtils.addZonesToRefresh(request, "hanQueryList");
		    }
			return mapping.findForward("attendee.inform_stage2");
		}else if("stage3".equals(cmd)){
			String custno = ParamUtil.getString(request,"custno");
			String custname = ParamUtil.getString(request,"custname");
			String duty = ParamUtil.getString(request,"duty");
			String dept = ParamUtil.getString(request,"dept");
			if (("".equals(custno)) && ("".equals(custname)) && ("-".equals(duty))
					&& ("-".equals(dept))) {
				request.setAttribute("tipinfo","��ָ����ѯ������");
				return mapping.findForward("error");
			}else{
				List result = AttendeeUtil.getCustList(custno,custname,duty,dept);
				
				if (AAUtils.isAjaxRequest(request)){
					request.setAttribute("result", result);
					AAUtils.addZonesToRefresh(request,"hjwquerylist");
				}				
				return mapping.findForward("attendee.inform_stage3");
			}
		}else if("stage4".equals(cmd)){
			return mapping.findForward("attendee.inform_stage4");
		}else if("stage1".equals(cmd)){
			List result = AttendeeUtil.getAttendeeListByConfId(confid);
			request.setAttribute("result",result);
			return mapping.findForward("attendee.inform_stage1");
		}
		return null;
	}
	
}
