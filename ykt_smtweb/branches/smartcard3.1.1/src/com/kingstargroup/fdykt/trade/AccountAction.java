package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;


public class AccountAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AccountAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		ActionForward forward = mapping.findForward("logon");
		if (session.getAttribute("cardno") == null){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return forward;
		}
		KSDaoSessionFactory.createSession();
		
		forward = doAccountInfo(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doAccountInfo(ActionMapping mapping, HttpServletRequest request) {
		HttpSession session = request.getSession();
		String cardno = (String) session.getAttribute("cardno");
		String custid = (String) session.getAttribute("cutid");
		try {
			
			DB2AccountDAO accountdao = new DB2AccountDAO();
			AccountDTO account = accountdao.getAccountInfoByCardno(cardno);
			if (account == null) {
				return (mapping.findForward("isnull"));
			}
			session.setAttribute("card_id", String.valueOf(account.getCardno()));
			session.setAttribute("account", account);
		} catch (Exception e) {
			logger.error("查询客户信息失败");
			return (mapping.findForward("failure"));
		}
		
		DB2NetAccDAO netaccdao = new DB2NetAccDAO();
		NetAccDTO netacc = new NetAccDTO();
		try {
			netacc = netaccdao.getNetAccInfoByCustid(custid);
			if(netacc==null){
				request.setAttribute("isnetaccnull", true);
				return (mapping.findForward("failure"));
			}
		} catch (Exception e) {
			request.setAttribute("isnetaccnull", true);
			logger.error("查询电子钱包账户信息失败");
			return (mapping.findForward("failure"));
		}
		
		request.setAttribute("isnetaccnull", false);
		request.setAttribute("netacc_no", String.valueOf(netacc.getAccno()));
		request.setAttribute("netacc", netacc);
		return (mapping.findForward("success"));
		
	}
}
