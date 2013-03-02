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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class DealTransferAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DealTransferAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dealSidyErr(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dealSidyErr(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		String serialNo = request.getParameter("serialno");
		
		String cardno = request.getSession().getAttribute("cardno").toString();
		
	    String bankno = request.getSession().getAttribute("bankno").toString();
	    
	    String password  = request.getSession().getAttribute("password").toString();
	    
	    String money = request.getSession().getAttribute("money").toString();
	    
	    BigDecimal s = new BigDecimal(money);
		BigDecimal c = new BigDecimal("100");
		BigDecimal one = new BigDecimal("1");
		BigDecimal f = s.divide(one, 2, BigDecimal.ROUND_HALF_UP);
		String transmoney = String.valueOf(f.multiply(c).doubleValue());
		
		if (serialNo == null || "".equals(serialNo)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("2222", "请求信息格式不合法！", "", "",
					"", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = 9000;
		int func = 847315;// 后台业务功能号
		int tries = 1;// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();

			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240107".getBytes());
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(serialNo));
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sserial0".getBytes(),
						cardno.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sstation0".getBytes(),
						password.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						transmoney.getBytes());
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth"
						.getBytes(), bankno.getBytes());

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

							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"卡状态重置成功", "",
									"", "", "",
									"", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
	

					} else {
						// 失败

							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"卡状态重置失败！请到卡务中心处理", "", "", "", "", "", null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
	
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
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
