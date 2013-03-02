package com.kingstargroup.fdykt.cityhotspot;

import java.math.BigDecimal;
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
import com.kingstargroup.fdykt.trade.ElecCheckAction;
import com.kingstargroup.fdykt.util.BdUtil;

public class CityHotspotPutInAction extends Action {

	private static final Logger logger = Logger
			.getLogger(ElecCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		String cardId = request.getParameter("cardId");
		System.out.println("------cardId----------"+cardId);
		String money = request.getParameter("money");
		System.out.println("------money----------"+money);
		String card_bala = request.getParameter("cardBala");
		System.out.println("------card_bala----------"+card_bala);
		String cxCnt = request.getParameter("cxCnt");
		System.out.println("------cxCnt----------"+cxCnt);
		//String pwd = request.getParameter("pwd")==null?"":request.getParameter("pwd").toString();
		//System.out.println("------pwd----------"+cxCnt);
		request.setAttribute("cardId", cardId);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", card_bala);
		//request.setAttribute("pwd",pwd);
		
		double cardBala = Double.parseDouble(card_bala);
		cardBala = cardBala / 100;
		String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
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
				"logicfunc_elect_check", 847316);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			System.out.println("------bcc----------");
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			
			if (0 != xpackhandle) {
				System.out.println("------xpackhandle----------");
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt("240209"));// 请求号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));// 卡号
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						cardBala);// 入卡值
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
						Double.parseDouble(money));// 交易金额
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(cxCnt));// 交易次数
			  //  bcc.SetStringFieldByName(xpackhandle, 0,"sserial1".getBytes(),pwd.getBytes());//转帐密码
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());// 操作员
				System.out.println("------xpackhandle---end-------");
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					System.out.println("------bccret---true-------");
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					System.out.println("------RetCode[0]----------"+RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							double[] OutCardAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), OutCardAmount);
							double[] TransAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), TransAmount);
							int[] SerialNo = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), SerialNo);
							double[] Price = new double[1];//(分)
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt2"
									.getBytes(), Price);
						/*	byte[] sbankname = new byte[81];
							bcc.GetStringFieldByName(xpackhandle, 0,
									"sbankname".getBytes(), sbankname, 81);*/

							/*String out_card_amount = String
									.valueOf(OutCardAmount[0] * 100);*/
							
							String out_card_amount = BdUtil.round(OutCardAmount[0],100,2,BigDecimal.ROUND_HALF_UP);
							
							String serial_no = String.valueOf(SerialNo[0]);

							/*int i = 0;
							for (i = 0; i < sbankname.length; i++) {
								if (0 == sbankname[i]) {
									break;
								}
							}*/
						

							//String sbankname_s = new String(sbankname, 0, i);
							request.setAttribute("serialNo", serial_no);
							request.setAttribute("outCardAmount",out_card_amount);
							request.setAttribute("cxCnt",cxCnt);
							//request.setAttribute("sbankname", sbankname_s);
							return mapping.findForward("success");
						} else {
							
							request.setAttribute("errmsg", "后台处理失败");
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
							String vs_mess = new String(vsmess, 0, i,"GB2312");
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
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
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，未找到cpackfile，请稍后重试！");
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}
