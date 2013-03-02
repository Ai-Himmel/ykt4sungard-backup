package com.kingstargroup.fdykt.rejie;

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
import com.kingstargroup.fdykt.trade.ElecTransAction;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class ReJieTransferAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ElecTransAction.class);  

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward; 
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		logger.info("---------瑞杰测试-------------");
		//System.out.println("---------瑞杰测试-------------");
		String cardId = request.getParameter("cardId");
		logger.info("---------cardId-------------"+cardId);
		//System.out.println("---------cardId-------------"+cardId);
		String money = request.getParameter("money");
		logger.info("---------money-------------"+money);
		//System.out.println("---------money-------------"+money);
		String serialNo = request.getParameter("serialNo");
		logger.info("---------serialNo-------------"+serialNo);
		//System.out.println("---------serialNo-------------"+serialNo);
		
		String chargeID = request.getParameter("chargeID");
		logger.info("---------chargeID-------------"+chargeID);
		//System.out.println("---------chargeID-------------"+chargeID);
		
		
		
		if (null == cardId || null == money || null == serialNo || null ==chargeID 
				|| "".equals(cardId) || "".equals(money) || "".equals(serialNo)  || "".equals(chargeID)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "请求数据错误!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
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
				"trans", 847317);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try { 
			
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			logger.info("---------xpackhandle-------------"+xpackhandle);
			System.out.println("---------xpackhandle-------------"+xpackhandle);
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt("240208"));// 请求号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));// 卡号
				//logger.info("---------卡号-------------"+card.getCardId());
				//System.out.println("---------卡号-------------"+card.getCardId());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(serialNo));// 流水号
				
				//logger.info("---------流水号-------------"+serialNo);
				//System.out.println("---------流水号-------------"+serialNo);
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
						Double.parseDouble(money));// 交易金额
				//logger.info("---------交易金额-------------"+money);
				//System.out.println("---------交易金额-------------"+money);
				bcc.SetStringFieldByName(xpackhandle, 0, "sall_name".getBytes(),
						chargeID.getBytes());// 网络收费ID
				//logger.info("---------网络收费ID-------------"+chargeID.getBytes());
				//System.out.println("---------网络收费ID-------------"+chargeID.getBytes());
				
				
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());// 操作员
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt("1"));
				boolean bccret = false;
				
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				//logger.info("---------bccret-------------"+bccret);
				//System.out.println("---------bccret-------------"+bccret);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
				//	logger.info("---------RetCode[0]=-------------"+RetCode[0]);
				//	System.out.println("---------RetCode[0]=-------------"+RetCode[0]);
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
							
							String  out_card_amount= String
									.valueOf(OutCardAmount[0] * 100);
							
							String serial_no = String.valueOf(SerialNo[0]);
							request.setAttribute("serialNo", serial_no);
							request.setAttribute("outCardAmount",
									out_card_amount);
							
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0000", "转账成功", String
											.valueOf(TransAmount[0]),
									out_card_amount, serial_no, cardId, null);
							System.out.println("TransAmount============="+String.valueOf(TransAmount[0]));
							
							System.out.println("out_card_amount==========="+out_card_amount);
							System.out.println("serial_no==========="+serial_no);
							System.out.println("xmlout==========="+xmlout);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							logger.info("---------0001=-------------"+RetCode[0]);
							System.out.println("---------0001=-------------"+RetCode[0]);
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回!"+RetCode[0], "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							logger.info("---------RetCode[0]=-------------"+RetCode[0]);
							System.out.println("---------RetCode[0]=-------------"+RetCode[0]);
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
							logger.info("---------0002=-------------"+vsmess+RetCode[0]);
							System.out.println("---------0002=-------------"+vsmess+RetCode[0]);
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0002", vs_mess+RetCode[0], "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							logger.info("---------0001=-------------"+RetCode[0]);
							System.out.println("---------0001=-------------"+RetCode[0]);
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回!"+RetCode[0], "", "", "", "", null);
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
					
					logger.info("---------1001=-------------"+RetCode[0]);
					System.out.println("---------1001=-------------"+RetCode[0]);
					String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " +RetCode[0], "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			logger.info("---------1002=-------------"+RetCode[0]);
			System.out.println("---------1002=-------------"+RetCode[0]);
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			logger.info("---------1003=-------------"+RetCode[0]);
			System.out.println("---------1003=-------------"+RetCode[0]);
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1003",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
			logger.info("---------1004=-------------"+RetCode[0]);
			System.out.println("---------1003=-------------"+RetCode[0]);
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1004",
					"系统初始化异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
