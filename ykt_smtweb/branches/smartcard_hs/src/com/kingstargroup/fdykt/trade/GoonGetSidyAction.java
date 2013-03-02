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

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.dto.SysParaDTO;
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
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doSidyLogin(ActionMapping mapping, HttpServletRequest request) {
	//	HttpSession session = request.getSession();
		String cardno = request.getParameter("cardno");
		try {
			DB2CardDAO carddao = new DB2CardDAO();
			DB2SysParaDAO sysParadao = new DB2SysParaDAO();
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
				request.setAttribute("msg","对不起,功能暂不可用,请稍后重试！");
				return mapping.findForward("failure");
			}else{
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();		
				int count = tradeserialdao.getSidyCountByCustNo(card.getCosumerId());			
				if(0==count){
					//没有补助
					return (mapping.findForward("null"));
				}else{
					//返回第一条需要领取的
					SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//设备授权密钥
					TTifSubsidyDTO subsidy = tradeserialdao.getAssistanceByCustNo(card.getCosumerId());
					Integer cutId = subsidy.getCustNo();
					CustomerDTO dto = tradeserialdao.getcustomer(cutId);
					if(dto!=null){
						request.setAttribute("stuemp_no", dto.getStuemp_no());
						request.setAttribute("cut_name", dto.getCut_name());
					}
					request.setAttribute("subsidy", subsidy);
					request.setAttribute("count", String.valueOf(count));
					request.setAttribute("cardno", cardno);			
					request.setAttribute("cardid", card.getCardId());
					request.setAttribute("paramKey", sysPara.getValue());//设备授权密钥
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
