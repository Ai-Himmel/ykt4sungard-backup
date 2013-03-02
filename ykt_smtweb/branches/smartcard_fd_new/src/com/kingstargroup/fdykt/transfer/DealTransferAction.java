package com.kingstargroup.fdykt.transfer;

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
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.DesUtil;
import com.kingstargroup.fdykt.util.RetMessageUtil;

public class DealTransferAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(DealTransferAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		
		ActionForward forward = dealTransfer(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dealTransfer(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		if (isTokenValid(request, true)) {
		HttpSession session = request.getSession(true);
		ServletContext  app = request.getSession().getServletContext();
		String cardno = request.getParameter("cardno"); 
		String bankno = session.getAttribute("bankno").toString();
		String money = session.getAttribute("money").toString();
        String moneyFen = String.valueOf(Integer.parseInt(money)*100);
		String cardbala = request.getParameter("cardBala").toString();
		String cxCnt = request.getParameter("cxCnt").toString();
		
		while(moneyFen.length()<9){
			moneyFen = "0"+moneyFen;
		}
		
		
		//logger.info("BankCardNo=["+bankno+"]");
		
		String deviceId = request.getParameter("deviceId");
		if (deviceId == null ||"".equals(deviceId) ) {
		    request.setAttribute("msg","请管理员为本机，注册一个设备号");
			return mapping.findForward("returninfo");
		}
		
		if(app.getAttribute("pinkey")==null){
			return mapping.findForward("devicelogon");
		}
		
		String password  = request.getParameter("password").toString();
		
		byte[] pinkey = (byte[])app.getAttribute("pinkey");
		
		String despassword = null;
			try{
				despassword = DesUtil.getDesPassword(password,pinkey);
				//logger.info("BankCardPwd=["+despassword+"]");
			}catch(Exception e){
				request.setAttribute("msg","获取密钥失败，系统暂时无法使用");
			    return mapping.findForward("returninfo");
			}
	
		DB2CardDAO carddao = new DB2CardDAO();
		
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
			request.setAttribute("msg","转账失败，校园卡卡号不存在");
			return mapping.findForward("returninfo");
		}
		
		long xpackhandle = 0;
		int drtpno = 1;//第2组，drtp
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int bankmainfunction = KSConfiguration.getInstance().getPropertyAsInt("bankmainfunction", 9998);
		int func = KSConfiguration.getInstance().getPropertyAsInt("banktransferfunction", 900077);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 1);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			
			System.out.println("-------cardId-------------"+card.getCardId());
			bcc = BccctlInit.getBccctlInstance();
		
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240001".getBytes());//交易代码
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sserial0".getBytes(),
						card.getCardId().getBytes());// 校园卡卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sstation0".getBytes(),
						despassword.getBytes());//银行卡密码
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						moneyFen.getBytes());//交易金额
				
				//logger.info("-----交易金额-----"+moneyFen);
				System.out.println("-------交易金额-------------"+moneyFen);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_auth".getBytes(), bankno.getBytes());//银行卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sserial1".getBytes(),
						cardbala.getBytes());//校园卡帐户金额
				
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(cxCnt));//交易次数
				
				//logger.info("-----校园卡帐户金额-----"+cardbala);
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder2".getBytes(), deviceId.getBytes());//设备号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						 "web".getBytes());/// 操作员
			
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							bankmainfunction, 5000, errcode, errmsg);
					if (bccret) {
					
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					
					System.out.println("----RetCode[0]-------"+RetCode[0]);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] transmoney = new byte[9];
							bcc.GetStringFieldByName(xpackhandle, 0, "sorder0"
									.getBytes(), transmoney, 9);//交易金额,分	
							
							byte[] feemoney = new byte[9];
							bcc.GetStringFieldByName(xpackhandle, 0, "sorder1"
									.getBytes(), feemoney, 9);//搭伙费
							
							int[] SerialNo = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), SerialNo);//流水号
							
			
							int i = 0;
							for (i = 0; i < transmoney.length; i++) {
								if (0 == transmoney[i]) {
									break;
								}
							}
							
							
							int j = 0;
							for (j = 0; j < feemoney.length; j++) {
								if (0 == feemoney[j]) {
									break;
								}
							}
							
							
							double t_money=Double.parseDouble(new String(transmoney,0,i));//交易金额，此处已经扣除了搭伙费
							double f_money = Double.parseDouble(new String(feemoney,0,i));//搭伙费
							double card_bala = Double.parseDouble(cardbala)/100;//原卡余额
							
							double showMoney = card_bala+t_money;//交易后卡余额
							
							int writeCardmoney = BdUtil.YuantoFen(showMoney);
							
					        request.setAttribute("SerialNo",String.valueOf(SerialNo[0]));
							request.setAttribute("transmoney",String.valueOf(t_money));
							request.setAttribute("feemoney",String.valueOf(f_money));
							request.setAttribute("cardno",cardno);
		                    request.setAttribute("writecardmoney",String.valueOf(writeCardmoney));
		                    request.setAttribute("cxCnt",cxCnt);
		                    request.setAttribute("showmoney",String.valueOf(showMoney));
		                    request.setAttribute("deviceId",deviceId);
		                    request.setAttribute("cardId", card.getCardId());
							return mapping.findForward("success");
						} else {
							request.setAttribute("msg","无数据返回，系统异常"+RetCode[0]);
							return mapping.findForward("returninfo");
						}

					} else {
						String vs_mess = "";
						RetMessageUtil retmsg = new RetMessageUtil();
						vs_mess = retmsg.getMsg(RetCode[0]);
						// 失败
						if (0 < RecordCount[0]) {
							request.setAttribute("msg",vs_mess+RetCode[0]);
							if(108120==RetCode[0]){//终段未登录
								return mapping.findForward("devicelogon");
							}
							return mapping.findForward("returninfo");  
						} else {
							request.setAttribute("msg",vs_mess+RetCode[0]);
							return mapping.findForward("returninfo");
						}

					}

				} else {
					// 请求失败
					request.setAttribute("msg","后台通讯暂时不可用，请稍后重试!");
					return mapping.findForward("returninfo");
				}
			}
			request.setAttribute("msg","系统出现异常，请稍后重试！");
			return mapping.findForward("returninfo");
		
		} catch (UnsatisfiedLinkError e) {
			
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
	  }else{
		  return mapping.findForward("index");
	  }
	}
}

