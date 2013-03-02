package com.kingstargroup.fdykt.trade;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;

import java.sql.SQLException;
import java.util.*;

public class LossQueryAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(LossQueryAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("failure");
		try {
			forward = doLossQuery(mapping, request);
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doLossQuery(ActionMapping mapping, HttpServletRequest request) {
		HttpSession session = request.getSession();
		String stuempno = (String) session.getAttribute("stuempno");
		try {
			if (null == stuempno || "".equals(stuempno))
				return mapping.findForward("logon");
			session.removeAttribute("card_id");
			session.removeAttribute("account");
			
			DB2AccountDAO accountdao = new DB2AccountDAO();
			ArrayList accounts = accountdao.getAccountInfo(stuempno);
			if(accounts.size() == 0){
				return (mapping.findForward("isnull"));
			}
			Iterator i = accounts.iterator();
			while(i.hasNext()){
				AccountDTO account = (AccountDTO) i.next();
				String state = account.getState_id();
				// 只有正常卡与写卡失败的卡可以挂失
				if(KSConstant.CARDSTAT_NORMAL.equals(state)||KSConstant.CARDSTAT_WFAIL.equals(state)){
					session.setAttribute("card_id", new Long(account.getCard_id()));
					session.setAttribute("account", account);
					return (mapping.findForward("success"));
				}
				else{
					request.setAttribute("card_id",new Long(account.getCard_id()));
					return (mapping.findForward("isnull"));
				}
				
			}
			return (mapping.findForward("isnull"));
			
		} catch (Exception e) {
			logger.error("查询挂失失败,stuemp_no[" + stuempno + "]");
			return (mapping.findForward("failure"));
		}
	}
}
