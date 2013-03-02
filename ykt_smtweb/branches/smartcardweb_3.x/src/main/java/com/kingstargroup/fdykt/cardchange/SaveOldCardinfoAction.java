package com.kingstargroup.fdykt.cardchange;

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
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.trade.MobileCheckAction;
import com.kingstargroup.fdykt.util.BccUtil;

public class SaveOldCardinfoAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(MobileCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = saveinfo(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward saveinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		saveToken(request);

		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String card_bala = request.getParameter("cardBala");		
		String pay_card_cnt = request.getParameter("pay_card_cnt");
		String dpt_card_cnt = request.getParameter("dpt_card_cnt");		

		String showcardno = request.getParameter("showcardno");
		String oldcardphyid = request.getParameter("oldcardphyid");
		String newcardphyid = request.getParameter("newcardphyid");
		String pursetype1 = request.getParameter("pursetype1");
		String pursetype2 = request.getParameter("pursetype2");
		String pursetype3 = request.getParameter("pursetype3");
		String water_money1 = request.getParameter("water_money1");
		String water_money2 = request.getParameter("water_money2");
		String water_money3 = request.getParameter("water_money3");
		
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
		"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");
		
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		
		request.setAttribute("newcardphyid", newcardphyid);
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("cardBala", card_bala);		
		request.setAttribute("pay_card_cnt", pay_card_cnt);
		request.setAttribute("dpt_card_cnt", dpt_card_cnt);		
		request.setAttribute("showcardno", showcardno);
		request.setAttribute("oldcardphyid", oldcardphyid);
		//�˶��Ͽ���Ϣ����ȷ��

		if(!oldcardphyid.equals(cardphyid)){
			//��Ϣ����Ӧ��
			request.setAttribute("errmsg", "��ʱ������ʽ����Ӧ��Ϣ����ȷ��<br><br>��˶Ժ����»�����<br><br>����Բ��У��뵽У԰����������");
			return mapping.findForward("failure");
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("����Ϣ��ȡʧ��");
			System.out.println("����Ϣ��ȡʧ��");
			request.setAttribute("errmsg", "����Ϣ��ȡʧ��");
			return mapping.findForward("failure");
		}
		
		if(card==null){
			request.setAttribute("errmsg", "�Ҳ������ſ��������Ϣ��<br><br>��˶Կ�Ƭ�Ƿ񱻹�ʧ<br><br>����Բ��У��뵽У԰����������");
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
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
				"logicfunc_changecard_oldcard", 846327);// ��̨ҵ���ܺ�
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
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						deviceid);// �ͻ���id
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "S".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// ����

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(),
						Integer.parseInt("0"));// �������κ�

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(dpt_card_cnt));// ���״���(��ֵ

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(pay_card_cnt));// ���״���(����

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// �����

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						cardphyid.getBytes());//������
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no2".getBytes(),
						newcardphyid.getBytes());//�¿�������
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						showcardno.getBytes());//��ʾ����
				if(pursetype1!=null&&!"0".equals(pursetype1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol10".getBytes(),
							pursetype1.getBytes());//ˮ��Ǯ����
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							water_money1.getBytes());//ˮ��Ǯ��
				}
				if(pursetype2!=null&&!"0".equals(pursetype2)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol11".getBytes(),
							pursetype2.getBytes());//ˮ��Ǯ����
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol2".getBytes(),
							water_money2.getBytes());//ˮ��Ǯ��
				}
				if(pursetype3!=null&&!"0".equals(pursetype3)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol12".getBytes(),
							pursetype3.getBytes());//ˮ��Ǯ����
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol3".getBytes(),
							water_money3.getBytes());//ˮ��Ǯ��
				}

				

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							return mapping.findForward("success");
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
