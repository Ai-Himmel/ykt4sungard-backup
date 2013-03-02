package com.kingstargroup.fdykt.shzh.student;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * ��ѯѧ����ҵ��Ϣ
 * 
 * @author Yiming.You
 * 
 */
public class JYXXAction extends Action {
	private static final Logger logger = Logger.getLogger(JYXXAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");
		if (cardphyid == null || "".equals(cardphyid)) {
			session.setAttribute("REQ_URL", request.getRequestURL());
//			return mapping.findForward("logon");
		}
		try {

			return mapping.findForward("success");
		} catch (Exception e) {
			logger.error("��ѯѧ����ҵ��Ϣʧ�ܣ�" + e);
			request.setAttribute("errmsg", "��ѯѧ����ҵ��Ϣʧ�ܣ�" + e.getMessage());
			return mapping.findForward("failure");
		}
	}
}
