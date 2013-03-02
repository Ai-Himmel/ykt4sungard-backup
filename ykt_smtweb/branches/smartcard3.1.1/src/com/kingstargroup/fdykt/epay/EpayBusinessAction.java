package com.kingstargroup.fdykt.epay;

import java.sql.SQLException;

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

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2NetAccDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.NetAccDTO;

public class EpayBusinessAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(EpayBusinessAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = checklogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward checklogin(ActionMapping mapping, HttpServletRequest request) {
		HttpSession session = request.getSession();
		String cardphyid = (String) session.getAttribute("cardphyid");	
		String cardno = (String) session.getAttribute("cardno");
		String custid = (String) session.getAttribute("cutid");
		if (cardphyid == null || "".equals(cardphyid)){
			session.setAttribute("REQ_URL", request.getRequestURL());
			return mapping.findForward("logon");	
		}			
		
		request.setAttribute("cardphyid", cardphyid);
		DB2AccountDAO accountdao = new DB2AccountDAO();
		AccountDTO account = new AccountDTO();
		ActionErrors errors = new ActionErrors();
		try {
			account = accountdao.getAccountInfoByCardno(cardno);
			if(account==null){
				return (mapping.findForward("isaccnull"));
			}
		} catch (Exception e) {
			logger.error("查询客户信息失败");
			request.setAttribute("istrans", false);
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("查询客户信息失败"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		DB2NetAccDAO netaccdao = new DB2NetAccDAO();
		NetAccDTO netacc = new NetAccDTO();
		
		try {
			netacc = netaccdao.getNetAccInfoByCustid(custid);
			if(netacc==null){
				return (mapping.findForward("isnetaccnull"));
			}
		} catch (Exception e) {
			logger.error("查询电子钱包账户信息失败");
			request.setAttribute("istrans", false);
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.getnetacc"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		request.setAttribute("card_id", String.valueOf(account.getCardno()));
		request.setAttribute("account", account);
		request.setAttribute("netacc_no", String.valueOf(netacc.getAccno()));
		request.setAttribute("netacc", netacc);
		
		
		//如果不为正常卡
		if(!account.getCardstatus().equals("0000000000")){
			request.setAttribute("istrans", false);
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.cardstate"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		//如果电子钱包账户不正常
		if(!netacc.getStatus().equals(KSConstant.NETACC_STAT_NORMAL)){
			request.setAttribute("istrans", false);
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.netaccstate"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		request.setAttribute("istrans", true);
		return (mapping.findForward("success"));
	}
}
