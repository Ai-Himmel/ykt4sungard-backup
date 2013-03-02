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
			request.setAttribute("tipinfo","请选择要删除的会议！");
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
					request.setAttribute("tipinfo","已开或正在开的会议不能删除！");
					return mapping.findForward("error");
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		request.setAttribute("tipinfo","删除失败！");
		return mapping.findForward("error");
	}
}
