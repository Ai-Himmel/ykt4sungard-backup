package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class WaterPutinAction extends Action {
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
		String cardId = request.getParameter("cardId");//物理卡号long
		String money = request.getParameter("money");//转账金额
		String waterBala = request.getParameter("waterBala");//一卡通余额
		String cardBala = request.getParameter("cardBala");//一卡通余额
		String txCnt = request.getParameter("txCnt");//交易次数
		request.setAttribute("cardId", cardId);
		request.setAttribute("money", money);
		request.setAttribute("waterBala", waterBala);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		return mapping.findForward("success");
	}
}
