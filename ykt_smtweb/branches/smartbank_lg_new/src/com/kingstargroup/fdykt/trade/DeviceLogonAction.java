package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.ServletContext;
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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class DeviceLogonAction extends Action {

	private static final Logger logger = Logger
			.getLogger(DeviceLogonAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = Device(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward Device(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		//System.out.print("---��ʼ��½----");

		String deviceId = request.getParameter("deviceId");

		if (deviceId == null || "".equals(deviceId)) {
			request.setAttribute("msg", "�����ԱΪ������ע��һ���豸��");
			return mapping.findForward("returninfo");
		}

		long xpackhandle = 0;
		int drtpno = 1;// ��2��drtp
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int bankmainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"bankmainfunction", 9998);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"banktransferfunction", 900077);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// Ĭ�����Դ���
		//System.out.print("---bankmainfunction----"+bankmainfunction+"--func--"+func);
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;

		try {
			//System.out.print("---��ʼbcc----");
			bcc = BccctlInit.getBccctlInstance();
			//System.out.print("---bcc over----");
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			//System.out.print("---xpackhandle----="+xpackhandle+"--");
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240101".getBytes());// ���״���

				bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),
						deviceId.getBytes());// �豸��

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						bankmainfunction, 10000, errcode, errmsg);
				//System.out.print("-----bccret-------"+bccret);
				if (bccret) {
					
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] key = new byte[16];

							bcc.GetStringFieldByName(xpackhandle, 0,
									"sstation0".getBytes(), key, 16);// ��ȡpin��Կ

							ServletContext app = request.getSession()
									.getServletContext();

							/*
							 * String temp=""; for(int i=0;i<key.length;i++){
							 * temp = temp+ key[i];
							 *  } System.out.println(temp);
							 */
							app.setAttribute("pinkey", key);
							//System.out.print("---key----" + key);
							/*
							 * byte[] pinkey =
							 * (byte[])app.getAttribute("pinkey"); String
							 * test=""; for(int i=0;i<pinkey.length;i++){ test =
							 * test+ pinkey[i]; } System.out.println(test);
							 */
							//System.out.print("---�豸��¼�ɹ�----");
							logger.info("�豸��¼�ɹ�" + RetCode[0]);
							return mapping.findForward("index");

						} else {
							logger.error("��ȡpin��Կʧ��" + RetCode[0]);
							return mapping.findForward("index");
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							logger.error("��ȡpin��Կʧ��" + RetCode[0]);

							return mapping.findForward("index");
						} else {
							return mapping.findForward("index");
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
					String msg = new String(errmsg, 0, i);

					logger.error("�豸��¼ʧ�� ����̨ͨѶ��ʱ������" + msg + "errcode"
							+ errcode[0]);

					return mapping.findForward("index");
				}
			}
			logger.error("�豸��¼ʧ��:ϵͳ�����쳣,û�ҵ�cpackfile");
			return mapping.findForward("index");

		} catch (UnsatisfiedLinkError  e) {
			// TODO: handle exception
			logger.error("�豸��¼ʧ�� ��ϵͳ�����쳣�����Ժ�����UnsatisfiedLinkError"+e.getStackTrace()+e.getMessage());

			return mapping.findForward("index");
		} catch (Exception e) {

			logger.error("�豸��¼ʧ�� ��ϵͳ�����쳣�����Ժ�����Exception");

			return mapping.findForward("index");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}

		}
	}
}