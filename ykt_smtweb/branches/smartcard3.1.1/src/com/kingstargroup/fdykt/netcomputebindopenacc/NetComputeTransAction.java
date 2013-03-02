package com.kingstargroup.fdykt.netcomputebindopenacc;

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
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class NetComputeTransAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(NetComputeTransAction.class);

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
		String cardphyid = request.getParameter("cardphyid");
		String money = request.getParameter("money");
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");
		String stuempno = request.getParameter("stuempno");
		if (null == cardphyid || null == money || null == sphone3 || null==saddr
				|| "".equals(cardphyid) || "".equals(money) || "".equals(sphone3)||"".equals(saddr)||"".equals(stuempno)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "�������ݴ���!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
				String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001", "����Ϣ�쳣�������Ƿ�������!",
						"", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001", "����Ϣ��ȡʧ��!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		String reqip = request.getRemoteAddr();
//		reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002", "�豸δע�ᣬ����ʹ�ô˹���!",
						"", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002", "�豸δע�ᣬ����ʹ�ô˹���!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_thirdpay", 850005);// ��̨ҵ���ܺ�
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
						.getBytes(), 2);// ���ױ�־				
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(),
						sphone3.getBytes());// ���ײο���				
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						saddr.getBytes());// macУ����
				bcc.SetStringFieldByName(xpackhandle, 0, "sbank_acc".getBytes(),
						stuempno.getBytes());// �Է��˺�		
				bcc.SetStringFieldByName(xpackhandle, 0, "vsvarstr0".getBytes(),
						"1004".getBytes());// ���������ʶ	
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							int[] intRec = new int[1];
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
									.getBytes(), intRec);// ���֣�
							String out_card_amount = String.valueOf(intRec[0]);
							request.setAttribute("outCardAmount",
									out_card_amount);
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0000", "�ϻ�����ת�˳ɹ�", out_card_amount,
									out_card_amount, sphone3, cardphyid, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "�����ݷ���!", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							Arrays.fill(vsmess, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0002", vs_mess, "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "�����ݷ���!", "", "", "", "", null);
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
					String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
							"��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s, "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1003",
					"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1004",
					"ϵͳ��ʼ���쳣�����Ժ����ԣ�", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
