package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.Arrays;

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
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CardTransOkAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CardTransOkAction.class);

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
		DB2AccountDAO accdao = new DB2AccountDAO();

		String card_id = request.getParameter("cardId");
		String card_bala = request.getParameter("cardBala");
		String tx_cnt = request.getParameter("txCnt");
		String ParamKey = request.getParameter("paramKey");
		String oldCardNo = request.getParameter("oldCardNo");
		String oldCardBalance = request.getParameter("oldCardBalance");
		String serialNo = request.getParameter("serialNo");
		String sdate = request.getParameter("sdate3");

		if (null == card_id || null == card_bala || null == tx_cnt
				|| null == ParamKey || null == oldCardNo
				|| null == oldCardBalance || "".equals(card_id)
				|| "".equals(card_bala) || "".equals(tx_cnt)
				|| "".equals(ParamKey) || "".equals(oldCardNo)
				|| "".equals(oldCardBalance)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("1000", "�������ݴ���!", "",
					"", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		String hexcardno = Integer.toHexString(Integer.parseInt(card_id))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		// ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("����Ϣ��ȡʧ��");
			System.out.println("����Ϣ��ȡʧ��");
			String xmlout = XMLGenerateUtil.XMLGenerate("0001", "����Ϣ��ȡʧ��!", "",
					"", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		// try {
		// deviceid = accdao.getdevidFromip(reqip);
		// if (deviceid < 0) {
		// String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
		// "�豸ûע�ᣬ����ʹ�ñ����ܣ� ", "", "", "", "", null);
		// return mapping.findForward("failure");
		// }
		// } catch (Exception e1) {
		// e1.printStackTrace();
		// String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
		// "�豸ûע�ᣬ����ʹ�ñ����ܣ� ", "", "", "", "", null);
		// return mapping.findForward("failure");
		// }
		deviceid = 1;
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_cardtrans_check", 846329);// ��̨ҵ���ܺ�
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
				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), String.valueOf(deviceid).getBytes());// �ն˺�
				bcc.SetIntFieldByName(xpackhandle, 0, "lbank_acc_type"
						.getBytes(), 1);// ���ױ�־

				bcc.SetIntFieldByName(xpackhandle, 0, "lserial1".getBytes(),
						Integer.parseInt(serialNo));// ��ˮ��

				bcc.SetStringFieldByName(xpackhandle, 0, "sdate3".getBytes(),
						sdate.getBytes());// ����

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth"
						.getBytes(), DateUtil.getNow().getBytes());// ���ͷ�ƾ֤��

				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation1".getBytes(), hexcardno.getBytes());// ������

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// ����

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// ������ǰ���(��)

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(tx_cnt));// ���״���
				bcc.SetIntFieldByName(xpackhandle, 0, "lsafe_level".getBytes(),
						Integer.parseInt(oldCardBalance));// ת�˽��(��)

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(oldCardNo));// �Ͽ�����

				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] inStr = new byte[300];
							int[] intRec = new int[1];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lserial1"
									.getBytes(), intRec);// ��ˮ��
							String serial_no = String.valueOf(intRec[0]);

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), intRec);// ���֣�
							String out_card_amount = String.valueOf(intRec[0]);

							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3"
									.getBytes(), inStr, 300);
							String sdate3 = BccUtil.getStringFromByte(inStr);

							request.setAttribute("serialNo", serial_no);
							request.setAttribute("sdate3", sdate3);
							request.setAttribute("outCardAmount",
									out_card_amount);
							
							String stime3 = DateUtil.getNow().substring(8);

							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"����ת�˳ɹ�", oldCardBalance, out_card_amount,
									serial_no, "", card_id, tx_cnt, "", sdate3,stime3,
									null);
							System.out.println(DateUtil.getNow() + " ����="
									+ card_id + " ����ת�˳ɹ�����Ӧ��ˮ��=" + serial_no
									+ "ת�˽��=" + oldCardBalance);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", "", "", "", "","",
									null);
							System.out.println(DateUtil.getNow() + " ����="
									+ card_id + " ����ת��ʧ�ܣ�������" + RetCode[0]);
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

							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess, "", "", "", "", "", "", "", "","",
									null);
							System.out.println(DateUtil.getNow() + " ����="
									+ card_id + " ����ת��ʧ�ܣ�������" + RetCode[0]
									+ "������Ϣ��" + vs_mess);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"�����ݷ���!", "", "", "", "", "", "", "", "","",
									null);
							System.out.println(DateUtil.getNow() + " ����="
									+ card_id + " ����ת��ʧ�ܣ�������" + RetCode[0]
									+ "�޴�����Ϣ");
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
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s, "", "", "", "", "", "","",
							"", "", null);
					System.out.println(DateUtil.getNow() + " ����=" + card_id
							+ " ����ת��ʧ�ܣ�������" + RetCode[0] + "������ʧ��");
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", "","", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", "", "","", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1004",
					"ϵͳ��ʼ���쳣�����Ժ����ԣ�", "", "", "", "", "", "","", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
