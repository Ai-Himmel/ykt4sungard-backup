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
		String refno = request.getParameter("sname2");//参考号


		if (null == gid || null == cardphyid || null == fee
				|| null == serialNo || "".equals(cardphyid) || "".equals(fee)
				|| "".equals(serialNo) || "".equals(gid)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "请求数据错误!",
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
						"卡信息异常，请检查是否正常卡!", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
			custdto = custdao.getCustomer(card.getCustid());
			
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("0001",
					"卡信息读取失败!", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		
	//第三方配置对象调用
		
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
								"0000", "操作成功", "", "", "", cardphyid, null);
						logger.info("1卡号=" + cardphyid + "扣费对象stuempno="
								+ custdto.getStuempno() + " 专用扣费成功，对应流水号=" + serialNo
								+ "扣费金额=" + fee);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}else{
						
						String errmsg = businessProcessor.getProcessMessage(session)==null?"":businessProcessor.getProcessMessage(session);
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0001", errmsg, "", "", "", "", null);
						logger.info("1卡号=" + cardphyid + "扣费对象stuempno="
								+  custdto.getStuempno() + " 专用扣费失败，对应流水号=" + serialNo
								+ "扣费金额=" + fee 
								+ "错误信息：" + errmsg);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}
				}else{
					BusinessProcessor businessProcessor = new BusinessProcessorImpl();
					boolean ret = businessProcessor.businessProcess(session, refno, custdto.getStuempno(), custdto.getCustname(), fee, args);
					if(ret==true){
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0000", "操作成功", "", "", "", cardphyid, null);
						logger.info("2卡号=" + cardphyid + "扣费对象stuempno="
								+ custdto.getStuempno() + " 网费充值成功，对应流水号=" + serialNo
								+ "充值金额=" + fee);
						XMLGenerateUtil.XMLSendOut(request, response,
								xmlout);
						return null;
					}else{
						String xmlout = XMLGenerateUtil.ElectXMLGenerate(
								"0002", "系统出现未知异常，请忽略此错误", "", "", "", "", null);
						logger.info("1卡号=" + cardphyid + "扣费对象stuempno="
								+  custdto.getStuempno() + " 专用扣费失败，对应流水号=" + serialNo
								+ "扣费金额=" + fee 
								+ "错误信息：未知" );
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
							"0000", "操作成功", "", "", "", cardphyid, null);
					logger.info("2卡号=" + cardphyid + "扣费对象stuempno="
							+ custdto.getStuempno() + " 网费充值成功，对应流水号=" + serialNo
							+ "充值金额=" + fee);
					XMLGenerateUtil.XMLSendOut(request, response,
							xmlout);
					return null;
				}else{
					String xmlout = XMLGenerateUtil.ElectXMLGenerate(
							"0002", "系统出现未知异常，请忽略此错误", "", "", "", "", null);
					logger.info("1卡号=" + cardphyid + "扣费对象stuempno="
							+  custdto.getStuempno() + " 专用扣费失败，对应流水号=" + serialNo
							+ "扣费金额=" + fee 
							+ "错误信息：未知" );
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
				"0003", "系统配置出错，第三方系统充值未能完成", "", "", "", "", null);
		logger.info("1卡号=" + cardphyid + "扣费对象stuempno="
				+  custdto.getStuempno() + " 专用扣费失败，对应流水号=" + serialNo
				+ "扣费金额=" + fee 
				+ "错误信息：系统配置出错，第三方系统充值未能完成" );
		XMLGenerateUtil.XMLSendOut(request, response,
				xmlout);
		return null;
	}
}
