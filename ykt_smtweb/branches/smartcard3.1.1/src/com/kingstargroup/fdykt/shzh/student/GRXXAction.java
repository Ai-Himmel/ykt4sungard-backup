package com.kingstargroup.fdykt.shzh.student;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.SHZHDao;

/**
 * 查询学生个人信息
 * 
 * @author Yiming.You
 * 
 */
public class GRXXAction extends Action {
	private static final Logger logger = Logger.getLogger(GRXXAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");
		if (cardphyid == null || "".equals(cardphyid)) {
			session.setAttribute("REQ_URL", request.getRequestURL());
			 return mapping.findForward("logon");
		}
		try {
			String xh = request.getSession().getAttribute("stuempno").toString();

			List<Map> result = SHZHDao.getXsjbsj(xh);
			if (result.size() == 0) {
				request.setAttribute("errmsg", "没有找到您的个人信息");
				return mapping.findForward("failure");
			}
			request.setAttribute("student", result.get(0));
			return mapping.findForward("success");
		} catch (Exception e) {
			logger.error(e);
			request.setAttribute("errmsg", "查询学生个人信息失败：" + e.getMessage());
			return mapping.findForward("failure");
		}
	}
}
