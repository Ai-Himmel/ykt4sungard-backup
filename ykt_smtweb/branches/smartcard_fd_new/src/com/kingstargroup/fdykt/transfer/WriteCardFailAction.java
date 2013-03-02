package com.kingstargroup.fdykt.transfer;

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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class WriteCardFailAction extends Action {

	private static final Logger logger = Logger
			.getLogger(WriteCardFailAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = cardFail(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward cardFail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
         
		String SerialNo = request.getParameter("SerialNo");
		String deviceId = request.getParameter("deviceId");

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
		String vs_mess = "���׳ɹ�д��ʧ�ܣ��뵽�������Ĵ���";
		try {
			bcc = BccctlInit.getBccctlInstance();

			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			System.out.println("---д��ʧ��WriteCardFailAction---");

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				 bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240107".getBytes());

				 bcc.SetIntFieldByName(xpackhandle, 0, "lvol1"
						.getBytes(), Integer.parseInt(SerialNo));//��ˮ��
				    System.out.println("---------��ˮ��-------------"+SerialNo);
					bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(), deviceId.getBytes());//�豸��
					System.out.println("---------�豸��-------------"+deviceId);
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

					/*String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);*/
					
					System.out.println("---------RetCode[0]-------------"+RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							request.setAttribute("msg", vs_mess);
							return mapping.findForward("returninfo");
						} else {
					
							request.setAttribute("msg", vs_mess+ RetCode[0]);
							return mapping.findForward("returninfo");
						}

					} else {
						// ʧ��
						
						request.setAttribute("msg", vs_mess);
						return mapping.findForward("returninfo");
					}

				} else {
					// ����ʧ��
					request.setAttribute("msg", vs_mess);
					return mapping.findForward("returninfo");
				}
			}
			request.setAttribute("msg", vs_mess);
			return mapping.findForward("returninfo");

		} catch (Exception e) {
			request.setAttribute("msg", vs_mess);
			return mapping.findForward("returninfo");
		} catch (UnsatisfiedLinkError e) {
			request.setAttribute("msg",vs_mess);
			return mapping.findForward("returninfo");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	  }
	}

