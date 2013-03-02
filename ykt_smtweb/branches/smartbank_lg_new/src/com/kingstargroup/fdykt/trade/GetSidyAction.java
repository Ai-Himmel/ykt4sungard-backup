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
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class GetSidyAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSidyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetSidy(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetSidy(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		String card_id = request.getParameter("cardId");
		
		String card_bala = request.getParameter("cardBala");
		String tx_cnt = request.getParameter("txCnt");
		//System.out.println("txcnt---------------"+tx_cnt);
		String ParamKey = request.getParameter("paramKey");
		//System.out.println("paramkey---------------"+ParamKey);
		String sidyno = request.getParameter("sidyno");
		//System.out.println("sidyno---------------"+sidyno);
		String  deviceId = request.getParameter("deviceId");
		if (card_id == null || null == card_bala || "".equals(card_bala)
				|| "".equals(card_id) || null == ParamKey
				|| "".equals(ParamKey) || null == tx_cnt || "".equals(tx_cnt)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("7777", "重新登陆", "", "",
					"", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		int  CardBala = Integer.parseInt(card_bala);
		
		String hexcardno = Integer.toHexString(Integer.parseInt(card_id))
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
			request.setAttribute("msg","补助领取失败，校园卡卡号不存在");
			return mapping.findForward("returninfo");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 9000);
		System.out.println("----mainfunction---------"+mainfunction);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_sidy", 240104);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();

			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240104".getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sname".getBytes(),
						sidyno.getBytes());
				System.out.println("----sidyno---------"+sidyno);
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));
				System.out.println("----card.getCardId()---------"+card.getCardId());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						CardBala);
				System.out.println("----cCardBala---------"+CardBala);
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(tx_cnt));
				
				System.out.println("----tx_cnt---------"+tx_cnt);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),deviceId.getBytes());//设备号
				
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 5000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					System.out.println("----getSidyAction---retcode---------"+RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							int[] SidyAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(), SidyAmount);
							
							System.out.println("----SidyAmount------------"+SidyAmount[0]);
							
							int[] OutCardAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
									.getBytes(), OutCardAmount);
							
							System.out.println("----OutCardAmount------------"+OutCardAmount[0]);
							
							byte[] SerialNo = new byte[26];
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial1"
									.getBytes(), SerialNo, 26);
							int i = 0;
							for (i = 0; i < SerialNo.length; i++) {
								if (0 == SerialNo[i]) {
									break;
								}
							}
							
							String cout_card_amount = String
									.valueOf(OutCardAmount[0]);
							String serial_no = new String(SerialNo, 0, i);
							System.out.println("----补助领取成功---------"+RetCode[0]);
							String xmlout = XMLGenerateUtil.SidyXMLGenerate("0000",
									"补助领取成功"+RetCode[0], String.valueOf(SidyAmount[0]),
									cout_card_amount, serial_no, ParamKey,
									card_id, null,tx_cnt,"1");
							//System.out.println("---xmlout--------"+xmlout);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							System.out.println("----无数据返回---------"+RetCode[0]);
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!"+RetCode[0], "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
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
							System.out.println("----失败---------"+RetCode[0]);

							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess+RetCode[0], "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!"+RetCode[0], "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
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
				/*	System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);*/
					System.out.println("---- 请求失败---------"+RetCode[0]);
					
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + RetCode[0], "", "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			System.out.println("---- 系统出现异常，请稍后重试！-1002--------"+RetCode[0]);
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			System.out.println("---- 系统出现异常，请稍后重试！---1003------"+RetCode[0]);
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
