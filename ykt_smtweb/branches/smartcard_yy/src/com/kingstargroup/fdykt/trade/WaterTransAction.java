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

public class WaterTransAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(WaterTransAction.class);

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
		String cardId = request.getParameter("cardId");
		String money = request.getParameter("money");
		String serialNo = request.getParameter("serialNo");
		if (null == cardId ||  null == money
				|| null == serialNo || "".equals(cardId)
				||  "".equals(money)
				|| "".equals(serialNo)) {
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
					"1000", "�������ݴ���!", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response,
					xmlout);
			return null;
		}
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
			logger.error("����Ϣ��ȡʧ��");
			System.out.println("����Ϣ��ȡʧ��");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_water_trans", 847317);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						Integer.parseInt("240300"));//�����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));//����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(serialNo));//��ˮ��
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
						Double.parseDouble(money));//���׽��
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());//����Ա
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
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
							String out_card_amount = String
									.valueOf(OutCardAmount[0] * 100);
							String serial_no = String.valueOf(SerialNo[0]);
							request.setAttribute("serialNo", serial_no);
							request.setAttribute("outCardAmount", out_card_amount);
	
							String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
									"0000", "ˮ��ת�˳ɹ�", String
											.valueOf(TransAmount[0]),
											out_card_amount, serial_no, "00", cardId,
									null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
									"0001", "�����ݷ���!", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// ʧ��
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

							String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
									"0002", vs_mess, "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
									"0001", "�����ݷ���!", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					}

				} else {
					// ����ʧ��

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
					String xmlout = XMLGenerateUtil.MoblileXMLGenerate("1001",
							"��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s, "", "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate("1002",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate("1003",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate("1004",
					"ϵͳ��ʼ���쳣�����Ժ����ԣ�", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
