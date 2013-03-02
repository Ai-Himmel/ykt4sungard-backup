package com.kingstargroup.fdykt.trade;

import java.io.IOException;
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

public class GetOnlineCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetOnlineCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doOnlineCheck(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("�ύ����ʧ��");
			e.printStackTrace();
		}

		if (forward.equals(mapping.findForward("none"))) {
			if (request.getSession().getAttribute("REQ_URL") != null) {
				try {
					response.sendRedirect(request.getSession().getAttribute(
							"REQ_URL").toString()+"&onlinecheck=checked");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				return null;
			} else {
				return forward;
			}

		} else {
			return forward;
		}
	}

	private ActionForward doOnlineCheck(ActionMapping mapping,
			HttpServletRequest request) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid"); // ������
		String dptCardCnt = request.getParameter("dptCardCnt");// ��ֵ����
		String payCardCnt = request.getParameter("payCardCnt");// ���Ѵ���
		String cardBala = request.getParameter("cardBala");// �����
		String tradetype = request.getParameter("tradetype");// ��������
		
		

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if (card == null) {
				request.setAttribute("errmsg", "����Ϣ�쳣�������Ƿ�������!");
				return mapping.findForward("failure");
			}
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("����Ϣ��ȡʧ��");
			request.setAttribute("errmsg", "����Ϣ��ȡʧ��");
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				request.setAttribute("errmsg", "�豸δע�ᣬ����ʹ�ô˹��ܣ�");
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			request.setAttribute("errmsg", "�豸δע�ᣬ����ʹ�ô˹��ܣ�");
			return mapping.findForward("failure");
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_online_check", 200001);// ��̨ҵ���ܺ�
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
						deviceid);// �ͻ���id

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// ����

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(cardBala));// �����

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(dptCardCnt));// ��ֵ����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(payCardCnt));// ���Ѵ���
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						tradetype.getBytes());

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), intRec);// �Ƿ���Ҫ��д
							String lvol1 = String.valueOf(intRec[0]);

							if ("1".equals(lvol1)) {

								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, 0, "lvol8"
										.getBytes(), intRec);// ����ֵ���֣�
								String lvol8 = String.valueOf(intRec[0]);
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, 0, "lvol7"
										.getBytes(), intRec);// ����ǰֵ���֣�
								String lvol7 = String.valueOf(intRec[0]);

								Arrays.fill(intRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle, 0,
										"damt0".getBytes(), doubleRec);
								String damt0 = String.valueOf(doubleRec[0]);

								byte[] byteStr = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"sdate0".getBytes(), byteStr, 300);
								String sdate0 = BccUtil
										.getStringFromByte(byteStr);// �ϴν�������

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"stime0".getBytes(), byteStr, 300);
								String stime0 = BccUtil
										.getStringFromByte(byteStr);// �ϴν���ʱ��

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"lcert_code".getBytes(), byteStr, 300);
								String lcert_code = BccUtil
										.getStringFromByte(byteStr);// �ϴν��״���

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"snote".getBytes(), byteStr, 300);
								String snote = BccUtil
										.getStringFromByte(byteStr);// �ϴν�������

								Arrays.fill(byteStr, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), byteStr, 300);
								String vsmess = BccUtil
										.getStringFromByte(byteStr);// ��ע��Ϣ
								String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
								"172.0.0.1");
								String drtpPort = KSConfiguration.getInstance().getProperty(
										"drtpport1", "4000");
								String svrFunc = KSConfiguration.getInstance().getProperty(
										"mainfunction1", "6000");
								
								request.setAttribute("ipServer", ipServer);
								request.setAttribute("drtpPort", drtpPort);
								request.setAttribute("svrFunc", svrFunc);	
								request.setAttribute("cardphyid", cardphyid);
								request.setAttribute("lvol7", lvol7);
								request.setAttribute("lvol8", lvol8);
								request.setAttribute("damt0", damt0);
								request.setAttribute("sdate0", sdate0);
								request.setAttribute("stime0", stime0);
								request.setAttribute("lcert_code", lcert_code);
								request.setAttribute("snote", snote);
								request.setAttribute("vsmess", vsmess);

								return mapping.findForward("success");

							} else {
								request.setAttribute("errmsg", "û����Ҫ��д��Ϣ");
								return mapping.findForward("none");
							}

						} else {
							request.setAttribute("errmsg", "��̨����ʧ��");
							return mapping.findForward("failure");
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "��̨����ʧ��");
							return mapping.findForward("failure");
						}

					}

				} else {
					// ����ʧ��
					String s = BccUtil.getStringFromByte(errmsg);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "ϵͳ�����쳣�����Ժ����ԣ�");
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "ϵͳ�����쳣�����Ժ����ԣ�");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "ϵͳ��ʼ���쳣�����Ժ����ԣ�");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
