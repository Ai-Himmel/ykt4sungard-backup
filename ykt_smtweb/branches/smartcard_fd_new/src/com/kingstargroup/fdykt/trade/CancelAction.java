package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;

public class CancelAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CancelAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		
		KSDaoSessionFactory.createSession();

		ActionForward forward = doAccountInfo(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doAccountInfo(ActionMapping mapping,
			HttpServletRequest request) {
		try {
			
			DB2CardDAO carddao = new DB2CardDAO();
			String cardno = request.getParameter("cardno");
			CardDTO card = carddao.getCardInfoByCardNo(cardno);
			if (card == null) {
				return mapping.findForward("msg");
			}
			String cardId = card.getCardId();
			DB2AccountDAO accountdao = new DB2AccountDAO();
			AccountDTO account = accountdao.getAccountInfoByCardId(cardId);
			if (account == null) {
				return (mapping.findForward("isnull"));
			}
			
			
			request.setAttribute("account", account);
            
			return (mapping.findForward("success"));

		} catch (Exception e) {
			logger.error("查询客户信息失败");
			return (mapping.findForward("failure"));
		}
	}
}
