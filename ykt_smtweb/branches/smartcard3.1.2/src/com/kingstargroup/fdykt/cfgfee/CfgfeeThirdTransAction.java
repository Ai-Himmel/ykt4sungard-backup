package com.kingstargroup.fdykt.cfgfee;

import java.sql.SQLException;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.itemconfig.ConfigProcess;
import com.kingstar.itemconfig.ConfigPropertyvalue;
import com.kingstar.itemconfig.Configitem;
import com.kingstargroup.BusinessProcessor;
import com.kingstargroup.BusinessProcessorImpl;
import com.kingstargroup.fdykt.ConfigItemInit;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CfgfeeThirdTransAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(CfgfeeThirdTransAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		DB2CardDAO carddao = new DB2CardDAO();
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		HttpSession session = request.getSession();
		String cardphyid = request.getParameter("cardphyid");
		String fee = request.getParameter("fee");
		String serialNo = request.getParameter("serialNo");
		String gid = request.getParameter("gid");
		String sdate3 = request.getParameter("sdate3");
		String refno = request.getParameter("sname2");//�ο���


		if (null == gid || null == cardphyid || null == fee
				|| null == serialNo || "".equals(cardphyid) || "".equals(fee)
				|| "".equals(serialNo) || "".equals(gid)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "�������ݴ���!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		// ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		CustomerDTO custdto = new CustomerDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
			if(card==null){
				String xmlout = XMLGenerateUtil.ElectXMLGenerate("0001",
						"����Ϣ�쳣�������Ƿ�������!", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
			custdto = custdao.getCustomer(card.getCustid());
			
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("����Ϣ��ȡʧ��");
			System.out.println("����Ϣ��ȡʧ��");
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("0001",
					"����Ϣ��ȡʧ��!", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		
	//���������ö������
		
		Configitem cfgitem = ConfigItemInit.getConfigItembyGid(gid);
		
		ConfigProcess cfgpress = cfgitem.getBusinessProcessor();
		
		
		ConfigPropertyvalue[] cfgpvArr = cfgpress.getParamArray();
		HashMap args = new HashMap();
		if(cfgpvArr!=null&&cfgpvArr.length>0){
			for(int i=0;i<cfgpvArr.length;i++){
				ConfigPropertyvalue cfgpv = cfgpvArr[i];
				String property = cfgpv.getProperty();
				String value = cfgpv.getValue();
				args.put(property, value);
			}
		}
		String classname = cfgpress.getClassname();
		
		
		Class c = null;
		try {
			if(null!=classname && !"".equals(classname)){
				c = Class.forName(classname);			
				if(c.newInstance() instanceof BusinessProcessor){
					BusinessProcessor businessProcessor = (BusinessProcessor)c.newInstance();
					boolean ret = businessProcessor.businessProcess(session, refno, custdto.getStuempno(), custdto.getCustname(), fee, args);
					if(ret==true){
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0000", "�����ɹ�", "", "", "", cardphyid, null);
						logger.info("1����=" + cardphyid + "�۷Ѷ���stuempno="
								+ custdto.getStuempno() + " ר�ÿ۷ѳɹ�����Ӧ��ˮ��=" + serialNo
								+ "�۷ѽ��=" + fee);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}else{
						
						String errmsg = businessProcessor.getProcessMessage(session)==null?"":businessProcessor.getProcessMessage(session);
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0001", errmsg, "", "", "", "", null);
						logger.info("1����=" + cardphyid + "�۷Ѷ���stuempno="
								+  custdto.getStuempno() + " ר�ÿ۷�ʧ�ܣ���Ӧ��ˮ��=" + serialNo
								+ "�۷ѽ��=" + fee 
								+ "������Ϣ��" + errmsg);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}
				}else{
					BusinessProcessor businessProcessor = new BusinessProcessorImpl();
					boolean ret = businessProcessor.businessProcess(session, refno, custdto.getStuempno(), custdto.getCustname(), fee, args);
					if(ret==true){
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0000", "�����ɹ�", "", "", "", cardphyid, null);
						logger.info("2����=" + cardphyid + "�۷Ѷ���stuempno="
								+ custdto.getStuempno() + " ���ѳ�ֵ�ɹ�����Ӧ��ˮ��=" + serialNo
								+ "��ֵ���=" + fee);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}else{
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0002", "ϵͳ����δ֪�쳣������Դ˴���", "", "", "", "", null);
						logger.info("1����=" + cardphyid + "�۷Ѷ���stuempno="
								+  custdto.getStuempno() + " ר�ÿ۷�ʧ�ܣ���Ӧ��ˮ��=" + serialNo
								+ "�۷ѽ��=" + fee 
								+ "������Ϣ��δ֪" );
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}					
				}
			}else{

				BusinessProcessor businessProcessor = new BusinessProcessorImpl();
				boolean ret = businessProcessor.businessProcess(session, refno, custdto.getStuempno(), custdto.getCustname(), fee, args);
				if(ret==true){
					String xmlout = XMLGenerateUtil.ElectXMLGenerate(
							"0000", "�����ɹ�", "", "", "", cardphyid, null);
					logger.info("2����=" + cardphyid + "�۷Ѷ���stuempno="
							+ custdto.getStuempno() + " ���ѳ�ֵ�ɹ�����Ӧ��ˮ��=" + serialNo
							+ "��ֵ���=" + fee);
					XMLGenerateUtil.XMLSendOut(request, response,
							xmlout);
					return null;
				}else{
					String xmlout = XMLGenerateUtil.ElectXMLGenerate(
							"0002", "ϵͳ����δ֪�쳣������Դ˴���", "", "", "", "", null);
					logger.info("1����=" + cardphyid + "�۷Ѷ���stuempno="
							+  custdto.getStuempno() + " ר�ÿ۷�ʧ�ܣ���Ӧ��ˮ��=" + serialNo
							+ "�۷ѽ��=" + fee 
							+ "������Ϣ��δ֪" );
					XMLGenerateUtil.XMLSendOut(request, response,
							xmlout);
					return null;
				}					
			
			}
			
			
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		}
		String xmlout = XMLGenerateUtil.ElectXMLGenerate(
				"0003", "ϵͳ���ó���������ϵͳ��ֵδ�����", "", "", "", "", null);
		logger.info("1����=" + cardphyid + "�۷Ѷ���stuempno="
				+  custdto.getStuempno() + " ר�ÿ۷�ʧ�ܣ���Ӧ��ˮ��=" + serialNo
				+ "�۷ѽ��=" + fee 
				+ "������Ϣ��ϵͳ���ó���������ϵͳ��ֵδ�����" );
		XMLGenerateUtil.XMLSendOut(request, response,
				xmlout);
		return null;
	}
}
