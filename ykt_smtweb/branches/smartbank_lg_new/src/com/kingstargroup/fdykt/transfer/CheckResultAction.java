package com.kingstargroup.fdykt.transfer;

import java.math.BigDecimal;
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
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.trade.GetSidyAction;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class CheckResultAction extends Action {
	
	private static final Logger logger = Logger.getLogger(GetSidyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = docheck(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		} 
		return forward;
	}

	private ActionForward docheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		if (isTokenValid(request, true)) {

		DB2CardDAO carddao = new DB2CardDAO();
		String card_bala = request.getSession().getAttribute("bala").toString();
		String cardno = request.getParameter("cardno").toString();
	    String money  = request.getParameter("money");
	    String bankno = request.getSession().getAttribute("bankno").toString();
	    String password  = request.getParameter("password").toString();
	    String ParamKey = request.getParameter("paramKey");
		if (null == cardno || null == money || null == bankno || null == password||null == card_bala || "".equals(card_bala)
				|| null == ParamKey
				|| "".equals(ParamKey)|| "".equals(cardno) || "".equals(money) || "".equals(bankno)||"".equals(password)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("7777", "请求数据错误", "", "",
					"", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		BigDecimal s = new BigDecimal(money);
		BigDecimal c = new BigDecimal("100");
		BigDecimal one = new BigDecimal("1");
		BigDecimal f = s.divide(one, 2, BigDecimal.ROUND_HALF_UP);
		String transmoney = String.valueOf(f.multiply(c).doubleValue());
		
		String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败"); 
			
			return mapping.findForward("failures");
		}
		long xpackhandle = 0;
		int drtpno = 1;//第2组，drtp
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("banktransfer", 90077);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			bcc.XPackInit(1);			
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
			
				
				bcc.SetIntFieldByName(xpackhandle, 0, "sserial0".getBytes(),
						Integer.parseInt(card.getCardId()));// 卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sstation0".getBytes(),
						password.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						transmoney.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth"
						.getBytes(), bankno.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						card_bala.getBytes());
				
				
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
						    
						
							byte[] outcardmoney = new byte[11];
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial1"
									.getBytes(), outcardmoney, 11);
							
							int[] serialno = new int[10];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), serialno);//流水号
							
							
							String serial_no = String.valueOf(serialno);
							
							int i = 0;
							
							for (i = 0; i < outcardmoney.length; i++) {
								if (0 == outcardmoney[i]) {
									break;
								}
							}
							
							String writecardmoney = new String(outcardmoney, 0, i);
							String xmlout = XMLGenerateUtil.XMLGenerate("0000","银行转账成功",
									"1",
									writecardmoney, serial_no, ParamKey,
									cardno, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return  null;
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}

							String vs_mess = new String(vsmess, 0, i);

							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess, "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", "", "", "", "", "", null);
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
					String msg = new String(errmsg, 0, i);
					
					logger.error("connect:errcode=" + errcode[0] + "msg=" + msg);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + msg, "", "", "", "", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		
		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}catch(UnsatisfiedLinkError e){
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1004",
					"系统初始化异常，请稍后重试！", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
			
		}		
	  }else{
		  return null;
	  }
      
	}

}
