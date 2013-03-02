package com.kingstargroup.fdykt.trade;

import java.sql.SQLException;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class FeeBalanceAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = feebalance(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();   
		}
		return forward;
	}
	
	private  ActionForward feebalance(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		HttpSession session = request.getSession(true);
		String deviceId = request.getParameter("deviceId");
		//System.out.println("deviceId----------"+deviceId);
		String card_bala = request.getParameter("cardBala");
		//System.out.println("card_bala----------"+card_bala);
		String pwd = request.getParameter("password");
		//System.out.println("pwd----------"+pwd);
		String cxCnt = request.getParameter("cxCnt");
		//System.out.println("cxCnt----------"+cxCnt);
		String cardId = session.getAttribute("cardId").toString();
		//System.out.println("cardId----------"+cardId);
		String cardno = request.getParameter("cardno");
		//System.out.println("cardno----------"+cardno);
		
		double cardBala = Double.parseDouble(card_bala);
		cardBala = cardBala/100; 
		
	
		ServletContext  app = request.getSession().getServletContext();
		
		if(app.getAttribute("pinkey")==null){
			return mapping.findForward("devicelogon");
		}	
	
	
	if (deviceId == null || "".equals(deviceId)) {
		request.setAttribute("msg", "请管理员为本机，注册一个设备号");
		return mapping.findForward("returninfo");
	}
	
	long xpackhandle = 0;
	int drtpno = 1;// 第2组drtp
	int errcode[] = { 1 };
	byte errmsg[] = new byte[300];
	int branchno = 0;// 后台drtp功能号
	int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
			"bankmainfunction", 9998);
	int func = KSConfiguration.getInstance().getPropertyAsInt(
			"banktransferfunction", 900077);// 后台业务功能号
	int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);
	int[] RetCode = new int[1];
	int[] RecordCount = new int[1];
	bccclt bcc = null;
	try{
		bcc = BccctlInit.getBccctlInstance();
		// System.out.print("---bcc over----");
		xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
		if (0 != xpackhandle) {
			bcc.SetRequestType(xpackhandle, func);
			bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
					.getBytes(), "240116".getBytes());// 交易代码
			
			
			bcc.SetDoubleFieldByName(xpackhandle, 0,"damt0".getBytes(),cardBala);
			
			bcc.SetIntFieldByName(xpackhandle, 0, "sserial0".getBytes(),
					Integer.parseInt(cardId));// 卡号
			
			bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(),
					deviceId.getBytes());// 设备号
			
			bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(),
					pwd.getBytes());//密码
			
			bcc.SetIntFieldByName(xpackhandle, 0, "lvol3".getBytes(),
					Integer.parseInt(cxCnt));// 交易次数
			
			bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),"web".getBytes());/// 操作员
			
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
				
				if (0 == RetCode[0]) {
					if (0 < RecordCount[0]) {
						double[] OutCardAmount = new double[1];
						bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
								.getBytes(), OutCardAmount);//入卡值
						
						int writecard = BdUtil.YuantoFen(OutCardAmount[0]);
						//System.out.println("showmoney-----"+String.valueOf(OutCardAmount[0]));
						//System.out.println("writecardmoney-----"+String.valueOf(writecard));
						request.setAttribute("cardno",cardno);
						request.setAttribute("showmoney",String.valueOf(OutCardAmount[0]));
						request.setAttribute("writecardmoney",String.valueOf(writecard));
						request.setAttribute("cxCnt",String.valueOf(cxCnt));
						return mapping.findForward("success");
					}
				}else{
					String vs_mess = "";
					RetMessageUtil retmsg = new RetMessageUtil();
					vs_mess = retmsg.getMsg(RetCode[0]);
						// 失败
						if (0 < RecordCount[0]) {
							request.setAttribute("msg",vs_mess+RetCode[0]);
							return mapping.findForward("returninfo");
						} else {
							request.setAttribute("msg", "操作处理失败,无数据返回,请稍后重试");
							return mapping.findForward("returninfo");
						}
			        }
				}else{
					  //请求失败
					request.setAttribute("msg","后台通讯暂时不可用，请稍后重试!");
					return mapping.findForward("returninfo");
				}
			}else{
				request.setAttribute("msg","系统出现异常,暂时不可用,未找到cpack文件!");
				return mapping.findForward("returninfo");
			}
		request.setAttribute("msg","系统出现异常，请稍后重试！");
		return mapping.findForward("returninfo");

	}catch (UnsatisfiedLinkError e) {
		
		request.setAttribute("msg","系统初始化异常，请稍后重试！");
		return mapping.findForward("returninfo");
	}catch(Exception e){
		request.setAttribute("msg","系统出现异常，请稍后重试！");
		return mapping.findForward("returninfo");
	} finally {
		if (xpackhandle != 0) {
			bcc.DeleteXpackHandle(xpackhandle);
		}
	}	
  }
}