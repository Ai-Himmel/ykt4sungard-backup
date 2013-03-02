package com.kingstargroup.fdykt.cardcard;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.CardDTO;

public class CardCardPutinAction extends Action {
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
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String money = request.getParameter("money");
		String cardphyno = request.getParameter("cardphyno");
		String cardbalance = request.getParameter("cardbalance");
		String cardcnt = request.getParameter("cardcnt");
		String outcardphyno = request.getParameter("outcardphyno");
		String outcardbalance = request.getParameter("outcardbalance");
		String outcardcnt = request.getParameter("outcardcnt");


		ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		CardDTO outcard = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyno);
			outcard =  carddao.getCardInfoById(outcardphyno);
		} catch (Exception e) {
			// TODO: handle exception
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "卡信息读取失败,或者卡片状态非正常。"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
		AccountDTO accdto = new AccountDTO();
		AccountDTO outaccdto= new AccountDTO();;
		String accname = "";
		String outaccname = "";
		String stuempno="";
		String outstuempno="";
		try {
			
			
			accdto = accdao.getAccountInfoByCardno(String.valueOf(card
					.getCardno()));
			accname = accdto.getCustname();
			stuempno = accdto.getStuempno();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			outaccdto = accdao.getAccountInfoByCardno(String.valueOf(outcard
					.getCardno()));
			outaccname = outaccdto.getCustname();
			outstuempno = outaccdto.getStuempno();
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		request.setAttribute("accname", accname);
		request.setAttribute("outaccname", outaccname);
		request.setAttribute("stuempno", stuempno);
		request.setAttribute("outstuempno", outstuempno);
		request.setAttribute("money", money);
		request.setAttribute("cardphyno", cardphyno);
		request.setAttribute("cardbalance", cardbalance);
		request.setAttribute("cardcnt", cardcnt);
		request.setAttribute("outcardphyno", outcardphyno);
		request.setAttribute("outcardbalance", outcardbalance);
		request.setAttribute("outcardcnt", outcardcnt);
		return (mapping.findForward("success"));
	}
}
