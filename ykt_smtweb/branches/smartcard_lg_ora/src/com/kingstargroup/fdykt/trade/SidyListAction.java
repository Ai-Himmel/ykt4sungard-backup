package com.kingstargroup.fdykt.trade;

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

import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;

/**
 * @author jackey
 *
 */
public class SidyListAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SidyListAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetSidy(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetSidy(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String sidyno = request.getParameter("sidyno");
		String cardno = request.getParameter("cardId");
		try {
			DB2CardDAO carddao = new DB2CardDAO();
			String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
			.toUpperCase();
			for (int i = hexcardno.length(); i < 8; i++) {
				hexcardno = "0" + hexcardno;//pad left
			}
			logger.debug("physical cardno:" + hexcardno);
			 
			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoById(hexcardno);
			
			if (card == null) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.password"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}else{
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();		
				int count = tradeserialdao.getSidyCountByCardId(card.getCardId(),sidyno);			
					
					request.setAttribute("count", String.valueOf(count));
					request.setAttribute("cardno", cardno);		
					request.setAttribute("sidyno", sidyno);

				return (mapping.findForward("success"));
			}
			
			
		} catch (Exception e) {
			logger.error(e.getMessage());
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}

	}
}
