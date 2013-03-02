package com.kingstargroup.fdykt.ncbanktransfer;

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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class NCDealTransCardExceptionAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(NCDealTransCardExceptionAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dealWaterTransErr(mapping, form, request,
				response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dealWaterTransErr(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		DB2AccountDAO accdao = new DB2AccountDAO();
		String sphone3 = request.getParameter("sphone3");
		String saddr = request.getParameter("saddr");
		String cardBala = request.getParameter("cardBala");
		String outCardAmount = request.getParameter("outCardAmount");
		String packetno = "0";

		if (sphone3 == null || "".equals(sphone3)||saddr == null || "".equals(saddr)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("2222", "请求信息格式不合法！",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		String reqip = request.getRemoteAddr();
//		reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				String xmlout = XMLGenerateUtil.XMLGenerate("3333", "设备未注册，不能使用此功能！",
						"", "", "", "", "", "", "", "","", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("3333", "设备未注册，不能使用此功能！",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_reportcardexception", 850002);// 后台业务功能号
//		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sphone3".getBytes(), sphone3.getBytes());
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(), saddr.getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(), Integer.parseInt(packetno));

				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), String.valueOf(deviceid).getBytes());// 客户端id
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(), Integer.parseInt(cardBala));
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol8".getBytes(), Integer.parseInt(outCardAmount));

				boolean bccret  = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {

						String xmlout = XMLGenerateUtil
								.XMLGenerate("0000", "写卡异常处理成功", "", "", "", "",
										"", "", "", "","", null);
						XMLGenerateUtil.XMLSendOut(request, response, xmlout);
						return null;

					} else {
						// 失败
						String xmlout = XMLGenerateUtil.XMLGenerate("0001",
								"写卡异常处理失败！请到卡务中心处理", "", "","", "", "", "", "", "",
								"", null);
						XMLGenerateUtil.XMLSendOut(request, response, xmlout);
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
					String s = new String(errmsg, 0, i);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, "", "","", "", "", "", "",
							"", "", null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", "", "", "", "", "", "","", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "", "", "","", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
