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

public class GoonGetSidyAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GoonGetSidyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doSidyLogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("�ύ����ʧ��");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doSidyLogin(ActionMapping mapping, HttpServletRequest request) {
		String sidyno = request.getParameter("sidyno");
		String cardno = request.getParameter("cardno");
		try {
			DB2CardDAO carddao = new DB2CardDAO();
			String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
			.toUpperCase();
			for (int i = hexcardno.length(); i < 8; i++) {
				hexcardno = "0" + hexcardno;//pad left
			}
			logger.debug("physical cardno:" + hexcardno);
			 
			// ��ѯ��Ψһ�Ŀ�
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
				if(0==count){
					//û�в���
					return (mapping.findForward("null"));
				}else{
					//���ص�һ����Ҫ��ȡ��
					TTifSubsidyDTO subsidy = tradeserialdao.getAssistanceByCardId(card.getCardId(),sidyno);
					Integer cutId = subsidy.getCustNo();
					CustomerDTO dto = tradeserialdao.getcustomer(cutId);
					if(dto!=null){
						request.setAttribute("cut_id", cutId);
						request.setAttribute("stuemp_no", dto.getStuemp_no());
						request.setAttribute("cut_name", dto.getCut_name());
					}
					request.setAttribute("subsidy", subsidy);
					request.setAttribute("count", String.valueOf(count));
					request.setAttribute("cardno", cardno);			
					request.setAttribute("cardid", card.getCardId());
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
