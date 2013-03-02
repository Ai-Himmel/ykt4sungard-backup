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
		String[] delId = request.getParameterValues("ids_allbox");
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		if (delId != null) {
			try {
				ConferenceUtil.deleteConference(delId);
				request.setAttribute("result",ConferenceUtil.getAllConference(username));			
				return mapping.findForward("defconflist");
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return mapping.findForward("error");
	}
}
