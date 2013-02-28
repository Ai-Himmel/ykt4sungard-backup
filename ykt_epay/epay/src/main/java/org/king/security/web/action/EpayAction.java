package org.king.security.web.action;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.king.common.Configuration;
import org.king.framework.util.MyUtils;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.TEpayShopinfo;
import org.king.security.domain.TNetacc;
import org.king.security.service.PayManageService;
import org.king.security.service.SecurityService;
import org.king.security.service.ShopService;
import org.king.utils.BccUtil;
import org.king.utils.Contants;
import org.king.utils.DateUtil;

import com.kingstar.bcc.BccctlInit;
import com.kingstar.bcc.bccclt;

public class EpayAction extends BaseAction{
	private ShopService shopService;
	private PayManageService payManageService;
	public void setShopService(ShopService shopService) {
		this.shopService = shopService;
	}
	private SecurityService securityService;

	public void setSecurityService(SecurityService securityService) {
		this.securityService = securityService;
	}
	public void setPayManageService(PayManageService payManageService) {
		this.payManageService = payManageService;
	}
	//付款请求开始
	public ActionForward createepay(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		String v_shopid = request.getParameter("v_shopid");
		String v_oid = request.getParameter("v_oid");
		String v_amount = request.getParameter("v_amount");
		String v_currency = request.getParameter("v_currency");
		String v_url = request.getParameter("v_url");
		String v_code = request.getParameter("v_code");
		String v_date = request.getParameter("v_date");
		String v_time = request.getParameter("v_time");
		TEpayShopinfo tEpayShopinfo = null;
		//判断商户是否为空
		if(!MyUtils.isBlank(v_shopid)){
			tEpayShopinfo = shopService.gettShopinfoByid(Long.parseLong(v_shopid));
			if(tEpayShopinfo==null){
				this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
				request.setAttribute("v_returncode", "");
				return mapping.findForward("epayfaile");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
			request.setAttribute("v_returncode", "");
			return mapping.findForward("epayfaile");
		}
		String pv_code = v_shopid+v_oid+v_amount+v_currency+v_url;
		if(!MyUtils.isBlank(v_oid)&&!MyUtils.isBlank(v_amount)
				&&!MyUtils.isBlank(v_currency)&&!MyUtils.isBlank(v_url)&&!MyUtils.isBlank(v_code)
				&&!MyUtils.isBlank(v_date)&&!MyUtils.isBlank(v_time)){
			if(MyUtils.toMD5(pv_code+tEpayShopinfo.getKey()).equals(v_code)){
				request.setAttribute("shopname", tEpayShopinfo.getShowname());
				return mapping.findForward("topaylogin");
			}else{
				this.setReturnerrcodePara(request,  Contants.EPAY_ERROR_ILLEGAL_AUTH_CODE, "交易失败!");
				request.setAttribute("v_returncode", payManageService.epaymd5errorcode(v_oid, "-1", v_amount, v_currency, tEpayShopinfo.getKey()));
				return mapping.findForward("epayfaile");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
			request.setAttribute("v_returncode", payManageService.epaymd5errorcode(v_oid, "-1", v_amount, v_currency, tEpayShopinfo.getKey()));
			return mapping.findForward("epayfaile");
		}
	}
	//登陆请求
	public ActionForward login(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		saveToken(request);
		HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
		ActionMessages errors = new ActionMessages();
		String accno = request.getParameter("name");
		String pwd = request.getParameter("password");
		String v_shopid = request.getParameter("v_shopid");
		String v_account = accno;
		String v_oid = request.getParameter("v_oid");
		String v_amount = request.getParameter("v_amount");
		String v_currency = request.getParameter("v_currency");
		String v_url = request.getParameter("v_url");
		String v_code = request.getParameter("v_code");
		String v_date = request.getParameter("v_date");
		String v_time = request.getParameter("v_time");
		TEpayShopinfo tEpayShopinfo = null;
		//判断商户是否为空
		if(!MyUtils.isBlank(v_shopid)){
			tEpayShopinfo = shopService.gettShopinfoByid(Long.parseLong(v_shopid));
			if(tEpayShopinfo==null){
				this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
				request.setAttribute("v_returncode", "");
				return mapping.findForward("epayfaile");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
			request.setAttribute("v_returncode", "");
			return mapping.findForward("epayfaile");
		}
		request.setAttribute("v_returncode", payManageService.epaymd5errorcode(v_oid, "-1", v_amount, v_currency, tEpayShopinfo.getKey()));
		if(!MyUtils.isBlank(v_oid)&&!MyUtils.isBlank(v_amount)
				&&!MyUtils.isBlank(v_currency)&&!MyUtils.isBlank(v_url)&&!MyUtils.isBlank(v_code)
				&&!MyUtils.isBlank(v_date)&&!MyUtils.isBlank(v_time)){
			String pv_code = v_shopid+v_oid+v_amount+v_currency+v_url;
			if (!session.getAttribute("chkCode").equals(
					request.getParameter("chkCode"))) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"errors.chkCodeNoMatch"));
				saveErrors(request, errors);
				request.setAttribute("shopname", tEpayShopinfo.getShowname());
				return mapping.findForward("topaylogin");
			}
			TNetacc netacc = securityService.getNetaccByAccno(accno);
			if(netacc!=null&&netacc.getStatus()!=null&&MyUtils.toMD5(pwd).equals(netacc.getAccpwd())){
				if(netacc.getFailedcnt()>3||"2".equals(netacc.getStatus())){
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_LOCK, "交易失败!密码锁定!");
					return mapping.findForward("epayfaile");
				}
				if("0".equals(netacc.getStatus())){
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_SLEEP,"交易失败!账号未激活!");
					return mapping.findForward("epayfaile");
				}
				if("3".equals(netacc.getStatus())){
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_LOGOUT, "交易失败!账号已销户!");
					return mapping.findForward("epayfaile");
				}
				netacc.setFailedcnt(Long.valueOf(0));
				netacc.setLastlogintime(DateUtil.getNow());
				securityService.updateTnetacc(netacc);
				savalog(accno, "0", "交易登陆成功", request);
				if(MyUtils.toMD5(pv_code+tEpayShopinfo.getKey()).equals(v_code)){
					request.setAttribute("shopname", tEpayShopinfo.getShowname());
					request.setAttribute("availbal", netacc.getAvailbal());
					request.setAttribute("accname", netacc.getAccname());
					return mapping.findForward("epay");
				}else{
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_AUTH_CODE,"交易失败!");
					return mapping.findForward("epayfaile");
				}
			}else{
				if(netacc!=null&&"1".equals(netacc.getStatus())){
					Long times = netacc.getFailedcnt();
					if(times==null){
						netacc.setFailedcnt(Long.valueOf(1));
					}else{
						if(times>=3){
							netacc.setStatus("2");
							netacc.setLastblocktime(DateUtil.getNow());
						}
						netacc.setFailedcnt(netacc.getFailedcnt()+1);
					}
					securityService.updateTnetacc(netacc);
				}
				savalog(accno, "0", "交易登陆失败", request);
				errors.add("User login", new ActionMessage("errors.LoginError"));
				saveErrors(request, errors);
				request.setAttribute("shopname", tEpayShopinfo.getShowname());
				return mapping.findForward("topaylogin");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA,"交易失败!");
			return mapping.findForward("epayfaile");
		}
		
	}
	//支付请求
	public ActionForward epayend(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
		String accno = request.getParameter("name");
		ActionMessages errors = new ActionMessages();
		String v_shopid = request.getParameter("v_shopid");
		String v_account = accno;
		String v_oid = request.getParameter("v_oid");
		String v_amount = request.getParameter("v_amount");
		String v_currency = request.getParameter("v_currency");
		String v_url = request.getParameter("v_url");
		String v_code = request.getParameter("v_code");
		String v_date = request.getParameter("v_date");
		String v_time = request.getParameter("v_time");
		String v_name = request.getParameter("v_name");
		String v_remark = request.getParameter("v_remark");
		TEpayShopinfo tEpayShopinfo = null;
		//判断商户是否为空
		if(!MyUtils.isBlank(v_shopid)){
			tEpayShopinfo = shopService.gettShopinfoByid(Long.parseLong(v_shopid));
			if(tEpayShopinfo==null){
				this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
				request.setAttribute("v_returncode", "");
				return mapping.findForward("epayfaile");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA, "交易失败!");
			request.setAttribute("v_returncode", "");
			return mapping.findForward("epayfaile");
		}
		request.setAttribute("v_returncode", payManageService.epaymd5errorcode(v_oid, "-1", v_amount, v_currency, tEpayShopinfo.getKey()));
		//判断参数
		if(!MyUtils.isBlank(v_oid)&&!MyUtils.isBlank(v_amount)
				&&!MyUtils.isBlank(v_currency)&&!MyUtils.isBlank(v_url)&&!MyUtils.isBlank(v_code)
				&&!MyUtils.isBlank(v_date)&&!MyUtils.isBlank(v_time)){
			String pv_code = v_shopid+v_oid+v_amount+v_currency+v_url;
			String paypwd = request.getParameter("password");
			TNetacc netacc = securityService.getNetaccByAccno(accno);
			if(!this.isTokenValid(request,true)){
				request.setAttribute("accname", netacc.getAccname());
				this.setReturnerrcodePara(request, Contants.EPAY_ERROR_FRESHSUBMIT,"请不要重复提交!");
				return mapping.findForward("epayfaile");
			}
			//判断支付密码
			if(!MyUtils.isBlank(paypwd)&&MyUtils.toMD5(paypwd).equals(netacc.getPaypwd())&&netacc.getStatus()!=null){
				if(netacc.getFailedcnt()>3||"2".equals(netacc.getStatus())){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_LOCK,"交易失败!密码锁定!");
					return mapping.findForward("epayfaile");
				}
				if("0".equals(netacc.getStatus())){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_SLEEP, "交易失败!账号未激活!");
					return mapping.findForward("epayfaile");
				}
				if("3".equals(netacc.getStatus())){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request,  Contants.EPAY_ERROR_ACCOUNT_STUTS_LOGOUT, "交易失败!账号已销户!");
					return mapping.findForward("epayfaile");
				}
				if("".equals(netacc.getStoppayflag())||netacc.getStoppayflag()==null){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request,  Contants.EPAY_ERROR_ACCOUNT_ERROR,"交易失败!账户异常!");
					return mapping.findForward("epayfaile");
				}
				if("1".equals(netacc.getStoppayflag())){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_STUTS_STOP,"交易失败!账户已止付!");
					return mapping.findForward("epayfaile");
				}
				if(netacc.getAvailbal()<Double.valueOf(v_amount)){
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ACCOUNT_AVAILBAL_NOENOUGH,"付款失败,余额不足!");
					return mapping.findForward("epayfaile"); 
				}
				//判断密钥
				if(MyUtils.toMD5(pv_code+tEpayShopinfo.getKey()).equals(v_code)){
					//掉后台处理
					long xpackhandle = 0;
					int drtpno = 0;
					int errcode[] = { 1 };
					byte errmsg[] = new byte[300];
					int branchno = 0;// 后台drtp功能号
					int[] RetCode = new int[1];
					int[] RecordCount = new int[1];
					int mainfunction = Configuration.getIntProperty("mainfunction", 6000);
					int func = Configuration.getIntProperty("epay_trade_fun", 846340);// 后台业务功能号
					bccclt bcc = null;
					try{
						request.setAttribute("accname", netacc.getAccname());
						bcc = BccctlInit.getBccctlInstance();
						xpackhandle = bcc.NewXpackHandle(Configuration.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
						if (0 != xpackhandle) {
							bcc.SetRequestType(xpackhandle, func);
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(), Integer.valueOf(v_shopid));
							bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(), Configuration.getIntProperty("deviceid", 0));
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(), 0);
							bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(), accno.getBytes());
							bcc.SetStringFieldByName(xpackhandle, 0, "sbankname".getBytes(), v_oid.getBytes());
							bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(), Double.valueOf(v_amount));
							bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(), netacc.getPaypwd().getBytes());
							bcc.SetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(), v_date.getBytes());
							bcc.SetStringFieldByName(xpackhandle, 0, "stime0".getBytes(), v_time.getBytes());
							bcc.SetStringFieldByName(xpackhandle, 0, "sstock_code".getBytes(), v_currency.getBytes());
							boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno, mainfunction, 10000, errcode, errmsg);
							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
								if (0 == RetCode[0]) {
									if (0 < RecordCount[0]) {
										//成功
										double[] balance= new double[1];
										bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(), balance);
										request.setAttribute("v_returncode", payManageService.epaymd5errorcode(v_oid, "1", v_amount, v_currency, tEpayShopinfo.getKey()));
										request.setAttribute("accname", netacc.getAccname());
										log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
										request.setAttribute("balance", balance[0]);
										request.setAttribute("v_errcode", "");
										request.setAttribute("v_errmsg","");
										request.setAttribute("msg","");
										return mapping.findForward("epaysuccess");
									}else{
										//后台处理失败
										request.setAttribute("accname", netacc.getAccname());
										this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,"后台处理失败!");
										log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
										return mapping.findForward("epayfaile");
									}
								}else{
									//失败
									if (0 < RecordCount[0]) {
										byte[] vsmess = new byte[300];
										bcc.GetStringFieldByName(xpackhandle, 0, "vsmess".getBytes(), vsmess, 300);
										String vs_mess = BccUtil.getStringFromByte(vsmess);
										request.setAttribute("accname", netacc.getAccname());
										this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,vs_mess);
										log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
										return mapping.findForward("epayfaile");
									}else{
										//后台处理失败
										request.setAttribute("accname", netacc.getAccname());
										this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,"后台处理失败!");
										log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
										return mapping.findForward("epayfaile");
									}
								}
							}else{
								//后台通讯暂时不可用，请稍后重试！
								request.setAttribute("accname", netacc.getAccname());
								this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,"后台通讯暂时不可用，请稍后重试!");
								log.error("function:["+func+"],bccret:["+bccret+"];retcode:["+RetCode[0]+"];recordcount:["+RecordCount[0]+"]");
								return mapping.findForward("epayfaile");
							}
						}
						//系统出现异常，请稍后重试！
						request.setAttribute("accname", netacc.getAccname());
						this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,"系统出现异常，请稍后重试!");
						log.error("cpack包构建失败!");
						return mapping.findForward("epayfaile");
					}catch(Exception e){
						//系统出现异常，请稍后重试！
						request.setAttribute("accname", netacc.getAccname());
						this.setReturnerrcodePara(request,Contants.EPAY_ERROR_SERVER_ERROR,"系统出现异常，请稍后重试!");
						log.error(e);
						return mapping.findForward("epayfaile");
					}catch(UnsatisfiedLinkError e){
						//系统初始化异常，请稍后重试！
						request.setAttribute("accname", netacc.getAccname());
						this.setReturnerrcodePara(request, Contants.EPAY_ERROR_SERVER_ERROR,"系统初始化异常，请稍后重试!");
						log.error(e);
						return mapping.findForward("epayfaile");
					}finally{
						if (xpackhandle != 0) {
							bcc.DeleteXpackHandle(xpackhandle);
						}
					}
				}else{
					//可能是模仿的url
					request.setAttribute("accname", netacc.getAccname());
					this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_AUTH_CODE,"交易失败!");
					return mapping.findForward("epayfaile");
				}
			}else{
				errors.add("User login", new ActionMessage("errors.LoginError.wrongPwd"));
				saveErrors(request, errors);
				request.setAttribute("shopname", tEpayShopinfo.getShowname());
				request.setAttribute("availbal", netacc.getAvailbal());
				request.setAttribute("accname", netacc.getAccname());
				this.resetToken(request);
				this.saveToken(request);
				return mapping.findForward("epay");
			}
		}else{
			this.setReturnerrcodePara(request, Contants.EPAY_ERROR_ILLEGAL_PARA,"交易失败!");
			return mapping.findForward("epayfaile");
		}
	}
	
	private void setReturnerrcodePara(HttpServletRequest request,String v_errcode,String msg){
		String v_errmsg = payManageService.epayerrorcode(v_errcode);
		request.setAttribute("v_errcode", v_errcode);
		request.setAttribute("v_errmsg",v_errmsg);
		request.setAttribute("msg",msg);
	}
	
	public ActionForward returnurl(ActionMapping mapping, ActionForm form, 
			HttpServletRequest request, HttpServletResponse response) {
		HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
		ActionMessages errors = new ActionMessages();
		return null;
	}
	
}
