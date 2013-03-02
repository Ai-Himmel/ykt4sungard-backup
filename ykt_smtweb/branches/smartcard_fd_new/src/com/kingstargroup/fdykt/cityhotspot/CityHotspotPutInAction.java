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
import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class CityHotspotPutInAction extends Action {

	private static final Logger logger = Logger
			.getLogger(CityHotspotPutInAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		HttpSession session = request.getSession(true);
		
		String money = request.getParameter("money");
		String card_bala = request.getParameter("cardBala");
		String cxCnt = request.getParameter("cxCnt");
		String pwd = request.getParameter("pwd").toString();
		String deviceId = request.getParameter("deviceId");
		String stuempno = session.getAttribute("stuempno").toString();
		//System.out.println("--putin---stuempno--------"+session.getAttribute("stuempno").toString());
		String cardId = session.getAttribute("cardId").toString();
		String cardno = request.getParameter("cardno");
		session.setAttribute("deviceId",deviceId);
		session.setAttribute("cardBala",card_bala);
		
		
		if (deviceId == null ||"".equals(deviceId) ) {
		    request.setAttribute("msg","请管理员为本机，注册一个设备号");
			return mapping.findForward("returninfo");
		}
		
		ServletContext app = request.getSession().getServletContext();
		if (app.getAttribute("pinkey") == null) {
			//logger.info("设备未登录");
			return mapping.findForward("devicelogon");
		}
		
		String feeAcc="";
		DB2DeviceDAO   deviceDao = new DB2DeviceDAO();
		try{
			 feeAcc =  deviceDao.getShopbyDeviceId(deviceId);
		}catch(Exception e){
			
		}
		if("".equals(feeAcc)){
			  request.setAttribute("msg","请管理员为本机，分配网络收费帐户");
			  return mapping.findForward("returninfo");
		}
	    
		double cardBala = Double.parseDouble(card_bala);
		cardBala = cardBala/100; 
		
		long xpackhandle = 0;
		int drtpno = 1;//第2组，drtp
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"bankmainfunction", 9998);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"banktransferfunction", 900077);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "sclose_emp".getBytes(),
						Integer.parseInt("240113"));// 请求号
				
				bcc.SetIntFieldByName(xpackhandle, 0, "sserial0".getBytes(),
						Integer.parseInt(cardId));// 卡号
				
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
						cardBala);// 原卡值
				
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						Double.parseDouble(money));// 交易金额
				
				
				bcc.SetStringFieldByName(xpackhandle, 0,"sdate0".getBytes(),feeAcc.getBytes());//网络收费帐户
				
				
				bcc.SetStringFieldByName(xpackhandle, 0,"scust_auth".getBytes(),stuempno.getBytes());//学工号
				
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
						Integer.parseInt(cxCnt));// 交易次数
                				
			    bcc.SetStringFieldByName(xpackhandle, 0,"semp_pwd".getBytes(),pwd.getBytes());//转帐密码
				
			    bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),deviceId.getBytes());//设备号
			    
			    bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),	"web".getBytes());/// 操作员
			    
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							double[] OutCardAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), OutCardAmount);//入卡值
							
						//	logger.info("-----OutCardAmount-----"+OutCardAmount[0]);
							
							double[] TransAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), TransAmount);//转账金额
						//	logger.info("-----TransAmount-----"+TransAmount[0]);
							
							int[] SerialNo = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), SerialNo);//流水号
							
							
							
						    request.setAttribute("OutCardAmount",String.valueOf(OutCardAmount[0]));
						    request.setAttribute("TransAmount",String.valueOf(TransAmount[0]));
						    request.setAttribute("SerialNo",String.valueOf(SerialNo[0]));
							request.setAttribute("cxCnt",cxCnt);
							request.setAttribute("cardno",cardno);
							request.setAttribute("pwd",pwd);
							return mapping.findForward("success");
						} else {
							request.setAttribute("errmsg", "后台处理失败"+RetCode[0]);
							return mapping.findForward("failure");
						}
					} else {
						// 失败
						if (0 < RecordCount[0]) {
							if(108120==RetCode[0]){//终段未登录
								return mapping.findForward("devicelogon");
							}
							request.setAttribute("errmsg", vs_mess+RetCode[0]);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "操作处理失败,无数据返回,请稍后重试");
							return mapping.findForward("failure");
						}
					}

				} else {
					// 请求失败
					request.setAttribute("errmsg", "请求失败，请稍后重试！ " +RetCode[0]);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，请稍后重试！"+RetCode[0]);
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！"+RetCode[0]);
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！"+RetCode[0]);
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}
