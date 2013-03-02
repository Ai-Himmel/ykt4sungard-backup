package com.kingstargroup.fdykt.authbanktransfer;

import java.sql.SQLException;
import java.util.Arrays;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BccUtil;

public class BankBindAction extends Action {
	/**
	 * Logger for this class
	 */
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(BankBindAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String stuempno = request.getParameter("stuempno");
		String bankacc = request.getParameter("bankacc");
		String authcode = request.getParameter("authcode");
		
		//�����п����� A����ʾ��ӣ���D����ʾ����󶨣���S����ʾͬ��,��R����ʾ������֤��
		String operType = "A";
		
		request.setAttribute("bankacc", bankacc);
		request.setAttribute("stuempno", stuempno);
//		request.setAttribute("authcode", authcode);
		
		ActionErrors errors = new ActionErrors();
		
		DB2AccountDAO accdao = new DB2AccountDAO();
		String reqip = request.getRemoteAddr();
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				logger.error("�豸δע�ᣬ����ʹ�ô˹��ܣ�");
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
		        saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
		
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_bankcard_bind", 841603);// ��̨ҵ���ܺ�
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
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "B".getBytes());// ��������
				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), String.valueOf(deviceid).getBytes());// �ͻ���id
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(), stuempno.getBytes());// ѧ��
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(), bankacc.getBytes());// ���п���
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1".getBytes(), operType.getBytes());// ��������
				bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(), authcode.getBytes());//���п�У����
				
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					logger.info("RetCode[0]:"+RetCode[0]);
					logger.info("RecordCount[0]:"+RecordCount[0]);
					
					if (0 == RetCode[0]) {
						//����ɹ���,��̨�޷�����Ϣ
						return mapping.findForward("success");
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							logger.error(vs_mess);
							errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error",vs_mess));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						} else {
							logger.error("��̨����ʧ��");
							errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error","��̨����ʧ��"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					}

				} else {
					// ����ʧ��
					String s = BccUtil.getStringFromByte(errmsg);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.connet"));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}
			}

			logger.error("ϵͳ�����쳣�����Ժ����ԣ�");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("system.error"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("system.error"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE,new ActionError("back.error","ϵͳ�����쳣[���ܼ���so�ļ�]�����Ժ����ԣ�"));
	        saveErrors(request, errors);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}