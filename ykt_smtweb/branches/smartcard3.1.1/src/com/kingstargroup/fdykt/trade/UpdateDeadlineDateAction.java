package com.kingstargroup.fdykt.trade;

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
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class UpdateDeadlineDateAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(UpdateDeadlineDateAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");// ������long
		String cardexpiredate= request.getParameter("enddate");
		
		if (null == cardphyid ||  null == cardexpiredate) {
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
					"1000", "�������ݴ���!", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response,
					xmlout);
			return null;
		}
		logger.error("cardexpiredate��"+cardexpiredate);
		
		if(cardexpiredate.length()<8){
			cardexpiredate=DateUtil.getNow("yyyyMMdd").substring(0, 2)+cardexpiredate;
		}
		
		logger.error("cardexpiredate��"+cardexpiredate);
		int deviceid = -2;
		try {
			String reqip = request.getRemoteAddr();
			System.out.print("ip����:"+reqip);

			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				logger.error("�豸δע�ᣬ����ʹ�ñ�����,����ip��"+reqip);
				String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
						"1001", "�豸δע�ᣬ����ʹ�ñ�����", "", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response,
						xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			logger.error("�豸δע�ᣬ����ʹ�ñ�����");
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate(
					"1001", "�豸δע�ᣬ����ʹ�ñ�����", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response,
					xmlout);
			return null;
		}

		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			System.out.println("����Ϣ��ȡʧ��");
			String xmlout = XMLGenerateUtil.MoblileXMLGenerate("1003",
					"����Ϣ��ȡʧ��", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		try {
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// ��̨drtp���ܺ�
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_consumerlimit_reset", 846320);// ��̨ҵ���ܺ�
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

					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), String.valueOf(deviceid).getBytes());// �ն˺�
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(String.valueOf(card.getCardno())));// ����
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate0"
							.getBytes(), cardexpiredate.getBytes());// ��Ч��

					bcc.SetStringFieldByName(xpackhandle, 0, "sstation1"
							.getBytes(), cardphyid.getBytes());// ������
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
							.getBytes(), "2".getBytes());


					boolean bccret = false;

					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 10000, errcode, errmsg);

					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							logger.error("��Ч�ڸ��³ɹ�");
							String xmlout = XMLGenerateUtil.XMLGenerate("0000", "��Ч�ڸ��³ɹ�", "", "", "","", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							// ʧ��
							logger.error("��Ч�ڸ���ʧ��,�����룺"+RetCode[0]);
							String xmlout = XMLGenerateUtil.XMLGenerate("0001", "��Ч�ڸ���ʧ��", "", "", "","", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;

						}

					} else {
						// ����ʧ��
						logger.error("��̨ͨѶ��ʱ������");
						String xmlout = XMLGenerateUtil.XMLGenerate("1001", "��̨ͨѶ��ʱ�����ã����Ժ����ԣ�", "","", "", "", "", "", "", "", "", null);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;

					}
				}
				logger.error("1002ϵͳ�����쳣�����Ժ�����");
				String xmlout = XMLGenerateUtil.XMLGenerate("1002", "ϵͳ�����쳣�����Ժ����ԣ�", "", "", "","", "", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response,
						xmlout);
				return null;

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				String xmlout = XMLGenerateUtil.XMLGenerate("1003", "ϵͳ�����쳣�����Ժ����ԣ�", "", "", "","", "", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response,
						xmlout);
				return null;
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				String xmlout = XMLGenerateUtil.XMLGenerate("1004", "ϵͳ�����쳣�����Ժ����ԣ�", "", "", "","", "", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response,
						xmlout);
				return null;
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1002", "ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "","", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response,
					xmlout);
			return null;
		}
	}
}
