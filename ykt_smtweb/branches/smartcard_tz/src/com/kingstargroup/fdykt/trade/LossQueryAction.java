package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2TPifAreaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class LossQueryAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(LossQueryAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("failure");
		try {
			forward = doLossQuery(mapping, request);
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLossQuery(ActionMapping mapping,
			HttpServletRequest request) {
		HttpSession session = request.getSession();
		Cookie[] cooks = request.getCookies();
		String temp = "";
		String areano = "";
		if (cooks != null) {
			for (int i = 0; i < cooks.length; i++) {
				Cookie cookie = cooks[i];
				temp = cookie.getName();
				if ("school".equals(temp)) {
					areano = cookie.getValue();
					break;
				}
			}
		}
		try{
		DB2TPifAreaDAO area = new DB2TPifAreaDAO();
		ArrayList areaList = null;
		areaList = area.DB2getSchoolArea();
		session.setAttribute("areaList", areaList);
		session.setAttribute("cookieschool", areano);
		return mapping.findForward("logon");
		} catch (Exception e) {
			session.setAttribute("areaList",null);
			session.setAttribute("cookieschool", areano);
			return mapping.findForward("logon");
		}
		
	}
}
