package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class ElecPutinAction extends Action {
	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String cardId = request.getParameter("cardId");//ŒÔ¿Ìø®∫≈long
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		request.setAttribute("cardId", cardId);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		return mapping.findForward("success");
	}
}
