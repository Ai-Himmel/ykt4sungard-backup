package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;

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
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class GetSidyQueryAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSidyQueryAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doSidyLogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doSidyLogin(ActionMapping mapping, HttpServletRequest request) {
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = (String) request.getParameter("cardphyid");	//物理卡号
		String sidyno = (String) request.getParameter("sidyno");//补助批次号
		String reqpage = request.getParameter("page");

		ActionErrors errors = new ActionErrors();
		String reqip = request.getRemoteAddr();
//		 reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			
			System.out.print("补助领取ip请求："+reqip);
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		if (cardphyid == null || "".equals(cardphyid))
			return mapping.findForward("logon");
		try {
			DB2CardDAO carddao = new DB2CardDAO();

			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoById(cardphyid);
			
			if (card == null) {				
				return mapping.findForward("carderror");
			}else{
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();		
				int count = tradeserialdao.getSidyCountByCustid(card.getCustid());			
				if(0==count){
					//没有补助
					return (mapping.findForward("null"));
				}else{
					ArrayList ttifsidys = new ArrayList();
					Integer page = new Integer(1);
					if(reqpage!=null){
						page = new Integer(reqpage);
					}
					
//					查询出所有的未领取补助，一次领取完毕。
					ttifsidys = tradeserialdao.getAssistanceSerial(card.getCustid(),(page.intValue() - 1) * 10 + 1 );
					request.setAttribute("ttifsidys", ttifsidys);
					request.setAttribute("page", page);
					request.setAttribute("count", String.valueOf(count));
					request.setAttribute("cardphyid", cardphyid);			
					request.setAttribute("sidyno", sidyno);	
					request.setAttribute("cardno", String.valueOf(card.getCardno()));
				}
				return (mapping.findForward("success"));
			}
			
			
		} catch (Exception e) {
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
			"function.error"));
			saveErrors(request, errors);
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
	}
}
