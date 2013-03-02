package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class ElecTransOkAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String cardphyid = request.getParameter("cardphyid");
		String money = request.getParameter("money");
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");		
		String outCardAmount = request.getParameter("outCardAmount");	
		String txCnt = request.getParameter("txCnt");
		String ipServer = request.getParameter("ipServer");
		String drtpPort = request.getParameter("drtpPort");
		String svrFunc = request.getParameter("svrFunc");		
		String sdate3 = request.getParameter("sdate3");	
		String stime3 = request.getParameter("stime3");	
		String room = request.getParameter("room");		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("sphone3", sphone3);
		request.setAttribute("saddr", saddr);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		request.setAttribute("sdate3", sdate3);
		request.setAttribute("stime3", stime3);
		request.setAttribute("outCardAmount", outCardAmount);
		request.setAttribute("room", room);
		return mapping.findForward("success");

	}
}
