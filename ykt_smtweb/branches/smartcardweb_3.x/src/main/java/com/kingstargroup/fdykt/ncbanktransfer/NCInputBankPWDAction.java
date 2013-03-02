package com.kingstargroup.fdykt.ncbanktransfer;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class NCInputBankPWDAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String cardphyid = request.getParameter("cardphyid");
		String money = request.getParameter("money");
		String card_bala = request.getParameter("cardBala");
		String dptCardCnt = request.getParameter("dptCardCnt");
		String payCardCnt = request.getParameter("payCardCnt");
		String bankcardinfo = request.getParameter("bankcardinfo");
		String bankcardno = request.getParameter("bankcardno");
		if("".equals(bankcardinfo)){
			request.setAttribute("errmsg", "银行卡信息读取失败，请重新转账刷卡！ ");
			return mapping.findForward("failure");
		}
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("dptCardCnt", dptCardCnt);
		request.setAttribute("payCardCnt", payCardCnt);
		request.setAttribute("cardBala", card_bala);
		request.setAttribute("bankcardinfo", bankcardinfo);
		request.setAttribute("bankcardno", bankcardno);
		
		return mapping.findForward("success");
	}
}
