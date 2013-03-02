package com.kingstargroup.fdykt.logon;

import java.sql.SQLException;
import java.util.ArrayList;

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

import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.dto.TTifSubsidyDTO;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class SidyLogonAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(SidyLogonAction.class);

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
		HttpSession session = request.getSession();
		String cardno = (String) request.getAttribute("cardno");		
		String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
		.toUpperCase();
		
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("index");
		try {
			
			DB2CardDAO carddao = new DB2CardDAO();

			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoById(hexcardno);
			
			
			if (card == null) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.password"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("logonerror");
			}else{
				String  stateId = card.getStateId();
				if("1100".equals(stateId)){
					request.setAttribute("errmsg","卡已挂失,不能领取补助");
					return mapping.findForward("failure");
				}else if("1010".equals(stateId)) {
					request.setAttribute("errmsg","卡已冻结,不能领取补助");
					return mapping.findForward("failure");
				}
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();		
				int count = tradeserialdao.getSidyCountByCustNo(card.getCosumerId());			
				if(0==count){
					//没有补助
					return (mapping.findForward("null"));
				}else{
					
					ArrayList ttifsidys = new ArrayList();
					Integer page = new Integer(1);
					
                    //查询出所有的未领取补助，一次领取完毕。
					
					ttifsidys = tradeserialdao.getSidyByCardId(card.getCardId(),page.intValue());
					Integer all = new Integer(tradeserialdao.getSidyCountByCardId(card.getCardId()));
					session.setAttribute("ttifsidys", ttifsidys);
					session.setAttribute("page", page);
					session.setAttribute("all", all);
					session.setAttribute("cardno",cardno);
					session.setAttribute("cardId",card.getCardId());
				}
				return (mapping.findForward("success"));
			}
			
			
		} catch (Exception e) {
			logger.error(e.getMessage());
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
	}
}
