package com.liferay.portal.score.action;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.LabelValueBean;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;

public class StudentScoreAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
        List yearList =new ArrayList();
		HttpSession ses = req.getSession();
		String userid = ses.getAttribute(WebKeys.USER_ID).toString();
		if (userid == null) {
			return mapping.findForward(Constants.COMMON_REFERER);
		}
		//Integer beginDate = new Integer(DateFormatUtil.getDateLaterNow().substring(0, 4));
		//Integer endDate =new Integer(beginDate.intValue()+1);
		String firstyear="2007";
	    String view="2007--2008Äê";
		//yearList =new  ConnectDatabase().getStudentYear(userid);
		LabelValueBean   label   =   new   LabelValueBean(view,firstyear);
		
		 yearList.add(label);
		//req.setAttribute("beginDate", beginDate);
		//req.setAttribute("endDate",endDate);
		
		req.setAttribute("yearList", yearList);
		return mapping.findForward("portlet.ecardtransaction.studentscore");
	}
}
