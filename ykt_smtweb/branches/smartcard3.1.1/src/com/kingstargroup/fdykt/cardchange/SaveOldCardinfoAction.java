package com.kingstargroup.fdykt.cardchange;

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
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.trade.MobileCheckAction;
import com.kingstargroup.fdykt.util.BccUtil;

public class SaveOldCardinfoAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(MobileCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = saveinfo(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward saveinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		saveToken(request);

		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String card_bala = request.getParameter("cardBala");		
		String pay_card_cnt = request.getParameter("pay_card_cnt");
		String dpt_card_cnt = request.getParameter("dpt_card_cnt");		

		String showcardno = request.getParameter("showcardno");
		String oldcardphyid = request.getParameter("oldcardphyid");
		String newcardphyid = request.getParameter("newcardphyid");
		String pursetype1 = request.getParameter("pursetype1");
		String pursetype2 = request.getParameter("pursetype2");
		String pursetype3 = request.getParameter("pursetype3");
		String water_money1 = request.getParameter("water_money1");
		String water_money2 = request.getParameter("water_money2");
		String water_money3 = request.getParameter("water_money3");
		
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1",
		"172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty(
				"drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty(
				"mainfunction1", "6000");
		
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		
		request.setAttribute("newcardphyid", newcardphyid);
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("cardBala", card_bala);		
		request.setAttribute("pay_card_cnt", pay_card_cnt);
		request.setAttribute("dpt_card_cnt", dpt_card_cnt);		
		request.setAttribute("showcardno", showcardno);
		request.setAttribute("oldcardphyid", oldcardphyid);
		//核对老卡信息的正确性

		if(!oldcardphyid.equals(cardphyid)){
			//信息不对应？
			request.setAttribute("errmsg", "临时卡与正式卡对应信息不正确，<br><br>请核对后重新换卡！<br><br>如果仍不行，请到校园卡管理中心");
			return mapping.findForward("failure");
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
			request.setAttribute("errmsg", "卡信息读取失败");
			return mapping.findForward("failure");
		}
		
		if(card==null){
			request.setAttribute("errmsg", "找不到这张卡的相关信息，<br><br>请核对卡片是否被挂失<br><br>如果仍不行，请到校园卡管理中心");
			return mapping.findForward("failure");
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				request.setAttribute("errmsg", "设备未注册，不能使用此功能！");
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			request.setAttribute("errmsg", "设备未注册，不能使用此功能！");
			return mapping.findForward("failure");
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_changecard_oldcard", 846327);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						deviceid);// 客户端id
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "S".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(),
						Integer.parseInt("0"));// 补助批次号

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(dpt_card_cnt));// 交易次数(充值

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(pay_card_cnt));// 交易次数(消费

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// 卡余额

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						cardphyid.getBytes());//物理卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no2".getBytes(),
						newcardphyid.getBytes());//新卡物理卡号
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						showcardno.getBytes());//显示卡号
				if(pursetype1!=null&&!"0".equals(pursetype1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol10".getBytes(),
							pursetype1.getBytes());//水控钱包号
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							water_money1.getBytes());//水控钱包
				}
				if(pursetype2!=null&&!"0".equals(pursetype2)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol11".getBytes(),
							pursetype2.getBytes());//水控钱包号
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol2".getBytes(),
							water_money2.getBytes());//水控钱包
				}
				if(pursetype3!=null&&!"0".equals(pursetype3)){
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol12".getBytes(),
							pursetype3.getBytes());//水控钱包号
					bcc.SetStringFieldByName(xpackhandle, 0, "lvol3".getBytes(),
							water_money3.getBytes());//水控钱包
				}

				

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
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
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							request.setAttribute("errmsg", vs_mess);
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}
					}

				} else {
					// 请求失败
					String s = BccUtil.getStringFromByte(errmsg);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}

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
