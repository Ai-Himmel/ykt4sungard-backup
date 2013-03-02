package com.kingstargroup.fdykt.cardcard;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
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

public class CardCardOutCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CardCardOutCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = docheck(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward docheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String outcardphyno = request.getParameter("outcardphyno");
		String outcardbalance = request.getParameter("outcardbalance");
		String outcardcnt = request.getParameter("outcardcnt");

		request.setAttribute("outcardphyno", outcardphyno);
		request.setAttribute("outcardbalance", outcardbalance);
		request.setAttribute("outcardcnt", outcardcnt);

		String hexcardno = Integer.toHexString(Integer.parseInt(outcardphyno))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}

		ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "卡信息读取失败,或者卡片状态非正常。"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
		AccountDTO accdto;
		String outaccname = "";
		String outstuempno =""; 
		try {
			accdto = accdao.getAccountInfoByCardId(String.valueOf(card.getCardno()));
			outaccname = accdto.getCustname();
			outstuempno = accdto.getStuempno();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 
		request.setAttribute("outaccname", outaccname);
		request.setAttribute("outstuempno", outstuempno);
		return mapping.findForward("success");

	}
}
