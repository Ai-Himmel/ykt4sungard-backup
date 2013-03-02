package com.kingstargroup.fdykt.epay;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.DateUtil;

/**
 * 卡转电子钱输入
 * @author Xuan.Zhou
 *
 */
public class CtpEpayPutinAction extends Action {
	/**
	 * Logger for this class
	 */
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(PtcEpayTransAction.class);

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
		HttpSession session = request.getSession();
		String password = session.getAttribute("password").toString();
		String cardphyid = request.getParameter("cardphyid");//物理卡号
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String dptCnt = request.getParameter("dptCnt");
		String transflag = request.getParameter("transflag");
		String date = DateUtil.getNow();
		String sdate3 = date.substring(0, 8);
		String stime3 = date.substring(8, date.length());
		String ipServer = KSConfiguration.getInstance().getProperty("drtpip1", "172.0.0.1");
		String drtpPort = KSConfiguration.getInstance().getProperty("drtpport1", "4000");
		String svrFunc = KSConfiguration.getInstance().getProperty("mainfunction1", "6000");
		Integer outCardAmount = Integer.parseInt(cardBala)-Integer.parseInt(money)*100;
		String out_card_amount = outCardAmount.toString();
		if (cardphyid == null || "".equals(cardphyid)){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return mapping.findForward("logon");	
		}	
		
		try {
			request.setAttribute("password", Util.DESEnc(password));
		} catch (Exception e) {
			// TODO: handle exception
		}
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("dptCnt", dptCnt);
		request.setAttribute("transflag", transflag);
		request.setAttribute("sdate3", sdate3);
		request.setAttribute("stime3", stime3);
		request.setAttribute("ipServer", ipServer);
		request.setAttribute("drtpPort", drtpPort);
		request.setAttribute("svrFunc", svrFunc);
		request.setAttribute("outCardAmount", out_card_amount);
		
		
		
		return (mapping.findForward("success"));
	}
}

