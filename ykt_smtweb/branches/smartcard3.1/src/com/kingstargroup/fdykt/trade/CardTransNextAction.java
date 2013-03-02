package com.kingstargroup.fdykt.trade;

import org.apache.log4j.Logger;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

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
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CardTransNextAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CardTransNextAction.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		if (logger.isDebugEnabled()) {
			logger.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}

		if (logger.isDebugEnabled()) {
			logger.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		if (logger.isDebugEnabled()) {
			logger.debug("doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();

		String card_id = request.getParameter("reqcardno");
		String card_bala = request.getParameter("reqcardBalance");
		String tx_cnt = request.getParameter("reqcardcnt");
		String oldCardNo = request.getParameter("oldCardNo");
		String oldCardBalance = request.getParameter("oldCardBalance");
		String oldCardPwd = request.getParameter("oldCardPwd");
		String serialNo = request.getParameter("serialNo");
		String sdate = request.getParameter("sdate3");
		
		request.setAttribute("reqcardno", card_id);
		request.setAttribute("reqcardBalance", card_bala);
		request.setAttribute("reqcardcnt", tx_cnt);

		request.setAttribute("oldCardNo", oldCardNo);
		request.setAttribute("oldCardBalance", oldCardBalance);
		request.setAttribute("oldCardPwd", oldCardPwd);

		String hexcardno = Integer.toHexString(Integer.parseInt(card_id))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		 ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("����Ϣ��ȡʧ��");
			System.out.println("����Ϣ��ȡʧ��");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "����Ϣ��ȡʧ��"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
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

							logger.info("��ʽ���˳ɹ�,�����ţ�"+hexcardno+",�Ͽ����ţ�"+oldCardNo+"���������ڣ�"+sdate3+"����ˮ�ţ�"+serial_no+",����ֵ��"+out_card_amount+"��");
							return mapping.findForward("success");
						} else {
							logger.info("��ʽ����ʧ��,��̨����ʧ��,�����ţ�"+hexcardno+",�Ͽ����ţ�"+oldCardNo);
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", "��̨����ʧ��"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", vs_mess));
							saveErrors(request, errors);
							
							logger.info("��ʽ����ʧ��,��̨����ʧ��,�����ţ�"+hexcardno+",�Ͽ����ţ�"+oldCardNo+"���ش�����Ϣ��"+vs_mess);
							return mapping.findForward("failure");
						} else {
							
							errors.add(ActionMessages.GLOBAL_MESSAGE,
									new ActionError("back.error", "��̨����ʧ��"));
							saveErrors(request, errors);
							logger.info("��ʽ����ʧ��,��̨����ʧ��,�����ţ�"+hexcardno+",�Ͽ����ţ�"+oldCardNo+"���ش�����Ϣ����");
							return mapping.findForward("failure");
						}

					}

				} else {
					// ����ʧ��

					String err_msg = BccUtil.getStringFromByte(errmsg);
					logger.info("��ʽ����ʧ��,��̨����ʧ��,�����ţ�"+hexcardno+",�Ͽ����ţ�"+oldCardNo+"connect:errcode="+errcode[0]+"msg="+err_msg);
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
							"back.error", "��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + err_msg));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}
			}
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "ϵͳ�����쳣�����Ժ����ԣ�"));
			saveErrors(request, errors);
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "ϵͳ�����쳣�����Ժ����ԣ�"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "ϵͳ�����쳣�����Ժ����ԣ�"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
	}
}
