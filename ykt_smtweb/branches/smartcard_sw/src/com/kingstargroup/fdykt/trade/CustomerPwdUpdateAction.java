// Created by Xslt generator for Eclipse.
// XSL :  not found (java.io.FileNotFoundException:  (Bad file descriptor))
// Default XSL used : easystruts.jar$org.easystruts.xslgen.JavaClass.xsl

package com.kingstargroup.fdykt.trade;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.Util;

import java.sql.SQLException;

/**
 * AccountSearchAction.java created by EasyStruts - XsltGen.
 * http://easystruts.sf.net
 * created on 01-18-2005
 *
 * XDoclet definition:
 * @struts:action path="/accountSearch" name="accountsearchForm" attribute="accountSearchForm" input="/accountSearch.jsp" validate="true"
 * @struts:action-forward name="/accountResult.jsp" path="/accountResult.jsp"
 */
public class CustomerPwdUpdateAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CustomerPwdUpdateAction.class);

	// --------------------------------------------------------- Instance Variables

	// --------------------------------------------------------- Methods

	/**
	 * Method execute
	 * @param ActionMapping mapping
	 * @param ActionForm form
	 * @param HttpServletRequest request
	 * @param HttpServletResponse response
	 * @return ActionForward
	 * @throws Exception
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		if (session.getAttribute("cardid") == null)
			return mapping.findForward("index");
		KSDaoSessionFactory.createSession();
		ActionForward forward = mapping.findForward("failure");
		try {
			if(doUpdatePswd(mapping, form, request)){
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			}
			else{
				KSDaoSessionFactory.rollback();
			}
		} catch (SQLException e) {
			logger.error("¸üÐÂ¿¨ÃÜÂëÊ§°Ü",e);
			e.printStackTrace();
		}
		return forward;
	}

	private boolean doUpdatePswd(ActionMapping mapping, ActionForm form, HttpServletRequest request) {
		HttpSession session = request.getSession();
		DB2CardDAO carddao = new DB2CardDAO();
		CustomerPwdUpdateForm customerPwdUpdateform = (CustomerPwdUpdateForm) form;
		// String cardPhysicalNo = (String) session.getAttribute("cardPhysicalNo");
		String cardId = (String)session.getAttribute("cardid");
		String newpwd = customerPwdUpdateform.getNewPwd();
		try {
			String ciphered = Util.DESEnc(newpwd);
			carddao.updateCardPassword(Integer.parseInt(cardId), ciphered);
			logger.debug(cardId + ":" + ciphered);
			request.setAttribute("newpwd", newpwd);
			return true;
		} catch (Exception e) {
			return false;
		}
	}
}
