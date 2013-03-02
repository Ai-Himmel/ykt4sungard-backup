package com.kingstargroup.fdykt.trade;

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

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;

import java.sql.SQLException;
import java.util.*;

public class LossCardAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LossCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.getInputForward();
		HttpSession session = request.getSession();
		if (session.getAttribute("stuempno") == null)
			return forward;
		KSDaoSessionFactory.createSession();
		try {
			forward = doLossCard(mapping, request, session);
			if (forward.getName().equals("success")) {
				KSDaoSessionFactory.commit();
			} else {
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally{
			KSDaoSessionFactory.closeSession();
		}
		return forward;
	}

	private ActionForward doLossCard(ActionMapping mapping,
			HttpServletRequest request, HttpSession session) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();

		String cutid = ((Integer) session.getAttribute("cutid")).toString();
		String stuempno = (String) session.getAttribute("stuempno");
		try {
			DB2AccountDAO accountdao = new DB2AccountDAO();
			ArrayList accounts = accountdao.getAccountInfo(stuempno);
			if (accounts.size() == 0) {
				return (mapping.findForward("isnull"));
			}
			AccountDTO account = (AccountDTO) accounts.get(0);
			String cardid = String.valueOf(account.getCard_id());

			card = carddao.getCardInfo(cardid);
			String state = card.getStateId();
			// 检查客户信息，判断是否可以挂失
			if (state.substring(0, 4).equals(KSConstant.CARDSTAT_LOGOUT)) {
				ActionErrors errors = new ActionErrors();
				errors.add("unable", new ActionError("errors.unable"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			if (state.substring(1, 2).equals("1")) {
				ActionErrors errors = new ActionErrors();
				errors.add("lost", new ActionError("errors.lost"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			// 插入卡挂失有效期限表
			/*
			Calendar now = Calendar.getInstance();
			String year = (new Integer(now.get(Calendar.YEAR))).toString();
			String month = (new Integer(now.get(Calendar.MONTH) + 1))
					.toString();
			if (month.length() == 1) {
				month = "0" + month;
			}
			String day = (new Integer(now.get(Calendar.DATE))).toString();
			if (day.length() == 1) {
				day = "0" + day;
			}
			String hour = (new Integer(now.get(Calendar.HOUR))).toString();
			if (hour.length() == 1) {
				hour = "0" + hour;
			}
			String minute = (new Integer(now.get(Calendar.MINUTE))).toString();
			if (minute.length() == 1) {
				minute = "0" + minute;
			}
			String second = (new Integer(now.get(Calendar.SECOND))).toString();
			if (second.length() == 1) {
				second = "0" + second;
			}
			*/
			
			String sysdate = new DB2SysParaDAO().getDBDateTime();
			String systime = sysdate.substring(8);
			sysdate = sysdate.substring(0,8);
			String enddate = carddao.getEndDate();
			CardLossInfoDTO lossinfo = new CardLossInfoDTO();
			lossinfo.setBeginDate(sysdate);
			lossinfo.setCardId(cardid);
			lossinfo.setEndDate(enddate);
			lossinfo.setOperateDate(sysdate);
			lossinfo.setOperateTime(systime);
			lossinfo.setStateId("1");
			carddao.createLossInfo(lossinfo);
			// 如果该卡号被冻结,则挂失时对黑名单不处理
			if (state.substring(2, 3).equals("0")) {
				// 插入黑名单表
				BlackSheetDTO blacksheet = new BlackSheetDTO();
				blacksheet.setCardId(cardid);
				blacksheet.setIsAd("0");
				blacksheet.setOperateDate(sysdate);
				blacksheet.setOperateTime(systime);
				blacksheet.setStateId("1");
				blacksheet.setValiddate("501230121212");
				blacksheet.setVolume(sysdate.substring(2, 8) + systime);
				carddao.createBlackSheet(blacksheet);
				// 广播黑名单
				MesListDTO meslist = new MesListDTO();
				String incontent = "<CARDID>" + cardid + "</CARDID>"
						+ "<VERNUM>" + blacksheet.getVolume() + "</VERNUM>"
						+ "<ADDDELSIGN>" + blacksheet.getIsAd()
						+ "</ADDDELSIGN>";
				meslist.setIncontent(incontent);
				meslist.setFunId("930005");
				meslist.setLevel("1");
				meslist.setEcode("9999");
				meslist.setStateId("1");
				meslist.setIndt(sysdate + systime);
				carddao.createMesList(meslist);
			}
			// 修改卡状态为挂失
			carddao.updateCardState(cardid, "1100");
			// 准备数据插入交易流水表
			TradeSerialDTO tradeserial = new TradeSerialDTO();
			tradeserial.setOperate_Date(sysdate);
			tradeserial.setOperate_time(systime);
			tradeserial.setCollect_Date(sysdate);
			tradeserial.setCollect_time(systime);
			tradeserial.setEnterAct_time(systime);
			tradeserial.setSerial_type("930001");
			tradeserial.setSerial_state(9);
			tradeserial.setCustomer_id((new Integer(cutid)).longValue());
			tradeserial.setCard_id((new Integer(cardid)).longValue());
			DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
			tradeserialdao.createTradeSerial(tradeserial);
			return mapping.findForward("success");
		} catch (Exception e) {
			logger.error("挂失卡失败 : " + e.getMessage() + ", stuempno[" + stuempno
					+ "]");
			return mapping.findForward("failed");
		}
	}
}
