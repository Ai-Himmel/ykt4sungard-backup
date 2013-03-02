package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BccUtil;

public class NetPutinAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(NetPutinAction.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try { 
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2AccountDAO accdao = new DB2AccountDAO();
		ActionErrors errors = new ActionErrors();	
		HttpSession session = request.getSession();
		String cardno = (String)session.getAttribute("cardno");
		String stuempno = request.getParameter("stuempno");		
		if(null==cardno){
			return mapping.findForward("index");
		}
		request.setAttribute("cardno", cardno);
		if (null == stuempno || "".equals(stuempno)) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","转账账号不能为空"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
			
		String reqip = request.getRemoteAddr();
//		reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);			
			if(deviceid<0){
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			logger.error("doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e1); //$NON-NLS-1$

			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}	
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_query", 3001);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		
		String loginName = KSConfiguration.getInstance().getProperty("loginName","");
		String loginPwd = KSConfiguration.getInstance().getProperty("loginPwd", "");
		String endpoint = KSConfiguration.getInstance().getProperty("endpoint", "http://localhost/csi/services/CamsWebService");
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				
				
				bcc.SetStringFieldByName(xpackhandle, 0, "vsvarstr0".getBytes(),
						endpoint.getBytes());// 第三方服务地址		
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// 第三方登录名				
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// 第三方登录密码				
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						stuempno.getBytes());// 第三方账号
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						String.valueOf(deviceid).getBytes());// 操作员
				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] inStr = new byte[300];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];
							
							Arrays.fill(inStr, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sall_name"
									.getBytes(), inStr, 300);
							String stuempname = BccUtil.getStringFromByte(inStr);	
							
							
							Arrays.fill(doubleRec, 0);
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), doubleRec);
							double curBalance =  doubleRec[0];
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), intRec);
							int feeType = intRec[0];
							
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), intRec);
							int state = intRec[0];
							
							request.setAttribute("stuempno", stuempno);
							request.setAttribute("stuempname", stuempname);							
							request.setAttribute("curBalance", String.valueOf(curBalance));
							String[] feeTypeArr = {"","","预付费","后付费","",""};
							if(feeType<4&&feeType>0){
								request.setAttribute("feeType", feeTypeArr[feeType]);
							}else{
								request.setAttribute("feeType", feeTypeArr[2]);
							}
							
							String[] statArr = {"","正常","暂停","注销","","",""};
							if(state<4&&state>0){
								request.setAttribute("state", String.valueOf(statArr[state]));
							}else{
								request.setAttribute("state", String.valueOf(statArr[1]));
							}
							if(state!=1){
								logger.info("查询bras账号：stuempno="+stuempno+",此账号已经"+String.valueOf(statArr[state]));
								errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","账号已经"+String.valueOf(statArr[state])+",不能转账"));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							}
							logger.info("查询bras账号：stuempno="+stuempno+"成功,stuempname["+stuempname+"]bala["+curBalance+"}");
							return mapping.findForward("success");

						} else {
							logger.info("查询bras账号：stuempno="+stuempno+"失败");
							errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","账号查询失败"));
							saveErrors(request, errors);
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error",vs_mess));
							saveErrors(request, errors);
							logger.info("查询bras账号：stuempno="+stuempno+"失败，错误信息["+vs_mess+"]");
							return mapping.findForward("failure");
							
						} else {
//							2002 用户不存在 
//							5002 没有可用的连接 
//							5003 没有操作权限 
//							5004 操作超时 
//							5005 操作员未登录 
//							50001 参数对象不能为空或其中的属性不能为空 
//							50002 参数内容不符合限制 
//							50003 参数长度不在限制范围之内 
//							50027 不能查询卡号用户信息 
//							50200 不能使用非法的组件 
							String retcode = String.valueOf(RetCode[0]);
							HashMap  errorcode = new HashMap();
							errorcode.put("2002", "用户不存在");
							errorcode.put("5002", "没有可用的连接 ");
							errorcode.put("5003", "没有操作权限 ");
							errorcode.put("5004", "操作超时");
							errorcode.put("5005", "操作员未登录");
							errorcode.put("50001", "参数对象不能为空或其中的属性不能为空");
							errorcode.put("50002", "参数内容不符合限制");
							errorcode.put("50003", "参数长度不在限制范围之内");
							errorcode.put("50027", "不能查询卡号用户信息");
							errorcode.put("50200", "不能使用非法的组件");			
							String errstr = errorcode.get(retcode)==null?"账号查询失败":errorcode.get(retcode).toString();
							errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error",errstr));
							saveErrors(request, errors);
							logger.info("查询bras账号：stuempno="+stuempno+"失败，错误信息["+errstr+"]");
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败

					String err_msg = BccUtil.getStringFromByte(errmsg);
					errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error",err_msg));
					saveErrors(request, errors);
					logger.info("查询bras账号：stuempno="+stuempno+"失败，错误信息["+err_msg+"]");
					return mapping.findForward("failure");

				}
			}
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","cpack初始化失败"));
			saveErrors(request, errors);
			logger.info("cpack初始化失败");
			return mapping.findForward("failure");

		} catch (Exception e) {
			logger.error("doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","系统初始化异常，请稍后重试"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error("doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error","系统初始化异常，请稍后重试"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
//		HttpSession session = request.getSession();
//		String cardno = (String)session.getAttribute("cardno");
//		request.setAttribute("cardno", cardno);
//		request.setAttribute("stuempno", "yikatong_test");
//		request.setAttribute("stuempname", "刘江峰");							
//		request.setAttribute("curBalance", String.valueOf("15.00"));
//		int feeType =2;
//		String[] feeTypeArr = {"","","预付费","后付费","",""};
//		if(feeType<4&&feeType>0){
//			request.setAttribute("feeType", feeTypeArr[feeType]);
//		}else{
//			request.setAttribute("feeType", feeTypeArr[2]);
//		}
//		int state=1;
//		String[] statArr = {"","正常","暂停","注销","","",""};
//		if(state<4&&state>0){
//			request.setAttribute("state", String.valueOf(statArr[state]));
//		}else{
//			request.setAttribute("state", String.valueOf(statArr[1]));
//		}
//		return mapping.findForward("success");
	}
}
