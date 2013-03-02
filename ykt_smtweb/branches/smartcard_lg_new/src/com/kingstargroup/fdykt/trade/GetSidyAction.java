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
		String ParamKey = request.getParameter("paramKey");
		if (card_id == null || null == card_bala || "".equals(card_bala)
				|| "".equals(card_id) || null == ParamKey
				|| "".equals(ParamKey) || null == tx_cnt || "".equals(tx_cnt)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("7777", "���µ�½", "", "",
					"", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		double CardBala = Double.parseDouble(card_bala);
		CardBala = CardBala / 100;
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
			logger.error("����Ϣ��ȡʧ��"); 
			System.out.println("����Ϣ��ȡʧ��");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_sidy", 847315);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
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
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						CardBala);
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(tx_cnt));
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());
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
							double[] SidyAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), SidyAmount);
							double[] OutCardAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt2"
									.getBytes(), OutCardAmount);
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
									.valueOf(OutCardAmount[0] * 100);
							String serial_no = new String(SerialNo, 0, i);
							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"������ȡ�ɹ�", String.valueOf(SidyAmount[0]),
									cout_card_amount, serial_no, ParamKey,
									card_id, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return  null;
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
                            vs_mess = vs_mess + RetCode[0];
                            System.out.println("error"+vs_mess);
							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess, "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", "", null);
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
					s = s + RetCode[0];
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s, "", "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}catch(UnsatisfiedLinkError e){
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1004",
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
