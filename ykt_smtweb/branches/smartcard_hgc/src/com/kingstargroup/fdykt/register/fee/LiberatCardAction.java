package com.kingstargroup.fdykt.register.fee;

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
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class LiberatCardAction extends Action {

	private static final Logger logger = Logger
			.getLogger(LiberatCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = liberatcard(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward liberatcard(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2CardDAO carddao = new DB2CardDAO();
		String stuempno = request.getParameter("stuempno");
		String cardId = request.getParameter("cardId");
		String custno =  request.getParameter("custno");
	
		if (null == stuempno || null == cardId || null == custno || "".equals(stuempno)
				|| "".equals(cardId) || "".equals(custno)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "请求数据错误!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		/*String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
		}*/
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_elect_trans", 847118);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			
			if (0 != xpackhandle) {
			//	logger.info("22222222222222");  
				bcc.SetRequestType(xpackhandle, func);
				
				//logger.info("=======cardId==========="+cardId);
			
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),Integer.parseInt(cardId));// 交易卡号
				
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(custno));// 客户号
			//	logger.info("=========custno=========="+Integer.parseInt(custno));
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol2".getBytes(),Integer.parseInt("1"));//标志
			//	logger.info("4444444444444");
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_limit".getBytes(),
						"web".getBytes());// 操作员
			//	logger.info("555555555555555");
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),Integer.parseInt("0"));//主设备号
			//	logger.info("6666666666");
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),Integer.parseInt("0"));//设备号
			//	logger.info("33333333333");
				
			    boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
				//	logger.info("=============bccret==========="+bccret);
					if (bccret) {
						break; 
					}
					
				}
				if (bccret) {  
				//	logger.info("========bccret = true==============");
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							byte[] blkver = new byte[13];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);//返回信息
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial0"
									.getBytes(), blkver, 13);//返回信息
							
							int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}
							int j;
							for (j = 0; j < blkver.length; j++) {
								if (vsmess[j] == 0) {
									break;
								}
							}
							
							String vs_mess = new String(vsmess, 0, i,"GB2312");
							request.setAttribute("UndoLoss", "UndoLoss");
							request.setAttribute("blkver", new String(blkver,0,12));
							request.setAttribute("errmsg",vs_mess);
							return mapping.findForward("success");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
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
							String vs_mess = new String(vsmess, 0, i,"GB2312");
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败
					//logger.info("========bccret = false==============");
					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String s = new String(errmsg, 0, i,"GB2312");
					/*System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);*/
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}
		//	logger.error("============xpackhandle = 0==============");
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}