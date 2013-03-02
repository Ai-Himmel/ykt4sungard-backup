package com.kingstargroup.fdykt.transfer;

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
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.DesUtil;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class BankQueryMoneyAction extends Action {

	private static final Logger logger = Logger
			.getLogger(BankQueryMoneyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = Querymoney(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward Querymoney(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		 if (isTokenValid(request, true)) {

		ServletContext app = request.getSession().getServletContext();
		if (app.getAttribute("pinkey") == null) {
			//logger.info("�豸δ��¼");
			return mapping.findForward("devicelogon");
		}
		String bankno = request.getSession().getAttribute("bankno").toString();
		//logger.info("BankCardNo=[" + bankno + "]");
		String password = request.getParameter("password").toString();

		String deviceId = request.getParameter("deviceId");
		if (deviceId == null || "".equals(deviceId)) {
			request.setAttribute("msg", "�����ԱΪ������ע��һ���豸��");
			return mapping.findForward("returninfo");
		}
		byte[] pinkey = (byte[]) app.getAttribute("pinkey");

		
		String despassword = null;
		try {
			despassword = DesUtil.getDesPassword(password, pinkey);
			//logger.info("BankCardPwd=[" + despassword + "]");
		} catch (Exception e) {
			request.setAttribute("msg", "��ȡ��Կʧ�ܣ�ϵͳ��ʱ�޷�ʹ��");
			return mapping.findForward("returninfo");
		}

		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int bankmainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"bankmainfunction", 9998);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"banktransferfunction", 900077);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		
		try {
			bcc = BccctlInit.getBccctlInstance();

			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240007".getBytes());

				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation0".getBytes(), despassword.getBytes());// ���п�����

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth"
						.getBytes(), bankno.getBytes());// ���п���

				bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),
						deviceId.getBytes());// �豸��
				
				 bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						 "web".getBytes());/// ����Ա

				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							bankmainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);

					String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);

					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							byte[] bankmoney = new byte[9];
							bcc.GetStringFieldByName(xpackhandle, 0, "scust_no"
									.getBytes(), bankmoney, 9);

							int i = 0;
							for (i = 0; i < bankmoney.length; i++) {
								if (0 == bankmoney[i]) {
									break;
								}
							}
							String showmoney = new String(bankmoney,0,i);
							request.setAttribute("bankmoney", BdUtil.FentoYuan(showmoney));
							return mapping.findForward("success");
						} else {
							vs_mess = "���п�����ѯʧ��,�����ݷ���";
							request.setAttribute("msg", vs_mess);
							return mapping.findForward("failure");
						}

					} else {
						// ʧ��
						if(108120==RetCode[0]){//�ն�δ��¼
							return mapping.findForward("devicelogon");
						}
						request.setAttribute("msg", vs_mess);
						return mapping.findForward("failure");

					}

				} else {
					// ����ʧ��
					request.setAttribute("msg", "��̨ͨѶ��ʱ������");
					return mapping.findForward("failure");
				}
			}
			request.setAttribute("msg", "ϵͳ�����쳣,��ʱ�޷�ʹ��");
			return mapping.findForward("failure");

		} catch (Exception e) {
			request.setAttribute("msg", "ϵͳ�����쳣����ʱ�޷�ʹ��");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			request.setAttribute("msg", "ϵͳ��ʼ���쳣����ʱ�޷�ʹ��");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	  }else{
		  return mapping.findForward("index");
	  }
	}
}
