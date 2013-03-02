package com.kingstargroup.conference.action.series;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.CardReadThread;

public class ReadcardStartAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionErrors messages = new ActionErrors();
		try {
			CardReadThread cardread = new CardReadThread();
			cardread.start();
			messages.add("errorinfo", new ActionError("readcard.threadstartok"));
			saveErrors(request, messages);
			return mapping.findForward("deviceconf");
		} catch (Exception e) {
			e.printStackTrace();
		}
		messages.add("errorinfo", new ActionError("readcard.threadstartfailue"));
		saveErrors(request, messages);
		return mapping.findForward("deviceconf");
	}

}
