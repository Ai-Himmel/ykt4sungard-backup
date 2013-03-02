package com.kingstargroup.fdykt.trade;

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
		HttpSession session = request.getSession();
		String cardno = (String) request.getParameter("cardno");	
		String card_bala = request.getParameter("cardBala");
		//session.setAttribute("cardno", cardno);
		String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
		.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("logon");
		try {
			DB2CardDAO carddao = new DB2CardDAO();

			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoById(hexcardno);
			
			if (card == null) {
				return mapping.findForward("logon");
			}else{
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();		
				int count = tradeserialdao.getSidyCountByCustNo(card.getCosumerId());			
				if(0==count){
					//没有补助
					return (mapping.findForward("null"));
				}else{
					ArrayList ttifsidys = new ArrayList();
					Integer page = new Integer(1);
					
					//返回第一条需要领取的
				    //SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//设备授权密钥
					//TTifSubsidyDTO subsidy = tradeserialdao.getAssistanceByCustNo(card.getCosumerId());
//					查询出所有的未领取补助，一次领取完毕。
					
					ttifsidys = tradeserialdao.getSidyByCardId(card.getCardId(),page.intValue());
					Integer all = new Integer(tradeserialdao.getSidyCountByCardId(card.getCardId()));
							
					session.setAttribute("ttifsidys", ttifsidys);
					/*session.setAttribute("begin", begin);
					session.setAttribute("end", end);*/
					session.setAttribute("page", page);
					session.setAttribute("all", all);
				/*	Integer cutId = subsidy.getCustNo();
					CustomerDTO dto = tradeserialdao.getcustomer(cutId);
					if(dto!=null){
						request.setAttribute("cut_id", cutId);
						request.setAttribute("stuemp_no", dto.getStuemp_no());
						request.setAttribute("cut_name", dto.getCut_name());
					}
					request.setAttribute("subsidy", subsidy);*/
					request.setAttribute("count", String.valueOf(count));
					request.getSession().setAttribute("cardno", cardno);				
					request.getSession().setAttribute("cardId", card.getCardId());
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
