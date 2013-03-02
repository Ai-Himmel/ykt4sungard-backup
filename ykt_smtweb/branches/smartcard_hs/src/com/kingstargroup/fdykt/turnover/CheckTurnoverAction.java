package com.kingstargroup.fdykt.turnover;

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
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CheckTurnoverAction  extends Action {
	
	private static final Logger logger = Logger
	.getLogger(CheckTurnoverAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doturn(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doturn(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DB2CardDAO carddao = new DB2CardDAO();
		String cardId = request.getParameter("cardId");//������
		String card_bala = request.getParameter("cardBala");
		request.setAttribute("cardId", cardId);
		request.setAttribute("cardBala", card_bala);
		String txCnt = request.getParameter("txCnt");
		double cardBala = Double.parseDouble(card_bala);
		cardBala = cardBala / 100.0;
		String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			System.out.println("����Ϣ��ȡʧ��");
			String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("7777", "����Ϣ��ȡʧ��", "", "",
					"", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_turnover", 847316);// ��̨ҵ���ܺ�
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
						Integer.parseInt("240405"));// �����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));// ����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(txCnt));//���״���
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						cardBala);// �뿨ֵ
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());// ����Ա

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
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

							String out_card_amount = BdUtil.round(OutCardAmount[0], 100, 2, BigDecimal.ROUND_HALF_UP);

							String serial_no = String.valueOf(SerialNo[0]);

//							request.setAttribute("serialNo", serial_no);
//							request.setAttribute("outCardAmount",
//									out_card_amount);

							String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("0000",
									"�ɷѽ���ѯ", String.valueOf(TransAmount[0]),
									String.valueOf(out_card_amount), serial_no, cardId, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", null);
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
							String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("0002",
									vs_mess, "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", null);
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
					String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("1001",
							"��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s, "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("1002",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "",  null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("1003",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "",  null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}catch(UnsatisfiedLinkError e){
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("1004",
					"ϵͳ��ʼ���쳣�����Ժ����ԣ�", "", "", "", "",  null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
		//for test
//		String xmlout = XMLGenerateUtil.TurnOverXMLGenerate("0000",
//				"�ɷѽ���", String.valueOf("1"),
//				String.valueOf(100), "22222", cardId, null);
//		XMLGenerateUtil.XMLSendOut(request, response,
//				xmlout);
//		return null;
		

	}

}
