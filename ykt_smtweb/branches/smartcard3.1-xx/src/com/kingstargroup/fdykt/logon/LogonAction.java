package com.kingstargroup.fdykt.logon;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionError;

import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.Util;

import java.io.IOException;
import java.sql.SQLException;
import java.util.*;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class LogonAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LogonAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doLogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		if(forward.equals(mapping.findForward("success"))){
			if(request.getSession().getAttribute("REQ_URL")!=null){
				try {
					response.sendRedirect(request.getSession().getAttribute("REQ_URL").toString());
					
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}	
				return null;
			}else{
				return forward;
			}
			
		}else{
			return forward;
		}
	}

	private ActionForward doLogin(ActionMapping mapping, HttpServletRequest request) {
		String cardphyid = request.getParameter("cardphyid");
		String password = request.getParameter("password");
		DB2CustomerDAO customerdao = new DB2CustomerDAO();
		DB2CardDAO carddao = new DB2CardDAO();
		DB2DeviceDAO devicedao = new DB2DeviceDAO();
		DB2TradeCodeDAO tradecodedao = new DB2TradeCodeDAO();
		try {
			if (null == password || "".equals(password)) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.emptypwd"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.getInputForward();
			}

			String ciphered = Util.DESEnc(password);
//			logger.debug("password:" + ciphered);
			 
			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoByIdPwd(cardphyid, ciphered);

			if (card == null) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.password"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} else {
				String sql = "select * from ykt_cur.t_customer cus "
						+ "where cus.custid= " + card.getCustid();
				ArrayList customers = customerdao.RetriveCustomer(sql);
				HttpSession session = request.getSession(true);
//				logger.info("Time out:"	+ session.getMaxInactiveInterval());
				HashMap device = devicedao.RetriveDevice();
				HashMap trademsg = tradecodedao.RetriveTradeMsgs();
				
				if (customers.size() > 0) {
					CustomerDTO custDTO = (CustomerDTO) customers.get(0);
					long custid = custDTO.getCustid();
					String custname = custDTO.getCustname();
					String stuempno = custDTO.getStuempno();
					if(stuempno!=null){
						stuempno= stuempno.toUpperCase();
					}
					session.setAttribute("name", custname);
					session.setAttribute("cutid", String.valueOf(custid));
					session.setAttribute("stuempno", stuempno);
			}
				session.setAttribute("cardno", String.valueOf(card.getCardno()));
				session.setAttribute("device", device);
				session.setAttribute("trademsg", trademsg);
				session.setAttribute("cardphyid", cardphyid);
				session.setAttribute("password", password);			
				
				
				return (mapping.findForward("success"));
			}
		} catch (Exception e) {
			logger.error(e.getMessage());
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
	}
}
