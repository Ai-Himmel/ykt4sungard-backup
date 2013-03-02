package com.kingstargroup.fdykt.turnover;

import java.sql.SQLException;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;

public class DoTurnOverAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DoTurnOverAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrun(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrun(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		String cardId = request.getParameter("cardId");
		if(null==cardId){			
			cardId = (String) session.getAttribute("cardId");
		}
		
		DB2CardDAO carddao = new DB2CardDAO();

		ActionErrors errors = new ActionErrors();
		if (null == cardId) {
			errors.add("errinfo", new ActionError("¿¨ºÅÎª¿Õ"));
			if (!errors.isEmpty()) {
				saveErrors(request, errors);
			}
			return mapping.findForward("index");
		}
		
		String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
		.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		
		Integer page = new Integer(request.getParameter("page")==null?"1":request.getParameter("page"));

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
			List list =carddao.getBmTestInfo(card.getCardId(),(page.intValue() - 1) * 10 + 1);
			Integer all = new Integer(carddao.getBmTestInfoCount(card.getCardId()));
			session.setAttribute("page", page);
			session.setAttribute("bminfos", list);
			session.setAttribute("all", all);
			session.setAttribute("cardId", cardId);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("¿¨ÐÅÏ¢¶ÁÈ¡Ê§°Ü");
			System.out.println("¿¨ÐÅÏ¢¶ÁÈ¡Ê§°Ü");
		}
		
		
		return mapping.findForward("success");
		
	}
}
