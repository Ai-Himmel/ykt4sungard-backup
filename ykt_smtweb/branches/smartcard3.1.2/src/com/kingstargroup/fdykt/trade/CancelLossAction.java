package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

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
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class CancelLossAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CancelLossAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession();
		if (session.getAttribute("cardno") == null){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return mapping.findForward("logon");
		}
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("error");
		try {
			DB2AccountDAO accdao = new DB2AccountDAO();
			ActionErrors errors = new ActionErrors();
			String reqip = request.getRemoteAddr();
//			InetAddress addr = InetAddress.getLocalHost();
//			String reqip = addr.getHostAddress();// ��ñ���IP
			int deviceid = -2;
			try {
				deviceid = accdao.getdevidFromip(reqip);			
				if(deviceid<0){
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
			
			
			if (doUnloss(mapping, request, session,deviceid)) {
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			} else {
				forward = mapping.findForward("failure");
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
			logger.error("����ʧ��:��ҿ�ʧ��");
		}
		return forward;
	}

	private boolean doUnloss(ActionMapping mapping, HttpServletRequest request,
			HttpSession session,int deviceid) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();
		String cardno = (String)session.getAttribute("cardno");
		String cutid = (String)session.getAttribute("cutid");
		String password = (String) session.getAttribute("password");
		ActionErrors errors = new ActionErrors();
		// ȡ��ϵͳ����ʱ��
		try {
			String sysdate = new DB2SysParaDAO().getDBDateTime();
//			String systime = sysdate.substring(8);
			sysdate = sysdate.substring(0, 8);
			card = carddao.getCardInfo(cardno);
			String state = card.getCardstatus();
			if (state == null || state.length() != 10)
				return false;
			char[] stateAry = state.toCharArray();
			if (KSConstant.BOOLEAN_TRUE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
				errors.add("100561", new ActionError("errors.100561"));
				saveErrors(request, errors);
				return false;
			}
			
			if(!"0".equals(cutid)){
				// ��鿨״̬�Ƿ�Ϊ��ʧ
				int flag = carddao.isCancel(cutid, cardno);
				if (flag != 0) {
					if (flag == KSConstant.MAINCARD_UNLOSSED) {	
						errors.add("100560", new ActionError("errors.100560"));
						saveErrors(request, errors);
						logger.info("���п�δ��ʧ,����Ҫ�ȹ�ʧ,custno[" + cutid + "]");
						return false;
					}
				}
			}
		
			// �ظ����Ҫ���´�����			
			// ����ÿ��ű�����,���ʧʱ�Ժ�����������
			if (KSConstant.BOOLEAN_FALSE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {

				long xpackhandle = 0;
				int drtpno = 0;
				int errcode[] = { 1 };
				byte errmsg[] = new byte[300];
				int branchno = 0;// ��̨drtp���ܺ�
				int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
						"mainfunction1", 9000);
				int func = KSConfiguration.getInstance().getPropertyAsInt(
						"logicfunc_card_loss_cancel", 846307);// ��̨ҵ���ܺ�
				int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
						3);// Ĭ�����Դ���
				int[] RetCode = new int[1];
				int[] RecordCount = new int[1];
				bccclt bcc = null;
				try {
					bcc = BccctlInit.getBccctlInstance();				
					xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
							.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
					if (0 != xpackhandle) {
						bcc.SetRequestType(xpackhandle, func);
						bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
								Integer.parseInt(cardno));// ����
						bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
								.getBytes(), password.getBytes());// ����
						bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
								.getBytes(), String.valueOf(deviceid).getBytes());//�ն˺�
						bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
								.getBytes(), "2".getBytes());//��ʧ��ұ�ʶ

						boolean bccret = false;
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
									mainfunction, 10000, errcode, errmsg);

						if (bccret) {
							bcc.GetRetCode(xpackhandle, RetCode);
							bcc.GetRecordCount(xpackhandle, RecordCount);
							if (0 == RetCode[0]) {
								if (0 < RecordCount[0]) {
									
									byte[] BlkVersion = new byte[13];
									bcc.GetStringFieldByName(xpackhandle, 0, "sserial0"
											.getBytes(), BlkVersion, 13);
									int i = 0;
									for (i = 0; i < BlkVersion.length; i++) {
										if (0 == BlkVersion[i]) {
											break;
										}
									}
									String blk_version = new String(BlkVersion, 0, i);
									
									request.setAttribute("blkversion", blk_version);							
									return true;
								} else {
									errors.add("lost", new ActionError("��̨����ʧ��"));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return false;
								}
							} else {
								// ʧ��
								if (0 < RecordCount[0]) {
									byte[] vsmess = new byte[300];
									bcc.GetStringFieldByName(xpackhandle, 0,
											"vsmess".getBytes(), vsmess, 300);
									String vs_mess = BccUtil.getStringFromByte(vsmess);
									errors.add("lost", new ActionError(vs_mess));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return false;
								} else {
									errors.add("lost", new ActionError("��̨����ʧ��"));
									if (!errors.isEmpty()) {
										saveErrors(request, errors);
									}
									return false;
								}

							}

						} else {
							// ����ʧ��
						
							errors.add("lost", new ActionError("errors.request"));
							if (!errors.isEmpty()) {
								saveErrors(request, errors);
							}
							return false;
						
						}
					}
					errors.add("lost", new ActionError("ϵͳ�����쳣�����Ժ����ԣ�"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;

				} catch (Exception e) {
					// TODO: handle exception
					logger.error(e.getMessage());
					errors.add("lost", new ActionError("ϵͳ�����쳣�����Ժ����ԣ�"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;
				} catch (UnsatisfiedLinkError e) {
					logger.error(e.getMessage());
					errors.add("lost", new ActionError("ϵͳ�����쳣�����Ժ����ԣ�"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					return false;
				} finally {
					if (xpackhandle != 0) {
						bcc.DeleteXpackHandle(xpackhandle);
					}
				}
			}
			return false;
		} catch (Exception e) {
			logger.error("��ҿ�ʧ��:" + e.getMessage());
			return false;
		}
	}

}
