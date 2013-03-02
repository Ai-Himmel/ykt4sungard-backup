package com.kingstargroup.conference.action.conference;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class ConferenceDeleteAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		String confids = request.getParameter("confid");
		if(confids.lastIndexOf(",")==-1){
			request.setAttribute("tipinfo","��ѡ��Ҫɾ���Ļ��飡");
			return mapping.findForward("error");
		}
		confids = confids.substring(0,confids.lastIndexOf(","));
		String[] delId = confids.split(",");
				
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		if (delId != null) {
			try {
				if(ConferenceUtil.canbedeleteofconference(delId)){
				ConferenceUtil.deleteConference(delId);
				request.setAttribute("result",ConferenceUtil.getAllConference(username));			
				return mapping.findForward("defconflist");
				}else{
					request.setAttribute("tipinfo","�ѿ������ڿ��Ļ��鲻��ɾ����");
					return mapping.findForward("error");
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		request.setAttribute("tipinfo","ɾ��ʧ�ܣ�");
		return mapping.findForward("error");
	}
}
