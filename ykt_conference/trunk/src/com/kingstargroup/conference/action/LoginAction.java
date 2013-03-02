package com.kingstargroup.conference.action;

import java.util.Date;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.common.WebKeys;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.mail.SendMailLotus;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.OperatorUtil;
import com.octo.captcha.image.ImageCaptcha;

public class LoginAction extends Action {

	Logger loginfo = Logger.getLogger("Businesslog");
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		String username = ParamUtil.getString(request, "username");
		String password = ParamUtil.getString(request, "password");
		String authCode = ParamUtil.getString(request, "authCode");
		//OAMailSender.sendMail("测试会议签到系统oa发送通知","test","mwu","测试");
		String[] p = new String[1];
		p[0] = "mwu";
		new SendMailLotus().startSend(1, p, "mailtest", "10.108.0.99",
                "10.108.0.99", "why i's check it!", 25, 1,
                new Date(), "127.0.0.1", "mailtest", "password", "0",
                "0", 0, "127.0.0.1");
		if (username.equals("")) {
			return mapping.findForward("conference.login");
		}
		ImageCaptcha captcha = (ImageCaptcha) request.getSession().getAttribute(WebKeys.CAPTCHA);
		if (captcha == null) {
			return mapping.findForward("conference.login");
		}
		Boolean validResponse = captcha.validateResponse(authCode);
		if ((validResponse == null) ||
				(validResponse.equals(Boolean.FALSE))) {
			request.getSession().removeAttribute(WebKeys.CAPTCHA);
			SessionErrors.add(request, "system.error.validate");
			return mapping.findForward("conference.login");
		}
		
		if (!OperatorUtil.login(username, password)) {
			SessionErrors.add(request, "system.error.validate");
			request.getSession().removeAttribute(WebKeys.CAPTCHA);
			return mapping.findForward("conference.login");
		}
		HttpSession session = request.getSession();
		session.setAttribute("username", username);
		WebKeys.USER_KEY = username;
		WebKeys.USER_DEPT = GetDictionary.getDeptByOperCode(username);
		OperatorUtil.createLoginInfo(username);
		loginfo.info(username+"：login conference system");
		if (OperatorUtil.getUserParentFuncList(username).size() == 0) {
			return mapping.findForward("conference.warning"); 
		}
		return mapping.findForward("conference.main");
	}

}
