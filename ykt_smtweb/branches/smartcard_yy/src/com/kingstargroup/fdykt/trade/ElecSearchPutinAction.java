package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;

public class ElecSearchPutinAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ElecSearchPutinAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = docheck(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward docheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		String cardId = request.getParameter("cardId");

		String room = request.getParameter("room");

		request.setAttribute("room", room);
		request.setAttribute("cardId", cardId);


		String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
				.toUpperCase();
		
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_elect_search", 847322);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));// 卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						room.getBytes());// 房间号

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 2000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				logger.info("-----bccret-----"+bccret);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					logger.info("-----RetCode-----"+RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							byte[] sstation0 = new byte[17];
							bcc.GetStringFieldByName(xpackhandle, 0, "sstation0"
									.getBytes(), sstation0, 17);
							
							byte[] sstation1 = new byte[17];
							bcc.GetStringFieldByName(xpackhandle, 0, "sstation1"
									.getBytes(), sstation1, 17);
							
							byte[] sbank_acc = new byte[17];
							bcc.GetStringFieldByName(xpackhandle, 0, "sbank_acc"
									.getBytes(), sbank_acc, 17);
							
                           try{
							String sstation_0 = new String(sstation0, 0, 16);
							//logger.info("-----sstation_0-----"+sstation_0);
							String sst_0_str = Float.toString(Float.parseFloat(sstation_0)/100);
							//logger.info("-----sst_0_str-----"+sst_0_str);
							request.setAttribute("sstation0", sst_0_str);
							

							String sstation_1 = new String(sstation1, 0, 16);
							//logger.info("-----sstation_1-----"+sstation_1);
							String sst_1_str = Float.toString(Float.parseFloat(sstation_1)/100);
							//logger.info("-----sst_1_str-----"+sst_1_str);
							request.setAttribute("sstation1", sst_1_str);
							
							
							String sbankacc = new String(sbank_acc,0,16);
							//logger.info("-----sbankacc-----"+sbankacc);
							if(sbankacc.indexOf("-")!=-1){
								sbankacc = sbankacc.substring(sbankacc.indexOf("-"));
							}
							//logger.info("-----sbankacc-----"+sbankacc);
							String sb_1_str = Float.toString(Float.parseFloat(sbankacc)/100);
							//logger.info("-----sb_1_str-----"+sb_1_str);
							request.setAttribute("sbank_acc", sb_1_str);
                           }catch(NumberFormatException e){
                        	   request.setAttribute("errmsg", "该卡未绑定房间无法查询,请先为该房间充值");
                        	   return mapping.findForward("failure");
                           }

							return mapping.findForward("success");
						} else {
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}
							String vs_mess = new String(vsmess, 0, i);
							request.setAttribute("errmsg", vs_mess+RetCode[0]);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败

					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String s = new String(errmsg, 0, i);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，请稍后重试,cpack文件没找到！");
			return mapping.findForward("failure");
		
		} catch (UnsatisfiedLinkError e) {
				e.printStackTrace();
				request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
				return mapping.findForward("failure");
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！Exception");
			return mapping.findForward("failure");
		
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
