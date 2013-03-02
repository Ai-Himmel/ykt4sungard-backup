package com.kingstargroup.fdykt.trade;

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

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.BlackSheetDTO;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CardLossInfoDTO;
import com.kingstargroup.fdykt.dto.MesListDTO;
import com.kingstargroup.fdykt.dto.TradeSerialDTO;

public class LossCardAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LossCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.getInputForward();
		HttpSession session = request.getSession();
		if (null == session.getAttribute("card_id")
				|| null == session.getAttribute("stuempno"))
			return forward;
		forward = doLossCard(mapping, request, session);
		return forward;
	}
	
	private ActionForward doLossCard(ActionMapping mapping,
			HttpServletRequest request, HttpSession session) {
		String card_id =  session.getAttribute("card_id").toString();
		String deviceId = request.getParameter("deviceId");
		ActionErrors errors = new ActionErrors();
		
		if("".equals(deviceId)){
			errors.add("lost", new ActionError("lost","此机器未配置设备号"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
		
		
		
		try {			
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction", 8001);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_loss", 847102);// 后台业务功能号
			int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
					3);// 默认重试次数
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;

			try {
				bcc = BccctlInit.getBccctlInstance();				
				xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
						.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							Integer.parseInt(card_id));// 卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), "web".getBytes());// 操作员号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
							Integer.parseInt(deviceId));// 设备id
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),0);//子系统id

					boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 10000, errcode, errmsg);
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							return mapping.findForward("success");
						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								int i = 0;
								for (i = 0; i < vsmess.length; i++) {
									if (0 == vsmess[i]) {
										break;
									}
								}
								String vs_mess =  new String(vsmess, 0, i);
								
								errors.add("lost", new ActionError(vs_mess));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							} else {
								errors.add("lost", new ActionError("lost","后台处理失败"));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							}

						}

					} else {
						// 请求失败
						int i = 0;
						for (i = 0; i < errmsg.length; i++) {
							if (0 == errmsg[i]) {
								break;
							}
						}
						String errmsg_str =  new String(errmsg, 0, i);
						errors.add("lost", new ActionError("lost",errmsg_str));
						saveErrors(request, errors);
						return mapping.findForward("failure");
					
					}
				}
				errors.add("lost", new ActionError("lost","系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return mapping.findForward("failure");

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("lost","系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("lost","系统出现异常，请稍后重试！"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			logger.error("挂失卡失败 : " + e.getMessage() + ", card_id[" + card_id
					+ "]");
			errors.add("lost", new ActionError("lost","挂失卡失败!请稍后重试！"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
	}

	private ActionForward bakdoLossCard(ActionMapping mapping,
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
