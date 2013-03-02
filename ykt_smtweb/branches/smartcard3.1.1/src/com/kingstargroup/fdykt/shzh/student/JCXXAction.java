package com.kingstargroup.fdykt.shzh.student;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.SHZHDao;

/**
 * 查询学生奖学金信息
 * 
 * @author Yiming.You
 * 
 */
public class JCXXAction extends Action {
	private static final Logger logger = Logger.getLogger(JCXXAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");
		if (cardphyid == null || "".equals(cardphyid)) {
			session.setAttribute("REQ_URL", request.getRequestURL());
			 return mapping.findForward("logon");
		}
		try {
			String xh = request.getSession().getAttribute("stuempno").toString();

			int currentPage = 1;
			if (StringUtils.isNotBlank((request.getParameter("currentPage")))) {
				currentPage = Integer.parseInt(request.getParameter("currentPage"));
			}
			int pageCount = 10;
			int totalPage = 1;
			List<Map> result = SHZHDao.getXsjxj(xh);
			if (result.size()!=0 && result.size() / pageCount == 0) {
				totalPage = result.size() / pageCount;
			} else {
				totalPage = result.size() / pageCount + 1;
			}
			int start = (currentPage - 1) * pageCount;
			int end = currentPage * pageCount - 1;
			if (end > result.size() - 1) {
				end = result.size() - 1;
			}
			if(result.size()>0){
				result = result.subList(start, end);
			}

			request.setAttribute("result", result);
			request.setAttribute("currentPage", Integer.valueOf(currentPage));
			request.setAttribute("totalPage", Integer.valueOf(totalPage));

			return mapping.findForward("success");
		} catch (Exception e) {
			logger.error("查询学生奖学金信息失败：" + e);
			request.setAttribute("errmsg", "查询学生奖学金信息失败：" + e.getMessage());
			return mapping.findForward("failure");
		}
	}
}
