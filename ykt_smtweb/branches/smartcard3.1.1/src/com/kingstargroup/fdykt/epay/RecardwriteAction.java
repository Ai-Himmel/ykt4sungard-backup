package com.kingstargroup.fdykt.epay;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class RecardwriteAction  extends Action {
	/**
	 * Logger for this class
	 */
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(RecardwriteAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doRecardwrite(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward doRecardwrite(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String cardphyid = request.getParameter("cardphyid");//ŒÔ¿Ìø®∫≈
		String money = request.getParameter("money");
		String txCnt = request.getParameter("txCnt");
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");
		String cardBala = request.getParameter("cardBala");
		String outCardAmount = request.getParameter("outCardAmount");
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("sphone3", sphone3);
		request.setAttribute("saddr", saddr);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("outCardAmount", outCardAmount);
		
		return mapping.findForward("success");
	}
}
