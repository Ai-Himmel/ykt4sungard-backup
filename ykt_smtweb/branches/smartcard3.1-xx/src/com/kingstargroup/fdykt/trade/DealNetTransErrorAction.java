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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class DealNetTransErrorAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DealNetTransErrorAction.class);

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
		DB2AccountDAO accdao = new DB2AccountDAO();
		String serialNo = request.getParameter("serialNo");
		String sdate3 = request.getParameter("sdate3");

		if (sdate3 == null) {
			sdate3 = DateUtil.getNow("yyyyMMdd");
		}

		if (serialNo == null || "".equals(serialNo)) {
			String xmlout = XMLGenerateUtil.XMLGenerate("2222", "请求信息格式不合法！",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
//		ActionErrors errors = new ActionErrors();
		
		String reqip = request.getRemoteAddr();
		
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);			
			if(deviceid<0){
				System.out.println("ip:"+reqip+"未注册，发送了冲正请求serialNo="+serialNo+" sdate3="+sdate3);
				String xmlout = XMLGenerateUtil.XMLGenerate("1001",
						"设备没注册，不能使用本功能！ ", "", "", "", "", "", "","",
						"", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("1001",
					"设备没注册，不能使用本功能！ ", "", "", "", "", "", "","",
					"", "", null);
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
				"logicfunc_net_trans_err", 846315);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
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
				bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
						.getBytes(), String.valueOf(deviceid).getBytes());//终端号				
				bcc.SetIntFieldByName(xpackhandle, 0, "lserial1".getBytes(),
						Integer.parseInt(serialNo));
				bcc.SetStringFieldByName(xpackhandle, 0, "sdate3".getBytes(),
						sdate3.getBytes());
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
								"流水冲正成功", "", "", "", "", "", "", "", "","",
								null);
						System.out.println("ip:"+reqip+"发送了冲正请求,冲正成功,serialNo="+serialNo+" sdate3="+sdate3);
						XMLGenerateUtil.XMLSendOut(request, response, xmlout);
						return null;

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
									vs_mess, "", "", "", "", "", "", "", "","",
									null);
							System.out.println("ip:"+reqip+"发送了冲正请求,处理失败RetCode="+RetCode[0]+",serialNo="+serialNo+" sdate3="+sdate3+"errormessage="+vs_mess);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", "", "", "", "", "", "", "", "","",
									null);
							System.out.println("ip:"+reqip+"发送了冲正请求,处理失败RetCode="+RetCode[0]+",serialNo="+serialNo+" sdate3="+sdate3+"，无返回错误信息");
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
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, "", "", "", "", "", "","",
							"", "", null);
					System.out.println("ip:"+reqip+"发送了冲正请求,处理失败 serialNo="+serialNo+" sdate3="+sdate3+",通讯失败");
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", "", "", "", "", "", "", "","", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			e.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "", "", "", "","", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}
