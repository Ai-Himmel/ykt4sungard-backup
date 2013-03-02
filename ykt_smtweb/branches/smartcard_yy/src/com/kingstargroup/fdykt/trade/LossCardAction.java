package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.ArrayList;

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

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.CardDTO;

public class LossCardAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LossCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.getInputForward();
		HttpSession session = request.getSession();
		if (null == session.getAttribute("cutid")
				|| null == session.getAttribute("stuempno"))
			return forward;
		KSDaoSessionFactory.createSession();
		try {
			forward = doLossCard(mapping, request, session);
			if (forward.getName().equals("success")) {
				KSDaoSessionFactory.commit();
			} else {
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLossCard(ActionMapping mapping,
			HttpServletRequest request, HttpSession session) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();

		String cutid = ((Integer) session.getAttribute("cutid")).toString();
		String stuempno = (String) session.getAttribute("stuempno");
		String password = (String) session.getAttribute("password");
		ActionErrors errors = new ActionErrors();
		try {
			DB2AccountDAO accountdao = new DB2AccountDAO();
			ArrayList accounts = accountdao.getAccountInfo(stuempno);
			if (accounts.size() == 0) {
				return (mapping.findForward("isnull"));
			}
			AccountDTO account = (AccountDTO) accounts.get(0);
			String cardid = String.valueOf(account.getCard_id());

			card = carddao.getCardInfo(cardid);
			String state = card.getStateId();
			// ���ͻ���Ϣ���ж��Ƿ���Թ�ʧ
			if (state.substring(0, 4).equals(KSConstant.CARDSTAT_LOGOUT)) {
				errors.add("unable", new ActionError("errors.unable"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			if (state.substring(1, 2).equals("1")) {
				errors.add("lost", new ActionError("errors.lost"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			}
			/*
			 * 
			 * String sysdate = new DB2SysParaDAO().getDBDateTime(); String
			 * systime = sysdate.substring(8); sysdate = sysdate.substring(0,8);
			 * String enddate = carddao.getEndDate(); CardLossInfoDTO lossinfo =
			 * new CardLossInfoDTO(); lossinfo.setBeginDate(sysdate);
			 * lossinfo.setCardId(cardid); lossinfo.setEndDate(enddate);
			 * lossinfo.setOperateDate(sysdate);
			 * lossinfo.setOperateTime(systime); lossinfo.setStateId("1");
			 * carddao.createLossInfo(lossinfo); // ����ÿ��ű�����,���ʧʱ�Ժ����������� if
			 * (state.substring(2, 3).equals("0")) { // ����������� BlackSheetDTO
			 * blacksheet = new BlackSheetDTO(); blacksheet.setCardId(cardid);
			 * blacksheet.setIsAd("0"); blacksheet.setOperateDate(sysdate);
			 * blacksheet.setOperateTime(systime); blacksheet.setStateId("1");
			 * blacksheet.setValiddate("501230121212");
			 * blacksheet.setVolume(sysdate.substring(2, 8) + systime);
			 * carddao.createBlackSheet(blacksheet); // �㲥������ MesListDTO meslist =
			 * new MesListDTO(); String incontent = "<CARDID>" + cardid + "</CARDID>" + "<VERNUM>" +
			 * blacksheet.getVolume() + "</VERNUM>" + "<ADDDELSIGN>" +
			 * blacksheet.getIsAd() + "</ADDDELSIGN>";
			 * meslist.setIncontent(incontent); meslist.setFunId("930005");
			 * meslist.setLevel("1"); meslist.setEcode("9999");
			 * meslist.setStateId("1"); meslist.setIndt(sysdate + systime);
			 * carddao.createMesList(meslist); } // �޸Ŀ�״̬Ϊ��ʧ
			 * carddao.updateCardState(cardid, "1100"); // ׼�����ݲ��뽻����ˮ��
			 * TradeSerialDTO tradeserial = new TradeSerialDTO();
			 * tradeserial.setOperate_Date(sysdate);
			 * tradeserial.setOperate_time(systime);
			 * tradeserial.setCollect_Date(sysdate);
			 * tradeserial.setCollect_time(systime);
			 * tradeserial.setEnterAct_time(systime);
			 * tradeserial.setSerial_type("930001");
			 * tradeserial.setSerial_state(9); tradeserial.setCustomer_id((new
			 * Integer(cutid)).longValue()); tradeserial.setCard_id((new
			 * Integer(cardid)).longValue()); DB2TradeSerialDAO tradeserialdao =
			 * new DB2TradeSerialDAO();
			 * tradeserialdao.createTradeSerial(tradeserial); return
			 * mapping.findForward("success");
			 */
			
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// ��̨drtp���ܺ�
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_card_loss", 847152);// ��̨ҵ���ܺ�
			int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
					3);// Ĭ�����Դ���
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;
			try {
				bcc = BccctlInit.getBccctlInstance();				
				xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
						.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
				System.out.println("��ý�巢������ ���ܺţ�"+mainfunction+"��̨ҵ��"+func);
				if (0 != xpackhandle) {
					System.out.println("��ý�����û���");
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(cutid));// �ͻ���
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							Integer.parseInt("0"));// ���׿���
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),
							Integer.parseInt("0"));// ���׿���
					bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
							.getBytes(), password.getBytes());//����
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
							.getBytes(), "1".getBytes());//У������
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit"
							.getBytes(), "web".getBytes());//����
					
					boolean bccret = false;
					while (--tries >= 0) {
						System.out.println("��ý�巢������:"+tries);
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 2000, errcode, errmsg);
						if (bccret) {
							break;
						}
					}
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							return mapping.findForward("success");
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								int i;
								for (i = 0; i < vsmess.length; i++) {
									if (vsmess[i] == 0) {
										break;
									}
								}
								String vs_mess = new String(vsmess, 0, i);
								/*errors.add("lost", new ActionError(vs_mess));
								if (!errors.isEmpty()) {
									saveErrors(request, errors);
								}*/
								request.setAttribute("msg",vs_mess+RetCode[0]);
								return mapping.findForward("failure");
							} else {
								/*errors.add("lost", new ActionError("��̨����ʧ��"));
								if (!errors.isEmpty()) {
									saveErrors(request, errors);
								}*/
								errors.add("lost", new ActionError("errors.background"));
								if (!errors.isEmpty()) {
									saveErrors(request, errors);
								}
								return mapping.findForward("failure");
							}

						}

					} else {
						// ����ʧ��

						int i = 0;
						for (i = 0; i < errmsg.length; i++) {
							if (errmsg[i] == 0) {
								break;
							}
						}
						String err_mess = new String(errmsg, 0, i);
						System.out.println("��ý�巢������ʧ��,�����룺"+errcode[0]+"����ԭ��"+err_mess);
						/*errors.add("lost", new ActionError("errors.request"));
						if (!errors.isEmpty()) {
							saveErrors(request, errors);
						}*/
						request.setAttribute("msg",err_mess+RetCode[0]);
						return mapping.findForward("failure");
					
					}
				}
				errors.add("lost", new ActionError("errors.system"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				
				return mapping.findForward("failure");

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("errors.system"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add("lost", new ActionError("errors.system"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			logger.error("��ʧ��ʧ�� : " + e.getMessage() + ", stuempno[" + stuempno
					+ "]");
			errors.add("lost", new ActionError("errors.losscard"));
			if (!errors.isEmpty()) {
				saveErrors(request, errors);
			}
			return mapping.findForward("failure");
		}
	}
}
