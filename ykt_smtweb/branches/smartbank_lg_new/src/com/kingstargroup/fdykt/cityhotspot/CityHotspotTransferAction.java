package com.kingstargroup.fdykt.cityhotspot;

import java.sql.SQLException;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.RetMessageUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CityHotspotTransferAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CityHotspotTransferAction.class);

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
		
		
		HttpSession session = request.getSession(true);
		DB2CardDAO carddao = new DB2CardDAO();
		String cardno = request.getParameter("cardno");
		//System.out.print("------cardno------"+cardno);
		String TransAmount = request.getParameter("TransAmount");
		//System.out.print("------TransAmount------"+TransAmount);
		String SerialNo = request.getParameter("SerialNo");
		//System.out.print("------SerialNo------"+SerialNo);
		String pwd = request.getParameter("pwd");
		//System.out.print("------pwd------"+pwd);
		String cxCnt  = request.getParameter("cxCnt"); 
		//System.out.print("------cxCnt------"+cxCnt);
		/*String OutCardAmount = request.getParameter("OutCardAmount");*/
		
		String deviceId  = request.getParameter("deviceId").toString();
		//System.out.print("------cardBala------"+deviceId);
		String cardBala = request.getParameter("cardBala").toString();
		//System.out.print("------cardBala------"+cardBala);
		String stuempno = request.getParameter("stuempno").toString();
		//System.out.print("------stuempno------"+stuempno);
		String cardId = request.getParameter("cardId").toString();
		//System.out.print("------cardId------"+cardId);
		 double cardBalaDoulbe = Double.parseDouble(cardBala)/100;
		/*if (null == cardId || null == money || null == serialNo
				|| "".equals(cardId) || "".equals(money) || "".equals(serialNo)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "请求数据错误!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}*/
		 
		
		
		 ServletContext app = request.getSession().getServletContext();
			if (app.getAttribute("pinkey") == null) {
				//logger.info("设备未登录");
				return mapping.findForward("devicelogon");
		} 
		 
		
	/*	String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			//logger.error("卡信息读取失败");
		}*/
		
		String feeAcc="";
		DB2DeviceDAO   deviceDao = new DB2DeviceDAO();
		try{
			 feeAcc =  deviceDao.getShopbyDeviceId(deviceId);
			 
		}catch(Exception e){
			
		}
		
		long xpackhandle = 0;
		int drtpno = 1;//第2组，drpt
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"cityhostportfunction", 9998);
		//System.out.print("------mainfunction------"+mainfunction);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"cityhostporttransfer", 900077);// 后台业务功能号
		//System.out.print("------func------"+func);
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "sclose_emp".getBytes(),
						Integer.parseInt("240112"));// 请求号
				
				bcc.SetIntFieldByName(xpackhandle, 0, "sserial0".getBytes(),
						Integer.parseInt(cardId));// 卡号
				//System.out.print("------cardId------"+cardId);
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
						cardBalaDoulbe);// 原卡值
				//System.out.print("------damt1------"+cardBalaDoulbe);
				
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						Double.parseDouble(TransAmount));// 交易金额
				//System.out.print("------damt0------"+Double.parseDouble(TransAmount));
				
				bcc.SetStringFieldByName(xpackhandle, 0,"sdate0".getBytes(),feeAcc.getBytes());//网络收费帐户
				//System.out.print("------sdate0----"+feeAcc);
				
				bcc.SetStringFieldByName(xpackhandle, 0,"scust_auth".getBytes(),stuempno.getBytes());//学工号
				//System.out.print("------scust_auth----"+stuempno);
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0"
						.getBytes(), Integer.parseInt(SerialNo));//流水号
				//System.out.print("------lvol0----"+Integer.parseInt(SerialNo));
				
			    bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						Integer.parseInt(cxCnt));// 交易次数
			   // System.out.print("------lvol3----"+Integer.parseInt(cxCnt));
                			
			    bcc.SetStringFieldByName(xpackhandle, 0,"semp_pwd".getBytes(),pwd.getBytes());//转帐密码
			   // System.out.print("------semp_pwd----"+pwd);
				
			    bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),deviceId.getBytes());//设备号
			   // System.out.print("------sorder2----"+deviceId);
			    
			    bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),	"web".getBytes());/// 操作员
			    
				
				
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				//System.out.print("------bccret----"+bccret);
				
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);
					
					System.out.print("-----"+RetCode[0]);
					System.out.print("-----"+vs_mess);
					
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							double[] OutCardAmountShow = new  double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), OutCardAmountShow);//入卡值
							//System.out.print("--OutCardAmountShow---"+OutCardAmountShow);
							
							
							double[] TransAmountShow = new  double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), TransAmountShow);//转账金额
							
							//System.out.print("--TransAmountShow---"+TransAmountShow);
							
							int[] SerialNoshow = new  int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), SerialNoshow);//流水号
							
							//System.out.print("--SerialNoshow---"+SerialNoshow);
							

							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0000", "转账成功", String.valueOf(TransAmountShow[0]),
									String.valueOf(OutCardAmountShow[0]), String.valueOf(SerialNoshow[0]), cardno, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							//System.out.print("--无数据返回--");
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回!"+RetCode[0], "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0002", vs_mess+RetCode[0], "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							if(108120==RetCode[0]){//终段未登录
								return mapping.findForward("devicelogon");
							}
							return null;
						} else {
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回,请稍后再试!"+RetCode[0], "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					}

				} else {
					// 请求失败

					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String s = new String(errmsg, 0, i);
						String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " +RetCode[0]+ s, "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1003",
					"系统出现异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			e.printStackTrace();
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1004",
					"系统初始化异常，请稍后重试！"+RetCode[0], "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
