package com.kingstargroup.fdykt.cardcard;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class CardTransRewriteAction extends Action {
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
		
		String money = request.getParameter("money");
		String outcardphyno = request.getParameter("outcardphyno");
		String outcardbalance = request.getParameter("outcardbalance");
		String outcardcnt = request.getParameter("outcardcnt");
		String out_card_amount = request.getParameter("outCardAmount");
		String sdate3 = request.getParameter("sdate3");
		String stime3 = request.getParameter("stime3");

		request.setAttribute("money", money);
		request.setAttribute("outcardphyno", outcardphyno);
		request.setAttribute("outcardbalance", outcardbalance);
		request.setAttribute("outcardcnt", outcardcnt);
		request.setAttribute("outCardAmount",out_card_amount);
		request.setAttribute("sdate3",sdate3);
		request.setAttribute("stime3",stime3);
		
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
		"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");
		
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		
		return (mapping.findForward("success"));
	}
}
