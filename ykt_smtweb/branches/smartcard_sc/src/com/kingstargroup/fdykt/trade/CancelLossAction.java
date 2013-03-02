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

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;

import java.sql.SQLException;

public class CancelLossAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CancelLossAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		if (session.getAttribute("cardid") == null)
			return mapping.findForward("index");
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("error");
		try {
			if (doUnloss(mapping, request, session)) {
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			} else {
				forward = mapping.findForward("failure");
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
			logger.error("事务失败:解挂卡失败");
		}
		return forward;
	}

	private boolean doUnloss(ActionMapping mapping, HttpServletRequest request,
			HttpSession session) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();
		String cardid = ((Long) session.getAttribute("card_id")).toString();
		String cutid = ((Integer) session.getAttribute("cutid")).toString();
		ActionErrors errors = new ActionErrors();
		// 取得系统日期时间
		try {
			String sysdate = new DB2SysParaDAO().getDBDateTime();
			String systime = sysdate.substring(8);
			sysdate = sysdate.substring(0, 8);
			card = carddao.getCardInfo(cardid);
			String state = card.getStateId();
			if (state == null || state.length() != 4)
				return false;
			char[] stateAry = state.toCharArray();
			if (KSConstant.BOOLEAN_TRUE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
				errors.add("100561", new ActionError("errors.100561"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return false;
			}
			// 检查卡状态是否为挂失
			int flag = carddao.isCancel(cutid, cardid);
			if (flag != 0) {
				// 允许重复解挂 modify by 汤成 2005-05-15
				/*
				 * if (flag == 100559) { ActionErrors errors = new
				 * ActionErrors(); errors.add("100559", new
				 * ActionError("errors.100559")); if (!errors.isEmpty()) {
				 * saveErrors(request, errors); }
				 * //System.out.println("-------------2-----------"); return
				 * mapping.findForward("failure"); } else
				 */
				if (flag == KSConstant.MAINCARD_UNLOSSED) {					
					errors.add("100560", new ActionError("errors.100560"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					logger.info("还有卡未挂失,所有要先挂失,custno[" + cutid + "]");
					return false;
				}
			}
			// 重复解挂要求下传名单			
			// 如果该卡号被冻结,则挂失时对黑名单不处理
			if (KSConstant.BOOLEAN_FALSE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
//				// 状态作为黑名单的有效状态,不作为卡状态
//				carddao.updateLossState(sysdate, cardid);
//				// 修改原来的黑名单的状态标志为无效
//				// 插入黑名单表
//				BlackSheetDTO blacksheet = new BlackSheetDTO();
//				blacksheet.setCardId(cardid);
//				blacksheet.setIsAd("1");
//				blacksheet.setOperateDate(sysdate);
//				blacksheet.setOperateTime(systime);
//				blacksheet.setStateId("1");
//				blacksheet.setValiddate("501230121212");
//				blacksheet.setVolume(sysdate.substring(2, 8) + systime);
//				carddao.createBlackSheet(blacksheet);
//				// 广播黑名单
//				MesListDTO meslist = new MesListDTO();
//				String incontent = "<CARDID>" + cardid + "</CARDID>"
//						+ "<VERNUM>" + blacksheet.getVolume() + "</VERNUM>"
//						+ "<ADDDELSIGN>" + blacksheet.getIsAd()
//						+ "</ADDDELSIGN>";
//				meslist.setIncontent(incontent);
//				meslist.setFunId("930005");
//				meslist.setLevel("1");
//				meslist.setEcode("9999");
//				meslist.setStateId("1");
//				meslist.setIndt(sysdate + systime);
//				session.setAttribute("blkversion", blacksheet.getVolume());
//				carddao.createMesList(meslist);
//				// 修改卡状态为解挂状态
//
//				stateAry[KSConstant.CARDSTAT_TYPE_LOST] = KSConstant.BOOLEAN_FALSE;
//				carddao.updateCardState(cardid, String.valueOf(stateAry));
//				// 准备数据插入交易流水表
//				TradeSerialDTO tradeserial = new TradeSerialDTO();
//				tradeserial.setOperate_Date(sysdate);
//				tradeserial.setOperate_time(systime);
//				tradeserial.setCollect_Date(sysdate);
//				tradeserial.setCollect_time(systime);
//				tradeserial.setEnterAct_time(systime);
//				tradeserial.setSerial_type("930002");
//				tradeserial.setSerial_state(9);
//				tradeserial.setCustomer_id((new Integer(cutid)).longValue());
//				tradeserial.setCard_id((new Integer(cardid)).longValue());
//				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
//				tradeserialdao.createTradeSerial(tradeserial);
//				return true;
				long xpackhandle = 0;
				int drtpno = 0;
				int errcode[] = { 1 };
				byte errmsg[] = new byte[300];
				int branchno = 0;// 后台drtp功能号
				int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
						"mainfunction", 9000);
				int func = KSConfiguration.getInstance().getPropertyAsInt(
						"logicfunc_card_loss_cancel", 847103);// 后台业务功能号
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
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
								Integer.parseInt(cutid));// 客户号
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
								Integer.parseInt(cardid));// 卡号
						bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
								.getBytes(), "web".getBytes());//密码

						boolean bccret = false;
						while (--tries >= 0) {
							bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
									mainfunction, 2000, errcode, errmsg);
							if (bccret) {
								break;
							}
						}
						if (bccret) {
							bcc.GetRetCode(xpackhandle, RetCode);
							bcc.GetRecordCount(xpackhandle, RecordCount);
							if (0 == RetCode[0]) {
								if (0 < RecordCount[0]) {
									
									byte[] BlkVersion = new byte[13];
									bcc.GetStringFieldByName(xpackhandle, 0, "sserial0"
											.getBytes(), BlkVersion, 13);
									int i = 0;
									for (i = 0; i < BlkVersion.length; i++) {
										if (0 == BlkVersion[i]) {
											break;
										}
									}
									String blk_version = new String(BlkVersion, 0, i);
									
									request.setAttribute("blkversion", blk_version);							
									return true;
								} else {
									errors.add("lost", new ActionError("后台处理失败"));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return false;
								}
							} else {
								// 失败
								if (0 < RecordCount[0]) {
									byte[] vsmess = new byte[300];
									bcc.GetStringFieldByName(xpackhandle, 0,
											"vsmess".getBytes(), vsmess, 300);
									int i;
									for (i = 0; i < vsmess.length; i++) {
										if (vsmess[i] == 0) {
											break;
										}
									}
									String vs_mess = new String(vsmess, 0, i,"GB2312");
									errors.add("lost", new ActionError(vs_mess));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return true;
								} else {
									errors.add("lost", new ActionError("后台处理失败"));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return false;
								}

							}

						} else {
							// 请求失败
						
							errors.add("lost", new ActionError("errors.request"));
							if (!errors.isEmpty()) {
								saveErrors(request, errors);
							}
							return false;
						
						}
					}
					errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;

				} catch (Exception e) {
					// TODO: handle exception
					logger.error(e.getMessage());
					errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;
				} catch (UnsatisfiedLinkError e) {
					logger.error(e.getMessage());
					errors.add("lost", new ActionError("系统出现异常，请稍后重试！"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;
				} finally {
					if (xpackhandle != 0) {
						bcc.DeleteXpackHandle(xpackhandle);
					}
				}
			}
			return false;
		} catch (Exception e) {
			logger.error("解挂卡失败:" + e.getMessage());
			return false;
		}
	}

}
