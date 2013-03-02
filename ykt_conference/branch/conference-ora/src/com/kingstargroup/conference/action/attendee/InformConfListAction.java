package com.kingstargroup.conference.action.attendee;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class InformConfListAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
		try {
			request.setAttribute("result",ConferenceUtil.getAllConference(username));			
			return mapping.findForward("informconflist");
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}

}
