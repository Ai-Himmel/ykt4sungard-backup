package com.kingstargroup.fdykt.elecclt;

import java.sql.SQLException;
import java.util.Arrays;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
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

public class ElecPutinAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(ElecPutinAction.class);
	
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
		String cardphyid = request.getParameter("cardphyid");//������long
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String room = request.getParameter("room");
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("room", room);
		
		String elecPayCode = KSConfiguration.getInstance().getProperty("elec_pay_code", "4000");//֧������
        String[] elecPayCodeArray = elecPayCode.split(",");
        String elecIndex = request.getParameter("elecIndex");
        String elec_pay_code;
        if(StringUtils.isNotBlank(elecIndex)){
        	elec_pay_code = elecPayCodeArray[Integer.parseInt(elecIndex)];
        } else {
        	elec_pay_code = elecPayCodeArray[0];
        }
        request.setAttribute("elecIndex", elecIndex);
        logger.info("elec pay code:" + elec_pay_code);
//		docheck(request,cardphyid,money,cardBala,txCnt,room);
		return mapping.findForward("success");
	}
	
	private void docheck(HttpServletRequest request,String cardphyid,String money,String cardBala,String txCnt,String room) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
				logger.error("����Ϣ�쳣�������Ƿ�������!");
				return;
			}
		} catch (Exception e) {
			logger.error("����Ϣ��ȡʧ��!");
		}
		String reqip = request.getRemoteAddr();
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				logger.error("�豸δע�ᣬ����ʹ�ô˹��ܣ�");
				return;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			logger.error("�豸δע�ᣬ����ʹ�ô˹��ܣ�");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_thirdpay", 850005);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
        String elecPayCode = KSConfiguration.getInstance().getProperty("elec_pay_code", "4000");//֧������
        String[] elecPayCodeArray = elecPayCode.split(",");
        String elecIndex = request.getParameter("elecIndex");
        String elec_pay_code;
        if(StringUtils.isNotBlank(elecIndex)){
        	elec_pay_code = elecPayCodeArray[Integer.parseInt(elecIndex)];
        } else {
        	elec_pay_code = elecPayCodeArray[0];
        }
        request.setAttribute("elecIndex", elecIndex);
        logger.info("elec pay code:" + elec_pay_code);
        
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), String.valueOf(deviceid).getBytes());// �ն˺�
				bcc.SetIntFieldByName(xpackhandle, 0, "lbank_acc_type".getBytes(), 0);// ���ױ�־����ѯ
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),Integer.parseInt(String.valueOf(card.getCardno())));// ����
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),Integer.parseInt(txCnt));// ���״���
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),Integer.parseInt(cardBala));// ������ǰ���(��)
				bcc.SetStringFieldByName(xpackhandle, 0,"sstation1".getBytes(), cardphyid.getBytes());// ������
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),Integer.parseInt(money)*100);// ת�˽��(��)
				bcc.SetStringFieldByName(xpackhandle, 0, "sbank_acc".getBytes(),room.getBytes());// �����				
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),Integer.parseInt(elec_pay_code));// �����

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);
				logger.info("bccret="+bccret);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					logger.info("RetCode[0]:"+RetCode[0]);
					logger.info("RecordCount[0]:"+RecordCount[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							//������Ϣ
							byte[] vsmess = new byte[300];
							Arrays.fill(vsmess, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess".getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);	
							logger.info("info:"+vs_mess);
							request.setAttribute("info", vs_mess);
						} else {
							request.setAttribute("errmsg", "��̨����ʧ��");
						}
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							Arrays.fill(vsmess, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);	
							logger.error("vs_mess:"+vs_mess);
							request.setAttribute("errmsg", vs_mess);
						} else {
							request.setAttribute("errmsg", "��̨����ʧ��");
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
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "��̨ͨѶ��ʱ�����ã����Ժ����ԣ� " + s);
				}
			} else {
				request.setAttribute("errmsg", "ϵͳ�����쳣�����Ժ����ԣ�");
				logger.error("xpackhandle="+xpackhandle);
			}
		} catch (Exception e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "ϵͳ�����쳣�����Ժ����ԣ�");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "ϵͳ��ʼ���쳣�����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
